// Urho3D editor camera functions

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
bool subscribedToEditorSettings = false;

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

void CreateEditorSettingsDialog()
{
    if (!(settingsDialog is null))
        return;
    
    settingsDialog = ui.LoadLayout(cache.GetResource("XMLFile", "UI/EditorSettingsDialog.xml"), uiStyle);
    ui.root.AddChild(settingsDialog);
    CenterDialog(settingsDialog);
    UpdateEditorSettingsDialog();
    HideEditorSettingsDialog();
}

void UpdateEditorSettingsDialog()
{
    if (settingsDialog is null)
        return;

    LineEdit@ nearClipEdit = settingsDialog.GetChild("NearClipEdit", true);
    nearClipEdit.text = String(camera.nearClip);
    
    LineEdit@ farClipEdit = settingsDialog.GetChild("FarClipEdit", true);
    farClipEdit.text = String(camera.farClip);
    
    LineEdit@ fovEdit = settingsDialog.GetChild("FOVEdit", true);
    fovEdit.text = String(camera.fov);

    LineEdit@ speedEdit = settingsDialog.GetChild("SpeedEdit", true);
    speedEdit.text = String(cameraBaseSpeed);

    LineEdit@ distanceEdit = settingsDialog.GetChild("DistanceEdit", true);
    distanceEdit.text = String(newNodeDistance);

    LineEdit@ moveStepEdit = settingsDialog.GetChild("MoveStepEdit", true);
    moveStepEdit.text = String(moveStep);
    CheckBox@ moveSnapToggle = settingsDialog.GetChild("MoveSnapToggle", true);
    moveSnapToggle.checked = moveSnap;

    LineEdit@ rotateStepEdit = settingsDialog.GetChild("RotateStepEdit", true);
    rotateStepEdit.text = String(rotateStep);
    CheckBox@ rotateSnapToggle = settingsDialog.GetChild("RotateSnapToggle", true);
    rotateSnapToggle.checked = rotateSnap;

    LineEdit@ scaleStepEdit = settingsDialog.GetChild("ScaleStepEdit", true);
    scaleStepEdit.text = String(scaleStep);
    CheckBox@ scaleSnapToggle = settingsDialog.GetChild("ScaleSnapToggle", true);
    scaleSnapToggle.checked = scaleSnap;

    CheckBox@ localIDToggle = settingsDialog.GetChild("LocalIDToggle", true);
    localIDToggle.checked = useLocalIDs;

    DropDownList@ pickModeEdit = settingsDialog.GetChild("PickModeEdit", true);
    pickModeEdit.selection = pickMode;

    DropDownList@ textureQualityEdit = settingsDialog.GetChild("TextureQualityEdit", true);
    textureQualityEdit.selection = renderer.textureQuality;

    DropDownList@ materialQualityEdit = settingsDialog.GetChild("MaterialQualityEdit", true);
    materialQualityEdit.selection = renderer.materialQuality;

    DropDownList@ shadowResolutionEdit = settingsDialog.GetChild("ShadowResolutionEdit", true);
    shadowResolutionEdit.selection = GetShadowResolution();

    DropDownList@ shadowQualityEdit = settingsDialog.GetChild("ShadowQualityEdit", true);
    shadowQualityEdit.selection = renderer.shadowQuality;

    LineEdit@ maxOccluderTrianglesEdit = settingsDialog.GetChild("MaxOccluderTrianglesEdit", true);
    maxOccluderTrianglesEdit.text = String(renderer.maxOccluderTriangles);

    CheckBox@ specularLightingToggle = settingsDialog.GetChild("SpecularLightingToggle", true);
    specularLightingToggle.checked = renderer.specularLighting;

    CheckBox@ dynamicInstancingToggle = settingsDialog.GetChild("DynamicInstancingToggle", true);
    dynamicInstancingToggle.checked = renderer.dynamicInstancing;

    CheckBox@ lightStencilMaskingToggle = settingsDialog.GetChild("LightStencilMaskingToggle", true);
    lightStencilMaskingToggle.checked = renderer.lightStencilMasking;

    CheckBox@ frameLimiterToggle = settingsDialog.GetChild("FrameLimiterToggle", true);
    frameLimiterToggle.checked = engine.maxFps > 0;

    if (!subscribedToEditorSettings)
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
        SubscribeToEvent(pickModeEdit, "ItemSelected", "EditPickMode");
        SubscribeToEvent(textureQualityEdit, "ItemSelected", "EditTextureQuality");
        SubscribeToEvent(materialQualityEdit, "ItemSelected", "EditMaterialQuality");
        SubscribeToEvent(shadowResolutionEdit, "ItemSelected", "EditShadowResolution");
        SubscribeToEvent(shadowQualityEdit, "ItemSelected", "EditShadowQuality");
        SubscribeToEvent(maxOccluderTrianglesEdit, "TextChanged", "EditMaxOccluderTriangles");
        SubscribeToEvent(maxOccluderTrianglesEdit, "TextFinished", "EditMaxOccluderTriangles");
        SubscribeToEvent(specularLightingToggle, "Toggled", "EditSpecularLighting");
        SubscribeToEvent(dynamicInstancingToggle, "Toggled", "EditDynamicInstancing");
        SubscribeToEvent(lightStencilMaskingToggle, "Toggled", "EditLightStencilMasking");
        SubscribeToEvent(frameLimiterToggle, "Toggled", "EditFrameLimiter");
        SubscribeToEvent(settingsDialog.GetChild("CloseButton", true), "Released", "HideEditorSettingsDialog");
        subscribedToEditorSettings = true;
    }
}

