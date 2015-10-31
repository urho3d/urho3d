//=============================================================================
// Copyright (c) 2015 LumakSoftware
//
//=============================================================================
#ifdef URHO3D_TB_DEMO

#include "../Urho3D.h"

#include <stdio.h>
#include <stdarg.h>

#include <tb_inline_select.h>
#include <tb_tab_container.h>
#include <animation/tb_widget_animation.h>
#include <tb_node_tree.h>
#include <tb_tempbuffer.h>
#include <tb_font_renderer.h>
#include <image/tb_image_manager.h>
#include <utf8/utf8.h>
#include <tests/tb_test.h>

#include "UTBDemo.h"
#include "UTBRendererBatcher.h"

#include "../DebugNew.h"

//=============================================================================
//=============================================================================
AdvancedItemSource advanced_source;
TBGenericStringItemSource name_source;
TBGenericStringItemSource popup_menu_source;


// == ResourceItem ====================================================================================

ResourceItem::ResourceItem(TBWidget *widget, const char *str)
	: TBGenericStringItem(str)
	, m_widget(widget)
{
}

// == ResourceEditWindow ==============================================================================

ResourceEditWindow::ResourceEditWindow()
	: m_widget_list(nullptr)
	, m_scroll_container(nullptr)
	, m_build_container(nullptr)
	, m_source_edit(nullptr)
{
	// Register as global listener to intercept events in the build container
	TBWidgetListener::AddGlobalListener(this);

	g_widgets_reader->LoadFile(this, "demo01/ui_resources/resource_edit_window.tb.txt");

	m_scroll_container = GetWidgetByIDAndType<TBScrollContainer>(TBIDC("scroll_container"));
	m_build_container = m_scroll_container->GetContentRoot();
	m_source_edit = GetWidgetByIDAndType<TBEditField>(TBIDC("source_edit"));

	m_widget_list = GetWidgetByIDAndType<TBSelectList>(TBIDC("widget_list"));
	m_widget_list->SetSource(&m_widget_list_source);

	SetRect(TBRect(100, 50, 900, 600));
}

ResourceEditWindow::~ResourceEditWindow()
{
	TBWidgetListener::RemoveGlobalListener(this);

	// avoid assert
	m_widget_list->SetSource(nullptr);
}

void ResourceEditWindow::Load(const char *resource_file)
{
	m_resource_filename.Set(resource_file);
	SetText(resource_file);

	// Set the text of the source view
	m_source_edit->SetText("");

	if (TBFile *file = TBFile::Open(m_resource_filename, TBFile::MODE_READ))
	{
		TBTempBuffer buffer;
		if (buffer.Reserve(file->Size()))
		{
			uint32 size_read = file->Read(buffer.GetData(), 1, buffer.GetCapacity());
			m_source_edit->SetText(buffer.GetData(), size_read);
		}
		delete file;
	}
	else // Error, show message
	{
		TBStr text;
		text.SetFormatted("Could not load file %s", resource_file);
		if (TBMessageWindow *msg_win = new TBMessageWindow(GetParentRoot(), TBIDC("")))
			msg_win->Show("Error loading resource", text);
	}

	RefreshFromSource();
}

void ResourceEditWindow::RefreshFromSource()
{
	// Clear old widgets
	while (TBWidget *child = m_build_container->GetFirstChild())
	{
		m_build_container->RemoveChild(child);
		delete child;
	}

	// Create new widgets from source
	g_widgets_reader->LoadData(m_build_container, m_source_edit->GetText());

	// Force focus back in case the edited resource has autofocus.
	// FIX: It would be better to prevent the focus change instead!
	m_source_edit->SetFocus(WIDGET_FOCUS_REASON_UNKNOWN);
}

void ResourceEditWindow::UpdateWidgetList(bool immediately)
{
	if (!immediately)
	{
		TBID id = TBIDC("update_widget_list");
		if (!GetMessageByID(id))
			PostMessage(id, nullptr);
	}
	else
	{
		m_widget_list_source.DeleteAllItems();
		AddWidgetListItemsRecursive(m_build_container, 0);

		m_widget_list->InvalidateList();
	}
}

void ResourceEditWindow::AddWidgetListItemsRecursive(TBWidget *widget, int depth)
{
	if (depth > 0) // Ignore the root
	{
		// Add a new ResourceItem for this widget
		TBStr str;
		const char *classname = widget->GetClassName();
		if (!*classname)
			classname = "<Unknown widget type>";
		str.SetFormatted("% *s%s", depth - 1, "", classname);

		if (ResourceItem *item = new ResourceItem(widget, str))
			m_widget_list_source.AddItem(item);
	}

	for (TBWidget *child = widget->GetFirstChild(); child; child = child->GetNext())
		AddWidgetListItemsRecursive(child, depth + 1);
}

ResourceEditWindow::ITEM_INFO ResourceEditWindow::GetItemFromWidget(TBWidget *widget)
{
	ITEM_INFO item_info = { nullptr, -1 };
	for (int i = 0; i < m_widget_list_source.GetNumItems(); i++)
		if (m_widget_list_source.GetItem(i)->GetWidget() == widget)
		{
			item_info.index = i;
			item_info.item = m_widget_list_source.GetItem(i);
			break;
		}
	return item_info;
}

void ResourceEditWindow::SetSelectedWidget(TBWidget *widget)
{
	m_selected_widget.Set(widget);
	ITEM_INFO item_info = GetItemFromWidget(widget);
	if (item_info.item)
		m_widget_list->SetValue(item_info.index);
}

