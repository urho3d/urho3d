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
#include "AttributeAnimation.h"
#include "AttributeAnimationInstance.h"
#include "Context.h"
#include "Log.h"
#include "ObjectAnimation.h"
#include "ResourceCache.h"
#include "XMLElement.h"

#include "DebugNew.h"

namespace Urho3D
{

extern const char* wrapModeNames[];

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
    attributeAnimationInstances_.Clear();

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
        SharedPtr<AttributeAnimation> attributeAnimation(new AttributeAnimation(context_));
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

    for (HashMap<String, SharedPtr<AttributeAnimationInstance> >::ConstIterator i = attributeAnimationInstances_.Begin(); i != attributeAnimationInstances_.End(); ++i)
    {
        AttributeAnimation* attributeAnimation = i->second_->GetAttributeAnimation();
        if (attributeAnimation->GetObjectAnimation())
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

void Animatable::SetAttributeAnimation(const String& name, AttributeAnimation* attributeAnimation, WrapMode wrapMode, float speed)
{
    AttributeAnimationInstance* currentInstance = GetAttributeAnimationInstance(name);

    if (attributeAnimation)
    {
        if (currentInstance && attributeAnimation == currentInstance->GetAttributeAnimation())
        {
            currentInstance->SetWrapMode(wrapMode);
            currentInstance->SetSpeed(speed);
            return;
        }

        // Get attribute info
        const AttributeInfo* attributeInfo = 0;
        if (currentInstance)
            attributeInfo = &currentInstance->GetAttributeInfo();
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
        if (attributeAnimation->GetValueType() != attributeInfo->type_)
        {
            LOGERROR("Invalid value type");
            return;
        }

        // Add network attribute to set
        if (attributeInfo->mode_ & AM_NET)
            animatedNetworkAttributes_.Insert(attributeInfo);

        attributeAnimationInstances_[name] = new AttributeAnimationInstance(this, *attributeInfo, attributeAnimation, wrapMode, speed);

        if (!currentInstance)
            OnAttributeAnimationAdded();
    }
    else
    {
        if (!currentInstance)
            return;

        // Remove network attribute from set
        if (currentInstance->GetAttributeInfo().mode_ & AM_NET)
            animatedNetworkAttributes_.Erase(&currentInstance->GetAttributeInfo());

        attributeAnimationInstances_.Erase(name);
        OnAttributeAnimationRemoved();
    }
}

void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode)
{
    AttributeAnimationInstance* currentInstance = GetAttributeAnimationInstance(name);
    if (currentInstance)
        currentInstance->SetWrapMode(wrapMode);
}

void Animatable::SetAttributeAnimationSpeed(const String& name, float speed)
{
    AttributeAnimationInstance* currentInstance = GetAttributeAnimationInstance(name);
    if (currentInstance)
        currentInstance->SetSpeed(speed);
}

ObjectAnimation* Animatable::GetObjectAnimation() const
{
    return objectAnimation_;
}

AttributeAnimation* Animatable::GetAttributeAnimation(const String& name) const
{
    const AttributeAnimationInstance* instance = GetAttributeAnimationInstance(name);
    return instance ? instance->GetAttributeAnimation() : 0;
}

WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const
{
    const AttributeAnimationInstance* instance = GetAttributeAnimationInstance(name);
    return instance ? instance->GetWrapMode() : WM_LOOP;
}

float Animatable::GetAttributeAnimationSpeed(const String& name) const
{
    const AttributeAnimationInstance* instance = GetAttributeAnimationInstance(name);
    return instance ? instance->GetSpeed() : 1.0f;
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
    const HashMap<String, SharedPtr<AttributeAnimationInfo> >& attributeAnimationInfos = objectAnimation->GetAttributeAnimationInfos();
    for (HashMap<String, SharedPtr<AttributeAnimationInfo> >::ConstIterator i = attributeAnimationInfos.Begin(); i != attributeAnimationInfos.End(); ++i)
    {
        const String& name = i->first_;
        AttributeAnimationInfo* info = i->second_;
        SetAttributeAnimation(name, info->GetAttributeAnimation(), info->GetWrapMode(), info->GetSpeed());
    }
}

void Animatable::OnObjectAnimationRemoved(ObjectAnimation* objectAnimation)
{
    if (!objectAnimation)
        return;

    // Just remove all attribute animations from the object animation
    Vector<String> names;
    for (HashMap<String, SharedPtr<AttributeAnimationInstance> >::Iterator i = attributeAnimationInstances_.Begin(); i != attributeAnimationInstances_.End(); ++i)
    {
        if (i->second_->GetAttributeAnimation()->GetObjectAnimation() == objectAnimation)
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
    for (HashMap<String, SharedPtr<AttributeAnimationInstance> >::ConstIterator i = attributeAnimationInstances_.Begin(); i != attributeAnimationInstances_.End(); ++i)
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

AttributeAnimationInstance* Animatable::GetAttributeAnimationInstance(const String& name) const
{
    HashMap<String, SharedPtr<AttributeAnimationInstance> >::ConstIterator i = attributeAnimationInstances_.Find(name);
    if (i != attributeAnimationInstances_.End())
        return i->second_;

    return 0;
}

}
