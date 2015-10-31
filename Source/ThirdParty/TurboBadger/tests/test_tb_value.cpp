// ================================================================================
// ==      This file is a part of Turbo Badger. (C) 2011-2014, Emil Segerås      ==
// ==                     See tb_core.h for more information.                    ==
// ================================================================================

#include "tb_test.h"
#include "tb_node_tree.h"

#ifdef TB_UNIT_TESTING

using namespace tb;

TB_TEST_GROUP(tb_value)
{
	TB_TEST(node_create_on_get)
	{
		TBNode node;
		TB_VERIFY(node.GetNode("foo>bar>funky") == nullptr);
		TB_VERIFY(node.GetNode("foo>bar>funky", TBNode::GET_MISS_POLICY_CREATE) != nullptr);
		TB_VERIFY(node.GetNode("foo>bar>funky") != nullptr);
	}

	// More coverage in test_tb_parser.cpp...
}

#endif // TB_UNIT_TESTING
