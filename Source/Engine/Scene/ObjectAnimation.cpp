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
#include "XMLFile.h"

#include "DebugNew.h"

namespace Urho3D
{

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
    if (xmlFile.Load(source))
        return false;

    XMLElement rootElem = xmlFile.GetRoot("ObjectAnimation");
    if (!rootElem)
        return false;

    return LoadXML(rootElem);
}

bool ObjectAnimation::Save(Serializer& dest) const
{
    XMLFile xmlFile(context_);

    XMLElement rootElem = xmlFile.CreateRoot("ObjectAnimation");
    if (!SaveXML(rootElem))
        return false;

    return xmlFile.Save(dest);
}

bool ObjectAnimation::LoadXML(const XMLElement& source)
{
    if (source.GetName() != "ObjectAnimation")
        return false;
    
    XMLElement animElem;
    animElem = source.GetChild("AttributeAnimation");
    while (animElem)
    {
        String name = animElem.GetAttribute("name");

        SharedPtr<AttributeAnimation> animation(new AttributeAnimation(context_));
        if (!animation->LoadXML(animElem))
            return false;

        AddAttributeAnimation(name, animation);

        animElem = animElem.GetNext("AttributeAnimation");
    }

    animElem = source.GetChild("ObjectAnimation");
    while (animElem)
    {
        String name = animElem.GetAttribute("name");

        SharedPtr<ObjectAnimation> animation(new ObjectAnimation(context_));
        if (!animation->LoadXML(animElem))
            return false;
        
        AddChildAnimation(name, animation);

        animElem = animElem.GetNext("ObjectAnimation");
    }

    return true;
}

bool ObjectAnimation::SaveXML(XMLElement& dest) const
{
    if (dest.GetName() != "ObjectAnimation")
        return false;

    for (HashMap<String, SharedPtr<AttributeAnimation> >::ConstIterator i = attributeAnimations_.Begin(); i != attributeAnimations_.End(); ++i)
    {
        XMLElement animElem = dest.CreateChild("AttributeAnimation");
        animElem.SetAttribute("name", i->first_);

        if (!i->second_->SaveXML(animElem))
            return false;
    }

    for (HashMap<String, SharedPtr<ObjectAnimation> >::ConstIterator i = objectAnimations_.Begin(); i != objectAnimations_.End(); ++i)
    {
        XMLElement animElem = dest.CreateChild("ObjectAnimation");
        animElem.SetAttribute("name", i->first_);

        if (!i->second_->SaveXML(animElem))
            return false;
    }

    return true;
}

void ObjectAnimation::AddChildAnimation(const String& name, ObjectAnimation* objectAnimation)
{
    if (!objectAnimation)
        return;

    objectAnimation->SetParentAnimation(this);
    objectAnimations_[name] = objectAnimation;
}

void ObjectAnimation::RemoveChildAnimation(const String& name)
{
    RemoveChildAnimation(GetObjectAnimation(name));
}

void ObjectAnimation::RemoveChildAnimation(ObjectAnimation* objectAnimation)
{
    if (!objectAnimation)
        return;

    for (HashMap<String, SharedPtr<ObjectAnimation> >::Iterator i = objectAnimations_.Begin(); i != objectAnimations_.End(); ++i)
    {
        if (i->second_ == objectAnimation)
        {
            objectAnimation->SetParentAnimation(0);
            objectAnimations_.Erase(i);
            return;
        }
    }
}

void ObjectAnimation::AddAttributeAnimation(const String& name, AttributeAnimation* attributeAnimation)
{
    if (!attributeAnimation)
        return;

    attributeAnimation->SetObjectAnimation(this);
    attributeAnimations_[name] = attributeAnimation;
}

void ObjectAnimation::RemoveAttributeAnimation(const String& name)
{
    RemoveAttributeAnimation(GetAttributeAnimation(name));
}

void ObjectAnimation::RemoveAttributeAnimation(AttributeAnimation* attributeAnimation)
{
    if (!attributeAnimation)
        return;

    for (HashMap<String, SharedPtr<AttributeAnimation> >::Iterator i = attributeAnimations_.Begin(); i != attributeAnimations_.End(); ++i)
    {
        if (i->second_ == attributeAnimation)
        {
            attributeAnimation->SetObjectAnimation(0);
            attributeAnimations_.Erase(i);
            return;
        }
    }
}

ObjectAnimation* ObjectAnimation::GetObjectAnimation(const String& name) const
{
    HashMap<String, SharedPtr<ObjectAnimation> >::ConstIterator i = objectAnimations_.Find(name);
    if (i != objectAnimations_.End())
        return i->second_;
    return 0;
}

AttributeAnimation* ObjectAnimation::GetAttributeAnimation(const String& name) const
{
    HashMap<String, SharedPtr<AttributeAnimation> >::ConstIterator i = attributeAnimations_.Find(name);
    if (i != objectAnimations_.End())
        return i->second_;
    return 0;
}

}
