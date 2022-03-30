//
// Copyright (c) 2008-2022 the Urho3D project.
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

#include "AppState_MainScreen.h"
#include "AppStateManager.h"

#include <Urho3D/Input/Input.h>
#include <Urho3D/Scene/SceneEvents.h>
#include <Urho3D/UI/Button.h>
#include <Urho3D/UI/Text.h>
#include <Urho3D/UI/UI.h>
#include <Urho3D/UI/UIEvents.h>
#include <Urho3D/UI/Window.h>

#include <Urho3D/DebugNew.h>

using namespace Urho3D;

static const String MAIN_SCREEN_WINDOW_STR = "Main Screen Window";
static const String BENCHMARK_01_STR = "Benchmark 01";
static const String BENCHMARK_02_STR = "Benchmark 02";
static const String BENCHMARK_03_STR = "Benchmark 03";

void AppState_MainScreen::HandleButtonPressed(StringHash eventType, VariantMap& eventData)
{
    Button* pressedButton = static_cast<Button*>(eventData["Element"].GetPtr());
    AppStateManager* appStateManager = GetSubsystem<AppStateManager>();
    
    if (pressedButton->GetName() == BENCHMARK_01_STR)
        appStateManager->SetRequiredAppStateId(APPSTATEID_BENCHMARK01);
    else if (pressedButton->GetName() == BENCHMARK_02_STR)
        appStateManager->SetRequiredAppStateId(APPSTATEID_BENCHMARK02);
    else if (pressedButton->GetName() == BENCHMARK_03_STR)
        appStateManager->SetRequiredAppStateId(APPSTATEID_BENCHMARK03);
}

void AppState_MainScreen::CreateButton(const String& name, const String& text, Window& parent)
{
    Button* button = parent.CreateChild<Button>(name);
    button->SetStyleAuto();
    button->SetFixedHeight(24);

    Text* buttonText = button->CreateChild<Text>();
    buttonText->SetStyleAuto();
    buttonText->SetText(text);
    buttonText->SetAlignment(HA_CENTER, VA_CENTER);

    SubscribeToEvent(button, E_RELEASED, URHO3D_HANDLER(AppState_MainScreen, HandleButtonPressed));
}

void AppState_MainScreen::CreateGui()
{
    UIElement* root = GetSubsystem<UI>()->GetRoot();

    Window* window = root->CreateChild<Window>(MAIN_SCREEN_WINDOW_STR);
    window->SetStyleAuto();
    window->SetMinWidth(384);
    window->SetLayout(LM_VERTICAL, 6, IntRect(6, 6, 6, 6));
    window->SetPosition(10, 34);

    Text* windowTitle = window->CreateChild<Text>();
    windowTitle->SetStyleAuto();
    windowTitle->SetText("Benchmark list");

    AppStateManager* appStateManager = GetSubsystem<AppStateManager>();

    CreateButton(BENCHMARK_01_STR, appStateManager->GetName(APPSTATEID_BENCHMARK01), *window);
    CreateButton(BENCHMARK_02_STR, appStateManager->GetName(APPSTATEID_BENCHMARK02), *window);
    CreateButton(BENCHMARK_03_STR, appStateManager->GetName(APPSTATEID_BENCHMARK03), *window);
}

void AppState_MainScreen::DestroyGui()
{
    UIElement* root = GetSubsystem<UI>()->GetRoot();
    Window* window = root->GetChildStaticCast<Window>(MAIN_SCREEN_WINDOW_STR);
    window->Remove();
}

void AppState_MainScreen::OnEnter()
{
    assert(!scene_);
    LoadSceneXml("99_Benchmark/Scenes/MainScreen.xml");

    CreateGui();
    SetupViewport();
    GetSubsystem<Input>()->SetMouseVisible(true);
    SubscribeToEvent(scene_, E_SCENEUPDATE, URHO3D_HANDLER(AppState_MainScreen, HandleSceneUpdate));
    fpsCounter_.Clear();
}

void AppState_MainScreen::OnLeave()
{
    DestroyViewport();
    DestroyGui();
    scene_ = nullptr;
}

void AppState_MainScreen::HandleSceneUpdate(StringHash eventType, VariantMap& eventData)
{
    float timeStep = eventData[SceneUpdate::P_TIMESTEP].GetFloat();

    fpsCounter_.Update(timeStep);
    UpdateCurrentFpsElement();
}
