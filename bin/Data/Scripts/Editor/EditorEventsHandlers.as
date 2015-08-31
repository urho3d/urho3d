// Editor main handlers (add your local handler in proper main handler to prevent losing events)

void EditorSubscribeToEvents()
{
    SubscribeToEvent("KeyDown", "EditorMainHandleKeyDown");
    SubscribeToEvent("KeyUp", "EditorMainHandleKeyUp");

    SubscribeToEvent("MouseMove", "EditorMainHandleMouseMove");
    SubscribeToEvent("MouseWheel", "EditorMainHandleMouseWheel");
    SubscribeToEvent("MouseButtonDown", "EditorMainHandleMouseButtonDown");
    SubscribeToEvent("MouseButtonUp", "EditorMainHandleMouseButtonUp");

    SubscribeToEvent("PostRenderUpdate", "EditorMainHandlePostRenderUpdate");

    SubscribeToEvent("UIMouseClick", "EditorMainHandleUIMouseClick");
    SubscribeToEvent("UIMouseClickEnd", "EditorMainHandleUIMouseClickEnd");

    SubscribeToEvent("BeginViewUpdate", "EditorMainHandleBeginViewUpdate");
    SubscribeToEvent("EndViewUpdate", "EditorMainHandleEndViewUpdate");
    SubscribeToEvent("BeginViewRender", "EditorMainHandleBeginViewRender");
    SubscribeToEvent("EndViewRender", "EditorMainHandleEndViewRender");
}

void EditorMainHandleKeyDown(StringHash eventType, VariantMap& eventData)
{
    // EditorUI.as handler
    HandleKeyDown(eventType, eventData);

    // EditorColorWheel.as handler
    HandleColorWheelKeyDown(eventType, eventData);
}

void EditorMainHandleKeyUp(StringHash eventType, VariantMap& eventData)
{
    // EditorUI.as handler
    UnfadeUI();
}

void EditorMainHandleMouseMove(StringHash eventType, VariantMap& eventData)
{
    // EditorView.as handler
    ViewMouseMove();

    // EditorColorWheel.as handler
    HandleColorWheelMouseMove(eventType, eventData);

    // EditorLayer.as handler
    HandleHideLayerEditor(eventType, eventData);
}

void EditorMainHandleMouseWheel(StringHash eventType, VariantMap& eventData)
{
    // EditorColorWheel.as handler
    HandleColorWheelMouseWheel(eventType, eventData);

    // EditorLayer.as handler
    HandleMaskTypeScroll(eventType, eventData);    
}

void EditorMainHandleMouseButtonDown(StringHash eventType, VariantMap& eventData)
{
    // EditorColorWheel.as handler
    HandleColorWheelMouseButtonDown(eventType, eventData);

    // EditorLayer.as handler
    HandleHideLayerEditor(eventType, eventData);

}

void EditorMainHandleMouseButtonUp(StringHash eventType, VariantMap& eventData)
{
    // EditorUI.as handler
    UnfadeUI();
}

void EditorMainHandlePostRenderUpdate(StringHash eventType, VariantMap& eventData)
{
    // EditorView.as handler
    HandlePostRenderUpdate();
} 

void EditorMainHandleUIMouseClick(StringHash eventType, VariantMap& eventData)
{
    // EditorView.as handler
    ViewMouseClick();
}

void EditorMainHandleUIMouseClickEnd(StringHash eventType, VariantMap& eventData)
{
    // EditorView.as handler
    ViewMouseClickEnd();
}

void EditorMainHandleBeginViewUpdate(StringHash eventType, VariantMap& eventData)
{
    // EditorView.as handler
    HandleBeginViewUpdate(eventType, eventData);
}

void EditorMainHandleEndViewUpdate(StringHash eventType, VariantMap& eventData)
{
    // EditorView.as handler
    HandleEndViewUpdate(eventType, eventData);
}

void EditorMainHandleBeginViewRender(StringHash eventType, VariantMap& eventData) 
{
    HandleBeginViewRender(eventType, eventData);
}

void EditorMainHandleEndViewRender(StringHash eventType, VariantMap& eventData)
{
    HandleEndViewRender(eventType, eventData);
}