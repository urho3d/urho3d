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
#include "Extensions/Zones/SPK_Cylinder.h"

namespace SPK
{
	Cylinder::Cylinder(
		const Vector3D& position,
		float height,
		float radius,
		const Vector3D& axis) :
		Zone(position)
	{
		setDimensions(height,radius);
		setAxis(axis);
	}
	
	Cylinder::Cylinder(const Cylinder& cylinder) :
		Zone(cylinder),
		height(cylinder.height),
		radius(cylinder.radius),
		axis(cylinder.axis),
		tAxis(cylinder.tAxis),
		tNormal(cylinder.tNormal),
		tCoNormal(cylinder.tCoNormal)
	{}

	void Cylinder::setDimensions(float height,float radius) 
	{
		if (height <= 0.0f)
		{
			SPK_LOG_WARNING("Cylinder::setDimenisions(float,float) - The height cannot be negative. Default value is used");
			height = 1.0f;
		}

		if (radius <= 0.0f)
		{
			SPK_LOG_WARNING("Cylinder::setDimenisions(float,float) - The radius cannot be negative. Default value is used");
			radius = 1.0f;
		}

		this->height = height;
		this->radius = radius;
	}

	void Cylinder::setAxis(const Vector3D& axis)
	{
		if (axis.isNull())
		{
			SPK_LOG_WARNING("Cylinder::setAxis(const Vector3D&) - The axis cannot be null. Default value is used");
			this->axis.set(0.0f,1.0f,0.0f);
		}
		else
			this->axis = axis;

		this->axis.normalize();
		computeTransformedBase();
	}

	void Cylinder::computeTransformedBase()
	{
		transformDir(tAxis,axis);
		tAxis.normalize();

		// We dont really care about the base as soon as it is orthonormal
		Vector3D tmp(1.0f,0.0f,0.0f);
		if (tAxis == tmp) tmp.set(0.0f,1.0f,0.0f);

		tNormal = crossProduct(tAxis,tmp);
		tNormal.normalize();
		tCoNormal = crossProduct(tNormal,tAxis);
	}

	void Cylinder::computePointOnDisk(Vector3D& v,float radius) const
	{
		do v = SPK_RANDOM(-radius,radius) * tNormal + SPK_RANDOM(-radius,radius) * tCoNormal;
		while (v.getSqrNorm() > radius * radius);
	}

	void Cylinder::generatePosition(Vector3D& v,bool full,float radius) const
	{
		if (full)
		{
			float relRadius = this->radius - radius;
			if (relRadius <= 0.0f)
				v.set(0.0f);
			else
				computePointOnDisk(v,relRadius);	
		}
		else
		{
			do computePointOnDisk(v,1.0f);
			while (v.isNull());
			v *= this->radius / v.getNorm();
		}
		
		float relHeight = height * 0.5f - radius;
		v += SPK_RANDOM(-relHeight,relHeight) * tAxis;
		v += getTransformedPosition();
	}
	
	bool Cylinder::contains(const Vector3D& v,float radius) const
	{
		Vector3D d = v - getTransformedPosition();
		float tangentDist = dotProduct(d,tAxis);
		if (std::abs(tangentDist) - radius > height * 0.5f)
			return false;

		float normalSqrDist = (d - tangentDist * tAxis).getSqrNorm();
		float relRadius = this->radius - radius;
		return normalSqrDist <= relRadius * relRadius;   
	}

	bool Cylinder::intersects(const Vector3D& v0,const Vector3D& v1,float radius,Vector3D* normal) const
	{
		SPK_LOG_INFO("The intersection is not implemented yet with the Cylinder Zone");
		return false;
	}

	Vector3D Cylinder::computeNormal(const Vector3D& v) const
	{
		Vector3D normal = v - getTransformedPosition();
		float dist = dotProduct(normal,tAxis);
		if (dist > height * 0.5f) return tAxis;
		if (dist < -height * 0.5f) return -tAxis;

		normal -= dist * tAxis;
		if (normal.getSqrNorm() > radius * radius)
		{
			normal.normalize();
			return normal;
		}
		else
		{
			normalizeOrRandomize(normal);
			return -normal;
		}
	}

	void Cylinder::innerUpdateTransform()
	{
		Zone::innerUpdateTransform();
		computeTransformedBase();
	}

	void Cylinder::innerImport(const IO::Descriptor& descriptor)
	{
		Zone::innerImport(descriptor);

		const IO::Attribute* attrib = NULL;

		float height = this->height;
		float radius = this->radius;

        if ((attrib = descriptor.getAttributeWithValue("height")))
			height = attrib->getValue<float>();

        if ((attrib = descriptor.getAttributeWithValue("radius")))
			radius = attrib->getValue<float>();

		setDimensions(height,radius);

        if ((attrib = descriptor.getAttributeWithValue("axis")))
			setAxis(attrib->getValue<Vector3D>());
	}

	void Cylinder::innerExport(IO::Descriptor& descriptor) const
	{
		Zone::innerExport(descriptor);
		descriptor.getAttribute("height")->setValue(getHeight());
		descriptor.getAttribute("radius")->setValue(getRadius());
		descriptor.getAttribute("axis")->setValue(getAxis());
	}
}
