//
// Copyright (c) 2008-2022 the Urho3D project.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

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
}
