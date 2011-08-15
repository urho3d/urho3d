// Urho3D editor camera functions

Node@ cameraNode;
Camera@ camera;
Window@ editorSettingsDialog;

enum ObjectMoveMode
{
    OBJ_MOVE = 0,
    OBJ_ROTATE,
    OBJ_SCALE
}

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
ObjectMoveMode moveMode = OBJ_MOVE;

Text@ renderStatsText;
Text@ cameraPosText;
bool subscribedToCameraEdits = false;

Array<String> moveModeText = {
    "Move    ",
    "Rotate  ",
    "Scale   "
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

void CreateEditorSettingsDialog()
{
    if (!(editorSettingsDialog is null))
        return;
    
    editorSettingsDialog = ui.LoadLayout(cache.GetResource("XMLFile", "UI/EditorSettingsDialog.xml"), uiStyle);
    ui.root.AddChild(editorSettingsDialog);
    CenterDialog(editorSettingsDialog);
    UpdateEditorSettingsDialog();
    HideEditorSettingsDialog();
}

void UpdateEditorSettingsDialog()
{
    if (editorSettingsDialog is null)
        return;

    LineEdit@ nearClipEdit = editorSettingsDialog.GetChild("NearClipEdit", true);
    nearClipEdit.text = String(camera.nearClip);
    
    LineEdit@ farClipEdit = editorSettingsDialog.GetChild("FarClipEdit", true);
    farClipEdit.text = String(camera.farClip);
    
    LineEdit@ fovEdit = editorSettingsDialog.GetChild("FOVEdit", true);
    fovEdit.text = String(camera.fov);

    LineEdit@ speedEdit = editorSettingsDialog.GetChild("SpeedEdit", true);
    speedEdit.text = String(cameraBaseSpeed);

    LineEdit@ distanceEdit = editorSettingsDialog.GetChild("DistanceEdit", true);
    distanceEdit.text = String(newNodeDistance);

    LineEdit@ moveStepEdit = editorSettingsDialog.GetChild("MoveStepEdit", true);
    moveStepEdit.text = String(moveStep);
    CheckBox@ moveSnapToggle = editorSettingsDialog.GetChild("MoveSnapToggle", true);
    moveSnapToggle.checked = moveSnap;

    LineEdit@ rotateStepEdit = editorSettingsDialog.GetChild("RotateStepEdit", true);
    rotateStepEdit.text = String(rotateStep);
    CheckBox@ rotateSnapToggle = editorSettingsDialog.GetChild("RotateSnapToggle", true);
    rotateSnapToggle.checked = rotateSnap;

    LineEdit@ scaleStepEdit = editorSettingsDialog.GetChild("ScaleStepEdit", true);
    scaleStepEdit.text = String(scaleStep);
    CheckBox@ scaleSnapToggle = editorSettingsDialog.GetChild("ScaleSnapToggle", true);
    scaleSnapToggle.checked = scaleSnap;

    CheckBox@ localIDToggle = editorSettingsDialog.GetChild("LocalIDToggle", true);
    localIDToggle.checked = useLocalIDs;

    if (!subscribedToCameraEdits)
    {
        SubscribeToEvent(nearClipEdit, "TextChanged", "EditCameraNearClip");
        SubscribeToEvent(nearClipEdit, "TextFinished", "EditCameraNearClip");
        SubscribeToEvent(farClipEdit, "TextChanged", "EditCameraFarClip");
        SubscribeToEvent(farClipEdit, "TextFinished", "EditCameraFarClip");
        SubscribeToEvent(fovEdit, "TextChanged", "EditCameraFOV");
        SubscribeToEvent(fovEdit, "TextFinished", "EditCameraFOV");
        SubscribeToEvent(speedEdit, "TextChanged", "EditCameraSpeed");
        SubscribeToEvent(speedEdit, "TextFinished", "EditCameraSpeed");
        SubscribeToEvent(distanceEdit, "TextChanged", "EditNewNodeDistance");
        SubscribeToEvent(distanceEdit, "TextFinished", "EditNewNodeDistance");
        SubscribeToEvent(moveStepEdit, "TextChanged", "EditMoveStep");
        SubscribeToEvent(moveStepEdit, "TextFinished", "EditMoveStep");
        SubscribeToEvent(rotateStepEdit, "TextChanged", "EditRotateStep");
        SubscribeToEvent(rotateStepEdit, "TextFinished", "EditRotateStep");
        SubscribeToEvent(scaleStepEdit, "TextChanged", "EditScaleStep");
        SubscribeToEvent(scaleStepEdit, "TextFinished", "EditScaleStep");
        SubscribeToEvent(moveSnapToggle, "Toggled", "EditMoveSnap");
        SubscribeToEvent(rotateSnapToggle, "Toggled", "EditRotateSnap");
        SubscribeToEvent(scaleSnapToggle, "Toggled", "EditScaleSnap");
        SubscribeToEvent(localIDToggle, "Toggled", "EditUseLocalIDs");
        SubscribeToEvent(editorSettingsDialog.GetChild("CloseButton", true), "Released", "HideEditorSettingsDialog");
        subscribedToCameraEdits = true;
    }
}

void ShowEditorSettingsDialog()
{
    UpdateEditorSettingsDialog();
    editorSettingsDialog.visible = true;
    editorSettingsDialog.BringToFront();
}

void HideEditorSettingsDialog()
{
    editorSettingsDialog.visible = false;
}

void EditCameraNearClip(StringHash eventType, VariantMap& eventData)
{
    LineEdit@ edit = eventData["Element"].GetUIElement();
    camera.nearClip = edit.text.ToFloat();
    if (eventType == StringHash("TextFinished"))
        edit.text = String(camera.nearClip);
}

void EditCameraFarClip(StringHash eventType, VariantMap& eventData)
{
    LineEdit@ edit = eventData["Element"].GetUIElement();
    camera.farClip = edit.text.ToFloat();
    if (eventType == StringHash("TextFinished"))
        edit.text = String(camera.farClip);
}

void EditCameraFOV(StringHash eventType, VariantMap& eventData)
{
    LineEdit@ edit = eventData["Element"].GetUIElement();
    camera.fov = edit.text.ToFloat();
    if (eventType == StringHash("TextFinished"))
        edit.text = String(camera.fov);
}

void EditCameraSpeed(StringHash eventType, VariantMap& eventData)
{
    LineEdit@ edit = eventData["Element"].GetUIElement();
    cameraBaseSpeed = Max(edit.text.ToFloat(), 1.0);
    if (eventType == StringHash("TextFinished"))
        edit.text = String(cameraBaseSpeed);
}

void EditNewNodeDistance(StringHash eventType, VariantMap& eventData)
{
    LineEdit@ edit = eventData["Element"].GetUIElement();
    newNodeDistance = Max(edit.text.ToFloat(), 0.0);
    if (eventType == StringHash("TextFinished"))
        edit.text = String(newNodeDistance);
}

void EditMoveStep(StringHash eventType, VariantMap& eventData)
{
    LineEdit@ edit = eventData["Element"].GetUIElement();
    moveStep = Max(edit.text.ToFloat(), 0.0);
    if (eventType == StringHash("TextFinished"))
        edit.text = String(moveStep);
}

void EditRotateStep(StringHash eventType, VariantMap& eventData)
{
    LineEdit@ edit = eventData["Element"].GetUIElement();
    rotateStep = Max(edit.text.ToFloat(), 0.0);
    if (eventType == StringHash("TextFinished"))
        edit.text = String(rotateStep);
}

void EditScaleStep(StringHash eventType, VariantMap& eventData)
{
    LineEdit@ edit = eventData["Element"].GetUIElement();
    scaleStep = Max(edit.text.ToFloat(), 0.0);
    if (eventType == StringHash("TextFinished"))
        edit.text = String(scaleStep);
}

void EditMoveSnap(StringHash eventType, VariantMap& eventData)
{
    CheckBox@ edit = eventData["Element"].GetUIElement();
    moveSnap = edit.checked;
}

void EditRotateSnap(StringHash eventType, VariantMap& eventData)
{
    CheckBox@ edit = eventData["Element"].GetUIElement();
    rotateSnap = edit.checked;
}

void EditScaleSnap(StringHash eventType, VariantMap& eventData)
{
    CheckBox@ edit = eventData["Element"].GetUIElement();
    scaleSnap = edit.checked;
}

void EditUseLocalIDs(StringHash eventType, VariantMap& eventData)
{
    CheckBox@ edit = eventData["Element"].GetUIElement();
    useLocalIDs = edit.checked;
}

void CreateStatsBar()
{
    Font@ font = cache.GetResource("Font", "Fonts/Anonymous Pro.ttf");

    renderStatsText = Text();
    cameraPosText = Text();

    if (ui.root.width >= 1024)
    {
        SetupStatsBarText(renderStatsText, font, 0, 20, HA_LEFT);
        SetupStatsBarText(cameraPosText, font, 0, 20, HA_RIGHT);
    }
    else
    {
        SetupStatsBarText(renderStatsText, font, 0, 20, HA_LEFT);
        SetupStatsBarText(cameraPosText, font, 0, 32, HA_LEFT);
    }
}

void SetupStatsBarText(Text@ text, Font@ font, int x, int y, HorizontalAlignment align)
{
    text.position = IntVector2(x, y);
    text.horizontalAlignment = align;
    text.SetFont(font, 11);
    text.color = Color(1, 1, 0);
    text.priority = -100;
    ui.root.AddChild(text);
}

void UpdateStats(float timeStep)
{
    renderStatsText.text = String(
        "Tris: " + renderer.numPrimitives +
        " Batches: " + renderer.numBatches +
        " Lights: " + renderer.numLights[true] +
        " Shadowmaps: " + renderer.numShadowMaps[true] +
        " Occluders: " + renderer.numOccluders[true] + " / " + renderer.numShadowOccluders[true]);

    Vector3 cameraPos = cameraNode.position;
    String xText(cameraPos.x);
    String yText(cameraPos.y);
    String zText(cameraPos.z);
    xText.Resize(8);
    yText.Resize(8);
    zText.Resize(8);
    
    cameraPosText.text = moveModeText[moveMode] + "Physics: " + (runPhysics ? "Running " : "Paused  ") + " Camera pos: " + xText
        + " " + yText + " " + zText + " ";
    
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
    if (selectedNode !is null && ui.focusElement is null && input.keyDown[KEY_LCTRL])
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
                    selectedNode.position = selectedNode.position + adjust * moveStep;
                    changed = true;
                }
                break;

            case OBJ_ROTATE:
                if (!rotateSnap)
                {
                    Vector3 euler = selectedNode.rotation.eulerAngles;
                    euler.x += adjust.z * rotateStep;
                    euler.y += adjust.x * rotateStep;
                    euler.z += adjust.y * rotateStep;
                    selectedNode.rotation = Quaternion(euler);
                    changed = true;
                }
                break;

            case OBJ_SCALE:
                if (!scaleSnap)
                {
                    selectedNode.scale = selectedNode.scale + adjust * scaleStep;
                    changed = true;
                }
                break;
            }
        }

        if (changed)
            UpdateAttributes();
    }
}

void SteppedObjectManipulation(int key)
{
    if (selectedNode is null)
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
        {
            Vector3 pos = selectedNode.position;
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
            selectedNode.position = pos;
        }
        break;

    case OBJ_ROTATE:
        {
            Vector3 rot = selectedNode.rotation.eulerAngles;
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
            selectedNode.rotation = Quaternion(rot);
        }
        break;

    case OBJ_SCALE:
        {
            Vector3 scale = selectedNode.scale;
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
            selectedNode.scale = scale;
        }
        break;
    }

    UpdateAttributes();
}

Vector3 GetNewNodePosition()
{
    return cameraNode.position + cameraNode.worldRotation * Vector3(0, 0, newNodeDistance);
}
