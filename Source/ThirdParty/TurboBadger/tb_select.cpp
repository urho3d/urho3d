// ================================================================================
// ==      This file is a part of Turbo Badger. (C) 2011-2014, Emil Segerås      ==
// ==                     See tb_core.h for more information.                    ==
// ================================================================================

#include "tb_select.h"
#include "tb_menu_window.h"
#include "tb_widgets_listener.h"
#include "tb_language.h"
#include "tb_tempbuffer.h"
#include "tb_sort.h"

namespace tb {

// == Sort callback for sorting items ===================================================

int select_list_sort_cb(TBSelectItemSource *source, const int *a, const int *b)
{
	int value = strcmp(source->GetItemString(*a), source->GetItemString(*b));
	return source->GetSort() == TB_SORT_DESCENDING ? -value : value;
}

// == TBSelectList ==============================================

TBSelectList::TBSelectList()
	: m_value(-1)
	, m_list_is_invalid(false)
	, m_scroll_to_current(false)
	, m_header_lng_string_id(TBIDC("TBList.header"))
{
	SetSource(&m_default_source);
	SetIsFocusable(true);
	SetSkinBg(TBIDC("TBSelectList"), WIDGET_INVOKE_INFO_NO_CALLBACKS);
	m_container.SetGravity(WIDGET_GRAVITY_ALL);
	m_container.SetRect(GetPaddingRect());
	AddChild(&m_container);
	m_layout.SetGravity(WIDGET_GRAVITY_ALL);
	m_layout.SetAxis(AXIS_Y);
	m_layout.SetSpacing(0);
	m_layout.SetLayoutPosition(LAYOUT_POSITION_LEFT_TOP);
	m_layout.SetLayoutDistributionPosition(LAYOUT_DISTRIBUTION_POSITION_LEFT_TOP);
	m_layout.SetLayoutSize(LAYOUT_SIZE_AVAILABLE);
	m_container.GetContentRoot()->AddChild(&m_layout);
	m_container.SetScrollMode(SCROLL_MODE_Y_AUTO);
	m_container.SetAdaptContentSize(true);
}

TBSelectList::~TBSelectList()
{
	m_container.GetContentRoot()->RemoveChild(&m_layout);
	RemoveChild(&m_container);
	SetSource(nullptr);
}

void TBSelectList::OnSourceChanged()
{
	InvalidateList();
}

void TBSelectList::OnItemChanged(int index)
{
	if (m_list_is_invalid) // We're updating all widgets soon.
		return;

	TBWidget *old_widget = GetItemWidget(index);
	if (!old_widget) // We don't have this widget so we have nothing to update.
		return;

	// Replace the old widget representing the item, with a new one. Preserve its state.
	WIDGET_STATE old_state = old_widget->GetStateRaw();

	if (TBWidget *widget = CreateAndAddItemAfter(index, old_widget))
		widget->SetStateRaw(old_state);

	old_widget->GetParent()->RemoveChild(old_widget);
	delete old_widget;
}

void TBSelectList::OnItemAdded(int index)
{
	if (m_list_is_invalid) // We're updating all widgets soon.
		return;

	// Sorting, filtering etc. makes it messy to handle dynamic addition of items.
	// Resort to invalidate the entire list (may even be faster anyway)
	InvalidateList();
}

void TBSelectList::OnItemRemoved(int index)
{
	if (m_list_is_invalid) // We're updating all widgets soon.
		return;

	// Sorting, filtering etc. makes it messy to handle dynamic addition of items.
	// Resort to invalidate the entire list (may even be faster anyway)
	InvalidateList();
}

void TBSelectList::OnAllItemsRemoved()
{
	InvalidateList();
	m_value = -1;
}

void TBSelectList::SetFilter(const char *filter)
{
	TBStr new_filter;
	if (filter && *filter)
		new_filter.Set(filter);
	if (m_filter.Equals(new_filter))
		return;
	m_filter.Set(new_filter);
	InvalidateList();
}

void TBSelectList::SetHeaderString(const TBID& id)
{
	if (m_header_lng_string_id == id)
		return;
	m_header_lng_string_id = id;
	InvalidateList();
}

void TBSelectList::InvalidateList()
{
	if (m_list_is_invalid)
		return;
	m_list_is_invalid = true;
	Invalidate();
}

void TBSelectList::ValidateList()
{
	if (!m_list_is_invalid)
		return;
	m_list_is_invalid = false;
	// FIX: Could delete and create only the changed items (faster filter change)

	// Remove old items
	while (TBWidget *child = m_layout.GetContentRoot()->GetFirstChild())
	{
		child->GetParent()->RemoveChild(child);
		delete child;
	}
	if (!m_source || !m_source->GetNumItems())
		return;

	// Create a sorted list of the items we should include using the current filter.
	TBTempBuffer sort_buf;
	if (!sort_buf.Reserve(m_source->GetNumItems() * sizeof(int)))
		return; // Out of memory
	int *sorted_index = (int *) sort_buf.GetData();

	// Populate the sorted index list
	int num_sorted_items = 0;
	for (int i = 0; i < m_source->GetNumItems(); i++)
		if (m_filter.IsEmpty() || m_source->Filter(i, m_filter))
			sorted_index[num_sorted_items++] = i;

	// Sort
	if (m_source->GetSort() != TB_SORT_NONE)
		insertion_sort<TBSelectItemSource*, int>(sorted_index, num_sorted_items, m_source, select_list_sort_cb);

	// Show header if we only show a subset of all items.
	if (!m_filter.IsEmpty())
	{
		if (TBWidget *widget = new TBTextField())
		{
			TBStr str;
			str.SetFormatted(g_tb_lng->GetString(m_header_lng_string_id), num_sorted_items, m_source->GetNumItems());
			widget->SetText(str);
			widget->SetSkinBg(TBIDC("TBList.header"));
			widget->SetState(WIDGET_STATE_DISABLED, true);
			widget->SetGravity(WIDGET_GRAVITY_ALL);
			widget->data.SetInt(-1);
			m_layout.GetContentRoot()->AddChild(widget);
		}
	}

	// Create new items
	for (int i = 0; i < num_sorted_items; i++)
		CreateAndAddItemAfter(sorted_index[i], nullptr);

	SelectItem(m_value, true);

	// FIX: Should not scroll just because we update the list. Only automatically first time!
	m_scroll_to_current = true;
}

TBWidget *TBSelectList::CreateAndAddItemAfter(int index, TBWidget *reference)
{
	if (TBWidget *widget = m_source->CreateItemWidget(index, this))
	{
		// Use item data as widget to index lookup
		widget->data.SetInt(index);
		m_layout.GetContentRoot()->AddChildRelative(widget, WIDGET_Z_REL_AFTER, reference);
		return widget;
	}
	return nullptr;
}

void TBSelectList::SetValue(int value)
{
	if (value == m_value)
		return;

	SelectItem(m_value, false);
	m_value = value;
	SelectItem(m_value, true);
	ScrollToSelectedItem();

	TBWidgetEvent ev(EVENT_TYPE_CHANGED);
	if (TBWidget *widget = GetItemWidget(m_value))
		ev.ref_id = widget->GetID();
	InvokeEvent(ev);
}

TBID TBSelectList::GetSelectedItemID()
{
	if (m_source && m_value >= 0 && m_value < m_source->GetNumItems())
		return m_source->GetItemID(m_value);
	return TBID();
}

void TBSelectList::SelectItem(int index, bool selected)
{
	if (TBWidget *widget = GetItemWidget(index))
		widget->SetState(WIDGET_STATE_SELECTED, selected);
}

TBWidget *TBSelectList::GetItemWidget(int index)
{
	if (index == -1)
		return nullptr;
	for (TBWidget *tmp = m_layout.GetContentRoot()->GetFirstChild(); tmp; tmp = tmp->GetNext())
		if (tmp->data.GetInt() == index)
			return tmp;
	return nullptr;
}

void TBSelectList::ScrollToSelectedItem()
{
	if (m_list_is_invalid)
	{
		m_scroll_to_current = true;
		return;
	}
	m_scroll_to_current = false;
	if (TBWidget *widget = GetItemWidget(m_value))
		m_container.ScrollIntoView(widget->GetRect());
	else
		m_container.ScrollTo(0, 0);
}

void TBSelectList::OnSkinChanged()
{
	m_container.SetRect(GetPaddingRect());
}

void TBSelectList::OnProcess()
{
	ValidateList();
}

void TBSelectList::OnProcessAfterChildren()
{
	if (m_scroll_to_current)
		ScrollToSelectedItem();
}

bool TBSelectList::OnEvent(const TBWidgetEvent &ev)
{
	if (ev.type == EVENT_TYPE_CLICK && ev.target->GetParent() == m_layout.GetContentRoot())
	{
		// SetValue (EVENT_TYPE_CHANGED) might cause something to delete this (f.ex closing
		// the dropdown menu. We want to sent another event, so ensure we're still around.
		TBWidgetSafePointer this_widget(this);

		int index = ev.target->data.GetInt();
		SetValue(index);

		// If we're still around, invoke the click event too.
		if (this_widget.Get())
		{
			TBSelectList *target_list = this;
			// If the parent window is a TBMenuWindow, we will iterate up the event destination
			// chain to find the top TBMenuWindow and invoke the event there.
			// That way events in submenus will reach the caller properly, and seem like it was
			// invoked on the top menu.
			TBWindow *window = GetParentWindow();
			while (TBMenuWindow *menu_win = TBSafeCast<TBMenuWindow>(window))
			{
				target_list = menu_win->GetList();
				window = menu_win->GetEventDestination()->GetParentWindow();
			}

			// Invoke the click event on the target list
			TBWidgetEvent ev(EVENT_TYPE_CLICK);
			if (TBWidget *widget = GetItemWidget(m_value))
				ev.ref_id = widget->GetID();
			target_list->InvokeEvent(ev);
		}
		return true;
	}
	else if (ev.type == EVENT_TYPE_KEY_DOWN)
	{
		if (ChangeValue(ev.special_key))
			return true;

		// Give the scroll container a chance to handle the key so it may
		// scroll. This matters if the list itself is focused instead of
		// some child view of any select item (since that would have passed
		// the container already)
		if (GetScrollContainer()->OnEvent(ev))
			return true;
	}
	return false;
}

bool TBSelectList::ChangeValue(SPECIAL_KEY key)
{
	if (!m_source || !m_layout.GetContentRoot()->GetFirstChild())
		return false;

	bool forward;
	if (key == TB_KEY_HOME || key == TB_KEY_DOWN)
		forward = true;
	else if (key == TB_KEY_END || key == TB_KEY_UP)
		forward = false;
	else
		return false;

	TBWidget *item_root = m_layout.GetContentRoot();
	TBWidget *current = GetItemWidget(m_value);
	TBWidget *origin = nullptr;
	if (key == TB_KEY_HOME || (!current && key == TB_KEY_DOWN))
		current = item_root->GetFirstChild();
	else if (key == TB_KEY_END || (!current && key == TB_KEY_UP))
		current = item_root->GetLastChild();
	else
		origin = current;

	while (current)
	{
		if (current != origin && !current->GetDisabled())
			break;
		current = forward ? current->GetNext() : current->GetPrev();
	}
	// Select and focus what we found
	if (current)
	{
		SetValue(current->data.GetInt());
		return true;
	}
	return false;
}

// == TBSelectDropdown ==========================================

TBSelectDropdown::TBSelectDropdown()
	: m_value(-1)
{
	SetSource(&m_default_source);
	SetSkinBg(TBIDC("TBSelectDropdown"), WIDGET_INVOKE_INFO_NO_CALLBACKS);
	m_arrow.SetSkinBg(TBIDC("TBSelectDropdown.arrow"), WIDGET_INVOKE_INFO_NO_CALLBACKS);
	GetContentRoot()->AddChild(&m_arrow);
}

TBSelectDropdown::~TBSelectDropdown()
{
	GetContentRoot()->RemoveChild(&m_arrow);
	SetSource(nullptr);
	CloseWindow();
}

void TBSelectDropdown::OnSourceChanged()
{
	m_value = -1;
	if (m_source && m_source->GetNumItems())
		SetValue(0);
}

void TBSelectDropdown::OnItemChanged(int index)
{
}

void TBSelectDropdown::SetValue(int value)
{
	if (value == m_value || !m_source)
		return;
	m_value = value;

	if (m_value < 0)
		SetText("");
	else if (m_value < m_source->GetNumItems())
		SetText(m_source->GetItemString(m_value));

	TBWidgetEvent ev(EVENT_TYPE_CHANGED);
	InvokeEvent(ev);
}

TBID TBSelectDropdown::GetSelectedItemID()
{
	if (m_source && m_value >= 0 && m_value < m_source->GetNumItems())
		return m_source->GetItemID(m_value);
	return TBID();
}

void TBSelectDropdown::OpenWindow()
{
	if (!m_source || !m_source->GetNumItems() || m_window_pointer.Get())
		return;

	if (TBMenuWindow *window = new TBMenuWindow(this, TBIDC("TBSelectDropdown.window")))
	{
		m_window_pointer.Set(window);
		window->SetSkinBg(TBIDC("TBSelectDropdown.window"));
		window->Show(m_source, TBPopupAlignment(), GetValue());
	}
}

void TBSelectDropdown::CloseWindow()
{
	if (TBMenuWindow *window = GetMenuIfOpen())
		window->Close();
}

TBMenuWindow *TBSelectDropdown::GetMenuIfOpen() const
{
	return TBSafeCast<TBMenuWindow>(m_window_pointer.Get());
}

bool TBSelectDropdown::OnEvent(const TBWidgetEvent &ev)
{
	if (ev.target == this && ev.type == EVENT_TYPE_CLICK)
	{
		// Open the menu, or set the value and close it if already open (this will
		// happen when clicking by keyboard since that will call click on this button)
		if (TBMenuWindow *menu_window = GetMenuIfOpen())
		{
			TBWidgetSafePointer tmp(this);
			int value = menu_window->GetList()->GetValue();
			menu_window->Die();
			if (tmp.Get())
				SetValue(value);
		}
		else
			OpenWindow();
		return true;
	}
	else if (ev.target->GetID() == TBIDC("TBSelectDropdown.window") && ev.type == EVENT_TYPE_CLICK)
	{
		// Set the value of the clicked item
		if (TBMenuWindow *menu_window = GetMenuIfOpen())
			SetValue(menu_window->GetList()->GetValue());
		return true;
	}
	else if (ev.target == this && m_source && ev.IsKeyEvent())
	{
		if (TBMenuWindow *menu_window = GetMenuIfOpen())
		{
			// Redirect the key strokes to the list
			TBWidgetEvent redirected_ev(ev);
			return menu_window->GetList()->InvokeEvent(redirected_ev);
		}
	}
	return false;
}

}; // namespace tb
