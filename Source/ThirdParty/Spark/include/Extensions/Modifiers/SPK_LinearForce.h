//
// SPARK particle engine
//
// Copyright (C) 2008-2011 - Julien Fryer - julienfryer@gmail.com
// Copyright (C) 2017 - Frédéric Martin - fredakilla@gmail.com
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

#ifndef H_SPK_LINEARFORCE
#define H_SPK_LINEARFORCE

namespace SPK
{
	/**
	* @class LinearForce
	* @brief A modifier applying a generic linear force on particles
	*
	* A linear force is a force that applies in a unique direction over all the zone.<br>
	* This modifier is very generic and can be used to set up a large variety of force (even fantasy ones !).
	* <br>
	* Some helper methods exist to help set up common force (gravity,wind,friction...)<br>
	* <br>
	* Note that this modifier can be used to set up a gravity or a friction which applies only within a zone.
	* Unlike Gravity and Friction modifiers which applies to the whole universe.<br>
	* <br>
	* Finally note that the zone test can be set to ZONE_TEST_ALWAYS, so that the force applies on the whole universe.
	*/
	class SPK_PREFIX LinearForce : public ZonedModifier
	{
	SPK_IMPLEMENT_OBJECT(LinearForce)

	SPK_START_DESCRIPTION
	SPK_PARENT_ATTRIBUTES(ZonedModifier)
	SPK_ATTRIBUTE("value",ATTRIBUTE_TYPE_VECTOR)
	SPK_ATTRIBUTE("relative value",ATTRIBUTE_TYPE_BOOL)
	SPK_ATTRIBUTE("squared speed",ATTRIBUTE_TYPE_BOOL)
	SPK_ATTRIBUTE("parameter",ATTRIBUTE_TYPE_STRING)
	SPK_ATTRIBUTE("factor type",ATTRIBUTE_TYPE_STRING)
	SPK_ATTRIBUTE("coefficient",ATTRIBUTE_TYPE_FLOAT)
	SPK_END_DESCRIPTION

	public :

		//////////////////
		// Constructors //
		//////////////////

		/**
		* @brief Creates a new linear force
		* @param value : a vector defining the direction and norm of the force
		* @param zone : the zone where the force applies
		* @param zoneTest : the zone test that triggers the force application
		*/
		static  Ref<LinearForce> create(
			const Vector3D& value = Vector3D(),
			const Ref<Zone>& zone = SPK_NULL_REF,
			ZoneTest zoneTest = ZONE_TEST_INSIDE);

		/**
		* @brief Creates a new linear force as a wind
		* See useAsWind for more info
		* @param value : the direction and amplitude of the wind
		* @param surfaceFactor : the factor used for computation
		* @param zone : the zone where the wind applies
		* @param zoneTest : the zone test that triggers the wind application
		*/
		static Ref<LinearForce> createAsWind(
			const Vector3D& value,
			Factor surfaceFactor,
			const Ref<Zone>& zone = SPK_NULL_REF,
			ZoneTest zoneTest = ZONE_TEST_INSIDE);
		
		/**
		* @brief Creates a new linear force as a friction
		* See useAsFriction for more info
		* @param value : the coefficient of friction
		* @param surfaceFactor : the factor used for computation
		* @param zone : the zone where the friction applies
		* @param zoneTest : the zone test that triggers the friction application
		*/
		static Ref<LinearForce> createAsFriction(
			float value,
			Factor surfaceFactor,
			const Ref<Zone>& zone = SPK_NULL_REF,
			ZoneTest zoneTest = ZONE_TEST_INSIDE);
		
		/**
		* @brief Creates a new linear force as a gravity
		* See useAsFriction for more info
		* @param value : the direction and amplitude of the gravity
		* @param zone : the zone where the gravity applies
		* @param zoneTest : the zone test that triggers the gravity application
		*/
		static Ref<LinearForce> createAsGravity(
			const Vector3D& value,
			const Ref<Zone>& zone = SPK_NULL_REF,
			ZoneTest zoneTest = ZONE_TEST_INSIDE);

