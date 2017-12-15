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
#include "Extensions/Modifiers/SPK_Obstacle.h"

namespace SPK
{
	Obstacle::Obstacle(const Ref<Zone>& zone,float bouncingRatio,float friction,ZoneTest zoneTest) :
		ZonedModifier(MODIFIER_PRIORITY_COLLISION,false,true,false,ZONE_TEST_FLAG_ALL & ~ZONE_TEST_FLAG_ALWAYS/*ZONE_TEST_FLAG_INTERSECT | ZONE_TEST_FLAG_ENTER | ZONE_TEST_FLAG_LEAVE*/,zoneTest,zone),
		bouncingRatio(bouncingRatio),
		friction(friction)
	{}

	Obstacle::Obstacle(const Obstacle& obstacle) :
		ZonedModifier(obstacle),
		bouncingRatio(obstacle.bouncingRatio),
		friction(obstacle.friction)
	{}

	void Obstacle::init(Particle& particle,DataSet* dataSet) const
	{
		switch(getZoneTest()) 
		{
		case ZONE_TEST_INSIDE :
		case ZONE_TEST_OUTSIDE :
			if (checkZone(particle))
				particle.kill(); // If the particle spawns inside a plain obstacle, it is killed
			break;

        default:
            // do nothing.
            break;
		}
	}

	void Obstacle::modify(Group& group,DataSet* dataSet,float deltaTime) const
	{
		Vector3D normal;
		for (GroupIterator particleIt(group); !particleIt.end(); ++particleIt)
		{
			if (checkZone(*particleIt,&normal))
			{ 
				particleIt->position() = particleIt->oldPosition();

				Vector3D& velocity = particleIt->velocity();

				float dist = dotProduct(velocity,normal);

				normal *= dist - 0.001f;
				velocity -= normal;			// tangent component
				velocity *= friction;
				normal *= bouncingRatio;	// normal component
				if (dist > 0.0f)
					normal.revert();
				velocity -= normal;
			}
		}
	}

	void Obstacle::innerImport(const IO::Descriptor& descriptor)
	{
		ZonedModifier::innerImport(descriptor);

		const IO::Attribute* attrib = NULL;
        if ((attrib = descriptor.getAttributeWithValue("bouncing ratio")))
			setBouncingRatio(attrib->getValue<float>());
        if ((attrib = descriptor.getAttributeWithValue("friction")))
			setFriction(attrib->getValue<float>());
	}

	void Obstacle::innerExport(IO::Descriptor& descriptor) const
	{
		ZonedModifier::innerExport(descriptor);
		descriptor.getAttribute("bouncing ratio")->setValue(getBouncingRatio());
		descriptor.getAttribute("friction")->setValue(getFriction());
	}
}
