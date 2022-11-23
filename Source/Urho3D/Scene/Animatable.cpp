// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#include "../Precompiled.h"

#include "../Core/Context.h"
#include "../IO/Log.h"
#include "../Resource/ResourceCache.h"
#include "../Resource/JSONValue.h"
#include "../Resource/XMLElement.h"
#include "../Scene/Animatable.h"
#include "../Scene/ObjectAnimation.h"
#include "../Scene/SceneEvents.h"
#include "../Scene/ValueAnimation.h"

#include "../DebugNew.h"

namespace Urho3D
{

extern const char* wrapModeNames[];

AttributeAnimationInfo::AttributeAnimationInfo(Animatable* animatable, const AttributeInfo& attributeInfo,
    ValueAnimation* attributeAnimation, WrapMode wrapMode, float speed) :
    ValueAnimationInfo(animatable, attributeAnimation, wrapMode, speed),
    attributeInfo_(attributeInfo)
{
}

AttributeAnimationInfo::AttributeAnimationInfo(const AttributeAnimationInfo& other) = default;

AttributeAnimationInfo::~AttributeAnimationInfo() = default;

void AttributeAnimationInfo::ApplyValue(const Variant& newValue)
{
    auto* animatable = static_cast<Animatable*>(target_.Get());
    if (animatable)
    {
        animatable->OnSetAttribute(attributeInfo_, newValue);
        animatable->ApplyAttributes();
    }
}

Animatable::Animatable(Context* context) :
    Serializable(context),
    animationEnabled_(true)
{
}

Animatable::~Animatable() = default;

void Animatable::RegisterObject(Context* context)
{
    URHO3D_MIXED_ACCESSOR_ATTRIBUTE("Object Animation", GetObjectAnimationAttr, SetObjectAnimationAttr, ResourceRef,
        ResourceRef(ObjectAnimation::GetTypeStatic()), AM_DEFAULT);
}

bool Animatable::LoadXML(const XMLElement& source)
{
    if (!Serializable::LoadXML(source))
        return false;

    SetObjectAnimation(nullptr);
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

bool Animatable::LoadJSON(const JSONValue& source)
{
    if (!Serializable::LoadJSON(source))
        return false;

    SetObjectAnimation(nullptr);
    attributeAnimationInfos_.Clear();

    JSONValue value = source.Get("objectanimation");
    if (!value.IsNull())
    {
        SharedPtr<ObjectAnimation> objectAnimation(new ObjectAnimation(context_));
        if (!objectAnimation->LoadJSON(value))
            return false;

        SetObjectAnimation(objectAnimation);
    }

    JSONValue attributeAnimationValue = source.Get("attributeanimation");

    if (attributeAnimationValue.IsNull())
        return true;

    if (!attributeAnimationValue.IsObject())
    {
        URHO3D_LOGWARNING("'attributeanimation' value is present in JSON data, but is not a JSON object; skipping it");
        return true;
    }

    const JSONObject& attributeAnimationObject = attributeAnimationValue.GetObject();
    for (JSONObject::ConstIterator it = attributeAnimationObject.Begin(); it != attributeAnimationObject.End(); it++)
    {
        String name = it->first_;
        JSONValue value = it->second_;
        SharedPtr<ValueAnimation> attributeAnimation(new ValueAnimation(context_));
        if (!attributeAnimation->LoadJSON(it->second_))
            return false;

        String wrapModeString = value.Get("wrapmode").GetString();
        WrapMode wrapMode = WM_LOOP;
        for (int i = 0; i <= WM_CLAMP; ++i)
        {
            if (wrapModeString == wrapModeNames[i])
            {
                wrapMode = (WrapMode)i;
                break;
            }
        }

        float speed = value.Get("speed").GetFloat();
        SetAttributeAnimation(name, attributeAnimation, wrapMode, speed);
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


    for (HashMap<String, SharedPtr<AttributeAnimationInfo>>::ConstIterator i = attributeAnimationInfos_.Begin();
         i != attributeAnimationInfos_.End(); ++i)
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

bool Animatable::SaveJSON(JSONValue& dest) const
{
    if (!Serializable::SaveJSON(dest))
        return false;

    // Object animation without name
    if (objectAnimation_ && objectAnimation_->GetName().Empty())
    {
        JSONValue objectAnimationValue;
        if (!objectAnimation_->SaveJSON(objectAnimationValue))
            return false;
        dest.Set("objectanimation", objectAnimationValue);
    }

    JSONValue attributeAnimationValue;

    for (HashMap<String, SharedPtr<AttributeAnimationInfo>>::ConstIterator i = attributeAnimationInfos_.Begin();
         i != attributeAnimationInfos_.End(); ++i)
    {
        ValueAnimation* attributeAnimation = i->second_->GetAnimation();
        if (attributeAnimation->GetOwner())
            continue;

        const AttributeInfo& attr = i->second_->GetAttributeInfo();
        JSONValue attributeValue;
        attributeValue.Set("name", attr.name_);
        if (!attributeAnimation->SaveJSON(attributeValue))
            return false;

        attributeValue.Set("wrapmode", wrapModeNames[i->second_->GetWrapMode()]);
        attributeValue.Set("speed", (float) i->second_->GetSpeed());

        attributeAnimationValue.Set(attr.name_, attributeValue);
    }

    if (!attributeAnimationValue.IsNull())
        dest.Set("attributeanimation", attributeAnimationValue);

    return true;
}

void Animatable::SetAnimationEnabled(bool enable)
{
    if (objectAnimation_)
    {
        // In object animation there may be targets in hierarchy. Set same enable/disable state in all
        HashSet<Animatable*> targets;
        const HashMap<String, SharedPtr<ValueAnimationInfo>>& infos = objectAnimation_->GetAttributeAnimationInfos();
        for (HashMap<String, SharedPtr<ValueAnimationInfo>>::ConstIterator i = infos.Begin(); i != infos.End(); ++i)
        {
            String outName;
            Animatable* target = FindAttributeAnimationTarget(i->first_, outName);
            if (target && target != this)
                targets.Insert(target);
        }

        for (HashSet<Animatable*>::Iterator i = targets.Begin(); i != targets.End(); ++i)
            (*i)->animationEnabled_ = enable;
    }

    animationEnabled_ = enable;
}

void Animatable::SetAnimationTime(float time)
{
    if (objectAnimation_)
    {
        // In object animation there may be targets in hierarchy. Set same time in all
        const HashMap<String, SharedPtr<ValueAnimationInfo>>& infos = objectAnimation_->GetAttributeAnimationInfos();
        for (HashMap<String, SharedPtr<ValueAnimationInfo>>::ConstIterator i = infos.Begin(); i != infos.End(); ++i)
        {
            String outName;
            Animatable* target = FindAttributeAnimationTarget(i->first_, outName);
            if (target)
                target->SetAttributeAnimationTime(outName, time);
        }
    }
    else
    {
        for (HashMap<String, SharedPtr<AttributeAnimationInfo>>::ConstIterator i = attributeAnimationInfos_.Begin();
            i != attributeAnimationInfos_.End(); ++i)
            i->second_->SetTime(time);
    }
}

void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation)
{
    if (objectAnimation == objectAnimation_)
        return;

    if (objectAnimation_)
    {
        OnObjectAnimationRemoved(objectAnimation_);
        UnsubscribeFromEvent(objectAnimation_, E_ATTRIBUTEANIMATIONADDED);
        UnsubscribeFromEvent(objectAnimation_, E_ATTRIBUTEANIMATIONREMOVED);
    }

    objectAnimation_ = objectAnimation;

    if (objectAnimation_)
    {
        OnObjectAnimationAdded(objectAnimation_);
        SubscribeToEvent(objectAnimation_, E_ATTRIBUTEANIMATIONADDED, URHO3D_HANDLER(Animatable, HandleAttributeAnimationAdded));
        SubscribeToEvent(objectAnimation_, E_ATTRIBUTEANIMATIONREMOVED, URHO3D_HANDLER(Animatable, HandleAttributeAnimationRemoved));
    }
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

        // Get attribute info
        const AttributeInfo* attributeInfo = nullptr;
        if (info)
            attributeInfo = &info->GetAttributeInfo();
        else
        {
            const Vector<AttributeInfo>* attributes = GetAttributes();
            if (!attributes)
            {
                URHO3D_LOGERROR(GetTypeName() + " has no attributes");
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
            URHO3D_LOGERROR("Invalid name: " + name);
            return;
        }

        // Check value type is same with attribute type
        if (attributeAnimation->GetValueType() != attributeInfo->type_)
        {
            URHO3D_LOGERROR("Invalid value type");
            return;
        }

        // Add network attribute to set
        if (attributeInfo->mode_ & AM_NET)
            animatedNetworkAttributes_.Insert(attributeInfo);

        attributeAnimationInfos_[name] = new AttributeAnimationInfo(this, *attributeInfo, attributeAnimation, wrapMode, speed);

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

void Animatable::SetAttributeAnimationTime(const String& name, float time)
{
    AttributeAnimationInfo* info = GetAttributeAnimationInfo(name);
    if (info)
        info->SetTime(time);
}

void Animatable::RemoveObjectAnimation()
{
    SetObjectAnimation(nullptr);
}

void Animatable::RemoveAttributeAnimation(const String& name)
{
    SetAttributeAnimation(name, nullptr);
}

ObjectAnimation* Animatable::GetObjectAnimation() const
{
    return objectAnimation_;
}

ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const
{
    const AttributeAnimationInfo* info = GetAttributeAnimationInfo(name);
    return info ? info->GetAnimation() : nullptr;
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

float Animatable::GetAttributeAnimationTime(const String& name) const
{
    const AttributeAnimationInfo* info = GetAttributeAnimationInfo(name);
    return info ? info->GetTime() : 0.0f;
}

void Animatable::SetObjectAnimationAttr(const ResourceRef& value)
{
    if (!value.name_.Empty())
    {
        auto* cache = GetSubsystem<ResourceCache>();
        SetObjectAnimation(cache->GetResource<ObjectAnimation>(value.name_));
    }
}

ResourceRef Animatable::GetObjectAnimationAttr() const
{
    return GetResourceRef(objectAnimation_, ObjectAnimation::GetTypeStatic());
}

Animatable* Animatable::FindAttributeAnimationTarget(const String& name, String& outName)
{
    // Base implementation only handles self
    outName = name;
    return this;
}

void Animatable::SetObjectAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode, float speed)
{
    String outName;
    Animatable* target = FindAttributeAnimationTarget(name, outName);
    if (target)
        target->SetAttributeAnimation(outName, attributeAnimation, wrapMode, speed);
}

void Animatable::OnObjectAnimationAdded(ObjectAnimation* objectAnimation)
{
    if (!objectAnimation)
        return;

    // Set all attribute animations from the object animation
    const HashMap<String, SharedPtr<ValueAnimationInfo>>& attributeAnimationInfos = objectAnimation->GetAttributeAnimationInfos();
    for (HashMap<String, SharedPtr<ValueAnimationInfo>>::ConstIterator i = attributeAnimationInfos.Begin();
         i != attributeAnimationInfos.End(); ++i)
    {
        const String& name = i->first_;
        ValueAnimationInfo* info = i->second_;
        SetObjectAttributeAnimation(name, info->GetAnimation(), info->GetWrapMode(), info->GetSpeed());
    }
}

void Animatable::OnObjectAnimationRemoved(ObjectAnimation* objectAnimation)
{
    if (!objectAnimation)
        return;

    // Just remove all attribute animations listed by the object animation
    const HashMap<String, SharedPtr<ValueAnimationInfo>>& infos = objectAnimation->GetAttributeAnimationInfos();
    for (HashMap<String, SharedPtr<ValueAnimationInfo>>::ConstIterator i = infos.Begin(); i != infos.End(); ++i)
        SetObjectAttributeAnimation(i->first_, nullptr, WM_LOOP, 1.0f);
}

void Animatable::UpdateAttributeAnimations(float timeStep)
{
    if (!animationEnabled_)
        return;

    // Keep weak pointer to self to check for destruction caused by event handling
    WeakPtr<Animatable> self(this);

    Vector<String> finishedNames;
    for (HashMap<String, SharedPtr<AttributeAnimationInfo>>::ConstIterator i = attributeAnimationInfos_.Begin();
         i != attributeAnimationInfos_.End(); ++i)
    {
        bool finished = i->second_->Update(timeStep);
        // If self deleted as a result of an event sent during animation playback, nothing more to do
        if (self.Expired())
            return;

        if (finished)
            finishedNames.Push(i->second_->GetAttributeInfo().name_);
    }

    for (const String& finishedName : finishedNames)
        SetAttributeAnimation(finishedName, nullptr);
}

bool Animatable::IsAnimatedNetworkAttribute(const AttributeInfo& attrInfo) const
{
    return animatedNetworkAttributes_.Find(&attrInfo) != animatedNetworkAttributes_.End();
}

AttributeAnimationInfo* Animatable::GetAttributeAnimationInfo(const String& name) const
{
    HashMap<String, SharedPtr<AttributeAnimationInfo>>::ConstIterator i = attributeAnimationInfos_.Find(name);
    if (i != attributeAnimationInfos_.End())
        return i->second_;

    return nullptr;
}

void Animatable::HandleAttributeAnimationAdded(StringHash eventType, VariantMap& eventData)
{
    if (!objectAnimation_)
        return;

    using namespace AttributeAnimationAdded;
    const String& name = eventData[P_ATTRIBUTEANIMATIONNAME].GetString();

    ValueAnimationInfo* info = objectAnimation_->GetAttributeAnimationInfo(name);
    if (!info)
        return;

    SetObjectAttributeAnimation(name, info->GetAnimation(), info->GetWrapMode(), info->GetSpeed());
}

void Animatable::HandleAttributeAnimationRemoved(StringHash eventType, VariantMap& eventData)
{
    if (!objectAnimation_)
        return;

    using namespace AttributeAnimationRemoved;
    const String& name = eventData[P_ATTRIBUTEANIMATIONNAME].GetString();

    SetObjectAttributeAnimation(name, nullptr, WM_LOOP, 1.0f);
}

}
