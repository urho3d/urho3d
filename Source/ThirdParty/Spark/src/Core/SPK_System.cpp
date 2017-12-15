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

#include <algorithm>
#include <limits> // for max float value

#include <SPARK_Core.h>

namespace SPK
{
	StepMode System::stepMode(STEP_MODE_REAL);
	float System::constantStep(0.0f);
	float System::minStep(0.0f);
	float System::maxStep(0.0f);

	bool System::clampStepEnabled(false);
	float System::clampStep(1.0f);

	System::System(bool initialize) :
		Transformable(SHARE_POLICY_TRUE),
		groups(),
		deltaStep(0.0f),		
		initialized(initialize),
        active(true),
        AABBComputationEnabled(false),
        AABBMin(),
        AABBMax()
	{}

	System::System(const System& system) :
		Transformable(system),
		deltaStep(0.0f),		
		initialized(system.initialized),
        active(system.active),
        AABBComputationEnabled(system.AABBComputationEnabled),
        AABBMin(system.AABBMin),
        AABBMax(system.AABBMax)
	{
		for (std::vector<Ref<Group> >::const_iterator it = system.groups.begin(); it != system.groups.end(); ++it)
		{
			Ref<Group> group = system.copyChild(*it);
			setGroupSystem(group,this);
			groups.push_back(group);
		}
	}

	System::~System()
	{
		while (groups.size() > 0)
			removeGroup(groups.back());
	}

	Ref<Group> System::createGroup(size_t capacity)
	{
		if (capacity == 0)
		{
			SPK_LOG_ERROR("System::createGroup(size_t) - The capacity of a Group cannot be 0, NULL is returned");
			return SPK_NULL_REF;
		}

		Ref<Group> newGroup = SPK_NEW(Group,this,capacity);
		groups.push_back(newGroup);
		return newGroup;
	}

	Ref<Group> System::createGroup(const Ref<Group>& group)
	{
		if (!group)
		{
			SPK_LOG_WARNING("System::createGroup(const Ref<Group>&) - The group to copy is NULL");
			return SPK_NULL_REF;
		}

		Ref<Group> newGroup = copy(group);
		setGroupSystem(newGroup,this);
		groups.push_back(newGroup);
		return newGroup;
	}

	void System::addGroup(const Ref<Group>& group)
	{
		if (!group)
		{
			SPK_LOG_WARNING("System::addGroup(const Ref<Group>&) - The group to add is NULL");
			return;
		}

		setGroupSystem(group,this);
		groups.push_back(group);
	}

	void System::removeGroup(const Ref<Group>& group)
	{
		std::vector<Ref<Group> >::iterator it = std::find(groups.begin(),groups.end(),group.get());
		if (it != groups.end())
		{
			setGroupSystem(*it,NULL,false); // false to avoid infinite loop
			groups.erase(it);
		}
		else
		{
			SPK_LOG_WARNING("System::removeGroup(Group*) - The group " << group.get() << " was not found in the system and cannot be removed");
		}
	}

	size_t System::getNbParticles() const
	{
		size_t nbParticles = 0;
		for (std::vector<Ref<Group> >::const_iterator it = groups.begin(); it != groups.end(); ++it)
			nbParticles += (*it)->getNbParticles();
		return nbParticles;
	}

