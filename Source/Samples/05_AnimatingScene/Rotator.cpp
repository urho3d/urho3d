// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#include <Urho3D/Scene/Scene.h>

#include "Rotator.h"

#include <Urho3D/DebugNew.h>

Rotator::Rotator(Context* context) :
    LogicComponent(context),
    rotationSpeed_(Vector3::ZERO)
{
    // Only the scene update event is needed: unsubscribe from the rest for optimization
    SetUpdateEventMask(USE_UPDATE);
}

void Rotator::SetRotationSpeed(const Vector3& speed)
{
    rotationSpeed_ = speed;
}

void Rotator::Update(float timeStep)
{
    // Components have their scene node as a member variable for convenient access. Rotate the scene node now: construct a
    // rotation quaternion from Euler angles, scale rotation speed with the scene update time step
    node_->Rotate(Quaternion(rotationSpeed_.x_ * timeStep, rotationSpeed_.y_ * timeStep, rotationSpeed_.z_ * timeStep));
}
