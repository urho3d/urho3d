//
// Copyright (c) 2008-2020 the Urho3D project.
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

#include "../Precompiled.h"

#include "../Graphics/DrawableEvents.h"
#include "../Scene/Component.h"
#include "../Scene/Node.h"
#include "../Urho2D/SpriterInstance2D.h"

#include <cmath>

namespace Urho3D
{

namespace Spriter
{

SpriterInstance::SpriterInstance(Component* owner, SpriterData* spriteData) :
    owner_(owner),
    spriterData_(spriteData),
    spatialInfo_(0.f, 0.f, 0.f, 1.f, 1.f)
{
}

SpriterInstance::~SpriterInstance()
{
    Clear();

    OnSetAnimation(nullptr);
    OnSetEntity(nullptr);
}

bool SpriterInstance::SetEntity(int index)
{
    if (!spriterData_)
        return false;

    if (index < (int)spriterData_->entities_.Size())
    {
        OnSetEntity(spriterData_->entities_[index]);
        return true;
    }

    return false;
}

bool SpriterInstance::SetEntity(const String& entityName)
{
    if (!spriterData_)
        return false;

    for (unsigned i = 0; i < spriterData_->entities_.Size(); ++i)
    {
        if (spriterData_->entities_[i]->name_ == entityName)
        {
            OnSetEntity(spriterData_->entities_[i]);
            return true;
        }
    }

    return false;
}

bool SpriterInstance::SetAnimation(int index, LoopMode loopMode)
{
    if (!entity_)
        return false;

    if (index < (int)entity_->animations_.Size())
    {
        OnSetAnimation(entity_->animations_[index], loopMode);
        return true;
    }

    return false;
}

bool SpriterInstance::SetAnimation(const String& animationName, LoopMode loopMode)
{
    if (!entity_)
        return false;

    for (unsigned i = 0; i < entity_->animations_.Size(); ++i)
    {
        if (entity_->animations_[i]->name_ == animationName)
        {
            OnSetAnimation(entity_->animations_[i], loopMode);
            return true;
        }
    }

    return false;
}

void SpriterInstance::setSpatialInfo(const SpatialInfo& spatialInfo)
{
    this->spatialInfo_ = spatialInfo;
}

void SpriterInstance::setSpatialInfo(float x, float y, float angle, float scaleX, float scaleY)
{
    spatialInfo_ = SpatialInfo(x, y, angle, scaleX, scaleY);
}

void SpriterInstance::Update(float deltaTime)
{
    if (!animation_)
        return;

    Clear();

    float lastTime = currentTime_;
    currentTime_ += deltaTime;
    if (currentTime_ > animation_->length_)
    {
        bool sendFinishEvent = false;

        if (looping_)
        {
            currentTime_ = Mod(currentTime_, animation_->length_);
            sendFinishEvent = true;
        }
        else
        {
            currentTime_ = animation_->length_;
            sendFinishEvent = lastTime != currentTime_;
        }

        if (sendFinishEvent && owner_)
        {
            Node* senderNode = owner_->GetNode();
            if (senderNode)
            {
                using namespace AnimationFinished;

                VariantMap& eventData = senderNode->GetEventDataMap();
                eventData[P_NODE] = senderNode;
                eventData[P_ANIMATION] = animation_;
                eventData[P_NAME] = animation_->name_;
                eventData[P_LOOPED] = looping_;

                senderNode->SendEvent(E_ANIMATIONFINISHED, eventData);
            }
        }
    }

    UpdateMainlineKey();
    UpdateTimelineKeys();
}

void SpriterInstance::OnSetEntity(Entity* entity)
{
    if (entity == this->entity_)
        return;

    OnSetAnimation(nullptr);

    this->entity_ = entity;
}

void SpriterInstance::OnSetAnimation(Animation* animation, LoopMode loopMode)
{
    if (animation == this->animation_)
        return;

    animation_ = animation;
    if (animation_)
    {
        if (loopMode == Default)
            looping_ = animation_->looping_;
        else if (loopMode == ForceLooped)
            looping_ = true;
        else
            looping_ = false;
    }

    currentTime_ = 0.0f;
    Clear();
}

void SpriterInstance::UpdateTimelineKeys()
{
    for (unsigned i = 0; i < mainlineKey_->boneRefs_.Size(); ++i)
    {
        Ref* ref = mainlineKey_->boneRefs_[i];
        auto* timelineKey = (BoneTimelineKey*)GetTimelineKey(ref);
        if (ref->parent_ >= 0)
        {
            timelineKey->info_ = timelineKey->info_.UnmapFromParent(timelineKeys_[ref->parent_]->info_);
        }
        else
        {
            timelineKey->info_ = timelineKey->info_.UnmapFromParent(spatialInfo_);
        }
        timelineKeys_.Push(timelineKey);
    }

    for (unsigned i = 0; i < mainlineKey_->objectRefs_.Size(); ++i)
    {
        Ref* ref = mainlineKey_->objectRefs_[i];
        auto* timelineKey = (SpriteTimelineKey*)GetTimelineKey(ref);

        if (ref->parent_ >= 0)
        {
            timelineKey->info_ = timelineKey->info_.UnmapFromParent(timelineKeys_[ref->parent_]->info_);
        }
        else
        {
            timelineKey->info_ = timelineKey->info_.UnmapFromParent(spatialInfo_);
        }

        timelineKey->zIndex_ = ref->zIndex_;

        timelineKeys_.Push(timelineKey);
    }
}

void SpriterInstance::UpdateMainlineKey()
{
    const PODVector<MainlineKey*>& mainlineKeys = animation_->mainlineKeys_;
    for (unsigned i = 0; i < mainlineKeys.Size(); ++i)
    {
        if (mainlineKeys[i]->time_ <= currentTime_)
        {
            mainlineKey_ = mainlineKeys[i];
        }

        if (mainlineKeys[i]->time_ >= currentTime_)
        {
            break;
        }
    }

    if (!mainlineKey_)
    {
        mainlineKey_ = mainlineKeys[0];
    }
}

TimelineKey* SpriterInstance::GetTimelineKey(Ref* ref) const
{
    Timeline* timeline = animation_->timelines_[ref->timeline_];
    TimelineKey* timelineKey = timeline->keys_[ref->key_]->Clone();
    if (timeline->keys_.Size() == 1 || timelineKey->curveType_ == INSTANT)
    {
        return timelineKey;
    }

    unsigned nextTimelineKeyIndex = ref->key_ + 1;
    if (nextTimelineKeyIndex >= timeline->keys_.Size())
    {
        if (animation_->looping_)
        {
            nextTimelineKeyIndex = 0;
        }
        else
        {
            return timelineKey;
        }
    }

    TimelineKey* nextTimelineKey = timeline->keys_[nextTimelineKeyIndex];

    float nextTimelineKeyTime = nextTimelineKey->time_;
    if (nextTimelineKey->time_ < timelineKey->time_)
    {
        nextTimelineKeyTime += animation_->length_;
    }

    float t = timelineKey->GetTByCurveType(currentTime_, nextTimelineKeyTime);
    timelineKey->Interpolate(*nextTimelineKey, t);

    return timelineKey;
}

void SpriterInstance::Clear()
{
    mainlineKey_ = nullptr;

    if (!timelineKeys_.Empty())
    {
        for (unsigned i = 0; i < timelineKeys_.Size(); ++i)
        {
            delete timelineKeys_[i];
        }
        timelineKeys_.Clear();
    }
}

}

}
