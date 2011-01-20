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

#include "Precompiled.h"
#include "AnimatedModel.h"
#include "Animation.h"
#include "AnimationController.h"
#include "AnimationState.h"
#include "Profiler.h"
#include "ReplicationUtils.h"
#include "ResourceCache.h"
#include "Scene.h"
#include "SceneEvents.h"

#include "DebugNew.h"

AnimationController::AnimationController(const std::string& name) :
    Component(name)
{
    subscribeToEvent(EVENT_SCENEPOSTUPDATE, EVENT_HANDLER(AnimationController, handleScenePostUpdate));
}

AnimationController::~AnimationController()
{
}

void AnimationController::save(Serializer& dest)
{
    // Write Component properties
    Component::save(dest);
    
    // Write AnimatedModel reference
    ComponentRef modelRef(mModel);
    modelRef.write(dest);
    
    // Write controlled animations' state
    // If this is the predicted component save, and local animation is enabled, do not store animation data
    bool localAnimation = (isProxy()) && (mModel) && (mModel->getLocalAnimation()) && (checkPrediction());
    if (!localAnimation)
    {
        dest.writeVLE(mAnimations.size());
        for (unsigned i = 0; i < mAnimations.size(); ++i)
        {
            const AnimationControl& control = mAnimations[i];
            dest.writeStringHash(control.mHash);
            dest.writeUByte(control.mGroup);
            dest.writeFloat(control.mSpeed);
            dest.writeFloat(control.mTargetWeight);
            dest.writeFloat(control.mFadeTime);
            dest.writeFloat(control.mAutoFadeTime);
        }
    }
    else
        dest.writeVLE(0);
}

void AnimationController::load(Deserializer& source, ResourceCache* cache)
{
    // Read Component properties
    Component::load(source, cache);
    
    // Read AnimatedModel reference
    mModelRef.read(source);
    
    // Read controlled animations' state
    unsigned numAnimations = source.readVLE();
    // If this is the predicted component load, and local animation is enabled, do not overwrite the animations
    bool localAnimation = (isProxy()) && (mModel) && (mModel->getLocalAnimation()) && (checkPrediction());
    if ((!localAnimation) || (numAnimations))
    {
        mAnimations.clear();
        for (unsigned i = 0; i < numAnimations; ++i)
        {
            AnimationControl newControl;
            newControl.mHash = source.readStringHash();
            newControl.mGroup = source.readUByte();
            newControl.mSpeed = source.readFloat();
            newControl.mTargetWeight = source.readFloat();
            newControl.mFadeTime = source.readFloat();
            newControl.mAutoFadeTime = source.readFloat();
            mAnimations.push_back(newControl);
        }
    }
}

void AnimationController::saveXML(XMLElement& dest)
{
    // Write Component properties
    Component::saveXML(dest);
    
    // Write AnimatedModel reference
    ComponentRef modelRef(mModel, true);
    if (modelRef.mEntityID)
    {
        XMLElement modelElem = dest.createChildElement("model");
        modelRef.writeXML(modelElem);
    }
    
    // Write controlled animations' state
    for (unsigned i = 0; i < mAnimations.size(); ++i)
    {
        const AnimationControl& control = mAnimations[i];
        AnimationState* state = mModel->getAnimationState(control.mHash);
        if (state)
        {
            Animation* animation = state->getAnimation();
            XMLElement animElem = dest.createChildElement("animation");
            animElem.setString("name", animation->getName());
            animElem.setInt("group", control.mGroup);
            animElem.setFloat("speed", control.mSpeed);
            animElem.setFloat("targetweight", control.mTargetWeight);
            animElem.setFloat("fadetime", control.mFadeTime);
            animElem.setFloat("autofadetime", control.mAutoFadeTime);
        }
    }
}

void AnimationController::loadXML(const XMLElement& source, ResourceCache* cache)
{
    // Read Component properties
    Component::loadXML(source, cache);
    
    // Read AnimatedModel reference
    if (source.hasChildElement("model"))
    {
        XMLElement modelElem = source.getChildElement("model");
        mModelRef.readXML(modelElem);
    }
    else
        mModelRef = ComponentRef();
    
    // Read controlled animations' state
    mAnimations.clear();
    XMLElement animElem = source.getChildElement("animation");
    while (animElem)
    {
        AnimationControl newControl;
        newControl.mHash = StringHash(animElem.getString("name"));
        newControl.mGroup = animElem.getInt("group");
        newControl.mSpeed = animElem.getFloat("speed");
        newControl.mTargetWeight = animElem.getFloat("targetweight");
        newControl.mFadeTime = animElem.getFloat("fadetime");
        newControl.mAutoFadeTime = animElem.getFloat("autofadetime");
        mAnimations.push_back(newControl);
    }
}

