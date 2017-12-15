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

#ifndef H_SPK_ACTION
#define H_SPK_ACTION

#include "IO/SPK_IO_Descriptor.h"

namespace SPK
{
	class Particle;

	/**
	* @brief An abstract class that allows to perform an action on a single particle
	*
	* The action can be triggered by a particular event.<br>
	* For instance by using Group::setBirthAction(Action*), the action will be triggered on a given particle when it's born.<br>
	* The equivalent method exists with particle's death (Group::setDeathAction(Action*).<br>
	* Some modifiers can also trigger actions. In a more general way, any object can potentially triggers actions.
	*/
	class Action : public SPKObject
	{
	SPK_START_DESCRIPTION
	SPK_PARENT_ATTRIBUTES(SPKObject)
	SPK_ATTRIBUTE("active",ATTRIBUTE_TYPE_BOOL)
	SPK_END_DESCRIPTION

	public :

		virtual ~Action() {}

		/**
		* @brief Activates or deactivates the action
		* An inactive action cannot be triggered 
		* @param active : true to activate, false to deactivate
		*/
		void setActive(bool active);

		/**
		* @brief Tells whether the action is active or not
		* @return true if the action is active, false of not
		*/
		bool isActive() const;

		/**
		* @brief Applies the action on a given particle
		* @param particle : the particle on which to apply the action
		*/
		virtual void apply(Particle& particle) const = 0;

	protected :
	
		Action();

		virtual void innerImport(const IO::Descriptor& descriptor) override;
		virtual void innerExport(IO::Descriptor& descriptor) const override;

	private :

		bool active;
	};

	inline Action::Action() :
		active(true)
	{}

	inline void Action::setActive(bool active)
	{
		this->active = active;
	}

	inline bool Action::isActive() const
	{
		return active;
	}

	inline void Action::innerImport(const IO::Descriptor& descriptor)
	{
		SPKObject::innerImport(descriptor);

		const IO::Attribute* attrib = NULL;
        if ((attrib = descriptor.getAttributeWithValue("active")))
			setActive(attrib->getValue<bool>());
	}

	inline void Action::innerExport(IO::Descriptor& descriptor) const
	{
		SPKObject::innerExport(descriptor);
		descriptor.getAttribute("active")->setValueOptionalOnTrue(isActive());
	}
}

#endif
