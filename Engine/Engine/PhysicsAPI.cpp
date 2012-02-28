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
#include "CollisionShape.h"
#include "Joint.h"
#include "PhysicsWorld.h"
#include "RigidBody.h"
#include "Scene.h"

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
    ptr->collisionShape_ = 0;
}

static CollisionShape* PhysicsRaycastResultGetCollisionShape(PhysicsRaycastResult* ptr)
{
    return ptr->collisionShape_;
}

static CScriptArray* PhysicsWorldRaycast(const Ray& ray, float maxDistance, unsigned collisionMask, PhysicsWorld* ptr)
{
    static PODVector<PhysicsRaycastResult> result;
    ptr->Raycast(result, ray, maxDistance, collisionMask);
    return VectorToArray<PhysicsRaycastResult>(result, "Array<PhysicsRaycastResult>");
}

static void RegisterCollisionShape(asIScriptEngine* engine)
{
    engine->RegisterEnum("ShapeType");
    engine->RegisterEnumValue("ShapeType", "SHAPE_NONE", SHAPE_NONE);
    engine->RegisterEnumValue("ShapeType", "SHAPE_BOX", SHAPE_BOX);
    engine->RegisterEnumValue("ShapeType", "SHAPE_SPHERE", SHAPE_SPHERE);
    engine->RegisterEnumValue("ShapeType", "SHAPE_CAPSULE", SHAPE_CAPSULE);
    engine->RegisterEnumValue("ShapeType", "SHAPE_CYLINDER", SHAPE_CYLINDER);
    engine->RegisterEnumValue("ShapeType", "SHAPE_TRIANGLEMESH", SHAPE_TRIANGLEMESH);
    engine->RegisterEnumValue("ShapeType", "SHAPE_HEIGHTFIELD", SHAPE_HEIGHTFIELD);
    engine->RegisterEnumValue("ShapeType", "SHAPE_CONVEXHULL", SHAPE_CONVEXHULL);
    
    RegisterComponent<CollisionShape>(engine, "CollisionShape");
    engine->RegisterObjectMethod("CollisionShape", "void Clear()", asMETHOD(CollisionShape, Clear), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape", "void SetSphere(float, const Vector3&in pos = Vector3(), const Quaternion&in rot = Quaternion())", asMETHOD(CollisionShape, SetSphere), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape", "void SetBox(const Vector3&in, const Vector3&in pos = Vector3(), const Quaternion&in rot = Quaternion())", asMETHOD(CollisionShape, SetBox), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape", "void SetCylinder(float, float, const Vector3&in pos = Vector3(), const Quaternion&in rot = Quaternion())", asMETHOD(CollisionShape, SetCylinder), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape", "void SetCapsule(float, float, const Vector3&in pos = Vector3(), const Quaternion&in rot = Quaternion())", asMETHOD(CollisionShape, SetCapsule), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape", "void SetTriangleMesh(Model@+, uint, const Vector3&in scale = Vector3(1, 1, 1), const Vector3&in pos = Vector3(), const Quaternion&in rot = Quaternion())", asMETHOD(CollisionShape, SetTriangleMesh), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape", "void SetHeightfield(Model@+, uint, uint, float, uint, const Vector3&in scale = Vector3(1, 1, 1), const Vector3&in pos = Vector3(), const Quaternion&in rot = Quaternion())", asMETHOD(CollisionShape, SetHeightfield), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape", "void SetConvexHull(Model@+, float, uint, const Vector3&in scale = Vector3(1, 1, 1), const Vector3&in pos = Vector3(), const Quaternion&in rot = Quaternion())", asMETHOD(CollisionShape, SetConvexHull), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape", "void SetTransform(const Vector3&in, const Quaternion&in)", asMETHOD(CollisionShape, SetTransform), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape", "void DrawDebugGeometry(DebugRenderer@+, bool)", asMETHOD(CollisionShape, DrawDebugGeometry), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape", "Model@+ get_model()", asMETHOD(CollisionShape, GetModel), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape", "ShapeType get_shapeType()", asMETHOD(CollisionShape, GetShapeType), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape", "void set_position(const Vector3&in)", asMETHOD(CollisionShape, SetPosition), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape", "const Vector3& get_position() const", asMETHOD(CollisionShape, GetPosition), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape", "void set_rotation(const Quaternion&in)", asMETHOD(CollisionShape, SetRotation), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape", "const Quaternion& get_rotation() const", asMETHOD(CollisionShape, GetRotation), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape", "void set_collisionLayer(uint)", asMETHOD(CollisionShape, SetCollisionLayer), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape", "uint get_collisionLayer() const", asMETHOD(CollisionShape, GetCollisionLayer), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape", "void set_collisionMask(uint)", asMETHOD(CollisionShape, SetCollisionMask), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape", "uint get_collisionMask() const", asMETHOD(CollisionShape, GetCollisionMask), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape", "void set_friction(float)", asMETHOD(CollisionShape, SetFriction), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape", "float get_friction() const", asMETHOD(CollisionShape, GetFriction), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape", "void set_bounce(float)", asMETHOD(CollisionShape, SetBounce), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape", "float get_bounce() const", asMETHOD(CollisionShape, GetBounce), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape", "void set_phantom(bool)", asMETHOD(CollisionShape, SetPhantom), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape", "bool get_phantom() const", asMETHOD(CollisionShape, IsPhantom), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape", "BoundingBox get_worldBoundingBox() const", asMETHOD(CollisionShape, GetWorldBoundingBox), asCALL_THISCALL);
    
    // Register Variant GetPtr() for CollisionShape
    engine->RegisterObjectMethod("Variant", "CollisionShape@+ GetCollisionShape() const", asFUNCTION(GetVariantPtr<CollisionShape>), asCALL_CDECL_OBJLAST);
}

