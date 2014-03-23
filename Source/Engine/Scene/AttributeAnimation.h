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

#include "Serializable.h"
#include "Variant.h"

namespace Urho3D
{

/// Cycle mode.
enum CycleMode
{
    /// Loop mode.
    CM_LOOP = 0,
    /// Clamp mode.
    CM_CLAMP,
    /// Pingpong Mode.
    CM_PINGPONG,
};

/// Base class for attribute animation.
class URHO3D_API AttributeAnimation : public Serializable
{
    OBJECT(AttributeAnimation);

public:
    /// Construct.
    AttributeAnimation(Context* context);
    /// Destruct.
    virtual ~AttributeAnimation();
    
    /// Set cycle mode.
    void SetCycleMode(CycleMode cycleMode);
    /// Set value type.
    void SetValueType(VariantType valueType);
    /// Set key frame.
    bool SetKeyFrame(float time, const Variant& value);

    /// Return cycle mode.
    CycleMode GetCycleMode() const { return cycleMode_; }
    /// Return value type.
    VariantType GetValueType() const { return valueType_; }
    /// Return begin time.
    float GetBeginTime() const { return beginTime_; }
    /// Return end time.
    float GetEndTime() const { return endTime_; }
    /// Get animation value.
    void GetAnimationValue(float time, Variant& value) const;

protected:
    /// Key frame
    struct KeyFrame
    {
        /// Time.
        float time_;
        /// Value.
        Variant value_;
    };

    /// Calculate scaled time.
    float CalculateScaledTime(float animationTime) const;
    /// Interpolation.
    void Interpolation(const KeyFrame& loKeyFrame, const KeyFrame& hiKeyFrame, float scaledTime, Variant& value) const;

    /// Cycle mode.
    CycleMode cycleMode_;
    /// Value type.
    VariantType valueType_;
    /// Begin time.
    float beginTime_;
    /// End time.
    float endTime_;
    /// Key frames.
    Vector<KeyFrame> keyframes_;
};

}
