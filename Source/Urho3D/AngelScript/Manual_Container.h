// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

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
