// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#pragma once

#include "Sample.h"

namespace Urho3D
{
    class Node;
    class Scene;
    class ConstraintDistance2D;
    class ConstraintFriction2D;
    class ConstraintGear2D;
    class ConstraintMotor2D;
    class ConstraintMouse2D;
    class ConstraintPrismatic2D;
    class ConstraintPulley2D;
    class ConstraintRevolute2D;
    class ConstraintRope2D;
    class ConstraintWeld2D;
    class ConstraintWheel2D;
}

/// Physics2D constraints sample.
/// This sample is designed to help understanding and chosing the right constraint.
/// This sample demonstrates:
///     - Creating physics constraints
///     - Creating Edge and Polygon Shapes from vertices
///     - Displaying physics debug geometry and constraints' joints
///     - Using SetOrderInLayer to alter the way sprites are drawn in relation to each other
///     - Using Text3D to display some text affected by zoom
///     - Setting the background color for the scene
class Urho2DConstraints : public Sample
{
    URHO3D_OBJECT(Urho2DConstraints, Sample);

public:
    /// Construct.
    explicit Urho2DConstraints(Context* context);

    /// Setup after engine initialization and before running the main loop.
    void Start() override;

protected:
    /// Return XML patch instructions for screen joystick layout for a specific sample app, if any.
    String GetScreenJoystickPatchString() const override { return
        "<patch>"
        "    <remove sel=\"/element/element[./attribute[@name='Name' and @value='Button0']]/attribute[@name='Is Visible']\" />"
        "    <replace sel=\"/element/element[./attribute[@name='Name' and @value='Button0']]/element[./attribute[@name='Name' and @value='Label']]/attribute[@name='Text']/@value\">Zoom In</replace>"
        "    <add sel=\"/element/element[./attribute[@name='Name' and @value='Button0']]\">"
        "        <element type=\"Text\">"
        "            <attribute name=\"Name\" value=\"KeyBinding\" />"
        "            <attribute name=\"Text\" value=\"PAGEUP\" />"
        "        </element>"
        "    </add>"
        "    <remove sel=\"/element/element[./attribute[@name='Name' and @value='Button1']]/attribute[@name='Is Visible']\" />"
        "    <replace sel=\"/element/element[./attribute[@name='Name' and @value='Button1']]/element[./attribute[@name='Name' and @value='Label']]/attribute[@name='Text']/@value\">Zoom Out</replace>"
        "    <add sel=\"/element/element[./attribute[@name='Name' and @value='Button1']]\">"
        "        <element type=\"Text\">"
        "            <attribute name=\"Name\" value=\"KeyBinding\" />"
        "            <attribute name=\"Text\" value=\"PAGEDOWN\" />"
        "        </element>"
        "    </add>"
        "</patch>";
    }

private:
    /// Construct the scene content.
    void CreateScene();
    /// Construct an instruction text to the UI.
    void CreateInstructions();
    /// Create Tex3D flag.
    void CreateFlag(const String& text, float x, float y);
    /// Read input and moves the camera.
    void MoveCamera(float timeStep);
    /// Subscribe to application-wide logic update events.
    void SubscribeToEvents();
    /// Handle the logic update event.
    void HandleUpdate(StringHash eventType, VariantMap& eventData);
    /// Handle the post render update event during which we request debug geometry.
    void HandlePostRenderUpdate(StringHash eventType, VariantMap& eventData);
    /// Handle the mouse click event.
    void HandleMouseButtonDown(StringHash eventType, VariantMap& eventData);
    /// Handle the mouse button up event.
    void HandleMouseButtonUp(StringHash eventType, VariantMap& eventData);
    /// Handle the mouse move event.
    void HandleMouseMove(StringHash eventType, VariantMap& eventData);
    /// Handle the touch begin event.
    void HandleTouchBegin3(StringHash eventType, VariantMap& eventData);
    /// Handle the touch move event.
    void HandleTouchMove3(StringHash eventType, VariantMap& eventData);
    /// Handle the touch end event.
    void HandleTouchEnd3(StringHash eventType, VariantMap& eventData);
    /// Get mouse position in 2D world coordinates.
    Vector2 GetMousePositionXY();
    /// Flag for drawing debug geometry.
    bool drawDebug_{};
    /// Camera object.
    Camera* camera_{};
};
