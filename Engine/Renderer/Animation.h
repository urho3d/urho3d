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

#ifndef RENDERER_ANIMATION_H
#define RENDERER_ANIMATION_H

#include "Quaternion.h"
#include "Resource.h"
#include "SharedPtr.h"
#include "Vector3.h"

#include <map>
#include <vector>

//! Animation keyframe
struct AnimationKeyFrame
{
    //! Keyframe time
    float mTime;
    //! Bone position
    Vector3 mPosition;
    //! Bone rotation
    Quaternion mRotation;
    //! Bone scale
    Vector3 mScale;
};

//! Animation track
struct AnimationTrack
{
    //! Return keyframe index based on time and previous index
    void getKeyFrameIndex(float time, unsigned& index) const;
    
    //! Bone name
    std::string mName;
    //! Bone name hash
    StringHash mNameHash;
    //! Bitmask of included data (position, rotation, scale)
    unsigned char mChannelMask;
    //! Keyframes
    std::vector<AnimationKeyFrame> mKeyFrames;
};

static const unsigned char CHANNEL_POSITION = 0x1;
static const unsigned char CHANNEL_ROTATION = 0x2;
static const unsigned char CHANNEL_SCALE = 0x4;

//! Animation resource
class Animation : public Resource
{
    DEFINE_TYPE(Animation);
    
public:
    //! Construct with name
    Animation(const std::string& name = std::string());
    //! Destruct
    virtual ~Animation();
    
    //! Load resource. Throw exception on error
    virtual void load(Deserializer& source, ResourceCache* cache = 0);
    //! Save resource. Throw exception on error
    virtual void save(Serializer& dest);
    
    //! Return animation name
    const std::string& getAnimationName() const { return mAnimationName; }
    //! Return animation name hash
    StringHash getAnimationNameHash() const { return mAnimationNameHash; }
    //! Return animation length
    float getLength() const { return mLength; }
    //! Return all animation tracks
    const std::vector<AnimationTrack>& getTracks() const { return mTracks; }
    //! Return number of animation tracks
    unsigned getNumTracks() const;
    //! Return animation track by index
    const AnimationTrack* getTrack(unsigned index) const;
    //! Return animation track by bone name
    const AnimationTrack* getTrack(const std::string& name) const;
    //! Return animation track by bone name hash
    const AnimationTrack* getTrack(const StringHash nameHash) const;
    
private:
    //! Animation name
    std::string mAnimationName;
    //! Animation name hash
    StringHash mAnimationNameHash;
    //! Animation length
    float mLength;
    //! Animation tracks
    std::vector<AnimationTrack> mTracks;
};

#endif // RENDERER_ANIMATION_H
