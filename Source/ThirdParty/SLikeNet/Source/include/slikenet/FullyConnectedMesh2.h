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

/// \file FullyConnectedMesh2.h
/// \brief Fully connected mesh plugin, revision 2.  
/// \details This will connect RakPeer to all connecting peers, and all peers the connecting peer knows about.
///


#include "NativeFeatureIncludes.h"
#if _RAKNET_SUPPORT_FullyConnectedMesh2==1

#ifndef __FULLY_CONNECTED_MESH_2_H
#define __FULLY_CONNECTED_MESH_2_H

#include "PluginInterface2.h"
#include "memoryoverride.h"
#include "NativeTypes.h"
#include "DS_List.h"
#include "string.h"
#include "BitStream.h"

typedef int64_t FCM2Guid;

namespace SLNet
{
/// Forward declarations
class RakPeerInterface;

/// \brief Fully connected mesh plugin, revision 2
/// \details This will connect RakPeer to all connecting peers, and all peers the connecting peer knows about.<BR>
/// It will also calculate which system has been running longest, to find out who should be host, if you need one system to act as a host
/// \pre You must also install the ConnectionGraph2 plugin in order to use SetConnectOnNewRemoteConnection()
/// \ingroup FULLY_CONNECTED_MESH_GROUP
class RAK_DLL_EXPORT FullyConnectedMesh2 : public PluginInterface2
{
public:
	// GetInstance() and DestroyInstance(instance*)
	STATIC_FACTORY_DECLARATIONS(FullyConnectedMesh2)

	FullyConnectedMesh2();
	virtual ~FullyConnectedMesh2();

	/// When the message ID_REMOTE_NEW_INCOMING_CONNECTION arrives, we try to connect to that system
	/// If \a attemptConnection is false, you can manually connect to all systems listed in ID_REMOTE_NEW_INCOMING_CONNECTION with ConnectToRemoteNewIncomingConnections()
	/// \note This will not work on any console. It will also not work if NAT punchthrough is needed. Generally, this should be false and you should connect manually. It is here for legacy reasons.
	/// \param[in] attemptConnection If true, we try to connect to any systems we are notified about with ID_REMOTE_NEW_INCOMING_CONNECTION, which comes from the ConnectionGraph2 plugin. Defaults to true.
	/// \param[in] pw The password to use to connect with. Only used if \a attemptConnection is true
	void SetConnectOnNewRemoteConnection(bool attemptConnection, SLNet::RakString pw);

	/// \brief The connected host is whichever system we are connected to that has been running the longest.
	/// \details Will return UNASSIGNED_RAKNET_GUID if we are not connected to anyone, or if we are connected and are calculating the host
	/// If includeCalculating is true, will return the estimated calculated host as long as the calculation is nearly complete
	/// includeCalculating should be true if you are taking action based on another system becoming host, because not all host calculations may complete at the exact same time
	/// \sa ConnectionGraph2::GetLowestAveragePingSystem() . If you need one system in the peer to peer group to relay data, have the host call this function after host migration, and use that system
	/// \return System address of whichever system is host. 
	RakNetGUID GetConnectedHost(void) const;
	SystemAddress GetConnectedHostAddr(void) const;

	/// \return System address of whichever system is host. Always returns something, even though it may be our own system.
	RakNetGUID GetHostSystem(void) const;

	/// \return If our system is host
	bool IsHostSystem(void) const;

	/// Get the list of connected systems, from oldest connected to newest
	/// This is also the order that the hosts will be chosen in
	void GetHostOrder(DataStructures::List<RakNetGUID> &hostList);

	/// \param[in] includeCalculating If true, and we are currently calculating a new host, return the new host if the calculation is nearly complete
	/// \return If our system is host
	bool IsConnectedHost(void) const;

	/// \brief Automatically add new connections to the fully connected mesh.
	/// Each remote system that you want to check should be added as a participant, either through SetAutoparticipateConnections() or by calling this function
	/// \details Defaults to true.
	/// \param[in] b As stated
	void SetAutoparticipateConnections(bool b);

	/// Clear our own host order, and recalculate as if we had just reconnected
	/// Call this to reset the running time of the host just before joining/creating a game room for networking
	void ResetHostCalculation(void);

	/// \brief if SetAutoparticipateConnections() is called with false, then you need to use AddParticipant before these systems will be added to the mesh 
	/// FullyConnectedMesh2 will track who is the who host among a fully connected mesh of participants
	/// Each remote system that you want to check should be added as a participant, either through SetAutoparticipateConnections() or by calling this function
	/// \param[in] participant The new participant
	/// \param[in] userContext Static data to be passed around with each participant, which can be queried with GetParticipantData().
	/// \sa StartVerifiedJoin()
	void AddParticipant(RakNetGUID rakNetGuid);

