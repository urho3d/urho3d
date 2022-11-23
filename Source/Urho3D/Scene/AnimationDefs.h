// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

/// \file

#pragma once

namespace Urho3D
{

/// Animation wrap mode.
enum WrapMode
{
    /// Loop mode.
    WM_LOOP = 0,
    /// Play once, when animation finished it will be removed.
    WM_ONCE,
    /// Clamp mode.
    WM_CLAMP,
};

}

