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

#include <algorithm> // for min

#include <SPARK_Core.h>
#include "Extensions/Zones/SPK_Sphere.h"

namespace SPK
{
	void Sphere::setRadius(float radius)
	{
		if (radius < 0)
		{
			radius = 0.0f;
			SPK_LOG_WARNING("Sphere::setRadius(float) - The radius cannot be set to a negative value - 0 is used");
		}
		this->radius = radius;
	}

	void Sphere::generatePosition(Vector3D& v,bool full,float radius) const
	{
		if (!full) 
		{
			do v = SPK_RANDOM(Vector3D(-1.0f,-1.0f,-1.0f),Vector3D(1.0f,1.0f,1.0f));
			while (v.getSqrNorm() > 1.0f || v.isNull());

			v *= this->radius / v.getNorm();
		}
		else 
		{
			const float relRadius = this->radius - radius;

			if (relRadius <= 0.0f) // The particle is larger than the sphere
				v.set(0.0f);
			else
			{
				do v = SPK_RANDOM(Vector3D(-relRadius,-relRadius,-relRadius),Vector3D(relRadius,relRadius,relRadius));
				while (v.getSqrNorm() > relRadius * relRadius);	
			}
		}

		v += getTransformedPosition();
	}

	bool Sphere::contains(const Vector3D& v,float radius) const
	{
		const float relRadius = this->radius - radius;
		return getSqrDist(getTransformedPosition(),v) <= relRadius * relRadius;
	}

	bool Sphere::intersects(const Vector3D& v0,const Vector3D& v1,float radius,Vector3D* normal) const
	{
		float r2 = this->radius * this->radius + radius * radius;
		float s2 = 2.0f * this->radius * radius;

		float dist0 = getSqrDist(getTransformedPosition(),v0);
		float dist1 = getSqrDist(getTransformedPosition(),v1);

		if (dist0 > r2 + s2) // the start sphere is completely out of the sphere
		{
			if (dist1 > r2 + s2) // the end sphere is completely out of the sphere
				return false;

			if (normal != NULL)
			{
				*normal = (v0 - getTransformedPosition());
				normalizeOrRandomize(*normal);
			}
			return true;
		}

		if (dist0 < r2 - s2) // the start sphere is completely in the sphere
		{
			if (dist1 < r2 - s2) // the end sphere is completely in the sphere
				return false;

			if (normal != NULL)
			{
				*normal = (getTransformedPosition() - v0);
				normal->normalize();
			}
			return true;
		}

		// the start sphere is already intersecting the sphere, the intersection is ignored
		return false;
	}

	Vector3D Sphere::computeNormal(const Vector3D& v) const
	{
		Vector3D normal(v - getTransformedPosition());
		normalizeOrRandomize(normal);
		if (contains(v))
			normal.revert();
		return normal;
	}

	void Sphere::innerImport(const IO::Descriptor& descriptor)
	{
		Zone::innerImport(descriptor);

		const IO::Attribute* attrib = NULL;
        if ((attrib = descriptor.getAttributeWithValue("radius")))
			setRadius(attrib->getValue<float>());
	}

	void Sphere::innerExport(IO::Descriptor& descriptor) const
	{
		Zone::innerExport(descriptor);
		descriptor.getAttribute("radius")->setValue(getRadius());
	}
}
