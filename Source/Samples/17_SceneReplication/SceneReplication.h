//
// Copyright (c) 2008-2015 the Urho3D project.
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
class Connection;
class Scene;
class Text;
class UIElement;

}

/// Scene network replication example.
/// This sample demonstrates:
///     - Creating a scene in which network clients can join
///     - Giving each client an object to control and sending the controls from the clients to the server
///       where the authoritative simulation happens
///     - Controlling a physics object's movement by applying forces
class SceneReplication : public Sample
{
    URHO3D_OBJECT(SceneReplication, Sample);

public:
    /// Construct.
    SceneReplication(Context* context);

    /// Setup after engine initialization and before running the main loop.
    virtual void Start();

protected:
    /// Return XML patch instructions for screen joystick layout for a specific sample app, if any.
    virtual String GetScreenJoystickPatchString() const { return
        "<patch>"
        "    <add sel=\"/element/element[./attribute[@name='Name' and @value='Hat0']]\">"
        "        <attribute name=\"Is Visible\" value=\"false\" />"
        "    </add>"
        "</patch>";
    }

private:
    /// Construct the scene content.
    void CreateScene();
    /// Construct instruction text and the login / start server UI.
    void CreateUI();
    /// Set up viewport.
    void SetupViewport();
    /// Subscribe to update, UI and network events.
    void SubscribeToEvents();
    /// Create a button to the button container.
    Button* CreateButton(const String& text, int width);
    /// Update visibility of buttons according to connection and server status.
    void UpdateButtons();
    /// Create a controllable ball object and return its scene node.
    Node* CreateControllableObject();
    /// Read input and move the camera.
    void MoveCamera();
    /// Handle the physics world pre-step event.
    void HandlePhysicsPreStep(StringHash eventType, VariantMap& eventData);
    /// Handle the logic post-update event.
    void HandlePostUpdate(StringHash eventType, VariantMap& eventData);
    /// Handle pressing the connect button.
    void HandleConnect(StringHash eventType, VariantMap& eventData);
    /// Handle pressing the disconnect button.
    void HandleDisconnect(StringHash eventType, VariantMap& eventData);
    /// Handle pressing the start server button.
    void HandleStartServer(StringHash eventType, VariantMap& eventData);
    /// Handle connection status change (just update the buttons that should be shown.)
    void HandleConnectionStatus(StringHash eventType, VariantMap& eventData);
    /// Handle a client connecting to the server.
    void HandleClientConnected(StringHash eventType, VariantMap& eventData);
    /// Handle a client disconnecting from the server.
    void HandleClientDisconnected(StringHash eventType, VariantMap& eventData);
    /// Handle remote event from server which tells our controlled object node ID.
    void HandleClientObjectID(StringHash eventType, VariantMap& eventData);

    /// Mapping from client connections to controllable objects.
    HashMap<Connection*, WeakPtr<Node> > serverObjects_;
    /// Button container element.
    SharedPtr<UIElement> buttonContainer_;
    /// Server address line editor element.
    SharedPtr<LineEdit> textEdit_;
    /// Connect button.
    SharedPtr<Button> connectButton_;
    /// Disconnect button.
    SharedPtr<Button> disconnectButton_;
    /// Start server button.
    SharedPtr<Button> startServerButton_;
    /// Instructions text.
    SharedPtr<Text> instructionsText_;
    /// ID of own controllable object (client only.)
    unsigned clientObjectID_;
};
