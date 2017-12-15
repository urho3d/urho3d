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

#ifndef H_SPK_PARTICLE
#define H_SPK_PARTICLE

#include <cmath> // for sqrt

namespace SPK
{
	/**
	* @brief A single particle
	*
	* This class is a handler to access the particle's data within its group.<br>
	* For optimisation purpose, particles' data are not stored in an AoS (array of structures) way, 
	* therefore the set of data of a single particle is not contiguous in memory and cannot be stored within a class.<br>
	* <br>
	* Knowing that, particles are just helper objects that must be used locally and not stored in any way.
	*/
	class Particle
	{
	friend class Group;

	template<typename T>
	friend class Iterator;
	template<typename T>
	friend class ConstIterator;

	public :

		/////////////
		// Setters //
		/////////////

		/**
		* @brief Accesses the current position of the particle
		* @return a reference to the current position of the particle
		*/
		Vector3D& position();

		/**
		* @brief Accesses the current velocity of the particle
		* @return a reference to the current velocity of the particle
		*/
		Vector3D& velocity();

		/**
		* @brief Accesses the position at previous update of the particle
		* Note that the old position must be modified with care in order to keep the displacement integrity of the particles for the physics engine.
		* @return a reference to the position at previous update of the particle
		*/
		Vector3D& oldPosition();

		/**
		* @brief Sets the color of the particle
		* @param color : the color of the particle
		*/
		void setColor(Color color);

		/**
		* @brief Sets a given parameter of the particle
		* If the parameter is not enabled, nothing happens
		* @param parameter : the parameter to set
		* @param value : the value of the parameter
		*/
		void setParam(Param parameter,float value);

		/**
		* @brief Sets a given parameter of the particle with no check on the existence of the parameter
		* This method is useful to set a parameter if it is sure that it exists.<br>
		* It allows to skip the test of existence and gain some precious cpu cycles.<br>
		* Calling this method on a parameter that does exist is unsafe.
		* @param parameter : the parameter to set
		* @param value : the value of the parameter
		*/
		void setParamNC(Param parameter,float value);

		/////////////
		// Getters //
		/////////////

		/**
		* @brief Gets the group to which belongs the particle
		* @return the group to which belongs the particle
		*/
		Group& getGroup();

		/**
		* @brief Gets the group to which belongs the particle in a constant way
		* @return the group to which belongs the particle
		*/
		const Group& getGroup() const;

		/**
		* @brief Gets the index of the particle within its group
		* @return the index of the particle
		*/
		size_t getIndex() const;

		/**
		* @brief Gets the current position of the particle
		* @return the current position of the particle
		*/
		const Vector3D& position() const;

		/**
		* @brief Gets the current velocity of the particle
		* @return the current velocity of the particle
		*/
		const Vector3D& velocity() const;

		/**
		* @brief Gets the old position of the particle
		* @return the old position of the particle
		*/
		const Vector3D& oldPosition() const;

		/**
		* @brief Gets the age of the particle in units of time
		* @return the age of the particle 
		*/
		float getAge() const;

		/**
		* @brief Gets the energy of the particle
		* The energy is a float number going from 1.0 to 0.0 as the particle gets older.<br>
		* It is computed as follow : <i>1.0 - age / lifeTime</i>
		* @return the energy of the particle
		*/
		float getEnergy() const;

		/**
		* @brief Gets the life time of the particle in units of time
		* The life time is the total amount of time the particle can live.
		* @return the life time of the particle
		*/
		float getLifeTime() const;

		/**
		* @brief Gets the physical radius of the particle in units
		* The physical radius is defined as : <i>particleScale * groupPhysicalRadius</i>
		* @return the physical radius of the particle
		*/
		float getRadius() const;

		/**
		* @brief Gets the distance of the particle from the camera
		* This value is relevant only if the group had the distance computation enabled.
		* @return the distance of the particle from the camera
		*/
		float getDistanceFromCamera() const;

