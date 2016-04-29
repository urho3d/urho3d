//
// Copyright (c) 2008-2016 the Urho3D project.
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
    Chat(Context* context);

    /// Setup after engine initialization and before running the main loop.
    virtual void Start();

protected:
    /// Return XML patch instructions for screen joystick layout for a specific sample app, if any.
    virtual String GetScreenJoystickPatchString() const { return
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
