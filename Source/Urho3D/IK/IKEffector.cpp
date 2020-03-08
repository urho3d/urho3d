//
// Copyright (c) 2008-2020 the Urho3D project.
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

#include "../Core/Context.h"
#include "../Graphics/DebugRenderer.h"
#include "../IK/IKConverters.h"
#include "../IK/IKEffector.h"
#include "../IK/IKEvents.h"
#include "../IK/IKSolver.h"
#include "../Scene/SceneEvents.h"
#include "../IO/Log.h"

#include <ik/node.h>
#include <ik/effector.h>
#include <ik/solver.h>
#include <ik/util.h>

namespace Urho3D
{

extern const char* IK_CATEGORY;

// ----------------------------------------------------------------------------
IKEffector::IKEffector(Context* context) :
    Component(context),
    ikEffectorNode_(nullptr),
    chainLength_(0),
    weight_(1.0f),
    rotationWeight_(1.0),
    rotationDecay_(0.25),
    features_(0)
{
    URHO3D_LOGDEBUG("IKEffector created");
}

// ----------------------------------------------------------------------------
IKEffector::~IKEffector()
{
    URHO3D_LOGDEBUG("IKEffector destroyed");
}

// ----------------------------------------------------------------------------
void IKEffector::RegisterObject(Context* context)
{
    context->RegisterFactory<IKEffector>(IK_CATEGORY);

    URHO3D_ACCESSOR_ATTRIBUTE("Target Node", GetTargetName, SetTargetName, String, String::EMPTY, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Chain Length", GetChainLength, SetChainLength, unsigned, 0, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Target Position", GetTargetPosition, SetTargetPosition, Vector3, Vector3::ZERO, AM_DEFAULT);
    URHO3D_MIXED_ACCESSOR_ATTRIBUTE("Target Rotation", GetTargetRotationEuler, SetTargetRotationEuler, Vector3, Vector3::ZERO, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Weight", GetWeight, SetWeight, float, 1.0, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Rotation Weight", GetRotationWeight, SetRotationWeight, float, 1.0, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Rotation Decay", GetRotationDecay, SetRotationDecay, float, 0.25, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Nlerp Weight", GetWEIGHT_NLERP, SetWEIGHT_NLERP, bool, false, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Inherit Parent Rotation", GetINHERIT_PARENT_ROTATION, SetINHERIT_PARENT_ROTATION, bool, false, AM_DEFAULT);
}

// ----------------------------------------------------------------------------
Node* IKEffector::GetTargetNode() const
{
    return targetNode_;
}

// ----------------------------------------------------------------------------
void IKEffector::SetTargetNode(Node* targetNode)
{
    using namespace IKEffectorTargetChanged;

    VariantMap& eventData = GetEventDataMap();
    eventData[P_EFFECTORNODE] = node_;       // The effector node that has changed targets
    eventData[P_TARGETNODE]   = targetNode_; // The new target node. NOTE: Can be NULL (means no target)
    SendEvent(E_IKEFFECTORTARGETCHANGED, eventData);

    // Finally change the target node
    targetNode_ = targetNode;
    targetName_ = targetNode != nullptr ? targetNode->GetName() : "";
}

// ----------------------------------------------------------------------------
const String& IKEffector::GetTargetName() const
{
    return targetName_;
}

// ----------------------------------------------------------------------------
void IKEffector::SetTargetName(const String& nodeName)
{
    targetName_ = nodeName;
    targetNode_ = nullptr;
}

// ----------------------------------------------------------------------------
const Vector3& IKEffector::GetTargetPosition() const
{
    return targetPosition_;
}

// ----------------------------------------------------------------------------
void IKEffector::SetTargetPosition(const Vector3& targetPosition)
{
    targetPosition_ = targetPosition;
    if (ikEffectorNode_ != nullptr)
        ikEffectorNode_->effector->target_position = Vec3Urho2IK(targetPosition);
}

// ----------------------------------------------------------------------------
const Quaternion& IKEffector::GetTargetRotation() const
{
    return targetRotation_;
}

// ----------------------------------------------------------------------------
void IKEffector::SetTargetRotation(const Quaternion& targetRotation)
{
    targetRotation_ = targetRotation;
    if (ikEffectorNode_)
        ikEffectorNode_->effector->target_rotation = QuatUrho2IK(targetRotation);
}

// ----------------------------------------------------------------------------
Vector3 IKEffector::GetTargetRotationEuler() const
{
    return targetRotation_.EulerAngles();
}

// ----------------------------------------------------------------------------
void IKEffector::SetTargetRotationEuler(const Vector3& targetRotation)
{
    SetTargetRotation(Quaternion(targetRotation.x_, targetRotation.y_, targetRotation.z_));
}

// ----------------------------------------------------------------------------
unsigned int IKEffector::GetChainLength() const
{
    return chainLength_;
}

// ----------------------------------------------------------------------------
void IKEffector::SetChainLength(unsigned chainLength)
{
    chainLength_ = chainLength;
    if (ikEffectorNode_ != nullptr)
    {
        ikEffectorNode_->effector->chain_length = chainLength;
        solver_->MarkChainsNeedUpdating();
    }
}

// ----------------------------------------------------------------------------
float IKEffector::GetWeight() const
{
    return weight_;
}

// ----------------------------------------------------------------------------
void IKEffector::SetWeight(float weight)
{
    weight_ = Clamp(weight, 0.0f, 1.0f);
    if (ikEffectorNode_ != nullptr)
        ikEffectorNode_->effector->weight = weight_;
}

// ----------------------------------------------------------------------------
float IKEffector::GetRotationWeight() const
{
    return rotationWeight_;
}

// ----------------------------------------------------------------------------
void IKEffector::SetRotationWeight(float weight)
{
    rotationWeight_ = Clamp(weight, 0.0f, 1.0f);
    if (ikEffectorNode_ != nullptr)
    {
        ikEffectorNode_->rotation_weight = rotationWeight_;
        ik_calculate_rotation_weight_decays(&solver_->solver_->chain_tree);
    }
}

// ----------------------------------------------------------------------------
float IKEffector::GetRotationDecay() const
{
    return rotationDecay_;
}

// ----------------------------------------------------------------------------
void IKEffector::SetRotationDecay(float decay)
{
    rotationDecay_ = Clamp(decay, 0.0f, 1.0f);
    if (ikEffectorNode_ != nullptr)
    {
        ikEffectorNode_->effector->rotation_decay = rotationDecay_;
        ik_calculate_rotation_weight_decays(&solver_->solver_->chain_tree);
    }
}

// ----------------------------------------------------------------------------
void IKEffector::SetFeature(Feature feature, bool enable)
{
    switch (feature)
    {
        case WEIGHT_NLERP:
        {
            if (ikEffectorNode_ != nullptr)
            {
                ikEffectorNode_->effector->flags &= ~EFFECTOR_WEIGHT_NLERP;
                if (enable)
                    ikEffectorNode_->effector->flags |= EFFECTOR_WEIGHT_NLERP;
            }
        } break;

        case INHERIT_PARENT_ROTATION:
            break;
    }

    features_ &= ~feature;
    if (enable)
        features_ |= feature;
}

// ----------------------------------------------------------------------------
bool IKEffector::GetFeature(Feature feature) const
{
    return (features_ & feature) != 0;
}

// ----------------------------------------------------------------------------
void IKEffector::UpdateTargetNodePosition()
{
    if (targetNode_ != nullptr || targetName_.Empty())
        return;

    // Try to find a node with the same name as our target name
    SetTargetNode(node_->GetScene()->GetChild(targetName_, true));
    if (targetNode_ == nullptr)
        return;

    SetTargetPosition(targetNode_->GetWorldPosition());
    SetTargetRotation(targetNode_->GetWorldRotation());
}

// ----------------------------------------------------------------------------
void IKEffector::DrawDebugGeometry(bool depthTest)
{
    auto* debug = GetScene()->GetComponent<DebugRenderer>();
    if (debug)
        DrawDebugGeometry(debug, depthTest);
}

// ----------------------------------------------------------------------------
void IKEffector::DrawDebugGeometry(DebugRenderer* debug, bool depthTest)
{
    Node* terminationNode;
    if (solver_ == nullptr)
        terminationNode = GetScene();
    else
        terminationNode = solver_->GetNode();

    // Calculate average length of all segments so we can determine the radius
    // of the debug spheres to draw
    int chainLength = chainLength_ == 0 ? -1 : chainLength_;
    Node* a = node_;
    float averageLength = 0.0f;
    unsigned numberOfSegments = 0;
    while (a && a != terminationNode->GetParent() && chainLength-- != 0)
    {
        averageLength += a->GetPosition().Length();
        ++numberOfSegments;
        a = a->GetParent();
    }
    averageLength /= numberOfSegments;

    // connect all chained nodes together with lines
    chainLength = chainLength_ == 0 ? -1 : chainLength_;
    a = node_;
    Node* b = a->GetParent();
    debug->AddSphere(
        Sphere(a->GetWorldPosition(), averageLength * 0.1f),
        Color::YELLOW,
        depthTest
    );
    while (b && b != terminationNode->GetParent() && chainLength-- != 0)
    {
        debug->AddLine(
            a->GetWorldPosition(),
            b->GetWorldPosition(),
            Color::WHITE,
            depthTest
        );
        debug->AddSphere(
            Sphere(b->GetWorldPosition(), averageLength * 0.1f),
            Color::YELLOW,
            depthTest
        );
        a = b;
        b = b->GetParent();
    }

    Vector3 direction = targetRotation_ * Vector3::FORWARD;
    direction = direction * averageLength + targetPosition_;
    debug->AddSphere(Sphere(targetPosition_, averageLength * 0.2f), Color(255, 128, 0), depthTest);
    debug->AddLine(targetPosition_, direction, Color(255, 128, 0), depthTest);
}

// ----------------------------------------------------------------------------
void IKEffector::SetIKEffectorNode(ik_node_t* effectorNode)
{
    ikEffectorNode_ = effectorNode;
    if (effectorNode)
    {
        ikEffectorNode_->effector->target_position = Vec3Urho2IK(targetPosition_);
        ikEffectorNode_->effector->target_rotation = QuatUrho2IK(targetRotation_);
        ikEffectorNode_->effector->weight = weight_;
        ikEffectorNode_->effector->rotation_weight = rotationWeight_;
        ikEffectorNode_->effector->rotation_decay = rotationDecay_;
        ikEffectorNode_->effector->chain_length = chainLength_;

        if (features_ & WEIGHT_NLERP)
            ikEffectorNode_->effector->flags |= EFFECTOR_WEIGHT_NLERP;
    }
}

// ----------------------------------------------------------------------------
void IKEffector::SetIKSolver(IKSolver* solver)
{
    solver_ = solver;
}

// ----------------------------------------------------------------------------
// Need these wrapper functions flags of GetFeature/SetFeature can be correctly
// exposed to the editor
// ----------------------------------------------------------------------------

#define DEF_FEATURE_GETTER(feature_name)   \
bool IKEffector::Get##feature_name() const \
{                                          \
    return GetFeature(feature_name);       \
}

#define DEF_FEATURE_SETTER(feature_name)        \
void IKEffector::Set##feature_name(bool enable) \
{                                               \
    SetFeature(feature_name, enable);           \
}

DEF_FEATURE_GETTER(WEIGHT_NLERP)
DEF_FEATURE_GETTER(INHERIT_PARENT_ROTATION)

DEF_FEATURE_SETTER(WEIGHT_NLERP)
DEF_FEATURE_SETTER(INHERIT_PARENT_ROTATION)


} // namespace Urho3D
