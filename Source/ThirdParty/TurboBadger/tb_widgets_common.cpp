// ================================================================================
// ==      This file is a part of Turbo Badger. (C) 2011-2014, Emil Segerås      ==
// ==                     See tb_core.h for more information.                    ==
// ================================================================================

#include "tb_widgets_common.h"
#include "tb_font_renderer.h"
#include "tb_widgets_listener.h"
#include "tb_system.h"
#include <assert.h>

namespace tb {

// == TBWidgetString =======================================

TBWidgetString::TBWidgetString()
	: m_text_align(TB_TEXT_ALIGN_CENTER)
{
}

int TBWidgetString::GetWidth(TBWidget *widget)
{
	return widget->GetFont()->GetStringWidth(m_text);
}

int TBWidgetString::GetHeight(TBWidget *widget)
{
	return widget->GetFont()->GetHeight();
}

void TBWidgetString::Paint(TBWidget *widget, const TBRect &rect, const TBColor &color)
{
	TBFontFace *font = widget->GetFont();
	int string_w = GetWidth(widget);

	int x = rect.x;
	if (m_text_align == TB_TEXT_ALIGN_RIGHT)
		x += rect.w - string_w;
	else if (m_text_align == TB_TEXT_ALIGN_CENTER)
		x += MAX(0, (rect.w - string_w) / 2);
	int y = rect.y + (rect.h - GetHeight(widget)) / 2;

	if (string_w <= rect.w)
		font->DrawString(x, y, color, m_text);
	else
	{
		// There's not enough room for the entire string
		// so cut it off and end with ellipsis (...)

		// const char *end = "…"; // 2026 HORIZONTAL ELLIPSIS
		// Some fonts seem to render ellipsis a lot uglier than three dots.
		const char *end = "...";

		int endw = font->GetStringWidth(end);
		int startw = 0;
		int startlen = 0;
		while (m_text.CStr()[startlen])
		{
			int new_startw = font->GetStringWidth(m_text, startlen);
			if (new_startw + endw > rect.w)
				break;
			startw = new_startw;
			startlen++;
		}
		startlen = MAX(0, startlen - 1);
		font->DrawString(x, y, color, m_text, startlen);
		font->DrawString(x + startw, y, color, end);
	}
}

// == TBTextField =======================================

/** This value on m_cached_text_width means it needs to be updated again. */
#define UPDATE_TEXT_WIDTH_CACHE -1

TBTextField::TBTextField()
	: m_cached_text_width(UPDATE_TEXT_WIDTH_CACHE)
	, m_squeezable(false)
{
	SetSkinBg(TBIDC("TBTextField"), WIDGET_INVOKE_INFO_NO_CALLBACKS);
}

bool TBTextField::SetText(const char *text)
{
	if (m_text.m_text.Equals(text))
		return true;
	m_cached_text_width = UPDATE_TEXT_WIDTH_CACHE;
	Invalidate();
	InvalidateLayout(INVALIDATE_LAYOUT_RECURSIVE);
	return m_text.SetText(text);
}

void TBTextField::SetSqueezable(bool squeezable)
{
	if (squeezable == m_squeezable)
		return;
	m_squeezable = squeezable;
	Invalidate();
	InvalidateLayout(INVALIDATE_LAYOUT_RECURSIVE);
}

PreferredSize TBTextField::OnCalculatePreferredContentSize(const SizeConstraints &constraints)
{
	PreferredSize ps;
	if (m_cached_text_width == UPDATE_TEXT_WIDTH_CACHE)
		m_cached_text_width = m_text.GetWidth(this);
	ps.pref_w = m_cached_text_width;
	ps.pref_h = ps.min_h = m_text.GetHeight(this);
	// If gravity pull both up and down, use default max_h (grow as much as possible).
	// Otherwise it makes sense to only accept one line height.
	if (!((GetGravity() & WIDGET_GRAVITY_TOP) && (GetGravity() & WIDGET_GRAVITY_BOTTOM)))
		ps.max_h = ps.pref_h;
	if (!m_squeezable)
		ps.min_w = ps.pref_w;
	return ps;
}

void TBTextField::OnFontChanged()
{
	m_cached_text_width = UPDATE_TEXT_WIDTH_CACHE;
	InvalidateLayout(INVALIDATE_LAYOUT_RECURSIVE);
}

void TBTextField::OnPaint(const PaintProps &paint_props)
{
	m_text.Paint(this, GetPaddingRect(), paint_props.text_color);
}

// == TBButton =======================================

const int auto_click_first_delay = 500;
const int auto_click_repeat_delay = 100;

TBButton::TBButton()
	: m_auto_repeat_click(false)
	, m_toggle_mode(false)
{
	SetIsFocusable(true);
	SetClickByKey(true);
	SetSkinBg(TBIDC("TBButton"), WIDGET_INVOKE_INFO_NO_CALLBACKS);
	AddChild(&m_layout);
	// Set the textfield gravity to all, even though it would display the same with default gravity.
	// This will make the buttons layout expand if there is space available, without forcing the parent
	// layout to grow to make the space available.
	m_textfield.SetGravity(WIDGET_GRAVITY_ALL);
	m_layout.AddChild(&m_textfield);
	m_layout.SetRect(GetPaddingRect());
	m_layout.SetGravity(WIDGET_GRAVITY_ALL);
	m_layout.SetPaintOverflowFadeout(false);
}

TBButton::~TBButton()
{
	m_layout.RemoveChild(&m_textfield);
	RemoveChild(&m_layout);
}

bool TBButton::SetText(const char *text)
{
	bool ret = m_textfield.SetText(text);
	UpdateTextFieldVisibility();
	return ret;
}

void TBButton::SetValue(int value)
{
	if (value == GetValue())
		return;
	SetState(WIDGET_STATE_PRESSED, value ? true : false);

	if (CanToggle())
	{
		// Invoke a changed event.
		TBWidgetEvent ev(EVENT_TYPE_CHANGED);
		InvokeEvent(ev);
	}

	if (value && GetGroupID())
		TBRadioCheckBox::UpdateGroupWidgets(this);
}

int TBButton::GetValue()
{
	return GetState(WIDGET_STATE_PRESSED);
}

void TBButton::OnCaptureChanged(bool captured)
{
	if (captured && m_auto_repeat_click)
		PostMessageDelayed(TBIDC("auto_click"), nullptr, auto_click_first_delay);
	else if (!captured)
	{
		if (TBMessage *msg = GetMessageByID(TBIDC("auto_click")))
			DeleteMessage(msg);
	}
}

void TBButton::OnSkinChanged()
{
	m_layout.SetRect(GetPaddingRect());
}

bool TBButton::OnEvent(const TBWidgetEvent &ev)
{
	if (CanToggle() && ev.type == EVENT_TYPE_CLICK && ev.target == this)
	{
		TBWidgetSafePointer this_widget(this);

		// Toggle the value, if it's not a grouped widget with value on.
		if (!(GetGroupID() && GetValue()))
			SetValue(!GetValue());

		if (!this_widget.Get())
			return true; // We got removed so we actually handled this event.

		// Intentionally don't return true for this event. We want it to continue propagating.
	}
	return TBWidget::OnEvent(ev);
}

void TBButton::OnMessageReceived(TBMessage *msg)
{
	if (msg->message == TBIDC("auto_click"))
	{
		assert(captured_widget == this);
		if (!cancel_click && GetHitStatus(pointer_move_widget_x, pointer_move_widget_y))
		{
			TBWidgetEvent ev(EVENT_TYPE_CLICK, pointer_move_widget_x, pointer_move_widget_y, true);
			captured_widget->InvokeEvent(ev);
		}
		if (auto_click_repeat_delay)
			PostMessageDelayed(TBIDC("auto_click"), nullptr, auto_click_repeat_delay);
	}
}

WIDGET_HIT_STATUS TBButton::GetHitStatus(int x, int y)
{
	// Never hit any of the children to the button. We always want to the button itself.
	return TBWidget::GetHitStatus(x, y) ? WIDGET_HIT_STATUS_HIT_NO_CHILDREN : WIDGET_HIT_STATUS_NO_HIT;
}

void TBButton::UpdateTextFieldVisibility()
{
	// Auto-collapse the textfield if the text is empty and there are other
	// widgets added apart from the textfield. This removes the extra spacing
	// added between the textfield and the other widget.
	bool collapse_textfield = m_textfield.IsEmpty() && m_layout.GetFirstChild() != m_layout.GetLastChild();
	m_textfield.SetVisibilility(collapse_textfield ? WIDGET_VISIBILITY_GONE : WIDGET_VISIBILITY_VISIBLE);
}

void TBButton::ButtonLayout::OnChildAdded(TBWidget *child)
{
	static_cast<TBButton*>(GetParent())->UpdateTextFieldVisibility();
}

void TBButton::ButtonLayout::OnChildRemove(TBWidget *child)
{
	static_cast<TBButton*>(GetParent())->UpdateTextFieldVisibility();
}

// == TBClickLabel ==========================================================================================

TBClickLabel::TBClickLabel()
{
	AddChild(&m_layout);
	m_layout.AddChild(&m_textfield);
	m_layout.SetRect(GetPaddingRect());
	m_layout.SetGravity(WIDGET_GRAVITY_ALL);
	m_layout.SetLayoutDistributionPosition(LAYOUT_DISTRIBUTION_POSITION_LEFT_TOP);
}

TBClickLabel::~TBClickLabel()
{
	m_layout.RemoveChild(&m_textfield);
	RemoveChild(&m_layout);
}

bool TBClickLabel::OnEvent(const TBWidgetEvent &ev)
{
	// Get a widget from the layout that isn't the textfield, or just bail out
	// if we only have the textfield.
	if (m_layout.GetFirstChild() == m_layout.GetLastChild())
		return false;
	TBWidget *click_target = (m_layout.GetFirstChild() == &m_textfield ? m_layout.GetLastChild() : m_layout.GetFirstChild());
	// Invoke the event on it, as if it was invoked on the target itself.
	if (click_target && ev.target != click_target)
	{
		// Focus the target if we clicked the label.
		if (ev.type == EVENT_TYPE_CLICK)
			click_target->SetFocus(WIDGET_FOCUS_REASON_POINTER);

		// Sync our pressed state with the click target. Special case for when we're just about to
		// lose it ourself (pointer is being released).
		bool pressed_state = (ev.target->GetAutoState() & WIDGET_STATE_PRESSED) ? true : false;
		if (ev.type == EVENT_TYPE_POINTER_UP || ev.type == EVENT_TYPE_CLICK)
			pressed_state = false;

		click_target->SetState(WIDGET_STATE_PRESSED, pressed_state);

		TBWidgetEvent target_ev(ev.type, ev.target_x - click_target->GetRect().x, ev.target_y - click_target->GetRect().y,
								ev.touch, ev.modifierkeys);
		return click_target->InvokeEvent(target_ev);
	}
	return false;
}

// == TBSkinImage =======================================

PreferredSize TBSkinImage::OnCalculatePreferredSize(const SizeConstraints &constraints)
{
	PreferredSize ps = TBWidget::OnCalculatePreferredSize(constraints);
	// FIX: Make it stretched proportionally if shrunk.
	ps.max_w = ps.pref_w;
	ps.max_h = ps.pref_h;
	return ps;
}

// == TBSeparator ===========================================

TBSeparator::TBSeparator()
{
	SetSkinBg(TBIDC("TBSeparator"), WIDGET_INVOKE_INFO_NO_CALLBACKS);
	SetState(WIDGET_STATE_DISABLED, true);
}

// == TBProgressSpinner =====================================

// FIX: Add spin_speed to skin!
// FIX: Make it post messages only if visible
const int spin_speed = 1000/30; ///< How fast should the spinner animation animate.

TBProgressSpinner::TBProgressSpinner()
	: m_value(0)
	, m_frame(0)
{
	SetSkinBg(TBIDC("TBProgressSpinner"), WIDGET_INVOKE_INFO_NO_CALLBACKS);
	m_skin_fg.Set(TBIDC("TBProgressSpinner.fg"));
}

void TBProgressSpinner::SetValue(int value)
{
	if (value == m_value)
		return;
	InvalidateSkinStates();
	assert(value >= 0); // If this happens, you probably have unballanced Begin/End calls.
	m_value = value;
	if (value > 0)
	{
		// Start animation
		if (!GetMessageByID(TBID(1)))
		{
			m_frame = 0;
			PostMessageDelayed(TBID(1), nullptr, spin_speed);
		}
	}
	else
	{
		// Stop animation
		if (TBMessage *msg = GetMessageByID(TBID(1)))
			DeleteMessage(msg);
	}
}

void TBProgressSpinner::OnPaint(const PaintProps &paint_props)
{
	if (IsRunning())
	{
		TBSkinElement *e = g_tb_skin->GetSkinElement(m_skin_fg);
		if (e && e->bitmap)
		{
			int size = e->bitmap->Height();
			int num_frames = e->bitmap->Width() / e->bitmap->Height();
			int current_frame = m_frame % num_frames;
			g_renderer->DrawBitmap(GetPaddingRect(), TBRect(current_frame * size, 0, size, size), e->bitmap);
		}
	}
}

void TBProgressSpinner::OnMessageReceived(TBMessage *msg)
{
	m_frame++;
	Invalidate();
	// Keep animation running
	PostMessageDelayed(TBID(1), nullptr, spin_speed);
}

// == TBRadioCheckBox =======================================

TBRadioCheckBox::TBRadioCheckBox()
	: m_value(0)
{
	SetIsFocusable(true);
	SetClickByKey(true);
}

//static
void TBRadioCheckBox::UpdateGroupWidgets(TBWidget *new_leader)
{
	assert(new_leader->GetValue() && new_leader->GetGroupID());

	// Find the group root widget.
	TBWidget *group = new_leader;
	while (group && !group->GetIsGroupRoot() && group->GetParent())
		group = group->GetParent();

	for (TBWidget *child = group; child; child = child->GetNextDeep(group))
		if (child != new_leader && child->GetGroupID() == new_leader->GetGroupID())
			child->SetValue(0);
}

void TBRadioCheckBox::SetValue(int value)
{
	if (m_value == value)
		return;
	m_value = value;

	SetState(WIDGET_STATE_SELECTED, value ? true : false);

	TBWidgetEvent ev(EVENT_TYPE_CHANGED);
	InvokeEvent(ev);

	if (value && GetGroupID())
		UpdateGroupWidgets(this);
}

PreferredSize TBRadioCheckBox::OnCalculatePreferredSize(const SizeConstraints &constraints)
{
	PreferredSize ps = TBWidget::OnCalculatePreferredSize(constraints);
	ps.min_w = ps.max_w = ps.pref_w;
	ps.min_h = ps.max_h = ps.pref_h;
	return ps;
}

bool TBRadioCheckBox::OnEvent(const TBWidgetEvent &ev)
{
	if (ev.target == this && ev.type == EVENT_TYPE_CLICK)
	{
		// Toggle the value, if it's not a grouped widget with value on.
		if (!(GetGroupID() && GetValue()))
		{
			SetValue(!GetValue());
		}
	}
	return false;
}

// == TBScrollBar =======================================

TBScrollBar::TBScrollBar()
	: m_axis(AXIS_Y) ///< Make SetAxis below always succeed and set the skin
	, m_value(0)
	, m_min(0)
	, m_max(1)
	, m_visible(1)
	, m_to_pixel_factor(0)
{
	SetAxis(AXIS_X);
	AddChild(&m_handle);
}

TBScrollBar::~TBScrollBar()
{
	RemoveChild(&m_handle);
}

void TBScrollBar::SetAxis(AXIS axis)
{
	if (axis == m_axis)
		return;
	m_axis = axis;
	if (axis == AXIS_X)
	{
		SetSkinBg(TBIDC("TBScrollBarBgX"), WIDGET_INVOKE_INFO_NO_CALLBACKS);
		m_handle.SetSkinBg(TBIDC("TBScrollBarFgX"), WIDGET_INVOKE_INFO_NO_CALLBACKS);
	}
	else
	{
		SetSkinBg(TBIDC("TBScrollBarBgY"), WIDGET_INVOKE_INFO_NO_CALLBACKS);
		m_handle.SetSkinBg(TBIDC("TBScrollBarFgY"), WIDGET_INVOKE_INFO_NO_CALLBACKS);
	}
	Invalidate();
}

void TBScrollBar::SetLimits(double min, double max, double visible)
{
	max = MAX(min, max);
	visible = MAX(visible, 0.0);
	if (min == m_min && max == m_max && m_visible == visible)
		return;
	m_min = min;
	m_max = max;
	m_visible = visible;
	SetValueDouble(m_value);

	// If we're currently dragging the scrollbar handle, convert the down point
	// to root and then back after the applying the new limit.
	// This prevents sudden jumps to unexpected positions when scrolling.
	if (captured_widget == &m_handle)
		m_handle.ConvertToRoot(pointer_down_widget_x, pointer_down_widget_y);

	UpdateHandle();

	if (captured_widget == &m_handle)
		m_handle.ConvertFromRoot(pointer_down_widget_x, pointer_down_widget_y);
}

void TBScrollBar::SetValueDouble(double value)
{
	value = CLAMP(value, m_min, m_max);
	if (value == m_value)
		return;
	m_value = value;

	UpdateHandle();
	TBWidgetEvent ev(EVENT_TYPE_CHANGED);
	InvokeEvent(ev);
}

bool TBScrollBar::OnEvent(const TBWidgetEvent &ev)
{
	if (ev.type == EVENT_TYPE_POINTER_MOVE && captured_widget == &m_handle)
	{
		if (m_to_pixel_factor > 0)
		{
			int dx = ev.target_x - pointer_down_widget_x;
			int dy = ev.target_y - pointer_down_widget_y;
			double delta_val = (m_axis == AXIS_X ? dx : dy) / m_to_pixel_factor;
			SetValueDouble(m_value + delta_val);
		}
		return true;
	}
	else if (ev.type == EVENT_TYPE_POINTER_MOVE && ev.target == this)
		return true;
	else if (ev.type == EVENT_TYPE_POINTER_DOWN && ev.target == this)
	{
		bool after_handle = (m_axis == AXIS_X ? ev.target_x > m_handle.GetRect().x : ev.target_y > m_handle.GetRect().y);
		SetValueDouble(m_value + (after_handle ? m_visible : -m_visible));
		return true;
	}
	else if (ev.type == EVENT_TYPE_WHEEL)
	{
		double old_val = m_value;
		SetValueDouble(m_value + ev.delta_y * TBSystem::GetPixelsPerLine());
		return m_value != old_val;
	}
	return false;
}

void TBScrollBar::UpdateHandle()
{
	// Calculate the mover size and position
	bool horizontal = m_axis == AXIS_X;
	int available_pixels = horizontal ? GetRect().w : GetRect().h;
	int min_thickness_pixels = MIN(GetRect().h, GetRect().w);

	int visible_pixels = available_pixels;

	if (m_max - m_min > 0 && m_visible > 0)
	{
		double visible_proportion = m_visible / (m_visible + m_max - m_min);
		visible_pixels = (int)(visible_proportion * available_pixels);

		// Limit the size of the indicator to the slider thickness so that it doesn't
		// become too tiny when the visible proportion is very small.
		visible_pixels = MAX(visible_pixels, min_thickness_pixels);

		m_to_pixel_factor = (double)(available_pixels - visible_pixels) / (m_max - m_min)/*+ 0.5*/;
	}
	else
	{
		m_to_pixel_factor = 0;

		// If we can't scroll anything, make the handle invisible
		visible_pixels = 0;
	}

	int pixel_pos = (int)(m_value * m_to_pixel_factor);

	TBRect rect;
	if (horizontal)
		rect.Set(pixel_pos, 0, visible_pixels, GetRect().h);
	else
		rect.Set(0, pixel_pos, GetRect().w, visible_pixels);

	m_handle.SetRect(rect);
}

void TBScrollBar::OnResized(int old_w, int old_h)
{
	UpdateHandle();
}

// == TBSlider ============================================

TBSlider::TBSlider()
	: m_axis(AXIS_Y) ///< Make SetAxis below always succeed and set the skin
	, m_value(0)
	, m_min(0)
	, m_max(1)
	, m_to_pixel_factor(0)
{
	SetIsFocusable(true);
	SetAxis(AXIS_X);
	AddChild(&m_handle);
}

TBSlider::~TBSlider()
{
	RemoveChild(&m_handle);
}

void TBSlider::SetAxis(AXIS axis)
{
	if (axis == m_axis)
		return;
	m_axis = axis;
	if (axis == AXIS_X)
	{
		SetSkinBg(TBIDC("TBSliderBgX"), WIDGET_INVOKE_INFO_NO_CALLBACKS);
		m_handle.SetSkinBg(TBIDC("TBSliderFgX"), WIDGET_INVOKE_INFO_NO_CALLBACKS);
	}
	else
	{
		SetSkinBg(TBIDC("TBSliderBgY"), WIDGET_INVOKE_INFO_NO_CALLBACKS);
		m_handle.SetSkinBg(TBIDC("TBSliderFgY"), WIDGET_INVOKE_INFO_NO_CALLBACKS);
	}
	Invalidate();
}

void TBSlider::SetLimits(double min, double max)
{
	min = MIN(min, max);
	if (min == m_min && max == m_max)
		return;
	m_min = min;
	m_max = max;
	SetValueDouble(m_value);
	UpdateHandle();
}

void TBSlider::SetValueDouble(double value)
{
	value = CLAMP(value, m_min, m_max);
	if (value == m_value)
		return;
	m_value = value;

	UpdateHandle();
	TBWidgetEvent ev(EVENT_TYPE_CHANGED);
	InvokeEvent(ev);
}

bool TBSlider::OnEvent(const TBWidgetEvent &ev)
{
	if (ev.type == EVENT_TYPE_POINTER_MOVE && captured_widget == &m_handle)
	{
		if (m_to_pixel_factor > 0)
		{
			int dx = ev.target_x - pointer_down_widget_x;
			int dy = ev.target_y - pointer_down_widget_y;
			double delta_val = (m_axis == AXIS_X ? dx : -dy) / m_to_pixel_factor;
			SetValueDouble(m_value + delta_val);
		}
		return true;
	}
	else if (ev.type == EVENT_TYPE_WHEEL)
	{
		double old_val = m_value;
		double step = (m_axis == AXIS_X ? GetSmallStep() : -GetSmallStep());
		SetValueDouble(m_value + step * ev.delta_y);
		return m_value != old_val;
	}
	else if (ev.type == EVENT_TYPE_KEY_DOWN)
	{
		double step = (m_axis == AXIS_X ? GetSmallStep() : -GetSmallStep());
		if (ev.special_key == TB_KEY_LEFT || ev.special_key == TB_KEY_UP)
			SetValueDouble(GetValueDouble() - step);
		else if (ev.special_key == TB_KEY_RIGHT || ev.special_key == TB_KEY_DOWN)
			SetValueDouble(GetValueDouble() + step);
		else
			return false;
		return true;
	}
	else if (ev.type == EVENT_TYPE_KEY_UP)
	{
		if (ev.special_key == TB_KEY_LEFT || ev.special_key == TB_KEY_UP ||
			ev.special_key == TB_KEY_RIGHT || ev.special_key == TB_KEY_DOWN)
			return true;
	}
	return false;
}

void TBSlider::UpdateHandle()
{
	// Calculate the handle position
	bool horizontal = m_axis == AXIS_X;
	int available_pixels = horizontal ? GetRect().w : GetRect().h;

	TBRect rect;
	if (m_max - m_min > 0)
	{
		PreferredSize ps = m_handle.GetPreferredSize();
		int handle_pixels = horizontal ? ps.pref_w : ps.pref_h;
		m_to_pixel_factor = (double)(available_pixels - handle_pixels) / (m_max - m_min)/*+ 0.5*/;

		int pixel_pos = (int)((m_value - m_min) * m_to_pixel_factor);

		if (horizontal)
			rect.Set(pixel_pos, (GetRect().h - ps.pref_h) / 2, ps.pref_w, ps.pref_h);
		else
			rect.Set((GetRect().w - ps.pref_w) / 2, GetRect().h - handle_pixels - pixel_pos, ps.pref_w, ps.pref_h);
	}
	else
		m_to_pixel_factor = 0;

	m_handle.SetRect(rect);
}

void TBSlider::OnResized(int old_w, int old_h)
{
	UpdateHandle();
}

// == TBContainer ===================================

TBContainer::TBContainer()
{
	SetSkinBg(TBIDC("TBContainer"), WIDGET_INVOKE_INFO_NO_CALLBACKS);
}

// == TBMover =======================================

TBMover::TBMover()
{
	SetSkinBg(TBIDC("TBMover"), WIDGET_INVOKE_INFO_NO_CALLBACKS);
}

bool TBMover::OnEvent(const TBWidgetEvent &ev)
{
	TBWidget *target = GetParent();
	if (!target)
		return false;
	if (ev.type == EVENT_TYPE_POINTER_MOVE && captured_widget == this)
	{
		int dx = ev.target_x - pointer_down_widget_x;
		int dy = ev.target_y - pointer_down_widget_y;
		TBRect rect = target->GetRect().Offset(dx, dy);
		if (target->GetParent())
		{
			// Apply limit.
			rect.x = CLAMP(rect.x, -pointer_down_widget_x, target->GetParent()->GetRect().w - pointer_down_widget_x);
			rect.y = CLAMP(rect.y, -pointer_down_widget_y, target->GetParent()->GetRect().h - pointer_down_widget_y);
		}
		target->SetRect(rect);
		return true;
	}
	return false;
}

// == TBResizer =======================================

TBResizer::TBResizer()
{
	SetSkinBg(TBIDC("TBResizer"), WIDGET_INVOKE_INFO_NO_CALLBACKS);
}

WIDGET_HIT_STATUS TBResizer::GetHitStatus(int x, int y)
{
	// Shave off some of the upper left diagonal half from the hit area.
	const int extra_hit_area = 3;
	if (x < GetRect().w - y - extra_hit_area)
		return WIDGET_HIT_STATUS_NO_HIT;
	return TBWidget::GetHitStatus(x, y);
}

bool TBResizer::OnEvent(const TBWidgetEvent &ev)
{
	TBWidget *target = GetParent();
	if (!target)
		return false;
	if (ev.type == EVENT_TYPE_POINTER_MOVE && captured_widget == this)
	{
		int dx = ev.target_x - pointer_down_widget_x;
		int dy = ev.target_y - pointer_down_widget_y;
		TBRect rect = target->GetRect();
		rect.w += dx;
		rect.h += dy;
		// Apply limit. We should not use minimum size since we can squeeze
		// the layout much more, and provide scroll/pan when smaller.
		rect.w = MAX(rect.w, 50);
		rect.h = MAX(rect.h, 50);
		target->SetRect(rect);
	}
	else
		return false;
	return true;
}

// == TBDimmer =======================================

TBDimmer::TBDimmer()
{
	SetSkinBg(TBIDC("TBDimmer"), WIDGET_INVOKE_INFO_NO_CALLBACKS);
	SetGravity(WIDGET_GRAVITY_ALL);
}

void TBDimmer::OnAdded()
{
	SetRect(TBRect(0, 0, GetParent()->GetRect().w, GetParent()->GetRect().h));
}

}; // namespace tb
