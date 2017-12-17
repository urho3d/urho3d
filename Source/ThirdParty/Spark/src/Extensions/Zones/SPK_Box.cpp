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

#include <limits> // for max float value

#include <SPARK_Core.h>
#include "Extensions/Zones/SPK_Box.h"

namespace SPK
{
	Box::Box(const Vector3D& position,const Vector3D& dimensions,const Vector3D& front,const Vector3D& up) :
		Zone(position)
	{
		setDimensions(dimensions);
		setAxis(front,up);
	}

	Box::Box(const Box& box) :
		Zone(box),
		dimensions(box.dimensions),
		halfDimensions(box.halfDimensions)
	{
		for (size_t i = 0; i < 3; ++i)
		{
			axis[i] = box.axis[i];
			tAxis[i] = box.tAxis[i];
		}
	}

	void Box::setDimensions(const Vector3D& dimensions)
	{
		this->dimensions = dimensions;

		if (dimensions.x < 0.0f || dimensions.y < 0.0f || dimensions.z < 0.0f)
		{
			SPK_LOG_WARNING("Box::setDimensions(const Vector3D&) - The dimensions cannot be negative. Values are inversed");
			this->dimensions.abs();
		}

		halfDimensions = this->dimensions * 0.5f;
	}

	void Box::setAxis(const Vector3D& front,const Vector3D& up)
	{
		if (front == up || front.isNull() || up.isNull())
		{
			SPK_LOG_WARNING("Box::setAxis(const Vector3D&,const Vector3D&) - The axis cannot be null or equal. Default value is used");
			axis[1] = Vector3D(0.0f,1.0f,0.0f);
			axis[2] = Vector3D(0.0f,0.0f,1.0f);	
		}
		else 
		{
			axis[2] = front;
			axis[2].normalize();

			axis[1] = up;
		}

		axis[0] = crossProduct(axis[2],axis[1]);
		axis[0].normalize();
		axis[1] = crossProduct(axis[0],axis[2]);

		for (size_t i = 0; i < 3; ++i)
		{
			transformDir(tAxis[i],axis[i]);
			tAxis[i].normalize();
		}
	}

	Vector3D Box::generateRandomDim(bool full,float radius) const
	{
		if (full)
		{
			Vector3D relDimensions;
			relDimensions.setMax(halfDimensions - radius);
			return SPK_RANDOM(-relDimensions,relDimensions);
		}
		else
		{
			Vector3D randomDim(SPK_RANDOM(-halfDimensions,halfDimensions));
			size_t n = SPK_RANDOM(0,6);		// a random number from 0 to 5 included
			size_t axis = n >> 1;			// 1 chance out of 3
			int dir = ((n & 1) << 1) - 1;	// -1 or 1
			randomDim[axis] = dir * halfDimensions[axis];
			return randomDim;
		}
	}

	void Box::generatePosition(Vector3D& v,bool full,float radius) const
	{
		Vector3D randomDim(generateRandomDim(full,radius));

		v = getTransformedPosition();
		for (size_t i = 0; i < 3; ++i)
			v += randomDim[i] * tAxis[i];
	}

	bool Box::contains(const Vector3D& v,float radius) const
	{
		Vector3D d(v - getTransformedPosition());
		for (size_t i = 0; i < 3; ++i)
			if (std::abs(dotProduct(tAxis[i],d)) - radius > halfDimensions[i])
				return false;
		return true;
	}

	bool Box::intersectSlab(float dist0,float dist1,float slab,const Vector3D& axis,float& minRatio,Vector3D* normal) const
	{
		float d0 = slab - dist0;
		float d1 = slab - dist1;
        if ((d0 > 0.0f) != (d1 > 0.0f))
		{
			float ratio = d0 / (d0 - d1);
			if (ratio < minRatio)
			{
				minRatio = ratio;
				if (normal != NULL)
					*normal = (dist0 - dist1 > 0.0f) ? axis : -axis;
				return true;
			}
		}
		return false;
	}

	bool Box::intersects(const Vector3D& v0,const Vector3D& v1,float radius,Vector3D* normal) const
	{
		Vector3D d0(v0 - getTransformedPosition());
		Vector3D d1(v1 - getTransformedPosition());

		float minRatio = std::numeric_limits<float>::max();
		bool intersect = false;

		for (size_t i = 0; i < 3; ++i) 
		{
			float dist0 = dotProduct(tAxis[i],d0);
			float dist1 = dotProduct(tAxis[i],d1);
			float minDist,maxDist;

			if (dist1 - dist0 > 0.0f)
			{
				dist0 += radius;
				dist1 += radius;
				minDist = dist0;
				maxDist = dist1;
			}
			else
			{
				dist0 -= radius;
				dist1 -= radius;
				minDist = dist1;
				maxDist = dist0;
			}

			if (maxDist < -halfDimensions[i] || minDist > halfDimensions[i]) 
				return false;

			intersect |= intersectSlab(dist0,dist1,halfDimensions[i],tAxis[i],minRatio,normal);
			intersect |= intersectSlab(dist0,dist1,-halfDimensions[i],tAxis[i],minRatio,normal);
		}

		return intersect;
	}

	Vector3D Box::computeNormal(const Vector3D& v) const
	{
		const float MAX_FLOAT = std::numeric_limits<float>::max();

		Vector3D d(v - getTransformedPosition());
		Vector3D ratio(MAX_FLOAT,MAX_FLOAT,MAX_FLOAT);
		for (size_t i = 0; i < 3; ++i)
			if (halfDimensions[i] > 0.0f)
				ratio[i] = dotProduct(tAxis[i],d) / halfDimensions[i];
		
		Vector3D absRatio(ratio);
		absRatio.abs();

		size_t axisIndex = 0;
		if (absRatio.y > absRatio.x) axisIndex = 1;
		if (absRatio.z > absRatio[axisIndex]) axisIndex = 2;

		return ratio[axisIndex] > 0.0f ? -tAxis[axisIndex] : tAxis[axisIndex];
	}

	void Box::innerUpdateTransform()
	{
		Zone::innerUpdateTransform();
		
		for (size_t i = 0; i < 3; ++i)
		{
			transformDir(tAxis[i],axis[i]);
			tAxis[i].normalize();
		}
	}

	void Box::innerImport(const IO::Descriptor& descriptor)
	{
		Zone::innerImport(descriptor);

		const IO::Attribute* attrib = NULL;
        if ((attrib = descriptor.getAttributeWithValue("dimensions")))
			setDimensions(attrib->getValue<Vector3D>());
		
		Vector3D front = Vector3D(0.0f,0.0f,1.0f);
		Vector3D up = Vector3D(0.0f,1.0f,0.0f);

        if ((attrib = descriptor.getAttributeWithValue("front")))
			front = attrib->getValue<Vector3D>();
        if ((attrib = descriptor.getAttributeWithValue("up")))
			up = attrib->getValue<Vector3D>();

		setAxis(front,up);
	}

	void Box::innerExport(IO::Descriptor& descriptor) const
	{
		Zone::innerExport(descriptor);
		descriptor.getAttribute("dimensions")->setValue(getDimensions());
		descriptor.getAttribute("front")->setValue(getZAxis());
		descriptor.getAttribute("up")->setValue(getYAxis());
	}
}
