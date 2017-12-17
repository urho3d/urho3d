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

#include <algorithm> // for std::swap and std::sort
#include <limits> // for max float value

#include <SPARK_Core.h>

namespace SPK
{
	const float Group::DEFAULT_VALUES[NB_PARAMETERS] =
	{
		1.0f,	// PARAM_SCALE
		1.0f,	// PARAM_MASS
		0.0f,	// PARAM_ANGLE
		0.0f,	// PARAM_TEXTURE_INDEX
		0.0f,	// PARAM_ROTATION_SPEED
	};

	Group::Group(const Ref<System>& system,size_t capacity) :
		Transformable(SHARE_POLICY_FALSE),
		system(system.get()),
		nbEnabledParameters(0),		
		birthAction(),
		deathAction(),
        minLifeTime(1.0f),
        maxLifeTime(1.0f),
        immortal(false),
        still(false),
        distanceComputationEnabled(false),
        sortingEnabled(false),
        AABBMin(),
        AABBMax(),
        physicalRadius(0.0f),
        graphicalRadius(1.0f),
        octree(NULL),
        nbBufferedParticles(0)
	{
		reallocate(capacity);
	}

	Group::Group(const Group& group) :
		Transformable(group),
		system(NULL),
		nbEnabledParameters(0),        
		minLifeTime(group.minLifeTime),
		maxLifeTime(group.maxLifeTime),
		immortal(group.immortal),
		still(group.still),
		distanceComputationEnabled(group.distanceComputationEnabled),
		sortingEnabled(group.sortingEnabled),
		AABBMin(group.AABBMin),
		AABBMax(group.AABBMax),
		physicalRadius(group.physicalRadius),		
        graphicalRadius(group.graphicalRadius),
        octree(NULL),
        nbBufferedParticles(0)
	{
		reallocate(group.getCapacity());

		renderer.obj = group.copyChild(group.renderer.obj);
		renderer.dataSet = attachDataSet(renderer.obj.get());

		setColorInterpolator(group.copyChild(group.colorInterpolator.obj));
		for (size_t i = 0; i < NB_PARAMETERS; ++i)
			setParamInterpolator(static_cast<Param>(i),group.copyChild(group.paramInterpolators[i].obj));

		for (std::vector<Ref<Emitter> >::const_iterator it = group.emitters.begin(); it != group.emitters.end(); ++it)
			emitters.push_back(group.copyChild(*it));

		for (std::vector<ModifierDef>::const_iterator it = group.modifiers.begin(); it != group.modifiers.end(); ++it)
		{
			const Ref<Modifier>& modifier = group.copyChild(it->obj);
			ModifierDef modifierDef(modifier,attachDataSet(modifier.get()));
			modifiers.push_back(modifierDef);
		}

		birthAction = group.copyChild(group.birthAction);
		deathAction = group.copyChild(group.deathAction);
	}

	Group::~Group()
	{
		destroyAllAdditionnalData();

		SPK_DELETE_ARRAY(particleData.positions);
		SPK_DELETE_ARRAY(particleData.velocities);
		SPK_DELETE_ARRAY(particleData.oldPositions);
		SPK_DELETE_ARRAY(particleData.ages);
		SPK_DELETE_ARRAY(particleData.lifeTimes);
		SPK_DELETE_ARRAY(particleData.energies);
		SPK_DELETE_ARRAY(particleData.sqrDists);
		SPK_DELETE_ARRAY(particleData.colors);

		for (size_t i = 0; i < NB_PARAMETERS; ++i)
			SPK_DELETE_ARRAY(particleData.parameters[i]);

		SPK_DELETE(octree);

		emptyBufferedParticles();
	}

	Particle Group::getParticle(size_t index)
	{
		SPK_ASSERT(index < particleData.nbParticles,"Group::getParticle(size_t) - Particle index is out of bounds : " << index);
		return Particle(*this,index);
	}

	const Particle Group::getParticle(size_t index) const
	{
		SPK_ASSERT(index < particleData.nbParticles,"Group::getParticle(size_t) - Particle index is out of bounds : " << index);
		return Particle(const_cast<Group&>(*this),index);
	}

	void Group::setLifeTime(float minLifeTime,float maxLifeTime)
	{
		SPK_ASSERT(minLifeTime > 0.0f && maxLifeTime > 0.0f,"Group::setLifeTime(float,float) - Life times must not be set to negative values");
		if (minLifeTime <= maxLifeTime)
		{
			this->minLifeTime = minLifeTime;
			this->maxLifeTime = maxLifeTime;
		}
		else
		{
			SPK_LOG_WARNING("Group::setEnergy(float,float) - minEnergy is higher than maxEnergy - Values are swapped");
			this->minLifeTime = maxLifeTime;
			this->maxLifeTime = minLifeTime;
		}
	}

