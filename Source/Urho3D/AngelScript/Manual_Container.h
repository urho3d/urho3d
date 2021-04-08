//
// Copyright (c) 2008-2020 the Urho3D project.
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

#pragma once

namespace Urho3D
{

#define REGISTER_MEMBERS_MANUAL_PART_RefCounted() \
    /* void RefCounted::AddRef() | File: ../Container/RefCounted.h */ \
    engine->RegisterObjectBehaviour(className, asBEHAVE_ADDREF, "void f()", AS_METHODPR(T, AddRef, (), void), AS_CALL_THISCALL); \
    \
    /* void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h */ \
    engine->RegisterObjectBehaviour(className, asBEHAVE_RELEASE, "void f()", AS_METHODPR(T, ReleaseRef, (), void), AS_CALL_THISCALL)

}
