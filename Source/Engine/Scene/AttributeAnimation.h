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

#include "Resource.h"
#include "Variant.h"

namespace Urho3D
{

class ObjectAnimation;
class XMLElement;

/// Attribute key frame
struct AttributeKeyFrame
{
    /// Time.
    float time_;
    /// Value.
    Variant value_;
};

/// Attribute event frame.
struct AttributeEventFrame
{
    /// Time.
    float time_;
    /// Event type.
    StringHash eventType_;
    /// Event data.
    VariantMap eventData_;
};

/// Base class for attribute animation.
class URHO3D_API AttributeAnimation : public Resource
{
    OBJECT(AttributeAnimation);

public:
    /// Construct.
    AttributeAnimation(Context* context);
    /// Destruct.
    virtual ~AttributeAnimation();
    /// Register object factory.
    static void RegisterObject(Context* context);

    /// Load resource. Return true if successful.
    virtual bool Load(Deserializer& source);
    /// Save resource. Return true if successful.
    virtual bool Save(Serializer& dest) const;
    /// Load from XML data. Return true if successful.
    bool LoadXML(const XMLElement& source);
    /// Save as XML data. Return true if successful.
    bool SaveXML(XMLElement& dest) const;

    /// Set object animation.
    void SetObjectAnimation(ObjectAnimation* objectAnimation);
    /// Set value type.
    void SetValueType(VariantType valueType);
    /// Set key frame.
    bool SetKeyFrame(float time, const Variant& value);
    /// Set event frame.
    void SetEventFrame(float time, const StringHash& eventType, const VariantMap& eventData = VariantMap());

    /// Return object animation.
    ObjectAnimation* GetObjectAnimation() const;
    /// Return value type.
    VariantType GetValueType() const { return valueType_; }
    /// Is interpolatable.
    bool IsInterpolatable() const { return isInterpolatable_; }
    /// Return begin time.
    float GetBeginTime() const { return beginTime_; }
    /// Return end time.
    float GetEndTime() const { return endTime_; }
    /// Return all key frames.
    const Vector<AttributeKeyFrame>& GetKeyFrames() const { return keyFrames_; }
    /// Has event frames.
    bool HasEventFrames() const { return eventFrames_.Size() != 0; }
    /// Return all event frames between time.
    void GetEventFrames(float beginTime, float endTime, Vector<const AttributeEventFrame*>& eventFrames) const;

protected:
    /// Object animation.
    WeakPtr<ObjectAnimation> objectAnimation_;
    /// Value type.
    VariantType valueType_;
    /// Is interpolatable.
    bool isInterpolatable_;
    /// Begin time.
    float beginTime_;
    /// End time.
    float endTime_;
    /// Key frames.
    Vector<AttributeKeyFrame> keyFrames_;
    /// Event frames.
    Vector<AttributeEventFrame> eventFrames_;
};

}
