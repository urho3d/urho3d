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
#include "Log.h"
#include "Scene.h"
#include "SceneEvents.h"
#include "SceneObject.h"

#include "DebugNew.h"

namespace Urho3D
{

SceneObject::SceneObject(Context* context) :
    Serializable(context),
    animationTime_(0.0f)
{
}

SceneObject::~SceneObject()
{
}

void SceneObject::SetAttributeAnimation(const String& name, AttributeAnimation* animation)
{
    if (!animation)
    {
        for (HashMap<const AttributeInfo*, SharedPtr<AttributeAnimation> >::Iterator i = attributeAnimations_.Begin(); i != attributeAnimations_.End(); ++i)
        {
            if (i->first_->name_.Contains(name, true))
            {
                attributeAnimations_.Erase(i);
                break;
            }
        }

        if (attributeAnimations_.Empty())
            UnsubscribeFromEvent(GetScene(), E_SCENEPOSTUPDATE);
    }
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
            const AttributeInfo* attributeInfo = &(*i);
            if (!attributeInfo->name_.Compare(name, true))
            {
                // Check that the new value's type matches the attribute type
                if (animation->GetValueType() == attributeInfo->type_)
                {
                    if (attributeAnimations_.Empty())
                    {
                        // Reset anmation time
                        animationTime_ = 0.0f;

                        SubscribeToEvent(GetScene(), E_SCENEPOSTUPDATE, HANDLER(SceneObject, HandleScenePostUpdate));
                    }

                    attributeAnimations_[attributeInfo] = SharedPtr<AttributeAnimation>(animation);
                    return;
                }
            }
        }

        LOGERROR("Could not find attribute " + name + " in " + GetTypeName());
    }
}

AttributeAnimation* SceneObject::GetAttributeAnimation(const String& name) const
{
    for (HashMap<const AttributeInfo*, SharedPtr<AttributeAnimation> >::ConstIterator i = attributeAnimations_.Begin(); i != attributeAnimations_.End(); ++i)
    {
        if (i->first_->name_.Contains(name, true))
            return i->second_;
    }

    return 0;
}

void SceneObject::UpdateAttributeAnimations(float timeStep)
{
    animationTime_ += timeStep;

    for (HashMap<const AttributeInfo*, SharedPtr<AttributeAnimation> >::Iterator i = attributeAnimations_.Begin(); i != attributeAnimations_.End(); ++i)
    {
        Variant animationValue;
        i->second_->GetValue(animationTime_, animationValue);

        OnSetAttribute(*i->first_, animationValue);
    }
}

void SceneObject::HandleScenePostUpdate(StringHash eventType, VariantMap& eventData)
{
    using namespace ScenePostUpdate;
    
    UpdateAttributeAnimations(eventData[P_TIMESTEP].GetFloat());
}

}
