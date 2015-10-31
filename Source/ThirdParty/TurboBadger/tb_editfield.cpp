// ================================================================================
// ==      This file is a part of Turbo Badger. (C) 2011-2014, Emil Segerås      ==
// ==                     See tb_core.h for more information.                    ==
// ================================================================================

#include "tb_editfield.h"
#include "tb_select.h"
#include "tb_menu_window.h"
#include "tb_system.h"
#include "tb_language.h"
#include "tb_style_edit_content.h"
#include "tb_widgets_reader.h"
#include "tb_widget_skin_condition_context.h"
#include "tb_font_renderer.h"
#include "tb_skin_util.h"

namespace tb {

const int CARET_BLINK_TIME = 500;
const int SELECTION_SCROLL_DELAY = 1000/30;

/** Get the delta that should be scrolled if dragging the pointer outside the range min-max */
int GetSelectionScrollSpeed(int pointerpos, int min, int max)
{
	int d = 0;
	if (pointerpos < min)
		d = pointerpos - min;
	else if (pointerpos > max)
		d = pointerpos - max;
	d *= d;
	d /= 40;
	return (pointerpos < min) ? -d : d;
}

TBEditField::TBEditField()
	: m_edit_type(EDIT_TYPE_TEXT)
	, m_adapt_to_content_size(false)
	, m_virtual_width(250)
{
	SetIsFocusable(true);
	SetWantLongClick(true);
	AddChild(&m_scrollbar_x);
	AddChild(&m_scrollbar_y);
	AddChild(&m_root);
	m_root.SetGravity(WIDGET_GRAVITY_ALL);
	m_scrollbar_x.SetGravity(WIDGET_GRAVITY_BOTTOM | WIDGET_GRAVITY_LEFT_RIGHT);
	m_scrollbar_y.SetGravity(WIDGET_GRAVITY_RIGHT | WIDGET_GRAVITY_TOP_BOTTOM);
	m_scrollbar_y.SetAxis(AXIS_Y);
	int scrollbar_y_w = m_scrollbar_y.GetPreferredSize().pref_w;
	int scrollbar_x_h = m_scrollbar_x.GetPreferredSize().pref_h;
	m_scrollbar_x.SetRect(TBRect(0, - scrollbar_x_h, - scrollbar_y_w, scrollbar_x_h));
	m_scrollbar_y.SetRect(TBRect(- scrollbar_y_w, 0, scrollbar_y_w, 0));
	m_scrollbar_x.SetOpacity(0);
	m_scrollbar_y.SetOpacity(0);

	SetSkinBg(TBIDC("TBEditField"), WIDGET_INVOKE_INFO_NO_CALLBACKS);
	m_style_edit.SetListener(this);

	m_root.SetRect(GetVisibleRect());

	m_placeholder.SetTextAlign(TB_TEXT_ALIGN_LEFT);

	m_content_factory.editfield = this;
	m_style_edit.SetContentFactory(&m_content_factory);
}

TBEditField::~TBEditField()
{
	RemoveChild(&m_root);
	RemoveChild(&m_scrollbar_y);
	RemoveChild(&m_scrollbar_x);
}

TBRect TBEditField::GetVisibleRect()
{
	TBRect rect = GetPaddingRect();
	if (m_scrollbar_y.GetOpacity())
		rect.w -= m_scrollbar_y.GetRect().w;
	if (m_scrollbar_x.GetOpacity())
		rect.h -= m_scrollbar_x.GetRect().h;
	return rect;
}

void TBEditField::UpdateScrollbarVisibility(bool multiline)
{
	bool enable_vertical = multiline && !m_adapt_to_content_size;
	m_scrollbar_y.SetOpacity(enable_vertical ? 1.f : 0.f);
	m_root.SetRect(GetVisibleRect());
}

void TBEditField::SetAdaptToContentSize(bool adapt)
{
	if (m_adapt_to_content_size == adapt)
		return;
	m_adapt_to_content_size = adapt;
	UpdateScrollbarVisibility(GetMultiline());
}

void TBEditField::SetVirtualWidth(int virtual_width)
{
	if (m_virtual_width == virtual_width)
		return;
	m_virtual_width = virtual_width;

	if (m_adapt_to_content_size && m_style_edit.packed.wrapping)
		InvalidateLayout(INVALIDATE_LAYOUT_RECURSIVE);
}

void TBEditField::SetMultiline(bool multiline)
{
	if (multiline == GetMultiline())
		return;
	UpdateScrollbarVisibility(multiline);
	m_style_edit.SetMultiline(multiline);
	SetWrapping(multiline);
	InvalidateSkinStates();
	TBWidget::Invalidate();
}

void TBEditField::SetStyling(bool styling)
{
	m_style_edit.SetStyling(styling);
}

void TBEditField::SetReadOnly(bool readonly)
{
	if (readonly == GetReadOnly())
		return;
	m_style_edit.SetReadOnly(readonly);
	InvalidateSkinStates();
	TBWidget::Invalidate();
}

void TBEditField::SetWrapping(bool wrapping)
{
	if (wrapping == GetWrapping())
		return;

	m_style_edit.SetWrapping(wrapping);

	// Invalidate the layout when the wrap mode change and we should adapt our size to it
	if (m_adapt_to_content_size)
		InvalidateLayout(INVALIDATE_LAYOUT_RECURSIVE);
}

void TBEditField::SetEditType(EDIT_TYPE type)
{
	if (m_edit_type == type)
		return;
	m_edit_type = type;
	m_style_edit.SetPassword(type == EDIT_TYPE_PASSWORD);
	InvalidateSkinStates();
	TBWidget::Invalidate();
}

bool TBEditField::GetCustomSkinCondition(const TBSkinCondition::CONDITION_INFO &info)
{
	if (info.custom_prop == TBIDC("edit-type"))
	{
		switch (m_edit_type)
		{
		case EDIT_TYPE_TEXT:		return info.value == TBIDC("text");
		case EDIT_TYPE_SEARCH:		return info.value == TBIDC("search");
		case EDIT_TYPE_PASSWORD:	return info.value == TBIDC("password");
		case EDIT_TYPE_EMAIL:		return info.value == TBIDC("email");
		case EDIT_TYPE_PHONE:		return info.value == TBIDC("phone");
		case EDIT_TYPE_URL:			return info.value == TBIDC("url");
		case EDIT_TYPE_NUMBER:		return info.value == TBIDC("number");
		};
	}
	else if (info.custom_prop == TBIDC("multiline"))
		return !((uint32)info.value) == !GetMultiline();
	else if (info.custom_prop == TBIDC("readonly"))
		return !((uint32)info.value) == !GetReadOnly();
	return false;
}

void TBEditField::ScrollTo(int x, int y)
{
	int old_x = m_scrollbar_x.GetValue();
	int old_y = m_scrollbar_y.GetValue();
	m_style_edit.SetScrollPos(x, y);
	if (old_x != m_scrollbar_x.GetValue() ||
		old_y != m_scrollbar_y.GetValue())
		TBWidget::Invalidate();
}

TBWidget::ScrollInfo TBEditField::GetScrollInfo()
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

bool TBEditField::OnEvent(const TBWidgetEvent &ev)
{
	if (ev.type == EVENT_TYPE_CHANGED && ev.target == &m_scrollbar_x)
	{
		m_style_edit.SetScrollPos(m_scrollbar_x.GetValue(), m_style_edit.scroll_y);
		OnScroll(m_scrollbar_x.GetValue(), m_style_edit.scroll_y);
		return true;
	}
	else if (ev.type == EVENT_TYPE_CHANGED && ev.target == &m_scrollbar_y)
	{
		m_style_edit.SetScrollPos(m_style_edit.scroll_x, m_scrollbar_y.GetValue());
		OnScroll(m_style_edit.scroll_x, m_scrollbar_y.GetValue());
		return true;
	}
	else if (ev.type == EVENT_TYPE_WHEEL && ev.modifierkeys == TB_MODIFIER_NONE)
	{
		int old_val = m_scrollbar_y.GetValue();
		m_scrollbar_y.SetValue(old_val + ev.delta_y * TBSystem::GetPixelsPerLine());
		return m_scrollbar_y.GetValue() != old_val;
	}
	else if (ev.type == EVENT_TYPE_POINTER_DOWN && ev.target == this)
	{
		TBRect padding_rect = GetPaddingRect();
		if (m_style_edit.MouseDown(
			TBPoint(ev.target_x - padding_rect.x, ev.target_y - padding_rect.y),
			1, ev.count, TB_MODIFIER_NONE, ev.touch))
		{
			// Post a message to start selection scroll
			PostMessageDelayed(TBIDC("selscroll"), nullptr, SELECTION_SCROLL_DELAY);
			return true;
		}
	}
	else if (ev.type == EVENT_TYPE_POINTER_MOVE && ev.target == this)
	{
		TBRect padding_rect = GetPaddingRect();
		return m_style_edit.MouseMove(TBPoint(ev.target_x - padding_rect.x, ev.target_y - padding_rect.y));
	}
	else if (ev.type == EVENT_TYPE_POINTER_UP && ev.target == this)
	{
		TBRect padding_rect = GetPaddingRect();
		return m_style_edit.MouseUp(TBPoint(ev.target_x - padding_rect.x, ev.target_y - padding_rect.y),
										1, TB_MODIFIER_NONE, ev.touch);
	}
	else if (ev.type == EVENT_TYPE_KEY_DOWN)
	{
		return m_style_edit.KeyDown(ev.key, ev.special_key, ev.modifierkeys);
	}
	else if (ev.type == EVENT_TYPE_KEY_UP)
	{
		return true;
	}
	else if ((ev.type == EVENT_TYPE_CLICK && ev.target->GetID() == TBIDC("popupmenu")) ||
			(ev.type == EVENT_TYPE_SHORTCUT))
	{
		if (ev.ref_id == TBIDC("cut") && !m_style_edit.packed.read_only)
			m_style_edit.Cut();
		else if (ev.ref_id == TBIDC("copy"))
			m_style_edit.Copy();
		else if (ev.ref_id == TBIDC("paste") && !m_style_edit.packed.read_only)
			m_style_edit.Paste();
		else if (ev.ref_id == TBIDC("delete") && !m_style_edit.packed.read_only)
			m_style_edit.Delete();
		else if (ev.ref_id == TBIDC("undo") && !m_style_edit.packed.read_only)
			m_style_edit.Undo();
		else if (ev.ref_id == TBIDC("redo") && !m_style_edit.packed.read_only)
			m_style_edit.Redo();
		else if (ev.ref_id == TBIDC("selectall"))
			m_style_edit.selection.SelectAll();
		else
			return false;
		return true;
	}
	else if (ev.type == EVENT_TYPE_CONTEXT_MENU && ev.target == this)
	{
		TBPoint pos_in_root(ev.target_x, ev.target_y);
		ev.target->ConvertToRoot(pos_in_root.x, pos_in_root.y);

		if (TBMenuWindow *menu = new TBMenuWindow(ev.target, TBIDC("popupmenu")))
		{
			TBGenericStringItemSource *source = menu->GetList()->GetDefaultSource();
			source->AddItem(new TBGenericStringItem(g_tb_lng->GetString(TBIDC("cut")), TBIDC("cut")));
			source->AddItem(new TBGenericStringItem(g_tb_lng->GetString(TBIDC("copy")), TBIDC("copy")));
			source->AddItem(new TBGenericStringItem(g_tb_lng->GetString(TBIDC("paste")), TBIDC("paste")));
			source->AddItem(new TBGenericStringItem(g_tb_lng->GetString(TBIDC("delete")), TBIDC("delete")));
			source->AddItem(new TBGenericStringItem("-"));
			source->AddItem(new TBGenericStringItem(g_tb_lng->GetString(TBIDC("selectall")), TBIDC("selectall")));
			menu->Show(source, TBPopupAlignment(pos_in_root), -1);
		}
		return true;
	}
	return false;
}

void TBEditField::OnPaint(const PaintProps &paint_props)
{
	TBRect visible_rect = GetVisibleRect();

	bool clip = m_scrollbar_x.CanScroll() || m_scrollbar_y.CanScroll();
	TBRect old_clip;
	if (clip)
		old_clip = g_renderer->SetClipRect(visible_rect, true);

	int trans_x = visible_rect.x, trans_y = visible_rect.y;
	g_renderer->Translate(trans_x, trans_y);

	// Draw text content, caret etc.
	visible_rect.x = visible_rect.y = 0;
	m_style_edit.Paint(visible_rect, GetCalculatedFontDescription(), paint_props.text_color);

	// If empty, draw placeholder text with some opacity.
	if (m_style_edit.IsEmpty())
	{
		float old_opacity = g_renderer->GetOpacity();
		g_renderer->SetOpacity(old_opacity * g_tb_skin->GetDefaultPlaceholderOpacity());
		TBRect placeholder_rect(visible_rect.x, visible_rect.y, visible_rect.w, GetFont()->GetHeight());
		m_placeholder.Paint(this, placeholder_rect, paint_props.text_color);
		g_renderer->SetOpacity(old_opacity);
	}
	g_renderer->Translate(-trans_x, -trans_y);

	if (clip)
		g_renderer->SetClipRect(old_clip, false);
}

void TBEditField::OnPaintChildren(const PaintProps &paint_props)
{
	TBWidget::OnPaintChildren(paint_props);

	// Draw fadeout skin at the needed edges.
	DrawEdgeFadeout(GetVisibleRect(),
		TBIDC("TBEditField.fadeout_x"),
		TBIDC("TBEditField.fadeout_y"),
		m_scrollbar_x.GetValue(),
		m_scrollbar_y.GetValue(),
		(int)(m_scrollbar_x.GetMaxValue() - m_scrollbar_x.GetValueDouble()),
		(int)(m_scrollbar_y.GetMaxValue() - m_scrollbar_y.GetValueDouble()));
}

void TBEditField::OnAdded()
{
	m_style_edit.SetFont(GetCalculatedFontDescription());
}

void TBEditField::OnFontChanged()
{
	m_style_edit.SetFont(GetCalculatedFontDescription());
}

void TBEditField::OnFocusChanged(bool focused)
{
	m_style_edit.Focus(focused);
}

void TBEditField::OnResized(int old_w, int old_h)
{
	// Make the scrollbars move
	TBWidget::OnResized(old_w, old_h);

	TBRect visible_rect = GetVisibleRect();
	m_style_edit.SetLayoutSize(visible_rect.w, visible_rect.h, false);

	UpdateScrollbars();
}

PreferredSize TBEditField::OnCalculatePreferredContentSize(const SizeConstraints &constraints)
{
	int font_height = GetFont()->GetHeight();
	PreferredSize ps;
	if (m_adapt_to_content_size)
	{
		int old_layout_width = m_style_edit.layout_width;
		int old_layout_height = m_style_edit.layout_height;
		if (m_style_edit.packed.wrapping)
		{
			// If we have wrapping enabled, we have to set a virtual width and format the text
			// so we can get the actual content width with a constant result every time.
			// If the layouter does not respect our size constraints in the end, we may
			// get a completly different content height due to different wrapping.
			// To fix that, we need to layout in 2 passes.

			// A hacky fix is to do something we probably shouldn't: use the old layout width
			// as virtual width for the new.
			//int layout_width = old_layout_width > 0 ? MAX(old_layout_width, m_virtual_width) : m_virtual_width;
			int layout_width = m_virtual_width;
			if (constraints.available_w != SizeConstraints::NO_RESTRICTION)
			{
				layout_width = constraints.available_w;
				if (TBSkinElement *bg_skin = GetSkinBgElement())
					layout_width -= bg_skin->padding_left + bg_skin->padding_right;
			}

			m_style_edit.SetLayoutSize(layout_width, old_layout_height, true);
			ps.size_dependency = SIZE_DEP_HEIGHT_DEPEND_ON_WIDTH;
		}
		int width = m_style_edit.GetContentWidth();
		int height = m_style_edit.GetContentHeight();
		if (m_style_edit.packed.wrapping)
			m_style_edit.SetLayoutSize(old_layout_width, old_layout_height, true);
		height = MAX(height, font_height);

		ps.min_w = ps.pref_w /*= ps.max_w*/ = width; // should go with the hack above.
		//ps.min_w = ps.pref_w = ps.max_w = width;
		ps.min_h = ps.pref_h = ps.max_h = height;
	}
	else
	{
		ps.pref_h = ps.min_h = font_height;
		if (m_style_edit.packed.multiline_on)
		{
			ps.pref_w = font_height * 10;
			ps.pref_h = font_height * 5;
		}
		else
			ps.max_h = ps.pref_h;
	}
	return ps;
}

void TBEditField::OnMessageReceived(TBMessage *msg)
{
	if (msg->message == TBIDC("blink"))
	{
		m_style_edit.caret.on = !m_style_edit.caret.on;
		m_style_edit.caret.Invalidate();

		// Post another blink message so we blink again.
		PostMessageDelayed(TBIDC("blink"), nullptr, CARET_BLINK_TIME);
	}
	else if (msg->message == TBIDC("selscroll") && captured_widget == this)
	{
		// Get scroll speed from where mouse is relative to the padding rect.
		TBRect padding_rect = GetVisibleRect().Shrink(2, 2);
		int dx = GetSelectionScrollSpeed(pointer_move_widget_x, padding_rect.x, padding_rect.x + padding_rect.w);
		int dy = GetSelectionScrollSpeed(pointer_move_widget_y, padding_rect.y, padding_rect.y + padding_rect.h);
		m_scrollbar_x.SetValue(m_scrollbar_x.GetValue() + dx);
		m_scrollbar_y.SetValue(m_scrollbar_y.GetValue() + dy);

		// Handle mouse move at the new scroll position, so selection is updated
		if (dx || dy)
			m_style_edit.MouseMove(TBPoint(pointer_move_widget_x, pointer_move_widget_y));

		// Post another setscroll message so we continue scrolling if we still should.
		if (m_style_edit.select_state)
			PostMessageDelayed(TBIDC("selscroll"), nullptr, SELECTION_SCROLL_DELAY);
	}
}

void TBEditField::OnChange()
{
	// Invalidate the layout when the content change and we should adapt our size to it
	if (m_adapt_to_content_size)
		InvalidateLayout(INVALIDATE_LAYOUT_RECURSIVE);

	TBWidgetEvent ev(EVENT_TYPE_CHANGED);
	InvokeEvent(ev);
}

bool TBEditField::OnEnter()
{
	return false;
}

void TBEditField::Invalidate(const TBRect &rect)
{
	TBWidget::Invalidate();
}

void TBEditField::DrawString(int32 x, int32 y, TBFontFace *font, const TBColor &color, const char *str, int32 len)
{
	font->DrawString(x, y, color, str, len);
}

void TBEditField::DrawRect(const TBRect &rect, const TBColor &color)
{
	g_renderer->DrawRect(rect, color);
}

void TBEditField::DrawRectFill(const TBRect &rect, const TBColor &color)
{
	g_renderer->DrawRectFill(rect, color);
}

void TBEditField::DrawTextSelectionBg(const TBRect &rect)
{
	TBWidgetSkinConditionContext context(this);
	g_tb_skin->PaintSkin(rect, TBIDC("TBEditField.selection"), static_cast<SKIN_STATE>(GetAutoState()), context);
}

void TBEditField::DrawContentSelectionFg(const TBRect &rect)
{
	TBWidgetSkinConditionContext context(this);
	g_tb_skin->PaintSkin(rect, TBIDC("TBEditField.selection"), static_cast<SKIN_STATE>(GetAutoState()), context);
}

void TBEditField::DrawCaret(const TBRect &rect)
{
	if (GetIsFocused() && !m_style_edit.packed.read_only)
		DrawTextSelectionBg(rect);
}

void TBEditField::Scroll(int32 dx, int32 dy)
{
	TBWidget::Invalidate();
	m_scrollbar_x.SetValue(m_style_edit.scroll_x);
	m_scrollbar_y.SetValue(m_style_edit.scroll_y);
}

void TBEditField::UpdateScrollbars()
{
	int32 w = m_style_edit.layout_width;
	int32 h = m_style_edit.layout_height;
	m_scrollbar_x.SetLimits(0, m_style_edit.GetContentWidth() - w, w);
	m_scrollbar_y.SetLimits(0, m_style_edit.GetContentHeight() - h, h);
}

void TBEditField::CaretBlinkStart()
{
	// Post the delayed blink message if we don't already have one
	if (!GetMessageByID(TBIDC("blink")))
		PostMessageDelayed(TBIDC("blink"), nullptr, CARET_BLINK_TIME);
}

void TBEditField::CaretBlinkStop()
{
	// Remove the blink message if we have one
	if (TBMessage *msg = GetMessageByID(TBIDC("blink")))
		DeleteMessage(msg);
}

// == TBEditFieldScrollRoot =======================================================================

void TBEditFieldScrollRoot::OnPaintChildren(const PaintProps &paint_props)
{
	// Avoid setting clipping (can be expensive) if we have no children to paint anyway.
	if (!GetFirstChild())
		return;
	// Clip children
	TBRect old_clip_rect = g_renderer->SetClipRect(GetPaddingRect(), true);
	TBWidget::OnPaintChildren(paint_props);
	g_renderer->SetClipRect(old_clip_rect, false);
}

void TBEditFieldScrollRoot::GetChildTranslation(int &x, int &y) const
{
	TBEditField *edit_field = static_cast<TBEditField *>(GetParent());
	x = (int) -edit_field->GetStyleEdit()->scroll_x;
	y = (int) -edit_field->GetStyleEdit()->scroll_y;
}

WIDGET_HIT_STATUS TBEditFieldScrollRoot::GetHitStatus(int x, int y)
{
	// Return no hit on this widget, but maybe on any of the children.
	if (TBWidget::GetHitStatus(x, y) && GetWidgetAt(x, y, false))
		return WIDGET_HIT_STATUS_HIT;
	return WIDGET_HIT_STATUS_NO_HIT;
}

// == TBTextFragmentContentWidget =================================================================

class TBTextFragmentContentWidget : public TBTextFragmentContent
{
public:
	TBTextFragmentContentWidget(TBWidget *parent, TBWidget *widget);
	virtual ~TBTextFragmentContentWidget();

