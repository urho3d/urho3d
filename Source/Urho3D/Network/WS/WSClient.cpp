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

#include "../../Core/WorkQueue.h"
#include "../../IO/MemoryBuffer.h"
#include "../../IO/Log.h"
#include "../Network.h"
#include "WSClient.h"
#include "WSHandler.h"

#include <string.h>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <emscripten/bind.h>

enum lws_callback_reasons {
    LWS_CALLBACK_ESTABLISHED = 0,
    LWS_CALLBACK_CLIENT_CONNECTION_ERROR = 1,
    LWS_CALLBACK_CLIENT_ESTABLISHED = 3,
    LWS_CALLBACK_CLOSED = 4,
    LWS_CALLBACK_RECEIVE = 6,
    LWS_CALLBACK_CLIENT_RECEIVE = 8,
    LWS_CALLBACK_CLIENT_WRITEABLE = 10,
    LWS_CALLBACK_SERVER_WRITEABLE = 11,
    LWS_CALLBACK_FILTER_PROTOCOL_CONNECTION = 20,
    LWS_CALLBACK_WSI_CREATE = 29,
    LWS_CALLBACK_WSI_DESTROY = 30,
    LWS_CALLBACK_CLIENT_CLOSED = 75
};    
#else
#include <libwebsockets.h>
#endif

static Urho3D::WSClient* WSClientInstance = nullptr;

#if defined(WIN32)
#define HAVE_STRUCT_TIMESPEC
#if defined(pid_t)
#undef pid_t
#endif
#endif

#ifndef __EMSCRIPTEN__
static struct lws *client_wsi;
static lws_sorted_usec_list_t sul;
static struct lws_context *wsContext;
static lws_retry_bo_t retry{};

/// Connect to server with retry functionality
static void ConnectToServer(lws_sorted_usec_list_t *_sul)
{
    struct lws_client_connect_info info;
    memset(&info, 0, sizeof(info));

    info.context = wsContext;
    info.port = WSClientInstance->GetPort();
    info.address = WSClientInstance->GetAddress().CString();
    info.path = "/";
    info.host = info.address;
    info.origin = info.address;
    info.protocol = WSClientInstance->GetServerProtocol().CString();
    info.alpn = "http/1.1";

    info.local_protocol_name = "ws_client";
    info.pwsi = &client_wsi;
    retry.secs_since_valid_ping = 3;
    retry.secs_since_valid_ping = 10;

    info.retry_and_idle_policy = &retry;

    if (!lws_client_connect_via_info(&info))
        lws_sul_schedule(wsContext, 0, _sul, ConnectToServer, 5 * LWS_USEC_PER_SEC);
}
#endif

static int WSCallback(struct lws *wsi, enum lws_callback_reasons reason, void *user, void *in, size_t len)
{
   // URHO3D_LOGINFOF("Incoming client messsage reason %d", reason);
    switch (reason) {
        case LWS_CALLBACK_CLIENT_CONNECTION_ERROR:
            if (WSClientInstance) {
                WSClientInstance->SetState(Urho3D::WCS_CONNECTION_FAILED);
            }
            break;

        case LWS_CALLBACK_CLIENT_ESTABLISHED:
            if (WSClientInstance) {
                URHO3D_LOGINFOF("LWS_CALLBACK_CLIENT_ESTABLISHED");
                WSClientInstance->SetWSConnection(wsi);
                WSClientInstance->SetState(Urho3D::WCS_CONNECTED);
            }
            break;

        case LWS_CALLBACK_CLIENT_RECEIVE: {
            Urho3D::VectorBuffer b((unsigned char*)in, len);
            if (b.GetData()[0] == URHO3D_MESSAGE) {
                WSPacket packet(wsi, b);
                if (WSClientInstance) {
                    WSClientInstance->AddIncomingPacket(packet);
                }
            } else {
                URHO3D_LOGINFOF("Received message that is not part of the engine %d", b.GetData()[0]);
            }
#ifndef __EMSCRIPTEN__
            lws_callback_on_writable(wsi);
#endif
            break;
        }

        case LWS_CALLBACK_CLIENT_WRITEABLE:
            if (WSClientInstance) {
#ifndef __EMSCRIPTEN__
               WSClientInstance->SendOutMessages(wsi);
#endif
            }
            break;

        case LWS_CALLBACK_CLIENT_CLOSED:
#ifndef __EMSCRIPTEN__
            if (WSClientInstance) {
                WSClientInstance->Disconnect();
            }
#endif
            URHO3D_LOGINFOF("LWS_CALLBACK_CLIENT_CLOSED");
            break;

        default:
            break;
    }

    return 0;
}

