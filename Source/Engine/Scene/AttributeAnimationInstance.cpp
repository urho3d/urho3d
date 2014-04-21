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
#include "AttributeAnimationInstance.h"
#include "Log.h"
#include "ValueAnimation.h"

#include "DebugNew.h"

namespace Urho3D
{

AttributeAnimationInstance::AttributeAnimationInstance(Animatable* animatable, const AttributeInfo& attributeInfo, ValueAnimation* attributeAnimation, WrapMode wrapMode, float speed) :
    ValueAnimationInfo(attributeAnimation, wrapMode, speed),
    animatable_(animatable),
    attributeInfo_(attributeInfo),
    currentTime_(0.0f),
    lastScaledTime_(0.0f)
{
}

AttributeAnimationInstance::AttributeAnimationInstance(const AttributeAnimationInstance& other) :
    ValueAnimationInfo(other),
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
    if (!animation_)
        return true;

    currentTime_ += timeStep * speed_;

    if (!animation_->IsValid())
        return true;

    bool finished = false;
    // Calculate scale time by wrap mode
    float scaledTime = CalculateScaledTime(currentTime_, finished);

    animatable_->OnSetAttribute(attributeInfo_, animation_->GetAnimationValue(scaledTime));

    if (animation_->HasEventFrames())
    {
        PODVector<const VAnimEventFrame*> eventFrames;
        GetEventFrames(lastScaledTime_, scaledTime, eventFrames);

        for (unsigned i = 0; i < eventFrames.Size(); ++i)
            animatable_->SendEvent(eventFrames[i]->eventType_, const_cast<VariantMap&>(eventFrames[i]->eventData_));
    }

    lastScaledTime_ = scaledTime;

    return finished;
}

}
