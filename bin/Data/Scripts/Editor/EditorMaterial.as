// Urho3D material editor

Window@ materialWindow;
Material@ editMaterial;
XMLFile@ oldMaterialState;
bool inMaterialRefresh = true;
View3D@ materialPreview;
Scene@ previewScene;
Node@ previewCameraNode;
Node@ previewLightNode;
Light@ previewLight;
Node@ previewModelNode;
StaticModel@ previewModel;

void CreateMaterialEditor()
{
    if (materialWindow !is null)
        return;

    materialWindow = LoadEditorUI("UI/EditorMaterialWindow.xml");
    ui.root.AddChild(materialWindow);
    materialWindow.opacity = uiMaxOpacity;

    InitMaterialPreview();
    InitModelPreviewList();
    RefreshMaterialEditor();

    int height = Min(ui.root.height - 60, 600);
    materialWindow.SetSize(400, height);
    CenterDialog(materialWindow);

    HideMaterialEditor();

    SubscribeToEvent(materialWindow.GetChild("NewButton", true), "Released", "NewMaterial");
    SubscribeToEvent(materialWindow.GetChild("RevertButton", true), "Released", "RevertMaterial");
    SubscribeToEvent(materialWindow.GetChild("SaveButton", true), "Released", "SaveMaterial");
    SubscribeToEvent(materialWindow.GetChild("SaveAsButton", true), "Released", "SaveMaterialAs");
    SubscribeToEvent(materialWindow.GetChild("CloseButton", true), "Released", "HideMaterialEditor");
    SubscribeToEvent(materialWindow.GetChild("NewParameterDropDown", true), "ItemSelected", "CreateShaderParameter");
    SubscribeToEvent(materialWindow.GetChild("DeleteParameterButton", true), "Released", "DeleteShaderParameter");
    SubscribeToEvent(materialWindow.GetChild("NewTechniqueButton", true), "Released", "NewTechnique");
    SubscribeToEvent(materialWindow.GetChild("DeleteTechniqueButton", true), "Released", "DeleteTechnique");
    SubscribeToEvent(materialWindow.GetChild("SortTechniquesButton", true), "Released", "SortTechniques");
    SubscribeToEvent(materialWindow.GetChild("VSDefinesEdit", true), "TextFinished", "EditVSDefines");
    SubscribeToEvent(materialWindow.GetChild("PSDefinesEdit", true), "TextFinished", "EditPSDefines");
    SubscribeToEvent(materialWindow.GetChild("ConstantBiasEdit", true), "TextChanged", "EditConstantBias");
    SubscribeToEvent(materialWindow.GetChild("ConstantBiasEdit", true), "TextFinished", "EditConstantBias");
    SubscribeToEvent(materialWindow.GetChild("SlopeBiasEdit", true), "TextChanged", "EditSlopeBias");
    SubscribeToEvent(materialWindow.GetChild("SlopeBiasEdit", true), "TextFinished", "EditSlopeBias");
    SubscribeToEvent(materialWindow.GetChild("RenderOrderEdit", true), "TextChanged", "EditRenderOrder");
    SubscribeToEvent(materialWindow.GetChild("RenderOrderEdit", true), "TextFinished", "EditRenderOrder");
    SubscribeToEvent(materialWindow.GetChild("CullModeEdit", true), "ItemSelected", "EditCullMode");
    SubscribeToEvent(materialWindow.GetChild("ShadowCullModeEdit", true), "ItemSelected", "EditShadowCullMode");
    SubscribeToEvent(materialWindow.GetChild("FillModeEdit", true), "ItemSelected", "EditFillMode");
    SubscribeToEvent(materialWindow.GetChild("OcclusionEdit", true), "Toggled", "EditOcclusion");
    SubscribeToEvent(materialWindow.GetChild("AlphaToCoverageEdit", true), "Toggled", "EditAlphaToCoverage");
    SubscribeToEvent(materialWindow.GetChild("LineAntiAliasEdit", true), "Toggled", "EditLineAntiAlias");
}

bool ToggleMaterialEditor()
{
    if (materialWindow.visible == false)
        ShowMaterialEditor();
    else
        HideMaterialEditor();
    return true;
}

void ShowMaterialEditor()
{
    RefreshMaterialEditor();
    materialWindow.visible = true;
    materialWindow.BringToFront();
}

void HideMaterialEditor()
{
    materialWindow.visible = false;
}

