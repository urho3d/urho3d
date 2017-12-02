// Urho3D Duplicator Editor

Window@ duplicatorWindow;
bool inDuplicatorRefresh = false;

Vector3 Position;
Vector3 Rotation;
Vector3 Scale;
uint DuplicatorCount;
String tagName = "TagEditDuplicator";
bool isSwitchOrder = false;
bool isClonesInChild = false;

void CreateDuplicatorEditor()
{
    if (duplicatorWindow !is null)
        return;
        
    duplicatorWindow = ui.LoadLayout(cache.GetResource("XMLFile", "UI/EditorDuplicator.xml"));
    ui.root.AddChild(duplicatorWindow);
    duplicatorWindow.opacity = uiMaxOpacity;

    InitDuplicatorWindow();
    RefreshDuplicatorWindow();

    int height = Min(ui.root.height - 60, 750);    
    duplicatorWindow.SetSize(400, 0);
    CenterDialog(duplicatorWindow);

    HideDuplicatorEditor();

    SubscribeToEvent(duplicatorWindow.GetChild("CloseButton", true), "Released", "HideDuplicatorEditor");
    SubscribeToEvent(duplicatorWindow.GetChild("Count", true), "TextChanged", "EditDuplicatorCount");
    SubscribeToEvent(duplicatorWindow.GetChild("PosX", true), "TextChanged", "EditDuplicatorPos");
    SubscribeToEvent(duplicatorWindow.GetChild("PosY", true), "TextChanged", "EditDuplicatorPos");
    SubscribeToEvent(duplicatorWindow.GetChild("PosZ", true), "TextChanged", "EditDuplicatorPos");
    SubscribeToEvent(duplicatorWindow.GetChild("RotX", true), "TextChanged", "EditDuplicatorRot");
    SubscribeToEvent(duplicatorWindow.GetChild("RotY", true), "TextChanged", "EditDuplicatorRot");
    SubscribeToEvent(duplicatorWindow.GetChild("RotZ", true), "TextChanged", "EditDuplicatorRot");
    SubscribeToEvent(duplicatorWindow.GetChild("ScaleX", true), "TextChanged", "EditDuplicatorScale");
    SubscribeToEvent(duplicatorWindow.GetChild("ScaleY", true), "TextChanged", "EditDuplicatorScale");
    SubscribeToEvent(duplicatorWindow.GetChild("ScaleZ", true), "TextChanged", "EditDuplicatorScale");
    SubscribeToEvent(duplicatorWindow.GetChild("CheckBox2", true), "Toggled", "OnCheckBox2");
    SubscribeToEvent(duplicatorWindow.GetChild("CheckBox3", true), "Toggled", "OnCheckBox3");
    SubscribeToEvent(duplicatorWindow.GetChild("ButtonPreview", true), "Released", "OnButtonPreview");
    SubscribeToEvent(duplicatorWindow.GetChild("ButtonClear", true), "Released", "OnButtonClear");
    SubscribeToEvent(duplicatorWindow.GetChild("ButtonApply", true), "Released", "OnButtonApply");
}

void InitDuplicatorWindow()
{
    DuplicatorCount = 1;

    Position = Vector3(0,0,0);
    Rotation = Vector3(0,0,0);
    Scale = Vector3(1,1,1);

    CreateDragSlider(cast<LineEdit>(duplicatorWindow.GetChild("Count", true)));
    CreateDragSlider(cast<LineEdit>(duplicatorWindow.GetChild("PosX", true)));
    CreateDragSlider(cast<LineEdit>(duplicatorWindow.GetChild("PosY", true)));
    CreateDragSlider(cast<LineEdit>(duplicatorWindow.GetChild("PosZ", true)));
    CreateDragSlider(cast<LineEdit>(duplicatorWindow.GetChild("RotX", true)));
    CreateDragSlider(cast<LineEdit>(duplicatorWindow.GetChild("RotY", true)));
    CreateDragSlider(cast<LineEdit>(duplicatorWindow.GetChild("RotZ", true)));
    CreateDragSlider(cast<LineEdit>(duplicatorWindow.GetChild("ScaleX", true)));
    CreateDragSlider(cast<LineEdit>(duplicatorWindow.GetChild("ScaleY", true)));
    CreateDragSlider(cast<LineEdit>(duplicatorWindow.GetChild("ScaleZ", true)));    
}

void RefreshDuplicatorWindow()
{
    inDuplicatorRefresh = true;

    RefreshDuplicatorWindowAttributes();

    inDuplicatorRefresh = false;
}


void RefreshDuplicatorWindowAttributes()
{
    cast<LineEdit>(duplicatorWindow.GetChild("Count", true)).text = DuplicatorCount;
    cast<LineEdit>(duplicatorWindow.GetChild("PosX", true)).text = Position.x;
    cast<LineEdit>(duplicatorWindow.GetChild("PosY", true)).text = Position.y;
    cast<LineEdit>(duplicatorWindow.GetChild("PosZ", true)).text = Position.z;
    cast<LineEdit>(duplicatorWindow.GetChild("RotX", true)).text = Rotation.x;
    cast<LineEdit>(duplicatorWindow.GetChild("RotY", true)).text = Rotation.y;
    cast<LineEdit>(duplicatorWindow.GetChild("RotZ", true)).text = Rotation.z;
    cast<LineEdit>(duplicatorWindow.GetChild("ScaleX", true)).text = Scale.x;
    cast<LineEdit>(duplicatorWindow.GetChild("ScaleY", true)).text = Scale.y;
    cast<LineEdit>(duplicatorWindow.GetChild("ScaleZ", true)).text = Scale.z;
    cast<CheckBox>(duplicatorWindow.GetChild("CheckBox2", true)).checked = isSwitchOrder;
    cast<CheckBox>(duplicatorWindow.GetChild("CheckBox3", true)).checked = isClonesInChild;
}