bool ResourceEditWindow::OnEvent(const TBWidgetEvent &ev)
{
	if (ev.type == EVENT_TYPE_CHANGED && ev.target->GetID() == TBIDC("widget_list_search"))
	{
		m_widget_list->SetFilter(ev.target->GetText());
		return true;
	}
	else if (ev.type == EVENT_TYPE_CHANGED && ev.target == m_widget_list)
	{
		if (m_widget_list->GetValue() >= 0 && m_widget_list->GetValue() < m_widget_list_source.GetNumItems())
			if (ResourceItem *item = m_widget_list_source.GetItem(m_widget_list->GetValue()))
				SetSelectedWidget(item->GetWidget());
	}
	else if (ev.type == EVENT_TYPE_CHANGED && ev.target == m_source_edit)
	{
		RefreshFromSource();
		return true;
	}
	else if (ev.type == EVENT_TYPE_CLICK && ev.target->GetID() == TBIDC("test"))
	{
		// Create a window containing the current layout, resize and center it.
		if (TBWindow *win = new TBWindow())
		{
			win->SetText("Test window");
			g_widgets_reader->LoadData(win->GetContentRoot(), m_source_edit->GetText());
			TBRect bounds(0, 0, GetParent()->GetRect().w, GetParent()->GetRect().h);
			win->SetRect(win->GetResizeToFitContentRect().CenterIn(bounds).MoveIn(bounds).Clip(bounds));
			GetParent()->AddChild(win);
		}
		return true;
	}
	else if (ev.target->GetID() == TBIDC("constrained"))
	{
		m_scroll_container->SetAdaptContentSize(ev.target->GetValue() ? true : false);
		return true;
	}
	else if (ev.type == EVENT_TYPE_FILE_DROP)
	{
		return OnDropFileEvent(ev);
	}
	return TBWindow::OnEvent(ev);
}

void ResourceEditWindow::OnPaintChildren(const PaintProps &paint_props)
{
	TBWindow::OnPaintChildren(paint_props);

	// Paint the selection of the selected widget
	if (TBWidget *selected_widget = GetSelectedWidget())
	{
		TBRect widget_rect(0, 0, selected_widget->GetRect().w, selected_widget->GetRect().h);
		selected_widget->ConvertToRoot(widget_rect.x, widget_rect.y);
		ConvertFromRoot(widget_rect.x, widget_rect.y);
		g_renderer->DrawRect(widget_rect, TBColor(255, 205, 0));
	}
}

void ResourceEditWindow::OnMessageReceived(TBMessage *msg)
{
	if (msg->message == TBIDC("update_widget_list"))
		UpdateWidgetList(true);
}

bool ResourceEditWindow::OnWidgetInvokeEvent(TBWidget *widget, const TBWidgetEvent &ev)
{
	// Intercept all events to widgets in the build container
	if (m_build_container->IsAncestorOf(ev.target))
	{
		// Let events through if alt is pressed so we can test some
		// functionality right in the editor (like toggle hidden UI).
		if (ev.modifierkeys & TB_ALT)
			return false;

		// Select widget when clicking
		if (ev.type == EVENT_TYPE_POINTER_DOWN)
			SetSelectedWidget(ev.target);

		if (ev.type == EVENT_TYPE_FILE_DROP)
			OnDropFileEvent(ev);
		return true;
	}
	return false;
}

void ResourceEditWindow::OnWidgetAdded(TBWidget *parent, TBWidget *child)
{
	if (m_build_container && m_build_container->IsAncestorOf(child))
		UpdateWidgetList(false);
}

void ResourceEditWindow::OnWidgetRemove(TBWidget *parent, TBWidget *child)
{
	if (m_build_container && m_build_container->IsAncestorOf(child))
		UpdateWidgetList(false);
}

bool ResourceEditWindow::OnDropFileEvent(const TBWidgetEvent &ev)
{
	const TBWidgetEventFileDrop *fd_event = TBSafeCast<TBWidgetEventFileDrop>(&ev);
	if (fd_event->files.GetNumItems() > 0)
		Load(*fd_event->files.Get(0));
	return true;
}

// == AdvancedItemWidget ======================================================

AdvancedItemWidget::AdvancedItemWidget(AdvancedItem *item, AdvancedItemSource *source,
										TBSelectItemViewer *source_viewer, int index)
	: m_source(source)
	, m_source_viewer(source_viewer)
	, m_index(index)
{
	SetSkinBg(TBIDC("TBSelectItem"));
	SetLayoutDistribution(LAYOUT_DISTRIBUTION_GRAVITY);
	SetLayoutDistributionPosition(LAYOUT_DISTRIBUTION_POSITION_LEFT_TOP);
	SetPaintOverflowFadeout(false);

	g_widgets_reader->LoadFile(GetContentRoot(), "demo01/ui_resources/test_list_item.tb.txt");
	TBCheckBox *checkbox = GetWidgetByIDAndType<TBCheckBox>(TBIDC("check"));
	TBTextField *name = GetWidgetByIDAndType<TBTextField>(TBIDC("name"));
	TBTextField *info = GetWidgetByIDAndType<TBTextField>(TBIDC("info"));
	checkbox->SetValue(item->GetChecked() ? true : false);
	name->SetText(item->str);
	info->SetText(item->GetMale() ? "Male" : "Female");
}

bool AdvancedItemWidget::OnEvent(const TBWidgetEvent &ev)
{
	if (ev.type == EVENT_TYPE_CLICK && ev.target->GetID() == TBIDC("check"))
	{
		AdvancedItem *item = m_source->GetItem(m_index);
		item->SetChecked(ev.target->GetValue() ? true : false);

		m_source->InvokeItemChanged(m_index, m_source_viewer);
		return true;
	}
	else if (ev.type == EVENT_TYPE_CLICK && ev.target->GetID() == TBIDC("delete"))
	{
		m_source->DeleteItem(m_index);
		return true;
	}
	return TBLayout::OnEvent(ev);
}

// == AdvancedItemSource ======================================================

bool AdvancedItemSource::Filter(int index, const char *filter)
{
	// Override this method so we can return hits for our extra data too.

	if (TBSelectItemSource::Filter(index, filter))
		return true;

	AdvancedItem *item = GetItem(index);
	return stristr(item->GetMale() ? "Male" : "Female", filter) ? true : false;
}

