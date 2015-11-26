// Urho3D editor settings dialog

bool subscribedToEditorSettings = false;
Window@ settingsDialog;

void CreateEditorSettingsDialog()
{
    if (settingsDialog !is null)
        return;
    
    settingsDialog = LoadEditorUI("UI/EditorSettingsDialog.xml");
    ui.root.AddChild(settingsDialog);
    settingsDialog.opacity = uiMaxOpacity;
    settingsDialog.height = 440;
    CenterDialog(settingsDialog);
    UpdateEditorSettingsDialog();
    HideEditorSettingsDialog();
}

void UpdateEditorSettingsDialog()
{
    if (settingsDialog is null)
        return;

    LineEdit@ nearClipEdit = settingsDialog.GetChild("NearClipEdit", true);
    nearClipEdit.text = String(viewNearClip);

    LineEdit@ farClipEdit = settingsDialog.GetChild("FarClipEdit", true);
    farClipEdit.text = String(viewFarClip);

    LineEdit@ fovEdit = settingsDialog.GetChild("FOVEdit", true);
    fovEdit.text = String(viewFov);

    LineEdit@ speedEdit = settingsDialog.GetChild("SpeedEdit", true);
    speedEdit.text = String(cameraBaseSpeed);

    CheckBox@ limitRotationToggle = settingsDialog.GetChild("LimitRotationToggle", true);
    limitRotationToggle.checked = limitRotation;

    CheckBox@ mouseWheelCameraPositionToggle = settingsDialog.GetChild("MouseWheelCameraPositionToggle", true);
    mouseWheelCameraPositionToggle.checked = mouseWheelCameraPosition;

    DropDownList@ mouseOrbitEdit = settingsDialog.GetChild("MouseOrbitEdit", true);
    mouseOrbitEdit.selection = mouseOrbitMode;

    CheckBox@ middleMousePanToggle = settingsDialog.GetChild("MiddleMousePanToggle", true);
    middleMousePanToggle.checked = mmbPanMode;

    DropDownList@ hotKeysModeEdit = settingsDialog.GetChild("HotKeysModeEdit", true);
    hotKeysModeEdit.selection = hotKeyMode;

    DropDownList@ newNodeModeEdit = settingsDialog.GetChild("NewNodeModeEdit", true);
    newNodeModeEdit.selection = newNodeMode;

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

    CheckBox@ applyMaterialListToggle = settingsDialog.GetChild("ApplyMaterialListToggle", true);
    applyMaterialListToggle.checked = applyMaterialList;

    CheckBox@ rememberResourcePathToggle = settingsDialog.GetChild("RememberResourcePathToggle", true);
    rememberResourcePathToggle.checked = rememberResourcePath;

    LineEdit@ importOptionsEdit = settingsDialog.GetChild("ImportOptionsEdit", true);
    importOptionsEdit.text = importOptions;

    DropDownList@ pickModeEdit = settingsDialog.GetChild("PickModeEdit", true);
    pickModeEdit.selection = pickMode;

    LineEdit@ renderPathNameEdit = settingsDialog.GetChild("RenderPathNameEdit", true);
    renderPathNameEdit.text = renderPathName;

    Button@ pickRenderPathButton = settingsDialog.GetChild("PickRenderPathButton", true);

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

    CheckBox@ frameLimiterToggle = settingsDialog.GetChild("FrameLimiterToggle", true);
    frameLimiterToggle.checked = engine.maxFps > 0;
    
    LineEdit@ cubemapPath = settingsDialog.GetChild("CubeMapGenPath", true);
    cubemapPath.text = cubeMapGen_Path;
    LineEdit@ cubemapName = settingsDialog.GetChild("CubeMapGenKey", true);
    cubemapName.text = cubeMapGen_Name;
    LineEdit@ cubemapSize = settingsDialog.GetChild("CubeMapGenSize", true);
    cubemapSize.text = String(cubeMapGen_Size);

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
        SubscribeToEvent(limitRotationToggle, "Toggled", "EditLimitRotation");
        SubscribeToEvent(mouseWheelCameraPositionToggle, "Toggled", "EditMouseWheelCameraPosition");
        SubscribeToEvent(middleMousePanToggle, "Toggled", "EditMiddleMousePan");
        SubscribeToEvent(mouseOrbitEdit, "ItemSelected", "EditMouseOrbitMode");
        SubscribeToEvent(hotKeysModeEdit, "ItemSelected", "EditHotKeyMode");
        SubscribeToEvent(newNodeModeEdit, "ItemSelected", "EditNewNodeMode");
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
        SubscribeToEvent(rememberResourcePathToggle, "Toggled", "EditRememberResourcePath");
        SubscribeToEvent(applyMaterialListToggle, "Toggled", "EditApplyMaterialList");
        SubscribeToEvent(importOptionsEdit, "TextChanged", "EditImportOptions");
        SubscribeToEvent(importOptionsEdit, "TextFinished", "EditImportOptions");
        SubscribeToEvent(pickModeEdit, "ItemSelected", "EditPickMode");
        SubscribeToEvent(renderPathNameEdit, "TextFinished", "EditRenderPathName");
        SubscribeToEvent(pickRenderPathButton, "Released", "PickRenderPath");
        SubscribeToEvent(textureQualityEdit, "ItemSelected", "EditTextureQuality");
        SubscribeToEvent(materialQualityEdit, "ItemSelected", "EditMaterialQuality");
        SubscribeToEvent(shadowResolutionEdit, "ItemSelected", "EditShadowResolution");
        SubscribeToEvent(shadowQualityEdit, "ItemSelected", "EditShadowQuality");
        SubscribeToEvent(maxOccluderTrianglesEdit, "TextChanged", "EditMaxOccluderTriangles");
        SubscribeToEvent(maxOccluderTrianglesEdit, "TextFinished", "EditMaxOccluderTriangles");
        SubscribeToEvent(specularLightingToggle, "Toggled", "EditSpecularLighting");
        SubscribeToEvent(dynamicInstancingToggle, "Toggled", "EditDynamicInstancing");
        SubscribeToEvent(frameLimiterToggle, "Toggled", "EditFrameLimiter");
        SubscribeToEvent(settingsDialog.GetChild("CloseButton", true), "Released", "HideEditorSettingsDialog");
        
        SubscribeToEvent(cubemapPath, "TextChanged",  "EditCubemapPath");
        SubscribeToEvent(cubemapPath, "TextFinished", "EditCubemapPath");
        SubscribeToEvent(cubemapName, "TextChanged",  "EditCubemapName");
        SubscribeToEvent(cubemapName, "TextFinished", "EditCubemapName");
        SubscribeToEvent(cubemapSize, "TextChanged",  "EditCubemapSize");
        SubscribeToEvent(cubemapSize, "TextFinished", "EditCubemapSize");
        
        subscribedToEditorSettings = true;
    }
}

