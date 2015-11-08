// ================================================================================
// ==      This file is a part of Turbo Badger. (C) 2011-2014, Emil Segerås      ==
// ==                     See tb_core.h for more information.                    ==
// ================================================================================

#include "tb_test.h"
#include "tb_tempbuffer.h"

#ifdef TB_UNIT_TESTING

using namespace tb;

TB_TEST_GROUP(tb_tempbuffer)
{
	TB_TEST(append_path_1)
	{
		TBTempBuffer buf;
		buf.AppendPath("foo.txt");
		TB_VERIFY_STR(buf.GetData(), "./");
	}
	TB_TEST(append_path_2)
	{
		TBTempBuffer buf;
		buf.AppendPath("Path/subpath/foo.txt");
		TB_VERIFY_STR(buf.GetData(), "Path/subpath/");
	}
	TB_TEST(append_path_3)
	{
		TBTempBuffer buf;
		buf.AppendPath("C:\\test\\foo.txt");
		TB_VERIFY_STR(buf.GetData(), "C:\\test\\");
	}
	TB_TEST(append_string)
	{
		TBTempBuffer buf;
		buf.AppendString("xxxxxxxxxx");
		TB_VERIFY(buf.GetAppendPos() == 10);
		TB_VERIFY_STR(buf.GetData(), "xxxxxxxxxx");

		buf.SetAppendPos(0);
		buf.AppendString("Foo");
		buf.AppendString("Bar");
		TB_VERIFY_STR(buf.GetData(), "FooBar");
	}
}

#endif // TB_UNIT_TESTING
