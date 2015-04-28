
bool subscribedToEditorToolBar = false;
bool toolBarDirty = true;
UIElement@ toolBar;

const StringHash VIEW_MODE("VIEW_MODE");

void CreateToolBar()
{
    toolBar = BorderImage("ToolBar");
    toolBar.style = "EditorToolBar";
    toolBar.SetLayout(LM_HORIZONTAL);
    toolBar.layoutSpacing = 4;
    toolBar.layoutBorder = IntRect(8, 4, 4, 8);
    toolBar.opacity = uiMaxOpacity;
    toolBar.SetFixedSize(graphics.width, 42);
    toolBar.SetPosition(0, uiMenuBar.height);
    ui.root.AddChild(toolBar);

    UIElement@ runUpdateGroup = CreateGroup("RunUpdateGroup", LM_HORIZONTAL);
    runUpdateGroup.AddChild(CreateToolBarToggle("RunUpdatePlay"));
    runUpdateGroup.AddChild(CreateToolBarToggle("RunUpdatePause"));
    runUpdateGroup.AddChild(CreateToolBarToggle("RevertOnPause"));
    FinalizeGroupHorizontal(runUpdateGroup, "ToolBarToggle");
    toolBar.AddChild(runUpdateGroup);

    toolBar.AddChild(CreateToolBarSpacer(4));
    UIElement@ editModeGroup = CreateGroup("EditModeGroup", LM_HORIZONTAL);
    editModeGroup.AddChild(CreateToolBarToggle("EditMove"));
    editModeGroup.AddChild(CreateToolBarToggle("EditRotate"));
    editModeGroup.AddChild(CreateToolBarToggle("EditScale"));
    editModeGroup.AddChild(CreateToolBarToggle("EditSelect"));
    FinalizeGroupHorizontal(editModeGroup, "ToolBarToggle");
    toolBar.AddChild(editModeGroup);

    UIElement@ axisModeGroup = CreateGroup("AxisModeGroup", LM_HORIZONTAL);
    axisModeGroup.AddChild(CreateToolBarToggle("AxisWorld"));
    axisModeGroup.AddChild(CreateToolBarToggle("AxisLocal"));
    FinalizeGroupHorizontal(axisModeGroup, "ToolBarToggle");
    toolBar.AddChild(axisModeGroup);

    toolBar.AddChild(CreateToolBarSpacer(4));
    toolBar.AddChild(CreateToolBarToggle("MoveSnap"));
    toolBar.AddChild(CreateToolBarToggle("RotateSnap"));
    toolBar.AddChild(CreateToolBarToggle("ScaleSnap"));

    UIElement@ snapScaleModeGroup = CreateGroup("SnapScaleModeGroup", LM_HORIZONTAL);
    snapScaleModeGroup.AddChild(CreateToolBarToggle("SnapScaleHalf"));
    snapScaleModeGroup.AddChild(CreateToolBarToggle("SnapScaleQuarter"));
    FinalizeGroupHorizontal(snapScaleModeGroup, "ToolBarToggle");
    toolBar.AddChild(snapScaleModeGroup);

    toolBar.AddChild(CreateToolBarSpacer(4));
    UIElement@ pickModeGroup = CreateGroup("PickModeGroup", LM_HORIZONTAL);
    pickModeGroup.AddChild(CreateToolBarToggle("PickGeometries"));
    pickModeGroup.AddChild(CreateToolBarToggle("PickLights"));
    pickModeGroup.AddChild(CreateToolBarToggle("PickZones"));
    pickModeGroup.AddChild(CreateToolBarToggle("PickRigidBodies"));
    pickModeGroup.AddChild(CreateToolBarToggle("PickUIElements"));
    FinalizeGroupHorizontal(pickModeGroup, "ToolBarToggle");
    toolBar.AddChild(pickModeGroup);

    toolBar.AddChild(CreateToolBarSpacer(4));
    UIElement@ fillModeGroup = CreateGroup("FillModeGroup", LM_HORIZONTAL);
    fillModeGroup.AddChild(CreateToolBarToggle("FillPoint"));
    fillModeGroup.AddChild(CreateToolBarToggle("FillWireFrame"));
    fillModeGroup.AddChild(CreateToolBarToggle("FillSolid"));
    FinalizeGroupHorizontal(fillModeGroup, "ToolBarToggle");
    toolBar.AddChild(fillModeGroup);

    toolBar.AddChild(CreateToolBarSpacer(4));
    DropDownList@ viewportModeList = DropDownList();
    viewportModeList.style = AUTO_STYLE;
    viewportModeList.SetMaxSize(100, 18);
    viewportModeList.SetAlignment(HA_LEFT, VA_CENTER);
    toolBar.AddChild(viewportModeList);
    viewportModeList.AddItem(CreateViewPortModeText("Single", VIEWPORT_SINGLE));
    viewportModeList.AddItem(CreateViewPortModeText("Vertical Split", VIEWPORT_LEFT|VIEWPORT_RIGHT));
    viewportModeList.AddItem(CreateViewPortModeText("Horizontal Split", VIEWPORT_TOP|VIEWPORT_BOTTOM));
    viewportModeList.AddItem(CreateViewPortModeText("Quad", VIEWPORT_TOP_LEFT|VIEWPORT_TOP_RIGHT|VIEWPORT_BOTTOM_LEFT|VIEWPORT_BOTTOM_RIGHT));
    viewportModeList.AddItem(CreateViewPortModeText("1 Top / 2 Bottom", VIEWPORT_TOP|VIEWPORT_BOTTOM_LEFT|VIEWPORT_BOTTOM_RIGHT));
    viewportModeList.AddItem(CreateViewPortModeText("2 Top / 1 Bottom", VIEWPORT_TOP_LEFT|VIEWPORT_TOP_RIGHT|VIEWPORT_BOTTOM));
    viewportModeList.AddItem(CreateViewPortModeText("1 Left / 2 Right", VIEWPORT_LEFT|VIEWPORT_TOP_RIGHT|VIEWPORT_BOTTOM_RIGHT));
    viewportModeList.AddItem(CreateViewPortModeText("2 Left / 1 Right", VIEWPORT_TOP_LEFT|VIEWPORT_BOTTOM_LEFT|VIEWPORT_RIGHT));
    for (uint i = 0; i < viewportModeList.numItems; ++i)
    {
        if (viewportModeList.items[i].vars[VIEW_MODE].GetUInt() == viewportMode)
        {
            viewportModeList.selection = i;
            break;
        }
    }
    SubscribeToEvent(viewportModeList, "ItemSelected", "ToolBarSetViewportMode");
}

