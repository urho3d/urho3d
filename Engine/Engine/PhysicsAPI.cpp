//
// Copyright (c) 2008-2013 the Urho3D project.
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
#include "Constraint.h"
#include "PhysicsWorld.h"
#include "RigidBody.h"
#include "Scene.h"

namespace Urho3D
{

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
    new(ptr) PhysicsRaycastResult();
}

static void DestructPhysicsRaycastResult(PhysicsRaycastResult* ptr)
{
    ptr->~PhysicsRaycastResult();
}

static RigidBody* PhysicsRaycastResultGetRigidBody(PhysicsRaycastResult* ptr)
{
    return ptr->body_;
}

static void RegisterCollisionShape(asIScriptEngine* engine)
{
    engine->RegisterEnum("ShapeType");
    engine->RegisterEnumValue("ShapeType", "SHAPE_BOX", SHAPE_BOX);
    engine->RegisterEnumValue("ShapeType", "SHAPE_SPHERE", SHAPE_SPHERE);
    engine->RegisterEnumValue("ShapeType", "SHAPE_CYLINDER", SHAPE_CYLINDER);
    engine->RegisterEnumValue("ShapeType", "SHAPE_CAPSULE", SHAPE_CAPSULE);
    engine->RegisterEnumValue("ShapeType", "SHAPE_CONE", SHAPE_CONE);
    engine->RegisterEnumValue("ShapeType", "SHAPE_TRIANGLEMESH", SHAPE_TRIANGLEMESH);
    engine->RegisterEnumValue("ShapeType", "SHAPE_CONVEXHULL", SHAPE_CONVEXHULL);
    engine->RegisterEnumValue("ShapeType", "SHAPE_TERRAIN", SHAPE_TERRAIN);
    
    RegisterComponent<CollisionShape>(engine, "CollisionShape");
    engine->RegisterObjectMethod("CollisionShape", "void SetBox(const Vector3&in, const Vector3&in pos = Vector3(), const Quaternion&in rot = Quaternion())", asMETHOD(CollisionShape, SetBox), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape", "void SetSphere(float, const Vector3&in pos = Vector3(), const Quaternion&in rot = Quaternion())", asMETHOD(CollisionShape, SetSphere), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape", "void SetCylinder(float, float, const Vector3&in pos = Vector3(), const Quaternion&in rot = Quaternion())", asMETHOD(CollisionShape, SetCylinder), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape", "void SetCapsule(float, float, const Vector3&in pos = Vector3(), const Quaternion&in rot = Quaternion())", asMETHOD(CollisionShape, SetCapsule), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape", "void SetCone(float, float, const Vector3&in pos = Vector3(), const Quaternion&in rot = Quaternion())", asMETHOD(CollisionShape, SetCone), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape", "void SetTriangleMesh(Model@+, uint, const Vector3&in scale = Vector3(1, 1, 1), const Vector3&in pos = Vector3(), const Quaternion&in rot = Quaternion())", asMETHOD(CollisionShape, SetTriangleMesh), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape", "void SetConvexHull(Model@+, uint, const Vector3&in scale = Vector3(1, 1, 1), const Vector3&in pos = Vector3(), const Quaternion&in rot = Quaternion())", asMETHOD(CollisionShape, SetConvexHull), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape", "void SetCustomConvexHull(CustomGeometry@+, const Vector3&in scale = Vector3(1, 1, 1), const Vector3&in pos = Vector3(), const Quaternion&in rot = Quaternion())", asMETHOD(CollisionShape, SetCustomConvexHull), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape", "void SetTerrain()", asMETHOD(CollisionShape, SetTerrain), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape", "void SetTransform(const Vector3&in, const Quaternion&in)", asMETHOD(CollisionShape, SetTransform), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape", "void set_shapeType(ShapeType)", asMETHOD(CollisionShape, SetShapeType), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape", "ShapeType get_shapeType() const", asMETHOD(CollisionShape, GetShapeType), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape", "void set_size(const Vector3&in)", asMETHOD(CollisionShape, SetSize), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape", "const Vector3& get_size() const", asMETHOD(CollisionShape, GetSize), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape", "void set_position(const Vector3&in)", asMETHOD(CollisionShape, SetPosition), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape", "const Vector3& get_position() const", asMETHOD(CollisionShape, GetPosition), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape", "void set_rotation(const Quaternion&in)", asMETHOD(CollisionShape, SetRotation), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape", "const Quaternion& get_rotation() const", asMETHOD(CollisionShape, GetRotation), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape", "void set_margin(float)", asMETHOD(CollisionShape, SetMargin), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape", "float get_margin() const", asMETHOD(CollisionShape, GetMargin), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape", "void set_model(Model@+)", asMETHOD(CollisionShape, SetModel), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape", "Model@+ get_model() const", asMETHOD(CollisionShape, GetModel), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape", "void set_lodLevel(uint)", asMETHOD(CollisionShape, SetLodLevel), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape", "uint get_lodLevel() const", asMETHOD(CollisionShape, GetLodLevel), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape", "BoundingBox get_worldBoundingBox() const", asMETHOD(CollisionShape, GetWorldBoundingBox), asCALL_THISCALL);
    
    // Register Variant GetPtr() for CollisionShape
    engine->RegisterObjectMethod("Variant", "CollisionShape@+ GetCollisionShape() const", asFUNCTION(GetVariantPtr<CollisionShape>), asCALL_CDECL_OBJLAST);
}

