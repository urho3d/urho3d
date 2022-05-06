// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#include "../ForceAssert.h"

#include <Urho3D/Container/Str.h>

#include <Urho3D/DebugNew.h>

using namespace Urho3D;

void Test_Container_Str()
{
    {
        String str;
        assert(str.Length() == 0);
        assert(str.IsShort());

        str.Resize(9);
        assert(str.Length() == 9);
        assert(str.IsShort());

        str.Resize(1024);
        assert(str.Length() == 1024);
        assert(!str.IsShort());

        str = "0123456789";
        assert(str.Length() == 10);
        assert(!str.IsShort());

        str.Resize(5);
        assert(!str.IsShort());
        assert(str == "01234");

        str.Compact();
        assert(str.IsShort());
        assert(str == "01234");
        assert(str.Length() == 5);
    }

    {
        String str = String::Joined({"aa", "bb", "CC"}, "!");
        assert(str == "aa!bb!CC");
        assert(str.IsShort());
    }

    {
        String str = "bool Swap(T[]&)";
        str.Replace(10, 3, "Array<T>");
        assert(str == "bool Swap(Array<T>&)");
    }
}
