// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#pragma once

#include "FpsCounter.h"

#include <Urho3D/Scene/Scene.h>

namespace U3D = Urho3D;

inline const U3D::String CURRENT_FPS_STR = "Current FPS";

class AppState_Base : public U3D::Object
{
public:
    URHO3D_OBJECT(AppState_Base, Object);

protected:
    U3D::String name_;

    U3D::SharedPtr<U3D::Scene> scene_;
    void LoadSceneXml(const U3D::String& path);

    FpsCounter fpsCounter_;
    void UpdateCurrentFpsElement();
    
    void SetupViewport();
    void DestroyViewport();

public:
    const U3D::String& GetName() const { return name_; }
    const FpsCounter& GetResult() const { return fpsCounter_; }

    AppState_Base(U3D::Context* context)
        : Object(context)
    {
    }

    void ClearResult() { fpsCounter_.Clear(); }

    virtual void OnEnter()
    {
    }

    virtual void OnLeave()
    {
    }
};

// Note: scene_ and GUI are destroyed and recreated on every state change so as not to affect other benchmarks
