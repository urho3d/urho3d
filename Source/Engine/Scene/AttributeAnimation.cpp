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
#include "Context.h"
#include "ObjectAnimation.h"
#include "Deserializer.h"
#include "Serializer.h"
#include "XMLFile.h"

#include "DebugNew.h"

namespace Urho3D
{

const char* cycleModeNames[] = 
{
    "Loop",
    "Clamp",
    "Pingpong",
    0
};

AttributeAnimation::AttributeAnimation(Context* context) :
    Resource(context),
    cycleMode_(CM_LOOP),
    valueType_(VAR_NONE),
    isInterpolatable_(false),
    beginTime_(M_INFINITY),
    endTime_(-M_INFINITY)
{
}

AttributeAnimation::~AttributeAnimation()
{
}

void AttributeAnimation::RegisterObject(Context* context)
{
    context->RegisterFactory<AttributeAnimation>();
}

bool AttributeAnimation::LoadXML(const XMLElement& source)
{
    valueType_ = VAR_NONE;
    eventFrames_.Clear();

    String cycleModeString = source.GetAttribute("cycleMode");
    cycleMode_ = CM_LOOP;
    for (int i = 0; i <= CM_PINGPONG; ++i)
    {
        if (cycleModeString == cycleModeNames[i])
        {
            cycleMode_ = (CycleMode)i;
            break;
        }
    }

    SetValueType(Variant::GetTypeFromName(source.GetAttribute("valueType")));

    XMLElement keyFrameEleme = source.GetChild("keyFrame");
    while (keyFrameEleme)
    {
        float time = keyFrameEleme.GetFloat("time");
        Variant value(valueType_, keyFrameEleme.GetAttribute("value"));
        SetKeyFrame(time, value);

        keyFrameEleme = keyFrameEleme.GetNext("keyFrame");
    }

    XMLElement eventFrameElem = source.GetChild("eventFrame");
    while (eventFrameElem)
    {
        float time = eventFrameElem.GetFloat("time");
        unsigned eventType = eventFrameElem.GetUInt("eventType");
        VariantMap eventData = eventFrameElem.GetChild("eventData").GetVariantMap();
        
        SetEventFrame(time, StringHash(eventType), eventData);
        eventFrameElem = eventFrameElem.GetNext("eventFrame");
    }

    return true;
}

bool AttributeAnimation::SaveXML(XMLElement& dest) const
{
    dest.SetAttribute("cycleMode", cycleModeNames[cycleMode_]);
    dest.SetAttribute("valueType", Variant::GetTypeName(valueType_));

    for (unsigned i = 0; i < keyFrames_.Size(); ++i)
    {
        const AttributeKeyFrame& keyFrame = keyFrames_[i];
        XMLElement keyFrameEleme = dest.CreateChild("keyFrame");
        keyFrameEleme.SetFloat("time", keyFrame.time_);
        keyFrameEleme.SetAttribute("value", keyFrame.value_.ToString());
    }

    for (unsigned i = 0; i < eventFrames_.Size(); ++i)
    {
        const AttributeEventFrame& eventFrame = eventFrames_[i];
        XMLElement eventFrameElem = dest.CreateChild("eventFrame");
        eventFrameElem.SetFloat("time", eventFrame.time_);
        eventFrameElem.SetUInt("eventType", eventFrame.eventType_.Value());
        eventFrameElem.CreateChild("eventData").SetVariantMap(eventFrame.eventData_);
    }

    return true;
}

void AttributeAnimation::SetObjectAnimation(ObjectAnimation* objectAnimation)
{
    objectAnimation_ = objectAnimation;
}

void AttributeAnimation::SetCycleMode(CycleMode cycleMode)
{
    cycleMode_ = cycleMode;
}

void AttributeAnimation::SetValueType(VariantType valueType)
{
    if (valueType == valueType_)
        return;

    valueType_ = valueType;

    isInterpolatable_ = (valueType_ == VAR_FLOAT) || (valueType_ == VAR_VECTOR2) || (valueType_ == VAR_VECTOR3) || 
        (valueType_ == VAR_VECTOR4) || (valueType_ == VAR_QUATERNION) || (valueType_ == VAR_COLOR);

    keyFrames_.Clear();
    beginTime_ = M_INFINITY;
    endTime_ = -M_INFINITY;
}

bool AttributeAnimation::SetKeyFrame(float time, const Variant& value)
{
    if (valueType_ == VAR_NONE)
        SetValueType(value.GetType());
    else if (value.GetType() != valueType_)
        return false;

    beginTime_ = Min(time, beginTime_);
    endTime_ = Max(time, endTime_);

    AttributeKeyFrame keyFrame;
    keyFrame.time_ = time;
    keyFrame.value_ = value;

    if (keyFrames_.Empty() || time >= keyFrames_.Back().time_)
        keyFrames_.Push(keyFrame);
    else
    {
        for (unsigned i = 0; i < keyFrames_.Size(); ++i)
        {
            if (time < keyFrames_[i].time_)
            {
                keyFrames_.Insert(i, keyFrame);
                break;
            }
        }
    }

    return true;
}

void AttributeAnimation::SetEventFrame(float time, const StringHash& eventType, const VariantMap& eventData)
{
    AttributeEventFrame eventFrame;
    eventFrame.time_ = time;
    eventFrame.eventType_ = eventType;
    eventFrame.eventData_ = eventData;

    if (eventFrames_.Empty() || time >= eventFrames_.Back().time_)
        eventFrames_.Push(eventFrame);
    else
    {
        for (unsigned i = 0; i < eventFrames_.Size(); ++i)
        {
            if (time < eventFrames_[i].time_)
            {
                eventFrames_.Insert(i, eventFrame);
                break;
            }
        }
    }
}

ObjectAnimation* AttributeAnimation::GetObjectAnimation() const
{
    return objectAnimation_;
}

float AttributeAnimation::CalculateScaledTime(float currentTime) const
{
    switch (cycleMode_)
    {
    case CM_LOOP:
        {
            float span = endTime_ - beginTime_;
            return beginTime_ + fmodf(currentTime - beginTime_, span);
        }

    case CM_CLAMP:
        return Clamp(currentTime, beginTime_, endTime_);

    case CM_PINGPONG:
        {
            float span = endTime_ - beginTime_;
            float doubleSpan = span * 2.0f;
            float fract = fmodf(currentTime - beginTime_, doubleSpan);
            return (fract < span) ? beginTime_ + fract : beginTime_ + doubleSpan - fract;
        }
        break;
    }

    return beginTime_;
}

void AttributeAnimation::GetEventFrames(float beginTime, float endTime, Vector<const AttributeEventFrame*>& eventFrames) const
{
    for (unsigned i = 0; i < eventFrames_.Size(); ++i)
    {
        const AttributeEventFrame& eventFrame = eventFrames_[i];
        if (eventFrame.time_ >= endTime)
            break;

        if (eventFrame.time_ >= beginTime)
            eventFrames.Push(&eventFrame);
    }
}

}
