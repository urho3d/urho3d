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

AnimationState::AnimationState(AnimatedModel* node, Animation* animation) :
    mNode(node),
    mStartBone(0),
    mLooped(false),
    mWeight(0.0f),
    mTime(0.0f),
    mPriority(0),
    mUseNlerp(false),
    mInterpolationFlags(0)
{
    setAnimation(animation);
}

AnimationState::~AnimationState()
{
}

void AnimationState::save(Serializer& dest)
{
    dest.writeStringHash(mAnimation->getNameHash());
    dest.writeStringHash(mStartBone->getNameHash());
    dest.writeBool(mLooped);
    if (!mNode->isProxy())
    {
        dest.writeFloat(mWeight);
        dest.writeFloat(mTime);
    }
    else
    {
        dest.writeFloat(mInterpolationWeight);
        dest.writeFloat(mInterpolationTime);
    }
    dest.writeInt(mPriority);
    dest.writeBool(mUseNlerp);
}

void AnimationState::load(Deserializer& source)
{
    // Loading the correct animation is handled by the AnimatedModel
    setStartBone(mNode->getSkeleton().getBone(source.readStringHash()));
    mLooped = source.readBool();
    if (!mNode->isProxy())
    {
        mWeight = clamp(source.readFloat(), 0.0f, 1.0f);
        mTime = clamp(source.readFloat(), 0.0f, mAnimation->getLength());
    }
    else
    {
        mInterpolationWeight = clamp(source.readFloat(), 0.0f, 1.0f);
        mInterpolationTime = clamp(source.readFloat(), 0.0f, mAnimation->getLength());
        mInterpolationFlags = INTERP_WEIGHT | INTERP_TIME;
    }
    mPriority = source.readInt();
    mUseNlerp = source.readBool();
}

void AnimationState::saveXML(XMLElement& element)
{
    element.setString("name", mAnimation->getName());
    element.setString("startbone", mAnimation->getName());
    element.setBool("looped", isLooped());
    element.setFloat("weight", getWeight());
    element.setFloat("time", getTime());
    element.setInt("priority", getPriority());
    element.setBool("nlerp", getUseNlerp());
}

void AnimationState::loadXML(const XMLElement& element)
{
    // Loading the correct animation is handled by the AnimatedModel
    setStartBone(mNode->getSkeleton().getBone(element.getString("startbone")));
    setLooped(element.getBool("looped"));
    setWeight(element.getFloat("weight"));
    setTime(element.getFloat("time"));
    setPriority(element.getInt("priority"));
    setUseNlerp(element.getBool("nlerp"));
}

void AnimationState::setAnimation(Animation* animation)
{
    if (!animation)
        EXCEPTION("Null animation for AnimationState");
    
    mAnimation = animation;
    setStartBone(0);
    
    // Setup a cache for last keyframe of each track
    mLastKeyFrame.resize(mAnimation->getNumTracks());
    for (unsigned i = 0; i < mLastKeyFrame.size(); ++i)
        mLastKeyFrame[i] = 0;
}

void AnimationState::setStartBone(Bone* startBone)
{
    Bone* rootBone = mNode->getSkeleton().getRootBone();
    if (!rootBone)
        return;
    if (!startBone)
        startBone = rootBone;
    if (mStartBone == startBone)
        return;
    
    mStartBone = startBone;
    mTrackToBoneMap.clear();
    const std::vector<AnimationTrack>& tracks = mAnimation->getTracks();
    
    for (unsigned i = 0; i < tracks.size(); ++i)
    {
        Bone* trackBone = 0;
        
        // Try to find a bone from the skeleton that corresponds to this track
        // with the limitation that it's startBone, or one of its children
        if (startBone->getNameHash() == tracks[i].mNameHash)
            trackBone = startBone;
        else
        {
            trackBone = dynamic_cast<Bone*>(startBone->getChild(tracks[i].mNameHash, true));
            // Make sure the child bone actually belongs to the skeleton
            if (trackBone)
            {
                if (trackBone->getRootBone() != rootBone)
                    trackBone = 0;
            }
        }
        
        if (trackBone)
            mTrackToBoneMap[i] = trackBone;
    }
    
    mNode->markAnimationDirty();
}

void AnimationState::setLooped(bool looped)
{
    mLooped = looped;
}

void AnimationState::setWeight(float weight)
{
    weight = clamp(weight, 0.0f, 1.0f);
    
    // If we are a network proxy, always interpolate, regardless whether it is a server update or local prediction
    if (mNode->isProxy())
    {
        if (weight != mInterpolationWeight)
        {
            mInterpolationWeight = weight;
            mInterpolationFlags |= INTERP_WEIGHT;
        }
    }
    else
    {
        if (weight != mWeight)
        {
            mWeight = weight;
            mNode->markAnimationDirty();
        }
    }
}

