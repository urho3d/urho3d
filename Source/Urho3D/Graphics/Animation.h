//
// Copyright (c) 2008-2015 the Urho3D project.
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

#include "../Math/Quaternion.h"
#include "../Resource/Resource.h"
#include "../Container/Ptr.h"
#include "../Math/Vector3.h"

namespace Urho3D
{

/// Skeletal animation keyframe.
struct AnimationKeyFrame
{
    /// Keyframe time.
    float time_;
    /// Bone position.
    Vector3 position_;
    /// Bone rotation.
    Quaternion rotation_;
    /// Bone scale.
    Vector3 scale_;
};

/// Skeletal animation track, stores keyframes of a single bone.
struct AnimationTrack
{
    /// Return keyframe index based on time and previous index.
    void GetKeyFrameIndex(float time, unsigned& index) const;
    
    /// Bone name.
    String name_;
    /// Bone name hash.
    StringHash nameHash_;
    /// Bitmask of included data (position, rotation, scale.)
    unsigned char channelMask_;
    /// Keyframes.
    Vector<AnimationKeyFrame> keyFrames_;
};

/// %Animation trigger point.
struct AnimationTriggerPoint
{
    /// Construct.
    AnimationTriggerPoint() :
        time_(0.0f)
    {
    }
    
    /// Trigger time.
    float time_;
    /// Trigger data.
    Variant data_;
};

static const unsigned char CHANNEL_POSITION = 0x1;
static const unsigned char CHANNEL_ROTATION = 0x2;
static const unsigned char CHANNEL_SCALE = 0x4;

/// Skeletal animation resource.
class URHO3D_API Animation : public Resource
{
    OBJECT(Animation);
    
public:
    /// Construct.
    Animation(Context* context);
    /// Destruct.
    virtual ~Animation();
    /// Register object factory.
    static void RegisterObject(Context* context);
    
    /// Load resource from stream. May be called from a worker thread. Return true if successful.
    virtual bool BeginLoad(Deserializer& source);
    /// Save resource. Return true if successful.
    virtual bool Save(Serializer& dest) const;
    
    /// Set animation name.
    void SetAnimationName(const String& name);
    /// Set animation length.
    void SetLength(float length);
    /// Set all animation tracks.
    void SetTracks(const Vector<AnimationTrack>& tracks);
    /// Add a trigger point.
    void AddTrigger(float time, bool timeIsNormalized, const Variant& data);
    /// Remove a trigger point by index.
    void RemoveTrigger(unsigned index);
    /// Remove all trigger points.
    void RemoveAllTriggers();
    /// Resize trigger point vector.
    void SetNumTriggers(unsigned num);
    
    /// Return animation name.
    const String& GetAnimationName() const { return animationName_; }
    /// Return animation name hash.
    StringHash GetAnimationNameHash() const { return animationNameHash_; }
    /// Return animation length.
    float GetLength() const { return length_; }
    /// Return all animation tracks.
    const Vector<AnimationTrack>& GetTracks() const { return tracks_; }
    /// Return number of animation tracks.
    unsigned GetNumTracks() const { return tracks_.Size(); }
    /// Return animation track by index.
    const AnimationTrack* GetTrack(unsigned index) const;
    /// Return animation track by bone name.
    const AnimationTrack* GetTrack(const String& name) const;
    /// Return animation track by bone name hash.
    const AnimationTrack* GetTrack(StringHash nameHash) const;
    /// Return animation trigger points.
    const Vector<AnimationTriggerPoint>& GetTriggers() const { return triggers_; }
    /// Return number of animation trigger points.
    unsigned GetNumTriggers() const {return triggers_.Size(); }
    
private:
    /// Animation name.
    String animationName_;
    /// Animation name hash.
    StringHash animationNameHash_;
    /// Animation length.
    float length_;
    /// Animation tracks.
    Vector<AnimationTrack> tracks_;
    /// Animation trigger points.
    Vector<AnimationTriggerPoint> triggers_;
};

}
