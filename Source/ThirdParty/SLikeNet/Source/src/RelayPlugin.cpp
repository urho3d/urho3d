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

#include "slikenet/NativeFeatureIncludes.h"
#if _RAKNET_SUPPORT_RelayPlugin==1

#include "slikenet/RelayPlugin.h"
#include "slikenet/MessageIdentifiers.h"
#include "slikenet/peerinterface.h"
#include "slikenet/BitStream.h"

using namespace SLNet;

STATIC_FACTORY_DEFINITIONS(RelayPlugin,RelayPlugin);

RelayPlugin::RelayPlugin()
{
	acceptAddParticipantRequests=false;
}

RelayPlugin::~RelayPlugin()
{
	DataStructures::List<StrAndGuidAndRoom*> itemList;
	DataStructures::List<RakString> keyList;
	strToGuidHash.GetAsList(itemList, keyList, _FILE_AND_LINE_);
	guidToStrHash.Clear(_FILE_AND_LINE_);
	for (unsigned int i=0; i < itemList.Size(); i++)
		SLNet::OP_DELETE(itemList[i], _FILE_AND_LINE_);
	for (unsigned int i=0; i < chatRooms.Size(); i++)
		SLNet::OP_DELETE(chatRooms[i], _FILE_AND_LINE_);
}

RelayPluginEnums RelayPlugin::AddParticipantOnServer(const RakString &key, const RakNetGUID &guid)
{
	ConnectionState cs = rakPeerInterface->GetConnectionState(guid);
	if (cs!=IS_CONNECTED)
		return RPE_ADD_CLIENT_TARGET_NOT_CONNECTED;

	if (strToGuidHash.HasData(key)==true)
		return RPE_ADD_CLIENT_NAME_ALREADY_IN_USE; // Name already in use

	// If GUID is already in use, remove existing
	StrAndGuidAndRoom *strAndGuidExisting;
	if (guidToStrHash.Pop(strAndGuidExisting, guid, _FILE_AND_LINE_))
	{
		strToGuidHash.Remove(strAndGuidExisting->str, _FILE_AND_LINE_);
		SLNet::OP_DELETE(strAndGuidExisting, _FILE_AND_LINE_);
	}

	StrAndGuidAndRoom *strAndGuid = SLNet::OP_NEW<StrAndGuidAndRoom>(_FILE_AND_LINE_);
	strAndGuid->guid=guid;
	strAndGuid->str=key;

	strToGuidHash.Push(key, strAndGuid, _FILE_AND_LINE_);
	guidToStrHash.Push(guid, strAndGuid, _FILE_AND_LINE_);

	return RPE_ADD_CLIENT_SUCCESS;
}
void RelayPlugin::RemoveParticipantOnServer(const RakNetGUID &guid)
{
	StrAndGuidAndRoom *strAndGuid;
	if (guidToStrHash.Pop(strAndGuid, guid, _FILE_AND_LINE_))
	{
		LeaveGroup(&strAndGuid);
		strToGuidHash.Remove(strAndGuid->str, _FILE_AND_LINE_);
		SLNet::OP_DELETE(strAndGuid, _FILE_AND_LINE_);
	}
}

