/*
 *  Original work: Copyright (c) 2014, Oculus VR, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the BSD-style license found in the
 *  RakNet License.txt file in the licenses directory of this source tree. An additional grant 
 *  of patent rights can be found in the RakNet Patents.txt file in the same directory.
 *
 *
 *  Modified work: Copyright (c) 2016-2017, SLikeSoft UG (haftungsbeschränkt)
 *
 *  This source code was modified by SLikeSoft. Modifications are licensed under the MIT-style
 *  license found in the license.txt file in the root directory of this source tree.
 */

/// \file
/// \brief A RakNet plugin performing networking to communicate with UDPProxyCoordinator. Ultimately used to tell UDPProxyServer to forward UDP packets.


#include "NativeFeatureIncludes.h"
#if _RAKNET_SUPPORT_UDPProxyClient==1

#ifndef __UDP_PROXY_CLIENT_H
#define __UDP_PROXY_CLIENT_H

#include "Export.h"
#include "types.h"
#include "PluginInterface2.h"
#include "DS_List.h"

/// \defgroup UDP_PROXY_GROUP UDPProxy
/// \brief Forwards UDP datagrams from one system to another. Protocol independent
/// \details Used when NatPunchthroughClient fails
/// \ingroup PLUGINS_GROUP

namespace SLNet
{
class UDPProxyClient;

/// Callback to handle results of calling UDPProxyClient::RequestForwarding()
/// \ingroup UDP_PROXY_GROUP
struct UDPProxyClientResultHandler
{
	UDPProxyClientResultHandler() {}
	virtual ~UDPProxyClientResultHandler() {}

	/// Called when our forwarding request was completed. We can now connect to \a targetAddress by using \a proxyAddress instead
	/// \param[out] proxyIPAddress IP Address of the proxy server, which will forward messages to targetAddress
	/// \param[out] proxyPort Remote port to use on the proxy server, which will forward messages to targetAddress
	/// \param[out] proxyCoordinator \a proxyCoordinator parameter originally passed to UDPProxyClient::RequestForwarding
	/// \param[out] sourceAddress \a sourceAddress parameter passed to UDPProxyClient::RequestForwarding. If it was UNASSIGNED_SYSTEM_ADDRESS, it is now our external IP address.
	/// \param[out] targetAddress \a targetAddress parameter originally passed to UDPProxyClient::RequestForwarding
	/// \param[out] targetGuid \a targetGuid parameter originally passed to UDPProxyClient::RequestForwarding
	/// \param[out] proxyClient The plugin that is calling this callback
	virtual void OnForwardingSuccess(const char *proxyIPAddress, unsigned short proxyPort,
		SystemAddress proxyCoordinator, SystemAddress sourceAddress, SystemAddress targetAddress, RakNetGUID targetGuid, SLNet::UDPProxyClient *proxyClientPlugin)=0;

	/// Called when another system has setup forwarding, with our system as the target address.
	/// Plugin automatically sends a datagram to proxyIPAddress before this callback, to open our router if necessary.
	/// \param[out] proxyIPAddress IP Address of the proxy server, which will forward messages to targetAddress
	/// \param[out] proxyPort Remote port to use on the proxy server, which will forward messages to targetAddress
	/// \param[out] proxyCoordinator \a proxyCoordinator parameter originally passed to UDPProxyClient::RequestForwarding
	/// \param[out] sourceAddress \a sourceAddress parameter passed to UDPProxyClient::RequestForwarding. This is originating source IP address of the remote system that will be sending to us.
	/// \param[out] targetAddress \a targetAddress parameter originally passed to UDPProxyClient::RequestForwarding. This is our external IP address.
	/// \param[out] targetGuid \a targetGuid parameter originally passed to UDPProxyClient::RequestForwarding
	/// \param[out] proxyClient The plugin that is calling this callback
	virtual void OnForwardingNotification(const char *proxyIPAddress, unsigned short proxyPort,
		SystemAddress proxyCoordinator, SystemAddress sourceAddress, SystemAddress targetAddress, RakNetGUID targetGuid, SLNet::UDPProxyClient *proxyClientPlugin)=0;

