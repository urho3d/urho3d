// Urho3D material editor

Window@ materialWindow;
Material@ editMaterial;

void CreateMaterialEditor()
{
    if (materialWindow !is null)
        return;

    materialWindow = ui.LoadLayout(cache.GetResource("XMLFile", "UI/EditorMaterialWindow.xml"));
    ui.root.AddChild(materialWindow);
    materialWindow.opacity = uiMaxOpacity;

    RefreshMaterialEditor();
    
    int height = Min(ui.root.height - 60, 500);
    materialWindow.SetSize(300, height);
    CenterDialog(materialWindow);

    HideMaterialEditor();

    SubscribeToEvent(materialWindow.GetChild("NewButton", true), "Released", "NewMaterial");
    SubscribeToEvent(materialWindow.GetChild("RevertButton", true), "Released", "RevertMaterial");
    SubscribeToEvent(materialWindow.GetChild("SaveButton", true), "Released", "SaveMaterial");
    SubscribeToEvent(materialWindow.GetChild("SaveAsButton", true), "Released", "SaveMaterialAs");
    SubscribeToEvent(materialWindow.GetChild("CloseButton", true), "Released", "HideMaterialEditor");
    SubscribeToEvent(materialWindow.GetChild("NewParameterDropDown", true), "ItemSelected", "CreateShaderParameter");
    SubscribeToEvent(materialWindow.GetChild("DeleteParameterButton", true), "Released", "DeleteShaderParameter");
}

bool ShowMaterialEditor()
{
    materialWindow.visible = true;       
    materialWindow.BringToFront();
    return true;
}

void HideMaterialEditor()
{
    materialWindow.visible = false;
}

void EditMaterial(Material@ mat)
{
    editMaterial = mat;
    RefreshMaterialEditor();
    ShowMaterialEditor();
}

void RefreshMaterialEditor()
{
    RefreshMaterialName();
    RefreshMaterialTechniques();
    RefreshMaterialTextures();
    RefreshMaterialShaderParameters();
}

void RefreshMaterialName()
{
    UIElement@ container = materialWindow.GetChild("NameContainer");
    container.RemoveAllChildren();

    LineEdit@ nameEdit = CreateAttributeLineEdit(container, null, 0, 0);
    if (editMaterial !is null)
        nameEdit.text = editMaterial.name;
    SubscribeToEvent(nameEdit, "TextFinished", "EditMaterialName");

    Button@ pickButton = CreateResourcePickerButton(container, null, 0, 0, "Pick");
    SubscribeToEvent(pickButton, "Released", "PickEditMaterial");
}

void RefreshMaterialTechniques()
{
    ListView@ list = materialWindow.GetChild("TechniqueList");
    list.RemoveAllItems();
}

void RefreshMaterialTextures()
{
    ListView@ list = materialWindow.GetChild("TextureList");
    list.RemoveAllItems();

    for (uint i = 0; i < MAX_MATERIAL_TEXTURE_UNITS; ++i)
    {
        UIElement@ parent = CreateAttributeEditorParentWithSeparatedLabel(list, GetTextureUnitName(TextureUnit(i)), i, 0, false);
        
        UIElement@ container = UIElement();
        container.SetLayout(LM_HORIZONTAL, 4, IntRect(10, 0, 4, 0));
        container.SetFixedHeight(ATTR_HEIGHT);
        parent.AddChild(container);

        LineEdit@ nameEdit = CreateAttributeLineEdit(container, null, i, 0);
        Button@ pickButton = CreateResourcePickerButton(container, null, i, 0, "Pick");
        SubscribeToEvent(pickButton, "Released", "PickMaterialTexture");
        Button@ openButton = CreateResourcePickerButton(container, null, i, 0, "Open");
        SubscribeToEvent(openButton, "Released", "OpenResource");

        if (editMaterial !is null)
        {
            Texture@ texture = editMaterial.textures[i];
            if (texture !is null)
                nameEdit.text = texture.name;
        }
        
        SubscribeToEvent(nameEdit, "TextFinished", "EditMaterialTexture");
    }
}

void RefreshMaterialShaderParameters()
{
    ListView@ list = materialWindow.GetChild("ShaderParameterList");
    list.RemoveAllItems();
    if (editMaterial is null)
        return;

    Array<String>@ parameterNames = editMaterial.shaderParameterNames;

    for (uint i = 0; i < parameterNames.length; ++i)
    {
        VariantType type = editMaterial.shaderParameters[parameterNames[i]].type;
        Variant value = editMaterial.shaderParameters[parameterNames[i]];
        UIElement@ parent = CreateAttributeEditorParent(list, parameterNames[i], 0, 0);
        uint numCoords = type - VAR_FLOAT + 1;

        Array<String> coordValues = value.ToString().Split(' ');

        for (uint j = 0; j < numCoords; ++j)
        {
            LineEdit@ attrEdit = CreateAttributeLineEdit(parent, null, 0, 0);
            attrEdit.vars["Coordinate"] = j;
            attrEdit.vars["Name"] = parameterNames[i];
            attrEdit.text = coordValues[j];
            SubscribeToEvent(attrEdit, "TextChanged", "EditShaderParameter");
            SubscribeToEvent(attrEdit, "TextFinished", "EditShaderParameter");
        }
    }
}