Button@ CreateToolBarButton(const String&in title)
{
    Button@ button = Button(title);
    button.defaultStyle = uiStyle;
    button.style = "ToolBarButton";

    CreateToolBarIcon(button);
    CreateToolTip(button, title, IntVector2(button.width + 10, button.height - 10));

    return button;
}

CheckBox@ CreateToolBarToggle(const String&in title)
{
    CheckBox@ toggle = CheckBox(title);
    toggle.defaultStyle = uiStyle;
    toggle.style = "ToolBarToggle";

    CreateToolBarIcon(toggle);
    CreateToolTip(toggle, title, IntVector2(toggle.width + 10, toggle.height - 10));

    return toggle;
}

void CreateToolBarIcon(UIElement@ element)
{
    BorderImage@ icon = BorderImage("Icon");
    icon.defaultStyle = iconStyle;
    icon.style = element.name;
    icon.SetFixedSize(30, 30);
    element.AddChild(icon);
}

UIElement@ CreateGroup(const String&in title, LayoutMode layoutMode)
{
    UIElement@ group = UIElement(title);
    group.defaultStyle = uiStyle;
    group.layoutMode = layoutMode;
    return group;
}

void FinalizeGroupHorizontal(UIElement@ group, const String&in baseStyle)
{
    for (uint i = 0; i < group.numChildren; ++i)
    {
        UIElement@ child = group.children[i];

        if (i == 0 && i < group.numChildren - 1)
            child.style = baseStyle + "GroupLeft";
        else if (i < group.numChildren - 1)
            child.style = baseStyle + "GroupMiddle";
        else
            child.style = baseStyle + "GroupRight";
    }

    group.maxSize = group.size;
}

