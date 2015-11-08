// ================================================================================
// ==      This file is a part of Turbo Badger. (C) 2011-2014, Emil Segerås      ==
// ==                     See tb_core.h for more information.                    ==
// ================================================================================

#include "tb_widgets_listener.h"
#include "tb_popup_window.h"

namespace tb {

// == TBPopupAlignment ======================================================================================

TBRect TBPopupAlignment::GetAlignedRect(TBWidget *popup, TBWidget *target) const
{
	TBWidget *root = target->GetParentRoot();

	SizeConstraints sc(root->GetRect().w, root->GetRect().h);

	PreferredSize ps = popup->GetPreferredSize(sc);

	// Amount of pixels that should be avoided if the target rect needs to be moved.
	int avoid_w = 0, avoid_h = 0;

	int x = 0, y = 0;
	int w = MIN(ps.pref_w, root->GetRect().w);
	int h = MIN(ps.pref_h, root->GetRect().h);

	if (pos_in_root.x != UNSPECIFIED &&
		pos_in_root.y != UNSPECIFIED)
	{
		x = pos_in_root.x;
		y = pos_in_root.y;
		avoid_w = pos_offset.x;
		avoid_h = pos_offset.y;
		// Make sure it's moved into view horizontally
		if (align == TB_ALIGN_TOP || align == TB_ALIGN_BOTTOM)
			x = Clamp(x, 0, root->GetRect().w - w);
	}
	else
	{
		target->ConvertToRoot(x, y);

		if (align == TB_ALIGN_TOP || align == TB_ALIGN_BOTTOM)
		{
			if (expand_to_target_width)
				w = MAX(w, target->GetRect().w);

			// If the menu is aligned top or bottom, limit its height to the worst case available height.
			// Being in the center of the root, that is half the root height minus the target rect.
			h = MIN(h, root->GetRect().h / 2 - target->GetRect().h);
		}
		avoid_w = target->GetRect().w;
		avoid_h = target->GetRect().h;
	}

	if (align == TB_ALIGN_BOTTOM)
		y = y + avoid_h + h > root->GetRect().h ? y - h : y + avoid_h;
	else if (align == TB_ALIGN_TOP)
		y = y - h < 0 ? y + avoid_h : y - h;
	else if (align == TB_ALIGN_RIGHT)
	{
		x = x + avoid_w + w > root->GetRect().w ? x - w : x + avoid_w;
		y = MIN(y, root->GetRect().h - h);
	}
	else // if (align == TB_ALIGN_LEFT)
	{
		x = x - w < 0 ? x + avoid_w : x - w;
		y = MIN(y, root->GetRect().h - h);
	}
	return TBRect(x, y, w, h);
}

// == TBPopupWindow =========================================================================================

TBPopupWindow::TBPopupWindow(TBWidget *target)
	: m_target(target)
{
	TBWidgetListener::AddGlobalListener(this);
	SetSkinBg(TBIDC("TBPopupWindow"), WIDGET_INVOKE_INFO_NO_CALLBACKS);
	SetSettings(WINDOW_SETTINGS_NONE);
}

TBPopupWindow::~TBPopupWindow()
{
	TBWidgetListener::RemoveGlobalListener(this);
}

bool TBPopupWindow::Show(const TBPopupAlignment &alignment)
{
	// Calculate and set a good size for the popup window
	SetRect(alignment.GetAlignedRect(this, m_target.Get()));

	TBWidget *root = m_target.Get()->GetParentRoot();
	root->AddChild(this);
	return true;
}

bool TBPopupWindow::OnEvent(const TBWidgetEvent &ev)
{
	if (ev.type == EVENT_TYPE_KEY_DOWN && ev.special_key == TB_KEY_ESC)
	{
		Close();
		return true;
	}
	return TBWindow::OnEvent(ev);
}

void TBPopupWindow::OnWidgetFocusChanged(TBWidget *widget, bool focused)
{
	if (focused && !IsEventDestinationFor(widget))
		Close();
}

bool TBPopupWindow::OnWidgetInvokeEvent(TBWidget *widget, const TBWidgetEvent &ev)
{
	if ((ev.type == EVENT_TYPE_POINTER_DOWN || ev.type == EVENT_TYPE_CONTEXT_MENU) &&
		!IsEventDestinationFor(ev.target))
		Close();
	return false;
}

void TBPopupWindow::OnWidgetDelete(TBWidget *widget)
{
	// If the target widget is deleted, close!
	if (!m_target.Get())
		Close();
}

bool TBPopupWindow::OnWidgetDying(TBWidget *widget)
{
	// If the target widget or an ancestor of it is dying, close!
	if (widget == m_target.Get() || widget->IsAncestorOf(m_target.Get()))
		Close();
	return false;
}

}; // namespace tb
