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

#include "SharedPtr.h"

#include <map>

class Animation;
class AnimatedModel;
class Deserializer;
class Serializer;
class Skeleton;
struct AnimationTrack;
struct Bone;

/// Animation instance in an animated model
class AnimationState : public RefCounted
{
public:
    /// Construct with animated model and animation pointers
    AnimationState(AnimatedModel* model, Animation* animation);
    /// Destruct
    ~AnimationState();
    
    /// Set start bone
    void SetStartBone(Bone* bone);
    /// Set looping enabled/disabled
    void SetLooped(bool looped);
    /// Set blending weight
    void SetWeight(float weight);
    /// Set time position
    void SetTime(float time);
    /// Modify blending weight
    void AddWeight(float delta);
    /// Modify time position
    void AddTime(float delta);
    /// Set blending layer
    void SetLayer(int layer);
    /// Set whether to use nlerp instead of slerp for rotation, default false
    void SetUseNlerp(bool enable);
    
    /// Return animation
    Animation* GetAnimation() const { return animation_; }
    /// Return start bone
    Bone* GetStartBone() const;
    /// Return whether weight is nonzero
    bool IsEnabled() const { return weight_ > 0.0f; }
    /// Return whether looped
    bool IsLooped() const { return looped_; }
    /// Return blending weight
    float GetWeight() const { return weight_; }
    /// Return time position
    float GetTime() const { return time_; }
    /// Return animation length
    float GetLength() const;
    /// Return blending layer
    int GetLayer() const { return layer_; }
    /// Return whether using nlerp for rotation
    bool GetUseNlerp() const { return useNlerp_; }
    
    /// Apply to the animated model's skeleton. Called by AnimatedModel
    void Apply();
    
private:
    /// Animated model
    WeakPtr<AnimatedModel> model_;
    /// Animation
    SharedPtr<Animation> animation_;
    /// Start bone
    Bone* startBone_;
    /// Mapping of animation track indices to bones
    std::map<unsigned, Bone*> trackToBoneMap_;
    /// Last keyframe on each animation track for optimized keyframe search
    std::vector<unsigned> lastKeyFrame_;
    /// Looped flag
    bool looped_;
    /// Blending weight
    float weight_;
    /// Time position
    float time_;
    /// Blending layer
    int layer_;
    /// Nlerp flag
    bool useNlerp_;
};