	/// Get the participants added with AddParticipant()
	/// \param[out] participantList Participants added with AddParticipant();
	void GetParticipantList(DataStructures::List<RakNetGUID> &participantList);

	/// \brief Returns if a participant is in the participant list
	/// \param[in] RakNetGUID of the participant to query
	/// \return True if in the list
	bool HasParticipant(RakNetGUID participantGuid);

	/// \brief Reads userData written with SetMyContext()
	/// \param[in] RakNetGUID of the participant to query
	/// \param[out] userContext Pointer to BitStream to be written to
	/// \return True if data was written
	// bool GetParticipantContext(RakNetGUID participantGuid, BitStream *userContext);

	/// Set data for other systems to read with GetParticipantContext
	/// \param[in] userContext Pointer to BitStream to be read from
	// void SetMyContext(BitStream *userContext);

	/// Connect to all systems from ID_REMOTE_NEW_INCOMING_CONNECTION
	/// You can call this if SetConnectOnNewRemoteConnection is false
	/// \param[in] packet The packet containing ID_REMOTE_NEW_INCOMING_CONNECTION
	/// \param[in] connectionPassword Password passed to RakPeerInterface::Connect()
	/// \param[in] connectionPasswordLength Password length passed to RakPeerInterface::Connect()
	void ConnectToRemoteNewIncomingConnections(Packet *packet);

	/// \brief Clear all memory and reset everything
	void Clear(void);

	unsigned int GetParticipantCount(void) const;
	void GetParticipantCount(unsigned int *participantListSize) const;

	/// In the simple case of forming a peer to peer mesh:
	///
	/// 1. AddParticipant() is called on the host whenever you get a new connection
	/// 2. The host sends all participants to the new client
	/// 3. The client connects to the participant list
	///
	/// However, the above steps assumes connections to all systems in the mesh always complete.
	/// When there is a risk of failure, such as if relying on NATPunchthroughClient, you may not want to call AddParticipant() until are connections have completed to all other particpants
	/// StartVerifiedJoin() can manage the overhead of the negotiation involved so the programmer only has to deal with overall success or failure
	///
	/// Processing:
	/// 1. Send the RakNetGUID and SystemAddress values of GetParticipantList() to the client with ID_FCM2_VERIFIED_JOIN_START
	/// 2. The client, on ID_FCM2_VERIFIED_JOIN_START, can execute NatPunchthroughClient::OpenNAT() (optional), followed by RakPeerInterface::Connect() if punchthrough success, for each system returned from GetVerifiedJoinRequiredProcessingList()
	/// 3. After all participants in step 2 have connected, failed to connect, or failed NatPunchthrough, the client automatically sends the results to the server.
	/// 4. The server compares the results of the operations in step 2 with the values from GetParticpantList().
	/// 4A. If the client failed to connect to a current participant, return ID_FCM2_VERIFIED_JOIN_FAILED to the client. CloseConnection() is automatically called on the client for the failed participants.
	/// 4B. If AddParticipant() was called between steps 1 and 4, go back to step 1, transmitting new participants.
	/// 4C. If the client successfully connected to all participants, the server gets ID_FCM2_VERIFIED_JOIN_CAPABLE. The server programmer, on the same frame, should execute RespondOnVerifiedJoinCapable() to either accept or reject the client.
	/// 5. If the client got ID_FCM2_VERIFIED_JOIN_ACCEPTED, AddParticipant() is automatically called for each system in the mesh.
	/// 6. If the client got ID_FCM2_VERIFIED_JOIN_REJECTED, CloseConnection() is automatically called for each system in the mesh. The connection is NOT automatically closed to the original host that sent StartVerifiedJoin().
	/// 7. If the client's connection to the server was lost before getting ID_FCM2_VERIFIED_JOIN_ACCEPTED or ID_FCM2_VERIFIED_JOIN_REJECTED, return to the programmer ID_FCM2_VERIFIED_JOIN_FAILED and call RakPeerInterface::CloseConnection() 
	///
	/// \brief Notify the client of GetParticipantList() in order to connect to each of those systems until the mesh has been completed
	/// \param[in] client The system to send ID_FCM2_VERIFIED_JOIN_START to
	virtual void StartVerifiedJoin(RakNetGUID client);
	
