#pragma once

#include "../../IO/VectorBuffer.h"
#include "../../Core/Mutex.h"
#include "../../Container/List.h"
#include "WSHandler.h"

struct lws;

namespace Urho3D {
class Network;

class WSClient: public WSHandler {
public:
    WSClient(Urho3D::Network *networkInstance);
    ~WSClient();
    int Connect();
    void Update(float timestep);
    void Disconnect();

    void SetWSConnection(lws *ws);
    lws* GetWSConnection() { return ws_; };

private:
    struct lws *ws_;
};
}
