// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#include "../Precompiled.h"

#include "../Math/Vector4.h"

#include <cstdio>

#include "../DebugNew.h"

namespace Urho3D
{

const Vector4 Vector4::ZERO;
const Vector4 Vector4::ONE(1.0f, 1.0f, 1.0f, 1.0f);

String Vector4::ToString() const
{
    char tempBuffer[CONVERSION_BUFFER_LENGTH];
    sprintf(tempBuffer, "%g %g %g %g", x_, y_, z_, w_);
    return String(tempBuffer);
}

}
