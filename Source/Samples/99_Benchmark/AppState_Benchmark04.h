// Copyright (c) 2008-2023 the Urho3D project
// License: MIT

#pragma once

#include "AppState_Base.h"

#include <Urho3D/Graphics/SpriteBatch.h>

// Бенчмарк для SpriteBatch
class AppState_Benchmark04 : public AppState_Base
{
public:
    URHO3D_OBJECT(AppState_Benchmark04, AppState_Base);

public:
    AppState_Benchmark04(U3D::Context* context)
        : AppState_Base(context)
    {
        name_ = "SpriteBatch";
    }

    void OnEnter() override;
    void OnLeave() override;

    Urho3D::SharedPtr<Urho3D::SpriteBatch> spriteBatch_;
    float angle_ = 0.f;
    float scale_ = 0.f;

    void HandleEndAllViewsRender(U3D::StringHash eventType, U3D::VariantMap& eventData);
};
