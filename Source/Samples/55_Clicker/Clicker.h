// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#pragma once

#include <Urho3D/Math/BigInt.h>

#include "Sample.h"

class Clicker : public Sample
{
    URHO3D_OBJECT(Clicker, Sample);

public:
    /// Construct.
    explicit Clicker(Context* context);

    /// Setup after engine initialization and before running the main loop.
    void Start() override;

protected:
    /// Return XML patch instructions for screen joystick layout for a specific sample app, if any.
    String GetScreenJoystickPatchString() const override {
        return
            "<patch>"
            "    <add sel=\"/element/element[./attribute[@name='Name' and @value='Hat0']]\">"
            "        <attribute name=\"Is Visible\" value=\"false\" />"
            "    </add>"
            "</patch>";
    }

private:
    /// Current score.
    BigInt score_;

    /// Number of points received per click.
    BigInt power_{1};

    /// Delay after click.
    float clickDelay_ = 0.f;

    /// Construct UI elements.
    void CreateUI();
    
    /// Subscribe to application-wide logic update events.
    void SubscribeToEvents();
    
    /// Handle the logic update event.
    void HandleUpdate(StringHash eventType, VariantMap& eventData);

    /// Handle the mouse click event.
    void HandleMouseButtonDown(StringHash eventType, VariantMap& eventData);
};
