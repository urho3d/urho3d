//
// SPARK particle engine
//
// Copyright (C) 2008-2011 - Julien Fryer - julienfryer@gmail.com
// Copyright (C) 2017 - Frederic Martin - fredakilla@gmail.com
//
// This software is provided 'as-is', without any express or implied
// warranty.  In no event will the authors be held liable for any damages
// arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented; you must not
//    claim that you wrote the original software. If you use this software
//    in a product, an acknowledgment in the product documentation would be
//    appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be
//    misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.
//

#ifndef SPK_NO_XML

#include <ctime>


//#include <Urho3D/ThirdParty/PugiXml/pugixml.hpp>
#include <pugixml.hpp>

#include <SPARK_Core.h>
#include "Extensions/IOConverters/SPK_IO_XMLLoader.h"

namespace SPK
{
namespace IO
{
    bool XMLLoader::innerLoad(std::istream& is,Graph& graph,const std::string& path) const
	{
		pugi::xml_document doc;
        //pugi::xml_parse_result result = doc.doc.load(is);
        pugi::xml_parse_result result = doc.load_file(path.c_str());

		if (!result)
		{
			SPK_LOG_ERROR("XMLLoader::innerLoad(std::istream&,Graph&) - Error while parsing XML : " << result.description() << " at character " << result.offset);
			return false;
		}

		const pugi::xml_node& root = doc.document_element();
		if (!root || std::string("SPARK") != root.name())
		{
			SPK_LOG_ERROR("XMLLoader::innerLoad(std::istream&,Graph&) - The root element is not conform (must be <SPARK>)");
			return false;
		}

		// Iterates in XML to find the objects and fill the graph
		std::vector<pugi::xml_node> objElements; // This will allow to find back objects description once created
		std::map<int,size_t> ref2Index; // This map allows to find back objects index in the vector from their reference id

		findObjects(root,objElements,ref2Index,true);
		for (size_t i = 0; i < objElements.size(); ++i)
			graph.addNode(i,std::string(objElements[i].name()));

		if (!graph.validateNodes())
			return false;

		// Fills up descriptors
		for (size_t i = 0; i < objElements.size(); ++i)
		{
			const pugi::xml_node& element = objElements[i];

			Node* node = graph.getNode(i);
			if (node != NULL)
			{
				Descriptor& desc = node->getDescriptor();
				parseAttributes(element,desc,graph,objElements,ref2Index);
			}
		}

		return true;
	}

    bool XMLLoader::innerLoadFromBuffer(Graph& graph, const char * data, unsigned int datasize)
    {
        pugi::xml_document doc;
        pugi::xml_parse_result result = doc.load_buffer(data, datasize);

        if (!result)
        {
            SPK_LOG_ERROR("XMLLoader::innerLoad(std::istream&,Graph&) - Error while parsing XML : " << result.description() << " at character " << result.offset);
            return false;
        }

        const pugi::xml_node& root = doc.document_element();
        if (!root || std::string("SPARK") != root.name())
        {
            SPK_LOG_ERROR("XMLLoader::innerLoad(std::istream&,Graph&) - The root element is not conform (must be <SPARK>)");
            return false;
        }

        // Iterates in XML to find the objects and fill the graph
        std::vector<pugi::xml_node> objElements; // This will allow to find back objects description once created
        std::map<int,size_t> ref2Index; // This map allows to find back objects index in the vector from their reference id

        findObjects(root,objElements,ref2Index,true);
        for (size_t i = 0; i < objElements.size(); ++i)
            graph.addNode(i,std::string(objElements[i].name()));

        if (!graph.validateNodes())
            return false;

        // Fills up descriptors
        for (size_t i = 0; i < objElements.size(); ++i)
        {
            const pugi::xml_node& element = objElements[i];

            Node* node = graph.getNode(i);
            if (node != NULL)
            {
                Descriptor& desc = node->getDescriptor();
                parseAttributes(element,desc,graph,objElements,ref2Index);
            }
        }

        return true;
    }

	const std::string XMLLoader::getValue(const pugi::xml_node& element) const
	{
		pugi::xml_attribute attr = element.attribute("value");
		if(!attr)
			return element.child_value();
		return attr.value();
	}

	Ref<SPKObject> XMLLoader::getRef(const pugi::xml_node& element,const std::map<int,size_t>& ref2Index,const Graph& graph) const
	{
		std::string tmpStr = element.attribute("ref").value();
		if(tmpStr == "")
			tmpStr = element.child_value();

		if (tmpStr == "") // No string value for ref is found
			return SPK_NULL_REF;

		int refID = -1;
		if (convert(tmpStr,refID))	// The string value can be converted into a refID
		{
			std::map<int,size_t>::const_iterator it = ref2Index.find(refID);
			if (it != ref2Index.end()) // The refID is found in the list of object
			{
				Node* node = graph.getNode(it->second);
				if (node != NULL)
					return node->getObject();
			}
		}

		return SPK_NULL_REF;
	}

	Ref<SPKObject> XMLLoader::getObject(const pugi::xml_node& element,const std::vector<pugi::xml_node>& objElements,const Graph& graph) const
	{
		if (element)
			for (size_t i = 0; i < objElements.size(); ++i) // This can be optimized in complexity by using a map
				if (objElements[i] == element)
				{
					Node* node = graph.getNode(i);
					if (node != NULL)
						return node->getObject();

				}

		return SPK_NULL_REF;
	}

