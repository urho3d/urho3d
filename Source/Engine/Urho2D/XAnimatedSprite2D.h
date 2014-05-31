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

#include "Drawable2D.h"

namespace Urho3D
{

class XAnimationSet2D;
class XAnimation2D;

/// Spriter animation component.
class URHO3D_API XAnimatedSprite2D : public Drawable2D
{
    OBJECT(XAnimatedSprite2D);

public:
    /// Construct.
    XAnimatedSprite2D(Context* context);
    /// Destruct.
    ~XAnimatedSprite2D();
    /// Register object factory.
    static void RegisterObject(Context* context);

    /// Handle enabled/disabled state change.
    virtual void OnSetEnabled();
    /// Set layer.
    virtual void SetLayer(int layer);

    /// Set speed.
    void SetSpeed(float speed);

    /// Set animation by animation set and name.
    void SetAnimation(XAnimationSet2D* animationSet, const String& name);
    /// Set animation.
    void SetAnimation(XAnimation2D* animation);
    /// Set animation by name.
    void SetAnimation(const String& name);

    /// Return speed.
    float GetSpeed() const { return speed_; }
    /// Return animation.
    XAnimation2D* GetAnimation() const;

protected:
    /// Handle node being assigned.
    virtual void OnNodeSet(Node* node);
    /// Recalculate the world-space bounding box.
    virtual void OnWorldBoundingBoxUpdate();
    /// Update vertices.
    virtual void UpdateVertices();
    /// Handle scene post update.
    void HandleScenePostUpdate(StringHash eventType, VariantMap& eventData);
    /// Update.
    void UpdateAnimation(float timeStep);

    /// Speed.
    float speed_;
    /// Animation.
    SharedPtr<XAnimation2D> animation_;
    /// Animation time.
    float animationTime_;
    /// Object nodes.
    Vector<SharedPtr<Node> > objectNodes_;
};

}
