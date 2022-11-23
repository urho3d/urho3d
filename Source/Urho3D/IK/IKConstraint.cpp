// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#include "../Core/Context.h"
#include "../IK/IK.h"
#include "../IK/IKConstraint.h"
#include "../Scene/Node.h"
#include "../Scene/SceneEvents.h"

#include <ik/constraint.h>
#include <ik/node.h>

namespace Urho3D
{

extern const char* IK_CATEGORY;

// ----------------------------------------------------------------------------
IKConstraint::IKConstraint(Context* context) :
    Component(context),
    ikConstraintNode_(nullptr),
    stiffness_(0.0f),
    stretchiness_(0.0f)
{
}

// ----------------------------------------------------------------------------
IKConstraint::~IKConstraint() = default;

// ----------------------------------------------------------------------------
void IKConstraint::RegisterObject(Context* context)
{
    context->RegisterFactory<IKConstraint>(IK_CATEGORY);

    URHO3D_ACCESSOR_ATTRIBUTE("Stiffness", GetStiffness, SetStiffness, float, 0.0f, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Stretchiness", GetStretchiness, SetStretchiness, float, 0.0f, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Length Constraints", GetLengthConstraints, SetLengthConstraints, Vector2, Vector2::ZERO, AM_DEFAULT);
}

// ----------------------------------------------------------------------------
float IKConstraint::GetStiffness() const
{
    return stiffness_;
}

// ----------------------------------------------------------------------------
void IKConstraint::SetStiffness(float stiffness)
{
    stiffness_ = Clamp(stiffness, 0.0f, 1.0f);
    // TODO
    //if (ikConstraintNode_ != nullptr)
    //    ikNode_->stiffness = stiffness_;
}

// ----------------------------------------------------------------------------
float IKConstraint::GetStretchiness() const
{
    return stretchiness_;
}

// ----------------------------------------------------------------------------
void IKConstraint::SetStretchiness(float stretchiness)
{
    stretchiness_ = Clamp(stretchiness, 0.0f, 1.0f);
    // TODO
    //if (ikConstraintNode_)
    //   ikNode_->stretchiness = stretchiness_;
}

// ----------------------------------------------------------------------------
const Vector2& IKConstraint::GetLengthConstraints() const
{
    return lengthConstraints_;
}

// ----------------------------------------------------------------------------
void IKConstraint::SetLengthConstraints(const Vector2& lengthConstraints)
{
    lengthConstraints_ = lengthConstraints;
    if (ikConstraintNode_ != nullptr)
    {
        /* TODO
        ikNode_->min_length = lengthConstraints_.x_;
        ikNode_->max_length = lengthConstraints_.y_;*/
    }
}

// ----------------------------------------------------------------------------
void IKConstraint::SetIKConstraintNode(ik_node_t* constraintNode)
{
    ikConstraintNode_ = constraintNode;
    if (constraintNode != nullptr)
    {
        /* TODO
        node->stiffness = stiffness_;
        node->stretchiness = stretchiness_;
        node->min_length = lengthConstraints_.x_;
        node->max_length = lengthConstraints_.y_;*/
    }
}

} // namespace Urho3D
