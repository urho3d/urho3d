// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#pragma once

#include "Sample.h"

namespace Urho3D
{

class Node;
class Scene;

}

/// Material animation example.
/// This sample is base on StaticScene, and it demonstrates:
///     - Usage of material shader animation for mush room material
class MaterialAnimation : public Sample
{
    URHO3D_OBJECT(MaterialAnimation, Sample);

public:
    /// Construct.
    explicit MaterialAnimation(Context* context);

    /// Setup after engine initialization and before running the main loop.
    void Start() override;

private:
    /// Construct the scene content.
    void CreateScene();
    /// Construct an instruction text to the UI.
    void CreateInstructions();
    /// Set up a viewport for displaying the scene.
    void SetupViewport();
    /// Read input and moves the camera.
    void MoveCamera(float timeStep);
    /// Subscribe to application-wide logic update events.
    void SubscribeToEvents();
    /// Handle the logic update event.
    void HandleUpdate(StringHash eventType, VariantMap& eventData);
};
