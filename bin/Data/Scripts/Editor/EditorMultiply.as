// Urho3D Multiply Editor

Window@ multiplyWindow;
bool inMultiplyRefresh = false;

Vector3 Position;
Vector3 Rotation;
Vector3 Scale;
uint MultiplyCount;
String tagName = "TagEditMultiplicator";
bool isSwitchOrder = false;
bool isClonesInChild = false;

void CreateMultiplyEditor()
{
    if (multiplyWindow !is null)
        return;
        
    multiplyWindow = ui.LoadLayout(cache.GetResource("XMLFile", "UI/EditorMultiply.xml"));
    ui.root.AddChild(multiplyWindow);
    multiplyWindow.opacity = uiMaxOpacity;

    InitMultiplyWindow();
    RefreshMultiplyWindow();

    int height = Min(ui.root.height - 60, 750);    
    multiplyWindow.SetSize(400, 0);
    CenterDialog(multiplyWindow);

    HideMultiplyEditor();

    SubscribeToEvent(multiplyWindow.GetChild("CloseButton", true), "Released", "HideMultiplyEditor");
    SubscribeToEvent(multiplyWindow.GetChild("Count", true), "TextChanged", "EditMultiplyCount");
    SubscribeToEvent(multiplyWindow.GetChild("PosX", true), "TextChanged", "EditMultiplyPos");
    SubscribeToEvent(multiplyWindow.GetChild("PosY", true), "TextChanged", "EditMultiplyPos");
    SubscribeToEvent(multiplyWindow.GetChild("PosZ", true), "TextChanged", "EditMultiplyPos");
    SubscribeToEvent(multiplyWindow.GetChild("RotX", true), "TextChanged", "EditMultiplyRot");
    SubscribeToEvent(multiplyWindow.GetChild("RotY", true), "TextChanged", "EditMultiplyRot");
    SubscribeToEvent(multiplyWindow.GetChild("RotZ", true), "TextChanged", "EditMultiplyRot");
    SubscribeToEvent(multiplyWindow.GetChild("ScaleX", true), "TextChanged", "EditMultiplyScale");
    SubscribeToEvent(multiplyWindow.GetChild("ScaleY", true), "TextChanged", "EditMultiplyScale");
    SubscribeToEvent(multiplyWindow.GetChild("ScaleZ", true), "TextChanged", "EditMultiplyScale");
    SubscribeToEvent(multiplyWindow.GetChild("CheckBox2", true), "Toggled", "OnCheckBox2");
    SubscribeToEvent(multiplyWindow.GetChild("CheckBox3", true), "Toggled", "OnCheckBox3");
    SubscribeToEvent(multiplyWindow.GetChild("ButtonPreview", true), "Released", "OnButtonPreview");
    SubscribeToEvent(multiplyWindow.GetChild("ButtonClear", true), "Released", "OnButtonClear");
    SubscribeToEvent(multiplyWindow.GetChild("ButtonApply", true), "Released", "OnButtonApply");
}

void InitMultiplyWindow()
{
    MultiplyCount = 1;

    Position = Vector3(0,0,0);
    Rotation = Vector3(0,0,0);
    Scale = Vector3(1,1,1);

    CreateDragSlider(cast<LineEdit>(multiplyWindow.GetChild("Count", true)));
    CreateDragSlider(cast<LineEdit>(multiplyWindow.GetChild("PosX", true)));
    CreateDragSlider(cast<LineEdit>(multiplyWindow.GetChild("PosY", true)));
    CreateDragSlider(cast<LineEdit>(multiplyWindow.GetChild("PosZ", true)));
    CreateDragSlider(cast<LineEdit>(multiplyWindow.GetChild("RotX", true)));
    CreateDragSlider(cast<LineEdit>(multiplyWindow.GetChild("RotY", true)));
    CreateDragSlider(cast<LineEdit>(multiplyWindow.GetChild("RotZ", true)));
    CreateDragSlider(cast<LineEdit>(multiplyWindow.GetChild("ScaleX", true)));
    CreateDragSlider(cast<LineEdit>(multiplyWindow.GetChild("ScaleY", true)));
    CreateDragSlider(cast<LineEdit>(multiplyWindow.GetChild("ScaleZ", true)));    
}

void RefreshMultiplyWindow()
{
    inMultiplyRefresh = true;

    RefreshMultiplyWindowAttributes();

    inMultiplyRefresh = false;
}


