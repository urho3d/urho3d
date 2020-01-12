//
// Copyright (c) 2008-2020 the Urho3D project.
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

/// \file

#pragma once

#include "../Core/Variant.h"
#include "../Resource/Resource.h"

namespace Urho3D
{

class XMLElement;
class JSONValue;

/// Interpolation method.
enum InterpMethod
{
    /// No interpolation.
    IM_NONE = 0,
    /// Linear interpolation (default).
    IM_LINEAR,
    /// Cardinal spline interpolation, default tension value is 0.5f. For more information please refer to http://cubic.org/docs/hermite.htm.
    IM_SPLINE,
};

/// Value animation key frame.
struct VAnimKeyFrame
{
    /// Time.
    float time_;
    /// Value.
    Variant value_;
};

/// Value animation event frame.
struct VAnimEventFrame
{
    /// Time.
    float time_;
    /// Event type.
    StringHash eventType_;
    /// Event data.
    VariantMap eventData_;
};

/// Value animation class.
class URHO3D_API ValueAnimation : public Resource
{
    URHO3D_OBJECT(ValueAnimation, Resource);

public:
    /// Construct.
    explicit ValueAnimation(Context* context);
    /// Destruct.
    ~ValueAnimation() override;
    /// Register object factory.
    static void RegisterObject(Context* context);

    /// Load resource from stream. May be called from a worker thread. Return true if successful.
    bool BeginLoad(Deserializer& source) override;
    /// Save resource. Return true if successful.
    bool Save(Serializer& dest) const override;
    /// Load from XML data. Return true if successful.
    bool LoadXML(const XMLElement& source);
    /// Save as XML data. Return true if successful.
    bool SaveXML(XMLElement& dest) const;
    /// Load from JSON data. Return true if successful.
    bool LoadJSON(const JSONValue& source);
    /// Save as XML data. Return true if successful.
    bool SaveJSON(JSONValue& dest) const;

    /// Set owner.
    void SetOwner(void* owner);
    /// Set interpolation method.
    void SetInterpolationMethod(InterpMethod method);
    /// Set spline tension, should be between 0.0f and 1.0f, but this is not a must.
    void SetSplineTension(float tension);
    /// Set value type.
    void SetValueType(VariantType valueType);

    /// Set key frame.
    bool SetKeyFrame(float time, const Variant& value);
    /// Set event frame.
    void SetEventFrame(float time, const StringHash& eventType, const VariantMap& eventData = VariantMap());

    /// Return animation is valid.
    bool IsValid() const;

    /// Return owner.
    void* GetOwner() const { return owner_; }

    /// Return interpolation method.
    InterpMethod GetInterpolationMethod() const { return interpolationMethod_; }

    /// Return spline tension.
    float GetSplineTension() const { return splineTension_; }

    /// Return value type.
    VariantType GetValueType() const { return valueType_; }

    /// Return begin time.
    float GetBeginTime() const { return beginTime_; }

    /// Return end time.
    float GetEndTime() const { return endTime_; }

    /// Return animation value.
    Variant GetAnimationValue(float scaledTime) const;

    /// Return all key frames.
    const Vector<VAnimKeyFrame>& GetKeyFrames() const { return keyFrames_; }

    /// Has event frames.
    bool HasEventFrames() const { return !eventFrames_.Empty(); }

    /// Return all event frames between time.
    void GetEventFrames(float beginTime, float endTime, PODVector<const VAnimEventFrame*>& eventFrames) const;

protected:
    /// Linear interpolation.
    Variant LinearInterpolation(unsigned index1, unsigned index2, float scaledTime) const;
    /// Spline interpolation.
    Variant SplineInterpolation(unsigned index1, unsigned index2, float scaledTime) const;
    /// Update spline tangents.
    void UpdateSplineTangents() const;
    /// Return (value1 - value2) * t.
    Variant SubstractAndMultiply(const Variant& value1, const Variant& value2, float t) const;

    /// Owner.
    void* owner_;
    /// Interpolation method.
    InterpMethod interpolationMethod_;
    /// Spline tension.
    float splineTension_;
    /// Value type.
    VariantType valueType_;
    /// Interpolatable flag.
    bool interpolatable_;
    /// Begin time.
    float beginTime_;
    /// End time.
    float endTime_;
    /// Key frames.
    Vector<VAnimKeyFrame> keyFrames_;
    /// Spline tangents.
    mutable VariantVector splineTangents_;
    /// Spline tangents dirty.
    mutable bool splineTangentsDirty_;
    /// Event frames.
    Vector<VAnimEventFrame> eventFrames_;
};

}