	bool Group::updateParticles(float deltaTime)
	{
		// Prepares the additionnal data
		prepareAdditionnalData();

		size_t nbAutoBorn = 0;
		size_t nbManualBorn = nbBufferedParticles;

		// Checks the number of born particles
		bool hasAliveEmitters = false;
		activeEmitters.clear();

		for (std::vector<Ref<Emitter> >::const_iterator it = emitters.begin(); it != emitters.end(); ++it)
			if ((*it)->isActive())
			{
				int nb = (*it)->updateTankFromTime(deltaTime);
				if (nb > 0)
				{
					activeEmitters.push_back(WeakEmitterPair(*it,nb));
					nbAutoBorn += nb;
				}

				hasAliveEmitters |= ((*it)->getCurrentTank() != 0); // An emitter with some particles in its tank is still potentially alive
			}

		size_t emitterIndex = 0;
		size_t nbBorn = nbAutoBorn + nbManualBorn;

		// Updates the age of the particles function of the delta time
		for (size_t i = 0; i < particleData.nbParticles; ++i)
			particleData.ages[i] += deltaTime;

		// Computes the energy of the particles (if they are not immortal)
		if (!immortal)
			for (size_t i = 0; i < particleData.nbParticles; ++i)
				particleData.energies[i] = 1.0f - particleData.ages[i] / particleData.lifeTimes[i];

		// Updates the position of particles function of their velocity
		if (!still)
			for (size_t i = 0; i < particleData.nbParticles; ++i)
			{
				particleData.oldPositions[i] = particleData.positions[i];
				particleData.positions[i] += particleData.velocities[i] * deltaTime;
			}

		// Interpolates the parameters
		if (colorInterpolator.obj)
			colorInterpolator.obj->interpolate(particleData.colors,*this,colorInterpolator.dataSet);
		for (size_t i = 0; i < nbEnabledParameters; ++i)
		{
			FloatInterpolatorDef& interpolator = paramInterpolators[enabledParamIndices[i]];
			interpolator.obj->interpolate(particleData.parameters[enabledParamIndices[i]],*this,interpolator.dataSet);
		}

		// Updates the octree if one
		if (octree != NULL)
			octree->update();

		// Modifies the particles with specific active modifiers behavior
		for (std::vector<WeakModifierDef>::const_iterator it = activeModifiers.begin(); it != activeModifiers.end(); ++it)
			it->obj->modify(*this,it->dataSet,deltaTime);

		// Updates the renderer data
		if (renderer.obj)
			renderer.obj->update(*this,renderer.dataSet);

		// Checks dead particles and reinits or swaps
		for (size_t i = 0; i < particleData.nbParticles; ++i)
			if (particleData.energies[i] <= 0.0f)
			{
				// Death action
				if (deathAction && deathAction->isActive())
				{
				    Particle particle = getParticle(i); // fix for gcc
					deathAction->apply(particle);
				}

				bool replaceDeadParticle = false;
				while (!replaceDeadParticle && nbBorn > 0)
				{
					if (initParticle(i,emitterIndex,nbManualBorn))
						replaceDeadParticle = true;
					--nbBorn;
				}

				if (!replaceDeadParticle)
				{
					swapParticles(i,particleData.nbParticles - 1);
					--particleData.nbParticles;
					--i; // As we need to test the swapped particle
				}
			}

		// Emits new particles if some left
		while (nbBorn > 0 && particleData.maxParticles - particleData.nbParticles > 0)
		{
			if (!initParticle(particleData.nbParticles++,emitterIndex,nbManualBorn))
				--particleData.nbParticles;
			--nbBorn;
		}

		// Computes the distance of particles from the camera
		if (distanceComputationEnabled)
		{
			for (size_t i = 0; i < particleData.nbParticles; ++i)
				particleData.sqrDists[i] = getSqrDist(particleData.positions[i],system->getCameraPosition());
		}

		emptyBufferedParticles();

		return hasAliveEmitters || particleData.nbParticles > 0;
	}

	void Group::renderParticles()
	{
		if (renderer.obj && renderer.obj->isActive())
		{
			renderer.obj->prepareData(*this,renderer.dataSet);
			if (renderer.renderBuffer == NULL)
				renderer.renderBuffer = renderer.obj->attachRenderBuffer(*this);
			renderer.obj->render(*this,renderer.dataSet,renderer.renderBuffer);
		}
	}

	void Group::reallocate(size_t capacity)
	{
		SPK_ASSERT(capacity != 0,"Group::reallocate(size_t) - Group capacity must not be 0");

		if (isInitialized() && (!particleData.initialized || capacity != particleData.maxParticles))
		{
			destroyAllAdditionnalData();

			size_t copySize = particleData.nbParticles;
			if (capacity < copySize)
				copySize = capacity;

			reallocateArray(particleData.positions,capacity,copySize);
			reallocateArray(particleData.velocities,capacity,copySize);
			reallocateArray(particleData.oldPositions,capacity,copySize);
			reallocateArray(particleData.ages,capacity,copySize);
			reallocateArray(particleData.lifeTimes,capacity,copySize);
			reallocateArray(particleData.energies,capacity,copySize);
			reallocateArray(particleData.sqrDists,capacity,copySize);
			reallocateArray(particleData.colors,capacity,copySize);

			for (size_t i = 0; i < nbEnabledParameters; ++i)
				reallocateArray(particleData.parameters[enabledParamIndices[i]],capacity,copySize);

			particleData.initialized = true;
		}

		particleData.maxParticles = capacity;
	}

