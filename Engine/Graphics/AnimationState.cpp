//
// Urho3D Engine
// Copyright (c) 2008-2011 Lasse Öörni
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
#include "AnimatedModel.h"
#include "Animation.h"
#include "AnimationState.h"
#include "Deserializer.h"
#include "Serializer.h"
#include "XMLElement.h"

#include "DebugNew.h"

AnimationState::AnimationState(AnimatedModel* model, Animation* animation) :
    model_(model),
    animation_(animation),
    startBone_(0),
    looped_(false),
    weight_(0.0f),
    time_(0.0f),
    layer_(0)
{
    SetStartBone(0);
    
    // Setup a cache for last keyframe of each track
    lastKeyFrame_.Resize(animation_->GetNumTracks());
    for (unsigned i = 0; i < lastKeyFrame_.Size(); ++i)
        lastKeyFrame_[i] = 0;
}

AnimationState::~AnimationState()
{
}

void AnimationState::SetStartBone(Bone* startBone)
{
    if (!model_)
        return;
    
    Skeleton& skeleton = model_->GetSkeleton();
    Bone* rootBone = skeleton.GetRootBone();
    if (!rootBone)
        return;
    if (!startBone)
        startBone = rootBone;
    
    // Do not reassign if the start bone did not actually change, and we already have valid bone nodes
    if (startBone == startBone_ && !trackToBoneMap_.Empty())
        return;
    
    startBone_ = startBone;
    
    trackToBoneMap_.Clear();
    if (!startBone->node_)
        return;
    
    const Vector<AnimationTrack>& tracks = animation_->GetTracks();
    
    for (unsigned i = 0; i < tracks.Size(); ++i)
    {
        // Include those tracks that are either the start bone itself, or its children
        Bone* trackBone = 0;
        const StringHash& nameHash = tracks[i].nameHash_;
        
        if (nameHash == startBone->nameHash_)
            trackBone = startBone;
        else
        {
            Node* trackBoneNode = startBone->node_->GetChild(nameHash, true);
            if (trackBoneNode)
                trackBone = skeleton.GetBone(nameHash);
        }
        
        if (trackBone)
            trackToBoneMap_[i] = trackBone;
    }
    
    model_->MarkAnimationDirty();
}

void AnimationState::SetLooped(bool looped)
{
    looped_ = looped;
}

void AnimationState::SetWeight(float weight)
{
    weight = Clamp(weight, 0.0f, 1.0f);
    if (weight != weight_)
    {
        weight_ = weight;
        if (model_)
            model_->MarkAnimationDirty();
    }
}

void AnimationState::SetTime(float time)
{
    time = Clamp(time, 0.0f, animation_->GetLength());
    if (time != time_)
    {
        time_ = time;
        if (model_)
            model_->MarkAnimationDirty();
    }
}

void AnimationState::AddWeight(float delta)
{
    if (delta == 0.0f)
        return;
    
    SetWeight(GetWeight() + delta);
}

void AnimationState::AddTime(float delta)
{
    float length = animation_->GetLength();
    if (delta == 0.0f || length == 0.0f)
        return;
    
    float time = GetTime() + delta;
    if (looped_)
    {
        while (time >= length)
            time -= length;
        while (time < 0.0f)
            time += length;
    }
    
    SetTime(time);
}

void AnimationState::SetLayer(unsigned char layer)
{
    if (layer != layer_)
    {
        layer_ = layer;
        if (model_)
            model_->MarkAnimationOrderDirty();
    }
}

Bone* AnimationState::GetStartBone() const
{
    return model_ ? startBone_ : 0;
}

float AnimationState::GetLength() const
{
    return animation_->GetLength();
}

