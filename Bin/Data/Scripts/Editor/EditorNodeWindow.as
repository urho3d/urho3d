// Urho3D editor attribute inspector window handling
#include "Scripts/Editor/AttributeEditor.as"

Window@ nodeWindow;
UIElement@ componentParentContainer;
XMLFile@ componentXMLResource;

bool applyMaterialList = true;

const String STRIKED_OUT = "---";

void AddComponentContainer()
{
    componentParentContainer.LoadXML(componentXMLResource, uiStyle);
}

void DeleteAllComponentContainers()
{
    componentParentContainer.RemoveAllChildren();
}

UIElement@ GetComponentContainer(uint index)
{
    return componentParentContainer.children[index];
}

void CreateNodeWindow()
{
    if (nodeWindow !is null)
        return;

    InitResourcePicker();
    InitVectorStructs();

    nodeWindow = ui.LoadLayout(cache.GetResource("XMLFile", "UI/EditorNodeWindow.xml"), uiStyle);
    componentXMLResource = cache.GetResource("XMLFile", "UI/EditorComponent.xml");
    componentParentContainer = nodeWindow.GetChild("ComponentParentContainer", true);
    AddComponentContainer();
    ui.root.AddChild(nodeWindow);
    int height = Min(ui.root.height - 60, 500);
    nodeWindow.SetSize(300, height);
    nodeWindow.SetPosition(ui.root.width - 20 - nodeWindow.width, 40);
    nodeWindow.opacity = uiMaxOpacity;
    nodeWindow.BringToFront();
    UpdateNodeWindow();

    SubscribeToEvent(nodeWindow.GetChild("CloseButton", true), "Released", "HideNodeWindow");
    SubscribeToEvent(nodeWindow.GetChild("NewVarDropDown", true), "ItemSelected", "CreateNewVariable");
    SubscribeToEvent(nodeWindow.GetChild("DeleteVarButton", true), "Released", "DeleteVariable");
}

void HideNodeWindow()
{
    nodeWindow.visible = false;
}

void ShowNodeWindow()
{
    nodeWindow.visible = true;
    nodeWindow.BringToFront();
}

void AppendID(String&inout localIds, String&inout ids, Node@ node)
{
    if (node.id >= FIRST_LOCAL_ID)
        localIds += " " + String(node.id - FIRST_LOCAL_ID);
    else
        ids += " " + String(node.id);
}

void UpdateNodeWindow()
{
    // If a resource pick was in progress, it cannot be completed now, as component was changed
    PickResourceCanceled();

    Text@ nodeTitle = nodeWindow.GetChild("NodeTitle", true);
    if (editNodes.length == 0)
        nodeTitle.text = "No node";
    else if (editNode !is null)
    {
        String idStr;
        if (editNode.id >= FIRST_LOCAL_ID)
            idStr = " Local ID " + String(editNode.id - FIRST_LOCAL_ID);
        else
            idStr = " ID " + String(editNode.id);
        nodeTitle.text = editNode.typeName + idStr;
    }
    else
        nodeTitle.text = editNodes[0].typeName + " ID " + STRIKED_OUT + " (" + editNodes.length + "x)";

    UpdateAttributes(true);
}

Array<Serializable@> ToSerializableArray(Array<Node@> nodes)
{
    Array<Serializable@> serializables;
    for (uint i = 0; i < nodes.length; ++i)
        serializables.Push(nodes[i]);
    return serializables;
}

void UpdateAttributes(bool fullUpdate)
{
    if (nodeWindow !is null)
    {
        UpdateAttributes(ToSerializableArray(editNodes), nodeWindow.GetChild("NodeAttributeList", true), fullUpdate);

        if (fullUpdate)
            DeleteAllComponentContainers();
        
        if (editComponents.empty)
        {
            if (componentParentContainer.numChildren == 0)
                AddComponentContainer();
            
            Text@ componentTitle = GetComponentContainer(0).GetChild("ComponentTitle");
            if (selectedComponents.length <= 1)
                componentTitle.text = "No component";
            else
                componentTitle.text = selectedComponents.length + " components";            
        }
        else
        {
            uint numEditableComponents = editComponents.length / numEditableComponentsPerNode;
            String multiplierText;
            if (numEditableComponents > 1)
                multiplierText = " (" + numEditableComponents + "x)";
            
            for (uint j = 0; j < numEditableComponentsPerNode; ++j)
            {
                if (j >= componentParentContainer.numChildren)
                    AddComponentContainer();
                
                Text@ componentTitle = GetComponentContainer(j).GetChild("ComponentTitle");
                componentTitle.text = GetComponentTitle(editComponents[j * numEditableComponents], 0) + multiplierText;
                
                Array<Serializable@> components;
                for (uint i = 0; i < numEditableComponents; ++i)
                    components.Push(editComponents[j * numEditableComponents + i]);
                
                UpdateAttributes(components, GetComponentContainer(j).GetChild("ComponentAttributeList"), fullUpdate);
            }
        }
    }
}

