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

#ifndef RENDERER_ANIMATIONSTATE_H
#define RENDERER_ANIMATIONSTATE_H

#include "RefCount.h"
#include "SharedPtr.h"

#include <map>

class Animation;
class AnimatedModel;
class Bone;
class Deserializer;
class Serializer;
class Skeleton;
struct AnimationTrack;

//! Animation instance in an animated model
class AnimationState
{
public:
    //! Construct with animated model and animation pointers
    AnimationState(AnimatedModel* node, Animation* animation);
    //! Destruct
    ~AnimationState();
    
    //! Write state to a stream
    void save(Serializer& dest);
    //! Read state from a stream
    void load(Deserializer& source);
    //! Write state to an XML element
    void saveXML(XMLElement& element);
    //! Read state from an XML element
    void loadXML(const XMLElement& element);
    //! Set animation
    void setAnimation(Animation* animation);
    //! Set start bone
    void setStartBone(Bone* startBone);
    //! Set looping enabled/disabled
    void setLooped(bool looped);
    //! Set blending weight
    void setWeight(float weight);
    //! Set time position
    void setTime(float time);
    //! Modify blending weight
    void addWeight(float delta);
    //! Modify time position
    void addTime(float delta);
    //! Set blending priority
    void setPriority(int priority);
    //! Set nlerp use instead of slerp, default false
    void setUseNlerp(bool enable);
    
    //! Return animation
    Animation* getAnimation() const { return mAnimation; }
    //! Return start bone
    Bone* getStartBone() const { return mStartBone; }
    //! Return whether weight is nonzero
    bool isEnabled() const { return mWeight != 0.0f; }
    //! Return whether looped
    bool isLooped() const { return mLooped; }
    //! Return blending weight
    float getWeight() const;
    //! Return time position
    float getTime() const;
    //! Return blending priority
    int getPriority() const { return mPriority; }
    //! Return whether using nlerp
    bool getUseNlerp() const { return mUseNlerp; }
    //! Return whether network client smoothing active
    bool isInterpolating() const { return mInterpolationFlags != 0; }
    
    //! Apply to the animated model's skeleton. Called by AnimatedModel
    void apply();
    //! Sync from another animation state. Called by AnimatedModel
    void sync(AnimationState* src);
    //! Perform client-side visual smoothing. Called by AnimatedModel
    void interpolate(bool snapToEnd, float t);
    
private:
    //! Animated model
    AnimatedModel* mNode;
    //! Start bone
    Bone* mStartBone;
    //! Animation
    SharedPtr<Animation> mAnimation;
    //! Mapping of animation track indices to bones
    std::map<unsigned, Bone*> mTrackToBoneMap;
    //! Last keyframe on each animation track for optimized keyframe search
    std::vector<unsigned> mLastKeyFrame;
    //! Looped flag
    bool mLooped;
    //! Blending weight
    float mWeight;
    //! Time position
    float mTime;
    //! Blending priority
    int mPriority;
    //! Nlerp flag
    bool mUseNlerp;
    //! Visual smoothing target blending weight
    float mInterpolationWeight;
    //! Visual smoothing target time position
    float mInterpolationTime;
    //! Currently active visual smoothings
    unsigned char mInterpolationFlags;
};

#endif // RENDERER_ANIMATIONSTATE_H