		/**
		* @brief Creates a new linear force as a simple force
		* See useAsSimpleForce for more info
		* @param value : the direction and amplitude of the force
		* @param zone : the zone where the force applies
		* @param zoneTest : the zone test that triggers the force application
		*/
		static Ref<LinearForce> createAsSimpleForce(
			const Vector3D& value,
			const Ref<Zone>& zone = SPK_NULL_REF,
			ZoneTest zoneTest = ZONE_TEST_INSIDE);

		///////////
		// Value //
		///////////

		/**
		* @brief Sets the value of the force
		* The value of the force is a vector defining a direction and its norm defines the power of the force
		* @param value : the value of the force
		*/
		void setValue(const Vector3D& value);

		/**
		* @brief Gets the value of the force
		* @return the value of the force
		*/
		const Vector3D& getValue() const;

		/**
		* @brief Gets the transformed value of the force
		* @return the transformed value of the force
		*/
		const Vector3D& getTransformedValue() const;

		//////////////
		// Relative //
		//////////////

		/**
		* @brief Sets whether this force is relative to the particle or not
		*
		* If the force is relative to the particle, it depends on the particle's velocity. The resulting force is :<br>
		* <i>force = tValue - velocity</i><br>
		* For non relative forces, the value is left unchanged.<br>
		* <br>
		* When using relative forces, there is the possibility to set the force to be function of the squared relative velocity 
		* of the force (instead of the relative velocity). This is a bit more computatationaly expensive but leads to a better
		* discrete approximation of the reality.<br>
		*
		* @param relative : true to use a relative force, false not to
		* @param squaredSpeed : true to use squared speed, false to use speed
		*/
		void setRelative(bool relative,bool squaredSpeed = false);

		/**
		* @brief Tells whether this force is relative to the particle's velocity
		* @return true if the force is relative, false if not
		*/
		bool isRelative() const;

		/**
		* @brief Tells whether squared relative speed is used to deduce the discrete force
		* Note that this only works with relative forces as using the squared speed gives a better
		* approximation of the reality
		* @return true if the squared relative speed is used, false otherwise
		*/
		bool isSquaredSpeedUsed() const;

		///////////////
		// Parameter //
		///////////////

		/**
		* @brief Dont use any parameter for this force
		* The factor is set to FACTOR_CONSTANT
		*/
		void setNoParam();

		/**
		* @brief Sets the parameter to use and the degree used
		* It is possible to multiply the discrete force by a parameter.<br>
		* Moreover it is possible to choose the degree of the parameter.
		* For instance if factor is set to FACTOR_QUADRATIC, the squared param will be used.<br>
		* <br>
		* This allow for instance to use the surface of the particle to derive the force applied by a wind,
		* or to use the mass of a particle to derive the force applied by a gravity...
		* <br>
		* Note that is factor is set to FACTOR_CONSTANT, no parameter is used to modulate the force
		* @param param : the parameter to use
		* @param factor : the degree of the parameter
		*/
		void setParam(Param param,Factor factor = FACTOR_LINEAR);

		/**
		* @brief Gets the parameter used to modulate the force
		* @return the parameter used to modulate the force 
		*/
		Param getParam() const;

		/**
		* @brief Gets the degree of the parameter used
		* @return the degree of the parameter used
		*/
		Factor getFactor() const;

		/////////////////
		// Coefficient //
		/////////////////

		/**
		* @brief Sets the constant by which is multiplied the force
		* @param coef : the constant by which is multiplied the force
		*/
		void setCoef(float coef);

		/**
		* @brief Gets the constant by which is multiplied the force
		* @return the constant by which is multiplied the force 
		*/
		float getCoef() const;

		//////////////
		// Helpers //
		/////////////

