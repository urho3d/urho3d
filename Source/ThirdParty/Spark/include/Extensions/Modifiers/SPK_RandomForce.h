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

#ifndef SPK_RANDOM_FORCE
#define SPK_RANDOM_FORCE

namespace SPK
{
	/**
	* @class RandomForce
	* @brief A modifier that applies a random force to particles
	* 
	* The force is determined per particle and last for a given period before being modified.<br>
	* The force for a given particle is determined between 2 vectors and the period is determined between 2 values.<br>
	* For each particle, each time the period is reached, the force is randomly generated again.
	*/
	class SPK_PREFIX RandomForce : public Modifier
	{
	SPK_IMPLEMENT_OBJECT(RandomForce)

	SPK_START_DESCRIPTION
	SPK_PARENT_ATTRIBUTES(Modifier)
	SPK_ATTRIBUTE("values",ATTRIBUTE_TYPE_VECTORS)
	SPK_ATTRIBUTE("period",ATTRIBUTE_TYPE_FLOATS)
	SPK_END_DESCRIPTION

	public :

		/**
		* @brief Creates a new RandomForce modifier
		* @param minVector : the minimum vector of the force
		* @param maxVector : the maximum vector of the force
		* @param minPeriod : the minimum period
		* @param maxPeriod : the maximum period
		* @return a new randomForce modifier
		*/
		static Ref<RandomForce> create(
			const Vector3D& minVector = Vector3D(),
			const Vector3D& maxVector = Vector3D(),
			float minPeriod = 1.0f,
			float maxPeriod = 1.0f);

		///////////////////////////////////////
		// Vectors (direction and amplitude) //
		///////////////////////////////////////

		/**
		* @brief Sets the bound vectors of this randomForce
		* 
		* force vector at a time is determined between thos 2 vectors.<br>
		* Note that it does not matter which vector hold minimum or maximum values, it is sorted internally.
		*
		* @param minVector : the minimum vector
		* @param maxVector : the maximum vector
		*/
		void setVectors(const Vector3D& minVector,const Vector3D& maxVector);

		/**
		* @brief Gets the min vector
		* @return the min vector
		*/
		const Vector3D& getMinVector() const;

		/**
		* @brief Gets the max vector
		* @return the max vector
		*/
		const Vector3D& getMaxVector() const;

		/**
		* @brief Gets the transformed min vector
		* @return the transformed min vector
		*/
		const Vector3D& getTransformedMinVector() const;

		/**
		* @brief Gets the transformed max vector
		* @return the transformed max vector
		*/
		const Vector3D& getTransformedMaxVector() const;

		////////////
		// Period //
		////////////

		/**
		* @brief Sets the min and max periods
		*
		* The periods determine the frequency of the change of the force vector (amplitude and direction) per particle.<br>
		* The period is computed per particle when necessary between minPeriod and maxPeriod.<br>
		* Note that both periods must be greated than 0.0.
		*
		* @param minPeriod : the minimal period
		* @param maxPeriod : the maximal period
		*/
		void setPeriods(float minPeriod,float maxPeriod);

		/**
		* @brief Gets the minimal period
		* @return the minimal period
		*/
		float getMinPeriod() const;

		/**
		* @brief Gets the maximal period
		* @return the maximal period
		*/
		float getMaxPeriod() const;

	protected :

		virtual void innerUpdateTransform() override;

		virtual void innerImport(const IO::Descriptor& descriptor) override;
		virtual void innerExport(IO::Descriptor& descriptor) const override;

	private :

		// Data indices
		static const size_t NB_DATA = 2;
		static const size_t FORCE_VECTOR_INDEX = 0;
		static const size_t REMAINING_TIME_INDEX = 1;

		Vector3D minVector;
		Vector3D maxVector;

		// transformed vectors
		Vector3D tMinVector;
		Vector3D tMaxVector;

		float minPeriod;
		float maxPeriod;

		RandomForce(
			const Vector3D& minVector = Vector3D(),
			const Vector3D& maxVector = Vector3D(),
			float minPeriod = 1.0f,
			float maxPeriod = 1.0f);

		void advanceTime(const Particle& particle,DataSet* dataSet,float deltaTime,float& time) const;
		void initParticle(const Particle& particle,DataSet* dataSet) const;

		virtual void createData(DataSet& dataSet,const Group& group) const override;

		virtual void init(Particle& particle,DataSet* dataSet) const override;
		virtual void modify(Group& group,DataSet* dataSet,float deltaTime) const override;
	};

	inline Ref<RandomForce> RandomForce::create(const Vector3D& minVector,const Vector3D& maxVector,float minPeriod,float maxPeriod)
	{
		return SPK_NEW(RandomForce,minVector,maxVector,minPeriod,maxPeriod);
	}

	inline const Vector3D& RandomForce::getMinVector() const
	{
		return minVector;
	}

	inline const Vector3D& RandomForce::getMaxVector() const
	{
		return maxVector;
	}

	inline const Vector3D& RandomForce::getTransformedMinVector() const
	{
		return tMinVector;
	}

	inline const Vector3D& RandomForce::getTransformedMaxVector() const
	{
		return tMaxVector;
	}

	inline float RandomForce::getMinPeriod() const
	{
		return minPeriod;
	}

	inline float RandomForce::getMaxPeriod() const
	{
		return maxPeriod;
	}
}

#endif
