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
#include "Log.h"

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

void Animatable::SetAnimationEnabled(bool animationEnabled)
{
    animationEnabled_ = animationEnabled;
}

void Animatable::SetAttributeAnimation(const String& name, AttributeAnimation* animation)
{
    unsigned index = M_MAX_UNSIGNED;
    for (unsigned i = 0; i < attributeAnimationInfos_.Size(); ++i)
    {
        AttributeAnimationInfo& attributeAnimationInfo = attributeAnimationInfos_[i];
        if (!attributeAnimationInfo.info_->name_.Compare(name, true))
        {
            index = i;
            break;
        }
    }

    if (animation)
    {
        if (index == M_MAX_UNSIGNED)
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
                    if (animation->GetValueType() == attributeInfo->type_)
                    {
                        AttributeAnimationInfo atrAnimInfo(attributeInfo, animation);
                        attributeAnimationInfos_.Push(atrAnimInfo);

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
            // Replace old animation and reset time
            attributeAnimationInfos_[index].animation_ = animation;
            attributeAnimationInfos_[index].time_ = 0.0f;
        }
    }
    else
    {
        if (index != M_MAX_UNSIGNED)
        {
            attributeAnimationInfos_.Erase(index);

            OnAttributeAnimationRemoved();
        }
    }
}

AttributeAnimation* Animatable::GetAttributeAnimation(const String& name) const
{
    for (unsigned i = 0; i < attributeAnimationInfos_.Size(); ++i)
    {
        const AttributeAnimationInfo& attributeAnimationInfo = attributeAnimationInfos_[i];
        if (!attributeAnimationInfo.info_->name_.Compare(name, true))
        {
            return attributeAnimationInfo.animation_;
        }
    }

    return 0;
}

void Animatable::UpdateAttributeAnimations(float timeStep)
{
    if (!animationEnabled_)
        return;

    for (unsigned i = 0; i < attributeAnimationInfos_.Size(); ++i)
    {
        AttributeAnimationInfo& attributeAnimationInfo = attributeAnimationInfos_[i];

        attributeAnimationInfo.time_ += timeStep;
        attributeAnimationInfo.animation_->GetAnimationValue(attributeAnimationInfo.time_, attributeAnimationInfo.value_);
        OnSetAttribute(*attributeAnimationInfo.info_, attributeAnimationInfo.value_);
    }        
}

}
