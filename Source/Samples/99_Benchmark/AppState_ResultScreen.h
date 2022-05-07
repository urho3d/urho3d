// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#pragma once

#include "AppState_Base.h"

class AppState_ResultScreen : public AppState_Base
{
public:
    URHO3D_OBJECT(AppState_ResultScreen, AppState_Base);

public:
    AppState_ResultScreen(U3D::Context* context)
        : AppState_Base(context)
    {
        name_ = "Result Screen";
    }

    void OnEnter() override;
    void OnLeave() override;

    void HandleSceneUpdate(U3D::StringHash eventType, U3D::VariantMap& eventData);

    void ShowResultWindow();
    void DestroyResultWindow();
    void HandleResultOkButtonPressed(U3D::StringHash eventType, U3D::VariantMap& eventData);
};