void AnimationController::postLoad(ResourceCache* cache)
{
    if (mModelRef.mDirty)
    {
        mModel = static_cast<AnimatedModel*>(mEntity->getScene()->getComponent(mModelRef));
        mModelRef.mDirty = false;
        if (!mModel)
            mAnimations.clear();
    }
}

bool AnimationController::writeNetUpdate(Serializer& dest, Serializer& destRevision, Deserializer& baseRevision, const NetUpdateInfo& info)
{
    ComponentRef modelRef(mModel);
    
    // Build bitmask of changed properties
    unsigned char bits = 0;
    checkComponentRef(modelRef, ComponentRef(), baseRevision, bits, 1);
    unsigned numBaseAnimations = baseRevision.getSize() ? baseRevision.readVLE() : 0;
    if (mAnimations.size() != numBaseAnimations)
        bits |= 2;
    static std::vector<unsigned char> animBits;
    animBits.resize(mAnimations.size());
    // Assume that animations are new ie. require update of all fields
    for (unsigned i = 0; i < mAnimations.size(); ++i)
        animBits[i] = 1 | 2 | 4 | 8 | 16;
    for (unsigned i = 0; i < numBaseAnimations; ++i)
    {
        StringHash animation = baseRevision.readStringHash();
        unsigned char group = baseRevision.readUByte();
        float speed = baseRevision.readFloat();
        float targetWeight = baseRevision.readFloat();
        float fadeTime = baseRevision.readFloat();
        float autoFadeTime = baseRevision.readFloat();
        
        bool found = false;
        for (unsigned j = 0; j < mAnimations.size(); ++j)
        {
            const AnimationControl& control = mAnimations[j];
            if (control.mHash == animation)
            {
                // If animation exists in base state, update only the necessary properties
                found = true;
                animBits[j] = 0;
                
                if (group != control.mGroup)
                    animBits[j] |= 1;
                if (speed != control.mSpeed)
                    animBits[j] |= 2;
                if (targetWeight != control.mTargetWeight)
                    animBits[j] |= 4;
                if (fadeTime != control.mFadeTime)
                    animBits[j] |= 8;
                if (autoFadeTime != control.mAutoFadeTime)
                    animBits[j] |= 16;
                if (animBits[j])
                    bits |= 2;
                break;
            }
        }
        // If not found, the number of animations has stayed same, but the animations are different
        if (!found)
            bits |= 2;
    }
    
    // If local animation, do not send even if changed. It is slightly unoptimal to first check, then disable, but it ensures
    // that the base revision data stays the same (otherwise out of bounds reads might result when toggling local animation)
    if ((mModel) && (mModel->getLocalAnimation()) && (checkPrediction(info.mConnection)))
        bits &= ~(8 | 16);
    
    // Update replication state fully, and network stream by delta
    dest.writeUByte(bits);
    writeComponentRefDelta(modelRef, dest, destRevision, bits & 1);
    destRevision.writeVLE(mAnimations.size());
    for (unsigned i = 0; i < mAnimations.size(); ++i)
    {
        const AnimationControl& control = mAnimations[i];
        destRevision.writeStringHash(control.mHash);
        destRevision.writeUByte(control.mGroup);
        destRevision.writeFloat(control.mSpeed);
        destRevision.writeFloat(control.mTargetWeight);
        destRevision.writeFloat(control.mFadeTime);
        destRevision.writeFloat(control.mAutoFadeTime);
    }
    if (bits & 2)
    {
        dest.writeVLE(mAnimations.size());
        for (unsigned i = 0; i < mAnimations.size(); ++i)
        {
            const AnimationControl& control = mAnimations[i];
            dest.writeStringHash(control.mHash);
            dest.writeUByte(animBits[i]);
            if (animBits[i] & 1)
                dest.writeUByte(control.mGroup);
            // Assume that 8x is the maximum sane animation speedup. This leaves 12 bits for decimals
            if (animBits[i] & 2)
                dest.writeShort((short)clamp(control.mSpeed * 4096.0f, -32767.0f, 32767.0f));
            if (animBits[i] & 4)
                dest.writeUByte((unsigned char)(control.mTargetWeight * 255.0f));
            if (animBits[i] & 8)
            {
                // Assume that 16 seconds is the maximum sane fade time. This leaves 12 bits for decimals
                unsigned short packed = (unsigned short)(min(control.mFadeTime * 4096.0f, 65535.0f));
                if ((!packed) && (control.mFadeTime > 0.0f))
                    packed = 1;
                dest.writeUShort(packed);
            }
            if (animBits[i] & 16)
            {
                unsigned short packed = (unsigned short)(min(control.mAutoFadeTime * 4096.0f, 65535.0f));
                if ((!packed) && (control.mAutoFadeTime > 0.0f))
                    packed = 1;
                dest.writeUShort(packed);
            }
        }
    }
    return bits != 0;
}

