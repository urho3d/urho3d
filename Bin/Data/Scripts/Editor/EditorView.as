// Urho3D editor view & camera functions

Node@ cameraNode;
Camera@ camera;

Node@ gridNode;
CustomGeometry@ grid;

enum EditMode
{
    EDIT_MOVE = 0,
    EDIT_ROTATE,
    EDIT_SCALE,
    EDIT_SELECT
}

enum AxisMode
{
    AXIS_WORLD = 0,
    AXIS_LOCAL
}

enum SnapScaleMode
{
    SNAP_SCALE_FULL = 0,
    SNAP_SCALE_HALF,
    SNAP_SCALE_QUARTER
}

Text@ editorModeText;
Text@ renderStatsText;
Text@ cameraPosText;

EditMode editMode = EDIT_MOVE;
AxisMode axisMode = AXIS_WORLD;
FillMode fillMode = FILL_SOLID;
SnapScaleMode snapScaleMode = SNAP_SCALE_FULL;

float cameraBaseSpeed = 10;
float cameraBaseRotationSpeed = 0.2;
float cameraShiftSpeedMultiplier = 5;
float cameraYaw = 0;
float cameraPitch = 0;
float newNodeDistance = 20;
float moveStep = 0.5;
float rotateStep = 5;
float scaleStep = 0.1;
float snapScale = 1.0;
bool limitRotation = false;
bool moveSnap = false;
bool rotateSnap = false;
bool scaleSnap = false;
bool renderingDebug = false;
bool physicsDebug = false;
bool octreeDebug = false;
int pickMode = PICK_GEOMETRIES;
bool orbiting = false;

bool showGrid = true;
bool grid2DMode = false;
uint gridSize = 16;
uint gridSubdivisions = 3;
float gridScale = 8.0;
Color gridColor(0.1, 0.1, 0.1);
Color gridSubdivisionColor(0.05, 0.05, 0.05);
Color gridXColor(0.5, 0.1, 0.1);
Color gridYColor(0.1, 0.5, 0.1);
Color gridZColor(0.1, 0.1, 0.5);

Array<int> pickModeDrawableFlags = {
    DRAWABLE_GEOMETRY,
    DRAWABLE_LIGHT,
    DRAWABLE_ZONE
};

Array<String> editModeText = {
    "Move",
    "Rotate",
    "Scale",
    "Select"
};

Array<String> axisModeText = {
    "World",
    "Local"
};

Array<String> pickModeText = {
    "Geometries",
    "Lights",
    "Zones",
    "Rigidbodies",
    "UI-elements"
};

Array<String> fillModeText = {
    "Solid",
    "Wire",
    "Point"
};

void CreateCamera()
{
    // Note: the camera is not inside the scene, so that it is not listed, and does not get deleted
    cameraNode = Node();
    camera = cameraNode.CreateComponent("Camera");
    audio.listener = cameraNode.CreateComponent("SoundListener");
    ResetCamera();

    renderer.viewports[0] = Viewport(editorScene, camera);

    SubscribeToEvent("PostRenderUpdate", "HandlePostRenderUpdate");
    SubscribeToEvent("UIMouseClick", "ViewMouseClick");
}

void ResetCamera()
{
    cameraNode.position = Vector3(0, 5, -10);
    // Look at the origin so user can see the scene.
    cameraNode.rotation = Quaternion(Vector3(0, 0, 1), -cameraNode.position);
    ReacquireCameraYawPitch();
}

void ReacquireCameraYawPitch()
{
    cameraYaw = cameraNode.rotation.yaw;
    cameraPitch = cameraNode.rotation.pitch;
}

void CreateGrid()
{
    gridNode = Node();
    grid = gridNode.CreateComponent("CustomGeometry");
    grid.numGeometries = 1;
    grid.material = cache.GetResource("Material", "Materials/VColUnlit.xml");
    grid.viewMask = 0x80000000; // Editor raycasts use viewmask 0x7fffffff
    grid.occludee = false;

    UpdateGrid();
}

void HideGrid()
{
    if (grid !is null)
        grid.enabled = false;
}

void ShowGrid()
{
    if (grid !is null)
    {
        grid.enabled = true;

        if (editorScene.octree !is null)
            editorScene.octree.AddManualDrawable(grid);
    }
}

