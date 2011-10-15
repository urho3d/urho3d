// Urho3D editor view & camera functions

Node@ cameraNode;
Camera@ camera;
Window@ settingsDialog;

enum ObjectMoveMode
{
    OBJ_MOVE = 0,
    OBJ_ROTATE,
    OBJ_SCALE
}

enum AxisMode
{
    AXIS_WORLD = 0,
    AXIS_LOCAL
}

Text@ editorModeText;
Text@ renderStatsText;
Text@ cameraPosText;

ObjectMoveMode moveMode = OBJ_MOVE;
AxisMode axisMode = AXIS_WORLD;

float cameraBaseSpeed = 10;
float cameraBaseRotationSpeed = 0.2;
float cameraShiftSpeedMultiplier = 5;
float cameraYaw = 0;
float cameraPitch = 0;
float newNodeDistance = 20;
float moveStep = 0.5;
float rotateStep = 5;
float scaleStep = 0.1;
bool moveSnap = false;
bool rotateSnap = false;
bool scaleSnap = false;

Array<String> moveModeText = {
    "Move",
    "Rotate",
    "Scale"
};

Array<String> axisModeText = {
    "World",
    "Local"
};

Array<String> pickModeText = {
    "Geometries",
    "Lights",
    "Zones",
    "Col.shapes"
};

void CreateCamera()
{
    // Note: the camera will not be bound into the scene, so that it is not listed, and does not get deleted
    cameraNode = Node();
    camera = cameraNode.CreateComponent("Camera");
    ResetCamera();

    renderer.viewports[0] = Viewport(editorScene, camera);
}

void ResetCamera()
{
    cameraNode.position = Vector3(0, 10, 0);
    cameraNode.rotation = Quaternion();
    cameraPitch = 0;
    cameraYaw = 0;
}

