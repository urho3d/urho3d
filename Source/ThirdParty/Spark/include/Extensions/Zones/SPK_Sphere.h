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

#ifndef H_SPK_SPHERE
#define H_SPK_SPHERE

namespace SPK
{
	class SPK_PREFIX Sphere : public Zone
	{
	SPK_IMPLEMENT_OBJECT(Sphere)

	SPK_START_DESCRIPTION
	SPK_PARENT_ATTRIBUTES(Zone)
	SPK_ATTRIBUTE("radius",ATTRIBUTE_TYPE_FLOAT)
	SPK_END_DESCRIPTION

	public :

		static Ref<Sphere> create(const Vector3D& position = Vector3D(),float radius = 1.0f);

		////////////
		// Radius //
		////////////

		void setRadius(float radius);
		float getRadius() const;

		///////////////
		// Interface //
		///////////////

		virtual void generatePosition(Vector3D& v,bool full,float radius = 0.0f) const override;
		virtual bool contains(const Vector3D& v,float radius = 0.0f) const override;
		virtual bool intersects(const Vector3D& v0,const Vector3D& v1,float radius = 0.0f,Vector3D* normal = NULL) const override;
		virtual Vector3D computeNormal(const Vector3D& v) const override;

	protected :

		virtual void innerImport(const IO::Descriptor& descriptor) override;
		virtual void innerExport(IO::Descriptor& descriptor) const override;

	private :

		float radius;

		Sphere(const Vector3D& position = Vector3D(),float radius = 1.0f);
		Sphere(const Sphere& sphere);
	};

	inline Sphere::Sphere(const Vector3D& position,float radius) :
		Zone(position)
	{
		setRadius(radius);
	}

	inline Sphere::Sphere(const Sphere& sphere) :
		Zone(sphere),
		radius(sphere.radius)
	{}

	inline Ref<Sphere> Sphere::create(const Vector3D& position,float radius)
	{
		return SPK_NEW(Sphere,position,radius);
	}

	inline float Sphere::getRadius() const
	{
		return radius;
	}
}

#endif
