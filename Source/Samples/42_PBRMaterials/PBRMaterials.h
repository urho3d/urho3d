// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#pragma once

#include "Sample.h"

namespace Urho3D
{

class Drawable;
class Node;
class Scene;
class Zone;

}

/// PBR materials example.
/// This sample demonstrates:
///      - Loading a scene that showcases physically based materials & shaders
///
/// To use with deferred rendering, a PBR deferred renderpath should be chosen:
/// CoreData/RenderPaths/PBRDeferred.xml or CoreData/RenderPaths/PBRDeferredHWDepth.xml
class PBRMaterials : public Sample
{
    URHO3D_OBJECT(PBRMaterials, Sample);

public:
    /// Construct.
    explicit PBRMaterials(Context* context);

    /// Setup after engine initialization and before running the main loop.
    void Start() override;

private:
    /// Construct the scene content.
    void CreateScene();
    /// Construct user interface elements.
    void CreateUI();
    /// Set up a viewport for displaying the scene.
    void SetupViewport();
    /// Subscribe to application-wide logic update event.
    void SubscribeToEvents();
    /// Reads input and moves the camera.
    void MoveCamera(float timeStep);
    /// Handle the logic update event.
    void HandleUpdate(StringHash eventType, VariantMap& eventData);
    /// Construct an instruction text to the UI.
    void CreateInstructions();
    /// Handle the roughness slider drag event.
    void HandleRoughnessSliderChanged(StringHash eventType, VariantMap& eventData);
    /// Handle the metallic slider drag event.
    void HandleMetallicSliderChanged(StringHash eventType, VariantMap& eventData);
    /// Handle the ambient HDR scale slider drag event.
    void HandleAmbientSliderChanged(StringHash eventType, VariantMap& eventData);

    /// Dynamic material.
    Material* dynamicMaterial_;
    /// Roughness label.
    Text* roughnessLabel_;
    /// Metallic label.
    Text* metallicLabel_;
    /// Ambient HDR scale label.
    Text* ambientLabel_;
    /// Zone component in scene.
    WeakPtr<Zone> zone_;
};
