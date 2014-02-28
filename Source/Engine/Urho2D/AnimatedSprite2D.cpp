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

#include "Precompiled.h"
#include "Animation2D.h"
#include "AnimatedSprite2D.h"
#include "Context.h"
#include "SceneEvents.h"
#include "Sprite2D.h"
#include "Scene.h"
#include "Texture2D.h"

#include "DebugNew.h"

namespace Urho3D
{

extern const char* URHO2D_CATEGORY;

const char* cycleModeNames[] = 
{
    "Loop",
    "Clamp",
    "Pingpong",
    0
};

template<> CycleMode Variant::Get<CycleMode>() const
{
    return (CycleMode)GetInt();
}

AnimatedSprite2D::AnimatedSprite2D(Context* context) : StaticSprite2D(context),
    speed_(1.0f), 
    cycleMode_(CM_LOOP),
    animationTime_(0.0f), 
    animationTotalTime_(1.0f)
{
}

AnimatedSprite2D::~AnimatedSprite2D()
{
}

void AnimatedSprite2D::RegisterObject(Context* context)
{
    context->RegisterFactory<AnimatedSprite2D>(URHO2D_CATEGORY);
    ACCESSOR_ATTRIBUTE(AnimatedSprite2D, VAR_FLOAT, "Speed", GetSpeed, SetSpeed, float, 1.0f, AM_DEFAULT);
    ENUM_ACCESSOR_ATTRIBUTE(AnimatedSprite2D, "Cycle Mode", GetCycleMode, SetCycleMode, CycleMode, cycleModeNames, 0, AM_FILE);
    COPY_BASE_ATTRIBUTES(AnimatedSprite2D, StaticSprite2D);
}

void AnimatedSprite2D::OnSetEnabled()
{
    StaticSprite2D::OnSetEnabled();

    Scene* scene = GetScene();
    if (scene)
    {
        if (IsEnabledEffective())
            SubscribeToEvent(scene, E_SCENEPOSTUPDATE, HANDLER(AnimatedSprite2D, HandleScenePostUpdate));
        else
            UnsubscribeFromEvent(scene, E_SCENEPOSTUPDATE);
    }
}

void AnimatedSprite2D::SetSpeed(float speed)
{
    speed_ = speed;
}

void AnimatedSprite2D::SetCycleMode(CycleMode cycleMode)
{
    cycleMode_ = cycleMode;
}

void AnimatedSprite2D::SetAnimation(Animation2D* animation, float startTime)
{
    animationTime_ = startTime;

    if (animation_ == animation)
        return;

    if (animation_)
        SetSprite(0);

    animation_ = animation;

    if (animation_)
    {
        const KeyFrame2D* keyFrame = animation_->GetKeyFrameByIndex(0);
        if (keyFrame)
            SetSprite(keyFrame->sprite_);

        animationTotalTime_ = animation_->GetTotalTime();
    }
}

Animation2D* AnimatedSprite2D::GetAnimation() const
{
    return animation_;
}

void AnimatedSprite2D::OnNodeSet(Node* node)
{
    StaticSprite2D::OnNodeSet(node);

    if (node)
    {
        Scene* scene = GetScene();
        if (scene && IsEnabledEffective())
            SubscribeToEvent(scene, E_SCENEPOSTUPDATE, HANDLER(AnimatedSprite2D, HandleScenePostUpdate));
    }
}

void AnimatedSprite2D::HandleScenePostUpdate(StringHash eventType, VariantMap& eventData)
{
    using namespace ScenePostUpdate;
    float timeStep = eventData[P_TIMESTEP].GetFloat();
    animationTime_ += timeStep * speed_;

    if (!animation_)
        return;

    float time;

    switch (cycleMode_)
    {
    case CM_LOOP:
        time = fmodf(animationTime_, animationTotalTime_);
        break;

    case CM_CLAMP:
        time = Clamp(animationTime_, 0.0f, animationTotalTime_);
        break;

    case CM_PINGPONG:
        {
            float doubleTotalTime = animationTotalTime_ * 2.0f;
            float fract = fmodf(animationTime_, doubleTotalTime);
            time = (fract < animationTotalTime_) ? fract : doubleTotalTime - fract;
        }
        break;
    }

    const KeyFrame2D* keyFrame = animation_->GetKeyFrameByTime(time);
    if (GetSprite() != keyFrame->sprite_)
        SetSprite(keyFrame->sprite_);

    MarkForUpdate();
}

}