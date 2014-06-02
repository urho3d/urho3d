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
#include "AnimatedSprite2D.h"
#include "Animation2D.h"
#include "AnimationSet2D.h"
#include "Context.h"
#include "ResourceCache.h"
#include "Scene.h"
#include "SceneEvents.h"
#include "Sprite2D.h"
#include "StaticSprite2D.h"

#include "DebugNew.h"

namespace Urho3D
{

extern const char* URHO2D_CATEGORY;
extern const char* blendModeNames[];

AnimatedSprite2D::AnimatedSprite2D(Context* context) :
    Drawable(context, DRAWABLE_GEOMETRY),
    layer_(0),
    orderInLayer_(0),
    blendMode_(BLEND_ALPHA),
    speed_(1.0f),
    currentTime_(0.0f)
{
}

AnimatedSprite2D::~AnimatedSprite2D()
{
}

void AnimatedSprite2D::RegisterObject(Context* context)
{
    context->RegisterFactory<AnimatedSprite2D>(URHO2D_CATEGORY);
    ACCESSOR_ATTRIBUTE(AnimatedSprite2D, VAR_INT, "Layer", GetLayer, SetLayer, int, 0, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(AnimatedSprite2D, VAR_INT, "Order in Layer", GetOrderInLayer, SetOrderInLayer, int, 0, AM_DEFAULT);
    ENUM_ACCESSOR_ATTRIBUTE(AnimatedSprite2D, "Blend Mode", GetBlendMode, SetBlendMode, BlendMode, blendModeNames, BLEND_ALPHA, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(AnimatedSprite2D, VAR_FLOAT, "Speed", GetSpeed, SetSpeed, float, 1.0f, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(AnimatedSprite2D, VAR_RESOURCEREF, "Animation Set", GetAnimationSetAttr, SetAnimationSetAttr, ResourceRef, ResourceRef(AnimatedSprite2D::GetTypeStatic()), AM_DEFAULT);
    REF_ACCESSOR_ATTRIBUTE(AnimatedSprite2D, VAR_STRING, "Animation", GetAnimation, SetAnimation, String, String::EMPTY, AM_DEFAULT);
    COPY_BASE_ATTRIBUTES(Drawable2D, Drawable);
}

void AnimatedSprite2D::OnSetEnabled()
{
    Drawable::OnSetEnabled();

    Scene* scene = GetScene();
    if (scene)
    {
        if (IsEnabledEffective())
            SubscribeToEvent(scene, E_SCENEPOSTUPDATE, HANDLER(AnimatedSprite2D, HandleScenePostUpdate));
        else
            UnsubscribeFromEvent(scene, E_SCENEPOSTUPDATE);
    }
}

void AnimatedSprite2D::SetLayer(int layer)
{
    if (layer == layer_)
        return;

    layer_ = layer;

    for (unsigned i = 0; i < timelineNodes_.Size(); ++i)
    {
        StaticSprite2D* objectSprite = timelineNodes_[i]->GetComponent<StaticSprite2D>();
        objectSprite->SetLayer(layer_);
    }
}

void AnimatedSprite2D::SetOrderInLayer(int orderInLayer)
{
    orderInLayer_ = orderInLayer;
}

void AnimatedSprite2D::SetBlendMode(BlendMode blendMode)
{
    if (blendMode == blendMode_)
        return;

    blendMode_ = blendMode;

    for (unsigned i = 0; i < timelineNodes_.Size(); ++i)
    {
        StaticSprite2D* objectSprite = timelineNodes_[i]->GetComponent<StaticSprite2D>();
        objectSprite->SetBlendMode(blendMode_);
    }
}

void AnimatedSprite2D::SetSpeed(float speed)
{
    speed_ = speed;
    MarkNetworkUpdate();
}

void AnimatedSprite2D::SetAnimation(AnimationSet2D* animationSet, const String& name)
{
    animationSet_ = animationSet;
    animationName_ = name;
    
    if (animationSet)
        SetAnimation(animationSet->GetAnimation(name));
    else
        SetAnimation(0);
}

void AnimatedSprite2D::SetAnimationSet(AnimationSet2D* animationSet)
{
    if (animationSet == animationSet_)
        return;

    animationSet_ = animationSet;

    if (animationSet_)
        SetAnimation(animationSet_->GetAnimation(animationName_));
    else
        SetAnimation(0);

}
void AnimatedSprite2D::SetAnimation(const String& name)
{
    animationName_ = name;

    if (animationSet_)
        SetAnimation(animationSet_->GetAnimation(animationName_));
}

AnimationSet2D* AnimatedSprite2D::GetAnimationSet() const
{
    return animationSet_;
}


void AnimatedSprite2D::SetAnimationSetAttr(ResourceRef value)
{
    ResourceCache* cache = GetSubsystem<ResourceCache>();
    SetAnimationSet(cache->GetResource<AnimationSet2D>(value.name_));
}

Urho3D::ResourceRef AnimatedSprite2D::GetAnimationSetAttr() const
{
    return GetResourceRef(animationSet_, AnimationSet2D::GetTypeStatic());
}

void AnimatedSprite2D::OnNodeSet(Node* node)
{
    Drawable::OnNodeSet(node);

    if (node)
    {
        Scene* scene = GetScene();
        if (scene && IsEnabledEffective())
            SubscribeToEvent(scene, E_SCENEPOSTUPDATE, HANDLER(AnimatedSprite2D, HandleScenePostUpdate));
    }
}

void AnimatedSprite2D::OnWorldBoundingBoxUpdate()
{
    boundingBox_.Clear();
    worldBoundingBox_.Clear();

    for (unsigned i = 0; i < timelineNodes_.Size(); ++i)
    {
        StaticSprite2D* staticSprite = timelineNodes_[i]->GetComponent<StaticSprite2D>();
        if (staticSprite)
            worldBoundingBox_.Merge(staticSprite->GetWorldBoundingBox());
    }

    boundingBox_ = worldBoundingBox_.Transformed(node_->GetWorldTransform().Inverse());
}

void AnimatedSprite2D::SetAnimation(Animation2D* animation)
{
    if (animation == animation_)
    {
        // Reset time
        currentTime_ = 0.0f;
        return;
    }

    if (animation_)
    {
        for (unsigned i = 0; i < timelineNodes_.Size(); ++i)
            timelineNodes_[i]->Remove();
        timelineNodes_.Clear();
    }

    animation_ = animation;

    if (!animation_)
        return;

    currentTime_ = 0.0f;

    timelineNodes_.Resize(animation_->GetNumTimelines());
    for (unsigned i = 0; i < animation_->GetNumTimelines(); ++i)
        CreateTimelineNode(i);

    UpdateAnimation(0.0f);

    MarkNetworkUpdate();
}

Node* AnimatedSprite2D::CreateTimelineNode(unsigned index)
{
    if (timelineNodes_[index])
        return timelineNodes_[index];

    const Timeline2D& timeline = animation_->GetTimeline(index);
    Node* parentNode = 0;    
    if (timeline.parent_ == -1)
        parentNode = GetNode();
    else
        parentNode = CreateTimelineNode(timeline.parent_);

    SharedPtr<Node> objectNode(parentNode->CreateChild(timeline.name_));
    timelineNodes_[index] = objectNode;

    if (timeline.type_ == OT_SPRITE)
    {
        StaticSprite2D* staticSprite = objectNode->CreateComponent<StaticSprite2D>();
        staticSprite->SetLayer(layer_);
        staticSprite->SetBlendMode(blendMode_);
        staticSprite->SetUseHotSpot(true);
    }

    return objectNode;
}


void AnimatedSprite2D::UpdateAnimation(float timeStep)
{
    if (!animation_)
        return;
    
    currentTime_ += timeStep * speed_;

    float animtationLength = animation_->GetLength();
    float time;

    if (animation_->IsLooped())
    {
        time = fmodf(currentTime_, animtationLength);
        if (time < 0.0f)
            time += animation_->GetLength();
    }
    else
        time = Clamp(currentTime_, 0.0f, animtationLength);

    const Vector<MainlineKey2D>& mainlineKeys = animation_->GetMainlineKeys();
    const MainlineKey2D* mainlineKey = 0;
    for (unsigned i = 1; i < mainlineKeys.Size(); ++i)
    {
        if (time < mainlineKeys[i].time_)
        {
            mainlineKey = &mainlineKeys[i - 1];
            break;
        }
    }

    if (!mainlineKey)
        mainlineKey = &mainlineKeys.Back();

    for (unsigned i = 0; i < animation_->GetNumTimelines(); ++i)
    {
        Node* objectNode = timelineNodes_[i];

        const Reference2D* objectRef = mainlineKey->GetReference(i);
        if (!objectRef)
            objectNode->SetEnabled(false);
        else
        {
            objectNode->SetEnabled(true);

            const Timeline2D& timeline = animation_->GetTimeline(i);
            const Vector<TimelineKey2D>& objectKeys = timeline.timelineKeys_;
            for (unsigned j = 0; j < objectKeys.Size() - 1; ++j)
            {
                if (time <= objectKeys[j + 1].time_)
                {
                    const TimelineKey2D& currKey = objectKeys[j];
                    const TimelineKey2D& nextKey = objectKeys[j + 1];

                    float t = (time - currKey.time_)  / (nextKey.time_ - currKey.time_);
                    if (t < 0.0f || t > 1.0f)
                    {
                        t = 0;
                    }

                    objectNode->SetPosition(currKey.position_.Lerp(nextKey.position_, t));

                    float angle;
                    if (currKey.spin_ > 0 && currKey.angle_ > nextKey.angle_)
                        angle = Lerp(currKey.angle_, nextKey.angle_ + 360.0f, t);
                    else if (currKey.spin_ < 0 && currKey.angle_ < nextKey.angle_)
                        angle = Lerp(currKey.angle_, nextKey.angle_ - 360.0f, t);
                    else
                        angle = Lerp(currKey.angle_, nextKey.angle_, t);
                    objectNode->SetRotation(angle);

                    objectNode->SetScale(currKey.scale_.Lerp(nextKey.scale_, t));

                    if (timeline.type_ == OT_SPRITE)
                    {
                        StaticSprite2D* staticSprite = objectNode->GetComponent<StaticSprite2D>();
                        staticSprite->SetOrderInLayer(orderInLayer_ + objectRef->zIndex_);
                        staticSprite->SetSprite(currKey.sprite_);
                        staticSprite->SetHotSpot(currKey.hotSpot_.Lerp(nextKey.hotSpot_, t));
                        float alpha_ = Lerp(currKey.alpha_, nextKey.alpha_, t);
                        staticSprite->SetColor(Color(1.0f, 1.0f, 1.0f, alpha_));
                    }

                    break;
                }
            }
        }       
    }

    MarkForUpdate();
}

void AnimatedSprite2D::HandleScenePostUpdate(StringHash eventType, VariantMap& eventData)
{
    using namespace ScenePostUpdate;
    float timeStep = eventData[P_TIMESTEP].GetFloat();
    UpdateAnimation(timeStep);
}

}