UIElement@ CreateToolBarSpacer(uint width)
{
    UIElement@ spacer = UIElement();
    spacer.SetFixedWidth(width);
    return spacer;
}

UIElement@ CreateToolTip(UIElement@ parent, const String&in title, const IntVector2&in offset)
{
    ToolTip@ toolTip = parent.CreateChild("ToolTip");
    toolTip.position = offset;

    BorderImage@ textHolder = toolTip.CreateChild("BorderImage");
    textHolder.SetStyle("ToolTipBorderImage");

    Text@ toolTipText = textHolder.CreateChild("Text");
    toolTipText.SetStyle("ToolTipText");
    toolTipText.text = title;

    return toolTip;
}

void ToolBarRunUpdatePlay(StringHash eventType, VariantMap& eventData)
{
    CheckBox@ edit = eventData["Element"].GetPtr();
    if (edit.checked)
        StartSceneUpdate();
    toolBarDirty = true;
}

void ToolBarRunUpdatePause(StringHash eventType, VariantMap& eventData)
{
    CheckBox@ edit = eventData["Element"].GetPtr();
    if (edit.checked)
        StopSceneUpdate();
    toolBarDirty = true;
}

void ToolBarRevertOnPause(StringHash eventType, VariantMap& eventData)
{
    CheckBox@ edit = eventData["Element"].GetPtr();
    revertOnPause = edit.checked;
    toolBarDirty = true;
}

void ToolBarEditModeMove(StringHash eventType, VariantMap& eventData)
{
    CheckBox@ edit = eventData["Element"].GetPtr();
    if (edit.checked)
        editMode = EDIT_MOVE;
    toolBarDirty = true;
}

void ToolBarEditModeRotate(StringHash eventType, VariantMap& eventData)
{
    CheckBox@ edit = eventData["Element"].GetPtr();
    if (edit.checked)
        editMode = EDIT_ROTATE;
    toolBarDirty = true;
}

void ToolBarEditModeScale(StringHash eventType, VariantMap& eventData)
{
    CheckBox@ edit = eventData["Element"].GetPtr();
    if (edit.checked)
        editMode = EDIT_SCALE;
    toolBarDirty = true;
}

void ToolBarEditModeSelect(StringHash eventType, VariantMap& eventData)
{
    CheckBox@ edit = eventData["Element"].GetPtr();
    if (edit.checked)
        editMode = EDIT_SELECT;
    toolBarDirty = true;
}

void ToolBarAxisModeWorld(StringHash eventType, VariantMap& eventData)
{
    CheckBox@ edit = eventData["Element"].GetPtr();
    if (edit.checked)
        axisMode = AXIS_WORLD;
    toolBarDirty = true;
}

void ToolBarAxisModeLocal(StringHash eventType, VariantMap& eventData)
{
    CheckBox@ edit = eventData["Element"].GetPtr();
    if (edit.checked)
        axisMode = AXIS_LOCAL;
    toolBarDirty = true;
}

void ToolBarMoveSnap(StringHash eventType, VariantMap& eventData)
{
    CheckBox@ edit = eventData["Element"].GetPtr();
    moveSnap = edit.checked;
    toolBarDirty = true;
}

void ToolBarRotateSnap(StringHash eventType, VariantMap& eventData)
{
    CheckBox@ edit = eventData["Element"].GetPtr();
    rotateSnap = edit.checked;
    toolBarDirty = true;
}

void ToolBarScaleSnap(StringHash eventType, VariantMap& eventData)
{
    CheckBox@ edit = eventData["Element"].GetPtr();
    scaleSnap = edit.checked;
    toolBarDirty = true;
}

