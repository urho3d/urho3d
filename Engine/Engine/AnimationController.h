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

#ifndef ENGINE_ANIMATIONCONTROLLER_H
#define ENGINE_ANIMATIONCONTROLLER_H

#include "Component.h"
#include "EventListener.h"
#include "SharedPtr.h"

class AnimatedModel;
class Animation;
class AnimationState;
class Bone;

//! Controlled animation
struct AnimationControl
{
    //! Construct with defaults
    AnimationControl() :
        mGroup(0),
        mSpeed(1.0f),
        mTargetWeight(0.0f),
        mFadeTime(0.0f),
        mAutoFadeTime(0.0f)
    {
    }
    
    //! Animation resource name hash
    StringHash mHash;
    //! Animation group
    unsigned char mGroup;
    //! Animation speed
    float mSpeed;
    //! Animation target weight
    float mTargetWeight;
    //! Animation weight fade time, 0 if no fade
    float mFadeTime;
    //! Animation autofade on stop -time, 0 if disabled
    float mAutoFadeTime;
};

//! Controls the animations of an AnimatedModel
class AnimationController : public Component, public EventListener
{
    DEFINE_TYPE(AnimationController);
    
public:
    //! Construct with name
    AnimationController(const std::string& name = std::string());
    //! Destruct
    virtual ~AnimationController();
    
    //! Write component state to a stream
    virtual void save(Serializer& dest);
    //! Read component state from a stream
    virtual void load(Deserializer& source, ResourceCache* cache);
    //! Write component state to an XML element
    virtual void saveXML(XMLElement& dest);
    //! Read component state from an XML element
    virtual void loadXML(const XMLElement& source, ResourceCache* cache);
    //! Resolve component references after loading
    virtual void postLoad(ResourceCache* cache);
    //! Write a network update
    virtual bool writeNetUpdate(Serializer& dest, Serializer& destRevision, Deserializer& baseRevision, const NetUpdateInfo& info);
    //! Read a network update
    virtual void readNetUpdate(Deserializer& source, ResourceCache* cache, const NetUpdateInfo& info);
    //! Resolve component references after a network update
    virtual void postNetUpdate(ResourceCache* cache);
    //! Return component references
    virtual void getComponentRefs(std::vector<ComponentRef>& dest);
    
    //! Update the animations. Is called from handleScenePostUpdate()
    void update(float timeStep);
    //! Set animated model to control
    void setAnimatedModel(AnimatedModel* model);
    //! Add an animation by full resource name. Return true on success
    bool addAnimation(const std::string& name, unsigned char group);
    //! Remove an animation. Zero fadetime is instant. Return true on success
    bool removeAnimation(const std::string& name, float fadeTime);
    //! Remove all animations within a group. Zero fadetime is instant
    void removeAnimations(unsigned char group, float fadeTime);
    //! Remove all animations. Zero fadetime is instant
    void removeAllAnimations(float fadeTime);
    //! Add animation if does not exist, and set multiple properties. Return true on success
    bool setAnimation(const std::string& name, unsigned char group, bool looped, bool restart, float speed, float targetWeight,
        float fadeTime, float autoFadeTime, bool fadeOutOthersInGroup);
    //! Set multiple properties, but do not add the animation if does not exist. Return true on success
    bool setProperties(const std::string& name, unsigned char group, float speed, float targetWeight, float fadeTime,
        float autoFadeTime);
    //! Set animation blending priority. Return true on success
    bool setPriority(const std::string& name, int priority);
    //! Set animation start bone. Return true on success
    bool setStartBone(const std::string& name, const std::string& startBoneName);
    //! Set both blending priority and start bone. Return true on success
    bool setBlending(const std::string& name, int priority, const std::string& startBoneName);
    //! Set animation time position. Return true on success
    bool setTime(const std::string& name, float time);
    //! Set animation weight. Return true on success
    bool setWeight(const std::string& name, float weight);
    //! Set animation looping. Return true on success
    bool setLooped(const std::string& name, bool enable);
    //! Set animation group. Return true on success
    bool setGroup(const std::string& name, unsigned char group);
    //! Set animation speed. Return true on success
    bool setSpeed(const std::string& name, float speed);
    //! Fade animation in or out. Time is in seconds. Return true on success
    bool setFade(const std::string& name, float targetWeight, float time);
    //! Fade other animations within same group. Return true on success
    bool setFadeOthers(const std::string& name, float targetWeight, float time);
    //! Set animation autofade on stop (non-looped animations only.) Zero time disables. Return true on success
    bool setAutoFade(const std::string& name, float time);
    
    //! Return animated model being controlled
    AnimatedModel* getAnimatedModel() const { return mModel; }
    //! Return whether an animation is active
    bool hasAnimation(const std::string& name) const;
    //! Return animation priority
    int getPriority(const std::string& name) const;
    //! Return animation start bone, or null if no such animation
    Bone* getStartBone(const std::string& name) const;
    //! Return animation time position
    float getTime(const std::string& name) const;
    //! Return animation weight
    float getWeight(const std::string& name) const;
    //! Return animation looping
    bool isLooped(const std::string& name) const;
    //! Return animation length
    float getLength(const std::string& name) const;
    //! Return animation group
    unsigned char getGroup(const std::string& name) const;
    //! Return animation speed
    float getSpeed(const std::string& name) const;
    //! Return animation fade target weight
    float getFadeTarget(const std::string& name) const;
    //! Return animation fade time
    float getFadeTime(const std::string& name) const;
    //! Return animation autofade time
    float getAutoFade(const std::string& name) const;
    
private:
    //! Find the internal index and animation state of an animation
    void findAnimation(const std::string& name, unsigned& index, AnimationState*& state) const;
    //! Find the animation state only
    AnimationState* findAnimationState(const std::string& name) const;
    //! Handle scene post-update event
    void handleScenePostUpdate(StringHash eventType, VariantMap& eventData);
    
    //! Animated model
    SharedPtr<AnimatedModel> mModel;
    //! Controlled animations
    std::vector<AnimationControl> mAnimations;
    //! Animated model component reference
    ComponentRef mModelRef;
};

#endif // ENGINE_ANIMATIONCONTROLLER_H
