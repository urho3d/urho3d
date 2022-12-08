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
/// \brief Contains the NAT-punchthrough plugin for the client.
///

#include "NativeFeatureIncludes.h"
#if _RAKNET_SUPPORT_NatPunchthroughClient==1

#ifndef __NAT_PUNCHTHROUGH_CLIENT_H
#define __NAT_PUNCHTHROUGH_CLIENT_H

#include "types.h"
#include "Export.h"
#include "PluginInterface2.h"
#include "PacketPriority.h"
#include "SocketIncludes.h"
#include "DS_List.h"
#include "string.h"
#include "DS_Queue.h"

// Trendnet TEW-632BRP sometimes starts at port 1024 and increments sequentially.
// Zonnet zsr1134we. Replies go out on the net, but are always absorbed by the remote router??
// Dlink ebr2310 to Trendnet ok
// Trendnet TEW-652BRP to Trendnet 632BRP OK
// Trendnet TEW-632BRP to Trendnet 632BRP OK
// Buffalo WHR-HP-G54 OK
// Netgear WGR614 ok

namespace SLNet
{
/// Forward declarations
class RakPeerInterface;
struct Packet;
#if _RAKNET_SUPPORT_PacketLogger==1
class PacketLogger;
#endif

/// \ingroup NAT_PUNCHTHROUGH_GROUP
struct RAK_DLL_EXPORT PunchthroughConfiguration
{
	/// internal: (15 ms * 2 tries + 30 wait) * 5 ports * 8 players = 2.4 seconds
	/// external: (50 ms * 8 sends + 200 wait) * 2 port * 8 players = 9.6 seconds
	/// Total: 8 seconds
	PunchthroughConfiguration() {
		TIME_BETWEEN_PUNCH_ATTEMPTS_INTERNAL=15;
		TIME_BETWEEN_PUNCH_ATTEMPTS_EXTERNAL=50;
		UDP_SENDS_PER_PORT_INTERNAL=2;
		UDP_SENDS_PER_PORT_EXTERNAL=8;
		INTERNAL_IP_WAIT_AFTER_ATTEMPTS=30;
		MAXIMUM_NUMBER_OF_INTERNAL_IDS_TO_CHECK=5; /// set to 0 to not do lan connects
		MAX_PREDICTIVE_PORT_RANGE=2;
		EXTERNAL_IP_WAIT_BETWEEN_PORTS=200;
		EXTERNAL_IP_WAIT_AFTER_FIRST_TTL=100;
		EXTERNAL_IP_WAIT_AFTER_ALL_ATTEMPTS=EXTERNAL_IP_WAIT_BETWEEN_PORTS;
		retryOnFailure=false;
	}

	/// How much time between each UDP send
	SLNet::Time TIME_BETWEEN_PUNCH_ATTEMPTS_INTERNAL;
	SLNet::Time TIME_BETWEEN_PUNCH_ATTEMPTS_EXTERNAL;

	/// How many tries for one port before giving up and going to the next port
	int UDP_SENDS_PER_PORT_INTERNAL;
	int UDP_SENDS_PER_PORT_EXTERNAL;

	/// After giving up on one internal port, how long to wait before trying the next port
	int INTERNAL_IP_WAIT_AFTER_ATTEMPTS;

	/// How many external ports to try past the last known starting port
	int MAX_PREDICTIVE_PORT_RANGE;

	/// After sending TTL, how long to wait until first punch attempt
	int EXTERNAL_IP_WAIT_AFTER_FIRST_TTL;

	/// After giving up on one external  port, how long to wait before trying the next port
	int EXTERNAL_IP_WAIT_BETWEEN_PORTS;

	/// After trying all external ports, how long to wait before returning ID_NAT_PUNCHTHROUGH_FAILED
	int EXTERNAL_IP_WAIT_AFTER_ALL_ATTEMPTS;

	/// Maximum number of internal IP address to try to connect to.
	/// Cannot be greater than MAXIMUM_NUMBER_OF_INTERNAL_IDS
	/// Should be high enough to try all internal IP addresses on the majority of computers
	int MAXIMUM_NUMBER_OF_INTERNAL_IDS_TO_CHECK;

	/// If the first punchthrough attempt fails, try again
	/// This sometimes works because the remote router was looking for an incoming message on a higher numbered port before responding to a lower numbered port from the other system
	bool retryOnFailure;
};

/// \ingroup NAT_PUNCHTHROUGH_GROUP
struct RAK_DLL_EXPORT NatPunchthroughDebugInterface
{
	NatPunchthroughDebugInterface() {}
	virtual ~NatPunchthroughDebugInterface() {}
	virtual void OnClientMessage(const char *msg)=0;
};

/// \ingroup NAT_PUNCHTHROUGH_GROUP
struct RAK_DLL_EXPORT NatPunchthroughDebugInterface_Printf : public NatPunchthroughDebugInterface
{
	virtual void OnClientMessage(const char *msg);
};

#if _RAKNET_SUPPORT_PacketLogger==1
/// \ingroup NAT_PUNCHTHROUGH_GROUP
struct RAK_DLL_EXPORT NatPunchthroughDebugInterface_PacketLogger : public NatPunchthroughDebugInterface
{
	// Set to non-zero to write to the packetlogger!
	PacketLogger *pl;