bool ToggleEditorSettingsDialog()
{
    if (settingsDialog.visible == false)
        ShowEditorSettingsDialog();
    else
        HideEditorSettingsDialog();
    return true;
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
    LineEdit@ edit = eventData["Element"].GetPtr();
    viewNearClip = edit.text.ToFloat();
    UpdateViewParameters();
    if (eventType == StringHash("TextFinished"))
        edit.text = String(camera.nearClip);
}

void EditCameraFarClip(StringHash eventType, VariantMap& eventData)
{
    LineEdit@ edit = eventData["Element"].GetPtr();
    viewFarClip = edit.text.ToFloat();
    UpdateViewParameters();
    if (eventType == StringHash("TextFinished"))
        edit.text = String(camera.farClip);
}

void EditCameraFOV(StringHash eventType, VariantMap& eventData)
{
    LineEdit@ edit = eventData["Element"].GetPtr();
    viewFov = edit.text.ToFloat();
    UpdateViewParameters();
    if (eventType == StringHash("TextFinished"))
        edit.text = String(camera.fov);
}

void EditCameraSpeed(StringHash eventType, VariantMap& eventData)
{
    LineEdit@ edit = eventData["Element"].GetPtr();
    cameraBaseSpeed = Max(edit.text.ToFloat(), 1.0);
    if (eventType == StringHash("TextFinished"))
        edit.text = String(cameraBaseSpeed);
}

void EditLimitRotation(StringHash eventType, VariantMap& eventData)
{
    CheckBox@ edit = eventData["Element"].GetPtr();
    limitRotation = edit.checked;
}

void EditMouseWheelCameraPosition(StringHash eventType, VariantMap& eventData)
{
    CheckBox@ edit = eventData["Element"].GetPtr();
    mouseWheelCameraPosition = edit.checked;
}

void EditMouseOrbitMode(StringHash eventType, VariantMap& eventData)
{
    DropDownList@ edit = eventData["Element"].GetPtr();
    mouseOrbitMode = edit.selection;
}

void EditMiddleMousePan(StringHash eventType, VariantMap& eventData)
{
    mmbPanMode = cast<CheckBox>(eventData["Element"].GetPtr()).checked;
}

void EditHotKeyMode(StringHash eventType, VariantMap& eventData)
{
    DropDownList@ edit = eventData["Element"].GetPtr();
    hotKeyMode = edit.selection;
    MessageBox("Please, restart Urho editor for applying changes.\n", " Notify ");
    
}

void EditNewNodeMode(StringHash eventType, VariantMap& eventData)
{
    DropDownList@ edit = eventData["Element"].GetPtr();
    newNodeMode = edit.selection;
}

void EditNewNodeDistance(StringHash eventType, VariantMap& eventData)
{
    LineEdit@ edit = eventData["Element"].GetPtr();
    newNodeDistance = Max(edit.text.ToFloat(), 0.0);
    if (eventType == StringHash("TextFinished"))
        edit.text = String(newNodeDistance);
}

void EditMoveStep(StringHash eventType, VariantMap& eventData)
{
    LineEdit@ edit = eventData["Element"].GetPtr();
    moveStep = Max(edit.text.ToFloat(), 0.0);
    if (eventType == StringHash("TextFinished"))
        edit.text = String(moveStep);
}

