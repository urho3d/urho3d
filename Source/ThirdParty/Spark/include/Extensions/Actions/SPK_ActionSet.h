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

#ifndef H_SPK_ACTIONSET
#define H_SPK_ACTIONSET

#include <vector>

namespace SPK
{
	class SPK_PREFIX ActionSet : public Action
	{
	SPK_IMPLEMENT_OBJECT(ActionSet)

	SPK_START_DESCRIPTION
	SPK_PARENT_ATTRIBUTES(Action)
	SPK_ATTRIBUTE("actions",ATTRIBUTE_TYPE_REFS)
	SPK_END_DESCRIPTION

	public :

		static  Ref<ActionSet> create();
		
		virtual ~ActionSet();

		void addAction(const Ref<Action>& action);
		void removeAction(const Ref<Action>& action);
		const Ref<Action>& getAction(size_t index) const;
		size_t getNbActions() const;
        void clearActions();

        virtual void apply(Particle& particle) const override;

		virtual Ref<SPKObject> findByName(const std::string& name) override;

	protected :

		virtual void innerImport(const IO::Descriptor& descriptor) override;
		virtual void innerExport(IO::Descriptor& descriptor) const override;

	private :

		ActionSet() {}
		ActionSet(const ActionSet& actionSet);

		std::vector<Ref<Action> > actions;
	};

	inline Ref<ActionSet> ActionSet::create()
	{
		return SPK_NEW(ActionSet);
	}

	inline size_t ActionSet::getNbActions() const
	{
		return actions.size();
	}
}

#endif