TBWidget *AdvancedItemSource::CreateItemWidget(int index, TBSelectItemViewer *viewer)
{
	if (TBLayout *layout = new AdvancedItemWidget(GetItem(index), this, viewer, index))
		return layout;
	return nullptr;
}

// == ListWindow ==============================================================

ListWindow::ListWindow(TBWidget *root, TBSelectItemSource *source) : DemoWindow(root)
{
	LoadResourceFile("demo01/ui_resources/test_select.tb.txt");
	if (TBSelectList *select = GetWidgetByIDAndType<TBSelectList>("list"))
	{
		select->SetSource(source);
		select->GetScrollContainer()->SetScrollMode(SCROLL_MODE_Y_AUTO);
	}
}

bool ListWindow::OnEvent(const TBWidgetEvent &ev)
{
	if (ev.type == EVENT_TYPE_CHANGED && ev.target->GetID() == TBIDC("filter"))
	{
		if (TBSelectList *select = GetWidgetByIDAndType<TBSelectList>("list"))
			select->SetFilter(ev.target->GetText());
		return true;
	}
	return DemoWindow::OnEvent(ev);
}

// == AdvancedListWindow ==============================================================

AdvancedListWindow::AdvancedListWindow(TBWidget *root, AdvancedItemSource *source)
	: DemoWindow(root)
	, m_source(source)
{
	LoadResourceFile("demo01/ui_resources/test_select_advanced.tb.txt");
	if (TBSelectList *select = GetWidgetByIDAndType<TBSelectList>("list"))
	{
		select->SetSource(source);
		select->GetScrollContainer()->SetScrollMode(SCROLL_MODE_X_AUTO_Y_AUTO);
	}
}

bool AdvancedListWindow::OnEvent(const TBWidgetEvent &ev)
{
	TBSelectList *select = GetWidgetByIDAndType<TBSelectList>("list");
	if (select && ev.type == EVENT_TYPE_CHANGED && ev.target->GetID() == TBIDC("filter"))
	{
		select->SetFilter(ev.target->GetText());
		return true;
	}
	else if (select && ev.type == EVENT_TYPE_CLICK && ev.target->GetID() == TBIDC("add"))
	{
		TBStr name = GetTextByID(TBIDC("add_name"));
		if (!name.IsEmpty())
			m_source->AddItem(new AdvancedItem(name, TBIDC("boy_item"), true));
		return true;
	}
	else if (select && ev.type == EVENT_TYPE_CLICK && ev.target->GetID() == TBIDC("delete all"))
	{
		m_source->DeleteAllItems();
		return true;
	}
	return DemoWindow::OnEvent(ev);
}

// == DemoWindow ==============================================================
DemoWindow::DemoWindow(TBWidget *root)
{
	root->AddChild(this);
}

bool DemoWindow::LoadResourceFile(const char *filename)
{
	// We could do g_widgets_reader->LoadFile(this, filename) but we want
	// some extra data we store under "WindowInfo", so read into node tree.
	TBNode node;
	if (!node.ReadFile(filename))
		return false;
	LoadResource(node);
	return true;
}

void DemoWindow::LoadResourceData(const char *data)
{
	// We could do g_widgets_reader->LoadData(this, filename) but we want
	// some extra data we store under "WindowInfo", so read into node tree.
	TBNode node;
	node.ReadData(data);
	LoadResource(node);
}

void DemoWindow::LoadResource(TBNode &node)
{
	g_widgets_reader->LoadNodeTree(this, &node);

	// Get title from the WindowInfo section (or use "" if not specified)
	SetText(node.GetValueString("WindowInfo>title", ""));

	const TBRect parent_rect(0, 0, GetParent()->GetRect().w, GetParent()->GetRect().h);
	const TBDimensionConverter *dc = g_tb_skin->GetDimensionConverter();
	TBRect window_rect = GetResizeToFitContentRect();

	// Use specified size or adapt to the preferred content size.
	TBNode *tmp = node.GetNode("WindowInfo>size");
	if (tmp && tmp->GetValue().GetArrayLength() == 2)
	{
		window_rect.w = dc->GetPxFromString(tmp->GetValue().GetArray()->GetValue(0)->GetString(), window_rect.w);
		window_rect.h = dc->GetPxFromString(tmp->GetValue().GetArray()->GetValue(1)->GetString(), window_rect.h);
	}

	// Use the specified position or center in parent.
	tmp = node.GetNode("WindowInfo>position");
	if (tmp && tmp->GetValue().GetArrayLength() == 2)
	{
		window_rect.x = dc->GetPxFromString(tmp->GetValue().GetArray()->GetValue(0)->GetString(), window_rect.x);
		window_rect.y = dc->GetPxFromString(tmp->GetValue().GetArray()->GetValue(1)->GetString(), window_rect.y);
	}
	else
		window_rect = window_rect.CenterIn(parent_rect);

	// Make sure the window is inside the parent, and not larger.
	window_rect = window_rect.MoveIn(parent_rect).Clip(parent_rect);

	SetRect(window_rect);

	// Ensure we have focus - now that we've filled the window with possible focusable
	// widgets. EnsureFocus was automatically called when the window was activated (by
	// adding the window to the root), but then we had nothing to focus.
	// Alternatively, we could add the window after setting it up properly.
	EnsureFocus();
}

bool DemoWindow::OnEvent(const TBWidgetEvent &ev)
{
	if (ev.type == EVENT_TYPE_KEY_DOWN && ev.special_key == TB_KEY_ESC)
	{
		// We could call Die() to fade away and die, but click the close button instead.
		// That way the window has a chance of intercepting the close and f.ex ask if it really should be closed.
		TBWidgetEvent click_ev(EVENT_TYPE_CLICK);
		m_close_button.InvokeEvent(click_ev);
		return true;
	}
	return TBWindow::OnEvent(ev);
}

