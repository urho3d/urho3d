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

#include "../Core/Context.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneEvents.h"
#include "../Scene/SmoothedTransform.h"

#include "../DebugNew.h"

namespace Urho3D
{

SmoothedTransform::SmoothedTransform(Context* context) :
    Component(context),
    targetPosition_(Vector3::ZERO),
    targetRotation_(Quaternion::IDENTITY),
    smoothingMask_(SMOOTH_NONE),
    subscribed_(false)
{
}

SmoothedTransform::~SmoothedTransform()
{
}

void SmoothedTransform::RegisterObject(Context* context)
{
    context->RegisterFactory<SmoothedTransform>();
}

void SmoothedTransform::Update(float constant, float squaredSnapThreshold)
{
    if (smoothingMask_ && node_)
    {
        Vector3 position = node_->GetPosition();
        Quaternion rotation = node_->GetRotation();

        if (smoothingMask_ & SMOOTH_POSITION)
        {
            // If position snaps, snap everything to the end
            float delta = (position - targetPosition_).LengthSquared();
            if (delta > squaredSnapThreshold)
                constant = 1.0f;

            if (delta < M_EPSILON || constant >= 1.0f)
            {
                position = targetPosition_;
                smoothingMask_ &= ~SMOOTH_POSITION;
            }
            else
                position = position.Lerp(targetPosition_, constant);

            node_->SetPosition(position);
        }

        if (smoothingMask_ & SMOOTH_ROTATION)
        {
            float delta = (rotation - targetRotation_).LengthSquared();
            if (delta < M_EPSILON || constant >= 1.0f)
            {
                rotation = targetRotation_;
                smoothingMask_ &= ~SMOOTH_ROTATION;
            }
            else
                rotation = rotation.Slerp(targetRotation_, constant);

            node_->SetRotation(rotation);
        }
    }

    // If smoothing has completed, unsubscribe from the update event
    if (!smoothingMask_)
    {
        UnsubscribeFromEvent(GetScene(), E_UPDATESMOOTHING);
        subscribed_ = false;
    }
}

void SmoothedTransform::SetTargetPosition(const Vector3& position)
{
    targetPosition_ = position;
    smoothingMask_ |= SMOOTH_POSITION;

    // Subscribe to smoothing update if not yet subscribed
    if (!subscribed_)
    {
        SubscribeToEvent(GetScene(), E_UPDATESMOOTHING, HANDLER(SmoothedTransform, HandleUpdateSmoothing));
        subscribed_ = true;
    }

    SendEvent(E_TARGETPOSITION);
}

void SmoothedTransform::SetTargetRotation(const Quaternion& rotation)
{
    targetRotation_ = rotation;
    smoothingMask_ |= SMOOTH_ROTATION;

    if (!subscribed_)
    {
        SubscribeToEvent(GetScene(), E_UPDATESMOOTHING, HANDLER(SmoothedTransform, HandleUpdateSmoothing));
        subscribed_ = true;
    }

    SendEvent(E_TARGETROTATION);
}

void SmoothedTransform::SetTargetWorldPosition(const Vector3& position)
{
    if (node_ && node_->GetParent())
        SetTargetPosition(node_->GetParent()->GetWorldTransform().Inverse() * position);
    else
        SetTargetPosition(position);
}

void SmoothedTransform::SetTargetWorldRotation(const Quaternion& rotation)
{
    if (node_ && node_->GetParent())
        SetTargetRotation(node_->GetParent()->GetWorldRotation().Inverse() * rotation);
    else
        SetTargetRotation(rotation);
}

Vector3 SmoothedTransform::GetTargetWorldPosition() const
{
    if (node_ && node_->GetParent())
        return node_->GetParent()->GetWorldTransform() * targetPosition_;
    else
        return targetPosition_;
}

Quaternion SmoothedTransform::GetTargetWorldRotation() const
{
    if (node_ && node_->GetParent())
        return node_->GetParent()->GetWorldRotation() * targetRotation_;
    else
        return targetRotation_;
}

void SmoothedTransform::OnNodeSet(Node* node)
{
    if (node)
    {
        // Copy initial target transform
        targetPosition_ = node->GetPosition();
        targetRotation_ = node->GetRotation();
    }
}

void SmoothedTransform::HandleUpdateSmoothing(StringHash eventType, VariantMap& eventData)
{
    using namespace UpdateSmoothing;

    float constant = eventData[P_CONSTANT].GetFloat();
    float squaredSnapThreshold = eventData[P_SQUAREDSNAPTHRESHOLD].GetFloat();
    Update(constant, squaredSnapThreshold);
}

}
