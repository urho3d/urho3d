//
// Copyright (c) 2008-2016 the Urho3D project.
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

#pragma once

#include "../Container/RefCounted.h"
#include "../Scene/AnimationDefs.h"

namespace Urho3D
{

class Object;
class ValueAnimation;
struct VAnimEventFrame;

/// Base class for a value animation instance, which includes animation runtime information and updates the target object's value automatically.
class URHO3D_API ValueAnimationInfo : public RefCounted
{
public:
    /// Construct without target object.
    ValueAnimationInfo(ValueAnimation* animation, WrapMode wrapMode, float speed);
    /// Construct with target object.
    ValueAnimationInfo(Object* target, ValueAnimation* animation, WrapMode wrapMode, float speed);
    /// Copy construct.
    ValueAnimationInfo(const ValueAnimationInfo& other);
    /// Destruct.
    ~ValueAnimationInfo();

    /// Advance time position and apply. Return true when the animation is finished. No-op when the target object is not defined.
    bool Update(float timeStep);
    /// Set time position and apply. Return true when the animation is finished. No-op when the target object is not defined.
    bool SetTime(float time);

    /// Set wrap mode.
    void SetWrapMode(WrapMode wrapMode) { wrapMode_ = wrapMode; }

    /// Set speed.
    void SetSpeed(float speed) { speed_ = speed; }

    /// Return target object.
    Object* GetTarget() const;

    /// Return animation.
    ValueAnimation* GetAnimation() const { return animation_; }

    /// Return wrap mode.
    WrapMode GetWrapMode() const { return wrapMode_; }

    /// Return time position.
    float GetTime() const { return currentTime_; }

    /// Return speed.
    float GetSpeed() const { return speed_; }

protected:
    /// Apply new animation value to the target object. Called by Update().
    virtual void ApplyValue(const Variant& newValue);
    /// Calculate scaled time.
    float CalculateScaledTime(float currentTime, bool& finished) const;
    /// Return event frames.
    void GetEventFrames(float beginTime, float endTime, PODVector<const VAnimEventFrame*>& eventFrames);

    /// Target object.
    WeakPtr<Object> target_;
    /// Attribute animation.
    SharedPtr<ValueAnimation> animation_;
    /// Wrap mode.
    WrapMode wrapMode_;
    /// Animation speed.
    float speed_;
    /// Current time.
    float currentTime_;
    /// Last scaled time.
    float lastScaledTime_;
};

}
