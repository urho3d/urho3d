//
// Copyright (c) 2008-2020 the Urho3D project.
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

#ifdef URHO3D_URHO2D

#include "../Urho2D/ParticleEffect2D.h"
#include "../Urho2D/TileMap2D.h"
#include "../Urho2D/PhysicsWorld2D.h"
#include "../Urho2D/CollisionPolygon2D.h"
#include "../Urho2D/CollisionChain2D.h"
#include "../Urho2D/RigidBody2D.h"

namespace Urho3D
{

// RigidBody2D* PhysicsRaycastResult2D::body_ | File: ../Urho2D/PhysicsWorld2D.h
RigidBody2D* PhysicsRaycastResultGetRigidBody2D(PhysicsRaycastResult2D* ptr);

#define REGISTER_MANUAL_PART_PhysicsRaycastResult2D(T, className) \
    /* RigidBody2D* PhysicsRaycastResult2D::body_ | File: ../Urho2D/PhysicsWorld2D.h */ \
    engine->RegisterObjectMethod(className, "RigidBody2D@+ get_body() const", asFUNCTION(PhysicsRaycastResultGetRigidBody2D), asCALL_CDECL_OBJLAST);

// ========================================================================================

// void PhysicsWorld2D::Raycast(PODVector< PhysicsRaycastResult2D > &results, const Vector2 &startPoint, const Vector2 &endPoint, unsigned collisionMask=M_MAX_UNSIGNED) | File: ../Urho2D/PhysicsWorld2D.h
CScriptArray* PhysicsWorld2DRaycast(const Vector2& startPoint, const Vector2& endPoint, unsigned collisionMask, PhysicsWorld2D* ptr);
// void PhysicsWorld2D::RaycastSingle(PhysicsRaycastResult2D &result, const Vector2 &startPoint, const Vector2 &endPoint, unsigned collisionMask=M_MAX_UNSIGNED) | File: ../Urho2D/PhysicsWorld2D.h
PhysicsRaycastResult2D PhysicsWorld2DRaycastSingle(const Vector2& startPoint, const Vector2& endPoint, unsigned collisionMask, PhysicsWorld2D* ptr);
// void PhysicsWorld2D::GetRigidBodies(PODVector< RigidBody2D * > &results, const Rect &aabb, unsigned collisionMask=M_MAX_UNSIGNED) | File: ../Urho2D/PhysicsWorld2D.h
CScriptArray* PhysicsWorld2DGetRigidBodies(const Rect& aabb, unsigned collisionMask, PhysicsWorld2D* ptr);

#define REGISTER_MANUAL_PART_PhysicsWorld2D(T, className) \
    /* void PhysicsWorld2D::Raycast(PODVector< PhysicsRaycastResult2D > &results, const Vector2 &startPoint, const Vector2 &endPoint, unsigned collisionMask=M_MAX_UNSIGNED) | File: ../Urho2D/PhysicsWorld2D.h */ \
    engine->RegisterObjectMethod(className, "Array<PhysicsRaycastResult2D>@ Raycast(const Vector2&, const Vector2&, uint collisionMask = 0xffff)", asFUNCTION(PhysicsWorld2DRaycast), asCALL_CDECL_OBJLAST); \
    /* void PhysicsWorld2D::RaycastSingle(PhysicsRaycastResult2D &result, const Vector2 &startPoint, const Vector2 &endPoint, unsigned collisionMask=M_MAX_UNSIGNED) | File: ../Urho2D/PhysicsWorld2D.h */ \
    engine->RegisterObjectMethod(className, "PhysicsRaycastResult2D RaycastSingle(const Vector2&, const Vector2&, uint collisionMask = 0xffff)", asFUNCTION(PhysicsWorld2DRaycastSingle), asCALL_CDECL_OBJLAST); \
    /* void PhysicsWorld2D::GetRigidBodies(PODVector< RigidBody2D * > &results, const Rect &aabb, unsigned collisionMask=M_MAX_UNSIGNED) | File: ../Urho2D/PhysicsWorld2D.h */ \
    engine->RegisterObjectMethod(className, "Array<RigidBody2D@>@ GetRigidBodies(const Rect&in, uint collisionMask = 0xffff)", asFUNCTION(PhysicsWorld2DGetRigidBodies), asCALL_CDECL_OBJLAST);

}

#endif // def URHO3D_URHO2D
