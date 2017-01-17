const bool DEFAULT_SHOW_NAMES_FOR_ALL = false;
const int ORIGIN_STEP_UPDATE = 10;
const int NAMES_SIZE = 11;
const StringHash ORIGIN_NODEID_VAR("OriginNodeID");
const Color ORIGIN_COLOR(1.0f,1.0f,1.0f,1.0f);
const Color ORIGIN_COLOR_SELECTED(0.0f,1.0f,1.0f,1.0f);
const Color ORIGIN_COLOR_DISABLED(1.0f,0.0f,0.0f,1.0f);
const Color ORIGIN_COLOR_TEXT(1.0f,1.0f,1.0f,0.3f);
const Color ORIGIN_COLOR_SELECTED_TEXT(1.0f,1.0f,1.0f,1.0f);
const IntVector2 ORIGIN_ICON_SIZE(14,14);
const IntVector2 ORIGIN_ICON_SIZE_SELECTED(18,18);
const float ORIGINS_VISIBLITY_RANGE = 32.0f;
const IntVector2 ORIGINOFFSETICON(8,8);
const IntVector2 ORIGINOFFSETICONSELECTED(10,8);

bool showNamesForAll = DEFAULT_SHOW_NAMES_FOR_ALL;
bool EditorOriginShow = false;
bool rebuildSceneOrigins = true;
bool isOriginsHovered = false;

int EditorOriginUITimeToUpdate = 0;
int EditorOriginUITimeToSceneNodeRead = 0;
int prevSelectedID;
int selectedNodeInfoState = 0;
int originHoveredIndex = -1;

UIElement@ EditorOriginUIContainer = null;
Text@ selectedNodeName = null;
BorderImage@ selectedNodeOrigin = null;

Array<BorderImage@> selectedNodeOriginChilds;
Array<Text@> selectedNodeNameChilds;
Array<Node@> originsNodes;
Array<BorderImage@> originsIcons;
Array<Text@> originsNames;

void CreateOriginsContainer()
{
    if (editorScene is null) return;
    EditorOriginUIContainer = UIElement();
    EditorOriginUIContainer.position = IntVector2(0,0);
    EditorOriginUIContainer.size = IntVector2(graphics.width,graphics.height);
    EditorOriginUIContainer.priority = -1000;
    EditorOriginUIContainer.focusMode = FM_NOTFOCUSABLE;
    EditorOriginUIContainer.bringToBack = true;
    EditorOriginUIContainer.name ="DebugOriginsContainer";
    EditorOriginUIContainer.temporary = true;
    ui.root.AddChild(EditorOriginUIContainer);
}

void HandleOriginToggled(StringHash eventType, VariantMap& eventData)
{
    UIElement@ origin = eventData["Element"].GetPtr();
    if (origin is null) return;

    if (EditorPaintSelectionShow) return;

    if (IsSceneOrigin(origin))
    {
        int nodeID = origin.vars[ORIGIN_NODEID_VAR].GetInt();
        if (editorScene !is null) 
        {
            bool goBackAndSelectNodeParent = input.qualifierDown[QUAL_CTRL];
            bool multiSelect = input.qualifierDown[QUAL_SHIFT];

            WeakHandle handle = editorScene.GetNode(nodeID);
            if (handle.Get() !is null) {
                Node@ selectedNodeByOrigin = handle.Get();
                if (selectedNodeByOrigin !is null)
                {
                    if (goBackAndSelectNodeParent)
                        SelectNode(selectedNodeByOrigin.parent, false);
                    else
                        SelectNode(selectedNodeByOrigin, multiSelect);
                }
            }
        }
    }
}

void ShowOrigins(bool isVisible = true)
{
    EditorOriginShow = isVisible;

    if (EditorOriginUIContainer is null)
      CreateOriginsContainer();
      
    EditorOriginUIContainer.visible = isVisible;
}

