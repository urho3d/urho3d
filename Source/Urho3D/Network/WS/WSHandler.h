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
#include "../../Container/HashMap.h"
#include "../../Core/Mutex.h"
#include "../../IO/VectorBuffer.h"

#include "WSConnection.h"
#include "WSPacket.h"

namespace Urho3D {

    /// Basic Websocket connection handler used by WS client and server
    class WSHandler {
    public:
        /// Construct.
        WSHandler();
        /// Destruct.
        ~WSHandler();

        /// Get incoming packet mutex
        Mutex& GetIncomingMutex() { return incomingMutex_; }
        /// Add incoming packet to the buffer
        void AddIncomingPacket(const WSPacket& packet);
        /// Get first incoming packet
        WSPacket* GetIncomingPacket();
        /// Remove first incoming packet
        void RemoveIncomingPacket();
        /// Get total number of incoming packets
        int GetNumIncomingPackets() { return incomingPackets_.Size(); }

        /// Get outgoing packet mutex
        Mutex& GetOutgoingMutex() { return outgoingMutex_; }
        /// Add outgoing packet to the buffer
        void AddOutgoingPacket(const WSPacket& packet);
        /// Get first outgoing packet for specific WS connection
        WSPacket* GetOutgoingPacket(const WSConnection& ws);
        /// Remove first outgoing packet for specific WS connection
        void RemoveOutgoingPacket(const WSConnection& ws);
        /// Get total number of outgoing packets for specific WS connection
        int GetNumOutgoingPackets(const WSConnection& ws);
        /// Get all outgoing packets for specific WS connection
        List<WSPacket>* GetOutgoingPackets(const WSConnection& ws);
        /// Retur all connection buffered outgoing packets
        HashMap<WSConnection, List<WSPacket>>* GetAllOutgoingPackets() { return &outgoingPackets_; };
        /// Handle all libwebsocket logs
        static void OutputWSLog(int level, const char *line);

    protected:
        /// Incoming packet mutex
        Mutex incomingMutex_;
        /// Outgoing packet mutex
        Mutex outgoingMutex_;
        /// Incoming packet buffer
        List<WSPacket> incomingPackets_;
        /// Outgoing packet buffer
        HashMap<WSConnection, List<WSPacket>> outgoingPackets_;
    };
}
