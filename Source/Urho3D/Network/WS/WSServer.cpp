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

#include "../Network.h"
#include "../../Core/WorkQueue.h"
#include "../../IO/Log.h"
#include "../../IO/MemoryBuffer.h"
#include "WSHandler.h"
#include "WSServer.h"

#include <libwebsockets.h>
#include <signal.h>
#include <string.h>

static Urho3D::WSServer* WSServerInstance = nullptr;
static struct lws_context *context;

static int WSCallback(struct lws *wsi, enum lws_callback_reasons reason, void *user, void *in, size_t len) {
    URHO3D_LOGINFOF("Incoming server messsage reason %d", reason);

    switch (reason) {
        case LWS_CALLBACK_PROTOCOL_INIT:
            break;

        case LWS_CALLBACK_ESTABLISHED:
            if (WSServerInstance) {
                WSServerInstance->AddPendingConnection(wsi);
            }
            break;

        case LWS_CALLBACK_SERVER_WRITEABLE:
        case LWS_CALLBACK_CLIENT_WRITEABLE:
            if (WSServerInstance) {
                Urho3D::MutexLock lock(WSServerInstance->GetOutgoingMutex());
                auto* packets = WSServerInstance->GetOutgoingPackets(wsi);
                for (auto it = packets->Begin(); it != packets->End(); ++it) {
                    WSPacket& packet = (*it);
                    unsigned char buf[LWS_PRE + packet.second_.GetSize()];
                    memcpy(&buf[LWS_PRE], packet.second_.GetData(), packet.second_.GetSize());
                    int retval = lws_write(packet.first_.GetWS(), &buf[LWS_PRE], packet.second_.GetSize(), LWS_WRITE_BINARY);
                    if (retval < packet.second_.GetSize()) {
                        URHO3D_LOGERRORF("Failed to write to WS, ret = %d", retval);
                        break;
                    }
                    packets->Erase(it);
                    lws_callback_on_writable(wsi);
                    break;
                }
            }
            break;

        case LWS_CALLBACK_RECEIVE: {
            Urho3D::VectorBuffer b((unsigned char*)in, len);
            if (b.GetData()[0] == URHO3D_MESSAGE) {
                WSPacket packet(wsi, b);
                if (WSServerInstance) {
                    WSServerInstance->AddIncomingPacket(packet);
                }
            } else {
                URHO3D_LOGINFOF("Received message that is not part of the engine %d", b.GetData()[0]);
            }
            break;
        }

        case LWS_CALLBACK_CLOSED: {
            if (WSServerInstance) {
                WSServerInstance->AddClosedConnection(wsi);
            }
            URHO3D_LOGINFOF("LWS_CALLBACK_CLOSED");
            break;
        }
        default:
            break;
    }

    return 0;
}

static struct lws_protocols protocols[] = {
        { "ws-server", WSCallback, 0, 0 },
        { NULL, NULL, 0, 0 } /* terminator */
};


static int interrupted;

void sigint_handler(int sig)
{
    interrupted = 1;
}

using namespace Urho3D;

static void RunService(const WorkItem* item, unsigned threadIndex) {
    auto packets = WSServerInstance->GetAllOutgoingPackets();
    for (auto it = packets->Begin(); it != packets->End(); ++it) {
        if (!(*it).second_.Empty()) {
            auto ws = (*it).second_.Front().first_;
            URHO3D_LOGINFOF("Outgoing packet count (server) %d", WSServerInstance->GetNumOutgoingPackets(ws));
            lws_callback_on_writable(ws.GetWS());
        }
    }

    int result = lws_service(context, 0);
    if (result < 0 && WSServerInstance) {
        WSServerInstance->StopServer();
    }
    URHO3D_LOGINFOF("Running server service");
}

WSServer::WSServer(Context* context):
    Object(context)
{
    WSServerInstance = this;
}

WSServer::~WSServer()
{
    WSServerInstance = nullptr;
}

