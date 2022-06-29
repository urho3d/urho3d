// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#include "../Precompiled.h"

#include "../IO/Log.h"
#if defined(URHO3D_PHYSICS) || defined(URHO3D_PHYSICS2D)
#include "../Physics/PhysicsEvents.h"
#endif
#include "../Scene/LogicComponent.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneEvents.h"

namespace Urho3D
{

LogicComponent::LogicComponent(Context* context) :
    Component(context),
    updateEventMask_(LogicComponentEvents::All),
    currentEventMask_(LogicComponentEvents::None),
    delayedStartCalled_(false)
{
}

LogicComponent::~LogicComponent() = default;

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

void LogicComponent::SetUpdateEventMask(LogicComponentEvents mask)
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
        // Execute the user-defined start function
        Start();
    }
    else
    {
        // We are being detached from a node: execute user-defined stop function and prepare for destruction
        Stop();
    }
}

void LogicComponent::OnSceneSet(Scene* scene)
{
    if (scene)
        UpdateEventSubscription();
    else
    {
        UnsubscribeFromEvent(E_SCENEUPDATE);
        UnsubscribeFromEvent(E_SCENEPOSTUPDATE);
#if defined(URHO3D_PHYSICS) || defined(URHO3D_PHYSICS2D)
        UnsubscribeFromEvent(E_PHYSICSPRESTEP);
        UnsubscribeFromEvent(E_PHYSICSPOSTSTEP);
#endif
        currentEventMask_ = LogicComponentEvents::None;
    }
}

void LogicComponent::UpdateEventSubscription()
{
    Scene* scene = GetScene();
    if (!scene)
        return;

    bool enabled = IsEnabledEffective();

    bool needUpdate = enabled && (!!(updateEventMask_ & LogicComponentEvents::Update) || !delayedStartCalled_);
    if (needUpdate && !(currentEventMask_ & LogicComponentEvents::Update))
    {
        SubscribeToEvent(scene, E_SCENEUPDATE, URHO3D_HANDLER(LogicComponent, HandleSceneUpdate));
        currentEventMask_ |= LogicComponentEvents::Update;
    }
    else if (!needUpdate && !!(currentEventMask_ & LogicComponentEvents::Update))
    {
        UnsubscribeFromEvent(scene, E_SCENEUPDATE);
        currentEventMask_ &= ~LogicComponentEvents::Update;
    }

    bool needPostUpdate = enabled && !!(updateEventMask_ & LogicComponentEvents::PostUpdate);
    if (needPostUpdate && !(currentEventMask_ & LogicComponentEvents::PostUpdate))
    {
        SubscribeToEvent(scene, E_SCENEPOSTUPDATE, URHO3D_HANDLER(LogicComponent, HandleScenePostUpdate));
        currentEventMask_ |= LogicComponentEvents::PostUpdate;
    }
    else if (!needPostUpdate && !!(currentEventMask_ & LogicComponentEvents::PostUpdate))
    {
        UnsubscribeFromEvent(scene, E_SCENEPOSTUPDATE);
        currentEventMask_ &= ~LogicComponentEvents::PostUpdate;
    }

#if defined(URHO3D_PHYSICS) || defined(URHO3D_PHYSICS2D)
    Component* world = GetFixedUpdateSource();
    if (!world)
        return;

    bool needFixedUpdate = enabled && !!(updateEventMask_ & LogicComponentEvents::FixedUpdate);
    if (needFixedUpdate && !(currentEventMask_ & LogicComponentEvents::FixedUpdate))
    {
        SubscribeToEvent(world, E_PHYSICSPRESTEP, URHO3D_HANDLER(LogicComponent, HandlePhysicsPreStep));
        currentEventMask_ |= LogicComponentEvents::FixedUpdate;
    }
    else if (!needFixedUpdate && !!(currentEventMask_ & LogicComponentEvents::FixedUpdate))
    {
        UnsubscribeFromEvent(world, E_PHYSICSPRESTEP);
        currentEventMask_ &= ~LogicComponentEvents::FixedUpdate;
    }

    bool needFixedPostUpdate = enabled && !!(updateEventMask_ & LogicComponentEvents::FixedPostUpdate);
    if (needFixedPostUpdate && !(currentEventMask_ & LogicComponentEvents::FixedPostUpdate))
    {
        SubscribeToEvent(world, E_PHYSICSPOSTSTEP, URHO3D_HANDLER(LogicComponent, HandlePhysicsPostStep));
        currentEventMask_ |= LogicComponentEvents::FixedPostUpdate;
    }
    else if (!needFixedPostUpdate && !!(currentEventMask_ & LogicComponentEvents::FixedPostUpdate))
    {
        UnsubscribeFromEvent(world, E_PHYSICSPOSTSTEP);
        currentEventMask_ &= ~LogicComponentEvents::FixedPostUpdate;
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
        if (!(updateEventMask_ & LogicComponentEvents::Update))
        {
            UnsubscribeFromEvent(GetScene(), E_SCENEUPDATE);
            currentEventMask_ &= ~LogicComponentEvents::Update;
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

#if defined(URHO3D_PHYSICS) || defined(URHO3D_PHYSICS2D)

void LogicComponent::HandlePhysicsPreStep(StringHash eventType, VariantMap& eventData)
{
    using namespace PhysicsPreStep;

    // Execute user-defined delayed start function before first fixed update if not called yet
    if (!delayedStartCalled_)
    {
        DelayedStart();
        delayedStartCalled_ = true;
    }

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
