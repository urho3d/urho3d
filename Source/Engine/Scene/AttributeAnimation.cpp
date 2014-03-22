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
#include "AttributeAnimation.h"

#include "DebugNew.h"

namespace Urho3D
{

AttributeAnimation::AttributeAnimation(Context* context) :
    Serializable(context),
    valueType_(VAR_NONE),
    cycleMode_(CM_LOOP),
    minTime_(M_INFINITY),
    maxTime_(-M_INFINITY)
{
}

AttributeAnimation::~AttributeAnimation()
{
}

void AttributeAnimation::SetValueType(VariantType valueType)
{
    if (valueType == valueType_)
        return;

    valueType_ = valueType;
    
    keyframes_.Clear();
    minTime_ = M_INFINITY;
    maxTime_ = -M_INFINITY;
}

void AttributeAnimation::SetCycleMode(CycleMode cycleMode)
{
    cycleMode_ = cycleMode;
}

void AttributeAnimation::AddKeyFrame(float time, const Variant& value)
{
    minTime_ = Min(time, minTime_);
    maxTime_ = Max(time, maxTime_);

    KeyFrame keyFrame;
    keyFrame.time_ = time;
    keyFrame.value_ = value;

    keyframes_.Push(keyFrame);
}

void AttributeAnimation::GetValue(float animationTime, Variant& animationValue) const
{
    if (keyframes_.Empty())
        return;

    float scaledTime = CalculateScaledTime(animationTime);

    for (unsigned i = 1; i < keyframes_.Size(); ++i)
    {
        if (keyframes_[i].time_ > scaledTime)
        {
            Interpolation(keyframes_[i - 1], keyframes_[i], scaledTime, animationValue);
            break;
        }
    }
}

float AttributeAnimation::CalculateScaledTime(float animationTime) const
{
    switch (cycleMode_)
    {
    case CM_LOOP:
        {
            float span = maxTime_ - minTime_;
            return minTime_ + fmodf(animationTime - minTime_, span);
        }

    case CM_CLAMP:
        return Clamp(animationTime, minTime_, maxTime_);

    case CM_PINGPONG:
        {
            float span = maxTime_ - minTime_;
            float doubleSpan = span * 2.0f;
            float fract = fmodf(animationTime - minTime_, doubleSpan);
            return (fract < span) ? minTime_ + fract : minTime_ + doubleSpan - fract;
        }
        break;
    }

    return animationTime;
}

void AttributeAnimation::Interpolation(const KeyFrame& loKeyFrame, const KeyFrame& hiKeyFrame, float scaledTime, Variant& animationValue) const
{
    switch (valueType_)
    {
    case VAR_INT:
        animationValue = loKeyFrame.value_.GetInt();
        return;
    case VAR_BOOL:
        animationValue = loKeyFrame.value_.GetBool();
        return;
    case VAR_FLOAT:
        {
            float factor = (scaledTime - loKeyFrame.time_) / (hiKeyFrame.time_ - loKeyFrame.time_);
            animationValue = Lerp(loKeyFrame.value_.GetFloat(), hiKeyFrame.value_.GetFloat(), factor);
        }
        return;
    case VAR_VECTOR2:
        {
            float factor = (scaledTime - loKeyFrame.time_) / (hiKeyFrame.time_ - loKeyFrame.time_);
            animationValue = loKeyFrame.value_.GetVector2().Lerp(hiKeyFrame.value_.GetVector2(), factor);
        }
        return;
    case VAR_VECTOR3:
        {
            float factor = (scaledTime - loKeyFrame.time_) / (hiKeyFrame.time_ - loKeyFrame.time_);
            animationValue = loKeyFrame.value_.GetVector3().Lerp(hiKeyFrame.value_.GetVector3(), factor);
        }
        return;
    case VAR_VECTOR4:
        {
            float factor = (scaledTime - loKeyFrame.time_) / (hiKeyFrame.time_ - loKeyFrame.time_);
            animationValue = loKeyFrame.value_.GetVector4().Lerp(hiKeyFrame.value_.GetVector4(), factor);
        }
        return;
    case VAR_QUATERNION:
        {
            float factor = (scaledTime - loKeyFrame.time_) / (hiKeyFrame.time_ - loKeyFrame.time_);
            animationValue = loKeyFrame.value_.GetQuaternion().Slerp(hiKeyFrame.value_.GetQuaternion(), factor);
        }
        return;
    case VAR_COLOR:
        {
            float factor = (scaledTime - loKeyFrame.time_) / (hiKeyFrame.time_ - loKeyFrame.time_);
            animationValue = loKeyFrame.value_.GetColor().Lerp(hiKeyFrame.value_.GetColor(), factor);
        }
        return;
    case VAR_STRING:
        animationValue = loKeyFrame.value_.GetString();
        return;
    case VAR_BUFFER:
        animationValue = loKeyFrame.value_.GetBuffer();
        return;
    case VAR_VOIDPTR:
        animationValue = loKeyFrame.value_.GetVoidPtr();
        return;
    case VAR_RESOURCEREF:
        animationValue = loKeyFrame.value_.GetResourceRef();
        return;
    case VAR_RESOURCEREFLIST:
        animationValue = loKeyFrame.value_.GetResourceRefList();
        return;
    case VAR_VARIANTVECTOR:
        animationValue = loKeyFrame.value_.GetVariantVector();
        return;
    case VAR_VARIANTMAP:
        animationValue = loKeyFrame.value_.GetVariantMap();
        return;
    case VAR_INTRECT:
        animationValue = loKeyFrame.value_.GetIntRect();
        return;
    case VAR_INTVECTOR2:
        animationValue = loKeyFrame.value_.GetIntVector2();
        return;
    case VAR_PTR:
        animationValue = loKeyFrame.value_.GetPtr();
        return;
    }
}

}
