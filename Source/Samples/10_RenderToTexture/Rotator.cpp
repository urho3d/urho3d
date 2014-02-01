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

#include "Rotator.h"
#include "Scene.h"
#include "SceneEvents.h"

#include "DebugNew.h"

Rotator::Rotator(Context* context) :
    Component(context),
    rotationSpeed_(Vector3::ZERO)
{
}

void Rotator::SetRotationSpeed(const Vector3& speed)
{
    rotationSpeed_ = speed;
}

void Rotator::OnNodeSet(Node* node)
{
    // If the node pointer is non-null, this component has been created into a scene node. Subscribe to the variable timestep
    // scene update event now
    if (node)
    {
        Scene* scene = node->GetScene();
        if (scene)
            SubscribeToEvent(scene, E_SCENEUPDATE, HANDLER(Rotator, HandleSceneUpdate));
    }
}

void Rotator::HandleSceneUpdate(StringHash eventType, VariantMap& eventData)
{
    // Get the timestep from the update event
    using namespace SceneUpdate;
    float timeStep = eventData[P_TIMESTEP].GetFloat();
    
    // Components have their scene node as a member variable for convenient access. Rotate the scene node now: construct a
    // rotation quaternion from Euler angles, scale rotation speed with the scene update time step
    node_->Rotate(Quaternion(rotationSpeed_.x_ * timeStep, rotationSpeed_.y_ * timeStep, rotationSpeed_.z_ * timeStep));
}