// == EditWindow ==============================================================
EditWindow::EditWindow(TBWidget *root) : DemoWindow(root)
{
    LoadResourceFile("demo01/ui_resources/test_textwindow.tb.txt");
}
void EditWindow::OnProcessStates()
{
    // Update the disabled state of undo/redo buttons, and caret info.

    if (TBEditField *edit = GetWidgetByIDAndType<TBEditField>(TBIDC("editfield")))
    {
        if (TBWidget *undo = GetWidgetByID("undo"))
            undo->SetState(WIDGET_STATE_DISABLED, !edit->GetStyleEdit()->CanUndo());
        if (TBWidget *redo = GetWidgetByID("redo"))
            redo->SetState(WIDGET_STATE_DISABLED, !edit->GetStyleEdit()->CanRedo());
        if (TBTextField *info = GetWidgetByIDAndType<TBTextField>(TBIDC("info")))
        {
            TBStr text;
            text.SetFormatted("Caret ofs: %d", edit->GetStyleEdit()->caret.GetGlobalOfs());
            info->SetText(text);
        }
    }
}
bool EditWindow::OnEvent(const TBWidgetEvent &ev)
{
    if (ev.type == EVENT_TYPE_CLICK)
    {
        TBEditField *edit = GetWidgetByIDAndType<TBEditField>(TBIDC("editfield"));
        if (!edit)
            return false;

        if (ev.target->GetID() == TBIDC("clear"))
        {
            edit->SetText("");
            return true;
        }
        else if (ev.target->GetID() == TBIDC("undo"))
        {
            edit->GetStyleEdit()->Undo();
            return true;
        }
        else if (ev.target->GetID() == TBIDC("redo"))
        {
            edit->GetStyleEdit()->Redo();
            return true;
        }
        else if (ev.target->GetID() == TBIDC("menu"))
        {
            static TBGenericStringItemSource source;
            if (!source.GetNumItems())
            {
                source.AddItem(new TBGenericStringItem("Default font", TBIDC("default font")));
                source.AddItem(new TBGenericStringItem("Default font (larger)", TBIDC("large font")));
                source.AddItem(new TBGenericStringItem("RGB font (Neon)", TBIDC("rgb font Neon")));
                source.AddItem(new TBGenericStringItem("RGB font (Orangutang)", TBIDC("rgb font Orangutang")));
                source.AddItem(new TBGenericStringItem("RGB font (Orange)", TBIDC("rgb font Orange")));
                source.AddItem(new TBGenericStringItem("-"));
                source.AddItem(new TBGenericStringItem("Glyph cache stresstest (CJK)", TBIDC("CJK")));
                source.AddItem(new TBGenericStringItem("-"));
                source.AddItem(new TBGenericStringItem("Toggle wrapping", TBIDC("toggle wrapping")));
                source.AddItem(new TBGenericStringItem("-"));
                source.AddItem(new TBGenericStringItem("Align left", TBIDC("align left")));
                source.AddItem(new TBGenericStringItem("Align center", TBIDC("align center")));
                source.AddItem(new TBGenericStringItem("Align right", TBIDC("align right")));
            }

            if (TBMenuWindow *menu = new TBMenuWindow(ev.target, TBIDC("popup_menu")))
                menu->Show(&source, TBPopupAlignment());
            return true;
        }
        else if (ev.target->GetID() == TBIDC("popup_menu"))
        {
            if (ev.ref_id == TBIDC("default font"))
                edit->SetFontDescription(TBFontDescription());
            else if (ev.ref_id == TBIDC("large font"))
            {
                TBFontDescription fd = g_font_manager->GetDefaultFontDescription();
                fd.SetSize(28);
                edit->SetFontDescription(fd);
            }
            else if (ev.ref_id == TBIDC("rgb font Neon"))
            {
                TBFontDescription fd = edit->GetCalculatedFontDescription();
                fd.SetID(TBIDC("Neon"));
                edit->SetFontDescription(fd);
            }
            else if (ev.ref_id == TBIDC("rgb font Orangutang"))
            {
                TBFontDescription fd = edit->GetCalculatedFontDescription();
                fd.SetID(TBIDC("Orangutang"));
                edit->SetFontDescription(fd);
            }
            else if (ev.ref_id == TBIDC("rgb font Orange"))
            {
                TBFontDescription fd = edit->GetCalculatedFontDescription();
                fd.SetID(TBIDC("Orange"));
                edit->SetFontDescription(fd);
            }
            else if (ev.ref_id == TBIDC("CJK"))
            {
                TBTempBuffer buf;
                for (int i = 0, cp = 0x4E00; cp <= 0x9FCC; cp++, i++)
                {
                    char utf8[8];
                    int len = utf8::encode(cp, utf8);
                    buf.Append(utf8, len);
                    if (i % 64 == 63)
                        buf.Append("\n", 1);
                }
                edit->GetStyleEdit()->SetText(buf.GetData(), buf.GetAppendPos());
            }
            else if (ev.ref_id == TBIDC("toggle wrapping"))
                edit->SetWrapping(!edit->GetWrapping());
            else if (ev.ref_id == TBIDC("align left"))
                edit->SetTextAlign(TB_TEXT_ALIGN_LEFT);
            else if (ev.ref_id == TBIDC("align center"))
                edit->SetTextAlign(TB_TEXT_ALIGN_CENTER);
            else if (ev.ref_id == TBIDC("align right"))
                edit->SetTextAlign(TB_TEXT_ALIGN_RIGHT);
            return true;
        }
    }
    return DemoWindow::OnEvent(ev);
}

// == LayoutWindow ============================================================

LayoutWindow::LayoutWindow(TBWidget *root, const char *filename) : DemoWindow(root)
{
	LoadResourceFile(filename);
}

