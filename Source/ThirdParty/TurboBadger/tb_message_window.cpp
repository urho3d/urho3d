// ================================================================================
// ==      This file is a part of Turbo Badger. (C) 2011-2014, Emil Segerås      ==
// ==                     See tb_core.h for more information.                    ==
// ================================================================================

#include "tb_message_window.h"
#include "tb_widgets_reader.h"
#include "tb_editfield.h"
#include "tb_language.h"
#include <assert.h>

namespace tb {

// == TBMessageWindow =======================================================================================

TBMessageWindow::TBMessageWindow(TBWidget *target, TBID id)
	: m_target(target)
{
	TBWidgetListener::AddGlobalListener(this);
	SetID(id);
}

TBMessageWindow::~TBMessageWindow()
{
	TBWidgetListener::RemoveGlobalListener(this);
	if (TBWidget *dimmer = m_dimmer.Get())
	{
		dimmer->GetParent()->RemoveChild(dimmer);
		delete dimmer;
	}
}

bool TBMessageWindow::Show(const char *title, const char *message, TBMessageWindowSettings *settings)
{
	TBWidget *target = m_target.Get();
	if (!target)
		return false;

	TBMessageWindowSettings default_settings;
	if (!settings)
		settings = &default_settings;

	TBWidget *root = target->GetParentRoot();

	const char *source =	"TBLayout: axis: y, distribution: available\n"
							"	TBLayout: distribution: available, size: available\n"
							"		TBSkinImage: id: 2\n"
							"		TBEditField: multiline: 1, readonly: 1, id: 1\n"
							"	TBLayout: distribution-position: right bottom, id: 3\n";
	if (!g_widgets_reader->LoadData(GetContentRoot(), source))
		return false;

	SetText(title);

	GetWidgetByIDAndType<TBSkinImage>(2)->SetSkinBg(settings->icon_skin);

	TBEditField *editfield = GetWidgetByIDAndType<TBEditField>(1);
	editfield->SetStyling(settings->styling);
	editfield->SetText(message);
	editfield->SetSkinBg("");

	// Create buttons
	if (settings->msg == TB_MSG_OK)
	{
		AddButton("TBMessageWindow.ok", true);
	}
	else if (settings->msg == TB_MSG_OK_CANCEL)
	{
		AddButton("TBMessageWindow.ok", true);
		AddButton("TBMessageWindow.cancel", false);
	}
	else if (settings->msg == TB_MSG_YES_NO)
	{
		AddButton("TBMessageWindow.yes", true);
		AddButton("TBMessageWindow.no", false);
	}

	// Size to fit content. This will use the default size of the textfield.
	ResizeToFitContent();
	TBRect rect = GetRect();

	// Get how much we overflow the textfield has given the current width, and grow our height to show all we can.
	// FIX: It would be better to use adapt-to-content on the editfield to achieve the most optimal size.
	// At least when we do full blown multi pass size checking.
	rect.h += editfield->GetStyleEdit()->GetOverflowY();

	// Create background dimmer
	if (settings->dimmer)
	{
		if (TBDimmer *dimmer = new TBDimmer)
		{
			root->AddChild(dimmer);
			m_dimmer.Set(dimmer);
		}
	}

	// Center and size to the new height
	TBRect bounds(0, 0, root->GetRect().w, root->GetRect().h);
	SetRect(rect.CenterIn(bounds).MoveIn(bounds).Clip(bounds));
	root->AddChild(this);
	return true;
}

void TBMessageWindow::AddButton(TBID id, bool focused)
{
	TBLayout *layout = GetWidgetByIDAndType<TBLayout>(3);
	if (!layout)
		return;
	if (TBButton *btn = new TBButton)
	{
		btn->SetID(id);
		btn->SetText(g_tb_lng->GetString(btn->GetID()));
		layout->AddChild(btn);
		if (focused)
			btn->SetFocus(WIDGET_FOCUS_REASON_UNKNOWN);
	}
}

bool TBMessageWindow::OnEvent(const TBWidgetEvent &ev)
{
	if (ev.type == EVENT_TYPE_CLICK && ev.target->IsOfType<TBButton>())
	{
		TBWidgetSafePointer this_widget(this);

		// Invoke the click on the target
		TBWidgetEvent target_ev(EVENT_TYPE_CLICK);
		target_ev.ref_id = ev.target->GetID();
		InvokeEvent(target_ev);

		// If target got deleted, close
		if (this_widget.Get())
			Close();
		return true;
	}
	else if (ev.type == EVENT_TYPE_KEY_DOWN && ev.special_key == TB_KEY_ESC)
	{
		TBWidgetEvent click_ev(EVENT_TYPE_CLICK);
		m_close_button.InvokeEvent(click_ev);
		return true;
	}
	return TBWindow::OnEvent(ev);
}

void TBMessageWindow::OnDie()
{
	if (TBWidget *dimmer = m_dimmer.Get())
		dimmer->Die();
}

void TBMessageWindow::OnWidgetDelete(TBWidget *widget)
{
	// If the target widget is deleted, close!
	if (!m_target.Get())
		Close();
}

bool TBMessageWindow::OnWidgetDying(TBWidget *widget)
{
	// If the target widget or an ancestor of it is dying, close!
	if (widget == m_target.Get() || widget->IsAncestorOf(m_target.Get()))
		Close();
	return false;
}

}; // namespace tb
