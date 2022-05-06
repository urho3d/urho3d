// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#pragma once

#include "Sample.h"

namespace Urho3D
{
    class Node;
}

/// Urho2D stretchable sprite example.
/// This sample demonstrates:
///     - Creating a 2D scene with both static and stretchable sprites
///     - Difference in scaling static and stretchable sprites
///     - Similarity in otherwise transforming static and stretchable sprites
///     - Displaying the scene using the Renderer subsystem
///     - Handling keyboard to transform nodes
class Urho2DStretchableSprite : public Sample
{
    URHO3D_OBJECT(Urho2DStretchableSprite, Sample);

public:
    /// Construct.
    explicit Urho2DStretchableSprite(Context* context);

    /// Setup after engine initialization and before running the main loop.
    void Start() override;

protected:
    /// Return XML patch instructions for screen joystick layout for a specific sample app, if any.
    String GetScreenJoystickPatchString() const override { return
        "<patch>"
        "    <remove sel=\"/element/element[./attribute[@name='Name' and @value='Button0']]/attribute[@name='Is Visible']\" />"
        "    <replace sel=\"/element/element[./attribute[@name='Name' and @value='Button0']]/element[./attribute[@name='Name' and @value='Label']]/attribute[@name='Text']/@value\">TAB</replace>"
        "    <add sel=\"/element/element[./attribute[@name='Name' and @value='Button0']]\">"
        "        <element type=\"Text\">"
        "            <attribute name=\"Name\" value=\"KeyBinding\" />"
        "            <attribute name=\"Text\" value=\"TAB\" />"
        "        </element>"
        "    </add>"
        "    <remove sel=\"/element/element[./attribute[@name='Name' and @value='Button1']]/attribute[@name='Is Visible']\" />"
        "    <replace sel=\"/element/element[./attribute[@name='Name' and @value='Button1']]/element[./attribute[@name='Name' and @value='Label']]/attribute[@name='Text']/@value\">CTRL</replace>"
        "    <add sel=\"/element/element[./attribute[@name='Name' and @value='Button1']]\">"
        "        <element type=\"Text\">"
        "            <attribute name=\"Name\" value=\"KeyBinding\" />"
        "            <attribute name=\"Text\" value=\"LCTRL\" />"
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
    /// Subscribe to application-wide logic update events.
    void SubscribeToEvents();
    /// Handle the logic update event.
    void HandleUpdate(StringHash eventType, VariantMap& eventData);
    /// Handle KeyUp event.
    void OnKeyUp(StringHash eventType, VariantMap& eventData);
    /// Translate sprite nodes.
    void TranslateSprites(float timeStep);
    /// Rotate sprite nodes.
    void RotateSprites(float timeStep);
    /// Scale sprite nodes.
    void ScaleSprites(float timeStep);

    /// Reference (static) sprite node.
    SharedPtr<Node> refSpriteNode_;
    /// Stretchable sprite node.
    SharedPtr<Node> stretchSpriteNode_;
    /// Transform mode tracking index.
    unsigned selectTransform_ = 0;
};