void AnimationState::Apply()
{
    if (!IsEnabled())
        return;
    
    // Check first if full weight or blending
    if (weight_ == 1.0f)
    {
        for (HashMap<unsigned, Bone*>::ConstIterator i = trackToBoneMap_.Begin(); i != trackToBoneMap_.End(); ++i)
        {
            const AnimationTrack* track = animation_->GetTrack(i->first_);
            Bone* bone = i->second_;
            Node* boneNode = bone->node_;
            if (!boneNode || !bone->animated_ || !track->keyFrames_.Size())
                continue;
            
            unsigned& frame = lastKeyFrame_[i->first_];
            track->GetKeyFrameIndex(time_, frame);
            
            // Check if next frame to interpolate to is valid, or if wrapping is needed (looping animation only)
            unsigned nextFrame = frame + 1;
            bool interpolate = true;
            if (nextFrame >= track->keyFrames_.Size())
            {
                if (!looped_)
                {
                    nextFrame = frame;
                    interpolate = false;
                }
                else
                    nextFrame = 0;
            }
            
            const AnimationKeyFrame* keyFrame = &track->keyFrames_[frame];
            unsigned char channelMask = track->channelMask_;
            
            if (!interpolate)
            {
                // No interpolation, full weight
                if (channelMask & CHANNEL_POSITION)
                    boneNode->SetPosition(keyFrame->position_);
                if (channelMask & CHANNEL_ROTATION)
                    boneNode->SetRotation(keyFrame->rotation_);
                if (channelMask & CHANNEL_SCALE)
                    boneNode->SetScale(keyFrame->scale_);
            }
            else
            {
                const AnimationKeyFrame* nextKeyFrame = &track->keyFrames_[nextFrame];
                float timeInterval = nextKeyFrame->time_ - keyFrame->time_;
                if (timeInterval < 0.0f)
                    timeInterval += animation_->GetLength();
                float t = timeInterval > 0.0f ? (time_ - keyFrame->time_) / timeInterval : 1.0f;
                
                // Interpolation, full weight
                if (channelMask & CHANNEL_POSITION)
                    boneNode->SetPosition(keyFrame->position_.Lerp(nextKeyFrame->position_, t));
                if (channelMask & CHANNEL_ROTATION)
                    boneNode->SetRotation(keyFrame->rotation_.Slerp(nextKeyFrame->rotation_, t));
                if (channelMask & CHANNEL_SCALE)
                    boneNode->SetScale(keyFrame->scale_.Lerp(nextKeyFrame->scale_, t));
            }
        }
    }
    else
    {
        for (HashMap<unsigned, Bone*>::ConstIterator i = trackToBoneMap_.Begin(); i != trackToBoneMap_.End(); ++i)
        {
            const AnimationTrack* track = animation_->GetTrack(i->first_);
            Bone* bone = i->second_;
            Node* boneNode = bone->node_;
            if (!boneNode || !bone->animated_ || !track->keyFrames_.Size())
                continue;
            
            unsigned& frame = lastKeyFrame_[i->first_];
            track->GetKeyFrameIndex(time_, frame);
            
            // Check if next frame to interpolate to is valid, or if wrapping is needed (looping animation only)
            unsigned nextFrame = frame + 1;
            bool interpolate = true;
            if (nextFrame >= track->keyFrames_.Size())
            {
                if (!looped_)
                {
                    nextFrame = frame;
                    interpolate = false;
                }
                else
                    nextFrame = 0;
            }
            
            const AnimationKeyFrame* keyFrame = &track->keyFrames_[frame];
            unsigned char channelMask = track->channelMask_;
            
            if (!interpolate)
            {
                // No interpolation, blend between old transform & animation
                if (channelMask & CHANNEL_POSITION)
                    boneNode->SetPosition(boneNode->GetPosition().Lerp(keyFrame->position_, weight_));
                if (channelMask & CHANNEL_ROTATION)
                    boneNode->SetRotation(boneNode->GetRotation().Slerp(keyFrame->rotation_, weight_));
                if (channelMask & CHANNEL_SCALE)
                    boneNode->SetScale(boneNode->GetScale().Lerp(keyFrame->scale_, weight_));
            }
            else
            {
                const AnimationKeyFrame* nextKeyFrame = &track->keyFrames_[nextFrame];
                float timeInterval = nextKeyFrame->time_ - keyFrame->time_;
                if (timeInterval < 0.0f)
                    timeInterval += animation_->GetLength();
                float t = timeInterval > 0.0f ? (time_ - keyFrame->time_) / timeInterval : 1.0f;
                
                // Interpolation, blend between old transform & animation
                if (channelMask & CHANNEL_POSITION)
                {
                    boneNode->SetPosition(boneNode->GetPosition().Lerp(
                        keyFrame->position_.Lerp(nextKeyFrame->position_, t), weight_));
                }
                if (channelMask & CHANNEL_ROTATION)
                {
                    boneNode->SetRotation(boneNode->GetRotation().Slerp(
                        keyFrame->rotation_.Slerp(nextKeyFrame->rotation_, t), weight_));
                }
                if (channelMask & CHANNEL_SCALE)
                {
                    boneNode->SetScale(boneNode->GetScale().Lerp(
                        keyFrame->scale_.Lerp(nextKeyFrame->scale_, t), weight_));
                }
            }
        }
    }
}
