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

#pragma once

#include "Deserializer.h"
#include "Serializer.h"

// Channel numbers
static const unsigned char CHN_RELIABLE = 0;
static const unsigned char CHN_UNRELIABLE = 1;

// File transfer fragment size
static const unsigned FILE_FRAGMENT_SIZE = 1024;

// Reliable messages (chn.0), server to client
static const unsigned char MSG_CHALLENGE = 0x00;
static const unsigned char MSG_SCENEINFO = 0x01;
static const unsigned char MSG_TRANSFERDATA = 0x02;
static const unsigned char MSG_TRANSFERFAILED = 0x03;
static const unsigned char MSG_JOINREPLY = 0x04;
static const unsigned char MSG_FULLUPDATE = 0x05;

// Reliable messages (chn.0), client to server
static const unsigned char MSG_LOGIN = 0x06;
static const unsigned char MSG_REQUESTFILE = 0x07;
static const unsigned char MSG_JOINSCENE = 0x08;
static const unsigned char MSG_FULLUPDATEACK = 0x09;

// Server/clientupdate sub-messages. Unreliable chn.1 messages consist entirely of these
static const unsigned char MSG_CREATENODE = 0x0a;
static const unsigned char MSG_UPDATENODE = 0x0b;
static const unsigned char MSG_REMOVENODE = 0x0c;
static const unsigned char MSG_CREATECOMPONENT = 0x0d;
static const unsigned char MSG_UPDATECOMPONENT = 0x0e;
static const unsigned char MSG_REMOVECOMPONENT = 0x0f;
static const unsigned char MSG_CONTROLS = 0x10;
static const unsigned char MSG_REMOTEEVENT = 0x11;
static const unsigned char MSG_REMOTENODEEVENT = 0x12;

/// Write a 24-bit networked Node or Component ID
inline void WriteNetID(Serializer& dest, unsigned id)
{
    // Write the low 24 bits
    dest.Write(&id, 3);
}

// Read a 24-bit networked Node or Component ID
inline unsigned ReadNetID(Deserializer& source)
{
    unsigned ret = 0;
    // Read the low 24 bits
    source.Read(&ret, 3);
    return ret;
}

/// Compare network frame numbers, taking wrapping into account
inline bool CheckFrameNumber(unsigned short lhs, unsigned short rhs, bool sameFrameOk = true)
{
    // Frame number 0 means "frame never received", so in that case lhs is always considered "newer"
    if ((lhs) && (!rhs))
        return true;
    
    if ((!sameFrameOk) && (lhs == rhs))
        return false;
    
    return ((lhs - rhs) & 0xffff) < 0x8000;
}
