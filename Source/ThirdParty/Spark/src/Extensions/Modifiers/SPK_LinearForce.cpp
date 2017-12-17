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

#include <SPARK_Core.h>
#include "Extensions/Modifiers/SPK_LinearForce.h"

namespace SPK
{
	LinearForce::LinearForce(const Vector3D& value,const Ref<Zone>& zone,ZoneTest zoneTest) :
		ZonedModifier(MODIFIER_PRIORITY_FORCE,false,false,false,ZONE_TEST_FLAG_ALWAYS | ZONE_TEST_FLAG_INSIDE | ZONE_TEST_FLAG_OUTSIDE,zoneTest,zone),
		relative(false),
		squaredSpeed(false),
		param(PARAM_SCALE),
		factor(FACTOR_CONSTANT),
		coef(1.0f)
	{
		setValue(value);
	}

	LinearForce::LinearForce(const LinearForce& linearForce) :
		ZonedModifier(linearForce),
		relative(linearForce.relative),
		squaredSpeed(linearForce.squaredSpeed),
		param(linearForce.param),
		factor(linearForce.factor),
		coef(linearForce.coef)
	{
		setValue(linearForce.value);
	}

	Ref<LinearForce> LinearForce::createAsWind(const Vector3D& value,Factor surfaceFactor,const Ref<Zone>& zone,ZoneTest zoneTest)
	{
		Ref<LinearForce> force = create();
		force->setZone(zone,zoneTest);
		force->useAsWind(value,surfaceFactor);
		return force;
	}

	Ref<LinearForce> LinearForce::createAsFriction(float value,Factor surfaceFactor,const Ref<Zone>& zone,ZoneTest zoneTest)
	{
		Ref<LinearForce> force = create();
		force->setZone(zone,zoneTest);
		force->useAsFriction(value,surfaceFactor);
		return force;
	}

	Ref<LinearForce> LinearForce::createAsGravity(const Vector3D& value,const Ref<Zone>& zone,ZoneTest zoneTest)
	{
		Ref<LinearForce> force = create();
		force->setZone(zone,zoneTest);
		force->useAsGravity(value);
		return force;
	}

	Ref<LinearForce> LinearForce::createAsSimpleForce(const Vector3D& value,const Ref<Zone>& zone,ZoneTest zoneTest)
	{
		Ref<LinearForce> force = create();
		force->setZone(zone,zoneTest);
		force->useAsSimpleForce(value);
		return force;
	}

	void LinearForce::setRelative(bool relative,bool squaredSpeed)
	{
		this->relative = relative;
		this->squaredSpeed = relative & squaredSpeed;
		if (!relative && squaredSpeed)
			SPK_LOG_WARNING("LinearForce::setRelative(bool,bool) - Only relative force can use squared speed");
	}

	void LinearForce::useAsWind(const Vector3D& value,Factor surfaceFactor)
	{
		setValue(value);
		setParam(PARAM_SCALE,surfaceFactor);
		setRelative(true,surfaceFactor >= FACTOR_QUADRATIC);
		setCoef(1.0f);

		if (surfaceFactor == FACTOR_CUBIC)
			SPK_LOG_WARNING("LinearForce::useAsWind(const Vector3D&,Factor) - A cubic factor has no physical sense here");
	}

	void LinearForce::useAsFriction(float value,Factor surfaceFactor)
	{
		setValue(value);
		setParam(PARAM_SCALE,surfaceFactor);
		setRelative(true,surfaceFactor >= FACTOR_QUADRATIC);
		setCoef(value);

		if (surfaceFactor == FACTOR_CUBIC)
			SPK_LOG_WARNING("LinearForce::useAsFriction(float,Factor) - A cubic factor has no physical sense here");
	}

	void LinearForce::useAsGravity(const Vector3D& value)
	{
		setValue(value);
		setParam(PARAM_MASS,FACTOR_LINEAR);
		setRelative(false);
		setCoef(1.0f);
	}

	void LinearForce::useAsSimpleForce(const Vector3D& value)
	{
		setValue(value);
		setNoParam();
		setRelative(false);
		setCoef(1.0f);
	}

