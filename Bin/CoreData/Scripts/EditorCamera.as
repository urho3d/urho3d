// Urho3D editor camera functions

Camera@ camera;
Window@ cameraDialog;

float cameraBaseSpeed = 10;
float cameraBaseRotationSpeed = 0.2;
float cameraShiftSpeedMultiplier = 5;
float cameraYaw = 0;
float cameraPitch = 0;
float updateStatsAcc = 0;

Text@ renderStatsText;
Text@ cameraPosText;
bool subscribedToCameraEdits = false;

void createCamera()
{
    // Note: this camera will not be bound into a scene entity, so that it does not get listed in the editor UI
    @camera = editorScene.createComponent("Camera");
    resetCamera();

    pipeline.setViewport(0, Viewport(editorScene, camera));
}

void moveCamera(float timeStep)
{
    if ((ui.getFocusElement() is null) && (!input.getKeyDown(KEY_CTRL)))
    {
        float speedMultiplier = 1.0f;
        if (input.getKeyDown(KEY_SHIFT))
            speedMultiplier = cameraShiftSpeedMultiplier;

        if ((input.getKeyDown('W')) || (input.getKeyDown(KEY_UP)))
            camera.translateRelative(Vector3(0, 0, cameraBaseSpeed) * timeStep * speedMultiplier);
        if ((input.getKeyDown('S')) || (input.getKeyDown(KEY_DOWN)))
            camera.translateRelative(Vector3(0, 0, -cameraBaseSpeed) * timeStep * speedMultiplier);
        if ((input.getKeyDown('A')) || (input.getKeyDown(KEY_LEFT)))
            camera.translateRelative(Vector3(-cameraBaseSpeed, 0, 0) * timeStep * speedMultiplier);
        if ((input.getKeyDown('D')) || (input.getKeyDown(KEY_RIGHT)))
            camera.translateRelative(Vector3(cameraBaseSpeed, 0, 0) * timeStep * speedMultiplier);
    }
    
    if (input.getMouseButtonDown(MOUSEB_RIGHT))
    {
        IntVector2 mouseMove = input.getMouseMove();
        if ((mouseMove.x != 0) || (mouseMove.y != 0))
        {
            cameraYaw += mouseMove.x * cameraBaseRotationSpeed;
            cameraPitch += mouseMove.y * cameraBaseRotationSpeed;
            if (cameraPitch < -90.0f)
                cameraPitch = -90.0f;
            if (cameraPitch > 90.0f)
                cameraPitch = 90.0f;

            camera.setRotation(Quaternion(cameraPitch, cameraYaw, 0));
        }
    }
}

void resetCamera()
{
    camera.setPosition(Vector3(0, 10, 0));
    camera.setRotation(Quaternion());
}

void createCameraDialog()
{
    if (!(cameraDialog is null))
        return;
    
    @cameraDialog = ui.loadLayout(cache.getResource("XMLFile", "UI/CameraDialog.xml"), uiStyle);
    uiRoot.addChild(cameraDialog);
    centerDialog(cameraDialog);
    updateCameraDialog();
    hideCameraDialog();
}

void updateCameraDialog()
{
    if (cameraDialog is null)
        return;
    
    LineEdit@ nearClipEdit = cameraDialog.getChild("NearClipEdit", true);
    nearClipEdit.setText(toString(camera.getNearClip()));
    
    LineEdit@ farClipEdit = cameraDialog.getChild("FarClipEdit", true);
    farClipEdit.setText(toString(camera.getFarClip()));
    
    LineEdit@ fovEdit = cameraDialog.getChild("FOVEdit", true);
    fovEdit.setText(toString(camera.getFov()));

    LineEdit@ speedEdit = cameraDialog.getChild("SpeedEdit", true);
    speedEdit.setText(toString(cameraBaseSpeed));

    if (!subscribedToCameraEdits)
    {
        subscribeToEvent(nearClipEdit, "TextChanged", "editCameraNearClip");
        subscribeToEvent(nearClipEdit, "TextFinished", "editCameraNearClip");
        subscribeToEvent(farClipEdit, "TextChanged", "editCameraFarClip");
        subscribeToEvent(farClipEdit, "TextFinished", "editCameraFarClip");
        subscribeToEvent(fovEdit, "TextChanged", "editCameraFOV");
        subscribeToEvent(fovEdit, "TextFinished", "editCameraFOV");
        subscribeToEvent(fovEdit, "TextChanged", "editCameraSpeed");
        subscribeToEvent(speedEdit, "TextFinished", "editCameraSpeed");
        subscribeToEvent(cameraDialog.getChild("CloseButton", true), "Released", "hideCameraDialog");
        subscribedToCameraEdits = true;
    }
}

