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

#pragma once

#include "Object.h"

/// Physics world is about to be stepped
EVENT(E_PHYSICSPRESTEP, PhysicsPreStep)
{
    PARAM(P_WORLD, World);                // PhysicsWorld pointer
    PARAM(P_TIMESTEP, TimeStep);          // float
}

/// Physics world has been stepped
EVENT(E_PHYSICSPOSTSTEP, PhysicsPostStep)
{
    PARAM(P_WORLD, World);                // PhysicsWorld pointer
    PARAM(P_TIMESTEP, TimeStep);          // float
}

/// Physics collision occurred
EVENT(E_PHYSICSCOLLISION, PhysicsCollision)
{
    PARAM(P_WORLD, World);                // PhysicsWorld pointer
    PARAM(P_NODEA, NodeA);                // Node pointer
    PARAM(P_NODEB, NodeB);                // Node pointer
    PARAM(P_SHAPEA, ShapeA);              // CollisionShape pointer
    PARAM(P_SHAPEB, ShapeB);              // CollisionShape pointer
    PARAM(P_NEWCOLLISION, NewCollision);  // bool
    PARAM(P_CONTACTS, Contacts);          // Buffer containing position, normal, depth, velocity for each contact
}

/// Physics collision occurred (sent to the participating scene nodes)
EVENT(E_NODECOLLISION, NodeCollision)
{
    PARAM(P_SHAPE, Shape);                // CollisionShape pointer
    PARAM(P_OTHERNODE, OtherNode);        // Node pointer
    PARAM(P_OTHERSHAPE, OtherShape);      // CollisionShape pointer
    PARAM(P_NEWCOLLISION, NewCollision);  // bool
    PARAM(P_CONTACTS, Contacts);          // Buffer containing position, normal, depth, velocity for each contact
}
