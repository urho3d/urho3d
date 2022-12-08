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
/// \brief Router2 plugin. Allows you to connect to a system by routing packets through another system that is connected to both you and the destination. Useful for getting around NATs.
///


#include "NativeFeatureIncludes.h"
#if _RAKNET_SUPPORT_Router2==1 && _RAKNET_SUPPORT_UDPForwarder==1

#ifndef __ROUTER_2_PLUGIN_H
#define __ROUTER_2_PLUGIN_H

#include "types.h"
#include "PluginInterface2.h"
#include "PacketPriority.h"
#include "Export.h"
#include "UDPForwarder.h"
#include "MessageIdentifiers.h"
#include "DS_List.h"
#include "SimpleMutex.h"

namespace SLNet
{
/// Forward declarations
class RakPeerInterface;

struct Router2DebugInterface
{
	Router2DebugInterface() {}
	virtual ~Router2DebugInterface() {}
	virtual void ShowFailure(const char *message);
	virtual void ShowDiagnostic(const char *message);
};

/// \defgroup ROUTER_2_GROUP Router2
/// \brief Part of the NAT punchthrough solution, allowing you to connect to systems by routing through a shared connection.
/// \details Router2 routes datagrams between two systems that are not directly connected by using the bandwidth of a third system, to which the other two systems were connected
/// It is of benefit when a fully connected mesh topology is desired, but could not be completely established due to routers and/or firewalls
/// As the system address of a remote system will be the system address of the intermediary, it is necessary to use the RakNetGUID object to refer to systems, including with other plugins
/// \ingroup PLUGINS_GROUP

/// \ingroup ROUTER_2_GROUP
/// \brief Class interface for the Router2 system
/// \details
class RAK_DLL_EXPORT Router2 : public PluginInterface2
{
public:
	// GetInstance() and DestroyInstance(instance*)
	STATIC_FACTORY_DECLARATIONS(Router2)

	Router2();
	virtual ~Router2();

	/// Sets the socket family to use, either IPV4 or IPV6
	/// \param[in] socketFamily For IPV4, use AF_INET (default). For IPV6, use AF_INET6. To autoselect, use AF_UNSPEC.
	void SetSocketFamily(unsigned short _socketFamily);

	/// \brief Query all connected systems to connect through them to a third system.
	/// System will return ID_ROUTER_2_FORWARDING_NO_PATH if unable to connect.
	/// Else you will get ID_ROUTER_2_FORWARDING_ESTABLISHED
	///
	/// On ID_ROUTER_2_FORWARDING_ESTABLISHED, EstablishRouting as follows:
	///
	/// SLNet::BitStream bs(packet->data, packet->length, false);
	/// bs.IgnoreBytes(sizeof(MessageID));
	/// RakNetGUID endpointGuid;
	/// bs.Read(endpointGuid);
	/// unsigned short sourceToDestPort;
	/// bs.Read(sourceToDestPort);
	/// char ipAddressString[32];
	/// packet->systemAddress.ToString(false, ipAddressString);
	/// rakPeerInterface->EstablishRouting(ipAddressString, sourceToDestPort, 0,0);
	///
	/// \note The SystemAddress for a connection should not be used - always use RakNetGuid as the address can change at any time.
	/// When the address changes, you will get ID_ROUTER_2_REROUTED
	void EstablishRouting(RakNetGUID endpointGuid);

	/// Set the maximum number of bidirectional connections this system will support
	/// Defaults to 0
	void SetMaximumForwardingRequests(int max);

	/// For testing and debugging
	void SetDebugInterface(Router2DebugInterface *_debugInterface);

	/// Get the pointer passed to SetDebugInterface()
	Router2DebugInterface *GetDebugInterface(void) const;

	// --------------------------------------------------------------------------------------------
	// Packet handling functions
	// --------------------------------------------------------------------------------------------
	virtual PluginReceiveResult OnReceive(Packet *packet);
	virtual void Update(void);
	virtual void OnClosedConnection(const SystemAddress &systemAddress, RakNetGUID rakNetGUID, PI2_LostConnectionReason lostConnectionReason );
	virtual void OnFailedConnectionAttempt(Packet *packet, PI2_FailedConnectionAttemptReason failedConnectionAttemptReason);
	virtual void OnRakPeerShutdown(void);


