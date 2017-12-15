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

#ifndef H_SPK_STRAIGHEMITTER
#define H_SPK_STRAIGHEMITTER

namespace SPK
{
	/**
	* @class StraightEmitter
	* @brief An Emitter that emits in a given direction
	*/
	class SPK_PREFIX StraightEmitter : public Emitter
	{
	SPK_IMPLEMENT_OBJECT(StraightEmitter)

	SPK_START_DESCRIPTION
	SPK_PARENT_ATTRIBUTES(Emitter)
	SPK_ATTRIBUTE("direction",ATTRIBUTE_TYPE_VECTOR)
	SPK_END_DESCRIPTION

	public :

		/**
		* @brief Creates and registers a new StraightEmitter
		* @param direction : the direction of the StraighEmitter
		*/
		static  Ref<StraightEmitter> create(
			const Vector3D& direction = Vector3D(0.0f,0.0f,-1.0f),
			const Ref<Zone>& zone = SPK_NULL_REF,
			bool full = true,
			int tank = -1,
			float flow = 1.0f,
			float forceMin = 1.0f,
			float forceMax = 1.0f);

		/**
		* @brief Sets the direction of this StraightEmitter
		*
		* Note that it is not necessary to provide a normalized Vector3D.
		* This Vector3D only indicates a direction, its norm does not matter.
		*
		* @param dir : the direction of this StraightEmitter
		*/
		void setDirection(const Vector3D& dir);

		/**
		* @brief Gets the direction of this StraightEmitter
		* @return the direction of this StraightEmitter
		*/
		const Vector3D& getDirection() const;

		/**
		* @brief Gets the transformed direction of this StraightEmitter
		* @return the transformed direction of this StraightEmitter
		*/
		const Vector3D& getTransformedDirection() const;

	protected :

		virtual void innerUpdateTransform() override;

		virtual void innerImport(const IO::Descriptor& descriptor) override;
		virtual void innerExport(IO::Descriptor& descriptor) const override;

	private :

		Vector3D direction;
		Vector3D tDirection;

		/**
		* @brief The constructor of StraightEmitter
		* @param direction : the direction of the StraighEmitter
		*/
		StraightEmitter(
			const Vector3D& direction = Vector3D(0.0f,0.0f,-1.0f),
			const Ref<Zone>& zone = SPK_NULL_REF,
			bool full = true,
			int tank = -1,
			float flow = 1.0f,
			float forceMin = 1.0f,
			float forceMax = 1.0f);

		StraightEmitter(const StraightEmitter& emitter);

        virtual void generateVelocity(Particle& particle,float speed) const override;
	};

	inline Ref<StraightEmitter> StraightEmitter::create(
			const Vector3D& direction,
			const Ref<Zone>& zone,
			bool full,
			int tank,
			float flow,
			float forceMin,
			float forceMax)
	{
		return SPK_NEW(StraightEmitter,direction,zone,full,tank,flow,forceMin,forceMax);
	}

	inline const Vector3D& StraightEmitter::getDirection() const
	{
		return direction;
	}

	inline const Vector3D& StraightEmitter::getTransformedDirection() const
	{
		return tDirection;
	}
}

#endif
