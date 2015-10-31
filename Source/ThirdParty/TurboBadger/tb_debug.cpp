// ================================================================================
// ==      This file is a part of Turbo Badger. (C) 2011-2014, Emil Segerås      ==
// ==                     See tb_core.h for more information.                    ==
// ================================================================================

#include "tb_core.h"
#include "tb_widgets_reader.h"
#include "tb_window.h"
#include "tb_editfield.h"
#include "tb_font_renderer.h"
#include "tb_tempbuffer.h"
#include <stdio.h>

namespace tb {

#ifdef TB_RUNTIME_DEBUG_INFO

TBDebugInfo g_tb_debug;

TBDebugInfo::TBDebugInfo()
{
	memset(settings, 0, sizeof(int) * NUM_SETTINGS);
}

/** Window showing runtime debug settings. */
class DebugSettingsWindow : public TBWindow, public TBWidgetListener
{
public:
	TBEditField *output;

	TBOBJECT_SUBCLASS(DebugSettingsWindow, TBWindow);

	DebugSettingsWindow(TBWidget *root)
	{
		SetText("Debug settings");
		g_widgets_reader->LoadData(this,
			"TBLayout: axis: y, distribution: available, position: left\n"
			"	TBLayout: id: 'container', axis: y, size: available\n"
			"	TBTextField: text: 'Event output:'\n"
			"	TBEditField: id: 'output', gravity: all, multiline: 1, wrap: 0\n"
			"		lp: pref-height: 100dp");

		AddCheckbox(TBDebugInfo::LAYOUT_BOUNDS, "Layout bounds");
		AddCheckbox(TBDebugInfo::LAYOUT_CLIPPING, "Layout clipping");
		AddCheckbox(TBDebugInfo::LAYOUT_PS_DEBUGGING, "Layout size calculation");
		AddCheckbox(TBDebugInfo::RENDER_BATCHES, "Render batches");
		AddCheckbox(TBDebugInfo::RENDER_SKIN_BITMAP_FRAGMENTS, "Render skin bitmap fragments");
		AddCheckbox(TBDebugInfo::RENDER_FONT_BITMAP_FRAGMENTS, "Render font bitmap fragments");

		output = GetWidgetByIDAndType<TBEditField>(TBIDC("output"));

		TBRect bounds(0, 0, root->GetRect().w, root->GetRect().h);
		SetRect(GetResizeToFitContentRect().CenterIn(bounds).MoveIn(bounds).Clip(bounds));

		root->AddChild(this);

		TBWidgetListener::AddGlobalListener(this);
	}

	~DebugSettingsWindow()
	{
		TBWidgetListener::RemoveGlobalListener(this);
	}

	void AddCheckbox(TBDebugInfo::SETTING setting, const char *str)
	{
		TBCheckBox *check = new TBCheckBox();
		check->SetValue(g_tb_debug.settings[setting]);
		check->data.SetInt(setting);
		check->SetID(TBIDC("check"));

		TBClickLabel *label = new TBClickLabel();
		label->SetText(str);
		label->GetContentRoot()->AddChild(check, WIDGET_Z_BOTTOM);

		GetWidgetByID(TBIDC("container"))->AddChild(label);
	}

	virtual bool OnEvent(const TBWidgetEvent &ev)
	{
		if (ev.type == EVENT_TYPE_CLICK && ev.target->GetID() == TBIDC("check"))
		{
			// Update setting and invalidate
			g_tb_debug.settings[ev.target->data.GetInt()] = ev.target->GetValue();
			GetParentRoot()->Invalidate();
			return true;
		}
		return TBWindow::OnEvent(ev);
	}

