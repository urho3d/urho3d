//
// Copyright (c) 2008-2022 the Urho3D project.
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

#include "../Precompiled.h"

#include "../Core/Context.h"
#include "../Core/Profiler.h"
#include "../Graphics/DebugRenderer.h"
#include "../Graphics/Graphics.h"
#include "../Graphics/Renderer.h"
#include "../IO/Log.h"
#include "../Physics2D/CollisionShape2D.h"
#include "../Physics2D/PhysicsEvents2D.h"
#include "../Physics2D/PhysicsUtils2D.h"
#include "../Physics2D/PhysicsWorld2D.h"
#include "../Physics2D/RigidBody2D.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneEvents.h"

#include "../DebugNew.h"

namespace Urho3D
{

extern const char* SUBSYSTEM_CATEGORY;
static const Vector2 DEFAULT_GRAVITY(0.0f, -9.81f);
static const int DEFAULT_VELOCITY_ITERATIONS = 8;
static const int DEFAULT_POSITION_ITERATIONS = 3;

PhysicsWorld2D::PhysicsWorld2D(Context* context) :
    Component(context),
    gravity_(DEFAULT_GRAVITY),
    velocityIterations_(DEFAULT_VELOCITY_ITERATIONS),
    positionIterations_(DEFAULT_POSITION_ITERATIONS)
{
    // Set default debug draw flags
    m_drawFlags = e_shapeBit;

    // Create Box2D world
    world_ = new b2World(ToB2Vec2(gravity_));
    // Set contact listener
    world_->SetContactListener(this);
    // Set debug draw
    world_->SetDebugDraw(this);
}

PhysicsWorld2D::~PhysicsWorld2D()
{
    for (unsigned i = 0; i < rigidBodies_.Size(); ++i)
        if (rigidBodies_[i])
            rigidBodies_[i]->ReleaseBody();
}

void PhysicsWorld2D::RegisterObject(Context* context)
{
    context->RegisterFactory<PhysicsWorld2D>(SUBSYSTEM_CATEGORY);

    URHO3D_ACCESSOR_ATTRIBUTE("Draw Shape", GetDrawShape, SetDrawShape, bool, false, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Draw Joint", GetDrawJoint, SetDrawJoint, bool, false, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Draw Aabb", GetDrawAabb, SetDrawAabb, bool, false, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Draw Pair", GetDrawPair, SetDrawPair, bool, false, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Draw CenterOfMass", GetDrawCenterOfMass, SetDrawCenterOfMass, bool, false, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Allow Sleeping", GetAllowSleeping, SetAllowSleeping, bool, false, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Warm Starting", GetWarmStarting, SetWarmStarting, bool, false, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Continuous Physics", GetContinuousPhysics, SetContinuousPhysics, bool, true, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Sub Stepping", GetSubStepping, SetSubStepping, bool, false, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Gravity", GetGravity, SetGravity, Vector2, DEFAULT_GRAVITY, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Auto Clear Forces", GetAutoClearForces, SetAutoClearForces, bool, false, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Velocity Iterations", GetVelocityIterations, SetVelocityIterations, int, DEFAULT_VELOCITY_ITERATIONS,
        AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Position Iterations", GetPositionIterations, SetPositionIterations, int, DEFAULT_POSITION_ITERATIONS,
        AM_DEFAULT);
}

void PhysicsWorld2D::DrawDebugGeometry(DebugRenderer* debug, bool depthTest)
{
    if (debug)
    {
        URHO3D_PROFILE(Physics2DDrawDebug);

        debugRenderer_ = debug;
        debugDepthTest_ = depthTest;
        world_->DrawDebugData();
        debugRenderer_ = nullptr;
    }
}

void PhysicsWorld2D::BeginContact(b2Contact* contact)
{
    // Only handle contact event while stepping the physics simulation
    if (!physicsStepping_)
        return;

    b2Fixture* fixtureA = contact->GetFixtureA();
    b2Fixture* fixtureB = contact->GetFixtureB();
    if (!fixtureA || !fixtureB)
        return;

    beginContactInfos_.Push(ContactInfo(contact));
}

void PhysicsWorld2D::EndContact(b2Contact* contact)
{
    if (!physicsStepping_)
        return;

    b2Fixture* fixtureA = contact->GetFixtureA();
    b2Fixture* fixtureB = contact->GetFixtureB();
    if (!fixtureA || !fixtureB)
        return;

    endContactInfos_.Push(ContactInfo(contact));
}

void PhysicsWorld2D::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{
    b2Fixture* fixtureA = contact->GetFixtureA();
    b2Fixture* fixtureB = contact->GetFixtureB();
    if (!fixtureA || !fixtureB)
        return;

    ContactInfo contactInfo(contact);

    // Send global event
    VariantMap& eventData = GetEventDataMap();
    eventData[PhysicsUpdateContact2D::P_WORLD] = this;
    eventData[PhysicsUpdateContact2D::P_ENABLED] = contact->IsEnabled();

    eventData[PhysicsUpdateContact2D::P_BODYA] = contactInfo.bodyA_.Get();
    eventData[PhysicsUpdateContact2D::P_BODYB] = contactInfo.bodyB_.Get();
    eventData[PhysicsUpdateContact2D::P_NODEA] = contactInfo.nodeA_.Get();
    eventData[PhysicsUpdateContact2D::P_NODEB] = contactInfo.nodeB_.Get();
    eventData[PhysicsUpdateContact2D::P_CONTACTS] = contactInfo.Serialize(contacts_);
    eventData[PhysicsUpdateContact2D::P_SHAPEA] = contactInfo.shapeA_.Get();
    eventData[PhysicsUpdateContact2D::P_SHAPEB] = contactInfo.shapeB_.Get();

    SendEvent(E_PHYSICSUPDATECONTACT2D, eventData);
    contact->SetEnabled(eventData[PhysicsUpdateContact2D::P_ENABLED].GetBool());
    eventData.Clear();

    // Send node event
    eventData[NodeUpdateContact2D::P_ENABLED] = contact->IsEnabled();
    eventData[NodeUpdateContact2D::P_CONTACTS] = contactInfo.Serialize(contacts_);

    if (contactInfo.nodeA_)
    {
        eventData[NodeUpdateContact2D::P_BODY] = contactInfo.bodyA_.Get();
        eventData[NodeUpdateContact2D::P_OTHERNODE] = contactInfo.nodeB_.Get();
        eventData[NodeUpdateContact2D::P_OTHERBODY] = contactInfo.bodyB_.Get();
        eventData[NodeUpdateContact2D::P_SHAPE] = contactInfo.shapeA_.Get();
        eventData[NodeUpdateContact2D::P_OTHERSHAPE] = contactInfo.shapeB_.Get();

        contactInfo.nodeA_->SendEvent(E_NODEUPDATECONTACT2D, eventData);
    }

    if (contactInfo.nodeB_)
    {
        eventData[NodeUpdateContact2D::P_BODY] = contactInfo.bodyB_.Get();
        eventData[NodeUpdateContact2D::P_OTHERNODE] = contactInfo.nodeA_.Get();
        eventData[NodeUpdateContact2D::P_OTHERBODY] = contactInfo.bodyA_.Get();
        eventData[NodeUpdateContact2D::P_SHAPE] = contactInfo.shapeB_.Get();
        eventData[NodeUpdateContact2D::P_OTHERSHAPE] = contactInfo.shapeA_.Get();

        contactInfo.nodeB_->SendEvent(E_NODEUPDATECONTACT2D, eventData);
    }

    contact->SetEnabled(eventData[NodeUpdateContact2D::P_ENABLED].GetBool());
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
    for (unsigned i = 0; i < 360; i += 30)
    {
        unsigned j = i + 30;
        float x1 = radius * Cos((float)i);
        float y1 = radius * Sin((float)i);
        float x2 = radius * Cos((float)j);
        float y2 = radius * Sin((float)j);

        debugRenderer_->AddLine(p + Vector3(x1, y1, 0.0f), p + Vector3(x2, y2, 0.0f), c, debugDepthTest_);
    }
}

extern URHO3D_API const float PIXEL_SIZE;

void PhysicsWorld2D::DrawPoint(const b2Vec2& p, float32 size, const b2Color& color)
{
    DrawSolidCircle(p, size * 0.5f * PIXEL_SIZE, b2Vec2(), color);
}

void PhysicsWorld2D::DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color)
{
    if (!debugRenderer_)
        return;

    Vector3 p = ToVector3(center);
    Color c(color.r, color.g, color.b, 0.5f);

    for (unsigned i = 0; i < 360; i += 30)
    {
        unsigned j = i + 30;
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

void PhysicsWorld2D::Update(float timeStep)
{
    URHO3D_PROFILE(UpdatePhysics2D);

    using namespace PhysicsPreStep;

    VariantMap& eventData = GetEventDataMap();
    eventData[P_WORLD] = this;
    eventData[P_TIMESTEP] = timeStep;
    SendEvent(E_PHYSICSPRESTEP, eventData);

    physicsStepping_ = true;
    world_->Step(timeStep, velocityIterations_, positionIterations_);
    physicsStepping_ = false;

    // Apply world transforms. Unparented transforms first
    for (unsigned i = 0; i < rigidBodies_.Size();)
    {
        if (rigidBodies_[i])
        {
            rigidBodies_[i]->ApplyWorldTransform();
            ++i;
        }
        else
        {
            // Erase possible stale weak pointer
            rigidBodies_.Erase(i);
        }
    }

    // Apply delayed (parented) world transforms now, if any
    while (!delayedWorldTransforms_.Empty())
    {
        for (HashMap<RigidBody2D*, DelayedWorldTransform2D>::Iterator i = delayedWorldTransforms_.Begin();
            i != delayedWorldTransforms_.End();)
        {
            const DelayedWorldTransform2D& transform = i->second_;

            // If parent's transform has already been assigned, can proceed
            if (!delayedWorldTransforms_.Contains(transform.parentRigidBody_))
            {
                transform.rigidBody_->ApplyWorldTransform(transform.worldPosition_, transform.worldRotation_);
                i = delayedWorldTransforms_.Erase(i);
            }
            else
                ++i;
        }
    }

    SendBeginContactEvents();
    SendEndContactEvents();

    using namespace PhysicsPostStep;
    SendEvent(E_PHYSICSPOSTSTEP, eventData);
}

void PhysicsWorld2D::DrawDebugGeometry()
{
    auto* debug = GetComponent<DebugRenderer>();
    if (debug)
        DrawDebugGeometry(debug, false);
}

void PhysicsWorld2D::SetUpdateEnabled(bool enable)
{
    updateEnabled_ = enable;
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

void PhysicsWorld2D::SetGravity(const Vector2& gravity)
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

void PhysicsWorld2D::AddDelayedWorldTransform(const DelayedWorldTransform2D& transform)
{
    delayedWorldTransforms_[transform.rigidBody_] = transform;
}

// Ray cast call back class.
class RayCastCallback : public b2RayCastCallback
{
public:
    // Construct.
    RayCastCallback(PODVector<PhysicsRaycastResult2D>& results, const Vector2& startPoint, unsigned collisionMask) :
        results_(results),
        startPoint_(startPoint),
        collisionMask_(collisionMask)
    {
    }

    // Called for each fixture found in the query.
    float32 ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction) override
    {
        // Ignore sensor
        if (fixture->IsSensor())
            return true;

        if ((fixture->GetFilterData().maskBits & collisionMask_) == 0)
            return true;

        PhysicsRaycastResult2D result;
        result.position_ = ToVector2(point);
        result.normal_ = ToVector2(normal);
        result.distance_ = (result.position_ - startPoint_).Length();
        result.body_ = (RigidBody2D*)(fixture->GetBody()->GetUserData());

        results_.Push(result);
        return true;
    }

protected:
    // Physics raycast results.
    PODVector<PhysicsRaycastResult2D>& results_;
    // Start point.
    Vector2 startPoint_;
    // Collision mask.
    unsigned collisionMask_;
};

void PhysicsWorld2D::Raycast(PODVector<PhysicsRaycastResult2D>& results, const Vector2& startPoint, const Vector2& endPoint,
    unsigned collisionMask)
{
    results.Clear();

    RayCastCallback callback(results, startPoint, collisionMask);
    world_->RayCast(&callback, ToB2Vec2(startPoint), ToB2Vec2(endPoint));
}

// Single ray cast call back class.
class SingleRayCastCallback : public b2RayCastCallback
{
public:
    // Construct.
    SingleRayCastCallback(PhysicsRaycastResult2D& result, const Vector2& startPoint, unsigned collisionMask) :
        result_(result),
        startPoint_(startPoint),
        collisionMask_(collisionMask),
        minDistance_(M_INFINITY)
    {
    }

    // Called for each fixture found in the query.
    float32 ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction) override
    {
        // Ignore sensor
        if (fixture->IsSensor())
            return true;

        if ((fixture->GetFilterData().maskBits & collisionMask_) == 0)
            return true;

        float distance = (ToVector2(point) - startPoint_).Length();
        if (distance < minDistance_)
        {
            minDistance_ = distance;

            result_.position_ = ToVector2(point);
            result_.normal_ = ToVector2(normal);
            result_.distance_ = distance;
            result_.body_ = (RigidBody2D*)(fixture->GetBody()->GetUserData());
        }

        return true;
    }

private:
    // Physics raycast result.
    PhysicsRaycastResult2D& result_;
    // Start point.
    Vector2 startPoint_;
    // Collision mask.
    unsigned collisionMask_;
    // Minimum distance.
    float minDistance_;
};

void PhysicsWorld2D::RaycastSingle(PhysicsRaycastResult2D& result, const Vector2& startPoint, const Vector2& endPoint,
    unsigned collisionMask)
{
    result.body_ = nullptr;

    SingleRayCastCallback callback(result, startPoint, collisionMask);
    world_->RayCast(&callback, ToB2Vec2(startPoint), ToB2Vec2(endPoint));
}

// Point query callback class.
class PointQueryCallback : public b2QueryCallback
{
public:
    // Construct.
    PointQueryCallback(const b2Vec2& point, unsigned collisionMask) :   // NOLINT(modernize-pass-by-value)
        point_(point),
        collisionMask_(collisionMask),
        rigidBody_(nullptr)
    {
    }

    // Called for each fixture found in the query AABB.
    bool ReportFixture(b2Fixture* fixture) override
    {
        // Ignore sensor
        if (fixture->IsSensor())
            return true;

        if ((fixture->GetFilterData().maskBits & collisionMask_) == 0)
            return true;

        if (fixture->TestPoint(point_))
        {
            rigidBody_ = (RigidBody2D*)(fixture->GetBody()->GetUserData());
            return false;
        }

        return true;
    }

    // Return rigid body.
    RigidBody2D* GetRigidBody() const { return rigidBody_; }

private:
    // Point.
    b2Vec2 point_;
    // Collision mask.
    unsigned collisionMask_;
    // Rigid body.
    RigidBody2D* rigidBody_;
};

RigidBody2D* PhysicsWorld2D::GetRigidBody(const Vector2& point, unsigned collisionMask)
{
    PointQueryCallback callback(ToB2Vec2(point), collisionMask);

    b2AABB b2Aabb;
    Vector2 delta(M_EPSILON, M_EPSILON);
    b2Aabb.lowerBound = ToB2Vec2(point - delta);
    b2Aabb.upperBound = ToB2Vec2(point + delta);

    world_->QueryAABB(&callback, b2Aabb);
    return callback.GetRigidBody();
}

RigidBody2D* PhysicsWorld2D::GetRigidBody(int screenX, int screenY, unsigned collisionMask)
{
    auto* renderer = GetSubsystem<Renderer>();
    for (unsigned i = 0; i < renderer->GetNumViewports(); ++i)
    {
        Viewport* viewport = renderer->GetViewport(i);
        // Find a viewport with same scene
        if (viewport && viewport->GetScene() == GetScene())
        {
            Vector3 worldPoint = viewport->ScreenToWorldPoint(screenX, screenY, 0.0f);
            return GetRigidBody(Vector2(worldPoint.x_, worldPoint.y_), collisionMask);
        }
    }

    return nullptr;
}

// Aabb query callback class.
class AabbQueryCallback : public b2QueryCallback
{
public:
    // Construct.
    AabbQueryCallback(PODVector<RigidBody2D*>& results, unsigned collisionMask) :
        results_(results),
        collisionMask_(collisionMask)
    {
    }

    // Called for each fixture found in the query AABB.
    bool ReportFixture(b2Fixture* fixture) override
    {
        // Ignore sensor
        if (fixture->IsSensor())
            return true;

        if ((fixture->GetFilterData().maskBits & collisionMask_) == 0)
            return true;

        results_.Push((RigidBody2D*)(fixture->GetBody()->GetUserData()));
        return true;
    }

private:
    // Results.
    PODVector<RigidBody2D*>& results_;
    // Collision mask.
    unsigned collisionMask_;
};

void PhysicsWorld2D::GetRigidBodies(PODVector<RigidBody2D*>& results, const Rect& aabb, unsigned collisionMask)
{
    AabbQueryCallback callback(results, collisionMask);

    b2AABB b2Aabb;
    Vector2 delta(M_EPSILON, M_EPSILON);
    b2Aabb.lowerBound = ToB2Vec2(aabb.min_ - delta);
    b2Aabb.upperBound = ToB2Vec2(aabb.max_ + delta);

    world_->QueryAABB(&callback, b2Aabb);
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

void PhysicsWorld2D::OnSceneSet(Scene* scene)
{
    // Subscribe to the scene subsystem update, which will trigger the physics simulation step
    if (scene)
        SubscribeToEvent(scene, E_SCENESUBSYSTEMUPDATE, URHO3D_HANDLER(PhysicsWorld2D, HandleSceneSubsystemUpdate));
    else
        UnsubscribeFromEvent(E_SCENESUBSYSTEMUPDATE);
}

void PhysicsWorld2D::HandleSceneSubsystemUpdate(StringHash eventType, VariantMap& eventData)
{
    if (!updateEnabled_)
        return;

    using namespace SceneSubsystemUpdate;
    Update(eventData[P_TIMESTEP].GetFloat());
}

void PhysicsWorld2D::SendBeginContactEvents()
{
    if (beginContactInfos_.Empty())
        return;

    using namespace PhysicsBeginContact2D;
    VariantMap& eventData = GetEventDataMap();
    VariantMap nodeEventData;
    eventData[P_WORLD] = this;

    for (unsigned i = 0; i < beginContactInfos_.Size(); ++i)
    {
        ContactInfo& contactInfo = beginContactInfos_[i];
        eventData[P_BODYA] = contactInfo.bodyA_.Get();
        eventData[P_BODYB] = contactInfo.bodyB_.Get();
        eventData[P_NODEA] = contactInfo.nodeA_.Get();
        eventData[P_NODEB] = contactInfo.nodeB_.Get();
        eventData[P_CONTACTS] = contactInfo.Serialize(contacts_);
        eventData[P_SHAPEA] = contactInfo.shapeA_.Get();
        eventData[P_SHAPEB] = contactInfo.shapeB_.Get();

        SendEvent(E_PHYSICSBEGINCONTACT2D, eventData);

        nodeEventData[NodeBeginContact2D::P_CONTACTS] = contactInfo.Serialize(contacts_);

        if (contactInfo.nodeA_)
        {
            nodeEventData[NodeBeginContact2D::P_BODY] = contactInfo.bodyA_.Get();
            nodeEventData[NodeBeginContact2D::P_OTHERNODE] = contactInfo.nodeB_.Get();
            nodeEventData[NodeBeginContact2D::P_OTHERBODY] = contactInfo.bodyB_.Get();
            nodeEventData[NodeBeginContact2D::P_SHAPE] = contactInfo.shapeA_.Get();
            nodeEventData[NodeBeginContact2D::P_OTHERSHAPE] = contactInfo.shapeB_.Get();

            contactInfo.nodeA_->SendEvent(E_NODEBEGINCONTACT2D, nodeEventData);
        }

        if (contactInfo.nodeB_)
        {
            nodeEventData[NodeBeginContact2D::P_BODY] = contactInfo.bodyB_.Get();
            nodeEventData[NodeBeginContact2D::P_OTHERNODE] = contactInfo.nodeA_.Get();
            nodeEventData[NodeBeginContact2D::P_OTHERBODY] = contactInfo.bodyA_.Get();
            nodeEventData[NodeBeginContact2D::P_SHAPE] = contactInfo.shapeB_.Get();
            nodeEventData[NodeBeginContact2D::P_OTHERSHAPE] = contactInfo.shapeA_.Get();

            contactInfo.nodeB_->SendEvent(E_NODEBEGINCONTACT2D, nodeEventData);
        }
    }

    beginContactInfos_.Clear();
}

void PhysicsWorld2D::SendEndContactEvents()
{
    if (endContactInfos_.Empty())
        return;

    using namespace PhysicsEndContact2D;
    VariantMap& eventData = GetEventDataMap();
    VariantMap nodeEventData;
    eventData[P_WORLD] = this;

    for (unsigned i = 0; i < endContactInfos_.Size(); ++i)
    {
        ContactInfo& contactInfo = endContactInfos_[i];
        eventData[P_BODYA] = contactInfo.bodyA_.Get();
        eventData[P_BODYB] = contactInfo.bodyB_.Get();
        eventData[P_NODEA] = contactInfo.nodeA_.Get();
        eventData[P_NODEB] = contactInfo.nodeB_.Get();
        eventData[P_CONTACTS] = contactInfo.Serialize(contacts_);
        eventData[P_SHAPEA] = contactInfo.shapeA_.Get();
        eventData[P_SHAPEB] = contactInfo.shapeB_.Get();

        SendEvent(E_PHYSICSENDCONTACT2D, eventData);

        nodeEventData[NodeEndContact2D::P_CONTACTS] = contactInfo.Serialize(contacts_);

        if (contactInfo.nodeA_)
        {
            nodeEventData[NodeEndContact2D::P_BODY] = contactInfo.bodyA_.Get();
            nodeEventData[NodeEndContact2D::P_OTHERNODE] = contactInfo.nodeB_.Get();
            nodeEventData[NodeEndContact2D::P_OTHERBODY] = contactInfo.bodyB_.Get();
            nodeEventData[NodeEndContact2D::P_SHAPE] = contactInfo.shapeA_.Get();
            nodeEventData[NodeEndContact2D::P_OTHERSHAPE] = contactInfo.shapeB_.Get();

            contactInfo.nodeA_->SendEvent(E_NODEENDCONTACT2D, nodeEventData);
        }

        if (contactInfo.nodeB_)
        {
            nodeEventData[NodeEndContact2D::P_BODY] = contactInfo.bodyB_.Get();
            nodeEventData[NodeEndContact2D::P_OTHERNODE] = contactInfo.nodeA_.Get();
            nodeEventData[NodeEndContact2D::P_OTHERBODY] = contactInfo.bodyA_.Get();
            nodeEventData[NodeEndContact2D::P_SHAPE] = contactInfo.shapeB_.Get();
            nodeEventData[NodeEndContact2D::P_OTHERSHAPE] = contactInfo.shapeA_.Get();

            contactInfo.nodeB_->SendEvent(E_NODEENDCONTACT2D, nodeEventData);
        }
    }

    endContactInfos_.Clear();
}

PhysicsWorld2D::ContactInfo::ContactInfo() = default;

PhysicsWorld2D::ContactInfo::ContactInfo(b2Contact* contact)
{
    b2Fixture* fixtureA = contact->GetFixtureA();
    b2Fixture* fixtureB = contact->GetFixtureB();
    bodyA_ = (RigidBody2D*)(fixtureA->GetBody()->GetUserData());
    bodyB_ = (RigidBody2D*)(fixtureB->GetBody()->GetUserData());
    nodeA_ = bodyA_->GetNode();
    nodeB_ = bodyB_->GetNode();
    shapeA_ = (CollisionShape2D*)fixtureA->GetUserData();
    shapeB_ = (CollisionShape2D*)fixtureB->GetUserData();

    b2WorldManifold worldManifold;
    contact->GetWorldManifold(&worldManifold);
    numPoints_ = contact->GetManifold()->pointCount;
    worldNormal_ = Vector2(worldManifold.normal.x, worldManifold.normal.y);
    for (int i = 0; i < numPoints_; ++i)
    {
        worldPositions_[i] = Vector2(worldManifold.points[i].x, worldManifold.points[i].y);
        separations_[i] = worldManifold.separations[i];
    }
}

const Urho3D::PODVector<unsigned char>& PhysicsWorld2D::ContactInfo::Serialize(VectorBuffer& buffer) const
{
    buffer.Clear();
    for (int i = 0; i < numPoints_; ++i)
    {
        buffer.WriteVector2(worldPositions_[i]);
        buffer.WriteVector2(worldNormal_);
        buffer.WriteFloat(separations_[i]);
    }
    return buffer.GetBuffer();
}

}
