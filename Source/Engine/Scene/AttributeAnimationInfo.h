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

#include "AttributeAnimationDefs.h"
#include "RefCounted.h"

namespace Urho3D
{

class AttributeAnimation;

/// Attribute animation info, it include attribute animation, wrap mode and animation speed.
class URHO3D_API AttributeAnimationInfo : public RefCounted
{
public:
    /// Construct.
    AttributeAnimationInfo(AttributeAnimation* attributeAnimation, WrapMode wrapMode, float speed);
    /// Construct.
    AttributeAnimationInfo(const AttributeAnimationInfo& other);
    /// Destruct.
    ~AttributeAnimationInfo();

    /// Set wrap mode.
    void SetWrapMode(WrapMode wrapMode) { wrapMode_ = wrapMode; }
    /// Set speed.
    void SetSpeed(float speed) { speed_ = speed; }

    /// Return attribute animation.
    AttributeAnimation* GetAttributeAnimation() const { return attributeAnimation_; }
    /// Return wrap mode.
    WrapMode GetWrapMode() const { return wrapMode_; }
    /// Return speed.
    float GetSpeed() const { return speed_; }

protected:
    /// Attribute animation.
    SharedPtr<AttributeAnimation> attributeAnimation_;
    /// Wrap mode.
    WrapMode wrapMode_;
    /// Animation speed.
    float speed_;
};

}
