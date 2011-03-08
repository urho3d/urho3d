// Urho3D editor camera functions

Camera@ camera;
Window@ cameraDialog;

float cameraBaseSpeed = 10.0;
float cameraBaseRotationSpeed = 0.2;
float cameraShiftSpeedMultiplier = 5.0;
float cameraYaw = 0.0;
float cameraPitch = 0.0;

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

    // Fill the current values and subscribe to changes
    LineEdit@ nearClipEdit = cameraDialog.getChild("NearClipEdit", true);
    nearClipEdit.setText(toString(camera.getNearClip()));
    subscribeToEvent(nearClipEdit, "TextFinished", "handleCameraDialogNearClip");

    LineEdit@ farClipEdit = cameraDialog.getChild("FarClipEdit", true);
    farClipEdit.setText(toString(camera.getFarClip()));
    subscribeToEvent(farClipEdit, "TextFinished", "handleCameraDialogFarClip");

    LineEdit@ fovEdit = cameraDialog.getChild("FOVEdit", true);
    fovEdit.setText(toString(camera.getFov()));
    subscribeToEvent(fovEdit, "TextFinished", "handleCameraDialogFOV");

    LineEdit@ speedEdit = cameraDialog.getChild("SpeedEdit", true);
    speedEdit.setText(toString(cameraBaseSpeed));
    subscribeToEvent(speedEdit, "TextFinished", "handleCameraDialogSpeed");

    subscribeToEvent(cameraDialog.getChild("CloseButton", true), "Pressed", "handleCameraDialogClose");
}

void closeCameraDialog()
{
    if (cameraDialog is null)
        return;
    uiRoot.removeChild(cameraDialog);
    @cameraDialog = null;
}

void handleCameraDialogClose(StringHash eventType, VariantMap& eventData)
{
    closeCameraDialog();
}

void handleCameraDialogNearClip(StringHash eventType, VariantMap& eventData)
{
    LineEdit@ edit = eventData["Element"].getUIElement();
    // Set to camera and then back to lineedit
    camera.setNearClip(edit.getText().toFloat());
    edit.setText(toString(camera.getNearClip()));
}

void handleCameraDialogFarClip(StringHash eventType, VariantMap& eventData)
{
    LineEdit@ edit = eventData["Element"].getUIElement();
    // Set to camera and then back to lineedit; watch for ridiculously low values
    camera.setFarClip(max(edit.getText().toFloat(), 10));
    edit.setText(toString(camera.getFarClip()));
}

void handleCameraDialogFOV(StringHash eventType, VariantMap& eventData)
{
    LineEdit@ edit = eventData["Element"].getUIElement();
    // Set to camera and then back to lineedit
    camera.setFov(edit.getText().toFloat());
    edit.setText(toString(camera.getFov()));
}

void handleCameraDialogSpeed(StringHash eventType, VariantMap& eventData)
{
    LineEdit@ edit = eventData["Element"].getUIElement();
    cameraBaseSpeed = max(edit.getText().toFloat(), 1);
    edit.setText(toString(cameraBaseSpeed));
}