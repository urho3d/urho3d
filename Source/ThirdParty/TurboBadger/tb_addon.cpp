// ================================================================================
// ==      This file is a part of Turbo Badger. (C) 2011-2014, Emil Segerås      ==
// ==                     See tb_core.h for more information.                    ==
// ================================================================================

#include "tb_system.h"
#include "tb_addon.h"

namespace tb {

// We can't use a linked list object since we don't know if its constructor
// would run before of after any widget factory constructor that add itself
// to it. Using a manual one way link list is very simple.
TBAddonFactory *g_registered_addon_factories = nullptr;

TBAddonFactory::TBAddonFactory()
	: next(g_registered_addon_factories)
{
	g_registered_addon_factories = this;
}

// ======================================================================================

TBLinkListOf<TBAddon> m_addons;

bool TBInitAddons()
{
	TBAddonFactory *f = g_registered_addon_factories;
	while (f)
	{
		TBAddon *addon = f->Create();
		if (!addon || !addon->Init())
		{
			delete addon;
			TBDebugOut("Failed initiating addon\n");
			return false;
		}
		m_addons.AddLast(addon);
		f = f->next;
	}
	return true;
}

void TBShutdownAddons()
{
	while (TBAddon *addon = m_addons.GetLast())
	{
		addon->Shutdown();
		m_addons.Delete(addon);
	}
}

}; // namespace tb
