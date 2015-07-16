//
// Copyright (c) 2008-2015 the Urho3D project.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

#include <Urho3D/Urho3D.h>

#include <Urho3D/Resource/Localization.h>
#include <Urho3D/Core/CoreEvents.h>
#include <Urho3D/UI/Window.h>
#include <Urho3D/UI/Text.h>
#include <Urho3D/UI/Button.h>
#include <Urho3D/UI/Font.h>
#include <Urho3D/Graphics/StaticModel.h>
#include <Urho3D/Graphics/Material.h>
#include <Urho3D/Graphics/Model.h>
#include <Urho3D/Graphics/Octree.h>
#include <Urho3D/UI/Text3D.h>
#include <Urho3D/UI/UIEvents.h>
#include <Urho3D/Graphics/Zone.h>

#include "L10n.h"

#include <Urho3D/DebugNew.h>

DEFINE_APPLICATION_MAIN(L10n)

L10n::L10n(Context* context) :
    Sample(context)
{
}

void L10n::Start()
{
    // Execute base class startup
    Sample::Start();

    // Enable OS cursor
    GetSubsystem<Input>()->SetMouseVisible(true);

    // Load strings
    Localization* l10n = GetSubsystem<Localization>();
    l10n->LoadJSONFile("StringsEnRu.json");
    l10n->LoadJSONFile("StringsDe.json");
    SubscribeToEvent(E_CHANGELANGUAGE, HANDLER(L10n, HandleChangeLanguage));

    CreateScene();
    CreateGUI();

    SubscribeToEvent(E_UPDATE, HANDLER(L10n, HandleUpdate));
}

void L10n::CreateGUI()
{
    Localization* l10n = GetSubsystem<Localization>();
    ResourceCache* cache = GetSubsystem<ResourceCache>();

    UIElement* root = GetSubsystem<UI>()->GetRoot();
    // Load the style sheet from xml
    root->SetDefaultStyle(cache->GetResource<XMLFile>("UI/DefaultStyle.xml"));

    // Create the Window and add it to the UI's root node
    Window* window = new Window(context_);
    root->AddChild(window);

    // Set Window size and layout settings
    window->SetMinSize(384, 192);
    window->SetLayout(LM_VERTICAL, 6, IntRect(6, 6, 6, 6));
    window->SetAlignment(HA_CENTER, VA_CENTER);
    window->SetName("Window");

    // Create Window 'titlebar' container
    UIElement* titleBar = new UIElement(context_);
    titleBar->SetMinSize(0, 24);
    titleBar->SetVerticalAlignment(VA_TOP);
    titleBar->SetLayoutMode(LM_HORIZONTAL);

    // Create the Window title Text
    Text* windowTitle = new Text(context_);
    windowTitle->SetName("WindowTitle");
    windowTitle->SetText(l10n->Get("title") + " (" + l10n->GetLanguage() + ")");

    // Add text to the title bar
    titleBar->AddChild(windowTitle);

    // Add the title bar to the Window
    window->AddChild(titleBar);

    // Apply styles
    window->SetStyleAuto();
    windowTitle->SetStyleAuto();


    // Create buttons
    Button* b = new Button(context_);
    window->AddChild(b);
    b->SetStyle("Button");
    b->SetMinHeight(24);
    Text* t = b->CreateChild<Text>("ButtonTextLanguage");
    t->SetAlignment(HA_CENTER, VA_CENTER);
    t->SetStyle("Text");
    t->SetAutoLocalizable(true);
    t->SetText("lang");
    SubscribeToEvent(b, E_RELEASED, HANDLER(L10n, HandleLangButtonPressed));

    b = new Button(context_);
    window->AddChild(b);
    b->SetStyle("Button");
    b->SetMinHeight(24);
    t = b->CreateChild<Text>("ButtonTextQuit");
    t->SetAlignment(HA_CENTER, VA_CENTER);
    t->SetStyle("Text");
    t->SetText(l10n->Get("quit"));
    SubscribeToEvent(b, E_RELEASED, HANDLER(L10n, HandleQuitButtonPressed));

}

