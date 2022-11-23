// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

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