bool ToggleDuplicatorEditor()
{
    if (duplicatorWindow.visible == false)
        ShowDuplicatorEditor();
    else
        HideDuplicatorEditor();
    return true;
}

void ShowDuplicatorEditor()
{
    RefreshDuplicatorWindow();
    duplicatorWindow.visible = true;
    duplicatorWindow.BringToFront();
}

void HideDuplicatorEditor()
{
    duplicatorWindow.visible = false;
}


void EditDuplicatorCount(StringHash eventType, VariantMap& eventData)
{
    if (inDuplicatorRefresh)
        return;

    LineEdit@ element = eventData["Element"].GetPtr();    

    if (element.name == "Count")
        DuplicatorCount = element.text.ToFloat();
}


void EditDuplicatorPos(StringHash eventType, VariantMap& eventData)
{
    if (inDuplicatorRefresh)
        return;

    LineEdit@ element = eventData["Element"].GetPtr();

    Vector3 v = Position;

    if (element.name == "PosX")
        Position = Vector3(element.text.ToFloat(), v.y, v.z);

    if (element.name == "PosY")
        Position = Vector3(v.x, element.text.ToFloat(), v.z);

    if (element.name == "PosZ")
        Position = Vector3(v.x, v.y, element.text.ToFloat());
}

void EditDuplicatorRot(StringHash eventType, VariantMap& eventData)
{
    if (inDuplicatorRefresh)
        return;

    LineEdit@ element = eventData["Element"].GetPtr();

    Vector3 v = Rotation;

    if (element.name == "RotX")
        Rotation = Vector3(element.text.ToFloat(), v.y, v.z);

    if (element.name == "RotY")
        Rotation = Vector3(v.x, element.text.ToFloat(), v.z);

    if (element.name == "RotZ")
        Rotation = Vector3(v.x, v.y, element.text.ToFloat());
}

void EditDuplicatorScale(StringHash eventType, VariantMap& eventData)
{
    if (inDuplicatorRefresh)
        return;

    LineEdit@ element = eventData["Element"].GetPtr();

    Vector3 v = Scale;

    if (element.name == "ScaleX")
        Scale = Vector3(element.text.ToFloat(), v.y, v.z);

    if (element.name == "ScaleY")
        Scale = Vector3(v.x, element.text.ToFloat(), v.z);

    if (element.name == "ScaleZ")
        Scale = Vector3(v.x, v.y, element.text.ToFloat());
}


void OnButtonPreview(StringHash eventType, VariantMap& eventData)
{    
    ProcessDuplicator();
}

void OnButtonClear(StringHash eventType, VariantMap& eventData)
{
    DuplicatorClearAll();
}

void OnButtonApply(StringHash eventType, VariantMap& eventData)
{
    DuplicatorApplyAll();
}

void OnCheckBox2(StringHash eventType, VariantMap& eventData)
{
    CheckBox@ edit = eventData["Element"].GetPtr();
    if (edit !is null)
        isSwitchOrder = edit.checked;

    ProcessDuplicator();
}

void OnCheckBox3(StringHash eventType, VariantMap& eventData)
{
    CheckBox@ edit = eventData["Element"].GetPtr();
    if (edit !is null)
        isClonesInChild = edit.checked;

    ProcessDuplicator();
}

void DuplicatorClearAll()
{
    Array<Node@> nodes = editorScene.GetChildrenWithTag(tagName,true);
    for(uint i=0; i<nodes.length; i++)
    {
        nodes[i].Remove();
    }
}

void DuplicatorApplyAll()
{
    Array<Node@> nodes = editorScene.GetChildrenWithTag(tagName,true);
    for(uint i=0; i<nodes.length; i++)
    {
        nodes[i].RemoveTag(tagName);
    }
}

void ProcessDuplicator()
{
    DuplicatorClearAll();

    if(isClonesInChild)
        DuplicatorInNode();        
    else
        DuplicatorInScene();
}

void DuplicatorInScene()
{
    if(selectedNodes.length > 0)
    {
        // Apply multiplication only on first selected node
        Node@ currentNode = selectedNodes[0];        
        
        Node@ baseClone = currentNode.Clone();
        baseClone.AddTag(tagName);

        Matrix3x4 mulMat(Position, Quaternion(Rotation), Scale);        
        Matrix3x4 accu = baseClone.transform;

        for(uint i=1; i<DuplicatorCount; i++)
        {
            if(isSwitchOrder)
                accu = mulMat * accu;
            else
                accu = accu * mulMat;

            Node@ cloneNode = baseClone.Clone();            
            cloneNode.SetTransform(accu);           
            
            editorScene.AddChild(cloneNode);         
        }

        baseClone.Remove();        
    }   
}

void DuplicatorInNode()
{
    if(selectedNodes.length > 0)
    {
        // Apply multiplication only on first selected node
        Node@ currentNode = selectedNodes[0];
        
        Node@ baseClone = currentNode.Clone();
        baseClone.AddTag(tagName);

        Matrix3x4 mulMat(Position, Quaternion(Rotation), Scale);        
        Matrix3x4 accu =  mulMat;

        for(uint i=1; i<DuplicatorCount; i++)
        {
            Node@ cloneNode = baseClone.Clone();            
            cloneNode.SetTransform(accu);
            currentNode.AddChild(cloneNode);  

            accu = mulMat * accu;
        }

        baseClone.Remove();
    }  
}