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

#ifndef H_SPK_DESTROYER
#define H_SPK_DESTROYER

namespace SPK
{
	/** @brief A Modifier that destroy particles */
	class Destroyer : public ZonedModifier
	{
	SPK_IMPLEMENT_OBJECT(Destroyer)

	public :

		/**
		* @brief Creates a new destroyer
		* @param zone : the zone
		* @param zoneTest : the zone test
		* @return A new destroyer
		*/
		static  Ref<Destroyer> create(const Ref<Zone>& zone = SPK_NULL_REF,ZoneTest zoneTest = ZONE_TEST_INSIDE);

	private :

		Destroyer(const Ref<Zone>& zone = SPK_NULL_REF,ZoneTest zoneTest = ZONE_TEST_INSIDE);
		Destroyer(const Destroyer& destroyer);

        virtual void init(Particle& particle,DataSet* dataSet) const override;
        virtual void modify(Group& group,DataSet* dataSet,float deltaTime) const override;
	};

	inline Ref<Destroyer> Destroyer::create(const Ref<Zone>& zone,ZoneTest zoneTest)
	{
		return SPK_NEW(Destroyer,zone,zoneTest);
	}

	inline Destroyer::Destroyer(const Ref<Zone>& zone,ZoneTest zoneTest) :
		ZonedModifier(MODIFIER_PRIORITY_COLLISION,false,true,false,ZONE_TEST_FLAG_ALL & ~ZONE_TEST_FLAG_ALWAYS,zoneTest,zone)
	{}

	inline Destroyer::Destroyer(const Destroyer& destroyer) :
		ZonedModifier(destroyer)
	{}

	inline void Destroyer::init(Particle& particle,DataSet* dataSet) const
	{
		if (checkZone(particle))
			particle.kill();
	}

	inline void Destroyer::modify(Group& group,DataSet* dataSet,float deltaTime) const
	{
		for (GroupIterator particleIt(group); !particleIt.end(); ++particleIt)
			if (checkZone(*particleIt))
				particleIt->kill();
	}
}

#endif