	/// Called when our forwarding request failed, because no UDPProxyServers are connected to UDPProxyCoordinator
	/// \param[out] proxyCoordinator \a proxyCoordinator parameter originally passed to UDPProxyClient::RequestForwarding
	/// \param[out] sourceAddress \a sourceAddress parameter passed to UDPProxyClient::RequestForwarding. If it was UNASSIGNED_SYSTEM_ADDRESS, it is now our external IP address.
	/// \param[out] targetAddress \a targetAddress parameter originally passed to UDPProxyClient::RequestForwarding
	/// \param[out] targetGuid \a targetGuid parameter originally passed to UDPProxyClient::RequestForwarding
	/// \param[out] proxyClient The plugin that is calling this callback
	virtual void OnNoServersOnline(SystemAddress proxyCoordinator, SystemAddress sourceAddress, SystemAddress targetAddress, RakNetGUID targetGuid, SLNet::UDPProxyClient *proxyClientPlugin)=0;

	/// Called when our forwarding request failed, because no UDPProxyServers are connected to UDPProxyCoordinator
	/// \param[out] proxyCoordinator \a proxyCoordinator parameter originally passed to UDPProxyClient::RequestForwarding
	/// \param[out] sourceAddress \a sourceAddress parameter passed to UDPProxyClient::RequestForwarding. If it was UNASSIGNED_SYSTEM_ADDRESS, it is now our external IP address.
	/// \param[out] targetAddress \a targetAddress parameter originally passed to UDPProxyClient::RequestForwarding
	/// \param[out] targetGuid \a targetGuid parameter originally passed to UDPProxyClient::RequestForwarding
	/// \param[out] proxyClient The plugin that is calling this callback
	virtual void OnRecipientNotConnected(SystemAddress proxyCoordinator, SystemAddress sourceAddress, SystemAddress targetAddress, RakNetGUID targetGuid, SLNet::UDPProxyClient *proxyClientPlugin)=0;

	/// Called when our forwarding request failed, because all UDPProxyServers that are connected to UDPProxyCoordinator are at their capacity
	/// Either add more servers, or increase capacity via UDPForwarder::SetMaxForwardEntries()
	/// \param[out] proxyCoordinator \a proxyCoordinator parameter originally passed to UDPProxyClient::RequestForwarding
	/// \param[out] sourceAddress \a sourceAddress parameter passed to UDPProxyClient::RequestForwarding. If it was UNASSIGNED_SYSTEM_ADDRESS, it is now our external IP address.
	/// \param[out] targetAddress \a targetAddress parameter originally passed to UDPProxyClient::RequestForwarding
	/// \param[out] targetGuid \a targetGuid parameter originally passed to UDPProxyClient::RequestForwarding
	/// \param[out] proxyClient The plugin that is calling this callback
	virtual void OnAllServersBusy(SystemAddress proxyCoordinator, SystemAddress sourceAddress, SystemAddress targetAddress, RakNetGUID targetGuid, SLNet::UDPProxyClient *proxyClientPlugin)=0;

	/// Called when our forwarding request is already in progress on the \a proxyCoordinator.
	/// This can be ignored, but indicates an unneeded second request
	/// \param[out] proxyIPAddress IP Address of the proxy server, which is forwarding messages to targetAddress
	/// \param[out] proxyPort Remote port to use on the proxy server, which is forwarding messages to targetAddress
	/// \param[out] proxyCoordinator \a proxyCoordinator parameter originally passed to UDPProxyClient::RequestForwarding
	/// \param[out] sourceAddress \a sourceAddress parameter passed to UDPProxyClient::RequestForwarding. If it was UNASSIGNED_SYSTEM_ADDRESS, it is now our external IP address.
	/// \param[out] targetAddress \a targetAddress parameter originally passed to UDPProxyClient::RequestForwarding
	/// \param[out] targetGuid \a targetGuid parameter originally passed to UDPProxyClient::RequestForwarding
	/// \param[out] proxyClient The plugin that is calling this callback
	virtual void OnForwardingInProgress(const char *proxyIPAddress, unsigned short proxyPort, SystemAddress proxyCoordinator, SystemAddress sourceAddress, SystemAddress targetAddress, RakNetGUID targetGuid, SLNet::UDPProxyClient *proxyClientPlugin)=0;
};


/// \brief Communicates with UDPProxyCoordinator, in order to find a UDPProxyServer to forward our datagrams.
/// \details When NAT Punchthrough fails, it is possible to use a non-NAT system to forward messages from us to the recipient, and vice-versa.<BR>
/// The class to forward messages is UDPForwarder, and it is triggered over the network via the UDPProxyServer plugin.<BR>
/// The UDPProxyClient connects to UDPProxyCoordinator to get a list of servers running UDPProxyServer, and the coordinator will relay our forwarding request
/// \sa NatPunchthroughServer
/// \sa NatPunchthroughClient
/// \ingroup UDP_PROXY_GROUP
class RAK_DLL_EXPORT UDPProxyClient : public PluginInterface2
{
public:
	// GetInstance() and DestroyInstance(instance*)
	STATIC_FACTORY_DECLARATIONS(UDPProxyClient)

