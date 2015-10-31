// ================================================================================
// ==      This file is a part of Turbo Badger. (C) 2011-2014, Emil Segerås      ==
// ==                     See tb_core.h for more information.                    ==
// ================================================================================

#include "tb_test.h"
#include "tb_node_tree.h"

#ifdef TB_UNIT_TESTING

using namespace tb;

TB_TEST_GROUP(tb_parser)
{
	TBNode node;
	TB_TEST(Init)
	{
		TB_VERIFY(node.ReadFile("demo01/ui_resources/test_tb_parser.tb.txt"));

		//TB_VERIFY(node.ReadFile(TB_TEST_FILE("test_tb_parser.tb.txt")));
	}

	TB_TEST(strings)
	{
		TB_VERIFY_STR(node.GetValueString("strings>string1", ""), "A string");
		TB_VERIFY_STR(node.GetValueString("strings>string2", ""), "\"A string\"");
		TB_VERIFY_STR(node.GetValueString("strings>string3", ""), "\'A string\'");
		TB_VERIFY_STR(node.GetValueString("strings>string4", ""), "\"\'A string\'\"");
		TB_VERIFY_STR(node.GetValueString("strings>string5", ""), "Foo\nBar");
	}

	TB_TEST(strings_compact)
	{
		TB_VERIFY_STR(node.GetValueString("strings_compact>string1", ""), "");
		TB_VERIFY_STR(node.GetValueString("strings_compact>string2", ""), "A string");
		TB_VERIFY_STR(node.GetValueString("strings_compact>string3", ""), "A string");
		TB_VERIFY_STR(node.GetValueString("strings_compact>string4", ""), "'A string'");
		TB_VERIFY_STR(node.GetValueString("strings_compact>string5", ""), "\"A string\"");
		TB_VERIFY_STR(node.GetValueString("strings_compact>string6", ""), "\"A string\"");
		TB_VERIFY_STR(node.GetValueString("strings_compact>string7", ""), "\\");
		TB_VERIFY_STR(node.GetValueString("strings_compact>string8", ""), "\"");
		TB_VERIFY_STR(node.GetValueString("strings_compact>string9", ""), "\\\\\\\\");
		TB_VERIFY_STR(node.GetValueString("strings_compact>string10", ""), "\\\\\"");
		TB_VERIFY_STR(node.GetValueString("strings_compact>string11", ""), "\"\"\'\'");
		TB_VERIFY_STR(node.GetValueStringRaw("strings_compact>string12", ""), "@language_string_token");
		TB_VERIFY_STR(node.GetValueString("strings_compact>string13", ""), "#ffdd00");
	}

	TB_TEST(numbers)
	{
		TB_VERIFY(node.GetValueInt("numbers>integer1", 0) == 42);
		TB_VERIFY_FLOAT(node.GetValueFloat("numbers>float1", 0), 1.1);
		TB_VERIFY(node.GetValueInt("numbers>integer2", 0) == 42);
		TB_VERIFY_FLOAT(node.GetValueFloat("numbers>float2", 0), 1.1);
	}

	TB_TEST(numbers_compact)
	{
		TB_VERIFY(node.GetValueInt("numbers_compact>integer1", 0) == -10);
		TB_VERIFY(node.GetValueInt("numbers_compact>integer2", 0) == -10);
		TB_VERIFY_FLOAT(node.GetValueFloat("numbers_compact>float1", 0), 1.0);
		TB_VERIFY_FLOAT(node.GetValueFloat("numbers_compact>float2", 0), -1.0);
		TB_VERIFY_FLOAT(node.GetValueFloat("numbers_compact>float3", 0), -.2);
		TB_VERIFY_FLOAT(node.GetValueFloat("numbers_compact>float4", 0), -.2);
		TB_VERIFY_FLOAT(node.GetValueFloat("numbers_compact>float5", 0), 1.1);
		TB_VERIFY_FLOAT(node.GetValueFloat("numbers_compact>float6", 0), 1.1);
	}

	TB_TEST(numbers_with_unit)
	{
		TB_VERIFY(node.GetValueInt("numbers_with_unit>number1", 0) == 10);
		TB_VERIFY_STR(node.GetValueString("numbers_with_unit>number1", ""), "10px");
		TB_VERIFY(node.GetValueInt("numbers_with_unit>number2", 0) == -10);
		TB_VERIFY_STR(node.GetValueString("numbers_with_unit>number2", ""), "-10px");
		TB_VERIFY(node.GetValueInt("numbers_with_unit>number3", 0) == 10);
		TB_VERIFY_STR(node.GetValueString("numbers_with_unit>number3", ""), "10px");
		TB_VERIFY(node.GetValueInt("numbers_with_unit>number4", 0) == -10);
		TB_VERIFY_STR(node.GetValueString("numbers_with_unit>number4", ""), "-10px");
		TB_VERIFY_FLOAT(node.GetValueFloat("numbers_with_unit>number5", 0), -2.1);
		TB_VERIFY_STR(node.GetValueString("numbers_with_unit>number5", ""), "-2.1px");
		TB_VERIFY_FLOAT(node.GetValueFloat("numbers_with_unit>number6", 0), -.1);
		TB_VERIFY_STR(node.GetValueString("numbers_with_unit>number6", ""), "-.1px");
		TB_VERIFY_FLOAT(node.GetValueFloat("numbers_with_unit>number7", 0), 1.f);
		TB_VERIFY_STR(node.GetValueString("numbers_with_unit>number7", ""), "1px ");
	}

	TB_TEST(compact_with_children)
	{
		TB_VERIFY_STR(node.GetValueString("compact_with_children>string", ""), "A string");
		TB_VERIFY_STR(node.GetValueString("compact_with_children>string>child1", ""), "Child 1");
		TB_VERIFY_STR(node.GetValueString("compact_with_children>string>child2", ""), "Child 2");

		TB_VERIFY(node.GetValueInt("compact_with_children>integer", 0) == -10);
		TB_VERIFY(node.GetValueInt("compact_with_children>integer>child1", 0) == 1);
		TB_VERIFY(node.GetValueInt("compact_with_children>integer>child2", 0) == 2);

		TB_VERIFY_FLOAT(node.GetValueFloat("compact_with_children>float", 0), 1);
		TB_VERIFY_FLOAT(node.GetValueFloat("compact_with_children>float>child1", 0), 1);
		TB_VERIFY_FLOAT(node.GetValueFloat("compact_with_children>float>child2", 0), 2);
	}

	TB_TEST(compact_no_value)
	{
		TB_VERIFY_STR(node.GetValueString("compact_no_value>string", ""), "A string");
		TB_VERIFY(node.GetValueInt("compact_no_value>int", 0) == 42);
		TB_VERIFY_FLOAT(node.GetValueFloat("compact_no_value>float", 0), 3.14);
		TB_VERIFY_STR(node.GetValueString("compact_no_value>subgroup>string1", ""), "A string, with \"comma\"");
		TB_VERIFY_STR(node.GetValueString("compact_no_value>subgroup>string2", ""), "'Another string'");
		TB_VERIFY_STR(node.GetValueString("compact_no_value>subgroup>string3", ""), "And another string");
	}

	TB_TEST(arrays_numbers)
	{
		TBNode *arr_n = node.GetNode("arrays>numbers");
		TB_VERIFY(arr_n);
		TB_VERIFY(arr_n->GetValue().GetArrayLength() == 5);
		TBValueArray *arr = arr_n->GetValue().GetArray();
		TB_VERIFY(arr->GetValue(0)->GetInt() == 1);
		TB_VERIFY(arr->GetValue(1)->GetInt() == 2);
		TB_VERIFY_FLOAT(arr->GetValue(2)->GetFloat(), 0.5);
		TB_VERIFY_FLOAT(arr->GetValue(3)->GetFloat(), 1.0E-8);
		TB_VERIFY(arr->GetValue(4)->GetInt() == 1000000000);
	}

	TB_TEST(arrays_dimensions)
	{
		TBNode *arr_n = node.GetNode("arrays>dimensions");
		TB_VERIFY(arr_n);
		TB_VERIFY(arr_n->GetValue().GetArrayLength() == 2);
		TBValueArray *arr = arr_n->GetValue().GetArray();
		TB_VERIFY(arr->GetValue(0)->GetInt() == 1);
		TB_VERIFY(arr->GetValue(1)->GetInt() == 2);
	}

//FIX: Not supported yet
//	TB_TEST(arrays_strings)
//	{
//		TBNode *arr_n = node.GetNode("arrays>strings");
//		TB_VERIFY(arr_n);
//		TB_VERIFY(arr_n->GetValue().GetArrayLength() == 5);
//		TBValueArray *arr = arr_n->GetValue().GetArray();
//		TB_VERIFY_STR(arr->GetValue(0)->GetString(), "Foo");
//		TB_VERIFY_STR(arr->GetValue(1)->GetString(), "'Foo'");
//		TB_VERIFY_STR(arr->GetValue(2)->GetString(), "Foo");
//		TB_VERIFY_STR(arr->GetValue(3)->GetString(), "\"Foo\"");
//		TB_VERIFY_STR(arr->GetValue(4)->GetString(), "Foo 'bar'");
//	}
//
//	TB_TEST(arrays_mixed)
//	{
//		TBNode *arr_n = node.GetNode("arrays>mixed");
//		TB_VERIFY(arr_n);
//		TB_VERIFY(arr_n->GetValue().GetArrayLength() == 4);
//		TBValueArray *arr = arr_n->GetValue().GetArray();
//		TB_VERIFY_STR(arr->GetValue(0)->GetString(), "Foo");
//		TB_VERIFY(arr->GetValue(1)->GetInt() == 2);
//		TB_VERIFY_STR(arr->GetValue(2)->GetString(), "bar");
//		TB_VERIFY(arr->GetValue(3)->GetFloat() == 4.0f);
//	}

	TB_TEST(strings_multiline)
	{
		TB_VERIFY_STR(node.GetValueString("strings_multiline>string1", ""), "Line 1\nLine 2\nLine 3");
		TB_VERIFY_STR(node.GetValueString("strings_multiline>string2", ""), "abc");
		TB_VERIFY_STR(node.GetValueString("strings_multiline>string3", ""), "AB");
		TB_VERIFY_STR(node.GetValueString("strings_multiline>string4", ""), "Line 1\nLine 2\nLine 3\n");
		TB_VERIFY_STR(node.GetValueString("strings_multiline>subgroup>first", ""), "Foo");
		TB_VERIFY_STR(node.GetValueString("strings_multiline>subgroup>second", ""), "AB");
		TB_VERIFY_STR(node.GetValueString("strings_multiline>string5", ""), "The last string");
	}

	TB_TEST(comments_and_space)
	{
		TB_VERIFY(node.GetValueInt("comments_and_space>one", 0) == 1);
		TB_VERIFY(node.GetValueInt("comments_and_space>two", 0) == 2);
		TB_VERIFY(node.GetValueInt("comments_and_space>three", 0) == 3);
	}

	TB_TEST(include_file)
	{
		TB_VERIFY_STR(node.GetValueString("include_file>file1>something1", ""), "Chocolate");
		TB_VERIFY_STR(node.GetValueString("include_file>file1>something2", ""), "Cake");
		TB_VERIFY_STR(node.GetValueString("include_file>file2>something1", ""), "Chocolate");
		TB_VERIFY_STR(node.GetValueString("include_file>file2>something2", ""), "Cake");
	}

	TB_TEST(include_locally)
	{
		TB_VERIFY_STR(node.GetValueString("include_branch>test1>skin", ""), "DarkSkin");
		TB_VERIFY_STR(node.GetValueString("include_branch>test2>skin", ""), "LightSkin");
	}

	TB_TEST(conditions)
	{
		TB_VERIFY(node.GetValueInt("conditions>value", 0) == 42);
	}

	TB_TEST(local_ref)
	{
		TB_VERIFY_STR(node.GetValueString("defines_test>test1", ""), "#ffdd00");
		TB_VERIFY_STR(node.GetValueString("defines_test>test2", ""), "#ffdd00");
		TB_VERIFY_STR(node.GetValueString("defines_test>broken", ""), "@>defines>colors>broken");
		TB_VERIFY_STR(node.GetValueString("defines_test>cycle", ""), "@>defines_test>cycle");
	}

	// More coverage in test_tb_node_ref_tree.cpp...
}

#endif // TB_UNIT_TESTING
