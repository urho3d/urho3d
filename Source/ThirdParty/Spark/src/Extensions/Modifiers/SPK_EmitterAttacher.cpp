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
#include "Extensions/Modifiers/SPK_EmitterAttacher.h"

namespace SPK
{
	EmitterAttacher::EmitterAttacher(const Ref<Group>& group,const Ref<Emitter>& emitter,bool orientate,bool rotate) :
		Modifier(MODIFIER_PRIORITY_CHECK,true,true,false),
		baseEmitter(emitter),
		targetGroup(group),
		orientationEnabled(orientate),
		rotationEnabled(rotate)
	{}

	EmitterAttacher::EmitterAttacher(const EmitterAttacher& emitterAttacher) :
		Modifier(emitterAttacher),
		orientationEnabled(emitterAttacher.orientationEnabled),
		rotationEnabled(emitterAttacher.rotationEnabled)
	{
		baseEmitter = emitterAttacher.copyChild(emitterAttacher.baseEmitter);
		targetGroup = emitterAttacher.copyChild(emitterAttacher.targetGroup);
	}

	EmitterAttacher::~EmitterAttacher(){}

	EmitterAttacher::EmitterData::EmitterData(size_t nbParticles,Group* emittingGroup) :
		data(SPK_NEW_ARRAY(Ref<Emitter>,nbParticles)),
		dataSize(nbParticles),
		group(emittingGroup)
	{}

	EmitterAttacher::EmitterData::~EmitterData()
	{
		SPK_DELETE_ARRAY(data);
	}

	void EmitterAttacher::createData(DataSet& dataSet,const Group& group) const
	{
		dataSet.init(NB_DATA);
		EmitterData* data = SPK_NEW(EmitterData,group.getCapacity(),targetGroup.get());
		dataSet.setData(EMITTER_INDEX,data);
		initData(*data,group);
	}

	void EmitterAttacher::checkData(DataSet& dataSet,const Group& group) const
	{
		EmitterData& data = SPK_GET_DATA(EmitterData,&dataSet,EMITTER_INDEX);
		Group* currentDataGroup = data.getGroup();
		if (currentDataGroup != targetGroup)
		{
			data.setGroup(targetGroup.get());
			initData(data,group);
		}
	}

	bool EmitterAttacher::checkValidity() const
	{
		if (!targetGroup)
		{
			SPK_LOG_ERROR("EmitterAttacher::checkValidity() - The target group is NULL and cannot be used");
			return false;
		}
		else if (!targetGroup->getSystem())
		{
			SPK_LOG_ERROR("EmitterAttacher::checkValidity() - The target group is invalid (it is not bound to a system) and cannot be used");
			return false;
		}

		if (!baseEmitter)
		{
			SPK_LOG_ERROR("EmitterAttacher::checkValidity() - The base emitter is NULL and cannot be used");
			return false;
		}
		else if (baseEmitter->getZone()->isShared())
		{
			SPK_LOG_ERROR("EmitterAttacher::checkValidity() - The base emitter is invalid (its zone is shared) and cannot be used");
			return false;
		}

		return true;
	}

	void EmitterAttacher::initData(EmitterData& data,const Group& group) const
	{
		for (ConstGroupIterator particleIt(group); !particleIt.end(); ++particleIt)
			data.setEmitter(particleIt->getIndex(),baseEmitter);
	}

	void EmitterAttacher::init(Particle& particle,DataSet* dataSet) const
	{
		SPK_GET_DATA(EmitterData,dataSet,EMITTER_INDEX).setEmitter(particle.getIndex(),baseEmitter);
	}

	void EmitterAttacher::modify(Group& group,DataSet* dataSet,float deltaTime) const
	{
		if (!checkValidity())
			return;

		EmitterData& data = SPK_GET_DATA(EmitterData,dataSet,EMITTER_INDEX);
		Ref<Emitter>* emitterIt = data.getEmitters();

		bool rotationEnabled = this->rotationEnabled && group.isEnabled(PARAM_ANGLE);

		for (ConstGroupIterator particleIt(group); !particleIt.end(); ++particleIt)
		{
			const Particle& particle = *particleIt;
			const Ref<Emitter>& emitter = *emitterIt;

			emitter->getTransform().setPosition(particle.position());
			if (orientationEnabled)
			{
				Vector3D look(-particle.velocity());
				Vector3D up(0.0f,1.0f,0.0f);

				if (look.x == 0.0f && look.z == 0.0f) // Handles special cases
				{
					float tmp = (look.y >= 0.0f ? 1.0f : -1.0f);
					look.set(0.0f,tmp,0.0f);
					up.set(0.0f,0.0f,-tmp);
				}
				if (rotationEnabled)
				{
					float angle = -particle.getParamNC(PARAM_ANGLE); // minus as look is inverted
					look.normalize();

					float c = std::cos(angle);
					float s = std::sin(angle);
					float a = 1 - c;

					up.x = look.x * look.y * a - look.z * s;
					up.y = look.y * look.y + (1.0f - look.y * look.y) * c;
					up.z = look.y * look.z * a + look.x * s;
				}

				emitter->getTransform().setOrientationRH(look,up); // TODO What about LH ?
			}

			emitter->updateTransform();
			targetGroup->addParticles(emitter,deltaTime);

			++emitterIt;
		}
	}

	void EmitterAttacher::EmitterData::setEmitter(size_t index,const Ref<Emitter>& emitter)
	{
		data[index] = copy(emitter);
		data[index]->getTransform().reset();
	}

	void EmitterAttacher::innerImport(const IO::Descriptor& descriptor)
	{
		Modifier::innerImport(descriptor);

		const IO::Attribute* attrib = NULL;
        if ((attrib = descriptor.getAttributeWithValue("base emitter")))
			setEmitter(attrib->getValueRef<Emitter>());

        if ((attrib = descriptor.getAttributeWithValue("orientation enabled")))
		{
			bool tmpRotationEnabled = false;
			bool tmpOrientationEnabled = attrib->getValue<bool>();
            if ((attrib = descriptor.getAttributeWithValue("rotation enabled")))
				tmpRotationEnabled = attrib->getValue<bool>();
			enableEmitterOrientation(tmpOrientationEnabled,tmpRotationEnabled);
		}

        if ((attrib = descriptor.getAttributeWithValue("target group")))
			setTargetGroup(attrib->getValueRef<Group>());
	}

	void EmitterAttacher::innerExport(IO::Descriptor& descriptor) const
	{
		Modifier::innerExport(descriptor);
		descriptor.getAttribute("base emitter")->setValueRef(getEmitter());
		descriptor.getAttribute("orientation enabled")->setValue(isEmitterOrientationEnabled());
		descriptor.getAttribute("rotation enabled")->setValue(isEmitterRotationEnabled());
		descriptor.getAttribute("target group")->setValueRef(getTargetGroup());
	}
}