	void Group::setColorInterpolator(const Ref<ColorInterpolator>& interpolator)
	{
		if (colorInterpolator.obj != interpolator)
		{
			detachDataSet(colorInterpolator.dataSet);
			colorInterpolator.obj = interpolator;
			colorInterpolator.dataSet = attachDataSet(interpolator.get());
		}
	}

	void Group::setParamInterpolator(Param param,const Ref<FloatInterpolator>& interpolator)
	{
		if (paramInterpolators[param].obj != interpolator)
		{
			if (!paramInterpolators[param].obj && interpolator)
			{
				if (particleData.parameters[param] != NULL)
					SPK_LOG_FATAL("Group::setParamInterpolator(Param,FloatInterpolator*) - Unexpected memory leak happened");

				// Creates the data for the parameter
				if (isInitialized())
					particleData.parameters[param] = SPK_NEW_ARRAY(float,particleData.maxParticles);
			}
			else if (paramInterpolators[param].obj && !interpolator)
			{
				if (particleData.parameters[param] == NULL)
				{
					SPK_LOG_FATAL("Group::setParamInterpolator(Param,FloatInterpolator*) - Unexpected error happened");
				}

				// Destroys the data for the parameter
				SPK_DELETE_ARRAY(particleData.parameters[param]);
				particleData.parameters[param] = NULL;
			}

			detachDataSet(paramInterpolators[param].dataSet);

			paramInterpolators[param].obj = interpolator;
			paramInterpolators[param].dataSet = attachDataSet(interpolator.get());

			recomputeEnabledParamIndices();
		}
	}

	void Group::addEmitter(const Ref<Emitter>& emitter)
	{
		if (!emitter)
		{
			SPK_LOG_WARNING("Group::addEmitter(const Ref<Emitter>&) - A NULL emitter cannot be added to a group");
			return;
		}

		std::vector<Ref<Emitter> >::const_iterator it = std::find(emitters.begin(),emitters.end(),emitter);
		if (it != emitters.end())
		{
			SPK_LOG_WARNING("Group::addEmitter(const Ref<Emitter>&) - The emitter is already in the group and cannot be added");
			return;
		}

		emitters.push_back(emitter);
	}

	void Group::removeEmitter(const Ref<Emitter>& emitter)
	{
		std::vector<Ref<Emitter> >::iterator it = std::find(emitters.begin(),emitters.end(),emitter);
		if(it != emitters.end())
		{
			emitters.erase(it);
			/// TODO: remove this by optimizing the data structure.
			for(size_t e = 0; e < activeEmitters.size(); e++)
				if(activeEmitters[e].obj == emitter.get())
				{
					activeEmitters.erase(activeEmitters.begin() + e);
					break;
				}
		}
		else
			SPK_LOG_WARNING("Group::removeEmitter(const Ref<Emitter>&) - The emitter was not found in the group and cannot be removed");
	}

	void Group::addModifier(const Ref<Modifier>& modifier)
	{
		if (!modifier)
		{
			SPK_LOG_WARNING("Group::addModifier(const Ref<Modifier>&) - A NULL modifier cannot be added to a group");
			return;
		}

		for (std::vector<ModifierDef>::const_iterator it = modifiers.begin(); it != modifiers.end(); ++it)
			if (it->obj == modifier)
			{
				SPK_LOG_WARNING("Group::addModifier(const Ref<Modifier>&) - The modifier is already in the group and cannot be added");
				return;
			}

		ModifierDef modifierDef(modifier,attachDataSet(modifier.get()));
		modifiers.push_back(modifierDef);
		if (isInitialized())
		{
			sortedModifiers.push_back(modifierDef);
			std::sort(sortedModifiers.begin(),sortedModifiers.end(),CompareModifierPriority());
			SPK_ASSERT(modifiers.size() == sortedModifiers.size(),"Group::addModifier(const Ref<Modifier>&) - Internal Error - Inconsistent storage of modifiers");
		}
	}

	void Group::removeModifier(const Ref<Modifier>& modifier)
	{
		for (std::vector<ModifierDef>::iterator it = modifiers.begin(); it != modifiers.end(); ++it)
		{
			if (it->obj == modifier)
			{
				detachDataSet(it->dataSet);
				if (isInitialized())
					for (std::vector<WeakModifierDef>::iterator it2 = sortedModifiers.begin(); it2 != sortedModifiers.end(); ++it2)
						if (it2->obj == modifier)
						{
							sortedModifiers.erase(it2);
							break;
						}
				modifiers.erase(it);
				return;
			}
		}

		if (isInitialized() && modifiers.size() != sortedModifiers.size())
		{
			SPK_LOG_FATAL("Group::addModifier(Modifier*) - Internal Error - Inconsistent storage of modifiers");
		}
		else
		{
			SPK_LOG_WARNING("The modifier was not found in the group and cannot be removed");
		}
	}

