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

/// Physics world is about to be stepped.
URHO3D_EVENT(E_PHYSICSPRESTEP2D, PhysicsPreStep2D)
{
    URHO3D_PARAM(P_WORLD, World);                  // PhysicsWorld2D pointer
    URHO3D_PARAM(P_TIMESTEP, TimeStep);            // float
}

/// Physics world has been stepped.
URHO3D_EVENT(E_PHYSICSPOSTSTEP2D, PhysicsPostStep2D)
{
    URHO3D_PARAM(P_WORLD, World);                  // PhysicsWorld2D pointer
    URHO3D_PARAM(P_TIMESTEP, TimeStep);            // float
}

/// Physics begin contact.
URHO3D_EVENT(E_PHYSICSBEGINCONTACT2D, PhysicsBeginContact2D)
{
    URHO3D_PARAM(P_WORLD, World);                  // PhysicsWorld2D pointer
    URHO3D_PARAM(P_BODYA, BodyA);                  // RigidBody2D pointer
    URHO3D_PARAM(P_BODYB, BodyB);                  // RigidBody2D pointer
    URHO3D_PARAM(P_NODEA, NodeA);                  // Node pointer
    URHO3D_PARAM(P_NODEB, NodeB);                  // Node pointer
}

/// Physics end contact.
URHO3D_EVENT(E_PHYSICSENDCONTACT2D, PhysicsEndContact2D)
{
    URHO3D_PARAM(P_WORLD, World);                  // PhysicsWorld2D pointer
    URHO3D_PARAM(P_BODYA, BodyA);                  // RigidBody2D pointer
    URHO3D_PARAM(P_BODYB, BodyB);                  // RigidBody2D pointer
    URHO3D_PARAM(P_NODEA, NodeA);                  // Node pointer
    URHO3D_PARAM(P_NODEB, NodeB);                  // Node pointer
}

}