void AnimationController::readNetUpdate(Deserializer& source, ResourceCache* cache, const NetUpdateInfo& info)
{
    unsigned char bits = source.readUByte();
    readComponentRefDelta(mModelRef, source, bits & 1);
    if (bits & 2)
    {
        unsigned numAnimations = source.readVLE();
        std::set<StringHash> processed;
        for (unsigned i = 0; i < numAnimations; ++i)
        {
            StringHash animation = source.readStringHash();
            unsigned char animBits = source.readUByte();
            processed.insert(animation);
            
            // Find the animation control structure. If not found, create new
            AnimationState* state = mModel ? mModel->getAnimationState(animation) : 0;
            unsigned index = M_MAX_UNSIGNED;
            for (unsigned j = 0; j < mAnimations.size(); ++j)
            {
                if (mAnimations[j].mHash == animation)
                {
                    index = j;
                    break;
                }
            }
            if (index == M_MAX_UNSIGNED)
            {
                AnimationControl newControl;
                newControl.mHash = animation;
                mAnimations.push_back(newControl);
                index = mAnimations.size() - 1;
            }
            
            AnimationControl& control = mAnimations[index];
            if (animBits & 1)
                control.mGroup = source.readUByte();
            if (animBits & 2)
                control.mSpeed = source.readShort() / 4096.0f;
            if (animBits & 4)
                control.mTargetWeight = source.readUByte() / 255.0f;
            if (animBits & 8)
                control.mFadeTime = source.readUShort() / 4096.0f;
            if (animBits & 16)
                control.mAutoFadeTime = source.readUShort() / 4096.0f;
        }
        
        // Now remove any extra animations not found in the update
        for (std::vector<AnimationControl>::iterator i = mAnimations.begin(); i != mAnimations.end();)
        {
            if (processed.find(i->mHash) == processed.end())
            {
                if (mModel)
                    mModel->removeAnimationState(i->mHash);
                i = mAnimations.erase(i);
            }
            else
                ++i;
        }
    }
}

void AnimationController::postNetUpdate(ResourceCache* cache)
{
    // This is the same as in file deserialization: update model if the ref is dirty
    postLoad(cache);
}

void AnimationController::getComponentRefs(std::vector<ComponentRef>& dest)
{
    if (mModel)
        dest.push_back(ComponentRef(mModel));
}

void AnimationController::update(float timeStep)
{
    if (!mModel)
        return;
    
    PROFILE(AnimationController_Update);
    
    // Loop through animations
    for (std::vector<AnimationControl>::iterator i = mAnimations.begin(); i != mAnimations.end();)
    {
        bool remove = false;
        AnimationState* state = mModel->getAnimationState(i->mHash);
        if (!state)
            remove = true;
        else
        {
            // Advance the animation
            if (i->mSpeed != 0.0f)
                state->addTime(i->mSpeed * timeStep);
            
            float targetWeight = i->mTargetWeight;
            float fadeTime = i->mFadeTime;
            
            // If non-looped animation at the end, activate autofade as applicable
            if ((!state->isLooped()) && (state->getTime() >= state->getLength()) && (i->mAutoFadeTime > 0.0f))
            {
                targetWeight = 0.0f;
                fadeTime = i->mAutoFadeTime;
            }
            
            // Process weight fade
            float currentWeight = state->getWeight();
            if ((currentWeight != targetWeight) && (fadeTime > 0.0f))
            {
                float weightDelta = 1.0f / fadeTime * timeStep;
                if (currentWeight < targetWeight)
                    currentWeight = min(currentWeight + weightDelta, targetWeight);
                else if (currentWeight > targetWeight)
                    currentWeight = max(currentWeight - weightDelta, targetWeight);
                state->setWeight(currentWeight);
            }
            
            // Remove if weight zero and target weight zero
            if ((state->getWeight() == 0.0f) && ((targetWeight == 0.0f) || (fadeTime == 0.0f)))
                remove = true;
        }
        
        if (remove)
        {
            if (state)
                mModel->removeAnimationState(state);
            i = mAnimations.erase(i);
        }
        else
            ++i;
    }
}

