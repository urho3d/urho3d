//
// Copyright (c) 2008-2015 the Urho3D project.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

#pragma once

#include "../Core/Object.h"

namespace Urho3D
{

/// Variable timestep scene update.
EVENT(E_SCENEUPDATE, SceneUpdate)
{
    PARAM(P_SCENE, Scene);                  // Scene pointer
    PARAM(P_TIMESTEP, TimeStep);            // float
}

/// Scene subsystem update.
EVENT(E_SCENESUBSYSTEMUPDATE, SceneSubsystemUpdate)
{
    PARAM(P_SCENE, Scene);                  // Scene pointer
    PARAM(P_TIMESTEP, TimeStep);            // float
}

/// Scene transform smoothing update.
EVENT(E_UPDATESMOOTHING, UpdateSmoothing)
{
    PARAM(P_CONSTANT, Constant);            // float
    PARAM(P_SQUAREDSNAPTHRESHOLD, SquaredSnapThreshold);  // float
}

/// Scene drawable update finished. Custom animation (eg. IK) can be done at this point.
EVENT(E_SCENEDRAWABLEUPDATEFINISHED, SceneDrawableUpdateFinished)
{
    PARAM(P_SCENE, Scene);                  // Scene pointer
    PARAM(P_TIMESTEP, TimeStep);            // float
}

/// SmoothedTransform target position changed.
EVENT(E_TARGETPOSITION, TargetPositionChanged)
{
}

/// SmoothedTransform target position changed.
EVENT(E_TARGETROTATION, TargetRotationChanged)
{
}

/// Scene attribute animation update.
EVENT(E_ATTRIBUTEANIMATIONUPDATE, AttributeAnimationUpdate)
{
    PARAM(P_SCENE, Scene);                  // Scene pointer
    PARAM(P_TIMESTEP, TimeStep);            // float
}

/// Attribute animation added to object animation.
EVENT(E_ATTRIBUTEANIMATIONADDED, AttributeAnimationAdded)
{
    PARAM(P_OBJECTANIMATION, ObjectAnimation);               // Object animation pointer
    PARAM(P_ATTRIBUTEANIMATIONNAME, AttributeAnimationName); // String
}

/// Attribute animation removed from object animation.
EVENT(E_ATTRIBUTEANIMATIONREMOVED, AttributeAnimationRemoved)
{
    PARAM(P_OBJECTANIMATION, ObjectAnimation);               // Object animation pointer
    PARAM(P_ATTRIBUTEANIMATIONNAME, AttributeAnimationName); // String
}

/// Variable timestep scene post-update.
EVENT(E_SCENEPOSTUPDATE, ScenePostUpdate)
{
    PARAM(P_SCENE, Scene);                  // Scene pointer
    PARAM(P_TIMESTEP, TimeStep);            // float
}

/// Asynchronous scene loading progress.
EVENT(E_ASYNCLOADPROGRESS, AsyncLoadProgress)
{
    PARAM(P_SCENE, Scene);                  // Scene pointer
    PARAM(P_PROGRESS, Progress);            // float
    PARAM(P_LOADEDNODES, LoadedNodes);      // int
    PARAM(P_TOTALNODES, TotalNodes);        // int
    PARAM(P_LOADEDRESOURCES, LoadedResources); // int
    PARAM(P_TOTALRESOURCES, TotalResources);   // int
};

/// Asynchronous scene loading finished.
EVENT(E_ASYNCLOADFINISHED, AsyncLoadFinished)
{
    PARAM(P_SCENE, Scene);                  // Scene pointer
};

/// A child node has been added to a parent node.
EVENT(E_NODEADDED, NodeAdded)
{
    PARAM(P_SCENE, Scene);                  // Scene pointer
    PARAM(P_PARENT, Parent);                // Node pointer
    PARAM(P_NODE, Node);                    // Node pointer
}

/// A child node is about to be removed from a parent node.
EVENT(E_NODEREMOVED, NodeRemoved)
{
    PARAM(P_SCENE, Scene);                  // Scene pointer
    PARAM(P_PARENT, Parent);                // Node pointer
    PARAM(P_NODE, Node);                    // Node pointer
}

/// A component has been created to a node.
EVENT(E_COMPONENTADDED, ComponentAdded)
{
    PARAM(P_SCENE, Scene);                  // Scene pointer
    PARAM(P_NODE, Node);                    // Node pointer
    PARAM(P_COMPONENT, Component);          // Component pointer
}

/// A component is about to be removed from a node.
EVENT(E_COMPONENTREMOVED, ComponentRemoved)
{
    PARAM(P_SCENE, Scene);                  // Scene pointer
    PARAM(P_NODE, Node);                    // Node pointer
    PARAM(P_COMPONENT, Component);          // Component pointer
}

/// A node's name has changed.
EVENT(E_NODENAMECHANGED, NodeNameChanged)
{
    PARAM(P_SCENE, Scene);                  // Scene pointer
    PARAM(P_NODE, Node);                    // Node pointer
}

/// A node's enabled state has changed.
EVENT(E_NODEENABLEDCHANGED, NodeEnabledChanged)
{
    PARAM(P_SCENE, Scene);                  // Scene pointer
    PARAM(P_NODE, Node);                    // Node pointer
}

/// A component's enabled state has changed.
EVENT(E_COMPONENTENABLEDCHANGED, ComponentEnabledChanged)
{
    PARAM(P_SCENE, Scene);                  // Scene pointer
    PARAM(P_NODE, Node);                    // Node pointer
    PARAM(P_COMPONENT, Component);          // Component pointer
}

/// A serializable's temporary state has changed.
EVENT(E_TEMPORARYCHANGED, TemporaryChanged)
{
    PARAM(P_SERIALIZABLE, Serializable);    // Serializable pointer
}

}