void InitMaterialPreview()
{
    previewScene = Scene("PreviewScene");
    previewScene.CreateComponent("Octree");

    Node@ zoneNode = previewScene.CreateChild("Zone");
    Zone@ zone = zoneNode.CreateComponent("Zone");
    zone.boundingBox = BoundingBox(-1000, 1000);
    zone.ambientColor = Color(0.15, 0.15, 0.15);
    zone.fogColor = Color(0, 0, 0);
    zone.fogStart = 10.0;
    zone.fogEnd = 100.0;

    previewCameraNode = previewScene.CreateChild("PreviewCamera");
    previewCameraNode.position = Vector3(0, 0, -1.5);
    Camera@ camera = previewCameraNode.CreateComponent("Camera");
    camera.nearClip = 0.1f;
    camera.farClip = 100.0f;

    previewLightNode = previewScene.CreateChild("PreviewLight");
    previewLightNode.direction = Vector3(0.5, -0.5, 0.5);
    previewLight = previewLightNode.CreateComponent("Light");
    previewLight.lightType = LIGHT_DIRECTIONAL;
    previewLight.specularIntensity = 0.5;

    previewModelNode = previewScene.CreateChild("PreviewModel");
    previewModelNode.rotation = Quaternion(0, 0, 0);
    previewModel = previewModelNode.CreateComponent("StaticModel");
    previewModel.model = cache.GetResource("Model", "Models/Sphere.mdl");

    materialPreview = materialWindow.GetChild("MaterialPreview", true);
    materialPreview.SetFixedHeight(100);
    materialPreview.SetView(previewScene, camera);
    materialPreview.viewport.renderPath = renderPath;
    materialPreview.autoUpdate = false;

    SubscribeToEvent(materialPreview, "DragMove", "RotateMaterialPreview");
}

void InitModelPreviewList()
{
    DropDownList@ modelPreview = materialWindow.GetChild("ModelPreview", true);
    modelPreview.selection = 1;
    SubscribeToEvent(materialWindow.GetChild("ModelPreview", true), "ItemSelected", "EditModelPreviewChange");
}

void EditMaterial(Material@ mat)
{
    if (editMaterial !is null)
        UnsubscribeFromEvent(editMaterial, "ReloadFinished");

    editMaterial = mat;

    if (editMaterial !is null)
        SubscribeToEvent(editMaterial, "ReloadFinished", "RefreshMaterialEditor");

    ShowMaterialEditor();
}

void RefreshMaterialEditor()
{
    RefreshMaterialPreview();
    RefreshMaterialName();
    RefreshMaterialTechniques();
    RefreshMaterialTextures();
    RefreshMaterialShaderParameters();
    RefreshMaterialMiscParameters();
}

void RefreshMaterialPreview()
{
    previewModel.material = editMaterial;
    materialPreview.QueueUpdate();
}

void RefreshMaterialName()
{
    UIElement@ container = materialWindow.GetChild("NameContainer", true);
    container.RemoveAllChildren();

    LineEdit@ nameEdit = CreateAttributeLineEdit(container, null, 0, 0);
    if (editMaterial !is null)
        nameEdit.text = editMaterial.name;
    SubscribeToEvent(nameEdit, "TextFinished", "EditMaterialName");

    Button@ pickButton = CreateResourcePickerButton(container, null, 0, 0, "smallButtonPick");
    SubscribeToEvent(pickButton, "Released", "PickEditMaterial");
}

