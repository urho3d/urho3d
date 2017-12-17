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

#ifndef H_SPK_ZONE
#define H_SPK_ZONE

namespace SPK
{
	class Particle;

#ifdef SPK_DOXYGEN_ONLY // For documentation purpose only
	/** Constants defining the tests that can be performed for particles on zones */
	enum ZoneTest
	{
		ZONE_TEST_INSIDE,		/**< Is the particle inside the zone ? */
		ZONE_TEST_OUTSIDE,		/**< Is the particle outside the zone ? */
		ZONE_TEST_INTERSECT,	/**< Does the particle intersect the zone ? */
		ZONE_TEST_ENTER,		/**< Does the particle enter the zone ? */
		ZONE_TEST_LEAVE,		/**< Does the particle leave the zone ? */
		ZONE_TEST_ALWAYS,		/**< The test is always passed */
	};
#endif

	#define SPK_ENUM_ZONE_TEST(XX) \
		XX(ZONE_TEST_INSIDE,) \
		XX(ZONE_TEST_OUTSIDE,) \
		XX(ZONE_TEST_INTERSECT,) \
		XX(ZONE_TEST_ENTER,) \
		XX(ZONE_TEST_LEAVE,) \
		XX(ZONE_TEST_ALWAYS,) \

	SPK_DECLARE_ENUM(ZoneTest,SPK_ENUM_ZONE_TEST)

	class SPK_PREFIX Zone : public Transformable
	{

	SPK_START_DESCRIPTION
	SPK_PARENT_ATTRIBUTES(Transformable)
	SPK_ATTRIBUTE("position",ATTRIBUTE_TYPE_VECTOR)
	SPK_END_DESCRIPTION

	public :

		////////////////
		// Destructor //
		////////////////

		virtual  ~Zone() {}

		//////////////
		// Position //
		//////////////

		void setPosition(const Vector3D& position);
		const Vector3D& getPosition() const;
		const Vector3D& getTransformedPosition() const;

		///////////////
		// Interface //
		///////////////

		virtual void generatePosition(Vector3D& v,bool full,float radius = 0.0f) const = 0;
		virtual bool contains(const Vector3D& v,float radius = 0.0f) const = 0;
		virtual bool intersects(const Vector3D& v0,const Vector3D& v1,float radius = 0.0f,Vector3D* normal = NULL) const = 0;
		virtual Vector3D computeNormal(const Vector3D& v) const = 0;
		
		/**
		* Performs a check for a particle on the zone
		* @param particle : the particle which is tested
		* @param zoneTest : the type of test to perform
		* @param normal : A pointer to a vector used to store the normal (if NULL, the normal wont be computed)
		* @return true if the test is fullfilled, false otherwise
		*/
		bool check(const Particle& particle,ZoneTest zoneTest,Vector3D* normal = NULL) const;

	protected :

		Zone(const Vector3D& position = Vector3D());

        virtual void innerUpdateTransform() override;
		static  void normalizeOrRandomize(Vector3D& v);

        virtual void innerImport(const IO::Descriptor& descriptor) override;
        virtual void innerExport(IO::Descriptor& descriptor) const override;

	private :

		Vector3D position;
		Vector3D tPosition;

		typedef bool (Zone::*checkFn)(const Particle&,Vector3D* normal) const;
		static const size_t NB_TEST_TYPES = 6;
		static checkFn TEST_FN[NB_TEST_TYPES];

		bool checkInside(const Particle& particle,Vector3D* normal) const;
		bool checkOutside(const Particle& particle,Vector3D* normal) const;
		bool checkIntersect(const Particle& particle,Vector3D* normal) const;
		bool checkEnter(const Particle& particle,Vector3D* normal) const;
		bool checkLeave(const Particle& particle,Vector3D* normal) const;
		bool checkAlways(const Particle& particle,Vector3D* normal) const;
	};

	inline Zone::Zone(const Vector3D& position) :
		Transformable(),
		position(position)
	{
		transformPos(tPosition,position);	
	}

	inline void Zone::setPosition(const Vector3D& v)
	{
		position = v;
		transformPos(tPosition,position);
	}

	inline const Vector3D& Zone::getPosition() const
	{
		return position;
	}

	inline const Vector3D& Zone::getTransformedPosition() const
	{
		return tPosition;
	}

	inline bool Zone::check(const Particle &particle, ZoneTest zoneTest,Vector3D* normal) const
	{
		return (this->*Zone::TEST_FN[zoneTest])(particle,normal);
	}

	inline void Zone::innerUpdateTransform()
	{
		transformPos(tPosition,position);
	}

	inline void Zone::normalizeOrRandomize(Vector3D& v)
	{
		while(!v.normalize())
		{
			do v = SPK_RANDOM(Vector3D(-1.0f,-1.0f,-1.0f),Vector3D(1.0f,1.0f,1.0f));
			while (v.getSqrNorm() > 1.0f);
		}
	}

	inline void Zone::innerImport(const IO::Descriptor& descriptor)
	{
		Transformable::innerImport(descriptor);

		const IO::Attribute* attrib = NULL;

        if ((attrib = descriptor.getAttributeWithValue("position")))
			setPosition(attrib->getValue<Vector3D>());
	}

	inline void Zone::innerExport(IO::Descriptor& descriptor) const
	{
		Transformable::innerExport(descriptor);
		descriptor.getAttribute("position")->setValue(getPosition());
	}
}

#endif
