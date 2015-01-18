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
#include "../Urho2D/AnimatedSprite2D.h"
#include "../Urho2D/Animation2D.h"
#include "../Urho2D/AnimationSet2D.h"
#include "../Core/Context.h"
#include "../Resource/ResourceCache.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneEvents.h"
#include "../Urho2D/Sprite2D.h"
#include "../Urho2D/StaticSprite2D.h"

#include "../DebugNew.h"

namespace Urho3D
{

extern const char* URHO2D_CATEGORY;
extern const char* blendModeNames[];

const char* loopModeNames[] =
{
    "Default",
    "ForceLooped",
    "ForceClamped",
    0
};

AnimatedSprite2D::AnimatedSprite2D(Context* context) :
    StaticSprite2D(context),
    speed_(1.0f),
    loopMode_(LM_DEFAULT),
    looped_(false),
    currentTime_(0.0f),
    numTracks_(0)
{
}

AnimatedSprite2D::~AnimatedSprite2D()
{
}

void AnimatedSprite2D::RegisterObject(Context* context)
{
    context->RegisterFactory<AnimatedSprite2D>(URHO2D_CATEGORY);

    COPY_BASE_ATTRIBUTES(StaticSprite2D);
    REMOVE_ATTRIBUTE("Sprite");
    ACCESSOR_ATTRIBUTE("Speed", GetSpeed, SetSpeed, float, 1.0f, AM_DEFAULT);
    MIXED_ACCESSOR_ATTRIBUTE("Animation Set", GetAnimationSetAttr, SetAnimationSetAttr, ResourceRef, ResourceRef(AnimatedSprite2D::GetTypeStatic()), AM_DEFAULT);
    ACCESSOR_ATTRIBUTE("Animation", GetAnimation, SetAnimationAttr, String, String::EMPTY, AM_DEFAULT);
    ENUM_ACCESSOR_ATTRIBUTE("Loop Mode", GetLoopMode, SetLoopMode, LoopMode2D, loopModeNames, LM_DEFAULT, AM_DEFAULT);
}

void AnimatedSprite2D::OnSetEnabled()
{
    StaticSprite2D::OnSetEnabled();

    bool enabled = IsEnabledEffective();

    Scene* scene = GetScene();
    if (scene)
    {
        if (enabled)
            SubscribeToEvent(scene, E_SCENEPOSTUPDATE, HANDLER(AnimatedSprite2D, HandleScenePostUpdate));
        else
            UnsubscribeFromEvent(scene, E_SCENEPOSTUPDATE);
    }

    for (unsigned i = 0; i < trackNodes_.Size(); ++i)
    {
        if (!trackNodes_[i])
            continue;

        StaticSprite2D* staticSprite = trackNodes_[i]->GetComponent<StaticSprite2D>();
        if (staticSprite)
            staticSprite->SetEnabled(enabled);
    }
}

void AnimatedSprite2D::SetSpeed(float speed)
{
    speed_ = speed;
    MarkNetworkUpdate();
}

void AnimatedSprite2D::SetAnimation(AnimationSet2D* animationSet, const String& name, LoopMode2D loopMode)
{
    animationSet_ = animationSet;

    SetAnimation(name, loopMode);
}

void AnimatedSprite2D::SetAnimation(const String& name, LoopMode2D loopMode)
{
    animationName_ = name;

    if (animationSet_)
        SetAnimation(animationSet_->GetAnimation(animationName_), loopMode);
}

void AnimatedSprite2D::SetAnimationSet(AnimationSet2D* animationSet)
{
    if (animationSet == animationSet_)
        return;

    animationSet_ = animationSet;

    SetAnimation(animationName_, loopMode_);
}

void AnimatedSprite2D::SetLoopMode(LoopMode2D loopMode)
{
    if (!animation_)
        return;

    loopMode_ = loopMode;

    switch (loopMode_)
    {
    case LM_FORCE_LOOPED:
        looped_ = true;
        break;

    case LM_FORCE_CLAMPED:
        looped_ = false;
        break;

    default:
        looped_ = animation_->IsLooped();
        break;
    }
}

AnimationSet2D* AnimatedSprite2D::GetAnimationSet() const
{
    return animationSet_;
}

Node* AnimatedSprite2D::GetRootNode() const
{
    return rootNode_;
}

void AnimatedSprite2D::SetAnimationSetAttr(const ResourceRef& value)
{
    ResourceCache* cache = GetSubsystem<ResourceCache>();
    SetAnimationSet(cache->GetResource<AnimationSet2D>(value.name_));
}

ResourceRef AnimatedSprite2D::GetAnimationSetAttr() const
{
    return GetResourceRef(animationSet_, AnimationSet2D::GetTypeStatic());
}

void AnimatedSprite2D::OnNodeSet(Node* node)
{
    StaticSprite2D::OnNodeSet(node);

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
        numTracks_ = 0;
        trackNodes_.Clear();
        trackNodeInfos_.Clear();
    }
}

