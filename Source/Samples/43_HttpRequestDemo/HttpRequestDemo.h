// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#pragma once

#include "Sample.h"

namespace Urho3D
{
    class HttpRequest;
    class Text;
}

/// Http request example.
/// This example demonstrates:
///     - How to use Http request API
class HttpRequestDemo : public Sample
{
    URHO3D_OBJECT(HttpRequestDemo, Sample);

public:
    /// Construct.
    explicit HttpRequestDemo(Context* context);

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
    /// Create the user interface.
    void CreateUI();
    /// Subscribe to application-wide logic update events.
    void SubscribeToEvents();
    /// Handle the logic update event.
    void HandleUpdate(StringHash eventType, VariantMap& eventData);

    String message_;
    SharedPtr<Text> text_;
    SharedPtr<HttpRequest> httpRequest_;
};
