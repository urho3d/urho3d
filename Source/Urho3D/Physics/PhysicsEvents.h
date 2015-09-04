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
EVENT(E_PHYSICSPRESTEP, PhysicsPreStep)
{
    PARAM(P_WORLD, World);                  // PhysicsWorld pointer
    PARAM(P_TIMESTEP, TimeStep);            // float
}

/// Physics world has been stepped.
EVENT(E_PHYSICSPOSTSTEP, PhysicsPostStep)
{
    PARAM(P_WORLD, World);                  // PhysicsWorld pointer
    PARAM(P_TIMESTEP, TimeStep);            // float
}

/// Physics collision started.
EVENT(E_PHYSICSCOLLISIONSTART, PhysicsCollisionStart)
{
    PARAM(P_WORLD, World);                  // PhysicsWorld pointer
    PARAM(P_NODEA, NodeA);                  // Node pointer
    PARAM(P_NODEB, NodeB);                  // Node pointer
    PARAM(P_BODYA, BodyA);                  // RigidBody pointer
    PARAM(P_BODYB, BodyB);                  // RigidBody pointer
    PARAM(P_TRIGGER, Trigger);              // bool
    PARAM(P_CONTACTS, Contacts);            // Buffer containing position (Vector3), normal (Vector3), distance (float), impulse (float) for each contact
}

/// Physics collision ongoing.
EVENT(E_PHYSICSCOLLISION, PhysicsCollision)
{
    PARAM(P_WORLD, World);                  // PhysicsWorld pointer
    PARAM(P_NODEA, NodeA);                  // Node pointer
    PARAM(P_NODEB, NodeB);                  // Node pointer
    PARAM(P_BODYA, BodyA);                  // RigidBody pointer
    PARAM(P_BODYB, BodyB);                  // RigidBody pointer
    PARAM(P_TRIGGER, Trigger);              // bool
    PARAM(P_CONTACTS, Contacts);            // Buffer containing position (Vector3), normal (Vector3), distance (float), impulse (float) for each contact
}

/// Physics collision ended.
EVENT(E_PHYSICSCOLLISIONEND, PhysicsCollisionEnd)
{
    PARAM(P_WORLD, World);                  // PhysicsWorld pointer
    PARAM(P_NODEA, NodeA);                  // Node pointer
    PARAM(P_NODEB, NodeB);                  // Node pointer
    PARAM(P_BODYA, BodyA);                  // RigidBody pointer
    PARAM(P_BODYB, BodyB);                  // RigidBody pointer
    PARAM(P_TRIGGER, Trigger);              // bool
}

/// Physics collision started (sent to the participating scene nodes.)
EVENT(E_NODECOLLISIONSTART, NodeCollisionStart)
{
    PARAM(P_BODY, Body);                    // RigidBody pointer
    PARAM(P_OTHERNODE, OtherNode);          // Node pointer
    PARAM(P_OTHERBODY, OtherBody);          // RigidBody pointer
    PARAM(P_TRIGGER, Trigger);              // bool
    PARAM(P_CONTACTS, Contacts);            // Buffer containing position (Vector3), normal (Vector3), distance (float), impulse (float) for each contact
}

/// Physics collision ongoing (sent to the participating scene nodes.)
EVENT(E_NODECOLLISION, NodeCollision)
{
    PARAM(P_BODY, Body);                    // RigidBody pointer
    PARAM(P_OTHERNODE, OtherNode);          // Node pointer
    PARAM(P_OTHERBODY, OtherBody);          // RigidBody pointer
    PARAM(P_TRIGGER, Trigger);              // bool
    PARAM(P_CONTACTS, Contacts);            // Buffer containing position (Vector3), normal (Vector3), distance (float), impulse (float) for each contact
}

/// Physics collision ended (sent to the participating scene nodes.)
EVENT(E_NODECOLLISIONEND, NodeCollisionEnd)
{
    PARAM(P_BODY, Body);                    // RigidBody pointer
    PARAM(P_OTHERNODE, OtherNode);          // Node pointer
    PARAM(P_OTHERBODY, OtherBody);          // RigidBody pointer
    PARAM(P_TRIGGER, Trigger);              // bool
}

}
