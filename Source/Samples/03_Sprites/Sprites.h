// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#pragma once

#include "Sample.h"

/// Moving sprites example.
/// This sample demonstrates:
///     - Adding Sprite elements to the UI
///     - Storing custom data (sprite velocity) inside UI elements
///     - Handling frame update events in which the sprites are moved
class Sprites : public Sample
{
    // Enable type information.
    URHO3D_OBJECT(Sprites, Sample);

public:
    /// Construct.
    explicit Sprites(Context* context);

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
    /// Construct the sprites.
    void CreateSprites();
    /// Move the sprites using the delta time step given.
    void MoveSprites(float timeStep);
    /// Subscribe to application-wide logic update events.
    void SubscribeToEvents();
    /// Handle the logic update event.
    void HandleUpdate(StringHash eventType, VariantMap& eventData);

    /// Vector to store the sprites for iterating through them.
    Vector<SharedPtr<Sprite> > sprites_;
};
