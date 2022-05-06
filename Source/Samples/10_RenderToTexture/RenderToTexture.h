// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#pragma once

#include "Sample.h"

namespace Urho3D
{

class Node;
class Scene;

}

/// Render to texture example
/// This sample demonstrates:
///     - Creating two 3D scenes and rendering the other into a texture
///     - Creating rendertarget texture and material programmatically
class RenderToTexture : public Sample
{
    URHO3D_OBJECT(RenderToTexture, Sample);

public:
    /// Construct.
    explicit RenderToTexture(Context* context);

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

    /// Scene that is rendered to a texture.
    SharedPtr<Scene> rttScene_;
    /// Camera scene node in the render-to-texture scene.
    SharedPtr<Node> rttCameraNode_;
};