void RefreshMaterialTechniques(bool fullUpdate = true)
{
    ListView@ list = materialWindow.GetChild("TechniqueList", true);

    if (editMaterial is null)
        return;

    if (fullUpdate == true)
    {
        list.RemoveAllItems();

        for (uint i = 0; i < editMaterial.numTechniques; ++i)
        {
            TechniqueEntry entry = editMaterial.techniqueEntries[i];

            UIElement@ container = UIElement();
            container.SetLayout(LM_HORIZONTAL, 4);
            container.SetFixedHeight(ATTR_HEIGHT);
            list.AddItem(container);

            LineEdit@ nameEdit = CreateAttributeLineEdit(container, null, i, 0);
            nameEdit.name = "TechniqueNameEdit" + String(i);

            Button@ pickButton = CreateResourcePickerButton(container, null, i, 0, "smallButtonPick");
            SubscribeToEvent(pickButton, "Released", "PickMaterialTechnique");
            Button@ openButton = CreateResourcePickerButton(container, null, i, 0, "smallButtonOpen");
            SubscribeToEvent(openButton, "Released", "OpenResource");

            if (entry.technique !is null)
                nameEdit.text = entry.technique.name;

            SubscribeToEvent(nameEdit, "TextFinished", "EditMaterialTechnique");

            UIElement@ container2 = UIElement();
            container2.SetLayout(LM_HORIZONTAL, 4);
            container2.SetFixedHeight(ATTR_HEIGHT);
            list.AddItem(container2);

            Text@ text = container2.CreateChild("Text");
            text.style = "EditorAttributeText";
            text.text = "Quality";
            LineEdit@ attrEdit = CreateAttributeLineEdit(container2, null, i, 0);
            attrEdit.text = String(entry.qualityLevel);
            SubscribeToEvent(attrEdit, "TextChanged", "EditTechniqueQuality");
            SubscribeToEvent(attrEdit, "TextFinished", "EditTechniqueQuality");

            text = container2.CreateChild("Text");
            text.style = "EditorAttributeText";
            text.text = "LOD Distance";
            attrEdit = CreateAttributeLineEdit(container2, null, i, 0);
            attrEdit.text = String(entry.lodDistance);
            SubscribeToEvent(attrEdit, "TextChanged", "EditTechniqueLodDistance");
            SubscribeToEvent(attrEdit, "TextFinished", "EditTechniqueLodDistance");
        }
    }
    else
    {
        for (uint i = 0; i < editMaterial.numTechniques; ++i)
        {
            TechniqueEntry entry = editMaterial.techniqueEntries[i];

            LineEdit@ nameEdit = materialWindow.GetChild("TechniqueNameEdit" + String(i), true);
            if (nameEdit is null)
                continue;

            nameEdit.text = entry.technique !is null ? entry.technique.name : "";
        }
    }
}

void RefreshMaterialTextures(bool fullUpdate = true)
{
    if (fullUpdate)
    {
        ListView@ list = materialWindow.GetChild("TextureList", true);
        list.RemoveAllItems();

        for (uint i = 0; i < MAX_MATERIAL_TEXTURE_UNITS; ++i)
        {
            String tuName = Material::GetTextureUnitName(TextureUnit(i));
            tuName[0] = ToUpper(tuName[0]);

            UIElement@ parent = CreateAttributeEditorParentWithSeparatedLabel(list, "Unit " + i + " " + tuName, i, 0, false);

            UIElement@ container = UIElement();
            container.SetLayout(LM_HORIZONTAL, 4, IntRect(10, 0, 4, 0));
            container.SetFixedHeight(ATTR_HEIGHT);
            parent.AddChild(container);

            LineEdit@ nameEdit = CreateAttributeLineEdit(container, null, i, 0);
            nameEdit.name = "TextureNameEdit" + String(i);

            Button@ pickButton = CreateResourcePickerButton(container, null, i, 0, "smallButtonPick");
            SubscribeToEvent(pickButton, "Released", "PickMaterialTexture");
            Button@ openButton = CreateResourcePickerButton(container, null, i, 0, "smallButtonOpen");
            SubscribeToEvent(openButton, "Released", "OpenResource");

            if (editMaterial !is null)
            {
                Texture@ texture = editMaterial.textures[TextureUnit(i)];
                if (texture !is null)
                    nameEdit.text = texture.name;
            }

            SubscribeToEvent(nameEdit, "TextFinished", "EditMaterialTexture");
        }
    }
    else
    {
        for (uint i = 0; i < MAX_MATERIAL_TEXTURE_UNITS; ++i)
        {
            LineEdit@ nameEdit = materialWindow.GetChild("TextureNameEdit" + String(i), true);
            if (nameEdit is null)
                continue;

            String textureName;
            if (editMaterial !is null)
            {
                Texture@ texture = editMaterial.textures[TextureUnit(i)];
                if (texture !is null)
                    textureName = texture.name;
            }
            
            nameEdit.text = textureName;
        }
    }
}