void UpdateNodeAttributes()
{
    if (nodeWindow !is null)
    {
        UpdateAttributes(ToSerializableArray(editNodes), nodeWindow.GetChild("NodeAttributeList", true), false);
    }
}

void PostEditAttribute(Array<Serializable@>@ serializables, uint index)
{
    // If node name changed, update it in the scene window also
    if (serializables[0].attributeInfos[index].name == "Name")
    {
        for (uint i = 0; i < serializables.length; ++i)
            UpdateSceneWindowNodeOnly(serializables[i]);
    }

    // If a StaticModel/AnimatedModel/Skybox model was changed, apply a possibly different material list
    if (applyMaterialList && serializables[0].attributeInfos[index].name == "Model")
    {
        for (uint i = 0; i < serializables.length; ++i)
        {
            StaticModel@ staticModel = cast<StaticModel>(serializables[i]);
            if (staticModel !is null)
                ApplyMaterialList(staticModel);
        }
    }
}

void SetAttributeEditorID(UIElement@ attrEdit, Array<Serializable@>@ serializables)
{
    // All target serializables must be either nodes or components, so can check the first for the type
    Node@ node = cast<Node>(serializables[0]);
    Array<Variant> ids;
    if (node !is null)
    {
        for (uint i = 0; i < serializables.length; ++i)
            ids.Push(Variant(cast<Node>(serializables[i]).id));
        attrEdit.vars["NodeIDs"] = ids;
    }
    else
    {
        for (uint i = 0; i < serializables.length; ++i)
            ids.Push(Variant(cast<Component>(serializables[i]).id));
        attrEdit.vars["ComponentIDs"] = ids;
    }
}

Array<Serializable@>@ GetAttributeEditorTargets(UIElement@ attrEdit)
{
    Array<Serializable@> ret;

    if (attrEdit.vars.Contains("NodeIDs"))
    {
        Array<Variant>@ ids = attrEdit.vars["NodeIDs"].GetVariantVector();
        for (uint i = 0; i < ids.length; ++i)
        {
            Node@ node = editorScene.GetNode(ids[i].GetUInt());
            if (node !is null)
                ret.Push(node);
        }
    }
    if (attrEdit.vars.Contains("ComponentIDs"))
    {
        Array<Variant>@ ids = attrEdit.vars["ComponentIDs"].GetVariantVector();
        for (uint i = 0; i < ids.length; ++i)
        {
            Component@ component = editorScene.GetComponent(ids[i].GetUInt());
            if (component !is null)
                ret.Push(component);
        }
    }
    
    return ret;
}

void CreateNewVariable(StringHash eventType, VariantMap& eventData)
{
    if (editNodes.length == 0)
        return;

    DropDownList@ dropDown = eventData["Element"].GetUIElement();
    LineEdit@ nameEdit = nodeWindow.GetChild("VarNameEdit", true);
    String sanitatedVarName = nameEdit.text.Trimmed().Replaced(";", "");
    if (sanitatedVarName.empty)
        return;

    editorScene.RegisterVar(sanitatedVarName);

    Variant newValue;
    switch (dropDown.selection)
    {
    case 0:
        newValue = int(0);
        break;
    case 1:
        newValue = false;
        break;
    case 2:
        newValue = float(0.0);
        break;
    case 3:
        newValue = String();
        break;
    case 4:
        newValue = Vector3();
        break;
    case 5:
        newValue = Color();
        break;
    }

    // If we overwrite an existing variable, must recreate the editor(s) for the correct type
    bool overwrite = false;
    for (uint i = 0; i < editNodes.length; ++i)
    {
        overwrite = overwrite || editNodes[i].vars.Contains(sanitatedVarName);
        editNodes[i].vars[sanitatedVarName] = newValue;
    }
    UpdateAttributes(overwrite);
}

void DeleteVariable(StringHash eventType, VariantMap& eventData)
{
    if (editNodes.length == 0)
        return;

    LineEdit@ nameEdit = nodeWindow.GetChild("VarNameEdit", true);
    String sanitatedVarName = nameEdit.text.Trimmed().Replaced(";", "");
    if (sanitatedVarName.empty)
        return;

    bool erased = false;
    for (uint i = 0; i < editNodes.length; ++i)
    {
        // \todo Should first check whether var in question is editable
        erased = editNodes[i].vars.Erase(sanitatedVarName) || erased;
    }
    if (erased)
        UpdateAttributes(false);
}
