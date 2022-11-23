// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#pragma once

#include "../Core/Object.h"

namespace Urho3D
{

/// Variable timestep scene update.
URHO3D_EVENT(E_SCENEUPDATE, SceneUpdate)
{
    URHO3D_PARAM(P_SCENE, Scene);                  // Scene pointer
    URHO3D_PARAM(P_TIMESTEP, TimeStep);            // float
}

/// Scene subsystem update.
URHO3D_EVENT(E_SCENESUBSYSTEMUPDATE, SceneSubsystemUpdate)
{
    URHO3D_PARAM(P_SCENE, Scene);                  // Scene pointer
    URHO3D_PARAM(P_TIMESTEP, TimeStep);            // float
}

/// Scene transform smoothing update.
URHO3D_EVENT(E_UPDATESMOOTHING, UpdateSmoothing)
{
    URHO3D_PARAM(P_CONSTANT, Constant);            // float
    URHO3D_PARAM(P_SQUAREDSNAPTHRESHOLD, SquaredSnapThreshold);  // float
}

/// Scene drawable update finished. Custom animation (eg. IK) can be done at this point.
URHO3D_EVENT(E_SCENEDRAWABLEUPDATEFINISHED, SceneDrawableUpdateFinished)
{
    URHO3D_PARAM(P_SCENE, Scene);                  // Scene pointer
    URHO3D_PARAM(P_TIMESTEP, TimeStep);            // float
}

/// SmoothedTransform target position changed.
URHO3D_EVENT(E_TARGETPOSITION, TargetPositionChanged)
{
}

/// SmoothedTransform target position changed.
URHO3D_EVENT(E_TARGETROTATION, TargetRotationChanged)
{
}

/// Scene attribute animation update.
URHO3D_EVENT(E_ATTRIBUTEANIMATIONUPDATE, AttributeAnimationUpdate)
{
    URHO3D_PARAM(P_SCENE, Scene);                  // Scene pointer
    URHO3D_PARAM(P_TIMESTEP, TimeStep);            // float
}

/// Attribute animation added to object animation.
URHO3D_EVENT(E_ATTRIBUTEANIMATIONADDED, AttributeAnimationAdded)
{
    URHO3D_PARAM(P_OBJECTANIMATION, ObjectAnimation);               // Object animation pointer
    URHO3D_PARAM(P_ATTRIBUTEANIMATIONNAME, AttributeAnimationName); // String
}

/// Attribute animation removed from object animation.
URHO3D_EVENT(E_ATTRIBUTEANIMATIONREMOVED, AttributeAnimationRemoved)
{
    URHO3D_PARAM(P_OBJECTANIMATION, ObjectAnimation);               // Object animation pointer
    URHO3D_PARAM(P_ATTRIBUTEANIMATIONNAME, AttributeAnimationName); // String
}

/// Variable timestep scene post-update.
URHO3D_EVENT(E_SCENEPOSTUPDATE, ScenePostUpdate)
{
    URHO3D_PARAM(P_SCENE, Scene);                  // Scene pointer
    URHO3D_PARAM(P_TIMESTEP, TimeStep);            // float
}

/// Asynchronous scene loading progress.
URHO3D_EVENT(E_ASYNCLOADPROGRESS, AsyncLoadProgress)
{
    URHO3D_PARAM(P_SCENE, Scene);                  // Scene pointer
    URHO3D_PARAM(P_PROGRESS, Progress);            // float
    URHO3D_PARAM(P_LOADEDNODES, LoadedNodes);      // int
    URHO3D_PARAM(P_TOTALNODES, TotalNodes);        // int
    URHO3D_PARAM(P_LOADEDRESOURCES, LoadedResources); // int
    URHO3D_PARAM(P_TOTALRESOURCES, TotalResources);   // int
}

/// Asynchronous scene loading finished.
URHO3D_EVENT(E_ASYNCLOADFINISHED, AsyncLoadFinished)
{
    URHO3D_PARAM(P_SCENE, Scene);                  // Scene pointer
}

/// A child node has been added to a parent node.
URHO3D_EVENT(E_NODEADDED, NodeAdded)
{
    URHO3D_PARAM(P_SCENE, Scene);                  // Scene pointer
    URHO3D_PARAM(P_PARENT, Parent);                // Node pointer
    URHO3D_PARAM(P_NODE, Node);                    // Node pointer
}

/// A child node is about to be removed from a parent node. Note that individual component removal events will not be sent.
URHO3D_EVENT(E_NODEREMOVED, NodeRemoved)
{
    URHO3D_PARAM(P_SCENE, Scene);                  // Scene pointer
    URHO3D_PARAM(P_PARENT, Parent);                // Node pointer
    URHO3D_PARAM(P_NODE, Node);                    // Node pointer
}

/// A component has been created to a node.
URHO3D_EVENT(E_COMPONENTADDED, ComponentAdded)
{
    URHO3D_PARAM(P_SCENE, Scene);                  // Scene pointer
    URHO3D_PARAM(P_NODE, Node);                    // Node pointer
    URHO3D_PARAM(P_COMPONENT, Component);          // Component pointer
}

/// A component is about to be removed from a node.
URHO3D_EVENT(E_COMPONENTREMOVED, ComponentRemoved)
{
    URHO3D_PARAM(P_SCENE, Scene);                  // Scene pointer
    URHO3D_PARAM(P_NODE, Node);                    // Node pointer
    URHO3D_PARAM(P_COMPONENT, Component);          // Component pointer
}

/// A node's name has changed.
URHO3D_EVENT(E_NODENAMECHANGED, NodeNameChanged)
{
    URHO3D_PARAM(P_SCENE, Scene);                  // Scene pointer
    URHO3D_PARAM(P_NODE, Node);                    // Node pointer
}

/// A node's enabled state has changed.
URHO3D_EVENT(E_NODEENABLEDCHANGED, NodeEnabledChanged)
{
    URHO3D_PARAM(P_SCENE, Scene);                  // Scene pointer
    URHO3D_PARAM(P_NODE, Node);                    // Node pointer
}

/// A node's tag has been added.
URHO3D_EVENT(E_NODETAGADDED, NodeTagAdded)
{
    URHO3D_PARAM(P_SCENE, Scene);                  // Scene pointer
    URHO3D_PARAM(P_NODE, Node);                    // Node pointer
    URHO3D_PARAM(P_TAG, Tag);                      // String tag
}

/// A node's tag has been removed.
URHO3D_EVENT(E_NODETAGREMOVED, NodeTagRemoved)
{
    URHO3D_PARAM(P_SCENE, Scene);                  // Scene pointer
    URHO3D_PARAM(P_NODE, Node);                    // Node pointer
    URHO3D_PARAM(P_TAG, Tag);                      // String tag
}

/// A component's enabled state has changed.
URHO3D_EVENT(E_COMPONENTENABLEDCHANGED, ComponentEnabledChanged)
{
    URHO3D_PARAM(P_SCENE, Scene);                  // Scene pointer
    URHO3D_PARAM(P_NODE, Node);                    // Node pointer
    URHO3D_PARAM(P_COMPONENT, Component);          // Component pointer
}

/// A serializable's temporary state has changed.
URHO3D_EVENT(E_TEMPORARYCHANGED, TemporaryChanged)
{
    URHO3D_PARAM(P_SERIALIZABLE, Serializable);    // Serializable pointer
}

/// A node (and its children and components) has been cloned.
URHO3D_EVENT(E_NODECLONED, NodeCloned)
{
    URHO3D_PARAM(P_SCENE, Scene);                  // Scene pointer
    URHO3D_PARAM(P_NODE, Node);                    // Node pointer
    URHO3D_PARAM(P_CLONENODE, CloneNode);          // Node pointer
}

/// A component has been cloned.
URHO3D_EVENT(E_COMPONENTCLONED, ComponentCloned)
{
    URHO3D_PARAM(P_SCENE, Scene);                  // Scene pointer
    URHO3D_PARAM(P_COMPONENT, Component);          // Component pointer
    URHO3D_PARAM(P_CLONECOMPONENT, CloneComponent); // Component pointer
}

/// A network attribute update from the server has been intercepted.
URHO3D_EVENT(E_INTERCEPTNETWORKUPDATE, InterceptNetworkUpdate)
{
    URHO3D_PARAM(P_SERIALIZABLE, Serializable);    // Serializable pointer
    URHO3D_PARAM(P_TIMESTAMP, TimeStamp);          // unsigned (0-255)
    URHO3D_PARAM(P_INDEX, Index);                  // unsigned
    URHO3D_PARAM(P_NAME, Name);                    // String
    URHO3D_PARAM(P_VALUE, Value);                  // Variant
}

}