    void Group::removeAllModifiers()
    {
        while(modifiers.size() > 0)
            removeModifier(modifiers.begin()->obj);
    }

	void Group::setRenderer(const Ref<Renderer>& renderer)
	{
		if (this->renderer.obj != renderer)
		{
			destroyRenderBuffer();
			detachDataSet(this->renderer.dataSet);

			this->renderer.obj = renderer;
			this->renderer.dataSet = attachDataSet(renderer.get());
		}
	}

	void Group::recomputeEnabledParamIndices()
	{
		nbEnabledParameters = 0;
		for (size_t i = 0; i < NB_PARAMETERS; ++i)
			if (paramInterpolators[i].obj)
				enabledParamIndices[nbEnabledParameters++] = i;
	}

	bool Group::initParticle(size_t index,size_t& emitterIndex,size_t& nbManualBorn)
	{
		Particle particle(getParticle(index));

		particleData.ages[index] = 0.0f;
		particleData.energies[index] = 1.0f;
		particleData.lifeTimes[index] = SPK_RANDOM(minLifeTime,maxLifeTime);

		if (colorInterpolator.obj)
			colorInterpolator.obj->init(particleData.colors[index],particle,colorInterpolator.dataSet);
		else
			particleData.colors[index] = 0xFFFFFFFF;

		for (size_t i = 0; i < nbEnabledParameters; ++i)
		{
			FloatInterpolatorDef& interpolator = paramInterpolators[enabledParamIndices[i]];
			interpolator.obj->init(particleData.parameters[enabledParamIndices[i]][index],particle,interpolator.dataSet);
		}

		if (nbManualBorn == 0)
		{
			activeEmitters[emitterIndex].obj->emit(particle);
			if (--activeEmitters[emitterIndex].nbBorn == 0)
				++emitterIndex;
		}
		else
		{
			CreationData& creationData = creationBuffer.front();

			if (creationData.zone)
				creationData.zone->generatePosition(particle.position(),creationData.full,particle.getRadius());
			else
				particle.position() = creationData.position;

			if (creationData.emitter)
			{
				float speed = SPK_RANDOM(creationData.emitter->getForceMin(),creationData.emitter->getForceMax()) / particle.getParam(PARAM_MASS);
				creationData.emitter->generateVelocity(particle,speed);
			}
			else
				particle.velocity() = creationData.velocity;

			--creationBuffer.front().nb;
			--nbManualBorn;
			--nbBufferedParticles;
			if (creationBuffer.front().nb <= 0)
				creationBuffer.pop_front();
		}

		particleData.oldPositions[index] = particleData.positions[index];

		for (std::vector<WeakModifierDef>::iterator it = initModifiers.begin(); it != initModifiers.end(); ++it)
			it->obj->init(particle,it->dataSet);

		if (particle.isAlive())
		{
			if (renderer.obj && renderer.obj->isActive())
				renderer.obj->init(particle,renderer.dataSet);

			// birth action
			if (birthAction && birthAction->isActive())
				birthAction->apply(particle);

			return true;
		}
		else
		{
			SPK_LOG_DEBUG("Particle " << index << " of Group " << this << " is born-dead");
			return false; // No birth neither death actions on born-dead particles
		}
	}

	void Group::swapParticles(size_t index0,size_t index1)
	{
		// Swaps particles attributes
		std::swap(particleData.positions[index0],particleData.positions[index1]);
		std::swap(particleData.velocities[index0],particleData.velocities[index1]);
		std::swap(particleData.oldPositions[index0],particleData.oldPositions[index1]);
		std::swap(particleData.ages[index0],particleData.ages[index1]);
		std::swap(particleData.energies[index0],particleData.energies[index1]);
		std::swap(particleData.lifeTimes[index0],particleData.lifeTimes[index1]);
		std::swap(particleData.sqrDists[index0],particleData.sqrDists[index1]);
		std::swap(particleData.colors[index0],particleData.colors[index1]);

		// Swaps particles enabled parameters
		for (size_t i = 0; i < nbEnabledParameters; ++i)
			std::swap(particleData.parameters[enabledParamIndices[i]][index0],particleData.parameters[enabledParamIndices[i]][index1]);

		// Swaps particles additionnal swappable data
		for (std::list<DataSet>::iterator it = dataSets.begin(); it != dataSets.end(); ++it)
			it->swap(index0,index1);
	}

	DataSet* Group::attachDataSet(DataHandler* dataHandler)
	{
		if (!isInitialized())
			return NULL;

		if (dataHandler != NULL && dataHandler->needsDataSet())
		{
			dataSets.push_back(DataSet());
			return &dataSets.back();
		}

		return NULL;
	}