void RelayPlugin::SetAcceptAddParticipantRequests(bool accept)
{
	acceptAddParticipantRequests=accept;
}
void RelayPlugin::AddParticipantRequestFromClient(const RakString &key, const RakNetGUID &relayPluginServerGuid)
{
	BitStream bsOut;
	bsOut.WriteCasted<MessageID>(ID_RELAY_PLUGIN);
	bsOut.WriteCasted<MessageID>(RPE_ADD_CLIENT_REQUEST_FROM_CLIENT);
	bsOut.WriteCompressed(key);
	SendUnified(&bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, relayPluginServerGuid, false);
}
void RelayPlugin::RemoveParticipantRequestFromClient(const RakNetGUID &relayPluginServerGuid)
{
	BitStream bsOut;
	bsOut.WriteCasted<MessageID>(ID_RELAY_PLUGIN);
	bsOut.WriteCasted<MessageID>(RPE_REMOVE_CLIENT_REQUEST_FROM_CLIENT);
	SendUnified(&bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, relayPluginServerGuid, false);
}
// Send a message to a server running RelayPlugin, to forward a message to the system identified by \a key
void RelayPlugin::SendToParticipant(const RakNetGUID &relayPluginServerGuid, const RakString &key, BitStream *bitStream, PacketPriority priority, PacketReliability reliability, char orderingChannel)
{
	BitStream bsOut;
	bsOut.WriteCasted<MessageID>(ID_RELAY_PLUGIN);
	bsOut.WriteCasted<MessageID>(RPE_MESSAGE_TO_SERVER_FROM_CLIENT);
	bsOut.WriteCasted<unsigned char>(priority);
	bsOut.WriteCasted<unsigned char>(reliability);
	bsOut.Write(orderingChannel);
	bsOut.WriteCompressed(key);
	bsOut.Write(bitStream);
	SendUnified(&bsOut, priority, reliability, orderingChannel, relayPluginServerGuid, false);
}
void RelayPlugin::SendGroupMessage(const RakNetGUID &relayPluginServerGuid, BitStream *bitStream, PacketPriority priority, PacketReliability reliability, char orderingChannel)
{
	BitStream bsOut;
	bsOut.WriteCasted<MessageID>(ID_RELAY_PLUGIN);
	bsOut.WriteCasted<MessageID>(RPE_GROUP_MESSAGE_FROM_CLIENT);
	bsOut.WriteCasted<unsigned char>(priority);
	bsOut.WriteCasted<unsigned char>(reliability);
	bsOut.Write(orderingChannel);
	bsOut.Write(bitStream);
	SendUnified(&bsOut, priority, reliability, orderingChannel, relayPluginServerGuid, false);
}
void RelayPlugin::LeaveGroup(const RakNetGUID &relayPluginServerGuid)
{
	BitStream bsOut;
	bsOut.WriteCasted<MessageID>(ID_RELAY_PLUGIN);
	bsOut.WriteCasted<MessageID>(RPE_LEAVE_GROUP_REQUEST_FROM_CLIENT);
	SendUnified(&bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, relayPluginServerGuid, false);
}
void RelayPlugin::GetGroupList(const RakNetGUID &relayPluginServerGuid)
{
	BitStream bsOut;
	bsOut.WriteCasted<MessageID>(ID_RELAY_PLUGIN);
	bsOut.WriteCasted<MessageID>(RPE_GET_GROUP_LIST_REQUEST_FROM_CLIENT);
	SendUnified(&bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, relayPluginServerGuid, false);
}
PluginReceiveResult RelayPlugin::OnReceive(Packet *packet)
{
	if (packet->data[0]==ID_RELAY_PLUGIN)
	{
		switch (packet->data[1])
		{
		case RPE_MESSAGE_TO_SERVER_FROM_CLIENT:
			{
				BitStream bsIn(packet->data, packet->length, false);
				bsIn.IgnoreBytes(sizeof(MessageID)*2);
				PacketPriority priority;
				PacketReliability reliability;
				char orderingChannel;
				unsigned char cIn;
				bsIn.Read(cIn);
				priority = (PacketPriority) cIn;
				bsIn.Read(cIn);
				reliability = (PacketReliability) cIn;
				bsIn.Read(orderingChannel);
				RakString key;
				bsIn.ReadCompressed(key);
				BitStream bsData;
				bsIn.Read(&bsData);
				StrAndGuidAndRoom **strAndGuid = strToGuidHash.Peek(key);
				StrAndGuidAndRoom **strAndGuidSender = guidToStrHash.Peek(packet->guid);
				if (strAndGuid && strAndGuidSender)
				{
					BitStream bsOut;
					bsOut.WriteCasted<MessageID>(ID_RELAY_PLUGIN);
					bsOut.WriteCasted<MessageID>(RPE_MESSAGE_TO_CLIENT_FROM_SERVER);
					bsOut.WriteCompressed( (*strAndGuidSender)->str );
					bsOut.AlignWriteToByteBoundary();
					bsOut.Write(bsData);
					SendUnified(&bsOut, priority, reliability, orderingChannel, (*strAndGuid)->guid, false);
				}

				return RR_STOP_PROCESSING_AND_DEALLOCATE;
			}

		case RPE_ADD_CLIENT_REQUEST_FROM_CLIENT:
			{
				BitStream bsIn(packet->data, packet->length, false);
				bsIn.IgnoreBytes(sizeof(MessageID)*2);
				RakString key;
				bsIn.ReadCompressed(key);
				BitStream bsOut;
				bsOut.WriteCasted<MessageID>(ID_RELAY_PLUGIN);
				if (acceptAddParticipantRequests)
					bsOut.WriteCasted<MessageID>(AddParticipantOnServer(key, packet->guid));
				else
					bsOut.WriteCasted<MessageID>(RPE_ADD_CLIENT_NOT_ALLOWED);
				bsOut.WriteCompressed(key);
				SendUnified(&bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, packet->systemAddress, false);

				return RR_STOP_PROCESSING_AND_DEALLOCATE;
			}
		case RPE_REMOVE_CLIENT_REQUEST_FROM_CLIENT:
			{
				RemoveParticipantOnServer(packet->guid);
			}
			return RR_STOP_PROCESSING_AND_DEALLOCATE;
		case RPE_GROUP_MESSAGE_FROM_CLIENT:
			{
				OnGroupMessageFromClient(packet);
			}
			return RR_STOP_PROCESSING_AND_DEALLOCATE;
		case RPE_JOIN_GROUP_REQUEST_FROM_CLIENT:
			{
				OnJoinGroupRequestFromClient(packet);
			}
			return RR_STOP_PROCESSING_AND_DEALLOCATE;
		case RPE_LEAVE_GROUP_REQUEST_FROM_CLIENT:
			{
				OnLeaveGroupRequestFromClient(packet);
			}
			return RR_STOP_PROCESSING_AND_DEALLOCATE;
		case RPE_GET_GROUP_LIST_REQUEST_FROM_CLIENT:
			{
				SendChatRoomsList(packet->guid);
			}
			return RR_STOP_PROCESSING_AND_DEALLOCATE;
		}

	}
	
	return RR_CONTINUE_PROCESSING;
}

