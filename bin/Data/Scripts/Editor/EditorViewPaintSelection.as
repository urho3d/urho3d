const int PAINT_STEP_UPDATE = 16;
const int PAINT_SELECTION_KEY = KEY_C;

bool EditorPaintSelectionShow = false;
int EditorPaintSelectionUITimeToUpdate = 0;

UIElement@ EditorPaintSelectionUIContainer = null;
BorderImage@ paintSelectionImage = null;

IntVector2 paintSelectionBrushDefaultSize(96,96);
IntVector2 paintSelectionBrushCurrentSize = paintSelectionBrushDefaultSize;
IntVector2 paintSelectionBrushMinSize(64,64);
IntVector2 paintSelectionBrushMaxSize(512,512);
IntVector2 paintSelectionBrushStepSizeChange(16,16);

void CreatePaintSelectionContainer()
{
    if (editorScene is null) return;
    EditorPaintSelectionUIContainer = UIElement();
    EditorPaintSelectionUIContainer.position = IntVector2(0,0);
    EditorPaintSelectionUIContainer.size = IntVector2(graphics.width,graphics.height);
    EditorPaintSelectionUIContainer.priority = -5;
    EditorPaintSelectionUIContainer.focusMode = FM_NOTFOCUSABLE;
    EditorPaintSelectionUIContainer.bringToBack = true;
    EditorPaintSelectionUIContainer.name ="DebugPaintSelectionContainer";
    EditorPaintSelectionUIContainer.temporary = true;
    ui.root.AddChild(EditorPaintSelectionUIContainer);
}

void CreatePaintSelectionTool()
{
    paintSelectionImage = BorderImage("Icon");
    paintSelectionImage.temporary = true;
    paintSelectionImage.SetFixedSize(paintSelectionBrushDefaultSize.x,paintSelectionBrushDefaultSize.y);
    paintSelectionImage.texture = cache.GetResource("Texture2D", "Textures/Editor/SelectionCircle.png");
    paintSelectionImage.imageRect = IntRect(0,0,512,512);
    paintSelectionImage.priority = -5;
    paintSelectionImage.color = Color(1,1,1);
    paintSelectionImage.bringToBack = true;
    paintSelectionImage.enabled = false;
    paintSelectionImage.selected = false;
    paintSelectionImage.visible = true;
    EditorPaintSelectionUIContainer.AddChild(paintSelectionImage);
}

void UpdatePaintSelection()
{
    PaintSelectionCheckKeyboard();

    // Early out if disabled
    if (!EditorPaintSelectionShow) return;

    if (editorScene is null || EditorPaintSelectionUITimeToUpdate > time.systemTime) return;

    EditorPaintSelectionUIContainer = ui.root.GetChild("DebugPaintSelectionContainer");

    if (EditorPaintSelectionUIContainer is null)
    {
        CreatePaintSelectionContainer();
        CreatePaintSelectionTool();
    }

    if (EditorPaintSelectionUIContainer !is null)
    {
        // Set visibility for all origins
        EditorPaintSelectionUIContainer.visible = EditorPaintSelectionShow;

        if (viewportMode!=VIEWPORT_SINGLE) 
            EditorPaintSelectionUIContainer.visible = false;

        if (EditorPaintSelectionShow)
        {
            IntVector2 mp = input.mousePosition;
            paintSelectionImage.position = IntVector2(mp.x - (paintSelectionBrushCurrentSize.x * 0.5f), mp.y - (paintSelectionBrushCurrentSize.y * 0.5f));
        }
    }

    EditorPaintSelectionUITimeToUpdate = time.systemTime + PAINT_STEP_UPDATE;
}