		/**
		* @brief Gets the square of the distance of the particle from the camera
		* This value is relevant only if the group had the distance computation enabled.<br>
		* The square distance is faster to compute that the real distance and should be used instead when possible.
		* @return the square of the distance of the particle from the camera
		*/
		float getSqrDistanceFromCamera() const;

		/**
		* @brief Gets the color of the particle
		* @return the color of the particle
		*/
		Color getColor() const;

		/**
		* @brief Gets the value of the given parameter of the particle
		* If the parameter does not exist, its default value is returned
		* @return the value of the given parameter of the particle
		*/
		float getParam(Param parameter) const;

		/**
		* @brief Gets the value of the given parameter of the particle with no check on the existence of the parameter
		* This method is useful to set a parameter if it is sure that it exists.<br>
		* It allows to skip the test of existence and gain some precious cpu cycles.<br>
		* Calling this method on a parameter that does exist is unsafe.
		* @return the value of the given parameter of the particle
		*/
		float getParamNC(Param parameter) const;

		/**
		* @brief Tells whether the particle is alive or not
		* Typically returns <i>energy > 0.0</i>
		* @return true if the particle is alive, false if not
		*/
		bool isAlive() const;

		///////////////
		// Interface //
		///////////////

		/**
		* @brief Kills the particle
		* This sets the energy of the particle to 0 and its age at its lifetime
		*/
		void kill();

	private :

		Particle(Group& group,size_t index);

		Group& group;
		mutable size_t index;
	};

	inline Particle::Particle(Group& group,size_t index) :
		group(group),
		index(index)
	{}

	inline Vector3D& Particle::position()
	{
		return group.particleData.positions[index];
	}

	inline Vector3D& Particle::velocity()
	{
		return group.particleData.velocities[index];
	}

	inline Vector3D& Particle::oldPosition()
	{
		return group.particleData.oldPositions[index];
	}

	inline void Particle::setColor(Color color)
	{
		group.particleData.colors[index] = color;
	}

	inline void Particle::setParam(Param parameter,float value)
	{
		if (group.isEnabled(parameter))
			group.particleData.parameters[parameter][index] = value;
	}

	inline void Particle::setParamNC(Param parameter,float value)
	{
		group.particleData.parameters[parameter][index] = value;
	}

	inline const Group& Particle::getGroup() const
	{
		return group;
	}

	inline Group& Particle::getGroup()
	{
		return group;
	}

	inline size_t Particle::getIndex() const
	{
		return index;
	}

	inline const Vector3D& Particle::position() const
	{
		return group.particleData.positions[index];
	}

	inline const Vector3D& Particle::velocity() const
	{
		return group.particleData.velocities[index];
	}

	inline const Vector3D& Particle::oldPosition() const
	{
		return group.particleData.oldPositions[index];
	}

	inline float Particle::getAge() const
	{
		return group.particleData.ages[index];
	}

	inline float Particle::getEnergy() const
	{
		return group.particleData.energies[index];
	}

	inline float Particle::getLifeTime() const
	{
		return group.particleData.lifeTimes[index];
	}

	inline float Particle::getRadius() const
	{
		return group.physicalRadius * getParam(PARAM_SCALE);
	}

	inline float Particle::getDistanceFromCamera() const
	{
		return std::sqrt(group.particleData.sqrDists[index]);
	}

	inline float Particle::getSqrDistanceFromCamera() const
	{
		return group.particleData.sqrDists[index];
	}

	inline Color Particle::getColor() const
	{
		return group.particleData.colors[index];
	}

	inline float Particle::getParam(Param parameter) const
	{
		if (group.isEnabled(parameter))
			return group.particleData.parameters[parameter][index];
		else
			return Group::DEFAULT_VALUES[parameter];
	}

	inline float Particle::getParamNC(Param parameter) const
	{
		return group.particleData.parameters[parameter][index];
	}

	inline bool Particle::isAlive() const
	{
		return group.particleData.energies[index] > 0.0f;
	}

	inline void Particle::kill()
	{
		group.particleData.energies[index] = 0.0f;
		group.particleData.ages[index] = group.particleData.lifeTimes[index];
	}
}

#endif