void RelayPlugin::OnClosedConnection(const SystemAddress &systemAddress, RakNetGUID rakNetGUID, PI2_LostConnectionReason lostConnectionReason )
{
	(void) lostConnectionReason;
	(void) systemAddress;

	RemoveParticipantOnServer(rakNetGUID);
}

RelayPlugin::RP_Group* RelayPlugin::JoinGroup(RP_Group* room, StrAndGuidAndRoom **strAndGuidSender)
{
	if (strAndGuidSender==0)
		return 0;

	NotifyUsersInRoom(room, RPE_USER_ENTERED_ROOM, (*strAndGuidSender)->str);
	StrAndGuid sag;
	sag.guid=(*strAndGuidSender)->guid;
	sag.str=(*strAndGuidSender)->str;

	room->usersInRoom.Push(sag, _FILE_AND_LINE_);
	(*strAndGuidSender)->currentRoom=room->roomName;

	return room;
}
void RelayPlugin::JoinGroupRequest(const RakNetGUID &relayPluginServerGuid, RakString groupName)
{
	BitStream bsOut;
	bsOut.WriteCasted<MessageID>(ID_RELAY_PLUGIN);
	bsOut.WriteCasted<MessageID>(RPE_JOIN_GROUP_REQUEST_FROM_CLIENT);
	bsOut.WriteCompressed(groupName);
	SendUnified(&bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, relayPluginServerGuid, false);
}
RelayPlugin::RP_Group* RelayPlugin::JoinGroup(RakNetGUID userGuid, RakString roomName)
{
	StrAndGuidAndRoom **strAndGuidSender = guidToStrHash.Peek(userGuid);
	if (strAndGuidSender)
	{
		if (roomName.IsEmpty())
			return 0;

		if ((*strAndGuidSender)->currentRoom==roomName)
			return 0;

		if ((*strAndGuidSender)->currentRoom.IsEmpty()==false)
			LeaveGroup(strAndGuidSender);

		RakString userName = (*strAndGuidSender)->str;

		for (unsigned int i=0; i < chatRooms.Size(); i++)
		{
			if (chatRooms[i]->roomName==roomName)
			{
				// Join existing room
				return JoinGroup(chatRooms[i],strAndGuidSender);
			}
		}

		// Create new room
		RP_Group *room = SLNet::OP_NEW<RP_Group>(_FILE_AND_LINE_);
		room->roomName=roomName;
		chatRooms.Push(room, _FILE_AND_LINE_);
		return JoinGroup(room,strAndGuidSender);
	}

	return 0;
}
void RelayPlugin::LeaveGroup(StrAndGuidAndRoom **strAndGuidSender)
{
	if (strAndGuidSender==0)
		return;

	RakString userName = (*strAndGuidSender)->str;
	for (unsigned int i=0; i < chatRooms.Size(); i++)
	{
		if (chatRooms[i]->roomName==(*strAndGuidSender)->currentRoom)
		{
			(*strAndGuidSender)->currentRoom.Clear();

			RP_Group *room = chatRooms[i];
			for (unsigned int j=0; j < room->usersInRoom.Size(); j++)
			{
				if (room->usersInRoom[j].guid==(*strAndGuidSender)->guid)
				{
					room->usersInRoom.RemoveAtIndexFast(j);

					if (room->usersInRoom.Size()==0)
					{
						SLNet::OP_DELETE(room, _FILE_AND_LINE_);
						chatRooms.RemoveAtIndexFast(i);
						return;
					}
				}
			}

			NotifyUsersInRoom(room, RPE_USER_LEFT_ROOM, userName);

			return;

		}
	}
}
void RelayPlugin::NotifyUsersInRoom(RP_Group *room, int msg, const RakString& message)
{
	for (unsigned int i=0; i < room->usersInRoom.Size(); i++)
	{
		BitStream bsOut;
		bsOut.WriteCasted<MessageID>(ID_RELAY_PLUGIN);
		bsOut.WriteCasted<MessageID>(msg);
		bsOut.WriteCompressed(message);

		SendUnified(&bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, room->usersInRoom[i].guid, false);
	}
}
void RelayPlugin::SendMessageToRoom(StrAndGuidAndRoom **strAndGuidSender, BitStream* message)
{
	if ((*strAndGuidSender)->currentRoom.IsEmpty())
		return;

	for (unsigned int i=0; i < chatRooms.Size(); i++)
	{
		if (chatRooms[i]->roomName==(*strAndGuidSender)->currentRoom)
		{
			BitStream bsOut;
			bsOut.WriteCasted<MessageID>(ID_RELAY_PLUGIN);
			bsOut.WriteCasted<MessageID>(RPE_GROUP_MSG_FROM_SERVER);
			message->ResetReadPointer();
			bsOut.WriteCompressed((*strAndGuidSender)->str);
			bsOut.AlignWriteToByteBoundary();
			bsOut.Write(message);

			RP_Group *room = chatRooms[i];
			for (unsigned int j=0; j < room->usersInRoom.Size(); j++)
			{
				if (room->usersInRoom[j].guid!=(*strAndGuidSender)->guid)
					SendUnified(&bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, room->usersInRoom[j].guid, false);
			}

			break;
		}
	}
}
void RelayPlugin::SendChatRoomsList(RakNetGUID target)
{
	BitStream bsOut;
	bsOut.WriteCasted<MessageID>(ID_RELAY_PLUGIN);
	bsOut.WriteCasted<MessageID>(RPE_GET_GROUP_LIST_REPLY_FROM_SERVER);
	bsOut.WriteCasted<uint16_t>(chatRooms.Size());
	for (unsigned int i=0; i < chatRooms.Size(); i++)
	{
		bsOut.WriteCompressed(chatRooms[i]->roomName);
		bsOut.WriteCasted<uint16_t>(chatRooms[i]->usersInRoom.Size());
	}
	SendUnified(&bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, target, false);
}
void RelayPlugin::OnGroupMessageFromClient(Packet *packet)
{
	BitStream bsIn(packet->data, packet->length, false);
	bsIn.IgnoreBytes(sizeof(MessageID)*2);

	PacketPriority priority;
	PacketReliability reliability;
	char orderingChannel;
	unsigned char cIn;
	bsIn.Read(cIn);
	priority = (PacketPriority) cIn;
	bsIn.Read(cIn);
	reliability = (PacketReliability) cIn;
	bsIn.Read(orderingChannel);
	BitStream bsData;
	bsIn.Read(&bsData);
	
	StrAndGuidAndRoom **strAndGuidSender = guidToStrHash.Peek(packet->guid);
	if (strAndGuidSender)
	{
		SendMessageToRoom(strAndGuidSender,&bsData);
	}
}
void RelayPlugin::OnJoinGroupRequestFromClient(Packet *packet)
{
	BitStream bsIn(packet->data, packet->length, false);
	bsIn.IgnoreBytes(sizeof(MessageID)*2);
	RakString groupName;
	bsIn.ReadCompressed(groupName);
	RelayPlugin::RP_Group *groupJoined = JoinGroup(packet->guid, groupName);

	BitStream bsOut;
	bsOut.WriteCasted<MessageID>(ID_RELAY_PLUGIN);
	if (groupJoined)
	{
		bsOut.WriteCasted<MessageID>(RPE_JOIN_GROUP_SUCCESS);
		bsOut.WriteCasted<uint16_t>(groupJoined->usersInRoom.Size());
		for (unsigned int i=0; i < groupJoined->usersInRoom.Size(); i++)
		{
			bsOut.WriteCompressed(groupJoined->usersInRoom[i].str);
		}
	}
	else
	{
		bsOut.WriteCasted<MessageID>(RPE_JOIN_GROUP_FAILURE);
	}

	SendUnified(&bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, packet->guid, false);
}
void RelayPlugin::OnLeaveGroupRequestFromClient(Packet *packet)
{
	BitStream bsIn(packet->data, packet->length, false);
	bsIn.IgnoreBytes(sizeof(MessageID)*2);
	StrAndGuidAndRoom **strAndGuidSender = guidToStrHash.Peek(packet->guid);
	if (strAndGuidSender)
		LeaveGroup(strAndGuidSender);
}
#endif // _RAKNET_SUPPORT_*