	/// \brief On ID_FCM2_VERIFIED_JOIN_CAPABLE , accept or reject the new connection
	/// \code
	/// fullyConnectedMesh->RespondOnVerifiedJoinCapable(packet, true, 0);
	/// \endcode
	/// \param[in] packet The system that sent ID_FCM2_VERIFIED_JOIN_CAPABLE. Based on \accept, ID_FCM2_VERIFIED_JOIN_ACCEPTED or ID_FCM2_VERIFIED_JOIN_REJECTED will be sent in reply
	/// \param[in] accept True to accept, and thereby automatically call AddParticipant() on all systems on the mesh. False to reject, and call CloseConnection() to all mesh systems on the target
	/// \param[in] additionalData Any additional data you want to add to the ID_FCM2_VERIFIED_JOIN_ACCEPTED or ID_FCM2_VERIFIED_JOIN_REJECTED messages
	/// \sa WriteVJCUserData()
	virtual void RespondOnVerifiedJoinCapable(Packet *packet, bool accept, BitStream *additionalData);

	/// \brief On ID_FCM2_VERIFIED_JOIN_START, read the SystemAddress and RakNetGUID values of each system to connect to
	/// \code
	/// DataStructures::List<SystemAddress> addresses;
	/// DataStructures::List<RakNetGUID> guids;
	/// fullyConnectedMesh->GetVerifiedJoinRequiredProcessingList(packet->guid, addresses, guids);
	/// for (unsigned int i=0; i < addresses.Size(); i++)
	///		rakPeer[i]->Connect(addresses[i].ToString(false), addresses[i].GetPort(), 0, 0);
	/// \endcode
	/// \param[in] host Which system sent ID_FCM2_VERIFIED_JOIN_START
	/// \param[out] addresses SystemAddress values of systems to connect to. List has the same number and order as \a guids
	/// \param[out] guids RakNetGUID values of systems to connect to. List has the same number and order as \a guids
	/// \param[out] userData What was written with WriteVJSUserData
	virtual void GetVerifiedJoinRequiredProcessingList(RakNetGUID host,
		DataStructures::List<SystemAddress> &addresses,
		DataStructures::List<RakNetGUID> &guids,
		DataStructures::List<BitStream*> &userData);

	/// \brief On ID_FCM2_VERIFIED_JOIN_ACCEPTED, read additional data passed to RespondOnVerifiedJoinCapable()
	/// \code
	/// bool thisSystemAccepted;
	/// DataStructures::List<RakNetGUID> systemsAccepted;
	/// SLNet::BitStream additionalData;
	/// fullyConnectedMesh->GetVerifiedJoinAcceptedAdditionalData(packet, &thisSystemAccepted, systemsAccepted, &additionalData);
	/// \endcode
	/// \param[in] packet Packet containing the ID_FCM2_VERIFIED_JOIN_ACCEPTED message
	/// \param[out] thisSystemAccepted If true, it was this instance of RakPeerInterface that was accepted. If false, this is notification for another system
	/// \param[out] systemsAccepted Which system(s) were added with AddParticipant(). If \a thisSystemAccepted is false, this list will only have length 1
	/// \param[out] additionalData \a additionalData parameter passed to RespondOnVerifiedJoinCapable()
	virtual void GetVerifiedJoinAcceptedAdditionalData(Packet *packet, bool *thisSystemAccepted, DataStructures::List<RakNetGUID> &systemsAccepted, BitStream *additionalData);

	/// \brief On ID_FCM2_VERIFIED_JOIN_REJECTED, read additional data passed to RespondOnVerifiedJoinCapable()
	/// \details This does not automatically close the connection. The following code will do so:
	/// \code
	/// rakPeer[i]->CloseConnection(packet->guid, true);
	/// \endcode
	/// \param[in] packet Packet containing the ID_FCM2_VERIFIED_JOIN_REJECTED message
	/// \param[out] additionalData \a additionalData parameter passed to RespondOnVerifiedJoinCapable().
	virtual void GetVerifiedJoinRejectedAdditionalData(Packet *packet, BitStream *additionalData);

	/// Override to write data when ID_FCM2_VERIFIED_JOIN_CAPABLE is sent
	virtual void WriteVJCUserData(SLNet::BitStream *bsOut) {(void) bsOut;}

	/// Use to read data written from WriteVJCUserData()
	/// \code
	/// SLNet::BitStream bsIn(packet->data,packet->length,false);
	/// FullyConnectedMesh2::SkipToVJCUserData(&bsIn);
	/// // Your code here
	static void SkipToVJCUserData(SLNet::BitStream *bsIn);

