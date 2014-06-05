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
#include "Drawable2D.h"
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
    flipX_(false),
    flipY_(false),
    color_(Color::WHITE),
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
    ACCESSOR_ATTRIBUTE(AnimatedSprite2D, VAR_BOOL, "Flip X", GetFlipX, SetFlipX, bool, false, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(AnimatedSprite2D, VAR_BOOL, "Flip Y", GetFlipY, SetFlipY, bool, false, AM_DEFAULT);
    REF_ACCESSOR_ATTRIBUTE(AnimatedSprite2D, VAR_COLOR, "Color", GetColor, SetColor, Color, Color::WHITE, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(AnimatedSprite2D, VAR_FLOAT, "Speed", GetSpeed, SetSpeed, float, 1.0f, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(AnimatedSprite2D, VAR_RESOURCEREF, "Animation Set", GetAnimationSetAttr, SetAnimationSetAttr, ResourceRef, ResourceRef(AnimatedSprite2D::GetTypeStatic()), AM_DEFAULT);
    REF_ACCESSOR_ATTRIBUTE(AnimatedSprite2D, VAR_STRING, "Animation", GetAnimation, SetAnimation, String, String::EMPTY, AM_DEFAULT);
    COPY_BASE_ATTRIBUTES(AnimatedSprite2D, Drawable);
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
        if (!timelineNodes_[i])
            continue;

        StaticSprite2D* staticSprite = timelineNodes_[i]->GetComponent<StaticSprite2D>();
        staticSprite->SetLayer(layer_);
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
        if (!timelineNodes_[i])
            continue;

        StaticSprite2D* staticSprite = timelineNodes_[i]->GetComponent<StaticSprite2D>();
        staticSprite->SetBlendMode(blendMode_);
    }
}

void AnimatedSprite2D::SetFlip(bool flipX, bool flipY)
{
    if (flipX == flipX_ && flipY == flipY_)
        return;

    flipX_ = flipX;
    flipY_ = flipY;
    
    for (unsigned i = 0; i < timelineNodes_.Size(); ++i)
    {
        if (!timelineNodes_[i])
            continue;

        StaticSprite2D* staticSprite = timelineNodes_[i]->GetComponent<StaticSprite2D>();
        staticSprite->SetFlip(flipX_, flipY_);
    }

    // For editor paused mode
    UpdateAnimation(0.0f);

    MarkNetworkUpdate();
}

void AnimatedSprite2D::SetFlipX(bool flipX)
{
    SetFlip(flipX, flipY_);
}

void AnimatedSprite2D::SetFlipY(bool flipY)
{
    SetFlip(flipX_, flipY);
}

void AnimatedSprite2D::SetColor(const Color& color)
{
    color_ = color;
    MarkNetworkUpdate();
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

Node* AnimatedSprite2D::GetRootNode() const
{
    return rootNode_;
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
    else
    {
        if (rootNode_)
            rootNode_->Remove();
        
        rootNode_ = 0;
        timelineNodes_.Clear();
    }
}

void AnimatedSprite2D::OnWorldBoundingBoxUpdate()
{
    boundingBox_.Clear();
    worldBoundingBox_.Clear();

    for (unsigned i = 0; i < timelineNodes_.Size(); ++i)
    {
        if (!timelineNodes_[i])
            continue;

        StaticSprite2D* staticSprite = timelineNodes_[i]->GetComponent<StaticSprite2D>();
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
        {
            if (timelineNodes_[i])
                timelineNodes_[i]->Remove();
        }

        timelineNodes_.Clear();
    }

    animation_ = animation;

    if (!animation_)
        return;

    currentTime_ = 0.0f;

    if (!rootNode_)
        rootNode_ = GetNode()->CreateChild("RootNode", LOCAL);

    timelineNodes_.Resize(animation_->GetNumTimelines());
    timelineTransformInfos_.Resize(animation_->GetNumTimelines());

    for (unsigned i = 0; i < animation_->GetNumTimelines(); ++i)
    {
        const Timeline2D& timeline = animation->GetTimeline(i);
        // Just create sprite type node
        if (timeline.type_ == OT_SPRITE)
        {
            SharedPtr<Node> timelineNode(rootNode_->CreateChild(timeline.name_, LOCAL));
            
            StaticSprite2D* staticSprite = timelineNode->CreateComponent<StaticSprite2D>();
            staticSprite->SetLayer(layer_);
            staticSprite->SetBlendMode(blendMode_);
            staticSprite->SetFlip(flipX_, flipY_);
            staticSprite->SetUseHotSpot(true);

            timelineNodes_[i] = timelineNode;
        }

        timelineTransformInfos_[i].parent_ = timeline.parent_;
    }

    UpdateAnimation(0.0f);

    MarkNetworkUpdate();
}

void AnimatedSprite2D::UpdateAnimation(float timeStep)
{
    if (!animation_)
        return;
    
    currentTime_ += timeStep * speed_;

    float time;
    float animtationLength = animation_->GetLength();

    if (animation_->IsLooped())
    {
        time = fmodf(currentTime_, animtationLength);
        if (time < 0.0f)
            time += animation_->GetLength();
    }
    else
        time = Clamp(currentTime_, 0.0f, animtationLength);

    // Update timeline's local transform
    for (unsigned i = 0; i < timelineTransformInfos_.Size(); ++i)
    {
        const Timeline2D& timeline = animation_->GetTimeline(i);
        
        const Vector<TimelineKey2D>& objectKeys = timeline.timelineKeys_;
        for (unsigned j = 0; j < objectKeys.Size() - 1; ++j)
        {
            if (time <= objectKeys[j + 1].time_)
            {
                const TimelineKey2D& currKey = objectKeys[j];
                const TimelineKey2D& nextKey = objectKeys[j + 1];
                float t = (time - currKey.time_)  / (nextKey.time_ - currKey.time_);

                timelineTransformInfos_[i].worldSpace_ = false;
                timelineTransformInfos_[i].transform_ = currKey.transform_.Lerp(nextKey.transform_, t, currKey.spin_);

                // Update sprite's sprite and hot spot and color
                Node* timelineNode = timelineNodes_[i];
                if (timelineNode)
                {
                    StaticSprite2D* staticSprite = timelineNode->GetComponent<StaticSprite2D>();
                    staticSprite->SetSprite(currKey.sprite_);
                    staticSprite->SetHotSpot(currKey.hotSpot_.Lerp(nextKey.hotSpot_, t));
                    float alpha = Lerp(currKey.alpha_, nextKey.alpha_, t);
                    staticSprite->SetColor(Color(color_.r_, color_.g_, color_.b_, color_.a_ * alpha));
                }

                break;
            }
        }
    }

    // Calculate timeline world transform.
    for (unsigned i = 0; i < timelineTransformInfos_.Size(); ++i)
        CalculateTimelineWorldTransform(i);

    // Get mainline key
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

    // Update node's transform and sprite's z order
    for (unsigned i = 0; i < timelineNodes_.Size(); ++i)
    {
        Node* timelineNode = timelineNodes_[i];
        if (!timelineNode)
            continue;

        const Reference2D* ref = mainlineKey->GetReference(i);
        if (!ref)
        {
            // Disable node
            if (timelineNode->IsEnabled())
                timelineNode->SetEnabled(false);
        }
        else
        {
            // Enable node
            if (!timelineNode->IsEnabled())
                timelineNode->SetEnabled(true);

            // Update node's transform
            const Transform2D& transform = timelineTransformInfos_[i].transform_;
            Vector2 position = transform.position_ * PIXEL_SIZE;
            if (flipX_)
                position.x_ = -position.x_;
            if (flipY_)
                position.y_ = -position.y_;
            timelineNode->SetPosition(position);

            float angle = transform.angle_;
            if (flipX_ != flipY_)
                angle = -angle;
            timelineNode->SetRotation(angle);

            timelineNode->SetScale(transform.scale_);

            // Update sprite's z order
            StaticSprite2D* staticSprite = timelineNode->GetComponent<StaticSprite2D>();
            staticSprite->SetOrderInLayer(orderInLayer_ + ref->zIndex_);
        }
    }

    MarkForUpdate();
}

void AnimatedSprite2D::CalculateTimelineWorldTransform(unsigned index)
{
    TransformInfo& info = timelineTransformInfos_[index];
    if (info.worldSpace_)
        return;

    info.worldSpace_ = true;

    if (info.parent_ != -1)
    {
        CalculateTimelineWorldTransform(info.parent_);
        info.transform_ = timelineTransformInfos_[info.parent_].transform_ * info.transform_;
    }
}

void AnimatedSprite2D::HandleScenePostUpdate(StringHash eventType, VariantMap& eventData)
{
    using namespace ScenePostUpdate;
    float timeStep = eventData[P_TIMESTEP].GetFloat();
    UpdateAnimation(timeStep);
}

}