void EditMaterialName(StringHash eventType, VariantMap& eventData)
{
    LineEdit@ nameEdit = eventData["Element"].GetUIElement();
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
    @resourcePicker = GetResourcePicker(ShortStringHash("Material"));
    if (resourcePicker is null)
        return;

    String lastPath = resourcePicker.lastPath;
    if (lastPath.empty)
        lastPath = sceneResourcePath;
    CreateFileSelector("Pick " + resourcePicker.typeName, "OK", "Cancel", lastPath, resourcePicker.filters, resourcePicker.lastFilter);
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

    cache.ReloadResource(editMaterial);
    RefreshMaterialEditor();
}

void SaveMaterial()
{
    if (editMaterial is null || editMaterial.name.empty)
        return;

    String fullName = cache.GetResourceFileName(editMaterial.name);
    if (fullName.empty)
        return;

    File saveFile(fullName, FILE_WRITE);
    editMaterial.Save(saveFile);
}

void SaveMaterialAs()
{
    if (editMaterial is null)
        return;

    @resourcePicker = GetResourcePicker(ShortStringHash("Material"));
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
    File saveFile(fullName, FILE_WRITE);
    if (editMaterial.Save(saveFile))
    {
        saveFile.Close();

        // Load the new resource to update the name in the editor
        Material@ newMat = cache.GetResource("Material", GetResourceNameFromFullName(fullName));
        if (newMat !is null)
            EditMaterial(newMat);
    }
}

void EditShaderParameter(StringHash eventType, VariantMap& eventData)
{
    if (editMaterial is null)
        return;

    LineEdit@ attrEdit = eventData["Element"].GetUIElement();
    uint coordinate = attrEdit.vars["Coordinate"].GetUInt();

    String name = attrEdit.vars["Name"].GetString();

    Variant oldValue = editMaterial.shaderParameters[name];
    Array<String> coordValues = oldValue.ToString().Split(' ');
    coordValues[coordinate] = String(attrEdit.text.ToFloat());

    String valueString;
    for (uint i = 0; i < coordValues.length; ++i)
    {
        valueString += coordValues[i];
        valueString += " ";
    }

    Variant newValue;
    newValue.FromString(oldValue.type, valueString);
    
    editMaterial.shaderParameters[name] = newValue;
}

void CreateShaderParameter(StringHash eventType, VariantMap& eventData)
{
    if (editMaterial is null)
        return;

    LineEdit@ nameEdit = materialWindow.GetChild("ParameterNameEdit", true);
    String newName = nameEdit.text.Trimmed();
    if (newName.empty)
        return;

    DropDownList@ dropDown = eventData["Element"].GetUIElement();
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
    }

    editMaterial.shaderParameters[newName] = newValue;
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

    editMaterial.RemoveShaderParameter(name);
    RefreshMaterialShaderParameters();
}

void PickMaterialTexture(StringHash eventType, VariantMap& eventData)
{
    if (editMaterial is null)
        return;

    UIElement@ button = eventData["Element"].GetUIElement();
    resourcePickIndex = button.vars["Index"].GetUInt();

    @resourcePicker = GetResourcePicker(ShortStringHash("Texture2D"));
    if (resourcePicker is null)
        return;

    String lastPath = resourcePicker.lastPath;
    if (lastPath.empty)
        lastPath = sceneResourcePath;
    CreateFileSelector("Pick " + resourcePicker.typeName, "OK", "Cancel", lastPath, resourcePicker.filters, resourcePicker.lastFilter);
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
        editMaterial.textures[resourcePickIndex] = res;
        RefreshMaterialTextures();
    }

    @resourcePicker = null;
}

void EditMaterialTexture(StringHash eventType, VariantMap& eventData)
{
    if (editMaterial is null)
        return;

    LineEdit@ attrEdit = eventData["Element"].GetUIElement();
    String textureName = attrEdit.text.Trimmed();
    uint index = attrEdit.vars["Index"].GetUInt();
    
    if (!textureName.empty)
    {
        Texture@ texture = cache.GetResource(GetExtension(textureName) == ".xml" ? "TextureCube" : "Texture2D", textureName);
        editMaterial.textures[index] = texture;
    }
    else
        editMaterial.textures[index] =null;

}

