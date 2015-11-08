// ================================================================================
// ==      This file is a part of Turbo Badger. (C) 2011-2014, Emil Segerås      ==
// ==                     See tb_core.h for more information.                    ==
// ================================================================================

#include "tb_test.h"
#include "tb_dimension.h"
#include "tb_core.h"

#ifdef TB_UNIT_TESTING

using namespace tb;

TB_TEST_GROUP(tb_dimension_converter)
{
	TBDimensionConverter dim_conv;

	TB_TEST(Init)
	{
		dim_conv.SetDPI(100, 200);
	}

	TB_TEST(set_from_string_unspecified)
	{
		int px = dim_conv.GetPxFromString("50", 0);
		TB_VERIFY(px == 50 * 2);
	}

	TB_TEST(set_from_string_px)
	{
		int px = dim_conv.GetPxFromString("50px", 0);
		TB_VERIFY(px == 50);
	}

	TB_TEST(set_from_string_dp)
	{
		int px = dim_conv.GetPxFromString("50dp", 0);
		TB_VERIFY(px == 50 * 2);
	}
}

#endif // TB_UNIT_TESTING
