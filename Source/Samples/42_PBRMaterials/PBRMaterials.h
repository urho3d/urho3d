//
// Copyright (c) 2008-2020 the Urho3D project.
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