static CScriptArray* RigidBodyGetCollidingBodies(RigidBody* ptr)
{
    PODVector<RigidBody*> result;
    ptr->GetCollidingBodies(result);
    return VectorToHandleArray<RigidBody>(result, "Array<RigidBody@>");
}

static void RegisterRigidBody(asIScriptEngine* engine)
{
    engine->RegisterEnum("CollisionEventMode");
    engine->RegisterEnumValue("CollisionEventMode", "COLLISION_NEVER", COLLISION_NEVER);
    engine->RegisterEnumValue("CollisionEventMode", "COLLISION_ACTIVE", COLLISION_ACTIVE);
    engine->RegisterEnumValue("CollisionEventMode", "COLLISION_ALWAYS", COLLISION_ALWAYS);
    
    RegisterComponent<RigidBody>(engine, "RigidBody");
    engine->RegisterObjectMethod("RigidBody", "void SetTransform(const Vector3&in, const Quaternion&in)", asMETHOD(RigidBody, SetTransform), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "void SetCollisionLayerAndMask(uint, uint)", asMETHOD(RigidBody, SetCollisionLayerAndMask), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "void ApplyForce(const Vector3&in)", asMETHODPR(RigidBody, ApplyForce, (const Vector3&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "void ApplyForce(const Vector3&in, const Vector3&in)", asMETHODPR(RigidBody, ApplyForce, (const Vector3&, const Vector3&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "void ApplyTorque(const Vector3&in)", asMETHOD(RigidBody, ApplyTorque), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "void ApplyImpulse(const Vector3&in)", asMETHODPR(RigidBody, ApplyImpulse, (const Vector3&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "void ApplyImpulse(const Vector3&in, const Vector3&in)", asMETHODPR(RigidBody, ApplyImpulse, (const Vector3&, const Vector3&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "void ApplyTorqueImpulse(const Vector3&in)", asMETHOD(RigidBody, ApplyTorqueImpulse), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "void ResetForces()", asMETHOD(RigidBody, ResetForces), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "void Activate()", asMETHOD(RigidBody, Activate), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "Vector3 GetVelocityAtPoint(const Vector3&in) const", asMETHOD(RigidBody, GetVelocityAtPoint), asCALL_THISCALL);
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
    engine->RegisterObjectMethod("RigidBody", "void set_contactProcessingThreshold(float)", asMETHOD(RigidBody, SetContactProcessingThreshold), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "float get_contactProcessingThreshold() const", asMETHOD(RigidBody, GetContactProcessingThreshold), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "void set_ccdRadius(float)", asMETHOD(RigidBody, SetCcdRadius), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "float get_ccdRadius() const", asMETHOD(RigidBody, GetCcdRadius), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "void set_ccdMotionThreshold(float)", asMETHOD(RigidBody, SetCcdMotionThreshold), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "float get_ccdMotionThreshold() const", asMETHOD(RigidBody, GetCcdMotionThreshold), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "void set_useGravity(bool)", asMETHOD(RigidBody, SetUseGravity), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "bool get_useGravity() const", asMETHOD(RigidBody, GetUseGravity), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "void set_gravityOverride(const Vector3&in)", asMETHOD(RigidBody, SetGravityOverride), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "const Vector3& get_gravityOverride() const", asMETHOD(RigidBody, GetGravityOverride), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "const Vector3& get_centerOfMass() const", asMETHOD(RigidBody, GetCenterOfMass), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "void set_phantom(bool)", asMETHOD(RigidBody, SetPhantom), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "bool get_phantom() const", asMETHOD(RigidBody, IsPhantom), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "void set_kinematic(bool)", asMETHOD(RigidBody, SetKinematic), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "bool get_kinematic() const", asMETHOD(RigidBody, IsKinematic), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "bool get_active() const", asMETHOD(RigidBody, IsActive), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "void set_collisionLayer(uint)", asMETHOD(RigidBody, SetCollisionLayer), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "uint get_collisionLayer() const", asMETHOD(RigidBody, GetCollisionLayer), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "void set_collisionMask(uint)", asMETHOD(RigidBody, SetCollisionMask), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "uint get_collisionMask() const", asMETHOD(RigidBody, GetCollisionMask), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "void set_collisionEventMode(CollisionEventMode)", asMETHOD(RigidBody, SetCollisionEventMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "CollisionEventMode get_collisionEventMode() const", asMETHOD(RigidBody, GetCollisionEventMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "Array<RigidBody@>@ get_collidingBodies() const", asFUNCTION(RigidBodyGetCollidingBodies), asCALL_CDECL_OBJLAST);

    // Register Variant GetPtr() for RigidBody
    engine->RegisterObjectMethod("Variant", "RigidBody@+ GetRigidBody() const", asFUNCTION(GetVariantPtr<RigidBody>), asCALL_CDECL_OBJLAST);
}

static void RegisterConstraint(asIScriptEngine* engine)
{
    engine->RegisterEnum("ConstraintType");
    engine->RegisterEnumValue("ConstraintType", "CONSTRAINT_POINT", CONSTRAINT_POINT);
    engine->RegisterEnumValue("ConstraintType", "CONSTRAINT_HINGE", CONSTRAINT_HINGE);
    engine->RegisterEnumValue("ConstraintType", "CONSTRAINT_SLIDER", CONSTRAINT_SLIDER);
    engine->RegisterEnumValue("ConstraintType", "CONSTRAINT_CONETWIST", CONSTRAINT_CONETWIST);
    
    RegisterComponent<Constraint>(engine, "Constraint");
    engine->RegisterObjectMethod("Constraint", "void set_constraintType(ConstraintType)", asMETHOD(Constraint, SetConstraintType), asCALL_THISCALL);
    engine->RegisterObjectMethod("Constraint", "ConstraintType get_constraintType() const", asMETHOD(Constraint, GetConstraintType), asCALL_THISCALL);
    engine->RegisterObjectMethod("Constraint", "void set_position(const Vector3&in)", asMETHOD(Constraint, SetPosition), asCALL_THISCALL);
    engine->RegisterObjectMethod("Constraint", "const Vector3& get_position() const", asMETHOD(Constraint, GetPosition), asCALL_THISCALL);
    engine->RegisterObjectMethod("Constraint", "void set_rotation(const Quaternion&in)", asMETHOD(Constraint, SetRotation), asCALL_THISCALL);
    engine->RegisterObjectMethod("Constraint", "void set_axis(const Vector3&in)", asMETHOD(Constraint, SetAxis), asCALL_THISCALL);
    engine->RegisterObjectMethod("Constraint", "const Quaternion& get_rotation() const", asMETHOD(Constraint, GetRotation), asCALL_THISCALL);
    engine->RegisterObjectMethod("Constraint", "void set_otherPosition(const Vector3&in)", asMETHOD(Constraint, SetOtherPosition), asCALL_THISCALL);
    engine->RegisterObjectMethod("Constraint", "const Vector3& get_otherPosition() const", asMETHOD(Constraint, GetOtherPosition), asCALL_THISCALL);
    engine->RegisterObjectMethod("Constraint", "void set_otherRotation(const Quaternion&in)", asMETHOD(Constraint, SetOtherRotation), asCALL_THISCALL);
    engine->RegisterObjectMethod("Constraint", "void set_otherAxis(const Vector3&in)", asMETHOD(Constraint, SetOtherAxis), asCALL_THISCALL);
    engine->RegisterObjectMethod("Constraint", "const Quaternion& get_otherRotation() const", asMETHOD(Constraint, GetOtherRotation), asCALL_THISCALL);
    engine->RegisterObjectMethod("Constraint", "void set_worldPosition(const Vector3&in)", asMETHOD(Constraint, SetWorldPosition), asCALL_THISCALL);
    engine->RegisterObjectMethod("Constraint", "Vector3 get_worldPosition() const", asMETHOD(Constraint, GetWorldPosition), asCALL_THISCALL);
    engine->RegisterObjectMethod("Constraint", "void set_highLimit(const Vector2&in)", asMETHOD(Constraint, SetHighLimit), asCALL_THISCALL);
    engine->RegisterObjectMethod("Constraint", "const Vector2& get_highLimit() const", asMETHOD(Constraint, GetHighLimit), asCALL_THISCALL);
    engine->RegisterObjectMethod("Constraint", "void set_lowLimit(const Vector2&in)", asMETHOD(Constraint, SetLowLimit), asCALL_THISCALL);
    engine->RegisterObjectMethod("Constraint", "const Vector2& get_lowLimit() const", asMETHOD(Constraint, GetLowLimit), asCALL_THISCALL);
    engine->RegisterObjectMethod("Constraint", "void set_erp(float)", asMETHOD(Constraint, SetERP), asCALL_THISCALL);
    engine->RegisterObjectMethod("Constraint", "float get_erp() const", asMETHOD(Constraint, GetERP), asCALL_THISCALL);
    engine->RegisterObjectMethod("Constraint", "void set_cfm(float)", asMETHOD(Constraint, SetCFM), asCALL_THISCALL);
    engine->RegisterObjectMethod("Constraint", "float get_cfm() const", asMETHOD(Constraint, GetCFM), asCALL_THISCALL);
    engine->RegisterObjectMethod("Constraint", "void set_disableCollision(bool)", asMETHOD(Constraint, SetDisableCollision), asCALL_THISCALL);
    engine->RegisterObjectMethod("Constraint", "bool get_disableCollision() const" ,asMETHOD(Constraint, GetDisableCollision), asCALL_THISCALL);
    engine->RegisterObjectMethod("Constraint", "RigidBody@+ get_ownBody() const", asMETHOD(Constraint, GetOwnBody), asCALL_THISCALL);
    engine->RegisterObjectMethod("Constraint", "void set_otherBody(RigidBody@+)", asMETHOD(Constraint, SetOtherBody), asCALL_THISCALL);
    engine->RegisterObjectMethod("Constraint", "RigidBody@+ get_otherBody() const", asMETHOD(Constraint, GetOtherBody), asCALL_THISCALL);
}

static CScriptArray* PhysicsWorldRaycast(const Ray& ray, float maxDistance, unsigned collisionMask, PhysicsWorld* ptr)
{
    PODVector<PhysicsRaycastResult> result;
    ptr->Raycast(result, ray, maxDistance, collisionMask);
    return VectorToArray<PhysicsRaycastResult>(result, "Array<PhysicsRaycastResult>");
}

static PhysicsRaycastResult PhysicsWorldRaycastSingle(const Ray& ray, float maxDistance, unsigned collisionMask, PhysicsWorld* ptr)
{
    PhysicsRaycastResult result;
    ptr->RaycastSingle(result, ray, maxDistance, collisionMask);
    return result;
}

static PhysicsRaycastResult PhysicsWorldSphereCast(const Ray& ray, float radius, float maxDistance, unsigned collisionMask, PhysicsWorld* ptr)
{
    PhysicsRaycastResult result;
    ptr->SphereCast(result, ray, radius, maxDistance, collisionMask);
    return result;
}

static CScriptArray* PhysicsWorldGetRigidBodiesSphere(const Sphere& sphere, unsigned collisionMask, PhysicsWorld* ptr)
{
    PODVector<RigidBody*> result;
    ptr->GetRigidBodies(result, sphere, collisionMask);
    return VectorToHandleArray<RigidBody>(result, "Array<RigidBody@>");
}

static CScriptArray* PhysicsWorldGetRigidBodiesBox(const BoundingBox& box, unsigned collisionMask, PhysicsWorld* ptr)
{
    PODVector<RigidBody*> result;
    ptr->GetRigidBodies(result, box, collisionMask);
    return VectorToHandleArray<RigidBody>(result, "Array<RigidBody@>");
}

static CScriptArray* PhysicsWorldGetRigidBodiesBody(RigidBody* body, PhysicsWorld* ptr)
{
    PODVector<RigidBody*> result;
    ptr->GetRigidBodies(result, body);
    return VectorToHandleArray<RigidBody>(result, "Array<RigidBody@>");
}

static void RegisterPhysicsWorld(asIScriptEngine* engine)
{
    engine->RegisterObjectType("PhysicsRaycastResult", sizeof(PhysicsRaycastResult), asOBJ_VALUE | asOBJ_APP_CLASS_C);
    engine->RegisterObjectBehaviour("PhysicsRaycastResult", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ConstructPhysicsRaycastResult), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("PhysicsRaycastResult", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(DestructPhysicsRaycastResult), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("PhysicsRaycastResult", "PhysicsRaycastResult& opAssign(const PhysicsRaycastResult&in)", asMETHODPR(PhysicsRaycastResult, operator =, (const PhysicsRaycastResult&), PhysicsRaycastResult&), asCALL_THISCALL);
    engine->RegisterObjectProperty("PhysicsRaycastResult", "Vector3 position", offsetof(PhysicsRaycastResult, position_));
    engine->RegisterObjectProperty("PhysicsRaycastResult", "Vector3 normal", offsetof(PhysicsRaycastResult, normal_));
    engine->RegisterObjectProperty("PhysicsRaycastResult", "float distance", offsetof(PhysicsRaycastResult, distance_));
    engine->RegisterObjectMethod("PhysicsRaycastResult", "RigidBody@+ get_body() const", asFUNCTION(PhysicsRaycastResultGetRigidBody), asCALL_CDECL_OBJLAST);
    
    RegisterComponent<PhysicsWorld>(engine, "PhysicsWorld");
    engine->RegisterObjectMethod("PhysicsWorld", "void Update(float)", asMETHOD(PhysicsWorld, Update), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "void UpdateCollisions()", asMETHOD(PhysicsWorld, UpdateCollisions), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "Array<PhysicsRaycastResult>@ Raycast(const Ray&in, float maxDistance = M_INFINITY, uint collisionMask = 0xffff)", asFUNCTION(PhysicsWorldRaycast), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("PhysicsWorld", "PhysicsRaycastResult RaycastSingle(const Ray&in, float maxDistance = M_INFINITY, uint collisionMask = 0xffff)", asFUNCTION(PhysicsWorldRaycastSingle), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("PhysicsWorld", "PhysicsRaycastResult SphereCast(const Ray&in, float, float maxDistance = M_INFINITY, uint collisionMask = 0xffff)", asFUNCTION(PhysicsWorldSphereCast), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("PhysicsWorld", "Array<RigidBody@>@ GetRigidBodies(const Sphere&in, uint collisionMask = 0xffff)", asFUNCTION(PhysicsWorldGetRigidBodiesSphere), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("PhysicsWorld", "Array<RigidBody@>@ GetRigidBodies(const BoundingBox&in, uint collisionMask = 0xffff)", asFUNCTION(PhysicsWorldGetRigidBodiesBox), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("PhysicsWorld", "Array<RigidBody@>@ GetRigidBodies(RigidBody@+)", asFUNCTION(PhysicsWorldGetRigidBodiesBody), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("PhysicsWorld", "void DrawDebugGeometry(bool)", asMETHODPR(PhysicsWorld, DrawDebugGeometry, (bool), void), asCALL_THISCALL);
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
    RegisterCollisionShape(engine);
    RegisterRigidBody(engine);
    RegisterConstraint(engine);
    RegisterPhysicsWorld(engine);
}

}
