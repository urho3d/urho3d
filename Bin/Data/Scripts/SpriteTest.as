uint numSprites = 100;
Array<Sprite@> sprites;
Array<Vector2> speeds;

void Start()
{
    if (engine.headless)
    {
        ErrorDialog("SpriteTest", "Headless mode is not supported. The program will now exit.");
        engine.Exit();
        return;
    }

    InitUI();
    InitSprites();

    SubscribeToEvent("Update", "HandleUpdate");
    SubscribeToEvent("KeyDown", "HandleKeyDown");
}

void InitUI()
{
    XMLFile@ uiStyle = cache.GetResource("XMLFile", "UI/DefaultStyle.xml");

    engine.CreateDebugHud();
    debugHud.style = uiStyle;
    debugHud.mode = DEBUGHUD_SHOW_ALL;

    engine.CreateConsole();
    console.style = uiStyle;

    Cursor@ cursor = Cursor("Cursor");
    cursor.style = uiStyle;
    cursor.position = IntVector2(graphics.width / 2, graphics.height / 2);
    ui.cursor = cursor;
    if (GetPlatform() == "Android" || GetPlatform() == "iOS")
        ui.cursor.visible = false;
}

void InitSprites()
{
    Texture2D@ decalTex = cache.GetResource("Texture2D", "Textures/UrhoDecal.dds");

    for (uint i = 0; i < numSprites; ++i)
    {
        Sprite@ sprite = Sprite();
        sprite.texture = decalTex;
        sprite.SetFullImageRect();
        sprite.position = Vector2(Random(graphics.width), Random(graphics.height));
        sprite.size = IntVector2(128, 128);
        sprite.hotSpot = IntVector2(64, 64);
        sprite.rotation = Random(360);
        sprite.SetScale(Random(1) + 0.5);
        sprite.color = Color(Random(0.5) + 0.5, Random(0.5) + 0.5, Random(0.5) + 0.5, 1.0);
        sprite.blendMode = BLEND_ADD;

        ui.root.AddChild(sprite);

        sprites.Push(sprite);
        speeds.Push(Vector2(Random(200) - 100, Random(200) - 100));
    }
}

void HandleUpdate(StringHash eventType, VariantMap& eventData)
{
    float timeStep = eventData["TimeStep"].GetFloat();

    for (uint i = 0; i < numSprites; ++i)
    {
        sprites[i].rotation = sprites[i].rotation + timeStep * 30;
        Vector2 newPos = sprites[i].position;
        newPos += speeds[i] * timeStep;
        if (newPos.x >= graphics.width)
            newPos.x -= graphics.width;
        else if (newPos.x < 0)
            newPos.x += graphics.width;
        if (newPos.y >= graphics.height)
            newPos.y -= graphics.height;
        else if (newPos.y < 0)
            newPos.y += graphics.height;
        sprites[i].position = newPos;
    }
}

void HandleKeyDown(StringHash eventType, VariantMap& eventData)
{
    int key = eventData["Key"].GetInt();

    if (key == KEY_ESC)
    {
        if (ui.focusElement is null)
            engine.Exit();
        else
            console.visible = false;
    }
    
    if (key == KEY_F1)
        console.Toggle();
        
    if (key == 'T')
        debugHud.Toggle(DEBUGHUD_SHOW_PROFILER);
}