void AnimationState::setTime(float time)
{
    time = clamp(time, 0.0f, mAnimation->getLength());
    
    // If we are a network proxy, always interpolate, regardless whether it is a server update or local prediction
    if (mNode->isProxy())
    {
        if (time != mInterpolationTime)
        {
            mInterpolationTime = time;
            mInterpolationFlags |= INTERP_TIME;
        }
    }
    else
    {
        if (time != mTime)
        {
            mTime = time;
            mNode->markAnimationDirty();
        }
    }
}

void AnimationState::addWeight(float delta)
{
    if (delta == 0.0f)
        return;
    
    // If we are a network proxy, use interpolation target weight as a base
    setWeight(getWeight() + delta);
}

void AnimationState::addTime(float delta)
{
    float length = mAnimation->getLength();
    if ((delta == 0.0f) || (length == 0.0f))
        return;
    
    // If we are a network proxy, use interpolation target time as a base
    float time = getTime() + delta;
    if (mLooped)
    {
        while (time >= length)
            time -= length;
        while (time < 0.0f)
            time += length;
    }
    
    setTime(time);
}

void AnimationState::setPriority(int priority)
{
    priority = clamp(priority, 0, 255);
    if (priority != mPriority)
    {
        mPriority = priority;
        mNode->markAnimationOrderDirty();
    }
}

void AnimationState::setUseNlerp(bool enable)
{
    mUseNlerp = enable;
}

float AnimationState::getWeight() const
{
    if (!mNode->isProxy())
        return mWeight;
    else
        return mInterpolationWeight;
}

float AnimationState::getTime() const
{
    if (!mNode->isProxy())
        return mTime;
    else
        return mInterpolationTime;
}

void AnimationState::apply()
{
    if (!isEnabled())
        return;
    
    // Check first if full weight or blending
    if (mWeight == 1.0f)
    {
        for (std::map<unsigned, Bone*>::const_iterator i = mTrackToBoneMap.begin(); i != mTrackToBoneMap.end(); ++i)
        {
            const AnimationTrack* track = mAnimation->getTrack(i->first);
            Bone* bone = i->second;
            
            if ((!bone->isAnimationEnabled()) || (!track->mKeyFrames.size()))
                continue;
            
            unsigned& frame = mLastKeyFrame[i->first];
            track->getKeyFrameIndex(mTime, frame);
            
            // Check if next frame to interpolate to is valid, or if wrapping is needed (looping animation only)
            unsigned nextFrame = frame + 1;
            bool interpolate = true;
            if (nextFrame >= track->mKeyFrames.size())
            {
                if (!mLooped)
                {
                    nextFrame = frame;
                    interpolate = false;
                }
                else
                    nextFrame = 0;
            }
            
            const AnimationKeyFrame* keyFrame = &track->mKeyFrames[frame];
            unsigned char channelMask = track->mChannelMask;
            
            if (!interpolate)
            {
                // No interpolation, full weight
                if (channelMask & CHANNEL_POSITION)
                    bone->setPosition(keyFrame->mPosition);
                if (channelMask & CHANNEL_ROTATION)
                    bone->setRotation(keyFrame->mRotation);
                if (channelMask & CHANNEL_SCALE)
                    bone->setScale(keyFrame->mScale);
            }
            else
            {
                const AnimationKeyFrame* nextKeyFrame = &track->mKeyFrames[nextFrame];
                float timeInterval = nextKeyFrame->mTime - keyFrame->mTime;
                if (timeInterval < 0.0f)
                    timeInterval += mAnimation->getLength();
                float t = 1.0f;
                if (timeInterval > 0.0f)
                    t = (mTime - keyFrame->mTime) / timeInterval;
                
                // Interpolation, full weight
                if (channelMask & CHANNEL_POSITION)
                    bone->setPosition(keyFrame->mPosition.lerp(nextKeyFrame->mPosition, t));
                if (channelMask & CHANNEL_ROTATION)
                {
                    if (!mUseNlerp)
                        bone->setRotation(keyFrame->mRotation.slerp(nextKeyFrame->mRotation, t));
                    else
                        bone->setRotation(keyFrame->mRotation.nlerpFast(nextKeyFrame->mRotation, t));
                }
                if (channelMask & CHANNEL_SCALE)
                    bone->setScale(keyFrame->mScale.lerp(nextKeyFrame->mScale, t));
            }
        }
    }
    else
    {
        for (std::map<unsigned, Bone*>::const_iterator i = mTrackToBoneMap.begin(); i != mTrackToBoneMap.end(); ++i)
        {
            const AnimationTrack* track = mAnimation->getTrack(i->first);
            Bone* bone = i->second;
            
            if ((!bone->isAnimationEnabled()) || (!track->mKeyFrames.size()))
                continue;
            
            unsigned& frame = mLastKeyFrame[i->first];
            track->getKeyFrameIndex(mTime, frame);
            
            // Check if next frame to interpolate to is valid, or if wrapping is needed (looping animation only)
            unsigned nextFrame = frame + 1;
            bool interpolate = true;
            if (nextFrame >= track->mKeyFrames.size())
            {
                if (!mLooped)
                {
                    nextFrame = frame;
                    interpolate = false;
                }
                else
                    nextFrame = 0;
            }
            
            const AnimationKeyFrame* keyFrame = &track->mKeyFrames[frame];
            unsigned char channelMask = track->mChannelMask;
            
            if (!interpolate)
            {
                // No interpolation, blend between old transform & animation
                if (channelMask & CHANNEL_POSITION)
                    bone->setPosition(bone->getPosition().lerp(keyFrame->mPosition, mWeight));
                if (channelMask & CHANNEL_ROTATION)
                {
                    if (!mUseNlerp)
                        bone->setRotation(bone->getRotation().slerp(keyFrame->mRotation, mWeight));
                    else
                        bone->setRotation(bone->getRotation().nlerpFast(keyFrame->mRotation, mWeight));
                }
                if (channelMask & CHANNEL_SCALE)
                    bone->setScale(bone->getScale().lerp(keyFrame->mScale, mWeight));
            }
            else
            {
                const AnimationKeyFrame* nextKeyFrame = &track->mKeyFrames[nextFrame];
                float timeInterval = nextKeyFrame->mTime - keyFrame->mTime;
                if (timeInterval < 0.0f)
                    timeInterval += mAnimation->getLength();
                float t = 1.0f;
                if (timeInterval > 0.0f)
                    t = (mTime - keyFrame->mTime) / timeInterval;
                
                // Interpolation, blend between old transform & animation
                if (channelMask & CHANNEL_POSITION)
                {
                    bone->setPosition(bone->getPosition().lerp(
                        keyFrame->mPosition.lerp(nextKeyFrame->mPosition, t), mWeight));
                }
                if (channelMask & CHANNEL_ROTATION)
                {
                    if (!mUseNlerp)
                    {
                        bone->setRotation(bone->getRotation().slerp(
                            keyFrame->mRotation.slerp(nextKeyFrame->mRotation, t), mWeight));
                    }
                    else
                    {
                        bone->setRotation(bone->getRotation().nlerpFast(
                            keyFrame->mRotation.nlerpFast(nextKeyFrame->mRotation, t), mWeight));
                    }
                }
                if (channelMask & CHANNEL_SCALE)
                {
                    bone->setScale(bone->getScale().lerp(
                        keyFrame->mScale.lerp(nextKeyFrame->mScale, t), mWeight));
                }
            }
        }
    }
}

