#if !defined(__EMSCRIPTEN__) && !defined(__ANDROID__)
#pragma once
#include "WSPacket.h"
#include "../../Core/Mutex.h"
#include "../../Container/List.h"
#include "WSHandler.h"

namespace Urho3D {
class Network;

class WSServer: public WSHandler {

public:
    WSServer(Urho3D::Network *networkInstance);
    ~WSServer();

    int StartServer();
    void StopServer();
    void Update(float timestep);
};
}
#endif