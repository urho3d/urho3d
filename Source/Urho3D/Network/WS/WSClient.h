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

enum WSClientState {
    WCS_CONNECTING,
    WCS_CONNECTED,
    WCS_CONNECTION_FAILED,
    WCS_DISCONNECTED,
};

class WSClient: public WSHandler, public Object {
    URHO3D_OBJECT(WSClient, Object);
public:
    WSClient(Context* context);
    ~WSClient();
    int Connect();
    void Update(float timestep);
    void Disconnect();

    void SetState(WSClientState state);
    void SetWSConnection(lws *ws);
    lws* GetWSConnection() { return ws_; };

private:
    void HandleWorkItemFinished(StringHash eventType, VariantMap& eventData);

    struct lws *ws_;
    SharedPtr<WorkItem> serviceWorkItem_;
    WSClientState nextState_;
    WSClientState currentState_;
};
}
