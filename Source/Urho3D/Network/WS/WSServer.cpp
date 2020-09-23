#if !defined(__EMSCRIPTEN__) && !defined(__ANDROID__)
#include "WSServer.h"
#include "WSHandler.h"
#include "../Network.h"
#include "../../IO/MemoryBuffer.h"

//#define LWS_WITH_NETWORK TRUE
//#define LWS_ROLE_H1 TRUE
//#define LWS_ROLE_WS TRUE
//#define LWS_WITH_SERVER TRUE

#include "../../IO/Log.h"
#include <libwebsockets.h>
#include <string.h>
#include <signal.h>

#define LWS_PLUGIN_STATIC

#if !defined (LWS_PLUGIN_STATIC)
#define LWS_DLL
#define LWS_INTERNAL
#include <libwebsockets.h>
#endif

const int ID_USER_PACKET_ENUM = 134;
static Urho3D::WSServer* WSServerInstance = nullptr;
static struct lws_context *context;

static int ws_server_callback(struct lws *wsi, enum lws_callback_reasons reason, void *user, void *in, size_t len);

static struct lws_protocols protocols[] = {
        { "ws-server", ws_server_callback, 0, 0 },
        { NULL, NULL, 0, 0 } /* terminator */
};

static int ws_server_callback(struct lws *wsi, enum lws_callback_reasons reason, void *user, void *in, size_t len)
{
    URHO3D_LOGINFOF("Incoming server messsage reason %d", reason);

    switch (reason) {
        case LWS_CALLBACK_PROTOCOL_INIT:
            break;

        case LWS_CALLBACK_ESTABLISHED:
            if (WSServerInstance) {
                WSServerInstance->GetNetworkInstance()->NewConnectionEstablished(wsi);
            }
            break;

        case LWS_CALLBACK_CLOSED:
            // TODO: Handle client disconnected
            break;


        case LWS_CALLBACK_SERVER_WRITEABLE:
        case LWS_CALLBACK_CLIENT_WRITEABLE:
            if (WSServerInstance) {
//                Urho3D::MutexLock lock(WSServerInstance->GetOutgoingMutex());
                auto* packets = WSServerInstance->GetOutgoingPackets();
                for (auto it = packets->Begin(); it != packets->End(); ++it) {
                    WSPacket& packet = (*it);
                    if (wsi != packet.first_) {
                        continue;
                    }
                    unsigned char buf[LWS_PRE + packet.second_.GetSize()];
                    memcpy(&buf[LWS_PRE], packet.second_.GetData(), packet.second_.GetSize());
                    int retval = lws_write(packet.first_, &buf[LWS_PRE], packet.second_.GetSize(), LWS_WRITE_BINARY);
                    if (retval < packet.second_.GetSize()) {
                        URHO3D_LOGERRORF("Failed to write to WS, ret = %d", retval);
                        break;
                    }
                    packets->Erase(it);
                    lws_callback_on_writable(wsi);
                    break;
                }
            }
            lws_callback_on_writable(wsi);
            break;

        case LWS_CALLBACK_RECEIVE: {
            Urho3D::VectorBuffer b((unsigned char*)in, len);
            if (b.GetData()[0] == ID_USER_PACKET_ENUM) {
                WSPacket packet(wsi, b);
                if (WSServerInstance) {
                    WSServerInstance->AddIncomingPacket(packet);
                }
            } else {
                URHO3D_LOGINFOF("Received message that is not part of the engine %d", b.GetData()[0]);
            }
            lws_callback_on_writable(wsi);
            break;
        }
        default:
            break;
    }

    return 0;
}

static int interrupted;

void sigint_handler(int sig)
{
    interrupted = 1;
}

using namespace Urho3D;

WSServer::WSServer(Urho3D::Network* networkInstance):
    WSHandler(networkInstance)
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
    if (context) {
        int result = lws_service(context, 0);
        if (result < 0) {
            StopServer();
        }
        if (GetNumOutgoingPackets()) {
            URHO3D_LOGINFOF("Outgoing packet count (server) %d", GetNumOutgoingPackets());
            lws_callback_on_writable(GetOutgoingPacket().first_);
        }
        while (GetNumIncomingPackets()) {
            WSPacket& packet = GetIncomingPacket();
            networkInstance_->HandleIncomingPacket(packet.first_, packet.second_, true);
            RemoveIncomingPacket();
        }
    }
}

void WSServer::StopServer()
{
    lws_context_destroy(context);
    context = nullptr;
}

#endif