	UDPProxyClient();
	~UDPProxyClient();

	/// Receives the results of calling RequestForwarding()
	/// Set before calling RequestForwarding or you won't know what happened
	/// \param[in] resultHandler 
	void SetResultHandler(UDPProxyClientResultHandler *rh);

	/// Sends a request to proxyCoordinator to find a server and have that server setup UDPForwarder::StartForwarding() on our address to \a targetAddressAsSeenFromCoordinator
	/// The forwarded datagrams can be from any UDP source, not just RakNet
	/// \pre Must be connected to \a proxyCoordinator
	/// \pre Systems running UDPProxyServer must be connected to \a proxyCoordinator and logged in via UDPProxyCoordinator::LoginServer() or UDPProxyServer::LoginToCoordinator()
	/// \note May still fail, if all proxy servers have no open connections.
	/// \note RakNet's protocol will ensure a message is sent at least every 5 seconds, so if routing RakNet messages, it is a reasonable value for timeoutOnNoDataMS, plus an extra few seconds for latency.
	/// \param[in] proxyCoordinator System we are connected to that is running the UDPProxyCoordinator plugin
	/// \param[in] sourceAddress External IP address of the system we want to forward messages from. This does not have to be our own system. To specify our own system, you can pass UNASSIGNED_SYSTEM_ADDRESS which the coordinator will treat as our external IP address.
	/// \param[in] targetAddressAsSeenFromCoordinator External IP address of the system we want to forward messages to. If this system is connected to UDPProxyCoordinator at this address using RakNet, that system will ping the server and thus open the router for incoming communication. In any other case, you are responsible for doing your own network communication to have that system ping the server. See also targetGuid in the other version of RequestForwarding(), to avoid the need to know the IP address to the coordinator of the destination.
	/// \param[in] timeoutOnNoData If no data is sent by the forwarded systems, how long before removing the forward entry from UDPForwarder? UDP_FORWARDER_MAXIMUM_TIMEOUT is the maximum value. Recommended 10 seconds.
	/// \param[in] serverSelectionBitstream If you want to send data to UDPProxyCoordinator::GetBestServer(), write it here
	/// \return true if the request was sent, false if we are not connected to proxyCoordinator
	bool RequestForwarding(SystemAddress proxyCoordinator, SystemAddress sourceAddress, SystemAddress targetAddressAsSeenFromCoordinator, SLNet::TimeMS timeoutOnNoDataMS, SLNet::BitStream *serverSelectionBitstream=0);

	/// Same as above, but specify the target with a GUID, in case you don't know what its address is to the coordinator
	/// If requesting forwarding to a RakNet enabled system, then it is easier to use targetGuid instead of targetAddressAsSeenFromCoordinator
	bool RequestForwarding(SystemAddress proxyCoordinator, SystemAddress sourceAddress, RakNetGUID targetGuid, SLNet::TimeMS timeoutOnNoDataMS, SLNet::BitStream *serverSelectionBitstream=0);

	/// \internal
	virtual void Update(void);
	virtual PluginReceiveResult OnReceive(Packet *packet);
	virtual void OnRakPeerShutdown(void);
	
	struct ServerWithPing
	{
		unsigned short ping;
		SystemAddress serverAddress;
	};
	struct SenderAndTargetAddress
	{
		SystemAddress senderClientAddress;
		SystemAddress targetClientAddress;
	};
	struct PingServerGroup
	{
		SenderAndTargetAddress sata;
		SLNet::TimeMS startPingTime;
		SystemAddress coordinatorAddressForPings;
		//DataStructures::Multilist<ML_UNORDERED_LIST, ServerWithPing> serversToPing;
		DataStructures::List<ServerWithPing> serversToPing;
		bool AreAllServersPinged(void) const;
		void SendPingedServersToCoordinator(RakPeerInterface *rakPeer);
	};
	//DataStructures::Multilist<ML_UNORDERED_LIST, PingServerGroup*> pingServerGroups;
	DataStructures::List<PingServerGroup*> pingServerGroups;
protected:

	void OnPingServers(Packet *packet);
	void Clear(void);
	UDPProxyClientResultHandler *resultHandler;

};

} // End namespace

#endif

#endif // _RAKNET_SUPPORT_*
