// ================================================================================
// ==      This file is a part of Turbo Badger. (C) 2011-2014, Emil Segerås      ==
// ==                     See tb_core.h for more information.                    ==
// ================================================================================

#include "tb_test.h"

#ifdef TB_UNIT_TESTING

using namespace tb;

TB_TEST_GROUP(tb_test)
{
	TB_TEST(single_test)
	{
		TB_PASS();
	}
}

TB_TEST_GROUP(tb_test_multiple_calls)
{
	int setup_calls;
	int test_calls;

	TB_TEST(Setup)
	{
		setup_calls++;
	}
	TB_TEST(test_1)
	{
		TB_VERIFY(setup_calls == 1);
		test_calls++;
	}
	TB_TEST(test_2)
	{
		TB_VERIFY(setup_calls == 2);
		test_calls++;
	}
	TB_TEST(Cleanup)
	{
		TB_VERIFY(test_calls > 0);
	}
}

#endif // TB_UNIT_TESTING
