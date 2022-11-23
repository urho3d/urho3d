// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#pragma once

#include "Sample.h"

namespace Urho3D
{

class Button;
class LineEdit;
class Text;
class UIElement;

}

const int SERVER_PORT = 54654;

/// Chat example
/// This sample demonstrates:
///     - Starting up a network server or connecting to it
///     - Implementing simple chat functionality with network messages
class NATPunchtrough : public Sample
{
    URHO3D_OBJECT(NATPunchtrough, Sample);

public:
    /// Construct.
    explicit NATPunchtrough(Context* context);

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
    /// Create the UI.
    void CreateUI();
    /// Subscribe to log message, UI and network events.
    void SubscribeToEvents();
    /// Create a button to the button container.
    Button* CreateButton(const String& text, int width, IntVector2 position);
    /// Create label
    void CreateLabel(const String& text, IntVector2 pos);
    /// Create input field
    LineEdit* CreateLineEdit(const String& placeholder, int width, IntVector2 pos);
    /// Print log message.
    void ShowLogMessage(const String& row);
    /// Save NAT server config
    void HandleSaveNatSettings(StringHash eventType, VariantMap& eventData);
    /// Handle server connection message
    void HandleServerConnected(StringHash eventType, VariantMap& eventData);
    /// Handle server disconnect message
    void HandleServerDisconnected(StringHash eventType, VariantMap& eventData);
    /// Handle failed connection
    void HandleConnectFailed(StringHash eventType, VariantMap& eventData);
    /// Start server
    void HandleStartServer(StringHash eventType, VariantMap& eventData);
    /// Attempt connecting using NAT punchtrough
    void HandleConnect(StringHash eventType, VariantMap& eventData);
    /// Handle NAT master server failed connection
    void HandleNatConnectionFailed(StringHash eventType, VariantMap& eventData);
    /// Handle NAT master server disconnected
    void HandleNatDisconnected(StringHash eventType, VariantMap& eventData);
    /// Handle NAT master server succesfull connection
    void HandleNatConnectionSucceeded(StringHash eventType, VariantMap& eventData);
    /// Handle NAT punchtrough success message
    void HandleNatPunchtroughSucceeded(StringHash eventType, VariantMap& eventData);
    /// Handle failed NAT punchtrough message
    void HandleNatPunchtroughFailed(StringHash eventType, VariantMap& eventData);
    /// Handle client connecting
    void HandleClientConnected(StringHash eventType, VariantMap& eventData);
    /// Handle client disconnecting
    void HandleClientDisconnected(StringHash eventType, VariantMap& eventData);

    /// NAT master server address
    SharedPtr<LineEdit> natServerAddress_;
    /// NAT master server port
    SharedPtr<LineEdit> natServerPort_;
    /// Save NAT settings button
    SharedPtr<Button> saveNatSettingsButton_;
    /// Start server button
    SharedPtr<Button> startServerButton_;
    /// Remote server GUID input field
    SharedPtr<LineEdit> serverGuid_;
    /// Connect button
    SharedPtr<Button> connectButton_;
    /// Log history text element
    SharedPtr<Text> logHistoryText_;
    /// Log messages
    Vector<String> logHistory_;
    /// Created server GUID field
    SharedPtr<LineEdit> guid_;
};
