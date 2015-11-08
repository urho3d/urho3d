// ================================================================================
// ==      This file is a part of Turbo Badger. (C) 2011-2014, Emil Segerås      ==
// ==                     See tb_core.h for more information.                    ==
// ================================================================================

#include "tb_menu_window.h"
#include "tb_widgets_listener.h"

namespace tb {

// == TBMenuWindow ==========================================

TBMenuWindow::TBMenuWindow(TBWidget *target, TBID id)
	: TBPopupWindow(target)
{
	SetID(id);
	SetSkinBg(TBIDC("TBMenuWindow"), WIDGET_INVOKE_INFO_NO_CALLBACKS);
	m_select_list.GetScrollContainer()->SetAdaptToContentSize(true);
	m_select_list.SetIsFocusable(false); ///< Avoid it autoclosing its window on click
	m_select_list.SetSkinBg("");
	m_select_list.SetRect(GetPaddingRect());
	m_select_list.SetGravity(WIDGET_GRAVITY_ALL);
	AddChild(&m_select_list);
}

TBMenuWindow::~TBMenuWindow()
{
	RemoveChild(&m_select_list);
}

bool TBMenuWindow::Show(TBSelectItemSource *source, const TBPopupAlignment &alignment, int initial_value)
{
	m_select_list.SetValue(initial_value);
	m_select_list.SetSource(source);
	m_select_list.ValidateList();

	return TBPopupWindow::Show(alignment);
}

bool TBMenuWindow::OnEvent(const TBWidgetEvent &ev)
{
	if (ev.type == EVENT_TYPE_CLICK && &m_select_list == ev.target)
	{
		TBWidgetSafePointer this_widget(this);

		// Invoke the click on the target
		TBWidgetEvent target_ev(EVENT_TYPE_CLICK);
		target_ev.ref_id = ev.ref_id;
		InvokeEvent(target_ev);

		// If target got deleted, close
		if (this_widget.Get())
			Close();
		return true;
	}
	return TBPopupWindow::OnEvent(ev);
}

}; // namespace tb
