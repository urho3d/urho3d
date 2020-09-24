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
    class WSHandler {
    public:
        WSHandler();
        ~WSHandler();

        Mutex& GetIncomingMutex() { return incomingMutex_; }
        void AddIncomingPacket(const WSPacket& packet);
        WSPacket* GetIncomingPacket();
        void RemoveIncomingPacket();
        int GetNumIncomingPackets() { return incomingPackets_.Size(); }

        Mutex& GetOutgoingMutex() { return outgoingMutex_; }
        void AddOutgoingPacket(const WSPacket& packet);
        WSPacket* GetOutgoingPacket(const WSConnection& ws);
        void RemoveOutgoingPacket(const WSConnection& ws);
        int GetNumOutgoingPackets(const WSConnection& ws);
        List<WSPacket>* GetOutgoingPackets(const WSConnection& ws);
        HashMap<WSConnection, List<WSPacket>>* GetAllOutgoingPackets() { return &outgoingPackets_; };

        static void OutputWSLog(int level, const char *line);

    protected:

        Mutex incomingMutex_;
        Mutex outgoingMutex_;
        List<WSPacket> incomingPackets_;
        HashMap<WSConnection, List<WSPacket>> outgoingPackets_;
    };
}
