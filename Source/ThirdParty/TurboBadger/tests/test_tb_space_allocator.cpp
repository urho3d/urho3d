// ================================================================================
// ==      This file is a part of Turbo Badger. (C) 2011-2014, Emil Segerås      ==
// ==                     See tb_core.h for more information.                    ==
// ================================================================================

#include "tb_test.h"
#include "tb_bitmap_fragment.h"

#ifdef TB_UNIT_TESTING

using namespace tb;

TB_TEST_GROUP(tb_space_allocator)
{
	TB_TEST(free_when_full)
	{
		TBSpaceAllocator spa(30);
		TB_VERIFY(spa.HasSpace(30));
		TBSpaceAllocator::Space *s1 = spa.AllocSpace(10);
		TBSpaceAllocator::Space *s2 = spa.AllocSpace(10);
		TBSpaceAllocator::Space *s3 = spa.AllocSpace(10);
		TB_VERIFY(s1 && s2 && s3);
		TB_VERIFY(!spa.HasSpace(1));

		// Free middle
		spa.FreeSpace(s2);
		TB_VERIFY(spa.HasSpace(10));

		// Allocate middle (again)
		s2 = spa.AllocSpace(10);
		TB_VERIFY(!spa.HasSpace(10));

		// Free first
		spa.FreeSpace(s1);
		TB_VERIFY(spa.HasSpace(10));

		// Allocate first (again)
		s1 = spa.AllocSpace(10);
		TB_VERIFY(!spa.HasSpace(10));

		// Free last
		spa.FreeSpace(s3);
		TB_VERIFY(spa.HasSpace(10));

		// Allocate last (again)
		s3 = spa.AllocSpace(10);
		TB_VERIFY(!spa.HasSpace(10));
	}
	TB_TEST(free_all)
	{
		TBSpaceAllocator spa(30);
		{
			TBSpaceAllocator::Space *s = spa.AllocSpace(30);
			spa.FreeSpace(s);
			TB_VERIFY(spa.HasSpace(30));
		}

		// Free in order
		TBSpaceAllocator::Space *s1 = spa.AllocSpace(10);
		TBSpaceAllocator::Space *s2 = spa.AllocSpace(10);
		TBSpaceAllocator::Space *s3 = spa.AllocSpace(10);
		TB_VERIFY(s1 && s2 && s3);
		spa.FreeSpace(s1);
		spa.FreeSpace(s2);
		spa.FreeSpace(s3);
		TB_VERIFY(spa.HasSpace(30));

		// Free in backwards order
		s1 = spa.AllocSpace(10);
		s2 = spa.AllocSpace(10);
		s3 = spa.AllocSpace(10);
		TB_VERIFY(s1 && s2 && s3);
		spa.FreeSpace(s3);
		spa.FreeSpace(s2);
		spa.FreeSpace(s1);
		TB_VERIFY(spa.HasSpace(30));

		// Free middle first (in order)
		s1 = spa.AllocSpace(10);
		s2 = spa.AllocSpace(10);
		s3 = spa.AllocSpace(10);
		TB_VERIFY(s1 && s2 && s3);
		spa.FreeSpace(s2);
		spa.FreeSpace(s1);
		spa.FreeSpace(s3);
		TB_VERIFY(spa.HasSpace(30));

		// Free middle first (in backwards order)
		s1 = spa.AllocSpace(10);
		s2 = spa.AllocSpace(10);
		s3 = spa.AllocSpace(10);
		TB_VERIFY(s1 && s2 && s3);
		spa.FreeSpace(s2);
		spa.FreeSpace(s3);
		spa.FreeSpace(s1);
		TB_VERIFY(spa.HasSpace(30));
	}
	TB_TEST(free_scattered)
	{
		TBSpaceAllocator spa(50);
		TBSpaceAllocator::Space *s1 = spa.AllocSpace(10);
		TBSpaceAllocator::Space *s2 = spa.AllocSpace(10);
		TBSpaceAllocator::Space *s3 = spa.AllocSpace(10);
		TBSpaceAllocator::Space *s4 = spa.AllocSpace(10);
		TBSpaceAllocator::Space *s5 = spa.AllocSpace(10);
		TB_VERIFY(s1 && s2 && s3 && s4 && s5);

		// Free all middle space
		spa.FreeSpace(s2);
		spa.FreeSpace(s4);
		spa.FreeSpace(s3);
		TB_VERIFY(spa.HasSpace(30));

		s2 = spa.AllocSpace(10);
		s3 = spa.AllocSpace(10);
		s4 = spa.AllocSpace(10);

		// Free edges, then middle
		spa.FreeSpace(s1);
		spa.FreeSpace(s5);
		spa.FreeSpace(s3);
		TB_VERIFY(!spa.HasSpace(30)); // We should not have 30 of continous space.
		s1 = spa.AllocSpace(10);
		s3 = spa.AllocSpace(10);
		s5 = spa.AllocSpace(10);
		TB_VERIFY(s1 && s3 && s5); // We should have 3 * 10 spaces though.
	}
}

#endif // TB_UNIT_TESTING
