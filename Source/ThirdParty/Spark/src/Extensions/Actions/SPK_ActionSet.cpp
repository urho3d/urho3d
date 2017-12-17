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
#include "Extensions/Actions/SPK_ActionSet.h"

namespace SPK
{
	ActionSet::ActionSet(const ActionSet& actionSet) :
        Action(actionSet),
		actions()
	{
		for (std::vector<Ref<Action> >::const_iterator it = actionSet.actions.begin(); it != actionSet.actions.end(); ++it)
			actions.push_back(actionSet.copyChild(*it));
	}

	ActionSet::~ActionSet(){}

    void ActionSet::clearActions()
    {
        actions.clear();
    }

	void ActionSet::addAction(const Ref<Action>& action)
	{
		if (action && action != this)
			actions.push_back(action);
		else
			SPK_LOG_WARNING("ActionSet::addAction(const Ref<Action>&) - Cannot add this action to the action set (Either NULL or the action set itself)");
	}

	void ActionSet::removeAction(const Ref<Action>& action)
	{
		for (std::vector<Ref<Action> >::iterator it = actions.begin(); it != actions.end(); ++it)
			if (*it == action)
			{
				actions.erase(it);
				return;
			}

		SPK_LOG_WARNING("ActionSet::removeAction(const Ref<Action>&) - The action was not found in the action set and cannot be removed");
	}

	const Ref<Action>& ActionSet::getAction(size_t index) const
	{
		SPK_ASSERT(index <= getNbActions(),"ActionSet::getAction(size_t) - Action index is out of bounds : " << index);
		return actions[index];
	}

	void ActionSet::apply(Particle& particle) const
	{
		for (std::vector<Ref<Action> >::const_iterator it = actions.begin(); it != actions.end(); ++it)
			(*it)->apply(particle);
	}

	Ref<SPKObject> ActionSet::findByName(const std::string& name)
	{
		Ref<SPKObject> object = Action::findByName(name);
		if (object) return object;

		for (std::vector<Ref<Action> >::const_iterator it = actions.begin(); it != actions.end(); ++it)
		{
			object = (*it)->findByName(name);
			if (object) return object;
		}

		return SPK_NULL_REF;
	}

	void ActionSet::innerImport(const IO::Descriptor& descriptor)
	{
		Action::innerImport(descriptor);

		const IO::Attribute* attrib = NULL;
        if ((attrib = descriptor.getAttributeWithValue("actions")))
		{
			std::vector<Ref<Action> > tmpActions = attrib->getValuesRef<Action>();
			for (size_t i = 0; i < tmpActions.size(); ++i)
				addAction(tmpActions[i]);
		}
	}

	void ActionSet::innerExport(IO::Descriptor& descriptor) const
	{
		Action::innerExport(descriptor);
		descriptor.getAttribute("actions")->setValuesRef<Action>(&actions[0],getNbActions());
	}
}
