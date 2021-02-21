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

#include "../Physics/PhysicsWorld.h"
#include "../Physics/RigidBody.h"
#include "../Physics/CollisionShape.h"

namespace Urho3D
{

// RigidBody* PhysicsRaycastResult::body_ | File: ../Physics/PhysicsWorld.h
RigidBody* PhysicsRaycastResultGetRigidBody(PhysicsRaycastResult* ptr);

#define REGISTER_MANUAL_PART_PhysicsRaycastResult(T, className) \
    /* RigidBody* PhysicsRaycastResult::body_ | File: ../Physics/PhysicsWorld.h */ \
    engine->RegisterObjectMethod(className, "RigidBody@+ get_body() const", AS_FUNCTION_OBJLAST(PhysicsRaycastResultGetRigidBody), AS_CALL_CDECL_OBJLAST);

// ========================================================================================

// void RigidBody::GetCollidingBodies(PODVector< RigidBody * > &result) const | File: ../Physics/RigidBody.h
CScriptArray* RigidBodyGetCollidingBodies(RigidBody* ptr);

#define REGISTER_MANUAL_PART_RigidBody(T, className) \
    /* void RigidBody::GetCollidingBodies(PODVector< RigidBody * > &result) const | File: ../Physics/RigidBody.h */ \
    engine->RegisterObjectMethod(className, "Array<RigidBody@>@ get_collidingBodies() const", AS_FUNCTION_OBJLAST(RigidBodyGetCollidingBodies), AS_CALL_CDECL_OBJLAST);

// ========================================================================================

// void PhysicsWorld::Raycast(PODVector< PhysicsRaycastResult > &result, const Ray &ray, float maxDistance, unsigned collisionMask=M_MAX_UNSIGNED) | File: ../Physics/PhysicsWorld.h
CScriptArray* PhysicsWorldRaycast(const Ray& ray, float maxDistance, unsigned collisionMask, PhysicsWorld* ptr);
// void PhysicsWorld::RaycastSingle(PhysicsRaycastResult &result, const Ray &ray, float maxDistance, unsigned collisionMask=M_MAX_UNSIGNED) | File: ../Physics/PhysicsWorld.h
PhysicsRaycastResult PhysicsWorldRaycastSingle(const Ray& ray, float maxDistance, unsigned collisionMask, PhysicsWorld* ptr);
// void PhysicsWorld::RaycastSingleSegmented(PhysicsRaycastResult &result, const Ray &ray, float maxDistance, float segmentDistance, unsigned collisionMask=M_MAX_UNSIGNED, float overlapDistance=0.1f) | File: ../Physics/PhysicsWorld.h
PhysicsRaycastResult PhysicsWorldRaycastSingleSegmented(const Ray& ray, float maxDistance, float segmentDistance, unsigned collisionMask, float overlapDistance, PhysicsWorld* ptr);
// void PhysicsWorld::SphereCast(PhysicsRaycastResult &result, const Ray &ray, float radius, float maxDistance, unsigned collisionMask=M_MAX_UNSIGNED) | File: ../Physics/PhysicsWorld.h
PhysicsRaycastResult PhysicsWorldSphereCast(const Ray& ray, float radius, float maxDistance, unsigned collisionMask, PhysicsWorld* ptr);
// void PhysicsWorld::ConvexCast(PhysicsRaycastResult &result, CollisionShape *shape, const Vector3 &startPos, const Quaternion &startRot, const Vector3 &endPos, const Quaternion &endRot, unsigned collisionMask=M_MAX_UNSIGNED) | File: ../Physics/PhysicsWorld.h
PhysicsRaycastResult PhysicsWorldConvexCast(CollisionShape* shape, const Vector3& startPos, const Quaternion& startRot, const Vector3& endPos, const Quaternion& endRot, unsigned collisionMask, PhysicsWorld* ptr);
// void PhysicsWorld::GetRigidBodies(PODVector< RigidBody * > &result, const Sphere &sphere, unsigned collisionMask=M_MAX_UNSIGNED) | File: ../Physics/PhysicsWorld.h
CScriptArray* PhysicsWorldGetRigidBodiesSphere(const Sphere& sphere, unsigned collisionMask, PhysicsWorld* ptr);
// void PhysicsWorld::GetRigidBodies(PODVector< RigidBody * > &result, const BoundingBox &box, unsigned collisionMask=M_MAX_UNSIGNED) | File: ../Physics/PhysicsWorld.h
CScriptArray* PhysicsWorldGetRigidBodiesBox(const BoundingBox& box, unsigned collisionMask, PhysicsWorld* ptr);
// void PhysicsWorld::GetRigidBodies(PODVector< RigidBody * > &result, const RigidBody *body) | File: ../Physics/PhysicsWorld.h
CScriptArray* PhysicsWorldGetRigidBodiesBody(RigidBody* body, PhysicsWorld* ptr);
// void PhysicsWorld::GetCollidingBodies(PODVector< RigidBody * > &result, const RigidBody *body) | File: ../Physics/PhysicsWorld.h
CScriptArray* PhysicsWorldGetCollidingBodies(RigidBody* body, PhysicsWorld* ptr);

#define REGISTER_MANUAL_PART_PhysicsWorld(T, className) \
    /* void PhysicsWorld::Raycast(PODVector< PhysicsRaycastResult > &result, const Ray &ray, float maxDistance, unsigned collisionMask=M_MAX_UNSIGNED) | File: ../Physics/PhysicsWorld.h */ \
    engine->RegisterObjectMethod(className, "Array<PhysicsRaycastResult>@ Raycast(const Ray&in, float, uint collisionMask = 0xffff)", AS_FUNCTION_OBJLAST(PhysicsWorldRaycast), AS_CALL_CDECL_OBJLAST); \
    /* void PhysicsWorld::RaycastSingle(PhysicsRaycastResult &result, const Ray &ray, float maxDistance, unsigned collisionMask=M_MAX_UNSIGNED) | File: ../Physics/PhysicsWorld.h */ \
    engine->RegisterObjectMethod(className, "PhysicsRaycastResult RaycastSingle(const Ray&in, float, uint collisionMask = 0xffff)", AS_FUNCTION_OBJLAST(PhysicsWorldRaycastSingle), AS_CALL_CDECL_OBJLAST); \
    /* void PhysicsWorld::RaycastSingleSegmented(PhysicsRaycastResult &result, const Ray &ray, float maxDistance, float segmentDistance, unsigned collisionMask=M_MAX_UNSIGNED, float overlapDistance=0.1f) | File: ../Physics/PhysicsWorld.h */ \
    engine->RegisterObjectMethod(className, "PhysicsRaycastResult RaycastSingleSegmented(const Ray&in, float, float, uint collisionMask = 0xffff, float overlapDistance = 0.1f)", AS_FUNCTION_OBJLAST(PhysicsWorldRaycastSingleSegmented), AS_CALL_CDECL_OBJLAST); \
    /* void PhysicsWorld::SphereCast(PhysicsRaycastResult &result, const Ray &ray, float radius, float maxDistance, unsigned collisionMask=M_MAX_UNSIGNED) | File: ../Physics/PhysicsWorld.h */ \
    engine->RegisterObjectMethod(className, "PhysicsRaycastResult SphereCast(const Ray&in, float, float, uint collisionMask = 0xffff)", AS_FUNCTION_OBJLAST(PhysicsWorldSphereCast), AS_CALL_CDECL_OBJLAST); \
    /* There seems to be a bug in AngelScript resulting in a crash if we use an auto handle with this function. */ \
    /* Work around by manually releasing the CollisionShape handle */ \
    /* void PhysicsWorld::ConvexCast(PhysicsRaycastResult &result, CollisionShape *shape, const Vector3 &startPos, const Quaternion &startRot, const Vector3 &endPos, const Quaternion &endRot, unsigned collisionMask=M_MAX_UNSIGNED) | File: ../Physics/PhysicsWorld.h */ \
    engine->RegisterObjectMethod(className, "PhysicsRaycastResult ConvexCast(CollisionShape@, const Vector3&in, const Quaternion&in, const Vector3&in, const Quaternion&in, uint collisionMask = 0xffff)", AS_FUNCTION_OBJLAST(PhysicsWorldConvexCast), AS_CALL_CDECL_OBJLAST); \
    /* void PhysicsWorld::GetRigidBodies(PODVector< RigidBody * > &result, const Sphere &sphere, unsigned collisionMask=M_MAX_UNSIGNED) | File: ../Physics/PhysicsWorld.h */ \
    engine->RegisterObjectMethod(className, "Array<RigidBody@>@ GetRigidBodies(const Sphere&in, uint collisionMask = 0xffff)", AS_FUNCTION_OBJLAST(PhysicsWorldGetRigidBodiesSphere), AS_CALL_CDECL_OBJLAST); \
    /* void PhysicsWorld::GetRigidBodies(PODVector< RigidBody * > &result, const BoundingBox &box, unsigned collisionMask=M_MAX_UNSIGNED) | File: ../Physics/PhysicsWorld.h */ \
    engine->RegisterObjectMethod(className, "Array<RigidBody@>@ GetRigidBodies(const BoundingBox&in, uint collisionMask = 0xffff)", AS_FUNCTION_OBJLAST(PhysicsWorldGetRigidBodiesBox), AS_CALL_CDECL_OBJLAST); \
    /* void PhysicsWorld::GetRigidBodies(PODVector< RigidBody * > &result, const RigidBody *body) | File: ../Physics/PhysicsWorld.h */ \
    engine->RegisterObjectMethod(className, "Array<RigidBody@>@ GetRigidBodies(RigidBody@+)", AS_FUNCTION_OBJLAST(PhysicsWorldGetRigidBodiesBody), AS_CALL_CDECL_OBJLAST); \
    /* void PhysicsWorld::GetCollidingBodies(PODVector< RigidBody * > &result, const RigidBody *body) | File: ../Physics/PhysicsWorld.h */ \
    engine->RegisterObjectMethod(className, "Array<RigidBody@>@ GetCollidingBodies(RigidBody@+)", AS_FUNCTION_OBJLAST(PhysicsWorldGetCollidingBodies), AS_CALL_CDECL_OBJLAST);

}

#endif // def URHO3D_PHYSICS
