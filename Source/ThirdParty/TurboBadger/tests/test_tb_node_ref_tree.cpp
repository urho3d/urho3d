// ================================================================================
// ==      This file is a part of Turbo Badger. (C) 2011-2014, Emil Segerås      ==
// ==                     See tb_core.h for more information.                    ==
// ================================================================================

#include "tb_test.h"
#include "tb_node_ref_tree.h"
#include "tb_widgets_reader.h"
#include "tb_layout.h"
#include "tb_editfield.h"

#ifdef TB_UNIT_TESTING

using namespace tb;

TB_TEST_GROUP(tb_node_ref_tree)
{
	class DataListener : public TBNodeRefTreeListener
	{
	public:
		TBStr changed_request;
		int changed_counter;
		DataListener() : changed_counter(0) {}
		virtual void OnDataChanged(TBNodeRefTree *dt, const char *request)
		{
			changed_request.Set(request);
			changed_counter++;
		}
	};

	TB_TEST(change_on_set)
	{
		TBNodeRefTree dt("r");
		DataListener dl;
		dt.AddListener(&dl);

		dt.SetValue("mainbar>size", TBValue("10mm", TBValue::SET_AS_STATIC));
		TB_VERIFY_STR(dl.changed_request, "mainbar>size");

		dt.SetValue("mainbar>axis", TBValue("x", TBValue::SET_AS_STATIC));
		TB_VERIFY_STR(dl.changed_request, "mainbar>axis");

		dt.SetValue("mainbar>visible", TBValue(42));
		TB_VERIFY_STR(dl.changed_request, "mainbar>visible");

		TB_VERIFY_STR(dt.GetValue("mainbar>size").GetString(), "10mm");
		TB_VERIFY_STR(dt.GetValue("mainbar>axis").GetString(), "x");
		TB_VERIFY(dt.GetValue("mainbar>visible").GetInt() == 42);

		TB_VERIFY(dl.changed_counter == 3);

		dt.RemoveListener(&dl);
	}

	TB_TEST(reference_value)
	{
		TBNodeRefTree dt("test_styles");
		dt.ReadData("FireButton\n"
					"	skin: 'FireButtonSkin'\n");

		TBWidget root;
		g_widgets_reader->LoadData(&root, "TBButton: id: 'fire', skin: '@test_styles>FireButton>skin'");

		TBWidget *button = root.GetWidgetByID(TBIDC("fire"));
		TB_VERIFY(button->GetSkinBg() == TBIDC("FireButtonSkin"));
	}

	TB_TEST(reference_value_recurse)
	{
		TBNodeRefTree dt1("test_foo");
		dt1.ReadData("foo_value: 42\n"
					 "foo_circular: '@test_bar>bar_circular'\n");
		TBNodeRefTree dt2("test_bar");
		dt2.ReadData("bar_value: '@test_foo>foo_value'\n"
					 "bar_circular: '@test_foo>foo_circular'\n"
					 "bar_circular2: '@test_bar>bar_circular'\n"
					 "bar_broken_node: '@test_foo>foo_broken_node'"
					 "bar_broken_tree: '@test_foo>foo_broken_tree'");

		TBWidget root;
		g_widgets_reader->LoadData(&root,
			"TBInlineSelect: id: 'select', value: '@test_bar>bar_value'\n"
			"TBButton: id: 'button_circular', text: '@test_bar>bar_circular'\n"
			"TBButton: id: 'button_broken_node', text: '@test_bar>bar_broken_node'\n"
			"TBButton: id: 'button_broken_tree', text: '@test_bad_tree>foo'\n");

		// Reference from resource to one tree to another tree.
		TBWidget *select = root.GetWidgetByID(TBIDC("select"));
		TB_VERIFY(select->GetValue() == 42);

		// Reference in a circular loop. Should not freeze.
		TBWidget *button_circular = root.GetWidgetByID(TBIDC("button_circular"));
		TB_VERIFY_STR(button_circular->GetText(), "@test_bar>bar_circular");

		// Reference in a circular loop. Should not freeze.
		TB_VERIFY(TBNodeRefTree::GetValueFromTree("@test_bar>bar_circular2").GetType() == TBValue::TYPE_NULL);

		// References tree is wrong
		TB_VERIFY(TBNodeRefTree::GetValueFromTree("@test_bad_tree>does_not_exist").GetType() == TBValue::TYPE_NULL);

		// Reference that is broken (has no matching node).
		TBWidget *button_broken1 = root.GetWidgetByID(TBIDC("button_broken_node"));
		TB_VERIFY_STR(button_broken1->GetText(), "@test_foo>foo_broken_node");

		// Reference that is broken (has no matching tree).
		TBWidget *button_broken2 = root.GetWidgetByID(TBIDC("button_broken_tree"));
		TB_VERIFY_STR(button_broken2->GetText(), "@test_bad_tree>foo");
	}

	TB_TEST(reference_include)
	{
		TBNodeRefTree dt("test_styles");
		dt.ReadData("VeryNice\n"
					"	skin: 'SpecialSkin'\n"
					"	text: 'hello'\n");

		TBWidget root;
		g_widgets_reader->LoadData(&root,	"TBEditField: id: 'edit'\n"
											"	@include @test_styles>VeryNice");
		TBEditField *edit = root.GetWidgetByIDAndType<TBEditField>(TBIDC("edit"));
		TB_VERIFY(edit->GetSkinBg() == TBIDC("SpecialSkin"));
		TB_VERIFY_STR(edit->GetText(), "hello");
	}

	TB_TEST(reference_local_include)
	{
		TBWidget root;
		g_widgets_reader->LoadData(&root,	"SomeDeclarations\n"
											"	skin: 'SpecialSkin'\n"
											"	text: 'hello'\n"
											"TBEditField: id: 'edit'\n"
											"	@include SomeDeclarations");
		TBEditField *edit = root.GetWidgetByIDAndType<TBEditField>(TBIDC("edit"));
		TB_VERIFY(edit->GetSkinBg() == TBIDC("SpecialSkin"));
		TB_VERIFY_STR(edit->GetText(), "hello");
	}

	TB_TEST(reference_condition)
	{
		TBNodeRefTree dt("test_settings");
		dt.ReadData("layout\n"
					"	landscape: 1\n");

		const char *layout_str =
					"TBLayout: id: 'layout'\n"
					"	distribution: 'available'\n"
					"	@if @test_settings>layout>landscape\n"
					"		axis: 'x'\n"
					"		spacing: 100px\n"
					"	@else\n"
					"		axis: 'y'\n"
					"		spacing: 200px\n"
					"	gravity: 'all'\n";

		TBWidget root1, root2;

		// Inflate & check
		g_widgets_reader->LoadData(&root1, layout_str);
		TBLayout *layout1 = root1.GetWidgetByIDAndType<TBLayout>(TBIDC("layout"));
		TB_VERIFY(layout1->GetAxis() == AXIS_X);
		TB_VERIFY(layout1->GetSpacing() == 100);
		TB_VERIFY(layout1->GetGravity() == WIDGET_GRAVITY_ALL);

		// Change data for condition
		dt.SetValue("layout>landscape", TBValue(0));

		// Inflate & check
		g_widgets_reader->LoadData(&root2, layout_str);
		TBLayout *layout2 = root2.GetWidgetByIDAndType<TBLayout>(TBIDC("layout"));
		TB_VERIFY(layout2->GetAxis() == AXIS_Y);
		TB_VERIFY(layout2->GetSpacing() == 200);
		TB_VERIFY(layout2->GetGravity() == WIDGET_GRAVITY_ALL);
	}

	TBNode *GetChildNodeFromIndex(TBNode *parent, int index)
	{
		TBNode *child = parent->GetFirstChild();
		while (child && index-- > 0)
			child = child->GetNext();
		return child;
	}

	TB_TEST(reference_condition_branch_insert_order)
	{
		const char *str =
					"A\n"
					"	B1\n"
					"		C1\n"
					"	@if 1\n"
					"		@if 1\n"
					"			B2\n"
					"		B3\n"
					"		B4\n"
					"	B5\n";
		TBNode node;
		node.ReadData(str);

		TBNode *a = GetChildNodeFromIndex(&node, 0);
		TB_VERIFY_STR(a->GetName(), "A");
		TB_VERIFY_STR(GetChildNodeFromIndex(a, 0)->GetName(), "B1");
		TB_VERIFY_STR(GetChildNodeFromIndex(GetChildNodeFromIndex(a, 0), 0)->GetName(), "C1");
		TB_VERIFY_STR(GetChildNodeFromIndex(a, 1)->GetName(), "B2");
		TB_VERIFY_STR(GetChildNodeFromIndex(a, 2)->GetName(), "B3");
		TB_VERIFY_STR(GetChildNodeFromIndex(a, 3)->GetName(), "B4");
		TB_VERIFY_STR(GetChildNodeFromIndex(a, 4)->GetName(), "B5");
	}
}

#endif // TB_UNIT_TESTING