#ifdef __EMSCRIPTEN__
static int WSHelper(intptr_t wsi, int reason, intptr_t user, intptr_t in, int len ) {
    return WSCallback(reinterpret_cast<struct lws *>(wsi), static_cast<enum lws_callback_reasons>(reason), reinterpret_cast<void*>(user), reinterpret_cast<void*>(in), (size_t)len);
}
using namespace emscripten;
EMSCRIPTEN_BINDINGS(WSClient) {
    function("WSHelper", &WSHelper);
}
#endif

#ifndef __EMSCRIPTEN__
static const struct lws_protocols protocols[] = {
        {"ws_client", WSCallback,0,0,},
        { NULL, NULL, 0, 0 }
};
#endif

using namespace Urho3D;

static void RunService(const WorkItem* item, unsigned threadIndex) {
#ifndef __EMSCRIPTEN__
    int result = lws_service(wsContext, 0);
    if (result < 0 && WSClientInstance) {
        WSClientInstance->Disconnect();
    }
#endif
}

WSClient::WSClient(Context* context):
Object(context),
ws_(nullptr)
{
    SetState(WCS_DISCONNECTED);
    WSClientInstance = this;

#ifdef __EMSCRIPTEN__
    EM_ASM({
        var libwebsocket = {};
        libwebsocket.socket = false;
        libwebsocket.on_event = Module.WSHelper;
        libwebsocket.connect = function( url, protocol, user_data ) {
            try {
                var socket = new WebSocket(url,protocol);
                socket.binaryType = "arraybuffer";
                socket.user_data = user_data;
                socket.id = 1;

                socket.onopen = this.on_connect;
                socket.onmessage = this.on_message;
                socket.onclose = this.on_close;
                socket.onerror = this.on_error;
                socket.destroy = this.destroy;

                this.socket = socket;
                return socket;
            } catch(e) {
                console.log("Socket creation failed:" + e);
                return 0;
            }
        };
        libwebsocket.on_connect = function() {
            // var stack = stackSave();
            // filter protocol //
            // var ret = libwebsocket.on_event(this.id, 9, 0, allocate(intArrayFromString(this.protocol), 'i8', ALLOC_STACK), this.protocol.length);
            // if( !ret ) {
                // client established
            console.log('this.id, 3, 0, 0, 0', this.id, 3, 0, 0, 0);
                ret = libwebsocket.on_event(this.id, 3, 0, 0, 0);
            // }
            if( ret ) {
                this.close();
            }
            // stackRestore(stack);
        };
        libwebsocket.on_message = function(event) {
            var len = event.data.byteLength;
            var ptr = Module._malloc(len);

            const data = new Uint8Array(Module.HEAPU8.buffer, ptr, len);
            data.set(new Uint8Array(event.data));

            // client receive //
            if(libwebsocket.on_event(this.id, 8, 0, data.byteOffset, len)) {
                this.close();
            }

            Module._free(data.byteOffset);
        };
        libwebsocket.on_close = function() {
            // closed //
            libwebsocket.on_event(this.id, 4, 0, 0, 0);
            this.destroy();
        };
        libwebsocket.on_error = function() {
            // client connection error //
            libwebsocket.on_event(this.id, 1, 0, 0, 0);
            this.destroy();
        };
        libwebsocket.destroy = function() {
            libwebsocket.on_event(libwebsocket.socket.id, 75, 0, 0, 0);
            libwebsocket.socket = false;
        };

        Module.__libwebsocket = libwebsocket;
    });
#endif
}

WSClient::~WSClient()
{
    WSClientInstance = nullptr;
}

int WSClient::Connect(const String& address, unsigned short port)
{
    address_ = address;
    port_ = port;
    serverProtocol_ = "ws-server";

    SetState(WCS_CONNECTING);
    SubscribeToEvent(E_WORKITEMCOMPLETED, URHO3D_HANDLER(WSClient, HandleWorkItemFinished));

#ifndef __EMSCRIPTEN__
    struct lws_context_creation_info info;
    lws_set_log_level(LLL_USER | LLL_ERR | LLL_WARN | LLL_NOTICE, OutputWSLog);

    memset(&info, 0, sizeof info);
    info.port = CONTEXT_PORT_NO_LISTEN;
    info.protocols = protocols;

    wsContext = lws_create_context(&info);
    if (!wsContext) {
        URHO3D_LOGERROR("Failed to start Websocket client");
        return 1;
    }

    lws_sul_schedule(wsContext, 0, &sul, ConnectToServer, 50);
#else
    EM_ASM({
        let address = UTF8ToString($0);
        let port = $1;
        let protocol = UTF8ToString($2); 
        Module.__libwebsocket.connect(address);
    }, address_.CString(), port, serverProtocol_.CString());
#endif

    return 0;
}

