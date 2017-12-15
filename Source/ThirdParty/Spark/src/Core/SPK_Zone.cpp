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
	SPK_DEFINE_ENUM(ZoneTest,SPK_ENUM_ZONE_TEST)

	Zone::checkFn Zone::TEST_FN[Zone::NB_TEST_TYPES] =
	{
		&Zone::checkInside,
		&Zone::checkOutside,
		&Zone::checkIntersect,
		&Zone::checkEnter,
		&Zone::checkLeave,
		&Zone::checkAlways,
	};

	bool Zone::checkInside(const Particle& particle,Vector3D* normal) const
	{
		return contains(particle.position(),particle.getRadius());
	}

	bool Zone::checkOutside(const Particle& particle,Vector3D* normal) const
	{
		return !contains(particle.position(),-particle.getRadius());
	}

	bool Zone::checkIntersect(const Particle& particle,Vector3D* normal) const
	{
		return intersects(particle.oldPosition(),particle.position(),particle.getRadius(),normal);
	}

	bool Zone::checkEnter(const Particle& particle,Vector3D* normal) const
	{
		if (!contains(particle.oldPosition()))
			return intersects(particle.oldPosition(),particle.position(),particle.getRadius(),normal);
		return false;
	}

	bool Zone::checkLeave(const Particle& particle,Vector3D* normal) const
	{
		if (contains(particle.oldPosition()))
			return intersects(particle.oldPosition(),particle.position(),particle.getRadius(),normal);
		return false;
	}

	bool Zone::checkAlways(const Particle& particle,Vector3D* normal) const
	{
		return true;
	}
}