void AnimatedSprite2D::SetAnimationAttr(const String& name)
{
    animationName_ = name;

    if (animationSet_)
        SetAnimation(animationSet_->GetAnimation(animationName_), loopMode_);
}

void AnimatedSprite2D::OnWorldBoundingBoxUpdate()
{
    boundingBox_.Clear();
    worldBoundingBox_.Clear();

    for (unsigned i = 0; i < numTracks_; ++i)
    {
        if (!trackNodes_[i])
            continue;

        StaticSprite2D* staticSprite = trackNodes_[i]->GetComponent<StaticSprite2D>();
        if (staticSprite)
            worldBoundingBox_.Merge(staticSprite->GetWorldBoundingBox());
    }

    boundingBox_ = worldBoundingBox_.Transformed(node_->GetWorldTransform().Inverse());
}

void AnimatedSprite2D::OnLayerChanged()
{
    for (unsigned i = 0; i < numTracks_; ++i)
    {
        if (!trackNodes_[i])
            continue;

        StaticSprite2D* staticSprite = trackNodes_[i]->GetComponent<StaticSprite2D>();
        if (staticSprite)
            staticSprite->SetLayer(layer_);
    }
}

void AnimatedSprite2D::OnBlendModeChanged()
{
    for (unsigned i = 0; i < numTracks_; ++i)
    {
        if (!trackNodes_[i])
            continue;

        StaticSprite2D* staticSprite = trackNodes_[i]->GetComponent<StaticSprite2D>();
        staticSprite->SetBlendMode(blendMode_);
    }
}

void AnimatedSprite2D::OnFlipChanged()
{
    for (unsigned i = 0; i < numTracks_; ++i)
    {
        if (!trackNodes_[i])
            continue;

        StaticSprite2D* staticSprite = trackNodes_[i]->GetComponent<StaticSprite2D>();
        staticSprite->SetFlip(flipX_, flipY_);
    }

    // For editor paused mode
    UpdateAnimation(0.0f);
}

void AnimatedSprite2D::UpdateVertices()
{
    verticesDirty_ = false;
}

void AnimatedSprite2D::SetAnimation(Animation2D* animation, LoopMode2D loopMode)
{
    if (animation == animation_)
    {
        SetLoopMode(loopMode_);

        currentTime_ = 0.0f;
        UpdateAnimation(0.0f);
        return;
    }

    for (unsigned i = 0; i < numTracks_; ++i)
    {
        if (trackNodes_[i])
            trackNodes_[i]->SetEnabled(false);
    }

    numTracks_ = 0;
    trackNodes_.Clear();
    trackNodeInfos_.Clear();

    animation_ = animation;

    if (!animation_)
        return;

    currentTime_ = 0.0f;

    if (!rootNode_)
    {
        rootNode_ = GetNode()->CreateChild("_root_", LOCAL);
        rootNode_->SetTemporary(true);
    }

    numTracks_ = animation_->GetNumTracks();
    trackNodes_.Resize(numTracks_);
    trackNodeInfos_.Resize(numTracks_);

    for (unsigned i = 0; i < numTracks_; ++i)
    {
        const AnimationTrack2D& track = animation->GetTrack(i);
        SharedPtr<Node> trackNode(rootNode_->GetChild(track.name_));

        StaticSprite2D* staticSprite = 0;
        if (trackNode)
        {
            // Enable track node
            trackNode->SetEnabled(true);
            
            // Get StaticSprite2D component
            if (track.hasSprite_)
                staticSprite = trackNode->GetComponent<StaticSprite2D>();
        }
        else
        {
            // Create new track node
            trackNode = rootNode_->CreateChild(track.name_, LOCAL);
            trackNode->SetTemporary(true);

            // Create StaticSprite2D component
            if (track.hasSprite_)
                staticSprite = trackNode->CreateComponent<StaticSprite2D>();
        }

        if (staticSprite)
        {
            staticSprite->SetLayer(layer_);
            staticSprite->SetBlendMode(blendMode_);
            staticSprite->SetFlip(flipX_, flipY_);
            staticSprite->SetUseHotSpot(true);
        }

        trackNodes_[i] = trackNode;

        trackNodeInfos_[i].hasSprite = track.hasSprite_;
    }

    SetLoopMode(loopMode);
    UpdateAnimation(0.0f);

    MarkNetworkUpdate();
}

