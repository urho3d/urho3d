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
#include "Extensions/Modifiers/SPK_RandomForce.h"

namespace SPK
{
	RandomForce::RandomForce(const Vector3D& minVector,const Vector3D& maxVector,float minPeriod,float maxPeriod) :
		Modifier(MODIFIER_PRIORITY_FORCE,true,true,false),
		minPeriod(1.0f),
		maxPeriod(1.0f)
	{
		setVectors(minVector,maxVector);
		setPeriods(minPeriod,maxPeriod);
	}

	void RandomForce::setVectors(const Vector3D& minVector,const Vector3D& maxVector)
	{
		this->minVector = minVector;
		this->maxVector = maxVector;
		this->minVector.setMin(maxVector);
		this->maxVector.setMax(minVector);
		transformDir(tMinVector,minVector);
		transformDir(tMaxVector,maxVector);
		tMinVector.setMin(tMaxVector);
		tMaxVector.setMax(tMinVector);
	}

	void RandomForce::setPeriods(float minPeriod,float maxPeriod)
	{
		if (minPeriod <= 0.0f || maxPeriod <= 0.0f)
		{
			SPK_LOG_WARNING("RandomForce::setPeriods(float,float) - Periods must be greater to 0, nothing is set");
			return;
		}

		if (minPeriod > maxPeriod)
		{
			SPK_LOG_WARNING("RandomForce::setPeriods(float,float) - min periods is greater than max periods, values are swapped");
			std::swap(minPeriod,maxPeriod);
		}

		this->minPeriod = minPeriod;
		this->maxPeriod = maxPeriod;
	}

	void RandomForce::innerUpdateTransform()
	{
		transformDir(tMinVector,minVector);
		transformDir(tMaxVector,maxVector);
		tMinVector.setMin(tMaxVector);
		tMaxVector.setMax(tMinVector);
	}

	void RandomForce::createData(DataSet& dataSet,const Group& group) const
	{
		dataSet.init(NB_DATA);
		dataSet.setData(FORCE_VECTOR_INDEX,SPK_NEW(Vector3DArrayData,group.getCapacity(),1));
		dataSet.setData(REMAINING_TIME_INDEX,SPK_NEW(FloatArrayData,group.getCapacity(),1));

		// Inits the data
		for (ConstGroupIterator particleIt(group); !particleIt.end(); ++particleIt)
			initParticle(*particleIt,&dataSet);
	}

	void RandomForce::init(Particle& particle,DataSet* dataSet) const
	{
		initParticle(particle,dataSet);
	}

	void RandomForce::advanceTime(const Particle& particle,DataSet* dataSet,float deltaTime,float& time) const
	{
		if (time <= 0.0f)
			initParticle(particle,dataSet);
		else
			time -= deltaTime;
	}

	void RandomForce::initParticle(const Particle& particle,DataSet* dataSet) const
	{
		size_t index = particle.getIndex();
		*SPK_GET_DATA(Vector3DArrayData,dataSet,FORCE_VECTOR_INDEX).getParticleData(index) = SPK_RANDOM(tMinVector,tMaxVector);
		*SPK_GET_DATA(FloatArrayData,dataSet,REMAINING_TIME_INDEX).getParticleData(index) = SPK_RANDOM(minPeriod,maxPeriod);
	}

	void RandomForce::modify(Group& group,DataSet* dataSet,float deltaTime) const
	{
		Vector3D* forceIt = SPK_GET_DATA(Vector3DArrayData,dataSet,FORCE_VECTOR_INDEX).getData();
		float* timeIt = SPK_GET_DATA(FloatArrayData,dataSet,REMAINING_TIME_INDEX).getData();

		if (group.isEnabled(PARAM_MASS))
			for (GroupIterator particleIt(group); !particleIt.end(); ++particleIt)
			{
				Particle& particle = *particleIt;
				advanceTime(particle,dataSet,deltaTime,*timeIt);

				particle.velocity() += *forceIt * deltaTime / particle.getParamNC(PARAM_MASS);

				++forceIt;
				++timeIt;
			}
		else
			for (GroupIterator particleIt(group); !particleIt.end(); ++particleIt)
			{
				Particle& particle = *particleIt;
				advanceTime(particle,dataSet,deltaTime,*timeIt);

				particle.velocity() += *forceIt * deltaTime; // opti for unset mass

				++forceIt;
				++timeIt;
			}
	}

	void RandomForce::innerImport(const IO::Descriptor& descriptor)
	{
		Modifier::innerImport(descriptor);

		const IO::Attribute* attrib = NULL;
        if ((attrib = descriptor.getAttributeWithValue("values")))
		{
			std::vector<Vector3D> tmpValues = attrib->getValues<Vector3D>();
			switch (tmpValues.size())
			{
			case 1 : setVectors(tmpValues[0],tmpValues[0]); break;
			case 2 : setVectors(tmpValues[0],tmpValues[1]); break;
			default : SPK_LOG_ERROR("RandomForce::innerImport(const IO::Descriptor&) - Wrong number of values : " << tmpValues.size());
			}
		}
        if ((attrib = descriptor.getAttributeWithValue("period")))
		{
			std::vector<float> tmpPeriods = attrib->getValues<float>();
			switch (tmpPeriods.size())
			{
			case 1 : setPeriods(tmpPeriods[0],tmpPeriods[0]); break;
			case 2 : setPeriods(tmpPeriods[0],tmpPeriods[1]); break;
			default : SPK_LOG_ERROR("RandomForce::innerImport(const IO::Descriptor&) - Wrong number of periods : " << tmpPeriods.size());
			}
		}
	}

	void RandomForce::innerExport(IO::Descriptor& descriptor) const
	{
		Modifier::innerExport(descriptor);

		Vector3D tmpValues[2] = {minVector,maxVector};
		descriptor.getAttribute("values")->setValues(tmpValues,2);

		float tmpPeriods[2] = {minPeriod,maxPeriod};
		descriptor.getAttribute("period")->setValues(tmpPeriods,minPeriod == maxPeriod ? 1 : 2);
	}
}
