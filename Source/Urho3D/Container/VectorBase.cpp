// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#include "../Precompiled.h"

#include "../Container/VectorBase.h"

#include "../DebugNew.h"

namespace Urho3D
{

unsigned char* VectorBase::AllocateBuffer(unsigned size)
{
    return new unsigned char[size];
}

}
