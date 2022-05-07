// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#include "../Precompiled.h"

#include "../Core/Context.h"
#include "../Core/Profiler.h"
#include "../Graphics/DebugRenderer.h"
#include "../IO/Log.h"
#include "../Physics/Constraint.h"
#include "../Physics/PhysicsUtils.h"
#include "../Physics/PhysicsWorld.h"
#include "../Physics/RigidBody.h"
#include "../Scene/Scene.h"

#include <Bullet/BulletDynamics/ConstraintSolver/btConeTwistConstraint.h>
#include <Bullet/BulletDynamics/ConstraintSolver/btHingeConstraint.h>
#include <Bullet/BulletDynamics/ConstraintSolver/btPoint2PointConstraint.h>
#include <Bullet/BulletDynamics/ConstraintSolver/btSliderConstraint.h>
#include <Bullet/BulletDynamics/Dynamics/btDiscreteDynamicsWorld.h>

using namespace std;

namespace Urho3D
{

static const char* typeNames[] =
{
    "Point",
    "Hinge",
    "Slider",
    "ConeTwist",
    nullptr
};

extern const char* PHYSICS_CATEGORY;

Constraint::Constraint(Context* context) :
    Component(context),
    constraintType_(CONSTRAINT_POINT),
    position_(Vector3::ZERO),
    rotation_(Quaternion::IDENTITY),
    otherPosition_(Vector3::ZERO),
    otherRotation_(Quaternion::IDENTITY),
    highLimit_(Vector2::ZERO),
    lowLimit_(Vector2::ZERO),
    erp_(0.0f),
    cfm_(0.0f),
    otherBodyNodeID_(0),
    disableCollision_(false),
    recreateConstraint_(true),
    framesDirty_(false),
    retryCreation_(false)
{
}

Constraint::~Constraint()
{
    ReleaseConstraint();

    if (physicsWorld_)
        physicsWorld_->RemoveConstraint(this);
}

void Constraint::RegisterObject(Context* context)
{
    context->RegisterFactory<Constraint>(PHYSICS_CATEGORY);

    URHO3D_ACCESSOR_ATTRIBUTE("Is Enabled", IsEnabled, SetEnabled, bool, true, AM_DEFAULT);
    URHO3D_ENUM_ATTRIBUTE_EX("Constraint Type", constraintType_, MarkConstraintDirty, typeNames, CONSTRAINT_POINT, AM_DEFAULT);
    URHO3D_ATTRIBUTE_EX("Position", Vector3, position_, AdjustOtherBodyPosition, Vector3::ZERO, AM_DEFAULT);
    URHO3D_ATTRIBUTE_EX("Rotation", Quaternion, rotation_, MarkFramesDirty, Quaternion::IDENTITY, AM_DEFAULT);
    URHO3D_ATTRIBUTE_EX("Other Body Position", Vector3, otherPosition_, MarkFramesDirty, Vector3::ZERO, AM_DEFAULT);
    URHO3D_ATTRIBUTE_EX("Other Body Rotation", Quaternion, otherRotation_, MarkFramesDirty, Quaternion::IDENTITY, AM_DEFAULT);
    URHO3D_ATTRIBUTE_EX("Other Body NodeID", unsigned, otherBodyNodeID_, MarkConstraintDirty, 0, AM_DEFAULT | AM_NODEID);
    URHO3D_ACCESSOR_ATTRIBUTE("High Limit", GetHighLimit, SetHighLimit, Vector2, Vector2::ZERO, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Low Limit", GetLowLimit, SetLowLimit, Vector2, Vector2::ZERO, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("ERP Parameter", GetERP, SetERP, float, 0.0f, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("CFM Parameter", GetCFM, SetCFM, float, 0.0f, AM_DEFAULT);
    URHO3D_ATTRIBUTE_EX("Disable Collision", bool, disableCollision_, MarkConstraintDirty, false, AM_DEFAULT);
}

void Constraint::ApplyAttributes()
{
    if (recreateConstraint_)
    {
        if (otherBody_)
            otherBody_->RemoveConstraint(this);

        otherBody_.Reset();

        Scene* scene = GetScene();
        if (scene && otherBodyNodeID_)
        {
            Node* otherNode = scene->GetNode(otherBodyNodeID_);
            if (otherNode)
                otherBody_ = otherNode->GetComponent<RigidBody>();
        }

        CreateConstraint();
    }
    else if (framesDirty_)
    {
        ApplyFrames();
        framesDirty_ = false;
    }
}

void Constraint::OnSetEnabled()
{
    if (constraint_)
        constraint_->setEnabled(IsEnabledEffective());
}

void Constraint::GetDependencyNodes(PODVector<Node*>& dest)
{
    if (otherBody_ && otherBody_->GetNode())
        dest.Push(otherBody_->GetNode());
}

void Constraint::DrawDebugGeometry(DebugRenderer* debug, bool depthTest)
{
    if (debug && physicsWorld_ && constraint_)
    {
        physicsWorld_->SetDebugRenderer(debug);
        physicsWorld_->SetDebugDepthTest(depthTest);
        physicsWorld_->GetWorld()->debugDrawConstraint(constraint_.get());
        physicsWorld_->SetDebugRenderer(nullptr);
    }
}

void Constraint::SetConstraintType(ConstraintType type)
{
    if (type != constraintType_ || !constraint_)
    {
        constraintType_ = type;
        CreateConstraint();
        MarkNetworkUpdate();
    }
}

void Constraint::SetOtherBody(RigidBody* body)
{
    if (otherBody_ != body)
    {
        if (otherBody_)
            otherBody_->RemoveConstraint(this);

        otherBody_ = body;

        // Update the connected body attribute
        Node* otherNode = otherBody_ ? otherBody_->GetNode() : nullptr;
        otherBodyNodeID_ = otherNode ? otherNode->GetID() : 0;

        CreateConstraint();
        MarkNetworkUpdate();
    }
}

void Constraint::SetPosition(const Vector3& position)
{
    if (position != position_)
    {
        position_ = position;
        ApplyFrames();
        MarkNetworkUpdate();
    }
}

void Constraint::SetRotation(const Quaternion& rotation)
{
    if (rotation != rotation_)
    {
        rotation_ = rotation;
        ApplyFrames();
        MarkNetworkUpdate();
    }
}

void Constraint::SetAxis(const Vector3& axis)
{
    switch (constraintType_)
    {
    case CONSTRAINT_POINT:
    case CONSTRAINT_HINGE:
        rotation_ = Quaternion(Vector3::FORWARD, axis);
        break;

    case CONSTRAINT_SLIDER:
    case CONSTRAINT_CONETWIST:
        rotation_ = Quaternion(Vector3::RIGHT, axis);
        break;

    default:
        break;
    }

    ApplyFrames();
    MarkNetworkUpdate();
}

void Constraint::SetOtherPosition(const Vector3& position)
{
    if (position != otherPosition_)
    {
        otherPosition_ = position;
        ApplyFrames();
        MarkNetworkUpdate();
    }
}

void Constraint::SetOtherRotation(const Quaternion& rotation)
{
    if (rotation != otherRotation_)
    {
        otherRotation_ = rotation;
        ApplyFrames();
        MarkNetworkUpdate();
    }
}

void Constraint::SetOtherAxis(const Vector3& axis)
{
    switch (constraintType_)
    {
    case CONSTRAINT_POINT:
    case CONSTRAINT_HINGE:
        otherRotation_ = Quaternion(Vector3::FORWARD, axis);
        break;

    case CONSTRAINT_SLIDER:
    case CONSTRAINT_CONETWIST:
        otherRotation_ = Quaternion(Vector3::RIGHT, axis);
        break;

    default:
        break;
    }

    ApplyFrames();
    MarkNetworkUpdate();
}

void Constraint::SetWorldPosition(const Vector3& position)
{
    if (constraint_)
    {
        btTransform ownBodyInverse = constraint_->getRigidBodyA().getWorldTransform().inverse();
        btTransform otherBodyInverse = constraint_->getRigidBodyB().getWorldTransform().inverse();
        btVector3 worldPos = ToBtVector3(position);
        position_ = (ToVector3(ownBodyInverse * worldPos) + ownBody_->GetCenterOfMass()) / cachedWorldScale_;
        otherPosition_ = ToVector3(otherBodyInverse * worldPos);
        if (otherBody_)
        {
            otherPosition_ += otherBody_->GetCenterOfMass();
            otherPosition_ /= otherBody_->GetNode()->GetWorldScale();
        }
        ApplyFrames();
        MarkNetworkUpdate();
    }
    else
        URHO3D_LOGWARNING("Constraint not created, world position could not be stored");
}

void Constraint::SetHighLimit(const Vector2& limit)
{
    if (limit != highLimit_)
    {
        highLimit_ = limit;
        ApplyLimits();
        MarkNetworkUpdate();
    }
}

void Constraint::SetLowLimit(const Vector2& limit)
{
    if (limit != lowLimit_)
    {
        lowLimit_ = limit;
        ApplyLimits();
        MarkNetworkUpdate();
    }
}

void Constraint::SetERP(float erp)
{
    erp = Max(erp, 0.0f);

    if (erp != erp_)
    {
        erp_ = erp;
        ApplyLimits();
        MarkNetworkUpdate();
    }
}

void Constraint::SetCFM(float cfm)
{
    cfm = Max(cfm, 0.0f);

    if (cfm != cfm_)
    {
        cfm_ = cfm;
        ApplyLimits();
        MarkNetworkUpdate();
    }
}

void Constraint::SetDisableCollision(bool disable)
{
    if (disable != disableCollision_)
    {
        disableCollision_ = disable;
        CreateConstraint();
        MarkNetworkUpdate();
    }
}

Vector3 Constraint::GetWorldPosition() const
{
    if (constraint_)
    {
        btTransform ownBody = constraint_->getRigidBodyA().getWorldTransform();
        return ToVector3(ownBody * ToBtVector3(position_ * cachedWorldScale_ - ownBody_->GetCenterOfMass()));
    }
    else
        return Vector3::ZERO;
}

void Constraint::ReleaseConstraint()
{
    if (constraint_)
    {
        if (ownBody_)
            ownBody_->RemoveConstraint(this);
        if (otherBody_)
            otherBody_->RemoveConstraint(this);

        if (physicsWorld_)
            physicsWorld_->GetWorld()->removeConstraint(constraint_.get());

        constraint_.reset();
    }
}

void Constraint::ApplyFrames()
{
    if (!constraint_ || !node_ || (otherBody_ && !otherBody_->GetNode()))
        return;

    cachedWorldScale_ = node_->GetWorldScale();

    Vector3 ownBodyScaledPosition = position_ * cachedWorldScale_ - ownBody_->GetCenterOfMass();
    Vector3 otherBodyScaledPosition =
        otherBody_ ? otherPosition_ * otherBody_->GetNode()->GetWorldScale() - otherBody_->GetCenterOfMass() : otherPosition_;

    switch (constraint_->getConstraintType())
    {
    case POINT2POINT_CONSTRAINT_TYPE:
        {
            auto* pointConstraint = static_cast<btPoint2PointConstraint*>(constraint_.get());
            pointConstraint->setPivotA(ToBtVector3(ownBodyScaledPosition));
            pointConstraint->setPivotB(ToBtVector3(otherBodyScaledPosition));
        }
        break;

    case HINGE_CONSTRAINT_TYPE:
        {
            auto* hingeConstraint = static_cast<btHingeConstraint*>(constraint_.get());
            btTransform ownFrame(ToBtQuaternion(rotation_), ToBtVector3(ownBodyScaledPosition));
            btTransform otherFrame(ToBtQuaternion(otherRotation_), ToBtVector3(otherBodyScaledPosition));
            hingeConstraint->setFrames(ownFrame, otherFrame);
        }
        break;

    case SLIDER_CONSTRAINT_TYPE:
        {
            auto* sliderConstraint = static_cast<btSliderConstraint*>(constraint_.get());
            btTransform ownFrame(ToBtQuaternion(rotation_), ToBtVector3(ownBodyScaledPosition));
            btTransform otherFrame(ToBtQuaternion(otherRotation_), ToBtVector3(otherBodyScaledPosition));
            sliderConstraint->setFrames(ownFrame, otherFrame);
        }
        break;

    case CONETWIST_CONSTRAINT_TYPE:
        {
            auto* coneTwistConstraint = static_cast<btConeTwistConstraint*>(constraint_.get());
            btTransform ownFrame(ToBtQuaternion(rotation_), ToBtVector3(ownBodyScaledPosition));
            btTransform otherFrame(ToBtQuaternion(otherRotation_), ToBtVector3(otherBodyScaledPosition));
            coneTwistConstraint->setFrames(ownFrame, otherFrame);
        }
        break;

    default:
        break;
    }
}

void Constraint::OnNodeSet(Node* node)
{
    if (node)
    {
        node->AddListener(this);
        cachedWorldScale_ = node->GetWorldScale();
    }
}

void Constraint::OnSceneSet(Scene* scene)
{
    if (scene)
    {
        if (scene == node_)
            URHO3D_LOGWARNING(GetTypeName() + " should not be created to the root scene node");

        physicsWorld_ = scene->GetOrCreateComponent<PhysicsWorld>();
        physicsWorld_->AddConstraint(this);

        // Create constraint now if necessary (attributes modified before adding to scene)
        if (retryCreation_)
            CreateConstraint();
    }
    else
    {
        ReleaseConstraint();

        if (physicsWorld_)
            physicsWorld_->RemoveConstraint(this);

        // Recreate when moved to a scene again
        retryCreation_ = true;
    }
}

void Constraint::OnMarkedDirty(Node* node)
{
    /// \todo This does not catch the connected body node's scale changing
    if (HasWorldScaleChanged(cachedWorldScale_, node->GetWorldScale()))
        ApplyFrames();
}

void Constraint::CreateConstraint()
{
    URHO3D_PROFILE(CreateConstraint);

    cachedWorldScale_ = node_->GetWorldScale();

    ReleaseConstraint();

    ownBody_ = GetComponent<RigidBody>();
    btRigidBody* ownBody = ownBody_ ? ownBody_->GetBody() : nullptr;
    btRigidBody* otherBody = otherBody_ ? otherBody_->GetBody() : nullptr;

    // If no physics world available now mark for retry later
    if (!physicsWorld_ || !ownBody)
    {
        retryCreation_ = true;
        return;
    }

    if (!otherBody)
        otherBody = &btTypedConstraint::getFixedBody();

    Vector3 ownBodyScaledPosition = position_ * cachedWorldScale_ - ownBody_->GetCenterOfMass();
    Vector3 otherBodyScaledPosition = otherBody_ ? otherPosition_ * otherBody_->GetNode()->GetWorldScale() -
                                                   otherBody_->GetCenterOfMass() : otherPosition_;

    switch (constraintType_)
    {
    case CONSTRAINT_POINT:
        {
            constraint_ = make_unique<btPoint2PointConstraint>(*ownBody, *otherBody, ToBtVector3(ownBodyScaledPosition),
                ToBtVector3(otherBodyScaledPosition));
        }
        break;

    case CONSTRAINT_HINGE:
        {
            btTransform ownFrame(ToBtQuaternion(rotation_), ToBtVector3(ownBodyScaledPosition));
            btTransform otherFrame(ToBtQuaternion(otherRotation_), ToBtVector3(otherBodyScaledPosition));
            constraint_ = make_unique<btHingeConstraint>(*ownBody, *otherBody, ownFrame, otherFrame);
        }
        break;

    case CONSTRAINT_SLIDER:
        {
            btTransform ownFrame(ToBtQuaternion(rotation_), ToBtVector3(ownBodyScaledPosition));
            btTransform otherFrame(ToBtQuaternion(otherRotation_), ToBtVector3(otherBodyScaledPosition));
            constraint_ = make_unique<btSliderConstraint>(*ownBody, *otherBody, ownFrame, otherFrame, false);
        }
        break;

    case CONSTRAINT_CONETWIST:
        {
            btTransform ownFrame(ToBtQuaternion(rotation_), ToBtVector3(ownBodyScaledPosition));
            btTransform otherFrame(ToBtQuaternion(otherRotation_), ToBtVector3(otherBodyScaledPosition));
            constraint_ = make_unique<btConeTwistConstraint>(*ownBody, *otherBody, ownFrame, otherFrame);
        }
        break;

    default:
        break;
    }

    if (constraint_)
    {
        constraint_->setUserConstraintPtr(this);
        constraint_->setEnabled(IsEnabledEffective());
        ownBody_->AddConstraint(this);
        if (otherBody_)
            otherBody_->AddConstraint(this);

        ApplyLimits();

        physicsWorld_->GetWorld()->addConstraint(constraint_.get(), disableCollision_);
    }

    recreateConstraint_ = false;
    framesDirty_ = false;
    retryCreation_ = false;
}

void Constraint::ApplyLimits()
{
    if (!constraint_)
        return;

    switch (constraint_->getConstraintType())
    {
    case HINGE_CONSTRAINT_TYPE:
        {
            auto* hingeConstraint = static_cast<btHingeConstraint*>(constraint_.get());
            hingeConstraint->setLimit(lowLimit_.x_ * M_DEGTORAD, highLimit_.x_ * M_DEGTORAD);
        }
        break;

    case SLIDER_CONSTRAINT_TYPE:
        {
            auto* sliderConstraint = static_cast<btSliderConstraint*>(constraint_.get());
            sliderConstraint->setUpperLinLimit(highLimit_.x_);
            sliderConstraint->setUpperAngLimit(highLimit_.y_ * M_DEGTORAD);
            sliderConstraint->setLowerLinLimit(lowLimit_.x_);
            sliderConstraint->setLowerAngLimit(lowLimit_.y_ * M_DEGTORAD);
        }
        break;

    case CONETWIST_CONSTRAINT_TYPE:
        {
            auto* coneTwistConstraint = static_cast<btConeTwistConstraint*>(constraint_.get());
            coneTwistConstraint->setLimit(highLimit_.y_ * M_DEGTORAD, highLimit_.y_ * M_DEGTORAD, highLimit_.x_ * M_DEGTORAD);
        }
        break;

    default:
        break;
    }

    if (erp_ != 0.0f)
        constraint_->setParam(BT_CONSTRAINT_STOP_ERP, erp_);
    if (cfm_ != 0.0f)
        constraint_->setParam(BT_CONSTRAINT_STOP_CFM, cfm_);
}

void Constraint::AdjustOtherBodyPosition()
{
    // Convenience for editing static constraints: if not connected to another body, adjust world position to match local
    // (when deserializing, the proper other body position will be read after own position, so this calculation is safely
    // overridden and does not accumulate constraint error
    if (constraint_ && !otherBody_)
    {
        btTransform ownBody = constraint_->getRigidBodyA().getWorldTransform();
        btVector3 worldPos = ownBody * ToBtVector3(position_ * cachedWorldScale_ - ownBody_->GetCenterOfMass());
        otherPosition_ = ToVector3(worldPos);
    }

    MarkFramesDirty();
}

}
