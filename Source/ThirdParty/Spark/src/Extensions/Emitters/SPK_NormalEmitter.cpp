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
#include "Extensions/Emitters/SPK_NormalEmitter.h"

namespace SPK
{
	NormalEmitter::NormalEmitter(
		const Ref<Zone>& zone,
		bool full,
		int tank,
		float flow,
		float forceMin,
		float forceMax,
		const Ref<Zone>& normalZone,
		bool inverted) :
		Emitter(zone,full,tank,flow,forceMin,forceMax),
		normalZone(),
		inverted(inverted)
	{
		setNormalZone(normalZone);
	}

	NormalEmitter::NormalEmitter(const NormalEmitter& emitter) :
		Emitter(emitter),
		inverted(emitter.inverted)
	{
		normalZone = emitter.copyChild(emitter.normalZone);
	}

	NormalEmitter::~NormalEmitter() {}

	void NormalEmitter::setNormalZone(const Ref<Zone>& zone)
	{
		normalZone = zone;
	}

	Ref<SPKObject> NormalEmitter::findByName(const std::string& name)
	{
		Ref<SPKObject> object = Emitter::findByName(name);
		if (object) return object;

		if (normalZone)
			object = normalZone->findByName(name);

		return SPK_NULL_REF;
	}

	void NormalEmitter::propagateUpdateTransform()
	{
		Emitter::propagateUpdateTransform();
		if (normalZone && !normalZone->isShared())
			normalZone->updateTransform(this);
	}

	void NormalEmitter::generateVelocity(Particle& particle,float speed) const
	{
		if (inverted) speed = -speed;
		const Ref<Zone>& zone = (!normalZone ? getZone() : normalZone);
		particle.velocity() = zone->computeNormal(particle.position()) * speed;
	}

	void NormalEmitter::innerImport(const IO::Descriptor& descriptor)
	{
		Emitter::innerImport(descriptor);

		const IO::Attribute* attrib = NULL;
        if ((attrib = descriptor.getAttributeWithValue("normal zone")))
			setNormalZone(attrib->getValueRef<Zone>());
        if ((attrib = descriptor.getAttributeWithValue("inverted normals")))
			setInverted(attrib->getValue<bool>());
	}

	void NormalEmitter::innerExport(IO::Descriptor& descriptor) const
	{
		Emitter::innerExport(descriptor);

		descriptor.getAttribute("normal zone")->setValueOptionalOnNull(getNormalZone());
		descriptor.getAttribute("inverted normals")->setValueOptionalOnFalse(isInverted());
	}
}
