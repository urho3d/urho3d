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
#include "CollisionShape2D.h"
#include "Context.h"
#include "Log.h"
#include "PhysicsUtils2D.h"
#include "PhysicsWorld2D.h"
#include "RigidBody2D.h"
#include "Scene.h"

#include "DebugNew.h"

namespace Urho3D
{

extern const char* URHO2D_CATEGORY;

RigidBody2D::RigidBody2D(Context* context) : Component(context),
    body_(0), 
    bodyDirty_(true),
    useFixtureMass_(true)
{
    massData_.mass = 0.0f;
    massData_.I = 0.0f;
}

RigidBody2D::~RigidBody2D()
{
    if (physicsWorld_)
    {
        ReleaseBody();

        physicsWorld_->RemoveRigidBody(this);
    }
}

void RigidBody2D::RegisterObject(Context* context)
{
    context->RegisterFactory<RigidBody2D>(URHO2D_CATEGORY);

    ACCESSOR_ATTRIBUTE(RigidBody2D, VAR_VECTOR2, "Mass Center", GetMassCenter, SetMassCenter, Vector2, Vector2::ZERO, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(RigidBody2D, VAR_BOOL, "Use Fixture Mass", GetUseFixtureMass, SetUseFixtureMass, bool, false, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(RigidBody2D, VAR_FLOAT, "Linear Damping", GetLinearDamping, SetLinearDamping, float, 0.0f, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(RigidBody2D, VAR_FLOAT, "Angular Damping", GetAngularDamping, SetAngularDamping, float, 0.0f, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(RigidBody2D, VAR_BOOL, "Fixed Rotation", IsFixedRotation, SetFixedRotation, bool, false, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(RigidBody2D, VAR_FLOAT, "Gravity Scale", GetGravityScale, SetGravityScale, float, 1.0f, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(RigidBody2D, VAR_VECTOR2, "Linear Velocity", GetLinearVelocity, SetLinearVelocity, Vector2, Vector2::ZERO, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(RigidBody2D, VAR_FLOAT, "Angular Velocity", GetAngularVelocity, SetAngularVelocity, float, 0.0f, AM_DEFAULT);

    COPY_BASE_ATTRIBUTES(RigidBody2D, Component);
}


void RigidBody2D::OnSetEnabled()
{
    bool enabled = IsEnabledEffective();

    bodyDef_.active = enabled;

    if (body_)
        body_->SetActive(enabled);
    else
        bodyDirty_ = true;

    MarkNetworkUpdate();
}

void RigidBody2D::SetBodyType(BodyType2D type)
{
    b2BodyType bodyType = (b2BodyType)type;
    if (bodyDef_.type == bodyType)
        return;

    bodyDef_.type = bodyType;

    if (body_)
        body_->SetType(bodyType);
    else
        bodyDirty_ = true;

    MarkNetworkUpdate();
}

void RigidBody2D::SetMass(float mass)
{
    mass = Max(mass, 0.0f);
    if (massData_.mass == mass)
        return;

    massData_.mass = mass;

    if (useFixtureMass_)
    {
        if (body_)
            body_->SetMassData(&massData_);
        else
            bodyDirty_ = true;
    }

    MarkNetworkUpdate();
}

void RigidBody2D::SetInertia(float inertia)
{
    inertia = Max(inertia, 0.0f);
    if (massData_.I == inertia)
        return;

    massData_.I = inertia;

    if (useFixtureMass_)
    {
        if (body_)
            body_->SetMassData(&massData_);
        else
            bodyDirty_ = true;
    }

    MarkNetworkUpdate();
}

void RigidBody2D::SetMassCenter(Vector2 center)
{
    b2Vec2 b2Center = ToB2Vec2(center);
    if (massData_.center == b2Center)
        return;

    massData_.center = b2Center;

    if (useFixtureMass_)
    {
        if (body_)
            body_->SetMassData(&massData_);
        else
            bodyDirty_ = true;
    }

    MarkNetworkUpdate();
}

void RigidBody2D::SetUseFixtureMass(bool useFixtureMass)
{
    if (useFixtureMass_ == useFixtureMass)
        return;

    useFixtureMass_ = useFixtureMass;

    if (body_)
    {
       if (useFixtureMass_)
            body_->ResetMassData();
        else
            body_->SetMassData(&massData_);
    }

    MarkNetworkUpdate();
}

void RigidBody2D::SetLinearDamping(float linearDamping)
{
    if (bodyDef_.linearDamping == linearDamping)
        return;

    bodyDef_.linearDamping = linearDamping;

    if (body_)
        body_->SetLinearDamping(linearDamping);
    else
        bodyDirty_ = true;

    MarkNetworkUpdate();
}

void RigidBody2D::SetAngularDamping(float angularDamping)
{
    if (bodyDef_.angularDamping == angularDamping)
        return;

    bodyDef_.angularDamping = angularDamping;

    if (body_)
        body_->SetAngularDamping(angularDamping);
    else
        bodyDirty_ = true;

    MarkNetworkUpdate();
}

void RigidBody2D::SetAllowSleep(bool allowSleep)
{
    if (bodyDef_.allowSleep == allowSleep)
        return;

    bodyDef_.allowSleep = allowSleep;

    if (body_)
        body_->SetSleepingAllowed(allowSleep);
    else
        bodyDirty_ = true;

    MarkNetworkUpdate();
}

void RigidBody2D::SetFixedRotation(bool fixedRotation)
{
    if (bodyDef_.fixedRotation == fixedRotation)
        return;

    bodyDef_.fixedRotation = fixedRotation;

    if (body_)
        body_->SetFixedRotation(fixedRotation);
    else
        bodyDirty_ = true;

    MarkNetworkUpdate();
}

void RigidBody2D::SetBullet(bool bullet)
{
    if (bodyDef_.bullet == bullet)
        return;

    bodyDef_.bullet = bullet;

    if (body_)
        body_->SetBullet(bullet);
    else
        bodyDirty_ = true;

    MarkNetworkUpdate();
}

void RigidBody2D::SetGravityScale(float gravityScale)
{
    if (bodyDef_.gravityScale == gravityScale)
        return;

    bodyDef_.gravityScale = gravityScale;

    if (body_)
        body_->SetGravityScale(gravityScale);
    else
        bodyDirty_ = true;

    MarkNetworkUpdate();
}

void RigidBody2D::SetAwake(bool awake)
{
    if (bodyDef_.awake == awake)
        return;

    bodyDef_.awake = awake;

    if (body_)
        body_->SetAwake(awake);
    else
        bodyDirty_ = true;

    MarkNetworkUpdate();
}

void RigidBody2D::SetLinearVelocity(Vector2 linearVelocity)
{
    b2Vec2 b2linearVelocity = ToB2Vec2(linearVelocity);
    if (bodyDef_.linearVelocity == b2linearVelocity)
        return;

    bodyDef_.linearVelocity = b2linearVelocity;

    if (body_)
        body_->SetLinearVelocity(b2linearVelocity);
    else
        bodyDirty_ = true;

    MarkNetworkUpdate();
}

void RigidBody2D::SetAngularVelocity(float angularVelocity)
{
    if (bodyDef_.angularVelocity == angularVelocity)
        return;

    bodyDef_.angularVelocity = angularVelocity;

    if (body_)
        body_->SetAngularVelocity(angularVelocity);
    else
        bodyDirty_ = true;

    MarkNetworkUpdate();
}

void RigidBody2D::ApplyForce(const Vector2& force, const Vector2& point, bool wake)
{
    if (body_ && force != Vector2::ZERO)
        body_->ApplyForce(ToB2Vec2(force), ToB2Vec2(point), wake);
}

void RigidBody2D::ApplyForceToCenter(const Vector2& force, bool wake)
{
    if (body_ && force != Vector2::ZERO)
        body_->ApplyForceToCenter(ToB2Vec2(force), wake);
}

void RigidBody2D::ApplyTorque(float torque, bool wake)
{
    if (body_ && torque != 0)
        body_->ApplyTorque(torque, wake);
}

void RigidBody2D::ApplyLinearImpulse(const Vector2& impulse, const Vector2& point, bool wake)
{
    if (body_ && impulse != 0)
        body_->ApplyLinearImpulse(ToB2Vec2(impulse), ToB2Vec2(point), wake);
}

void RigidBody2D::ApplyAngularImpulse(float impulse, bool wake)
{
    if (body_)
        body_->ApplyAngularImpulse(impulse, wake);
}

void RigidBody2D::CreateBody()
{
    if (body_)
        return;

    if (!physicsWorld_ || !physicsWorld_->GetWorld())
        return;

    body_ = physicsWorld_->GetWorld()->CreateBody(&bodyDef_);
    body_->SetUserData(this);

    for (unsigned i = 0; i < collisionShapes_.Size(); ++i)
        if (collisionShapes_[i])
            collisionShapes_[i]->ReleaseFixture();

    if (!useFixtureMass_)
        body_->SetMassData(&massData_);
}

void RigidBody2D::UpdateBody()
{
    bool shapeDirty = false;
    for (unsigned i = 0; i < collisionShapes_.Size(); ++i)
    {
        if (collisionShapes_[i]->IsFixtureDirty())
        {
            shapeDirty = true;
            break;
        }
    }

    if (!bodyDirty_ || !shapeDirty)
        return;

    if (bodyDirty_)
    {
        for (unsigned i = 0; i < collisionShapes_.Size(); ++i)
            collisionShapes_[i]->ReleaseFixture();
        ReleaseBody();

        CreateBody();
        for (unsigned i = 0; i < collisionShapes_.Size(); ++i)
            collisionShapes_[i]->CreateFixture();
        bodyDirty_ = false;
    }
    else
    {
        for (unsigned i = 0; i < collisionShapes_.Size(); ++i)
            collisionShapes_[i]->UpdateFixture();
    }
}

void RigidBody2D::ReleaseBody()
{
    if (!body_)
        return;

    if (!physicsWorld_ || !physicsWorld_->GetWorld())
        return;

    for (unsigned i = 0; i < collisionShapes_.Size(); ++i)
        if (collisionShapes_[i])
            collisionShapes_[i]->ReleaseFixture();

    physicsWorld_->GetWorld()->DestroyBody(body_);
    body_ = 0;
}

void RigidBody2D::ApplyWorldTransform()
{
    if (!body_)
        return;

    physicsWorld_->SetApplyingTransforms(true);

    Node* node = GetNode();
    const b2Transform& transform = body_->GetTransform();
    node->SetWorldPosition(ToVector3(transform.p));
    node->SetWorldRotation(Quaternion(transform.q.GetAngle() * M_RADTODEG, Vector3::FORWARD));

    physicsWorld_->SetApplyingTransforms(false);
}

void RigidBody2D::AddCollisionShape2D(CollisionShape2D* collisionShape)
{
    if (!collisionShape)
        return;

    WeakPtr<CollisionShape2D> collisionShapePtr(collisionShape);
    if (collisionShapes_.Contains(collisionShapePtr))
        return;
    collisionShapes_.Push(collisionShapePtr);
}

void RigidBody2D::RemoveCollisionShape2D(CollisionShape2D* collisionShape)
{
    if (!collisionShape)
        return;

    WeakPtr<CollisionShape2D> collisionShapePtr(collisionShape);
    collisionShapes_.Remove(collisionShapePtr);
}

float RigidBody2D::GetMass() const
{
    if (!useFixtureMass_)
        return massData_.mass;

    return body_ ? body_->GetMass() : 0.0f;
}

float RigidBody2D::GetInertia() const
{
    if (!useFixtureMass_)
        return massData_.I;

    return body_ ? body_->GetInertia() : 0.0f;
}

Vector2 RigidBody2D::GetMassCenter() const
{
    if (!useFixtureMass_)
        return ToVector2(massData_.center);

    return body_ ? ToVector2(body_->GetLocalCenter()) : Vector2::ZERO;
}

bool RigidBody2D::IsAwake() const
{
    return body_ ? body_->IsAwake() : bodyDef_.awake;
}

Vector2 RigidBody2D::GetLinearVelocity() const
{
    return ToVector2(body_ ? body_->GetLinearVelocity() : bodyDef_.linearVelocity);
}

float RigidBody2D::GetAngularVelocity() const
{
    return body_ ? body_->GetAngularVelocity() : bodyDef_.angularVelocity;
}

void RigidBody2D::OnNodeSet(Node* node)
{
    Component::OnNodeSet(node);

    if (node)
    {
        Scene* scene = GetScene();
        physicsWorld_ = scene->GetComponent<PhysicsWorld2D>();
        if (physicsWorld_)
            physicsWorld_->AddRigidBody(this);
        else
            LOGERROR("No physic world component in scene, can not create rigid body");
    }
}

void RigidBody2D::OnMarkedDirty(Node* node)
{
    if (physicsWorld_ && physicsWorld_->IsApplyingTransforms())
        return;

    // Physics operations are not safe from worker threads
    Scene* scene = GetScene();
    if (scene && scene->IsThreadedUpdate())
    {
        scene->DelayedMarkedDirty(this);
        return;
    }

    // Check if transform has changed from the last one set in ApplyWorldTransform()
    b2Vec2 newPosition = ToB2Vec2(node_->GetWorldPosition());
    if (bodyDef_.position != newPosition)
    {
        bodyDef_.position = newPosition;
        if (body_)
            body_->SetTransform(newPosition, 0.0f);
        else
            bodyDirty_ = true;
    }
}

}

