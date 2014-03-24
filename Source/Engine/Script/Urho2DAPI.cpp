//
// Copyright (c) 2008-2014 the Urho3D project.
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
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRNTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

#include "Precompiled.h"
#include "APITemplates.h"
#include "AnimatedSprite2D.h"
#include "Animation2D.h"
#include "CollisionBox2D.h"
#include "CollisionChain2D.h"
#include "CollisionCircle2D.h"
#include "CollisionEdge2D.h"
#include "CollisionPolygon2D.h"
#include "CollisionShape2D.h"
#include "Constraint2D.h"
#include "ConstraintDistance2D.h"
#include "ConstraintFriction2D.h"
#include "ConstraintGear2D.h"
#include "ConstraintMotor2D.h"
#include "ConstraintMouse2D.h"
#include "ConstraintPrismatic2D.h"
#include "ConstraintPulley2D.h"
#include "ConstraintRevolute2D.h"
#include "ConstraintWeld2D.h"
#include "ConstraintWheel2D.h"
#include "ConstraintRope2D.h"
#include "Drawable2D.h"
#include "ParticleEffect2D.h"
#include "ParticleEmitter2D.h"
#include "PhysicsWorld2D.h"
#include "RigidBody2D.h"
#include "Scene.h"
#include "Sprite2D.h"
#include "SpriteSheet2D.h"
#include "StaticSprite2D.h"

#ifdef _MSC_VER
#pragma warning(disable:4345)
#endif