void UpdateOrigins()
{
    // Early out if Origins are disabled
    if (!EditorOriginShow) return; 

    CheckKeyboardQualifers();

    if (editorScene is null || EditorOriginUITimeToUpdate > time.systemTime) return;

    EditorOriginUIContainer = ui.root.GetChild("DebugOriginsContainer");

    // Since editor not clear UIs then do loading new scenes, this creation called once per Editor's starting event
    // for other scenes we use the same container
    if (EditorOriginUIContainer is null)
    {
        CreateOriginsContainer();
    }

    if (EditorOriginUIContainer !is null)
    {
        // Set visibility for all origins
        EditorOriginUIContainer.visible = EditorOriginShow;

        if (viewportMode!=VIEWPORT_SINGLE) 
            EditorOriginUIContainer.visible = false;
        
        // Forced read nodes for some reason:
        if ((originsNodes.length < 1) || rebuildSceneOrigins)
        {
            originsNodes = editorScene.GetChildren(true);
            // If we are hot have free origins icons in arrays, resize x 2
            if (originsIcons.length < originsNodes.length)
            {
                EditorOriginUIContainer.RemoveAllChildren();
                originsIcons.Clear();
                originsNames.Clear();

                originsIcons.Resize(originsNodes.length * 2);
                originsNames.Resize(originsNodes.length * 2);

                if (originsIcons.length > 0)
                {
                    for (int i=0; i < originsIcons.length; i++)
                    {
                        CreateOrigin(i, false);
                    }
                }
            }
            // If this rebuild pass after new scene loading or add/delete node - reset flag to default
            if (rebuildSceneOrigins)
                rebuildSceneOrigins = false;
        }

        if (originsNodes.length > 0)
        {
            // Get selected node for feeding proper arrray's UIElements with slyte colorig and additional info on ALT
            Node@ selectedNode = null;
            if (selectedNodes.length > 0)
            {
                selectedNode = selectedNodes[0];
            }
            else if (selectedComponents.length > 0)
            {
                selectedNode = selectedComponents[0].node;
            }

            // Update existed origins (every 10 ms)
            if (originsNodes.length > 0 )
            {
                for (int i=0; i < originsNodes.length; i++)
                {
                    Vector3 eyeDir = originsNodes[i].worldPosition - cameraNode.worldPosition;
                    float distance = (eyeDir).length;
                    eyeDir.Normalize();
                    Vector3 cameraDir = (cameraNode.worldRotation * Vector3(0.0f, 0.0f, 1.0f)).Normalized();
                    float angleCameraDirVsDirToNode = eyeDir.DotProduct(cameraDir);

                    // if node in range and in camera view (clip back sibe)
                    if (distance < ORIGINS_VISIBLITY_RANGE && angleCameraDirVsDirToNode > 0.7f)
                    {
                        // turn on origin and move
                        MoveOrigin(i, true);

                        if (isThisNodeOneOfSelected(originsNodes[i]))
                        {
                            ShowSelectedNodeOrigin(originsNodes[i], i);
                            originsNames[i].visible = true;
                        }
                        else
                        { 
                            if (showNamesForAll || (isOriginsHovered && originHoveredIndex == i))
                                originsNames[i].text = NodeInfo(originsNodes[i], selectedNodeInfoState);
                        }
                    }
                    else
                    {
                        // turn-off origin
                        VisibilityOrigin(i, false);
                    }
                }

                // Hide non used origins
                for (int j=originsNodes.length; j < originsIcons.length; j++)
                {
                    VisibilityOrigin(j, false);
                }
            }  
        }
    }

    EditorOriginUITimeToUpdate = time.systemTime + ORIGIN_STEP_UPDATE;
}

bool isThisNodeOneOfSelected(Node@ node)
{
    if (selectedNodes.length < 1) return false;

    for (int i = 0; i < selectedNodes.length; i++)
    {
        if (node is selectedNodes[i])
            return true;
    }

    return false;
}

