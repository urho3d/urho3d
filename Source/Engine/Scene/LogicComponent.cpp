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
#include "Log.h"
#include "LogicComponent.h"
#include "PhysicsEvents.h"
#include "PhysicsWorld.h"
#include "Scene.h"
#include "SceneEvents.h"

namespace Urho3D
{

LogicComponent::LogicComponent(Context* context) :
    Component(context),
    updateEventMask_(USE_UPDATE | USE_POSTUPDATE | USE_FIXEDUPDATE | USE_FIXEDPOSTUPDATE),
    delayedStartCalled_(false)
{
}

LogicComponent::~LogicComponent()
{
}

void LogicComponent::OnSetEnabled()
{
    UpdateEventSubscription();
}

void LogicComponent::SetUpdateEventMask(unsigned mask)
{
    if (updateEventMask_ != mask)
    {
        updateEventMask_ = mask;
        UpdateEventSubscription();
    }
}

void LogicComponent::OnNodeSet(Node* node)
{
    if (node)
    {
        // We have been attached to a node. Set initial update event subscription state
        UpdateEventSubscription();
        // Then execute the start function
        Start();
    }
    else
    {
        // We are being detached from a node: execute stop function and prepare for destruction
        Stop();
    }
}

void LogicComponent::UpdateEventSubscription()
{
    // If scene node is not assigned yet, no need to update subscription
    if (!node_)
        return;
    
    Scene* scene = GetScene();
    if (!scene)
    {
        LOGWARNING("Node is detached from scene, can not subscribe to update events");
        return;
    }
    
    bool enabled = IsEnabledEffective();
    
    if (enabled)
    {
        if (updateEventMask_ & USE_UPDATE)
            SubscribeToEvent(scene, E_SCENEUPDATE, HANDLER(LogicComponent, HandleSceneUpdate));
        if (updateEventMask_ & USE_POSTUPDATE)
            SubscribeToEvent(scene, E_SCENEPOSTUPDATE, HANDLER(LogicComponent, HandleScenePostUpdate));
        
        if (updateEventMask_ & (USE_FIXEDUPDATE | USE_FIXEDPOSTUPDATE))
        {
            PhysicsWorld* world = scene->GetComponent<PhysicsWorld>();
            if (world)
            {
                if (updateEventMask_ & USE_FIXEDUPDATE)
                    SubscribeToEvent(world, E_PHYSICSPRESTEP, HANDLER(LogicComponent, HandlePhysicsPreStep));
                if (updateEventMask_ & USE_FIXEDPOSTUPDATE)
                    SubscribeToEvent(world, E_PHYSICSPOSTSTEP, HANDLER(LogicComponent, HandlePhysicsPostStep));
            }
            else
                LOGERROR("No physics world, can not subscribe to fixed update events");
        }
    }
    else
    {
        UnsubscribeFromEvent(scene, E_SCENEUPDATE);
        UnsubscribeFromEvent(scene, E_SCENEPOSTUPDATE);
        
        PhysicsWorld* world = scene->GetComponent<PhysicsWorld>();
        if (world)
        {
            UnsubscribeFromEvent(world, E_PHYSICSPRESTEP);
            UnsubscribeFromEvent(world, E_PHYSICSPOSTSTEP);
        }
    }
}

void LogicComponent::HandleSceneUpdate(StringHash eventType, VariantMap& eventData)
{
    using namespace SceneUpdate;
    
    // Execute delayed start before first update
    if (!delayedStartCalled_)
    {
        DelayedStart();
        delayedStartCalled_ = true;
    }
    
    Update(eventData[P_TIMESTEP].GetFloat());
}

void LogicComponent::HandleScenePostUpdate(StringHash eventType, VariantMap& eventData)
{
    using namespace ScenePostUpdate;
    
    PostUpdate(eventData[P_TIMESTEP].GetFloat());
}

void LogicComponent::HandlePhysicsPreStep(StringHash eventType, VariantMap& eventData)
{
    using namespace PhysicsPreStep;
    
    // Execute delayed start before first update
    if (!delayedStartCalled_)
    {
        DelayedStart();
        delayedStartCalled_ = true;
    }
    
    FixedUpdate(eventData[P_TIMESTEP].GetFloat());
}

void LogicComponent::HandlePhysicsPostStep(StringHash eventType, VariantMap& eventData)
{
    using namespace PhysicsPostStep;
    
    FixedUpdate(eventData[P_TIMESTEP].GetFloat());
}

}
