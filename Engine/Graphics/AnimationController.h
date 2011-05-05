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

#include "Component.h"

class AnimatedModel;
class Animation;
class AnimationState;
struct Bone;

/// Control data for an animation
struct AnimationControl
{
    /// Construct with defaults
    AnimationControl() :
        speed_(1.0f),
        targetWeight_(0.0f),
        fadeTime_(0.0f),
        autoFadeTime_(0.0f)
    {
    }

    /// Animation resource name hash
    StringHash hash_;
    /// Animation speed
    float speed_;
    /// Animation target weight
    float targetWeight_;
    /// Animation weight fade time, 0 if no fade
    float fadeTime_;
    /// Animation autofade on stop -time, 0 if disabled
    float autoFadeTime_;
};

/// Component that drives an AnimatedModel's animations
class AnimationController : public Component
{
    OBJECT(AnimationController);

public:
    /// Construct
    AnimationController(Context* context);
    /// Destruct
    virtual ~AnimationController();
    /// Register object factory
    static void RegisterObject(Context* context);
    
    /// Handle attribute write access
    virtual void OnSetAttribute(const AttributeInfo& attr, const Variant& value);
    /// Handle attribute read access
    virtual Variant OnGetAttribute(const AttributeInfo& attr);
    
    /// Update the animations. Is called from HandleScenePostUpdate()
    void Update(float timeStep);
    /// Play an animation and set full target weight. Name must be the full resource name. Return true on success
    bool Play(const std::string& name, int layer, bool looped, float fadeInTime);
    /// Play an animation, set full target weight and fade out all other animations on the same layer. Name must be the full resource name. Return true on success
    bool PlayExclusive(const std::string& name, int layer, bool looped, float fadeTime);
    /// Stop an animation. Zero fadetime is instant. Return true on success
    bool Stop(const std::string& name, float fadeOutTime);
    /// Stop all animations on a specific layer. Zero fadetime is instant
    void StopLayer(int layer, float fadeOutTime);
    /// Stop all animations. Zero fadetime is instant
    void StopAll(float fadeTime);
    /// Fade animation to target weight. Return true on success
    bool Fade(const std::string& name, float targetWeight, float fadeTime);
    /// Fade other animations on the same layer to target weight. Return true on success
    bool FadeOthers(const std::string& name, float targetWeight, float fadeTime);
    
    /// Set animation blending layer priority. Return true on success
    bool SetLayer(const std::string& name, int layer);
    /// Set animation start bone. Return true on success
    bool SetStartBone(const std::string& name, const std::string& startBoneName);
    /// Set animation time position. Return true on success
    bool SetTime(const std::string& name, float time);
    /// Set animation weight. Return true on success
    bool SetWeight(const std::string& name, float weight);
    /// Set animation looping. Return true on success
    bool SetLooped(const std::string& name, bool enable);
    /// Set animation speed. Return true on success
    bool SetSpeed(const std::string& name, float speed);
    /// Set animation autofade on stop (non-looped animations only.) Zero time disables. Return true on success
    bool SetAutoFade(const std::string& name, float fadeOutTime);
    
    /// Return whether an animation is active
    bool IsPlaying(const std::string& name) const;
    /// Return whether an animation is fading in
    bool IsFadingIn(const std::string& name) const;
    /// Return whether an animation is fading out
    bool IsFadingOut(const std::string& name) const;
    /// Return animation blending layer
    int GetLayer(const std::string& name) const;
    /// Return animation start bone, or null if no such animation
    Bone* GetStartBone(const std::string& name) const;
    /// Return animation start bone name, or null if no such animation
    const std::string& GetStartBoneName(const std::string& name) const;
    /// Return animation time position
    float GetTime(const std::string& name) const;
    /// Return animation weight
    float GetWeight(const std::string& name) const;
    /// Return animation looping
    bool IsLooped(const std::string& name) const;
    /// Return animation length
    float GetLength(const std::string& name) const;
    /// Return animation speed
    float GetSpeed(const std::string& name) const;
    /// Return animation fade target weight
    float GetFadeTarget(const std::string& name) const;
    /// Return animation fade time
    float GetFadeTime(const std::string& name) const;
    /// Return animation autofade time
    float GetAutoFade(const std::string& name) const;

protected:
    /// Handle node being assigned
    virtual void OnNodeSet(Node* node);

private:
    /// Find the internal index and animation state of an animation
    void FindAnimation(const std::string& name, unsigned& index, AnimationState*& state) const;
    /// Find the animation state only
    AnimationState* FindAnimationState(const std::string& name) const;
    /// Handle scene post-update event
    void HandleScenePostUpdate(StringHash eventType, VariantMap& eventData);
    
    /// Controlled animations
    std::vector<AnimationControl> animations_;
};
