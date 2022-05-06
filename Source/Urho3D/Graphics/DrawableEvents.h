// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#pragma once

#include "../Core/Object.h"

namespace Urho3D
{

/// AnimatedModel bone hierarchy created.
URHO3D_EVENT(E_BONEHIERARCHYCREATED, BoneHierarchyCreated)
{
    URHO3D_PARAM(P_NODE, Node);                    // Node pointer
}

/// AnimatedModel animation trigger.
URHO3D_EVENT(E_ANIMATIONTRIGGER, AnimationTrigger)
{
    URHO3D_PARAM(P_NODE, Node);                    // Node pointer
    URHO3D_PARAM(P_ANIMATION, Animation);          // Animation pointer
    URHO3D_PARAM(P_NAME, Name);                    // String
    URHO3D_PARAM(P_TIME, Time);                    // Float
    URHO3D_PARAM(P_DATA, Data);                    // User-defined data type
}

/// AnimatedModel animation finished or looped.
URHO3D_EVENT(E_ANIMATIONFINISHED, AnimationFinished)
{
    URHO3D_PARAM(P_NODE, Node);                    // Node pointer
    URHO3D_PARAM(P_ANIMATION, Animation);          // Animation pointer
    URHO3D_PARAM(P_NAME, Name);                    // String
    URHO3D_PARAM(P_LOOPED, Looped);                // Bool
}

/// Particle effect finished.
URHO3D_EVENT(E_PARTICLEEFFECTFINISHED, ParticleEffectFinished)
{
    URHO3D_PARAM(P_NODE, Node);                    // Node pointer
    URHO3D_PARAM(P_EFFECT, Effect);                // ParticleEffect pointer
}

/// Terrain geometry created.
URHO3D_EVENT(E_TERRAINCREATED, TerrainCreated)
{
    URHO3D_PARAM(P_NODE, Node);                    // Node pointer
}

}
