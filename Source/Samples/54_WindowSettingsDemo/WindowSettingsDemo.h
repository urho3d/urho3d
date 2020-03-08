//
// Copyright (c) 2008-2020 the Urho3D project.
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

#include "Sample.h"

namespace Urho3D
{

class Window;
class DropDownList;
class CheckBox;

}

/// Demo application for dynamic window settings change.
class WindowSettingsDemo : public Sample
{
    URHO3D_OBJECT(WindowSettingsDemo, Sample);

public:
    /// Construct.
    explicit WindowSettingsDemo(Context* context);

    /// Setup after engine initialization and before running the main loop.
    void Start() override;

protected:
    /// Return XML patch instructions for screen joystick layout for a specific sample app, if any.
    String GetScreenJoystickPatchString() const override { return
        "<patch>"
        "    <add sel=\"/element/element[./attribute[@name='Name' and @value='Hat0']]\">"
        "        <attribute name=\"Is Visible\" value=\"false\" />"
        "    </add>"
        "</patch>";
    }

private:
    /// Construct the scene content.
    void CreateScene();
    /// Create window with settings.
    void InitSettings();
    /// Synchronize settings with current state of the engine.
    void SynchronizeSettings();

    /// The Window.
    Window* window_{};
    /// The UI's root UIElement.
    UIElement* uiRoot_{};

    /// Monitor control.
    DropDownList* monitorControl_{};
    /// Resolution control.
    DropDownList* resolutionControl_{};
    /// Fullscreen control.
    CheckBox* fullscreenControl_{};
    /// Borderless flag control.
    CheckBox* borderlessControl_{};
    /// Resizable flag control.
    CheckBox* resizableControl_{};
    /// V-sync flag control.
    CheckBox* vsyncControl_{};
    /// MSAA control.
    DropDownList* multiSampleControl_{};
};


