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

#ifndef H_SPK_MODIFIER
#define H_SPK_MODIFIER

namespace SPK
{
	class Particle;
	class Group;

	/** @brief Constants defining the priority of a modifier */
	enum ModifierPriority
	{
		MODIFIER_PRIORITY_POSITION = 10,		/**< The modifier modifies the position of a particle */
		MODIFIER_PRIORITY_FORCE = 20,			/**< The modifier modifies the velocity of a particle */
		MODIFIER_PRIORITY_COLLISION = 30,		/**< The modifier checks the position/velocity of particles and can modify them */
		MODIFIER_PRIORITY_FRICTION = 40,		/**< The modifier applies a threshold over velocity */
		MODIFIER_PRIORITY_CHECK = 50,			/**< The modifier performs checks over parameters */
	};

	/**
	* @brief An abstract class that allows to modify the behaviour of a group of particles over time
	*
	* 
	*/
	class Modifier :	public Transformable,
						public DataHandler
	{
	friend class Group;

	SPK_START_DESCRIPTION
	SPK_PARENT_ATTRIBUTES(Transformable)
	SPK_ATTRIBUTE("active",ATTRIBUTE_TYPE_BOOL)
	SPK_ATTRIBUTE("local",ATTRIBUTE_TYPE_BOOL)
	SPK_END_DESCRIPTION

	public :

		virtual  ~Modifier() {}

		void setActive(bool active);
		bool isActive() const;

		/**
		* @brief Sets whether to consider this modifier local to a system or not
		* A local modifier is transformed when its system is transformed, a non local one will not.
		* @param local : true to consider the modifier local, false not to
		*/
		void setLocalToSystem(bool local);

		/**
		* @brief Tells whether this modifier is considered as being local to a system or not
		* A local modifier is transformed when its system is transformed, a non local one will not.
		* @return true if it is local, false if not
		*/
		bool isLocalToSystem() const;

		/**
		* @brief Gets the priority
		* The priority defines the order in which modifiers are applied (the lower, the sooner)
		* @return the priority
		*/
		unsigned int getPriority() const;

	protected :

		Modifier(unsigned int PRIORITY,bool NEEDS_DATASET,bool CALL_INIT,bool NEEDS_OCTREE);

		virtual void innerImport(const IO::Descriptor& descriptor) override;
		virtual void innerExport(IO::Descriptor& descriptor) const override;

	private :

		const unsigned int PRIORITY;
		const bool CALL_INIT;
		const bool NEEDS_OCTREE;
		
		bool active;
		bool local;

		virtual void init(Particle& particle,DataSet* dataSet) const {};
		virtual void modify(Group& group,DataSet* dataSet,float deltaTime) const = 0;
	};

	inline Modifier::Modifier(unsigned int PRIORITY,bool NEEDS_DATASET,bool CALL_INIT,bool NEEDS_OCTREE) :
		DataHandler(NEEDS_DATASET),
		PRIORITY(PRIORITY),
		CALL_INIT(CALL_INIT),
		NEEDS_OCTREE(NEEDS_OCTREE),
		active(true),
        local(true)
	{}

	inline void Modifier::setActive(bool active)
	{
		this->active = active;
	}
	
	inline bool Modifier::isActive() const
	{
		return active;
	}

	inline void Modifier::setLocalToSystem(bool local)
	{
		this->local = local;
	}

	inline bool Modifier::isLocalToSystem() const
	{
		return local;
	}

	inline unsigned int Modifier::getPriority() const
	{
		return PRIORITY;
	}

	inline void Modifier::innerImport(const IO::Descriptor& descriptor)
	{
		Transformable::innerImport(descriptor);

		const IO::Attribute* attrib = NULL;

        if ((attrib = descriptor.getAttributeWithValue("active")))
			setActive(attrib->getValue<bool>());
        if ((attrib = descriptor.getAttributeWithValue("local")))
			setLocalToSystem(attrib->getValue<bool>());
	}

	inline void Modifier::innerExport(IO::Descriptor& descriptor) const
	{
		Transformable::innerExport(descriptor);

		descriptor.getAttribute("active")->setValueOptionalOnTrue(isActive());
		descriptor.getAttribute("local")->setValueOptionalOnFalse(isLocalToSystem());
	}
}

#endif
