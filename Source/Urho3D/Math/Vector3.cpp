// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#include "../Precompiled.h"

#include "../Math/Vector3.h"

#include <cstdio>

#include "../DebugNew.h"

namespace Urho3D
{

const Vector3 Vector3::ZERO;
const Vector3 Vector3::LEFT(-1.0f, 0.0f, 0.0f);
const Vector3 Vector3::RIGHT(1.0f, 0.0f, 0.0f);
const Vector3 Vector3::UP(0.0f, 1.0f, 0.0f);
const Vector3 Vector3::DOWN(0.0f, -1.0f, 0.0f);
const Vector3 Vector3::FORWARD(0.0f, 0.0f, 1.0f);
const Vector3 Vector3::BACK(0.0f, 0.0f, -1.0f);
const Vector3 Vector3::ONE(1.0f, 1.0f, 1.0f);

const IntVector3 IntVector3::ZERO;
const IntVector3 IntVector3::LEFT(-1, 0, 0);
const IntVector3 IntVector3::RIGHT(1, 0, 0);
const IntVector3 IntVector3::UP(0, 1, 0);
const IntVector3 IntVector3::DOWN(0, -1, 0);
const IntVector3 IntVector3::FORWARD(0, 0, 1);
const IntVector3 IntVector3::BACK(0, 0, -1);
const IntVector3 IntVector3::ONE(1, 1, 1);

String Vector3::ToString() const
{
    char tempBuffer[CONVERSION_BUFFER_LENGTH];
    sprintf(tempBuffer, "%g %g %g", x_, y_, z_);
    return String(tempBuffer);
}

String IntVector3::ToString() const
{
    char tempBuffer[CONVERSION_BUFFER_LENGTH];
    sprintf(tempBuffer, "%d %d %d", x_, y_, z_);
    return String(tempBuffer);
}

}
