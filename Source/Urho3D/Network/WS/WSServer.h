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
#include "../../Core/Mutex.h"
#include "../../Core/Object.h"
#include "WSConnection.h"
#include "WSHandler.h"

namespace Urho3D {

class Network;
class WorkItem;

/// Server state
enum WSServerState {
    WSS_STOPPED,
    WSS_RUNNING
};

/// Websocket server handler
class WSServer: public WSHandler, public Object {
    URHO3D_OBJECT(WSServer, Object);
public:
    /// Construct.
    explicit WSServer(Context* context);
    /// Destruct.
    ~WSServer();

    /// Start whe Websockets server
    int StartServer(unsigned short port, unsigned int maxConnections);
    /// Stop the Websockets server
    void StopServer();
    /// Run the update loop to send/fetch all the buffered messages
    void Update(float timestep);
    /// New client connection to the server established, add it to the queue
    void AddPendingConnection(lws* ws);
    /// Client connection lost, add it to the queue
    void AddClosedConnection(lws* ws);
    /// Set the server state
    void SetState(WSServerState state);
    /// Get maximum number of connections allowed
    unsigned short GetMaxConnections() { return maxConnections_; };

private:
    /// Handle work item finished event
    void HandleWorkItemFinished(StringHash eventType, VariantMap& eventData);

    /// Work item which runs the WS service loop
    SharedPtr<WorkItem> serviceWorkItem_;
    /// Pending connections queue that should be processed inside the engine
    List<WSConnection> pendingConnections_;
    /// Close connections queue that should be cleared up from the engine
    List<WSConnection> closedConnections;
    /// Current state of the server
    WSServerState currentState_;
    /// Next state of the server that will be handled in the next update loop
    WSServerState nextState_;
    /// Max allowed connections to the server
    unsigned int maxConnections_;
};
}
