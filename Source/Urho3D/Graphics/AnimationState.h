// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

/// \file

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

/// %Animation blending mode.
enum AnimationBlendMode
{
    // Lerp blending (default)
    ABM_LERP = 0,
    // Additive blending based on difference from bind pose
    ABM_ADDITIVE
};

/// %Animation instance per-track data.
struct AnimationStateTrack
{
    /// Construct with defaults.
    AnimationStateTrack();
    /// Destruct.
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
    ~AnimationState() override;

    /// Set start bone. Not supported in node animation mode. Resets any assigned per-bone weights.
    /// @property
    void SetStartBone(Bone* startBone);
    /// Set looping enabled/disabled.
    /// @property
    void SetLooped(bool looped);
    /// Set blending weight.
    /// @property
    void SetWeight(float weight);
    /// Set blending mode.
    /// @property
    void SetBlendMode(AnimationBlendMode mode);
    /// Set time position. Does not fire animation triggers.
    /// @property
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
    /// @property
    void SetLayer(unsigned char layer);

    /// Return animation.
    /// @property
    Animation* GetAnimation() const { return animation_; }

    /// Return animated model this state belongs to (model mode).
    /// @property
    AnimatedModel* GetModel() const;
    /// Return root scene node this state controls (node hierarchy mode).
    /// @property
    Node* GetNode() const;
    /// Return start bone.
    /// @property
    Bone* GetStartBone() const;
    /// Return per-bone blending weight by track index.
    float GetBoneWeight(unsigned index) const;
    /// Return per-bone blending weight by name.
    /// @property{get_boneWeights}
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
    /// @property
    bool IsEnabled() const { return weight_ > 0.0f; }

    /// Return whether looped.
    /// @property
    bool IsLooped() const { return looped_; }

    /// Return blending weight.
    /// @property
    float GetWeight() const { return weight_; }

    /// Return blending mode.
    /// @property
    AnimationBlendMode GetBlendMode() const { return blendingMode_; }

    /// Return time position.
    /// @property
    float GetTime() const { return time_; }

    /// Return animation length.
    /// @property
    float GetLength() const;

    /// Return blending layer.
    /// @property
    unsigned char GetLayer() const { return layer_; }

    /// Apply the animation at the current time position.
    void Apply();

private:
    /// Apply animation to a skeleton. Transform changes are applied silently, so the model needs to dirty its root model afterward.
    void ApplyToModel();
    /// Apply animation to a scene node hierarchy.
    void ApplyToNodes();
    /// Apply track.
    void ApplyTrack(AnimationStateTrack& stateTrack, float weight, bool silent);

    /// Animated model (model mode).
    WeakPtr<AnimatedModel> model_;
    /// Root scene node (node hierarchy mode).
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
    /// Blending mode.
    AnimationBlendMode blendingMode_;
};

}