void ShowEditorSettingsDialog()
{
    UpdateEditorSettingsDialog();
    settingsDialog.visible = true;
    settingsDialog.BringToFront();
}

void HideEditorSettingsDialog()
{
    settingsDialog.visible = false;
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

void EditPickMode(StringHash eventType, VariantMap& eventData)
{
    DropDownList@ edit = eventData["Element"].GetUIElement();
    pickMode = edit.selection;
}

void EditTextureQuality(StringHash eventType, VariantMap& eventData)
{
    DropDownList@ edit = eventData["Element"].GetUIElement();
    renderer.textureQuality = edit.selection;
}

void EditMaterialQuality(StringHash eventType, VariantMap& eventData)
{
    DropDownList@ edit = eventData["Element"].GetUIElement();
    renderer.materialQuality = edit.selection;
}

void EditShadowResolution(StringHash eventType, VariantMap& eventData)
{
    DropDownList@ edit = eventData["Element"].GetUIElement();
    SetShadowResolution(edit.selection);
}

void EditShadowQuality(StringHash eventType, VariantMap& eventData)
{
    DropDownList@ edit = eventData["Element"].GetUIElement();
    renderer.shadowQuality = edit.selection;
}

void EditMaxOccluderTriangles(StringHash eventType, VariantMap& eventData)
{
    LineEdit@ edit = eventData["Element"].GetUIElement();
    renderer.maxOccluderTriangles = edit.text.ToInt();
    if (eventType == StringHash("TextFinished"))
        edit.text = String(renderer.maxOccluderTriangles);
}

void EditSpecularLighting(StringHash eventType, VariantMap& eventData)
{
    CheckBox@ edit = eventData["Element"].GetUIElement();
    renderer.specularLighting = edit.checked;
}

void EditDynamicInstancing(StringHash eventType, VariantMap& eventData)
{
    CheckBox@ edit = eventData["Element"].GetUIElement();
    renderer.dynamicInstancing = edit.checked;
}

void EditLightStencilMasking(StringHash eventType, VariantMap& eventData)
{
    CheckBox@ edit = eventData["Element"].GetUIElement();
    renderer.lightStencilMasking = edit.checked;
}

void EditFrameLimiter(StringHash eventType, VariantMap& eventData)
{
    CheckBox@ edit = eventData["Element"].GetUIElement();
    engine.maxFps = edit.checked ? 200 : 0;
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
    if (editNode !is null && ui.focusElement is null && input.keyDown[KEY_LCTRL])
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
                    if (axisMode == AXIS_LOCAL)
                        adjust = editNode.rotation * adjust;
                    editNode.position = editNode.position + adjust * moveStep;
                    changed = true;
                }
                break;

            case OBJ_ROTATE:
                if (!rotateSnap)
                {
                    Vector3 euler = editNode.rotation.eulerAngles;
                    euler.x += adjust.z * rotateStep;
                    euler.y += adjust.x * rotateStep;
                    euler.z += adjust.y * rotateStep;
                    editNode.rotation = Quaternion(euler);
                    changed = true;
                }
                break;

            case OBJ_SCALE:
                if (!scaleSnap)
                {
                    editNode.scale = editNode.scale + adjust * scaleStep;
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
    if (editNode is null)
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
            if (axisMode == AXIS_LOCAL)
                adjust = editNode.rotation * adjust;

            Vector3 pos = editNode.position;
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
            editNode.position = pos;
        }
        break;

    case OBJ_ROTATE:
        {
            Vector3 rot = editNode.rotation.eulerAngles;
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
            editNode.rotation = Quaternion(rot);
        }
        break;

    case OBJ_SCALE:
        {
            Vector3 scale = editNode.scale;
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
            editNode.scale = scale;
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