void L10n::CreateScene()
{
    ResourceCache* cache = GetSubsystem<ResourceCache>();
    Localization* l10n = GetSubsystem<Localization>();
    scene_ = new Scene(context_);
    scene_->CreateComponent<Octree>();
    
    Node* zoneNode = scene_->CreateChild("Zone");
    Zone* zone = zoneNode->CreateComponent<Zone>();
    zone->SetBoundingBox(BoundingBox(-1000.0f, 1000.0f));
    zone->SetAmbientColor(Color(0.15f, 0.15f, 0.15f));
    zone->SetFogColor(Color(0.5f, 0.5f, 0.7f));
    zone->SetFogStart(100.0f);
    zone->SetFogEnd(300.0f);

    Node* planeNode = scene_->CreateChild("Plane");
    planeNode->SetScale(Vector3(200.0f, 1.0f, 200.0f));
    StaticModel* planeObject = planeNode->CreateComponent<StaticModel>();
    planeObject->SetModel(cache->GetResource<Model>("Models/Plane.mdl"));
    planeObject->SetMaterial(cache->GetResource<Material>("Materials/StoneTiled.xml"));

    Node* lightNode = scene_->CreateChild("DirectionalLight");
    lightNode->SetDirection(Vector3(0.6f, -1.0f, 0.8f)); // The direction vector does not need to be normalized
    Light* light = lightNode->CreateComponent<Light>();
    light->SetLightType(LIGHT_DIRECTIONAL);

    cameraNode_ = scene_->CreateChild("Camera");
    cameraNode_->CreateComponent<Camera>();

    // Set an initial position for the camera scene node above the plane
    cameraNode_->SetPosition(Vector3(0.0f, 10.0f, -30.0f));

    Node* text3DNode = scene_->CreateChild("Text3D");
    text3DNode->SetPosition(Vector3(0.0f, 0.0f, 30.0f));
    Text3D* text3D = text3DNode->CreateComponent<Text3D>();
    text3D->SetText(l10n->Get("long text"));
    text3D->SetFont(cache->GetResource<Font>("Fonts/Anonymous Pro.ttf"), 30);
    text3D->SetColor(Color::BLACK);
    text3D->SetAlignment(HA_CENTER, VA_BOTTOM);
    text3DNode->SetScale(15);

    Renderer* renderer = GetSubsystem<Renderer>();
    SharedPtr<Viewport> viewport(new Viewport(context_, scene_, cameraNode_->GetComponent<Camera>()));
    renderer->SetViewport(0, viewport);
}

void L10n::HandleUpdate(StringHash eventType, VariantMap& eventData)
{
    using namespace Update;
    float timeStep = eventData[P_TIMESTEP].GetFloat();
    MoveCamera(timeStep);
}

void L10n::MoveCamera(float timeStep)
{
    Input* input = GetSubsystem<Input>();

    const float MOUSE_SENSITIVITY = 0.1f;

    // Use this frame's mouse motion to adjust camera node yaw and pitch. Clamp the pitch between -90 and 90 degrees
    IntVector2 mouseMove = input->GetMouseMove();
    yaw_ += MOUSE_SENSITIVITY * mouseMove.x_;
    pitch_ += MOUSE_SENSITIVITY * mouseMove.y_;
    pitch_ = Clamp(pitch_, -90.0f, 90.0f);

    // Construct new orientation for the camera scene node from yaw and pitch. Roll is fixed to zero
    cameraNode_->SetRotation(Quaternion(pitch_, yaw_, 0.0f));
}

void L10n::HandleLangButtonPressed(StringHash eventType, VariantMap& eventData)
{
    Localization* l10n = GetSubsystem<Localization>();
    unsigned lang = l10n->GetLanguageIndex();
    lang++;
    if (lang >= l10n->GetNumLanguages())
        lang = 0;
    l10n->SetLanguage(lang);
}

void L10n::HandleQuitButtonPressed(StringHash eventType, VariantMap& eventData)
{
    engine_->Exit();
}

void L10n::HandleChangeLanguage(StringHash eventType, VariantMap& eventData)
{
    Localization* l10n = GetSubsystem<Localization>();
    ResourceCache* cache = GetSubsystem<ResourceCache>();
    UIElement* uiRoot = GetSubsystem<UI>()->GetRoot();
    Text* windowTitle = static_cast<Text*>(uiRoot->GetChild("WindowTitle", true));
    windowTitle->SetText(l10n->Get("title") + " (" + l10n->GetLanguage() + ")");
    Text* buttonText = static_cast<Text*>(uiRoot->GetChild("ButtonTextQuit", true));
    buttonText->SetText(l10n->Get("quit"));
    Text3D* text3D = scene_->GetChild("Text3D")->GetComponent<Text3D>();
    text3D->SetText(l10n->Get("long text"));
}
