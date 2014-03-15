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
#include "AnimatedSprite2D.h"
#include "Animation2D.h"
#include "APITemplates.h"
#include "CollisionBox2D.h"
#include "CollisionCircle2D.h"
#include "CollisionShape2D.h"
#include "Drawable2D.h"
#include "ParticleEmitter2D.h"
#include "ParticleModel2D.h"
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

/// Template function for registering a class derived from Drawable2D.
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

/// Template function for registering a class derived from StaticSprite2D.
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

static void RegisterParticleModel2D(asIScriptEngine* engine)
{
    engine->RegisterEnum("EmitterType2D");
    engine->RegisterEnumValue("EmitterType2D", "EMITTER_TYPE_GRAVITY", EMITTER_TYPE_GRAVITY);
    engine->RegisterEnumValue("EmitterType2D", "EMITTER_TYPE_RADIAL", EMITTER_TYPE_RADIAL);

    RegisterResource<ParticleModel2D>(engine, "ParticleModel2D");
}

static void RegisterParticleEmitter2D(asIScriptEngine* engine)
{
    RegisterDrawable2D<ParticleEmitter2D>(engine, "ParticleEmitter2D");
    engine->RegisterObjectMethod("ParticleEmitter2D", "void set_model(ParticleModel2D@+)", asMETHOD(ParticleEmitter2D, SetModel), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter2D", "ParticleModel2D@+ get_model() const", asMETHOD(ParticleEmitter2D, GetModel), asCALL_THISCALL);
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
    RegisterComponent<PhysicsWorld2D>(engine, "PhysicsWorld2D");

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

/// Template function for registering a class derived from CollisionShape2D.
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

void RegisterUrho2DAPI(asIScriptEngine* engine)
{
    RegisterSprite2D(engine);
    RegisterSpriteSheet2D(engine);
    RegisterDrawable2D(engine);
    RegisterStaticSprite2D(engine);
    RegisterAnimation2D(engine);
    RegisterAnimatedSprite2D(engine);
    RegisterParticleModel2D(engine);
    RegisterParticleEmitter2D(engine);
    RegisterPhysicsWorld2D(engine);
    RegisterRigidBody2D(engine);
    RegisterCollisionShape2D(engine);
    RegisterCollisionBox2D(engine);
    RegisterCollisionCircle2D(engine);
}

}
