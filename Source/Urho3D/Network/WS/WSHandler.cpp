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

#ifdef URHO3D_WEBSOCKETS

#include "../../IO/Log.h"
#include "WSHandler.h"
#include "WSPacket.h"

#ifndef __EMSCRIPTEN__
#include <libwebsockets.h>
#endif

using namespace Urho3D;

WSHandler::WSHandler()
{

}

WSHandler::~WSHandler()
{

}

void WSHandler::AddIncomingPacket(const WSPacket& packet)
{
    Urho3D::MutexLock lock(GetIncomingMutex());
    incomingPackets_.Push(packet);
}

WSPacket* WSHandler::GetIncomingPacket()
{
    return &incomingPackets_.Front();
}

void WSHandler::RemoveIncomingPacket()
{
    if (GetNumIncomingPackets() > 0) {
        Urho3D::MutexLock lock(GetIncomingMutex());
        incomingPackets_.Front().second_.Clear();
        incomingPackets_.PopFront();
    }
}

void WSHandler::AddOutgoingPacket(const WSPacket& packet)
{
    Urho3D::MutexLock lock(GetOutgoingMutex());
    outgoingPackets_[packet.first_].Push(packet);
}

WSPacket* WSHandler::GetOutgoingPacket(const WSConnection& ws)
{
    if (outgoingPackets_.Contains(ws)) {
        return &outgoingPackets_[ws].Front();
    }

    return nullptr;
}

void WSHandler::RemoveOutgoingPacket(const WSConnection& ws)
{
    if (GetNumOutgoingPackets(ws) > 0) {
        Urho3D::MutexLock lock(GetOutgoingMutex());
        outgoingPackets_[ws].Front().second_.Clear();
        outgoingPackets_[ws].PopFront();
    }
}

int WSHandler::GetNumOutgoingPackets(const WSConnection& ws)
{
    if (outgoingPackets_.Contains(ws)) {
        return outgoingPackets_[ws].Size();
    }

    return 0;
}

List<WSPacket>* WSHandler::GetOutgoingPackets(const WSConnection& ws)
{
    if (outgoingPackets_.Contains(ws)) {
        return &outgoingPackets_[ws];
    }

    return nullptr;
}

void WSHandler::OutputWSLog(int level, const char *line)
{
#ifndef __EMSCRIPTEN__
    switch(level) {
        case LLL_NOTICE:
            URHO3D_LOGINFOF("WSClient: %s", line);
            break;
        case LLL_WARN:
            URHO3D_LOGWARNINGF("WSClient: %s", line);
            break;
        case LLL_ERR:
            URHO3D_LOGERRORF("WSClient: %s", line);
            break;
        case LLL_USER:
            URHO3D_LOGINFOF("WSClient: %s", line);
            break;
    }
#endif
}

#endif