void ShowSelectedNodeOrigin(Node@ node, int index)
{
    if (node !is null)
    {
        // just keep node's text and node's origin icon position in actual view
        Viewport@ vp = activeViewport.viewport;
        Vector2 sp = activeViewport.camera.WorldToScreenPoint(node.worldPosition);
        //originsIcons[index].position = IntVector2(10+int(vp.rect.left + sp.x * vp.rect.right), -5 + int(vp.rect.top + sp.y* vp.rect.bottom));
        originsIcons[index].position = IntVector2(int(vp.rect.left + sp.x * vp.rect.right) - ORIGINOFFSETICONSELECTED.x, int(vp.rect.top + sp.y* vp.rect.bottom) - ORIGINOFFSETICONSELECTED.y);
        originsNames[index].color = ORIGIN_COLOR_SELECTED_TEXT;

        if (originsNodes[index].enabled)
            originsIcons[index].color = ORIGIN_COLOR_SELECTED;
        else
            originsIcons[index].color = ORIGIN_COLOR_DISABLED;
        
        originsIcons[index].SetFixedSize(ORIGIN_ICON_SIZE_SELECTED.x,ORIGIN_ICON_SIZE_SELECTED.y);

        // if selected node chaged, reset some vars
        if (prevSelectedID != node.id)
        {
            prevSelectedID = node.id;
            selectedNodeInfoState = 0;
            originsIcons[index].vars[ORIGIN_NODEID_VAR] = node.id;
        }

        // We always update to keep and feed alt-info with actual info about node components
        Array<Component@> components = node.GetComponents();
        Array<String> componentsShortInfo;
        Array<String> componentsDetailInfo;
        componentsShortInfo.Resize(components.length);
        componentsDetailInfo.Resize(components.length);
        // Add std info node name + tags
        originsNames[index].text = NodeInfo(node, selectedNodeInfoState) + "\n";
    }
}

void CreateOrigin(int index, bool isVisible = false) 
{
    if (originsIcons.length < index) return;

    originsIcons[index] = BorderImage("Icon");
    originsIcons[index].temporary = true;
    originsIcons[index].SetFixedSize(ORIGIN_ICON_SIZE.x,ORIGIN_ICON_SIZE.y);
    originsIcons[index].texture = cache.GetResource("Texture2D", "Textures/Editor/EditorIcons.png");
    originsIcons[index].imageRect = IntRect(0,0,14,14);
    originsIcons[index].priority = -1000;
    originsIcons[index].color = ORIGIN_COLOR;
    originsIcons[index].bringToBack = true;
    originsIcons[index].enabled = true;
    originsIcons[index].selected = true;
    originsIcons[index].visible = isVisible;
    EditorOriginUIContainer.AddChild(originsIcons[index]);

    originsNames[index] = Text();
    originsNames[index].visible = false;
    originsNames[index].SetFont(cache.GetResource("Font", "Fonts/Anonymous Pro.ttf"), NAMES_SIZE);
    originsNames[index].color = ORIGIN_COLOR_TEXT;
    //originsNames[index].textEffect = TE_STROKE;
    originsNames[index].temporary = true;
    originsNames[index].bringToBack = true;
    originsNames[index].priority = -1000;
    originsNames[index].enabled = false;

    EditorOriginUIContainer.AddChild(originsNames[index]);
}

void MoveOrigin(int index, bool isVisible = false)
{
    if (originsIcons.length < index) return;
    if (originsIcons[index] is null) return;
    if (originsNodes[index].temporary)
    {
        originsIcons[index].visible = false;
        originsNames[index].visible = false;
        return;
    }

    Viewport@ vp = activeViewport.viewport;
    Vector2 sp = activeViewport.camera.WorldToScreenPoint(originsNodes[index].worldPosition);

    originsIcons[index].SetFixedSize(ORIGIN_ICON_SIZE.x,ORIGIN_ICON_SIZE.y);

    if (originsNodes[index].enabled)
        originsIcons[index].color = ORIGIN_COLOR;
    else
        originsIcons[index].color = ORIGIN_COLOR_DISABLED;

    originsIcons[index].position = IntVector2(int(vp.rect.left + sp.x * vp.rect.right) - ORIGINOFFSETICON.x, int(vp.rect.top + sp.y* vp.rect.bottom) - ORIGINOFFSETICON.y);
    originsIcons[index].visible = isVisible;
    originsIcons[index].vars[ORIGIN_NODEID_VAR] = originsNodes[index].id;

    originsNames[index].position = IntVector2(10+int(vp.rect.left + sp.x * vp.rect.right), -5 + int(vp.rect.top + sp.y* vp.rect.bottom));

    if (isOriginsHovered && originHoveredIndex == index)
    {
        originsNames[index].visible = true;
        originsNames[index].color = ORIGIN_COLOR_SELECTED_TEXT;
    }
    else
    {
        originsNames[index].visible = showNamesForAll ? isVisible : false;
        originsNames[index].color = ORIGIN_COLOR_TEXT;
    }
}

