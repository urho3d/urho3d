// Urho3D editor camera functions

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

array<string> moveModeText = {
    "Move    ",
    "Rotate  ",
    "Scale   "
};

void createCamera()
{
    // Note: this camera will not be bound into a scene entity, so that it does not get listed in the editor UI
    @camera = editorScene.createComponent("Camera");
    resetCamera();

    pipeline.setViewport(0, Viewport(editorScene, camera));
}

void resetCamera()
{
    camera.setPosition(Vector3(0, 10, 0));
    camera.setRotation(Quaternion());
    cameraPitch = 0;
    cameraYaw = 0;
}

void createEditorSettingsDialog()
{
    if (!(editorSettingsDialog is null))
        return;
    
    @editorSettingsDialog = ui.loadLayout(cache.getResource("XMLFile", "UI/EditorSettingsDialog.xml"), uiStyle);
    uiRoot.addChild(editorSettingsDialog);
    centerDialog(editorSettingsDialog);
    updateEditorSettingsDialog();
    hideEditorSettingsDialog();
}

void updateEditorSettingsDialog()
{
    if (editorSettingsDialog is null)
        return;

    LineEdit@ nearClipEdit = editorSettingsDialog.getChild("NearClipEdit", true);
    nearClipEdit.setText(toString(camera.getNearClip()));
    
    LineEdit@ farClipEdit = editorSettingsDialog.getChild("FarClipEdit", true);
    farClipEdit.setText(toString(camera.getFarClip()));
    
    LineEdit@ fovEdit = editorSettingsDialog.getChild("FOVEdit", true);
    fovEdit.setText(toString(camera.getFov()));

    LineEdit@ speedEdit = editorSettingsDialog.getChild("SpeedEdit", true);
    speedEdit.setText(toString(cameraBaseSpeed));

    LineEdit@ distanceEdit = editorSettingsDialog.getChild("DistanceEdit", true);
    distanceEdit.setText(toString(newNodeDistance));

    LineEdit@ moveStepEdit = editorSettingsDialog.getChild("MoveStepEdit", true);
    moveStepEdit.setText(toString(moveStep));
    CheckBox@ moveSnapToggle = editorSettingsDialog.getChild("MoveSnapToggle", true);
    moveSnapToggle.setChecked(moveSnap);

    LineEdit@ rotateStepEdit = editorSettingsDialog.getChild("RotateStepEdit", true);
    rotateStepEdit.setText(toString(rotateStep));
    CheckBox@ rotateSnapToggle = editorSettingsDialog.getChild("RotateSnapToggle", true);
    rotateSnapToggle.setChecked(rotateSnap);

    LineEdit@ scaleStepEdit = editorSettingsDialog.getChild("ScaleStepEdit", true);
    scaleStepEdit.setText(toString(scaleStep));
    CheckBox@ scaleSnapToggle = editorSettingsDialog.getChild("ScaleSnapToggle", true);
    scaleSnapToggle.setChecked(scaleSnap);

    CheckBox@ localIDToggle = editorSettingsDialog.getChild("LocalIDToggle", true);
    localIDToggle.setChecked(useLocalIDs);

    if (!subscribedToCameraEdits)
    {
        subscribeToEvent(nearClipEdit, "TextChanged", "editCameraNearClip");
        subscribeToEvent(nearClipEdit, "TextFinished", "editCameraNearClip");
        subscribeToEvent(farClipEdit, "TextChanged", "editCameraFarClip");
        subscribeToEvent(farClipEdit, "TextFinished", "editCameraFarClip");
        subscribeToEvent(fovEdit, "TextChanged", "editCameraFOV");
        subscribeToEvent(fovEdit, "TextFinished", "editCameraFOV");
        subscribeToEvent(speedEdit, "TextChanged", "editCameraSpeed");
        subscribeToEvent(speedEdit, "TextFinished", "editCameraSpeed");
        subscribeToEvent(distanceEdit, "TextChanged", "editNewNodeDistance");
        subscribeToEvent(distanceEdit, "TextFinished", "editNewNodeDistance");
        subscribeToEvent(moveStepEdit, "TextChanged", "editMoveStep");
        subscribeToEvent(moveStepEdit, "TextFinished", "editMoveStep");
        subscribeToEvent(rotateStepEdit, "TextChanged", "editRotateStep");
        subscribeToEvent(rotateStepEdit, "TextFinished", "editRotateStep");
        subscribeToEvent(scaleStepEdit, "TextChanged", "editScaleStep");
        subscribeToEvent(scaleStepEdit, "TextFinished", "editScaleStep");
        subscribeToEvent(moveSnapToggle, "Toggled", "editMoveSnap");
        subscribeToEvent(rotateSnapToggle, "Toggled", "editRotateSnap");
        subscribeToEvent(scaleSnapToggle, "Toggled", "editScaleSnap");
        subscribeToEvent(localIDToggle, "Toggled", "editUseLocalIDs");
        subscribeToEvent(editorSettingsDialog.getChild("CloseButton", true), "Released", "hideEditorSettingsDialog");
        subscribedToCameraEdits = true;
    }
}

