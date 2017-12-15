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

#ifndef H_SPK_POINTMASS
#define H_SPK_POINTMASS

namespace SPK
{
	/**
	* @brief A Modifier defining a point with a mass that attracts or repels particles
	*
	* The power of the force is function of the square of the distance of the particle to the point mass.<br>
	* An offset is added to the distance to prevent from having a force reaching the infinity.<br>
	* <br>
	* A positive mass will attract particles while a negative mass whill repel them.
	*/
	class SPK_PREFIX PointMass : public Modifier
	{
	SPK_IMPLEMENT_OBJECT(PointMass)

	SPK_START_DESCRIPTION
	SPK_PARENT_ATTRIBUTES(Modifier)
	SPK_ATTRIBUTE("position",ATTRIBUTE_TYPE_VECTOR)
	SPK_ATTRIBUTE("mass",ATTRIBUTE_TYPE_FLOAT)
	SPK_ATTRIBUTE("offset",ATTRIBUTE_TYPE_FLOAT)
	SPK_END_DESCRIPTION

	public :

		/**
		* @brief Creates a new point mass
		* @param pos : the position
		* @param mass : the mass
		* @param offset : the offset
		*/
		static  Ref<PointMass> create(const Vector3D& pos = Vector3D(),float mass = 1.0f,float offset = 0.01f);
		
		//////////////
		// Position //
		//////////////

		/**
		* @brief Sets the position of the point mass
		* @param pos : the position
		*/
		void setPosition(const Vector3D& pos);

		/**
		* @brief Gets the position of the point mass
		* @return the position
		*/
		const Vector3D& getPosition() const;

		/**
		* @brief Gets the transformed position of the point mass
		* @return the transformed position
		*/
		const Vector3D& getTransformedPosition() const;

		//////////
		// Mass //
		//////////

		/**
		* @brief Sets the mass of the point mass
		*
		* The mass defines the strenght of the attraction. The more the mass, the stronger the attraction.<br>
		* A position mass will result into an attraction while a negative mass will result into a repulsion.<br>
		* Moreover a mass equal to 0 make the PointMass have no effect.
		*
		* @param mass : the mass
		*/
		void setMass(float mass);

		/**
		* @brief Gets the mass of the point mass
		* @return the mass
		*/
		float getMass() const;

		////////////
		// Offset //
		////////////

		/**
		* @brief Sets the offset of the point mass
		*
		* The offset if added to the distance of the particle to the point mass during force computation.<br>
		* It prevent the force from approaching infinity as the particle gets closer to the point mass.<br>
		* <br>
		* Note that the offset must be strictly positive.
		*
		* @param offset : the offset
		*/
		void setOffset(float offset);

		/**
		* @brief Gets the offset of the point mass
		* @return the offset
		*/
		float getOffset() const;

	protected :

        virtual  void innerUpdateTransform() override;

		virtual void innerImport(const IO::Descriptor& descriptor) override;
		virtual void innerExport(IO::Descriptor& descriptor) const override;

	private :

		Vector3D position;
		Vector3D tPosition;

		float mass;
		float offset;

		PointMass(const Vector3D& pos = Vector3D(),float mass = 1.0f,float offset = 0.01f);
		PointMass(const PointMass& pointMass);

		virtual void modify(Group& group,DataSet* dataSet,float deltaTime) const override;
	};

	inline Ref<PointMass> PointMass::create(const Vector3D& pos,float mass,float offset)
	{
		return SPK_NEW(PointMass,pos,mass,offset);
	}

	inline void PointMass::setPosition(const Vector3D& pos)
	{
		position = pos;
		transformPos(tPosition,pos);
	}

	inline const Vector3D& PointMass::getPosition() const
	{
		return position;
	}

	inline const Vector3D& PointMass::getTransformedPosition() const
	{
		return tPosition;
	}

	inline void PointMass::setMass(float mass)
	{
		this->mass = mass;
	}

	inline float PointMass::getMass() const
	{
		return mass;
	}

	inline float PointMass::getOffset() const
	{
		return offset;
	}

	inline void PointMass::innerUpdateTransform()
	{
		transformPos(tPosition,position);
	}
}

#endif
