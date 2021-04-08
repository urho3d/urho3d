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
template <class T> RigidBody2D* PhysicsRaycastResult2D_GetBody(T* ptr)
{
    return ptr->body_;
}

#define REGISTER_MEMBERS_MANUAL_PART_PhysicsRaycastResult2D() \
    /* RigidBody2D* PhysicsRaycastResult2D::body_ | File: ../Urho2D/PhysicsWorld2D.h */ \
    engine->RegisterObjectMethod(className, "RigidBody2D@+ get_body() const", AS_FUNCTION_OBJLAST(PhysicsRaycastResult2D_GetBody<T>), AS_CALL_CDECL_OBJLAST);

// ========================================================================================

// void PhysicsWorld2D::Raycast(PODVector<PhysicsRaycastResult2D>& results, const Vector2& startPoint, const Vector2& endPoint, unsigned collisionMask = M_MAX_UNSIGNED) | File: ../Urho2D/PhysicsWorld2D.h
template <class T> CScriptArray* PhysicsWorld2D_Raycast(const Vector2& startPoint, const Vector2& endPoint, unsigned collisionMask, T* ptr)
{
    PODVector<PhysicsRaycastResult2D> result;
    ptr->Raycast(result, startPoint, endPoint, collisionMask);
    return VectorToArray<PhysicsRaycastResult2D>(result, "Array<PhysicsRaycastResult2D>");
}

// void PhysicsWorld2D::RaycastSingle(PhysicsRaycastResult2D& result, const Vector2& startPoint, const Vector2& endPoint, unsigned collisionMask = M_MAX_UNSIGNED) | File: ../Urho2D/PhysicsWorld2D.h
template <class T> PhysicsRaycastResult2D PhysicsWorld2D_RaycastSingle(const Vector2& startPoint, const Vector2& endPoint, unsigned collisionMask, T* ptr)
{
    PhysicsRaycastResult2D result;
    ptr->RaycastSingle(result, startPoint, endPoint, collisionMask);
    return result;
}

// void PhysicsWorld2D::GetRigidBodies(PODVector<RigidBody2D*>& results, const Rect& aabb, unsigned collisionMask = M_MAX_UNSIGNED) | File: ../Urho2D/PhysicsWorld2D.h
template <class T> CScriptArray* PhysicsWorld2D_GetRigidBodies(const Rect& aabb, unsigned collisionMask, T* ptr)
{
    PODVector<RigidBody2D*> results;
    ptr->GetRigidBodies(results, aabb, collisionMask);
    return VectorToHandleArray<RigidBody2D>(results, "Array<RigidBody2D@>");
}

#define REGISTER_MEMBERS_MANUAL_PART_PhysicsWorld2D() \
    /* void PhysicsWorld2D::Raycast(PODVector<PhysicsRaycastResult2D>& results, const Vector2& startPoint, const Vector2& endPoint, unsigned collisionMask = M_MAX_UNSIGNED) */ \
    engine->RegisterObjectMethod(className, "Array<PhysicsRaycastResult2D>@ Raycast(const Vector2&, const Vector2&, uint = 0xffff)", AS_FUNCTION_OBJLAST(PhysicsWorld2D_Raycast<T>), AS_CALL_CDECL_OBJLAST); \
    \
    /* void PhysicsWorld2D::RaycastSingle(PhysicsRaycastResult2D& result, const Vector2& startPoint, const Vector2& endPoint, unsigned collisionMask = M_MAX_UNSIGNED) | File: ../Urho2D/PhysicsWorld2D.h */ \
    engine->RegisterObjectMethod(className, "PhysicsRaycastResult2D RaycastSingle(const Vector2&, const Vector2&, uint = 0xffff)", AS_FUNCTION_OBJLAST(PhysicsWorld2D_RaycastSingle<T>), AS_CALL_CDECL_OBJLAST); \
    \
    /* void PhysicsWorld2D::GetRigidBodies(PODVector<RigidBody2D*>& results, const Rect& aabb, unsigned collisionMask = M_MAX_UNSIGNED) | File: ../Urho2D/PhysicsWorld2D.h */ \
    engine->RegisterObjectMethod(className, "Array<RigidBody2D@>@ GetRigidBodies(const Rect&in, uint = 0xffff)", AS_FUNCTION_OBJLAST(PhysicsWorld2D_GetRigidBodies<T>), AS_CALL_CDECL_OBJLAST);

}

#endif // def URHO3D_URHO2D
