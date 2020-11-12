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

// class RefCounted | File: ../Container/RefCounted.h
template <class T> void RegisterRefCounted(asIScriptEngine* engine, const char* className)
{
    engine->RegisterObjectType(className, 0, asOBJ_REF);

    // void RefCounted::AddRef()
    engine->RegisterObjectBehaviour(className, asBEHAVE_ADDREF, "void f()", asMETHODPR(T, AddRef, (), void), asCALL_THISCALL);

    // void RefCounted::ReleaseRef()
    engine->RegisterObjectBehaviour(className, asBEHAVE_RELEASE, "void f()", asMETHODPR(T, ReleaseRef, (), void), asCALL_THISCALL);

    // int RefCounted::Refs() const
    engine->RegisterObjectMethod(className, "int Refs() const", asMETHODPR(T, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "int get_refs() const", asMETHODPR(T, Refs, () const, int), asCALL_THISCALL);

    // int RefCounted::WeakRefs() const
    engine->RegisterObjectMethod(className, "int WeakRefs() const", asMETHODPR(T, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "int get_weakRefs() const", asMETHODPR(T, WeakRefs, () const, int), asCALL_THISCALL);
}

} // namespace Urho3D
