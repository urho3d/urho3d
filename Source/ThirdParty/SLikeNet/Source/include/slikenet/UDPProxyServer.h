/*
 *  Original work: Copyright (c) 2014, Oculus VR, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the BSD-style license found in the
 *  RakNet License.txt file in the licenses directory of this source tree. An additional grant 
 *  of patent rights can be found in the RakNet Patents.txt file in the same directory.
 *
 *
 *  Modified work: Copyright (c) 2017, SLikeSoft UG (haftungsbeschränkt)
 *
 *  This source code was modified by SLikeSoft. Modifications are licensed under the MIT-style
 *  license found in the license.txt file in the root directory of this source tree.
 */

/// \file
/// \brief A RakNet plugin performing networking to communicate with UDPProxyServer. It allows UDPProxyServer to control our instance of UDPForwarder.
///


#include "NativeFeatureIncludes.h"
#if _RAKNET_SUPPORT_UDPProxyServer==1 && _RAKNET_SUPPORT_UDPForwarder==1

#ifndef __UDP_PROXY_SERVER_H
#define __UDP_PROXY_SERVER_H

#include "Export.h"
#include "types.h"
#include "PluginInterface2.h"
#include "UDPForwarder.h"
#include "string.h"

namespace SLNet
{
class UDPProxyServer;

/// Callback to handle results of calling UDPProxyServer::LoginToCoordinator()
/// \ingroup UDP_PROXY_GROUP
struct UDPProxyServerResultHandler
{
	UDPProxyServerResultHandler() {}
	virtual ~UDPProxyServerResultHandler() {}

	/// Called when our login succeeds
	/// \param[out] usedPassword The password we passed to UDPProxyServer::LoginToCoordinator()
	/// \param[out] proxyServer The plugin calling this callback
	virtual void OnLoginSuccess(SLNet::RakString usedPassword, SLNet::UDPProxyServer *proxyServerPlugin)=0;

	/// We are already logged in.
	/// This login failed, but the system is operational as if it succeeded
	/// \param[out] usedPassword The password we passed to UDPProxyServer::LoginToCoordinator()
	/// \param[out] proxyServer The plugin calling this callback
	virtual void OnAlreadyLoggedIn(SLNet::RakString usedPassword, SLNet::UDPProxyServer *proxyServerPlugin)=0;

	/// The coordinator operator forgot to call UDPProxyCoordinator::SetRemoteLoginPassword()
	/// \param[out] usedPassword The password we passed to UDPProxyServer::LoginToCoordinator()
	/// \param[out] proxyServer The plugin calling this callback
	virtual void OnNoPasswordSet(SLNet::RakString usedPassword, SLNet::UDPProxyServer *proxyServerPlugin)=0;

	/// The coordinator operator set a different password in UDPProxyCoordinator::SetRemoteLoginPassword() than what we passed
	/// \param[out] usedPassword The password we passed to UDPProxyServer::LoginToCoordinator()
	/// \param[out] proxyServer The plugin calling this callback
	virtual void OnWrongPassword(SLNet::RakString usedPassword, SLNet::UDPProxyServer *proxyServerPlugin)=0;
};

/// \brief UDPProxyServer to control our instance of UDPForwarder
/// \details When NAT Punchthrough fails, it is possible to use a non-NAT system to forward messages from us to the recipient, and vice-versa.<BR>
/// The class to forward messages is UDPForwarder, and it is triggered over the network via the UDPProxyServer plugin.<BR>
/// The UDPProxyServer connects to UDPProxyServer to get a list of servers running UDPProxyServer, and the coordinator will relay our forwarding request.
/// \ingroup UDP_PROXY_GROUP
class RAK_DLL_EXPORT UDPProxyServer : public PluginInterface2
{
public:
	// GetInstance() and DestroyInstance(instance*)
	STATIC_FACTORY_DECLARATIONS(UDPProxyServer)

	UDPProxyServer();
	~UDPProxyServer();

	/// Sets the socket family to use, either IPV4 or IPV6
	/// \param[in] socketFamily For IPV4, use AF_INET (default). For IPV6, use AF_INET6. To autoselect, use AF_UNSPEC.
	void SetSocketFamily(unsigned short _socketFamily);

	/// Receives the results of calling LoginToCoordinator()
	/// Set before calling LoginToCoordinator or you won't know what happened
	/// \param[in] resultHandler 
	void SetResultHandler(UDPProxyServerResultHandler *rh);

	/// Before the coordinator will register the UDPProxyServer, you must login
	/// \pre Must be connected to the coordinator
	/// \pre Coordinator must have set a password with UDPProxyCoordinator::SetRemoteLoginPassword()
	/// \returns false if already logged in, or logging in. Returns true otherwise
	bool LoginToCoordinator(SLNet::RakString password, SystemAddress coordinatorAddress);

	/// \brief The server IP reported to the client is the IP address from the server to the coordinator.
	/// If the server and coordinator are on the same LAN, you need to call SetServerPublicIP() to tell the client what address to connect to
	/// \param[in] ip IP address to report in UDPProxyClientResultHandler::OnForwardingSuccess() and UDPProxyClientResultHandler::OnForwardingNotification() as proxyIPAddress
	void SetServerPublicIP(RakString ip);

	/// Operative class that performs the forwarding
	/// Exposed so you can call UDPForwarder::SetMaxForwardEntries() if you want to change away from the default
	/// UDPForwarder::Startup(), UDPForwarder::Shutdown(), and UDPForwarder::Update() are called automatically by the plugin
	UDPForwarder udpForwarder;

	virtual void OnAttach(void);
	virtual void OnDetach(void);

	/// \internal
	virtual void Update(void);
	virtual PluginReceiveResult OnReceive(Packet *packet);
	virtual void OnClosedConnection(const SystemAddress &systemAddress, RakNetGUID rakNetGUID, PI2_LostConnectionReason lostConnectionReason );
	virtual void OnRakPeerStartup(void);
	virtual void OnRakPeerShutdown(void);

protected:
	void OnForwardingRequestFromCoordinatorToServer(Packet *packet);

	DataStructures::OrderedList<SystemAddress, SystemAddress> loggingInCoordinators;
	DataStructures::OrderedList<SystemAddress, SystemAddress> loggedInCoordinators;

	UDPProxyServerResultHandler *resultHandler;
	unsigned short socketFamily;
	RakString serverPublicIp;

};

} // End namespace

#endif

#endif // _RAKNET_SUPPORT_*