	float LinearForce::getDiscreteFactor(const Particle& particle) const
	{
		float discreteFactor = 1.0f;
		if (factor != FACTOR_CONSTANT && particle.getGroup().isEnabled(param))
		{
			float paramValue = particle.getParamNC(param);
			for (int i = 0; i < factor; ++i)
				discreteFactor *= paramValue;
		}
		if (particle.getGroup().isEnabled(PARAM_MASS))
			discreteFactor /= particle.getParamNC(PARAM_MASS);
		return discreteFactor;
	}

	void LinearForce::modify(Group& group,DataSet* dataSet,float deltaTime) const
	{
		// Optimization to compute the factor only if needed
		bool factorByParticle = true;
		if ((factor == FACTOR_CONSTANT || !group.isEnabled(param)) && !group.isEnabled(PARAM_MASS)) // no factor, no mass
			factorByParticle = false;
		if (param == PARAM_MASS && factor == FACTOR_LINEAR) // gravity type force
			factorByParticle = false;

		// if the param is scale, it is assumed that it is the size that matters, therefore the coef is multiplied by the physical radius
		float realCoef = coef;
		if (param == PARAM_SCALE)
			for (int i = 0; i < factor; ++i)
				realCoef *= group.getPhysicalRadius();

		if (!relative)
		{
			const Vector3D discreteForce = tValue * deltaTime * realCoef;

			if (!factorByParticle)
			{
				for (GroupIterator particleIt(group); !particleIt.end(); ++particleIt)
					if (checkZone(*particleIt))
						particleIt->velocity() += discreteForce;
			}
			else
			{
				for (GroupIterator particleIt(group); !particleIt.end(); ++particleIt)
					if (checkZone(*particleIt))
						particleIt->velocity() += discreteForce * getDiscreteFactor(*particleIt);
			}
		}
		else
		{
			for (GroupIterator particleIt(group); !particleIt.end(); ++particleIt)
				if (checkZone(*particleIt))
				{
					Particle& particle = *particleIt;
					Vector3D relativeForce = tValue - particle.velocity();

					float clamp = 1.0f;
					if (squaredSpeed)
					{
						Vector3D absForce(relativeForce);
						absForce.abs();
						clamp = 1.0f / absForce.getMax();
						relativeForce *= relativeForce;
					}

					float discreteFactor = deltaTime * realCoef;
					if (factorByParticle)
						discreteFactor *= getDiscreteFactor(particle);

					// the factor is clamped due to the use of a discrete time.
					// this is to prevent odd behaviours like the air drag being so strong that particle starts going towards the opposite direction.
					if (discreteFactor > clamp)
						discreteFactor = clamp;

					particle.velocity() += relativeForce * discreteFactor;
				}
		}
	}

	void LinearForce::innerImport(const IO::Descriptor& descriptor)
	{
		ZonedModifier::innerImport(descriptor);

		const IO::Attribute* attrib = NULL;
        if ((attrib = descriptor.getAttributeWithValue("value")))
			setValue(attrib->getValue<Vector3D>());

        if ((attrib = descriptor.getAttributeWithValue("relative value")))
		{
			bool tmpSquaredSpeed = false;
			bool tmpRelative = attrib->getValue<bool>();
            if ((attrib = descriptor.getAttributeWithValue("squared speed")))
				tmpSquaredSpeed = attrib->getValue<bool>();
			setRelative(tmpRelative,tmpSquaredSpeed);
		}

        if ((attrib = descriptor.getAttributeWithValue("parameter")))
		{
			Factor tmpFactor = FACTOR_LINEAR;
			Param tmpParam = getEnumValue<Param>(attrib->getValue<std::string>());
            if ((attrib = descriptor.getAttributeWithValue("factor type")))
				tmpFactor = getEnumValue<Factor>(attrib->getValue<std::string>());
			setParam(tmpParam,tmpFactor);
		}

        if ((attrib = descriptor.getAttributeWithValue("coefficient")))
			setCoef(attrib->getValue<float>());
	}

	void LinearForce::innerExport(IO::Descriptor& descriptor) const
	{
		ZonedModifier::innerExport(descriptor);
		descriptor.getAttribute("value")->setValue(getValue());
		descriptor.getAttribute("relative value")->setValue(isRelative());
		descriptor.getAttribute("squared speed")->setValue(isSquaredSpeedUsed());
		descriptor.getAttribute("parameter")->setValue<std::string>(getEnumName(getParam()));
		descriptor.getAttribute("factor type")->setValue<std::string>(getEnumName(getFactor()));
		descriptor.getAttribute("coefficient")->setValue(getCoef());
	}
}
