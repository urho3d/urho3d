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

#include "Precompiled.h"
#include "Joint.h"
#include "PhysicsWorld.h"
#include "RegisterTemplates.h"
#include "RigidBody.h"
#include "Scene.h"
#include "ScriptInstance.h"

#include <angelscript.h>

static PhysicsWorld* SceneGetPhysicsWorld(Scene* ptr)
{
    return ptr->getExtension<PhysicsWorld>();
}

static PhysicsWorld* GetPhysicsWorld()
{
    Scene* scene = getScriptContextScene();
    return scene ? scene->getExtension<PhysicsWorld>() : 0;
}

static void ConstructPhysicsRaycastResult(PhysicsRaycastResult* ptr)
{
    ptr->mPosition = Vector3::sZero;
    ptr->mNormal = Vector3::sZero;
    ptr->mDistance = 0.0f;
    ptr->mBody = 0;
}

static RigidBody* PhysicsRaycastResultGetBody(PhysicsRaycastResult* ptr)
{
    return ptr->mBody;
}

static CScriptArray* PhysicsWorldRaycast(const Ray& ray, float maxDistance, unsigned collisionMask, PhysicsWorld* ptr)
{
    static std::vector<PhysicsRaycastResult> result;
    ptr->raycast(result, ray, maxDistance, collisionMask);
    return vectorToArray<PhysicsRaycastResult>(result, "array<PhysicsRaycastResult>");
}

