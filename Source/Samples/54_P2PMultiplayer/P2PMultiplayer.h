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
#include "Peer.h"
#include <Urho3D/UI/Window.h>

namespace Urho3D
{

class Button;
class LineEdit;
class Text;
class UIElement;
class RigidBody;
class HttpRequest;

}

enum GameState {
    IN_MENU,
    IN_LOBBY,
    IN_GAME
};

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

    void CreatePlayerListWindow();

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

    void HandleUpdate(StringHash eventType, VariantMap& eventData);

    void StartSession();
    void JoinSession(const String& guid);

    void HandleServerFull(StringHash eventType, VariantMap& eventData);

    void HandleAllReadyChanged(StringHash eventType, VariantMap& eventData);

    void HandleSessionStarted(StringHash eventType, VariantMap& eventData);
    void HandleSessionJoined(StringHash eventType, VariantMap& eventData);

    void HandleSearchSession(StringHash eventType, VariantMap& eventData);

    void HandleGameState(StringHash eventType, VariantMap& eventData);

    void UpdateClientObjects();

    void HandleNewHost(StringHash eventType, VariantMap& eventData);

    void HandleBanned(StringHash eventType, VariantMap& eventData);

    void HandleClientIdentity(StringHash eventType, VariantMap& eventData);

    void CreatePlayerNode(Connection* connection);
    void DestroyPlayerNode(Connection* connection);

    void SetStatusMessage(const String& message);

    void InitPlayers();

    void UpdatePlayerList();

    Timer timer_;
    SharedPtr<Button> searchGame_;
    SharedPtr<LineEdit> nickname_;
//    /// Found server list
	SharedPtr<Text> clientCount_;
    SharedPtr<Text> info_;
    SharedPtr<Text> statusMessage_;
    String message_;

    SharedPtr<HttpRequest> httpRequest_;

    bool _allReady{};
    Controls controls_;
    SharedPtr<Window> playerList_;

    HashMap<Connection*, SharedPtr<Peer>> peers_;

    GameState gameState_;

    bool startGame_{};
    Timer startCountdown_;

    List<String> messages_;
};
