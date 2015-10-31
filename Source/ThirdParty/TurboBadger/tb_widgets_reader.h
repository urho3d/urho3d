// ================================================================================
// ==      This file is a part of Turbo Badger. (C) 2011-2014, Emil Segerås      ==
// ==                     See tb_core.h for more information.                    ==
// ================================================================================

#ifndef TBWIDGETS_READER_H
#define TBWIDGETS_READER_H

#include "tb_linklist.h"
#include "tb_widgets.h"

namespace tb {

class TBWidgetsReader;
class TBWidgetFactory;
class TBWidget;
class TBNode;

/** INFLATE_INFO contains info passed to TBWidget::OnInflate during resource loading. */
struct INFLATE_INFO {
	INFLATE_INFO(TBWidgetsReader *reader, TBWidget *target, TBNode *node, TBValue::TYPE sync_type)
		: reader(reader), target(target), node(node), sync_type(sync_type) {}
	TBWidgetsReader *reader;

	/** The widget that that will be parent to the inflated widget. */
	TBWidget *target;
	/** The node containing properties. */
	TBNode *node;
	/** The data type that should be synchronized through TBWidgetValue. */
	TBValue::TYPE sync_type;
};

/** TBWidgetFactory creates a widget from a TBNode. */
class TBWidgetFactory : public TBLinkOf<TBWidgetFactory>
{
public:
	TBWidgetFactory(const char *name, TBValue::TYPE sync_type);

	/** Create and return the new widget or nullptr on out of memory. */
	virtual TBWidget *Create(INFLATE_INFO *info) = 0;

	void Register();
public:
	const char *name;
	TBValue::TYPE sync_type;
	TBWidgetFactory *next_registered_wf;
};

/** This macro creates a new TBWidgetFactory for the given class name so it can
	be created from resources (using TBWidgetsReader).

	classname - The name of the class.
	sync_type - The data type that should be synchronized through TBWidgetValue.
	add_child_z - The order in which children should be added to it by default.

	It should be followed by an empty block (may eventually be removed).
	Reading custom properties from resources can be done by overriding
	TBWidget::OnInflate.

	Example:

	TB_WIDGET_FACTORY(MyWidget, TBValue::TYPE_INT, WIDGET_Z_TOP) {}
	*/
#define TB_WIDGET_FACTORY(classname, sync_type, add_child_z) \
	class classname##WidgetFactory : public TBWidgetFactory \
	{ \
	public: \
		classname##WidgetFactory() \
			: TBWidgetFactory(#classname, sync_type) { Register(); } \
		virtual TBWidget *Create(INFLATE_INFO *info) \
		{ \
			classname *widget = new classname(); \
			if (widget) { \
				widget->GetContentRoot()->SetZInflate(add_child_z); \
				ReadCustomProps(widget, info); \
			} \
			return widget; \
		} \
		void ReadCustomProps(classname *widget, INFLATE_INFO *info); \
	}; \
	static classname##WidgetFactory classname##_wf; \
	void classname##WidgetFactory::ReadCustomProps(classname *widget, INFLATE_INFO *info)

/**
	TBWidgetsReader parse a resource file (or buffer) into a TBNode tree,
	and turn it into a hierarchy of widgets. It can create all types of widgets
	that have a registered factory (TBWidgetFactory). All core widgets have
	a factory by default, and you can also add your own.

	Values may be looked up from any existing TBNodeRefTree using the syntax
	"@treename>noderequest". If treename is left out, the request will be looked
	up in the same node tree. In addition to this, strings will be looked up
	from the global TBLanguage by using the syntax "@stringid"

	Branches may be included or not depending on the value of a TBNodeRefTree
	node, using "@if @treename>noderequest" and optionally a following "@else".

	Branches may be included from TBNodeRefTree using
	"@include @treename>noderequest", or included from nodes specified previosly
	in the same tree using "@include noderequest".

	Files can be included by using the syntax "@file filename".

	Each factory may have its own set of properties, but a set of generic
	properties is always supported on all widgets. Those are:

	Resource name:		TBWidget property:			Values:

	id					TBWidget::m_id				TBID (string or int)
	group-id			TBWidget::m_group_id		TBID (string or int)
	value				TBWidget::SetValue			integer
	data				TBWidget::m_data			integer
	is-group-root		TBWidget::SetIsGroupRoot	boolean
	is-focusable		TBWidget::SetIsFocusable	boolean
	want-long-click		TBWidget::SetWantLongClick	boolean
	ignore-input		TBWidget::SetIgnoreInput	boolean
	opacity				TBWidget::SetOpacity		float (0 - 1)
	text				TBWidget::SetText			string
	connection			TBWidget::Connect			string
	axis				TBWidget::SetAxis			x or y
	gravity				TBWidget::SetGravity		string (combination of left, top, right, bottom, or all)
	visibility			TBWidget::SetVisibility		string (visible, invisible, gone)
	state				TBWidget::SetState			string (disabled)
	skin				TBWidget::SetSkinBg			TBID (string or int)
	rect				TBWidget::SetRect			4 integers (x, y, width, height)
	lp>width			TBWidget::SetLayoutParams	dimension
	lp>min-width		TBWidget::SetLayoutParams	dimension
	lp>max-width		TBWidget::SetLayoutParams	dimension
	lp>pref-width		TBWidget::SetLayoutParams	dimension
	lp>height			TBWidget::SetLayoutParams	dimension
	lp>min-height		TBWidget::SetLayoutParams	dimension
	lp>max-height		TBWidget::SetLayoutParams	dimension
	lp>pref-height		TBWidget::SetLayoutParams	dimension
	autofocus			The TBWidget will be focused automatically the first time its TBWindow is activated.
	font>name			Font name
	font>size			Font size
*/
class TBWidgetsReader
{
public:
	static TBWidgetsReader *Create();
	~TBWidgetsReader();

	/** Add a widget factory. Does not take ownership of the factory.
		The easiest way to add factories for custom widget types, is using the
		TB_WIDGET_FACTORY macro that automatically register it during startup. */
	bool AddFactory(TBWidgetFactory *wf) { factories.AddLast(wf); return true; }
	void RemoveFactory(TBWidgetFactory *wf) { factories.Remove(wf); }

	/** Set the id from the given node. */
	static void SetIDFromNode(TBID &id, TBNode *node);

	bool LoadFile(TBWidget *target, const char *filename);
	bool LoadData(TBWidget *target, const char *data);
	bool LoadData(TBWidget *target, const char *data, int data_len);
	void LoadNodeTree(TBWidget *target, TBNode *node);
private:
	bool Init();
	bool CreateWidget(TBWidget *target, TBNode *node);
	TBLinkListOf<TBWidgetFactory> factories;
};

}; // namespace tb

#endif // TBWIDGETS_READER_H