	bool System::updateParticles(float deltaTime)
	{
		if (!initialized)
		{
			SPK_LOG_WARNING("System::updateParticles(float) - An uninitialized system cannot be updated");
			return true;
		}

		bool alive = true;

		if ((clampStepEnabled)&&(deltaTime > clampStep))
			deltaTime = clampStep;

		if (stepMode != STEP_MODE_REAL)
		{
			deltaTime += deltaStep;

			float updateStep;
			if (stepMode == STEP_MODE_ADAPTIVE)
			{
				if (deltaTime > maxStep)
					updateStep = maxStep;
				else if (deltaTime < minStep)
					updateStep = minStep;
				else
					updateStep = deltaTime;
			}
			else
				updateStep = constantStep;

			while(deltaTime >= updateStep)
			{
				if (alive && !innerUpdate(updateStep))
					alive = false;
				deltaTime -= updateStep;
			}
			deltaStep = deltaTime;
		}
		else
			alive = innerUpdate(deltaTime);

		for (std::vector<Ref<Group> >::const_iterator it = groups.begin(); it != groups.end(); ++it)
			(*it)->sortParticles();

		if (isAABBComputationEnabled())
		{
			const float maxFloat = std::numeric_limits<float>::max();
			AABBMin.set(maxFloat,maxFloat,maxFloat);
			AABBMax.set(-maxFloat,-maxFloat,-maxFloat);

			for (std::vector<Ref<Group> >::const_iterator it = groups.begin(); it != groups.end(); ++it)
			{
				(*it)->computeAABB();

				AABBMin.setMin((*it)->getAABBMin());
				AABBMax.setMax((*it)->getAABBMax());
			}
		}
		else
		{
			const Vector3D pos = getTransform().getWorldPos();
			AABBMin = AABBMax = pos;
		}

		active = alive;
		return active;
	}

	void System::renderParticles() const
	{
		if (!initialized)
		{
			SPK_LOG_WARNING("System::updateParticles(float) - An uninitialized system cannot be rendered");
			return;
		}

		for (std::vector<Ref<Group> >::const_iterator it = groups.begin(); it != groups.end(); ++it)
			(*it)->renderParticles();
	}

	void System::initialize()
	{
		if (initialized)
			return; // the system is already initialized

		initialized = true;
		for (std::vector<Ref<Group> >::const_iterator it = groups.begin(); it != groups.end(); ++it)
			(*it)->initData();
	}

	Ref<SPKObject> System::findByName(const std::string& name)
	{
		Ref<SPKObject> object = SPKObject::findByName(name);
		if (object) return object;

		for (std::vector<Ref<Group> >::const_iterator it = groups.begin(); it != groups.end(); ++it)
		{
			object = (*it)->findByName(name);
			if (object) return object;
		}

		return SPK_NULL_REF;
	}

	bool System::innerUpdate(float deltaTime)
	{
        // Transform
		updateTransform();

        // Particles
		bool alive = false;
		for (std::vector<Ref<Group> >::const_iterator it = groups.begin(); it != groups.end(); ++it)
			alive |= (*it)->updateParticles(deltaTime);
		return alive;
	}

	void System::propagateUpdateTransform()
	{
		for (std::vector<Ref<Group> >::const_iterator it = groups.begin(); it != groups.end(); ++it)
			(*it)->updateTransform(this);
	}

	void System::innerImport(const IO::Descriptor& descriptor)
	{
		Transformable::innerImport(descriptor);

		const IO::Attribute* attrib = NULL;
        if ((attrib = descriptor.getAttributeWithValue("groups")))
		{
			const std::vector<Ref<Group> >& tmpGroups = attrib->getValuesRef<Group>();
            for (size_t i = 0; i < tmpGroups.size(); ++i)
                addGroup(tmpGroups[i]);
		}
	}

	void System::innerExport(IO::Descriptor& descriptor) const
	{
		Transformable::innerExport(descriptor);
		if (getNbGroups() > 0)
			descriptor.getAttribute("groups")->setValuesRef(&groups[0],getNbGroups());
	}

	void System::setGroupSystem(const Ref<Group>& group,System* system,bool remove)
	{
		if (group->system != system)
		{
			if (!group)
				SPK_LOG_FATAL("System::setGroupSystem(const Ref<Group>&,const System*,bool) - Internal Error - The group is NULL");

			if (remove && group->system != NULL)
				group->system->removeGroup(group);

			group->system = system;
			group->initData(); // To initialize the group if needed
		}
	}
}
