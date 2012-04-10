//
// Urho3D Engine
// Copyright (c) 2008-2012 Lasse Öörni
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

#include "Precompiled.h"
#include "APITemplates.h"
#include "BoxShape.h"
#include "CapsuleShape.h"
#include "ConeShape.h"
#include "CylinderShape.h"
#include "Joint.h"
#include "PhysicsWorld.h"
#include "RigidBody.h"
#include "Scene.h"
#include "SphereShape.h"
#include "TriangleMeshShape.h"

static PhysicsWorld* SceneGetPhysicsWorld(Scene* ptr)
{
    return ptr->GetComponent<PhysicsWorld>();
}

static PhysicsWorld* GetPhysicsWorld()
{
    Scene* scene = GetScriptContextScene();
    return scene ? scene->GetComponent<PhysicsWorld>() : 0;
}

static void ConstructPhysicsRaycastResult(PhysicsRaycastResult* ptr)
{
    ptr->position_ = Vector3::ZERO;
    ptr->normal_ = Vector3::ZERO;
    ptr->distance_ = 0.0f;
    ptr->body_ = 0;
}

static RigidBody* PhysicsRaycastResultGetRigidBody(PhysicsRaycastResult* ptr)
{
    return ptr->body_;
}

static CScriptArray* PhysicsWorldRaycast(const Ray& ray, float maxDistance, unsigned collisionMask, PhysicsWorld* ptr)
{
    static PODVector<PhysicsRaycastResult> result;
    ptr->Raycast(result, ray, maxDistance, collisionMask);
    return VectorToArray<PhysicsRaycastResult>(result, "Array<PhysicsRaycastResult>");
}

