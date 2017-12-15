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

#include <SPARK_Core.h>
#include "Extensions/IOConverters/SPK_IO_SPKSaver.h"

namespace SPK
{
namespace IO
{
	const char SPKSaver::MAGIC_NUMBER[3] = { 0x53, 0x50, 0x4B }; // "SPK" in ASCII
	const char SPKSaver::VERSION = 0;

	const size_t SPKSaver::DATA_LENGTH_OFFSET = 4;
	const size_t SPKSaver::HEADER_LENGTH = 12;

    bool SPKSaver::innerSave(std::ostream& os, Graph& graph, const std::string &filepath) const
	{
		IOBuffer output(2048);	// Output buffer
		IOBuffer buffer(256);	// buffer for objects writing

		// Header
		output.put(MAGIC_NUMBER,3);
		output.put(VERSION);
		output.skip(4); // Room for data length
		output.put(static_cast<uint32>(graph.getNbNodes()));

		// Writes objects
		Node* node = NULL;
		while ((node = graph.getNextNode()) != NULL)
		{
			buffer.clear();
			writeObject(buffer,node->getDescriptor(),graph);
			output.putBuffer(buffer);
		}

		// Writes data length
		output.setPosition(DATA_LENGTH_OFFSET);
		output.put(static_cast<uint32>(output.getSize() - HEADER_LENGTH));

		os.write(output.getData(),output.getSize()); // Writes the output buffer into the output stream
		return true;
	}

	bool SPKSaver::writeObject(IOBuffer& buffer,const Descriptor& desc,Graph& graph) const
	{
		buffer.put(desc.getName());	

		size_t lengthOffset = buffer.getPosition();
		buffer.skip(4); // Room for data length

		buffer.put(static_cast<uint32>(desc.getSignature()));

		for (size_t i = 0; i < desc.getNbAttributes(); ++i)
			writeAttribute(buffer,desc.getAttribute(i),graph);

		buffer.setPosition(lengthOffset);
		buffer.put(static_cast<uint32>(buffer.getSize() - lengthOffset - 4));
		return true;
	}

	bool SPKSaver::writeAttribute(IOBuffer& buffer,const Attribute& attrib,Graph& graph) const
	{
		bool defined = attrib.hasValue() && !attrib.isValueOptional();
		buffer.put(defined);

		if (defined)	
			switch (attrib.getType())
			{
			case ATTRIBUTE_TYPE_CHAR :		buffer.put(attrib.getValue<char>()); break;
			case ATTRIBUTE_TYPE_BOOL :		buffer.put(attrib.getValue<bool>()); break;
			case ATTRIBUTE_TYPE_INT32 :		buffer.put(attrib.getValue<int32>()); break;
			case ATTRIBUTE_TYPE_UINT32 :	buffer.put(attrib.getValue<uint32>()); break;
			case ATTRIBUTE_TYPE_FLOAT :		buffer.put(attrib.getValue<float>()); break;
			case ATTRIBUTE_TYPE_VECTOR :	buffer.put(attrib.getValue<Vector3D>()); break;
			case ATTRIBUTE_TYPE_COLOR :		buffer.put(attrib.getValue<Color>()); break;
			case ATTRIBUTE_TYPE_STRING :	buffer.put(attrib.getValue<std::string>()); break;	

			case ATTRIBUTE_TYPE_CHARS :		buffer.putArray(attrib.getValues<char>()); break;
			case ATTRIBUTE_TYPE_BOOLS :		buffer.putArray(attrib.getValues<bool>()); break;
			case ATTRIBUTE_TYPE_INT32S :	buffer.putArray(attrib.getValues<int32>()); break;
			case ATTRIBUTE_TYPE_UINT32S :	buffer.putArray(attrib.getValues<uint32>()); break;
			case ATTRIBUTE_TYPE_FLOATS :	buffer.putArray(attrib.getValues<float>()); break;
			case ATTRIBUTE_TYPE_VECTORS :	buffer.putArray(attrib.getValues<Vector3D>()); break;
			case ATTRIBUTE_TYPE_COLORS :	buffer.putArray(attrib.getValues<Color>()); break;
			case ATTRIBUTE_TYPE_STRINGS :	buffer.putArray(attrib.getValues<std::string>()); break;
			
			case ATTRIBUTE_TYPE_REF : {
				Node* refNode = graph.getNode(attrib.getValueRef<SPKObject>());
				if (refNode != NULL)
					buffer.put(static_cast<uint32>(refNode->getReferenceID()));
				break; }

			case ATTRIBUTE_TYPE_REFS : {
				const std::vector<Ref<SPKObject> >& refs = attrib.getValuesRef<SPKObject>();
				buffer.put(static_cast<uint32>(refs.size()));
				for (size_t i = 0; i < refs.size(); ++i)
				{
					Node* refNode = graph.getNode(refs[i]);
					if (refNode != NULL)
						buffer.put(static_cast<uint32>(refNode->getReferenceID()));
				}
				break; }

			default :
				SPK_LOG_FATAL("SPKSaver::writeAttribute(IOBuffer&,const Attribute&,Graph&) - Unknown attribute type");
			}

		return true;
	}
}}
