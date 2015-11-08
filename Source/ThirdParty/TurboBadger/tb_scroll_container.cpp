// ================================================================================
// ==      This file is a part of Turbo Badger. (C) 2011-2014, Emil Segerås      ==
// ==                     See tb_core.h for more information.                    ==
// ================================================================================

#include "tb_scroll_container.h"
#include "tb_system.h"
#include <assert.h>

namespace tb {

// == TBScrollBarVisibility ===================================

TBScrollBarVisibility TBScrollBarVisibility::Solve(SCROLL_MODE mode, int content_w, int content_h,
																	int available_w, int available_h,
																	int scrollbar_x_h, int scrollbar_y_w)
{
	TBScrollBarVisibility visibility;
	visibility.visible_w = available_w;
	visibility.visible_h = available_h;

	if (mode == SCROLL_MODE_X_Y)
	{
		visibility.y_on = true;
		visibility.x_on = true;
		visibility.visible_w -= scrollbar_y_w;
		visibility.visible_h -= scrollbar_x_h;
	}
	else if (mode == SCROLL_MODE_OFF)
	{
	}
	else if (mode == SCROLL_MODE_Y)
	{
		visibility.y_on = true;
		visibility.visible_w -= scrollbar_y_w;
	}
	else if (mode == SCROLL_MODE_Y_AUTO)
	{
		if (content_h > available_h)
		{
			visibility.y_on = true;
			visibility.visible_w -= scrollbar_y_w;
		}
	}
	else if (mode == SCROLL_MODE_X_AUTO_Y_AUTO)
	{
		if (content_w > visibility.visible_w)
		{
			visibility.x_on = true;
			visibility.visible_h = available_h - scrollbar_x_h;
		}
		if (content_h > visibility.visible_h)
		{
			visibility.y_on = true;
			visibility.visible_w = available_w - scrollbar_y_w;
		}
		if (content_w > visibility.visible_w)
		{
			visibility.x_on = true;
			visibility.visible_h = available_h - scrollbar_x_h;
		}
	}
	return visibility;
}

// == TBScrollContainerRoot ===================================

void TBScrollContainerRoot::OnPaintChildren(const PaintProps &paint_props)
{
	// We only want clipping in one axis (the overflowing one) so we
	// don't damage any expanded skins on the other axis. Add some fluff.
	const int fluff = 100;
	TBScrollContainer *sc = static_cast<TBScrollContainer *>(GetParent());
	TBRect clip_rect = GetPaddingRect().Expand(sc->m_scrollbar_x.CanScrollNegative() ? 0 : fluff,
												sc->m_scrollbar_y.CanScrollNegative() ? 0 : fluff,
												sc->m_scrollbar_x.CanScrollPositive() ? 0 : fluff,
												sc->m_scrollbar_y.CanScrollPositive() ? 0 : fluff);

	TBRect old_clip_rect = g_renderer->SetClipRect(clip_rect, true);

	TB_IF_DEBUG_SETTING(LAYOUT_CLIPPING, g_renderer->DrawRect(clip_rect, TBColor(255, 0, 0, 200)));

	TBWidget::OnPaintChildren(paint_props);

	g_renderer->SetClipRect(old_clip_rect, false);
}

void TBScrollContainerRoot::GetChildTranslation(int &x, int &y) const
{
	TBScrollContainer *sc = static_cast<TBScrollContainer *>(GetParent());
	x = (int) -sc->m_scrollbar_x.GetValue();
	y = (int) -sc->m_scrollbar_y.GetValue();
}

// == TBScrollContainer =======================================

TBScrollContainer::TBScrollContainer()
	: m_adapt_to_content_size(false)
	, m_adapt_content_size(false)
	, m_layout_is_invalid(false)
	, m_mode(SCROLL_MODE_X_Y)
{
	AddChild(&m_scrollbar_x);
	AddChild(&m_scrollbar_y);
	AddChild(&m_root);
	m_scrollbar_y.SetAxis(AXIS_Y);
}

TBScrollContainer::~TBScrollContainer()
{
	RemoveChild(&m_root);
	RemoveChild(&m_scrollbar_y);
	RemoveChild(&m_scrollbar_x);
}

void TBScrollContainer::SetAdaptToContentSize(bool adapt)
{
	if (m_adapt_to_content_size == adapt)
		return;
	InvalidateLayout(INVALIDATE_LAYOUT_RECURSIVE);
	m_adapt_to_content_size = adapt;
	InvalidateLayout(INVALIDATE_LAYOUT_RECURSIVE);
}

void TBScrollContainer::SetAdaptContentSize(bool adapt)
{
	if (m_adapt_content_size == adapt)
		return;
	m_adapt_content_size = adapt;
	InvalidateLayout(INVALIDATE_LAYOUT_TARGET_ONLY);
}

void TBScrollContainer::SetScrollMode(SCROLL_MODE mode)
{
	if (mode == m_mode)
		return;
	m_mode = mode;
	InvalidateLayout(INVALIDATE_LAYOUT_TARGET_ONLY);
}

void TBScrollContainer::ScrollTo(int x, int y)
{
	int old_x = m_scrollbar_x.GetValue();
	int old_y = m_scrollbar_y.GetValue();
	m_scrollbar_x.SetValue(x);
	m_scrollbar_y.SetValue(y);
	if (old_x != m_scrollbar_x.GetValue() ||
		old_y != m_scrollbar_y.GetValue())
		Invalidate();
}

TBWidget::ScrollInfo TBScrollContainer::GetScrollInfo()
{
	ScrollInfo info;
	info.min_x = static_cast<int>(m_scrollbar_x.GetMinValue());
	info.min_y = static_cast<int>(m_scrollbar_y.GetMinValue());
	info.max_x = static_cast<int>(m_scrollbar_x.GetMaxValue());
	info.max_y = static_cast<int>(m_scrollbar_y.GetMaxValue());
	info.x = m_scrollbar_x.GetValue();
	info.y = m_scrollbar_y.GetValue();
	return info;
}

void TBScrollContainer::InvalidateLayout(INVALIDATE_LAYOUT il)
{
	m_layout_is_invalid = true;
	// No recursion up to parents here unless we adapt to content size.
	if (m_adapt_to_content_size)
		TBWidget::InvalidateLayout(il);
}

TBRect TBScrollContainer::GetPaddingRect()
{
	int visible_w = GetRect().w;
	int visible_h = GetRect().h;
	if (m_scrollbar_x.GetOpacity())
		visible_h -= m_scrollbar_x.GetPreferredSize().pref_h;
	if (m_scrollbar_y.GetOpacity())
		visible_w -= m_scrollbar_y.GetPreferredSize().pref_w;
	return TBRect(0, 0, visible_w, visible_h);
}

PreferredSize TBScrollContainer::OnCalculatePreferredContentSize(const SizeConstraints &constraints)
{
	PreferredSize ps;
	ps.pref_w = ps.pref_h = 100;
	ps.min_w = ps.min_h = 50;
	if (m_adapt_to_content_size)
	{
		if (TBWidget *content_child = m_root.GetFirstChild())
		{
			ps = content_child->GetPreferredSize(constraints);
			int scrollbar_y_w = m_scrollbar_y.GetPreferredSize().pref_w;
			int scrollbar_x_h = m_scrollbar_x.GetPreferredSize().pref_h;

			ps.pref_w += scrollbar_y_w;
			ps.max_w += scrollbar_y_w;

			if (m_mode == SCROLL_MODE_X_Y ||
				m_mode == SCROLL_MODE_X_AUTO_Y_AUTO)
			{
				ps.pref_h += scrollbar_x_h;
				ps.max_h += scrollbar_x_h;
			}
		}
	}
	return ps;
}

bool TBScrollContainer::OnEvent(const TBWidgetEvent &ev)
{
	if (ev.type == EVENT_TYPE_CHANGED && (ev.target == &m_scrollbar_x || ev.target == &m_scrollbar_y))
	{
		Invalidate();
		OnScroll(m_scrollbar_x.GetValue(), m_scrollbar_y.GetValue());
		return true;
	}
	else if (ev.type == EVENT_TYPE_WHEEL && ev.modifierkeys == TB_MODIFIER_NONE)
	{
		double old_val_y = m_scrollbar_y.GetValueDouble();
		m_scrollbar_y.SetValueDouble(old_val_y + ev.delta_y * TBSystem::GetPixelsPerLine());
		double old_val_x = m_scrollbar_x.GetValueDouble();
		m_scrollbar_x.SetValueDouble(old_val_x + ev.delta_x * TBSystem::GetPixelsPerLine());
		return (m_scrollbar_x.GetValueDouble() != old_val_x || m_scrollbar_y.GetValueDouble() != old_val_y);
	}
	else if (ev.type == EVENT_TYPE_KEY_DOWN)
	{
		if (ev.special_key == TB_KEY_LEFT && m_scrollbar_x.CanScrollNegative())
			ScrollBySmooth(-TBSystem::GetPixelsPerLine(), 0);
		else if (ev.special_key == TB_KEY_RIGHT && m_scrollbar_x.CanScrollPositive())
			ScrollBySmooth(TBSystem::GetPixelsPerLine(), 0);
		else if (ev.special_key == TB_KEY_UP && m_scrollbar_y.CanScrollNegative())
			ScrollBySmooth(0, -TBSystem::GetPixelsPerLine());
		else if (ev.special_key == TB_KEY_DOWN && m_scrollbar_y.CanScrollPositive())
			ScrollBySmooth(0, TBSystem::GetPixelsPerLine());
		else if (ev.special_key == TB_KEY_PAGE_UP && m_scrollbar_y.CanScrollNegative())
			ScrollBySmooth(0, -GetPaddingRect().h);
		else if (ev.special_key == TB_KEY_PAGE_DOWN && m_scrollbar_y.CanScrollPositive())
			ScrollBySmooth(0, GetPaddingRect().h);
		else if (ev.special_key == TB_KEY_HOME)
			ScrollToSmooth(m_scrollbar_x.GetValue(), 0);
		else if (ev.special_key == TB_KEY_END)
			ScrollToSmooth(m_scrollbar_x.GetValue(), (int)m_scrollbar_y.GetMaxValue());
		else
			return false;
		return true;
	}
	return false;
}

void TBScrollContainer::OnProcess()
{
	SizeConstraints sc(GetRect().w, GetRect().h);
	ValidateLayout(sc);
}

void TBScrollContainer::ValidateLayout(const SizeConstraints &constraints)
{
	if (!m_layout_is_invalid)
		return;
	m_layout_is_invalid = false;

	// Layout scrollbars (no matter if they are visible or not)
	int scrollbar_y_w = m_scrollbar_y.GetPreferredSize().pref_w;
	int scrollbar_x_h = m_scrollbar_x.GetPreferredSize().pref_h;
	m_scrollbar_x.SetRect(TBRect(0, GetRect().h - scrollbar_x_h, GetRect().w - scrollbar_y_w, scrollbar_x_h));
	m_scrollbar_y.SetRect(TBRect(GetRect().w - scrollbar_y_w, 0, scrollbar_y_w, GetRect().h));

	if (TBWidget *content_child = m_root.GetFirstChild())
	{
		int horizontal_padding = TBScrollBarVisibility::IsAlwaysOnY(m_mode) ? scrollbar_y_w : 0;
		int vertical_padding = TBScrollBarVisibility::IsAlwaysOnX(m_mode) ? scrollbar_x_h : 0;

		SizeConstraints inner_sc = constraints.ConstrainByPadding(horizontal_padding, vertical_padding);

		PreferredSize ps = content_child->GetPreferredSize(inner_sc);

		TBScrollBarVisibility visibility = TBScrollBarVisibility::Solve(m_mode, ps.pref_w, ps.pref_h,
																		GetRect().w, GetRect().h,
																		scrollbar_x_h, scrollbar_y_w);
		m_scrollbar_x.SetOpacity(visibility.x_on ? 1.f : 0.f);
		m_scrollbar_y.SetOpacity(visibility.y_on ? 1.f : 0.f);
		m_root.SetRect(TBRect(0, 0, visibility.visible_w, visibility.visible_h));

		int content_w, content_h;
		if (m_adapt_content_size)
		{
			content_w = MAX(ps.pref_w, m_root.GetRect().w);
			content_h = MAX(ps.pref_h, m_root.GetRect().h);
			if (!visibility.x_on && m_root.GetRect().w < ps.pref_w)
				content_w = MIN(ps.pref_w, m_root.GetRect().w);
		}
		else
		{
			content_w = ps.pref_w;
			content_h = ps.pref_h;
		}

		content_child->SetRect(TBRect(0, 0, content_w, content_h));
		double limit_max_w = MAX(0, content_w - m_root.GetRect().w);
		double limit_max_h = MAX(0, content_h - m_root.GetRect().h);
		m_scrollbar_x.SetLimits(0, limit_max_w, m_root.GetRect().w);
		m_scrollbar_y.SetLimits(0, limit_max_h, m_root.GetRect().h);
	}
}

void TBScrollContainer::OnResized(int old_w, int old_h)
{
	InvalidateLayout(INVALIDATE_LAYOUT_TARGET_ONLY);
	SizeConstraints sc(GetRect().w, GetRect().h);
	ValidateLayout(sc);
}

}; // namespace tb