void AnimationController::setAnimatedModel(AnimatedModel* model)
{
    if (model != mModel)
    {
        mModel = model;
        mAnimations.clear();
    }
}

bool AnimationController::addAnimation(const std::string& name, unsigned char group)
{
    if (!mModel)
        return false;
    
    //! Check if already exists
    unsigned index;
    AnimationState* state;
    findAnimation(name, index, state);
    
    if (!state)
    {
        if ((!mEntity) || (!mEntity->getScene()))
            return false;
        ResourceCache* cache = mEntity->getScene()->getResourceCache();
        try
        {
            Animation* newAnimation = cache->getResource<Animation>(name);
            state = mModel->addAnimationState(newAnimation);
            if (!state)
                return false;
        }
        catch (...)
        {
            return false;
        }
    }
    
    if (index == M_MAX_UNSIGNED)
    {
        AnimationControl newControl;
        Animation* animation = state->getAnimation();
        newControl.mHash = animation->getNameHash();
        mAnimations.push_back(newControl);
        index = mAnimations.size() - 1;
    }
    
    mAnimations[index].mGroup = group;
    return true;
}

bool AnimationController::removeAnimation(const std::string& name, float fadeTime)
{
    unsigned index;
    AnimationState* state;
    findAnimation(name, index, state);
    if (fadeTime <= 0.0f)
    {
        if (index != M_MAX_UNSIGNED)
            mAnimations.erase(mAnimations.begin() + index);
        if (state)
            mModel->removeAnimationState(state);
    }
    else
    {
        if (index != M_MAX_UNSIGNED)
        {
            mAnimations[index].mTargetWeight = 0.0f;
            mAnimations[index].mFadeTime = fadeTime;
        }
    }
    
    return (index != M_MAX_UNSIGNED) || (state != 0);
}

void AnimationController::removeAnimations(unsigned char group, float fadeTime)
{
    for (std::vector<AnimationControl>::iterator i = mAnimations.begin(); i != mAnimations.end();)
    {
        bool remove = false;
        
        if (i->mGroup == group)
        {
            if (fadeTime < 0.0f)
            {
                remove = true;
                AnimationState* state = mModel->getAnimationState(i->mHash);
                if (state)
                    mModel->removeAnimationState(state);
            }
            else
            {
                i->mTargetWeight = 0.0f;
                i->mFadeTime = fadeTime;
            }
        }
        
        if (remove)
            i = mAnimations.erase(i);
        else
            ++i;
    }
}

void AnimationController::removeAllAnimations(float fadeTime)
{
    for (std::vector<AnimationControl>::iterator i = mAnimations.begin(); i != mAnimations.end();)
    {
        bool remove = false;
        
        if (fadeTime < 0.0f)
        {
            remove = true;
            AnimationState* state = mModel->getAnimationState(i->mHash);
            if (state)
                mModel->removeAnimationState(state);
        }
        else
        {
            i->mTargetWeight = 0.0f;
            i->mFadeTime = fadeTime;
        }
    
        if (remove)
            i = mAnimations.erase(i);
        else
            ++i;
    }
}