void showEditorSettingsDialog()
{
    updateEditorSettingsDialog();
    editorSettingsDialog.setVisible(true);
    editorSettingsDialog.bringToFront();
}

void hideEditorSettingsDialog()
{
    editorSettingsDialog.setVisible(false);
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

void editNewNodeDistance(StringHash eventType, VariantMap& eventData)
{
    LineEdit@ edit = eventData["Element"].getUIElement();
    newNodeDistance = max(edit.getText().toFloat(), 0);
    if (eventType == StringHash("TextFinished"))
        edit.setText(toString(newNodeDistance));
}

void editMoveStep(StringHash eventType, VariantMap& eventData)
{
    LineEdit@ edit = eventData["Element"].getUIElement();
    moveStep = max(edit.getText().toFloat(), 0);
    if (eventType == StringHash("TextFinished"))
        edit.setText(toString(moveStep));
}

void editRotateStep(StringHash eventType, VariantMap& eventData)
{
    LineEdit@ edit = eventData["Element"].getUIElement();
    rotateStep = max(edit.getText().toFloat(), 0);
    if (eventType == StringHash("TextFinished"))
        edit.setText(toString(rotateStep));
}

void editScaleStep(StringHash eventType, VariantMap& eventData)
{
    LineEdit@ edit = eventData["Element"].getUIElement();
    scaleStep = max(edit.getText().toFloat(), 0);
    if (eventType == StringHash("TextFinished"))
        edit.setText(toString(scaleStep));
}

void editMoveSnap(StringHash eventType, VariantMap& eventData)
{
    CheckBox@ edit = eventData["Element"].getUIElement();
    moveSnap = edit.isChecked();
}

void editRotateSnap(StringHash eventType, VariantMap& eventData)
{
    CheckBox@ edit = eventData["Element"].getUIElement();
    rotateSnap = edit.isChecked();
}

void editScaleSnap(StringHash eventType, VariantMap& eventData)
{
    CheckBox@ edit = eventData["Element"].getUIElement();
    scaleSnap = edit.isChecked();
}

void editUseLocalIDs(StringHash eventType, VariantMap& eventData)
{
    CheckBox@ edit = eventData["Element"].getUIElement();
    useLocalIDs = edit.isChecked();
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
        "Tris: " + pipeline.getNumPrimitives() +
        " Batches: " + pipeline.getNumBatches() +
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
    
    cameraPosText.setText(moveModeText[moveMode] + "Physics: " + (runPhysics ? "Running " : "Paused  ") + " Camera pos: " + xText
        + " " + yText + " " + zText + " ");
    
    renderStatsText.setSize(renderStatsText.getMinSize());
    cameraPosText.setSize(cameraPosText.getMinSize());
}

void moveCamera(float timeStep)
{
    // Move camera
    if ((ui.getFocusElement() is null) && (!input.getKeyDown(KEY_CTRL)))
    {
        float speedMultiplier = 1.0;
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

    // Rotate camera
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

    // Move/rotate/scale object
    if ((selectedComponent !is null) && (ui.getFocusElement() is null) && (input.getKeyDown(KEY_CTRL)))
    {
        Node@ node = cast<Node>(selectedComponent);
        if (node !is null)
        {
            bool changed = false;
            Vector3 adjust(0, 0, 0);
            if (input.getKeyDown(KEY_UP))
                adjust.z = 1;
            if (input.getKeyDown(KEY_DOWN))
                adjust.z = -1;
            if (input.getKeyDown(KEY_LEFT))
                adjust.x = -1;
            if (input.getKeyDown(KEY_RIGHT))
                adjust.x = 1;
            if (input.getKeyDown(KEY_PAGEUP))
                adjust.y = 1;
            if (input.getKeyDown(KEY_PAGEDOWN))
                adjust.y = -1;
            if (moveMode == OBJ_SCALE)
            {
                if ((input.getKeyDown(KEY_ADD)) || (input.getKeyDown(KEY_OEM_PLUS)))
                    adjust = Vector3(1, 1, 1);
                if ((input.getKeyDown(KEY_SUBTRACT)) || (input.getKeyDown(KEY_OEM_MINUS)))
                    adjust = Vector3(-1, -1, -1);
            }

            if (adjust != Vector3(0, 0, 0))
            {
                adjust *= timeStep * 10;

                if (input.getKeyDown(KEY_SHIFT))
                    adjust *= cameraShiftSpeedMultiplier;

                switch (moveMode)
                {
                case OBJ_MOVE:
                    if (!moveSnap)
                    {
                        node.setPosition(node.getPosition() + adjust * moveStep);
                        changed = true;
                    }
                    break;
    
                case OBJ_ROTATE:
                    if (!rotateSnap)
                    {
                        Vector3 euler = node.getRotation().getEulerAngles();
                        euler.x += adjust.z * rotateStep;
                        euler.y += adjust.x * rotateStep;
                        euler.z += adjust.y * rotateStep;
                        node.setRotation(Quaternion(euler));
                        changed = true;
                    }
                    break;
    
                case OBJ_SCALE:
                    if (!scaleSnap)
                    {
                        node.setScale(node.getScale() + adjust * scaleStep);
                        changed = true;
                    }
                    break;
                }
            }

            if (changed)
            {
                // If is a physics body, make sure the physics and rendering transforms are in sync
                RigidBody@ body = cast<RigidBody>(node);
                if (body !is null)
                    body.setTransform(node.getPosition(), node.getRotation(), node.getScale());

                updateComponentAttributes();
            }
        }
    }
}

void steppedObjectManipulation(int key)
{
    Node@ node = cast<Node>(selectedComponent);
    if (node is null)
        return;

    // Do not react in non-snapped mode, because that is handled in frame update
    if ((moveMode == OBJ_MOVE) && (!moveSnap))
        return;
    if ((moveMode == OBJ_ROTATE) && (!rotateSnap))
        return;
    if ((moveMode == OBJ_SCALE) && (!scaleSnap))
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
        if ((key == KEY_ADD) || (key == KEY_OEM_PLUS))
            adjust = Vector3(1, 1, 1);
        if ((key == KEY_SUBTRACT) || (key == KEY_OEM_MINUS))
            adjust = Vector3(-1, -1, -1);
    }

    if (adjust == Vector3(0, 0, 0))
        return;

    switch (moveMode)
    {
    case OBJ_MOVE:
        {
            Vector3 pos = node.getPosition();
            if (adjust.x != 0)
            {
                pos.x += adjust.x * moveStep;
                pos.x = floor(pos.x / moveStep + 0.5) * moveStep;
            }
            if (adjust.y != 0)
            {
                pos.y += adjust.y * moveStep;
                pos.y = floor(pos.y / moveStep + 0.5) * moveStep;
            }
            if (adjust.z != 0)
            {
                pos.z += adjust.z * moveStep;
                pos.z = floor(pos.z / moveStep + 0.5) * moveStep;
            }
            node.setPosition(pos);
        }
        break;

    case OBJ_ROTATE:
        {
            Vector3 rot = node.getRotation().getEulerAngles();
            if (adjust.z != 0)
            {
                rot.x += adjust.z * rotateStep;
                rot.x = floor(rot.x / rotateStep + 0.5) * rotateStep;
            }
            if (adjust.x != 0)
            {
                rot.y += adjust.x * rotateStep;
                rot.y = floor(rot.y / rotateStep + 0.5) * rotateStep;
            }
            if (adjust.y != 0)
            {
                rot.z += adjust.y * rotateStep;
                rot.z = floor(rot.z / rotateStep + 0.5) * rotateStep;
            }
            node.setRotation(Quaternion(rot));
        }
        break;

    case OBJ_SCALE:
        {
            Vector3 scale = node.getScale();
            if (adjust.x != 0)
            {
                scale.x += adjust.x * scaleStep;
                scale.x = floor(scale.x / scaleStep + 0.5) * scaleStep;
            }
            if (adjust.y != 0)
            {
                scale.y += adjust.y * scaleStep;
                scale.y = floor(scale.y / scaleStep + 0.5) * scaleStep;
            }
            if (adjust.z != 0)
            {
                scale.z += adjust.z * scaleStep;
                scale.z = floor(scale.z / scaleStep + 0.5) * scaleStep;
            }
            node.setScale(scale);
        }
        break;
    }

    // If is a physics body, make sure the physics and rendering transforms are in sync
    RigidBody@ body = cast<RigidBody>(node);
    if (body !is null)
        body.setTransform(node.getPosition(), node.getRotation(), node.getScale());

    updateComponentAttributes();
}

Vector3 getNewNodePosition()
{
    return camera.getWorldPosition() + camera.getWorldRotation() * Vector3(0, 0, newNodeDistance);
}
