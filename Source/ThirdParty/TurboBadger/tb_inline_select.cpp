// ================================================================================
// ==      This file is a part of Turbo Badger. (C) 2011-2014, Emil Segerås      ==
// ==                     See tb_core.h for more information.                    ==
// ================================================================================

#include "tb_inline_select.h"
#include <assert.h>
#include <stdlib.h>

namespace tb {

// FIX: axis should affect the buttons arrow skin!
// FIX: unfocus should set the correct text!

// == TBInlineSelect ========================================================================================

TBInlineSelect::TBInlineSelect()
	: m_value(0)
	, m_min(0)
	, m_max(100)
{
	SetSkinBg(TBIDC("TBInlineSelect"));
	AddChild(&m_layout);
	m_layout.AddChild(&m_buttons[0]);
	m_layout.AddChild(&m_editfield);
	m_layout.AddChild(&m_buttons[1]);
	m_layout.SetRect(GetPaddingRect());
	m_layout.SetGravity(WIDGET_GRAVITY_ALL);
	m_layout.SetSpacing(0);
	m_buttons[0].SetSkinBg(TBIDC("TBButton.flat"));
	m_buttons[1].SetSkinBg(TBIDC("TBButton.flat"));
	m_buttons[0].GetContentRoot()->AddChild(new TBSkinImage(TBIDC("arrow.left")));
	m_buttons[1].GetContentRoot()->AddChild(new TBSkinImage(TBIDC("arrow.right")));
	m_buttons[0].SetIsFocusable(false);
	m_buttons[1].SetIsFocusable(false);
	m_buttons[0].SetID(TBIDC("dec"));
	m_buttons[1].SetID(TBIDC("inc"));
	m_buttons[0].SetAutoRepeat(true);
	m_buttons[1].SetAutoRepeat(true);
	m_editfield.SetTextAlign(TB_TEXT_ALIGN_CENTER);
	m_editfield.SetEditType(EDIT_TYPE_NUMBER);
	m_editfield.SetText("0");
}

TBInlineSelect::~TBInlineSelect()
{
	m_layout.RemoveChild(&m_buttons[1]);
	m_layout.RemoveChild(&m_editfield);
	m_layout.RemoveChild(&m_buttons[0]);
	RemoveChild(&m_layout);
}

void TBInlineSelect::SetLimits(int min, int max)
{
	assert(min <= max);
	m_min = min;
	m_max = max;
	SetValue(m_value);
}

void TBInlineSelect::SetValueInternal(int value, bool update_text)
{
	value = CLAMP(value, m_min, m_max);
	if (value == m_value)
		return;
	m_value = value;

	if (update_text)
	{
		TBStr strval;
		strval.SetFormatted("%d", m_value);
		m_editfield.SetText(strval);
	}

	TBWidgetEvent ev(EVENT_TYPE_CHANGED);
	InvokeEvent(ev);

	// Warning: Do nothing here since the event might have deleted us.
	//          If needed, check if we are alive using a safe pointer first.
}

void TBInlineSelect::OnSkinChanged()
{
	m_layout.SetRect(GetPaddingRect());
}

bool TBInlineSelect::OnEvent(const TBWidgetEvent &ev)
{
	if (ev.type == EVENT_TYPE_KEY_DOWN)
	{
		if (ev.special_key == TB_KEY_UP || ev.special_key == TB_KEY_DOWN)
		{
			int dv = ev.special_key == TB_KEY_UP ? 1 : -1;
			SetValue(GetValue() + dv);
			return true;
		}
	}
	else if (ev.type == EVENT_TYPE_CLICK && ev.target->GetID() == TBIDC("dec"))
	{
		SetValue(GetValue() - 1);
		return true;
	}
	else if (ev.type == EVENT_TYPE_CLICK && ev.target->GetID() == TBIDC("inc"))
	{
		SetValue(GetValue() + 1);
		return true;
	}
	else if (ev.type == EVENT_TYPE_CHANGED && ev.target == &m_editfield)
	{
		TBStr text;
		m_editfield.GetText(text);
		SetValueInternal(atoi(text), false);
	}
	return false;
}

}; // namespace tb