bool LayoutWindow::OnEvent(const TBWidgetEvent &ev)
{
	if (ev.type == EVENT_TYPE_CHANGED && ev.target->GetID() == TBIDC("select position"))
	{
		LAYOUT_POSITION pos = LAYOUT_POSITION_CENTER;
		if (TBSelectDropdown *select = GetWidgetByIDAndType<TBSelectDropdown>(TBIDC("select position")))
			pos = static_cast<LAYOUT_POSITION>(select->GetValue());
		for (int i = 0; i < 3; i++)
			if (TBLayout *layout = GetWidgetByIDAndType<TBLayout>(i + 1))
				layout->SetLayoutPosition(pos);
		return true;
	}
	else if (ev.type == EVENT_TYPE_CLICK && ev.target->GetID() == TBIDC("toggle axis"))
	{
		static AXIS axis = AXIS_Y;
		for (int i = 0; i < 3; i++)
			if (TBLayout *layout = GetWidgetByIDAndType<TBLayout>(i + 1))
				layout->SetAxis(axis);
		axis = axis == AXIS_X ? AXIS_Y : AXIS_X;
		if (TBLayout *layout = GetWidgetByIDAndType<TBLayout>(TBIDC("switch_layout")))
			layout->SetAxis(axis);
		ResizeToFitContent(RESIZE_FIT_CURRENT_OR_NEEDED);
		return true;
	}
	return DemoWindow::OnEvent(ev);
}

// == TabContainerWindow ============================================================

TabContainerWindow::TabContainerWindow(TBWidget *root) : DemoWindow(root)
{
	LoadResourceFile("demo01/ui_resources/test_tabcontainer01.tb.txt");
}

bool TabContainerWindow::OnEvent(const TBWidgetEvent &ev)
{
	if (ev.type == EVENT_TYPE_CLICK && ev.target->GetID() == TBIDC("set_align"))
	{
		if (TBTabContainer *tc = GetWidgetByIDAndType<TBTabContainer>(TBIDC("tabcontainer")))
			tc->SetAlignment(static_cast<TB_ALIGN>(ev.target->data.GetInt()));
		ResizeToFitContent(RESIZE_FIT_CURRENT_OR_NEEDED);
	}
	else if (ev.type == EVENT_TYPE_CLICK && ev.target->GetID() == TBIDC("toggle_tab_axis"))
	{
		static AXIS axis = AXIS_X;
		axis = axis == AXIS_X ? AXIS_Y : AXIS_X;
		if (TBTabContainer *tc = GetWidgetByIDAndType<TBTabContainer>(TBIDC("tabcontainer")))
		{
			for (TBWidget *child = tc->GetTabLayout()->GetFirstChild(); child; child = child->GetNext())
			{
				if (TBButton *button = TBSafeCast<TBButton>(child))
					button->SetAxis(axis);
			}
		}
		ResizeToFitContent(RESIZE_FIT_CURRENT_OR_NEEDED);
	}
	else if (ev.type == EVENT_TYPE_CLICK && ev.target->GetID() == TBIDC("start_spinner"))
	{
		if (TBProgressSpinner *spinner = GetWidgetByIDAndType<TBProgressSpinner>(TBIDC("spinner")))
			spinner->SetValue(1);
	}
	else if (ev.type == EVENT_TYPE_CLICK && ev.target->GetID() == TBIDC("stop_spinner"))
	{
		if (TBProgressSpinner *spinner = GetWidgetByIDAndType<TBProgressSpinner>(TBIDC("spinner")))
			spinner->SetValue(0);
	}
	return DemoWindow::OnEvent(ev);
}

// == ConnectionWindow =========================================================

ConnectionWindow::ConnectionWindow(TBWidget *root) : DemoWindow(root)
{
	LoadResourceFile("demo01/ui_resources/test_connections.tb.txt");
}

bool ConnectionWindow::OnEvent(const TBWidgetEvent &ev)
{
	if (ev.type == EVENT_TYPE_CLICK && ev.target->GetID() == TBIDC("reset-master-volume"))
	{
		if (TBWidgetValue *val = g_value_group.GetValue(TBIDC("master-volume")))
			val->SetInt(50);
	}
	else if (ev.type == EVENT_TYPE_CLICK && ev.target->GetID() == TBIDC("reset-user-name"))
	{
		if (TBWidgetValue *val = g_value_group.GetValue(TBIDC("user-name")))
			val->SetText("");
	}
	return DemoWindow::OnEvent(ev);
}

// == ScrollContainerWindow ===================================================

ScrollContainerWindow::ScrollContainerWindow(TBWidget *root) : DemoWindow(root)
{
	LoadResourceFile("demo01/ui_resources/test_scrollcontainer.tb.txt");

	if (TBSelectDropdown *select = GetWidgetByIDAndType<TBSelectDropdown>(TBIDC("name dropdown")))
		select->SetSource(&name_source);

	if (TBSelectDropdown *select = GetWidgetByIDAndType<TBSelectDropdown>(TBIDC("advanced dropdown")))
		select->SetSource(&advanced_source);
}

bool ScrollContainerWindow::OnEvent(const TBWidgetEvent &ev)
{
	if (ev.type == EVENT_TYPE_CLICK)
	{
		if (ev.target->GetID() == TBIDC("add img"))
		{
			TBButton *button = TBSafeCast<TBButton>(ev.target);
			TBSkinImage *skin_image = new TBSkinImage;
			skin_image->SetSkinBg(TBIDC("Icon16"));
			button->GetContentRoot()->AddChild(skin_image, WIDGET_Z_BOTTOM);
			return true;
		}
		else if (ev.target->GetID() == TBIDC("new buttons"))
		{
			for(int i = 0; i < ev.target->data.GetInt(); i++)
			{
				TBStr str;
				str.SetFormatted("Remove %d", i);
				TBButton *button = new TBButton;
				button->SetID(TBIDC("remove button"));
				button->SetText(str);
				ev.target->GetParent()->AddChild(button);
			}
			return true;
		}
		else if (ev.target->GetID() == TBIDC("new buttons delayed"))
		{
			for(int i = 0; i < ev.target->data.GetInt(); i++)
			{
				TBMessageData *data = new TBMessageData();
				data->id1 = ev.target->GetParent()->GetID();
				data->v1.SetInt(i);
				PostMessageDelayed(TBIDC("new button"), data, 100 + i * 500);
			}
			return true;
		}
		else if (ev.target->GetID() == TBIDC("remove button"))
		{
			ev.target->GetParent()->RemoveChild(ev.target);
			delete ev.target;
			return true;
		}
		else if (ev.target->GetID() == TBIDC("showpopupmenu1"))
		{
			if (TBMenuWindow *menu = new TBMenuWindow(ev.target, TBIDC("popupmenu1")))
				menu->Show(&popup_menu_source, TBPopupAlignment());
			return true;
		}
		else if (ev.target->GetID() == TBIDC("popupmenu1"))
		{
			TBStr str;
			str.SetFormatted("Menu event received!\nref_id: %d", (int)ev.ref_id);
			TBMessageWindow *msg_win = new TBMessageWindow(this, TBIDC("popup_dialog"));
			msg_win->Show("Info", str);
			return true;
		}
	}
	return DemoWindow::OnEvent(ev);
}