void RefreshMaterialShaderParameters()
{
    ListView@ list = materialWindow.GetChild("ShaderParameterList", true);
    list.RemoveAllItems();
    if (editMaterial is null)
        return;

    Array<String>@ parameterNames = editMaterial.shaderParameterNames;

    for (uint i = 0; i < parameterNames.length; ++i)
    {
        VariantType type = editMaterial.shaderParameters[parameterNames[i]].type;
        Variant value = editMaterial.shaderParameters[parameterNames[i]];
        UIElement@ parent = CreateAttributeEditorParent(list, parameterNames[i], 0, 0);
        uint numCoords = 1;
        if (type >= VAR_VECTOR2 && type <= VAR_VECTOR4)
            numCoords = type - VAR_FLOAT + 1;

        Array<String> coordValues = value.ToString().Split(' ');

        for (uint j = 0; j < numCoords; ++j)
        {
            LineEdit@ attrEdit = CreateAttributeLineEdit(parent, null, 0, 0);
            attrEdit.vars["Coordinate"] = j;
            attrEdit.vars["Name"] = parameterNames[i];
            attrEdit.text = coordValues[j];

            CreateDragSlider(attrEdit);

            SubscribeToEvent(attrEdit, "TextChanged", "EditShaderParameter");
            SubscribeToEvent(attrEdit, "TextFinished", "EditShaderParameter");
        }
    }
}

void RefreshMaterialMiscParameters()
{
    if (editMaterial is null)
        return;
        
    inMaterialRefresh = true;

    BiasParameters bias = editMaterial.depthBias;
    LineEdit@ attrEdit = materialWindow.GetChild("ConstantBiasEdit", true);
    attrEdit.text = String(bias.constantBias);
    attrEdit = materialWindow.GetChild("SlopeBiasEdit", true);
    attrEdit.text = String(bias.slopeScaledBias);
    attrEdit = materialWindow.GetChild("RenderOrderEdit", true);
    attrEdit.text = String(uint(editMaterial.renderOrder));
    attrEdit = materialWindow.GetChild("VSDefinesEdit", true);
    attrEdit.text = editMaterial.vertexShaderDefines;
    attrEdit = materialWindow.GetChild("PSDefinesEdit", true);
    attrEdit.text = editMaterial.pixelShaderDefines;

    DropDownList@ attrList = materialWindow.GetChild("CullModeEdit", true);
    attrList.selection = editMaterial.cullMode;
    attrList = materialWindow.GetChild("ShadowCullModeEdit", true);
    attrList.selection = editMaterial.shadowCullMode;
    attrList = materialWindow.GetChild("FillModeEdit", true);
    attrList.selection = editMaterial.fillMode;

    CheckBox@ attrCheckBox = materialWindow.GetChild("OcclusionEdit", true);
    attrCheckBox.checked = editMaterial.occlusion;
    attrCheckBox = materialWindow.GetChild("AlphaToCoverageEdit", true);
    attrCheckBox.checked = editMaterial.alphaToCoverage;
    attrCheckBox = materialWindow.GetChild("LineAntiAliasEdit", true);
    attrCheckBox.checked = editMaterial.lineAntiAlias;

    inMaterialRefresh = false;
}

void RotateMaterialPreview(StringHash eventType, VariantMap& eventData)
{
    int elemX = eventData["ElementX"].GetInt();
    int elemY = eventData["ElementY"].GetInt();
    
    if (materialPreview.height > 0 && materialPreview.width > 0)
    {
        float yaw = ((materialPreview.height / 2) - elemY) * (90.0 / materialPreview.height);
        float pitch = ((materialPreview.width / 2) - elemX) * (90.0 / materialPreview.width);

        previewModelNode.rotation = previewModelNode.rotation.Slerp(Quaternion(yaw, pitch, 0), 0.1);
        materialPreview.QueueUpdate();
    }
}

void EditMaterialName(StringHash eventType, VariantMap& eventData)
{
    LineEdit@ nameEdit = eventData["Element"].GetPtr();
    String newMaterialName = nameEdit.text.Trimmed();
    if (!newMaterialName.empty)
    {
        Material@ newMaterial = cache.GetResource("Material", newMaterialName);
        if (newMaterial !is null)
            EditMaterial(newMaterial);
    }
}

void PickEditMaterial()
{
    @resourcePicker = GetResourcePicker(StringHash("Material"));
    if (resourcePicker is null)
        return;

    String lastPath = resourcePicker.lastPath;
    if (lastPath.empty)
        lastPath = sceneResourcePath;
    CreateFileSelector(localization.Get("Pick ") + resourcePicker.typeName, "OK", "Cancel", lastPath, resourcePicker.filters, resourcePicker.lastFilter, false);
    SubscribeToEvent(uiFileSelector, "FileSelected", "PickEditMaterialDone");
}

