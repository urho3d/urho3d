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

#include "../../Container/List.h"
#include "../../Core/Object.h"
#include "../../Core/Mutex.h"
#include "../../IO/VectorBuffer.h"
#include "WSHandler.h"

namespace Urho3D {

class Network;
class WorkItem;

/// Client state
enum WSClientState {
    WCS_CONNECTING,
    WCS_CONNECTED,
    WCS_CONNECTION_FAILED,
    WCS_DISCONNECTED,
};

/// Websocket client handler
class WSClient: public WSHandler, public Object {
    URHO3D_OBJECT(WSClient, Object);
public:
    /// Construct.
    WSClient(Context* context);
    /// Destruct.
    ~WSClient();

    /// Connect to Websockets server
    int Connect(const String& address, unsigned short port);
    /// Run the update loop to send/fetch all the buffered messages
    void Update(float timestep);
    /// Disconnect from the server
    void Disconnect();
    /// Set the client connection state
    void SetState(WSClientState state);
    /// Set the Websocket connection information for this client
    void SetWSConnection(lws *ws);
    /// Get Websocket connection information for this client
    lws* GetWSConnection() { return ws_; };
    /// Get server address
    const String& GetAddress() const { return address_; };
    /// Get server port
    unsigned short GetPort() { return port_; };
    /// Get server protocol used for connection
    const String& GetServerProtocol() const { return serverProtocol_; };
    /// Send out client messages
    void SendOutMessages(lws *ws);

private:
    /// Handle work item finished event
    void HandleWorkItemFinished(StringHash eventType, VariantMap& eventData);

    /// Work item which runs the WS service loop
    SharedPtr<WorkItem> serviceWorkItem_;
    /// Websocket connection information
    struct lws *ws_;
    /// Current state of the client
    WSClientState currentState_;
    /// Next state of the client that will be handled in the next update loop
    WSClientState nextState_;
    /// Server address
    String address_;
    /// server port
    unsigned short port_;
    /// Server protocol used for connection
    String serverProtocol_;
};
}