	enum Router2RequestStates
	{
		R2RS_REQUEST_STATE_QUERY_FORWARDING,
		REQUEST_STATE_REQUEST_FORWARDING,
	};

	struct ConnectionRequestSystem
	{
		RakNetGUID guid;
		int pingToEndpoint;
		unsigned short usedForwardingEntries;
	};

	struct ConnnectRequest
	{
		ConnnectRequest();
		~ConnnectRequest();

		DataStructures::List<ConnectionRequestSystem> connectionRequestSystems;
		SimpleMutex connectionRequestSystemsMutex;
		Router2RequestStates requestState;
		SLNet::TimeMS pingTimeout;
		RakNetGUID endpointGuid;
		RakNetGUID lastRequestedForwardingSystem;
		bool returnConnectionLostOnFailure;
		unsigned int GetGuidIndex(RakNetGUID guid);
	};

	unsigned int GetConnectionRequestIndex(RakNetGUID endpointGuid);

	struct MiniPunchRequest
	{
		RakNetGUID endpointGuid;
		SystemAddress endpointAddress;
		bool gotReplyFromEndpoint;
		RakNetGUID sourceGuid;
		SystemAddress sourceAddress;
		bool gotReplyFromSource;
		SLNet::TimeMS timeout;
		SLNet::TimeMS nextAction;
		unsigned short forwardingPort;
		__UDPSOCKET__ forwardingSocket;
	};

	struct ForwardedConnection
	{
		RakNetGUID endpointGuid;
		RakNetGUID intermediaryGuid;
		SystemAddress intermediaryAddress;
		bool returnConnectionLostOnFailure;
		bool weInitiatedForwarding;
	};

protected:

	bool UpdateForwarding(ConnnectRequest* connectionRequest);
	void RemoveConnectionRequest(unsigned int connectionRequestIndex);
	void RequestForwarding(ConnnectRequest* connectionRequest);
	void OnQueryForwarding(Packet *packet);
	void OnQueryForwardingReply(Packet *packet);
	void OnRequestForwarding(Packet *packet);
	void OnRerouted(Packet *packet);
	void OnMiniPunchReply(Packet *packet);
	void OnMiniPunchReplyBounce(Packet *packet);
	bool OnForwardingSuccess(Packet *packet);
	int GetLargestPingAmongConnectedSystems(void) const;
	void ReturnToUser(MessageID messageId, RakNetGUID endpointGuid, const SystemAddress &systemAddress, bool wasGeneratedLocally);
	bool ConnectInternal(RakNetGUID endpointGuid, bool returnConnectionLostOnFailure);

	UDPForwarder *udpForwarder;
	int maximumForwardingRequests;
	SimpleMutex connectionRequestsMutex, miniPunchesInProgressMutex, forwardedConnectionListMutex;
	DataStructures::List<ConnnectRequest*> connectionRequests;
	DataStructures::List<MiniPunchRequest> miniPunchesInProgress;
	// Forwarding we have initiated
	DataStructures::List<ForwardedConnection> forwardedConnectionList;

	void ClearConnectionRequests(void);
	void ClearMinipunches(void);
	void ClearForwardedConnections(void);
	void ClearAll(void);
	int ReturnFailureOnCannotForward(RakNetGUID sourceGuid, RakNetGUID endpointGuid);
	void SendFailureOnCannotForward(RakNetGUID sourceGuid, RakNetGUID endpointGuid);
	void SendForwardingSuccess(MessageID messageId, RakNetGUID sourceGuid, RakNetGUID endpointGuid, unsigned short sourceToDstPort);
	void SendOOBFromRakNetPort(OutOfBandIdentifiers oob, BitStream *extraData, SystemAddress sa);
	void SendOOBFromSpecifiedSocket(OutOfBandIdentifiers oob, SystemAddress sa, __UDPSOCKET__ socket);
	void SendOOBMessages(MiniPunchRequest *mpr);

	Router2DebugInterface *debugInterface;
	unsigned short socketFamily;
};

}

#endif

#endif // _RAKNET_SUPPORT_*
