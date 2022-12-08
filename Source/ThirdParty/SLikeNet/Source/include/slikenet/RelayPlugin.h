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
/// \brief Contains the class RelayPlugin
///


#include "NativeFeatureIncludes.h"
#if _RAKNET_SUPPORT_RelayPlugin==1

#ifndef __RELAY_PLUGIN_H
#define __RELAY_PLUGIN_H

#include "PluginInterface2.h"
#include "string.h"
#include "DS_Hash.h"

/// \defgroup RELAY_PLUGIN_GROUP RelayPlugin
/// \brief A simple class to relay messages from one system to another through an intermediary
/// \ingroup PLUGINS_GROUP

namespace SLNet
{

/// Forward declarations
class RakPeerInterface;

enum RelayPluginEnums
{
	// Server handled messages
	RPE_MESSAGE_TO_SERVER_FROM_CLIENT,
	RPE_ADD_CLIENT_REQUEST_FROM_CLIENT,
	RPE_REMOVE_CLIENT_REQUEST_FROM_CLIENT,
	RPE_GROUP_MESSAGE_FROM_CLIENT,
	RPE_JOIN_GROUP_REQUEST_FROM_CLIENT,
	RPE_LEAVE_GROUP_REQUEST_FROM_CLIENT,
	RPE_GET_GROUP_LIST_REQUEST_FROM_CLIENT,
	// Client handled messages
	RPE_MESSAGE_TO_CLIENT_FROM_SERVER,
	RPE_ADD_CLIENT_NOT_ALLOWED,
	RPE_ADD_CLIENT_TARGET_NOT_CONNECTED,
	RPE_ADD_CLIENT_NAME_ALREADY_IN_USE,
	RPE_ADD_CLIENT_SUCCESS,
	RPE_USER_ENTERED_ROOM,
	RPE_USER_LEFT_ROOM,
	RPE_GROUP_MSG_FROM_SERVER,
	RPE_GET_GROUP_LIST_REPLY_FROM_SERVER,
	RPE_JOIN_GROUP_SUCCESS,
	RPE_JOIN_GROUP_FAILURE,
};

/// \brief A simple class to relay messages from one system to another, identifying remote systems by a string.
/// \ingroup RELAY_PLUGIN_GROUP
class RAK_DLL_EXPORT RelayPlugin : public PluginInterface2
{
public:
	// GetInstance() and DestroyInstance(instance*)
	STATIC_FACTORY_DECLARATIONS(RelayPlugin)

	/// Constructor
	RelayPlugin();

	/// Destructor
	virtual ~RelayPlugin();

	/// \brief Forward messages from any system, to the system specified by the combination of key and guid. The sending system only needs to know the key.
	/// \param[in] key A string to identify the target's RakNetGUID. This is so the sending system does not need to know the RakNetGUID of the target system. The key should be unique among all guids added. If the key is not unique, only one system will be sent to (at random).
	/// \param[in] guid The RakNetGuid of the system to send to. If this system disconnects, it is removed from the internal hash 
	/// \return RPE_ADD_CLIENT_TARGET_NOT_CONNECTED, RPE_ADD_CLIENT_NAME_ALREADY_IN_USE, or RPE_ADD_CLIENT_OK
	RelayPluginEnums AddParticipantOnServer(const RakString &key, const RakNetGUID &guid);

	/// \brief Remove a chat participant
	void RemoveParticipantOnServer(const RakNetGUID &guid);

	/// \brief If true, then if the client calls AddParticipantRequestFromClient(), the server will call AddParticipantOnServer() automatically
	/// Defaults to false
	/// \param[in] accept true to accept, false to not.
	void SetAcceptAddParticipantRequests(bool accept);

	/// \brief Request from the client for the server to call AddParticipantOnServer()
	/// \pre The server must have called SetAcceptAddParticipantRequests(true) or the request will be ignored
	/// \param[in] key A string to identify out system. Passed to \a key on AddParticipantOnServer()
	/// \param[in] relayPluginServerGuid the RakNetGUID of the system running RelayPlugin
	void AddParticipantRequestFromClient(const RakString &key, const RakNetGUID &relayPluginServerGuid);

	/// \brief Remove yourself as a participant
	void RemoveParticipantRequestFromClient(const RakNetGUID &relayPluginServerGuid);

	/// \brief Request that the server relay \a bitStream to the system designated by \a key
	/// \param[in] relayPluginServerGuid the RakNetGUID of the system running RelayPlugin
	/// \param[in] destinationGuid The key value passed to AddParticipant() earlier on the server. If this was not done, the server will not relay the message (it will be silently discarded).
	/// \param[in] bitStream The data to relay
	/// \param[in] priority See the parameter of the same name in RakPeerInterface::Send()
	/// \param[in] reliability See the parameter of the same name in RakPeerInterface::Send()
	/// \param[in] orderingChannel See the parameter of the same name in RakPeerInterface::Send()
	void SendToParticipant(const RakNetGUID &relayPluginServerGuid, const RakString &destinationGuid, BitStream *bitStream, PacketPriority priority, PacketReliability reliability, char orderingChannel);

	void SendGroupMessage(const RakNetGUID &relayPluginServerGuid, BitStream *bitStream, PacketPriority priority, PacketReliability reliability, char orderingChannel);
	void JoinGroupRequest(const RakNetGUID &relayPluginServerGuid, RakString groupName);
	void LeaveGroup(const RakNetGUID &relayPluginServerGuid);
	void GetGroupList(const RakNetGUID &relayPluginServerGuid);

	/// \internal
	virtual PluginReceiveResult OnReceive(Packet *packet);
	/// \internal
	virtual void OnClosedConnection(const SystemAddress &systemAddress, RakNetGUID rakNetGUID, PI2_LostConnectionReason lostConnectionReason );

	struct StrAndGuidAndRoom
	{
		RakString str;
		RakNetGUID guid;
		RakString currentRoom;
	};

	struct StrAndGuid
	{
		RakString str;
		RakNetGUID guid;
	};

	struct RP_Group
	{
		RakString roomName;
		DataStructures::List<StrAndGuid> usersInRoom;
	};
	
protected:

	RelayPlugin::RP_Group* JoinGroup(RakNetGUID userGuid, RakString roomName);
	RelayPlugin::RP_Group* JoinGroup(RP_Group* room, StrAndGuidAndRoom **strAndGuidSender);
	void LeaveGroup(StrAndGuidAndRoom **strAndGuidSender);
	void NotifyUsersInRoom(RP_Group *room, int msg, const RakString& message);
	void SendMessageToRoom(StrAndGuidAndRoom **strAndGuidSender, BitStream* message);
	void SendChatRoomsList(RakNetGUID target);
	void OnGroupMessageFromClient(Packet *packet);
	void OnJoinGroupRequestFromClient(Packet *packet);
	void OnLeaveGroupRequestFromClient(Packet *packet);

	DataStructures::Hash<RakString, StrAndGuidAndRoom*, 8096, SLNet::RakString::ToInteger> strToGuidHash;
	DataStructures::Hash<RakNetGUID, StrAndGuidAndRoom*, 8096, SLNet::RakNetGUID::ToUint32> guidToStrHash;
	DataStructures::List<RP_Group*> chatRooms;
	bool acceptAddParticipantRequests;

};

} // End namespace

#endif

#endif // _RAKNET_SUPPORT_*
