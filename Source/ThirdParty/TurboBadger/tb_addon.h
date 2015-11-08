// ================================================================================
// ==      This file is a part of Turbo Badger. (C) 2011-2014, Emil Segerås      ==
// ==                     See tb_core.h for more information.                    ==
// ================================================================================

#ifndef TB_ADDON_H
#define TB_ADDON_H

#include "tb_linklist.h"
#include "tb_widgets.h"

namespace tb {

/** TBAddon provides a simple API with Init/Shutdown callbacks that will
	be called during tb_core_init and tb_core_shutdown.

	THIS CLASS IS DEPRECATED! */

class TBAddon : public TBLinkOf<TBAddon>
{
public:
	/** Called during tb_core_init after turbo badger core has been initiated. */
	virtual bool Init() = 0;

	/** Called during tb_core_shutdown before turbo badger core has been shut down. */
	virtual void Shutdown() = 0;

	virtual ~TBAddon() {}
};

/** TBAddonFactory is ment to be subclassed to create a TBAddon, by
	being declared as a global object. It will then register itself
	so the addon is created, initiated during tb_core_init and
	destroyed during tb_core_shutdown.

	THIS CLASS IS DEPRECATED! */
class TBAddonFactory
{
public:
	TBAddonFactory();

	virtual TBAddon *Create() = 0;

	TBAddonFactory *next;	///< Next registered addon factory.
};

/** Init addons. */
bool TBInitAddons();

/** Shutdown and delete addons. */
void TBShutdownAddons();

/** This macro creates a new TBAddonFactory for the given class name. */
#define TB_ADDON_FACTORY(classname) \
	class classname##AddonFactory : public TBAddonFactory \
	{ \
	public: \
		virtual TBAddon *Create() \
		{ \
			return new classname(); \
		} \
	}; \
	static classname##AddonFactory classname##_af;

}; // namespace tb

#endif // TB_ADDON_H