void EditRotateStep(StringHash eventType, VariantMap& eventData)
{
    LineEdit@ edit = eventData["Element"].GetPtr();
    rotateStep = Max(edit.text.ToFloat(), 0.0);
    if (eventType == StringHash("TextFinished"))
        edit.text = String(rotateStep);
}

void EditScaleStep(StringHash eventType, VariantMap& eventData)
{
    LineEdit@ edit = eventData["Element"].GetPtr();
    scaleStep = Max(edit.text.ToFloat(), 0.0);
    if (eventType == StringHash("TextFinished"))
        edit.text = String(scaleStep);
}

void EditMoveSnap(StringHash eventType, VariantMap& eventData)
{
    CheckBox@ edit = eventData["Element"].GetPtr();
    moveSnap = edit.checked;
    toolBarDirty = true;
}

void EditRotateSnap(StringHash eventType, VariantMap& eventData)
{
    CheckBox@ edit = eventData["Element"].GetPtr();
    rotateSnap = edit.checked;
    toolBarDirty = true;
}

void EditScaleSnap(StringHash eventType, VariantMap& eventData)
{
    CheckBox@ edit = eventData["Element"].GetPtr();
    scaleSnap = edit.checked;
    toolBarDirty = true;
}

void EditRememberResourcePath(StringHash eventType, VariantMap& eventData)
{
    CheckBox@ edit = eventData["Element"].GetPtr();
    rememberResourcePath = edit.checked;
}

void EditApplyMaterialList(StringHash eventType, VariantMap& eventData)
{
    CheckBox@ edit = eventData["Element"].GetPtr();
    applyMaterialList = edit.checked;
}

void EditImportOptions(StringHash eventType, VariantMap& eventData)
{
    LineEdit@ edit = eventData["Element"].GetPtr();
    importOptions = edit.text.Trimmed();
}

void EditPickMode(StringHash eventType, VariantMap& eventData)
{
    DropDownList@ edit = eventData["Element"].GetPtr();
    pickMode = edit.selection;
}

void EditRenderPathName(StringHash eventType, VariantMap& eventData)
{
    LineEdit@ edit = eventData["Element"].GetPtr();
    SetRenderPath(edit.text);
}

void PickRenderPath(StringHash eventType, VariantMap& eventData)
{
    CreateFileSelector("Load render path", "Load", "Cancel", uiRenderPathPath, uiRenderPathFilters, uiRenderPathFilter);
    SubscribeToEvent(uiFileSelector, "FileSelected", "HandleLoadRenderPath");
}

void HandleLoadRenderPath(StringHash eventType, VariantMap& eventData)
{
    CloseFileSelector(uiRenderPathFilter, uiRenderPathPath);
    SetRenderPath(GetResourceNameFromFullName(ExtractFileName(eventData)));
    LineEdit@ renderPathNameEdit = settingsDialog.GetChild("RenderPathNameEdit", true);
    renderPathNameEdit.text = renderPathName;
}

void EditTextureQuality(StringHash eventType, VariantMap& eventData)
{
    DropDownList@ edit = eventData["Element"].GetPtr();
    renderer.textureQuality = edit.selection;
}

void EditMaterialQuality(StringHash eventType, VariantMap& eventData)
{
    DropDownList@ edit = eventData["Element"].GetPtr();
    renderer.materialQuality = edit.selection;
}

void EditShadowResolution(StringHash eventType, VariantMap& eventData)
{
    DropDownList@ edit = eventData["Element"].GetPtr();
    SetShadowResolution(edit.selection);
}

void EditShadowQuality(StringHash eventType, VariantMap& eventData)
{
    DropDownList@ edit = eventData["Element"].GetPtr();
    renderer.shadowQuality = edit.selection;
}

void EditMaxOccluderTriangles(StringHash eventType, VariantMap& eventData)
{
    LineEdit@ edit = eventData["Element"].GetPtr();
    renderer.maxOccluderTriangles = edit.text.ToInt();
    if (eventType == StringHash("TextFinished"))
        edit.text = String(renderer.maxOccluderTriangles);
}

void EditSpecularLighting(StringHash eventType, VariantMap& eventData)
{
    CheckBox@ edit = eventData["Element"].GetPtr();
    renderer.specularLighting = edit.checked;
}

void EditDynamicInstancing(StringHash eventType, VariantMap& eventData)
{
    CheckBox@ edit = eventData["Element"].GetPtr();
    renderer.dynamicInstancing = edit.checked;
}

void EditFrameLimiter(StringHash eventType, VariantMap& eventData)
{
    CheckBox@ edit = eventData["Element"].GetPtr();
    engine.maxFps = edit.checked ? 200 : 0;
}

void EditCubemapPath(StringHash eventType, VariantMap& eventData)
{
    LineEdit@ edit = eventData["Element"].GetPtr();
    cubeMapGen_Path = edit.text;
}

void EditCubemapName(StringHash eventType, VariantMap& eventData)
{
    LineEdit@ edit = eventData["Element"].GetPtr();
    cubeMapGen_Name = edit.text;
}

void EditCubemapSize(StringHash eventType, VariantMap& eventData)
{
    LineEdit@ edit = eventData["Element"].GetPtr();
    cubeMapGen_Size = edit.text.ToInt();
}