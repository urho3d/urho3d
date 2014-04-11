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

#include "AttributeAnimationInfo.h"

namespace Urho3D
{

class Animatable;

/// Attribute animation instance, it include animation runtime information, when animation playing it will update the object's attribute value automatically.
class URHO3D_API AttributeAnimationInstance : public AttributeAnimationInfo
{
public:
    /// Construct.
    AttributeAnimationInstance(Animatable* animatable, const AttributeInfo& attributeInfo, AttributeAnimation* attributeAnimation, WrapMode wrapMode, float speed);
    /// Construct.
    AttributeAnimationInstance(const AttributeAnimationInstance& other);
    /// Destruct.
    ~AttributeAnimationInstance();

    /// Update (if animaiton finished return true).
    bool Update(float timeStep);

    /// Return animatable.
    Animatable* GetAnimatable() const;
    /// Return attribute infomation.
    const AttributeInfo& GetAttributeInfo() const { return attributeInfo_; }
    /// Return current time.
    float GetCurrentTime() const { return currentTime_; }

private:
    /// Calculate scaled time.
    float CalculateScaledTime(float currentTime, bool& finished) const;
    /// Interpolation.
    Variant Interpolation(const AttributeKeyFrame& prevKeyFrame, const AttributeKeyFrame& currKeyFrame, float scaledTime) const;

    /// Animatable.
    WeakPtr<Animatable> animatable_;
    /// Attribute information.
    const AttributeInfo& attributeInfo_;
    /// Current time.
    float currentTime_;
    /// Last scaled time.
    float lastScaledTime_;
};

}
