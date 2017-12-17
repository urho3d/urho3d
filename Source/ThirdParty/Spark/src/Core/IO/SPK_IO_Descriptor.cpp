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

namespace SPK
{
namespace IO
{
	Descriptor::Descriptor(const std::vector<Attribute>& attributes) :
		attributes(attributes),
		name()
	{
		markAttributes();
		computeSignature();
	}

	Descriptor::Descriptor(const Descriptor& descriptor) :
		attributes(descriptor.attributes),
		buffer(descriptor.buffer),
		refBuffer(descriptor.refBuffer),
		signature(descriptor.signature),
		name(descriptor.name)
	{
		markAttributes();
	}

	Attribute* Descriptor::getAttribute(const std::string& name)
	{
		for (std::vector<Attribute>::iterator it = attributes.begin(); it != attributes.end(); ++it)
			if (it->getName() == name)
				return &*it;

		return NULL;
	}

	Attribute* Descriptor::getAttributeWithValue(const std::string& name)
	{
		Attribute* attrib = getAttribute(name);
		if (attrib != NULL && !attrib->hasValue())
			attrib = NULL;

		return attrib;
	}

	Attribute& Descriptor::getAttribute(size_t index)
	{
		SPK_ASSERT(index < attributes.size(),"Descriptor::getAttribute(size_t) - the index is out of bounds");
		return attributes[index];
	}

	void Descriptor::computeSignature()
	{
		signature = 0;

		// First a buffer is filled with the type and name of the attribute in order
		std::vector<char> buffer;
		for (std::vector<Attribute>::const_iterator it = attributes.begin(); it != attributes.end(); ++it)
		{
			buffer.push_back(static_cast<char>(it->getType()));
			buffer.insert(buffer.end(),it->getName().begin(),it->getName().end());
		}
		
		// Jenkins hash is sufficient to get a relevant signature on 32 bits
		for (std::vector<char>::const_iterator it = buffer.begin(); it != buffer.end(); ++it)
		{
			signature += *it;
			signature += (signature << 10);
			signature ^= (signature >> 6);
		}

		signature += (signature << 3);
		signature ^= (signature >> 11);
		signature += (signature << 15);
	}

	void Descriptor::markAttributes()
	{
		for (std::vector<IO::Attribute>::iterator it = attributes.begin(); it != attributes.end(); ++it)
			it->descriptor = this;
	}
}}