void ScrollContainerWindow::OnMessageReceived(TBMessage *msg)
{
	if (msg->message == TBIDC("new button") && msg->data)
	{
		if (TBWidget *target = GetWidgetByID(msg->data->id1))
		{
			TBStr str;
			str.SetFormatted("Remove %d", msg->data->v1.GetInt());
			TBButton *button = new TBButton;
			button->SetID(TBIDC("remove button"));
			button->SetText(str);
			target->AddChild(button);
		}
	}
}

// == ImageWindow =============================================================

ImageWindow::ImageWindow(TBWidget *root) : DemoWindow(root)
{
	LoadResourceFile("demo01/ui_resources/test_image_widget.tb.txt");
}

bool ImageWindow::OnEvent(const TBWidgetEvent &ev)
{
	if (ev.type == EVENT_TYPE_CLICK && ev.target->GetID() == TBIDC("remove"))
	{
		TBWidget *image = ev.target->GetParent();
		image->GetParent()->RemoveChild(image);
		delete image;
		return true;
	}
	return DemoWindow::OnEvent(ev);
}

// == PageWindow =============================================================

PageWindow::PageWindow(TBWidget *root) : DemoWindow(root)
{
	LoadResourceFile("demo01/ui_resources/test_scroller_snap.tb.txt");

	// Listen to the pagers scroller
	if (TBWidget *pager = GetWidgetByID(TBIDC("page-scroller")))
		pager->GetScroller()->SetSnapListener(this);
}

bool PageWindow::OnEvent(const TBWidgetEvent &ev)
{
	return DemoWindow::OnEvent(ev);
}

void PageWindow::OnScrollSnap(TBWidget *target_widget, int &target_x, int &target_y)
{
	int page_w = target_widget->GetPaddingRect().w;
	int target_page = (target_x + page_w / 2) / page_w;
	target_x = target_page * page_w;
}

// == AnimationsWindow ========================================================

AnimationsWindow::AnimationsWindow(TBWidget *root) : DemoWindow(root)
{
	LoadResourceFile("demo01/ui_resources/test_animations.tb.txt");
	Animate();
}

void AnimationsWindow::Animate()
{
	// Abort any still unfinished animations.
	TBWidgetsAnimationManager::AbortAnimations(this);

	ANIMATION_CURVE curve = ANIMATION_CURVE_SLOW_DOWN;
	double duration = 500;
	bool fade = true;

	if (TBSelectList *curve_select = GetWidgetByIDAndType<TBSelectList>("curve"))
		curve = static_cast<ANIMATION_CURVE>(curve_select->GetValue());
	if (TBInlineSelect *duration_select = GetWidgetByIDAndType<TBInlineSelect>("duration"))
		duration = duration_select->GetValueDouble();
	if (TBCheckBox *fade_check = GetWidgetByIDAndType<TBCheckBox>("fade"))
		fade = fade_check->GetValue() ? true : false;

	// Start move animation
	if (TBAnimationObject *anim = new TBWidgetAnimationRect(this, GetRect().Offset(-GetRect().x - GetRect().w, 0), GetRect()))
		TBAnimationManager::StartAnimation(anim, curve, duration);
	// Start fade animation
	if (fade)
	{
		if (TBAnimationObject *anim = new TBWidgetAnimationOpacity(this, TB_ALMOST_ZERO_OPACITY, 1, false))
			TBAnimationManager::StartAnimation(anim, ANIMATION_CURVE_SLOW_DOWN, duration);
	}
}

bool AnimationsWindow::OnEvent(const TBWidgetEvent &ev)
{
	if (ev.type == EVENT_TYPE_CLICK && ev.target->GetID() == TBIDC("Animate!"))
		Animate();
	return DemoWindow::OnEvent(ev);
}

// == MainWindow ==============================================================
MainWindow::MainWindow(TBWidget *root) : DemoWindow(root)
{
	LoadResourceFile("demo01/ui_resources/test_ui.tb.txt");

	SetOpacity(0.97f);
}

void MainWindow::OnMessageReceived(TBMessage *msg)
{
	if (msg->message == TBIDC("instantmsg"))
	{
		TBMessageWindow *msg_win = new TBMessageWindow(this, TBIDC("test_dialog"));
		msg_win->Show("Message window", "Instant message received!");
	}
	else if (msg->message == TBIDC("busy"))
	{
		// Keep the message queue busy by posting another "busy" message.
		PostMessage(TBIDC("busy"), nullptr);
	}
	else if (msg->message == TBIDC("delayedmsg"))
	{
		TBStr text;
		text.SetFormatted("Delayed message received!\n\n"
							"It was received %d ms after its intended fire time.",
							(int)(TBSystem::GetTimeMS() - msg->GetFireTime()));
		TBMessageWindow *msg_win = new TBMessageWindow(this, TBIDC(""));
		msg_win->Show("Message window", text);
	}
}