	void Group::detachDataSet(DataSet* dataSet)
	{
		if (dataSet != NULL)
			for (std::list<DataSet>::iterator it = dataSets.begin(); it != dataSets.end(); ++it)
				if (&*it == dataSet)
				{
					dataSets.erase(it);
					break;
				}
	}

	void Group::destroyRenderBuffer()
	{
		SPK_DELETE(renderer.renderBuffer);
		renderer.renderBuffer = NULL;
	}

	void Group::destroyAllAdditionnalData()
	{
		destroyRenderBuffer();

		for (std::list<DataSet>::iterator it = dataSets.begin(); it != dataSets.end(); ++it)
			it->destroyAllData();
	}

	void Group::manageOctreeInstance(bool needsOctree)
	{
		if (needsOctree && octree == NULL) // creates an octree if needed
			octree = SPK_NEW(Octree,this);
		else if (!needsOctree && octree != NULL) // deletes the octree if no more needed
		{
			SPK_DELETE(octree);
			octree = NULL;
		}
	}

	Octree* Group::getOctree()
	{
		bool needsOctree = false;
		for (std::vector<WeakModifierDef>::const_iterator it = sortedModifiers.begin(); it != sortedModifiers.end(); ++it)
			needsOctree |= it->obj->NEEDS_OCTREE;
		manageOctreeInstance(needsOctree);

		return octree;
	}

	void Group::sortParticles()
	{
		if (sortingEnabled)
			sortParticles(0,particleData.nbParticles - 1);
	}

	void Group::computeAABB()
	{
		const float maxFloat = std::numeric_limits<float>::max();
		AABBMin.set(maxFloat,maxFloat,maxFloat);
		AABBMax.set(-maxFloat,-maxFloat,-maxFloat);

		if (renderer.obj && renderer.obj->isActive())
		{
			renderer.obj->prepareData(*this,renderer.dataSet);
			renderer.obj->computeAABB(AABBMin,AABBMax,*this,renderer.dataSet);
		}
		else // Switches to default AABB computation
			for (size_t i = 0; i < particleData.nbParticles; ++i)
			{
				AABBMin.setMin(particleData.positions[i]);
				AABBMax.setMax(particleData.positions[i]);
			}
	}

	void Group::sortParticles(int start,int end)
	{
		// quick sort implementation (can be optimized)
		if (start < end)
		{
			int i = start - 1;
			int j = end + 1;
			float pivot = particleData.sqrDists[(start + end) >> 1];
			while (true)
			{
				do ++i;
				while (particleData.sqrDists[i] > pivot);
				do --j;
				while (particleData.sqrDists[j] < pivot);
				if (i < j)
					swapParticles(i,j);
				else break;
			}

			sortParticles(start,j);
			sortParticles(j + 1,end);
		}
	}

	void Group::propagateUpdateTransform()
	{
		for (std::vector<Ref<Emitter> >::const_iterator it = emitters.begin(); it != emitters.end(); ++it)
			if (!(*it)->isShared())
				(*it)->updateTransform(this);

		for (std::vector<ModifierDef>::const_iterator it = modifiers.begin(); it != modifiers.end(); ++it)
			if (!it->obj->isShared() && it->obj->isLocalToSystem())
				it->obj->updateTransform(this);
	}

	void Group::addParticles(unsigned int nb,const Ref<Zone>& zone,const Ref<Emitter>& emitter,bool full)
	{
		SPK_ASSERT(emitter,"Group::addParticles(unsigned int,Zone*,Emitter*,bool) - emitter must not be NULL");
		SPK_ASSERT(zone,"Group::addParticles(unsigned int,Zone*,Emitter*,bool) - zone must not be NULL");
		addParticles(emitter->updateTankFromNb(nb),Vector3D(),Vector3D(),zone,emitter,full);
	}

	void Group::addParticles(unsigned int nb,const Ref<Zone>& zone,const Vector3D& velocity,bool full)
	{
		SPK_ASSERT(zone,"Group::addParticles(unsigned int,Zone*,const Vector3D&,bool) - zone must not be NULL");
		addParticles(nb,Vector3D(),velocity,zone,SPK_NULL_REF,full);
	}

	void Group::addParticles(unsigned int nb,const Vector3D& position,const Ref<Emitter>& emitter)
	{
		SPK_ASSERT(emitter,"Group::addParticles(unsigned int,const Vector3D&,Emitter*) - emitter must not be NULL");
		addParticles(emitter->updateTankFromNb(nb),position,Vector3D(),SPK_NULL_REF,emitter);
	}

	void Group::addParticles(unsigned int nb,const Ref<Emitter>& emitter)
	{
		SPK_ASSERT(emitter,"Group::addParticles(unsigned int,Emitter*) - emitter must not be NULL");
		addParticles(emitter->updateTankFromNb(nb),Vector3D(),Vector3D(),emitter->getZone(),emitter,emitter->isFullZone());
	}

