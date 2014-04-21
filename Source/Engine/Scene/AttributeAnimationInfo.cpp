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
#include "AttributeAnimationInfo.h"
#include "Log.h"

#include "DebugNew.h"

namespace Urho3D
{

AttributeAnimationInfo::AttributeAnimationInfo(AttributeAnimation* attributeAnimation, WrapMode wrapMode, float speed) :
    attributeAnimation_(attributeAnimation),
    wrapMode_(wrapMode),
    speed_(speed)
{
    speed_ = Max(0.0f, speed_);
}

AttributeAnimationInfo::AttributeAnimationInfo(const AttributeAnimationInfo& other) :
    attributeAnimation_(other.attributeAnimation_),
    wrapMode_(other.wrapMode_),
    speed_(other.speed_)
{
}

AttributeAnimationInfo::~AttributeAnimationInfo()
{
}

float AttributeAnimationInfo::CalculateScaledTime(float currentTime, bool& finished) const
{
    float beginTime = attributeAnimation_->GetBeginTime();
    float endTime = attributeAnimation_->GetEndTime();

    switch (wrapMode_)
    {
    case WM_LOOP:
        {
            float span = endTime - beginTime;
            float time = fmodf(currentTime - beginTime, span);
            if (time < 0.0f)
                time += span;
            return beginTime + time;
        }

    case WM_ONCE:
        finished = (currentTime >= endTime);
        // Fallthrough

    case WM_CLAMP:
        return Clamp(currentTime, beginTime, endTime);

    default:
        LOGERROR("Unsupported attribute animation wrap mode");
        return beginTime;
    }
}

void AttributeAnimationInfo::GetEventFrames(float beginTime, float endTime, PODVector<const AttributeEventFrame*>& eventFrames)
{
    switch (wrapMode_)
    {
    case WM_LOOP:
        if (beginTime < endTime)
            attributeAnimation_->GetEventFrames(beginTime, endTime, eventFrames);
        else
        {
            attributeAnimation_->GetEventFrames(beginTime, attributeAnimation_->GetEndTime(), eventFrames);
            attributeAnimation_->GetEventFrames(attributeAnimation_->GetBeginTime(), endTime, eventFrames);
        }
        break;

    case WM_ONCE:
    case WM_CLAMP:
        attributeAnimation_->GetEventFrames(beginTime, endTime, eventFrames);
        break;
    }
}

}
