//
// Copyright (c) 2008-2013 the Urho3D project.
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
#include "Context.h"
#include "Log.h"
#include "MemoryBuffer.h"
#include "Profiler.h"
#include "ResourceCache.h"
#include "Scene.h"
#include "SceneEvents.h"

#include "DebugNew.h"

namespace Urho3D
{

static const unsigned char CTRL_LOOPED = 0x1;
static const unsigned char CTRL_STARTBONE = 0x2;
static const unsigned char CTRL_AUTOFADE = 0x4;
static const unsigned char CTRL_SETTIME = 0x08;
static const unsigned char CTRL_SETWEIGHT = 0x10;
static const float EXTRA_ANIM_FADEOUT_TIME = 0.1f;
static const float COMMAND_STAY_TIME = 0.25f;

extern const char* ANIMATION_CATEGORY;

OBJECTTYPESTATIC(AnimationController);

AnimationController::AnimationController(Context* context) :
    Component(context)
{
}

AnimationController::~AnimationController()
{
}

void AnimationController::RegisterObject(Context* context)
{
    context->RegisterFactory<AnimationController>(ANIMATION_CATEGORY);
    
    ACCESSOR_ATTRIBUTE(AnimationController, VAR_BOOL, "Is Enabled", IsEnabled, SetEnabled, bool, true, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(AnimationController, VAR_VARIANTVECTOR, "Animations", GetAnimationsAttr, SetAnimationsAttr, VariantVector, Variant::emptyVariantVector, AM_FILE | AM_NOEDIT);
    REF_ACCESSOR_ATTRIBUTE(AnimationController, VAR_BUFFER, "Network Animations", GetNetAnimationsAttr, SetNetAnimationsAttr, PODVector<unsigned char>, Variant::emptyBuffer, AM_NET | AM_LATESTDATA | AM_NOEDIT);
}

void AnimationController::OnSetEnabled()
{
    Scene* scene = GetScene();
    if (scene)
    {
        if (IsEnabledEffective())
            SubscribeToEvent(scene, E_SCENEPOSTUPDATE, HANDLER(AnimationController, HandleScenePostUpdate));
        else
            UnsubscribeFromEvent(scene, E_SCENEPOSTUPDATE);
    }
}

void AnimationController::Update(float timeStep)
{
    AnimatedModel* model = GetComponent<AnimatedModel>();
    if (!model)
        return;
    
    // Loop through animations
    for (Vector<AnimationControl>::Iterator i = animations_.Begin(); i != animations_.End();)
    {
        bool remove = false;
        AnimationState* state = model->GetAnimationState(i->hash_);
        if (!state)
            remove = true;
        else
        {
            // Advance the animation
            if (i->speed_ != 0.0f)
                state->AddTime(i->speed_ * timeStep);
            
            float targetWeight = i->targetWeight_;
            float fadeTime = i->fadeTime_;
            
            // If non-looped animation at the end, activate autofade as applicable
            if (!state->IsLooped() && state->GetTime() >= state->GetLength() && i->autoFadeTime_ > 0.0f)
            {
                targetWeight = 0.0f;
                fadeTime = i->autoFadeTime_;
            }
            
            // Process weight fade
            float currentWeight = state->GetWeight();
            if (currentWeight != targetWeight)
            {
                if (fadeTime > 0.0f)
                {
                    float weightDelta = 1.0f / fadeTime * timeStep;
                    if (currentWeight < targetWeight)
                        currentWeight = Min(currentWeight + weightDelta, targetWeight);
                    else if (currentWeight > targetWeight)
                        currentWeight = Max(currentWeight - weightDelta, targetWeight);
                    state->SetWeight(currentWeight);
                }
                else
                    state->SetWeight(targetWeight);
            }
            
            // Remove if weight zero and target weight zero
            if (state->GetWeight() == 0.0f && (targetWeight == 0.0f || fadeTime == 0.0f))
                remove = true;
        }
        
        // Decrement the command time-to-live values
        if (i->setTimeTtl_ > 0.0f)
            i->setTimeTtl_ = Max(i->setTimeTtl_ - timeStep, 0.0f);
        if (i->setWeightTtl_ > 0.0f)
            i->setWeightTtl_ = Max(i->setWeightTtl_ - timeStep, 0.0f);
        
        if (remove)
        {
            if (state)
                model->RemoveAnimationState(state);
            i = animations_.Erase(i);
            MarkNetworkUpdate();
        }
        else
            ++i;
    }
}

bool AnimationController::Play(const String& name, unsigned char layer, bool looped, float fadeInTime)
{
    AnimatedModel* model = GetComponent<AnimatedModel>();
    if (!model)
        return false;
    
    // Check if already exists
    unsigned index;
    AnimationState* state;
    FindAnimation(name, index, state);
    
    if (!state)
    {
        Animation* newAnimation = GetSubsystem<ResourceCache>()->GetResource<Animation>(name);
        state = model->AddAnimationState(newAnimation);
        if (!state)
            return false;
    }
    
    if (index == M_MAX_UNSIGNED)
    {
        AnimationControl newControl;
        Animation* animation = state->GetAnimation();
        newControl.hash_ = animation->GetNameHash();
        animations_.Push(newControl);
        index = animations_.Size() - 1;
    }
    
    state->SetLayer(layer);
    state->SetLooped(looped);
    animations_[index].targetWeight_ = 1.0f;
    animations_[index].fadeTime_ = fadeInTime;
    
    MarkNetworkUpdate();
    return true;
}

bool AnimationController::PlayExclusive(const String& name, unsigned char layer, bool looped, float fadeTime)
{
    FadeOthers(name, 0.0f, fadeTime);
    return Play(name, layer, looped, fadeTime);
}

bool AnimationController::Stop(const String& name, float fadeOutTime)
{
    AnimatedModel* model = GetComponent<AnimatedModel>();
    if (!model)
        return false;
    
    unsigned index;
    AnimationState* state;
    FindAnimation(name, index, state);
    if (index != M_MAX_UNSIGNED)
    {
        animations_[index].targetWeight_ = 0.0f;
        animations_[index].fadeTime_ = fadeOutTime;
        MarkNetworkUpdate();
    }
    
    return index != M_MAX_UNSIGNED || state != 0;
}

void AnimationController::StopLayer(unsigned char layer, float fadeOutTime)
{
    AnimatedModel* model = GetComponent<AnimatedModel>();
    if (!model)
        return;
    
    bool needUpdate = false;
    for (Vector<AnimationControl>::Iterator i = animations_.Begin(); i != animations_.End(); ++i)
    {
        AnimationState* state = model->GetAnimationState(i->hash_);
        if (state && state->GetLayer() == layer)
        {
            i->targetWeight_ = 0.0f;
            i->fadeTime_ = fadeOutTime;
            needUpdate = true;
        }
    }
    
    if (needUpdate)
        MarkNetworkUpdate();
}

void AnimationController::StopAll(float fadeOutTime)
{
    AnimatedModel* model = GetComponent<AnimatedModel>();
    if (!model)
        return;
    
    if (animations_.Size())
    {
        for (Vector<AnimationControl>::Iterator i = animations_.Begin(); i != animations_.End(); ++i)
        {
            i->targetWeight_ = 0.0f;
            i->fadeTime_ = fadeOutTime;
        }
        
        MarkNetworkUpdate();
    }
}

bool AnimationController::Fade(const String& name, float targetWeight, float fadeTime)
{
    unsigned index;
    AnimationState* state;
    FindAnimation(name, index, state);
    if (index == M_MAX_UNSIGNED)
        return false;
    
    animations_[index].targetWeight_ = Clamp(targetWeight, 0.0f, 1.0f);
    animations_[index].fadeTime_ = fadeTime;
    MarkNetworkUpdate();
    return true;
}

bool AnimationController::FadeOthers(const String& name, float targetWeight, float fadeTime)
{
    unsigned index;
    AnimationState* state;
    FindAnimation(name, index, state);
    if (index == M_MAX_UNSIGNED || !state)
        return false;
    
    AnimatedModel* model = GetComponent<AnimatedModel>();
    unsigned char layer = state->GetLayer();
    
    bool needUpdate = false;
    for (unsigned i = 0; i < animations_.Size(); ++i)
    {
        if (i != index)
        {
            AnimationControl& control = animations_[i];
            AnimationState* otherState = model->GetAnimationState(control.hash_);
            if (otherState && otherState->GetLayer() == layer)
            {
                control.targetWeight_ = Clamp(targetWeight, 0.0f, 1.0f);
                control.fadeTime_ = fadeTime;
                needUpdate = true;
            }
        }
    }
    
    if (needUpdate)
        MarkNetworkUpdate();
    return true;
}

bool AnimationController::SetLayer(const String& name, unsigned char layer)
{
    AnimationState* state = FindAnimationState(name);
    if (!state)
        return false;
    
    state->SetLayer(layer);
    MarkNetworkUpdate();
    return true;
}

bool AnimationController::SetStartBone(const String& name, const String& startBoneName)
{
    AnimationState* state = FindAnimationState(name);
    if (!state)
        return false;
    
    AnimatedModel* model = GetComponent<AnimatedModel>();
    Bone* bone = model->GetSkeleton().GetBone(startBoneName);
    state->SetStartBone(bone);
    MarkNetworkUpdate();
    return true;
}

bool AnimationController::SetTime(const String& name, float time)
{
    unsigned index;
    AnimationState* state;
    FindAnimation(name, index, state);
    if (index == M_MAX_UNSIGNED || !state)
        return false;
    
    time = Clamp(time, 0.0f, state->GetLength());
    state->SetTime(time);
    // Prepare "set time" command for network replication
    animations_[index].setTime_ = (unsigned short)(time / state->GetLength() * 65535.0f);
    animations_[index].setTimeTtl_ = COMMAND_STAY_TIME;
    ++animations_[index].setTimeRev_;
    MarkNetworkUpdate();
    return true;
}

bool AnimationController::SetSpeed(const String& name, float speed)
{
    unsigned index;
    AnimationState* state;
    FindAnimation(name, index, state);
    if (index == M_MAX_UNSIGNED)
        return false;
    
    animations_[index].speed_ = speed;
    MarkNetworkUpdate();
    return true;
}

bool AnimationController::SetWeight(const String& name, float weight)
{
    unsigned index;
    AnimationState* state;
    FindAnimation(name, index, state);
    if (index == M_MAX_UNSIGNED || !state)
        return false;
    
    weight = Clamp(weight, 0.0f, 1.0f);
    state->SetWeight(weight);
    // Prepare "set weight" command for network replication
    animations_[index].setWeight_ = (unsigned char)(weight * 255.0f);
    animations_[index].setWeightTtl_ = COMMAND_STAY_TIME;
    ++animations_[index].setWeightRev_;
    MarkNetworkUpdate();
    return true;
}

bool AnimationController::SetLooped(const String& name, bool enable)
{
    AnimationState* state = FindAnimationState(name);
    if (!state)
        return false;
    
    state->SetLooped(enable);
    MarkNetworkUpdate();
    return true;
}

bool AnimationController::SetAutoFade(const String& name, float fadeOutTime)
{
    unsigned index;
    AnimationState* state;
    FindAnimation(name, index, state);
    if (index == M_MAX_UNSIGNED)
        return false;
    
    animations_[index].autoFadeTime_ = Max(fadeOutTime, 0.0f);
    MarkNetworkUpdate();
    return true;
}

bool AnimationController::IsPlaying(const String& name) const
{
    unsigned index;
    AnimationState* state;
    FindAnimation(name, index, state);
    return index != M_MAX_UNSIGNED;
}

bool AnimationController::IsFadingIn(const String& name) const
{
    unsigned index;
    AnimationState* state;
    FindAnimation(name, index, state);
    if (index == M_MAX_UNSIGNED || !state)
        return false;
    
    return animations_[index].fadeTime_ && animations_[index].targetWeight_ > state->GetWeight();
}

bool AnimationController::IsFadingOut(const String& name) const
{
    unsigned index;
    AnimationState* state;
    FindAnimation(name, index, state);
    if (index == M_MAX_UNSIGNED || !state)
        return false;
    
    return (animations_[index].fadeTime_ && animations_[index].targetWeight_ < state->GetWeight())
        || (!state->IsLooped() && state->GetTime() >= state->GetLength() && animations_[index].autoFadeTime_);
}

unsigned char AnimationController::GetLayer(const String& name) const
{
    AnimationState* state = FindAnimationState(name);
    return state ? state->GetLayer() : 0;
}

Bone* AnimationController::GetStartBone(const String& name) const
{
    AnimationState* state = FindAnimationState(name);
    return state ? state->GetStartBone() : 0;
}

const String& AnimationController::GetStartBoneName(const String& name) const
{
    Bone* bone = GetStartBone(name);
    return bone ? bone->name_ : String::EMPTY;
}

float AnimationController::GetTime(const String& name) const
{
    AnimationState* state = FindAnimationState(name);
    return state ? state->GetTime() : 0.0f;
}

float AnimationController::GetWeight(const String& name) const
{
    AnimationState* state = FindAnimationState(name);
    return state ? state->GetWeight() : 0.0f;
}

bool AnimationController::IsLooped(const String& name) const
{
    AnimationState* state = FindAnimationState(name);
    return state ? state->IsLooped() : false;
}

float AnimationController::GetLength(const String& name) const
{
    AnimationState* state = FindAnimationState(name);
    return state ? state->GetLength() : 0.0f;
}

float AnimationController::GetSpeed(const String& name) const
{
    unsigned index;
    AnimationState* state;
    FindAnimation(name, index, state);
    return index != M_MAX_UNSIGNED ? animations_[index].speed_ : 0.0f;
}

float AnimationController::GetFadeTarget(const String& name) const
{
    unsigned index;
    AnimationState* state;
    FindAnimation(name, index, state);
    return index != M_MAX_UNSIGNED ? animations_[index].targetWeight_ : 0.0f;
}

float AnimationController::GetFadeTime(const String& name) const
{
    unsigned index;
    AnimationState* state;
    FindAnimation(name, index, state);
    return index != M_MAX_UNSIGNED ? animations_[index].targetWeight_ : 0.0f;
}

float AnimationController::GetAutoFade(const String& name) const
{
    unsigned index;
    AnimationState* state;
    FindAnimation(name, index, state);
    return index != M_MAX_UNSIGNED ? animations_[index].autoFadeTime_ : 0.0f;
}

void AnimationController::SetAnimationsAttr(VariantVector value)
{
    animations_.Clear();
    animations_.Reserve(value.Size() / 5);  // Incomplete data is discarded
    unsigned index = 0;
    while (index + 4 < value.Size())    // Prevent out-of-bound index access
    {
        AnimationControl newControl;
        newControl.hash_ = value[index++].GetStringHash();
        newControl.speed_ = value[index++].GetFloat();
        newControl.targetWeight_ = value[index++].GetFloat();
        newControl.fadeTime_ = value[index++].GetFloat();
        newControl.autoFadeTime_ = value[index++].GetFloat();
        animations_.Push(newControl);
    }
}

void AnimationController::SetNetAnimationsAttr(const PODVector<unsigned char>& value)
{
    // To apply animations, the model must exist first (practically, have been added before AnimationController)
    AnimatedModel* model = GetComponent<AnimatedModel>();
    if (!model)
        return;
    
    MemoryBuffer buf(value);
    
    // Check which animations we need to remove
    HashSet<StringHash> processedAnimations;
    
    unsigned numAnimations = buf.ReadVLE();
    while (numAnimations--)
    {
        StringHash animHash = buf.ReadStringHash();
        processedAnimations.Insert(animHash);
        
        // Check if the animation state exists. If not, add new
        AnimationState* state = model->GetAnimationState(animHash);
        if (!state)
        {
            Animation* newAnimation = GetSubsystem<ResourceCache>()->GetResource<Animation>(animHash);
            state = model->AddAnimationState(newAnimation);
            if (!state)
            {
                LOGERROR("Animation update applying aborted due to unknown animation");
                return;
            }
        }
        // Check if the internal control structure exists. If not, add new
        unsigned index;
        for (index = 0; index < animations_.Size(); ++index)
        {
            if (animations_[index].hash_ == animHash)
                break;
        }
        if (index == animations_.Size())
        {
            AnimationControl newControl;
            newControl.hash_ = animHash;
            animations_.Push(newControl);
        }
        
        unsigned char ctrl = buf.ReadUByte();
        state->SetLayer(buf.ReadUByte());
        state->SetLooped((ctrl & CTRL_LOOPED) != 0);
        animations_[index].speed_ = (float)buf.ReadShort() / 2048.0f; // 11 bits of decimal precision, max. 16x playback speed
        animations_[index].targetWeight_ = (float)buf.ReadUByte() / 255.0f; // 8 bits of decimal precision
        animations_[index].fadeTime_ = (float)buf.ReadUByte() / 64.0f; // 6 bits of decimal precision, max. 4 seconds fade
        if (ctrl & CTRL_STARTBONE)
            state->SetStartBone(model->GetSkeleton().GetBone(buf.ReadStringHash()));
        else
            state->SetStartBone(0);
        if (ctrl & CTRL_AUTOFADE)
            animations_[index].autoFadeTime_ = (float)buf.ReadUByte() / 64.0f; // 6 bits of decimal precision, max. 4 seconds fade
        else
            animations_[index].autoFadeTime_ = 0.0f;
        if (ctrl & CTRL_SETTIME)
        {
            unsigned char setTimeRev = buf.ReadUByte();
            unsigned short setTime = buf.ReadUShort();
            // Apply set time command only if revision differs
            if (setTimeRev != animations_[index].setTimeRev_)
            {
                state->SetTime(((float)setTime / 65535.0f) * state->GetLength());
                animations_[index].setTimeRev_ = setTimeRev;
            }
        }
        if (ctrl & CTRL_SETWEIGHT)
        {
            unsigned char setWeightRev = buf.ReadUByte();
            unsigned char setWeight = buf.ReadUByte();
            // Apply set weight command only if revision differs
            if (setWeightRev != animations_[index].setWeightRev_)
            {
                state->SetWeight((float)setWeight / 255.0f);
                animations_[index].setWeightRev_ = setWeightRev;
            }
        }
    }
    
    // Set any extra animations to fade out
    for (Vector<AnimationControl>::Iterator i = animations_.Begin(); i != animations_.End(); ++i)
    {
        if (!processedAnimations.Contains(i->hash_))
        {
            i->targetWeight_ = 0.0f;
            i->fadeTime_ = EXTRA_ANIM_FADEOUT_TIME;
        }
    }
}

VariantVector AnimationController::GetAnimationsAttr() const
{
    VariantVector ret;
    ret.Reserve(animations_.Size() * 5);
    for (Vector<AnimationControl>::ConstIterator i = animations_.Begin(); i != animations_.End(); ++i)
    {
        ret.Push(i->hash_);
        ret.Push(i->speed_);
        ret.Push(i->targetWeight_);
        ret.Push(i->fadeTime_);
        ret.Push(i->autoFadeTime_);
    }
    return ret;
}

const PODVector<unsigned char>& AnimationController::GetNetAnimationsAttr() const
{
    attrBuffer_.Clear();
    
    AnimatedModel* model = GetComponent<AnimatedModel>();
    if (!model)
    {
        attrBuffer_.WriteVLE(0);
        return attrBuffer_.GetBuffer();
    }
    
    unsigned validAnimations = 0;
    for (Vector<AnimationControl>::ConstIterator i = animations_.Begin(); i != animations_.End(); ++i)
    {
        if (model->GetAnimationState(i->hash_))
            ++validAnimations;
    }
    
    attrBuffer_.WriteVLE(validAnimations);
    for (Vector<AnimationControl>::ConstIterator i = animations_.Begin(); i != animations_.End(); ++i)
    {
        AnimationState* state = model->GetAnimationState(i->hash_);
        if (!state)
            continue;
        
        unsigned char ctrl = 0;
        Bone* startBone = state->GetStartBone();
        if (state->IsLooped())
            ctrl |= CTRL_LOOPED;
        if (startBone && startBone != model->GetSkeleton().GetRootBone())
            ctrl |= CTRL_STARTBONE;
        if (i->autoFadeTime_ > 0.0f)
            ctrl |= CTRL_AUTOFADE;
        if (i->setTimeTtl_ > 0.0f)
            ctrl |= CTRL_SETTIME;
        if (i->setWeightTtl_ > 0.0f)
            ctrl |= CTRL_SETWEIGHT;
        
        attrBuffer_.WriteStringHash(i->hash_);
        attrBuffer_.WriteUByte(ctrl);
        attrBuffer_.WriteUByte(state->GetLayer());
        attrBuffer_.WriteShort((short)Clamp(i->speed_ * 2048.0f, -32767.0f, 32767.0f));
        attrBuffer_.WriteUByte((unsigned char)(i->targetWeight_ * 255.0f));
        attrBuffer_.WriteUByte((unsigned char)Clamp(i->fadeTime_ * 64.0f, 0.0f, 255.0f));
        if (ctrl & CTRL_STARTBONE)
            attrBuffer_.WriteStringHash(startBone->nameHash_);
        if (ctrl & CTRL_AUTOFADE)
            attrBuffer_.WriteUByte((unsigned char)Clamp(i->autoFadeTime_ * 64.0f, 0.0f, 255.0f));
        if (ctrl & CTRL_SETTIME)
        {
            attrBuffer_.WriteUByte(i->setTimeRev_);
            attrBuffer_.WriteUShort(i->setTime_);
        }
        if (ctrl & CTRL_SETWEIGHT)
        {
            attrBuffer_.WriteUByte(i->setWeightRev_);
            attrBuffer_.WriteUByte(i->setWeight_);
        }
    }
    
    return attrBuffer_.GetBuffer();
}

void AnimationController::OnNodeSet(Node* node)
{
    if (node)
    {
        Scene* scene = GetScene();
        if (scene && IsEnabledEffective())
            SubscribeToEvent(scene, E_SCENEPOSTUPDATE, HANDLER(AnimationController, HandleScenePostUpdate));
    }
}

void AnimationController::FindAnimation(const String& name, unsigned& index, AnimationState*& state) const
{
    AnimatedModel* model = GetComponent<AnimatedModel>();
    StringHash nameHash(name);
    
    // Find the AnimationState
    state = model ? model->GetAnimationState(nameHash) : 0;
    if (state)
    {
        // Either a resource name or animation name may be specified. We store resource names, so correct the hash if necessary
        nameHash = state->GetAnimation()->GetNameHash();
    }
    
    // Find the internal control structure
    index = M_MAX_UNSIGNED;
    for (unsigned i = 0; i < animations_.Size(); ++i)
    {
        if (animations_[i].hash_ == nameHash)
        {
            index = i;
            break;
        }
    }
}

AnimationState* AnimationController::FindAnimationState(const String& name) const
{
    AnimatedModel* model = GetComponent<AnimatedModel>();
    return model ? model->GetAnimationState(StringHash(name)) : 0;
}

void AnimationController::HandleScenePostUpdate(StringHash eventType, VariantMap& eventData)
{
    using namespace ScenePostUpdate;
    
    Update(eventData[P_TIMESTEP].GetFloat());
}

}