void PickEditMaterialDone(StringHash eventType, VariantMap& eventData)
{
    StoreResourcePickerPath();
    CloseFileSelector();

    if (!eventData["OK"].GetBool())
    {
        @resourcePicker = null;
        return;
    }

    String resourceName = eventData["FileName"].GetString();
    Resource@ res = GetPickedResource(resourceName);

    if (res !is null)
        EditMaterial(cast<Material>(res));

    @resourcePicker = null;
}

void NewMaterial()
{
    EditMaterial(Material());
}

void RevertMaterial()
{
    if (editMaterial is null)
        return;

    BeginMaterialEdit();
    cache.ReloadResource(editMaterial);
    EndMaterialEdit();
    
    RefreshMaterialEditor();
}

void SaveMaterial()
{
    if (editMaterial is null || editMaterial.name.empty)
        return;

    String fullName = cache.GetResourceFileName(editMaterial.name);
    if (fullName.empty)
        return;

    MakeBackup(fullName);
    File saveFile(fullName, FILE_WRITE);
    bool success;
    if (GetExtension(fullName) == ".json")
    {
        JSONFile json;
        editMaterial.Save(json.root);
        success = json.Save(saveFile);
    }
    else
        success = editMaterial.Save(saveFile);
    RemoveBackup(success, fullName);
}

void SaveMaterialAs()
{
    if (editMaterial is null)
        return;

    @resourcePicker = GetResourcePicker(StringHash("Material"));
    if (resourcePicker is null)
        return;

    String lastPath = resourcePicker.lastPath;
    if (lastPath.empty)
        lastPath = sceneResourcePath;
    CreateFileSelector("Save material as", "Save", "Cancel", lastPath, resourcePicker.filters, resourcePicker.lastFilter);
    SubscribeToEvent(uiFileSelector, "FileSelected", "SaveMaterialAsDone");
}

void SaveMaterialAsDone(StringHash eventType, VariantMap& eventData)
{
    StoreResourcePickerPath();
    CloseFileSelector();
    @resourcePicker = null;

    if (editMaterial is null)
        return;

    if (!eventData["OK"].GetBool())
    {
        @resourcePicker = null;
        return;
    }

    String fullName = eventData["FileName"].GetString();

    // Add default extension for saving if not specified
    String filter = eventData["Filter"].GetString();
    if (GetExtension(fullName).empty && filter != "*.*")
        fullName = fullName + filter.Substring(1);

    MakeBackup(fullName);
    File saveFile(fullName, FILE_WRITE);
    bool success;
    if (GetExtension(fullName) == ".json")
    {
        JSONFile json;
        editMaterial.Save(json.root);
        success = json.Save(saveFile);
    }
    else
        success = editMaterial.Save(saveFile);

    if (success)
    {
        saveFile.Close();
        RemoveBackup(true, fullName);

        // Load the new resource to update the name in the editor
        Material@ newMat = cache.GetResource("Material", GetResourceNameFromFullName(fullName));
        if (newMat !is null)
            EditMaterial(newMat);
    }
}

void EditModelPreviewChange(StringHash eventType, VariantMap& eventData)
{
    if (materialPreview is null)
        return;
        
    previewModelNode.scale = Vector3(1.0, 1.0, 1.0);
    
    DropDownList@ element = eventData["Element"].GetPtr();
    
    switch (element.selection)
    {
        case 0:
            previewModel.model = cache.GetResource("Model", "Models/Box.mdl");
            break;
        case 1:
            previewModel.model = cache.GetResource("Model", "Models/Sphere.mdl");
            break;
        case 2:
            previewModel.model = cache.GetResource("Model", "Models/Plane.mdl");
            break;
        case 3:
            previewModel.model = cache.GetResource("Model", "Models/Cylinder.mdl");
            previewModelNode.scale = Vector3(0.8, 0.8, 0.8);
            break;
        case 4:
            previewModel.model = cache.GetResource("Model", "Models/Cone.mdl");
            break;
        case 5:
            previewModel.model = cache.GetResource("Model", "Models/TeaPot.mdl");
            break;
    }
        
    materialPreview.QueueUpdate();
    
}