	void Group::addParticles(const Ref<Zone>& zone,const Ref<Emitter>& emitter,float deltaTime,bool full)
	{
		SPK_ASSERT(emitter,"Group::addParticles(Zone*,Emitter*,float,bool) - emitter must not be NULL");
		SPK_ASSERT(zone,"Group::addParticles(Zone*,Emitter*,float,bool) - zone must not be NULL");
		addParticles(emitter->updateTankFromTime(deltaTime),Vector3D(),Vector3D(),zone,emitter,full);
	}

	void Group::addParticles(const Vector3D& position,const Ref<Emitter>& emitter,float deltaTime)
	{
		SPK_ASSERT(emitter,"Group::addParticles(const Vector3D&,Emitter*,float) - emitter must not be NULL");
		addParticles(emitter->updateTankFromTime(deltaTime),position,Vector3D(),SPK_NULL_REF,emitter);
	}

	void Group::addParticles(const Ref<Emitter>& emitter,float deltaTime)
	{
		SPK_ASSERT(emitter,"Group::addParticles(Emitter*,float) - emitter must not be NULL");
		addParticles(emitter->updateTankFromTime(deltaTime),Vector3D(),Vector3D(),emitter->getZone(),emitter,emitter->isFullZone());
	}

	float Group::addParticles(const Vector3D& start,const Vector3D& end,const Ref<Emitter>& emitter,float step,float offset)
	{
		SPK_ASSERT(emitter,"Group::addParticles(const Vector3D&,const Vector3D&,Emitter*,float,float) - emitter must not be NULL");

		if ((step <= 0.0f)||(offset < 0.0f))
			return 0.0f;

		Vector3D displacement = end - start;
		float totalDist = displacement.getNorm();

		while(offset < totalDist)
		{
			Vector3D position = start;
			position += displacement * offset / totalDist;
			addParticles(1,position,Vector3D(),Ref<Zone>(),emitter);
			offset += step;
		}

		return offset - totalDist;
	}

	float Group::addParticles(const Vector3D& start,const Vector3D& end,const Vector3D& velocity,float step,float offset)
	{
		if ((step <= 0.0f)||(offset < 0.0f))
			return 0.0f;

		Vector3D displacement = end - start;
		float totalDist = displacement.getNorm();

		while(offset < totalDist)
		{
			Vector3D position = start;
			position += displacement * (offset / totalDist);
			addParticles(1,position,velocity,Ref<Zone>(),Ref<Emitter>());
			offset += step;
		}

		return offset - totalDist;
	}

	void Group::addParticles(unsigned int nb,const Vector3D& position,const Vector3D& velocity,const Ref<Zone>& zone,const Ref<Emitter>& emitter,bool full)
	{
		if (nb == 0)
			return;

		SPK_ASSERT(isInitialized(),"Group::addParticles(unsigned int,const Vector3D&,const Vector3D&,Zone*,Emitter*,bool) - Particles cannot be added to an uninitialized group");

		CreationData data = {nb,position,velocity,zone,emitter,full};
		creationBuffer.push_back(data);
		nbBufferedParticles += nb;
	}

	void Group::flushBufferedParticles()
	{
		if (nbBufferedParticles == 0)
			return;

		prepareAdditionnalData();

		size_t nbManualBorn = nbBufferedParticles;

		size_t dummy;
		while (nbManualBorn > 0 && particleData.maxParticles - particleData.nbParticles > 0)
			if (!initParticle(particleData.nbParticles++,dummy,nbManualBorn))
				--particleData.nbParticles;

		emptyBufferedParticles();
	}

	void Group::emptyBufferedParticles()
	{
		creationBuffer.clear();
		nbBufferedParticles = 0;
	}

	inline void Group::prepareAdditionnalData()
	{
		if (renderer.obj)
			renderer.obj->prepareData(*this,renderer.dataSet);

		activeModifiers.clear();
		initModifiers.clear();

		bool needsOctree = false;
		for (std::vector<WeakModifierDef>::const_iterator it = sortedModifiers.begin(); it != sortedModifiers.end(); ++it)
		{
			it->obj->prepareData(*this,it->dataSet);	// if it has a data set, it is prepared
			if (it->obj->CALL_INIT)
				initModifiers.push_back(*it); // if its init method needs to be called it is added to the init vector
			if (it->obj->isActive())
				activeModifiers.push_back(*it); // if the modifier is active, it is added to the active vector
			needsOctree |= it->obj->NEEDS_OCTREE;
		}

		manageOctreeInstance(needsOctree);

		if (colorInterpolator.obj)
			colorInterpolator.obj->prepareData(*this,colorInterpolator.dataSet);
		for (size_t i = 0; i < nbEnabledParameters; ++i)
		{
			FloatInterpolatorDef& interpolator = paramInterpolators[enabledParamIndices[i]];
			interpolator.obj->prepareData(*this,interpolator.dataSet);
		}
	}

