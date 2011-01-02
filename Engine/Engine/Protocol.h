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

#ifndef ENGINE_PROTOCOL_H
#define ENGINE_PROTOCOL_H

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

// Reliable messages (chn.0), client to server. Each of these starts with the next response code
static const unsigned char MSG_IDENTITY = 0x06;
static const unsigned char MSG_REQUESTFILE = 0x07;
static const unsigned char MSG_JOINSCENE = 0x08;
static const unsigned char MSG_FULLUPDATEACK = 0x09;

// Server/clientupdate sub-messages. Unreliable chn.1 messages consist entirely of these
static const unsigned char MSG_CREATEENTITY = 0x0a;
static const unsigned char MSG_REMOVEENTITY = 0x0b;
static const unsigned char MSG_UPDATEENTITY = 0x0c;
static const unsigned char MSG_REMOTEEVENT = 0x0d;
static const unsigned char MSG_REMOTEENTITYEVENT = 0x0e;
static const unsigned char MSG_CONTROLS = 0x0f;

// MSG_UPDATEENTITY sub-update bits
static const unsigned char UPD_PROPERTIES = 0x10;
static const unsigned char UPD_NEWCOMPONENTS = 0x20;
static const unsigned char UPD_REMOVECOMPONENTS = 0x40;
static const unsigned char UPD_UPDATECOMPONENTS = 0x80;

#endif // ENGINE_PROTOCOL_H
