// Localization example.
// This sample demonstrates:
//     - Loading a collection of strings from JSON-files
//     - Creating text elements that automatically translates itself by changing the language
//     - The manually reaction to change language

#include "Scripts/Utilities/Sample.as"

void Start()
{
    // Execute the common startup for samples
    SampleStart();

    // Enable OS cursor
    input.mouseVisible = true;

    // Load strings from JSON files and subscribe to the change language event
    InitLocalizationSystem();

    // Init the 3D space
    CreateScene();

    // Init the user interface
    CreateGUI();

    // Set the mouse mode to use in the sample
    SampleInitMouseMode(MM_FREE);
}

void InitLocalizationSystem()
{
    // JSON files must be in UTF8 encoding without BOM
    // The first found language will be set as current
    localization.LoadJSONFile("StringsEnRu.json");
    // You can load multiple files
    localization.LoadJSONFile("StringsDe.json");
    // Hook up to the change language
    SubscribeToEvent("ChangeLanguage", "HandleChangeLanguage");
}

void CreateGUI()
{
    ui.root.defaultStyle = cache.GetResource("XMLFile", "UI/DefaultStyle.xml");

    Window@ window = Window();
    ui.root.AddChild(window);
    window.SetMinSize(384, 192);
    window.SetLayout(LM_VERTICAL, 6, IntRect(6, 6, 6, 6));
    window.SetAlignment(HA_CENTER, VA_CENTER);
    window.SetStyleAuto();

    Text@ windowTitle = Text();
    windowTitle.name = "WindowTitle";
    windowTitle.SetStyleAuto();
    window.AddChild(windowTitle);

    // In this place the current language is "en" because it was found first when loading the JSON files
    String langName = localization.language;
    // Languages are numbered in the loading order
    int langIndex = localization.languageIndex; // == 0 at the beginning
    // Get string with identifier "title" in the current language
    String localizedString = localization.Get("title");
    // Localization.Get returns String::EMPTY if the id is empty.
    // Localization.Get returns the id if translation is not found and will be added a warning into the log.

    windowTitle.text = localizedString + " (" + String(langIndex) + " " + langName + ")";

    Button@ b = Button();
    window.AddChild(b);
    b.SetStyle("Button");
    b.minHeight = 24;

    Text@ t = b.CreateChild("Text", "ButtonTextChangeLang");
    // The showing text value will automatically change when language is changed
    t.autoLocalizable = true;
    // The text value used as a string identifier in this mode.
    // Remember that a letter case of the id and of the lang name is important.
    t.text = "Press this button";

    t.SetAlignment(HA_CENTER, VA_CENTER);
    t.SetStyle("Text");
    SubscribeToEvent(b, "Released", "HandleChangeLangButtonPressed");

    b = Button();
    window.AddChild(b);
    b.SetStyle("Button");
    b.minHeight = 24;
    t = b.CreateChild("Text", "ButtonTextQuit");
    t.SetAlignment(HA_CENTER, VA_CENTER);
    t.SetStyle("Text");

    // Manually set text in the current language
    t.text = localization.Get("quit");

    SubscribeToEvent(b, "Released", "HandleQuitButtonPressed");
}

void CreateScene()
{
    scene_ = Scene();
    scene_.CreateComponent("Octree");

    Zone@ zone = scene_.CreateComponent("Zone");
    zone.boundingBox = BoundingBox(-1000.0f, 1000.0f);
    zone.ambientColor = Color(0.5f, 0.5f, 0.5f);
    zone.fogColor = Color(0.4f, 0.5f, 0.8f);
    zone.fogStart = 1.0f;
    zone.fogEnd = 100.0f;

    Node@ planeNode = scene_.CreateChild("Plane");
    planeNode.scale = Vector3(300.0f, 1.0f, 300.0f);
    StaticModel@ planeObject = planeNode.CreateComponent("StaticModel");
    planeObject.model = cache.GetResource("Model", "Models/Plane.mdl");
    planeObject.material = cache.GetResource("Material", "Materials/StoneTiled.xml");

    Node@ lightNode = scene_.CreateChild("DirectionalLight");
    lightNode.direction = Vector3(0.6f, -1.0f, 0.8f);
    Light@ light = lightNode.CreateComponent("Light");
    light.lightType = LIGHT_DIRECTIONAL;
    light.color = Color(0.8f, 0.8f, 0.8f);

    cameraNode = scene_.CreateChild("Camera");
    cameraNode.CreateComponent("Camera");
    cameraNode.position = Vector3(0.0f, 10.0f, -30.0f);

    Node@ text3DNode = scene_.CreateChild("Text3D");
    text3DNode.position = Vector3(0.0f, 0.1f, 30.0f);
    text3DNode.SetScale(15);
    Text3D@ text3D = text3DNode.CreateComponent("Text3D");

    // Manually set text in the current language.
    text3D.text = localization.Get("lang");

    text3D.SetFont(cache.GetResource("Font", "Fonts/Anonymous Pro.ttf"), 30);
    text3D.color = BLACK;
    text3D.SetAlignment(HA_CENTER, VA_BOTTOM);

    Viewport@ viewport = Viewport(scene_, cameraNode.GetComponent("Camera"));
    renderer.viewports[0] = viewport;

    SubscribeToEvent("Update", "HandleUpdate");
}

void HandleUpdate(StringHash eventType, VariantMap& eventData)
{
    float timeStep = eventData["TimeStep"].GetFloat();
    const float MOUSE_SENSITIVITY = 0.1f;
    IntVector2 mouseMove = input.mouseMove;
    yaw += MOUSE_SENSITIVITY * mouseMove.x;
    pitch += MOUSE_SENSITIVITY * mouseMove.y;
    pitch = Clamp(pitch, -90.0f, 90.0f);
    cameraNode.rotation = Quaternion(pitch, yaw, 0.0f);
}

void HandleChangeLangButtonPressed(StringHash eventType, VariantMap& eventData)
{
    // Languages are numbered in the loading order
    int lang = localization.languageIndex;
    lang++;
    if (lang >= localization.numLanguages)
        lang = 0;
    localization.SetLanguage(lang);
}

void HandleQuitButtonPressed(StringHash eventType, VariantMap& eventData)
{
    engine.Exit();
}

// You can manually change texts, sprites and other aspects of the game when language is changed
void HandleChangeLanguage(StringHash eventType, VariantMap& eventData)
{
    Text@ windowTitle = ui.root.GetChild("WindowTitle", true);
    windowTitle.text = localization.Get("title") + " (" +
                           String(localization.languageIndex) + " " +
                           localization.language + ")";

    Text@ buttonText = ui.root.GetChild("ButtonTextQuit", true);
    buttonText.text = localization.Get("quit");

    Text3D@ text3D = scene_.GetChild("Text3D").GetComponent("Text3D");
    text3D.text = localization.Get("lang");

    // A text on the button "Press this button" changes automatically
}

String patchInstructions = "";
