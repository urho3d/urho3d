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

#include <Urho3D/Urho3D.h>

#include <Urho3D/Core/Context.h>
#include <Urho3D/Resource/ResourceCache.h>

#include <Urho3D/Scene/Scene.h>
#include <Urho3D/Scene/SceneEvents.h>

#include <Urho3D/Graphics/AnimatedModel.h>
#include <Urho3D/Graphics/Animation.h>
#include <Urho3D/Graphics/AnimationState.h>
#include <Urho3D/Graphics/DebugRenderer.h>

#include "RootMotionComputer.h"

#include <Urho3D/DebugNew.h>

/*
 * Obtain the position of t projected onto rootNode's zx plane
 * */
inline Vector3 GetProjectedPosition(Node* r, Node* t)
{
    Vector3 p = r->GetWorldTransform().Inverse() * t->GetWorldPosition();
    p.y_ = 0;
    return p;
}

/*
 * Obtain the projection of axis on t onto rootNode's zx plane
 * */
inline Vector3 GetProjectedAxis(Node* r, Node* t, Vector3 axis)
{
    Quaternion invQ = r->GetWorldRotation().Inverse();
    Vector3 dir = t->GetWorldRotation() * axis;
    Vector3 p =  invQ * dir;
    p.y_ = 0;
    return p;
}

RootMotionComputer::RootMotionComputer(Context* context) :
    LogicComponent(context),
    debugGizmoSize(0.25f)
{
    // Only the scene update event is needed: unsubscribe from the rest for optimization
    SetUpdateEventMask(USE_UPDATE);
}

void RootMotionComputer::Update(float timeStep)
{
    // Components have their scene node as a member variable for convenient access. Rotate the scene node now: construct a
    // rotation quaternion from Euler angles, scale rotation speed with the scene update time step
    // node_->Rotate(Quaternion(rotationSpeed_.x_ * timeStep, rotationSpeed_.y_ * timeStep, rotationSpeed_.z_ * timeStep));
}

void RootMotionComputer::SetupNewAnimInfo(const String& animName)
{
    ResourceCache* cache = GetSubsystem<ResourceCache>();

    Animation* anim = cache->GetResource<Animation>(animName);
    if (!anim)
        return;


}

void RootMotionComputer::DrawDebugGeometry(DebugRenderer* debug, bool depthTest)
{
    if (!pelvis)
        return;

    float distance = 10.0f;
    Vector3 dir = pelvis->GetWorldRotation() * pelvisRightAxis * debugGizmoSize;
    // draw pelvis right axis
    debug->AddLine(pelvis->GetWorldPosition(), pelvis->GetWorldPosition() + dir * distance, Color::RED, depthTest);

    // draw root node axes
    dir = rootNode->GetWorldRotation() * Vector3::FORWARD * debugGizmoSize;
    debug->AddLine(rootNode->GetWorldPosition(), rootNode->GetWorldPosition() + dir * distance, Color::BLUE, depthTest);

    dir = rootNode->GetWorldRotation() * Vector3::RIGHT * debugGizmoSize;
    debug->AddLine(rootNode->GetWorldPosition(), rootNode->GetWorldPosition() + dir * distance, Color::RED, depthTest);

    dir = rootNode->GetWorldRotation() * Vector3::UP * debugGizmoSize;
    debug->AddLine(rootNode->GetWorldPosition(), rootNode->GetWorldPosition() + dir * distance, Color::GREEN, depthTest);
}