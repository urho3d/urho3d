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
#include "Animatable.h"
#include "AttributeAnimation.h"
#include "AttributeAnimationInstance.h"
#include "Log.h"

#include "DebugNew.h"

namespace Urho3D
{

AttributeAnimationInstance::AttributeAnimationInstance(Animatable* animatable, const AttributeInfo& attributeInfo, AttributeAnimation* attributeAnimation) :
    animatable_(animatable),
    attributeInfo_(attributeInfo),
    attributeAnimation_(attributeAnimation),
    currentTime_(0.0f),
    lastScaledTime_(0.0f)
{
}

AttributeAnimationInstance::AttributeAnimationInstance(const AttributeAnimationInstance& other) :
    animatable_(other.animatable_),
    attributeInfo_(other.attributeInfo_),
    attributeAnimation_(other.attributeAnimation_),
    currentTime_(0.0f),
    lastScaledTime_(0.0f)
{
}

AttributeAnimationInstance::~AttributeAnimationInstance()
{
}

void AttributeAnimationInstance::Update(float timeStep)
{
    if (!attributeAnimation_)
        return;
    
    currentTime_ += timeStep;
    
    const Vector<AttributeKeyFrame>& keyFrames = attributeAnimation_->GetKeyFrames();
    if (keyFrames.Size() < 2)
        return;

    float scaledTime = attributeAnimation_->CalculateScaledTime(currentTime_);
    for (unsigned i = 1; i < keyFrames.Size(); ++i)
    {
        const AttributeKeyFrame& currKeyFrame = keyFrames[i];
        if (scaledTime <= currKeyFrame.time_)
        {
            const AttributeKeyFrame& prevKeyFrame = keyFrames[i - 1];
            if (!attributeAnimation_->IsInterpolatable())
                animatable_->OnSetAttribute(attributeInfo_, prevKeyFrame.value_);
            else
                animatable_->OnSetAttribute(attributeInfo_, Interpolation(prevKeyFrame, currKeyFrame, scaledTime));
            break;
        }
    }

    if (attributeAnimation_->HasEventFrames())
    {
        Vector<const AttributeEventFrame*> eventFrames;
        switch (attributeAnimation_->GetCycleMode())
        {
        case CM_LOOP:
            if (lastScaledTime_ < scaledTime)
                attributeAnimation_->GetEventFrames(lastScaledTime_, scaledTime, eventFrames);
            else
            {
                attributeAnimation_->GetEventFrames(lastScaledTime_, attributeAnimation_->GetEndTime(), eventFrames);
                attributeAnimation_->GetEventFrames(attributeAnimation_->GetBeginTime(), scaledTime, eventFrames);
            }
            break;
        case CM_CLAMP:
            attributeAnimation_->GetEventFrames(lastScaledTime_, scaledTime, eventFrames);
            break;

        case CM_PINGPONG:
            // Not implement
            break;
        }

        for (unsigned i = 0; i < eventFrames.Size(); ++i)
            animatable_->SendEvent(eventFrames[i]->eventType_, const_cast<VariantMap&>(eventFrames[i]->eventData_));
    }

    lastScaledTime_ = scaledTime;
}

Animatable* AttributeAnimationInstance::GetAnimatable() const
{
    return animatable_;
}

AttributeAnimation* AttributeAnimationInstance::GetAttributeAnimation() const
{
    return attributeAnimation_;
}

Variant AttributeAnimationInstance::Interpolation(const AttributeKeyFrame& prevKeyFrame, const AttributeKeyFrame& currKeyFrame, float scaledTime) const
{
    float factor = (scaledTime - prevKeyFrame.time_) / (currKeyFrame.time_ - prevKeyFrame.time_);

    switch (attributeAnimation_->GetValueType())
    {
    case VAR_FLOAT:
        return Lerp(prevKeyFrame.value_.GetFloat(), currKeyFrame.value_.GetFloat(), factor);
    case VAR_VECTOR2:
        return prevKeyFrame.value_.GetVector2().Lerp(currKeyFrame.value_.GetVector2(), factor);
    case VAR_VECTOR3:
        return prevKeyFrame.value_.GetVector3().Lerp(currKeyFrame.value_.GetVector3(), factor);
    case VAR_VECTOR4:
        return prevKeyFrame.value_.GetVector4().Lerp(currKeyFrame.value_.GetVector4(), factor);
    case VAR_QUATERNION:
        return prevKeyFrame.value_.GetQuaternion().Slerp(currKeyFrame.value_.GetQuaternion(), factor);
    case VAR_COLOR:
        return prevKeyFrame.value_.GetColor().Lerp(currKeyFrame.value_.GetColor(), factor);
    }

    LOGERROR("value type");

    return Variant::EMPTY;
}

}