static void RegisterRigidBody(asIScriptEngine* engine)
{
    RegisterComponent<RigidBody>(engine, "RigidBody");
    engine->RegisterObjectMethod("RigidBody", "void SetTransform(const Vector3&in, const Quaternion&in)", asMETHOD(RigidBody, SetTransform), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "void ApplyForce(const Vector3&in)", asMETHOD(RigidBody, ApplyForce), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "void ApplyForceAtPosition(const Vector3&in, const Vector3&in)", asMETHOD(RigidBody, ApplyForceAtPosition), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "void ApplyTorque(const Vector3&in)", asMETHOD(RigidBody, ApplyTorque), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "void ResetForces()", asMETHOD(RigidBody, ResetForces), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "void set_mass(float)", asMETHOD(RigidBody, SetMass), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "float get_mass() const", asMETHOD(RigidBody, GetMass), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "void set_massAxis(int)", asMETHOD(RigidBody, SetMassAxis), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "int get_massAxis() const", asMETHOD(RigidBody, GetMassAxis), asCALL_THISCALL),
    engine->RegisterObjectMethod("RigidBody", "void set_linearVelocity(const Vector3&in)", asMETHOD(RigidBody, SetLinearVelocity), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "const Vector3& get_linearVelocity() const", asMETHOD(RigidBody, GetLinearVelocity), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "void set_linearRestThreshold(float)", asMETHOD(RigidBody, SetLinearRestThreshold), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "float get_linearRestThreshold() const", asMETHOD(RigidBody, GetLinearRestThreshold), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "void set_angularVelocity(const Vector3&in)", asMETHOD(RigidBody, SetAngularVelocity), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "const Vector3& get_angularVelocity() const", asMETHOD(RigidBody, GetAngularVelocity), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "void set_angularRestThreshold(float)", asMETHOD(RigidBody, SetAngularRestThreshold), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "float get_angularRestThreshold() const", asMETHOD(RigidBody, GetAngularRestThreshold), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "void set_angularMaxVelocity(float)", asMETHOD(RigidBody, SetAngularMaxVelocity), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "float get_angularMaxVelocity() const", asMETHOD(RigidBody, GetAngularMaxVelocity), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "void set_active(bool)", asMETHOD(RigidBody, SetActive), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "bool get_active() const", asMETHOD(RigidBody, IsActive), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "void set_position(const Vector3&in)", asMETHOD(RigidBody, SetPosition), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "const Vector3& get_position() const", asMETHOD(RigidBody, GetPosition), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "void set_rotation(const Quaternion&in)", asMETHOD(RigidBody, SetRotation), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "const Quaternion& get_rotation() const", asMETHOD(RigidBody, GetRotation), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "void set_linearDampingThreshold(float)", asMETHOD(RigidBody, SetLinearDampingThreshold), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "float get_linearDampingThreshold() const", asMETHOD(RigidBody, GetLinearDampingThreshold), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "void set_linearDampingScale(float)", asMETHOD(RigidBody, SetLinearDampingScale), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "float get_linearDampingScale() const", asMETHOD(RigidBody, GetLinearDampingScale), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "void set_angularDampingThreshold(float)", asMETHOD(RigidBody, SetAngularDampingThreshold), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "float get_angularDampingThreshold() const", asMETHOD(RigidBody, GetAngularDampingThreshold), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "void set_angularDampingScale(float)", asMETHOD(RigidBody, SetAngularDampingScale), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "float get_angularDampingScale() const", asMETHOD(RigidBody, GetAngularDampingScale), asCALL_THISCALL);
    
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
    engine->RegisterObjectMethod("Joint", "bool SetBall(const Vector3&in, RigidBody@+, RigidBody@+)", asMETHOD(Joint, SetBall), asCALL_THISCALL);
    engine->RegisterObjectMethod("Joint", "bool SetHinge(const Vector3&in, const Vector3&in, RigidBody@+, RigidBody@+)", asMETHOD(Joint, SetHinge), asCALL_THISCALL);
    engine->RegisterObjectMethod("Joint", "void set_position(Vector3)", asMETHOD(Joint, SetPosition), asCALL_THISCALL);
    engine->RegisterObjectMethod("Joint", "Vector3 get_position() const", asMETHOD(Joint, GetPosition), asCALL_THISCALL);
    engine->RegisterObjectMethod("Joint", "void set_axis(Vector3)", asMETHOD(Joint, SetAxis), asCALL_THISCALL);
    engine->RegisterObjectMethod("Joint", "Vector3 get_axis() const", asMETHOD(Joint, GetAxis), asCALL_THISCALL);
    engine->RegisterObjectMethod("Joint", "RigidBody@+ get_bodyA() const", asMETHOD(Joint, GetBodyA), asCALL_THISCALL);
    engine->RegisterObjectMethod("Joint", "RigidBody@+ get_bodyB() const", asMETHOD(Joint, GetBodyB), asCALL_THISCALL);
    engine->RegisterObjectMethod("Joint", "JointType get_jointType() const", asMETHOD(Joint, GetJointType), asCALL_THISCALL);
}

