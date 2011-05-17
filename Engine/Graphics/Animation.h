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

#pragma once

#include "Quaternion.h"
#include "Resource.h"
#include "SharedPtr.h"
#include "Vector3.h"

/// Skeletal animation keyframe
struct AnimationKeyFrame
{
    /// Keyframe time
    float time_;
    /// Bone position
    Vector3 position_;
    /// Bone rotation
    Quaternion rotation_;
    /// Bone scale
    Vector3 scale_;
};

/// Skeletal animation track, stores keyframes of a single bone
struct AnimationTrack
{
    /// Return keyframe index based on time and previous index
    void GetKeyFrameIndex(float time, unsigned& index) const;
    
    /// Bone name
    String name_;
    /// Bone name hash
    StringHash nameHash_;
    /// Bitmask of included data (position, rotation, scale)
    unsigned char channelMask_;
    /// Keyframes
    std::vector<AnimationKeyFrame> keyFrames_;
};

static const unsigned char CHANNEL_POSITION = 0x1;
static const unsigned char CHANNEL_ROTATION = 0x2;
static const unsigned char CHANNEL_SCALE = 0x4;

/// Skeletal animation resource
class Animation : public Resource
{
    OBJECT(Animation);
    
public:
    /// Construct
    Animation(Context* context);
    /// Destruct
    virtual ~Animation();
    /// Register object factory
    static void RegisterObject(Context* context);
    
    /// Load resource. Return true if successful
    virtual bool Load(Deserializer& source);
    /// Save resource. Return true if successful
    virtual bool Save(Serializer& dest);
    
    /// Set animation name
    void SetAnimationName(const String& name);
    /// Set animation length
    void SetLength(float length);
    /// Set all animation tracks
    void SetTracks(const std::vector<AnimationTrack>& tracks);
    
    /// Return animation name
    const String& GetAnimationName() const { return animationName_; }
    /// Return animation name hash
    StringHash GetAnimationNameHash() const { return animationNameHash_; }
    /// Return animation length
    float GetLength() const { return length_; }
    /// Return all animation tracks
    const std::vector<AnimationTrack>& GetTracks() const { return tracks_; }
    /// Return number of animation tracks
    unsigned GetNumTracks() const;
    /// Return animation track by index
    const AnimationTrack* GetTrack(unsigned index) const;
    /// Return animation track by bone name
    const AnimationTrack* GetTrack(const String& name) const;
    /// Return animation track by bone name hash
    const AnimationTrack* GetTrack(StringHash nameHash) const;
    
private:
    /// Animation name
    String animationName_;
    /// Animation name hash
    StringHash animationNameHash_;
    /// Animation length
    float length_;
    /// Animation tracks
    std::vector<AnimationTrack> tracks_;
};
