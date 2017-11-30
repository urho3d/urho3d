// Urho3D Multiply Editor

Window@ multiplyWindow;
bool inMultiplyRefresh = false;

Vector3 Position;
Vector3 Rotation;
Vector3 Scale;
Vector3 PrePosition;
Vector3 PreRotation;
Vector3 PreScale;
uint MultiplyCount;

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

    SubscribeToEvent(multiplyWindow.GetChild("PrePosX", true), "TextChanged", "EditMultiplyPrePos");
    SubscribeToEvent(multiplyWindow.GetChild("PrePosY", true), "TextChanged", "EditMultiplyPrePos");
    SubscribeToEvent(multiplyWindow.GetChild("PrePosZ", true), "TextChanged", "EditMultiplyPrePos");

    SubscribeToEvent(multiplyWindow.GetChild("PreRotX", true), "TextChanged", "EditMultiplyPreRot");
    SubscribeToEvent(multiplyWindow.GetChild("PreRotY", true), "TextChanged", "EditMultiplyPreRot");
    SubscribeToEvent(multiplyWindow.GetChild("PreRotZ", true), "TextChanged", "EditMultiplyPreRot");

    SubscribeToEvent(multiplyWindow.GetChild("PreScaleX", true), "TextChanged", "EditMultiplyPreScale");
    SubscribeToEvent(multiplyWindow.GetChild("PreScaleY", true), "TextChanged", "EditMultiplyPreScale");
    SubscribeToEvent(multiplyWindow.GetChild("PreScaleZ", true), "TextChanged", "EditMultiplyPreScale");

    SubscribeToEvent(multiplyWindow.GetChild("ButtonPreview", true), "Released", "OnButtonPreview");
    SubscribeToEvent(multiplyWindow.GetChild("ButtonClear", true), "Released", "OnButtonClear");
    SubscribeToEvent(multiplyWindow.GetChild("ButtonApply", true), "Released", "OnButtonApply");
}

