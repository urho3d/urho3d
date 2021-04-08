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

#ifdef URHO3D_PHYSICS

#include "../Precompiled.h"
#include "../AngelScript/APITemplates.h"

#include "../Physics/CollisionShape.h"
#include "../Physics/PhysicsWorld.h"
#include "../Physics/RigidBody.h"

namespace Urho3D
{

// RigidBody* PhysicsRaycastResult::body_ | File: ../Physics/PhysicsWorld.h
template <class T> RigidBody* PhysicsRaycastResult_GetRigidBody(T* ptr)
{
    return ptr->body_;
}

#define REGISTER_MEMBERS_MANUAL_PART_PhysicsRaycastResult() \
    /* RigidBody* PhysicsRaycastResult::body_ | File: ../Physics/PhysicsWorld.h */ \
    engine->RegisterObjectMethod(className, "RigidBody@+ get_body() const", AS_FUNCTION_OBJLAST(PhysicsRaycastResult_GetRigidBody<T>), AS_CALL_CDECL_OBJLAST);

// ========================================================================================

// void RigidBody::GetCollidingBodies(PODVector<RigidBody*>& result) const | File: ../Physics/RigidBody.h
template <class T> CScriptArray* RigidBody_GetCollidingBodies(T* ptr)
{
    PODVector<RigidBody*> result;
    ptr->GetCollidingBodies(result);
    return VectorToHandleArray<RigidBody>(result, "Array<RigidBody@>");
}

#define REGISTER_MEMBERS_MANUAL_PART_RigidBody() \
    /* void RigidBody::GetCollidingBodies(PODVector<RigidBody*>& result) const | File: ../Physics/RigidBody.h */ \
    engine->RegisterObjectMethod(className, "Array<RigidBody@>@ get_collidingBodies() const", AS_FUNCTION_OBJLAST(RigidBody_GetCollidingBodies<T>), AS_CALL_CDECL_OBJLAST);

// ========================================================================================

// void PhysicsWorld::Raycast(PODVector<PhysicsRaycastResult>& result, const Ray& ray, float maxDistance, unsigned collisionMask = M_MAX_UNSIGNED) | File: ../Physics/PhysicsWorld.h
template <class T> CScriptArray* PhysicsWorld_Raycast(const Ray& ray, float maxDistance, unsigned collisionMask, T* ptr)
{
    PODVector<PhysicsRaycastResult> result;
    ptr->Raycast(result, ray, maxDistance, collisionMask);
    return VectorToArray<PhysicsRaycastResult>(result, "Array<PhysicsRaycastResult>");
}

// void PhysicsWorld::RaycastSingle(PhysicsRaycastResult& result, const Ray& ray, float maxDistance, unsigned collisionMask = M_MAX_UNSIGNED) | File: ../Physics/PhysicsWorld.h
template <class T> PhysicsRaycastResult PhysicsWorld_RaycastSingle(const Ray& ray, float maxDistance, unsigned collisionMask, T* ptr)
{
    PhysicsRaycastResult result;
    ptr->RaycastSingle(result, ray, maxDistance, collisionMask);
    return result;
}

// void PhysicsWorld::RaycastSingleSegmented(PhysicsRaycastResult& result, const Ray& ray, float maxDistance, float segmentDistance, unsigned collisionMask = M_MAX_UNSIGNED, float overlapDistance = 0.1f) | File: ../Physics/PhysicsWorld.h
template <class T> PhysicsRaycastResult PhysicsWorld_RaycastSingleSegmented(const Ray& ray, float maxDistance, float segmentDistance, unsigned collisionMask, float overlapDistance, T* ptr)
{
    PhysicsRaycastResult result;
    ptr->RaycastSingleSegmented(result, ray, maxDistance, segmentDistance, collisionMask, overlapDistance);
    return result;
}

// void PhysicsWorld::SphereCast(PhysicsRaycastResult& result, const Ray& ray, float radius, float maxDistance, unsigned collisionMask = M_MAX_UNSIGNED) | File: ../Physics/PhysicsWorld.h
template <class T> PhysicsRaycastResult PhysicsWorld_SphereCast(const Ray& ray, float radius, float maxDistance, unsigned collisionMask, T* ptr)
{
    PhysicsRaycastResult result;
    ptr->SphereCast(result, ray, radius, maxDistance, collisionMask);
    return result;
}

// void PhysicsWorld::GetRigidBodies(PODVector<RigidBody*>& result, const Sphere& sphere, unsigned collisionMask = M_MAX_UNSIGNED) | File: ../Physics/PhysicsWorld.h
template <class T> CScriptArray* PhysicsWorld_GetRigidBodies_Sphere(const Sphere& sphere, unsigned collisionMask, T* ptr)
{
    PODVector<RigidBody*> result;
    ptr->GetRigidBodies(result, sphere, collisionMask);
    return VectorToHandleArray<RigidBody>(result, "Array<RigidBody@>");
}

// void PhysicsWorld::GetRigidBodies(PODVector<RigidBody*>& result, const BoundingBox& box, unsigned collisionMask = M_MAX_UNSIGNED) | File: ../Physics/PhysicsWorld.h
template <class T> CScriptArray* PhysicsWorld_GetRigidBodies_Box(const BoundingBox& box, unsigned collisionMask, T* ptr)
{
    PODVector<RigidBody*> result;
    ptr->GetRigidBodies(result, box, collisionMask);
    return VectorToHandleArray<RigidBody>(result, "Array<RigidBody@>");
}

// void PhysicsWorld::GetRigidBodies(PODVector<RigidBody*>& result, const RigidBody* body) | File: ../Physics/PhysicsWorld.h
template <class T> CScriptArray* PhysicsWorld_GetRigidBodies_Body(RigidBody* body, T* ptr)
{
    PODVector<RigidBody*> result;
    ptr->GetRigidBodies(result, body);
    return VectorToHandleArray<RigidBody>(result, "Array<RigidBody@>");
}

// void PhysicsWorld::GetCollidingBodies(PODVector<RigidBody*>& result, const RigidBody* body) | File: ../Physics/PhysicsWorld.h
template <class T> CScriptArray* PhysicsWorld_GetCollidingBodies(RigidBody* body, T* ptr)
{
    PODVector<RigidBody*> result;
    ptr->GetCollidingBodies(result, body);
    return VectorToHandleArray<RigidBody>(result, "Array<RigidBody@>");
}

// void PhysicsWorld::ConvexCast(PhysicsRaycastResult& result, CollisionShape* shape, const Vector3& startPos, const Quaternion& startRot, const Vector3& endPos, const Quaternion& endRot, unsigned collisionMask = M_MAX_UNSIGNED) | File: ../Physics/PhysicsWorld.h
template <class T> PhysicsRaycastResult PhysicsWorld_ConvexCast(CollisionShape* shape, const Vector3& startPos, const Quaternion& startRot, const Vector3& endPos, const Quaternion& endRot, unsigned collisionMask, T* ptr)
{
    PhysicsRaycastResult result;
    ptr->ConvexCast(result, shape, startPos, startRot, endPos, endRot, collisionMask);
    // Release extra ref manually due to not using an auto handle
    if (shape)
        shape->ReleaseRef();
    return result;
}

#define REGISTER_MEMBERS_MANUAL_PART_PhysicsWorld() \
    /* void PhysicsWorld::Raycast(PODVector<PhysicsRaycastResult>& result, const Ray& ray, float maxDistance, unsigned collisionMask = M_MAX_UNSIGNED) | File: ../Physics/PhysicsWorld.h */ \
    engine->RegisterObjectMethod(className, "Array<PhysicsRaycastResult>@ Raycast(const Ray&in, float, uint = 0xffff)", AS_FUNCTION_OBJLAST(PhysicsWorld_Raycast<T>), AS_CALL_CDECL_OBJLAST); \
    \
    /* void PhysicsWorld::RaycastSingle(PhysicsRaycastResult& result, const Ray& ray, float maxDistance, unsigned collisionMask = M_MAX_UNSIGNED) | File: ../Physics/PhysicsWorld.h */ \
    engine->RegisterObjectMethod(className, "PhysicsRaycastResult RaycastSingle(const Ray&in, float, uint = 0xffff)", AS_FUNCTION_OBJLAST(PhysicsWorld_RaycastSingle<T>), AS_CALL_CDECL_OBJLAST); \
    \
    /* void PhysicsWorld::RaycastSingleSegmented(PhysicsRaycastResult& result, const Ray& ray, float maxDistance, float segmentDistance, unsigned collisionMask = M_MAX_UNSIGNED, float overlapDistance = 0.1f) | File: ../Physics/PhysicsWorld.h */ \
    engine->RegisterObjectMethod(className, "PhysicsRaycastResult RaycastSingleSegmented(const Ray&in, float, float, uint collisionMask = 0xffff, float overlapDistance = 0.1f)", AS_FUNCTION_OBJLAST(PhysicsWorld_RaycastSingleSegmented<T>), AS_CALL_CDECL_OBJLAST); \
    \
    /* void PhysicsWorld::SphereCast(PhysicsRaycastResult& result, const Ray& ray, float radius, float maxDistance, unsigned collisionMask = M_MAX_UNSIGNED) | File: ../Physics/PhysicsWorld.h */ \
    engine->RegisterObjectMethod(className, "PhysicsRaycastResult SphereCast(const Ray&in, float, float, uint collisionMask = 0xffff)", AS_FUNCTION_OBJLAST(PhysicsWorld_SphereCast<T>), AS_CALL_CDECL_OBJLAST); \
    \
    /* void PhysicsWorld::GetRigidBodies(PODVector<RigidBody*>& result, const Sphere& sphere, unsigned collisionMask = M_MAX_UNSIGNED) | File: ../Physics/PhysicsWorld.h */ \
    engine->RegisterObjectMethod(className, "Array<RigidBody@>@ GetRigidBodies(const Sphere&in, uint = 0xffff)", AS_FUNCTION_OBJLAST(PhysicsWorld_GetRigidBodies_Sphere<T>), AS_CALL_CDECL_OBJLAST); \
    \
    /* void PhysicsWorld::GetRigidBodies(PODVector<RigidBody*>& result, const BoundingBox& box, unsigned collisionMask = M_MAX_UNSIGNED) | File: ../Physics/PhysicsWorld.h */ \
    engine->RegisterObjectMethod(className, "Array<RigidBody@>@ GetRigidBodies(const BoundingBox&in, uint collisionMask = 0xffff)", AS_FUNCTION_OBJLAST(PhysicsWorld_GetRigidBodies_Box<T>), AS_CALL_CDECL_OBJLAST); \
    \
    /* void PhysicsWorld::GetRigidBodies(PODVector<RigidBody*>& result, const RigidBody* body) | File: ../Physics/PhysicsWorld.h */ \
    engine->RegisterObjectMethod(className, "Array<RigidBody@>@ GetRigidBodies(RigidBody@+)", AS_FUNCTION_OBJLAST(PhysicsWorld_GetRigidBodies_Body<T>), AS_CALL_CDECL_OBJLAST); \
    \
    /* void PhysicsWorld::GetCollidingBodies(PODVector<RigidBody*>& result, const RigidBody* body) | File: ../Physics/PhysicsWorld.h */ \
    engine->RegisterObjectMethod(className, "Array<RigidBody@>@ GetCollidingBodies(RigidBody@+)", AS_FUNCTION_OBJLAST(PhysicsWorld_GetCollidingBodies<T>), AS_CALL_CDECL_OBJLAST); \
    \
    /* There seems to be a bug in AngelScript resulting in a crash if we use an auto handle with this function. */    \
    /* Work around by manually releasing the CollisionShape handle */                                                 \
    /* void PhysicsWorld::ConvexCast(PhysicsRaycastResult& result, CollisionShape* shape, const Vector3& startPos, const Quaternion& startRot, const Vector3& endPos, const Quaternion& endRot, unsigned collisionMask = M_MAX_UNSIGNED) | File: ../Physics/PhysicsWorld.h */ \
    engine->RegisterObjectMethod(className, "PhysicsRaycastResult ConvexCast(CollisionShape@, const Vector3&in, const Quaternion&in, const Vector3&in, const Quaternion&in, uint = 0xffff)", AS_FUNCTION_OBJLAST(PhysicsWorld_ConvexCast<T>), AS_CALL_CDECL_OBJLAST);

}

#endif // def URHO3D_PHYSICS
