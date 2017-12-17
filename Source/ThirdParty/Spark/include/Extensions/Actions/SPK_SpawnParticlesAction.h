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

#ifndef H_SPK_SPAWNPARTICLESACTION
#define H_SPK_SPAWNPARTICLESACTION

#include <deque>

namespace SPK
{
	/**
	* @brief An action that allows particles to spawn punctually at another particle's position
	*
	* This allows to have some particles spawn at some particle's position when the action is triggered.<br>
	* Note that this is only for a punctual spawning. For a continuous spawning, consider using an EmitterAttacher.<br>
	* <br>
	* To set up particle spawning, an base Emitter is used. The emitter and its zone are copied and the copied emitter is transformed accordingly to
	* the particle's position when an action is triggered.<br>
	* <br>
	* A pool of copied emitter is used internally to avoid creating too many emitters.
	*/
	class SPK_PREFIX SpawnParticlesAction : public Action
	{
	SPK_IMPLEMENT_OBJECT(SpawnParticlesAction)

	SPK_START_DESCRIPTION
	SPK_PARENT_ATTRIBUTES(Action)
	SPK_ATTRIBUTE("spawning numbers",ATTRIBUTE_TYPE_FLOATS)
	SPK_ATTRIBUTE("base emitter",ATTRIBUTE_TYPE_REF)
	SPK_ATTRIBUTE("target group",ATTRIBUTE_TYPE_REF)
	SPK_END_DESCRIPTION

	public :

		//////////////////////////////
		// Constructor / Destructor //
		//////////////////////////////

		/**
		* @brief Creates a new spawnParticles action
		* @param minNb : the minimum number of spawned particles
		* @param maxNb : the maximum number of spawned particles
		* @param group : the group in which to spawn particles
		* @param emitter : the emitter used to spawn particles
		*/
		static Ref<SpawnParticlesAction> create(
			unsigned int minNb = 1,
			unsigned int maxNb = 1,
			const Ref<Group>& group = SPK_NULL_REF,
			const Ref<Emitter>& emitter = SPK_NULL_REF);

		/////////////////////////
		// Number of particles //
		/////////////////////////

		/**
		* @brief Sets the number of particle to spawn
		* Note that this sets both the minimum and maximum number
		* @param nb : the number of particles to spawn
		*/
		void setNb(unsigned int nb);

		/**
		* @brief Sets the number of particle to spawn
		* The actual number of particle spawn is generated within [min,max]
		* @param min : the minimum number of particles to spawn
		* @param max : the maximum number of particles to spawn
		*/
		void setNb(unsigned int min,unsigned int max);

		/**
		* @brief Gets the minimum number of particles to spawn
		* @return the minimum number of particles to spawn
		*/
		unsigned int getMinNb() const;

		/**
		* @brief Gets the maximum number of particles to spawn
		* @return the maximum number of particles to spawn
		*/
		unsigned int getMaxNb() const;

		//////////////////
		// Base emitter //
		//////////////////

		/**
		* @brief Sets the base emitter used to spawn particles
		* The emitter is copied for every particle and is transformed accordingly to particle's position.<br>
		* Note that the zone of the emitter must not be shared as its zone is copied as well, else the base emitter is considered as invalid.
		* @param emitter : the base emitter used to create emitters
		*/
		void setEmitter(const Ref<Emitter>& emitter);

		/**
		* @brief Gets the base emitter
		* If the base emitter is modified, a call to resetPool() will allow the changes to take effects
		* @return the base emitter
		*/
		const Ref<Emitter>& getEmitter() const;

		/////////////////
		// Group index //
		/////////////////

		/**
		* @brief Sets the index of the group in which to spawn particles
		* The index is the index of the group within the parent system.<br>
		* Note that setting the group index to the index of the group which owns the spawn particle action may result in infinitely growing group.
		* @param index : the index of the group in the parent system in which to spawn particles
		*/
		void setTargetGroup(const Ref<Group>& group);

		/**
		* @brief Gets the index of the group within the parent system in which to spawn particles
		* @return the index of the group in which to spawn particles
		*/
		const Ref<Group>& getTargetGroup() const;

		///////////////
		// Interface //
		///////////////

		/** @brief Resets the pool of particles */
		void resetPool();

		virtual void apply(Particle& particle) const override;
		virtual Ref<SPKObject> findByName(const std::string& name) override;

	protected :

		virtual void innerImport(const IO::Descriptor& descriptor) override;
		virtual void innerExport(IO::Descriptor& descriptor) const override;

	private :

		unsigned int minNb;
		unsigned int maxNb;

		Ref<Emitter> baseEmitter;
		Ref<Group> targetGroup;

		mutable std::deque<Ref<Emitter> > emitterPool;
		
		SpawnParticlesAction(
			unsigned int minNb = 1,
			unsigned int maxNb = 1,
			const Ref<Group>& group = SPK_NULL_REF,
			const Ref<Emitter>& emitter = SPK_NULL_REF);

		SpawnParticlesAction(const SpawnParticlesAction& action);

		bool checkValidity() const;
		const Ref<Emitter>& getNextAvailableEmitter() const;
	};

	inline void SpawnParticlesAction::setNb(unsigned int nb)
	{
		setNb(nb,nb);
	}

	inline unsigned int SpawnParticlesAction::getMinNb() const
	{
		return minNb;
	}

	inline unsigned int SpawnParticlesAction::getMaxNb() const
	{
		return maxNb;
	}

	inline Ref<SpawnParticlesAction> SpawnParticlesAction::create(
		unsigned int minNb,
		unsigned int maxNb,
		const Ref<Group>& group,
		const Ref<Emitter>& emitter)
	{
		return SPK_NEW(SpawnParticlesAction,minNb,maxNb,group,emitter);
	}

	inline const Ref<Emitter>& SpawnParticlesAction::getEmitter() const
	{
		return baseEmitter;
	}

	inline void SpawnParticlesAction::setTargetGroup(const Ref<Group>& group)
	{
		targetGroup = group;
	}

	inline const Ref<Group>& SpawnParticlesAction::getTargetGroup() const
	{
		return targetGroup;
	}
}

#endif
