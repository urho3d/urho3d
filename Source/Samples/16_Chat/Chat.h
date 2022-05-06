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

/// Chat example
/// This sample demonstrates:
///     - Starting up a network server or connecting to it
///     - Implementing simple chat functionality with network messages
class Chat : public Sample
{
    URHO3D_OBJECT(Chat, Sample);

public:
    /// Construct.
    explicit Chat(Context* context);

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
    Button* CreateButton(const String& text, int width);
    /// Print chat text.
    void ShowChatText(const String& row);
    /// Update visibility of buttons according to connection and server status.
    void UpdateButtons();
    /// Handle log message event; pipe it also to the chat display.
    void HandleLogMessage(StringHash eventType, VariantMap& eventData);
    /// Handle pressing the send button.
    void HandleSend(StringHash eventType, VariantMap& eventData);
    /// Handle pressing the connect button.
    void HandleConnect(StringHash eventType, VariantMap& eventData);
    /// Handle pressing the disconnect button.
    void HandleDisconnect(StringHash eventType, VariantMap& eventData);
    /// Handle pressing the start server button.
    void HandleStartServer(StringHash eventType, VariantMap& eventData);
    /// Handle an incoming network message.
    void HandleNetworkMessage(StringHash eventType, VariantMap& eventData);
    /// Handle connection status change (just update the buttons that should be shown.)
    void HandleConnectionStatus(StringHash eventType, VariantMap& eventData);
    /// Strings printed so far.
    Vector<String> chatHistory_;
    /// Chat text element.
    SharedPtr<Text> chatHistoryText_;
    /// Button container element.
    SharedPtr<UIElement> buttonContainer_;
    /// Server address / chat message line editor element.
    SharedPtr<LineEdit> textEdit_;
    /// Send button.
    SharedPtr<Button> sendButton_;
    /// Connect button.
    SharedPtr<Button> connectButton_;
    /// Disconnect button.
    SharedPtr<Button> disconnectButton_;
    /// Start server button.
    SharedPtr<Button> startServerButton_;
};