void InitMultiplyWindow()
{
    Position = Vector3(0,0,0);
    Rotation = Vector3(0,0,0);
    Scale = Vector3(1,1,1);

    PrePosition = Vector3(0,0,0);
    PreRotation = Vector3(0,0,0);
    PreScale = Vector3(1,1,1);

    MultiplyCount = 1;

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

    CreateDragSlider(cast<LineEdit>(multiplyWindow.GetChild("PrePosX", true)));
    CreateDragSlider(cast<LineEdit>(multiplyWindow.GetChild("PrePosY", true)));
    CreateDragSlider(cast<LineEdit>(multiplyWindow.GetChild("PrePosZ", true)));

    CreateDragSlider(cast<LineEdit>(multiplyWindow.GetChild("PreRotX", true)));
    CreateDragSlider(cast<LineEdit>(multiplyWindow.GetChild("PreRotY", true)));
    CreateDragSlider(cast<LineEdit>(multiplyWindow.GetChild("PreRotZ", true)));

    CreateDragSlider(cast<LineEdit>(multiplyWindow.GetChild("PreScaleX", true)));
    CreateDragSlider(cast<LineEdit>(multiplyWindow.GetChild("PreScaleY", true)));
    CreateDragSlider(cast<LineEdit>(multiplyWindow.GetChild("PreScaleZ", true)));
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

    cast<LineEdit>(multiplyWindow.GetChild("PrePosX", true)).text = PrePosition.x;
    cast<LineEdit>(multiplyWindow.GetChild("PrePosY", true)).text = PrePosition.y;
    cast<LineEdit>(multiplyWindow.GetChild("PrePosZ", true)).text = PrePosition.z;

    cast<LineEdit>(multiplyWindow.GetChild("PreRotX", true)).text = PreRotation.x;
    cast<LineEdit>(multiplyWindow.GetChild("PreRotY", true)).text = PreRotation.y;
    cast<LineEdit>(multiplyWindow.GetChild("PreRotZ", true)).text = PreRotation.z;

    cast<LineEdit>(multiplyWindow.GetChild("PreScaleX", true)).text = PreScale.x;
    cast<LineEdit>(multiplyWindow.GetChild("PreScaleY", true)).text = PreScale.y;
    cast<LineEdit>(multiplyWindow.GetChild("PreScaleZ", true)).text = PreScale.z;
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

void EditMultiplyPrePos(StringHash eventType, VariantMap& eventData)
{
    if (inMultiplyRefresh)
        return;

    LineEdit@ element = eventData["Element"].GetPtr();

    Vector3 v = PrePosition;

    if (element.name == "PrePosX")
        PrePosition = Vector3(element.text.ToFloat(), v.y, v.z);

    if (element.name == "PrePosY")
        PrePosition = Vector3(v.x, element.text.ToFloat(), v.z);

    if (element.name == "PrePosZ")
        PrePosition = Vector3(v.x, v.y, element.text.ToFloat());
}

void EditMultiplyPreRot(StringHash eventType, VariantMap& eventData)
{
    if (inMultiplyRefresh)
        return;

    LineEdit@ element = eventData["Element"].GetPtr();

    Vector3 v = PreRotation;

    if (element.name == "PreRotX")
        PreRotation = Vector3(element.text.ToFloat(), v.y, v.z);

    if (element.name == "PreRotY")
        PreRotation = Vector3(v.x, element.text.ToFloat(), v.z);

    if (element.name == "PreRotZ")
        PreRotation = Vector3(v.x, v.y, element.text.ToFloat());
}

void EditMultiplyPreScale(StringHash eventType, VariantMap& eventData)
{
    if (inMultiplyRefresh)
        return;

    LineEdit@ element = eventData["Element"].GetPtr();

    Vector3 v = PreScale;

    if (element.name == "PreScaleX")
        PreScale = Vector3(element.text.ToFloat(), v.y, v.z);

    if (element.name == "PreScaleY")
        PreScale = Vector3(v.x, element.text.ToFloat(), v.z);

    if (element.name == "PreScaleZ")
        PreScale = Vector3(v.x, v.y, element.text.ToFloat());
}


void OnButtonPreview(StringHash eventType, VariantMap& eventData)
{
    setMultiply();
}

void OnButtonClear(StringHash eventType, VariantMap& eventData)
{
    if(selectedNodes.length > 0)
    {
        Node@ currentNode = selectedNodes[0];

        Array<Node@> nodes = currentNode.GetChildrenWithTag("EditMul");
        for(uint i=0; i<nodes.length; i++)
        {
            nodes[i].Remove();
        }
    }
}

void OnButtonApply(StringHash eventType, VariantMap& eventData)
{
    if(selectedNodes.length > 0)
    {
        Node@ currentNode = selectedNodes[0];
        
        Array<Node@> nodes = currentNode.GetChildrenWithTag("EditMul");
        for(uint i=0; i<nodes.length; i++)
        {
            nodes[i].RemoveTag("EditMul");
        }
    }
}


void setMultiply()
{
    if(selectedNodes.length > 0)
    {
        // get only first selected node
        Node@ currentNode = selectedNodes[0];         

        // clear cloned nodes with tags
        Array<Node@> nodes = currentNode.GetChildrenWithTag("EditMul");
        for(uint i=0; i<nodes.length; i++)
        {
            nodes[i].Remove();
        }
        
        Node@ baseClone = currentNode.Clone();

        Matrix3x4 mulMat(Position, Quaternion(Rotation), Scale);
        Matrix3x4 preMat(PrePosition, Quaternion(PreRotation), PreScale);
        
        Matrix3x4 accu = mulMat;
        Matrix3x4 mat0;

        for(uint i=1; i<MultiplyCount; i++)
        {
            mat0 = preMat * accu;
            accu = accu * mulMat ;

            Node@ cloneNode = baseClone.Clone();
            cloneNode.AddTag("EditMul");
            cloneNode.SetTransform(mat0);

            currentNode.AddChild(cloneNode);
        }

        baseClone.Remove();
    }   
}