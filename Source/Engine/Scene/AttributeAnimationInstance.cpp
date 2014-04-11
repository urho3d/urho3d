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

AttributeAnimationInstance::AttributeAnimationInstance(Animatable* animatable, const AttributeInfo& attributeInfo, AttributeAnimation* attributeAnimation, WrapMode wrapMode, float speed) :
    AttributeAnimationInfo(attributeAnimation, wrapMode, speed),
    animatable_(animatable),
    attributeInfo_(attributeInfo),
    currentTime_(0.0f),
    lastScaledTime_(0.0f)
{
}

AttributeAnimationInstance::AttributeAnimationInstance(const AttributeAnimationInstance& other) :
    AttributeAnimationInfo(other),
    animatable_(other.animatable_),
    attributeInfo_(other.attributeInfo_),
    currentTime_(0.0f),
    lastScaledTime_(0.0f)
{
}

AttributeAnimationInstance::~AttributeAnimationInstance()
{
}

bool AttributeAnimationInstance::Update(float timeStep)
{
    if (!attributeAnimation_)
        return true;
    
    currentTime_ += timeStep * speed_;
    
    if (!attributeAnimation_->IsValid())
        return true;

    bool finished = false;
    // Calculate scale time by wrap mode
    float scaledTime = CalculateScaledTime(currentTime_, finished);

    attributeAnimation_->UpdateAttributeValue(animatable_, attributeInfo_, scaledTime);

    if (attributeAnimation_->HasEventFrames())
    {
        Vector<const AttributeEventFrame*> eventFrames;
        switch (wrapMode_)
        {
        case WM_LOOP:
            if (lastScaledTime_ < scaledTime)
                attributeAnimation_->GetEventFrames(lastScaledTime_, scaledTime, eventFrames);
            else
            {
                attributeAnimation_->GetEventFrames(lastScaledTime_, attributeAnimation_->GetEndTime(), eventFrames);
                attributeAnimation_->GetEventFrames(attributeAnimation_->GetBeginTime(), scaledTime, eventFrames);
            }
            break;

        case WM_ONCE:
        case WM_CLAMP:
            attributeAnimation_->GetEventFrames(lastScaledTime_, scaledTime, eventFrames);
            break;
        }

        for (unsigned i = 0; i < eventFrames.Size(); ++i)
            animatable_->SendEvent(eventFrames[i]->eventType_, const_cast<VariantMap&>(eventFrames[i]->eventData_));
    }

    lastScaledTime_ = scaledTime;

    return finished;
}

Animatable* AttributeAnimationInstance::GetAnimatable() const
{
    return animatable_;
}

float AttributeAnimationInstance::CalculateScaledTime(float currentTime, bool& finished) const
{
    float beginTime = attributeAnimation_->GetBeginTime();
    float endTime = attributeAnimation_->GetEndTime();

    switch (wrapMode_)
    {
    case WM_LOOP:
        {
            float span = endTime - beginTime;
            return beginTime + fmodf(currentTime - beginTime, span);
        }

    case WM_ONCE:
        finished = (currentTime >= endTime);

    case WM_CLAMP:
        return Clamp(currentTime, beginTime, endTime);
    }

    return beginTime;
}

//Variant AttributeAnimationInstance::Interpolation(const AttributeKeyFrame& prevKeyFrame, const AttributeKeyFrame& currKeyFrame, float scaledTime) const
//{
//    float factor = (scaledTime - prevKeyFrame.time_) / (currKeyFrame.time_ - prevKeyFrame.time_);
//
//    switch (attributeAnimation_->GetValueType())
//    {
//    case VAR_FLOAT:
//        return Lerp(prevKeyFrame.value_.GetFloat(), currKeyFrame.value_.GetFloat(), factor);
//    case VAR_VECTOR2:
//        return prevKeyFrame.value_.GetVector2().Lerp(currKeyFrame.value_.GetVector2(), factor);
//    case VAR_VECTOR3:
//        return prevKeyFrame.value_.GetVector3().Lerp(currKeyFrame.value_.GetVector3(), factor);
//    case VAR_VECTOR4:
//        return prevKeyFrame.value_.GetVector4().Lerp(currKeyFrame.value_.GetVector4(), factor);
//    case VAR_QUATERNION:
//        return prevKeyFrame.value_.GetQuaternion().Slerp(currKeyFrame.value_.GetQuaternion(), factor);
//    case VAR_COLOR:
//        return prevKeyFrame.value_.GetColor().Lerp(currKeyFrame.value_.GetColor(), factor);
//    }
//
//    LOGERROR("value type");
//
//    return Variant::EMPTY;
//}

}