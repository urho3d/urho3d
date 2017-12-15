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
#include "Extensions/Zones/SPK_Plane.h"

namespace SPK
{
	void Plane::setNormal(const Vector3D& n)
	{
		normal = n;
		normal.normalize();
		transformDir(tNormal,normal);
		tNormal.normalize();
	}

	bool Plane::intersects(const Vector3D& v0,const Vector3D& v1,float radius,Vector3D* normal) const
	{
		float dist0 = dotProduct(tNormal,v0 - getTransformedPosition());
		
		if (std::abs(dist0) < radius)
			return false; // the particle is already intersecting the plane, the intersection is ignored

		float dist1 = dotProduct(tNormal,v1 - getTransformedPosition());
		if (std::abs(dist1) < radius)
		{
			if (normal != NULL)
				*normal = (dist0 < 0.0f ? -tNormal : tNormal);
			return true;
		}
		
		if (dist1 > 0.0f)
			dist1 -= radius;
		else
			dist1 += radius;

		if ((dist0 < 0.0f) == (dist1 < 0.0f)) // both particles are on the same side
			return false;

		if (normal != NULL)
			*normal = (dist0 < 0.0f ? -tNormal : tNormal);
		return true;
	}

	void Plane::innerUpdateTransform()
	{
		Zone::innerUpdateTransform();
		transformDir(tNormal,normal);
		tNormal.normalize();
	}

	void Plane::innerImport(const IO::Descriptor& descriptor)
	{
		Zone::innerImport(descriptor);

		const IO::Attribute* attrib = NULL;
        if ((attrib = descriptor.getAttributeWithValue("normal")))
			setNormal(attrib->getValue<Vector3D>());
	}

	void Plane::innerExport(IO::Descriptor& descriptor) const
	{
		Zone::innerExport(descriptor);
		descriptor.getAttribute("normal")->setValue(getNormal());
	}
}
