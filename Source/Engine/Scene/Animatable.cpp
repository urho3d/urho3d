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
#include "Context.h"
#include "Log.h"
#include "ObjectAnimation.h"
#include "ResourceCache.h"
#include "ValueAnimation.h"
#include "XMLElement.h"

#include "DebugNew.h"

namespace Urho3D
{

extern const char* wrapModeNames[];

AttributeAnimationInfo::AttributeAnimationInfo(Animatable* animatable, const AttributeInfo& attributeInfo, ValueAnimation* attributeAnimation, WrapMode wrapMode, float speed) :
    ValueAnimationInfo(attributeAnimation, wrapMode, speed),
    animatable_(animatable),
    attributeInfo_(attributeInfo),
    currentTime_(0.0f),
    lastScaledTime_(0.0f)
{
}

AttributeAnimationInfo::AttributeAnimationInfo(const AttributeAnimationInfo& other) :
    ValueAnimationInfo(other),
    animatable_(other.animatable_),
    attributeInfo_(other.attributeInfo_),
    currentTime_(0.0f),
    lastScaledTime_(0.0f)
{
}

AttributeAnimationInfo::~AttributeAnimationInfo()
{
}

bool AttributeAnimationInfo::Update(float timeStep)
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

Animatable::Animatable(Context* context) :
    Serializable(context),
    animationEnabled_(true)
{
}

Animatable::~Animatable()
{
}

void Animatable::RegisterObject(Context* context)
{
    ACCESSOR_ATTRIBUTE(Animatable, VAR_RESOURCEREF, "Object Animation", GetObjectAnimationAttr, SetObjectAnimationAttr, ResourceRef, ResourceRef(ObjectAnimation::GetTypeStatic()), AM_DEFAULT);
}

bool Animatable::LoadXML(const XMLElement& source, bool setInstanceDefault)
{
    if (!Serializable::LoadXML(source, setInstanceDefault))
        return false;

    SetObjectAnimation(0);
    attributeAnimationInfos_.Clear();

    XMLElement elem = source.GetChild("objectanimation");
    if (elem)
    {
        SharedPtr<ObjectAnimation> objectAnimation(new ObjectAnimation(context_));
        if (!objectAnimation->LoadXML(elem))
            return false;

        SetObjectAnimation(objectAnimation);
    }

    elem = source.GetChild("attributeanimation");
    while (elem)
    {
        String name = elem.GetAttribute("name");
        SharedPtr<ValueAnimation> attributeAnimation(new ValueAnimation(context_));
        if (!attributeAnimation->LoadXML(elem))
            return false;

        String wrapModeString = source.GetAttribute("wrapmode");
        WrapMode wrapMode = WM_LOOP;
        for (int i = 0; i <= WM_CLAMP; ++i)
        {
            if (wrapModeString == wrapModeNames[i])
            {
                wrapMode = (WrapMode)i;
                break;
            }
        }

        float speed = elem.GetFloat("speed");
        SetAttributeAnimation(name, attributeAnimation, wrapMode, speed);

        elem = elem.GetNext("attributeanimation");
    }

    return true;
}

bool Animatable::SaveXML(XMLElement& dest) const
{
    if (!Serializable::SaveXML(dest))
        return false;

    // Object animation without name
    if (objectAnimation_ && objectAnimation_->GetName().Empty())
    {
        XMLElement elem = dest.CreateChild("objectanimation");
        if (!objectAnimation_->SaveXML(elem))
            return false;
    }

    for (HashMap<String, SharedPtr<AttributeAnimationInfo> >::ConstIterator i = attributeAnimationInfos_.Begin(); i != attributeAnimationInfos_.End(); ++i)
    {
        ValueAnimation* attributeAnimation = i->second_->GetAnimation();
        if (attributeAnimation->GetOwner())
            continue;

        const AttributeInfo& attr = i->second_->GetAttributeInfo();
        XMLElement elem = dest.CreateChild("attributeanimation");
        elem.SetAttribute("name", attr.name_);
        if (!attributeAnimation->SaveXML(elem))
            return false;

        elem.SetAttribute("wrapmode", wrapModeNames[i->second_->GetWrapMode()]);
        elem.SetFloat("speed", i->second_->GetSpeed());
    }

    return true;
}

void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation)
{
    if (objectAnimation == objectAnimation_)
        return;

    if (objectAnimation_)
        OnObjectAnimationRemoved(objectAnimation_);

    objectAnimation_ = objectAnimation;

    if (objectAnimation_)
        OnObjectAnimationAdded(objectAnimation_);
}

