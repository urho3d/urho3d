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

#ifndef H_SPK_EMITTER
#define H_SPK_EMITTER

namespace SPK
{
	class Particle;
	class Group;

	/**
	* @brief An abstract class that defines an emitter of particles
	*
	* An emitter is an object that launches particles by giving them an initial velocity and position.<br>
	* The position is derived from the zone of the emitter.<br>
	* The velocity is derived from the emitter itself.<br>
	* <br>
	* An Emitter has a flow and a tank of particles.
	* The flow defines the rate at which particles are launched and the tank defines the total number of Particles the Emitter can launch.<br>
	* An emitter is also defined by a range of forces (force min and force max) which defines the force at which particles are emitted <i>(initial velocity = force / mass)</i>.<br>
	*/
	class SPK_PREFIX Emitter :	public Transformable
	{
	friend class Group;

	SPK_START_DESCRIPTION
	SPK_PARENT_ATTRIBUTES(Transformable)
	SPK_ATTRIBUTE("active",ATTRIBUTE_TYPE_BOOL)
	SPK_ATTRIBUTE("tank",ATTRIBUTE_TYPE_INT32S)
	SPK_ATTRIBUTE("flow",ATTRIBUTE_TYPE_FLOAT)
	SPK_ATTRIBUTE("force",ATTRIBUTE_TYPE_FLOATS)
	SPK_ATTRIBUTE("zone",ATTRIBUTE_TYPE_REF)
	SPK_ATTRIBUTE("full",ATTRIBUTE_TYPE_BOOL)
	SPK_END_DESCRIPTION

	public :

		virtual ~Emitter();

		////////////
		// Active //
		////////////

		/**
		* @brief Sets this emitter active or not.
		*
		* An inactive emitter will not emit in its parent Group during update.<br>
		*
		* @param active : true to activate this emitter, false to deactivate it
		*/
		void setActive(bool active);

		/**
		* @brief Tells whether this emitter is active or not
		* @return true if this emitter is active, false if is is inactive
		*/
		bool isActive() const;

		//////////
		// Tank //
		//////////

		/**
		* @brief Sets the initial number of particles in this emitter's tank
		*
		* Each time the emitter is updated, the number of particles emitted is deduced from the emitter tank.
		* When the tank reaches 0, the emitter will not emit any longer until it is refilled.<br>
		* <br>
		* A number of -1 (or any negative number) means the emitter has an infinite tank which will never be empty.<br>
		/ <br>
		* Note that having both negative tank and flow is illegal.
		* The current tank can be reset to its initial value with a call to resetTank()
		*
		* @param tank : the initial number of particles in this emitters's tank
		*/
		void setTank(int tank);

		/**
		* @brief Sets the min and max number of particles in this emitter's tank
		* 
		* min and max value must be of the same sign (negative numbers meaning the tank is infinite).<br>
		* The current tank is drawn between min and max.<br>
		* The current tank can be redrawn with a call to resetTank().
		*
		* @param minTank : the minimum initial number of particles in this emitters's tank
		* @param maxTank : the maximum initial number of particles in this emitters's tank
		*/
		void setTank(int minTank,int maxTank);

		/**
		* @brief Gets the current number of particles in this emitter's tank
		* @return the current number of particles in this emitters's tank
		*/
		int getCurrentTank() const;

		/**
		* @brief Gets the minimum initial number of particles in this emitter's tank
		* @return the minimum initial number of particles in this emitters's tank
		*/
		int getMinTank() const;

		/**
		* @brief Gets the maximum initial number of particles in this emitter's tank
		* @return the maximum initial number of particles in this emitters's tank
		*/
		int getMaxTank() const;

		/**
		* @brief Resets the current tank
		* The current tank is reevaluated between the min and max tank
		*/
		void resetTank();

		//////////
		// Flow //
		//////////

		/**
		* @brief Sets the flow of this emitter
		*
		* The flow is in the unit : nb of particle per unit step.
		* A flow of -1 (or any negative number) indicates an infinite flow which means all particles in the emitters's tank are generated instantly.<br>
		* <br>
		* Note that having both negative tank and flow is illegal.
		*
		* @param flow : the flow of this emitter
		*/
		void setFlow(float flow);

		/**
		* @brief Gets the flow of this emitter
		* @return the flow of this emitter
		*/
		float getFlow() const;

		///////////
		// Force //
		///////////

		/**
		* @brief Sets the force of this emitter
		*
		* The force of the emitter varies for each launch of a Particle between a minimum and a maximum.
		* To have a fixed force for the Emitter, just have <i>min = max</i>.<br>
		* <br>
		* the speed at which a Particle will be launched is equal to : <i>force / mass of the Particle</i>.
		*
		* @param min : the minimum force of the emitter
		* @param max : the maximum force of the emitter
		*/
		void setForce(float min,float max);