void UpdateGrid(bool updateGridGeometry = true)
{
    showGrid ? ShowGrid() : HideGrid();
    gridNode.scale = Vector3(gridScale, gridScale, gridScale);

    if (!updateGridGeometry)
        return;

    uint size = uint(Floor(gridSize / 2) * 2);
    float halfSizeScaled = size / 2;
    float scale = 1.0;
    uint subdivisionSize = uint(Pow(2.0f, float(gridSubdivisions)));

    if (subdivisionSize > 0)
    {
        size *= subdivisionSize;
        scale /= subdivisionSize;
    }

    uint halfSize = size / 2;

    grid.BeginGeometry(0, LINE_LIST);
    float lineOffset = -halfSizeScaled;
    for (uint i = 0; i <= size; ++i)
    {
        bool lineCenter = i == halfSize;
        bool lineSubdiv = !Equals(Mod(i, subdivisionSize), 0.0);

        if (!grid2DMode)
        {
            grid.DefineVertex(Vector3(lineOffset, 0.0, halfSizeScaled));
            grid.DefineColor(lineCenter ? gridZColor : (lineSubdiv ? gridSubdivisionColor : gridColor));
            grid.DefineVertex(Vector3(lineOffset, 0.0, -halfSizeScaled));
            grid.DefineColor(lineCenter ? gridZColor : (lineSubdiv ? gridSubdivisionColor : gridColor));

            grid.DefineVertex(Vector3(-halfSizeScaled, 0.0, lineOffset));
            grid.DefineColor(lineCenter ? gridXColor : (lineSubdiv ? gridSubdivisionColor : gridColor));
            grid.DefineVertex(Vector3(halfSizeScaled, 0.0, lineOffset));
            grid.DefineColor(lineCenter ? gridXColor : (lineSubdiv ? gridSubdivisionColor : gridColor));
        }
        else
        {
            grid.DefineVertex(Vector3(lineOffset, halfSizeScaled, 0.0));
            grid.DefineColor(lineCenter ? gridYColor : (lineSubdiv ? gridSubdivisionColor : gridColor));
            grid.DefineVertex(Vector3(lineOffset, -halfSizeScaled, 0.0));
            grid.DefineColor(lineCenter ? gridYColor : (lineSubdiv ? gridSubdivisionColor : gridColor));

            grid.DefineVertex(Vector3(-halfSizeScaled, lineOffset, 0.0));
            grid.DefineColor(lineCenter ? gridXColor : (lineSubdiv ? gridSubdivisionColor : gridColor));
            grid.DefineVertex(Vector3(halfSizeScaled, lineOffset, 0.0));
            grid.DefineColor(lineCenter ? gridXColor : (lineSubdiv ? gridSubdivisionColor : gridColor));
        }

        lineOffset  += scale;
    }
    grid.Commit();
}

void CreateStatsBar()
{
    Font@ font = cache.GetResource("Font", "Fonts/Anonymous Pro.ttf");

    editorModeText = Text();
    ui.root.AddChild(editorModeText);
    renderStatsText = Text();
    ui.root.AddChild(renderStatsText);
    cameraPosText = Text();
    ui.root.AddChild(cameraPosText);

    if (ui.root.width >= 1200)
    {
        SetupStatsBarText(editorModeText, font, 4, 64, HA_LEFT, VA_TOP);
        SetupStatsBarText(renderStatsText, font, -4, 64, HA_RIGHT, VA_TOP);
    }
    else
    {
        SetupStatsBarText(editorModeText, font, 4, 64, HA_LEFT, VA_TOP);
        SetupStatsBarText(renderStatsText, font, 4, 78, HA_LEFT, VA_TOP);
    }

    SetupStatsBarText(cameraPosText, font, 0, 0, HA_LEFT, VA_BOTTOM);
}

void SetupStatsBarText(Text@ text, Font@ font, int x, int y, HorizontalAlignment hAlign, VerticalAlignment vAlign)
{
    text.position = IntVector2(x, y);
    text.horizontalAlignment = hAlign;
    text.verticalAlignment = vAlign;
    text.SetFont(font, 11);
    text.color = Color(1, 1, 0);
    text.priority = -100;
}