	void XMLLoader::findObjects(const pugi::xml_node& parent,std::vector<pugi::xml_node>& objElements,std::map<int,size_t>& ref2Index,bool objectLevel) const
	{
		for(pugi::xml_node element = parent.first_child(); element; element = element.next_sibling())
		{
			if(objectLevel && std::string("attrib") != element.name() && std::string("Ref") != element.name())
			{
				objElements.push_back(element);
				int referenceID = -1;
				if(element.attribute("ref"))
				{
					referenceID = element.attribute("ref").as_int();
					if (!ref2Index.insert(std::make_pair(referenceID,objElements.size() - 1)).second)
						SPK_LOG_ERROR("XMLLoader::findObjects(const pugi::xml_node&,std::vector<const pugi::xml_node&>&,std::map<int,size_t>&,bool) - An object with an already used reference was found");
				}
			}

			findObjects(element,objElements,ref2Index,!objectLevel);
		}
	}

	void XMLLoader::parseAttributes(
		const pugi::xml_node& element,
		Descriptor& desc,
		const Graph& graph,
		const std::vector<pugi::xml_node>& objElements,
		const std::map<int,size_t>& ref2Index) const
	{
		// name
		std::string name = element.attribute("name").value();
		if (name != "")
			desc.getAttribute("name")->setValue(name); // We assume name attribute in descriptor exist

		for (pugi::xml_node attrib = element.first_child(); attrib; attrib = attrib.next_sibling())
			if (std::string("attrib") == attrib.name())
			{
				name = attrib.attribute("id").value();
				if (name != "")
				{
					Attribute* attribute = desc.getAttribute(name);
					if (attribute != NULL)
					{
						switch(attribute->getType())
						{
						case ATTRIBUTE_TYPE_CHAR :		setAttributeValue<char>(*attribute,attrib); break;
						case ATTRIBUTE_TYPE_BOOL :		setAttributeValue<bool>(*attribute,attrib); break;
						case ATTRIBUTE_TYPE_INT32 :		setAttributeValue<int32>(*attribute,attrib); break;
						case ATTRIBUTE_TYPE_UINT32 :	setAttributeValue<uint32>(*attribute,attrib); break;
						case ATTRIBUTE_TYPE_FLOAT :		setAttributeValue<float>(*attribute,attrib); break;
						case ATTRIBUTE_TYPE_VECTOR :	setAttributeValue<Vector3D>(*attribute,attrib); break;
						case ATTRIBUTE_TYPE_COLOR :		setAttributeValue<Color>(*attribute,attrib); break;
						case ATTRIBUTE_TYPE_STRING :	setAttributeValue<std::string>(*attribute,attrib); break;

						case ATTRIBUTE_TYPE_CHARS :		setAttributeValueArray<char>(*attribute,attrib); break;
						case ATTRIBUTE_TYPE_BOOLS :		setAttributeValueArray<bool>(*attribute,attrib); break;
						case ATTRIBUTE_TYPE_INT32S :	setAttributeValueArray<int32>(*attribute,attrib); break;
						case ATTRIBUTE_TYPE_UINT32S :	setAttributeValueArray<uint32>(*attribute,attrib); break;
						case ATTRIBUTE_TYPE_FLOATS :	setAttributeValueArray<float>(*attribute,attrib); break;
						case ATTRIBUTE_TYPE_VECTORS :	setAttributeValueArray<Vector3D>(*attribute,attrib); break;
						case ATTRIBUTE_TYPE_COLORS :	setAttributeValueArray<Color>(*attribute,attrib); break;
						case ATTRIBUTE_TYPE_STRINGS :	setAttributeValueArray<std::string>(*attribute,attrib); break;

						case ATTRIBUTE_TYPE_REF :
						{
							Ref<SPKObject> obj = getRef(attrib,ref2Index,graph);
							if (!obj)
								obj = getObject(attrib.first_child(),objElements,graph);
							if (obj)
								attribute->setValueRef(obj);
							break;
						}

						case ATTRIBUTE_TYPE_REFS :
						{
							std::vector<Ref<SPKObject> > objects;
							for (pugi::xml_node child = attrib.first_child(); child; child = child.next_sibling())
							{
								Ref<SPKObject> tmp;
								if (std::string("Ref") == child.name())
									tmp = getRef(child,ref2Index,graph);
								else
									tmp = getObject(child,objElements,graph);
								if (tmp)
									objects.push_back(tmp);
							}
							if (!objects.empty())
								attribute->setValuesRef(&objects[0],objects.size());
							break;
						}

						default : SPK_LOG_FATAL("XMLLoader::parseAttributes(const pugi::xml_node&,Descriptor&,const Graph&,const std::vector<const pugi::xml_node&>&,const std::map<int,size_t>&) - Unknown attribute type");
						}
					}
					else SPK_LOG_WARNING("XMLLoader::parseAttributes(const pugi::xml_node&,Descriptor&,const Graph&,const std::vector<const pugi::xml_node&>&,const std::map<int,size_t>&) - The attribute \"" << name << "\" does not exist");
				}
			}
	}

	template<>
	void XMLLoader::setAttributeValueArray<bool>(Attribute& attribute,const pugi::xml_node& element) const
	{
		std::vector<bool> tmp;
		const std::string value = getValue(element);
		if (value != "" && convert2Array(value,tmp)) // Ok because convertArray ensures the vector is not empty
		{
			bool* buffer = SPK_NEW_ARRAY(bool,tmp.size());
			for (size_t i = 0; i < tmp.size(); ++i)
				buffer[i] = tmp[i];
			attribute.setValues(buffer,tmp.size());
			SPK_DELETE_ARRAY(buffer);
		}
	}
}}

#endif
