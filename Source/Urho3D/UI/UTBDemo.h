//=============================================================================
// Copyright (c) 2015 LumakSoftware
//
//=============================================================================
#pragma once

#ifdef URHO3D_TB_DEMO
#include <tb_window.h>
#include <tb_system.h>
#include <tb_select.h>
#include <tb_menu_window.h>
#include <tb_widgets.h>
#include <tb_widgets_common.h>
#include <tb_widgets_reader.h>
#include <tb_widgets_listener.h>
#include <tb_message_window.h>
#include <tb_msg.h>
#include <tb_scroller.h>
#include <tb_editfield.h>

using namespace tb;

//=============================================================================
//=============================================================================
class ResourceItem : public TBGenericStringItem
{
public:
	ResourceItem(TBWidget *widget, const char *str);
	TBWidget *GetWidget() { return m_widget; }
private:
	TBWidget *m_widget;
};

class ResourceEditWindow : public TBWindow, public TBMessageHandler, public TBWidgetListener
{
public:
	// For safe typecasting
	TBOBJECT_SUBCLASS(ResourceEditWindow, TBWindow);

	ResourceEditWindow();
	~ResourceEditWindow();

	void UpdateWidgetList(bool immediately);

	struct ITEM_INFO {
		ResourceItem *item;
		int index;
	};
	ITEM_INFO GetItemFromWidget(TBWidget *widget);
	TBWidget *GetSelectedWidget() { return m_selected_widget.Get(); }
	void SetSelectedWidget(TBWidget *widget);

	void Load(const char *resource_file);
	void RefreshFromSource();

	// == TBWindow ======================================================================
	virtual bool OnEvent(const TBWidgetEvent &ev);
	virtual void OnPaintChildren(const PaintProps &paint_props);

	// == TBMessageHandler ==============================================================
	virtual void OnMessageReceived(TBMessage *msg);

	// == TBWidgetListener ========================================================
	virtual bool OnWidgetInvokeEvent(TBWidget *widget, const TBWidgetEvent &ev);
	virtual void OnWidgetAdded(TBWidget *parent, TBWidget *child);
	virtual void OnWidgetRemove(TBWidget *parent, TBWidget *child);
private:
	TBSelectList *m_widget_list;
	TBSelectItemSourceList<ResourceItem> m_widget_list_source;
	TBScrollContainer *m_scroll_container;
	TBWidget *m_build_container;
	TBEditField *m_source_edit;
	TBStr m_resource_filename;
	TBWidgetSafePointer m_selected_widget;
	void AddWidgetListItemsRecursive(TBWidget *widget, int depth);
	bool OnDropFileEvent(const TBWidgetEvent &ev);
};

//=============================================================================
//=============================================================================
class DemoWindow : public TBWindow
{
public:
	DemoWindow(TBWidget *root);
	bool LoadResourceFile(const char *filename);
	void LoadResourceData(const char *data);
	void LoadResource(TBNode &node);

	virtual bool OnEvent(const TBWidgetEvent &ev);
};

class MainWindow : public DemoWindow, public TBMessageHandler
{
public:
	MainWindow(TBWidget *root);
	virtual bool OnEvent(const TBWidgetEvent &ev);

	// Implement TBMessageHandler
	virtual void OnMessageReceived(TBMessage *msg);
};

class ImageWindow : public DemoWindow
{
public:
	ImageWindow(TBWidget *root);
	virtual bool OnEvent(const TBWidgetEvent &ev);
};

class PageWindow : public DemoWindow, public TBScrollerSnapListener
{
public:
	PageWindow(TBWidget *root);
	virtual bool OnEvent(const TBWidgetEvent &ev);
	virtual void OnScrollSnap(TBWidget *target_widget, int &target_x, int &target_y);
};

class AnimationsWindow : public DemoWindow
{
public:
	AnimationsWindow(TBWidget *root);
	void Animate();
	virtual bool OnEvent(const TBWidgetEvent &ev);
};

class EditWindow : public DemoWindow
{
public:
	EditWindow(TBWidget *root);
	virtual void OnProcessStates();
	virtual bool OnEvent(const TBWidgetEvent &ev);
};

class LayoutWindow : public DemoWindow
{
public:
	LayoutWindow(TBWidget *root, const char *filename);
	virtual bool OnEvent(const TBWidgetEvent &ev);
};

class TabContainerWindow : public DemoWindow
{
public:
	TabContainerWindow(TBWidget *root);
	virtual bool OnEvent(const TBWidgetEvent &ev);
};

class ConnectionWindow : public DemoWindow
{
public:
	ConnectionWindow(TBWidget *root);
	virtual bool OnEvent(const TBWidgetEvent &ev);
};

class ScrollContainerWindow : public DemoWindow, public TBMessageHandler
{
public:
	ScrollContainerWindow(TBWidget *root);
	virtual bool OnEvent(const TBWidgetEvent &ev);

	// Implement TBMessageHandler
	virtual void OnMessageReceived(TBMessage *msg);
};


//=============================================================================
//=============================================================================
/** Shows a list of items from *any* type of source. */
class ListWindow : public DemoWindow
{
public:
	ListWindow(TBWidget *root, TBSelectItemSource *source);
	virtual bool OnEvent(const TBWidgetEvent &ev);
};

/** AdvancedItem adds extra info to a string item. */
class AdvancedItem : public TBGenericStringItem
{
public:
	AdvancedItem(const char *str, const TBID &id, bool male)
		: TBGenericStringItem(str, id)
		, m_checked(false)
		, m_male(male) {}
	void SetChecked(bool checked) { m_checked = checked; }
	bool GetChecked() const { return m_checked; }
	bool GetMale() const { return m_male; }
private:
	TBStr m_info;
	bool m_checked;
	bool m_male;
};

/** AdvancedItemSource provides items of type AdvancedItem and makes sure
	the viewer is populated with the customized widget for each item. */
class AdvancedItemSource : public TBSelectItemSourceList<AdvancedItem>
{
public:
	virtual bool Filter(int index, const char *filter);
	virtual TBWidget *CreateItemWidget(int index, TBSelectItemViewer *viewer);
};


/** Shows a list of items from a source of type AdvancedItemSource. */
class AdvancedListWindow : public DemoWindow
{
public:
	AdvancedListWindow(TBWidget *root, AdvancedItemSource *source);
	virtual bool OnEvent(const TBWidgetEvent &ev);
private:
	AdvancedItemSource *m_source;
};

/** AdvancedItemWidget is the widget representing a AdvancedItem.
	On changes to the item, it calls InvokeItemChanged on the source, so that all
	viewers of the source are updated to reflect the change. */
class AdvancedItemWidget : public TBLayout
{
public:
	AdvancedItemWidget(AdvancedItem *item, AdvancedItemSource *source, TBSelectItemViewer *source_viewer, int index);
	virtual bool OnEvent(const TBWidgetEvent &ev);
private:
	AdvancedItemSource *m_source;
	TBSelectItemViewer *m_source_viewer;
	int m_index;
};

//=============================================================================
//=============================================================================
namespace Urho3D
{

class URHO3D_API UTBDemo
{
public:
    static void Start();
};

} //namespace Urho3D

#endif //URHO3D_TB_DEMO