void UpdateStats(float timeStep)
{
    editorModeText.text = String(
        "Mode: " + editModeText[editMode] +
        "  Axis: " + axisModeText[axisMode] +
        "  Pick: " + pickModeText[pickMode] +
        "  Fill: " + fillModeText[fillMode] +
        "  Updates: " + (runUpdate ? "Running" : "Paused"));

    renderStatsText.text = String(
        "Tris: " + renderer.numPrimitives +
        "  Batches: " + renderer.numBatches +
        "  Lights: " + renderer.numLights[true] +
        "  Shadowmaps: " + renderer.numShadowMaps[true] +
        "  Occluders: " + renderer.numOccluders[true]);

    Vector3 cameraPos = cameraNode.position;
    String xText(cameraPos.x);
    String yText(cameraPos.y);
    String zText(cameraPos.z);
    xText.Resize(8);
    yText.Resize(8);
    zText.Resize(8);

    cameraPosText.text = String(
        "Pos: " + xText + " " + yText + " " + zText);

    editorModeText.size = editorModeText.minSize;
    renderStatsText.size = renderStatsText.minSize;
    cameraPosText.size = cameraPosText.minSize;
}

void UpdateView(float timeStep)
{
    // Move camera
    if (ui.focusElement is null && !input.keyDown[KEY_LCTRL])
    {
        float speedMultiplier = 1.0;
        if (input.keyDown[KEY_LSHIFT])
            speedMultiplier = cameraShiftSpeedMultiplier;

        if (input.keyDown['W'] || input.keyDown[KEY_UP])
        {
            cameraNode.TranslateRelative(Vector3(0, 0, cameraBaseSpeed) * timeStep * speedMultiplier);
            FadeUI();
        }
        if (input.keyDown['S'] || input.keyDown[KEY_DOWN])
        {
            cameraNode.TranslateRelative(Vector3(0, 0, -cameraBaseSpeed) * timeStep * speedMultiplier);
            FadeUI();
        }
        if (input.keyDown['A'] || input.keyDown[KEY_LEFT])
        {
            cameraNode.TranslateRelative(Vector3(-cameraBaseSpeed, 0, 0) * timeStep * speedMultiplier);
            FadeUI();
        }
        if (input.keyDown['D'] || input.keyDown[KEY_RIGHT])
        {
            cameraNode.TranslateRelative(Vector3(cameraBaseSpeed, 0, 0) * timeStep * speedMultiplier);
            FadeUI();
        }
        if (input.keyDown[KEY_PAGEUP])
        {
            cameraNode.Translate(Vector3(0, cameraBaseSpeed, 0) * timeStep * speedMultiplier);
            FadeUI();
        }
        if (input.keyDown[KEY_PAGEDOWN])
        {
            cameraNode.Translate(Vector3(0, -cameraBaseSpeed, 0) * timeStep * speedMultiplier);
            FadeUI();
        }
        if (input.keyDown['E'])
        {
            cameraNode.Translate(Vector3(0, cameraBaseSpeed, 0) * timeStep * speedMultiplier);
            FadeUI();
        }
        if (input.keyDown['Q'])
        {
            cameraNode.Translate(Vector3(0, -cameraBaseSpeed, 0) * timeStep * speedMultiplier);
            FadeUI();
        }
    }

    // Rotate/orbit camera
    if (input.mouseButtonDown[MOUSEB_RIGHT] || input.mouseButtonDown[MOUSEB_MIDDLE])
    {
        IntVector2 mouseMove = input.mouseMove;
        if (mouseMove.x != 0 || mouseMove.y != 0)
        {
            cameraYaw += mouseMove.x * cameraBaseRotationSpeed;
            cameraPitch += mouseMove.y * cameraBaseRotationSpeed;

            if (limitRotation)
                cameraPitch = Clamp(cameraPitch, -90.0, 90.0);

            Quaternion q = Quaternion(cameraPitch, cameraYaw, 0);
            cameraNode.rotation = q;
            if (input.mouseButtonDown[MOUSEB_MIDDLE] && editNode !is null)
            {
                Vector3 d = cameraNode.worldPosition - editNode.worldPosition;
                cameraNode.worldPosition = editNode.worldPosition - q * Vector3(0.0, 0.0, d.length);
                orbiting = true;
            }
            
            FadeUI();
        }
    }
    if (orbiting && !input.mouseButtonDown[MOUSEB_MIDDLE])
        orbiting = false;

    // Move/rotate/scale object
    if (!editNodes.empty && editMode != EDIT_SELECT && ui.focusElement is null && input.keyDown[KEY_LCTRL])
    {
        Vector3 adjust(0, 0, 0);
        if (input.keyDown[KEY_UP])
            adjust.z = 1;
        if (input.keyDown[KEY_DOWN])
            adjust.z = -1;
        if (input.keyDown[KEY_LEFT])
            adjust.x = -1;
        if (input.keyDown[KEY_RIGHT])
            adjust.x = 1;
        if (input.keyDown[KEY_PAGEUP])
            adjust.y = 1;
        if (input.keyDown[KEY_PAGEDOWN])
            adjust.y = -1;
        if (editMode == EDIT_SCALE)
        {
            if (input.keyDown[KEY_ADD])
                adjust = Vector3(1, 1, 1);
            if (input.keyDown[KEY_SUBTRACT])
                adjust = Vector3(-1, -1, -1);
        }

        if (adjust == Vector3(0, 0, 0))
            return;

        bool moved = false;
        adjust *= timeStep * 10;

        switch (editMode)
        {
        case EDIT_MOVE:
            if (!moveSnap)
                moved = MoveNodes(adjust * moveStep);
            break;

        case EDIT_ROTATE:
            if (!rotateSnap)
                moved = RotateNodes(adjust * rotateStep);
            break;

        case EDIT_SCALE:
            if (!scaleSnap)
                moved = ScaleNodes(adjust * scaleStep);
            break;
        }

        if (moved)
            UpdateNodeAttributes();
    }
}

