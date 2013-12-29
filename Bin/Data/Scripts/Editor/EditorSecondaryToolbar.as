UIElement@ secondaryToolBar;

void CreateSecondaryToolBar()
{
    secondaryToolBar = BorderImage("secondaryToolBar");
    ui.root.AddChild(secondaryToolBar);

    secondaryToolBar.style = "EditorToolBar";
    secondaryToolBar.SetLayout(LM_VERTICAL);
    secondaryToolBar.layoutSpacing = 4;
    secondaryToolBar.layoutBorder = IntRect(4, 4, 4, 4);
    secondaryToolBar.opacity = uiMaxOpacity;
    secondaryToolBar.SetFixedSize(28, graphics.height);
    secondaryToolBar.SetPosition(0, uiMenuBar.height+40);
    secondaryToolBar.SetFixedHeight(graphics.height);

    Button@ b = CreateSmallToolBarButton("Node", "Replicated Node");
    secondaryToolBar.AddChild(b);
    SubscribeToEvent(b, "Released", "SmallToolBarCreateReplNode");  

    b = CreateSmallToolBarButton("Node", "Local Node");
    secondaryToolBar.AddChild(b);
    SubscribeToEvent(b, "Released", "SmallToolBarCreateLocalNode");

    secondaryToolBar.AddChild(CreateSmallToolBarSpacer(3));

    b = CreateSmallToolBarButton("Light");
    secondaryToolBar.AddChild(b);
    SubscribeToEvent(b, "Released", "SmallToolBarCreateComponent"); 

    b = CreateSmallToolBarButton("Camera");
    secondaryToolBar.AddChild(b);
    SubscribeToEvent(b, "Released", "SmallToolBarCreateComponent");

    b = CreateSmallToolBarButton("Zone");
    secondaryToolBar.AddChild(b);
    SubscribeToEvent(b, "Released", "SmallToolBarCreateComponent"); 

    b = CreateSmallToolBarButton("StaticModel");
    secondaryToolBar.AddChild(b);
    SubscribeToEvent(b, "Released", "SmallToolBarCreateComponent");

    b = CreateSmallToolBarButton("AnimatedModel");
    secondaryToolBar.AddChild(b);
    SubscribeToEvent(b, "Released", "SmallToolBarCreateComponent");

    b = CreateSmallToolBarButton("BillboardSet");
    secondaryToolBar.AddChild(b);
    SubscribeToEvent(b, "Released", "SmallToolBarCreateComponent");

    b = CreateSmallToolBarButton("ParticleEmitter");
    secondaryToolBar.AddChild(b);
    SubscribeToEvent(b, "Released", "SmallToolBarCreateComponent");

    b = CreateSmallToolBarButton("Skybox");
    secondaryToolBar.AddChild(b);
    SubscribeToEvent(b, "Released", "SmallToolBarCreateComponent");

    b = CreateSmallToolBarButton("Terrain");
    secondaryToolBar.AddChild(b);
    SubscribeToEvent(b, "Released", "SmallToolBarCreateComponent");

    b = CreateSmallToolBarButton("Text3D");
    secondaryToolBar.AddChild(b);
    SubscribeToEvent(b, "Released", "SmallToolBarCreateComponent");

    secondaryToolBar.AddChild(CreateSmallToolBarSpacer(3));

    b = CreateSmallToolBarButton("SoundListener");
    secondaryToolBar.AddChild(b);
    SubscribeToEvent(b, "Released", "SmallToolBarCreateComponent"); 

    b = CreateSmallToolBarButton("SoundSource3D");
    secondaryToolBar.AddChild(b);
    SubscribeToEvent(b, "Released", "SmallToolBarCreateComponent");

    b = CreateSmallToolBarButton("SoundSource");
    secondaryToolBar.AddChild(b);
    SubscribeToEvent(b, "Released", "SmallToolBarCreateComponent"); 

    secondaryToolBar.AddChild(CreateSmallToolBarSpacer(3));

    b = CreateSmallToolBarButton("RigidBody");
    secondaryToolBar.AddChild(b);
    SubscribeToEvent(b, "Released", "SmallToolBarCreateComponent");

    b = CreateSmallToolBarButton("CollisionShape");
    secondaryToolBar.AddChild(b);
    SubscribeToEvent(b, "Released", "SmallToolBarCreateComponent");

    b = CreateSmallToolBarButton("Constraint");
    secondaryToolBar.AddChild(b);
    SubscribeToEvent(b, "Released", "SmallToolBarCreateComponent"); 

    secondaryToolBar.AddChild(CreateSmallToolBarSpacer(3)); 

    b = CreateSmallToolBarButton("AnimationController");
    secondaryToolBar.AddChild(b);
    SubscribeToEvent(b, "Released", "SmallToolBarCreateComponent");

    b = CreateSmallToolBarButton("ScriptInstance");
    secondaryToolBar.AddChild(b);
    SubscribeToEvent(b, "Released", "SmallToolBarCreateComponent");

    secondaryToolBar.AddChild(CreateSmallToolBarSpacer(3));

    b = CreateSmallToolBarButton("Navigable");
    secondaryToolBar.AddChild(b);
    SubscribeToEvent(b, "Released", "SmallToolBarCreateComponent");

    b = CreateSmallToolBarButton("NavigationMesh");
    secondaryToolBar.AddChild(b);
    SubscribeToEvent(b, "Released", "SmallToolBarCreateComponent");

    b = CreateSmallToolBarButton("OffMeshConnection");
    secondaryToolBar.AddChild(b);
    SubscribeToEvent(b, "Released", "SmallToolBarCreateComponent");

    secondaryToolBar.AddChild(CreateSmallToolBarSpacer(3));

    b = CreateSmallToolBarButton("NetworkPriority");
    secondaryToolBar.AddChild(b);
    SubscribeToEvent(b, "Released", "SmallToolBarCreateComponent"); 
}

Button@ CreateSmallToolBarButton(const String&in title, String toolTipTitle = "")
{
    Button@ button = Button(title);
    button.defaultStyle = uiStyle;
    button.style = "ToolBarButton";
    button.SetFixedSize(20, 20);
    CreateSmallToolBarIcon(button);

    if (toolTipTitle.empty)
        toolTipTitle = title;
    CreateToolTip(button, toolTipTitle, IntVector2(button.width + 10, button.height - 10));

    return button;
}

void CreateSmallToolBarIcon(UIElement@ element)
{
    BorderImage@ icon = BorderImage("Icon");
    icon.defaultStyle = iconStyle;
    icon.style = element.name;
    icon.SetFixedSize(14, 14);
    element.AddChild(icon);
}

UIElement@ CreateSmallToolBarSpacer(uint width)
{
    UIElement@ spacer = UIElement();
    spacer.SetFixedHeight(width);
    return spacer;
}

void SmallToolBarCreateReplNode(StringHash eventType, VariantMap& eventData)
{
    CreateNode(REPLICATED);
}

void SmallToolBarCreateLocalNode(StringHash eventType, VariantMap& eventData)
{
    CreateNode(LOCAL);
}

void SmallToolBarCreateComponent(StringHash eventType, VariantMap& eventData)
{
    Button@ b = GetEventSender();
    CreateComponent(b.name);
}