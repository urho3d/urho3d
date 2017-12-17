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

#ifndef H_SPK_PLANE
#define H_SPK_PLANE

namespace SPK
{
	/**
	* @class Plane
	* @brief A Zone defining a plane in the universe
	*
	* A Plane is defined by 2 parameters :
	* <ul>
	* <li>A Position is the universe</li>
	* <li>A Normal</li>
	* </ul>
	* The defined Plane is the Plane having the normal and passing by the position.<br>
	* The direction of the normal defines the sens of the plane. The normal goes from inside the Plane to outside.<br>
	* <br>
	* Note that the normal does not have to be normalized as it is normalized internally when set.
	*/
	class SPK_PREFIX Plane : public Zone
	{
	SPK_IMPLEMENT_OBJECT(Plane)

	SPK_START_DESCRIPTION
	SPK_PARENT_ATTRIBUTES(Zone)
	SPK_ATTRIBUTE("normal",ATTRIBUTE_TYPE_VECTOR)
	SPK_END_DESCRIPTION

	public :

		//////////////////
		// Constructors //
		//////////////////

		/**
		* @brief Creates a new Plane
		* @param position : the position of the Plane
		* @param normal : the normal of the Plane
		* @return a new plane
		*/
		static  Ref<Plane> create(const Vector3D& position = Vector3D(0.0f,0.0f,0.0f),const Vector3D& normal = Vector3D(0.0f,1.0f,0.0f));	

		////////////
		// Normal //
		////////////

		/**
		* @brief Sets the normal of this Plane
		*
		* Note that the normal is normalized internally.
		*
		* @param n : the normal of this Plane
		*/
		void setNormal(const Vector3D& n);

		/**
		* @brief Gets the normal of this Plane
		* @return the normal of this Plane
		*/
		const Vector3D& getNormal() const;

		/**
		* @brief Gets the transformed normal of this Plane
		* @return the transformed normal of this Plane
		*/
		const Vector3D& getTransformedNormal() const;

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

		Vector3D normal;	// normal
		Vector3D tNormal;	// transformed normal

		Plane(const Vector3D& position = Vector3D(0.0f,0.0f,0.0f),const Vector3D& normal = Vector3D(0.0f,1.0f,0.0f));
		Plane(const Plane& plane);
	};

	inline Plane::Plane(const Vector3D& position,const Vector3D& normal) :
		Zone(position)
	{
		setNormal(normal);
	}

	inline Plane::Plane(const Plane& plane) :
		Zone(plane)
	{
		setNormal(plane.normal);
	}

	inline Ref<Plane> Plane::create(const Vector3D& position,const Vector3D& normal)
	{
		return SPK_NEW(Plane,position,normal);
	}

	inline const Vector3D& Plane::getNormal() const
	{
		return normal;
	}

	inline const Vector3D& Plane::getTransformedNormal() const
	{
		return tNormal;
	}

	inline void Plane::generatePosition(Vector3D& v,bool full,float radius) const
	{
		v = getTransformedPosition();
	}

	inline bool Plane::contains(const Vector3D& v,float radius) const
	{
		return dotProduct(tNormal,v - getTransformedPosition()) <= radius;
	}

	inline Vector3D Plane::computeNormal(const Vector3D& point) const
	{
		return contains(point) ? -tNormal : tNormal;
	}
}

#endif
