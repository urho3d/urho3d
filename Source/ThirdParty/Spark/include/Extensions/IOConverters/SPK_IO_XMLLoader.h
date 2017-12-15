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

#ifndef H_SPK_IO_XMLLOADER
#define H_SPK_IO_XMLLOADER

#ifndef SPK_NO_XML

#include <sstream>

namespace pugi
{
	class xml_node;
	class xml_attribute;
}

namespace SPK
{
namespace IO
{
	/** @brief A class to deserialize a System from an XML document */
	class SPK_PREFIX XMLLoader : public Loader
	{
	private :

        virtual bool innerLoad(std::istream& is, Graph& graph, const std::string &path=0) const override;
        virtual bool innerLoadFromBuffer(Graph& graph, const char * data, unsigned int datasize) override;

		const std::string getValue(const pugi::xml_node& element) const;
		Ref<SPKObject> getRef(const pugi::xml_node& element,const std::map<int,size_t>& ref2Index,const Graph& graph) const;
		Ref<SPKObject> getObject(const pugi::xml_node& element,const std::vector<pugi::xml_node>& objElements,const Graph& graph) const;

		void findObjects(const pugi::xml_node& parent,std::vector<pugi::xml_node>& objElements,std::map<int,size_t>& ref2Index,bool objectLevel) const;
		void parseAttributes(const pugi::xml_node& element,Descriptor& desc,const Graph& graph,const std::vector<pugi::xml_node>& objElements,const std::map<int,size_t>& ref2Index) const;

		template<typename T> void setAttributeValue(Attribute& attribute,const pugi::xml_node& element) const;
		template<typename T> void setAttributeValueArray(Attribute& attribute,const pugi::xml_node& element) const;

		template<typename T> static bool convert(const std::string& str,T& value);
		template<typename T> static bool convert2Array(const std::string& str,std::vector<T>& values);
	};

	template<typename T>
	bool XMLLoader::convert(const std::string& str,T& value)
    {
        std::istringstream is(str);

        bool success = static_cast<bool>(is >> std::boolalpha >> value);
        int length = static_cast<int>(is.tellg());
        size_t strsize = str.size();

        bool result = ( success && ( (length == -1) || ((size_t)length == strsize)) );

        return result;
	}

	template<typename T>
	bool XMLLoader::convert2Array(const std::string& str,std::vector<T>& values)
	{
		values.clear();

		if (str.empty())
			return false;

		size_t oldPos = 0;
		size_t pos = 0;
		T tmp = T();

		do
		{
			pos = str.find(';',oldPos);
			std::string subStr = str.substr(oldPos,pos - oldPos);
			if (convert(subStr,tmp))
				values.push_back(tmp);
			oldPos = pos + 1;
		}
		while (pos != std::string::npos);

		return !values.empty();
	}

	template<typename T>
	void XMLLoader::setAttributeValue(Attribute& attribute,const pugi::xml_node& element) const
	{
		T tmp = T();
		const std::string value = getValue(element);
		if (value != "" && convert(value,tmp))
			attribute.setValue(tmp);
	}

	template<typename T>
	void XMLLoader::setAttributeValueArray(Attribute& attribute,const pugi::xml_node& element) const
	{
		std::vector<T> tmp;
		const std::string value = getValue(element);
		if (value != "" && convert2Array(value,tmp)) // Ok because convertArray ensures the vector is not empty
			attribute.setValues(&tmp[0],tmp.size());
	}

	// Specialization for bool as vector<bool> is handled differently in the standard (we cannot cast a vector<bool> to a bool* with &v[0])
	template<>
	void SPK_PREFIX XMLLoader::setAttributeValueArray<bool>(Attribute& attribute,const pugi::xml_node& element) const;
}}

#endif
#endif
