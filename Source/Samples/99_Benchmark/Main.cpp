// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#include "AppStateManager.h"

#include <Urho3D/Core/CoreEvents.h>
#include <Urho3D/Engine/Application.h>
#include <Urho3D/Engine/EngineDefs.h>
#include <Urho3D/Input/Input.h>
#include <Urho3D/IO/FileSystem.h>
#include <Urho3D/Resource/ResourceCache.h>
#include <Urho3D/UI/Text.h>
#include <Urho3D/UI/UI.h>

using namespace Urho3D;

class App : public Application
{
    URHO3D_OBJECT(App, Application);

public:
    App(Context* context)
        : Application(context)
    {
        // The first handler for the first event in each frame.
        // To prevent a crash, we can only change the current scene at the start of a frame,
        // before any scene events are processed
        SubscribeToEvent(E_BEGINFRAME, URHO3D_HANDLER(App, ApplyAppState));
    }

    void Setup() override
    {
        engineParameters_[EP_WINDOW_TITLE] = "Urho3D Benchmark";
        engineParameters_[EP_LOG_NAME] = GetSubsystem<FileSystem>()->GetAppPreferencesDir("urho3d", "logs") + "99_Benchmark.log";
        engineParameters_[EP_FULL_SCREEN] = false;
        engineParameters_[EP_WINDOW_WIDTH] = 960;
        engineParameters_[EP_WINDOW_HEIGHT] = 720;
        engineParameters_[EP_FRAME_LIMITER] = false;
    }

    // This elements can be used anywhere in the program
    void CreateCurrentFpsUiElement()
    {
        UIElement* root = GetSubsystem<UI>()->GetRoot();
        root->SetDefaultStyle(GetSubsystem<ResourceCache>()->GetResource<XMLFile>("UI/DefaultStyle.xml"));

        Text* fpsElement = root->CreateChild<Text>(CURRENT_FPS_STR);
        fpsElement->SetStyleAuto();
        fpsElement->SetTextEffect(TE_SHADOW);
        fpsElement->SetPosition(10, 10);
        fpsElement->SetText("FPS");
    }

    void Start() override
    {
        context_->RegisterSubsystem(new AppStateManager(context_));
        AppStateManager* appStateManager = context_->GetSubsystem<AppStateManager>();
        appStateManager->SetRequiredAppStateId(APPSTATEID_MAINSCREEN);

        GetSubsystem<Input>()->SetToggleFullscreen(false); // Block Alt+Enter

        CreateCurrentFpsUiElement();
    }

    void ApplyAppState(StringHash eventType, VariantMap& eventData)
    {
        context_->GetSubsystem<AppStateManager>()->Apply();
    }
};

URHO3D_DEFINE_APPLICATION_MAIN(App);