	virtual void UpdatePos(int x, int y);
	virtual int32 GetWidth(TBFontFace *font, TBTextFragment *fragment);
	virtual int32 GetHeight(TBFontFace *font, TBTextFragment *fragment);
	virtual int32 GetBaseline(TBFontFace *font, TBTextFragment *fragment);
private:
	TBWidget *m_widget;
};

TBTextFragmentContentWidget::TBTextFragmentContentWidget(TBWidget *parent, TBWidget *widget)
	: m_widget(widget)
{
	parent->GetContentRoot()->AddChild(widget);
}

TBTextFragmentContentWidget::~TBTextFragmentContentWidget()
{
	m_widget->GetParent()->RemoveChild(m_widget);
	delete m_widget;
}

void TBTextFragmentContentWidget::UpdatePos(int x, int y)
{
	m_widget->SetRect(TBRect(x, y, GetWidth(nullptr, nullptr), GetHeight(nullptr, nullptr)));
}

int32 TBTextFragmentContentWidget::GetWidth(TBFontFace *font, TBTextFragment *fragment)
{
	return m_widget->GetRect().w ? m_widget->GetRect().w : m_widget->GetPreferredSize().pref_w;
}

int32 TBTextFragmentContentWidget::GetHeight(TBFontFace *font, TBTextFragment *fragment)
{
	return m_widget->GetRect().h ? m_widget->GetRect().h : m_widget->GetPreferredSize().pref_h;
}

int32 TBTextFragmentContentWidget::GetBaseline(TBFontFace *font, TBTextFragment *fragment)
{
	int height = GetHeight(font, fragment);
	return (height + fragment->block->CalculateBaseline(font)) / 2;
}

// == TBEditFieldContentFactory ===================================================================

int TBEditFieldContentFactory::GetContent(const char *text)
{
	return TBTextFragmentContentFactory::GetContent(text);
}

TBTextFragmentContent *TBEditFieldContentFactory::CreateFragmentContent(const char *text, int text_len)
{
	if (strncmp(text, "<widget ", MIN(text_len, 8)) == 0)
	{
		// Create a wrapper for the generated widget.
		// Its size will adapt to the content.
		if (TBWidget *widget = new TBWidget())
		{
			if (TBTextFragmentContentWidget *cw = new TBTextFragmentContentWidget(editfield, widget))
			{
				g_widgets_reader->LoadData(widget, text + 8, text_len - 9);
				return cw;
			}
			delete widget;
		}
	}

	return TBTextFragmentContentFactory::CreateFragmentContent(text, text_len);
}

}; // namespace tb
