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
#include "Context.h"
#include "DebugRenderer.h"
#include "PhysicsEvents2D.h"
#include "PhysicsUtils2D.h"
#include "PhysicsWorld2D.h"
#include "Profiler.h"
#include "RigidBody2D.h"
#include "scene.h"
#include "SceneEvents.h"

#include "DebugNew.h"

namespace Urho3D
{

extern const char* SUBSYSTEM_CATEGORY;
static const Vector2 DEFAULT_GRAVITY(0.0f, -9.81f);

PhysicsWorld2D::PhysicsWorld2D(Context* context) : Component(context),
    world_(0),
    gravity_(DEFAULT_GRAVITY),
    velocityIterations_(8),
    positionIterations_(3),
    debugRenderer_(0),
    applyingTransforms_(false)
{
    // Set default debug draw flags
    // m_drawFlags = e_shapeBit | e_jointBit | e_centerOfMassBit;
    m_drawFlags = e_shapeBit;

    // Create Box2D world
    world_ = new b2World(ToB2Vec2(gravity_));
    // Set contact listener
    world_->SetContactListener(this);
    // Set debug draw
    world_->SetDebugDraw(this);

    world_->SetContinuousPhysics(true);
    world_->SetSubStepping(true);
}

PhysicsWorld2D::~PhysicsWorld2D()
{
    for (unsigned i = 0; i < rigidBodies_.Size(); ++i)
        if (rigidBodies_[i])
            rigidBodies_[i]->ReleaseBody();

    delete world_;
    world_ = 0;
}

void PhysicsWorld2D::RegisterObject(Context* context)
{
    context->RegisterFactory<PhysicsWorld2D>(SUBSYSTEM_CATEGORY);

    ACCESSOR_ATTRIBUTE(PhysicsWorld2D, VAR_BOOL, "Draw Shape", GetDrawShape, SetDrawShape, bool, false, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(PhysicsWorld2D, VAR_BOOL, "Draw Joint", GetDrawJoint, SetDrawJoint, bool, false, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(PhysicsWorld2D, VAR_BOOL, "Draw Aabb", GetDrawAabb, SetDrawAabb, bool, false, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(PhysicsWorld2D, VAR_BOOL, "Draw Pair", GetDrawPair, SetDrawPair, bool, false, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(PhysicsWorld2D, VAR_BOOL, "Draw CenterOfMass", GetDrawCenterOfMass, SetDrawCenterOfMass, bool, false, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(PhysicsWorld2D, VAR_BOOL, "Allow Sleeping", GetAllowSleeping, SetAllowSleeping, bool, false, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(PhysicsWorld2D, VAR_BOOL, "Warm Starting", GetWarmStarting, SetWarmStarting, bool, false, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(PhysicsWorld2D, VAR_BOOL, "Continuous Physics", GetContinuousPhysics, SetContinuousPhysics, bool, false, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(PhysicsWorld2D, VAR_BOOL, "Sub Stepping", GetSubStepping, SetSubStepping, bool, false, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(PhysicsWorld2D, VAR_VECTOR2, "Gravity", GetGravity, SetGravity, Vector2, DEFAULT_GRAVITY, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(PhysicsWorld2D, VAR_BOOL, "Auto Clear Forces", GetAutoClearForces, SetAutoClearForces, bool, false, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(PhysicsWorld2D, VAR_INT, "Velocity Iterations", GetVelocityIterations, SetVelocityIterations, int, false, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(PhysicsWorld2D, VAR_INT, "Position Iterations", GetPositionIterations, SetPositionIterations, int, false, AM_DEFAULT);

    COPY_BASE_ATTRIBUTES(PhysicsWorld2D, Component);
}

void PhysicsWorld2D::DrawDebugGeometry(DebugRenderer* debug, bool depthTest)
{
    if (debug)
    {
        PROFILE(Physics2DDrawDebug);

        debugRenderer_ = debug;
        debugDepthTest_ = depthTest;
        world_->DrawDebugData();
        debugRenderer_ = 0;
    }
}

void PhysicsWorld2D::BeginContact(b2Contact* contact)
{
    b2Fixture* fixtureA = contact->GetFixtureA();
    b2Fixture* fixtureB = contact->GetFixtureB();
    if (!fixtureA || !fixtureB)
        return;

    using namespace PhysicsBeginContact2D;
    VariantMap& eventData = GetEventDataMap();
    eventData[P_WORLD] = this;

    RigidBody2D* rigidBodyA = (RigidBody2D*)(fixtureA->GetBody()->GetUserData());
    RigidBody2D* rigidBodyB = (RigidBody2D*)(fixtureB->GetBody()->GetUserData());
    eventData[P_BODYA] = rigidBodyA;
    eventData[P_BODYB] = rigidBodyB;
    eventData[P_NODEA] = rigidBodyA->GetNode();
    eventData[P_NODEB] = rigidBodyB->GetNode();

    SendEvent(E_PHYSICSBEGINCONTACT2D, eventData);
}

void PhysicsWorld2D::EndContact(b2Contact* contact)
{
    b2Fixture* fixtureA = contact->GetFixtureA();
    b2Fixture* fixtureB = contact->GetFixtureB();
    if (!fixtureA || !fixtureB)
        return;

    using namespace PhysicsEndContact2D;
    VariantMap& eventData = GetEventDataMap();
    eventData[P_WORLD] = this;

    RigidBody2D* rigidBodyA = (RigidBody2D*)(fixtureA->GetBody()->GetUserData());
    RigidBody2D* rigidBodyB = (RigidBody2D*)(fixtureB->GetBody()->GetUserData());
    eventData[P_BODYA] = rigidBodyA;
    eventData[P_BODYB] = rigidBodyB;
    eventData[P_NODEA] = rigidBodyA->GetNode();
    eventData[P_NODEB] = rigidBodyB->GetNode();

    SendEvent(E_PHYSICSENDCOLLISION2D, eventData);
}

void PhysicsWorld2D::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
    if (!debugRenderer_)
        return;

    Color c = ToColor(color);
    for (int i = 0; i < vertexCount - 1; ++i)
        debugRenderer_->AddLine(ToVector3(vertices[i]), ToVector3(vertices[i + 1]), c, debugDepthTest_);

    debugRenderer_->AddLine(ToVector3(vertices[vertexCount - 1]), ToVector3(vertices[0]), c, debugDepthTest_);
}

void PhysicsWorld2D::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
    if (!debugRenderer_)
        return;

    Vector3 v = ToVector3(vertices[0]);
    Color c(color.r, color.g, color.b, 0.5f);
    for (int i = 1; i < vertexCount - 1; ++i)
        debugRenderer_->AddTriangle(v, ToVector3(vertices[i]), ToVector3(vertices[i + 1]), c, debugDepthTest_);
}

void PhysicsWorld2D::DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color)
{
    if (!debugRenderer_)
        return;

    Vector3 p = ToVector3(center);
    Color c = ToColor(color);
    for (unsigned i = 0; i < 360; i += 45)
    {
        unsigned j = i + 45;
        float x1 = radius * Cos((float)i);
        float y1 = radius * Sin((float)i);
        float x2 = radius * Cos((float)j);
        float y2 = radius * Sin((float)j);

        debugRenderer_->AddLine(p + Vector3(x1, y1, 0.0f), p + Vector3(x2, y2, 0.0f), c, debugDepthTest_);
    }
}

void PhysicsWorld2D::DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color)
{
    if (!debugRenderer_)
        return;

    Vector3 p = ToVector3(center);
    Color c(color.r, color.g, color.b, 0.5f);

    for (unsigned i = 0; i < 360; i += 45)
    {
        unsigned j = i + 45;
        float x1 = radius * Cos((float)i);
        float y1 = radius * Sin((float)i);
        float x2 = radius * Cos((float)j);
        float y2 = radius * Sin((float)j);

        debugRenderer_->AddTriangle(p, p + Vector3(x1, y1, 0.0f), p + Vector3(x2, y2, 0.0f), c, debugDepthTest_);
    }
}

void PhysicsWorld2D::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
{
    if (debugRenderer_)
        debugRenderer_->AddLine(ToVector3(p1), ToVector3(p2), ToColor(color), debugDepthTest_);
}

void PhysicsWorld2D::DrawTransform(const b2Transform& xf)
{
    if (!debugRenderer_)
        return;

    const float32 axisScale = 0.4f;

    b2Vec2 p1 = xf.p, p2;
    p2 = p1 + axisScale * xf.q.GetXAxis();    
    debugRenderer_->AddLine(Vector3(p1.x, p1.y, 0.0f), Vector3(p2.x, p2.y, 0.0f), Color::RED, debugDepthTest_);

    p2 = p1 + axisScale * xf.q.GetYAxis();
    debugRenderer_->AddLine(Vector3(p1.x, p1.y, 0.0f), Vector3(p2.x, p2.y, 0.0f), Color::GREEN, debugDepthTest_);
}

void PhysicsWorld2D::SetDrawShape(bool drawShape)
{
    if (drawShape)
        m_drawFlags |= e_shapeBit;
    else
        m_drawFlags &= ~e_shapeBit;

}

void PhysicsWorld2D::SetDrawJoint(bool drawJoint)
{
    if (drawJoint)
        m_drawFlags |= e_jointBit;
    else
        m_drawFlags &= ~e_jointBit;
}

void PhysicsWorld2D::SetDrawAabb(bool drawAabb)
{
    if (drawAabb)
        m_drawFlags |= e_aabbBit;
    else
        m_drawFlags &= ~e_aabbBit;
}

void PhysicsWorld2D::SetDrawPair(bool drawPair)
{
    if (drawPair)
        m_drawFlags |= e_pairBit;
    else
        m_drawFlags &= ~e_pairBit;
}

void PhysicsWorld2D::SetDrawCenterOfMass(bool drawCenterOfMass)
{
    if (drawCenterOfMass)
        m_drawFlags |= e_centerOfMassBit;
    else
        m_drawFlags &= ~e_centerOfMassBit;
}

void PhysicsWorld2D::SetAllowSleeping(bool enable)
{
    world_->SetAllowSleeping(enable);
}

void PhysicsWorld2D::SetWarmStarting(bool enable)
{
    world_->SetWarmStarting(enable);
}

void PhysicsWorld2D::SetContinuousPhysics(bool enable)
{
    world_->SetContinuousPhysics(enable);
}

void PhysicsWorld2D::SetSubStepping(bool enable)
{
    world_->SetSubStepping(enable);
}

void PhysicsWorld2D::SetGravity(Vector2 gravity)
{
    gravity_ = gravity;

    world_->SetGravity(ToB2Vec2(gravity_));
}

void PhysicsWorld2D::SetAutoClearForces(bool enable)
{
    world_->SetAutoClearForces(enable);
}

void PhysicsWorld2D::SetVelocityIterations(int velocityIterations)
{
    velocityIterations_ = velocityIterations;
}

void PhysicsWorld2D::SetPositionIterations(int positionIterations)
{
    positionIterations_ = positionIterations;
}

void PhysicsWorld2D::AddRigidBody(RigidBody2D* rigidBody)
{
    if (!rigidBody)
        return;

    WeakPtr<RigidBody2D> rigidBodyPtr(rigidBody);
    if (rigidBodies_.Contains(rigidBodyPtr))
        return;

    rigidBodies_.Push(rigidBodyPtr);
}

void PhysicsWorld2D::RemoveRigidBody(RigidBody2D* rigidBody)
{
    if (!rigidBody)
        return;

    WeakPtr<RigidBody2D> rigidBodyPtr(rigidBody);
    rigidBodies_.Remove(rigidBodyPtr);
}

void PhysicsWorld2D::Update(float timeStep)
{
    using namespace Physics2DPreStep2D;

    VariantMap& eventData = GetEventDataMap();
    eventData[P_WORLD] = this;
    eventData[P_TIMESTEP] = timeStep;
    SendEvent(E_PHYSICSPRESTEP2D, eventData);

    world_->Step(timeStep, velocityIterations_, positionIterations_);

    for (unsigned i = 0; i < rigidBodies_.Size(); ++i)
        rigidBodies_[i]->ApplyWorldTransform();

    using namespace PhysicsPostStep2D;
    SendEvent(E_PHYSICSPOSTSTEP2D, eventData);
}

void PhysicsWorld2D::DrawDebugGeometry()
{
    DebugRenderer* debug = GetComponent<DebugRenderer>();
    if (debug)
        DrawDebugGeometry(debug, false);
}

void PhysicsWorld2D::SetDebugRenderer(DebugRenderer* debug)
{
    debugRenderer_ = debug;
}

void PhysicsWorld2D::SetDebugDepthTest(bool enable)
{
    debugDepthTest_ = enable;
}

bool PhysicsWorld2D::GetAllowSleeping() const
{
    return world_->GetAllowSleeping();
}

bool PhysicsWorld2D::GetWarmStarting() const
{
    return world_->GetWarmStarting();
}

bool PhysicsWorld2D::GetContinuousPhysics() const
{
    return world_->GetContinuousPhysics();
}

bool PhysicsWorld2D::GetSubStepping() const
{
    return world_->GetSubStepping();
}

bool PhysicsWorld2D::GetAutoClearForces() const
{
    return world_->GetAutoClearForces();
}

void PhysicsWorld2D::OnNodeSet(Node* node)
{
    // Subscribe to the scene subsystem update, which will trigger the physics simulation step
    if (node)
    {
        scene_ = GetScene();
        SubscribeToEvent(node, E_SCENESUBSYSTEMUPDATE, HANDLER(PhysicsWorld2D, HandleSceneSubsystemUpdate));
    }
}

void PhysicsWorld2D::HandleSceneSubsystemUpdate(StringHash eventType, VariantMap& eventData)
{
    using namespace SceneSubsystemUpdate;

    for (unsigned i = 0; i < rigidBodies_.Size(); ++i)
        if (rigidBodies_[i])
            rigidBodies_[i]->UpdateBody();

    Update(eventData[P_TIMESTEP].GetFloat());

    DrawDebugGeometry();
}

}
