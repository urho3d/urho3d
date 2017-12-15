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

#ifndef H_SPK_CYLINDER
#define H_SPK_CYLINDER

namespace SPK
{
	class SPK_PREFIX Cylinder : public Zone
	{
	SPK_IMPLEMENT_OBJECT(Cylinder)

	SPK_START_DESCRIPTION
	SPK_PARENT_ATTRIBUTES(Zone)
	SPK_ATTRIBUTE("height",ATTRIBUTE_TYPE_FLOAT)
	SPK_ATTRIBUTE("radius",ATTRIBUTE_TYPE_FLOAT)
	SPK_ATTRIBUTE("axis",ATTRIBUTE_TYPE_VECTOR)
	SPK_END_DESCRIPTION

	public :
	
		static Ref<Cylinder> create(
			const Vector3D& position = Vector3D(),
			float height = 1.0f,
			float radius = 1.0f,
			const Vector3D& axis = Vector3D(0.0f,1.0f,0.0f));

		void setDimensions(float height,float radius);
		float getHeight() const	{ return height; }
		float getRadius() const	{ return radius; }

		void setAxis(const Vector3D& axis);
		const Vector3D& getAxis() const				{ return axis; }
		const Vector3D& getTransformedAxis() const	{ return tAxis; }

		virtual void generatePosition(Vector3D& v,bool full,float radius = 0.0f) const override;
		virtual bool contains(const Vector3D& v,float radius = 0.0f) const override;
		virtual bool intersects(const Vector3D& v0,const Vector3D& v1,float radius = 0.0f,Vector3D* normal = NULL) const override;
		virtual Vector3D computeNormal(const Vector3D& v) const override;

	protected :

		virtual void innerUpdateTransform() override;

		virtual void innerImport(const IO::Descriptor& descriptor) override;
		virtual void innerExport(IO::Descriptor& descriptor) const override;

	private :

		float height;
		float radius;

		Vector3D axis;
		Vector3D tAxis;
		Vector3D tNormal;
		Vector3D tCoNormal;

		Cylinder(
			const Vector3D& position = Vector3D(),
			float height = 1.0f,
			float radius = 1.0f,
			const Vector3D& axis = Vector3D(0.0f,1.0f,0.0f));
		Cylinder(const Cylinder& cylinder);

		void computeTransformedBase();
		void computePointOnDisk(Vector3D& v,float radius) const;
	};

	inline Ref<Cylinder> Cylinder::create(const Vector3D& position,float height,float radius,const Vector3D& axis)
	{
		return SPK_NEW(Cylinder,position,height,radius,axis);
	}
}

#endif
