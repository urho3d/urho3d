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