	virtual void OnPaint(const PaintProps &paint_props)
	{
		// Draw stuff to the right of the debug window
		g_renderer->Translate(GetRect().w, 0);

		// Draw skin bitmap fragments
		if (TB_DEBUG_SETTING(RENDER_SKIN_BITMAP_FRAGMENTS))
			g_tb_skin->Debug();

		// Draw font glyph fragments (the font of the hovered widget)
		if (TB_DEBUG_SETTING(RENDER_FONT_BITMAP_FRAGMENTS))
		{
			TBWidget *widget = TBWidget::hovered_widget ? TBWidget::hovered_widget : TBWidget::focused_widget;
			g_font_manager->GetFontFace(widget ?
										widget->GetCalculatedFontDescription() :
										g_font_manager->GetDefaultFontDescription())->Debug();
		}

		g_renderer->Translate(-GetRect().w, 0);
	}

	TBStr GetIDString(const TBID &id)
	{
		TBStr str;
#ifdef TB_RUNTIME_DEBUG_INFO
		str.Append("\"");
		str.Append(id.debug_string);
		str.Append("\"");
#else
		str.SetFormatted("%u", (uint32)id);
#endif
		return str;
	}

	// TBWidgetListener
	virtual bool OnWidgetInvokeEvent(TBWidget *widget, const TBWidgetEvent &ev)
	{
		// Skip these events for now
		if (ev.IsPointerEvent())
			return false;

		// Always ignore activity in this window (or we might get endless recursion)
		if (TBWindow *window = widget->GetParentWindow())
			if (TBSafeCast<DebugSettingsWindow>(window))
				return false;

		TBTempBuffer buf;
		buf.AppendString(GetEventTypeStr(ev.type));
		buf.AppendString(" (");
		buf.AppendString(widget->GetClassName());
		buf.AppendString(")");

		buf.AppendString(" id: ");
		buf.AppendString(GetIDString(ev.target->GetID()));

		if (ev.ref_id)
		{
			buf.AppendString(", ref_id: ");
			buf.AppendString(GetIDString(ev.ref_id));
		}

		if (ev.type == EVENT_TYPE_CHANGED)
		{
			TBStr extra, text;
			if (ev.target->GetText(text) && text.Length() > 24)
				sprintf(text.CStr() + 20, "...");
			extra.SetFormatted(", value: %.2f (\"%s\")", ev.target->GetValueDouble(), text.CStr());
			buf.AppendString(extra);
		}
		buf.AppendString("\n");

		// Append the line to the output textfield
		TBStyleEdit *se = output->GetStyleEdit();
		se->selection.SelectNothing();
		se->AppendText(buf.GetData(), TB_ALL_TO_TERMINATION, true);
		se->ScrollIfNeeded(false, true);

		// Remove lines from the top if we exceed the height limit.
		const int height_limit = 2000;
		int current_height = se->GetContentHeight();
		if (current_height > height_limit)
		{
			se->caret.Place(TBPoint(0, current_height - height_limit));
			se->selection.SelectToCaret(se->blocks.GetFirst(), 0);
			se->Delete();
		}
		return false;
	}

	const char *GetEventTypeStr(EVENT_TYPE type) const
	{
		switch (type)
		{
		case EVENT_TYPE_CLICK:			return "CLICK";
		case EVENT_TYPE_LONG_CLICK:		return "LONG_CLICK";
		case EVENT_TYPE_POINTER_DOWN:	return "POINTER_DOWN";
		case EVENT_TYPE_POINTER_UP:		return "POINTER_UP";
		case EVENT_TYPE_POINTER_MOVE:	return "POINTER_MOVE";
		case EVENT_TYPE_WHEEL:			return "WHEEL";
		case EVENT_TYPE_CHANGED:		return "CHANGED";
		case EVENT_TYPE_KEY_DOWN:		return "KEY_DOWN";
		case EVENT_TYPE_KEY_UP:			return "KEY_UP";
		case EVENT_TYPE_SHORTCUT:		return "SHORT_CUT";
		case EVENT_TYPE_CONTEXT_MENU:	return "CONTEXT_MENU";
		default: return "[UNKNOWN]";
		};
	}
};

void ShowDebugInfoSettingsWindow(TBWidget *root)
{
	new DebugSettingsWindow(root);
}

#endif // TB_RUNTIME_DEBUG_INFO

}; // namespace tb
