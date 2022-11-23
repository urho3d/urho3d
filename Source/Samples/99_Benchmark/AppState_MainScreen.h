// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#pragma once

#include "AppState_Base.h"

namespace Urho3D
{
    class Window;
}

class AppState_MainScreen : public AppState_Base
{
public:
    URHO3D_OBJECT(AppState_MainScreen, AppState_Base);

private:
    void HandleButtonPressed(U3D::StringHash eventType, U3D::VariantMap& eventData);
    void CreateButton(const U3D::String& name, const U3D::String& text, U3D::Window& parent);
    void CreateGui();
    void DestroyGui();

public:
    AppState_MainScreen(U3D::Context* context)
        : AppState_Base(context)
    {
        name_ = "Main Screen";
    }

    void OnEnter() override;
    void OnLeave() override;

    void HandleSceneUpdate(U3D::StringHash eventType, U3D::VariantMap& eventData);
};
