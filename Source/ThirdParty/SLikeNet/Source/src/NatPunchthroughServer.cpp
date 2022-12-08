/*
 *  Original work: Copyright (c) 2014, Oculus VR, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the BSD-style license found in the
 *  RakNet License.txt file in the licenses directory of this source tree. An additional grant 
 *  of patent rights can be found in the RakNet Patents.txt file in the same directory.
 *
 *
 *  Modified work: Copyright (c) 2016-2018, SLikeSoft UG (haftungsbeschränkt)
 *
 *  This source code was modified by SLikeSoft. Modifications are licensed under the MIT-style
 *  license found in the license.txt file in the root directory of this source tree.
 */

#include "slikenet/NativeFeatureIncludes.h"
#if _RAKNET_SUPPORT_NatPunchthroughServer==1

#include "slikenet/NatPunchthroughServer.h"
#include "slikenet/SocketLayer.h"
#include "slikenet/BitStream.h"
#include "slikenet/MessageIdentifiers.h"
#include "slikenet/peerinterface.h"
#include "slikenet/MTUSize.h"
#include "slikenet/GetTime.h"
#include "slikenet/PacketLogger.h"
#include "slikenet/linux_adapter.h"
#include "slikenet/osx_adapter.h"

using namespace SLNet;

void NatPunchthroughServerDebugInterface_Printf::OnServerMessage(const char *msg)
{
	printf("%s\n", msg);
}
#if _RAKNET_SUPPORT_PacketLogger==1
void NatPunchthroughServerDebugInterface_PacketLogger::OnServerMessage(const char *msg)
{
	if (pl)
	{
		pl->WriteMiscellaneous("Nat", msg);
	}
}
#endif

void NatPunchthroughServer::User::DeleteConnectionAttempt(NatPunchthroughServer::ConnectionAttempt *ca)
{
	unsigned int index = connectionAttempts.GetIndexOf(ca);
	if ((unsigned int)index!=(unsigned int)-1)
	{
		SLNet::OP_DELETE(ca,_FILE_AND_LINE_);
		connectionAttempts.RemoveAtIndex(index);
	}
}
void NatPunchthroughServer::User::DerefConnectionAttempt(NatPunchthroughServer::ConnectionAttempt *ca)
{
	unsigned int index = connectionAttempts.GetIndexOf(ca);
	if ((unsigned int)index!=(unsigned int)-1)
	{
		connectionAttempts.RemoveAtIndex(index);
	}
}
bool NatPunchthroughServer::User::HasConnectionAttemptToUser(User *user)
{
	unsigned int index;
	for (index=0; index < connectionAttempts.Size(); index++)
	{
		if (connectionAttempts[index]->recipient->guid==user->guid ||
			connectionAttempts[index]->sender->guid==user->guid)
			return true;
	}
	return false;
}
void NatPunchthroughServer::User::LogConnectionAttempts(SLNet::RakString &rs)
{
	rs.Clear();
	unsigned int index;
	char guidStr[128], ipStr[128];
	guid.ToString(guidStr, 128);
	systemAddress.ToString(true,ipStr,static_cast<size_t>(128));
	rs= SLNet::RakString("User systemAddress=%s guid=%s\n", ipStr, guidStr);
	rs+= SLNet::RakString("%i attempts in list:\n", connectionAttempts.Size());
	for (index=0; index < connectionAttempts.Size(); index++)
	{
		rs+= SLNet::RakString("%i. SessionID=%i ", index+1, connectionAttempts[index]->sessionId);
		if (connectionAttempts[index]->sender==this)
			rs+="(We are sender) ";
		else
			rs+="(We are recipient) ";
		if (isReady)
			rs+="(READY TO START) ";
		else
			rs+="(NOT READY TO START) ";
		if (connectionAttempts[index]->attemptPhase==NatPunchthroughServer::ConnectionAttempt::NAT_ATTEMPT_PHASE_NOT_STARTED)
			rs+="(NOT_STARTED). ";
		else
			rs+="(GETTING_RECENT_PORTS). ";
		if (connectionAttempts[index]->sender==this)
		{
			connectionAttempts[index]->recipient->guid.ToString(guidStr, 128);
			connectionAttempts[index]->recipient->systemAddress.ToString(true,ipStr,static_cast<size_t>(128));
		}
		else
		{
			connectionAttempts[index]->sender->guid.ToString(guidStr, 128);
			connectionAttempts[index]->sender->systemAddress.ToString(true,ipStr,static_cast<size_t>(128));
		}

		rs+= SLNet::RakString("Target systemAddress=%s, guid=%s.\n", ipStr, guidStr);
	}
}

