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
static bool context = false;

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
static struct lws_context *context;
static const lws_retry_bo_t retry = {
        .secs_since_valid_ping = 3,
        .secs_since_valid_hangup = 10,
};
#endif

#ifndef __EMSCRIPTEN__
static void connect_cb(lws_sorted_usec_list_t *_sul)
{
    struct lws_client_connect_info i;

    lwsl_notice("%s: connecting\n", __func__);

    memset(&i, 0, sizeof(i));

    i.context = context;
    i.port = WSClientInstance->GetPort();
    i.address = WSClientInstance->GetAddress().CString();
    i.path = "/";
    i.host = i.address;
    i.origin = i.address;
    i.protocol = WSClientInstance->GetServerProtocol().CString();
    i.alpn = "http/1.1";

    i.local_protocol_name = "ws_client";
    i.pwsi = &client_wsi;
    i.retry_and_idle_policy = &retry;

    if (!lws_client_connect_via_info(&i))
        lws_sul_schedule(context, 0, _sul, connect_cb, 5 * LWS_USEC_PER_SEC);
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
            // lwsl_user("%s: established\n", __func__);
            break;

        case LWS_CALLBACK_CLIENT_RECEIVE: {
            URHO3D_LOGINFOF("Received buffer of size %d", len);
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
#ifdef __EMSCRIPTEN__
                if(WSClientInstance->GetNumOutgoingPackets(wsi))
                {
                    auto packet = WSClientInstance->GetOutgoingPacket(wsi);
                    if (packet)
                    {
                        int retval = EM_ASM_INT({
                            var socket = Module.__libwebsocket.socket;
                            if( ! socket ) {
                                return -1;
                            }
                            // alloc a Uint8Array backed by the incoming data.
                            var data_in = new Uint8Array(Module.HEAPU8.buffer, $1, $2 );
                            // allow the dest array
                            var data = new Uint8Array($2);
                            // set the dest from the src
                            data.set(data_in);
                            socket.send(data);

                            // TODO: possible memory leak?
                            return $2;

                        }, packet->second_.GetData(), packet->second_.GetSize());
                        if (retval <  packet->second_.GetSize()) {
                            URHO3D_LOGERRORF("Failed to write to WS, bytes written = %d", retval);
                            break;
                        }
                        WSClientInstance->RemoveOutgoingPacket(wsi);
                    }
                }
#else
                if(WSClientInstance->GetNumOutgoingPackets(wsi)) {
                    auto packet = WSClientInstance->GetOutgoingPacket(wsi);
                    if (packet) {
                        unsigned char buf[LWS_PRE + packet->second_.GetSize()];
                        memcpy(&buf[LWS_PRE],  packet->second_.GetData(),  packet->second_.GetSize());
                        int retval = lws_write(wsi, &buf[LWS_PRE],  packet->second_.GetSize(), LWS_WRITE_BINARY);
                        if (retval <  packet->second_.GetSize()) {
                            URHO3D_LOGERRORF("Failed to write to WS, bytes written = %d", retval);
                            break;
                        }
                        WSClientInstance->RemoveOutgoingPacket(wsi);
                    }
                }
                lws_callback_on_writable(wsi);
#endif
            }
            break;

        case LWS_CALLBACK_CLIENT_CLOSED:
            if (WSClientInstance) {
                WSClientInstance->Disconnect();
            }
            URHO3D_LOGINFOF("LWS_CALLBACK_CLIENT_CLOSED");
            break;

        default:
            break;
    }

    return 0;
}

#ifdef __EMSCRIPTEN__
// static int WSHelper(struct lws *wsi, enum lws_callback_reasons reason, void *user, void *in, size_t len ) {
//         return WSCallback(wsi, reason, user, in, len);
// }
static int WSHelper(intptr_t wsi, int reason, intptr_t user, intptr_t in, int len ) {
    URHO3D_LOGINFOF("WSHelper called");
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
#ifdef __EMSCRIPTEN__
    // Trigger writing on the socket
    WSCallback(nullptr, LWS_CALLBACK_CLIENT_WRITEABLE, nullptr, nullptr, 0);
#else
    int result = lws_service(context, 0);
    if (result < 0 && WSClientInstance) {
        WSClientInstance->Disconnect();
    }
    URHO3D_LOGINFOF("Running client service");
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
        // libwebsocket.on_event = function(){ console.log('on_event'); };//Module.cwrap('WSHelper', 'number', ['number', 'number', 'number', 'number', 'number']);
        libwebsocket.on_event = Module.WSHelper;//Module.cwrap('WSHelper', 'number', ['number', 'number', 'number', 'number', 'number']);
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
            console.log('on_message', event);
            // const nDataBytes = data.byteLength;
            //   const dataPtr = Module._malloc(nDataBytes);
            //   const dataHeap = new Uint8Array(Module.HEAPU8.buffer, dataPtr, nDataBytes);
            //   dataHeap.set(new Uint8Array(data));
            //   if (Module.JSResponse) {
            //     Module.JSResponse(httpRequestHandlerPtr, dataHeap.byteOffset, nDataBytes);
            //   } else {
            //     console.error('Module.JSResponse() method doesn\'t exist');
            //   }
            //   Module._free(dataHeap.byteOffset);
            // var stack = stackSave();
            var len = event.data.byteLength;
            var ptr = Module._malloc(len);

            const data = new Uint8Array(Module.HEAPU8.buffer, dataPtr, nDataBytes);
            data.set(new Uint8Array(event.data));

            // client receive //
            if(libwebsocket.on_event(this.id, 8, 0, data.byteOffset, len)) {
                this.close();
            }

            Module._free(data.byteOffset);
            // stackRestore(stack);
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
            libwebsocket.socket = false;
            libwebsocket.on_event(this.id, 75, 0, 0, 0);
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

    context = lws_create_context(&info);
    if (!context) {
        URHO3D_LOGERROR("Failed to start Websocket client");
        return 1;
    }

    lws_sul_schedule(context, 0, &sul, connect_cb, 50);
#else
    context = true;
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
    }
    if (nextState_ == WCS_CONNECTION_FAILED) {
        GetSubsystem<Network>()->OnServerDisconnected(GetWSConnection(), true);
    }

    if (context) {
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
    if (context)
    {
        lws_context_destroy(context);
        context = nullptr;
    }
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

#endif