void ToolBarSnapScaleModeHalf(StringHash eventType, VariantMap& eventData)
{
    CheckBox@ edit = eventData["Element"].GetPtr();
    if (edit.checked)
    {
        snapScaleMode = SNAP_SCALE_HALF;
        snapScale = 0.5;
    }
    else if (snapScaleMode == SNAP_SCALE_HALF)
    {
        snapScaleMode = SNAP_SCALE_FULL;
        snapScale = 1.0;
    }
    toolBarDirty = true;
}

void ToolBarSnapScaleModeQuarter(StringHash eventType, VariantMap& eventData)
{
    CheckBox@ edit = eventData["Element"].GetPtr();
    if (edit.checked)
    {
        snapScaleMode = SNAP_SCALE_QUARTER;
        snapScale = 0.25;
    }
    else if (snapScaleMode == SNAP_SCALE_QUARTER)
    {
        snapScaleMode = SNAP_SCALE_FULL;
        snapScale = 1.0;
    }
    toolBarDirty = true;
}

void ToolBarPickModeGeometries(StringHash eventType, VariantMap& eventData)
{
    CheckBox@ edit = eventData["Element"].GetPtr();
    if (edit.checked)
        pickMode = PICK_GEOMETRIES;
    toolBarDirty = true;
}

void ToolBarPickModeLights(StringHash eventType, VariantMap& eventData)
{
    CheckBox@ edit = eventData["Element"].GetPtr();
    if (edit.checked)
        pickMode = PICK_LIGHTS;
    toolBarDirty = true;
}

void ToolBarPickModeZones(StringHash eventType, VariantMap& eventData)
{
    CheckBox@ edit = eventData["Element"].GetPtr();
    if (edit.checked)
        pickMode = PICK_ZONES;
    toolBarDirty = true;
}

void ToolBarPickModeRigidBodies(StringHash eventType, VariantMap& eventData)
{
    CheckBox@ edit = eventData["Element"].GetPtr();
    if (edit.checked)
        pickMode = PICK_RIGIDBODIES;
    toolBarDirty = true;
}

void ToolBarPickModeUIElements(StringHash eventType, VariantMap& eventData)
{
    CheckBox@ edit = eventData["Element"].GetPtr();
    if (edit.checked)
        pickMode = PICK_UI_ELEMENTS;
    toolBarDirty = true;
}

void ToolBarFillModePoint(StringHash eventType, VariantMap& eventData)
{
    CheckBox@ edit = eventData["Element"].GetPtr();
    if (edit.checked)
    {
        fillMode = FILL_POINT;
        SetFillMode(fillMode);
    }
    toolBarDirty = true;
}

void ToolBarFillModeWireFrame(StringHash eventType, VariantMap& eventData)
{
    CheckBox@ edit = eventData["Element"].GetPtr();
    if (edit.checked)
    {
        fillMode = FILL_WIREFRAME;
        SetFillMode(fillMode);
    }
    toolBarDirty = true;
}

void ToolBarFillModeSolid(StringHash eventType, VariantMap& eventData)
{
    CheckBox@ edit = eventData["Element"].GetPtr();
    if (edit.checked)
    {
        fillMode = FILL_SOLID;
        SetFillMode(fillMode);
    }
    toolBarDirty = true;
}

void ToolBarSetViewportMode(StringHash eventType, VariantMap& eventData)
{
    DropDownList@ dropDown = eventData["Element"].GetPtr();
    UIElement@ selected = dropDown.selectedItem;
    dropDown.focus = false;     // Lose the focus so the RMB dragging, immediately followed after changing viewport setup, behaves as expected
    uint mode = selected.vars[VIEW_MODE].GetUInt();
    SetViewportMode(mode);
}