		/**
		* @brief Gets the minimum force of this emitter
		* @return the minimum force of this emitter
		*/
		float getForceMin() const;

		/**
		* @brief Gets the maximum force of this emitter
		* @return the maximum force of this emitter
		*/
		float getForceMax() const;
		
		//////////
		// Zone //
		//////////

		/**
		* @brief Sets the zone of this emitter
		*
		* If the zone is NULL, the default Zone will be used (A Point centered at the origin)
		*
		* @param zone : the zone of this emitter
		* @param full : true to generate particles in the whole Zone, false to generate particles only at the zone's borders.
		*/
        void setZone(const Ref<Zone>& zone,bool full);

        void setZone(const Ref<Zone>& zone);
        void setUseFullZone(bool f);


		/**
		* @brief Gets the zone of this emitter
		* @return the zone of this emitter
		*/
		const Ref<Zone>& getZone() const;

		/**
		* @brief Tells whether this emitter emits in the whole Zone or only at its borders
		* @return true if this emitter emits in the whole Zone, false if it is only at its borders
		*/
		bool isFullZone() const;

        virtual Ref<SPKObject> findByName(const std::string& name) override;

	protected :

		Emitter(const Ref<Zone>& zone = SPK_NULL_REF,
			bool full = true,
			int tank = -1,
			float flow = 1.0f,
			float forceMin = 1.0f,
			float forceMax = 1.0f);

		Emitter(const Emitter& emitter);

        virtual void propagateUpdateTransform() override;

        virtual void innerImport(const IO::Descriptor& descriptor) override;
        virtual void innerExport(IO::Descriptor& descriptor) const override;

	private :

		bool active;

		int minTank;
		int maxTank;
		int currentTank;
		float flow;

		float forceMin;
		float forceMax;

		Ref<Zone> zone;
		bool full;

		mutable float fraction;
		
		void emit(Particle& particle) const;

		size_t updateTankFromTime(float deltaTime);
		size_t updateTankFromNb(size_t nb);

		/**
		* @brief Gives the particle an initial velocity
		*
		* This method is called internally and must be overriden in inherited emitters.<br>
		* The speed is derived from the force of the emitter and the mass of the particle.<br>
		* The initial velocity of the particle has to be consistent with the given speed.
		*
		* @param particle : the particle whose velocity has to be set
		* @param speed : the desired speed of the particle
		*/
		virtual void generateVelocity(Particle& particle,float speed) const = 0;
	};

	inline void Emitter::setActive(bool active)
	{
		this->active = active;
	}
	
	inline bool Emitter::isActive() const
	{
		return active;
	}

	inline void Emitter::setTank(int tank)
	{
		setTank(tank,tank);
	}

	inline int Emitter::getCurrentTank() const
	{
		return currentTank;
	}

	inline int Emitter::getMinTank() const
	{
		return minTank;
	}

	inline int Emitter::getMaxTank() const
	{
		return maxTank;
	}

	inline void Emitter::resetTank()
	{
		currentTank = SPK_RANDOM(minTank,maxTank);
	}

	inline float Emitter::getFlow() const
	{
		return flow;
	}

	inline float Emitter::getForceMin() const
	{
		return forceMin;
	}

	inline float Emitter::getForceMax() const
	{
		return forceMax;
	}

	inline const Ref<Zone>& Emitter::getZone() const
	{
		return zone;
	}

	inline bool Emitter::isFullZone() const
	{
		return full;
	}

    inline void Emitter::setZone(const Ref<Zone>& zone, bool full)
    {
        setZone(zone);
        setUseFullZone(full);
    }

    inline void Emitter::setUseFullZone(bool f)
    {
        full = f;
    }

	inline size_t Emitter::updateTankFromTime(float deltaTime)
	{
		if (deltaTime < 0.0f)
			return 0;

		size_t nbBorn;
		if (flow < 0.0f)
		{
			nbBorn = currentTank > 0 ? currentTank : 0;
			currentTank = 0;
		}
		else if (currentTank != 0)
		{
			fraction += flow * deltaTime;
			nbBorn = static_cast<size_t>(fraction);
			if (currentTank >= 0)
			{
				if (nbBorn > static_cast<size_t>(currentTank))
					nbBorn = currentTank;
				currentTank -= nbBorn;
			}
			fraction -= nbBorn;
		}
		else 
			nbBorn = 0;
		return nbBorn;
	}

	inline size_t  Emitter::updateTankFromNb(size_t nb)
	{
		if (currentTank < 0)
			return nb;

		if (nb > static_cast<size_t>(currentTank))
			nb = currentTank;
		currentTank -= nb;
		return nb;
	}
}

#endif
