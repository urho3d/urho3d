// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#include <Urho3D/Core/CoreEvents.h>
#include <Urho3D/Graphics/Material.h>
#include <Urho3D/Graphics/Model.h>
#include <Urho3D/Graphics/Octree.h>
#include <Urho3D/Graphics/StaticModel.h>
#include <Urho3D/Graphics/Zone.h>
#include <Urho3D/Resource/Localization.h>
#include <Urho3D/Resource/ResourceEvents.h>
#include <Urho3D/UI/Button.h>
#include <Urho3D/UI/Font.h>
#include <Urho3D/UI/Text.h>
#include <Urho3D/UI/Text3D.h>
#include <Urho3D/UI/UIEvents.h>
#include <Urho3D/UI/Window.h>

#include "L10n.h"

#include <Urho3D/DebugNew.h>

URHO3D_DEFINE_APPLICATION_MAIN(L10n)

L10n::L10n(Context* context) :
    Sample(context)
{
}

void L10n::Start()
{
    // Execute base class startup
    Sample::Start();

    // Enable and center OS cursor
    auto* input = GetSubsystem<Input>();
    input->SetMouseVisible(true);
    input->CenterMousePosition();

    // Load strings from JSON files and subscribe to the change language event
    InitLocalizationSystem();

    // Init the 3D space
    CreateScene();

    // Init the user interface
    CreateGUI();

    // Set the mouse mode to use in the sample
    Sample::InitMouseMode(MM_FREE);
}

void L10n::InitLocalizationSystem()
{
    auto* l10n = GetSubsystem<Localization>();
    // JSON files must be in UTF8 encoding without BOM
    // The first found language will be set as current
    l10n->LoadJSONFile("StringsEnRu.json");
    // You can load multiple files
    l10n->LoadJSONFile("StringsDe.json");
    l10n->LoadJSONFile("StringsLv.json", "lv");
    // Hook up to the change language
    SubscribeToEvent(E_CHANGELANGUAGE, URHO3D_HANDLER(L10n, HandleChangeLanguage));
}

void L10n::CreateGUI()
{
    // Get localization subsystem
    auto* l10n = GetSubsystem<Localization>();

    auto* cache = GetSubsystem<ResourceCache>();
    UIElement* root = GetSubsystem<UI>()->GetRoot();
    root->SetDefaultStyle(cache->GetResource<XMLFile>("UI/DefaultStyle.xml"));

    auto* window = new Window(context_);
    root->AddChild(window);
    window->SetMinSize(384, 192);
    window->SetLayout(LM_VERTICAL, 6, IntRect(6, 6, 6, 6));
    window->SetAlignment(HA_CENTER, VA_CENTER);
    window->SetStyleAuto();

    auto* windowTitle = new Text(context_);
    windowTitle->SetName("WindowTitle");
    windowTitle->SetStyleAuto();
    window->AddChild(windowTitle);

    // In this place the current language is "en" because it was found first when loading the JSON files
    String langName = l10n->GetLanguage();
    // Languages are numbered in the loading order
    int langIndex = l10n->GetLanguageIndex(); // == 0 at the beginning
    // Get string with identifier "title" in the current language
    String localizedString = l10n->Get("title");
    // Localization::Get returns String::EMPTY if the id is empty.
    // Localization::Get returns the id if translation is not found and will be added a warning into the log.

    windowTitle->SetText(localizedString + " (" + String(langIndex) + " " + langName + ")");

    auto* b = new Button(context_);
    window->AddChild(b);
    b->SetStyle("Button");
    b->SetMinHeight(24);

    auto* t = b->CreateChild<Text>("ButtonTextChangeLang");
    // The showing text value will automatically change when language is changed
    t->SetAutoLocalizable(true);
    // The text value used as a string identifier in this mode.
    // Remember that a letter case of the id and of the lang name is important.
    t->SetText("Press this button");

    t->SetAlignment(HA_CENTER, VA_CENTER);
    t->SetStyle("Text");
    SubscribeToEvent(b, E_RELEASED, URHO3D_HANDLER(L10n, HandleChangeLangButtonPressed));

    b = new Button(context_);
    window->AddChild(b);
    b->SetStyle("Button");
    b->SetMinHeight(24);
    t = b->CreateChild<Text>("ButtonTextQuit");
    t->SetAlignment(HA_CENTER, VA_CENTER);
    t->SetStyle("Text");

    // Manually set text in the current language
    t->SetText(l10n->Get("quit"));

    SubscribeToEvent(b, E_RELEASED, URHO3D_HANDLER(L10n, HandleQuitButtonPressed));
}