void VisibilityOrigin(int index, bool isVisible = false)
{
    originsIcons[index].visible = isVisible;
    originsNames[index].visible = isVisible;
}

bool IsSceneOrigin(UIElement@ element)
{
    if (originsIcons.length < 1) return false;

    for (int i=0; i < originsIcons.length; i++)
    {
        if (element is originsIcons[i])
        {
            originHoveredIndex = i;
            return true;
        }
    }

    originHoveredIndex = -1;
    return false;
}

void CheckKeyboardQualifers()
{
    // if pressed alt we inc state for info
    bool showAltInfo = input.keyPress[KEY_ALT];
    if (showAltInfo)
        if (selectedNodeInfoState < 3) selectedNodeInfoState += 1;

    // if pressed ctrl we reset info state
    bool hideAltInfo = input.qualifierDown[QUAL_CTRL];
    if (hideAltInfo)
        selectedNodeInfoState = 0;

    bool showNameForOther = false;

    // In-B.mode Key_Space are busy by quick menu, so we use other key for B.mode
    if (hotKeyMode == HOTKEYS_MODE_BLENDER)
      showNameForOther = (input.keyPress[KEY_TAB] && ui.focusElement is null);
    else
      showNameForOther = (input.keyPress[KEY_SPACE] && ui.focusElement is null);

    if (showNameForOther)
        showNamesForAll =!showNamesForAll;

}

String NodeInfo(Node& node, int st)
{
    String result = "";
    if (node !is editorScene)
    {
        if (node.name.empty)
            result = "Node";
        else
            result = node.name;

        // Add node's tags if wey are exist
        if (st > 0 && node.tags.length > 0)
        {
            result = result + "\n[";
            for (int i=0;i<node.tags.length; i++)
            {
                result = result + " " + node.tags[i];
            }
            result = result + " ] ";
        }
    }
    else
        result = "Scene Origin";

    return result;
}

void HandleSceneLoadedForOrigins()
{
    rebuildSceneOrigins = true;
}

void HandleOriginsHoverBegin(StringHash eventType, VariantMap& eventData)
{
    UIElement@ origin = eventData["Element"].GetPtr();
    if (origin is null)
        return;

    if (IsSceneOrigin(origin))
    {
        VariantMap data;
        data["Element"] = originsIcons[originHoveredIndex];
        data["Id"] = originHoveredIndex;
        data["NodeId"] = originsIcons[originHoveredIndex].vars[ORIGIN_NODEID_VAR].GetInt();
        SendEvent(EDITOR_EVENT_ORIGIN_START_HOVER, data);
        isOriginsHovered = true;
    }
}

void HandleOriginsHoverEnd(StringHash eventType, VariantMap& eventData)
{
    UIElement@ origin = eventData["Element"].GetPtr();
    if (origin is null)
        return;

    if (IsSceneOrigin(origin))
    {
        VariantMap data;
        data["Element"] = originsIcons[originHoveredIndex];
        data["Id"] = originHoveredIndex;
        data["NodeId"] = originsIcons[originHoveredIndex].vars[ORIGIN_NODEID_VAR].GetInt();
        SendEvent(EDITOR_EVENT_ORIGIN_END_HOVER, data);
        isOriginsHovered = false;
    }
}