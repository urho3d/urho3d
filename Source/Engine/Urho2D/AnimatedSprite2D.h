//
// Copyright (c) 2008-2014 the Urho3D project.
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

#include "Animation2D.h"
#include "Drawable.h"

namespace Urho3D
{

class AnimationSet2D;

/// Spriter animation component.
class URHO3D_API AnimatedSprite2D : public Drawable
{
    OBJECT(AnimatedSprite2D);

public:
    /// Construct.
    AnimatedSprite2D(Context* context);
    /// Destruct.
    ~AnimatedSprite2D();
    /// Register object factory.
    static void RegisterObject(Context* context);

    /// Handle enabled/disabled state change.
    virtual void OnSetEnabled();
    
    /// Set layer.
    void SetLayer(int layer);
    /// Set order in layer.
    void SetOrderInLayer(int orderInLayer);
    /// Set blend mode.
    void SetBlendMode(BlendMode mode);
    /// Set speed.
    void SetSpeed(float speed);
    /// Set animation by animation set and name.
    void SetAnimation(AnimationSet2D* animationSet, const String& name);
    /// Set animation set.
    void SetAnimationSet(AnimationSet2D* animationSet);
    /// Set animation by name.
    void SetAnimation(const String& name);

    /// Return layer.
    int GetLayer() const { return layer_; }
    /// Return order in layer.
    int GetOrderInLayer() const { return orderInLayer_; }
    /// Return blend mode.
    BlendMode GetBlendMode() const { return blendMode_; }
    /// Return speed.
    float GetSpeed() const { return speed_; }
    /// Return animation.
    AnimationSet2D* GetAnimationSet() const;
    /// Return animation name.
    const String& GetAnimation() const { return animationName_; }

    /// Set animation set attribute.
    void SetAnimationSetAttr(ResourceRef value);
    /// Return animation set attribute.
    ResourceRef GetAnimationSetAttr() const;

protected:
    /// Handle node being assigned.
    virtual void OnNodeSet(Node* node);
    /// Recalculate the world-space bounding box.
    virtual void OnWorldBoundingBoxUpdate();
    /// Set animation.
    void SetAnimation(Animation2D* animation);
    /// Update animation.
    void UpdateAnimation(float timeStep);
    /// Update timeline world transform.
    void UpateTimelineWorldTransform(unsigned index);
    /// Handle scene post update.
    void HandleScenePostUpdate(StringHash eventType, VariantMap& eventData);

    /// Layer.
    int layer_;
    /// Order in layer.
    int orderInLayer_;
    /// Blend mode.
    BlendMode blendMode_;
    /// Speed.
    float speed_;
    /// Animation set.
    SharedPtr<AnimationSet2D> animationSet_;
    /// Animation name.
    String animationName_;
    /// Animation.
    SharedPtr<Animation2D> animation_;
    /// Current time.
    float currentTime_;
    /// Timeline nodes.
    Vector<SharedPtr<Node> > timelineNodes_;
    /// Transform info.
    struct TransformInfo
    {
        /// Parent.
        int parent_;
        /// Local transform.
        Transform2D localTransform_;
        /// World transform updated.
        bool worldTransformUpdated_;
        /// World transform.
        Transform2D worldTransform_;
    };
    /// Timeline transform infos.
    Vector<TransformInfo> timelineTransformInfos_;
};

}
