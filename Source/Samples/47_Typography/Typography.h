// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#pragma once

#include "Sample.h"

/// Text rendering example.
/// Displays text at various sizes, with checkboxes to change the rendering parameters.
class Typography : public Sample
{
    URHO3D_OBJECT(Typography, Sample);

public:
    /// Construct.
    explicit Typography(Context* context);

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
    SharedPtr<UIElement> uielement_;

    void CreateText();
    SharedPtr<CheckBox> CreateCheckbox(const String& label, EventHandler* handler);
    SharedPtr<DropDownList> CreateMenu(const String& label, const char** items, EventHandler* handler);

    void HandleWhiteBackground(StringHash eventType, VariantMap& eventData);
    void HandleSRGB(StringHash eventType, VariantMap& eventData);
    void HandleForceAutoHint(StringHash eventType, VariantMap& eventData);
    void HandleFontHintLevel(StringHash eventType, VariantMap& eventData);
    void HandleFontSubpixel(StringHash eventType, VariantMap& eventData);
    void HandleFontOversampling(StringHash eventType, VariantMap& eventData);
};
