//
// Copyright (c) 2008-2020 the Urho3D project.
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
class LANDiscovery : public Sample
{
    URHO3D_OBJECT(LANDiscovery, Sample);

public:
    /// Construct.
    explicit LANDiscovery(Context* context);

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
    Text* CreateLabel(const String& text, IntVector2 pos);
    
    /// Handle found LAN server
    void HandleNetworkHostDiscovered(StringHash eventType, VariantMap& eventData);
    /// Start server
    void HandleStartServer(StringHash eventType, VariantMap& eventData);
    /// Stop server
	void HandleStopServer(StringHash eventType, VariantMap& eventData);
	/// Start network discovery
	void HandleDoNetworkDiscovery(StringHash eventType, VariantMap& eventData);
    /// Start server
    SharedPtr<Button> startServer_;
    /// Stop server
    SharedPtr<Button> stopServer_;
    /// Redo LAN discovery
    SharedPtr<Button> refreshServerList_;
    /// Found server list
	SharedPtr<Text> serverList_;
};