void WSClient::Update(float timestep)
{
    if (currentState_ == WCS_CONNECTING && nextState_ == WCS_CONNECTED) {
        GetSubsystem<Network>()->OnServerConnected(GetWSConnection());
        URHO3D_LOGINFOF("WSclient OnServerConnected");
    }

    if (nextState_ == WCS_DISCONNECTED) {
        GetSubsystem<Network>()->OnServerDisconnected(GetWSConnection(), false);
        return;
    }
    if (nextState_ == WCS_CONNECTION_FAILED) {
        GetSubsystem<Network>()->OnServerDisconnected(GetWSConnection(), true);
        return;
    }

#ifndef __EMSCRIPTEN__
    if (wsContext) {
        if (!serviceWorkItem_ && currentState_ != WCS_DISCONNECTED) {
            WorkQueue *workQueue = GetSubsystem<WorkQueue>();
            serviceWorkItem_ = workQueue->GetFreeItem();
            serviceWorkItem_->priority_ = M_MAX_INT;
            serviceWorkItem_->workFunction_ = RunService;
            serviceWorkItem_->aux_ = this;
            serviceWorkItem_->sendEvent_ = true;
            workQueue->AddWorkItem(serviceWorkItem_);
        }
    }
#else
    // For web port we can send out messages immediatelly
    SendOutMessages(GetWSConnection());
#endif

    while (GetNumIncomingPackets()) {
        auto packet = GetIncomingPacket();
        GetSubsystem<Network>()->HandleIncomingPacket(packet, false);
        RemoveIncomingPacket();
    }

    if (currentState_ != nextState_) {
        currentState_ = nextState_;
    }
}

void WSClient::Disconnect()
{
    SetState(WCS_DISCONNECTED);
#ifndef __EMSCRIPTEN__
    if (wsContext)
    {
        lws_context_destroy(wsContext);
        wsContext = nullptr;
    }
#else
    EM_ASM({
        Module.__libwebsocket.destroy();
    });
#endif
}

void WSClient::SetWSConnection(lws *ws)
{
    ws_ = ws;
}

void WSClient::SetState(WSClientState state)
{
    nextState_ = state;
}

void WSClient::HandleWorkItemFinished(StringHash eventType, VariantMap& eventData)
{
    using namespace WorkItemCompleted;
    WorkItem *workItem = reinterpret_cast<WorkItem *>(eventData[P_ITEM].GetPtr());
    if (workItem->aux_ != this) {
        return;
    }
    if (workItem->workFunction_ == RunService) {
        serviceWorkItem_.Reset();
    }
}

void WSClient::SendOutMessages(lws *ws)
{
#ifdef __EMSCRIPTEN__
    if(GetNumOutgoingPackets(ws))
    {
        auto packet = GetOutgoingPacket(ws);
        if (packet)
        {
            int retval = EM_ASM_INT({
                var socket = Module.__libwebsocket.socket;
                if( ! socket ) {
                    return -1;
                }
                // alloc a Uint8Array backed by the incoming data.
                var data_in = new Uint8Array(Module.HEAPU8.buffer, $0, $1);
                // allow the dest array
                var data = new Uint8Array($1);
                // set the dest from the src
                data.set(data_in);
                socket.send(data);

                return $1;

            }, packet->second_.GetData(), packet->second_.GetSize());
            if (retval <  packet->second_.GetSize())
            {
                URHO3D_LOGERRORF("Failed to write to WS, bytes written = %d", retval);
            }
            else
                RemoveOutgoingPacket(ws);
        }
    }
#else
    if(WSClientInstance->GetNumOutgoingPackets(ws)) {
        auto packet = WSClientInstance->GetOutgoingPacket(ws);
        if (packet) {
            unsigned char buf[LWS_PRE + packet->second_.GetSize()];
            memcpy(&buf[LWS_PRE],  packet->second_.GetData(),  packet->second_.GetSize());
            int retval = lws_write(ws, &buf[LWS_PRE],  packet->second_.GetSize(), LWS_WRITE_BINARY);
            if (retval <  packet->second_.GetSize()) {
                URHO3D_LOGERRORF("Failed to write to WS, bytes written = %d", retval);
                break;:
            }
            WSClientInstance->RemoveOutgoingPacket(ws);
        }
    }
    lws_callback_on_writable(ws);
#endif
}

#endif
