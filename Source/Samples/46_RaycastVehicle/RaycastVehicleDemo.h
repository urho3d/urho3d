// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#pragma once

#include "Sample.h"

namespace Urho3D
{
    class Node;
    class Scene;
}

class Vehicle;

/// Vehicle example.
/// This sample demonstrates:
///     - Creating a heightmap terrain with collision
///     - Constructing 100 raycast vehicles
///     - Defining attributes (including node and component references) of a custom component
///     (Saving and loading is broken now)

class RaycastVehicleDemo : public Sample
{
    URHO3D_OBJECT(RaycastVehicleDemo, Sample);

public:
    /// Construct.
    explicit RaycastVehicleDemo(Context* context);

    /// Setup after engine initialization and before running the main loop.
    void Start() override;

private:
    /// Create static scene content.
    void CreateScene();

    /// Create the vehicle.
    void CreateVehicle();

    /// Construct an instruction text to the UI.
    void CreateInstructions();

    /// Subscribe to necessary events.
    void SubscribeToEvents();

    /// Handle application update. Set controls to vehicle.
    void HandleUpdate(StringHash eventType, VariantMap& eventData);

    /// Handle application post-update. Update camera position after vehicle has moved.
    void HandlePostUpdate(StringHash eventType, VariantMap& eventData);

    /// The controllable vehicle component.
    WeakPtr<Vehicle> vehicle_;
};
