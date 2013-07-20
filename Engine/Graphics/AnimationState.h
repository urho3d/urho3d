//
// Copyright (c) 2008-2013 the Urho3D project.
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

#include "HashMap.h"
#include "Ptr.h"

namespace Urho3D
{

class Animation;
class AnimatedModel;
class Deserializer;
class Serializer;
class Skeleton;
struct AnimationTrack;
struct Bone;

/// %Animation instance.
class AnimationState : public RefCounted
{
public:
    /// Construct with animated model and animation pointers.
    AnimationState(AnimatedModel* model, Animation* animation);
    /// Construct with root scene node and animation pointers.
    AnimationState(Node* node, Animation* animation);
    /// Destruct.
    ~AnimationState();
    
    /// Set start bone. Not supported in node animation mode.
    void SetStartBone(Bone* bone);
    /// Set looping enabled/disabled.
    void SetLooped(bool looped);
    /// Set blending weight.
    void SetWeight(float weight);
    /// Set time position. Does not fire animation triggers.
    void SetTime(float time);
    /// Modify blending weight.
    void AddWeight(float delta);
    /// Modify time position. %Animation triggers will be fired.
    void AddTime(float delta);
    /// Set blending layer.
    void SetLayer(unsigned char layer);
    
    /// Return animation.
    Animation* GetAnimation() const { return animation_; }
    /// Return animated model this state belongs to (model mode.)
    AnimatedModel* GetModel() const;
    /// Return root scene node this state controls (node hierarchy mode.)
    Node* GetNode() const;
    /// Return start bone.
    Bone* GetStartBone() const;
    /// Return whether weight is nonzero.
    bool IsEnabled() const { return weight_ > 0.0f; }
    /// Return whether looped.
    bool IsLooped() const { return looped_; }
    /// Return blending weight.
    float GetWeight() const { return weight_; }
    /// Return time position.
    float GetTime() const { return time_; }
    /// Return animation length.
    float GetLength() const;
    /// Return blending layer.
    unsigned char GetLayer() const { return layer_; }
    
    /// Apply the animation at the current time position.
    void Apply();
    
private:
    /// Apply animation to a skeleton.
    void ApplyToModel();
    /// Apply animation to a scene node hierarchy.
    void ApplyToNodes();
    /// Apply animation track to a scene node, full weight.
    void ApplyTrackToNodeFullWeight(unsigned index, Node* node);
    /// Apply animation track to a scene node, blended with current node transform.
    void ApplyTrackToNodeBlended(unsigned index, Node* node);
    
    /// Animated model (model mode.)
    WeakPtr<AnimatedModel> model_;
    /// Root scene node (node hierarchy mode.)
    WeakPtr<Node> node_;
    /// Animation.
    SharedPtr<Animation> animation_;
    /// Start bone.
    Bone* startBone_;
    /// Mapping of animation track indices to bones.
    HashMap<unsigned, Bone*> trackToBoneMap_;
    /// Mapping of animation track indices to scene nodes.
    HashMap<unsigned, WeakPtr<Node> > trackToNodeMap_;
    /// Last keyframe on each animation track for optimized keyframe search.
    PODVector<unsigned> lastKeyFrame_;
    /// Looped flag.
    bool looped_;
    /// Blending weight.
    float weight_;
    /// Time position.
    float time_;
    /// Blending layer.
    unsigned char layer_;
};

}
