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

#include <libwebsockets.h>
#include <string.h>

static Urho3D::WSClient* WSClientInstance = nullptr;
static struct lws_context *context;

#if defined(WIN32)
#define HAVE_STRUCT_TIMESPEC
#if defined(pid_t)
#undef pid_t
#endif
#endif

static struct lws *client_wsi;
static lws_sorted_usec_list_t sul;

static const lws_retry_bo_t retry = {
        .secs_since_valid_ping = 3,
        .secs_since_valid_hangup = 10,
};

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

static int WSCallback(struct lws *wsi, enum lws_callback_reasons reason, void *user, void *in, size_t len)
{
//    URHO3D_LOGINFOF("Incoming client messsage reason %d", reason);
    switch (reason) {
        case LWS_CALLBACK_CLIENT_CONNECTION_ERROR:
            if (WSClientInstance) {
                WSClientInstance->SetState(Urho3D::WCS_CONNECTION_FAILED);
            }
            break;

        case LWS_CALLBACK_CLIENT_ESTABLISHED:
            if (WSClientInstance) {
                WSClientInstance->SetWSConnection(wsi);
                WSClientInstance->SetState(Urho3D::WCS_CONNECTED);
            }
            lwsl_user("%s: established\n", __func__);
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
            lws_callback_on_writable(wsi);
            break;
        }

        case LWS_CALLBACK_CLIENT_WRITEABLE:
            if (WSClientInstance) {
                if(WSClientInstance->GetNumOutgoingPackets(wsi)) {
                    auto packet = WSClientInstance->GetOutgoingPacket(wsi);
                    if (packet) {
                        unsigned char buf[LWS_PRE + packet->second_.GetSize()];
                        memcpy(&buf[LWS_PRE],  packet->second_.GetData(),  packet->second_.GetSize());
                        int retval = lws_write(wsi, &buf[LWS_PRE],  packet->second_.GetSize(), LWS_WRITE_BINARY);
                        if (retval <  packet->second_.GetSize()) {
                            URHO3D_LOGERRORF("Failed to write to WS, ret = %d", retval);
                            break;
                        }
                        WSClientInstance->RemoveOutgoingPacket(wsi);
                    }
                }
                lws_callback_on_writable(wsi);
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


static const struct lws_protocols protocols[] = {
        {"ws_client", WSCallback,0,0,},
        { NULL, NULL, 0, 0 }
};

using namespace Urho3D;

static void RunService(const WorkItem* item, unsigned threadIndex) {
    int result = lws_service(context, 0);
    if (result < 0 && WSClientInstance) {
        WSClientInstance->Disconnect();
    }
    URHO3D_LOGINFOF("Running client service");
}

WSClient::WSClient(Context* context):
Object(context),
ws_(nullptr)
{
    SetState(WCS_DISCONNECTED);
    WSClientInstance = this;
}

WSClient::~WSClient()
{
    WSClientInstance = nullptr;
}

int WSClient::Connect(const String& address, unsigned short port)
{
    struct lws_context_creation_info info;
    lws_set_log_level(LLL_USER | LLL_ERR | LLL_WARN | LLL_NOTICE, OutputWSLog);

    address_ = address;
    port_ = port;
    serverProtocol_ = "ws-server";

    memset(&info, 0, sizeof info);
    info.port = CONTEXT_PORT_NO_LISTEN;
    info.protocols = protocols;

    context = lws_create_context(&info);
    if (!context) {
        URHO3D_LOGERROR("Failed to start Websocket client");
        return 1;
    }

    lws_sul_schedule(context, 0, &sul, connect_cb, 50);
    SubscribeToEvent(E_WORKITEMCOMPLETED, URHO3D_HANDLER(WSClient, HandleWorkItemFinished));
    SetState(WCS_CONNECTING);
    return 0;
}

void WSClient::Update(float timestep)
{
    if (currentState_ == WCS_CONNECTING && nextState_ == WCS_CONNECTED) {
        GetSubsystem<Network>()->OnServerConnected(GetWSConnection());
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
    if (context)
    {
        lws_context_destroy(context);
        context = nullptr;
    }
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