bool MainWindow::OnEvent(const TBWidgetEvent &ev)
{
	if (ev.type == EVENT_TYPE_CLICK)
	{
		if (ev.target->GetID() == TBIDC("new"))
		{
			new MainWindow(GetParentRoot());
			return true;
		}
		if (ev.target->GetID() == TBIDC("msg"))
		{
			PostMessage(TBIDC("instantmsg"), nullptr);
			return true;
		}
		else if (ev.target->GetID() == TBIDC("busymsg"))
		{
			if (ev.target->GetValue() == 1)
			{
				// Post the first "busy" message when we check the checkbox.
				assert(!GetMessageByID(TBIDC("busy")));
				if (!GetMessageByID(TBIDC("busy")))
				{
					PostMessage(TBIDC("busy"), nullptr);
					TBMessageWindow *msg_win = new TBMessageWindow(this, TBIDC("test_dialog"));
					msg_win->Show("Message window", "The message loop is now constantly busy with messages to process.\n\n"
								"The main thread should be working hard, but input & animations should still be running smoothly.");
				}
			}
			else
			{
				// Remove any pending "busy" message when we uncheck the checkbox.
				assert(GetMessageByID(TBIDC("busy")));
				if (TBMessage *busymsg = GetMessageByID(TBIDC("busy")))
					DeleteMessage(busymsg);
			}
			return true;
		}
		else if (ev.target->GetID() == TBIDC("delayedmsg"))
		{
			PostMessageDelayed(TBIDC("delayedmsg"), nullptr, 2000);
			return true;
		}
		else if (ev.target->GetID() == TBIDC("TBWindow.close"))
		{
			// Intercept the TBWindow.close message and stop it from bubbling
			// to TBWindow (prevent the window from closing)
			TBMessageWindow *msg_win = new TBMessageWindow(this, TBIDC("confirm_close_dialog"));
			TBMessageWindowSettings settings(TB_MSG_YES_NO, TBIDC("Icon48"));
			settings.dimmer = true;
			settings.styling = true;
			msg_win->Show("Are you sure?", "Really <color #0794f8>close</color> the window?", &settings);
			return true;
		}
		else if (ev.target->GetID() == TBIDC("confirm_close_dialog"))
		{
			if (ev.ref_id == TBIDC("TBMessageWindow.yes"))
				Close();
			return true;
		}
		else if (ev.target->GetID() == TBIDC("reload skin bitmaps"))
		{
			int reload_count = 10;
			double t1 = TBSystem::GetTimeMS();
			for (int i = 0; i < reload_count; i++)
				g_tb_skin->ReloadBitmaps();
			double t2 = TBSystem::GetTimeMS();

			TBStr message;
			message.SetFormatted("Reloading the skin graphics %d times took %dms", reload_count, (int)(t2 - t1));
			TBMessageWindow *msg_win = new TBMessageWindow(ev.target, TBID());
			msg_win->Show("GFX load performance", message);
			return true;
		}
		else if (ev.target->GetID() == TBIDC("test context lost"))
		{
			g_renderer->InvokeContextLost();
			g_renderer->InvokeContextRestored();
			TBMessageWindow *msg_win = new TBMessageWindow(ev.target, TBID());
			msg_win->Show("Context lost & restore",
							"Called InvokeContextLost and InvokeContextRestored.\n\n"
							"Does everything look fine?");
			return true;
		}
		else if (ev.target->GetID() == TBIDC("test-layout"))
		{
			TBStr resource_file("demo01/ui_resources/");
			resource_file.Append(ev.target->data.GetString());
			new LayoutWindow(GetParentRoot(), resource_file);
			return true;
		}
		else if (ev.target->GetID() == TBIDC("test-connections"))
		{
			new ConnectionWindow(GetParentRoot());
			return true;
		}
		else if (ev.target->GetID() == TBIDC("test-list"))
		{
			new AdvancedListWindow(GetParentRoot(), &advanced_source);
			return true;
		}
		else if (ev.target->GetID() == TBIDC("test-image"))
		{
			new ImageWindow(GetParentRoot());
			return true;
		}
		else if (ev.target->GetID() == TBIDC("test-page"))
		{
			new PageWindow(GetParentRoot());
			return true;
		}
		else if (ev.target->GetID() == TBIDC("test-animations"))
		{
			new AnimationsWindow(GetParentRoot());
			return true;
		}
		else if (ev.target->GetID() == TBIDC("test-scroll-container"))
		{
			new ScrollContainerWindow(GetParentRoot());
			return true;
		}
		else if (ev.target->GetID() == TBIDC("test-skin-conditions"))
		{
			(new DemoWindow(GetParentRoot()))->LoadResourceFile("demo01/ui_resources/test_skin_conditions01.tb.txt");
			(new DemoWindow(GetParentRoot()))->LoadResourceFile("demo01/ui_resources/test_skin_conditions02.tb.txt");
			return true;
		}
		else if (ev.target->GetID() == TBIDC("test-resource-edit"))
		{
			ResourceEditWindow *res_edit_win = new ResourceEditWindow();
			res_edit_win->Load("demo01/ui_resources/resource_edit_test.tb.txt");
			GetParent()->AddChild(res_edit_win);
			return true;
		}
		else if (ev.type == EVENT_TYPE_CLICK && ev.target->GetID() == TBIDC("debug settings"))
		{
#ifdef TB_RUNTIME_DEBUG_INFO
			ShowDebugInfoSettingsWindow(GetParentRoot());
#else
			TBMessageWindow *msg_win = new TBMessageWindow(ev.target, TBID());
			msg_win->Show("Debug settings",
							"Debug settings is only available in builds "
							"compiled with TB_RUNTIME_DEBUG_INFO defined.\n\n"
							"Debug builds enable this by default.");
#endif
			return true;
		}
	}
	return DemoWindow::OnEvent(ev);
}