void L10n::CreateScene()
{
    // Get localization subsystem
    auto* l10n = GetSubsystem<Localization>();

    auto* cache = GetSubsystem<ResourceCache>();
    scene_ = new Scene(context_);
    scene_->CreateComponent<Octree>();

    auto* zone = scene_->CreateComponent<Zone>();
    zone->SetBoundingBox(BoundingBox(-1000.0f, 1000.0f));
    zone->SetAmbientColor(Color(0.5f, 0.5f, 0.5f));
    zone->SetFogColor(Color(0.4f, 0.5f, 0.8f));
    zone->SetFogStart(1.0f);
    zone->SetFogEnd(100.0f);

    Node* planeNode = scene_->CreateChild("Plane");
    planeNode->SetScale(Vector3(300.0f, 1.0f, 300.0f));
    auto* planeObject = planeNode->CreateComponent<StaticModel>();
    planeObject->SetModel(cache->GetResource<Model>("Models/Plane.mdl"));
    planeObject->SetMaterial(cache->GetResource<Material>("Materials/StoneTiled.xml"));

    Node* lightNode = scene_->CreateChild("DirectionalLight");
    lightNode->SetDirection(Vector3(0.6f, -1.0f, 0.8f));
    auto* light = lightNode->CreateComponent<Light>();
    light->SetLightType(LIGHT_DIRECTIONAL);
    light->SetColor(Color(0.8f, 0.8f, 0.8f));

    cameraNode_ = scene_->CreateChild("Camera");
    cameraNode_->CreateComponent<Camera>();
    cameraNode_->SetPosition(Vector3(0.0f, 10.0f, -30.0f));

    Node* text3DNode = scene_->CreateChild("Text3D");
    text3DNode->SetPosition(Vector3(0.0f, 0.1f, 30.0f));
    auto* text3D = text3DNode->CreateComponent<Text3D>();

    // Manually set text in the current language.
    text3D->SetText(l10n->Get("lang"));

    text3D->SetFont(cache->GetResource<Font>("Fonts/Anonymous Pro.ttf"), 30);
    text3D->SetColor(Color::BLACK);
    text3D->SetAlignment(HA_CENTER, VA_BOTTOM);
    text3DNode->SetScale(15);

    auto* renderer = GetSubsystem<Renderer>();
    SharedPtr<Viewport> viewport(new Viewport(context_, scene_, cameraNode_->GetComponent<Camera>()));
    renderer->SetViewport(0, viewport);

    SubscribeToEvent(E_UPDATE, URHO3D_HANDLER(L10n, HandleUpdate));
}

void L10n::HandleUpdate(StringHash eventType, VariantMap& eventData)
{
    using namespace Update;
    float timeStep = eventData[P_TIMESTEP].GetFloat();
    auto* input = GetSubsystem<Input>();
    const float MOUSE_SENSITIVITY = 0.1f;
    IntVector2 mouseMove = input->GetMouseMove();
    yaw_ += MOUSE_SENSITIVITY * mouseMove.x_;
    pitch_ += MOUSE_SENSITIVITY * mouseMove.y_;
    pitch_ = Clamp(pitch_, -90.0f, 90.0f);
    cameraNode_->SetRotation(Quaternion(pitch_, yaw_, 0.0f));
}

void L10n::HandleChangeLangButtonPressed(StringHash eventType, VariantMap& eventData)
{
    auto* l10n = GetSubsystem<Localization>();
    // Languages are numbered in the loading order
    int lang = l10n->GetLanguageIndex();
    lang++;
    if (lang >= l10n->GetNumLanguages())
        lang = 0;
    l10n->SetLanguage(lang);
}

void L10n::HandleQuitButtonPressed(StringHash eventType, VariantMap& eventData)
{
    if (GetPlatform() != "Web")
        engine_->Exit();
}

// You can manually change texts, sprites and other aspects of the game when language is changed
void L10n::HandleChangeLanguage(StringHash eventType, VariantMap& eventData)
{
    auto* l10n = GetSubsystem<Localization>();
    UIElement* uiRoot = GetSubsystem<UI>()->GetRoot();

    auto* windowTitle = uiRoot->GetChildStaticCast<Text>("WindowTitle", true);
    windowTitle->SetText(l10n->Get("title") + " (" + String(l10n->GetLanguageIndex()) + " " + l10n->GetLanguage() + ")");

    auto* buttonText = uiRoot->GetChildStaticCast<Text>("ButtonTextQuit", true);
    buttonText->SetText(l10n->Get("quit"));

    auto* text3D = scene_->GetChild("Text3D")->GetComponent<Text3D>();
    text3D->SetText(l10n->Get("lang"));

    // A text on the button "Press this button" changes automatically
}