	NatPunchthroughDebugInterface_PacketLogger() {pl=0;}
	~NatPunchthroughDebugInterface_PacketLogger() {}
	virtual void OnClientMessage(const char *msg);
};
#endif

/// \brief Client code for NATPunchthrough
/// \details Maintain connection to NatPunchthroughServer to process incoming connection attempts through NatPunchthroughClient<BR>
/// Client will send datagrams to port to estimate next port<BR>
/// Will simultaneously connect with another client once ports are estimated.
/// \sa NatTypeDetectionClient
/// See also http://www.jenkinssoftware.com/raknet/manual/natpunchthrough.html
/// \ingroup NAT_PUNCHTHROUGH_GROUP
class RAK_DLL_EXPORT NatPunchthroughClient : public PluginInterface2
{
public:

	// GetInstance() and DestroyInstance(instance*)
	STATIC_FACTORY_DECLARATIONS(NatPunchthroughClient)

	NatPunchthroughClient();
	~NatPunchthroughClient();

	/// If the instance of RakPeer running NATPunchthroughServer was bound to two IP addresses, then you can call FindRouterPortStride()
	/// This will determine the stride that your router uses when assigning ports, if your router is full-cone
	/// This function is also called automatically when you call OpenNAT - however, calling it earlier when you are connected to the facilitator will speed up the process
	/// \param[in] destination The system to punch. Must already be connected to \a facilitator
	void FindRouterPortStride(const SystemAddress &facilitator);

	/// Punchthrough a NAT. Doesn't connect, just tries to setup the routing table
	/// \param[in] destination The system to punch. Must already be connected to \a facilitator
	/// \param[in] facilitator A system we are already connected to running the NatPunchthroughServer plugin
	/// \sa OpenNATGroup()
	/// You will get ID_NAT_PUNCHTHROUGH_SUCCEEDED on success
	/// You will get ID_NAT_TARGET_NOT_CONNECTED, ID_NAT_TARGET_UNRESPONSIVE, ID_NAT_CONNECTION_TO_TARGET_LOST, ID_NAT_ALREADY_IN_PROGRESS, or ID_NAT_PUNCHTHROUGH_FAILED on failures of various types
	/// However, if you lose connection to the facilitator, you may not necessarily get above
	bool OpenNAT(RakNetGUID destination, const SystemAddress &facilitator);

	/*
	/// \deprecated See FullyConnectedMesh2::StartVerifiedJoin() which is more flexible
	/// Same as calling OpenNAT for a list of systems, but reply is delayed until all systems pass.
	/// This is useful for peer to peer games where you want to connect to every system in the remote session, not just one particular system
	/// \note For cloud computing, all systems in the group must be connected to the same facilitator since we're only specifying one
	/// You will get ID_NAT_GROUP_PUNCH_SUCCEEDED on success
	/// You will get ID_NAT_TARGET_NOT_CONNECTED, ID_NAT_ALREADY_IN_PROGRESS, or ID_NAT_GROUP_PUNCH_FAILED on failures of various types
	/// However, if you lose connection to the facilitator, you may not necessarily get above
	bool OpenNATGroup(DataStructures::List<RakNetGUID> destinationSystems, const SystemAddress &facilitator);
	*/

	/// Modify the system configuration if desired
	/// Don't modify the variables in the structure while punchthrough is in progress
	PunchthroughConfiguration* GetPunchthroughConfiguration(void);

	/// Sets a callback to be called with debug messages
	/// \param[in] i Pointer to an interface. The pointer is stored, so don't delete it while in progress. Pass 0 to clear.
	void SetDebugInterface(NatPunchthroughDebugInterface *i);

	/// Get the port mappings you should pass to UPNP (for miniupnpc-1.6.20120410, for the function UPNP_AddPortMapping)
	void GetUPNPPortMappings(char *externalPort, char *internalPort, const SystemAddress &natPunchthroughServerAddress);

	/// \internal For plugin handling
	virtual void Update(void);

	/// \internal For plugin handling
	virtual PluginReceiveResult OnReceive(Packet *packet);

	/// \internal For plugin handling
	virtual void OnNewConnection(const SystemAddress &systemAddress, RakNetGUID rakNetGUID, bool isIncoming);