	void Group::initData()
	{
		if (isInitialized() && !particleData.initialized)
		{
			// Creates particle data arrays
			reallocate(particleData.maxParticles);

			// Creates data sets
			renderer.dataSet = attachDataSet(renderer.obj.get());
			colorInterpolator.dataSet = attachDataSet(colorInterpolator.obj.get());
			for (size_t i = 0; i < nbEnabledParameters; ++i)
			{
				FloatInterpolatorDef& interpolator = paramInterpolators[enabledParamIndices[i]];
				interpolator.dataSet = attachDataSet(interpolator.obj.get());
			}

			for (std::vector<ModifierDef>::iterator it = modifiers.begin(); it != modifiers.end(); ++it)
			{
				it->dataSet = attachDataSet(it->obj.get());
				sortedModifiers.push_back(*it);
			}
			std::sort(sortedModifiers.begin(),sortedModifiers.end(),CompareModifierPriority());
		}
	}

	void Group::setBirthAction(const Ref<Action>& action)
	{
		birthAction = action;
	}

	void Group::setDeathAction(const Ref<Action>& action)
	{
		deathAction = action;
	}

	DataSet* Group::getModifierDataSet(const Ref<Modifier>& modifier)
	{
		for (std::vector<ModifierDef>::const_iterator it = modifiers.begin(); it != modifiers.end(); ++it)
			if (it->obj == modifier)
				return it->dataSet;

		SPK_LOG_WARNING("Group::getModifierDataSet(Modifier*) - The modifier was not found in the group, NULL is returned");
		return NULL;
	}

	void Group::setGraphicalRadius(float radius)
	{
		if (radius < 0)
		{
			radius = 0.0f;
			SPK_LOG_WARNING("Group::setGraphicalRadius(float) - The radius cannot be set to a negative value - 0 is used");
		}
		graphicalRadius = radius;
	}

	void Group::setPhysicalRadius(float radius)
	{
		if (radius < 0)
		{
			radius = 0.0f;
			SPK_LOG_WARNING("Group::setPhysicalRadius(float) - The radius cannot be set to a negative value - 0 is used");
		}
		physicalRadius = radius;
	}

	Ref<SPKObject> Group::findByName(const std::string& name)
	{
		Ref<SPKObject> object = SPKObject::findByName(name);
		if (object) return object;

		if (renderer.obj)
		{
			object = renderer.obj->findByName(name);
			if (object) return object;
		}

		if (colorInterpolator.obj)
		{
			object = colorInterpolator.obj->findByName(name);
			if (object) return object;
		}

		for (size_t i = 0; i < NB_PARAMETERS; ++i)
			if (paramInterpolators[i].obj)
			{
				object = paramInterpolators[i].obj->findByName(name);
				if (object) return object;
			}

		for (std::vector<Ref<Emitter> >::const_iterator it = emitters.begin(); it != emitters.end(); ++it)
		{
			object = (*it)->findByName(name);
			if (object) return object;
		}

		for (std::vector<ModifierDef>::const_iterator it = modifiers.begin(); it != modifiers.end(); ++it)
		{
			object = it->obj->findByName(name);
			if (object) return object;
		}

		if (birthAction)
		{
			object = birthAction->findByName(name);
			if (object) return object;
		}

		if (deathAction)
		{
			object = deathAction->findByName(name);
			if (object) return object;
		}

		return SPK_NULL_REF;
	}