int SLNet::NatPunchthroughServer::NatPunchthroughUserComp( const RakNetGUID &key, User * const &data )
{
	if (key < data->guid)
		return -1;
	if (key > data->guid)
		return 1;
	return 0;
}

STATIC_FACTORY_DEFINITIONS(NatPunchthroughServer,NatPunchthroughServer);

NatPunchthroughServer::NatPunchthroughServer()
{
	lastUpdate=0;
	sessionId=0;
	natPunchthroughServerDebugInterface=0;
	for (int i=0; i < MAXIMUM_NUMBER_OF_INTERNAL_IDS; i++)
		boundAddresses[i]=UNASSIGNED_SYSTEM_ADDRESS;
	boundAddressCount=0;
}
NatPunchthroughServer::~NatPunchthroughServer()
{
	User *user, *otherUser;
	ConnectionAttempt *connectionAttempt;
	unsigned int j;
	while(users.Size())
	{
		user = users[0];
		for (j=0; j < user->connectionAttempts.Size(); j++)
		{
			connectionAttempt=user->connectionAttempts[j];
			if (connectionAttempt->sender==user)
				otherUser=connectionAttempt->recipient;
			else
				otherUser=connectionAttempt->sender;
			otherUser->DeleteConnectionAttempt(connectionAttempt);
		}
		SLNet::OP_DELETE(user,_FILE_AND_LINE_);
		users[0]=users[users.Size()-1];
		users.RemoveAtIndex(users.Size()-1);
	}
}
void NatPunchthroughServer::SetDebugInterface(NatPunchthroughServerDebugInterface *i)
{
	natPunchthroughServerDebugInterface=i;
}
void NatPunchthroughServer::Update(void)
{
	ConnectionAttempt *connectionAttempt;
	User *user, *recipient;
	unsigned int i,j;
	SLNet::Time time = SLNet::GetTime();
	if (time > lastUpdate+250)
	{
		lastUpdate=time;

		for (i=0; i < users.Size(); i++)
		{
			user=users[i];
			for (j=0; j < user->connectionAttempts.Size(); j++)
			{
				connectionAttempt=user->connectionAttempts[j];
				if (connectionAttempt->sender==user)
				{
					if (connectionAttempt->attemptPhase!=ConnectionAttempt::NAT_ATTEMPT_PHASE_NOT_STARTED &&
						time > connectionAttempt->startTime &&
						time > 10000 + connectionAttempt->startTime ) // Formerly 5000, but sometimes false positives
					{
						SLNet::BitStream outgoingBs;
						
						// that other system might not be running the plugin
						outgoingBs.Write((MessageID)ID_NAT_TARGET_UNRESPONSIVE);
						outgoingBs.Write(connectionAttempt->recipient->guid);
						outgoingBs.Write(connectionAttempt->sessionId);
						rakPeerInterface->Send(&outgoingBs,HIGH_PRIORITY,RELIABLE_ORDERED,0,connectionAttempt->sender->systemAddress,false);

						// 05/28/09 Previously only told sender about ID_NAT_CONNECTION_TO_TARGET_LOST
						// However, recipient may be expecting it due to external code
						// In that case, recipient would never get any response if the sender dropped
						outgoingBs.Reset();
						outgoingBs.Write((MessageID)ID_NAT_TARGET_UNRESPONSIVE);
						outgoingBs.Write(connectionAttempt->sender->guid);
						outgoingBs.Write(connectionAttempt->sessionId);
						rakPeerInterface->Send(&outgoingBs,HIGH_PRIORITY,RELIABLE_ORDERED,0,connectionAttempt->recipient->systemAddress,false);

						connectionAttempt->sender->isReady=true;
						connectionAttempt->recipient->isReady=true;
						recipient=connectionAttempt->recipient;


						if (natPunchthroughServerDebugInterface)
						{
							char str[1024];
							char addr1[128], addr2[128];
							// 8/01/09 Fixed bug where this was after DeleteConnectionAttempt()
							connectionAttempt->sender->systemAddress.ToString(true,addr1,static_cast<size_t>(128));
							connectionAttempt->recipient->systemAddress.ToString(true,addr2,static_cast<size_t>(128));
							sprintf_s(str, "Sending ID_NAT_TARGET_UNRESPONSIVE to sender %s and recipient %s.", addr1, addr2);
							natPunchthroughServerDebugInterface->OnServerMessage(str);
							SLNet::RakString log;
							connectionAttempt->sender->LogConnectionAttempts(log);
							connectionAttempt->recipient->LogConnectionAttempts(log);
						}


						connectionAttempt->sender->DerefConnectionAttempt(connectionAttempt);
						connectionAttempt->recipient->DeleteConnectionAttempt(connectionAttempt);

						StartPunchthroughForUser(user);
						StartPunchthroughForUser(recipient);

						break;
					}
				}
			}
		}
	}
}
PluginReceiveResult NatPunchthroughServer::OnReceive(Packet *packet)
{
	switch (packet->data[0])
	{
	case ID_NAT_PUNCHTHROUGH_REQUEST:
		OnNATPunchthroughRequest(packet);
		return RR_STOP_PROCESSING_AND_DEALLOCATE;
	case ID_NAT_GET_MOST_RECENT_PORT:
		OnGetMostRecentPort(packet);
		return RR_STOP_PROCESSING_AND_DEALLOCATE;
	case ID_NAT_CLIENT_READY:
		OnClientReady(packet);
		return RR_STOP_PROCESSING_AND_DEALLOCATE;
	case ID_NAT_REQUEST_BOUND_ADDRESSES:
		{
		SLNet::BitStream outgoingBs;
			outgoingBs.Write((MessageID)ID_NAT_RESPOND_BOUND_ADDRESSES);
			
			if (boundAddresses[0]==UNASSIGNED_SYSTEM_ADDRESS)
			{
				DataStructures::List<RakNetSocket2* > sockets;
				rakPeerInterface->GetSockets(sockets);
				for (unsigned i=0; i < sockets.Size() && i < MAXIMUM_NUMBER_OF_INTERNAL_IDS; i++)
				{
					boundAddresses[i]=sockets[i]->GetBoundAddress();
					boundAddressCount++;
				}
			}

			outgoingBs.Write(boundAddressCount);
			for (int i=0; i < boundAddressCount; i++)
			{
				outgoingBs.Write(boundAddresses[i]);
			}

			rakPeerInterface->Send(&outgoingBs,HIGH_PRIORITY,RELIABLE_ORDERED,0,packet->systemAddress,false);
		}
		return RR_STOP_PROCESSING_AND_DEALLOCATE;
	case ID_NAT_PING:
		{
		}
		return RR_STOP_PROCESSING_AND_DEALLOCATE;
	case ID_OUT_OF_BAND_INTERNAL:
		if (packet->length>=2 && packet->data[1]==ID_NAT_PING)
		{
			SLNet::BitStream bs(packet->data,packet->length,false);
			bs.IgnoreBytes(sizeof(MessageID)*2);
			uint16_t externalPort;
			bs.Read(externalPort);

			SLNet::BitStream outgoingBs;
			outgoingBs.Write((MessageID)ID_NAT_PONG);
			outgoingBs.Write(externalPort);
			uint16_t externalPort2 = packet->systemAddress.GetPort();
			outgoingBs.Write(externalPort2);
			rakPeerInterface->SendOutOfBand((const char*) packet->systemAddress.ToString(false),packet->systemAddress.GetPort(),(const char*) outgoingBs.GetData(),outgoingBs.GetNumberOfBytesUsed());

			return RR_STOP_PROCESSING_AND_DEALLOCATE;
		}
	}
	return RR_CONTINUE_PROCESSING;
}
void NatPunchthroughServer::OnClosedConnection(const SystemAddress &systemAddress, RakNetGUID rakNetGUID, PI2_LostConnectionReason lostConnectionReason )
{
	(void) lostConnectionReason;
	(void) systemAddress;

	unsigned int i=0;
	bool objectExists;
	i = users.GetIndexFromKey(rakNetGUID, &objectExists);
	if (objectExists)
	{
		SLNet::BitStream outgoingBs;
		DataStructures::List<User *> freedUpInProgressUsers;
		User *user = users[i];
		User *otherUser;
		unsigned int connectionAttemptIndex;
		ConnectionAttempt *connectionAttempt;
		for (connectionAttemptIndex=0; connectionAttemptIndex < user->connectionAttempts.Size(); connectionAttemptIndex++)
		{
			connectionAttempt=user->connectionAttempts[connectionAttemptIndex];
			outgoingBs.Reset();
			if (connectionAttempt->recipient==user)
			{
				otherUser=connectionAttempt->sender;
			}
			else
			{
				otherUser=connectionAttempt->recipient;
			}

			// 05/28/09 Previously only told sender about ID_NAT_CONNECTION_TO_TARGET_LOST
			// However, recipient may be expecting it due to external code
			// In that case, recipient would never get any response if the sender dropped
			outgoingBs.Write((MessageID)ID_NAT_CONNECTION_TO_TARGET_LOST);
			outgoingBs.Write(rakNetGUID);
			outgoingBs.Write(connectionAttempt->sessionId);
			rakPeerInterface->Send(&outgoingBs,HIGH_PRIORITY,RELIABLE_ORDERED,0,otherUser->systemAddress,false);

			// 4/22/09 - Bug: was checking inProgress, legacy variable not used elsewhere
			if (connectionAttempt->attemptPhase==ConnectionAttempt::NAT_ATTEMPT_PHASE_GETTING_RECENT_PORTS)
			{
				otherUser->isReady=true;
				freedUpInProgressUsers.Insert(otherUser, _FILE_AND_LINE_ );
			}

			otherUser->DeleteConnectionAttempt(connectionAttempt);
		}

		SLNet::OP_DELETE(users[i], _FILE_AND_LINE_);
		users.RemoveAtIndex(i);

		for (i=0; i < freedUpInProgressUsers.Size(); i++)
		{
			StartPunchthroughForUser(freedUpInProgressUsers[i]);
		}
	}

	/*
	// Also remove from groupPunchthroughRequests
	for (i=0; i < users.Size(); i++)
	{
		bool objectExists;
		unsigned int gprIndex;
		gprIndex = users[i]->groupPunchthroughRequests.GetIndexFromKey(rakNetGUID, &objectExists);
		if (objectExists)
		{
//			printf("DEBUG %i\n", __LINE__);

			SLNet::BitStream outgoingBs;
			outgoingBs.Write((MessageID)ID_NAT_TARGET_NOT_CONNECTED);
			outgoingBs.Write(rakNetGUID);
			rakPeerInterface->Send(&outgoingBs,HIGH_PRIORITY,RELIABLE_ORDERED,0,users[i]->systemAddress,false);

			users[i]->groupPunchthroughRequests.RemoveAtIndex(gprIndex);
		}
	}
	*/
}

