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

#pragma once

#include "AnimationDefs.h"
#include "RefCounted.h"

namespace Urho3D
{

class ValueAnimation;
struct VAnimEventFrame;

/// Value animation info, it include animation, wrap mode and animation speed.
class ValueAnimationInfo : public RefCounted
{
public:
    /// Construct.
    ValueAnimationInfo(ValueAnimation* animation, WrapMode wrapMode, float speed);
    /// Construct.
    ValueAnimationInfo(const ValueAnimationInfo& other);
    /// Destruct.
    ~ValueAnimationInfo();

    /// Set wrap mode.
    void SetWrapMode(WrapMode wrapMode) { wrapMode_ = wrapMode; }
    /// Set speed.
    void SetSpeed(float speed) { speed_ = speed; }

    /// Return animation.
    ValueAnimation* GetAnimation() const { return animation_; }
    /// Return wrap mode.
    WrapMode GetWrapMode() const { return wrapMode_; }
    /// Return speed.
    float GetSpeed() const { return speed_; }

protected:
    /// Calculate scaled time.
    float CalculateScaledTime(float currentTime, bool& finished) const;
    /// Return event frames.
    void GetEventFrames(float beginTime, float endTime, PODVector<const VAnimEventFrame*>& eventFrames);

    /// Attribute animation.
    SharedPtr<ValueAnimation> animation_;
    /// Wrap mode.
    WrapMode wrapMode_;
    /// Animation speed.
    float speed_;
};

}
