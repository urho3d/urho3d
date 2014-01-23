// Common sample initialization as a framework for all samples.
//    - Create Urho3D logo at screen;
//    - Create Console and Debug HUD, and use F1 and F2 key to toggle them;
//    - Toggle rendering options from the keys 1-8;
//    - Handle Esc key down to hide Console or exit application;

Sprite@ logoSprite;

void SampleStart()
{
    // Create logo
    CreateLogo();

    // Create console and debug HUD
    CreateConsoleAndDebugHud();

    // Subscribe key down event
    SubscribeToEvent("KeyDown", "HandleKeyDown");
}

void SetLogoVisible(bool enable)
{
    if (logoSprite !is null)
        logoSprite.visible = enable;
}

void CreateLogo()
{
    // Get logo texture
    Texture2D@ logoTexture = cache.GetResource("Texture2D", "Textures/LogoLarge.png");
    if (logoTexture is null)
        return;

    // Create logo sprite and add to the UI layout
    logoSprite = ui.root.CreateChild("Sprite");

    // Set logo sprite texture
    logoSprite.texture = logoTexture;

    int textureWidth = logoTexture.width;
    int textureHeight = logoTexture.height;

    // Set logo sprite scale
    logoSprite.SetScale(256.0f / textureWidth);

    // Set logo sprite size
    logoSprite.SetSize(textureWidth, textureHeight);

    // Set logo sprite hot spot
    logoSprite.SetHotSpot(0, textureHeight);

    // Set logo sprite alignment
    logoSprite.SetAlignment(HA_LEFT, VA_BOTTOM);
    
    // Make logo not fully opaque to show the scene underneath
    logoSprite.opacity = 0.75f;
    
    // Set a low priority for the logo so that other UI elements can be drawn on top
    logoSprite.priority = -100;
}

void CreateConsoleAndDebugHud()
{
    // Get default style
    XMLFile@ xmlFile = cache.GetResource("XMLFile", "UI/DefaultStyle.xml");
    if (xmlFile is null)
        return;

    // Create console
    Console@ console = engine.CreateConsole();
    console.defaultStyle = xmlFile;

    // Create debug HUD
    DebugHud@ debugHud = engine.CreateDebugHud();
    debugHud.defaultStyle = xmlFile;
}

void HandleKeyDown(StringHash eventType, VariantMap& eventData)
{
    int key = eventData["Key"].GetInt();

    // Close console (if open) or exit when ESC is pressed
    if (key == KEY_ESC)
    {
        if (!console.visible)
            engine.Exit();
        else
            console.visible = false;
    }

    // Toggle console with F1
    else if (key == KEY_F1)
        console.Toggle();

    // Toggle debug HUD with F2
    else if (key == KEY_F2)
        debugHud.ToggleAll();

    // Common rendering quality controls, only when UI has no focused element
    if (ui.focusElement is null)
    {
        // Texture quality
        if (key == '1')
        {
            int quality = renderer.textureQuality;
            ++quality;
            if (quality > QUALITY_HIGH)
                quality = QUALITY_LOW;
            renderer.textureQuality = quality;
        }

        // Material quality
        else if (key == '2')
        {
            int quality = renderer.materialQuality;
            ++quality;
            if (quality > QUALITY_HIGH)
                quality = QUALITY_LOW;
            renderer.materialQuality = quality;
        }
        
        // Specular lighting
        else if (key == '3')
            renderer.specularLighting = !renderer.specularLighting;

        // Shadow rendering
        else if (key == '4')
            renderer.drawShadows = !renderer.drawShadows;

        // Shadow map resolution
        else if (key == '5')
        {
            int shadowMapSize = renderer.shadowMapSize;
            shadowMapSize *= 2;
            if (shadowMapSize > 2048)
                shadowMapSize = 512;
            renderer.shadowMapSize = shadowMapSize;
        }
        
        // Shadow depth and filtering quality
        else if (key == '6')
        {
            int quality = renderer.shadowQuality;
            ++quality;
            if (quality > SHADOWQUALITY_HIGH_24BIT)
                quality = SHADOWQUALITY_LOW_16BIT;
            renderer.shadowQuality = quality;
        }
        
        // Occlusion culling
        else if (key == '7')
        {
            bool occlusion = renderer.maxOccluderTriangles > 0;
            occlusion = !occlusion;
            renderer.maxOccluderTriangles = occlusion ? 5000 : 0;
        }
        
        // Instancing
        else if (key == '8')
            renderer.dynamicInstancing = !renderer.dynamicInstancing;
    }
}
