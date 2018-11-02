//
// Copyright (c) 2008-2018 the Urho3D project.
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

const int SERVER_PORT = 54654;

/// Chat example
/// This sample demonstrates:
///     - Starting up a network server or connecting to it
///     - Implementing simple chat functionality with network messages
class P2PMultiplayer : public Sample
{
    URHO3D_OBJECT(P2PMultiplayer, Sample);

public:
    /// Construct.
    explicit P2PMultiplayer(Context* context);

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

    //
    void Init();

    void CreateScene();

    /// Set up viewport.
    void SetupViewport();

    /// Handle a client connecting to the server.
    void HandleClientConnected(StringHash eventType, VariantMap& eventData);
    /// Handle a client disconnecting from the server.
    void HandleClientDisconnected(StringHash eventType, VariantMap& eventData);

    /// Create a button to the button container.
    Button* CreateButton(const String& text, int width, IntVector2 position);
    LineEdit* CreateLineEdit(const String& placeholder, int width, IntVector2 pos);
//    /// Create label
    Text* CreateLabel(const String& text, IntVector2 pos);
//
//    /// Handle found LAN server
    void HandleServerConnected(StringHash eventType, VariantMap& eventData);
//    /// Start server
    void HandleUpdate(StringHash eventType, VariantMap& eventData);

    void HandleStartP2PSession(StringHash eventType, VariantMap& eventData);
    void HandleJoinP2PSession(StringHash eventType, VariantMap& eventData);

    void HandleReady(StringHash eventType, VariantMap& eventData);

    void HandleResetHost(StringHash eventType, VariantMap& eventData);
    void HandleAllReadyChanged(StringHash eventType, VariantMap& eventData);

    void HandleSessionStarted(StringHash eventType, VariantMap& eventData);

    void HandleDisconnect(StringHash eventType, VariantMap& eventData);

    void CreatePlayerNode(Connection* connection);
    void DestroyPlayerNode(Connection* connection);

    Timer timer_;
//    /// Stop server
//	void HandleStopServer(StringHash eventType, VariantMap& eventData);
//	/// Start network discovery
//	void HandleDoNetworkDiscovery(StringHash eventType, VariantMap& eventData);
//    /// Start server
//    SharedPtr<Button> startServer_;
    /// Start P2P Session
    SharedPtr<Button> startSession_;
    /// Join P2P Session
    SharedPtr<Button> joinSession_;
    SharedPtr<Button> readyButton_;
    SharedPtr<Button> resetHostButton_;
    SharedPtr<Button> disconnect_;
    SharedPtr<LineEdit> guid_;
//    /// Found server list
	SharedPtr<Text> clientCount_;
    SharedPtr<Text> roleTitle_;
    SharedPtr<Text> myGuid_;
    SharedPtr<Text> hostGuid_;
    SharedPtr<RigidBody> body_;
    HashMap<Connection*, WeakPtr<Node>> playerNodes_;
    String message_;
    SharedPtr<HttpRequest> httpRequest_;

    SharedPtr<Node> ball_;
    bool _allReady;
};
