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

#include "DebugNew.h"

namespace Urho3D
{

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

void Animatable::SetAnimationEnabled(bool animationEnabled)
{
    animationEnabled_ = animationEnabled;
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

void Animatable::SetAttributeAnimation(const String& name, AttributeAnimation* attributeAnimation)
{
    const AttributeAnimation* currentAnimation = GetAttributeAnimation(name);
    if (currentAnimation == attributeAnimation)
        return;

    if (attributeAnimation)
    {
        const Vector<AttributeInfo>* attributes = GetAttributes();
        if (!attributes)
        {
            LOGERROR(GetTypeName() + " has no attributes");
            return;
        }

        for (Vector<AttributeInfo>::ConstIterator i = attributes->Begin(); i != attributes->End(); ++i)
        {
            const AttributeInfo& attributeInfo = *i;
            if (!attributeInfo.name_.Compare(name, true))
            {
                if (attributeAnimation->GetValueType() == attributeInfo.type_)
                {
                    SharedPtr<AttributeAnimationInstance> attributeAnimationInstance(new AttributeAnimationInstance(this, attributeInfo, attributeAnimation));
                    attributeAnimationInstances_[name] = attributeAnimationInstance;

                    if (!currentAnimation)
                        OnAttributeAnimationAdded();
                }
                else
                {
                    LOGERROR("Error value type");
                    return;
                }

            }
        }
    }
    else
    {
        if (currentAnimation)
        {
            attributeAnimationInstances_.Erase(name);
            OnAttributeAnimationRemoved();
        }
    }
}

const ObjectAnimation* Animatable::GetObjectAnimation() const
{
    return objectAnimation_;
}

const AttributeAnimation* Animatable::GetAttributeAnimation(const String& name) const
{
    HashMap<String, SharedPtr<AttributeAnimationInstance> >::ConstIterator i = attributeAnimationInstances_.Find(name);
    if (i != attributeAnimationInstances_.End())
        return i->second_->GetAttributeAnimation();
    return 0;
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
    if (objectAnimation_ && !objectAnimation_->GetParentAnimation())
        return GetResourceRef(objectAnimation_, ObjectAnimation::GetTypeStatic());
    return ResourceRef();
}

void Animatable::OnObjectAnimationAdded(ObjectAnimation* objectAnimation)
{
    if (!objectAnimation)
        return;

    // Set all attribute animations from the object animation
    HashMap<String, SharedPtr<AttributeAnimation> > attributeAnimations = objectAnimation->GetAttributeAnimations();
    for (HashMap<String, SharedPtr<AttributeAnimation> >::Iterator i = attributeAnimations.Begin(); i != attributeAnimations.End(); ++i)
        SetAttributeAnimation(i->first_, i->second_);
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
    
    for (HashMap<String, SharedPtr<AttributeAnimationInstance> >::ConstIterator i = attributeAnimationInstances_.Begin(); i != attributeAnimationInstances_.End(); ++i)
        i->second_->Update(timeStep);
}

}
