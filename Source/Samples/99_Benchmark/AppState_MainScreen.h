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