void UpdateDirtyToolBar()
{
    if (toolBar is null || !toolBarDirty)
        return;

    CheckBox@ runUpdatePlayToggle = toolBar.GetChild("RunUpdatePlay", true);
    if (runUpdatePlayToggle.checked != runUpdate)
        runUpdatePlayToggle.checked = runUpdate;

    CheckBox@ runUpdatePauseToggle = toolBar.GetChild("RunUpdatePause", true);
    if (runUpdatePauseToggle.checked != (runUpdate == false))
        runUpdatePauseToggle.checked = runUpdate == false;

    CheckBox@ revertOnPauseToggle = toolBar.GetChild("RevertOnPause", true);
    if (revertOnPauseToggle.checked != revertOnPause)
        revertOnPauseToggle.checked = revertOnPause;

    CheckBox@ editMoveToggle = toolBar.GetChild("EditMove", true);
    if (editMoveToggle.checked != (editMode == EDIT_MOVE))
        editMoveToggle.checked = editMode == EDIT_MOVE;

    CheckBox@ editRotateToggle = toolBar.GetChild("EditRotate", true);
    if (editRotateToggle.checked != (editMode == EDIT_ROTATE))
        editRotateToggle.checked = editMode == EDIT_ROTATE;

    CheckBox@ editScaleToggle = toolBar.GetChild("EditScale", true);
    if (editScaleToggle.checked != (editMode == EDIT_SCALE))
        editScaleToggle.checked = editMode == EDIT_SCALE;

    CheckBox@ editSelectToggle = toolBar.GetChild("EditSelect", true);
    if (editSelectToggle.checked != (editMode == EDIT_SELECT))
        editSelectToggle.checked = editMode == EDIT_SELECT;

    CheckBox@ axisWorldToggle = toolBar.GetChild("AxisWorld", true);
    if (axisWorldToggle.checked != (axisMode == AXIS_WORLD))
        axisWorldToggle.checked = axisMode == AXIS_WORLD;

    CheckBox@ axisLocalToggle = toolBar.GetChild("AxisLocal", true);
    if (axisLocalToggle.checked != (axisMode == AXIS_LOCAL))
        axisLocalToggle.checked = axisMode == AXIS_LOCAL;

    CheckBox@ moveSnapToggle = toolBar.GetChild("MoveSnap", true);
    if (moveSnapToggle.checked != moveSnap)
        moveSnapToggle.checked = moveSnap;

    CheckBox@ rotateSnapToggle = toolBar.GetChild("RotateSnap", true);
    if (rotateSnapToggle.checked != rotateSnap)
        rotateSnapToggle.checked = rotateSnap;

    CheckBox@ scaleSnapToggle = toolBar.GetChild("ScaleSnap", true);
    if (scaleSnapToggle.checked != scaleSnap)
        scaleSnapToggle.checked = scaleSnap;

    CheckBox@ snapStepHalfToggle = toolBar.GetChild("SnapScaleHalf", true);
    if (snapStepHalfToggle.checked != (snapScaleMode == SNAP_SCALE_HALF))
        snapStepHalfToggle.checked = snapScaleMode == SNAP_SCALE_HALF;

    CheckBox@ snapStepQuarterToggle = toolBar.GetChild("SnapScaleQuarter", true);
    if (snapStepQuarterToggle.checked != (snapScaleMode == SNAP_SCALE_QUARTER))
        snapStepQuarterToggle.checked = snapScaleMode == SNAP_SCALE_QUARTER;

    CheckBox@ pickGeometriesToggle = toolBar.GetChild("PickGeometries", true);
    if (pickGeometriesToggle.checked != (pickMode == PICK_GEOMETRIES))
        pickGeometriesToggle.checked = pickMode == PICK_GEOMETRIES;

    CheckBox@ pickLightsToggle = toolBar.GetChild("PickLights", true);
    if (pickLightsToggle.checked != (pickMode == PICK_LIGHTS))
        pickLightsToggle.checked = pickMode == PICK_LIGHTS;

    CheckBox@ pickZonesToggle = toolBar.GetChild("PickZones", true);
    if (pickZonesToggle.checked != (pickMode == PICK_ZONES))
        pickZonesToggle.checked = pickMode == PICK_ZONES;

    CheckBox@ pickRigidBodiesToggle = toolBar.GetChild("PickRigidBodies", true);
    if (pickRigidBodiesToggle.checked != (pickMode == PICK_RIGIDBODIES))
        pickRigidBodiesToggle.checked = pickMode == PICK_RIGIDBODIES;

    CheckBox@ pickUIElementsToggle = toolBar.GetChild("PickUIElements", true);
    if (pickUIElementsToggle.checked != (pickMode == PICK_UI_ELEMENTS))
        pickUIElementsToggle.checked = pickMode == PICK_UI_ELEMENTS;

    CheckBox@ fillPointToggle = toolBar.GetChild("FillPoint", true);
    if (fillPointToggle.checked != (fillMode == FILL_POINT))
        fillPointToggle.checked = fillMode == FILL_POINT;

    CheckBox@ fillWireFrameToggle = toolBar.GetChild("FillWireFrame", true);
    if (fillWireFrameToggle.checked != (fillMode == FILL_WIREFRAME))
        fillWireFrameToggle.checked = fillMode == FILL_WIREFRAME;

    CheckBox@ fillSolidToggle = toolBar.GetChild("FillSolid", true);
    if (fillSolidToggle.checked != (fillMode == FILL_SOLID))
        fillSolidToggle.checked = fillMode == FILL_SOLID;

    if (!subscribedToEditorToolBar)
    {
        SubscribeToEvent(runUpdatePlayToggle, "Toggled", "ToolBarRunUpdatePlay");
        SubscribeToEvent(runUpdatePauseToggle, "Toggled", "ToolBarRunUpdatePause");
        SubscribeToEvent(revertOnPauseToggle, "Toggled", "ToolBarRevertOnPause");
        SubscribeToEvent(editMoveToggle, "Toggled", "ToolBarEditModeMove");
        SubscribeToEvent(editRotateToggle, "Toggled", "ToolBarEditModeRotate");
        SubscribeToEvent(editScaleToggle, "Toggled", "ToolBarEditModeScale");
        SubscribeToEvent(editSelectToggle, "Toggled", "ToolBarEditModeSelect");
        SubscribeToEvent(axisWorldToggle, "Toggled", "ToolBarAxisModeWorld");
        SubscribeToEvent(axisLocalToggle, "Toggled", "ToolBarAxisModeLocal");
        SubscribeToEvent(moveSnapToggle, "Toggled", "ToolBarMoveSnap");
        SubscribeToEvent(rotateSnapToggle, "Toggled", "ToolBarRotateSnap");
        SubscribeToEvent(scaleSnapToggle, "Toggled", "ToolBarScaleSnap");
        SubscribeToEvent(snapStepHalfToggle, "Toggled", "ToolBarSnapScaleModeHalf");
        SubscribeToEvent(snapStepQuarterToggle, "Toggled", "ToolBarSnapScaleModeQuarter");
        SubscribeToEvent(pickGeometriesToggle, "Toggled", "ToolBarPickModeGeometries");
        SubscribeToEvent(pickLightsToggle, "Toggled", "ToolBarPickModeLights");
        SubscribeToEvent(pickZonesToggle, "Toggled", "ToolBarPickModeZones");
        SubscribeToEvent(pickRigidBodiesToggle, "Toggled", "ToolBarPickModeRigidBodies");
        SubscribeToEvent(pickUIElementsToggle, "Toggled", "ToolBarPickModeUIElements");
        SubscribeToEvent(fillPointToggle, "Toggled", "ToolBarFillModePoint");
        SubscribeToEvent(fillWireFrameToggle, "Toggled", "ToolBarFillModeWireFrame");
        SubscribeToEvent(fillSolidToggle, "Toggled", "ToolBarFillModeSolid");
        subscribedToEditorToolBar = true;
    }

    toolBarDirty = false;
}

Text@ CreateViewPortModeText(String text_, uint mode)
{
    Text@ text = Text();
    text.text = text_;
    text.vars[VIEW_MODE] = mode;
    text.style = "EditorEnumAttributeText";
    return text;
}
