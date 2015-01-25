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

#include "../Urho2D/CollisionShape2D.h"
#include "../Urho2D/Constraint2D.h"
#include "../Core/Context.h"
#include "../IO/Log.h"
#include "../Urho2D/PhysicsUtils2D.h"
#include "../Urho2D/PhysicsWorld2D.h"
#include "../Urho2D/RigidBody2D.h"
#include "../Scene/Scene.h"

#include "../DebugNew.h"

namespace Urho3D
{

extern const char* URHO2D_CATEGORY;
static const BodyType2D DEFAULT_BODYTYPE = BT_STATIC;

static const char* bodyTypeNames[] =
{
    "Static",
    "Dynamic",
    "Kinematic",
    0
};

RigidBody2D::RigidBody2D(Context* context) :
    Component(context),
    massData_(),    // b2MassData structure does not have a constructor so need to zero-initialize all its members
    useFixtureMass_(true),
    body_(0)
{
    // Make sure the massData's center is zero-initialized as well
    massData_.center.SetZero();
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

    ACCESSOR_ATTRIBUTE("Is Enabled", IsEnabled, SetEnabled, bool, true, AM_DEFAULT);
    ENUM_ACCESSOR_ATTRIBUTE("Body Type", GetBodyType, SetBodyType, BodyType2D, bodyTypeNames, DEFAULT_BODYTYPE, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE("Mass", GetMass, SetMass, float, 0.0f, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE("Inertia", GetInertia, SetInertia, float, 0.0f, AM_DEFAULT);
    MIXED_ACCESSOR_ATTRIBUTE("Mass Center", GetMassCenter, SetMassCenter, Vector2, Vector2::ZERO, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE("Use Fixture Mass", GetUseFixtureMass, SetUseFixtureMass, bool, true, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE("Linear Damping", GetLinearDamping, SetLinearDamping, float, 0.0f, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE("Angular Damping", GetAngularDamping, SetAngularDamping, float, 0.0f, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE("Allow Sleep", IsAllowSleep, SetAllowSleep, bool, true, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE("Fixed Rotation", IsFixedRotation, SetFixedRotation, bool, false, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE("Bullet", IsBullet, SetBullet, bool, false, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE("Gravity Scale", GetGravityScale, SetGravityScale, float, 1.0f, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE("Awake", IsAwake, SetAwake, bool, true, AM_DEFAULT);
    MIXED_ACCESSOR_ATTRIBUTE("Linear Velocity", GetLinearVelocity, SetLinearVelocity, Vector2, Vector2::ZERO, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE("Angular Velocity", GetAngularVelocity, SetAngularVelocity, float, 0.0f, AM_DEFAULT);
}


void RigidBody2D::OnSetEnabled()
{
    bool enabled = IsEnabledEffective();

    bodyDef_.active = enabled;

    if (body_)
        body_->SetActive(enabled);

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

    MarkNetworkUpdate();
}

void RigidBody2D::SetMass(float mass)
{
    mass = Max(mass, 0.0f);
    if (massData_.mass == mass)
        return;

    massData_.mass = mass;

    if (useFixtureMass_ && body_)
        body_->SetMassData(&massData_);

    MarkNetworkUpdate();
}

void RigidBody2D::SetInertia(float inertia)
{
    inertia = Max(inertia, 0.0f);
    if (massData_.I == inertia)
        return;

    massData_.I = inertia;

    if (useFixtureMass_ && body_)
        body_->SetMassData(&massData_);

    MarkNetworkUpdate();
}

void RigidBody2D::SetMassCenter(const Vector2& center)
{
    b2Vec2 b2Center = ToB2Vec2(center);
    if (massData_.center == b2Center)
        return;

    massData_.center = b2Center;

    if (useFixtureMass_ && body_)
        body_->SetMassData(&massData_);

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

    MarkNetworkUpdate();
}

void RigidBody2D::SetAngularDamping(float angularDamping)
{
    if (bodyDef_.angularDamping == angularDamping)
        return;

    bodyDef_.angularDamping = angularDamping;

    if (body_)
        body_->SetAngularDamping(angularDamping);

    MarkNetworkUpdate();
}

void RigidBody2D::SetAllowSleep(bool allowSleep)
{
    if (bodyDef_.allowSleep == allowSleep)
        return;

    bodyDef_.allowSleep = allowSleep;

    if (body_)
        body_->SetSleepingAllowed(allowSleep);

    MarkNetworkUpdate();
}

void RigidBody2D::SetFixedRotation(bool fixedRotation)
{
    if (bodyDef_.fixedRotation == fixedRotation)
        return;

    bodyDef_.fixedRotation = fixedRotation;

    if (body_)
        body_->SetFixedRotation(fixedRotation);

    MarkNetworkUpdate();
}

void RigidBody2D::SetBullet(bool bullet)
{
    if (bodyDef_.bullet == bullet)
        return;

    bodyDef_.bullet = bullet;

    if (body_)
        body_->SetBullet(bullet);

    MarkNetworkUpdate();
}

void RigidBody2D::SetGravityScale(float gravityScale)
{
    if (bodyDef_.gravityScale == gravityScale)
        return;

    bodyDef_.gravityScale = gravityScale;

    if (body_)
        body_->SetGravityScale(gravityScale);

    MarkNetworkUpdate();
}

void RigidBody2D::SetAwake(bool awake)
{
    if (bodyDef_.awake == awake)
        return;

    bodyDef_.awake = awake;

    if (body_)
        body_->SetAwake(awake);

    MarkNetworkUpdate();
}

void RigidBody2D::SetLinearVelocity(const Vector2& linearVelocity)
{
    b2Vec2 b2linearVelocity = ToB2Vec2(linearVelocity);
    if (bodyDef_.linearVelocity == b2linearVelocity)
        return;

    bodyDef_.linearVelocity = b2linearVelocity;

    if (body_)
        body_->SetLinearVelocity(b2linearVelocity);

    MarkNetworkUpdate();
}

void RigidBody2D::SetAngularVelocity(float angularVelocity)
{
    if (bodyDef_.angularVelocity == angularVelocity)
        return;

    bodyDef_.angularVelocity = angularVelocity;

    if (body_)
        body_->SetAngularVelocity(angularVelocity);

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
    if (body_ && impulse != Vector2::ZERO)
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

    bodyDef_.position = ToB2Vec2(node_->GetWorldPosition());;
    bodyDef_.angle = node_->GetWorldRotation().RollAngle() * M_DEGTORAD;

    body_ = physicsWorld_->GetWorld()->CreateBody(&bodyDef_);
    body_->SetUserData(this);

    for (unsigned i = 0; i < collisionShapes_.Size(); ++i)
    {
        if (collisionShapes_[i])
            collisionShapes_[i]->CreateFixture();
    }

    if (!useFixtureMass_)
        body_->SetMassData(&massData_);

    for (unsigned i = 0; i < constraints_.Size(); ++i)
    {
            if (constraints_[i])
            constraints_[i]->CreateJoint();
    }
}

void RigidBody2D::ReleaseBody()
{
    if (!body_)
        return;

    if (!physicsWorld_ || !physicsWorld_->GetWorld())
        return;

    for (unsigned i = 0; i < constraints_.Size(); ++i)
    {
        if (constraints_[i])
            constraints_[i]->ReleaseJoint();
    }

    for (unsigned i = 0; i < collisionShapes_.Size(); ++i)
    {
        if (collisionShapes_[i])
            collisionShapes_[i]->ReleaseFixture();
    }

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

void RigidBody2D::AddConstraint2D(Constraint2D* constraint)
{
    if (!constraint)
        return;

    WeakPtr<Constraint2D> constraintPtr(constraint);
    if (constraints_.Contains(constraintPtr))
        return;
    constraints_.Push(constraintPtr);
}

void RigidBody2D::RemoveConstraint2D(Constraint2D* constraint)
{
    if (!constraint)
        return;

    WeakPtr<Constraint2D> constraintPtr(constraint);
    constraints_.Remove(constraintPtr);
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
        node->AddListener(this);
        Scene* scene = GetScene();
        physicsWorld_ = scene->GetOrCreateComponent<PhysicsWorld2D>();

        CreateBody();
        physicsWorld_->AddRigidBody(this);
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
    float newAngle = node_->GetWorldRotation().RollAngle() * M_DEGTORAD;
    if (newPosition != bodyDef_.position || newAngle != bodyDef_.angle)
    {
        bodyDef_.position = newPosition;
        bodyDef_.angle = newAngle;
        if (body_)
            body_->SetTransform(newPosition, newAngle);
    }
}

}