		/**
		* @brief A helper method to configure the force as a wind
		*
		* A wind is relative to the velocity of a particle, the parameter used will be the scale of the particle.<br>
		* the higher the factor, the more realistic but the more computationaly expensive will be the wind :
		* <ul>
		* <li>FACTOR_CONSTANT : the scale of the particle is not used and the speed is used</li>
		* <li>FACTOR_LINEAR : the scale in one dimension is used and the speed is used</li>
		* <li>FACTOR_QUADRATIC : the surface of the particle is used and the squared speed is used (the best discrete approximation of the reality)</li>
		* <li>FACTOR_CUBIC : the volume of the particle is used but it has no physical sense</li>
		* </ul>
		* The correct formula is : <i>f = 0.5 * volumetric density of the fluid * surface * speed²</i><br>
		* The coefficient can then be set to give realistic winds depending of the shape of the particle and on the fluid. <br>
		* For instance for a sphere in the air we have :
		* <ul>
		* <li>volumetric density of the air : 1.293 kg.m^-3</li>
		* <li>surface of sphere in contact with the wind : PI * r * r m²<li>
		* </ul>
		* Therefore, the coefficient will be 0.5 * 1.293 * 3.14159 = 2.03
		*
		* @param value : the direction and amplitude of the wind
		* @param surfaceFactor : the factor used for computation
		*/
		void useAsWind(const Vector3D& value,Factor surfaceFactor);

		/**
		* @brief A helper method to configure the force as a friction
		*
		* A friction acts as a wind with no amplitude at all (only a relative wind exists)
		* See useAsWind for more info
		*
		* @param value : the value of the friction constant
		* @param surfaceFactor : the factor used for computation
		*/
		void useAsFriction(float value,Factor surfaceFactor);

		/**
		* @brief A helper method to configure the force as a gravity
		*
		* A gravity is a non relative force which is function of the mass,
		* the parameter set is therefore the mass in a linear manner.<br>
		* <br>
		* The formula is : f = g * mass
		* On earth, the gravity is equal to 9.81 m.s^-2
		*
		* @param value : the direction and amplitude of the gravity
		*/
		void useAsGravity(const Vector3D& value);

		/**
		* @brief A helper method to configure the force as a generic simple force
		* The simple force is non-relative and function of no parameter
		* @param value : the direction and amplitude of the force
		*/
		void useAsSimpleForce(const Vector3D& value);

	protected :

		virtual  void innerUpdateTransform() override;

		virtual void innerImport(const IO::Descriptor& descriptor) override;
		virtual void innerExport(IO::Descriptor& descriptor) const override;

	private :

		Vector3D value;
		Vector3D tValue;

		bool relative;
		bool squaredSpeed;

		Param param;
		Factor factor;
		float coef;

		LinearForce(
			const Vector3D& value = Vector3D(),
			const Ref<Zone>& zone = SPK_NULL_REF,
			ZoneTest zoneTest = ZONE_TEST_INSIDE);

		LinearForce(const LinearForce& linearForce);
	
		float getDiscreteFactor(const Particle& particle) const;
		
		virtual void modify(Group& group,DataSet* dataSet,float deltaTime) const override;
	};

	inline Ref<LinearForce> LinearForce::create(const Vector3D& value,const Ref<Zone>& zone,ZoneTest zoneTest)
	{
		return SPK_NEW(LinearForce,value,zone,zoneTest);
	}
	
	inline void LinearForce::setValue(const Vector3D& value)
	{
		this->value = value;
		transformDir(tValue,value);
	}

	inline const Vector3D& LinearForce::getValue() const
	{
		return value;
	}

	inline const Vector3D& LinearForce::getTransformedValue() const
	{
		return tValue;
	}

	inline bool LinearForce::isRelative() const
	{
		return relative;
	}

	inline bool LinearForce::isSquaredSpeedUsed() const
	{
		return squaredSpeed;
	}

	inline void LinearForce::setNoParam()
	{
		factor = FACTOR_CONSTANT;
	}

	inline void LinearForce::setParam(Param param,Factor factor)
	{
		this->param = param;
		this->factor = factor;
	}
	
	inline Param LinearForce::getParam() const
	{
		return param;
	}
	
	inline Factor LinearForce::getFactor() const
	{
		return factor;
	}

	inline void LinearForce::setCoef(float coef)
	{
		this->coef = coef;
	}

	inline float LinearForce::getCoef() const
	{
		return coef;
	}

	inline void LinearForce::innerUpdateTransform()
	{
		ZonedModifier::innerUpdateTransform();
		transformDir(tValue,value);
	}
}

#endif
