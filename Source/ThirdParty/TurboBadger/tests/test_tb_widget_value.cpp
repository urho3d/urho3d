// ================================================================================
// ==      This file is a part of Turbo Badger. (C) 2011-2014, Emil Segerås      ==
// ==                     See tb_core.h for more information.                    ==
// ================================================================================

#include "tb_test.h"
#include "tb_editfield.h"
#include "tb_widgets_common.h"
#include "tb_select.h"
#include "tb_inline_select.h"
#include "tb_widget_value.h"

#ifdef TB_UNIT_TESTING

using namespace tb;

TB_TEST_GROUP(tb_widget_value_text)
{
	TBWidgetValue widget_val(TBIDC("test value text"));
	TBWidget *a, *b, *c;

	TB_TEST(Init)
	{
		TB_VERIFY(a = new TBEditField);
		TB_VERIFY(b = new TBEditField);
		TB_VERIFY(c = new TBEditField);
	}

	TB_TEST(connect)
	{
		// Set the initial value, no widgets connected yet.
		widget_val.SetText("turbo badger");

		// Connecting widgets should give them the current value.
		a->Connect(&widget_val);
		b->Connect(&widget_val);
		c->Connect(&widget_val);

		TB_VERIFY_STR(a->GetText(), "turbo badger");
		TB_VERIFY_STR(b->GetText(), "turbo badger");
		TB_VERIFY_STR(c->GetText(), "turbo badger");
	}

	TB_TEST(change_value)
	{
		// Changing the value should change all widgets
		widget_val.SetText("Emil");

		TB_VERIFY_STR(a->GetText(), "Emil");
		TB_VERIFY_STR(b->GetText(), "Emil");
		TB_VERIFY_STR(c->GetText(), "Emil");
	}

	TB_TEST(change_widget)
	{
		// When a widget change, all the other widgets should also change.
		a->SetText("A");
		TB_VERIFY_STR(b->GetText(), "A");
		TB_VERIFY_STR(c->GetText(), "A");

		b->SetText("B");
		TB_VERIFY_STR(a->GetText(), "B");
		TB_VERIFY_STR(c->GetText(), "B");

		c->SetText("C");
		TB_VERIFY_STR(a->GetText(), "C");
		TB_VERIFY_STR(b->GetText(), "C");

		// The value itself should also have changed.
		TB_VERIFY_STR(widget_val.GetText(), "C");
	}

	TB_TEST(Shutdown)
	{
		delete a;
		delete b;
		delete c;
	}
}

TB_TEST_GROUP(tb_widget_value_int)
{
	TBWidgetValue widget_val(TBIDC("test value int"));
	TBSlider *a;
	TBScrollBar *b;
	TBInlineSelect *c;

	TB_TEST(Init)
	{
		TB_VERIFY(a = new TBSlider);
		TB_VERIFY(b = new TBScrollBar);
		TB_VERIFY(c = new TBInlineSelect);
		a->SetLimits(0, 1000);
		b->SetLimits(0, 1000, 1);
		c->SetLimits(0, 1000);
	}

	TB_TEST(connect)
	{
		// Set the initial value, no widgets connected yet.
		widget_val.SetInt(42);

		// Connecting widgets should give them the current value.
		a->Connect(&widget_val);
		b->Connect(&widget_val);
		c->Connect(&widget_val);

		TB_VERIFY(a->GetValue() == 42);
		TB_VERIFY(b->GetValue() == 42);
		TB_VERIFY(c->GetValue() == 42);
	}

	TB_TEST(change_value)
	{
		// Changing the value should change all widgets
		widget_val.SetInt(123);

		TB_VERIFY(a->GetValue() == 123);
		TB_VERIFY(b->GetValue() == 123);
		TB_VERIFY(c->GetValue() == 123);
	}

	TB_TEST(change_widget)
	{
		// When a widget change, all the other widgets should also change.
		a->SetValue(1);
		TB_VERIFY(b->GetValue() == 1);
		TB_VERIFY(c->GetValue() == 1);

		b->SetValue(2);
		TB_VERIFY(a->GetValue() == 2);
		TB_VERIFY(c->GetValue() == 2);

		c->SetValue(3);
		TB_VERIFY(a->GetValue() == 3);
		TB_VERIFY(b->GetValue() == 3);

		// The value itself should also have changed.
		TB_VERIFY(widget_val.GetInt() == 3);
	}

	TB_TEST(Shutdown)
	{
		delete a;
		delete b;
		delete c;
	}
}

TB_TEST_GROUP(tb_widget_value_listener)
{
	TBWidgetValue widget_val(TBIDC("test value check"));
	TBCheckBox *a, *b;

	/** Listen to changes and update val to any changed value. */
	class MyListener : public TBValueGroupListener
	{
	public:
		int change_counter;
		TBValue val;
		MyListener() : change_counter(0) {}
		virtual void OnValueChanged(const TBValueGroup *group, const TBWidgetValue *value)
		{
			val = value->GetValue();
			change_counter++;
		}
	};
	MyListener listener;

	TB_TEST(Init)
	{
		TB_VERIFY(a = new TBCheckBox);
		TB_VERIFY(b = new TBCheckBox);
	}

	TB_TEST(Setup) { g_value_group.AddListener(&listener); }

	TB_TEST(Cleanup) { g_value_group.RemoveListener(&listener); }

	TB_TEST(Shutdown)
	{
		delete a;
		delete b;
	}

	TB_TEST(change_with_no_widgets)
	{
		// Set the initial value, no widgets connected yet.
		widget_val.SetInt(1);

		// The listener should have registered the change
		TB_VERIFY(listener.val.GetInt() == 1);
		TB_VERIFY(listener.change_counter == 1);
	}

	TB_TEST(change_with_widgets)
	{
		a->Connect(&widget_val);
		b->Connect(&widget_val);

		// Change the value to 0
		widget_val.SetInt(0);

		// The listener should have registered the change, once.
		TB_VERIFY(listener.val.GetInt() == 0);
		TB_VERIFY(listener.change_counter == 2);
	}

	TB_TEST(change_widget)
	{
		// Change one of the widgets
		a->SetValue(1);

		// The listener should have registered the change, once.
		TB_VERIFY(listener.val.GetInt() == 1);
		TB_VERIFY(listener.change_counter == 3);
	}
}

#endif // TB_UNIT_TESTING