void SteppedObjectManipulation(int key)
{
    if (editNodes.empty || editMode == EDIT_SELECT)
        return;

    // Do not react in non-snapped mode, because that is handled in frame update
    if (editMode == EDIT_MOVE && !moveSnap)
        return;
    if (editMode == EDIT_ROTATE && !rotateSnap)
        return;
    if (editMode == EDIT_SCALE && !scaleSnap)
        return;

    Vector3 adjust(0, 0, 0);
    if (key == KEY_UP)
        adjust.z = 1;
    if (key == KEY_DOWN)
        adjust.z = -1;
    if (key == KEY_LEFT)
        adjust.x = -1;
    if (key == KEY_RIGHT)
        adjust.x = 1;
    if (key == KEY_PAGEUP)
        adjust.y = 1;
    if (key == KEY_PAGEDOWN)
        adjust.y = -1;
    if (editMode == EDIT_SCALE)
    {
        if (key == KEY_ADD)
            adjust = Vector3(1, 1, 1);
        if (key == KEY_SUBTRACT)
            adjust = Vector3(-1, -1, -1);
    }

    if (adjust == Vector3(0, 0, 0))
        return;

    bool moved = false;

    switch (editMode)
    {
    case EDIT_MOVE:
        moved = MoveNodes(adjust);
        break;

    case EDIT_ROTATE:
        {
            float rotateStepScaled = rotateStep * snapScale;
            moved = RotateNodes(adjust * rotateStepScaled);
        }
        break;

    case EDIT_SCALE:
        {
            float scaleStepScaled = scaleStep * snapScale;
            moved = ScaleNodes(adjust * scaleStepScaled);
        }
        break;
    }

    if (moved)
        UpdateNodeAttributes();
}


void HandlePostRenderUpdate()
{
    DebugRenderer@ debug = editorScene.debugRenderer;
    if (debug is null || orbiting)
        return;

    // Visualize the currently selected nodes as their local axes + the first drawable component
    for (uint i = 0; i < selectedNodes.length; ++i)
    {
        Node@ node = selectedNodes[i];
        debug.AddNode(node, 1.0, false);
        for (uint j = 0; j < node.numComponents; ++j)
        {
            Drawable@ drawable = cast<Drawable>(node.components[j]);
            if (drawable !is null)
            {
                drawable.DrawDebugGeometry(debug, false);
                break;
            }
        }
    }

    // Visualize the currently selected components
    for (uint i = 0; i < selectedComponents.length; ++i)
        selectedComponents[i].DrawDebugGeometry(debug, false);

    // Visualize the currently selected UI-elements
    for (uint i = 0; i < selectedUIElements.length; ++i)
        ui.DebugDraw(selectedUIElements[i]);

    if (renderingDebug)
        renderer.DrawDebugGeometry(false);
    if (physicsDebug && editorScene.physicsWorld !is null)
        editorScene.physicsWorld.DrawDebugGeometry(true);
    if (octreeDebug && editorScene.octree !is null)
        editorScene.octree.DrawDebugGeometry(true);

    ViewRaycast(false);
}

void ViewMouseClick()
{
    ViewRaycast(true);
}

