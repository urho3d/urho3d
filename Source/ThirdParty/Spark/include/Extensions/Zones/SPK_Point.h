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

#ifndef H_SPK_POINT
#define H_SPK_POINT

namespace SPK
{
	class Point : public Zone
	{
	SPK_IMPLEMENT_OBJECT(Point);

	public :

		static Ref<Point> create(const Vector3D& position = Vector3D());

		virtual void generatePosition(Vector3D& v,bool full,float radius = 0.0f) const override;
		virtual bool contains(const Vector3D& v,float radius = 0.0f) const override;
		virtual bool intersects(const Vector3D& v0,const Vector3D& v1,float radius = 0.0f,Vector3D* normal = NULL) const override;
		virtual Vector3D computeNormal(const Vector3D& v) const override;

	private :

		Point(const Vector3D& position = Vector3D());
		Point(const Point& point);
	};

	inline Point::Point(const Vector3D& position) :
		Zone(position)
	{}

	inline Point::Point(const Point& point) :
		Zone(point)
	{}

	inline Ref<Point> Point::create(const Vector3D& position)
	{
		return SPK_NEW(Point,position);
	}

	inline void Point::generatePosition(Vector3D& v,bool full,float radius) const
	{
		v = getTransformedPosition();
	}

	inline bool Point::contains(const Vector3D& v,float radius) const
	{
		return false;
	}

	inline bool Point::intersects(const Vector3D& v0,const Vector3D& v1,float radius,Vector3D* normal) const
	{
		return false;
	}

	inline Vector3D Point::computeNormal(const Vector3D& v) const
	{
		Vector3D normal(v - getTransformedPosition());
		normalizeOrRandomize(normal);
		return normal;
	}
}

#endif