int WSServer::StartServer()
{
    struct lws_context_creation_info info;
    const char *p;
    int n = 0, logs = LLL_USER | LLL_ERR | LLL_WARN | LLL_NOTICE
    /* for LLL_ verbosity above NOTICE to be built into lws,
     * lws must have been configured and built with
     * -DCMAKE_BUILD_TYPE=DEBUG instead of =RELEASE */
    /* | LLL_INFO */ /* | LLL_PARSER */ /* | LLL_HEADER */
    /* | LLL_EXT */ /* | LLL_CLIENT */ /* | LLL_LATENCY */
    /* | LLL_DEBUG */;

    signal(SIGINT, sigint_handler);

    lws_set_log_level(logs, OutputWSLog);
    lwsl_user("LWS minimal ws server | visit http://localhost:9292 (-s = use TLS / https)\n");

    memset(&info, 0, sizeof info); /* otherwise uninitialized garbage */
    info.port = 9292;
//    info.mounts = &mount;
    info.protocols = protocols;
//    info.vhost_name = "localhost";
    info.options = LWS_SERVER_OPTION_HTTP_HEADERS_SECURITY_BEST_PRACTICES_ENFORCE;
    info.gid = -1;
    info.uid = -1;
//    info.username = "";
//    info.groupname = "";

#if defined(LWS_WITH_TLS)
    if (lws_cmdline_option(argc, argv, "-s")) {
		lwsl_user("Server using TLS\n");
		info.options |= LWS_SERVER_OPTION_DO_SSL_GLOBAL_INIT;
		info.ssl_cert_filepath = "localhost-100y.cert";
		info.ssl_private_key_filepath = "localhost-100y.key";
	}
#endif

    lwsl_err("creating context");
    context = lws_create_context(&info);
    lwsl_err("context started");
    if (!context) {
        lwsl_err("lws init failed\n");
        return 1;
    }

    lwsl_err("Server started");

    SubscribeToEvent(E_WORKITEMCOMPLETED, URHO3D_HANDLER(WSServer, HandleWorkItemFinished));

    return 0;
//	struct lws_context_creation_info info;
//	memset(&info, 0, sizeof(info));
//	info.protocols = protocols2;
//	info.port = 9090;//config.port;
//	info.gid = -1;
//	info.uid = -1;
//#define WS_OPT(member, var) info.member = (!var.empty()) ? var.c_str() : NULL
//	WS_OPT(iface, config.iface);
//	WS_OPT(ssl_cert_filepath, config.sslCertFile);
//	WS_OPT(ssl_private_key_filepath, config.sslPrivateKeyFile);
//	WS_OPT(ssl_ca_filepath, config.sslCACertFile);
//	WS_OPT(ssl_cipher_list, config.sslCipherList);
//    WS_OPT(http_proxy_address, config.httpProxyAddress);
//#undef WS_OPT

//	context = libwebsocket_create_context(&info);
//
//
//	initialized_ = true;
	return 0;
}

void WSServer::Update(float timestep)
{
    if (currentState_ == WSS_RUNNING && nextState_ == WSS_STOPPED) {
        GetSubsystem<Network>()->StopServer();
    }
    while(!closedConnections.Empty()) {
        auto ws = closedConnections.Front().GetWS();
        GetSubsystem<Network>()->ClientDisconnected(closedConnections.Front());
        auto packets = GetAllOutgoingPackets();
        packets->Erase(ws);
        closedConnections.PopFront();
    }
    while(!pendingConnections_.Empty()) {
        auto ws = pendingConnections_.Front();
        GetSubsystem<Network>()->NewConnectionEstablished(ws);
        pendingConnections_.PopFront();
    }
    if (context) {
        if (!serviceWorkItem_) {
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
        GetSubsystem<Network>()->HandleIncomingPacket(packet, true);
        RemoveIncomingPacket();
    }
    if (currentState_ != nextState_) {
        currentState_ = nextState_;
    }
}

void WSServer::StopServer()
{
    SetState(WSS_STOPPED);
    if (context) {
        lws_context_destroy(context);
        context = nullptr;
    }
}

void WSServer::HandleWorkItemFinished(StringHash eventType, VariantMap& eventData)
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

void WSServer::AddPendingConnection(lws* ws)
{
    pendingConnections_.Push(ws);
}

void WSServer::AddClosedConnection(lws* ws)
{
    closedConnections.Push(ws);
}

void WSServer::SetState(WSServerState state)
{
    nextState_ = state;
}
