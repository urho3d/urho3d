
bool objExportZUp_ = false;
bool objExportRightHanded_ = true;

void ExportSceneToOBJ(String fileName)
{
    if (fileName.empty)
    {
        MessageBox("File name for OBJ export unspecified");
        return;
    }
    // append obj extension if missing
    if (GetExtension(fileName).empty)
        fileName += ".obj";
        
    Octree@ octree = scene.GetComponent("Octree");
    if (octree is null)
    {
        MessageBox("Octree missing from scene");
        return;
    }
        
    Array<Drawable@> drawables = octree.GetAllDrawables();
    if (drawables.length == 0)
    {
        MessageBox("No drawables to export in the scene");
        return;
    }

    RemoveDebugDrawables(drawables);

    File@ file = File(fileName, FILE_WRITE);
    if (WriteDrawablesToOBJ(drawables, file, objExportZUp_, objExportRightHanded_))
    {
        MessageBox("OBJ file written to " + fileName, "Success");
        file.Close();
    }
    else
    {
        // Cleanup our file so we don't mislead anyone
        MessageBox("Unable to write OBJ file");
        file.Close();
        fileSystem.Delete(fileName);
    }
}

void ExportSelectedToOBJ(String fileName)
{
    if (fileName.empty)
    {
        MessageBox("File name for OBJ export unspecified");
        return;
    }
    if (GetExtension(fileName).empty)
        fileName += ".obj";
    
    Array<Drawable@> drawables;
    
    // Add any explicitly selected drawables
    for (uint i = 0; i < selectedComponents.length; ++i)
    {
        Drawable@ drawable = cast<Drawable>(selectedComponents[i]);
        if (drawable !is null)
            drawables.Push(drawable);
    }
    
    // Add drawables of any selected nodes
    for (uint i = 0; i < selectedNodes.length; ++i)
    {
        Array<Component@>@ components = selectedNodes[i].GetComponents();
        for (uint comp = 0; comp < components.length; ++comp)
        {
            Drawable@ drawable = cast<Drawable>(components[comp]);
            if (drawable !is null && drawables.FindByRef(drawable) < 0)
                drawables.Push(drawable);
        }
    }

    RemoveDebugDrawables(drawables);

    if (drawables.length > 0)
    {
        File@ file = File(fileName, FILE_WRITE);
        if (WriteDrawablesToOBJ(drawables, file, objExportZUp_, objExportRightHanded_))
        {
            MessageBox("OBJ file written to " + fileName, "Success");
            file.Close();
        }
        else
        {
            MessageBox("Unable to write OBJ file");
            // Cleanup our file so we don't mislead anyone
            file.Close();
            fileSystem.Delete(fileName);
        }
    }
    else
    {
        MessageBox("No selected drawables to export to OBJ");
    }
}

void RemoveDebugDrawables(Array<Drawable@>@ drawables)
{
    for (uint i = 0; i < drawables.length;)
    {
        if (drawables[i].node !is null && (drawables[i].node.name == "EditorGizmo" || drawables[i].node.name == "DebugIconsContainer"
            || drawables[i].node.name == "EditorGrid"))
            drawables.Erase(i);
        else
            ++i;
    }
}

void HandleOBJZUpChanged(StringHash eventType, VariantMap& eventData)
{
    CheckBox@ checkBox = cast<CheckBox>(eventData["Element"].GetPtr());
    objExportZUp_ = checkBox.checked;
}

void HandleOBJRightHandedChanged(StringHash eventType, VariantMap& eventData)
{
    CheckBox@ checkBox = cast<CheckBox>(eventData["Element"].GetPtr());
    objExportRightHanded_ = checkBox.checked;
}