namespace Urho3D
{

static void RegisterSprite2D(asIScriptEngine* engine)
{
    RegisterResource<Sprite2D>(engine, "Sprite2D");
    engine->RegisterObjectMethod("Sprite2D", "void set_texture(Texture2D@+)", asMETHOD(Sprite2D, SetTexture), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite2D", "Texture2D@+ get_texture() const", asMETHOD(Sprite2D, GetTexture), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite2D", "void set_rectangle(const IntRect&in)", asMETHOD(Sprite2D, SetRectangle), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite2D", "const IntRect& get_rectangle() const", asMETHOD(Sprite2D, GetRectangle), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite2D", "void set_hotSpot(const Vector2&in)", asMETHOD(Sprite2D, SetHotSpot), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite2D", "const Vector2& get_hotSpot() const", asMETHOD(Sprite2D, GetHotSpot), asCALL_THISCALL);
}

static void RegisterSpriteSheet2D(asIScriptEngine* engine)
{
    RegisterResource<SpriteSheet2D>(engine, "SpriteSheet2D");
    engine->RegisterObjectMethod("SpriteSheet2D", "Texture2D@+ get_texture() const", asMETHOD(SpriteSheet2D, GetTexture), asCALL_THISCALL);
    engine->RegisterObjectMethod("SpriteSheet2D", "Sprite2D@+ GetSprite(const String&)", asMETHOD(SpriteSheet2D, GetSprite), asCALL_THISCALL);
    engine->RegisterObjectMethod("SpriteSheet2D", "void DefineSprite(const String&, const IntRect&, const Vector2&)", asMETHOD(SpriteSheet2D, DefineSprite), asCALL_THISCALL);
    engine->RegisterObjectMethod("SpriteSheet2D", "void UpdateSprite(const String&, const IntRect&, const Vector2&)", asMETHOD(SpriteSheet2D, UpdateSprite), asCALL_THISCALL);
}

// Template function for registering a class derived from Drawable2D.
template <class T> void RegisterDrawable2D(asIScriptEngine* engine, const char* className)
{
    RegisterDrawable<T>(engine, className);
    RegisterSubclass<Drawable2D, T>(engine, "Drawable2D", className);
    engine->RegisterObjectMethod(className, "void set_sprite(Sprite2D@+)", asMETHOD(T, SetSprite), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "Sprite2D@+ get_sprite() const", asMETHOD(T, GetSprite), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_material(Material@+)", asMETHOD(T, SetMaterial), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "Material@+ get_material() const", asMETHOD(T, GetMaterial), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_blendMode(BlendMode)", asMETHOD(T, SetBlendMode), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "BlendMode get_blendMode() const", asMETHOD(T, GetBlendMode), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_zValue(float)", asMETHOD(T, SetZValue), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "float get_zValue() const", asMETHOD(T, GetZValue), asCALL_THISCALL);
}

static void RegisterDrawable2D(asIScriptEngine* engine)
{
    engine->RegisterGlobalProperty("const float PIXEL_SIZE", (void*)&PIXEL_SIZE);

    RegisterDrawable2D<Drawable2D>(engine, "Drawable2D");
}

// Template function for registering a class derived from StaticSprite2D.
template <class T> void RegisterStaticSprite2D(asIScriptEngine* engine, const char* className)
{
    RegisterDrawable2D<T>(engine, className);
    RegisterSubclass<StaticSprite2D, T>(engine, "StaticSprite2D", className);
    engine->RegisterObjectMethod(className, "void SetFlip(bool, bool)", asMETHOD(T, SetFlip), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_flipX(bool)", asMETHOD(T, SetFlipX), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool get_flipX() const", asMETHOD(T, GetFlipX), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_flipY(bool)", asMETHOD(T, SetFlipY), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool get_flipY() const", asMETHOD(T, GetFlipY), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_color(const Color&in)", asMETHOD(T, SetColor), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "const Color& get_color() const", asMETHOD(T, GetColor), asCALL_THISCALL);
}

static void RegisterStaticSprite2D(asIScriptEngine* engine)
{
    RegisterStaticSprite2D<StaticSprite2D>(engine, "StaticSprite2D");
}

static void RegisterAnimation2D(asIScriptEngine* engine)
{
    RegisterResource<Animation2D>(engine, "Animation2D");
    engine->RegisterObjectMethod("Animation2D", "float get_totalTime() const", asMETHOD(Animation2D, GetTotalTime), asCALL_THISCALL);
    engine->RegisterObjectMethod("Animation2D", "uint get_numFrames() const", asMETHOD(Animation2D, GetNumFrames), asCALL_THISCALL);
    engine->RegisterObjectMethod("Animation2D", "Sprite@+ GetFrameSprite(uint) const", asMETHOD(Animation2D, GetFrameSprite), asCALL_THISCALL);
    engine->RegisterObjectMethod("Animation2D", "Sprite@+ GetFrameSpriteByTime(float) const", asMETHOD(Animation2D, GetFrameSpriteByTime), asCALL_THISCALL);
}

static void RegisterAnimatedSprite2D(asIScriptEngine* engine)
{
    engine->RegisterEnum("CycleMode");
    engine->RegisterEnumValue("CycleMode", "CM_LOOP", CM_LOOP);
    engine->RegisterEnumValue("CycleMode", "CM_CLAMP", CM_CLAMP);
    engine->RegisterEnumValue("CycleMode", "CM_PINGPONG", CM_PINGPONG);

    RegisterStaticSprite2D<AnimatedSprite2D>(engine, "AnimatedSprite2D");
    engine->RegisterObjectMethod("AnimatedSprite2D", "void set_speed(float)", asMETHOD(AnimatedSprite2D, SetSpeed), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "float get_speed() const", asMETHOD(AnimatedSprite2D, GetSpeed), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "void set_cycleMode(CycleMode)", asMETHOD(AnimatedSprite2D, SetCycleMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "CycleMode get_cycleMode() const", asMETHOD(AnimatedSprite2D, GetCycleMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "void set_animation(Animation2D@+)", asMETHOD(AnimatedSprite2D, SetAnimation), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "Animation2D@+ get_animation() const", asMETHOD(AnimatedSprite2D, GetAnimation), asCALL_THISCALL);
}

static void RegisterParticleEffect2D(asIScriptEngine* engine)
{
    engine->RegisterEnum("EmitterType2D");
    engine->RegisterEnumValue("EmitterType2D", "EMITTER_TYPE_GRAVITY", EMITTER_TYPE_GRAVITY);
    engine->RegisterEnumValue("EmitterType2D", "EMITTER_TYPE_RADIAL", EMITTER_TYPE_RADIAL);

    RegisterResource<ParticleEffect2D>(engine, "ParticleEffect2D");
}

static void RegisterParticleEmitter2D(asIScriptEngine* engine)
{
    RegisterDrawable2D<ParticleEmitter2D>(engine, "ParticleEmitter2D");
    engine->RegisterObjectMethod("ParticleEmitter2D", "void set_effect(ParticleEffect2D@+)", asMETHOD(ParticleEmitter2D, SetEffect), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter2D", "ParticleEffect2D@+ get_effect() const", asMETHOD(ParticleEmitter2D, GetEffect), asCALL_THISCALL);
}

static void RegisterRigidBody2D(asIScriptEngine* engine)
{
    engine->RegisterEnum("BodyType2D");
    engine->RegisterEnumValue("BodyType2D", "BT_STATIC", BT_STATIC);
    engine->RegisterEnumValue("BodyType2D", "BT_DYNAMIC", BT_DYNAMIC);
    engine->RegisterEnumValue("BodyType2D", "BT_KINEMATIC", BT_KINEMATIC);

    RegisterComponent<RigidBody2D>(engine, "RigidBody2D");
    engine->RegisterObjectMethod("RigidBody2D", "void set_bodyType(BodyType2D)", asMETHOD(RigidBody2D, SetBodyType), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "BodyType2D get_bodyType() const", asMETHOD(RigidBody2D, GetBodyType), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "void set_mass(float)", asMETHOD(RigidBody2D, SetMass), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "float get_mass() const", asMETHOD(RigidBody2D, GetMass), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "void set_inertia(float)", asMETHOD(RigidBody2D, SetInertia), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "float get_inertia() const", asMETHOD(RigidBody2D, GetInertia), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "void set_massCenter(Vector2)", asMETHOD(RigidBody2D, SetMassCenter), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "Vector2 get_massCenter() const", asMETHOD(RigidBody2D, GetMassCenter), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "void set_useFixtureMass(bool)", asMETHOD(RigidBody2D, SetUseFixtureMass), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "bool get_useFixtureMass() const", asMETHOD(RigidBody2D, GetUseFixtureMass), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "void set_linearDamping(float)", asMETHOD(RigidBody2D, SetLinearDamping), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "float get_linearDamping() const", asMETHOD(RigidBody2D, GetLinearDamping), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "void set_angularDamping(float)", asMETHOD(RigidBody2D, SetAngularDamping), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "float get_angularDamping() const", asMETHOD(RigidBody2D, GetAngularDamping), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "void set_allowSleep(bool)", asMETHOD(RigidBody2D, SetAllowSleep), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "bool get_allowSleep() const", asMETHOD(RigidBody2D, IsAllowSleep), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "void set_fixedRotation(bool)", asMETHOD(RigidBody2D, SetFixedRotation), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "bool get_fixedRotation() const", asMETHOD(RigidBody2D, IsFixedRotation), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "void set_bullet(bool)", asMETHOD(RigidBody2D, SetBullet), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "bool get_bullet() const", asMETHOD(RigidBody2D, IsBullet), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "void set_gravityScale(float)", asMETHOD(RigidBody2D, SetGravityScale), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "float get_gravityScale() const", asMETHOD(RigidBody2D, GetGravityScale), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "void set_awake(bool)", asMETHOD(RigidBody2D, SetAwake), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "bool get_awake() const", asMETHOD(RigidBody2D, IsAwake), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "void set_linearVelocity(Vector2)", asMETHOD(RigidBody2D, SetLinearVelocity), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "Vector2 get_linearVelocity() const", asMETHOD(RigidBody2D, GetLinearVelocity), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "void ApplyForce(const Vector2&in, const Vector2&in, bool)", asMETHOD(RigidBody2D, ApplyForce), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "void ApplyForceToCenter(const Vector2&in, bool)", asMETHOD(RigidBody2D, ApplyForceToCenter), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "void ApplyTorque(float torque, bool)", asMETHOD(RigidBody2D, ApplyTorque), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "void ApplyLinearImpulse(const Vector2&in, const Vector2&in, bool)", asMETHOD(RigidBody2D, ApplyLinearImpulse), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "void ApplyAngularImpulse(float, bool)", asMETHOD(RigidBody2D, ApplyAngularImpulse), asCALL_THISCALL);
}

static void ConstructPhysicsRaycastResult2D(PhysicsRaycastResult2D* ptr)
{
    new(ptr) PhysicsRaycastResult2D();
    ptr->position_ = Vector2::ZERO;
    ptr->normal_ = Vector2::ZERO;
    ptr->distance_ = 0.0f;
}

static void DestructPhysicsRaycastResult2D(PhysicsRaycastResult2D* ptr)
{
    ptr->~PhysicsRaycastResult2D();
}

static RigidBody2D* PhysicsRaycastResultGetRigidBody2D(PhysicsRaycastResult2D* ptr)
{
    return ptr->body_;
}

static CScriptArray* PhysicsWorld2DRaycast(const Vector2& startPoint, const Vector2& endPoint, unsigned collisionMask, PhysicsWorld2D* ptr)
{
    PODVector<PhysicsRaycastResult2D> result;
    ptr->Raycast(result, startPoint, endPoint, collisionMask);
    return VectorToArray<PhysicsRaycastResult2D>(result, "Array<PhysicsRaycastResult2D>");
}

static PhysicsRaycastResult2D PhysicsWorld2DRaycastSingle(const Vector2& startPoint, const Vector2& endPoint, unsigned collisionMask, PhysicsWorld2D* ptr)
{
    PhysicsRaycastResult2D result;
    ptr->RaycastSingle(result, startPoint, endPoint, collisionMask);
    return result;
}

static CScriptArray* PhysicsWorld2DGetRigidBodies(const Rect& aabb, unsigned collisionMask, PhysicsWorld2D* ptr)
{
    PODVector<RigidBody2D*> results;
    ptr->GetRigidBodies(results, aabb, collisionMask);
    return VectorToHandleArray<RigidBody2D>(results, "Array<RigidBody2D@>");
}

static PhysicsWorld2D* SceneGetPhysicsWorld2D(Scene* ptr)
{
    return ptr->GetComponent<PhysicsWorld2D>();
}

static PhysicsWorld2D* GetPhysicsWorld2D()
{
    Scene* scene = GetScriptContextScene();
    return scene ? scene->GetComponent<PhysicsWorld2D>() : 0;
}

static void RegisterPhysicsWorld2D(asIScriptEngine* engine)
{
    engine->RegisterObjectType("PhysicsRaycastResult2D", sizeof(PhysicsRaycastResult2D), asOBJ_VALUE | asOBJ_APP_CLASS_C);
    engine->RegisterObjectBehaviour("PhysicsRaycastResult2D", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ConstructPhysicsRaycastResult2D), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("PhysicsRaycastResult2D", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(DestructPhysicsRaycastResult2D), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("PhysicsRaycastResult2D", "PhysicsRaycastResult2D& opAssign(const PhysicsRaycastResult2D&in)", asMETHODPR(PhysicsRaycastResult2D, operator =, (const PhysicsRaycastResult2D&), PhysicsRaycastResult2D&), asCALL_THISCALL);
    engine->RegisterObjectProperty("PhysicsRaycastResult2D", "Vector2 position", offsetof(PhysicsRaycastResult2D, position_));
    engine->RegisterObjectProperty("PhysicsRaycastResult2D", "Vector2 normal", offsetof(PhysicsRaycastResult2D, normal_));
    engine->RegisterObjectProperty("PhysicsRaycastResult2D", "float distance", offsetof(PhysicsRaycastResult2D, distance_));
    engine->RegisterObjectMethod("PhysicsRaycastResult2D", "RigidBody2D@+ get_body() const", asFUNCTION(PhysicsRaycastResultGetRigidBody2D), asCALL_CDECL_OBJLAST);

    RegisterComponent<PhysicsWorld2D>(engine, "PhysicsWorld2D");
    engine->RegisterObjectMethod("PhysicsWorld2D", "Array<PhysicsRaycastResult2D>@ Raycast(const Vector2&, const Vector2&, uint collisionMask = 0xffff)", asFUNCTION(PhysicsWorld2DRaycast), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("PhysicsWorld2D", "PhysicsRaycastResult2D RaycastSingle(const Vector2&, const Vector2&, uint collisionMask = 0xffff)", asFUNCTION(PhysicsWorld2DRaycastSingle), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("PhysicsWorld2D", "RigidBody2D@+ GetRigidBody(const Vector2&, uint collisionMask = 0xffff)", asMETHOD(PhysicsWorld2D, GetRigidBody), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "Array<RigidBody2D@>@ GetRigidBodies(const Rect&in, uint collisionMask = 0xffff)", asFUNCTION(PhysicsWorld2DGetRigidBodies), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("PhysicsWorld2D", "void set_drawShape(bool)", asMETHOD(PhysicsWorld2D, SetDrawShape), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "bool get_drawShape() const", asMETHOD(PhysicsWorld2D, GetDrawShape), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "void set_drawJoint(bool)", asMETHOD(PhysicsWorld2D, SetDrawJoint), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "bool get_drawJoint() const", asMETHOD(PhysicsWorld2D, GetDrawJoint), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "void set_drawAabb(bool)", asMETHOD(PhysicsWorld2D, SetDrawAabb), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "bool get_drawAabb() const", asMETHOD(PhysicsWorld2D, GetDrawAabb), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "void set_drawPair(bool)", asMETHOD(PhysicsWorld2D, SetDrawPair), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "bool get_drawPair() const", asMETHOD(PhysicsWorld2D, GetDrawPair), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "void set_drawCenterOfMass(bool)", asMETHOD(PhysicsWorld2D, SetDrawCenterOfMass), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "bool get_drawCenterOfMass() const", asMETHOD(PhysicsWorld2D, GetDrawCenterOfMass), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "void set_allowSleeping(bool)", asMETHOD(PhysicsWorld2D, SetAllowSleeping), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "bool get_allowSleeping() const", asMETHOD(PhysicsWorld2D, GetAllowSleeping), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "void set_warmStarting(bool)", asMETHOD(PhysicsWorld2D, SetWarmStarting), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "bool get_warmStarting() const", asMETHOD(PhysicsWorld2D, GetWarmStarting), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "void set_continuousPhysics(bool)", asMETHOD(PhysicsWorld2D, SetContinuousPhysics), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "bool get_continuousPhysics() const", asMETHOD(PhysicsWorld2D, GetContinuousPhysics), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "void set_subStepping(bool)", asMETHOD(PhysicsWorld2D, SetSubStepping), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "bool get_subStepping() const", asMETHOD(PhysicsWorld2D, GetSubStepping), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "void set_gravity(const Vector2&in)", asMETHOD(PhysicsWorld2D, SetGravity), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "const Vector2& get_gravity() const", asMETHOD(PhysicsWorld2D, GetGravity), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "void set_autoClearForces(bool)", asMETHOD(PhysicsWorld2D, SetAutoClearForces), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "bool get_autoClearForces() const", asMETHOD(PhysicsWorld2D, GetAutoClearForces), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "void set_velocityIterations(uint)", asMETHOD(PhysicsWorld2D, SetVelocityIterations), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "uint get_velocityIterations() const", asMETHOD(PhysicsWorld2D, GetVelocityIterations), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "void set_positionIterations(uint)", asMETHOD(PhysicsWorld2D, SetPositionIterations), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "uint get_positionIterations() const", asMETHOD(PhysicsWorld2D, GetPositionIterations), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "void DrawDebugGeometry() const", asMETHOD(PhysicsWorld2D, DrawDebugGeometry), asCALL_THISCALL);

    engine->RegisterObjectMethod("Scene", "PhysicsWorld2D@+ get_physicsWorld2D() const", asFUNCTION(SceneGetPhysicsWorld2D), asCALL_CDECL_OBJLAST);
    engine->RegisterGlobalFunction("PhysicsWorld2D@+ get_physicsWorld2D()", asFUNCTION(GetPhysicsWorld2D), asCALL_CDECL);
}

// Template function for registering a class derived from CollisionShape2D.
template <class T> void RegisterCollisionShape2D(asIScriptEngine* engine, const char* className)
{
    RegisterComponent<T>(engine, className);
    RegisterSubclass<CollisionShape2D, T>(engine, "CollisionShape2D", className);
    engine->RegisterObjectMethod(className, "void set_sensor(bool)", asMETHOD(T, SetSensor), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool get_sensor() const", asMETHOD(T, IsSensor), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_categoryBits(int)", asMETHOD(T, SetCategoryBits), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "int get_categoryBits() const", asMETHOD(T, GetCategoryBits), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_maskBits(int)", asMETHOD(T, SetMaskBits), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "int get_maskBits() const", asMETHOD(T, GetMaskBits), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_groupIndex(int)", asMETHOD(T, SetGroupIndex), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "int get_groupIndex() const", asMETHOD(T, GetGroupIndex), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_density(float)", asMETHOD(T, SetDensity), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "float get_density() const", asMETHOD(T, GetDensity), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_friction(float)", asMETHOD(T, SetFriction), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "float get_friction() const", asMETHOD(T, GetFriction), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_restitution(float)", asMETHOD(T, SetRestitution), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "float get_restitution() const", asMETHOD(T, GetRestitution), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "float get_mass() const", asMETHOD(T, GetMass), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "float get_inertia() const", asMETHOD(T, GetInertia), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "Vector2 get_massCenter() const", asMETHOD(T, GetMassCenter), asCALL_THISCALL);
}

static void RegisterCollisionShape2D(asIScriptEngine* engine)
{
    RegisterCollisionShape2D<CollisionShape2D>(engine, "CollisionShape2D");
}

static void RegisterCollisionBox2D(asIScriptEngine* engine)
{
    RegisterCollisionShape2D<CollisionBox2D>(engine, "CollisionBox2D");
    engine->RegisterObjectMethod("CollisionBox2D", "void set_size(const Vector2&in)", asMETHODPR(CollisionBox2D, SetSize, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionBox2D", "void SetSize(float, float)", asMETHODPR(CollisionBox2D, SetSize, (float, float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionBox2D", "const Vector2& get_size() const", asMETHOD(CollisionBox2D, GetSize), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionBox2D", "void set_center(const Vector2&in)", asMETHODPR(CollisionBox2D, SetCenter, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionBox2D", "void SetCenter(float, float)", asMETHODPR(CollisionBox2D, SetCenter, (float, float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionBox2D", "const Vector2& get_center() const", asMETHOD(CollisionBox2D, GetCenter), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionBox2D", "void set_angle(float)", asMETHOD(CollisionBox2D, SetAngle), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionBox2D", "float get_angle() const", asMETHOD(CollisionBox2D, GetAngle), asCALL_THISCALL);
}

static void RegisterCollisionCircle2D(asIScriptEngine* engine)
{
    RegisterCollisionShape2D<CollisionCircle2D>(engine, "CollisionCircle2D");
    engine->RegisterObjectMethod("CollisionCircle2D", "void set_radius(float)", asMETHOD(CollisionCircle2D, SetRadius), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionCircle2D", "float get_radius() const", asMETHOD(CollisionCircle2D, GetRadius), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionCircle2D", "void set_center(const Vector2&in)", asMETHODPR(CollisionCircle2D, SetCenter, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionCircle2D", "void SetCenter(float, float)", asMETHODPR(CollisionCircle2D, SetCenter, (float, float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionCircle2D", "const Vector2& get_center() const", asMETHOD(CollisionCircle2D, GetCenter), asCALL_THISCALL);
}

static void CollisionChain2DSetVertices(CScriptArray* vertices, CollisionChain2D* ptr)
{
    ptr->SetVertices(ArrayToPODVector<Vector2>(vertices));
}

static CScriptArray* CollisionChain2DGetVertices(CollisionChain2D* ptr)
{
    return VectorToArray<Vector2>(ptr->GetVertices(), "Array<Vector2>");
}

static void RegisterCollisionChain2D(asIScriptEngine* engine)
{
    RegisterCollisionShape2D<CollisionChain2D>(engine, "CollisionChain2D");
    engine->RegisterObjectMethod("CollisionChain2D", "void set_loop(bool)", asMETHOD(CollisionChain2D, SetLoop), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionChain2D", "bool get_loop() const", asMETHOD(CollisionChain2D, GetLoop), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionChain2D", "void set_vertexCount(uint)", asMETHOD(CollisionChain2D, SetVertexCount), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionChain2D", "uint get_vertexCount() const", asMETHOD(CollisionChain2D, GetVertexCount), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionChain2D", "void SetVertex(uint, const Vector2&in)", asMETHOD(CollisionChain2D, SetVertex), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionChain2D", "const Vector2& GetVertex(uint) const", asMETHOD(CollisionChain2D, GetVertex), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionChain2D", "void SetVertices(Array<Vector2>@+)", asFUNCTION(CollisionChain2DSetVertices), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("CollisionChain2D", "Array<Vector2>@ GetVertices() const", asFUNCTION(CollisionChain2DGetVertices), asCALL_CDECL_OBJLAST);
}

static void RegisterCollisionEdge2D(asIScriptEngine* engine)
{
    RegisterCollisionShape2D<CollisionEdge2D>(engine, "CollisionEdge2D");
    engine->RegisterObjectMethod("CollisionEdge2D", "void set_vertex1(const Vector2&in)", asMETHOD(CollisionEdge2D, SetVertex1), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionEdge2D", "const Vector2& get_vertex1() const", asMETHOD(CollisionEdge2D, GetVertex1), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionEdge2D", "void set_vertex2(const Vector2&in)", asMETHOD(CollisionEdge2D, SetVertex2), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionEdge2D", "const Vector2& get_vertex2() const", asMETHOD(CollisionEdge2D, GetVertex2), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionEdge2D", "void SetVertices(const Vector2&in, const Vector2&in)", asMETHOD(CollisionEdge2D, SetVertices), asCALL_THISCALL);
}

static void CollisionPolygon2DSetVertices(CScriptArray* vertices, CollisionPolygon2D* ptr)
{
    ptr->SetVertices(ArrayToPODVector<Vector2>(vertices));
}

static CScriptArray* CollisionPolygon2DGetVertices(CollisionPolygon2D* ptr)
{
    return VectorToArray<Vector2>(ptr->GetVertices(), "Array<Vector2>");
}

static void RegisterCollisionPolygon2D(asIScriptEngine* engine)
{
    RegisterCollisionShape2D<CollisionPolygon2D>(engine, "CollisionPolygon2D");
    engine->RegisterObjectMethod("CollisionPolygon2D", "void set_vertexCount(uint)", asMETHOD(CollisionPolygon2D, SetVertexCount), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionPolygon2D", "uint get_vertexCount() const", asMETHOD(CollisionPolygon2D, GetVertexCount), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionPolygon2D", "void SetVertex(uint, const Vector2&in)", asMETHOD(CollisionPolygon2D, SetVertex), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionPolygon2D", "const Vector2& GetVertex(uint) const", asMETHOD(CollisionPolygon2D, GetVertex), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionPolygon2D", "void SetVertices(Array<Vector2>@+)", asFUNCTION(CollisionPolygon2DSetVertices), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("CollisionPolygon2D", "Array<Vector2>@ GetVertices() const", asFUNCTION(CollisionPolygon2DGetVertices), asCALL_CDECL_OBJLAST);
}

// Template function for registering a class derived from Constraint2D.
template <class T> void RegisterConstraint2D(asIScriptEngine* engine, const char* className)
{
    RegisterComponent<T>(engine, className);
    RegisterSubclass<Constraint2D, T>(engine, "Constraint2D", className);
    engine->RegisterObjectMethod(className, "void set_otherBody(RigidBody2D@+)", asMETHOD(T, SetOtherBody), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "RigidBody2D@+ get_ownerBody() const", asMETHOD(T, GetOwnerBody), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "RigidBody2D@+ get_otherBody() const", asMETHOD(T, GetOtherBody), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_collideConnected(bool)", asMETHOD(T, SetCollideConnected), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool get_collideConnected() const", asMETHOD(T, GetCollideConnected), asCALL_THISCALL);
}


static void RegisterConstraint2D(asIScriptEngine* engine)
{
    RegisterConstraint2D<Constraint2D>(engine, "Constraint2D");
}

static void RegisterConstraintDistance2D(asIScriptEngine* engine)
{
    RegisterConstraint2D<ConstraintDistance2D>(engine, "ConstraintDistance2D");
    engine->RegisterObjectMethod("ConstraintDistance2D", "void set_ownerBodyAnchor(const Vector2&)", asMETHOD(ConstraintDistance2D, SetOwnerBodyAnchor), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintDistance2D", "const Vector2& get_ownerBodyAnchor() const", asMETHOD(ConstraintDistance2D, GetOwnerBodyAnchor), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintDistance2D", "void set_otherBodyAnchor(const Vector2&)", asMETHOD(ConstraintDistance2D, SetOtherBodyAnchor), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintDistance2D", "const Vector2& get_otherBodyAnchor() const", asMETHOD(ConstraintDistance2D, GetOtherBodyAnchor), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintDistance2D", "void set_frequencyHz(float)", asMETHOD(ConstraintDistance2D, SetFrequencyHz), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintDistance2D", "float get_frequencyHz() const", asMETHOD(ConstraintDistance2D, GetFrequencyHz), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintDistance2D", "void set_dampingRatio(float)", asMETHOD(ConstraintDistance2D, SetDampingRatio), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintDistance2D", "float get_dampingRatio() const", asMETHOD(ConstraintDistance2D, GetDampingRatio), asCALL_THISCALL);
}

static void RegisterConstraintFriction2D(asIScriptEngine* engine)
{
    RegisterConstraint2D<ConstraintFriction2D>(engine, "ConstraintFriction2D");
    engine->RegisterObjectMethod("ConstraintFriction2D", "void set_anchor(const Vector2&)", asMETHOD(ConstraintFriction2D, SetAnchor), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintFriction2D", "const Vector2& get_anchor() const", asMETHOD(ConstraintFriction2D, GetAnchor), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintFriction2D", "void set_maxForce(float)", asMETHOD(ConstraintFriction2D, SetMaxForce), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintFriction2D", "float get_maxForce() const", asMETHOD(ConstraintFriction2D, GetMaxForce), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintFriction2D", "void set_maxTorque(float)", asMETHOD(ConstraintFriction2D, SetMaxTorque), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintFriction2D", "float get_maxTorque() const", asMETHOD(ConstraintFriction2D, GetMaxTorque), asCALL_THISCALL);
}

static void RegisterConstraintGear2D(asIScriptEngine* engine)
{
    RegisterConstraint2D<ConstraintGear2D>(engine, "ConstraintGear2D");
    engine->RegisterObjectMethod("ConstraintGear2D", "void set_ownerConstraint(Constraint2D@+)", asMETHOD(ConstraintGear2D, SetOwnerConstraint), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintGear2D", "Constraint2D@+ get_ownerConstraint() const", asMETHOD(ConstraintGear2D, GetOwnerConstraint), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintGear2D", "void set_otherConstraint(Constraint2D@+)", asMETHOD(ConstraintGear2D, SetOtherConstraint), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintGear2D", "Constraint2D@+ get_otherConstraint() const", asMETHOD(ConstraintGear2D, GetOtherConstraint), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintGear2D", "void set_ratio(float)", asMETHOD(ConstraintGear2D, SetRatio), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintGear2D", "float get_ratio() const", asMETHOD(ConstraintGear2D, GetRatio), asCALL_THISCALL);
}

static void RegisterConstraintMotor2D(asIScriptEngine* engine)
{
    RegisterConstraint2D<ConstraintMotor2D>(engine, "ConstraintMotor2D");
    engine->RegisterObjectMethod("ConstraintMotor2D", "void set_ownerBodyAnchor(const Vector2&)", asMETHOD(ConstraintMotor2D, SetOwnerBodyAnchor), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMotor2D", "const Vector2& get_ownerBodyAnchor() const", asMETHOD(ConstraintMotor2D, GetOwnerBodyAnchor), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMotor2D", "void set_otherBodyAnchor(const Vector2&)", asMETHOD(ConstraintMotor2D, SetOtherBodyAnchor), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMotor2D", "const Vector2& get_otherBodyAnchor() const", asMETHOD(ConstraintMotor2D, GetOtherBodyAnchor), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMotor2D", "void set_maxLength(float)", asMETHOD(ConstraintMotor2D, SetMaxLength), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMotor2D", "float get_maxLength() const", asMETHOD(ConstraintMotor2D, GetMaxLength), asCALL_THISCALL);
}

static void RegisterConstraintMouse2D(asIScriptEngine* engine)
{
    RegisterConstraint2D<ConstraintMouse2D>(engine, "ConstraintMouse2D");
    engine->RegisterObjectMethod("ConstraintMouse2D", "void set_target(const Vector2&)", asMETHOD(ConstraintMouse2D, SetTarget), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMouse2D", "const Vector2& get_target() const", asMETHOD(ConstraintMouse2D, GetTarget), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMouse2D", "void set_maxForce(float)", asMETHOD(ConstraintMouse2D, SetMaxForce), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMouse2D", "float get_maxForce() const", asMETHOD(ConstraintMouse2D, GetMaxForce), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMouse2D", "void set_frequencyHz(float)", asMETHOD(ConstraintMouse2D, SetFrequencyHz), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMouse2D", "float get_frequencyHz() const", asMETHOD(ConstraintMouse2D, GetFrequencyHz), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMouse2D", "void set_dampingRatio(float)", asMETHOD(ConstraintMouse2D, SetDampingRatio), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMouse2D", "float get_dampingRatio() const", asMETHOD(ConstraintMouse2D, GetDampingRatio), asCALL_THISCALL);
}

static void RegisterConstraintPrismatic2D(asIScriptEngine* engine)
{
    RegisterConstraint2D<ConstraintPrismatic2D>(engine, "ConstraintPrismatic2D");
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void set_anchor(const Vector2&)", asMETHOD(ConstraintPrismatic2D, SetAnchor), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "const Vector2& get_anchor() const", asMETHOD(ConstraintPrismatic2D, GetAnchor), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void set_axis(const Vector2&)", asMETHOD(ConstraintPrismatic2D, SetAxis), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "const Vector2& get_axis() const", asMETHOD(ConstraintPrismatic2D, GetAxis), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void set_enableLimit(bool)", asMETHOD(ConstraintPrismatic2D, SetEnableLimit), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "bool get_enableLimit() const", asMETHOD(ConstraintPrismatic2D, GetEnableLimit), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void set_lowerTranslation(float)", asMETHOD(ConstraintPrismatic2D, SetLowerTranslation), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "float get_lowerTranslation() const", asMETHOD(ConstraintPrismatic2D, GetLowerTranslation), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void set_upperTranslation(float)", asMETHOD(ConstraintPrismatic2D, SetUpperTranslation), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "float get_upperTranslation() const", asMETHOD(ConstraintPrismatic2D, GetUpperTranslation), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void set_enableMotor(bool)", asMETHOD(ConstraintPrismatic2D, SetEnableMotor), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "bool get_enableMotor() const", asMETHOD(ConstraintPrismatic2D, GetEnableMotor), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void set_maxMotorForce(float)", asMETHOD(ConstraintPrismatic2D, SetMaxMotorForce), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "float get_maxMotorForce() const", asMETHOD(ConstraintPrismatic2D, GetMaxMotorForce), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void set_motorSpeed(float)", asMETHOD(ConstraintPrismatic2D, SetMotorSpeed), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "float get_motorSpeed() const", asMETHOD(ConstraintPrismatic2D, GetMotorSpeed), asCALL_THISCALL);
}

static void RegisterConstraintPulley2D(asIScriptEngine* engine)
{
    RegisterConstraint2D<ConstraintPulley2D>(engine, "ConstraintPulley2D");
    engine->RegisterObjectMethod("ConstraintPulley2D", "void set_ownerBodyGroundAnchor(const Vector2&)", asMETHOD(ConstraintPulley2D, SetOwnerBodyGroundAnchor), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPulley2D", "const Vector2& get_ownerBodyGroundAnchor() const", asMETHOD(ConstraintPulley2D, GetOwnerBodyGroundAnchor), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPulley2D", "void set_otherBodyGroundAnchor(const Vector2&)", asMETHOD(ConstraintPulley2D, SetOtherBodyGroundAnchor), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPulley2D", "const Vector2& get_otherBodyGroundAnchor() const", asMETHOD(ConstraintPulley2D, GetOtherBodyGroundAnchor), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPulley2D", "void set_ownerBodyAnchor(const Vector2&)", asMETHOD(ConstraintPulley2D, SetOwnerBodyAnchor), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPulley2D", "const Vector2& get_ownerBodyAnchor() const", asMETHOD(ConstraintPulley2D, GetOwnerBodyAnchor), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPulley2D", "void set_otherBodyAnchor(const Vector2&)", asMETHOD(ConstraintPulley2D, SetOtherBodyAnchor), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPulley2D", "const Vector2& get_otherBodyAnchor() const", asMETHOD(ConstraintPulley2D, GetOtherBodyAnchor), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPulley2D", "void set_ratio(float)", asMETHOD(ConstraintPulley2D, SetRatio), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPulley2D", "float get_ratio() const", asMETHOD(ConstraintPulley2D, GetRatio), asCALL_THISCALL);
}

static void RegisterConstraintRevolute2D(asIScriptEngine* engine)
{
    RegisterConstraint2D<ConstraintRevolute2D>(engine, "ConstraintRevolute2D");
    engine->RegisterObjectMethod("ConstraintRevolute2D", "void set_anchor(const Vector2&)", asMETHOD(ConstraintRevolute2D, SetAnchor), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRevolute2D", "const Vector2& get_anchor() const", asMETHOD(ConstraintRevolute2D, GetAnchor), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRevolute2D", "void set_enableLimit(bool)", asMETHOD(ConstraintRevolute2D, SetEnableLimit), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRevolute2D", "bool get_enableLimit() const", asMETHOD(ConstraintRevolute2D, GetEnableLimit), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRevolute2D", "void set_lowerAngle(float)", asMETHOD(ConstraintRevolute2D, SetLowerAngle), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRevolute2D", "float get_lowerAngle() const", asMETHOD(ConstraintRevolute2D, GetLowerAngle), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRevolute2D", "void set_upperAngle(float)", asMETHOD(ConstraintRevolute2D, SetUpperAngle), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRevolute2D", "float get_upperAngle() const", asMETHOD(ConstraintRevolute2D, GetUpperAngle), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRevolute2D", "void set_enableMotor(bool)", asMETHOD(ConstraintRevolute2D, SetEnableMotor), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRevolute2D", "bool get_enableMotor() const", asMETHOD(ConstraintRevolute2D, GetEnableMotor), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRevolute2D", "void set_motorSpeed(float)", asMETHOD(ConstraintRevolute2D, SetMotorSpeed), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRevolute2D", "float get_motorSpeed() const", asMETHOD(ConstraintRevolute2D, GetMotorSpeed), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRevolute2D", "void set_maxMotorTorque(float)", asMETHOD(ConstraintRevolute2D, SetMaxMotorTorque), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRevolute2D", "float get_maxMotorTorque() const", asMETHOD(ConstraintRevolute2D, GetMaxMotorTorque), asCALL_THISCALL);
}

static void RegisterConstraintWeld2D(asIScriptEngine* engine)
{
    RegisterConstraint2D<ConstraintWeld2D>(engine, "ConstraintWeld2D");
    engine->RegisterObjectMethod("ConstraintWeld2D", "void set_anchor(const Vector2&)", asMETHOD(ConstraintWeld2D, SetAnchor), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWeld2D", "const Vector2& get_anchor() const", asMETHOD(ConstraintWeld2D, GetAnchor), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWeld2D", "void set_frequencyHz(float)", asMETHOD(ConstraintWeld2D, SetFrequencyHz), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWeld2D", "float get_frequencyHz() const", asMETHOD(ConstraintWeld2D, GetFrequencyHz), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWeld2D", "void set_dampingRatio(float)", asMETHOD(ConstraintWeld2D, SetDampingRatio), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWeld2D", "float get_dampingRatio() const", asMETHOD(ConstraintWeld2D, GetDampingRatio), asCALL_THISCALL);
}

static void RegisterConstraintWheel2D(asIScriptEngine* engine)
{
    RegisterConstraint2D<ConstraintWheel2D>(engine, "ConstraintWheel2D");
    engine->RegisterObjectMethod("ConstraintWheel2D", "void set_anchor(const Vector2&)", asMETHOD(ConstraintWheel2D, SetAnchor), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWheel2D", "const Vector2& get_anchor() const", asMETHOD(ConstraintWheel2D, GetAnchor), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWheel2D", "void set_axis(const Vector2&)", asMETHOD(ConstraintWheel2D, SetAxis), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWheel2D", "const Vector2& get_axis() const", asMETHOD(ConstraintWheel2D, GetAxis), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWheel2D", "void set_enableMotor(bool)", asMETHOD(ConstraintWheel2D, SetEnableMotor), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWheel2D", "bool get_enableMotor() const", asMETHOD(ConstraintWheel2D, GetEnableMotor), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWheel2D", "void set_maxMotorTorque(float)", asMETHOD(ConstraintWheel2D, SetMaxMotorTorque), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWheel2D", "float get_maxMotorTorque() const", asMETHOD(ConstraintWheel2D, GetMaxMotorTorque), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWheel2D", "void set_motorSpeed(float)", asMETHOD(ConstraintWheel2D, SetMotorSpeed), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWheel2D", "float get_motorSpeed() const", asMETHOD(ConstraintWheel2D, GetMotorSpeed), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWheel2D", "void set_frequencyHz(float)", asMETHOD(ConstraintWheel2D, SetFrequencyHz), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWheel2D", "float get_frequencyHz() const", asMETHOD(ConstraintWheel2D, GetFrequencyHz), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWheel2D", "void set_dampingRatio(float)", asMETHOD(ConstraintWheel2D, SetDampingRatio), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWheel2D", "float get_dampingRatio() const", asMETHOD(ConstraintWheel2D, GetDampingRatio), asCALL_THISCALL);
}

static void RegisterConstraintRope2D(asIScriptEngine* engine)
{
    RegisterConstraint2D<ConstraintRope2D>(engine, "ConstraintRope2D");
    engine->RegisterObjectMethod("ConstraintRope2D", "void set_ownerBodyAnchor(const Vector2&)", asMETHOD(ConstraintRope2D, SetOwnerBodyAnchor), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRope2D", "const Vector2& get_ownerBodyAnchor() const", asMETHOD(ConstraintRope2D, GetOwnerBodyAnchor), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRope2D", "void set_otherBodyAnchor(const Vector2&)", asMETHOD(ConstraintRope2D, SetOtherBodyAnchor), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRope2D", "const Vector2& get_otherBodyAnchor() const", asMETHOD(ConstraintRope2D, GetOtherBodyAnchor), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRope2D", "void set_maxLength(float)", asMETHOD(ConstraintRope2D, SetMaxLength), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRope2D", "float get_maxLength() const", asMETHOD(ConstraintRope2D, GetMaxLength), asCALL_THISCALL);
}

void RegisterUrho2DAPI(asIScriptEngine* engine)
{
    RegisterSprite2D(engine);
    RegisterSpriteSheet2D(engine);
    RegisterDrawable2D(engine);
    RegisterStaticSprite2D(engine);
    RegisterAnimation2D(engine);
    RegisterAnimatedSprite2D(engine);
    RegisterParticleEffect2D(engine);
    RegisterParticleEmitter2D(engine);

    RegisterRigidBody2D(engine);
    RegisterPhysicsWorld2D(engine);

    RegisterCollisionShape2D(engine);
    RegisterCollisionBox2D(engine);
    RegisterCollisionCircle2D(engine);
    RegisterCollisionChain2D(engine);
    RegisterCollisionEdge2D(engine);
    RegisterCollisionPolygon2D(engine);

    RegisterConstraint2D(engine);
    RegisterConstraintDistance2D(engine);
    RegisterConstraintFriction2D(engine);
    RegisterConstraintGear2D(engine);
    RegisterConstraintMotor2D(engine);
    RegisterConstraintMouse2D(engine);
    RegisterConstraintPrismatic2D(engine);
    RegisterConstraintPulley2D(engine);
    RegisterConstraintRevolute2D(engine);
    RegisterConstraintWeld2D(engine);
    RegisterConstraintWheel2D(engine);
    RegisterConstraintRope2D(engine);
}

}