void showCameraDialog()
{
    updateCameraDialog();
    cameraDialog.setVisible(true);
    cameraDialog.bringToFront();
}

void hideCameraDialog()
{
    cameraDialog.setVisible(false);
}

void editCameraNearClip(StringHash eventType, VariantMap& eventData)
{
    LineEdit@ edit = eventData["Element"].getUIElement();
    camera.setNearClip(edit.getText().toFloat());
    if (eventType == StringHash("TextFinished"))
        edit.setText(toString(camera.getNearClip()));
}

void editCameraFarClip(StringHash eventType, VariantMap& eventData)
{
    LineEdit@ edit = eventData["Element"].getUIElement();
    camera.setFarClip(max(edit.getText().toFloat(), 10));
    if (eventType == StringHash("TextFinished"))
        edit.setText(toString(camera.getFarClip()));
}

void editCameraFOV(StringHash eventType, VariantMap& eventData)
{
    LineEdit@ edit = eventData["Element"].getUIElement();
    camera.setFov(edit.getText().toFloat());
    if (eventType == StringHash("TextFinished"))
        edit.setText(toString(camera.getFov()));
}

void editCameraSpeed(StringHash eventType, VariantMap& eventData)
{
    LineEdit@ edit = eventData["Element"].getUIElement();
    cameraBaseSpeed = max(edit.getText().toFloat(), 1);
    if (eventType == StringHash("TextFinished"))
        edit.setText(toString(cameraBaseSpeed));
}

void createStatsBar()
{
    Font@ font = cache.getResource("Font", "cour.ttf");
    
    @renderStatsText = Text();
    @cameraPosText = Text();
    
    if (uiRoot.getWidth() >= 1024)
    {
        setupStatsBarText(renderStatsText, font, 0, 20, HA_LEFT);
        setupStatsBarText(cameraPosText, font, 0, 20, HA_RIGHT);
    }
    else
    {
        setupStatsBarText(renderStatsText, font, 0, 20, HA_LEFT);
        setupStatsBarText(cameraPosText, font, 0, 32, HA_LEFT);
    }
}

void setupStatsBarText(Text@ text, Font@ font, int x, int y, HorizontalAlignment align)
{
    text.setPosition(x, y);
    text.setHorizontalAlignment(align);
    text.setFont(font, 9);
    text.setColor(Color(1, 1, 0));
    text.setPriority(-100);
    uiRoot.addChild(text);
}

void updateStats(float timeStep)
{
    renderStatsText.setText(
        "Tris: " + renderer.getNumPrimitives() +
        " Batches: " + renderer.getNumBatches() +
        " Lights: " + pipeline.getNumLights(true) +
        " Shadowmaps: " + pipeline.getNumShadowMaps(true) +
        " Occluders: " + (pipeline.getNumOccluders(true) + pipeline.getNumShadowOccluders(true))
    );
    
    Vector3 cameraPos = camera.getPosition();
    string xText = toString(cameraPos.x);
    string yText = toString(cameraPos.y);
    string zText = toString(cameraPos.z);
    xText.resize(8);
    yText.resize(8);
    zText.resize(8);
    
    cameraPosText.setText("Physics: " + (runPhysics ? "Running " : "Paused  ") + " Camera pos: " + xText + " " + yText + " " + zText + " ");
    
    renderStatsText.setSize(renderStatsText.getMinSize());
    cameraPosText.setSize(cameraPosText.getMinSize());
}