void ViewRaycast(bool mouseClick)
{
    // Ignore if UI has modal element
    if (ui.HasModalElement())
        return;

    // Do not raycast / change selection if hovering over the gizmo
    if (IsGizmoSelected())
        return;

    DebugRenderer@ debug = editorScene.debugRenderer;

    IntVector2 pos = ui.cursorPosition;
    UIElement@ elementAtPos = ui.GetElementAt(pos, pickMode != PICK_UI_ELEMENTS);
    if (pickMode == PICK_UI_ELEMENTS)
    {
        bool leftClick = mouseClick && input.mouseButtonPress[MOUSEB_LEFT];
        bool multiselect = input.qualifierDown[QUAL_CTRL];

        // Only interested in user-created UI elements
        if (elementAtPos !is editorUIElement && elementAtPos.GetElementEventSender() is editorUIElement)
        {
            ui.DebugDraw(elementAtPos);

            if (leftClick)
                SelectUIElement(elementAtPos, multiselect);
        }
        // If clicked on emptiness in non-multiselect mode, clear the selection
        else if (leftClick && !multiselect && ui.GetElementAt(pos) is null)
            hierarchyList.ClearSelection();

        return;
    }

    // Do not raycast / change selection if hovering over a UI element when not in PICK_UI_ELEMENTS Mode
    if (elementAtPos !is null)
        return;

    Ray cameraRay = camera.GetScreenRay(float(pos.x) / graphics.width, float(pos.y) / graphics.height);
    Component@ selectedComponent;

    if (pickMode != PICK_RIGIDBODIES)
    {
        if (editorScene.octree is null)
            return;

        RayQueryResult result = editorScene.octree.RaycastSingle(cameraRay, RAY_TRIANGLE, camera.farClip,
            pickModeDrawableFlags[pickMode], 0x7fffffff);
        if (result.drawable !is null)
        {
            Drawable@ drawable = result.drawable;
            // If selecting a terrain patch, select the parent terrain instead
            if (drawable.typeName != "TerrainPatch")
            {
                selectedComponent = drawable;
                if (debug !is null)
                {
                    debug.AddNode(drawable.node, 1.0, false);
                    drawable.DrawDebugGeometry(debug, false);
                }
            }
            else if (drawable.node.parent !is null)
                selectedComponent = drawable.node.parent.GetComponent("Terrain");
        }
    }
    else
    {
        if (editorScene.physicsWorld is null)
            return;

        // If we are not running the actual physics update, refresh collisions before raycasting
        if (!runUpdate)
            editorScene.physicsWorld.UpdateCollisions();

        PhysicsRaycastResult result = editorScene.physicsWorld.RaycastSingle(cameraRay, camera.farClip);
        if (result.body !is null)
        {
            RigidBody@ body = result.body;
            if (debug !is null)
            {
                debug.AddNode(body.node, 1.0, false);
                body.DrawDebugGeometry(debug, false);
            }
            selectedComponent = body;
        }
    }

    if (mouseClick && input.mouseButtonPress[MOUSEB_LEFT])
    {
        bool multiselect = input.qualifierDown[QUAL_CTRL];
        if (selectedComponent !is null)
        {
            if (input.qualifierDown[QUAL_SHIFT])
            {
                // If we are selecting components, but have nodes in existing selection, do not multiselect to prevent confusion
                if (!selectedNodes.empty)
                    multiselect = false;
                SelectComponent(selectedComponent, multiselect);
            }
            else
            {
                // If we are selecting nodes, but have components in existing selection, do not multiselect to prevent confusion
                if (!selectedComponents.empty)
                    multiselect = false;
                SelectNode(selectedComponent.node, multiselect);
            }
        }
        else
        {
            // If clicked on emptiness in non-multiselect mode, clear the selection
            if (!multiselect)
               SelectComponent(null, false);
        }
    }
}

Vector3 GetNewNodePosition()
{
    return cameraNode.position + cameraNode.worldRotation * Vector3(0, 0, newNodeDistance);
}

int GetShadowResolution()
{
    if (!renderer.drawShadows)
        return 0;
    int level = 1;
    int res = renderer.shadowMapSize;
    while (res > 512)
    {
        res >>= 1;
        ++level;
    }
    if (level > 3)
        level = 3;

    return level;
}

void SetShadowResolution(int level)
{
    if (level <= 0)
    {
        renderer.drawShadows = false;
        return;
    }
    else
    {
        renderer.drawShadows = true;
        renderer.shadowMapSize = 256 << level;
    }
}

void ToggleRenderingDebug()
{
    renderingDebug = !renderingDebug;
}

void TogglePhysicsDebug()
{
    physicsDebug = !physicsDebug;
}

void ToggleOctreeDebug()
{
    octreeDebug = !octreeDebug;
}

bool StopTestAnimation()
{
    testAnimState = null;
    return true;
}