	/// Write custom user data to be sent with ID_FCM2_VERIFIED_JOIN_START, per user
	/// \param[out] bsOut Write your data here, if any. Has to match what is read by ReadVJSUserData
	/// \param[in] userGuid The RakNetGuid of the user you are writing for
	/// \param[in] userContext The data set with SetMyContext() for that system. May be empty. To properly write userContext, you will need to first write userContext->GetNumberOfBitsUsed(), followed by bsOut->Write(userContext);
	//virtual void WriteVJSUserData(SLNet::BitStream *bsOut, RakNetGUID userGuid, BitStream *userContext) {(void) bsOut; (void) userGuid; (void) userContext;}
	virtual void WriteVJSUserData(SLNet::BitStream *bsOut, RakNetGUID userGuid) {(void) bsOut; (void) userGuid;}

	/// \internal
	SLNet::TimeUS GetElapsedRuntime(void);

	/// \internal
	virtual PluginReceiveResult OnReceive(Packet *packet);
	/// \internal
	virtual void OnRakPeerStartup(void);
	/// \internal
	virtual void OnAttach(void);
	/// \internal
	virtual void OnRakPeerShutdown(void);
	/// \internal
	virtual void OnClosedConnection(const SystemAddress &systemAddress, RakNetGUID rakNetGUID, PI2_LostConnectionReason lostConnectionReason );
	/// \internal
	virtual void OnNewConnection(const SystemAddress &systemAddress, RakNetGUID rakNetGUID, bool isIncoming);
	/// \internal
	virtual void OnFailedConnectionAttempt(Packet *packet, PI2_FailedConnectionAttemptReason failedConnectionAttemptReason);

	/// \internal
	struct FCM2Participant
	{
		FCM2Participant() {}
		FCM2Participant(const FCM2Guid &_fcm2Guid, const RakNetGUID &_rakNetGuid) : fcm2Guid(_fcm2Guid), rakNetGuid(_rakNetGuid) {}

		// Low half is a random number.
		// High half is the order we connected in (totalConnectionCount)
		FCM2Guid fcm2Guid;
		RakNetGUID rakNetGuid;
		// BitStream userContext;
	};

	enum JoinInProgressState
	{
		JIPS_PROCESSING,
		JIPS_FAILED,
		JIPS_CONNECTED,
		JIPS_UNNECESSARY,
	};

	struct VerifiedJoinInProgressMember
	{
		SystemAddress systemAddress;
		RakNetGUID guid;
		JoinInProgressState joinInProgressState;
		BitStream *userData;

		bool workingFlag;
	};

	/// \internal
	struct VerifiedJoinInProgress
	{
		RakNetGUID requester;
		DataStructures::List<VerifiedJoinInProgressMember> vjipMembers;
		//bool sentResults;
	};

	/// \internal for debugging
	unsigned int GetTotalConnectionCount(void) const;

protected:
	void PushNewHost(const RakNetGUID &guid, RakNetGUID oldHost);
	void SendOurFCMGuid(SystemAddress addr);
	void SendFCMGuidRequest(RakNetGUID rakNetGuid);
	void SendConnectionCountResponse(SystemAddress addr, unsigned int responseTotalConnectionCount);
	void OnRequestFCMGuid(Packet *packet);
	//void OnUpdateUserContext(Packet *packet);
	void OnRespondConnectionCount(Packet *packet);
	void OnInformFCMGuid(Packet *packet);
	void OnUpdateMinTotalConnectionCount(Packet *packet);
	void AssignOurFCMGuid(void);
	void CalculateHost(RakNetGUID *rakNetGuid, FCM2Guid *fcm2Guid);
	// bool AddParticipantInternal( RakNetGUID rakNetGuid, FCM2Guid theirFCMGuid, BitStream *userContext );
	bool AddParticipantInternal( RakNetGUID rakNetGuid, FCM2Guid theirFCMGuid );
	void CalculateAndPushHost(void);
	bool ParticipantListComplete(void);
	void IncrementTotalConnectionCount(unsigned int i);
	PluginReceiveResult OnVerifiedJoinStart(Packet *packet);
	PluginReceiveResult OnVerifiedJoinCapable(Packet *packet);
	virtual void OnVerifiedJoinFailed(RakNetGUID hostGuid, bool callCloseConnection);
	virtual void OnVerifiedJoinAccepted(Packet *packet);
	virtual void OnVerifiedJoinRejected(Packet *packet);
	unsigned int GetJoinsInProgressIndex(RakNetGUID requester) const;
	void UpdateVerifiedJoinInProgressMember(const AddressOrGUID systemIdentifier, RakNetGUID guidToAssign, JoinInProgressState newState);
	bool ProcessVerifiedJoinInProgressIfCompleted(VerifiedJoinInProgress *vjip);
	void ReadVerifiedJoinInProgressMember(SLNet::BitStream *bsIn, VerifiedJoinInProgressMember *vjipm);
	unsigned int GetVerifiedJoinInProgressMemberIndex(const AddressOrGUID systemIdentifier, VerifiedJoinInProgress *vjip);
	void DecomposeJoinCapable(Packet *packet, VerifiedJoinInProgress *vjip);
	void WriteVerifiedJoinCapable(SLNet::BitStream *bsOut, VerifiedJoinInProgress *vjip);
	void CategorizeVJIP(VerifiedJoinInProgress *vjip,
		DataStructures::List<RakNetGUID> &participatingMembersOnClientSucceeded,
		DataStructures::List<RakNetGUID> &participatingMembersOnClientFailed,
		DataStructures::List<RakNetGUID> &participatingMembersNotOnClient,
		DataStructures::List<RakNetGUID> &clientMembersNotParticipatingSucceeded,
		DataStructures::List<RakNetGUID> &clientMembersNotParticipatingFailed);

