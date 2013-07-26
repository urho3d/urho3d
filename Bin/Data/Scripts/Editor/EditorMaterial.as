// Urho3D material editor

Window@ materialWindow;

void CreateMaterialEditor()
{
    if (materialWindow !is null)
        return;
    
    materialWindow = ui.LoadLayout(cache.GetResource("XMLFile", "UI/EditorMaterialWindow.xml"));
    ui.root.AddChild(materialWindow);
    materialWindow.opacity = uiMaxOpacity;
    CenterDialog(materialWindow);
}

void EditMaterial(Material@ mat)
{
    CreateMaterialEditor();
}