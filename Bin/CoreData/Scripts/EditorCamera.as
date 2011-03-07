// Urho3D editor camera functions

Camera@ camera;

float cameraBaseSpeed = 10.0;
float cameraBaseRotationSpeed = 0.2;
float cameraShiftSpeedMultiplier = 5.0;
float cameraYaw = 0.0;
float cameraPitch = 0.0;

void createCamera()
{
    // Note: this camera will not be bound into a scene entity, so that it does not get listed in the editor UI
    @camera = editorScene.createComponent("Camera");

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
