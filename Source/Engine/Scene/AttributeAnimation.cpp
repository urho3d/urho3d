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
    animationMode_(AM_LOOP)
{
}

AttributeAnimation::~AttributeAnimation()
{
}

void AttributeAnimation::SetAnimationMode(AnimationMode animationMode)
{
    animationMode_ = animationMode;
}

void AttributeAnimation::AddKeyFrame(float time, const Variant& value)
{
    KeyFrame keyFrame;
    keyFrame.time_ = time;
    keyFrame.value_ = value;

    keyframes_.Push(keyFrame);
}

VariantType AttributeAnimation::GetValueType() const
{
    return keyframes_.Empty() ? VAR_NONE : keyframes_[0].value_.GetType();
}

void AttributeAnimation::GetValue(float animationTime, Variant& animationValue) const
{
    if (keyframes_.Empty())
        return;

    float keyTime = CalculateTime(animationTime, keyframes_.Back().time_);

    for (unsigned i = 1; i < keyframes_.Size(); ++i)
    {
        if (keyframes_[i].time_ > keyTime)
        {
            // Hack here
            if (GetValueType() == VAR_COLOR)
            {
                float t = (keyTime - keyframes_[i - 1].time_) / (keyframes_[i].time_ - keyframes_[i - 1].time_);
                animationValue = keyframes_[i - 1].value_.GetColor().Lerp(keyframes_[i].value_.GetColor(), t);
            }
            else
                animationValue = keyframes_[i - 1].value_;

            break;
        }
    }
}

float AttributeAnimation::CalculateTime(float animationTime, float totalTime) const
{
    switch (animationMode_)
    {
    case AM_LOOP:
        return fmodf(animationTime, totalTime);

    case AM_CLAMP:
        return Clamp(animationTime, 0.0f, totalTime);

    case AM_PINGPONG:
        {
            float doubleTotalTime = totalTime * 2.0f;
            float fract = fmodf(animationTime, doubleTotalTime);
            return (fract < totalTime) ? fract : doubleTotalTime - fract;
        }
        break;
    }

    return animationTime;
}

}
