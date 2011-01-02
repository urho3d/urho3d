//
// Urho3D Engine
// Copyright (c) 2008-2011 Lasse Öörni
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

#ifndef PHYSICS_PHYSICSEVENTS_H
#define PHYSICS_PHYSICSEVENTS_H

#include "Event.h"

//! Physics world is about to be stepped
DEFINE_EVENT(EVENT_PHYSICSPRESTEP, PhysicsPreStep)
{
    EVENT_PARAM(P_WORLD, World);                // PhysicsWorld pointer
    EVENT_PARAM(P_SCENE, Scene);                // Scene pointer
    EVENT_PARAM(P_TIMESTEP, TimeStep);          // float
}

//! Physics world has been stepped
DEFINE_EVENT(EVENT_PHYSICSPOSTSTEP, PhysicsPostStep)
{
    EVENT_PARAM(P_WORLD, World);                // PhysicsWorld pointer
    EVENT_PARAM(P_SCENE, Scene);                // Scene pointer
    EVENT_PARAM(P_TIMESTEP, TimeStep);          // float
}

//! Physics collision occurred
DEFINE_EVENT(EVENT_PHYSICSCOLLISION, PhysicsCollision)
{
    EVENT_PARAM(P_WORLD, World);                // PhysicsWorld pointer
    EVENT_PARAM(P_SCENE, Scene);                // Scene pointer
    EVENT_PARAM(P_BODYA, BodyA);                // RigidBody pointer
    EVENT_PARAM(P_BODYB, BodyB);                // RigidBody pointer
    EVENT_PARAM(P_NEWCOLLISION, NewCollision);  // bool
    EVENT_PARAM(P_CONTACTS, Contacts);          // Buffer containing position, normal, depth, velocity for each contact
}

//! Physics collision occurred (sent to the participating Entity)
DEFINE_EVENT(EVENT_ENTITYCOLLISION, EntityCollision)
{
    EVENT_PARAM(P_BODY, Body);                  // RigidBody pointer
    EVENT_PARAM(P_OTHERBODY, OtherBody);        // RigidBody pointer
    EVENT_PARAM(P_OTHERENTITY, OtherEntity);    // Entity pointer
    EVENT_PARAM(P_NEWCOLLISION, NewCollision);  // bool
    EVENT_PARAM(P_CONTACTS, Contacts);          // Buffer containing position, normal, depth, velocity for each contact
}

#endif // PHYSICS_PHYSICSEVENTS_H