//=============================================================================
//=============================================================================
int fps = 0;
uint32 frame_counter_total = 0;
uint32 frame_counter = 0;
double frame_counter_reset_time = 0;

const char *girl_names[] = {
	"Maja", "Alice", "Julia", "Linnéa", "Wilma", "Ella", "Elsa", "Emma", "Alva", "Olivia", "Molly", "Ebba", "Klara", "Nellie", "Agnes",
	"Isabelle", "Ida", "Elin", "Ellen", "Moa", "Emilia", "Nova", "Alma", "Saga", "Amanda", "Isabella", "Lilly", "Alicia", "Astrid",
	"Matilda", "Tuva", "Tilde", "Stella", "Felicia", "Elvira", "Tyra", "Hanna", "Sara", "Vera", "Thea", "Freja", "Lova", "Selma",
	"Meja", "Signe", "Ester", "Lovisa", "Ellie", "Lea", "Tilda", "Tindra", "Sofia", "Nora", "Nathalie", "Leia", "Filippa", "Siri",
	"Emelie", "Inez", "Edith", "Stina", "Liv", "Lisa", "Linn", "Tove", "Emmy", "Livia", "Jasmine", "Evelina", "Cornelia", "Märta",
	"Svea", "Ingrid", "My", "Rebecca", "Joline", "Mira", "Ronja", "Hilda", "Melissa", "Anna", "Frida", "Maria", "Iris", "Josefine",
	"Elise", "Elina", "Greta", "Vilda", "Minna", "Lina", "Hedda", "Nicole", "Kajsa", "Majken", "Sofie", "Annie", "Juni", "Novalie", "Hedvig", 0 };
const char *boy_names[] = {
	"Oscar", "William", "Lucas", "Elias", "Alexander", "Hugo", "Oliver", "Theo", "Liam", "Leo", "Viktor", "Erik", "Emil",
	"Isak", "Axel", "Filip", "Anton", "Gustav", "Edvin", "Vincent", "Arvid", "Albin", "Ludvig", "Melvin", "Noah", "Charlie", "Max",
	"Elliot", "Viggo", "Alvin", "Alfred", "Theodor", "Adam", "Olle", "Wilmer", "Benjamin", "Simon", "Nils", "Noel", "Jacob", "Leon",
	"Rasmus", "Kevin", "Linus", "Casper", "Gabriel", "Jonathan", "Milo", "Melker", "Felix", "Love", "Ville", "Sebastian", "Sixten",
	"Carl", "Malte", "Neo", "David", "Joel", "Adrian", "Valter", "Josef", "Jack", "Hampus", "Samuel", "Mohammed", "Alex", "Tim",
	"Daniel", "Vilgot", "Wilhelm", "Harry", "Milton", "Maximilian", "Robin", "Sigge", "Måns", "Eddie", "Elton", "Vidar", "Hjalmar",
	"Loke", "Elis", "August", "John", "Hannes", "Sam", "Frank", "Svante", "Marcus", "Mio", "Otto", "Ali", "Johannes", "Fabian",
	"Ebbe", "Aron", "Julian", "Elvin", "Ivar", 0 };

//=============================================================================
//=============================================================================
namespace Urho3D
{

void UTBDemo::Start()
{
    // Block new animations during Init.
	TBAnimationBlocker anim_blocker;

	// Run unit tests
	int num_failed_tests = TBRunTests();

	// TBSelectList and TBSelectDropdown widgets have a default item source that are fed with any items
	// specified in the resource files. But it is also possible to set any source which can save memory
	// and improve performance. Then you don't have to populate each instance with its own set of items,
	// for widgets that occur many times in a UI, always with the same items.
	// Here we prepare the name source, that is used in a few places.
	for (int i = 0; boy_names[i]; i++)
		advanced_source.AddItem(new AdvancedItem(boy_names[i++], TBIDC("boy_item"), true));
	for (int i = 0; girl_names[i]; i++)
		advanced_source.AddItem(new AdvancedItem(girl_names[i++], TBIDC("girl_item"), false));
	for (int i = 0; girl_names[i]; i++)
		name_source.AddItem(new TBGenericStringItem(girl_names[i++], TBIDC("girl_item")));
	for (int i = 0; boy_names[i]; i++)
		name_source.AddItem(new TBGenericStringItem(boy_names[i++], TBIDC("boy_item")));
	advanced_source.SetSort(TB_SORT_ASCENDING);
	name_source.SetSort(TB_SORT_ASCENDING);

	// Prepare a source with submenus (with eternal recursion) so we can test sub menu support.
	popup_menu_source.AddItem(new TBGenericStringItem("Option 1", TBIDC("opt 1")));
	popup_menu_source.AddItem(new TBGenericStringItem("Option 2", TBIDC("opt 2")));
	popup_menu_source.AddItem(new TBGenericStringItem("-"));
	popup_menu_source.AddItem(new TBGenericStringItem("Same submenu", &popup_menu_source));
	popup_menu_source.AddItem(new TBGenericStringItem("Long submenu", &name_source));
	// Give the first item a skin image
	popup_menu_source.GetItem(0)->SetSkinImage(TBIDC("Icon16"));

    new MainWindow( &UTBRendererBatcher::Singleton().Root() );

    new EditWindow( &UTBRendererBatcher::Singleton().Root() );

    new ListWindow( &UTBRendererBatcher::Singleton().Root(), &name_source );

    new AdvancedListWindow( &UTBRendererBatcher::Singleton().Root(), &advanced_source );

    new TabContainerWindow( &UTBRendererBatcher::Singleton().Root() );

	if ( num_failed_tests )
	{
		TBStr text;
		text.SetFormatted("There is %d failed tests!\nCheck the output for details.", num_failed_tests);
		TBMessageWindow *msg_win = new TBMessageWindow( &UTBRendererBatcher::Singleton().Root(), TBIDC("") );
		msg_win->Show("Testing results", text);
	}
}

} //namespace Urho3D
#endif //TB_DEMO
