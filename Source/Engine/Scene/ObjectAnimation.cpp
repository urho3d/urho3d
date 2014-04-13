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
#include "AttributeAnimationInfo.h"
#include "Context.h"
#include "ObjectAnimation.h"
#include "XMLFile.h"

#include "DebugNew.h"

namespace Urho3D
{

const char* wrapModeNames[] =
{
    "Loop",
    "Once",
    "Clamp",
    0
};

ObjectAnimation::ObjectAnimation(Context* context) :
    Resource(context)
{
}

ObjectAnimation::~ObjectAnimation()
{
}

void ObjectAnimation::RegisterObject(Context* context)
{
    context->RegisterFactory<ObjectAnimation>();
}

bool ObjectAnimation::Load(Deserializer& source)
{
    XMLFile xmlFile(context_);
    if (!xmlFile.Load(source))
        return false;

    return LoadXML(xmlFile.GetRoot());
}

bool ObjectAnimation::Save(Serializer& dest) const
{
    XMLFile xmlFile(context_);

    XMLElement rootElem = xmlFile.CreateRoot("objectanimation");
    if (!SaveXML(rootElem))
        return false;

    return xmlFile.Save(dest);
}

bool ObjectAnimation::LoadXML(const XMLElement& source)
{
    attributeAnimationInfos_.Clear();

    XMLElement animElem;
    animElem = source.GetChild("attributeanimation");
    while (animElem)
    {
        String name = animElem.GetAttribute("name");
        
        SharedPtr<AttributeAnimation> animation(new AttributeAnimation(context_));
        if (!animation->LoadXML(animElem))
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

        float speed = animElem.GetFloat("speed");
        AddAttributeAnimation(name, animation, wrapMode, speed);

        animElem = animElem.GetNext("attributeanimation");
    }

    return true;
}

bool ObjectAnimation::SaveXML(XMLElement& dest) const
{
    for (HashMap<String, SharedPtr<AttributeAnimationInfo> >::ConstIterator i = attributeAnimationInfos_.Begin(); i != attributeAnimationInfos_.End(); ++i)
    {
        XMLElement animElem = dest.CreateChild("attributeanimation");
        animElem.SetAttribute("name", i->first_);

        const AttributeAnimationInfo* info = i->second_;
        if (!info->GetAttributeAnimation()->SaveXML(animElem))
            return false;

        animElem.SetAttribute("wrapmode", wrapModeNames[info->GetWrapMode()]);
        animElem.SetFloat("speed", info->GetSpeed());
    }

    return true;
}

void ObjectAnimation::AddAttributeAnimation(const String& name, AttributeAnimation* attributeAnimation, WrapMode wrapMode, float speed)
{
    if (!attributeAnimation)
        return;

    attributeAnimation->SetObjectAnimation(this);
    attributeAnimationInfos_[name] = new AttributeAnimationInfo(attributeAnimation, wrapMode, speed);
}

void ObjectAnimation::RemoveAttributeAnimation(const String& name)
{
    HashMap<String, SharedPtr<AttributeAnimationInfo> >::Iterator i = attributeAnimationInfos_.Find(name);
    if (i != attributeAnimationInfos_.End())
    {
        i->second_->GetAttributeAnimation()->SetObjectAnimation(0);
        attributeAnimationInfos_.Erase(i);
    }
}

void ObjectAnimation::RemoveAttributeAnimation(AttributeAnimation* attributeAnimation)
{
    if (!attributeAnimation)
        return;

    for (HashMap<String, SharedPtr<AttributeAnimationInfo> >::Iterator i = attributeAnimationInfos_.Begin(); i != attributeAnimationInfos_.End(); ++i)
    {
        if (i->second_->GetAttributeAnimation() == attributeAnimation)
        {
            attributeAnimation->SetObjectAnimation(0);
            attributeAnimationInfos_.Erase(i);
            return;
        }
    }
}

AttributeAnimation* ObjectAnimation::GetAttributeAnimation(const String& name) const
{
    AttributeAnimationInfo* info = GetAttributeAnimationInfo(name);
    return info ? info->GetAttributeAnimation() : 0;
}

WrapMode ObjectAnimation::GetAttributeAnimationWrapMode(const String& name) const
{
    AttributeAnimationInfo* info = GetAttributeAnimationInfo(name);
    return info ? info->GetWrapMode() : WM_LOOP;
}

float ObjectAnimation::GetAttributeAnimationSpeed(const String& name) const
{
    AttributeAnimationInfo* info = GetAttributeAnimationInfo(name);
    return info ? info->GetSpeed() : 1.0f;
}

AttributeAnimationInfo* ObjectAnimation::GetAttributeAnimationInfo(const String& name) const
{
    HashMap<String, SharedPtr<AttributeAnimationInfo> >::ConstIterator i = attributeAnimationInfos_.Find(name);
    if (i != attributeAnimationInfos_.End())
        return i->second_;
    return 0;
}

}
