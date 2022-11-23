// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#include "../Precompiled.h"

#include "../Container/VectorBase.h"

#include "../DebugNew.h"

namespace Urho3D
{

u8* VectorBase::AllocateBuffer(i32 size)
{
    return new u8[size];
}

}
