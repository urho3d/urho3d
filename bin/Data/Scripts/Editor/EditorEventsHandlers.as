// Editor main handlers (add your's local handler in proper main handler to prevent losing events)

void EditorSubscribeToEvents() 
{
    SubscribeToEvent("KeyDown", "EditorMainHandleKeyDown");
    SubscribeToEvent("KeyUp", "EditorMainHandleKeyUp");
       
    SubscribeToEvent("MouseMove", "EditorMainHandleMouseMove");
    SubscribeToEvent("MouseWheel", "EditorMainHandleMouseWheel");
    SubscribeToEvent("MouseButtonDown", "EditorMainHandleMouseButtonDown");
        
}

void EditorMainHandleKeyDown(StringHash eventType, VariantMap& eventData) 
{
    // EditorColorWheel.as handler
    HandleColorWheelKeyDown(eventType, eventData);
}

void EditorMainHandleKeyUp(StringHash eventType, VariantMap& eventData) 
{

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