void RefreshMultiplyWindowAttributes()
{
    cast<LineEdit>(multiplyWindow.GetChild("Count", true)).text = MultiplyCount;
    cast<LineEdit>(multiplyWindow.GetChild("PosX", true)).text = Position.x;
    cast<LineEdit>(multiplyWindow.GetChild("PosY", true)).text = Position.y;
    cast<LineEdit>(multiplyWindow.GetChild("PosZ", true)).text = Position.z;
    cast<LineEdit>(multiplyWindow.GetChild("RotX", true)).text = Rotation.x;
    cast<LineEdit>(multiplyWindow.GetChild("RotY", true)).text = Rotation.y;
    cast<LineEdit>(multiplyWindow.GetChild("RotZ", true)).text = Rotation.z;
    cast<LineEdit>(multiplyWindow.GetChild("ScaleX", true)).text = Scale.x;
    cast<LineEdit>(multiplyWindow.GetChild("ScaleY", true)).text = Scale.y;
    cast<LineEdit>(multiplyWindow.GetChild("ScaleZ", true)).text = Scale.z;
    cast<CheckBox>(multiplyWindow.GetChild("CheckBox2", true)).checked = isSwitchOrder;
    cast<CheckBox>(multiplyWindow.GetChild("CheckBox3", true)).checked = isClonesInChild;
}


bool ToggleMultiplyEditor()
{
    if (multiplyWindow.visible == false)
        ShowMultiplyEditor();
    else
        HideMultiplyEditor();
    return true;
}

void ShowMultiplyEditor()
{
    RefreshMultiplyWindow();
    multiplyWindow.visible = true;
    multiplyWindow.BringToFront();
}

void HideMultiplyEditor()
{
    multiplyWindow.visible = false;
}


void EditMultiplyCount(StringHash eventType, VariantMap& eventData)
{
    if (inMultiplyRefresh)
        return;

    LineEdit@ element = eventData["Element"].GetPtr();    

    if (element.name == "Count")
        MultiplyCount = element.text.ToFloat();
}


void EditMultiplyPos(StringHash eventType, VariantMap& eventData)
{
    if (inMultiplyRefresh)
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

void EditMultiplyRot(StringHash eventType, VariantMap& eventData)
{
    if (inMultiplyRefresh)
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

void EditMultiplyScale(StringHash eventType, VariantMap& eventData)
{
    if (inMultiplyRefresh)
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
    ProcessMultiply();
}

void OnButtonClear(StringHash eventType, VariantMap& eventData)
{
    MultiplyClearAll();
}

void OnButtonApply(StringHash eventType, VariantMap& eventData)
{
    MultiplyApplyAll();
}

void OnCheckBox2(StringHash eventType, VariantMap& eventData)
{
    CheckBox@ edit = eventData["Element"].GetPtr();
    if (edit !is null)
        isSwitchOrder = edit.checked;

    ProcessMultiply();
}

void OnCheckBox3(StringHash eventType, VariantMap& eventData)
{
    CheckBox@ edit = eventData["Element"].GetPtr();
    if (edit !is null)
        isClonesInChild = edit.checked;

    ProcessMultiply();
}

void MultiplyClearAll()
{
    Array<Node@> nodes = editorScene.GetChildrenWithTag(tagName,true);
    for(uint i=0; i<nodes.length; i++)
    {
        nodes[i].Remove();
    }
}

void MultiplyApplyAll()
{
    Array<Node@> nodes = editorScene.GetChildrenWithTag(tagName,true);
    for(uint i=0; i<nodes.length; i++)
    {
        nodes[i].RemoveTag(tagName);
    }
}

void ProcessMultiply()
{
    MultiplyClearAll();

    if(isClonesInChild)
        MultiplyInNode();        
    else
        MultiplyInScene();
}

void MultiplyInScene()
{
    if(selectedNodes.length > 0)
    {
        // Apply multiplication only on first selected node
        Node@ currentNode = selectedNodes[0];
        
        Node@ baseClone = currentNode.Clone();
        baseClone.AddTag(tagName);

        Matrix3x4 mulMat(Position, Quaternion(Rotation), Scale);        
        Matrix3x4 accu = baseClone.transform;

        for(uint i=1; i<MultiplyCount; i++)
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

void MultiplyInNode()
{
    if(selectedNodes.length > 0)
    {
        // Apply multiplication only on first selected node
        Node@ currentNode = selectedNodes[0];
        
        Node@ baseClone = currentNode.Clone();
        baseClone.AddTag(tagName);

        Matrix3x4 mulMat(Position, Quaternion(Rotation), Scale);        
        Matrix3x4 accu =  mulMat;

        for(uint i=1; i<MultiplyCount; i++)
        {
            Node@ cloneNode = baseClone.Clone();            
            cloneNode.SetTransform(accu);
            currentNode.AddChild(cloneNode);  

            accu = mulMat * accu;
        }

        baseClone.Remove();
    }  
}