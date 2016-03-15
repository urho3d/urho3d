// Urho3D editor layer window

enum EditMaskType
{
    EDIT_VIEW_MASK = 0,
    EDIT_LIGHT_MASK,
    EDIT_SHADOW_MASK,
    EDIT_ZONE_MASK
}

StringHash lineEditType = StringHash("LineEdit");
StringHash eventTypeMouseButtonDown = StringHash("MouseButtonDown");
StringHash eventTypeMouseMove = StringHash("MouseMove");

Array<CheckBox@> bits;
Window@ layerWindow;
IntVector2 layerWindowPosition;
Node@ patternMaskNode;
EditMode previousEdit ;
bool toggleBusy = false;
int editMaskType = 0;

void CreateLayerEditor()
{
    if (layerWindow !is null)
        return;

    layerWindow = LoadEditorUI("UI/EditorLayersWindow.xml");
    ui.root.AddChild(layerWindow);
    layerWindow.opacity = uiMaxOpacity;
    
    HideLayerEditor();
    
    bits.Resize(MAX_BITMASK_BITS);
    
    DropDownList@ EditMaskModeList = layerWindow.GetChild("LayerModeEdit", true);
    SubscribeToEvent(EditMaskModeList, "ItemSelected", "HandleLayerModeEdit");
    
    for (int i=0; i < MAX_BITMASK_BITS; i++) 
    {
            bits[i] = layerWindow.GetChild("Bit" + String(i), true);
            bits[i].vars["index"] = i;
            SubscribeToEvent(bits[i], "Toggled", "ToggleBits");
    }
}

bool ShowLayerEditor()
{
    // avoid to show layer window when we type text in LineEdit
    if (ui.focusElement !is null && ui.focusElement.type == lineEditType && lastSelectedNode.Get() is null) 
        return false;
    
    // to avoid when we close dialog with selected other node
    Node@ node = lastSelectedNode.Get(); 
    patternMaskNode = node;
    
    // just change position if already opened
    if (layerWindow.visible == true)
    {
        HideLayerEditor();
        /*
        layerWindowPosition = ui.cursorPosition;
        layerWindow.position = layerWindowPosition;
        layerWindowPosition.x += layerWindow.width / 2;
        layerWindow.BringToFront();
        */
        return true;
    }
    
    // to prevent manipulation until we change mask for one or group nodes
    previousEdit = editMode;
    editMode = EDIT_SELECT;
    
    // get mask type from pattern node
    EstablishSelectedNodeBitMaskToPanel();
    
    layerWindowPosition = ui.cursorPosition;
    layerWindow.position = layerWindowPosition;
    layerWindowPosition.x += layerWindow.width / 2;
    layerWindow.visible = true;
    layerWindow.BringToFront();

    return true;
}

void HideLayerEditor()
{
    layerWindow.visible = false;        
    editMode = previousEdit;
}

void EstablishSelectedNodeBitMaskToPanel() 
{
    if (selectedNodes.length < 1) return;
    Node@ node;
    node = patternMaskNode;
    
    if (node !is null) 
    {
        // find first drawable to get mask
        Array<Component@> components = node.GetComponents();

        Drawable@ firstDrawableInNode;         
        if (components.length > 0 ) 
        {
            firstDrawableInNode = cast<Drawable>(components[0]);
        }
        
        if (firstDrawableInNode !is null)
        {
            int showMask = 0;
            
            switch (editMaskType) 
            {
                case EDIT_VIEW_MASK:
                    showMask = firstDrawableInNode.viewMask;
                    break;
                case EDIT_LIGHT_MASK:
                    showMask = firstDrawableInNode.lightMask;
                    break;
                case EDIT_SHADOW_MASK:
                    showMask = firstDrawableInNode.shadowMask;
                    break;
                case EDIT_ZONE_MASK:
                    showMask = firstDrawableInNode.zoneMask;
                    break;
            }
            
            SetupBitsPanel(showMask);
        }
    }
}

