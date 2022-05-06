// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#pragma once

#include "Sample.h"

namespace Urho3D
{

class Drawable;
class Node;
class Scene;

}

/// Navigation example.
/// This sample demonstrates:
///     - Generating a navigation mesh into the scene
///     - Performing path queries to the navigation mesh
///     - Rebuilding the navigation mesh partially when adding or removing objects
///     - Visualizing custom debug geometry
///     - Raycasting drawable components
///     - Making a node follow the Detour path
class Navigation : public Sample
{
    URHO3D_OBJECT(Navigation, Sample);

public:
    /// Construct.
    explicit Navigation(Context* context);

    /// Setup after engine initialization and before running the main loop.
    void Start() override;

protected:
    /// Return XML patch instructions for screen joystick layout for a specific sample app, if any.
    String GetScreenJoystickPatchString() const override { return
        "<patch>"
        "    <add sel=\"/element\">"
        "        <element type=\"Button\">"
        "            <attribute name=\"Name\" value=\"Button3\" />"
        "            <attribute name=\"Position\" value=\"-120 -120\" />"
        "            <attribute name=\"Size\" value=\"96 96\" />"
        "            <attribute name=\"Horiz Alignment\" value=\"Right\" />"
        "            <attribute name=\"Vert Alignment\" value=\"Bottom\" />"
        "            <attribute name=\"Texture\" value=\"Texture2D;Textures/TouchInput.png\" />"
        "            <attribute name=\"Image Rect\" value=\"96 0 192 96\" />"
        "            <attribute name=\"Hover Image Offset\" value=\"0 0\" />"
        "            <attribute name=\"Pressed Image Offset\" value=\"0 0\" />"
        "            <element type=\"Text\">"
        "                <attribute name=\"Name\" value=\"Label\" />"
        "                <attribute name=\"Horiz Alignment\" value=\"Center\" />"
        "                <attribute name=\"Vert Alignment\" value=\"Center\" />"
        "                <attribute name=\"Color\" value=\"0 0 0 1\" />"
        "                <attribute name=\"Text\" value=\"Teleport\" />"
        "            </element>"
        "            <element type=\"Text\">"
        "                <attribute name=\"Name\" value=\"KeyBinding\" />"
        "                <attribute name=\"Text\" value=\"LSHIFT\" />"
        "            </element>"
        "            <element type=\"Text\">"
        "                <attribute name=\"Name\" value=\"MouseButtonBinding\" />"
        "                <attribute name=\"Text\" value=\"LEFT\" />"
        "            </element>"
        "        </element>"
        "        <element type=\"Button\">"
        "            <attribute name=\"Name\" value=\"Button4\" />"
        "            <attribute name=\"Position\" value=\"-120 -12\" />"
        "            <attribute name=\"Size\" value=\"96 96\" />"
        "            <attribute name=\"Horiz Alignment\" value=\"Right\" />"
        "            <attribute name=\"Vert Alignment\" value=\"Bottom\" />"
        "            <attribute name=\"Texture\" value=\"Texture2D;Textures/TouchInput.png\" />"
        "            <attribute name=\"Image Rect\" value=\"96 0 192 96\" />"
        "            <attribute name=\"Hover Image Offset\" value=\"0 0\" />"
        "            <attribute name=\"Pressed Image Offset\" value=\"0 0\" />"
        "            <element type=\"Text\">"
        "                <attribute name=\"Name\" value=\"Label\" />"
        "                <attribute name=\"Horiz Alignment\" value=\"Center\" />"
        "                <attribute name=\"Vert Alignment\" value=\"Center\" />"
        "                <attribute name=\"Color\" value=\"0 0 0 1\" />"
        "                <attribute name=\"Text\" value=\"Obstacles\" />"
        "            </element>"
        "            <element type=\"Text\">"
        "                <attribute name=\"Name\" value=\"MouseButtonBinding\" />"
        "                <attribute name=\"Text\" value=\"MIDDLE\" />"
        "            </element>"
        "        </element>"
        "    </add>"
        "    <remove sel=\"/element/element[./attribute[@name='Name' and @value='Button0']]/attribute[@name='Is Visible']\" />"
        "    <replace sel=\"/element/element[./attribute[@name='Name' and @value='Button0']]/element[./attribute[@name='Name' and @value='Label']]/attribute[@name='Text']/@value\">Set</replace>"
        "    <add sel=\"/element/element[./attribute[@name='Name' and @value='Button0']]\">"
        "        <element type=\"Text\">"
        "            <attribute name=\"Name\" value=\"MouseButtonBinding\" />"
        "            <attribute name=\"Text\" value=\"LEFT\" />"
        "        </element>"
        "    </add>"
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
    /// Construct user interface elements.
    void CreateUI();
    /// Set up a viewport for displaying the scene.
    void SetupViewport();
    /// Subscribe to application-wide logic update and post-render update events.
    void SubscribeToEvents();
    /// Read input and moves the camera.
    void MoveCamera(float timeStep);
    /// Set path start or end point.
    void SetPathPoint();
    /// Add or remove object.
    void AddOrRemoveObject();
    /// Create a mushroom object at position.
    Node* CreateMushroom(const Vector3& pos);
    /// Utility function to raycast to the cursor position. Return true if hit
    bool Raycast(float maxDistance, Vector3& hitPos, Drawable*& hitDrawable);
    /// Make Jack follow the Detour path.
    void FollowPath(float timeStep);
    /// Toggle navigation mesh streaming.
    void ToggleStreaming(bool enabled);
    /// Update navigation mesh streaming.
    void UpdateStreaming();
    /// Save navigation data for streaming.
    void SaveNavigationData();
    /// Handle the logic update event.
    void HandleUpdate(StringHash eventType, VariantMap& eventData);
    /// Handle the post-render update event.
    void HandlePostRenderUpdate(StringHash eventType, VariantMap& eventData);

    /// Last calculated path.
    PODVector<Vector3> currentPath_;
    /// Path end position.
    Vector3 endPos_;
    /// Jack scene node.
    SharedPtr<Node> jackNode_;
    /// Flag for drawing debug geometry.
    bool drawDebug_;
    /// Flag for using navigation mesh streaming.
    bool useStreaming_;
    /// Streaming distance.
    int streamingDistance_;
    /// Tile data.
    HashMap<IntVector2, PODVector<unsigned char> > tileData_;
    /// Added tiles.
    HashSet<IntVector2> addedTiles_;
};
