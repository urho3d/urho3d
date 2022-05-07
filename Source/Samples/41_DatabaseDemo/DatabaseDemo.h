// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#pragma once

#include "Sample.h"

/// Database demo. This sample demonstrates how to use database subsystem to connect to a database and execute adhoc SQL statements.
class DatabaseDemo : public Sample
{
    URHO3D_OBJECT(DatabaseDemo, Sample)

public:
    /// Construct.
    explicit DatabaseDemo(Context* context);
    /// Destruct.
    ~DatabaseDemo() override;

    /// Setup after engine initialization and before running the main loop.
    void Start() override;

protected:
    /// Return XML patch instructions for screen joystick layout for a specific sample app, if any.
    String GetScreenJoystickPatchString() const override { return
        "<patch>"
        "    <add sel=\"/element/element[./attribute[@name='Name' and @value='Button2']]\">"
        "        <attribute name=\"Is Visible\" value=\"false\" />"
        "    </add>"
        "    <add sel=\"/element/element[./attribute[@name='Name' and @value='Hat0']]\">"
        "        <attribute name=\"Is Visible\" value=\"false\" />"
        "    </add>"
        "</patch>";
    }

private:
    /// Handle console command event.
    void HandleConsoleCommand(StringHash eventType, VariantMap& eventData);
    /// Handle frame update event.
    void HandleUpdate(StringHash eventType, VariantMap& eventData);
    /// Handle ESC key down event to quit the engine.
    void HandleEscKeyDown(StringHash eventType, VariantMap& eventData);
    /// Handle Database cursor event.
    void HandleDbCursor(StringHash eventType, VariantMap& eventData);
    /// Handle user input either from the engine console or standard input.
    void HandleInput(const String& input);
    /// Print text to the engine console and standard output.
    void Print(const String& output);

    /// Managed database connection object (owned by Database subsystem).
    DbConnection* connection_;
    /// Internal row counter.
    unsigned row_;
    /// Maximum rows to be printed out.
    unsigned maxRows_;
};