	// Used to track how long RakNet has been running. This is so we know who has been running longest
	SLNet::TimeUS startupTime;

	// Option for SetAutoparticipateConnections
	bool autoParticipateConnections;

	// totalConnectionCount is roughly maintained across all systems, and increments by 1 each time a new system connects to the mesh
	// It is always kept at the highest known value
	// It is used as the high 4 bytes for new FCMGuids. This causes newer values of FCM2Guid to be higher than lower values. The lowest value is the host.
	unsigned int totalConnectionCount;

	// Our own ourFCMGuid. Starts at unassigned (0). Assigned once we send ID_FCM2_REQUEST_FCMGUID and get back ID_FCM2_RESPOND_CONNECTION_COUNT
	FCM2Guid ourFCMGuid;

	/// List of systems we know the FCM2Guid for
	DataStructures::List<FCM2Participant*> fcm2ParticipantList;

	RakNetGUID lastPushedHost;

	// Optimization: Store last calculated host in these variables.
	RakNetGUID hostRakNetGuid;
	FCM2Guid hostFCM2Guid;

	SLNet::RakString connectionPassword;
	bool connectOnNewRemoteConnections;

	DataStructures::List<VerifiedJoinInProgress*> joinsInProgress;
	BitStream myContext;
};

} // namespace SLNet

/*
Startup()
ourFCMGuid=unknown
totalConnectionCount=0
Set startupTime

AddParticipant()
if (sender by guid is a participant)
return;
AddParticipantInternal(guid);
if (ourFCMGuid==unknown)
Send to that system a request for their fcmGuid, totalConnectionCount. Inform startupTime.
else
Send to that system a request for their fcmGuid. Inform total connection count, our fcmGuid

OnRequestGuid()
if (sender by guid is not a participant)
{
	// They added us as a participant, but we didn't add them. This can be caused by lag where both participants are not added at the same time.
	// It doesn't affect the outcome as long as we still process the data
	AddParticipantInternal(guid);
}
if (ourFCMGuid==unknown)
{
	if (includedStartupTime)
	{
		// Nobody has a fcmGuid

		if (their startup time is greater than our startup time)
			ReplyConnectionCount(1);
		else
			ReplyConnectionCount(2);
	}
	else
	{
		// They have a fcmGuid, we do not

		SetMaxTotalConnectionCount(remoteCount);
		AssignTheirGuid()
		GenerateOurGuid();
		SendOurGuid(all);
	}
}
else
{
	if (includedStartupTime)
	{
		// We have a fcmGuid they do not

		ReplyConnectionCount(totalConnectionCount+1);
		SendOurGuid(sender);
	}
	else
	{
		// We both have fcmGuids

		SetMaxTotalConnectionCount(remoteCount);
		AssignTheirGuid();
		SendOurGuid(sender);
	}
}

OnReplyConnectionCount()
SetMaxTotalConnectionCount(remoteCount);
GenerateOurGuid();
SendOurGuid(allParticipants);

OnReceiveTheirGuid()
AssignTheirGuid()
*/

#endif

#endif // _RAKNET_SUPPORT_*