	void Group::innerImport(const IO::Descriptor& descriptor)
	{
		Transformable::innerImport(descriptor);

		const IO::Attribute* attrib = NULL;

        if ((attrib = descriptor.getAttributeWithValue("capacity")))
			reallocate(attrib->getValue<uint32>());
        if ((attrib = descriptor.getAttributeWithValue("color interpolator")))
			setColorInterpolator(attrib->getValueRef<ColorInterpolator>());
        if ((attrib = descriptor.getAttributeWithValue("scale interpolator")))
			setParamInterpolator(PARAM_SCALE,attrib->getValueRef<FloatInterpolator>());
        if ((attrib = descriptor.getAttributeWithValue("mass interpolator")))
			setParamInterpolator(PARAM_MASS,attrib->getValueRef<FloatInterpolator>());
        if ((attrib = descriptor.getAttributeWithValue("angle interpolator")))
			setParamInterpolator(PARAM_ANGLE,attrib->getValueRef<FloatInterpolator>());
        if ((attrib = descriptor.getAttributeWithValue("texture index interpolator")))
			setParamInterpolator(PARAM_TEXTURE_INDEX,attrib->getValueRef<FloatInterpolator>());
        if ((attrib = descriptor.getAttributeWithValue("rotation speed interpolator")))
			setParamInterpolator(PARAM_ROTATION_SPEED,attrib->getValueRef<FloatInterpolator>());

        if ((attrib = descriptor.getAttributeWithValue("emitters")))
		{
			const std::vector<Ref<Emitter> >& tmpEmitters = attrib->getValuesRef<Emitter>();
			for (size_t i = 0; i < tmpEmitters.size(); ++i)
				addEmitter(tmpEmitters[i]);
		}

        if ((attrib = descriptor.getAttributeWithValue("modifiers")))
		{
			const std::vector<Ref<Modifier> >& tmpModifiers = attrib->getValuesRef<Modifier>();
			for (size_t i = 0; i < tmpModifiers.size(); ++i)
                addModifier(tmpModifiers[i]);
		}

        if ((attrib = descriptor.getAttributeWithValue("birth action")))
			setBirthAction(attrib->getValueRef<Action>());
        if ((attrib = descriptor.getAttributeWithValue("death action")))
			setDeathAction(attrib->getValueRef<Action>());
        if ((attrib = descriptor.getAttributeWithValue("renderer")))
			setRenderer(attrib->getValueRef<Renderer>());

        if ((attrib = descriptor.getAttributeWithValue("life time")))
		{
			std::vector<float> tmpTimes = attrib->getValues<float>();
			switch(tmpTimes.size())
			{
				case 1 : setLifeTime(tmpTimes[0],tmpTimes[0]); break;
				case 2 : setLifeTime(tmpTimes[0],tmpTimes[1]); break;
				default : SPK_LOG_ERROR("Group::innerImport(const IO::Descriptor&) - Wrong number of life times : " << tmpTimes.size());
			}
		}

        if ((attrib = descriptor.getAttributeWithValue("immortal")))
			setImmortal(attrib->getValue<bool>());
        if ((attrib = descriptor.getAttributeWithValue("still")))
			setStill(attrib->getValue<bool>());
        if ((attrib = descriptor.getAttributeWithValue("distance computation enabled")))
			enableDistanceComputation(attrib->getValue<bool>());
        if ((attrib = descriptor.getAttributeWithValue("sorting enabled")))
			enableSorting(attrib->getValue<bool>());

        if ((attrib = descriptor.getAttributeWithValue("radius")))
		{
			std::vector<float> tmpRadiuses = attrib->getValues<float>();
			switch(tmpRadiuses.size())
			{
				case 1 : setRadius(tmpRadiuses[0]); break;
				case 2 : setGraphicalRadius(tmpRadiuses[0]); setPhysicalRadius(tmpRadiuses[1]); break;
				default : SPK_LOG_ERROR("Group::innerImport(const IO::Descriptor&) - Wrong number of radiuses : " << tmpRadiuses.size());
			}
		}
	}

	void Group::innerExport(IO::Descriptor& descriptor) const
	{
		Transformable::innerExport(descriptor);

		descriptor.getAttribute("capacity")->setValue<uint32>(getCapacity());
		descriptor.getAttribute("color interpolator")->setValueOptionalOnNull(getColorInterpolator());
		descriptor.getAttribute("scale interpolator")->setValueOptionalOnNull(getParamInterpolator(PARAM_SCALE));
		descriptor.getAttribute("mass interpolator")->setValueOptionalOnNull(getParamInterpolator(PARAM_MASS));
		descriptor.getAttribute("angle interpolator")->setValueOptionalOnNull(getParamInterpolator(PARAM_ANGLE));
		descriptor.getAttribute("texture index interpolator")->setValueOptionalOnNull(getParamInterpolator(PARAM_TEXTURE_INDEX));
		descriptor.getAttribute("rotation speed interpolator")->setValueOptionalOnNull(getParamInterpolator(PARAM_ROTATION_SPEED));

		size_t nbEmitters = getNbEmitters();
		if (nbEmitters > 0)
			descriptor.getAttribute("emitters")->setValuesRef(&emitters[0],nbEmitters);

		size_t nbModifiers = getNbModifiers();
		if (nbModifiers > 0)
		{
			Ref<Modifier>* tmpModifiers = SPK_NEW_ARRAY(Ref<Modifier>,nbModifiers);
			for (size_t i = 0; i < nbModifiers; ++i)
				tmpModifiers[i] = getModifier(i);
			descriptor.getAttribute("modifiers")->setValuesRef(tmpModifiers,nbModifiers);
			SPK_DELETE_ARRAY(tmpModifiers);
		}

		descriptor.getAttribute("birth action")->setValueOptionalOnNull(getBirthAction());
		descriptor.getAttribute("death action")->setValueOptionalOnNull(getDeathAction());
		descriptor.getAttribute("renderer")->setValueOptionalOnNull(getRenderer());

		float tmpTimes[2] = {minLifeTime,maxLifeTime};
		descriptor.getAttribute("life time")->setValues(tmpTimes,tmpTimes[0] == tmpTimes[1] ? 1 : 2);

		descriptor.getAttribute("immortal")->setValueOptionalOnFalse(immortal);
		descriptor.getAttribute("still")->setValueOptionalOnFalse(still);
		descriptor.getAttribute("distance computation enabled")->setValueOptionalOnFalse(distanceComputationEnabled);
		descriptor.getAttribute("sorting enabled")->setValueOptionalOnFalse(sortingEnabled);

		float tmpRadiuses[2] = {graphicalRadius,physicalRadius};
		descriptor.getAttribute("radius")->setValues(tmpRadiuses,tmpRadiuses[0] == tmpRadiuses[1] ? 1 : 2);
	}
}
