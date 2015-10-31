// ================================================================================
// ==      This file is a part of Turbo Badger. (C) 2011-2014, Emil Segerås      ==
// ==                     See tb_core.h for more information.                    ==
// ================================================================================

#include "tb_toggle_container.h"
#include "tb_widgets_reader.h"
#include "tb_node_tree.h"

namespace tb {

// == TBSectionHeader =====================================

TBSectionHeader::TBSectionHeader()
{
	SetSkinBg(TBIDC("TBSectionHeader"));
	SetGravity(WIDGET_GRAVITY_LEFT | WIDGET_GRAVITY_RIGHT);
	SetToggleMode(true);
}

bool TBSectionHeader::OnEvent(const TBWidgetEvent &ev)
{
	if (ev.target == this && ev.type == EVENT_TYPE_CHANGED && GetParent()->GetParent())
	{
		if (TBSection *section = TBSafeCast<TBSection>(GetParent()->GetParent()))
		{
			section->GetContainer()->SetValue(GetValue());

			// Try to scroll the container into view when expanded
			section->SetPendingScrollIntoView(GetValue() ? true : false);
		}
	}
	return TBButton::OnEvent(ev);
}

// == TBSectionHeader =====================================

TBSection::TBSection()
	: m_pending_scroll(false)
{
	SetGravity(WIDGET_GRAVITY_LEFT | WIDGET_GRAVITY_RIGHT);

	SetSkinBg(TBIDC("TBSection"), WIDGET_INVOKE_INFO_NO_CALLBACKS);
	m_layout.SetSkinBg(TBIDC("TBSection.layout"), WIDGET_INVOKE_INFO_NO_CALLBACKS);

	m_toggle_container.SetSkinBg(TBIDC("TBSection.container"));
	m_toggle_container.SetToggle(TBToggleContainer::TOGGLE_EXPANDED);
	m_toggle_container.SetGravity(WIDGET_GRAVITY_ALL);
	m_layout.SetAxis(AXIS_Y);
	m_layout.SetGravity(WIDGET_GRAVITY_ALL);
	m_layout.SetLayoutSize(LAYOUT_SIZE_AVAILABLE);

	AddChild(&m_layout);
	m_layout.AddChild(&m_header);
	m_layout.AddChild(&m_toggle_container);
}

TBSection::~TBSection()
{
	m_layout.RemoveChild(&m_toggle_container);
	m_layout.RemoveChild(&m_header);
	RemoveChild(&m_layout);
}

void TBSection::SetValue(int value)
{
	m_header.SetValue(value);
	m_toggle_container.SetValue(value);
}

void TBSection::OnProcessAfterChildren()
{
	if (m_pending_scroll)
	{
		m_pending_scroll = false;
		ScrollIntoViewRecursive();
	}
}

PreferredSize TBSection::OnCalculatePreferredSize(const SizeConstraints &constraints)
{
	PreferredSize ps = TBWidget::OnCalculatePreferredContentSize(constraints);
	// We should not grow larger than we are, when there's extra space available.
	ps.max_h = ps.pref_h;
	return ps;
}

// == TBToggleContainer ===================================

TBToggleContainer::TBToggleContainer()
	: m_toggle(TOGGLE_NOTHING)
	, m_invert(false)
	, m_value(0)
{
	SetSkinBg(TBIDC("TBToggleContainer"), WIDGET_INVOKE_INFO_NO_CALLBACKS);
}

void TBToggleContainer::SetToggle(TOGGLE toggle)
{
	if (toggle == m_toggle)
		return;

	if (m_toggle == TOGGLE_EXPANDED)
		InvalidateLayout(INVALIDATE_LAYOUT_RECURSIVE);

	m_toggle = toggle;
	UpdateInternal();
}

void TBToggleContainer::SetInvert(bool invert)
{
	if (invert == m_invert)
		return;
	m_invert = invert;
	UpdateInternal();
}

void TBToggleContainer::SetValue(int value)
{
	if (value == m_value)
		return;
	m_value = value;
	UpdateInternal();
	InvalidateSkinStates();
}

void TBToggleContainer::UpdateInternal()
{
	bool on = GetIsOn();
	switch (m_toggle)
	{
	case TOGGLE_NOTHING:
		break;
	case TOGGLE_ENABLED:
		SetState(WIDGET_STATE_DISABLED, !on);
		break;
	case TOGGLE_OPACITY:
		SetOpacity(on ? 1.f : 0);
		break;
	case TOGGLE_EXPANDED:
		SetVisibilility(on ? WIDGET_VISIBILITY_VISIBLE : WIDGET_VISIBILITY_GONE);

		// Also disable when collapsed so tab focus skips the children.
		SetState(WIDGET_STATE_DISABLED, !on);
		break;
	};
}

}; // namespace tb
