// Copyright (c) 2008-2023 the Urho3D project
// License: MIT

#include "AppState_Benchmark01.h"
#include "AppStateManager.h"

#include <Urho3D/Input/Input.h>
#include <Urho3D/Scene/SceneEvents.h>

#include <Urho3D/DebugNew.h>

using namespace Urho3D;

void AppState_Benchmark01::OnEnter()
{
    assert(!scene_);
    LoadSceneXml("99_Benchmark/Scenes/Benchmark01.xml");

    GetSubsystem<Input>()->SetMouseVisible(false);
    SetupViewport();
    SubscribeToEvent(scene_, E_SCENEUPDATE, URHO3D_HANDLER(AppState_Benchmark01, HandleSceneUpdate));
    fpsCounter_.Clear();
}

void AppState_Benchmark01::OnLeave()
{
    UnsubscribeFromAllEvents();
    DestroyViewport();
    scene_ = nullptr;
}

void AppState_Benchmark01::HandleSceneUpdate(StringHash eventType, VariantMap& eventData)
{
    float timeStep = eventData[SceneUpdate::P_TIMESTEP].GetFloat();

    fpsCounter_.Update(timeStep);
    UpdateCurrentFpsElement();

    if (GetSubsystem<Input>()->GetKeyDown(KEY_ESCAPE))
    {
        GetSubsystem<AppStateManager>()->SetRequiredAppStateId(APPSTATEID_MAINSCREEN);
        return;
    }

    if (fpsCounter_.GetTotalTime() >= 25.f)
        GetSubsystem<AppStateManager>()->SetRequiredAppStateId(APPSTATEID_RESULTSCREEN);
}