void EditShaderParameter(StringHash eventType, VariantMap& eventData)
{
    if (editMaterial is null)
        return;

    LineEdit@ attrEdit = eventData["Element"].GetPtr();
    uint coordinate = attrEdit.vars["Coordinate"].GetUInt();

    String name = attrEdit.vars["Name"].GetString();

    Variant oldValue = editMaterial.shaderParameters[name];
    Array<String> coordValues = oldValue.ToString().Split(' ');
    if (oldValue.type != VAR_BOOL)
        coordValues[coordinate] = String(attrEdit.text.ToFloat());
    else
        coordValues[coordinate] = attrEdit.text;

    String valueString;
    for (uint i = 0; i < coordValues.length; ++i)
    {
        valueString += coordValues[i];
        valueString += " ";
    }

    Variant newValue;
    newValue.FromString(oldValue.type, valueString);

    BeginMaterialEdit();
    editMaterial.shaderParameters[name] = newValue;
    EndMaterialEdit();
}

void CreateShaderParameter(StringHash eventType, VariantMap& eventData)
{
    if (editMaterial is null)
        return;

    LineEdit@ nameEdit = materialWindow.GetChild("ParameterNameEdit", true);
    String newName = nameEdit.text.Trimmed();
    if (newName.empty)
        return;

    DropDownList@ dropDown = eventData["Element"].GetPtr();
    Variant newValue;

    switch (dropDown.selection)
    {
    case 0:
        newValue = float(0);
        break;
    case 1:
        newValue = Vector2(0, 0);
        break;
    case 2:
        newValue = Vector3(0, 0, 0);
        break;
    case 3:
        newValue = Vector4(0, 0, 0, 0);
        break;
    case 4:
        newValue = int(0);
        break;
    case 5:
        newValue = false;
        break;
    }

    BeginMaterialEdit();
    editMaterial.shaderParameters[newName] = newValue;
    EndMaterialEdit();

    RefreshMaterialShaderParameters();
}

void DeleteShaderParameter()
{
    if (editMaterial is null)
        return;

    LineEdit@ nameEdit = materialWindow.GetChild("ParameterNameEdit", true);
    String name = nameEdit.text.Trimmed();
    if (name.empty)
        return;

    BeginMaterialEdit();
    editMaterial.RemoveShaderParameter(name);
    EndMaterialEdit();

    RefreshMaterialShaderParameters();
}

void PickMaterialTexture(StringHash eventType, VariantMap& eventData)
{
    if (editMaterial is null)
        return;

    UIElement@ button = eventData["Element"].GetPtr();
    resourcePickIndex = button.vars["Index"].GetUInt();

    @resourcePicker = GetResourcePicker(StringHash("Texture2D"));
    if (resourcePicker is null)
        return;

    String lastPath = resourcePicker.lastPath;
    if (lastPath.empty)
        lastPath = sceneResourcePath;
    CreateFileSelector(localization.Get("Pick ") + resourcePicker.typeName, "OK", "Cancel", lastPath, resourcePicker.filters, resourcePicker.lastFilter, false);
    SubscribeToEvent(uiFileSelector, "FileSelected", "PickMaterialTextureDone");
}

void PickMaterialTextureDone(StringHash eventType, VariantMap& eventData)
{
    StoreResourcePickerPath();
    CloseFileSelector();

    if (!eventData["OK"].GetBool())
    {
        @resourcePicker = null;
        return;
    }

    String resourceName = eventData["FileName"].GetString();
    Resource@ res = GetPickedResource(resourceName);

    if (res !is null && editMaterial !is null)
    {
        BeginMaterialEdit();
        editMaterial.textures[TextureUnit(resourcePickIndex)] = res;
        EndMaterialEdit();

        RefreshMaterialTextures(false);
    }

    @resourcePicker = null;
}

void EditMaterialTexture(StringHash eventType, VariantMap& eventData)
{
    if (editMaterial is null)
        return;

    LineEdit@ attrEdit = eventData["Element"].GetPtr();
    String textureName = attrEdit.text.Trimmed();
    uint index = attrEdit.vars["Index"].GetUInt();

    BeginMaterialEdit();

    if (!textureName.empty)
    {
        Texture@ texture = cache.GetResource(GetExtension(textureName) == ".xml" ? "TextureCube" : "Texture2D", textureName);
        editMaterial.textures[TextureUnit(index)] = texture;
    }
    else
        editMaterial.textures[TextureUnit(index)] = null;

    EndMaterialEdit();
}

