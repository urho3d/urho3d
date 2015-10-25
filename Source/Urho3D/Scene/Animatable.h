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

#include "../Container/HashSet.h"
#include "../Scene/Serializable.h"
#include "../Scene/ValueAnimationInfo.h"

namespace Urho3D
{

class Animatable;
class ValueAnimation;
class AttributeAnimationInfo;
class ObjectAnimation;

/// Attribute animation instance.
class AttributeAnimationInfo : public ValueAnimationInfo
{
public:
    /// Construct.
    AttributeAnimationInfo
        (Animatable* animatable, const AttributeInfo& attributeInfo, ValueAnimation* attributeAnimation, WrapMode wrapMode,
            float speed);
    /// Copy construct.
    AttributeAnimationInfo(const AttributeAnimationInfo& other);
    /// Destruct.
    ~AttributeAnimationInfo();

    /// Return attribute infomation.
    const AttributeInfo& GetAttributeInfo() const { return attributeInfo_; }

protected:
    /// Apply new animation value to the target object. Called by Update().
    virtual void ApplyValue(const Variant& newValue);

private:
    /// Attribute information.
    const AttributeInfo& attributeInfo_;
};

/// Base class for animatable object, an animatable object can be set animation on it's attributes, or can be set an object animation to it.
class URHO3D_API Animatable : public Serializable
{
    URHO3D_OBJECT(Animatable, Serializable);

public:
    /// Construct.
    Animatable(Context* context);
    /// Destruct.
    virtual ~Animatable();
    /// Register object factory.
    static void RegisterObject(Context* context);

    /// Load from XML data. When setInstanceDefault is set to true, after setting the attribute value, store the value as instance's default value. Return true if successful.
    virtual bool LoadXML(const XMLElement& source, bool setInstanceDefault = false);
    /// Save as XML data. Return true if successful.
    virtual bool SaveXML(XMLElement& dest) const;

    /// Set automatic update of animation, default true.
    void SetAnimationEnabled(bool enable);
    /// Set time position of all attribute animations or an object animation manually. Automatic update should be disabled in this case.
    void SetAnimationTime(float time);

    /// Set object animation.
    void SetObjectAnimation(ObjectAnimation* objectAnimation);
    /// Set attribute animation.
    void SetAttributeAnimation
        (const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode = WM_LOOP, float speed = 1.0f);
    /// Set attribute animation wrap mode.
    void SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode);
    /// Set attribute animation speed.
    void SetAttributeAnimationSpeed(const String& name, float speed);
    /// Set attribute animation time position manually. Automatic update should be disabled in this case.
    void SetAttributeAnimationTime(const String& name, float time);
    /// Remove object animation. Same as calling SetObjectAnimation with a null pointer.
    void RemoveObjectAnimation();
    /// Remove attribute animation. Same as calling SetAttributeAnimation with a null pointer.
    void RemoveAttributeAnimation(const String& name);

    /// Return animation enabled.
    bool GetAnimationEnabled() const { return animationEnabled_; }

    /// Return object animation.
    ObjectAnimation* GetObjectAnimation() const;
    /// Return attribute animation.
    ValueAnimation* GetAttributeAnimation(const String& name) const;
    /// Return attribute animation wrap mode.
    WrapMode GetAttributeAnimationWrapMode(const String& name) const;
    /// Return attribute animation speed.
    float GetAttributeAnimationSpeed(const String& name) const;
    /// Return attribute animation time position.
    float GetAttributeAnimationTime(const String& name) const;

    /// Set object animation attribute.
    void SetObjectAnimationAttr(const ResourceRef& value);
    /// Return object animation attribute.
    ResourceRef GetObjectAnimationAttr() const;

protected:
    /// Handle attribute animation added.
    virtual void OnAttributeAnimationAdded() = 0;
    /// Handle attribute animation removed.
    virtual void OnAttributeAnimationRemoved() = 0;
    /// Find target of an attribute animation from object hierarchy by name.
    virtual Animatable* FindAttributeAnimationTarget(const String& name, String& outName);
    /// Set object attribute animation internal.
    void SetObjectAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode, float speed);
    /// Handle object animation added.
    void OnObjectAnimationAdded(ObjectAnimation* objectAnimation);
    /// Handle object animation removed.
    void OnObjectAnimationRemoved(ObjectAnimation* objectAnimation);
    /// Update attribute animations.
    void UpdateAttributeAnimations(float timeStep);
    /// Is animated network attribute.
    bool IsAnimatedNetworkAttribute(const AttributeInfo& attrInfo) const;
    /// Return attribute animation info.
    AttributeAnimationInfo* GetAttributeAnimationInfo(const String& name) const;
    /// Handle attribute animation added.
    void HandleAttributeAnimationAdded(StringHash eventType, VariantMap& eventData);
    /// Handle attribute animation removed.
    void HandleAttributeAnimationRemoved(StringHash eventType, VariantMap& eventData);

    /// Animation enabled.
    bool animationEnabled_;
    /// Animation.
    SharedPtr<ObjectAnimation> objectAnimation_;
    /// Animated network attribute set.
    HashSet<const AttributeInfo*> animatedNetworkAttributes_;
    /// Attribute animation infos.
    HashMap<String, SharedPtr<AttributeAnimationInfo> > attributeAnimationInfos_;
};

}
