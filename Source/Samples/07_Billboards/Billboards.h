// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#pragma once

#include "Sample.h"

namespace Urho3D
{

class Node;
class Scene;

}

/// Billboard example.
/// This sample demonstrates:
///     - Populating a 3D scene with billboard sets and several shadow casting spotlights
///     - Parenting scene nodes to allow more intuitive creation of groups of objects
///     - Examining rendering performance with a somewhat large object and light count
class Billboards : public Sample
{
    URHO3D_OBJECT(Billboards, Sample);

public:
    /// Construct.
    explicit Billboards(Context* context);

    /// Setup after engine initialization and before running the main loop.
    void Start() override;

protected:
    /// Return XML patch instructions for screen joystick layout for a specific sample app, if any.
    String GetScreenJoystickPatchString() const override { return
        "<patch>"
        "    <remove sel=\"/element/element[./attribute[@name='Name' and @value='Button1']]/attribute[@name='Is Visible']\" />"
        "    <replace sel=\"/element/element[./attribute[@name='Name' and @value='Button1']]/element[./attribute[@name='Name' and @value='Label']]/attribute[@name='Text']/@value\">Debug</replace>"
        "    <add sel=\"/element/element[./attribute[@name='Name' and @value='Button1']]\">"
        "        <element type=\"Text\">"
        "            <attribute name=\"Name\" value=\"KeyBinding\" />"
        "            <attribute name=\"Text\" value=\"SPACE\" />"
        "        </element>"
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
    /// Subscribe to application-wide logic update and post-render update events.
    void SubscribeToEvents();
    /// Read input and moves the camera.
    void MoveCamera(float timeStep);
    /// Animate the scene.
    void AnimateScene(float timeStep);
    /// Handle the logic update event.
    void HandleUpdate(StringHash eventType, VariantMap& eventData);
    /// Handle the post-render update event.
    void HandlePostRenderUpdate(StringHash eventType, VariantMap& eventData);

    /// Flag for drawing debug geometry.
    bool drawDebug_;
};