static void RegisterCollisionShapes(asIScriptEngine* engine)
{
    RegisterCollisionShape<CollisionShape>(engine, "CollisionShape");
    
    RegisterCollisionShape<BoxShape>(engine, "BoxShape");
    engine->RegisterObjectMethod("BoxShape", "void set_size(const Vector3&in)", asMETHOD(BoxShape, SetSize), asCALL_THISCALL);
    engine->RegisterObjectMethod("BoxShape", "const Vector3& get_size() const", asMETHOD(BoxShape, GetSize), asCALL_THISCALL);
    
    RegisterCollisionShape<CapsuleShape>(engine, "CapsuleShape");
    engine->RegisterObjectMethod("CapsuleShape", "void set_radius(float)", asMETHOD(CapsuleShape, SetRadius), asCALL_THISCALL);
    engine->RegisterObjectMethod("CapsuleShape", "float get_radius() const", asMETHOD(CapsuleShape, GetRadius), asCALL_THISCALL);
    engine->RegisterObjectMethod("CapsuleShape", "void set_height(float)", asMETHOD(CapsuleShape, SetHeight), asCALL_THISCALL);
    engine->RegisterObjectMethod("CapsuleShape", "float get_height() const", asMETHOD(CapsuleShape, GetHeight), asCALL_THISCALL);
    
    RegisterCollisionShape<ConeShape>(engine, "ConeShape");
    engine->RegisterObjectMethod("ConeShape", "void set_radius(float)", asMETHOD(ConeShape, SetRadius), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConeShape", "float get_radius() const", asMETHOD(ConeShape, GetRadius), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConeShape", "void set_height(float)", asMETHOD(ConeShape, SetHeight), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConeShape", "float get_height() const", asMETHOD(ConeShape, GetHeight), asCALL_THISCALL);
    
    RegisterCollisionShape<CylinderShape>(engine, "CylinderShape");
    engine->RegisterObjectMethod("CylinderShape", "void set_radius(float)", asMETHOD(CylinderShape, SetRadius), asCALL_THISCALL);
    engine->RegisterObjectMethod("CylinderShape", "float get_radius() const", asMETHOD(CylinderShape, GetRadius), asCALL_THISCALL);
    engine->RegisterObjectMethod("CylinderShape", "void set_height(float)", asMETHOD(CylinderShape, SetHeight), asCALL_THISCALL);
    engine->RegisterObjectMethod("CylinderShape", "float get_height() const", asMETHOD(CylinderShape, GetHeight), asCALL_THISCALL);
    
    RegisterCollisionShape<SphereShape>(engine, "SphereShape");
    engine->RegisterObjectMethod("SphereShape", "void set_radius(float)", asMETHOD(SphereShape, SetRadius), asCALL_THISCALL);
    engine->RegisterObjectMethod("SphereShape", "float get_radius() const", asMETHOD(SphereShape, GetRadius), asCALL_THISCALL);
    
    RegisterCollisionShape<TriangleMeshShape>(engine, "TriangleMeshShape");
    engine->RegisterObjectMethod("TriangleMeshShape", "void set_model(Model@+)", asMETHOD(TriangleMeshShape, SetModel), asCALL_THISCALL);
    engine->RegisterObjectMethod("TriangleMeshShape", "Model@+ get_model() const", asMETHOD(TriangleMeshShape, GetModel), asCALL_THISCALL);
    engine->RegisterObjectMethod("TriangleMeshShape", "void set_lodLevel(uint)", asMETHOD(TriangleMeshShape, SetLodLevel), asCALL_THISCALL);
    engine->RegisterObjectMethod("TriangleMeshShape", "uint get_lodLevel() const", asMETHOD(TriangleMeshShape, GetLodLevel), asCALL_THISCALL);
    engine->RegisterObjectMethod("TriangleMeshShape", "void set_size(const Vector3&in)", asMETHOD(TriangleMeshShape, SetSize), asCALL_THISCALL);
    engine->RegisterObjectMethod("TriangleMeshShape", "const Vector3& get_size() const", asMETHOD(TriangleMeshShape, GetSize), asCALL_THISCALL);
    
    // Register Variant GetPtr() for CollisionShape
    engine->RegisterObjectMethod("Variant", "CollisionShape@+ GetCollisionShape() const", asFUNCTION(GetVariantPtr<CollisionShape>), asCALL_CDECL_OBJLAST);
}

static void RegisterRigidBody(asIScriptEngine* engine)
{
    RegisterComponent<RigidBody>(engine, "RigidBody");
    engine->RegisterObjectMethod("RigidBody", "void SetTransform(const Vector3&in, const Quaternion&in)", asMETHOD(RigidBody, SetTransform), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "void SetCollisionGroupAndMask(uint, uint)", asMETHOD(RigidBody, SetCollisionGroupAndMask), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "void ApplyForce(const Vector3&in)", asMETHODPR(RigidBody, ApplyForce, (const Vector3&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "void ApplyForce(const Vector3&in, const Vector3&in)", asMETHODPR(RigidBody, ApplyForce, (const Vector3&, const Vector3&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "void ApplyTorque(const Vector3&in)", asMETHOD(RigidBody, ApplyTorque), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "void ApplyImpulse(const Vector3&in)", asMETHODPR(RigidBody, ApplyImpulse, (const Vector3&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "void ApplyImpulse(const Vector3&in, const Vector3&in)", asMETHODPR(RigidBody, ApplyImpulse, (const Vector3&, const Vector3&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "void ApplyTorqueImpulse(const Vector3&in)", asMETHOD(RigidBody, ApplyTorqueImpulse), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "void ResetForces()", asMETHOD(RigidBody, ResetForces), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "void Activate()", asMETHOD(RigidBody, Activate), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "void DrawDebugGeometry(DebugRenderer@+, bool)", asMETHOD(RigidBody, DrawDebugGeometry), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "void set_mass(float)", asMETHOD(RigidBody, SetMass), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "float get_mass() const", asMETHOD(RigidBody, GetMass), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "void set_position(Vector3)", asMETHOD(RigidBody, SetPosition), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "Vector3 get_position() const", asMETHOD(RigidBody, GetPosition), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "void set_rotation(Quaternion)", asMETHOD(RigidBody, SetRotation), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "Quaternion get_rotation() const", asMETHOD(RigidBody, GetRotation), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "void set_linearVelocity(Vector3)", asMETHOD(RigidBody, SetLinearVelocity), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "Vector3 get_linearVelocity() const", asMETHOD(RigidBody, GetLinearVelocity), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "void set_linearFactor(Vector3)", asMETHOD(RigidBody, SetLinearFactor), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "Vector3 get_linearFactor() const", asMETHOD(RigidBody, GetLinearFactor), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "void set_linearRestThreshold(float)", asMETHOD(RigidBody, SetLinearRestThreshold), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "float get_linearRestThreshold() const", asMETHOD(RigidBody, GetLinearRestThreshold), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "void set_linearDamping(float)", asMETHOD(RigidBody, SetLinearDamping), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "float get_linearDamping() const", asMETHOD(RigidBody, GetLinearDamping), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "void set_angularVelocity(Vector3)", asMETHOD(RigidBody, SetAngularVelocity), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "Vector3 get_angularVelocity() const", asMETHOD(RigidBody, GetAngularVelocity), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "void set_angularFactor(Vector3)", asMETHOD(RigidBody, SetAngularFactor), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "Vector3 get_angularFactor() const", asMETHOD(RigidBody, GetAngularFactor), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "void set_angularRestThreshold(float)", asMETHOD(RigidBody, SetAngularRestThreshold), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "float get_angularRestThreshold() const", asMETHOD(RigidBody, GetAngularRestThreshold), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "void set_angularDamping(float)", asMETHOD(RigidBody, SetAngularDamping), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "float get_angularDamping() const", asMETHOD(RigidBody, GetAngularDamping), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "void set_friction(float)", asMETHOD(RigidBody, SetFriction), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "float get_friction() const", asMETHOD(RigidBody, GetFriction), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "void set_restitution(float)", asMETHOD(RigidBody, SetRestitution), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "float get_restitution() const", asMETHOD(RigidBody, GetRestitution), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "void set_useGravity(bool)", asMETHOD(RigidBody, SetUseGravity), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "bool get_useGravity() const", asMETHOD(RigidBody, GetUseGravity), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "void set_phantom(bool)", asMETHOD(RigidBody, SetPhantom), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "bool get_phantom() const", asMETHOD(RigidBody, IsPhantom), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "void set_kinematic(bool)", asMETHOD(RigidBody, SetKinematic), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "bool get_kinematic() const", asMETHOD(RigidBody, IsKinematic), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "bool get_active() const", asMETHOD(RigidBody, IsActive), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "void set_collisionGroup(uint)", asMETHOD(RigidBody, SetCollisionGroup), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "uint get_collisionGroup() const", asMETHOD(RigidBody, GetCollisionGroup), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "void set_collisionMask(uint)", asMETHOD(RigidBody, SetCollisionMask), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "uint get_collisionMask() const", asMETHOD(RigidBody, GetCollisionMask), asCALL_THISCALL);
    
    // Register Variant GetPtr() for RigidBody
    engine->RegisterObjectMethod("Variant", "RigidBody@+ GetRigidBody() const", asFUNCTION(GetVariantPtr<RigidBody>), asCALL_CDECL_OBJLAST);
}

static void RegisterJoint(asIScriptEngine* engine)
{
    engine->RegisterEnum("JointType");
    engine->RegisterEnumValue("JointType", "JOINT_NONE", JOINT_NONE);
    engine->RegisterEnumValue("JointType", "JOINT_BALL", JOINT_BALL);
    engine->RegisterEnumValue("JointType", "JOINT_HINGE", JOINT_HINGE);
    
    RegisterComponent<Joint>(engine, "Joint");
    engine->RegisterObjectMethod("Joint", "void Clear()", asMETHOD(Joint, Clear), asCALL_THISCALL);
    engine->RegisterObjectMethod("Joint", "void DrawDebugGeometry(DebugRenderer@+, bool)", asMETHOD(Joint, DrawDebugGeometry), asCALL_THISCALL);
    engine->RegisterObjectMethod("Joint", "void set_position(const Vector3&in)", asMETHOD(Joint, SetPosition), asCALL_THISCALL);
    engine->RegisterObjectMethod("Joint", "const Vector3& get_position() const", asMETHOD(Joint, GetPosition), asCALL_THISCALL);
    engine->RegisterObjectMethod("Joint", "void set_axis(const Vector3&in)", asMETHOD(Joint, SetAxis), asCALL_THISCALL);
    engine->RegisterObjectMethod("Joint", "const Vector3& get_axis() const", asMETHOD(Joint, GetAxis), asCALL_THISCALL);
    engine->RegisterObjectMethod("Joint", "RigidBody@+ get_ownBody() const", asMETHOD(Joint, GetOwnBody), asCALL_THISCALL);
    engine->RegisterObjectMethod("Joint", "void set_otherBody(RigidBody@+)", asMETHOD(Joint, SetOtherBody), asCALL_THISCALL);
    engine->RegisterObjectMethod("Joint", "RigidBody@+ get_otherBody() const", asMETHOD(Joint, GetOtherBody), asCALL_THISCALL);
    engine->RegisterObjectMethod("Joint", "bool set_jointType(JointType)", asMETHOD(Joint, SetJointType), asCALL_THISCALL);
    engine->RegisterObjectMethod("Joint", "JointType get_jointType() const", asMETHOD(Joint, GetJointType), asCALL_THISCALL);
}

static void RegisterPhysicsWorld(asIScriptEngine* engine)
{
    engine->RegisterObjectType("PhysicsRaycastResult", sizeof(PhysicsRaycastResult), asOBJ_VALUE | asOBJ_POD);
    engine->RegisterObjectBehaviour("PhysicsRaycastResult", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ConstructPhysicsRaycastResult), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectProperty("PhysicsRaycastResult", "Vector3 position", offsetof(PhysicsRaycastResult, position_));
    engine->RegisterObjectProperty("PhysicsRaycastResult", "Vector3 normal", offsetof(PhysicsRaycastResult, normal_));
    engine->RegisterObjectProperty("PhysicsRaycastResult", "float distance", offsetof(PhysicsRaycastResult, distance_));
    engine->RegisterObjectMethod("PhysicsRaycastResult", "RigidBody@+ get_body() const", asFUNCTION(PhysicsRaycastResultGetRigidBody), asCALL_CDECL_OBJLAST);
    
    RegisterComponent<PhysicsWorld>(engine, "PhysicsWorld");
    engine->RegisterObjectMethod("PhysicsWorld", "void Update(float)", asMETHOD(PhysicsWorld, Update), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "Array<PhysicsRaycastResult>@ Raycast(const Ray&in, float maxDistance = M_INFINITY, uint collisionMask = 0xffffffff)", asFUNCTION(PhysicsWorldRaycast), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("PhysicsWorld", "void DrawDebugGeometry(bool)", asMETHOD(PhysicsWorld, DrawDebugGeometry), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "void set_gravity(Vector3)", asMETHOD(PhysicsWorld, SetGravity), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "Vector3 get_gravity() const", asMETHOD(PhysicsWorld, GetGravity), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "void set_fps(int)", asMETHOD(PhysicsWorld, SetFps), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "int get_fps() const", asMETHOD(PhysicsWorld, GetFps), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "void set_interpolation(bool)", asMETHOD(PhysicsWorld, SetInterpolation), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "bool get_interpolation() const", asMETHOD(PhysicsWorld, GetInterpolation), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "PhysicsWorld@+ get_physicsWorld() const", asFUNCTION(SceneGetPhysicsWorld), asCALL_CDECL_OBJLAST);
    engine->RegisterGlobalFunction("PhysicsWorld@+ get_physicsWorld()", asFUNCTION(GetPhysicsWorld), asCALL_CDECL);
    
    // Register Variant GetPtr() for PhysicsWorld
    engine->RegisterObjectMethod("Variant", "PhysicsWorld@+ GetPhysicsWorld() const", asFUNCTION(GetVariantPtr<PhysicsWorld>), asCALL_CDECL_OBJLAST);
}

void RegisterPhysicsAPI(asIScriptEngine* engine)
{
    RegisterCollisionShapes(engine);
    RegisterRigidBody(engine);
    RegisterJoint(engine);
    RegisterPhysicsWorld(engine);
}
