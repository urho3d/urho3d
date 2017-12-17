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

#include <algorithm> // for std::swap

#include <SPARK_Core.h>
#include "Extensions/Zones/SPK_Ring.h"

namespace SPK
{
	Ring::Ring(const Vector3D& position,const Vector3D& normal,float minRadius,float maxRadius) :
		Zone(position)
	{
		setNormal(normal);
		setRadius(minRadius,maxRadius);
	}

	Ring::Ring(const Ring& ring) :
		Zone(ring),
		minRadius(ring.minRadius),
		maxRadius(ring.maxRadius)
	{
		setNormal(ring.normal);
	}

	void Ring::setNormal(const Vector3D& n)
	{
		normal = n;
		normal.normalize();
		transformDir(tNormal,normal);
		tNormal.normalize();
	}

	void Ring::setRadius(float minRadius,float maxRadius)
	{
		if (minRadius < 0.0f || maxRadius < 0.0f)
		{
			SPK_LOG_WARNING("Ring::setRadius(float,float) - Radius cannot be negative - Values are inverted");
			minRadius = std::abs(minRadius);
			maxRadius = std::abs(maxRadius);
		}
		if (minRadius > maxRadius)
		{
			SPK_LOG_WARNING("Ring::setRadius(float,float) - minRadius is greater than maxRadius - Values are swapped");
			std::swap(minRadius,maxRadius);
		}
		this->minRadius = minRadius;
		this->maxRadius = maxRadius;
	}

	void Ring::generatePosition(Vector3D& v,bool full,float radius) const
	{
		float relMinRadius = minRadius + radius; 
		float relMaxRadius = maxRadius - radius;

		if (relMinRadius > relMaxRadius)
		{
			float relRadius = (relMinRadius + relMaxRadius) * 0.5f;
			relMinRadius = relMaxRadius = relRadius;
		}

		relMinRadius *= relMinRadius;
		relMaxRadius *= relMaxRadius;

		Vector3D tmp;
		do tmp = SPK_RANDOM(Vector3D(-1.0f,-1.0f,-1.0f),Vector3D(1.0f,1.0f,1.0f));
		while (tmp.getSqrNorm() > 1.0f);
		
		crossProduct(tNormal,tmp,v);
		normalizeOrRandomize(v);

		v *= std::sqrt(SPK_RANDOM(relMinRadius,relMaxRadius)); // to have a uniform distribution
		v += getTransformedPosition();
	}

	bool Ring::intersects(const Vector3D& v0,const Vector3D& v1,float radius,Vector3D* normal) const
	{
		Vector3D r0 = v0 - getTransformedPosition();
		float dist0 = dotProduct(tNormal,r0);
		
		if (std::abs(dist0) < radius)
			return false; // the particle is already intersecting the plane, the intersection is ignored

		Vector3D r1 = v1 - getTransformedPosition();
		float dist1 = dotProduct(tNormal,r1);

		if (std::abs(dist1) >= radius)
		{
			float dist1Bis = dist1;
			if (dist1Bis > 0.0f)
				dist1Bis -= radius;
			else
				dist1Bis += radius;

			if ((dist0 < 0.0f) == (dist1Bis < 0.0f)) // both particles are on the same side
				return false;
		}

		// The particle is intersecting the plane but is it within the ring ?
		// Projects on the ring's plane
		r0 -= dist0 * tNormal;
		r1 -= dist1 * tNormal;

		float minSqrRadius = minRadius - radius;
		float maxSqrRadius = maxRadius + radius;
		
		if (minSqrRadius > 0.0f)
			minSqrRadius *= minSqrRadius;
		maxSqrRadius *= maxSqrRadius;

		float r0SqrNorm = r0.getSqrNorm();
		float r1SqrNorm = r1.getSqrNorm();

		bool hasIntersection = ((r0SqrNorm >= minSqrRadius && r0SqrNorm <= maxSqrRadius) || (r1SqrNorm >= minSqrRadius && r1SqrNorm <= maxSqrRadius));
		if (hasIntersection && normal != NULL)
			*normal = (dist0 < 0.0f ? -tNormal : tNormal);
		return hasIntersection;
	}

	void Ring::innerUpdateTransform()
	{
		Zone::innerUpdateTransform();
		transformDir(tNormal,normal);
		tNormal.normalize();
	}

	void Ring::innerImport(const IO::Descriptor& descriptor)
	{
		Zone::innerImport(descriptor);

		const IO::Attribute* attrib = NULL;
        if ((attrib = descriptor.getAttributeWithValue("normal")))
			setNormal(attrib->getValue<Vector3D>());
        if ((attrib = descriptor.getAttributeWithValue("radius")))
		{
			std::vector<float> tmpRadius = attrib->getValues<float>();
			switch (tmpRadius.size())
			{
			case 1 : setRadius(tmpRadius[0],tmpRadius[0]); break;
			case 2 : setRadius(tmpRadius[0],tmpRadius[1]); break;
			default : SPK_LOG_ERROR("Ring::innerImport(const IO::Descriptor&) - Wrong number of radiuses : " << tmpRadius.size());
			}
		}
	}

	void Ring::innerExport(IO::Descriptor& descriptor) const
	{
		Zone::innerExport(descriptor);

		descriptor.getAttribute("normal")->setValue(getNormal());
		float tmpRadius[2] = {minRadius,maxRadius};
		descriptor.getAttribute("radius")->setValues(tmpRadius,2);
	}
}
