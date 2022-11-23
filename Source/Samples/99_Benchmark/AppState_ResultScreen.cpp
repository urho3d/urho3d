// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#include "AppState_ResultScreen.h"
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

static const U3D::String RESULT_WINDOW_STR = "Result Window";

void AppState_ResultScreen::OnEnter()
{
    assert(!scene_);
    LoadSceneXml("99_Benchmark/Scenes/ResultScreen.xml");

    GetSubsystem<Input>()->SetMouseVisible(true);
    SetupViewport();
    SubscribeToEvent(scene_, E_SCENEUPDATE, URHO3D_HANDLER(AppState_ResultScreen, HandleSceneUpdate));
    fpsCounter_.Clear();
    ShowResultWindow();
}

void AppState_ResultScreen::OnLeave()
{
    DestroyViewport();
    DestroyResultWindow();
    scene_ = nullptr;
}

void AppState_ResultScreen::HandleSceneUpdate(StringHash eventType, VariantMap& eventData)
{
    float timeStep = eventData[SceneUpdate::P_TIMESTEP].GetFloat();

    fpsCounter_.Update(timeStep);
    UpdateCurrentFpsElement();

    Input* input = GetSubsystem<Input>();

    if (input->GetKeyDown(KEY_ESCAPE) || input->GetKeyDown(KEY_RETURN) || input->GetKeyDown(KEY_KP_ENTER))
        GetSubsystem<AppStateManager>()->SetRequiredAppStateId(APPSTATEID_MAINSCREEN);
}

void AppState_ResultScreen::ShowResultWindow()
{
    UIElement* root = GetSubsystem<UI>()->GetRoot();

    Window* window = root->CreateChild<Window>(RESULT_WINDOW_STR);
    window->SetStyleAuto();
    window->SetLayout(LM_VERTICAL, 6, IntRect(6, 6, 6, 6));
    window->SetAlignment(HA_CENTER, VA_CENTER);

    Text* windowTitle = window->CreateChild<Text>();
    windowTitle->SetStyleAuto();
    windowTitle->SetText("Result");

    AppStateManager* appStateManager = GetSubsystem<AppStateManager>();
    AppStateId prevAppStateId = appStateManager->GetPreviousAppStateId();
    const String& benchmarkName = appStateManager->GetName(prevAppStateId);
    const FpsCounter& benchmarkResult = appStateManager->GetResult(prevAppStateId);

    Text* resultText = window->CreateChild<Text>();
    resultText->SetStyleAuto();
    resultText->SetText(benchmarkName + ": " + String(benchmarkResult.GetResultFps()) + " FPS (min: " +
        String(benchmarkResult.GetResultMinFps()) + ", max: " + String(benchmarkResult.GetResultMaxFps()) + ")");

    Button* okButton = window->CreateChild<Button>();
    okButton->SetStyleAuto();
    okButton->SetFixedHeight(24);

    Text* buttonText = okButton->CreateChild<Text>();
    buttonText->SetStyleAuto();
    buttonText->SetText("Ok");
    buttonText->SetAlignment(HA_CENTER, VA_CENTER);

    SubscribeToEvent(okButton, E_RELEASED, URHO3D_HANDLER(AppState_ResultScreen, HandleResultOkButtonPressed));
}

void AppState_ResultScreen::DestroyResultWindow()
{
    UIElement* root = GetSubsystem<UI>()->GetRoot();
    UIElement* window = root->GetChild(RESULT_WINDOW_STR);
    window->Remove();
}

void AppState_ResultScreen::HandleResultOkButtonPressed(StringHash eventType, VariantMap& eventData)
{
    GetSubsystem<AppStateManager>()->SetRequiredAppStateId(APPSTATEID_MAINSCREEN);
}
