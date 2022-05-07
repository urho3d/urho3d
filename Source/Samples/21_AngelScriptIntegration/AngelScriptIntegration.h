// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#pragma once

#include "Sample.h"

namespace Urho3D
{

class Node;
class Scene;

}

/// Animating 3D scene example with script integration.
/// This sample demonstrates:
///     - Initializing the AngelScript scripting subsystem
///     - Creating a 3D scene and using a script object to animate the objects
class AngelScriptIntegration : public Sample
{
    URHO3D_OBJECT(AngelScriptIntegration, Sample);

public:
    /// Construct.
    explicit AngelScriptIntegration(Context* context);

    /// Setup after engine initialization and before running the main loop.
    void Start() override;

private:
    /// Construct the scene content.
    void CreateScene();
    /// Construct an instruction text to the UI.
    void CreateInstructions();
    /// Set up a viewport for displaying the scene.
    void SetupViewport();
    /// Subscribe to application-wide logic update events.
    void SubscribeToEvents();
    /// Read input and moves the camera.
    void MoveCamera(float timeStep);
    /// Handle the logic update event.
    void HandleUpdate(StringHash eventType, VariantMap& eventData);
};