void SetupBitsPanel(int mask) 
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
        for (uint componentIndex = 0; componentIndex < components.length; componentIndex++) 
        {
            Component@ component = components[componentIndex];
            Drawable@ drawable = cast<Drawable>(component);
            if (drawable !is null) 
            { 
                // Save before modification
                CreateDrawableMaskAction action;
                action.Define(drawable, editMaskType);
                group.actions.Push(action);
                
                switch (editMaskType) 
                {
                    case EDIT_VIEW_MASK:
                        drawable.viewMask = mask;
                        break;
                    case EDIT_LIGHT_MASK:
                        drawable.lightMask = mask;
                        break;
                    case EDIT_SHADOW_MASK:
                        drawable.shadowMask = mask;
                        break;
                    case EDIT_ZONE_MASK:
                        drawable.zoneMask = mask;
                        break;
                }   
            }       
        }
    }
}

void EstablishBitMaskToSelectedNodes() 
{
    if (selectedNodes.length < 1) return;
    
    int maskTypeSelected = 0;
            
    // Group for storing undo actions
    EditActionGroup group;
    
    for (uint indexNode = 0; indexNode < selectedNodes.length; indexNode++) 
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
                for (uint i = 0; i < children.length; i++) 
                {
                    ChangeNodeViewMask(children[i], group, mask);
                }
            }   
        }
    }
    
    SaveEditActionGroup(group);
    SetSceneModified();
}

void HandleLayerModeEdit(StringHash eventType, VariantMap& eventData)
{
    DropDownList@ edit = eventData["Element"].GetPtr();
    editMaskType = edit.selection;
    EstablishSelectedNodeBitMaskToPanel();
}

void HandleMaskTypeScroll(StringHash eventType, VariantMap& eventData)
{
    if (!layerWindow.IsInside(ui.cursorPosition, true)) return;
    
    DropDownList@ listView = layerWindow.GetChild("LayerModeEdit", true);
    editMaskType = listView.selection;
    
    int wheel = eventData["Wheel"].GetInt();
    
    if (wheel > 0) 
    {
        if (editMaskType > 0) editMaskType--;
    }
    else if (wheel < 0) 
    {
        if (editMaskType < 3) editMaskType++;
    }
    
    listView.selection = editMaskType;
    EstablishSelectedNodeBitMaskToPanel();
}

void HandleHideLayerEditor(StringHash eventType, VariantMap& eventData)
{
    if (layerWindow.visible == false) return;
    
    // if layer window not in focus and mouse folow away - close layer window
    if ( eventType == eventTypeMouseMove) 
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
    // if user click on scene - close layser window
    else if (eventType == eventTypeMouseButtonDown) 
    {
        if (ui.focusElement is null) 
        {
            HideLayerEditor();
        } 
    }
}

// Every time then we click on bits they are immediately established for all selected nodes for masks
void ToggleBits(StringHash eventType, VariantMap& eventData)
{
    if (toggleBusy) return;
    toggleBusy = true;
    
    CheckBox@ cb = cast<CheckBox>(eventData["Element"].GetPtr());
    int bitIndex = cb.vars["index"].GetInt();
    
    
    if (bitIndex < MAX_BITMASK_BITS) 
    {
        // batch bits invert if pressed ctrl or alt
        if (input.keyDown[KEY_CTRL])
        {
            bool bit = true;
            bits[bitIndex].checked = bit;
            
            for (int i = 0; i < MAX_BITMASK_BITS; i++) 
            {
                if (i != bitIndex) 
                {
                    bits[i].checked = !bit;
                }; 
            }
        }
        else if (input.keyDown[KEY_ALT]) 
        {
            bool bit = false;
            bits[bitIndex].checked = bit;
            
            for (int i = 0; i < MAX_BITMASK_BITS; i++) 
            {
                if (i != bitIndex) 
                {
                    bits[i].checked = !bit;
                }; 
            }
        }
        
        EstablishBitMaskToSelectedNodes();
    }
    
    toggleBusy = false;
}