void PaintSelectionCheckKeyboard()
{
    bool key = input.keyPress[PAINT_SELECTION_KEY];

    if (key && ui.focusElement is null)
    {
        EditorPaintSelectionShow = !EditorPaintSelectionShow;
        if (EditorPaintSelectionUIContainer !is null)
            EditorPaintSelectionUIContainer.visible = EditorPaintSelectionShow;

        if (EditorPaintSelectionShow)
        {
            // When we start paint selection we change editmode to select
            editMode = EDIT_SELECT;
            //selectedNodes.Clear();
            // and also we show origins for proper origins update
            ShowOrigins(true);
            toolBarDirty = true;
        }
    }
    else if (EditorPaintSelectionShow && ui.focusElement is null)
    {
        if (editMode != EDIT_SELECT)
        {
            EditorPaintSelectionShow = false;
            EditorPaintSelectionUIContainer.visible = false;
        }
    }

    if (input.mouseButtonDown[MOUSEB_RIGHT])
    {
        EditorPaintSelectionShow = false;
        if (EditorPaintSelectionUIContainer !is null)
            EditorPaintSelectionUIContainer.visible = false;
    }
}

void SelectOriginsByPaintSelection(IntVector2 curPos, float brushRadius, bool isOperationAddToSelection = true)
{
    if (!EditorPaintSelectionShow || EditorPaintSelectionUIContainer is null) return;

    for (int i=0; i < originsNodes.length; i++)
    {
        Vector3 v1(originsIcons[i].position.x, originsIcons[i].position.y, 0);
        Vector3 v2(curPos.x - ORIGINOFFSETICON.x, curPos.y - ORIGINOFFSETICON.y, 0);

        float distance = (v1 - v2).length;
        bool isThisOriginInCircle = distance < brushRadius ? true : false;
        int nodeID = originsIcons[i].vars[ORIGIN_NODEID_VAR].GetInt();

        if (isThisOriginInCircle)
        {
            WeakHandle handle = editorScene.GetNode(nodeID);
            if (handle.Get() !is null)
            {
                Node@ node = handle.Get();
                if (isOperationAddToSelection)
                {
                    if (node !is null && isThisNodeOneOfSelected(node) == false)
                        SelectNode(node, true);
                }
                else // Deselect origins operation
                {
                    if (node !is null && isThisNodeOneOfSelected(node) == true)
                        DeselectNode(node);
                }
            }
        }
    }
}

void HandlePaintSelectionMouseMove(StringHash eventType, VariantMap& eventData)
{
    if (!EditorPaintSelectionShow || EditorPaintSelectionUIContainer is null) return;

    int x = eventData["X"].GetInt();
    int y = eventData["Y"].GetInt();
    float r = (paintSelectionBrushCurrentSize.x * 0.5);

    IntVector2 mousePos(x,y);

    // Select by mouse
    if (input.mouseButtonDown[MOUSEB_LEFT] && input.qualifierDown[QUAL_CTRL] != true)
    {
        SelectOriginsByPaintSelection(mousePos, r, true);
    }
    // Deselect by mouse
    else if (input.mouseButtonDown[MOUSEB_LEFT] && input.qualifierDown[QUAL_CTRL] == true)
    {
        SelectOriginsByPaintSelection(mousePos, r, false);
    }
}

void HandlePaintSelectionWheel(StringHash eventType, VariantMap& eventData)
{
    if (!EditorPaintSelectionShow || EditorPaintSelectionUIContainer is null) return;

    int wheelValue = eventData["Wheel"].GetInt();

    if (wheelValue != 0)
    {
        if (wheelValue > 0)
        {
            paintSelectionBrushCurrentSize = paintSelectionBrushCurrentSize - paintSelectionBrushStepSizeChange;
            paintSelectionBrushCurrentSize = IntVector2(Max(paintSelectionBrushCurrentSize.x, paintSelectionBrushMinSize.x), Max(paintSelectionBrushCurrentSize.y, paintSelectionBrushMinSize.y));
        }
        else if (wheelValue < 0)
        {
            paintSelectionBrushCurrentSize = paintSelectionBrushCurrentSize + paintSelectionBrushStepSizeChange;
            paintSelectionBrushCurrentSize = IntVector2(Min(paintSelectionBrushCurrentSize.x, paintSelectionBrushMaxSize.x), Min(paintSelectionBrushCurrentSize.y, paintSelectionBrushMaxSize.y));
        }
        paintSelectionImage.SetFixedSize(paintSelectionBrushCurrentSize.x, paintSelectionBrushCurrentSize.y);
    }
}
