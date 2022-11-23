// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#pragma once

#include "AppState_Base.h"

class AppState_Benchmark01 : public AppState_Base
{
public:
    URHO3D_OBJECT(AppState_Benchmark01, AppState_Base);

public:
    AppState_Benchmark01(U3D::Context* context)
        : AppState_Base(context)
    {
        name_ = "Static Scene";
    }

    void OnEnter() override;
    void OnLeave() override;

    void HandleSceneUpdate(U3D::StringHash eventType, U3D::VariantMap& eventData);
};
