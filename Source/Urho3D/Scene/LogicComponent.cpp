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

#include "../IO/Log.h"
#include "../Scene/LogicComponent.h"
#ifdef URHO3D_PHYSICS
#include "../Physics/PhysicsEvents.h"
#include "../Physics/PhysicsWorld.h"
#endif
#include "../Scene/Scene.h"
#include "../Scene/SceneEvents.h"

namespace Urho3D
{

LogicComponent::LogicComponent(Context* context) :
    Component(context),
    updateEventMask_(USE_UPDATE | USE_POSTUPDATE | USE_FIXEDUPDATE | USE_FIXEDPOSTUPDATE),
    currentEventMask_(0),
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

void LogicComponent::Update(float timeStep)
{
}

void LogicComponent::PostUpdate(float timeStep)
{
}

void LogicComponent::FixedUpdate(float timeStep)
{
}

void LogicComponent::FixedPostUpdate(float timeStep)
{
}

void LogicComponent::SetUpdateEventMask(unsigned char mask)
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
        // Then execute the user-defined start function
        Start();
    }
    else
    {
        // We are being detached from a node: execute user-defined stop function and prepare for destruction
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
    
    bool needUpdate = enabled && ((updateEventMask_ & USE_UPDATE) || !delayedStartCalled_);
    if (needUpdate && !(currentEventMask_ & USE_UPDATE))
    {
        SubscribeToEvent(scene, E_SCENEUPDATE, HANDLER(LogicComponent, HandleSceneUpdate));
        currentEventMask_ |= USE_UPDATE;
    }
    else if (!needUpdate && (currentEventMask_ & USE_UPDATE))
    {
        UnsubscribeFromEvent(scene, E_SCENEUPDATE);
        currentEventMask_ &= ~USE_UPDATE;
    }
    
    bool needPostUpdate = enabled && (updateEventMask_ & USE_POSTUPDATE);
    if (needPostUpdate && !(currentEventMask_ & USE_POSTUPDATE))
    {
        SubscribeToEvent(scene, E_SCENEPOSTUPDATE, HANDLER(LogicComponent, HandleScenePostUpdate));
        currentEventMask_ |= USE_POSTUPDATE;
    }
    else if (!needUpdate && (currentEventMask_ & USE_POSTUPDATE))
    {
        UnsubscribeFromEvent(scene, E_SCENEPOSTUPDATE);
        currentEventMask_ &= ~USE_POSTUPDATE;
    }

#ifdef URHO3D_PHYSICS
    PhysicsWorld* world = scene->GetComponent<PhysicsWorld>();
    if (!world)
        return;

    bool needFixedUpdate = enabled && (updateEventMask_ & USE_FIXEDUPDATE);
    if (needFixedUpdate && !(currentEventMask_ & USE_FIXEDUPDATE))
    {
        SubscribeToEvent(world, E_PHYSICSPRESTEP, HANDLER(LogicComponent, HandlePhysicsPreStep));
        currentEventMask_ |= USE_FIXEDUPDATE;
    }
    else if (!needFixedUpdate && (currentEventMask_ & USE_FIXEDUPDATE))
    {
        UnsubscribeFromEvent(world, E_PHYSICSPRESTEP);
        currentEventMask_ &= ~USE_FIXEDUPDATE;
    }
    
    bool needFixedPostUpdate = enabled && (updateEventMask_ & USE_FIXEDPOSTUPDATE);
    if (needFixedPostUpdate && !(currentEventMask_ & USE_FIXEDPOSTUPDATE))
    {
        SubscribeToEvent(world, E_PHYSICSPOSTSTEP, HANDLER(LogicComponent, HandlePhysicsPostStep));
        currentEventMask_ |= USE_FIXEDPOSTUPDATE;
    }
    else if (!needFixedPostUpdate && (currentEventMask_ & USE_FIXEDPOSTUPDATE))
    {
        UnsubscribeFromEvent(world, E_PHYSICSPOSTSTEP);
        currentEventMask_ &= ~USE_FIXEDPOSTUPDATE;
    }
#endif 
}

void LogicComponent::HandleSceneUpdate(StringHash eventType, VariantMap& eventData)
{
    using namespace SceneUpdate;
    
    // Execute user-defined delayed start function before first update
    if (!delayedStartCalled_)
    {
        DelayedStart();
        delayedStartCalled_ = true;
        
        // If did not need actual update events, unsubscribe now
        if (!(updateEventMask_ & USE_UPDATE))
        {
            UnsubscribeFromEvent(GetScene(), E_SCENEUPDATE);
            currentEventMask_ &= ~USE_UPDATE;
            return;
        }
    }
    
    // Then execute user-defined update function
    Update(eventData[P_TIMESTEP].GetFloat());
}

void LogicComponent::HandleScenePostUpdate(StringHash eventType, VariantMap& eventData)
{
    using namespace ScenePostUpdate;
    
    // Execute user-defined post-update function
    PostUpdate(eventData[P_TIMESTEP].GetFloat());
}

#ifdef URHO3D_PHYSICS
void LogicComponent::HandlePhysicsPreStep(StringHash eventType, VariantMap& eventData)
{
    using namespace PhysicsPreStep;
    
    // Execute user-defined fixed update function
    FixedUpdate(eventData[P_TIMESTEP].GetFloat());
}

void LogicComponent::HandlePhysicsPostStep(StringHash eventType, VariantMap& eventData)
{
    using namespace PhysicsPostStep;
    
    // Execute user-defined fixed post-update function
    FixedPostUpdate(eventData[P_TIMESTEP].GetFloat());
}
#endif

}
