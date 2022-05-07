// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#include "../Precompiled.h"

#include "../Math/Vector2.h"

#include <cstdio>

#include "../DebugNew.h"

namespace Urho3D
{

const Vector2 Vector2::ZERO;
const Vector2 Vector2::LEFT(-1.0f, 0.0f);
const Vector2 Vector2::RIGHT(1.0f, 0.0f);
const Vector2 Vector2::UP(0.0f, 1.0f);
const Vector2 Vector2::DOWN(0.0f, -1.0f);
const Vector2 Vector2::ONE(1.0f, 1.0f);

const IntVector2 IntVector2::ZERO;
const IntVector2 IntVector2::LEFT(-1, 0);
const IntVector2 IntVector2::RIGHT(1, 0);
const IntVector2 IntVector2::UP(0, 1);
const IntVector2 IntVector2::DOWN(0, -1);
const IntVector2 IntVector2::ONE(1, 1);

String Vector2::ToString() const
{
    char tempBuffer[CONVERSION_BUFFER_LENGTH];
    sprintf(tempBuffer, "%g %g", x_, y_);
    return String(tempBuffer);
}

String IntVector2::ToString() const
{
    char tempBuffer[CONVERSION_BUFFER_LENGTH];
    sprintf(tempBuffer, "%d %d", x_, y_);
    return String(tempBuffer);
}

}