void AnimationState::sync(AnimationState* src)
{
    Bone* srcStartBone = src->getStartBone();
    if (!srcStartBone)
        return;
    
    if (mStartBone->getName() != srcStartBone->getName())
    {
        // Note: this may return null, in that case new startbone is simply the rootbone
        // Downside is that we will attempt changing the startbone each time sync() is called
        Bone* newStartBone = mNode->getSkeleton().getBone(srcStartBone->getNameHash());
        setStartBone(newStartBone);
    }
    
    setLooped(src->isLooped());
    setPriority(src->getPriority());
    setTime(src->getTime());
    setWeight(src->getWeight());
}

void AnimationState::interpolate(bool snapToEnd, float t)
{
    if (!mInterpolationFlags)
        return;
    
    if (!snapToEnd)
    {
        if (mInterpolationFlags & INTERP_WEIGHT)
        {
            if (fabsf(mWeight - mInterpolationWeight) < M_EPSILON)
            {
                mWeight = mInterpolationWeight;
                mInterpolationFlags &= ~INTERP_WEIGHT;
            }
            else
                mWeight = lerp(mWeight, mInterpolationWeight, t);
        }
        
        if (mInterpolationFlags & INTERP_TIME)
        {
            if (fabsf(mTime - mInterpolationTime) < M_EPSILON)
            {
                mTime = mInterpolationTime;
                mInterpolationFlags &= ~INTERP_TIME;
            }
            else
            {
                // If animation is looping, use the shortest path
                if (mLooped)
                {
                    float lerpStartTime = mTime;
                    float animLength = mAnimation->getLength();
                    if (fabsf(mInterpolationTime - lerpStartTime) > (animLength * 0.5f))
                    {
                        if (lerpStartTime > mInterpolationTime)
                            lerpStartTime -= animLength;
                        else
                            lerpStartTime += animLength;
                    }
                    mTime = lerp(lerpStartTime, mInterpolationTime, t);
                    if (mTime < 0.0f)
                        mTime += animLength;
                    if (mTime > animLength)
                        mTime -= animLength;
                }
                else
                    mTime = lerp(mTime, mInterpolationTime, t);
            }
        }
    }
    else
    {
        if (mInterpolationFlags & INTERP_WEIGHT)
            mWeight = mInterpolationWeight;
        if (mInterpolationFlags & INTERP_TIME)
            mTime = mInterpolationTime;
        mInterpolationFlags = INTERP_NONE;
    }
    
    mNode->markAnimationDirty();
}
