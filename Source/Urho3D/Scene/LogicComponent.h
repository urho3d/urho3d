//
// Copyright (c) 2008-2022 the Urho3D project.
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

/// \file

#pragma once

#include "../Container/FlagSet.h"
#include "../Scene/Component.h"

namespace Urho3D
{

enum UpdateEvent : unsigned
{
    /// Bitmask for not using any events.
    USE_NO_EVENT = 0x0,
    /// Bitmask for using the scene update event.
    USE_UPDATE = 0x1,
    /// Bitmask for using the scene post-update event.
    USE_POSTUPDATE = 0x2,
    /// Bitmask for using the physics update event.
    USE_FIXEDUPDATE = 0x4,
    /// Bitmask for using the physics post-update event.
    USE_FIXEDPOSTUPDATE = 0x8,
};
URHO3D_FLAGSET(UpdateEvent, UpdateEventFlags);

/// Helper base class for user-defined game logic components that hooks up to update events and forwards them to virtual functions similar to ScriptInstance class.
class URHO3D_API LogicComponent : public Component
{
    URHO3D_OBJECT(LogicComponent, Component);

    /// Construct.
    explicit LogicComponent(Context* context);
    /// Destruct.
    ~LogicComponent() override;

    /// Handle enabled/disabled state change. Changes update event subscription.
    void OnSetEnabled() override;

    /// Called when the component is added to a scene node. Other components may not yet exist.
    virtual void Start() { }

    /// Called before the first update. At this point all other components of the node should exist. Will also be called if update events are not wanted; in that case the event is immediately unsubscribed afterward.
    virtual void DelayedStart() { }

    /// Called when the component is detached from a scene node, usually on destruction. Note that you will no longer have access to the node and scene at that point.
    virtual void Stop() { }

    /// Called on scene update, variable timestep.
    virtual void Update(float timeStep);
    /// Called on scene post-update, variable timestep.
    virtual void PostUpdate(float timeStep);
    /// Called on physics update, fixed timestep.
    virtual void FixedUpdate(float timeStep);
    /// Called on physics post-update, fixed timestep.
    virtual void FixedPostUpdate(float timeStep);

    /// Set what update events should be subscribed to. Use this for optimization: by default all are in use. Note that this is not an attribute and is not saved or network-serialized, therefore it should always be called eg. in the subclass constructor.
    void SetUpdateEventMask(UpdateEventFlags mask);

    /// Return what update events are subscribed to.
    UpdateEventFlags GetUpdateEventMask() const { return updateEventMask_; }

    /// Return whether the DelayedStart() function has been called.
    bool IsDelayedStartCalled() const { return delayedStartCalled_; }

protected:
    /// Handle scene node being assigned at creation.
    void OnNodeSet(Node* node) override;
    /// Handle scene being assigned.
    void OnSceneSet(Scene* scene) override;

private:
    /// Subscribe/unsubscribe to update events based on current enabled state and update event mask.
    void UpdateEventSubscription();
    /// Handle scene update event.
    void HandleSceneUpdate(StringHash eventType, VariantMap& eventData);
    /// Handle scene post-update event.
    void HandleScenePostUpdate(StringHash eventType, VariantMap& eventData);
#if defined(URHO3D_PHYSICS) || defined(URHO3D_PHYSICS2D)
    /// Handle physics pre-step event.
    void HandlePhysicsPreStep(StringHash eventType, VariantMap& eventData);
    /// Handle physics post-step event.
    void HandlePhysicsPostStep(StringHash eventType, VariantMap& eventData);
#endif
    /// Requested event subscription mask.
    UpdateEventFlags updateEventMask_;
    /// Current event subscription mask.
    UpdateEventFlags currentEventMask_;
    /// Flag for delayed start.
    bool delayedStartCalled_;
};

}
