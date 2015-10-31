// ================================================================================
// ==      This file is a part of Turbo Badger. (C) 2011-2014, Emil Segerås      ==
// ==                     See tb_core.h for more information.                    ==
// ================================================================================

#include "tb_test.h"
#include "tb_geometry.h"

#ifdef TB_UNIT_TESTING

using namespace tb;

TB_TEST_GROUP(tb_geometry)
{
	TB_TEST(TBRegion_include)
	{
		TBRegion region;

		TB_VERIFY(region.IncludeRect(TBRect(10, 10, 100, 100)));
		TB_VERIFY(region.IncludeRect(TBRect(50, 50, 100, 100)));
		TB_VERIFY(region.GetNumRects() == 3);
		TB_VERIFY(region.GetRect(0).Equals(TBRect(10, 10, 100, 100)));
		TB_VERIFY(region.GetRect(1).Equals(TBRect(110, 50, 40, 60)));
		TB_VERIFY(region.GetRect(2).Equals(TBRect(50, 110, 100, 40)));
	}

	TB_TEST(TBRegion_include_adjecent_coalesce)
	{
		TBRegion region;

		TB_VERIFY(region.IncludeRect(TBRect(10, 10, 10, 10)));

		// extend right
		TB_VERIFY(region.IncludeRect(TBRect(20, 10, 10, 10)));
		TB_VERIFY(region.GetNumRects() == 1);
		TB_VERIFY(region.GetRect(0).Equals(TBRect(10, 10, 20, 10)));

		// extend bottom
		TB_VERIFY(region.IncludeRect(TBRect(10, 20, 20, 10)));
		TB_VERIFY(region.GetNumRects() == 1);
		TB_VERIFY(region.GetRect(0).Equals(TBRect(10, 10, 20, 20)));

		// extend left
		TB_VERIFY(region.IncludeRect(TBRect(0, 10, 10, 20)));
		TB_VERIFY(region.GetNumRects() == 1);
		TB_VERIFY(region.GetRect(0).Equals(TBRect(0, 10, 30, 20)));

		// extend top
		TB_VERIFY(region.IncludeRect(TBRect(0, 0, 30, 10)));
		TB_VERIFY(region.GetNumRects() == 1);
		TB_VERIFY(region.GetRect(0).Equals(TBRect(0, 0, 30, 30)));
	}

	TB_TEST(TBRegion_include_overlap_coalesce)
	{
		TBRegion region;

		TB_VERIFY(region.IncludeRect(TBRect(10, 10, 10, 10)));

		// extend to left and right
		TB_VERIFY(region.IncludeRect(TBRect(0, 10, 30, 10)));
		TB_VERIFY(region.GetNumRects() == 1);
		TB_VERIFY(region.GetRect(0).Equals(TBRect(0, 10, 30, 10)));
	}

	TB_TEST(TBRegion_include_overlap_multi_coalesce)
	{
		TBRegion region;

		TB_VERIFY(region.IncludeRect(TBRect(10, 10, 10, 10)));

		// extend in all directions at once
		TB_VERIFY(region.IncludeRect(TBRect(0, 0, 100, 100)));
		TB_VERIFY(region.GetNumRects() == 1);
		TB_VERIFY(region.GetRect(0).Equals(TBRect(0, 0, 100, 100)));
	}

	TB_TEST(TBRegion_exclude)
	{
		TBRegion region;

		TB_VERIFY(region.Set(TBRect(100, 100, 100, 100)));

		// Exclude in the middle (cut a 20x20 hole)
		TB_VERIFY(region.ExcludeRect(TBRect(140, 140, 20, 20)));
		TB_VERIFY(region.GetNumRects() == 4);
		TB_VERIFY(region.GetRect(0).Equals(TBRect(100, 100, 100, 40)));
		TB_VERIFY(region.GetRect(1).Equals(TBRect(100, 140, 40, 20)));
		TB_VERIFY(region.GetRect(2).Equals(TBRect(160, 140, 40, 20)));
		TB_VERIFY(region.GetRect(3).Equals(TBRect(100, 160, 100, 40)));

		// Exclude in the middle (cut a 40x40 hole)
		TB_VERIFY(region.ExcludeRect(TBRect(130, 130, 40, 40)));
		TB_VERIFY(region.GetNumRects() == 4);
		TB_VERIFY(region.GetRect(0).Equals(TBRect(100, 100, 100, 30)));
		TB_VERIFY(region.GetRect(1).Equals(TBRect(100, 130, 30, 40)));
		TB_VERIFY(region.GetRect(2).Equals(TBRect(170, 130, 30, 40)));
		TB_VERIFY(region.GetRect(3).Equals(TBRect(100, 170, 100, 30)));
	}
}

#endif // TB_UNIT_TESTING
