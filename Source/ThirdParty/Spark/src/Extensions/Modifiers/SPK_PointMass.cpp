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
#include "Extensions/Modifiers/SPK_PointMass.h"

namespace SPK
{
	PointMass::PointMass(const Vector3D& pos,float mass,float offset) :
		Modifier(MODIFIER_PRIORITY_FORCE,false,false,false),
		mass(mass)
	{
		setPosition(pos);
		setOffset(offset);
	}

	PointMass::PointMass(const PointMass& pointMass) :
		Modifier(pointMass),
		mass(pointMass.mass),
		offset(pointMass.offset)
	{
		setPosition(pointMass.position);
	}

	void PointMass::setOffset(float offset)
	{
		if (offset <= 0.0f)
		{
			SPK_LOG_WARNING("PointMass::setOffset(float) - Offset must be superior to 0. Offset is set to 0.01f");
			offset = 0.01f;
		}

		this->offset = offset;
	}

	void PointMass::modify(Group& group,DataSet* dataSet,float deltaTime) const
	{
		float sqrOffset = offset * offset;
		float massSecond = mass * deltaTime;

		for (GroupIterator particleIt(group); !particleIt.end(); ++particleIt)
		{
			Particle& particle = *particleIt;
			Vector3D force = tPosition - particle.position();
			force *= massSecond / (force.getSqrNorm() + sqrOffset);
			particle.velocity() += force;
		}
	}

	void PointMass::innerImport(const IO::Descriptor& descriptor)
	{
		Modifier::innerImport(descriptor);

		const IO::Attribute* attrib = NULL;
        if ((attrib = descriptor.getAttributeWithValue("position")))
			setPosition(attrib->getValue<Vector3D>());
        if ((attrib = descriptor.getAttributeWithValue("mass")))
			setMass(attrib->getValue<float>());
        if ((attrib = descriptor.getAttributeWithValue("offset")))
			setOffset(attrib->getValue<float>());
	}

	void PointMass::innerExport(IO::Descriptor& descriptor) const
	{
		Modifier::innerExport(descriptor);
		descriptor.getAttribute("position")->setValue(getPosition());
		descriptor.getAttribute("mass")->setValue(getMass());
		descriptor.getAttribute("offset")->setValue(getOffset());
	}
}
