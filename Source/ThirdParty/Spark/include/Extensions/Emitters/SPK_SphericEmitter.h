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

#ifndef H_SPK_SPHERICEMITTER
#define H_SPK_SPHERICEMITTER

namespace SPK
{
	/**
	* @class SphericEmitter
	* @brief An Emitter that emits particles in a portion of sphere
	*
	* This Emitter can emit particles in a spheric way.
	* To do that 2 angles and a direction Vector3D can be parametered :
	* <ul>
	* <li>The direction Vector3D defines the direction of the emitter.</li>
	* <li>The angles defines the area in between which wil be emitted the particles velocities.</li>
	* </ul>
	* Here are a few examples :
	* <ul>
	* <li><i>0 and 2 * PI</i> will define a complete sphere ie equivalent to a RandomEmitter</li>
	* <li><i>0 and 0</i> will define a Emitter equivalent to a StraightEmitter</li>
	* <li><i>PI and PI</i> will define a disk</li>
	* <li><i>PI / 2 and PI / 2</i> will define a Cone of angle PI / 2</li>
	* <li>...</li>
	* </ul>
	*/
	class SPK_PREFIX SphericEmitter : public Emitter
	{
	SPK_IMPLEMENT_OBJECT(SphericEmitter)

	SPK_START_DESCRIPTION
	SPK_PARENT_ATTRIBUTES(Emitter)
	SPK_ATTRIBUTE("direction",ATTRIBUTE_TYPE_VECTOR)
	SPK_ATTRIBUTE("angles",ATTRIBUTE_TYPE_FLOATS)
	SPK_END_DESCRIPTION

	public :

		/**
		* @brief Creates and registers a new SphericEmitter
		* @param direction : the direction of the SphericEmitter
		* @param angleA : the first angle in radians of the SphericEmitter
		* @param angleB : the second angle in radians of the SphericEmitter
		*/
		static  Ref<SphericEmitter> create(
			const Vector3D& direction = Vector3D(0.0f,0.0f,-1.0f),
			float angleA = 0.0f,
			float angleB = 0.0f,
			const Ref<Zone>& zone = SPK_NULL_REF,
			bool full = true,
			int tank = -1,
			float flow = 1.0f,
			float forceMin = 1.0f,
			float forceMax = 1.0f);

		/**
		* @brief Sets the direction of this SphericEmitter
		*
		* Note that it is not necessary to provide a normalized Vector3D.
		* This Vector3D only indicates a direction, its norm does not matter.
		*
		* @param direction : the direction of this SphericEmitter
		*/
		void setDirection(const Vector3D& direction);

		/**
		* @brief Gets the direction of this SphericEmitter
		* @return the direction of this SphericEmitter
		*/
		const Vector3D& getDirection() const;

		/**
		* @brief Gets the direction of this SphericEmitter
		* @return the direction of this SphericEmitter
		*/
		const Vector3D& getTransformedDirection() const;

		/**
		* @brief Sets the angles of this SphericEmitter
		*
		* Note that angles are clamped between 0 and 2 * PI
		*
		* @param angleMin : the first angle in radians of this SphericEmitter
		* @param angleMax : the second angle in radians of this SphericEmitter
		*/
		void setAngles(float angleMin,float angleMax);

		/**
		* @brief Gets the minimum angle of this SphericEmitter
		* @return the minimum angle of this SphericEmitter
		*/
		float getAngleMin() const;

		/**
		* @brief Gets the maximum angle of this SphericEmitter
		* @return the maximum angle of this SphericEmitter
		*/
		float getAngleMax() const;

	protected :

		virtual void innerUpdateTransform() override;

		virtual void innerImport(const IO::Descriptor& descriptor) override;
		virtual void innerExport(IO::Descriptor& descriptor) const override;

	private :

		static const float PI;

		Vector3D direction;
		Vector3D tDirection; // transformed direction

		float angleMin;
		float angleMax;

		float cosAngleMin;
		float cosAngleMax;

		float matrix[9];

		/////////////////
		// Constructor //
		/////////////////

		/**
		* @brief Constructor of SphericEmitter
		* @param direction : the direction of the SphericEmitter
		* @param angleA : the first angle in radians of the SphericEmitter
		* @param angleB : the second angle in radians of the SphericEmitter
		*/
		SphericEmitter(
			const Vector3D& direction = Vector3D(0.0f,0.0f,-1.0f),
			float angleA = 0.0f,
			float angleB = 0.0f,
			const Ref<Zone>& zone = SPK_NULL_REF,
			bool full = true,
			int tank = -1,
			float flow = 1.0f,
			float forceMin = 1.0f,
			float forceMax = 1.0f);

		SphericEmitter(const SphericEmitter& emitter);

        virtual void generateVelocity(Particle& particle,float speed) const override;

		void computeMatrix();
	};

	inline Ref<SphericEmitter> SphericEmitter::create(
		const Vector3D& direction,
		float angleMin,
		float angleMax,
		const Ref<Zone>& zone,
		bool full,
		int tank,
		float flow,
		float forceMin,
		float forceMax)
	{
		return SPK_NEW(SphericEmitter,direction,angleMin,angleMax,zone,full,tank,flow,forceMin,forceMax);
	}

	inline const Vector3D& SphericEmitter::getDirection() const
	{
		return direction;
	}

	inline const Vector3D& SphericEmitter::getTransformedDirection() const
	{
		return tDirection;
	}

	inline float SphericEmitter::getAngleMin() const
	{
		return angleMin;
	}

	inline float SphericEmitter::getAngleMax() const
	{
		return angleMax;
	}
}

#endif