void AnimatedSprite2D::UpdateAnimation(float timeStep)
{
    if (!animation_)
        return;

    currentTime_ += timeStep * speed_;

    float time;
    float animationLength = animation_->GetLength();

    if (looped_)
    {
        time = fmodf(currentTime_, animationLength);
        if (time < 0.0f)
            time += animation_->GetLength();
    }
    else
        time = Clamp(currentTime_, 0.0f, animationLength);

    for (unsigned i = 0; i < numTracks_; ++i)
    {
        trackNodeInfos_[i].worldSpace = false;
        
        const AnimationTrack2D& track = animation_->GetTrack(i);        
        const Vector<AnimationKeyFrame2D>& keyFrames = track.keyFrames_;

        // Time out of range
        if (time < keyFrames[0].time_ || time > keyFrames.Back().time_)
            trackNodeInfos_[i].value.enabled_ = false;
        else
        {
            unsigned index = keyFrames.Size() - 1;
            for (unsigned j = 0; j < keyFrames.Size() - 1; ++j)
            {
                if (time <= keyFrames[j + 1].time_)
                {
                    index = j;
                    break;
                }
            }

            const AnimationKeyFrame2D& currKey = keyFrames[index];
            AnimationKeyFrame2D& value = trackNodeInfos_[i].value;

            value.enabled_ = currKey.enabled_;
            value.parent_ = currKey.parent_;

            if (index < keyFrames.Size() - 1)
            {
                const AnimationKeyFrame2D& nextKey = keyFrames[index + 1];
                float t = (time - currKey.time_)  / (nextKey.time_ - currKey.time_);
                value.transform_ = currKey.transform_.Lerp(nextKey.transform_, t, currKey.spin_);

                if (trackNodeInfos_[i].hasSprite)
                    value.alpha_ = Urho3D::Lerp(currKey.alpha_, nextKey.alpha_, t);
            }
            else
            {
                value.transform_ = currKey.transform_;

                if (trackNodeInfos_[i].hasSprite)
                    value.alpha_ = currKey.alpha_;
            }

            if (trackNodeInfos_[i].hasSprite)
            {
                value.zIndex_ = currKey.zIndex_;
                value.sprite_ = currKey.sprite_;
                value.useHotSpot_ = currKey.useHotSpot_;
                value.hotSpot_ = currKey.hotSpot_;
            }
        }
    }

    for (unsigned i = 0; i < numTracks_; ++i)
    {
        Node* node = trackNodes_[i];
        TrackNodeInfo& nodeInfo = trackNodeInfos_[i];

        if (!nodeInfo.value.enabled_)
            node->SetEnabled(false);
        else
        {
            node->SetEnabled(true);

            // Calculate world transform.
            CalculateTimelineWorldTransform(i);

            // Update node's transform
            Vector2 position = nodeInfo.value.transform_.position_ * PIXEL_SIZE;
            if (flipX_)
                position.x_ = -position.x_;
            if (flipY_)
                position.y_ = -position.y_;
            node->SetPosition(position);

            float angle = nodeInfo.value.transform_.angle_;
            if (flipX_ != flipY_)
                angle = -angle;
            node->SetRotation(angle);
            node->SetScale(nodeInfo.value.transform_.scale_);

            if (nodeInfo.hasSprite)
            {
                StaticSprite2D* staticSprite = node->GetComponent<StaticSprite2D>();
                if (staticSprite)
                {
                    staticSprite->SetOrderInLayer(orderInLayer_ + nodeInfo.value.zIndex_);
                    staticSprite->SetSprite(nodeInfo.value.sprite_);
                    staticSprite->SetUseHotSpot(nodeInfo.value.useHotSpot_);
                    staticSprite->SetHotSpot(nodeInfo.value.hotSpot_);
                }
            }
        }
    }

    MarkForUpdate();
}

void AnimatedSprite2D::CalculateTimelineWorldTransform(unsigned index)
{
    TrackNodeInfo& info = trackNodeInfos_[index];
    if (info.worldSpace)
        return;

    info.worldSpace = true;

    int parent = info.value.parent_;
    if (parent != -1)
    {
        CalculateTimelineWorldTransform(parent);
        info.value.transform_ = trackNodeInfos_[parent].value.transform_ * info.value.transform_;
    }
}

void AnimatedSprite2D::HandleScenePostUpdate(StringHash eventType, VariantMap& eventData)
{
    using namespace ScenePostUpdate;
    float timeStep = eventData[P_TIMESTEP].GetFloat();
    UpdateAnimation(timeStep);
}

}
