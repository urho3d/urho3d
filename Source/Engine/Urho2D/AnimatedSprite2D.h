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

#include "StaticSprite2D.h"

namespace Urho3D
{

class Animation2D;

/// Animated sprite component.
class URHO3D_API AnimatedSprite2D : public StaticSprite2D
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

    /// Set speed.
    void SetSpeed(float speed);
    /// Set cycle mode.
    void SetCycleMode(CycleMode cycleMode);
    /// Set animation.
    void SetAnimation(Animation2D* animation);

    /// Return speed.
    float GetSpeed() const { return speed_; }
    /// Return cycle mode.
    CycleMode GetCycleMode() const { return cycleMode_; }
    /// Return Animation.
    Animation2D* GetAnimation() const;

    /// Set animation attr.
    void SetAnimationAttr(ResourceRef value);
    /// Return animation attr.
    ResourceRef GetAnimationAttr() const;

protected:
    /// Handle node being assigned.
    virtual void OnNodeSet(Node* node);
    /// Handle scene post update.
    void HandleScenePostUpdate(StringHash eventType, VariantMap& eventData);

    /// Speed.
    float speed_;
    /// Cycle mode.
    CycleMode cycleMode_;
    /// Animation.
    SharedPtr<Animation2D> animation_;
    /// Animation time.
    float animationTime_;
    /// Animation total time.
    float animationTotalTime_;
};

}