void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode, float speed)
{
    AttributeAnimationInfo* info = GetAttributeAnimationInfo(name);

    if (attributeAnimation)
    {
        if (info && attributeAnimation == info->GetAnimation())
        {
            info->SetWrapMode(wrapMode);
            info->SetSpeed(speed);
            return;
        }

        // Use shared ptr to avoid memory leak
        SharedPtr<ValueAnimation> animationPtr(attributeAnimation);

        // Get attribute info
        const AttributeInfo* attributeInfo = 0;
        if (info)
            attributeInfo = &info->GetAttributeInfo();
        else
        {
            const Vector<AttributeInfo>* attributes = GetAttributes();
            if (!attributes)
            {
                LOGERROR(GetTypeName() + " has no attributes");
                return;
            }

            for (Vector<AttributeInfo>::ConstIterator i = attributes->Begin(); i != attributes->End(); ++i)
            {
                if (name == (*i).name_)
                {
                    attributeInfo = &(*i);
                    break;
                }
            }
        }

        if (!attributeInfo)
        {
            LOGERROR("Invalid name: " + name);
            return;
        }

        // Check value type is same with attribute type
        if (animationPtr->GetValueType() != attributeInfo->type_)
        {
            LOGERROR("Invalid value type");
            return;
        }

        // Add network attribute to set
        if (attributeInfo->mode_ & AM_NET)
            animatedNetworkAttributes_.Insert(attributeInfo);

        attributeAnimationInfos_[name] = new AttributeAnimationInfo(this, *attributeInfo, animationPtr, wrapMode, speed);

        if (!info)
            OnAttributeAnimationAdded();
    }
    else
    {
        if (!info)
            return;

        // Remove network attribute from set
        if (info->GetAttributeInfo().mode_ & AM_NET)
            animatedNetworkAttributes_.Erase(&info->GetAttributeInfo());

        attributeAnimationInfos_.Erase(name);
        OnAttributeAnimationRemoved();
    }
}

void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode)
{
    AttributeAnimationInfo* info = GetAttributeAnimationInfo(name);
    if (info)
        info->SetWrapMode(wrapMode);
}

void Animatable::SetAttributeAnimationSpeed(const String& name, float speed)
{
    AttributeAnimationInfo* info = GetAttributeAnimationInfo(name);
    if (info)
        info->SetSpeed(speed);
}

ObjectAnimation* Animatable::GetObjectAnimation() const
{
    return objectAnimation_;
}

ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const
{
    const AttributeAnimationInfo* info = GetAttributeAnimationInfo(name);
    return info ? info->GetAnimation() : 0;
}

WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const
{
    const AttributeAnimationInfo* info = GetAttributeAnimationInfo(name);
    return info ? info->GetWrapMode() : WM_LOOP;
}

float Animatable::GetAttributeAnimationSpeed(const String& name) const
{
    const AttributeAnimationInfo* info = GetAttributeAnimationInfo(name);
    return info ? info->GetSpeed() : 1.0f;
}

void Animatable::SetObjectAnimationAttr(ResourceRef value)
{
    if (!value.name_.Empty())
    {
        ResourceCache* cache = GetSubsystem<ResourceCache>();
        SetObjectAnimation(cache->GetResource<ObjectAnimation>(value.name_));
    }
}

ResourceRef Animatable::GetObjectAnimationAttr() const
{
    return GetResourceRef(objectAnimation_, ObjectAnimation::GetTypeStatic());
}

void Animatable::OnObjectAnimationAdded(ObjectAnimation* objectAnimation)
{
    if (!objectAnimation)
        return;

    // Set all attribute animations from the object animation
    const HashMap<String, SharedPtr<ValueAnimationInfo> >& attributeAnimationInfos = objectAnimation->GetAttributeAnimationInfos();
    for (HashMap<String, SharedPtr<ValueAnimationInfo> >::ConstIterator i = attributeAnimationInfos.Begin(); i != attributeAnimationInfos.End(); ++i)
    {
        const String& name = i->first_;
        ValueAnimationInfo* info = i->second_;
        SetAttributeAnimation(name, info->GetAnimation(), info->GetWrapMode(), info->GetSpeed());
    }
}

void Animatable::OnObjectAnimationRemoved(ObjectAnimation* objectAnimation)
{
    if (!objectAnimation)
        return;

    // Just remove all attribute animations from the object animation
    Vector<String> names;
    for (HashMap<String, SharedPtr<AttributeAnimationInfo> >::Iterator i = attributeAnimationInfos_.Begin(); i != attributeAnimationInfos_.End(); ++i)
    {
        if (i->second_->GetAnimation()->GetOwner() == objectAnimation)
            names.Push(i->first_);
    }

    for (unsigned int i = 0; i < names.Size(); ++i)
        SetAttributeAnimation(names[i], 0);
}

void Animatable::UpdateAttributeAnimations(float timeStep)
{
    if (!animationEnabled_)
        return;

    Vector<String> finishedNames;
    for (HashMap<String, SharedPtr<AttributeAnimationInfo> >::ConstIterator i = attributeAnimationInfos_.Begin(); i != attributeAnimationInfos_.End(); ++i)
    {
        if (i->second_->Update(timeStep))
            finishedNames.Push(i->second_->GetAttributeInfo().name_);
    }

    for (unsigned i = 0; i < finishedNames.Size(); ++i)
        SetAttributeAnimation(finishedNames[i], 0);
}

bool Animatable::IsAnimatedNetworkAttribute(const AttributeInfo& attrInfo) const
{
    return animatedNetworkAttributes_.Find(&attrInfo) != animatedNetworkAttributes_.End();
}

AttributeAnimationInfo* Animatable::GetAttributeAnimationInfo(const String& name) const
{
    HashMap<String, SharedPtr<AttributeAnimationInfo> >::ConstIterator i = attributeAnimationInfos_.Find(name);
    if (i != attributeAnimationInfos_.End())
        return i->second_;

    return 0;
}

}
