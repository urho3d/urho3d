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
#include "Animation.h"
#include "Deserializer.h"
#include "Serializer.h"

#include "DebugNew.h"

void AnimationTrack::getKeyFrameIndex(float time, unsigned& index) const
{
    if (time < 0.0f)
        time = 0.0f;
    
    if (index >= mKeyFrames.size())
        index = mKeyFrames.size() - 1;
    
    // Check for being too far ahead
    while ((index) && (time < mKeyFrames[index].mTime))
        index--;
    
    // Check for being too far behind
    while ((index < mKeyFrames.size() - 1) && (time >= mKeyFrames[index + 1].mTime))
        index++;
}

Animation::Animation(const std::string& name) :
    Resource(name)
{
}

Animation::~Animation()
{
}

void Animation::load(Deserializer& source, ResourceCache* cache)
{
    unsigned memoryUse = 0;
    
    mAnimationName = source.readString();
    mAnimationNameHash = StringHash(mAnimationName);
    mLength = source.readFloat();
    mTracks.clear();
    
    unsigned tracks = source.readUInt();
    mTracks.resize(tracks);
    memoryUse += tracks * sizeof(AnimationTrack);
    
    // Read tracks
    for (unsigned i = 0; i < tracks; ++i)
    {
        AnimationTrack& newTrack = mTracks[i];
        newTrack.mName = source.readString();
        newTrack.mNameHash = StringHash(newTrack.mName);
        newTrack.mChannelMask = source.readUByte();
        
        unsigned keyFrames = source.readUInt();
        newTrack.mKeyFrames.resize(keyFrames);
        memoryUse += keyFrames * sizeof(AnimationKeyFrame);
        
        // Read keyframes of the track
        for (unsigned j = 0; j < keyFrames; ++j)
        {
            AnimationKeyFrame& newKeyFrame = newTrack.mKeyFrames[j];
            newKeyFrame.mTime = source.readFloat();
            if (newTrack.mChannelMask & CHANNEL_POSITION)
                newKeyFrame.mPosition = source.readVector3();
            if (newTrack.mChannelMask & CHANNEL_ROTATION)
                newKeyFrame.mRotation = source.readQuaternion();
            if (newTrack.mChannelMask & CHANNEL_SCALE)
                newKeyFrame.mScale = source.readVector3();
        }
    }
    
    setMemoryUse(memoryUse);
}

void Animation::save(Serializer& dest)
{
    dest.writeString(mAnimationName);
    dest.writeFloat(mLength);
    
    // Write tracks
    dest.writeUInt(mTracks.size());
    for (unsigned i = 0; i < mTracks.size(); ++i)
    {
        const AnimationTrack& track = mTracks[i];
        dest.writeString(track.mName);
        dest.writeUByte(track.mChannelMask);
        dest.writeUInt(track.mKeyFrames.size());
        
        // Write keyframes of the track
        for (unsigned j = 0; j < track.mKeyFrames.size(); ++j)
        {
            const AnimationKeyFrame& keyFrame = track.mKeyFrames[j];
            dest.writeFloat(keyFrame.mTime);
            if (track.mChannelMask & CHANNEL_POSITION)
                dest.writeVector3(keyFrame.mPosition);
            if (track.mChannelMask & CHANNEL_ROTATION)
                dest.writeQuaternion(keyFrame.mRotation);
            if (track.mChannelMask & CHANNEL_SCALE)
                dest.writeVector3(keyFrame.mScale);
        }
    }
}

unsigned Animation::getNumTracks() const
{
    return mTracks.size();
}

const AnimationTrack* Animation::getTrack(unsigned index) const
{
    if (index >= mTracks.size())
        return 0;
    
    return &mTracks[index];
}

const AnimationTrack* Animation::getTrack(const std::string& name) const
{
    for (std::vector<AnimationTrack>::const_iterator i = mTracks.begin(); i != mTracks.end(); ++i)
    {
        if ((*i).mName == name)
            return &(*i);
    }
    
    return 0;
}

const AnimationTrack* Animation::getTrack(const StringHash nameHash) const
{
    for (std::vector<AnimationTrack>::const_iterator i = mTracks.begin(); i != mTracks.end(); ++i)
    {
        if ((*i).mNameHash == nameHash)
            return &(*i);
    }
    
    return 0;
}
