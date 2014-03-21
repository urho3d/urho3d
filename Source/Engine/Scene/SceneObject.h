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
class Scene;

/// Base class for scene objects.
class URHO3D_API SceneObject : public Serializable
{
    OBJECT(SceneObject);

public:
    /// Construct.
    SceneObject(Context* context);
    /// Destruct.
    virtual ~SceneObject();

    /// Return scene.
    virtual Scene* GetScene() const = 0;

    /// Add attribute animation.
    void SetAttributeAnimation(const String& name, AttributeAnimation* animation);
    /// Get attribute animation.
    AttributeAnimation* GetAttributeAnimation(const String& name) const;

private:
    /// Update attribute animations.
    void UpdateAttributeAnimations(float timeStep);
    /// Handle scene post-update event.
    void HandleScenePostUpdate(StringHash eventType, VariantMap& eventData);

    /// Animation time.
    float animationTime_;
    /// Attribute animations.
    HashMap<const AttributeInfo*, SharedPtr<AttributeAnimation> > attributeAnimations_;

};

}