static void RegisterPhysicsWorld(asIScriptEngine* engine)
{
    engine->RegisterObjectType("PhysicsRaycastResult", sizeof(PhysicsRaycastResult), asOBJ_VALUE | asOBJ_POD);
    engine->RegisterObjectBehaviour("PhysicsRaycastResult", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ConstructPhysicsRaycastResult), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectProperty("PhysicsRaycastResult", "Vector3 position", offsetof(PhysicsRaycastResult, position_));
    engine->RegisterObjectProperty("PhysicsRaycastResult", "Vector3 normal", offsetof(PhysicsRaycastResult, normal_));
    engine->RegisterObjectProperty("PhysicsRaycastResult", "float distance", offsetof(PhysicsRaycastResult, distance_));
    engine->RegisterObjectMethod("PhysicsRaycastResult", "CollisionShape@+ get_collisionShape() const", asFUNCTION(PhysicsRaycastResultGetCollisionShape), asCALL_CDECL_OBJLAST);
    
    RegisterComponent<PhysicsWorld>(engine, "PhysicsWorld");
    engine->RegisterObjectMethod("PhysicsWorld", "void Update(float)", asMETHOD(PhysicsWorld, Update), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "Array<PhysicsRaycastResult>@ Raycast(const Ray&in, float maxDistance = M_INFINITY, uint collisionMask = 0xffffffff)", asFUNCTION(PhysicsWorldRaycast), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("PhysicsWorld", "void DrawDebugGeometry(bool)", asMETHOD(PhysicsWorld, DrawDebugGeometry), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "void set_gravity(Vector3)", asMETHOD(PhysicsWorld, SetGravity), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "Vector3 get_gravity() const", asMETHOD(PhysicsWorld, GetGravity), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "void set_fps(int)", asMETHOD(PhysicsWorld, SetFps), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "int get_fps() const", asMETHOD(PhysicsWorld, GetFps), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "void set_maxContacts(uint)", asMETHOD(PhysicsWorld, SetMaxContacts), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "uint get_maxContacts() const", asMETHOD(PhysicsWorld, GetMaxContacts), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "void set_interpolation(bool)", asMETHOD(PhysicsWorld, SetInterpolation), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "bool get_interpolation() const", asMETHOD(PhysicsWorld, GetInterpolation), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "void set_linearRestThreshold(float)", asMETHOD(PhysicsWorld, SetLinearRestThreshold), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "float get_linearRestThreshold() const", asMETHOD(PhysicsWorld, GetLinearRestThreshold), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "void set_angularRestThreshold(float)", asMETHOD(PhysicsWorld, SetAngularRestThreshold), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "float get_angularRestThreshold() const", asMETHOD(PhysicsWorld, GetAngularRestThreshold), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "void set_bounceThreshold(float)", asMETHOD(PhysicsWorld, SetBounceThreshold), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "float get_bounceThreshold() const", asMETHOD(PhysicsWorld, GetBounceThreshold), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "void set_erp(float)", asMETHOD(PhysicsWorld, SetERP), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "float get_erp() const", asMETHOD(PhysicsWorld, GetERP), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "void set_cfm(float)", asMETHOD(PhysicsWorld, SetCFM), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "float get_cfm() const", asMETHOD(PhysicsWorld, GetCFM), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "void set_contactSurfaceLayer(float)", asMETHOD(PhysicsWorld, SetContactSurfaceLayer), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "float get_contactSurfaceLayer() const", asMETHOD(PhysicsWorld, GetContactSurfaceLayer), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "void set_linearDampingThreshold(float)", asMETHOD(PhysicsWorld, SetLinearDampingThreshold), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "float get_linearDampingThreshold() const", asMETHOD(PhysicsWorld, GetLinearDampingThreshold), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "void set_linearDampingScale(float)", asMETHOD(PhysicsWorld, SetLinearDampingScale), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "float get_linearDampingScale() const", asMETHOD(PhysicsWorld, GetLinearDampingScale), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "void set_angularDampingThreshold(float)", asMETHOD(PhysicsWorld, SetAngularDampingThreshold), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "float get_angularDampingThreshold() const", asMETHOD(PhysicsWorld, GetAngularDampingThreshold), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "void set_angularDampingScale(float)", asMETHOD(PhysicsWorld, SetAngularDampingScale), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "float get_angularDampingScale() const", asMETHOD(PhysicsWorld, GetAngularDampingScale), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "PhysicsWorld@+ get_physicsWorld() const", asFUNCTION(SceneGetPhysicsWorld), asCALL_CDECL_OBJLAST);
    engine->RegisterGlobalFunction("PhysicsWorld@+ get_physicsWorld()", asFUNCTION(GetPhysicsWorld), asCALL_CDECL);
    
    // Register Variant GetPtr() for PhysicsWorld
    engine->RegisterObjectMethod("Variant", "PhysicsWorld@+ GetPhysicsWorld() const", asFUNCTION(GetVariantPtr<PhysicsWorld>), asCALL_CDECL_OBJLAST);
}

void RegisterPhysicsAPI(asIScriptEngine* engine)
{
    RegisterCollisionShape(engine);
    RegisterRigidBody(engine);
    RegisterJoint(engine);
    RegisterPhysicsWorld(engine);
}