bool AnimationController::setAnimation(const std::string& name, unsigned char group, bool looped, bool restart, float speed, 
    float targetWeight, float fadeTime, float autoFadeTime, bool fadeOutOthersInGroup)
{
    unsigned index;
    AnimationState* state;
    findAnimation(name, index, state);
    if ((index == M_MAX_UNSIGNED) || (!state))
    {
        // If animation is not active, and target weight is zero, do nothing
        if (targetWeight <= 0.0f)
            return true;
        // Attempt to add, then re-find
        if (!addAnimation(name, group))
            return false;
        findAnimation(name, index, state);
    }
    
    state->setLooped(looped);
    if (restart)
        state->setTime(0.0f);
    
    AnimationControl& control = mAnimations[index];
    control.mGroup = group;
    control.mSpeed = speed;
    
    if (fadeTime > 0.0f)
        control.mTargetWeight = clamp(targetWeight, 0.0f, 1.0f);
    else
        state->setWeight(targetWeight);
    control.mFadeTime = max(fadeTime, 0.0f);
    control.mAutoFadeTime = max(autoFadeTime, 0.0f);
    
    if (fadeOutOthersInGroup)
    {
        for (unsigned i = 0; i < mAnimations.size(); ++i)
        {
            AnimationControl& otherControl = mAnimations[i];
            if ((otherControl.mGroup == group) && (i != index))
            {
                otherControl.mTargetWeight = 0.0f;
                otherControl.mFadeTime = max(fadeTime, M_EPSILON);
            }
        }
    }
    return true;
}

bool AnimationController::setProperties(const std::string& name, unsigned char group, float speed, float targetWeight, float fadeTime,
    float autoFadeTime)
{
    unsigned index;
    AnimationState* state;
    findAnimation(name, index, state);
    if (index == M_MAX_UNSIGNED)
        return false;
    AnimationControl& control = mAnimations[index];
    control.mGroup = group;
    control.mSpeed = speed;
    control.mTargetWeight = clamp(targetWeight, 0.0f, 1.0f);
    control.mFadeTime = max(fadeTime, 0.0f);
    control.mAutoFadeTime = max(fadeTime, 0.0f);
    return true;
}

bool AnimationController::setPriority(const std::string& name, int priority)
{
    AnimationState* state = findAnimationState(name);
    if (!state)
        return false;
    state->setPriority(priority);
    return true;
}

bool AnimationController::setStartBone(const std::string& name, const std::string& startBoneName)
{
    AnimationState* state = findAnimationState(name);
    if (!state)
        return false;
    Bone* bone = mModel->getSkeleton().getBone(startBoneName);
    state->setStartBone(bone);
    return true;
}

bool AnimationController::setBlending(const std::string& name, int priority, const std::string& startBoneName)
{
    AnimationState* state = findAnimationState(name);
    if (!state)
        return false;
    Bone* bone = mModel->getSkeleton().getBone(startBoneName);
    state->setPriority(priority);
    state->setStartBone(bone);
    return true;
}

bool AnimationController::setTime(const std::string& name, float time)
{
    AnimationState* state = findAnimationState(name);
    if (!state)
        return false;
    state->setTime(time);
    return true;
}

bool AnimationController::setGroup(const std::string& name, unsigned char group)
{
    unsigned index;
    AnimationState* state;
    findAnimation(name, index, state);
    if (index == M_MAX_UNSIGNED)
        return false;
    mAnimations[index].mGroup = group;
    return true;
}

bool AnimationController::setSpeed(const std::string& name, float speed)
{
    unsigned index;
    AnimationState* state;
    findAnimation(name, index, state);
    if (index == M_MAX_UNSIGNED)
        return false;
    mAnimations[index].mSpeed = speed;
    return true;
}

bool AnimationController::setWeight(const std::string& name, float weight)
{
    unsigned index;
    AnimationState* state;
    findAnimation(name, index, state);
    if ((index == M_MAX_UNSIGNED) || (!state))
        return false;
    state->setWeight(weight);
    // Stop any ongoing fade
    mAnimations[index].mFadeTime = 0.0f;
    return true;
}

bool AnimationController::setFade(const std::string& name, float targetWeight, float time)
{
    unsigned index;
    AnimationState* state;
    findAnimation(name, index, state);
    if (index == M_MAX_UNSIGNED)
        return false;
    mAnimations[index].mTargetWeight = clamp(targetWeight, 0.0f, 1.0f);
    mAnimations[index].mFadeTime = max(time, M_EPSILON);
    return true;
}

bool AnimationController::setFadeOthers(const std::string& name, float targetWeight, float time)
{
    unsigned index;
    AnimationState* state;
    findAnimation(name, index, state);
    if (index == M_MAX_UNSIGNED)
        return false;
    unsigned char group = mAnimations[index].mGroup;
    
    for (unsigned i = 0; i < mAnimations.size(); ++i)
    {
        AnimationControl& control = mAnimations[i];
        if ((control.mGroup == group) && (i != index))
        {
            control.mTargetWeight = clamp(targetWeight, 0.0f, 1.0f);
            control.mFadeTime = max(time, M_EPSILON);
        }
    }
    return true;
}

