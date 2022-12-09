// Test for AngelScript "format"
#include "Scripts/Utilities/Assert.as"

void TestStrFormat_Empty()
{
    Assert("".f() == "");
    Assert(format("") == "");
    Assert("test".f() == "test");
    Assert(format("test") == "test");
}

void TestStrFormat_Args()
{
    Assert("{}".f(0) == "0");
    Assert("{}{}".f(0, 1) == "01");
    Assert("{}{}{}".f(0, 1, 2) == "012");
    Assert("{}{}{}{}".f(0, 1, 2, 3) == "0123");
    Assert("{}{}{}{}{}".f(0, 1, 2, 3, 4) == "01234");
    Assert("{}{}{}{}{}{}".f(0, 1, 2, 3, 4, 5) == "012345");
    Assert("{}{}{}{}{}{}{}".f(0, 1, 2, 3, 4, 5, 6) == "0123456");
    Assert("{}{}{}{}{}{}{}{}".f(0, 1, 2, 3, 4, 5, 6, 7) == "01234567");
    Assert("{}{}{}{}{}{}{}{}{}".f(0, 1, 2, 3, 4, 5, 6, 7, 8) == "012345678");
    Assert("{}{}{}{}{}{}{}{}{}{}".f(0, 1, 2, 3, 4, 5, 6, 7, 8, 9) == "0123456789");

    Assert(format("{}", 0) == "0");
    Assert(format("{}{}", 0, 1) == "01");
    Assert(format("{}{}{}", 0, 1, 2) == "012");
    Assert(format("{}{}{}{}", 0, 1, 2, 3) == "0123");
    Assert(format("{}{}{}{}{}", 0, 1, 2, 3, 4) == "01234");
    Assert(format("{}{}{}{}{}{}", 0, 1, 2, 3, 4, 5) == "012345");
    Assert(format("{}{}{}{}{}{}{}", 0, 1, 2, 3, 4, 5, 6) == "0123456");
    Assert(format("{}{}{}{}{}{}{}{}", 0, 1, 2, 3, 4, 5, 6, 7) == "01234567");
    Assert(format("{}{}{}{}{}{}{}{}{}", 0, 1, 2, 3, 4, 5, 6, 7, 8) == "012345678");
    Assert(format("{}{}{}{}{}{}{}{}{}{}", 0, 1, 2, 3, 4, 5, 6, 7, 8, 9) == "0123456789");
}

void TestStrFormat_Text()
{
    Assert("test {} {}".f("test", 99) == "test test 99"); 
}

void TestStrFormat_NumArgs() {
    Assert("-{1}-{0}-".f(0, 1) == "-1-0-");
    Assert(format("-{1}-{0}-", 0, 1) == "-1-0-");
}

void TestStrFormat_ArgsFormat()
{
    Assert("{%04d}".f(1) == "0001");
    Assert("'{%10s}'".f("test") == "'      test'");
    Assert("0x{%08X}".f(0xba) == "0x000000BA");
}

void TestStrFormat_Locals(int arg)
{
    Assert("test={arg}".f() == "test=" + arg);

    int test = 99;
    Assert("test={test}".f() == "test=99");
    Assert("test={test},{}".f(test - 1) == "test=99,98");
    Assert("test=0x{test%02X}".f() == "test=0x63");
    String str = "test";
    Assert("test=[{str}]".f() == "test=[test]");
    Assert("test=[{str%-6s}]".f() == "test=[test  ]");
    Assert("test=[{str%.2s}]".f() == "test=[te]");
    Assert("test=[{str%6.2s}]".f() == "test=[    te]");
    Assert("test=[{str%-6.2s}]".f() == "test=[te    ]");
    double dbl = 1.2;
    Assert("-{dbl}-".f() == "-1.2-");
}

int globalVar = 101;

void TestStrFormat_Globals()
{
    int test = 99;
    Assert("test={test},{},{globalVar},{}".f(test - 1, 50) == "test=99,98,101,50");
}

class NoConversion
{
    int member = 15;
    String format(int v) const
    {
        return "m={member}, v={v}".f();
    }
};

class ImplConversion
{
    int member = 15;
    String opImplConv() const
    {
        return "ImplConversion " + member;
    }
    String format(int v) const
    {
        return "{this}, v={v}".f();
    }
};

class ToStringConversion
{
    int member = 15;
    String ToString() const
    {
        return "ToStringConversion " + member;
    }
    String format(int v) const
    {
        return "{this}, v={v}".f();
    }
};

class toStringConversion
{
    int member = 15;
    String toString() const
    {
        return "toStringConversion " + member;
    }
    String format(int v) const
    {
        return "{this}, v={v}".f();
    }
};

void TestStrFormat_Member()
{
    NoConversion obj;
    Assert(obj.format(10) == "m=15, v=10");
}

void TestStrFormat_ObjNoConversion()
{
    NoConversion obj;
    Assert("{obj%.20s}".f() == "[object NoConversion");
}

void TestStrFormat_ObjImplConversion()
{
    ImplConversion obj;
    Assert("{obj}".f() == "ImplConversion 15");
    Assert("{}".f(obj) == "ImplConversion 15");
    Assert("{}".f(@obj) == "ImplConversion 15");
    Assert(obj.format(10) == "ImplConversion 15, v=10");
}

void TestStrFormat_ObjToStringConversion()
{
    ToStringConversion obj;
    Assert("{obj}".f() == "ToStringConversion 15");
    Assert(obj.format(10) == "ToStringConversion 15, v=10");
}

void TestStrFormat_ObjtoStringConversion()
{
    toStringConversion @obj = toStringConversion();
    Assert("{obj}".f() == "toStringConversion 15");
    Assert(obj.format(10) == "toStringConversion 15, v=10");
}

void TestStrFormat_AppObjToStringConversion()
{
    Vector3 obj(1.5f, 1.5f, 1.5f);
    Assert("--{{{obj}}--".f() == "--{1.5 1.5 1.5}--");
    Assert("--[{}]--".f(Vector3(0.1f, 0.1f, 0.1f)) == "--[0.1 0.1 0.1]--");
}

String ToString(const Scene&in obj)
{
    return "Scene {}".f(obj.name);
}

void TestStrFormat_GlobalToStringConversion()
{
    Scene sc;
    sc.name = "Test";
    Assert("{sc}".f() == "Scene Test");
}

void Test_Str_Format()
{
    TestStrFormat_Empty();
    TestStrFormat_Args();
    TestStrFormat_Text();
    TestStrFormat_NumArgs();
    TestStrFormat_ArgsFormat();
    TestStrFormat_Locals(100);
    TestStrFormat_Globals();
    TestStrFormat_Member();
    TestStrFormat_ObjNoConversion();
    TestStrFormat_ObjImplConversion();
    TestStrFormat_ObjToStringConversion();
    TestStrFormat_ObjtoStringConversion();
    TestStrFormat_AppObjToStringConversion();
    TestStrFormat_GlobalToStringConversion();
}