void CreateStatsBar()
{
    Font@ font = cache.GetResource("Font", "Fonts/Anonymous Pro.ttf");

    editorModeText = Text();
    renderStatsText = Text();
    cameraPosText = Text();

    if (ui.root.width >= 1024)
    {
        SetupStatsBarText(editorModeText, font, 0, 20, HA_LEFT, VA_TOP);
        SetupStatsBarText(renderStatsText, font, 0, 20, HA_RIGHT, VA_TOP);
    }
    else
    {
        SetupStatsBarText(editorModeText, font, 0, 20, HA_LEFT, VA_TOP);
        SetupStatsBarText(renderStatsText, font, 0, 32, HA_LEFT, VA_TOP);
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
    ui.root.AddChild(text);
}

void UpdateStats(float timeStep)
{
    editorModeText.text = String(
        "Mode: " + moveModeText[moveMode] +
        "  Axis: " + axisModeText[axisMode] +
        "  Pick: " + pickModeText[pickMode] +
        "  Updates: " + (runUpdate ? "Running" : "Paused"));

    renderStatsText.text = String(
        "Tris: " + renderer.numPrimitives +
        "  Batches: " + renderer.numBatches +
        "  Lights: " + renderer.numLights[true] +
        "  Shadowmaps: " + renderer.numShadowMaps[true] +
        "  Occluders: " + renderer.numOccluders[true] + " / " + renderer.numShadowOccluders[true]);

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

void MoveCamera(float timeStep)
{
    // Move camera
    if (ui.focusElement is null && !input.keyDown[KEY_LCTRL])
    {
        float speedMultiplier = 1.0;
        if (input.keyDown[KEY_LSHIFT])
            speedMultiplier = cameraShiftSpeedMultiplier;

        if (input.keyDown['W'] || input.keyDown[KEY_UP])
            cameraNode.TranslateRelative(Vector3(0, 0, cameraBaseSpeed) * timeStep * speedMultiplier);
        if (input.keyDown['S'] || input.keyDown[KEY_DOWN])
            cameraNode.TranslateRelative(Vector3(0, 0, -cameraBaseSpeed) * timeStep * speedMultiplier);
        if (input.keyDown['A'] || input.keyDown[KEY_LEFT])
            cameraNode.TranslateRelative(Vector3(-cameraBaseSpeed, 0, 0) * timeStep * speedMultiplier);
        if (input.keyDown['D'] || input.keyDown[KEY_RIGHT])
            cameraNode.TranslateRelative(Vector3(cameraBaseSpeed, 0, 0) * timeStep * speedMultiplier);
    }

    // Rotate camera
    if (input.mouseButtonDown[MOUSEB_RIGHT])
    {
        IntVector2 mouseMove = input.mouseMove;
        if (mouseMove.x != 0 || mouseMove.y != 0)
        {
            cameraYaw += mouseMove.x * cameraBaseRotationSpeed;
            cameraPitch += mouseMove.y * cameraBaseRotationSpeed;
            if (cameraPitch < -90.0)
                cameraPitch = -90.0;
            if (cameraPitch > 90.0)
                cameraPitch = 90.0;

            cameraNode.rotation = Quaternion(cameraPitch, cameraYaw, 0);
        }
    }

    // Move/rotate/scale object
    if (!editNodes.empty && ui.focusElement is null && input.keyDown[KEY_LCTRL])
    {
        bool changed = false;
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
        if (moveMode == OBJ_SCALE)
        {
            if (input.keyDown[KEY_ADD])
                adjust = Vector3(1, 1, 1);
            if (input.keyDown[KEY_SUBTRACT])
                adjust = Vector3(-1, -1, -1);
        }

        if (adjust != Vector3(0, 0, 0))
        {
            adjust *= timeStep * 10;

            if (input.keyDown[KEY_LSHIFT])
                adjust *= cameraShiftSpeedMultiplier;

            switch (moveMode)
            {
            case OBJ_MOVE:
                if (!moveSnap)
                {
                    for (uint i = 0; i < editNodes.length; ++i)
                    {
                        Node@ node = editNodes[i];
                        Vector3 nodeAdjust = adjust;
                        if (axisMode == AXIS_LOCAL)
                            nodeAdjust = node.worldRotation * nodeAdjust;
                        if (node.parent !is null)
                            nodeAdjust = node.parent.WorldToLocal(Vector4(nodeAdjust, 0.0));
                        node.position = node.position + nodeAdjust * moveStep;
                    }
                    changed = true;
                }
                break;

            case OBJ_ROTATE:
                if (!rotateSnap)
                {
                    for (uint i = 0; i < editNodes.length; ++i)
                    {
                        Node@ node = editNodes[i];
                        Vector3 euler = node.rotation.eulerAngles;
                        euler.x += adjust.z * rotateStep;
                        euler.y += adjust.x * rotateStep;
                        euler.z += adjust.y * rotateStep;
                        node.rotation = Quaternion(euler);
                    }
                    changed = true;
                }
                break;

            case OBJ_SCALE:
                if (!scaleSnap)
                {
                    for (uint i = 0; i < editNodes.length; ++i)
                    {
                        Node@ node = editNodes[i];
                        node.scale = node.scale + adjust * scaleStep;
                    }
                    changed = true;
                }
                break;
            }
        }

        if (changed)
            UpdateAttributes(false);
    }
}

void SteppedObjectManipulation(int key)
{
    if (editNodes.empty)
        return;

    // Do not react in non-snapped mode, because that is handled in frame update
    if (moveMode == OBJ_MOVE && !moveSnap)
        return;
    if (moveMode == OBJ_ROTATE && !rotateSnap)
        return;
    if (moveMode == OBJ_SCALE && !scaleSnap)
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
    if (moveMode == OBJ_SCALE)
    {
        if (key == KEY_ADD)
            adjust = Vector3(1, 1, 1);
        if (key == KEY_SUBTRACT)
            adjust = Vector3(-1, -1, -1);
    }

    if (adjust == Vector3(0, 0, 0))
        return;

    switch (moveMode)
    {
    case OBJ_MOVE:
        for (uint i = 0; i < editNodes.length; ++i)
        {
            Node@ node = editNodes[i];
            Vector3 nodeAdjust = adjust;
            if (axisMode == AXIS_LOCAL)
                nodeAdjust = node.worldRotation * nodeAdjust;
            if (node.parent !is null)
                nodeAdjust = node.parent.WorldToLocal(Vector4(nodeAdjust, 0.0));

            Vector3 pos = node.position;
            if (adjust.x != 0)
            {
                pos.x += adjust.x * moveStep;
                pos.x = Floor(pos.x / moveStep + 0.5) * moveStep;
            }
            if (adjust.y != 0)
            {
                pos.y += adjust.y * moveStep;
                pos.y = Floor(pos.y / moveStep + 0.5) * moveStep;
            }
            if (adjust.z != 0)
            {
                pos.z += adjust.z * moveStep;
                pos.z = Floor(pos.z / moveStep + 0.5) * moveStep;
            }
            node.position = pos;
        }
        break;

    case OBJ_ROTATE:
        for (uint i = 0; i < editNodes.length; ++i)
        {
            Node@ node = editNodes[i];
            Vector3 rot = node.rotation.eulerAngles;
            if (adjust.z != 0)
            {
                rot.x += adjust.z * rotateStep;
                rot.x = Floor(rot.x / rotateStep + 0.5) * rotateStep;
            }
            if (adjust.x != 0)
            {
                rot.y += adjust.x * rotateStep;
                rot.y = Floor(rot.y / rotateStep + 0.5) * rotateStep;
            }
            if (adjust.y != 0)
            {
                rot.z += adjust.y * rotateStep;
                rot.z = Floor(rot.z / rotateStep + 0.5) * rotateStep;
            }
            node.rotation = Quaternion(rot);
        }
        break;

    case OBJ_SCALE:
        for (uint i = 0; i < editNodes.length; ++i)
        {
            Node@ node = editNodes[i];
            Vector3 scale = node.scale;
            if (adjust.x != 0)
            {
                scale.x += adjust.x * scaleStep;
                scale.x = Floor(scale.x / scaleStep + 0.5) * scaleStep;
            }
            if (adjust.y != 0)
            {
                scale.y += adjust.y * scaleStep;
                scale.y = Floor(scale.y / scaleStep + 0.5) * scaleStep;
            }
            if (adjust.z != 0)
            {
                scale.z += adjust.z * scaleStep;
                scale.z = Floor(scale.z / scaleStep + 0.5) * scaleStep;
            }
            node.scale = scale;
        }
        break;
    }

    UpdateAttributes(false);
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