static void registerPhysicsWorld(asIScriptEngine* engine)
{
    registerNode<RigidBody>(engine, "RigidBody");
    
    engine->RegisterObjectType("PhysicsRaycastResult", sizeof(PhysicsRaycastResult), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_C);
    engine->RegisterObjectBehaviour("PhysicsRaycastResult", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ConstructPhysicsRaycastResult), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectProperty("PhysicsRaycastResult", "Vector3 position", offsetof(PhysicsRaycastResult, mPosition));
    engine->RegisterObjectProperty("PhysicsRaycastResult", "Vector3 normal", offsetof(PhysicsRaycastResult, mNormal));
    engine->RegisterObjectProperty("PhysicsRaycastResult", "float distance", offsetof(PhysicsRaycastResult, mDistance));
    engine->RegisterObjectMethod("PhysicsRaycastResult", "RigidBody@+ get_body() const", asFUNCTION(PhysicsRaycastResultGetBody), asCALL_CDECL_OBJLAST);
    
    registerHashedType<PhysicsWorld>(engine, "PhysicsWorld");
    engine->RegisterObjectMethod("PhysicsWorld", "void update(float)", asMETHOD(PhysicsWorld, update), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "void setGravity(const Vector3& in)", asMETHOD(PhysicsWorld, setGravity), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "void setFps(int)", asMETHOD(PhysicsWorld, setFps), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "void setMaxContacts(uint)", asMETHOD(PhysicsWorld, setMaxContacts), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "void setLinearRestThreshold(float)", asMETHOD(PhysicsWorld, setLinearRestThreshold), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "void setLinearDamping(float, float)", asMETHOD(PhysicsWorld, setLinearDamping), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "void setAngularRestThreshold(float)", asMETHOD(PhysicsWorld, setAngularRestThreshold), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "void setAngularDamping(float, float)", asMETHOD(PhysicsWorld, setAngularDamping), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "void setAngularMaxNetVelocity(float)", asMETHOD(PhysicsWorld, setAngularMaxNetVelocity), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "void setBounceThreshold(float)", asMETHOD(PhysicsWorld, setBounceThreshold), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "void setERP(float)", asMETHOD(PhysicsWorld, setERP), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "void setCFM(float)", asMETHOD(PhysicsWorld, setCFM), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "void setContactSurfaceLayer(float)", asMETHOD(PhysicsWorld, setContactSurfaceLayer), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "void setRandomSeed(uint)", asMETHOD(PhysicsWorld, setRandomSeed), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "void drawDebugGeometry(bool)", asMETHOD(PhysicsWorld, drawDebugGeometry), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "array<PhysicsRaycastResult>@ raycast(const Ray& in, float, uint)", asFUNCTION(PhysicsWorldRaycast), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("PhysicsWorld", "Vector3 getGravity() const", asMETHOD(PhysicsWorld, getGravity), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "int getFps() const", asMETHOD(PhysicsWorld, getFps), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "uint getMaxContacts() const", asMETHOD(PhysicsWorld, getMaxContacts), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "float getLinearRestThreshold() const", asMETHOD(PhysicsWorld, getLinearRestThreshold), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "float getLinearDampingThreshold() const", asMETHOD(PhysicsWorld, getLinearDampingThreshold), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "float getLinearDampingScale() const", asMETHOD(PhysicsWorld, getLinearDampingScale), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "float getAngularRestThreshold() const", asMETHOD(PhysicsWorld, getAngularRestThreshold), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "float getAngularDampingThreshold() const", asMETHOD(PhysicsWorld, getAngularDampingThreshold), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "float getAngularDampingScale() const", asMETHOD(PhysicsWorld, getAngularDampingScale), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "float getAngularMaxNetVelocity() const", asMETHOD(PhysicsWorld, getAngularMaxNetVelocity), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "float getBounceThreshold() const", asMETHOD(PhysicsWorld, getBounceThreshold), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "float getERP() const", asMETHOD(PhysicsWorld, getERP), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "float getCFM() const", asMETHOD(PhysicsWorld, getCFM), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "float getContactSurfaceLayer() const", asMETHOD(PhysicsWorld, getContactSurfaceLayer), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "uint getRandomSeed() const", asMETHOD(PhysicsWorld, getRandomSeed), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "PhysicsWorld@+ getPhysicsWorld() const", asFUNCTION(SceneGetPhysicsWorld), asCALL_CDECL_OBJLAST);
    registerRefCasts<EventListener, PhysicsWorld>(engine, "EventListener", "PhysicsWorld");
    
    engine->RegisterGlobalFunction("PhysicsWorld@+ getPhysicsWorld()", asFUNCTION(GetPhysicsWorld), asCALL_CDECL);
    engine->RegisterGlobalFunction("PhysicsWorld@+ get_physicsWorld()", asFUNCTION(GetPhysicsWorld), asCALL_CDECL);
    
    // Register Variant getPtr() for PhysicsWorld
    engine->RegisterObjectMethod("Variant", "PhysicsWorld@+ getPhysicsWorld() const", asFUNCTION(getVariantPtr<PhysicsWorld>), asCALL_CDECL_OBJLAST);
}

static CollisionShape* ConstructCollisionShape(const std::string& name)
{
    return new CollisionShape(name);
}

static void CollisionShapeSave(File* file, CollisionShape* ptr)
{
    if (!file)
        SAFE_EXCEPTION("Null destination file");
    
    TRY_SAFE_RETHROW(ptr->save(*file));
}

static void CollisionShapeAddTriangleMesh(const Model* model, unsigned lodLevel, const Vector3& position, const Quaternion& rotation, CollisionShape* ptr)
{
    TRY_SAFE_RETHROW(ptr->addTriangleMesh(model, lodLevel, position, rotation));
}

static void CollisionShapeAddHeightfield(const Model* model, unsigned xPoints, unsigned zPoints, float thickness, unsigned lodLevel, const Vector3& position, const Quaternion& rotation, CollisionShape* ptr)
{
    TRY_SAFE_RETHROW(ptr->addHeightfield(model, xPoints, zPoints, thickness, lodLevel, position, rotation));
}

static void CollisionShapeAddConvexHull(const Model* model, float skinWidth, unsigned lodLevel, const Vector3& position, const Quaternion& rotation, CollisionShape* ptr)
{
    TRY_SAFE_RETHROW(ptr->addConvexHull(model, skinWidth, lodLevel, position, rotation));
}

static void registerCollisionShape(asIScriptEngine* engine)
{
    registerResource<CollisionShape>(engine, "CollisionShape");
    engine->RegisterObjectBehaviour("CollisionShape", asBEHAVE_FACTORY, "CollisionShape@+ f(const string& in)", asFUNCTION(ConstructCollisionShape), asCALL_CDECL);
    engine->RegisterObjectMethod("CollisionShape", "void save(File@+)", asFUNCTION(CollisionShapeSave), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("CollisionShape", "void addSphere(float, const Vector3& in, const Quaternion& in)", asMETHOD(CollisionShape, addSphere), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape", "void addBox(const Vector3& in, const Vector3& in, const Quaternion& in)", asMETHOD(CollisionShape, addBox), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape", "void addCylinder(float, float, const Vector3& in, const Quaternion& in)", asMETHOD(CollisionShape, addCylinder), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape", "void addCapsule(float, float, const Vector3& in, const Quaternion& in)", asMETHOD(CollisionShape, addCapsule), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape", "void addTriangleMesh(Model@+, uint, const Vector3& in, const Quaternion& in)", asFUNCTION(CollisionShapeAddTriangleMesh), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("CollisionShape", "void addHeightfield(Model@+, uint, uint, float, uint, const Vector3& in, const Quaternion& in)", asFUNCTION(CollisionShapeAddHeightfield), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("CollisionShape", "void addConvexHull(Model@+, float, uint, const Vector3& in, const Quaternion& in)", asFUNCTION(CollisionShapeAddConvexHull), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("CollisionShape", "void clear()", asMETHOD(CollisionShape, clear), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionShape", "uint getNumSubShapes() const", asMETHOD(CollisionShape, getNumSubShapes), asCALL_THISCALL);
    registerRefCasts<Resource, CollisionShape>(engine, "Resource", "CollisionShape");
}

static void registerRigidBody(asIScriptEngine* engine)
{
    engine->RegisterEnum("PhysicsMode");
    engine->RegisterEnumValue("PhysicsMode", "PHYS_STATIC", PHYS_STATIC);
    engine->RegisterEnumValue("PhysicsMode", "PHYS_DYNAMIC", PHYS_DYNAMIC);
    engine->RegisterEnumValue("PhysicsMode", "PHYS_KINEMATIC", PHYS_KINEMATIC);
    
    engine->RegisterObjectMethod("RigidBody", "void setMode(PhysicsMode)", asMETHOD(RigidBody, setMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "void setMass(float)", asMETHOD(RigidBody, setMass), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "void setFriction(float)", asMETHOD(RigidBody, setFriction), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "void setBounce(float)", asMETHOD(RigidBody, setBounce), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "void setCollisionShape(CollisionShape@+)", asMETHOD(RigidBody, setCollisionShape), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "void setCollisionGroup(uint)", asMETHOD(RigidBody, setCollisionGroup), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "void setCollisionMask(uint)", asMETHOD(RigidBody, setCollisionMask), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "void setLinearVelocity(const Vector3& in)", asMETHOD(RigidBody, setLinearVelocity), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "void setLinearRestThreshold(float)", asMETHOD(RigidBody, setLinearRestThreshold), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "void setLinearDamping(float, float)", asMETHOD(RigidBody, setLinearDamping), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "void setAngularVelocity(const Vector3& in)", asMETHOD(RigidBody, setAngularVelocity), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "void setAngularRestThreshold(float)", asMETHOD(RigidBody, setAngularRestThreshold), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "void setAngularDamping(float, float)", asMETHOD(RigidBody, setAngularDamping), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "void setAngularMaxVelocity(float)", asMETHOD(RigidBody, setAngularMaxVelocity), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "void setActive(bool)", asMETHOD(RigidBody, setActive), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "void applyForce(const Vector3& in)", asMETHOD(RigidBody, applyForce), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "void applyForceAtPosition(const Vector3& in, const Vector3& in)", asMETHOD(RigidBody, applyForceAtPosition), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "void applyTorque(const Vector3& in)", asMETHOD(RigidBody, applyTorque), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "void resetForces()", asMETHOD(RigidBody, resetForces), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "void drawDebugGeometry(DebugRenderer@+, bool)", asMETHOD(RigidBody, drawDebugGeometry), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "PhysicsWorld@+ getPhysicsWorld() const", asMETHOD(RigidBody, getPhysicsWorld), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "CollisionShape@+ getCollisionShape() const", asMETHOD(RigidBody, getCollisionShape), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "PhysicsMode getMode() const", asMETHOD(RigidBody, getMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "float getMass() const", asMETHOD(RigidBody, getMass), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "float getFriction() const", asMETHOD(RigidBody, getFriction), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "float getBounce() const", asMETHOD(RigidBody, getBounce), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "uint getCollisionGroup() const", asMETHOD(RigidBody, getCollisionGroup), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "uint getCollisionMask() const", asMETHOD(RigidBody, getCollisionMask), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "Vector3 getPhysicsPosition() const", asMETHOD(RigidBody, getPhysicsPosition), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "Quaternion getPhysicsRotation() const", asMETHOD(RigidBody, getPhysicsRotation), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "Vector3 getLinearVelocity() const", asMETHOD(RigidBody, getLinearVelocity), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "float getLinearRestThreshold() const", asMETHOD(RigidBody, getLinearRestThreshold), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "float getLinearDampingThreshold() const", asMETHOD(RigidBody, getLinearDampingThreshold), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "float getLinearDampingScale() const", asMETHOD(RigidBody, getLinearDampingScale), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "Vector3 getAngularVelocity() const", asMETHOD(RigidBody, getAngularVelocity), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "float getAngularRestThreshold() const", asMETHOD(RigidBody, getAngularRestThreshold), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "float getAngularDampingThreshold() const", asMETHOD(RigidBody, getAngularDampingThreshold), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "float getAngularDampingScale() const", asMETHOD(RigidBody, getAngularDampingScale), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "float getAngularMaxVelocity() const", asMETHOD(RigidBody, getAngularMaxVelocity), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "bool isActive() const", asMETHOD(RigidBody, isActive), asCALL_THISCALL);
    registerRefCasts<Component, RigidBody>(engine, "Component", "RigidBody");
    registerRefCasts<Node, RigidBody>(engine, "Node", "RigidBody");
    
    // Register Variant getPtr() for RigidBody
    engine->RegisterObjectMethod("Variant", "RigidBody@+ getRigidBody() const", asFUNCTION(getVariantPtr<RigidBody>), asCALL_CDECL_OBJLAST);
}

static void registerJoint(asIScriptEngine* engine)
{
    engine->RegisterEnum("JointType");
    engine->RegisterEnumValue("JointType", "JOINT_NONE", JOINT_NONE);
    engine->RegisterEnumValue("JointType", "JOINT_BALL", JOINT_BALL);
    engine->RegisterEnumValue("JointType", "JOINT_HINGE", JOINT_HINGE);
    
    registerComponent<Joint>(engine, "Joint");
    engine->RegisterObjectMethod("Joint", "void reset()", asMETHOD(Joint, reset), asCALL_THISCALL);
    engine->RegisterObjectMethod("Joint", "bool setBall(const Vector3& in, RigidBody@+, RigidBody@+)", asMETHOD(Joint, setBall), asCALL_THISCALL);
    engine->RegisterObjectMethod("Joint", "bool setHinge(const Vector3& in, const Vector3& in, RigidBody@+, RigidBody@+)", asMETHOD(Joint, setHinge), asCALL_THISCALL);
    engine->RegisterObjectMethod("Joint", "void setPosition(const Vector3& in)", asMETHOD(Joint, setPosition), asCALL_THISCALL);
    engine->RegisterObjectMethod("Joint", "void setAxis(const Vector3& in)", asMETHOD(Joint, setAxis), asCALL_THISCALL);
    engine->RegisterObjectMethod("Joint", "PhysicsWorld@+ getPhysicsWorld() const", asMETHOD(Joint, getPhysicsWorld), asCALL_THISCALL);
    engine->RegisterObjectMethod("Joint", "RigidBody@+ getBodyA() const", asMETHOD(Joint, getBodyA), asCALL_THISCALL);
    engine->RegisterObjectMethod("Joint", "RigidBody@+ getBodyB() const", asMETHOD(Joint, getBodyB), asCALL_THISCALL);
    engine->RegisterObjectMethod("Joint", "JointType getJointType() const", asMETHOD(Joint, getJointType), asCALL_THISCALL);
    engine->RegisterObjectMethod("Joint", "Vector3 getPosition() const", asMETHOD(Joint, getPosition), asCALL_THISCALL);
    engine->RegisterObjectMethod("Joint", "Vector3 getAxis() const", asMETHOD(Joint, getAxis), asCALL_THISCALL);
    registerRefCasts<Component, Joint>(engine, "Component", "Joint");
}

void registerPhysicsLibrary(asIScriptEngine* engine)
{
    registerPhysicsWorld(engine);
    registerCollisionShape(engine);
    registerRigidBody(engine);
    registerJoint(engine);
}
