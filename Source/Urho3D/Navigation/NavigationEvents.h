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

/// Complete rebuild of navigation mesh.
URHO3D_EVENT(E_NAVIGATION_MESH_REBUILT, NavigationMeshRebuilt)
{
    URHO3D_PARAM(P_NODE, Node); // Node pointer
    URHO3D_PARAM(P_MESH, Mesh); // NavigationMesh pointer
}

/// Partial bounding box rebuild of navigation mesh.
URHO3D_EVENT(E_NAVIGATION_AREA_REBUILT, NavigationAreaRebuilt)
{
    URHO3D_PARAM(P_NODE, Node); // Node pointer
    URHO3D_PARAM(P_MESH, Mesh); // NavigationMesh pointer
    URHO3D_PARAM(P_BOUNDSMIN, BoundsMin); // Vector3
    URHO3D_PARAM(P_BOUNDSMAX, BoundsMax); // Vector3
}

/// Crowd agent formation.
URHO3D_EVENT(E_CROWD_AGENT_FORMATION, CrowdAgentFormation)
{
    URHO3D_PARAM(P_NODE, Node); // Node pointer
    URHO3D_PARAM(P_CROWD_AGENT, CrowdAgent); // CrowdAgent pointer
    URHO3D_PARAM(P_INDEX, Index); // unsigned
    URHO3D_PARAM(P_SIZE, Size); // unsigned
    URHO3D_PARAM(P_POSITION, Position); // Vector3 [in/out]
}

/// Crowd agent formation specific to a node.
URHO3D_EVENT(E_CROWD_AGENT_NODE_FORMATION, CrowdAgentNodeFormation)
{
    URHO3D_PARAM(P_NODE, Node); // Node pointer
    URHO3D_PARAM(P_CROWD_AGENT, CrowdAgent); // CrowdAgent pointer
    URHO3D_PARAM(P_INDEX, Index); // unsigned
    URHO3D_PARAM(P_SIZE, Size); // unsigned
    URHO3D_PARAM(P_POSITION, Position); // Vector3 [in/out]
}

/// Crowd agent has been repositioned.
URHO3D_EVENT(E_CROWD_AGENT_REPOSITION, CrowdAgentReposition)
{
    URHO3D_PARAM(P_NODE, Node); // Node pointer
    URHO3D_PARAM(P_CROWD_AGENT, CrowdAgent); // CrowdAgent pointer
    URHO3D_PARAM(P_POSITION, Position); // Vector3
    URHO3D_PARAM(P_VELOCITY, Velocity); // Vector3
    URHO3D_PARAM(P_ARRIVED, Arrived); // bool
    URHO3D_PARAM(P_TIMESTEP, TimeStep); // float
}

/// Crowd agent has been repositioned, specific to a node
URHO3D_EVENT(E_CROWD_AGENT_NODE_REPOSITION, CrowdAgentNodeReposition)
{
    URHO3D_PARAM(P_NODE, Node); // Node pointer
    URHO3D_PARAM(P_CROWD_AGENT, CrowdAgent); // CrowdAgent pointer
    URHO3D_PARAM(P_POSITION, Position); // Vector3
    URHO3D_PARAM(P_VELOCITY, Velocity); // Vector3
    URHO3D_PARAM(P_ARRIVED, Arrived); // bool
    URHO3D_PARAM(P_TIMESTEP, TimeStep); // float
}

/// Crowd agent's internal state has become invalidated. This is a special case of CrowdAgentStateChanged event.
URHO3D_EVENT(E_CROWD_AGENT_FAILURE, CrowdAgentFailure)
{
    URHO3D_PARAM(P_NODE, Node); // Node pointer
    URHO3D_PARAM(P_CROWD_AGENT, CrowdAgent); // CrowdAgent pointer
    URHO3D_PARAM(P_POSITION, Position); // Vector3
    URHO3D_PARAM(P_VELOCITY, Velocity); // Vector3
    URHO3D_PARAM(P_CROWD_AGENT_STATE, CrowdAgentState); // int
    URHO3D_PARAM(P_CROWD_TARGET_STATE, CrowdTargetState); // int
}

/// Crowd agent's internal state has become invalidated. This is a special case of CrowdAgentStateChanged event.
URHO3D_EVENT(E_CROWD_AGENT_NODE_FAILURE, CrowdAgentNodeFailure)
{
    URHO3D_PARAM(P_NODE, Node); // Node pointer
    URHO3D_PARAM(P_CROWD_AGENT, CrowdAgent); // CrowdAgent pointer
    URHO3D_PARAM(P_POSITION, Position); // Vector3
    URHO3D_PARAM(P_VELOCITY, Velocity); // Vector3
    URHO3D_PARAM(P_CROWD_AGENT_STATE, CrowdAgentState); // int
    URHO3D_PARAM(P_CROWD_TARGET_STATE, CrowdTargetState); // int
}

/// Crowd agent's state has been changed.
URHO3D_EVENT(E_CROWD_AGENT_STATE_CHANGED, CrowdAgentStateChanged)
{
    URHO3D_PARAM(P_NODE, Node); // Node pointer
    URHO3D_PARAM(P_CROWD_AGENT, CrowdAgent); // CrowdAgent pointer
    URHO3D_PARAM(P_POSITION, Position); // Vector3
    URHO3D_PARAM(P_VELOCITY, Velocity); // Vector3
    URHO3D_PARAM(P_CROWD_AGENT_STATE, CrowdAgentState); // int
    URHO3D_PARAM(P_CROWD_TARGET_STATE, CrowdTargetState); // int
}

/// Crowd agent's state has been changed.
URHO3D_EVENT(E_CROWD_AGENT_NODE_STATE_CHANGED, CrowdAgentNodeStateChanged)
{
    URHO3D_PARAM(P_NODE, Node); // Node pointer
    URHO3D_PARAM(P_CROWD_AGENT, CrowdAgent); // CrowdAgent pointer
    URHO3D_PARAM(P_POSITION, Position); // Vector3
    URHO3D_PARAM(P_VELOCITY, Velocity); // Vector3
    URHO3D_PARAM(P_CROWD_AGENT_STATE, CrowdAgentState); // int
    URHO3D_PARAM(P_CROWD_TARGET_STATE, CrowdTargetState); // int
}

/// Addition of obstacle to dynamic navigation mesh.
URHO3D_EVENT(E_NAVIGATION_OBSTACLE_ADDED, NavigationObstacleAdded)
{
    URHO3D_PARAM(P_NODE, Node); // Node pointer
    URHO3D_PARAM(P_OBSTACLE, Obstacle); // Obstacle pointer
    URHO3D_PARAM(P_POSITION, Position); // Vector3
    URHO3D_PARAM(P_RADIUS, Radius); // float
    URHO3D_PARAM(P_HEIGHT, Height); // float
}

/// Removal of obstacle from dynamic navigation mesh.
URHO3D_EVENT(E_NAVIGATION_OBSTACLE_REMOVED, NavigationObstacleRemoved)
{
    URHO3D_PARAM(P_NODE, Node); // Node pointer
    URHO3D_PARAM(P_OBSTACLE, Obstacle); // Obstacle pointer
    URHO3D_PARAM(P_POSITION, Position); // Vector3
    URHO3D_PARAM(P_RADIUS, Radius); // float
    URHO3D_PARAM(P_HEIGHT, Height); // float
}

}