void NewTechnique()
{
    if (editMaterial is null)
        return;
        
    BeginMaterialEdit();
    editMaterial.numTechniques = editMaterial.numTechniques + 1;
    EndMaterialEdit();
    
    RefreshMaterialTechniques();
}

void DeleteTechnique()
{
    if (editMaterial is null || editMaterial.numTechniques < 2)
        return;

    BeginMaterialEdit();
    editMaterial.numTechniques = editMaterial.numTechniques - 1;
    EndMaterialEdit();
    
    RefreshMaterialTechniques();
}

void PickMaterialTechnique(StringHash eventType, VariantMap& eventData)
{
    if (editMaterial is null)
        return;

    UIElement@ button = eventData["Element"].GetPtr();
    resourcePickIndex = button.vars["Index"].GetUInt();

    @resourcePicker = GetResourcePicker(StringHash("Technique"));
    if (resourcePicker is null)
        return;

    String lastPath = resourcePicker.lastPath;
    if (lastPath.empty)
        lastPath = sceneResourcePath;
    CreateFileSelector(localization.Get("Pick ") + resourcePicker.typeName, "OK", "Cancel", lastPath, resourcePicker.filters, resourcePicker.lastFilter, false);
    SubscribeToEvent(uiFileSelector, "FileSelected", "PickMaterialTechniqueDone");
}

void PickMaterialTechniqueDone(StringHash eventType, VariantMap& eventData)
{
    StoreResourcePickerPath();
    CloseFileSelector();

    if (!eventData["OK"].GetBool())
    {
        @resourcePicker = null;
        return;
    }

    String resourceName = eventData["FileName"].GetString();
    Resource@ res = GetPickedResource(resourceName);

    if (res !is null && editMaterial !is null)
    {
        BeginMaterialEdit();
        TechniqueEntry entry = editMaterial.techniqueEntries[resourcePickIndex];
        editMaterial.SetTechnique(resourcePickIndex, res, entry.qualityLevel, entry.lodDistance);
        EndMaterialEdit();

        RefreshMaterialTechniques(false);
    }

    @resourcePicker = null;
}

void EditMaterialTechnique(StringHash eventType, VariantMap& eventData)
{
    if (editMaterial is null)
        return;

    LineEdit@ attrEdit = eventData["Element"].GetPtr();
    String techniqueName = attrEdit.text.Trimmed();
    uint index = attrEdit.vars["Index"].GetUInt();

    BeginMaterialEdit();

    Technique@ newTech;
    if (!techniqueName.empty)
        newTech = cache.GetResource("Technique", techniqueName);

    TechniqueEntry entry = editMaterial.techniqueEntries[index];
    editMaterial.SetTechnique(index, newTech, entry.qualityLevel, entry.lodDistance);

    EndMaterialEdit();
}

void EditTechniqueQuality(StringHash eventType, VariantMap& eventData)
{
    if (editMaterial is null)
        return;

    LineEdit@ attrEdit = eventData["Element"].GetPtr();
    uint newQualityLevel = attrEdit.text.ToUInt();
    uint index = attrEdit.vars["Index"].GetUInt();

    BeginMaterialEdit();
    TechniqueEntry entry = editMaterial.techniqueEntries[index];
    editMaterial.SetTechnique(index, entry.technique, newQualityLevel, entry.lodDistance);
    EndMaterialEdit();
}

void EditTechniqueLodDistance(StringHash eventType, VariantMap& eventData)
{
    if (editMaterial is null)
        return;

    LineEdit@ attrEdit = eventData["Element"].GetPtr();
    float newLodDistance = attrEdit.text.ToFloat();
    uint index = attrEdit.vars["Index"].GetUInt();

    BeginMaterialEdit();
    TechniqueEntry entry = editMaterial.techniqueEntries[index];
    editMaterial.SetTechnique(index, entry.technique, entry.qualityLevel, newLodDistance);
    EndMaterialEdit();
}

void SortTechniques()
{
    if (editMaterial is null)
        return;
        
    BeginMaterialEdit();
    editMaterial.SortTechniques();
    EndMaterialEdit();
    
    RefreshMaterialTechniques();
}

void EditConstantBias(StringHash eventType, VariantMap& eventData)
{
    if (editMaterial is null || inMaterialRefresh)
        return;
        
    BeginMaterialEdit();
 
    LineEdit@ attrEdit = eventData["Element"].GetPtr();
    BiasParameters bias = editMaterial.depthBias;
    bias.constantBias = attrEdit.text.ToFloat();
    editMaterial.depthBias = bias;

    EndMaterialEdit();
}

