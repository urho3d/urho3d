// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#pragma once

#include "Sample.h"

namespace Urho3D
{
    class Node;
    class Scene;
}

// Urho2D particle example.
// This sample demonstrates:
//     - Creating a 2D scene with particle
//     - Displaying the scene using the Renderer subsystem
//     - Handling mouse move to move particle
class Urho2DParticle : public Sample
{
    URHO3D_OBJECT(Urho2DParticle, Sample);

public:
    /// Construct.
    explicit Urho2DParticle(Context* context);

    /// Setup after engine initialization and before running the main loop.
    void Start() override;

protected:
    /// Return XML patch instructions for screen joystick layout for a specific sample app, if any.
    String GetScreenJoystickPatchString() const override { return
        "<patch>"
        "    <add sel=\"/element/element[./attribute[@name='Name' and @value='Hat0']]\">"
        "        <attribute name=\"Is Visible\" value=\"false\" />"
        "    </add>"
        "</patch>";
    }

private:
    /// Construct the scene content.
    void CreateScene();
    /// Construct an instruction text to the UI.
    void CreateInstructions();
    /// Set up a viewport for displaying the scene.
    void SetupViewport();
    /// Subscribe to application-wide logic update events.
    void SubscribeToEvents();
    /// Handle mouse move event.
    void HandleMouseMove(StringHash eventType, VariantMap& eventData);

    /// Particle scene node.
    SharedPtr<Node> particleNode_;
};