bool AnimationController::setLooped(const std::string& name, bool enable)
{
    AnimationState* state = findAnimationState(name);
    if (!state)
        return false;
    state->setLooped(enable);
    return true;
}

bool AnimationController::setAutoFade(const std::string& name, float time)
{
    unsigned index;
    AnimationState* state;
    findAnimation(name, index, state);
    if (index == M_MAX_UNSIGNED)
        return false;
    mAnimations[index].mAutoFadeTime = max(time, 0.0f);
    return true;
}

bool AnimationController::hasAnimation(const std::string& name) const
{
    unsigned index;
    AnimationState* state;
    findAnimation(name, index, state);
    return index != M_MAX_UNSIGNED;
}

int AnimationController::getPriority(const std::string& name) const
{
    AnimationState* state = findAnimationState(name);
    if (!state)
        return 0;
    return state->getPriority();
}

Bone* AnimationController::getStartBone(const std::string& name) const
{
    AnimationState* state = findAnimationState(name);
    if (!state)
        return 0;
    return state->getStartBone();
}

float AnimationController::getTime(const std::string& name) const
{
    AnimationState* state = findAnimationState(name);
    if (!state)
        return 0.0f;
    return state->getTime();
}

float AnimationController::getWeight(const std::string& name) const
{
    AnimationState* state = findAnimationState(name);
    if (!state)
        return 0.0f;
    return state->getWeight();
}

bool AnimationController::isLooped(const std::string& name) const
{
    AnimationState* state = findAnimationState(name);
    if (!state)
        return false;
    return state->isLooped();
}

float AnimationController::getLength(const std::string& name) const
{
    AnimationState* state = findAnimationState(name);
    if (!state)
        return 0.0f;
    return state->getLength();
}

unsigned char AnimationController::getGroup(const std::string& name) const
{
    unsigned index;
    AnimationState* state;
    findAnimation(name, index, state);
    if (index == M_MAX_UNSIGNED)
        return 0;
    return mAnimations[index].mGroup;
}

float AnimationController::getSpeed(const std::string& name) const
{
    unsigned index;
    AnimationState* state;
    findAnimation(name, index, state);
    if (index == M_MAX_UNSIGNED)
        return 0.0f;
    return mAnimations[index].mSpeed;
}

float AnimationController::getFadeTarget(const std::string& name) const
{
    unsigned index;
    AnimationState* state;
    findAnimation(name, index, state);
    if (index == M_MAX_UNSIGNED)
        return 0.0f;
    return mAnimations[index].mTargetWeight;
}

float AnimationController::getFadeTime(const std::string& name) const
{
    unsigned index;
    AnimationState* state;
    findAnimation(name, index, state);
    if (index == M_MAX_UNSIGNED)
        return 0.0f;
    return mAnimations[index].mTargetWeight;
}

float AnimationController::getAutoFade(const std::string& name) const
{
    unsigned index;
    AnimationState* state;
    findAnimation(name, index, state);
    if (index == M_MAX_UNSIGNED)
        return 0.0f;
    return mAnimations[index].mAutoFadeTime;
}

void AnimationController::findAnimation(const std::string& name, unsigned& index, AnimationState*& state) const
{
    StringHash nameHash(name);
    
    // Find the AnimationState
    state = mModel ? mModel->getAnimationState(nameHash) : 0;
    if (state)
    {
        // Either a resource name or animation name may be specified. We store resource names, so correct the hash if necessary
        nameHash = state->getAnimation()->getNameHash();
    }
    
    // Find the internal control structure
    index = M_MAX_UNSIGNED;
    for (unsigned i = 0; i < mAnimations.size(); ++i)
    {
        if (mAnimations[i].mHash == nameHash)
        {
            index = i;
            break;
        }
    }
}

AnimationState* AnimationController::findAnimationState(const std::string& name) const
{
    StringHash nameHash(name);
    return mModel ? mModel->getAnimationState(nameHash) : 0;
}

void AnimationController::handleScenePostUpdate(StringHash eventType, VariantMap& eventData)
{
    using namespace ScenePostUpdate;
    
    // Check that the scene matches
    Scene* scene = mEntity ? mEntity->getScene() : 0;
    if (eventData[P_SCENE].getPtr() == (void*)scene)
        update(eventData[P_TIMESTEP].getFloat());
}

