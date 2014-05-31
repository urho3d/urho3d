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
#include "Context.h"
#include "Scene.h"
#include "SceneEvents.h"
#include "Sprite2D.h"
#include "StaticSprite2D.h"
#include "XAnimatedSprite2D.h"
#include "XAnimation2D.h"
#include "XAnimationSet2D.h"

#include "DebugNew.h"

namespace Urho3D
{

extern const char* URHO2D_CATEGORY;

XAnimatedSprite2D::XAnimatedSprite2D(Context* context) :
    Drawable2D(context),
    speed_(1.0f),
    animationTime_(0.0f)
{
}

XAnimatedSprite2D::~XAnimatedSprite2D()
{
}

void XAnimatedSprite2D::RegisterObject(Context* context)
{
    context->RegisterFactory<XAnimatedSprite2D>(URHO2D_CATEGORY);
    ACCESSOR_ATTRIBUTE(XAnimatedSprite2D, VAR_FLOAT, "Speed", GetSpeed, SetSpeed, float, 1.0f, AM_DEFAULT);
}

void XAnimatedSprite2D::OnSetEnabled()
{
    Drawable2D::OnSetEnabled();

    Scene* scene = GetScene();
    if (scene)
    {
        if (IsEnabledEffective())
            SubscribeToEvent(scene, E_SCENEPOSTUPDATE, HANDLER(XAnimatedSprite2D, HandleScenePostUpdate));
        else
            UnsubscribeFromEvent(scene, E_SCENEPOSTUPDATE);
    }
}

void XAnimatedSprite2D::SetLayer(int layer)
{
    Drawable2D::SetLayer(layer);
    for (unsigned i = 0; i < objectNodes_.Size(); ++i)
    {
        StaticSprite2D* objectSprite = objectNodes_[i]->GetComponent<StaticSprite2D>();
        objectSprite->SetLayer(layer);
    }
}

void XAnimatedSprite2D::SetSpeed(float speed)
{
    speed_ = speed;
    MarkNetworkUpdate();
}

void XAnimatedSprite2D::SetAnimation(XAnimationSet2D* animationSet, const String& name)
{
    SetAnimation(animationSet->GetAnimation(name));
}

void XAnimatedSprite2D::SetAnimation(XAnimation2D* animation)
{
    if (animation == animation_)
    {
        // Reset time
        animationTime_ = 0.0f;
        return;
    }

    if (animation_)
    {
        // Remove all object nodes
        for (unsigned i = 0; i < objectNodes_.Size(); ++i)
            objectNodes_[i]->Remove();
        objectNodes_.Clear();
    }

    animation_ = animation;
    
    if (!animation_)
        return;

    animationTime_ = 0.0f;
    
    for (unsigned i = 0; i < animation_->GetTimelines().Size(); ++i)
    {
        SharedPtr<Node> objectNode(GetNode()->CreateChild(animation_->GetTimelines()[i].name_));

        StaticSprite2D* staticSprite = objectNode->CreateComponent<StaticSprite2D>();
        staticSprite->SetLayer(GetLayer());
        staticSprite->SetUseHotSpot(true);
        staticSprite->SetBlendMode(BLEND_ALPHA);

        objectNodes_.Push(objectNode);        
    }

    UpdateAnimation(0.0f);

    UpdateDefaultMaterial();
    MarkNetworkUpdate();
}

void XAnimatedSprite2D::SetAnimation(const String& name)
{
    if (!animation_)
        return;

    XAnimationSet2D* animationSet = animation_->GetAnimationSet();
    if (!animationSet)
        return;

    SetAnimation(animationSet->GetAnimation(name));
}

XAnimation2D* XAnimatedSprite2D::GetAnimation() const
{
    return animation_;
}

void XAnimatedSprite2D::OnNodeSet(Node* node)
{
    Drawable2D::OnNodeSet(node);

    if (node)
    {
        Scene* scene = GetScene();
        if (scene && IsEnabledEffective())
            SubscribeToEvent(scene, E_SCENEPOSTUPDATE, HANDLER(XAnimatedSprite2D, HandleScenePostUpdate));
    }
}

void XAnimatedSprite2D::OnWorldBoundingBoxUpdate()
{
    boundingBox_.Clear();
    worldBoundingBox_.Clear();

    for (unsigned i = 0; i < objectNodes_.Size(); ++i)
    {
        StaticSprite2D* ss = objectNodes_[i]->GetComponent<StaticSprite2D>();
        worldBoundingBox_.Merge(ss->GetWorldBoundingBox());
    }

    boundingBox_ = worldBoundingBox_.Transformed(node_->GetWorldTransform().Inverse());
}

void XAnimatedSprite2D::UpdateVertices()
{
}

void XAnimatedSprite2D::HandleScenePostUpdate(StringHash eventType, VariantMap& eventData)
{
    using namespace ScenePostUpdate;
    float timeStep = eventData[P_TIMESTEP].GetFloat();
    UpdateAnimation(timeStep);
}

void XAnimatedSprite2D::UpdateAnimation(float timeStep)
{
    if (!animation_)
        return;
    
    animationTime_ += timeStep * speed_;

    float animtationLength = animation_->GetLength();
    float time;

    if (animation_->IsLooped())
    {
        time = fmodf(animationTime_, animtationLength);
        if (time < 0.0f)
            time += animation_->GetLength();
    }
    else
        time = Clamp(animationTime_, 0.0f, animtationLength);

    const Vector<MainlineKey>& mainlineKeys = animation_->GetMainlineKeys();
    const MainlineKey* mainlineKey = 0;
    for (unsigned i = 1; i < mainlineKeys.Size(); ++i)
    {
        if (time < mainlineKeys[i].time_)
        {
            mainlineKey = &mainlineKeys[i - 1];
            break;
        }
    }

    if (!mainlineKey)
        mainlineKey = &mainlineKeys.Back();

    const Vector<Timeline>& timelines = animation_->GetTimelines();
    for (unsigned i = 0; i < timelines.Size(); ++i)
    {
        Node* objectNode = objectNodes_[i];

        const ObjectRef* objectRef = mainlineKey->GetObjectRef(i);
        if (!objectRef)
            objectNode->SetEnabled(false);
        else
        {
            objectNode->SetEnabled(true);

            StaticSprite2D* staticSprite = objectNode->GetComponent<StaticSprite2D>();
            staticSprite->SetOrderInLayer(objectRef->zIndex_);

            const Vector<ObjectKey>& objectKeys = timelines[i].objectKeys_;
            for (unsigned j = 0; j < objectKeys.Size() - 1; ++j)
            {
                if (time <= objectKeys[j + 1].time_)
                {
                    const ObjectKey& currKey = objectKeys[j];
                    const ObjectKey& nextKey = objectKeys[j + 1];

                    float t = (time - currKey.time_)  / (nextKey.time_ - currKey.time_);
                    if (t < 0.0f || t > 1.0f)
                    {
                        t = 0;
                    }
                    objectNode->SetPosition(currKey.position_.Lerp(nextKey.position_, t));

                    float angle;
                    if (currKey.spin_ > 0 && currKey.angle_ > nextKey.angle_)
                        angle = Lerp(currKey.angle_, nextKey.angle_ + 360.0f, t);
                    else if (currKey.spin_ < 0 && currKey.angle_ < nextKey.angle_)
                        angle = Lerp(currKey.angle_, nextKey.angle_ - 360.0f, t);
                    else
                        angle = Lerp(currKey.angle_, nextKey.angle_, t);
                    objectNode->SetRotation(angle);

                    objectNode->SetScale(currKey.scale_.Lerp(nextKey.scale_, t));

                    staticSprite->SetSprite(currKey.sprite_);
                    staticSprite->SetHotSpot(currKey.pivot_.Lerp(nextKey.pivot_, t));
                    float alpha_ = Lerp(currKey.alpha_, nextKey.alpha_, t);
                    staticSprite->SetColor(Color(1.0f, 1.0f, 1.0f, alpha_));

                    break;
                }
            }
        }       
    }

    MarkForUpdate();
}

}

