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

#include "../Container/HashMap.h"
#include "../Container/Ptr.h"

namespace Urho3D
{

class Animation;
class AnimatedModel;
class Deserializer;
class Serializer;
class Skeleton;
struct AnimationTrack;
struct Bone;

/// %Animation instance per-track data.
struct AnimationStateTrack
{
    /// Construct with defaults.
    AnimationStateTrack();
    /// Destruct
    ~AnimationStateTrack();
    
    /// Animation track.
    const AnimationTrack* track_;
    /// Bone pointer.
    Bone* bone_;
    /// Scene node pointer.
    WeakPtr<Node> node_;
    /// Blending weight.
    float weight_;
    /// Last key frame.
    unsigned keyFrame_;
};

/// %Animation instance.
class URHO3D_API AnimationState : public RefCounted
{
public:
    /// Construct with animated model and animation pointers.
    AnimationState(AnimatedModel* model, Animation* animation);
    /// Construct with root scene node and animation pointers.
    AnimationState(Node* node, Animation* animation);
    /// Destruct.
    ~AnimationState();
    
    /// Set start bone. Not supported in node animation mode. Resets any assigned per-bone weights.
    void SetStartBone(Bone* bone);
    /// Set looping enabled/disabled.
    void SetLooped(bool looped);
    /// Set blending weight.
    void SetWeight(float weight);
    /// Set time position. Does not fire animation triggers.
    void SetTime(float time);
    /// Set per-bone blending weight by track index. Default is 1.0 (full), is multiplied  with the state's blending weight when applying the animation. Optionally recurses to child bones.
    void SetBoneWeight(unsigned index, float weight, bool recursive = false);
    /// Set per-bone blending weight by name.
    void SetBoneWeight(const String& name, float weight, bool recursive = false);
    /// Set per-bone blending weight by name hash.
    void SetBoneWeight(StringHash nameHash, float weight, bool recursive = false);
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
    /// Return per-bone blending weight by track index.
    float GetBoneWeight(unsigned index) const;
    /// Return per-bone blending weight by name.
    float GetBoneWeight(const String& name) const;
    /// Return per-bone blending weight by name.
    float GetBoneWeight(StringHash nameHash) const;
    /// Return track index with matching bone node, or M_MAX_UNSIGNED if not found.
    unsigned GetTrackIndex(Node* node) const;
    /// Return track index by bone name, or M_MAX_UNSIGNED if not found.
    unsigned GetTrackIndex(const String& name) const;
    /// Return track index by bone name hash, or M_MAX_UNSIGNED if not found.
    unsigned GetTrackIndex(StringHash nameHash) const;
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
    /// Apply animation to a skeleton. Transform changes are applied silently, so the model needs to dirty its root model afterward.
    void ApplyToModel();
    /// Apply animation to a scene node hierarchy.
    void ApplyToNodes();
    /// Apply animation track to a scene node, full weight.
    void ApplyTrackFullWeight(AnimationStateTrack& stateTrack);
    /// Apply animation track to a scene node, full weight. Apply transform changes silently without marking the node dirty.
    void ApplyTrackFullWeightSilent(AnimationStateTrack& stateTrack);
    /// Apply animation track to a scene node, blended with current node transform. Apply transform changes silently without marking the node dirty.
    void ApplyTrackBlendedSilent(AnimationStateTrack& stateTrack, float weight);

    /// Animated model (model mode.)
    WeakPtr<AnimatedModel> model_;
    /// Root scene node (node hierarchy mode.)
    WeakPtr<Node> node_;
    /// Animation.
    SharedPtr<Animation> animation_;
    /// Start bone.
    Bone* startBone_;
    /// Per-track data.
    Vector<AnimationStateTrack> stateTracks_;
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
