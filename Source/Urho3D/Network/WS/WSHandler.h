#pragma once

#include "../../IO/VectorBuffer.h"
#include "../../Core/Mutex.h"
#include "../../Container/List.h"
#include "WSPacket.h"

namespace Urho3D {
    class Network;

    class WSHandler {
    public:
        WSHandler(Urho3D::Network *networkInstance);
        ~WSHandler();

        Network* GetNetworkInstance() { return networkInstance_; }

        Mutex& GetIncomingMutex() { return incomingMutex_; }
        void AddIncomingPacket(const WSPacket& packet);
        WSPacket& GetIncomingPacket();
        void RemoveIncomingPacket();
        int GetNumIncomingPackets() { return incomingPackets_.Size(); }

        Mutex& GetOutgoingMutex() { return outgoingMutex_; }
        void AddOutgoingPacket(const WSPacket& packet);
        WSPacket& GetOutgoingPacket();
        void RemoveOutgoingPacket();
        int GetNumOutgoingPackets() { return outgoingPackets_.Size(); }
        List<WSPacket>* GetOutgoingPackets() { return &outgoingPackets_; };

        static void OutputWSLog(int level, const char *line);

    protected:
        Network *networkInstance_;

        Mutex incomingMutex_;
        Mutex outgoingMutex_;
        List<WSPacket> incomingPackets_;
        List<WSPacket> outgoingPackets_;
    };
}
