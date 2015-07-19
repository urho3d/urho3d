// Urho3D editor layer window

Array<CheckBox@> bits;
Window@ layerWindow;
IntVector2 layerWindowPosition;

void CreateLayerEditor()
{
    if (layerWindow !is null)
        return;

    layerWindow = LoadEditorUI("UI/EditorLayersWindow.xml");
    ui.root.AddChild(layerWindow);
    layerWindow.opacity = uiMaxOpacity;
    
    HideLayerEditor();
    
    bits.Resize(MAX_BITMASK_BITS);
    
    for (int i=0; i < MAX_BITMASK_BITS; i++) 
    {
            bits[i] = layerWindow.GetChild("Bit" + String(i), true);
            bits[i].vars["index"] = i;
            SubscribeToEvent(bits[i], "Toggled", "ToggleBits");
    }
}

bool ShowLayerEditor()
{
    //if (ui.focusElement !is null) return false;
    
    if ( layerWindow.visible == true )
    {
        layerWindowPosition = ui.cursorPosition;
        layerWindow.position = layerWindowPosition;
        layerWindowPosition.x += layerWindow.width / 2;
        layerWindow.BringToFront();
        return true;
    }
    
    EstablishSelectedNodeBitMaskToPanel();
    
    layerWindowPosition = ui.cursorPosition;
    layerWindow.position = layerWindowPosition;
    layerWindowPosition.x += layerWindow.width / 2;
    layerWindow.visible = true;
    layerWindow.BringToFront();
    
    // Subscribe while window are visible
    SubscribeToEvent("MouseMove", "HandleHideLayerEditor");
    SubscribeToEvent("MouseButtonDown", "HandleHideLayerEditor");
    
    return true;
}

void HideLayerEditor()
{
    layerWindow.visible = false;
    // Unsubscribe then window are hides
    UnsubscribeFromEvent(layerWindow, "MouseMove");
    UnsubscribeFromEvent("MouseButtonDown");
}

void EstablishSelectedNodeBitMaskToPanel() 
{
    if (selectedNodes.length < 1) return;
    
    Node@ node;
    
    node = lastSelectedNode;
    
    if (node !is null) 
    {
        StaticModel@ model = node.GetComponent("StaticModel");
        if (model !is null) 
        {
            SetupBitsPanel(model.viewMask);
        }
    }
}

void SetupBitsPanel( int mask) 
{
    for (int i = 0; i < 8; i++) 
    {
        if ((1 << i) & mask != 0) 
        {
            bits[i].checked = true;
        }
        else
        {
            bits[i].checked = false;
        }
    }
}

void ChangeNodeViewMask(Node@ node, EditActionGroup@ group, int mask) 
{
    Array<Component@> components = node.GetComponents();
    if (components.length > 0) 
    {
        for (int componentIndex = 0; componentIndex < components.length; componentIndex++) 
        {
            Component@ component = components[componentIndex];
            Drawable@ drawable = cast<Drawable>(component);
            if (drawable !is null) 
            {
                    
                    // Save before modification
                    CreateDrawableMaskAction action;
                    action.Define(drawable);
                    group.actions.Push(action);
    
                    drawable.viewMask = mask;    
            }       
        }
    }
}

void EstablishBitMaskToSelectedNodes() 
{
    if (selectedNodes.length < 1) return;
    
    // Group for storing undo actions
    EditActionGroup group;
    
    for (int indexNode = 0; indexNode < selectedNodes.length; indexNode++) 
    {
        Node@ node = selectedNodes[indexNode];
        if (node !is null) 
        {
            int mask = 0;
            for (int i = 0; i < MAX_BITMASK_BITS; i++) 
            {
                mask = mask | (bits[i].checked ? 1 << i : 0);
            }
            
            if (mask == MAX_BITMASK_VALUE)
                mask = -1;
            
            
            ChangeNodeViewMask(node, group, mask);
            Array<Node@> children = node.GetChildren(true);
            if (children.length > 0) 
            {
                for (int i =0; i < children.length; i++) 
                {
                    ChangeNodeViewMask(children[i], group, mask);
                }
            }   
        }
    }
    
    SaveEditActionGroup(group);
    SetSceneModified();
}

void HandleHideLayerEditor(StringHash eventType, VariantMap& eventData)
{
    if ( eventType == StringHash("MouseMove") && ui.focusElement is null) 
    {
        IntVector2 mousePos;
        mousePos.x = eventData["X"].GetInt();
        mousePos.y = eventData["Y"].GetInt();
        
        Vector2 a = Vector2(layerWindowPosition.x, layerWindowPosition.y);
        Vector2 b = Vector2(mousePos.x, mousePos.y);
        Vector2 dir = a - b;
        float distance = dir.length;
        
        if (distance > layerWindow.width)
            HideLayerEditor();
    } 
    else if ( eventType == StringHash("MouseButtonDown") ) 
    {
        if (ui.focusElement is null) 
        {
            HideLayerEditor();
        } 
    }
}

void ToggleBits(StringHash eventType, VariantMap& eventData)
{
    CheckBox@ cb = cast<CheckBox>(eventData["Element"].GetPtr());
    int bitIndex = cb.vars["index"].GetInt();
  
    if (bitIndex < MAX_BITMASK_BITS) 
    {
        EstablishBitMaskToSelectedNodes();
    }
    

}