void NatPunchthroughServer::OnNewConnection(const SystemAddress &systemAddress, RakNetGUID rakNetGUID, bool isIncoming)
{
	(void) systemAddress;
	(void) isIncoming;

	User *user = SLNet::OP_NEW<User>(_FILE_AND_LINE_);
	user->guid=rakNetGUID;
	user->mostRecentPort=0;
	user->systemAddress=systemAddress;
	user->isReady=true;
	users.Insert(rakNetGUID, user, true, _FILE_AND_LINE_);

//	printf("Adding to users %s\n", rakNetGUID.ToString());
//	printf("DEBUG users[0] guid=%s\n", users[0]->guid.ToString());
}
void NatPunchthroughServer::OnNATPunchthroughRequest(Packet *packet)
{
	SLNet::BitStream outgoingBs;
	SLNet::BitStream incomingBs(packet->data, packet->length, false);
	incomingBs.IgnoreBytes(sizeof(MessageID));
	RakNetGUID recipientGuid, senderGuid;
	incomingBs.Read(recipientGuid);
	senderGuid=packet->guid;
	unsigned int i;
	bool objectExists;
	i = users.GetIndexFromKey(senderGuid, &objectExists);
	RakAssert(objectExists);

	ConnectionAttempt *ca = SLNet::OP_NEW<ConnectionAttempt>(_FILE_AND_LINE_);
	ca->sender=users[i];
	ca->sessionId=sessionId++;
	i = users.GetIndexFromKey(recipientGuid, &objectExists);
	if (objectExists==false || ca->sender == ca->recipient)
	{
// 		printf("DEBUG %i\n", __LINE__);
// 		printf("DEBUG recipientGuid=%s\n", recipientGuid.ToString());
// 		printf("DEBUG users[0] guid=%s\n", users[0]->guid.ToString());

		outgoingBs.Write((MessageID)ID_NAT_TARGET_NOT_CONNECTED);
		outgoingBs.Write(recipientGuid);
		rakPeerInterface->Send(&outgoingBs,HIGH_PRIORITY,RELIABLE_ORDERED,0,packet->systemAddress,false);
		SLNet::OP_DELETE(ca,_FILE_AND_LINE_);
		return;
	}
	ca->recipient=users[i];
	if (ca->recipient->HasConnectionAttemptToUser(ca->sender))
	{
		outgoingBs.Write((MessageID)ID_NAT_ALREADY_IN_PROGRESS);
		outgoingBs.Write(recipientGuid);
		rakPeerInterface->Send(&outgoingBs,HIGH_PRIORITY,RELIABLE_ORDERED,0,packet->systemAddress,false);
		SLNet::OP_DELETE(ca,_FILE_AND_LINE_);
		return;
	}

	ca->sender->connectionAttempts.Insert(ca, _FILE_AND_LINE_ );
	ca->recipient->connectionAttempts.Insert(ca, _FILE_AND_LINE_ );

	StartPunchthroughForUser(ca->sender);
}
void NatPunchthroughServer::OnClientReady(Packet *packet)
{
	unsigned int i;
	bool objectExists;
	i = users.GetIndexFromKey(packet->guid, &objectExists);
	if (objectExists)
	{
		users[i]->isReady=true;
		StartPunchthroughForUser(users[i]);
	}
}
void NatPunchthroughServer::OnGetMostRecentPort(Packet *packet)
{
	SLNet::BitStream bsIn(packet->data, packet->length, false);
	bsIn.IgnoreBytes(sizeof(MessageID));
	uint16_t curSessionId;
	unsigned short mostRecentPort;
	bsIn.Read(curSessionId);
	bsIn.Read(mostRecentPort);

	unsigned int i,j;
	User *user;
	ConnectionAttempt *connectionAttempt;
	bool objectExists;
	i = users.GetIndexFromKey(packet->guid, &objectExists);

	if (natPunchthroughServerDebugInterface)
	{
		SLNet::RakString log;
		char addr1[128], addr2[128];
		packet->systemAddress.ToString(true,addr1,static_cast<size_t>(128));
		packet->guid.ToString(addr2, 128);
		log= SLNet::RakString("Got ID_NAT_GET_MOST_RECENT_PORT from systemAddress %s guid %s. port=%i. sessionId=%i. userFound=%i.", addr1, addr2, mostRecentPort, curSessionId, objectExists);
		natPunchthroughServerDebugInterface->OnServerMessage(log.C_String());
	}

	if (objectExists)
	{
		user=users[i];
		user->mostRecentPort=mostRecentPort;
		SLNet::Time time = SLNet::GetTime();

		for (j=0; j < user->connectionAttempts.Size(); j++)
		{
			connectionAttempt=user->connectionAttempts[j];
			if (connectionAttempt->attemptPhase==ConnectionAttempt::NAT_ATTEMPT_PHASE_GETTING_RECENT_PORTS &&
				connectionAttempt->sender->mostRecentPort!=0 &&
				connectionAttempt->recipient->mostRecentPort!=0 &&
				// 04/29/08 add sessionId to prevent processing for other systems
				connectionAttempt->sessionId== curSessionId)
			{
				SystemAddress senderSystemAddress = connectionAttempt->sender->systemAddress;
				SystemAddress recipientSystemAddress = connectionAttempt->recipient->systemAddress;
				SystemAddress recipientTargetAddress = recipientSystemAddress;
				SystemAddress senderTargetAddress = senderSystemAddress;
				recipientTargetAddress.SetPortHostOrder(connectionAttempt->recipient->mostRecentPort);
				senderTargetAddress.SetPortHostOrder(connectionAttempt->sender->mostRecentPort);

				// Pick a time far enough in the future that both systems will have gotten the message
				int targetPing = rakPeerInterface->GetAveragePing(recipientTargetAddress);
				int senderPing = rakPeerInterface->GetAveragePing(senderSystemAddress);
				SLNet::Time simultaneousAttemptTime;
				if (targetPing==-1 || senderPing==-1)
					simultaneousAttemptTime = time + 1500;
				else
				{
					int largerPing = targetPing > senderPing ? targetPing : senderPing;
					if (largerPing * 4 < 100)
						simultaneousAttemptTime = time + 100;
					else
						simultaneousAttemptTime = time + (largerPing * 4);
				}

				if (natPunchthroughServerDebugInterface)
				{
					SLNet::RakString log;
					char addr1[128], addr2[128];
					recipientSystemAddress.ToString(true,addr1,static_cast<size_t>(128));
					connectionAttempt->recipient->guid.ToString(addr2, 128);
					log= SLNet::RakString("Sending ID_NAT_CONNECT_AT_TIME to recipient systemAddress %s guid %s", addr1, addr2);
					natPunchthroughServerDebugInterface->OnServerMessage(log.C_String());
				}

				// Send to recipient timestamped message to connect at time
				SLNet::BitStream bsOut;
				bsOut.Write((MessageID)ID_TIMESTAMP);
				bsOut.Write(simultaneousAttemptTime);
				bsOut.Write((MessageID)ID_NAT_CONNECT_AT_TIME);
				bsOut.Write(connectionAttempt->sessionId);
				bsOut.Write(senderTargetAddress); // Public IP, using most recent port
				for (j=0; j < MAXIMUM_NUMBER_OF_INTERNAL_IDS; j++) // Internal IP
					bsOut.Write(rakPeerInterface->GetInternalID(senderSystemAddress,j));
				bsOut.Write(connectionAttempt->sender->guid);
				bsOut.Write(false);
				rakPeerInterface->Send(&bsOut,HIGH_PRIORITY,RELIABLE_ORDERED,0,recipientSystemAddress,false);


				if (natPunchthroughServerDebugInterface)
				{
					SLNet::RakString log;
					char addr1[128], addr2[128];
					senderSystemAddress.ToString(true,addr1,static_cast<size_t>(128));
					connectionAttempt->sender->guid.ToString(addr2, 128);
					log= SLNet::RakString("Sending ID_NAT_CONNECT_AT_TIME to sender systemAddress %s guid %s", addr1, addr2);
					natPunchthroughServerDebugInterface->OnServerMessage(log.C_String());
				}


				// Same for sender
				bsOut.Reset();
				bsOut.Write((MessageID)ID_TIMESTAMP);
				bsOut.Write(simultaneousAttemptTime);
				bsOut.Write((MessageID)ID_NAT_CONNECT_AT_TIME);
				bsOut.Write(connectionAttempt->sessionId);
				bsOut.Write(recipientTargetAddress); // Public IP, using most recent port
				for (j=0; j < MAXIMUM_NUMBER_OF_INTERNAL_IDS; j++) // Internal IP
					bsOut.Write(rakPeerInterface->GetInternalID(recipientSystemAddress,j));						
				bsOut.Write(connectionAttempt->recipient->guid);
				bsOut.Write(true);
				rakPeerInterface->Send(&bsOut,HIGH_PRIORITY,RELIABLE_ORDERED,0,senderSystemAddress,false);

				connectionAttempt->recipient->DerefConnectionAttempt(connectionAttempt);
				connectionAttempt->sender->DeleteConnectionAttempt(connectionAttempt);

				// 04/29/08 missing return
				return;
			}
		}
	}
	else
	{

		if (natPunchthroughServerDebugInterface)
		{
			SLNet::RakString log;
			char addr1[128], addr2[128];
			packet->systemAddress.ToString(true,addr1,static_cast<size_t>(128));
			packet->guid.ToString(addr2, 128);
			log= SLNet::RakString("Ignoring ID_NAT_GET_MOST_RECENT_PORT from systemAddress %s guid %s", addr1, addr2);
			natPunchthroughServerDebugInterface->OnServerMessage(log.C_String());
		}

	}
}
void NatPunchthroughServer::StartPunchthroughForUser(User *user)
{
	if (user->isReady==false)
		return;

	ConnectionAttempt *connectionAttempt;
	User *sender,*recipient,*otherUser;
	unsigned int i;
	for (i=0; i < user->connectionAttempts.Size(); i++)
	{
		connectionAttempt=user->connectionAttempts[i];
		if (connectionAttempt->sender==user)
		{
			otherUser=connectionAttempt->recipient;
			sender=user;
			recipient=otherUser;
		}
		else
		{
			otherUser=connectionAttempt->sender;
			recipient=user;
			sender=otherUser;
		}

		if (otherUser->isReady)
		{
			if (natPunchthroughServerDebugInterface)
			{
				char str[1024];
				char addr1[128], addr2[128];
				sender->systemAddress.ToString(true,addr1,static_cast<size_t>(128));
				recipient->systemAddress.ToString(true,addr2,static_cast<size_t>(128));
				sprintf_s(str, "Sending NAT_ATTEMPT_PHASE_GETTING_RECENT_PORTS to sender %s and recipient %s.", addr1, addr2);
				natPunchthroughServerDebugInterface->OnServerMessage(str);
			}

			sender->isReady=false;
			recipient->isReady=false;
			connectionAttempt->attemptPhase=ConnectionAttempt::NAT_ATTEMPT_PHASE_GETTING_RECENT_PORTS;
			connectionAttempt->startTime= SLNet::GetTime();

			sender->mostRecentPort=0;
			recipient->mostRecentPort=0;

			SLNet::BitStream outgoingBs;
			outgoingBs.Write((MessageID)ID_NAT_GET_MOST_RECENT_PORT);
			// 4/29/09 Write sessionID so we don't use returned port for a system we don't want
			outgoingBs.Write(connectionAttempt->sessionId);
			rakPeerInterface->Send(&outgoingBs,HIGH_PRIORITY,RELIABLE_ORDERED,0,sender->systemAddress,false);
			rakPeerInterface->Send(&outgoingBs,HIGH_PRIORITY,RELIABLE_ORDERED,0,recipient->systemAddress,false);

			// 4/22/09 - BUG: missing break statement here
			break;
		}
	}
}

#endif // _RAKNET_SUPPORT_*
