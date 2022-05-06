// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#pragma once

#include "../Core/Object.h"

namespace Urho3D
{

URHO3D_EVENT(E_IKEFFECTORTARGETCHANGED, IKEffectorTargetChanged)
{
    URHO3D_PARAM(P_EFFECTORNODE, EffectorNode);      // (Node*) The effector node that has changed targets
    URHO3D_PARAM(P_TARGETNODE,   TargetNode);        // (Node*) The new target node. NOTE: Can be NULL (means no target)
}

}
