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
	SPKObject::SPKObject(SharePolicy SHARE_POLICY) :
		name(),
		nbReferences(0),
		SHARE_POLICY(SHARE_POLICY),
		shared(SHARE_POLICY == SHARE_POLICY_TRUE),
		copyBuffer(NULL)
	{
		SPK_LOG_DEBUG("Creation of SPKObject " << this);
	}

	SPKObject::SPKObject(const SPKObject& obj) :
		name(obj.name),
		nbReferences(0),
		SHARE_POLICY(obj.SHARE_POLICY),
		shared(obj.shared),
		copyBuffer(NULL)
	{
		SPK_LOG_DEBUG("Creation of SPKObject " << this << " from " << &obj);
	}

	SPKObject::~SPKObject()
	{
		SPK_LOG_DEBUG("Destruction of SPKObject " << this);
		SPK_ASSERT(nbReferences == 0,"SPKObject::~SPKObject() - The number of references of the object is not 0 during destruction");
	}

	void SPKObject::setShared(bool shared)
	{
		if (SHARE_POLICY != SHARE_POLICY_CUSTOM)
		{
			SPK_LOG_WARNING("SPKObject::setShared(bool) - This object cannot be set to be shared or not. Nothing happens");
			return;
		}

		this->shared = shared;
	}

	void SPKObject::importAttributes(const IO::Descriptor& descriptor)
	{
		const std::string& descName = descriptor.getName();
		if (descName != getClassName())
		{
			SPK_LOG_ERROR("SPKObject::importAttributes(const Descriptor&) - The descriptor does not match the object : \"" << descName << "\" for \"" << getClassName() << "\"");
		}
		else
			innerImport(descriptor);
	}

	IO::Descriptor SPKObject::exportAttributes() const
	{
		IO::Descriptor descriptor = createDescriptor();
		innerExport(descriptor);
		return descriptor;
	}

	IO::Descriptor SPKObject::createDescriptor() const
	{
		std::vector<IO::Attribute> attributes;
		fillAttributeList(attributes);
		IO::Descriptor descriptor(attributes);
		descriptor.setName(getClassName());
		SPK_LOG_DEBUG("Create descriptor for " << descriptor.getName() << " with " << descriptor.getNbAttributes() << " attributes and signature " << descriptor.getSignature());
		return descriptor;
	}

	void SPKObject::innerImport(const IO::Descriptor& descriptor)
	{
		const IO::Attribute* attrib = NULL;

        if ((attrib = descriptor.getAttributeWithValue("name")))
			setName(attrib->getValue<std::string>());

        if ((attrib = descriptor.getAttributeWithValue("shared")))
			setShared(attrib->getValue<bool>());
	}

	void SPKObject::innerExport(IO::Descriptor& descriptor) const
	{
		descriptor.getAttribute("name")->setValueOptionalOnEmpty(name);
		descriptor.getAttribute("shared")->setValueOptionalOnFalse(SHARE_POLICY == SHARE_POLICY_CUSTOM && isShared());
	}
}