	/// \internal For plugin handling
	virtual void OnClosedConnection(const SystemAddress &systemAddress, RakNetGUID rakNetGUID, PI2_LostConnectionReason lostConnectionReason );

	virtual void OnAttach(void);
	virtual void OnDetach(void);
	virtual void OnRakPeerShutdown(void);
	void Clear(void);

	struct SendPing
	{
		SLNet::Time nextActionTime;
		SystemAddress targetAddress;
		SystemAddress facilitator;
		SystemAddress internalIds[MAXIMUM_NUMBER_OF_INTERNAL_IDS];
		RakNetGUID targetGuid;
		bool weAreSender;
		int attemptCount;
		int retryCount;
		int punchingFixedPortAttempts; // only used for TestMode::PUNCHING_FIXED_PORT
		uint16_t sessionId;
		bool sentTTL;
		// Give priority to internal IP addresses because if we are on a LAN, we don't want to try to connect through the internet
		enum TestMode
		{
			TESTING_INTERNAL_IPS,
			WAITING_FOR_INTERNAL_IPS_RESPONSE,
			//SEND_WITH_TTL,
			TESTING_EXTERNAL_IPS_FACILITATOR_PORT_TO_FACILITATOR_PORT,
			TESTING_EXTERNAL_IPS_1024_TO_FACILITATOR_PORT,
			TESTING_EXTERNAL_IPS_FACILITATOR_PORT_TO_1024,
			TESTING_EXTERNAL_IPS_1024_TO_1024,
			WAITING_AFTER_ALL_ATTEMPTS,

			// The trendnet remaps the remote port to 1024.
			// If you continue punching on a different port for the same IP it bans you and the communication becomes unidirectioal
			PUNCHING_FIXED_PORT,

			// try port 1024-1028
		} testMode;
	} sp;

protected:
	unsigned short mostRecentExternalPort;
	//void OnNatGroupPunchthroughRequest(Packet *packet);
	void OnFailureNotification(Packet *packet);
	//void OnNatGroupPunchthroughReply(Packet *packet);
	void OnGetMostRecentPort(Packet *packet);
	void OnConnectAtTime(Packet *packet);
	unsigned int GetPendingOpenNATIndex(RakNetGUID destination, const SystemAddress &facilitator);
	void SendPunchthrough(RakNetGUID destination, const SystemAddress &facilitator);
	void QueueOpenNAT(RakNetGUID destination, const SystemAddress &facilitator);
	void SendQueuedOpenNAT(void);
	void SendTTL(const SystemAddress &sa);
	void SendOutOfBand(SystemAddress sa, MessageID oobId);
	void OnPunchthroughFailure(void);
	void OnReadyForNextPunchthrough(void);
	void PushFailure(void);
	bool RemoveFromFailureQueue(void);
	void PushSuccess(void);

	PunchthroughConfiguration pc;
	NatPunchthroughDebugInterface *natPunchthroughDebugInterface;

	// The first time we fail a NAT attempt, we add it to failedAttemptList and try again, since sometimes trying again later fixes the problem
	// The second time we fail, we return ID_NAT_PUNCHTHROUGH_FAILED
	struct AddrAndGuid
	{
		SystemAddress addr;
		RakNetGUID guid;
	};
	DataStructures::List<AddrAndGuid> failedAttemptList;

	struct DSTAndFac
	{
		RakNetGUID destination;
		SystemAddress facilitator;
	};
	DataStructures::Queue<DSTAndFac> queuedOpenNat;

	void IncrementExternalAttemptCount(SLNet::Time time, SLNet::Time delta);
	unsigned short portStride;
	enum
	{
		HAS_PORT_STRIDE,
		UNKNOWN_PORT_STRIDE,
		CALCULATING_PORT_STRIDE,
		INCAPABLE_PORT_STRIDE
	} hasPortStride;
	SLNet::Time portStrideCalTimeout;

	/*
	struct TimeAndGuid
	{
		SLNet::Time time;
		RakNetGUID guid;
	};
	DataStructures::List<TimeAndGuid> groupRequestsInProgress;

	struct GroupPunchRequest
	{
		SystemAddress facilitator;
		DataStructures::List<RakNetGUID> pendingList;
		DataStructures::List<RakNetGUID> passedListGuid;
		DataStructures::List<SystemAddress> passedListAddress;
		DataStructures::List<RakNetGUID> failedList;
		DataStructures::List<RakNetGUID> ignoredList;
	};
	DataStructures::List<GroupPunchRequest*> groupPunchRequests;
	void UpdateGroupPunchOnNatResult(SystemAddress facilitator, RakNetGUID targetSystem, SystemAddress targetSystemAddress, int result); // 0=failed, 1=success, 2=ignore
	*/
};

} // namespace SLNet

#endif

#endif // _RAKNET_SUPPORT_*
