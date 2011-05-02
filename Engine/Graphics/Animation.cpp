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
#include "Context.h"
#include "Deserializer.h"
#include "Log.h"
#include "Profiler.h"
#include "Serializer.h"

#include "DebugNew.h"

void AnimationTrack::GetKeyFrameIndex(float time, unsigned& index) const
{
    if (time < 0.0f)
        time = 0.0f;
    
    if (index >= keyFrames_.size())
        index = keyFrames_.size() - 1;
    
    // Check for being too far ahead
    while ((index) && (time < keyFrames_[index].time_))
        index--;
    
    // Check for being too far behind
    while ((index < keyFrames_.size() - 1) && (time >= keyFrames_[index + 1].time_))
        index++;
}

OBJECTTYPESTATIC(Animation);

Animation::Animation(Context* context) :
    Resource(context)
{
}

Animation::~Animation()
{
}

void Animation::RegisterObject(Context* context)
{
    context->RegisterFactory<Animation>();
}

bool Animation::Load(Deserializer& source)
{
    PROFILE(LoadAnimation);
    
    unsigned memoryUse = 0;
    
    // Check ID
    if (source.ReadID() != "UANI")
    {
        LOGERROR(source.GetName() + " is not a valid animation file");
        return false;
    }
    
    // Read name and length
    animationName_ = source.ReadString();
    animationNameHash_ = StringHash(animationName_);
    length_ = source.ReadFloat();
    tracks_.clear();
    
    unsigned tracks = source.ReadUInt();
    tracks_.resize(tracks);
    memoryUse += tracks * sizeof(AnimationTrack);
    
    // Read tracks
    for (unsigned i = 0; i < tracks; ++i)
    {
        AnimationTrack& newTrack = tracks_[i];
        newTrack.name_ = source.ReadString();
        newTrack.nameHash_ = StringHash(newTrack.name_);
        newTrack.channelMask_ = source.ReadUByte();
        
        unsigned keyFrames = source.ReadUInt();
        newTrack.keyFrames_.resize(keyFrames);
        memoryUse += keyFrames * sizeof(AnimationKeyFrame);
        
        // Read keyframes of the track
        for (unsigned j = 0; j < keyFrames; ++j)
        {
            AnimationKeyFrame& newKeyFrame = newTrack.keyFrames_[j];
            newKeyFrame.time_ = source.ReadFloat();
            if (newTrack.channelMask_ & CHANNEL_POSITION)
                newKeyFrame.position_ = source.ReadVector3();
            if (newTrack.channelMask_ & CHANNEL_ROTATION)
                newKeyFrame.rotation_ = source.ReadQuaternion();
            if (newTrack.channelMask_ & CHANNEL_SCALE)
                newKeyFrame.scale_ = source.ReadVector3();
        }
    }
    
    SetMemoryUse(memoryUse);
    return true;
}

bool Animation::Save(Serializer& dest)
{
    // Write ID, name and length
    dest.WriteID("UANI");
    dest.WriteString(animationName_);
    dest.WriteFloat(length_);
    
    // Write tracks
    dest.WriteUInt(tracks_.size());
    for (unsigned i = 0; i < tracks_.size(); ++i)
    {
        const AnimationTrack& track = tracks_[i];
        dest.WriteString(track.name_);
        dest.WriteUByte(track.channelMask_);
        dest.WriteUInt(track.keyFrames_.size());
        
        // Write keyframes of the track
        for (unsigned j = 0; j < track.keyFrames_.size(); ++j)
        {
            const AnimationKeyFrame& keyFrame = track.keyFrames_[j];
            dest.WriteFloat(keyFrame.time_);
            if (track.channelMask_ & CHANNEL_POSITION)
                dest.WriteVector3(keyFrame.position_);
            if (track.channelMask_ & CHANNEL_ROTATION)
                dest.WriteQuaternion(keyFrame.rotation_);
            if (track.channelMask_ & CHANNEL_SCALE)
                dest.WriteVector3(keyFrame.scale_);
        }
    }
    
    return true;
}

void Animation::SetAnimationName(const std::string& name)
{
    animationName_ = name;
    animationNameHash_ = StringHash(name);
}

void Animation::SetLength(float length)
{
    length_ = Max(length, 0.0f);
}

void Animation::SetTracks(const std::vector<AnimationTrack>& tracks)
{
    tracks_ = tracks;
}

unsigned Animation::GetNumTracks() const
{
    return tracks_.size();
}

const AnimationTrack* Animation::GetTrack(unsigned index) const
{
    return index < tracks_.size() ? &tracks_[index] : 0;
}

const AnimationTrack* Animation::GetTrack(const std::string& name) const
{
    for (std::vector<AnimationTrack>::const_iterator i = tracks_.begin(); i != tracks_.end(); ++i)
    {
        if ((*i).name_ == name)
            return &(*i);
    }
    
    return 0;
}

const AnimationTrack* Animation::GetTrack(StringHash nameHash) const
{
    for (std::vector<AnimationTrack>::const_iterator i = tracks_.begin(); i != tracks_.end(); ++i)
    {
        if ((*i).nameHash_ == nameHash)
            return &(*i);
    }
    
    return 0;
}