void EditSlopeBias(StringHash eventType, VariantMap& eventData)
{
    if (editMaterial is null || inMaterialRefresh)
        return;
        
    BeginMaterialEdit();
 
    LineEdit@ attrEdit = eventData["Element"].GetPtr();
    BiasParameters bias = editMaterial.depthBias;
    bias.slopeScaledBias = attrEdit.text.ToFloat();
    editMaterial.depthBias = bias;

    EndMaterialEdit();
}

void EditRenderOrder(StringHash eventType, VariantMap& eventData)
{
    if (editMaterial is null || inMaterialRefresh)
        return;

    BeginMaterialEdit();

    LineEdit@ attrEdit = eventData["Element"].GetPtr();
    editMaterial.renderOrder = attrEdit.text.ToUInt();

    EndMaterialEdit();
}

void EditCullMode(StringHash eventType, VariantMap& eventData)
{
    if (editMaterial is null || inMaterialRefresh)
        return;
        
    BeginMaterialEdit();
    
    DropDownList@ attrEdit = eventData["Element"].GetPtr();
    editMaterial.cullMode = CullMode(attrEdit.selection);

    EndMaterialEdit();
}

void EditShadowCullMode(StringHash eventType, VariantMap& eventData)
{
    if (editMaterial is null || inMaterialRefresh)
        return;
        
    BeginMaterialEdit();
    
    DropDownList@ attrEdit = eventData["Element"].GetPtr();
    editMaterial.shadowCullMode = CullMode(attrEdit.selection);

    EndMaterialEdit();
}

void EditFillMode(StringHash eventType, VariantMap& eventData)
{
    if (editMaterial is null || inMaterialRefresh)
        return;
        
    BeginMaterialEdit();
    
    DropDownList@ attrEdit = eventData["Element"].GetPtr();
    editMaterial.fillMode = FillMode(attrEdit.selection);

    EndMaterialEdit();
}

void EditOcclusion(StringHash eventType, VariantMap& eventData)
{
    if (editMaterial is null || inMaterialRefresh)
        return;

    BeginMaterialEdit();

    CheckBox@ attrEdit = eventData["Element"].GetPtr();
    editMaterial.occlusion = attrEdit.checked;

    EndMaterialEdit();
}

void EditAlphaToCoverage(StringHash eventType, VariantMap& eventData)
{
    if (editMaterial is null || inMaterialRefresh)
        return;

    BeginMaterialEdit();

    CheckBox@ attrEdit = eventData["Element"].GetPtr();
    editMaterial.alphaToCoverage = attrEdit.checked;

    EndMaterialEdit();
}

void EditLineAntiAlias(StringHash eventType, VariantMap& eventData)
{
    if (editMaterial is null || inMaterialRefresh)
        return;

    BeginMaterialEdit();

    CheckBox@ attrEdit = eventData["Element"].GetPtr();
    editMaterial.lineAntiAlias = attrEdit.checked;

    EndMaterialEdit();
}

void EditVSDefines(StringHash eventType, VariantMap& eventData)
{
    if (editMaterial is null || inMaterialRefresh)
        return;

    BeginMaterialEdit();

    LineEdit@ attrEdit = eventData["Element"].GetPtr();
    editMaterial.vertexShaderDefines = attrEdit.text.Trimmed();

    EndMaterialEdit();
}

void EditPSDefines(StringHash eventType, VariantMap& eventData)
{
    if (editMaterial is null || inMaterialRefresh)
        return;

    BeginMaterialEdit();

    LineEdit@ attrEdit = eventData["Element"].GetPtr();
    editMaterial.pixelShaderDefines = attrEdit.text.Trimmed();

    EndMaterialEdit();
}

void BeginMaterialEdit()
{
    if (editMaterial is null)
        return;

    oldMaterialState = XMLFile();
    XMLElement materialElem = oldMaterialState.CreateRoot("material");
    editMaterial.Save(materialElem);
}

void EndMaterialEdit()
{
    if (editMaterial is null)
        return;
    if (!dragEditAttribute)
    {
        EditMaterialAction@ action = EditMaterialAction();
        action.Define(editMaterial, oldMaterialState);
        SaveEditAction(action);
    }
    
    materialPreview.QueueUpdate();
}
