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
#ifndef H_SPK_COLLIDER
#define H_SPK_COLLIDER

namespace SPK
{
	/**
	* @class Collider
	* @brief A Modifier that perfoms particle against particle collisions in the Group
	*
	* The collision between particles uses the size of the particle to determine its radius.<br>
	* <br>
	* Moreover the mass ratio of two particles colliding is used to get realistic collision.<br>
	* <br>
	* The collision can be set as being elastic or inelastic. This is determined thanks to the elasticity of this modifier :
	* <ul>
	* <li>An elasticity of 1.0f means the collision is fully elastic</li>
	* <li>An elasticity of 0.0f means the collision is fully inelastic</li>
	* <li>An elasticity superior to 1.0f means the collision creates energy. It is physically not possible but can however be set</li>
	* <li>An elasticity inferior to 0.0f has no sense and cannot be set</li>
	* <li>To simulate collisions the elasticity will generally be set between ]0.0f,1.0f[ depending on the material of the particle</li>
	* </ul>
	* Note that collision particle vs particles requires intensive processing.
	* Moreover the algorithm has a complexity that badly scales which means processing times increase fastly as particles count increase.<br>
	* Tries to limitate the number of particles to perform collision on. More than 1000 particles can require a lot of processing time even of recent hardware.<br>
	* <br>
	* The accuracy of the collisions is better with small update steps.
	* Therefore try to keep the update time small by for instance multiplying the number of updates per frame.
	*/
	class SPK_PREFIX Collider : public Modifier
	{
	SPK_IMPLEMENT_OBJECT(Collider)

	SPK_START_DESCRIPTION
	SPK_PARENT_ATTRIBUTES(Modifier)
	SPK_ATTRIBUTE("elasticity",ATTRIBUTE_TYPE_FLOAT)
	SPK_END_DESCRIPTION

	public :

		/////////////////
		// Constructor //
		/////////////////

		/**
		* @brief Creates and registers a new collider
		* @param elasticity : the elasticity of the collisions
		*/
		static  Ref<Collider> create(float elasticity = 1.0f);

		/////////////////
		// Elascticity //
		/////////////////

		/**
		* @brief Sets the elasticity of the collisions
		*
		* The elasticity of the collisions refers to the coefficient of restitution (also called bounciness).<br>
		* See the class description for more information.
		*
		* @param elasticity : the elasticity of the collisions
		*/
		void setElasticity(float elasticity);

		/**
		* @brief Gets the elasticity of the collisions
		* @return the elasticity of the collisions
		*/
		float getElasticity() const;

	protected :

		virtual void innerImport(const IO::Descriptor& descriptor) override;
		virtual void innerExport(IO::Descriptor& descriptor) const override;

	private :

		float elasticity;

		Collider(float elasticity = 1.0f);
		Collider(const Collider& collider);

		virtual void modify(Group& group,DataSet* dataSet,float deltaTime) const override;
	};

	inline Collider::Collider(float elasticity) :
		Modifier(MODIFIER_PRIORITY_COLLISION,false,false,true)
	{
		setElasticity(elasticity);
	}

	inline Collider::Collider(const Collider& collider) :
		Modifier(collider),
		elasticity(collider.elasticity)
	{}

	inline Ref<Collider> Collider::create(float elasticity)
	{
		return SPK_NEW(Collider,elasticity);
	}

	inline float Collider::getElasticity() const
	{
		return elasticity;
	}
}

#endif

