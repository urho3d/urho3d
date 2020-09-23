#include "WSClient.h"
#include "WSHandler.h"
#include "../Network.h"
#include "../../IO/MemoryBuffer.h"

#include <libwebsockets.h>
#include <string.h>
#include <signal.h>
#include "../../IO/Log.h"

const int ID_USER_PACKET_ENUM = 134;
static Urho3D::WSClient* WSClientInstance = nullptr;
static struct lws_context *context;

#if defined(WIN32)
#define HAVE_STRUCT_TIMESPEC
#if defined(pid_t)
#undef pid_t
#endif
#endif
#include <pthread.h>

static struct lws *client_wsi;
static int interrupted, port = 9292, ssl_connection = LCCSCF_USE_SSL;
static const char *server_address = "127.0.0.1", *pro = "ws-server";
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
    i.port = port;
    i.address = server_address;
    i.path = "/";
    i.host = i.address;
    i.origin = i.address;
//    i.ssl_connection = ssl_connection;
    i.protocol = pro; // Server protocol name to connect to
    i.alpn = "http/1.1";

    i.local_protocol_name = "ws_client";
    i.pwsi = &client_wsi;
//    i.retry_and_idle_policy = &retry;

    if (!lws_client_connect_via_info(&i))
        lws_sul_schedule(context, 0, _sul, connect_cb, 5 * LWS_USEC_PER_SEC);
}

static int ws_client_callback(struct lws *wsi, enum lws_callback_reasons reason, void *user, void *in, size_t len)
{
    URHO3D_LOGINFOF("Incoming client messsage reason %d", reason);
    switch (reason) {
        case LWS_CALLBACK_CLIENT_CLOSED:
            URHO3D_LOGINFOF("Connection closed from server!");
            break;
        case LWS_CALLBACK_CLIENT_CONNECTION_ERROR:
            lwsl_err("CLIENT_CONNECTION_ERROR: %s\n",
                     in ? (char *)in : "(null)");
            lws_sul_schedule(context, 0, &sul, connect_cb, 5 * LWS_USEC_PER_SEC);
            break;

        case LWS_CALLBACK_CLIENT_ESTABLISHED:
            if (WSClientInstance) {
                WSClientInstance->SetWSConnection(wsi);
                WSClientInstance->GetNetworkInstance()->OnServerConnected(wsi);
            }
            lwsl_user("%s: established\n", __func__);
            break;

        case LWS_CALLBACK_CLIENT_RECEIVE: {
            URHO3D_LOGINFOF("Received buffer of size %d", len);
            Urho3D::VectorBuffer b((unsigned char*)in, len);
            if (b.GetData()[0] == ID_USER_PACKET_ENUM) {
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
                if(WSClientInstance->GetNumOutgoingPackets()) {
                    WSPacket& packet = WSClientInstance->GetOutgoingPacket();
                    unsigned char buf[LWS_PRE + packet.second_.GetSize()];
                    memcpy(&buf[LWS_PRE], packet.second_.GetData(), packet.second_.GetSize());
                    int retval = lws_write(wsi, &buf[LWS_PRE], packet.second_.GetSize(), LWS_WRITE_BINARY);
                    if (retval < packet.second_.GetSize()) {
                        URHO3D_LOGERRORF("Failed to write to WS, ret = %d", retval);
                        break;
                    }
                    WSClientInstance->RemoveOutgoingPacket();
                }
                lws_callback_on_writable(wsi);
            }
            break;

        default:
            break;
    }

    return 0;
}

static const struct lws_protocols protocols[] = {
        {
                "ws_client",
                ws_client_callback,
                      0,
                         0,
        },
        { NULL, NULL, 0, 0 }
};

static void sigint_handler(int sig)
{
    interrupted = 1;
}

using namespace Urho3D;

WSClient::WSClient(Urho3D::Network *networkInstance):
WSHandler(networkInstance),
ws_(nullptr)
{
    WSClientInstance = this;
}

WSClient::~WSClient()
{
    WSClientInstance = nullptr;
}

int WSClient::Connect()
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
    lwsl_user("LWS minimal ws client PING\n");

    memset(&info, 0, sizeof info); /* otherwise uninitialized garbage */
//    info.options = LWS_SERVER_OPTION_DO_SSL_GLOBAL_INIT;
    info.port = CONTEXT_PORT_NO_LISTEN; /* we do not run any server */
    info.protocols = protocols;
#if defined(LWS_WITH_MBEDTLS) || defined(USE_WOLFSSL)
    /*
	 * OpenSSL uses the system trust store.  mbedTLS has to be told which
	 * CA to trust explicitly.
	 */
	info.client_ssl_ca_filepath = "./libwebsockets.org.cer";
#endif

//    info.fd_limit_per_thread = 1 + 1 + 1;

    context = lws_create_context(&info);
    if (!context) {
        lwsl_err("lws init failed\n");
        return 1;
    }

    lws_sul_schedule(context, 0, &sul, connect_cb, 50);
    return 0;
}

void WSClient::Update(float timestep)
{
    if (context) {
        int result = lws_service(context, 0);
        if (result < 0) {
            Disconnect();
        }
        while (GetNumIncomingPackets()) {
            WSPacket& packet = GetIncomingPacket();
            networkInstance_->HandleIncomingPacket(packet.first_, packet.second_, false);
            RemoveIncomingPacket();
        }
    }
}

void WSClient::Disconnect()
{
    lws_context_destroy(context);
    context = nullptr;
}

void WSClient::SetWSConnection(lws *ws)
{
    ws_ = ws;
}
