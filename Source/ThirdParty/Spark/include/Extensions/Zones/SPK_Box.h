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

#ifndef H_SPK_BOX
#define H_SPK_BOX

namespace SPK
{
	class SPK_PREFIX Box : public Zone
	{
	SPK_IMPLEMENT_OBJECT(Box)

	SPK_START_DESCRIPTION
	SPK_PARENT_ATTRIBUTES(Zone)
	SPK_ATTRIBUTE("dimensions",ATTRIBUTE_TYPE_VECTOR)
	SPK_ATTRIBUTE("up",ATTRIBUTE_TYPE_VECTOR)
	SPK_ATTRIBUTE("front",ATTRIBUTE_TYPE_VECTOR)
	SPK_END_DESCRIPTION

	public :
	
		static Ref<Box> create(
			const Vector3D& position = Vector3D(),
			const Vector3D& dimensions = Vector3D(1.0f,1.0f,1.0f),
			const Vector3D& front = Vector3D(0.0f,0.0f,1.0f),
			const Vector3D& up = Vector3D(0.0f,1.0f,0.0f));

		void setAxis(const Vector3D& front,const Vector3D& up = Vector3D(0.0f,1.0f,0.0f));

		void setDimensions(const Vector3D& dimensions = Vector3D());
		const Vector3D& getDimensions() const { return dimensions; }

		const Vector3D& getXAxis() const { return axis[0]; }
		const Vector3D& getYAxis() const { return axis[1]; }
		const Vector3D& getZAxis() const { return axis[2]; }

		const Vector3D& getTransformedXAxis() const { return tAxis[0]; }
		const Vector3D& getTransformedYAxis() const { return tAxis[1]; }
		const Vector3D& getTransformedZAxis() const { return tAxis[2]; }

		///////////////
		// Interface //
		///////////////

        virtual void generatePosition(Vector3D& v,bool full,float radius = 0.0f) const override;
        virtual bool contains(const Vector3D& v,float radius = 0.0f) const override;
        virtual bool intersects(const Vector3D& v0,const Vector3D& v1,float radius = 0.0f,Vector3D* normal = NULL) const override;
        virtual Vector3D computeNormal(const Vector3D& v) const override;

	protected :

        virtual void innerUpdateTransform() override;

		virtual void innerImport(const IO::Descriptor& descriptor) override;
		virtual void innerExport(IO::Descriptor& descriptor) const override;

	private :

		Vector3D dimensions;
		Vector3D halfDimensions; // Stores also the half dimensions to avoid always computing it

		Vector3D axis[3];
		Vector3D tAxis[3];

		Box(const Vector3D& position = Vector3D(),
			const Vector3D& dimensions = Vector3D(1.0f,1.0f,1.0f),
			const Vector3D& front = Vector3D(0.0f,0.0f,1.0f),
			const Vector3D& up = Vector3D(0.0f,1.0f,0.0f));
		Box(const Box& box);

		bool intersectSlab(float dist0,float dist1,float slab,const Vector3D& axis,float& minRatio,Vector3D* normal) const;
		Vector3D generateRandomDim(bool full,float radius) const; 
	};

	inline Ref<Box> Box::create(
		const Vector3D& position,
		const Vector3D& dimensions,
		const Vector3D& front,
		const Vector3D& up)
	{
		return SPK_NEW(Box,position,dimensions,front,up);
	}
}

#endif
