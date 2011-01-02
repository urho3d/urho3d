//
// Urho3D Engine
// Copyright (c) 2008-2011 Lasse Öörni
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

#ifndef NETWORK_NETWORKEVENTS_H
#define NETWORK_NETWORKEVENTS_H

#include "Event.h"

//! Network peer connected
DEFINE_EVENT(EVENT_PEERCONNECTED, PeerConnected)
{
    EVENT_PARAM(P_PEER, Peer);                  // Peer pointer
}

//! Network packet received (only sent if packet events are enabled)
DEFINE_EVENT(EVENT_NETWORKPACKET, NetworkPacket)
{
    EVENT_PARAM(P_PEER, Peer);                  // Peer pointer
    EVENT_PARAM(P_CHANNEL, Channel);            // int
    EVENT_PARAM(P_DATA, Data);                  // Buffer (packet data)
}

//! Network peer disconnected
DEFINE_EVENT(EVENT_PEERDISCONNECTED, PeerDisconnected)
{
    EVENT_PARAM(P_PEER, Peer);                  // Peer pointer
}

#endif // NETWORK_NETWORKEVENTS_H
