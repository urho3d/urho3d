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
#include "XMLFile.h"

#include "DebugNew.h"

namespace Urho3D
{

AttributeAnimation::AttributeAnimation(Context* context) :
    Resource(context),
    cycleMode_(CM_LOOP),
    valueType_(VAR_NONE),
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

bool AttributeAnimation::Load(Deserializer& source)
{
    XMLFile xmlFile(context_);
    if (xmlFile.Load(source))
        return false;

    XMLElement rootElem = xmlFile.GetRoot("AttributeAnimation");
    if (!rootElem)
        return false;

    return LoadXML(rootElem);
}

bool AttributeAnimation::Save(Serializer& dest) const
{
    XMLFile xmlFile(context_);

    XMLElement rootElem = xmlFile.CreateRoot("AttributeAnimation");
    if (!SaveXML(rootElem))
        return false;

    return xmlFile.Save(dest);
}

bool AttributeAnimation::LoadXML(const XMLElement& source)
{
    if (source.GetName() != "AttributeAnimation")
        return false;
    
    keyframes_.Clear();

    cycleMode_ = (CycleMode)source.GetInt("cycle mode");
    valueType_ = (VariantType)source.GetInt("value type");

    XMLElement keyFrameEleme = source.GetChild("KeyFrame");
    while (keyFrameEleme)
    {
        float time = keyFrameEleme.GetFloat("time");
        Variant value(valueType_, keyFrameEleme.GetAttribute("value"));
        SetKeyFrame(time, value);

        keyFrameEleme = keyFrameEleme.GetNext("KeyFrame");
    }

    return true;
}

bool AttributeAnimation::SaveXML(XMLElement& dest) const
{
    if (dest.GetName() != "AttributeAnimation")
        return false;

    dest.SetInt("cycle mode", (int)cycleMode_);
    dest.SetInt("value type", (int)valueType_);

    for (unsigned i = 0; i < keyframes_.Size(); ++i)
    {
        const KeyFrame& keyFrame = keyframes_[i];
        XMLElement keyFrameEleme = dest.CreateChild("KeyFrame");
        keyFrameEleme.SetFloat("time", keyFrame.time_);
        keyFrameEleme.SetAttribute("value", keyFrame.value_.ToString());
    }
    
    return true;
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
    
    keyframes_.Clear();
    beginTime_ = M_INFINITY;
    endTime_ = -M_INFINITY;
}

bool AttributeAnimation::SetKeyFrame(float time, const Variant& value)
{
    if (valueType_ == VAR_NONE)
        valueType_ = value.GetType();
    else if (value.GetType() != valueType_)
        return false;

    beginTime_ = Min(time, beginTime_);
    endTime_ = Max(time, endTime_);

    KeyFrame keyFrame;
    keyFrame.time_ = time;
    keyFrame.value_ = value;

    if (keyframes_.Empty() || time >= keyframes_.Back().time_)
        keyframes_.Push(keyFrame);
    else
    {
        for (unsigned i = 0; i < keyframes_.Size(); ++i)
        {
            if (time < keyframes_[i].time_)
            {
                keyframes_.Insert(i, keyFrame);
                break;
            }
        }
    }

    return true;
}

void AttributeAnimation::GetAnimationValue(float time, Variant& value) const
{
    if (keyframes_.Empty())
        return;

    float scaledTime = CalculateScaledTime(time);

    for (unsigned i = 1; i < keyframes_.Size(); ++i)
    {
        if (keyframes_[i].time_ > scaledTime)
        {
            Interpolation(keyframes_[i - 1], keyframes_[i], scaledTime, value);
            break;
        }
    }
}

float AttributeAnimation::CalculateScaledTime(float time) const
{
    switch (cycleMode_)
    {
    case CM_LOOP:
        {
            float span = endTime_ - beginTime_;
            return beginTime_ + fmodf(time - beginTime_, span);
        }

    case CM_CLAMP:
        return Clamp(time, beginTime_, endTime_);

    case CM_PINGPONG:
        {
            float span = endTime_ - beginTime_;
            float doubleSpan = span * 2.0f;
            float fract = fmodf(time - beginTime_, doubleSpan);
            return (fract < span) ? beginTime_ + fract : beginTime_ + doubleSpan - fract;
        }
        break;
    }

    return time;
}

void AttributeAnimation::Interpolation(const KeyFrame& loKeyFrame, const KeyFrame& hiKeyFrame, float scaledTime, Variant& value) const
{
    switch (valueType_)
    {
    case VAR_INT:
        value = loKeyFrame.value_.GetInt();
        return;
    case VAR_BOOL:
        value = loKeyFrame.value_.GetBool();
        return;
    case VAR_FLOAT:
        {
            float factor = (scaledTime - loKeyFrame.time_) / (hiKeyFrame.time_ - loKeyFrame.time_);
            value = Lerp(loKeyFrame.value_.GetFloat(), hiKeyFrame.value_.GetFloat(), factor);
        }
        return;
    case VAR_VECTOR2:
        {
            float factor = (scaledTime - loKeyFrame.time_) / (hiKeyFrame.time_ - loKeyFrame.time_);
            value = loKeyFrame.value_.GetVector2().Lerp(hiKeyFrame.value_.GetVector2(), factor);
        }
        return;
    case VAR_VECTOR3:
        {
            float factor = (scaledTime - loKeyFrame.time_) / (hiKeyFrame.time_ - loKeyFrame.time_);
            value = loKeyFrame.value_.GetVector3().Lerp(hiKeyFrame.value_.GetVector3(), factor);
        }
        return;
    case VAR_VECTOR4:
        {
            float factor = (scaledTime - loKeyFrame.time_) / (hiKeyFrame.time_ - loKeyFrame.time_);
            value = loKeyFrame.value_.GetVector4().Lerp(hiKeyFrame.value_.GetVector4(), factor);
        }
        return;
    case VAR_QUATERNION:
        {
            float factor = (scaledTime - loKeyFrame.time_) / (hiKeyFrame.time_ - loKeyFrame.time_);
            value = loKeyFrame.value_.GetQuaternion().Slerp(hiKeyFrame.value_.GetQuaternion(), factor);
        }
        return;
    case VAR_COLOR:
        {
            float factor = (scaledTime - loKeyFrame.time_) / (hiKeyFrame.time_ - loKeyFrame.time_);
            value = loKeyFrame.value_.GetColor().Lerp(hiKeyFrame.value_.GetColor(), factor);
        }
        return;
    case VAR_STRING:
        value = loKeyFrame.value_.GetString();
        return;
    case VAR_BUFFER:
        value = loKeyFrame.value_.GetBuffer();
        return;
    case VAR_VOIDPTR:
        value = loKeyFrame.value_.GetVoidPtr();
        return;
    case VAR_RESOURCEREF:
        value = loKeyFrame.value_.GetResourceRef();
        return;
    case VAR_RESOURCEREFLIST:
        value = loKeyFrame.value_.GetResourceRefList();
        return;
    case VAR_VARIANTVECTOR:
        value = loKeyFrame.value_.GetVariantVector();
        return;
    case VAR_VARIANTMAP:
        value = loKeyFrame.value_.GetVariantMap();
        return;
    case VAR_INTRECT:
        value = loKeyFrame.value_.GetIntRect();
        return;
    case VAR_INTVECTOR2:
        value = loKeyFrame.value_.GetIntVector2();
        return;
    case VAR_PTR:
        value = loKeyFrame.value_.GetPtr();
        return;
    }
}

}
