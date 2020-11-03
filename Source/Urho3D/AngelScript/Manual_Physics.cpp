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

#ifdef URHO3D_PHYSICS

#include "../AngelScript/Manual_Physics.h"

#include "../Scene/Scene.h"

namespace Urho3D
{

// This function is called before ASRegisterGenerated()
void ASRegisterManualFirst_Physics(asIScriptEngine* engine)
{
}

// ========================================================================================

// template<class T> T * Node::GetComponent(bool recursive=false) const | File: ../Scene/Node.h
static PhysicsWorld* GetPhysicsWorld()
{
    Scene* scene = GetScriptContextScene();
    return scene ? scene->GetComponent<PhysicsWorld>() : nullptr;
}

// This function is called after ASRegisterGenerated()
void ASRegisterManualLast_Physics(asIScriptEngine* engine)
{
    // template<class T> T * Node::GetComponent(bool recursive=false) const | File: ../Scene/Node.h
    engine->RegisterGlobalFunction("PhysicsWorld@+ get_physicsWorld()", asFUNCTION(GetPhysicsWorld), asCALL_CDECL);
}

// ========================================================================================

// RigidBody* PhysicsRaycastResult::body_ | File: ../Physics/PhysicsWorld.h
RigidBody* PhysicsRaycastResultGetRigidBody(PhysicsRaycastResult* ptr)
{
    return ptr->body_;
}

// ========================================================================================

// void RigidBody::GetCollidingBodies(PODVector< RigidBody * > &result) const | File: ../Physics/RigidBody.h
CScriptArray* RigidBodyGetCollidingBodies(RigidBody* ptr)
{
    PODVector<RigidBody*> result;
    ptr->GetCollidingBodies(result);
    return VectorToHandleArray<RigidBody>(result, "Array<RigidBody@>");
}

// ========================================================================================

// void PhysicsWorld::Raycast(PODVector< PhysicsRaycastResult > &result, const Ray &ray, float maxDistance, unsigned collisionMask=M_MAX_UNSIGNED) | File: ../Physics/PhysicsWorld.h
CScriptArray* PhysicsWorldRaycast(const Ray& ray, float maxDistance, unsigned collisionMask, PhysicsWorld* ptr)
{
    PODVector<PhysicsRaycastResult> result;
    ptr->Raycast(result, ray, maxDistance, collisionMask);
    return VectorToArray<PhysicsRaycastResult>(result, "Array<PhysicsRaycastResult>");
}

// void PhysicsWorld::RaycastSingle(PhysicsRaycastResult &result, const Ray &ray, float maxDistance, unsigned collisionMask=M_MAX_UNSIGNED) | File: ../Physics/PhysicsWorld.h
PhysicsRaycastResult PhysicsWorldRaycastSingle(const Ray& ray, float maxDistance, unsigned collisionMask, PhysicsWorld* ptr)
{
    PhysicsRaycastResult result;
    ptr->RaycastSingle(result, ray, maxDistance, collisionMask);
    return result;
}

// void PhysicsWorld::RaycastSingleSegmented(PhysicsRaycastResult &result, const Ray &ray, float maxDistance, float segmentDistance, unsigned collisionMask=M_MAX_UNSIGNED, float overlapDistance=0.1f) | File: ../Physics/PhysicsWorld.h
PhysicsRaycastResult PhysicsWorldRaycastSingleSegmented(const Ray& ray, float maxDistance, float segmentDistance, unsigned collisionMask, float overlapDistance, PhysicsWorld* ptr)
{
    PhysicsRaycastResult result;
    ptr->RaycastSingleSegmented(result, ray, maxDistance, segmentDistance, collisionMask, overlapDistance);
    return result;
}

// void PhysicsWorld::SphereCast(PhysicsRaycastResult &result, const Ray &ray, float radius, float maxDistance, unsigned collisionMask=M_MAX_UNSIGNED) | File: ../Physics/PhysicsWorld.h
PhysicsRaycastResult PhysicsWorldSphereCast(const Ray& ray, float radius, float maxDistance, unsigned collisionMask, PhysicsWorld* ptr)
{
    PhysicsRaycastResult result;
    ptr->SphereCast(result, ray, radius, maxDistance, collisionMask);
    return result;
}

// void PhysicsWorld::ConvexCast(PhysicsRaycastResult &result, CollisionShape *shape, const Vector3 &startPos, const Quaternion &startRot, const Vector3 &endPos, const Quaternion &endRot, unsigned collisionMask=M_MAX_UNSIGNED) | File: ../Physics/PhysicsWorld.h
PhysicsRaycastResult PhysicsWorldConvexCast(CollisionShape* shape, const Vector3& startPos, const Quaternion& startRot, const Vector3& endPos, const Quaternion& endRot, unsigned collisionMask, PhysicsWorld* ptr)
{
    PhysicsRaycastResult result;
    ptr->ConvexCast(result, shape, startPos, startRot, endPos, endRot, collisionMask);
    // Release extra ref manually due to not using an auto handle (see below)
    if (shape)
        shape->ReleaseRef();
    return result;
}

// void PhysicsWorld::GetRigidBodies(PODVector< RigidBody * > &result, const Sphere &sphere, unsigned collisionMask=M_MAX_UNSIGNED) | File: ../Physics/PhysicsWorld.h
CScriptArray* PhysicsWorldGetRigidBodiesSphere(const Sphere& sphere, unsigned collisionMask, PhysicsWorld* ptr)
{
    PODVector<RigidBody*> result;
    ptr->GetRigidBodies(result, sphere, collisionMask);
    return VectorToHandleArray<RigidBody>(result, "Array<RigidBody@>");
}

// void PhysicsWorld::GetRigidBodies(PODVector< RigidBody * > &result, const BoundingBox &box, unsigned collisionMask=M_MAX_UNSIGNED) | File: ../Physics/PhysicsWorld.h
CScriptArray* PhysicsWorldGetRigidBodiesBox(const BoundingBox& box, unsigned collisionMask, PhysicsWorld* ptr)
{
    PODVector<RigidBody*> result;
    ptr->GetRigidBodies(result, box, collisionMask);
    return VectorToHandleArray<RigidBody>(result, "Array<RigidBody@>");
}

// void PhysicsWorld::GetRigidBodies(PODVector< RigidBody * > &result, const RigidBody *body) | File: ../Physics/PhysicsWorld.h
CScriptArray* PhysicsWorldGetRigidBodiesBody(RigidBody* body, PhysicsWorld* ptr)
{
    PODVector<RigidBody*> result;
    ptr->GetRigidBodies(result, body);
    return VectorToHandleArray<RigidBody>(result, "Array<RigidBody@>");
}

// void PhysicsWorld::GetCollidingBodies(PODVector< RigidBody * > &result, const RigidBody *body) | File: ../Physics/PhysicsWorld.h
CScriptArray* PhysicsWorldGetCollidingBodies(RigidBody* body, PhysicsWorld* ptr)
{
    PODVector<RigidBody*> result;
    ptr->GetCollidingBodies(result, body);
    return VectorToHandleArray<RigidBody>(result, "Array<RigidBody@>");
}

}

#endif // def URHO3D_PHYSICS
