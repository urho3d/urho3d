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

#include "Serializable.h"

namespace Urho3D
{

class AttributeAnimation;
class AttributeAnimationInstance;
class ObjectAnimation;

/// Base class for animatable object
class URHO3D_API Animatable : public Serializable
{
    OBJECT(Animatable);

public:
    /// Construct.
    Animatable(Context* context);
    /// Destruct.
    virtual ~Animatable();
    /// Register object factory.
    static void RegisterObject(Context* context);

    /// Set animation enabled.
    void SetAnimationEnabled(bool enable);
    /// Set object animation.
    void SetObjectAnimation(ObjectAnimation* objectAnimation);
    /// Set attribute animation.
    void SetAttributeAnimation(const String& name, AttributeAnimation* attributeAnimation);

    /// Return animation enabled.
    bool GetAnimationEnabled() const { return animationEnabled_; }
    /// Return object animation.
    const ObjectAnimation* GetObjectAnimation() const;
    /// Return attribute animation.
    const AttributeAnimation* GetAttributeAnimation(const String& name) const;

    /// Set object animation attribute.
    void SetObjectAnimationAttr(ResourceRef value);
    /// Return object animation attribute.
    ResourceRef GetObjectAnimationAttr() const;

protected:
    /// Handle object animation added.
    virtual void OnObjectAnimationAdded(ObjectAnimation* objectAnimation);
    /// Handle object animation removed.
    virtual void OnObjectAnimationRemoved(ObjectAnimation* objectAnimation);
    /// Handle attribute animation added.
    virtual void OnAttributeAnimationAdded() = 0;
    /// Handle attribute animation removed.
    virtual void OnAttributeAnimationRemoved() = 0;
    /// Update attribute animations.
    void UpdateAttributeAnimations(float timeStep);

    /// Animation enabled.
    bool animationEnabled_;
    /// Animation.
    SharedPtr<ObjectAnimation> objectAnimation_;
    /// Attribute animation instances.
    HashMap<String, SharedPtr<AttributeAnimationInstance> > attributeAnimationInstances_;
};

}
