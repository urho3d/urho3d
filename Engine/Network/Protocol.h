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

// Client->server: send VariantMap of identity and authentication data
static const int MSG_IDENTITY = 0x5;
// Client->server: send controls (buttons and mouse movement)
static const int MSG_CONTROLS = 0x6;
// Client->server: scene has been loaded and client is ready to proceed
static const int MSG_SCENELOADED = 0x7;

// Server->client: load new scene. In case of empty filename the client should just empty the scene
static const int MSG_LOADSCENE = 0x8;
// Server->client: wrong scene checksum, can not participate
static const int MSG_SCENECHECKSUMERROR = 0x9;
// Server->client: create new node
static const int MSG_CREATENODE = 0xa;
// Server->client: node delta update
static const int MSG_NODEDELTAUPDATE = 0xb;
// Server->client: node latest data update
static const int MSG_NODELATESTDATA = 0xc;
// Server->client: remove node
static const int MSG_REMOVENODE = 0xd;
// Server->client: create new component
static const int MSG_CREATECOMPONENT = 0xe;
// Server->client: component delta update
static const int MSG_COMPONENTDELTAUPDATE = 0xf;
// Server->client: component latest data update
static const int MSG_COMPONENTLATESTDATA = 0x10;
// Server->client: remove component
static const int MSG_REMOVECOMPONENT = 0x11;

// Client->server and server->client: remote event
static const int MSG_REMOTEEVENT = 0x12;
// Client->server and server->client: remote node event
static const int MSG_REMOTENODEEVENT = 0x13;

// Fixed content ID for client controls update
static const unsigned CONTROLS_CONTENT_ID = 1;
