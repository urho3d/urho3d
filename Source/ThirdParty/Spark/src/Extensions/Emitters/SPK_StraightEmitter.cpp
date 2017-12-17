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
#include "Extensions/Emitters/SPK_StraightEmitter.h"

namespace SPK
{
	StraightEmitter::StraightEmitter(
			const Vector3D& direction,
			const Ref<Zone>& zone,
			bool full,
			int tank,
			float flow,
			float forceMin,
			float forceMax) :
		Emitter(zone,full,tank,flow,forceMin,forceMax)
	{
		setDirection(direction);
	}

	StraightEmitter::StraightEmitter(const StraightEmitter& emitter) :
		Emitter(emitter)
	{
		setDirection(emitter.direction);
	}

	void StraightEmitter::setDirection(const Vector3D& dir)
	{
		this->direction = dir;
		if (!this->direction.normalize())
			SPK_LOG_WARNING("StraightEmitter::setDirection(const Vector3D&) - The direction is a null vector");
		transformDir(tDirection,direction);
		tDirection.normalize();
	}

	void StraightEmitter::generateVelocity(Particle& particle,float speed) const
	{
		particle.velocity() = tDirection;
		particle.velocity() *= speed;
	}

	void StraightEmitter::innerUpdateTransform()
	{
		Emitter::innerUpdateTransform();
		transformDir(tDirection,direction);
		tDirection.normalize();
	}

	void StraightEmitter::innerImport(const IO::Descriptor& descriptor)
	{
		Emitter::innerImport(descriptor);

		const IO::Attribute* attrib = NULL;
        if ((attrib = descriptor.getAttributeWithValue("direction")))
			setDirection(attrib->getValue<Vector3D>());
	}

	void StraightEmitter::innerExport(IO::Descriptor& descriptor) const
	{
		Emitter::innerExport(descriptor);
		descriptor.getAttribute("direction")->setValue(getDirection());
	}
}
