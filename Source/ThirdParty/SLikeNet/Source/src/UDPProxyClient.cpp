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
#if _RAKNET_SUPPORT_UDPProxyClient==1

#include "slikenet/UDPProxyClient.h"
#include "slikenet/BitStream.h"
#include "slikenet/UDPProxyCommon.h"
#include "slikenet/peerinterface.h"
#include "slikenet/MessageIdentifiers.h"
#include "slikenet/GetTime.h"

using namespace SLNet;
static const int DEFAULT_UNRESPONSIVE_PING_TIME_COORDINATOR=1000;

// bool operator<( const DataStructures::MLKeyRef<UDPProxyClient::ServerWithPing> &inputKey, const UDPProxyClient::ServerWithPing &cls ) {return inputKey.Get().serverAddress < cls.serverAddress;}
// bool operator>( const DataStructures::MLKeyRef<UDPProxyClient::ServerWithPing> &inputKey, const UDPProxyClient::ServerWithPing &cls ) {return inputKey.Get().serverAddress > cls.serverAddress;}
// bool operator==( const DataStructures::MLKeyRef<UDPProxyClient::ServerWithPing> &inputKey, const UDPProxyClient::ServerWithPing &cls ) {return inputKey.Get().serverAddress == cls.serverAddress;}

STATIC_FACTORY_DEFINITIONS(UDPProxyClient,UDPProxyClient);

UDPProxyClient::UDPProxyClient()
{
	resultHandler=0;
}
UDPProxyClient::~UDPProxyClient()
{
	Clear();
}
void UDPProxyClient::SetResultHandler(UDPProxyClientResultHandler *rh)
{
	resultHandler=rh;
}
bool UDPProxyClient::RequestForwarding(SystemAddress proxyCoordinator, SystemAddress sourceAddress, RakNetGUID targetGuid, SLNet::TimeMS timeoutOnNoDataMS, SLNet::BitStream *serverSelectionBitstream)
{
	// Return false if not connected 
	ConnectionState cs = rakPeerInterface->GetConnectionState(proxyCoordinator);
	if (cs!=IS_CONNECTED)
		return false;

	// Pretty much a bug not to set the result handler, as otherwise you won't know if the operation succeeed or not
	RakAssert(resultHandler!=0);
	if (resultHandler==0)
		return false;

	BitStream outgoingBs;
	outgoingBs.Write((MessageID)ID_UDP_PROXY_GENERAL);
	outgoingBs.Write((MessageID)ID_UDP_PROXY_FORWARDING_REQUEST_FROM_CLIENT_TO_COORDINATOR);
	outgoingBs.Write(sourceAddress);
	outgoingBs.Write(false);
	outgoingBs.Write(targetGuid);
	outgoingBs.Write(timeoutOnNoDataMS);
	if (serverSelectionBitstream && serverSelectionBitstream->GetNumberOfBitsUsed()>0)
	{
		outgoingBs.Write(true);
		outgoingBs.Write(serverSelectionBitstream);
	}
	else
	{
		outgoingBs.Write(false);
	}
	rakPeerInterface->Send(&outgoingBs, MEDIUM_PRIORITY, RELIABLE_ORDERED, 0, proxyCoordinator, false);

	return true;
}
bool UDPProxyClient::RequestForwarding(SystemAddress proxyCoordinator, SystemAddress sourceAddress, SystemAddress targetAddressAsSeenFromCoordinator, SLNet::TimeMS timeoutOnNoDataMS, SLNet::BitStream *serverSelectionBitstream)
{
	// Return false if not connected 
	ConnectionState cs = rakPeerInterface->GetConnectionState(proxyCoordinator);
	if (cs!=IS_CONNECTED)
		return false;

	// Pretty much a bug not to set the result handler, as otherwise you won't know if the operation succeeed or not
	RakAssert(resultHandler!=0);
	if (resultHandler==0)
		return false;

	BitStream outgoingBs;
	outgoingBs.Write((MessageID)ID_UDP_PROXY_GENERAL);
	outgoingBs.Write((MessageID)ID_UDP_PROXY_FORWARDING_REQUEST_FROM_CLIENT_TO_COORDINATOR);
	outgoingBs.Write(sourceAddress);
	outgoingBs.Write(true);
	outgoingBs.Write(targetAddressAsSeenFromCoordinator);
	outgoingBs.Write(timeoutOnNoDataMS);
	if (serverSelectionBitstream && serverSelectionBitstream->GetNumberOfBitsUsed()>0)
	{
		outgoingBs.Write(true);
		outgoingBs.Write(serverSelectionBitstream);
	}
	else
	{
		outgoingBs.Write(false);
	}
	rakPeerInterface->Send(&outgoingBs, MEDIUM_PRIORITY, RELIABLE_ORDERED, 0, proxyCoordinator, false);

	return true;
}
void UDPProxyClient::Update(void)
{
	unsigned int idx1=0;
	while (idx1 < pingServerGroups.Size())
	{
		PingServerGroup *psg = pingServerGroups[idx1];

		if (psg->serversToPing.Size() > 0 && 
			SLNet::GetTimeMS() > psg->startPingTime+DEFAULT_UNRESPONSIVE_PING_TIME_COORDINATOR)
		{
			// If they didn't reply within DEFAULT_UNRESPONSIVE_PING_TIME_COORDINATOR, just give up on them
			psg->SendPingedServersToCoordinator(rakPeerInterface);

			SLNet::OP_DELETE(psg,_FILE_AND_LINE_);
			pingServerGroups.RemoveAtIndex(idx1);
		}
		else
			idx1++;
	}

}
PluginReceiveResult UDPProxyClient::OnReceive(Packet *packet)
{
	if (packet->data[0]==ID_UNCONNECTED_PONG)
	{
		unsigned int idx1, idx2;
		PingServerGroup *psg;
		for (idx1=0; idx1 < pingServerGroups.Size(); idx1++)
		{
			psg = pingServerGroups[idx1];
			for (idx2=0; idx2 < psg->serversToPing.Size(); idx2++)
			{
				if (psg->serversToPing[idx2].serverAddress==packet->systemAddress)
				{
					SLNet::BitStream bsIn(packet->data,packet->length,false);
					bsIn.IgnoreBytes(sizeof(MessageID));
					SLNet::TimeMS sentTime;
					bsIn.Read(sentTime);
					SLNet::TimeMS curTime = SLNet::GetTimeMS();
					int ping;
					if (curTime>sentTime)
						ping=(int) (curTime-sentTime);
					else
						ping=0;
					psg->serversToPing[idx2].ping=(unsigned short) ping;

					// If all servers to ping are now pinged, reply to coordinator
					if (psg->AreAllServersPinged())
					{
						psg->SendPingedServersToCoordinator(rakPeerInterface);
						SLNet::OP_DELETE(psg,_FILE_AND_LINE_);
						pingServerGroups.RemoveAtIndex(idx1);
					}

					return RR_STOP_PROCESSING_AND_DEALLOCATE;
				}
			}

		}
	}
	else if (packet->data[0]==ID_UDP_PROXY_GENERAL && packet->length>1)
	{
		switch (packet->data[1])
		{
		case ID_UDP_PROXY_PING_SERVERS_FROM_COORDINATOR_TO_CLIENT:
			{
				OnPingServers(packet);
			}
		break;
		case ID_UDP_PROXY_FORWARDING_SUCCEEDED:
		case ID_UDP_PROXY_ALL_SERVERS_BUSY:
		case ID_UDP_PROXY_IN_PROGRESS:
		case ID_UDP_PROXY_NO_SERVERS_ONLINE:
		case ID_UDP_PROXY_RECIPIENT_GUID_NOT_CONNECTED_TO_COORDINATOR:
		case ID_UDP_PROXY_FORWARDING_NOTIFICATION:
			{
				RakNetGUID targetGuid;
				SystemAddress senderAddress, targetAddress;
				SLNet::BitStream incomingBs(packet->data, packet->length, false);
				incomingBs.IgnoreBytes(sizeof(MessageID)*2);
				incomingBs.Read(senderAddress);
				incomingBs.Read(targetAddress);
				incomingBs.Read(targetGuid);

				switch (packet->data[1])
				{
				case ID_UDP_PROXY_FORWARDING_NOTIFICATION:
				case ID_UDP_PROXY_FORWARDING_SUCCEEDED:
				case ID_UDP_PROXY_IN_PROGRESS:
					{
						unsigned short forwardingPort;
						SLNet::RakString serverIP;
						incomingBs.Read(serverIP);
						incomingBs.Read(forwardingPort);
						if (packet->data[1]==ID_UDP_PROXY_FORWARDING_SUCCEEDED)
						{
							if (resultHandler)
								resultHandler->OnForwardingSuccess(serverIP.C_String(), forwardingPort, packet->systemAddress, senderAddress, targetAddress, targetGuid, this);
						}
						else if (packet->data[1]==ID_UDP_PROXY_IN_PROGRESS)
						{
							if (resultHandler)
								resultHandler->OnForwardingInProgress(serverIP.C_String(), forwardingPort, packet->systemAddress, senderAddress, targetAddress, targetGuid, this);
						}
						else
						{
							// Send a datagram to the proxy, so if we are behind a router, that router adds an entry to the routing table.
							// Otherwise the router would block the incoming datagrams from source
							// It doesn't matter if the message actually arrives as long as it goes through the router
							rakPeerInterface->Ping(serverIP.C_String(), forwardingPort, false);

							if (resultHandler)
								resultHandler->OnForwardingNotification(serverIP.C_String(), forwardingPort, packet->systemAddress, senderAddress, targetAddress, targetGuid, this);
						}
					}
					break;
				case ID_UDP_PROXY_ALL_SERVERS_BUSY:
					if (resultHandler)
						resultHandler->OnAllServersBusy(packet->systemAddress, senderAddress, targetAddress, targetGuid, this);
					break;
				case ID_UDP_PROXY_NO_SERVERS_ONLINE:
					if (resultHandler)
						resultHandler->OnNoServersOnline(packet->systemAddress, senderAddress, targetAddress, targetGuid, this);
					break;
				case ID_UDP_PROXY_RECIPIENT_GUID_NOT_CONNECTED_TO_COORDINATOR:
					{
						if (resultHandler)
							resultHandler->OnRecipientNotConnected(packet->systemAddress, senderAddress, targetAddress, targetGuid, this);
						break;
					}
				}
			
			}
			return RR_STOP_PROCESSING_AND_DEALLOCATE;
		}
	}
	return RR_CONTINUE_PROCESSING;
}
void UDPProxyClient::OnRakPeerShutdown(void)
{
	Clear();
}
void UDPProxyClient::OnPingServers(Packet *packet)
{
	SLNet::BitStream incomingBs(packet->data, packet->length, false);
	incomingBs.IgnoreBytes(2);

	PingServerGroup *psg = SLNet::OP_NEW<PingServerGroup>(_FILE_AND_LINE_);
	
	ServerWithPing swp;
	incomingBs.Read(psg->sata.senderClientAddress);
	incomingBs.Read(psg->sata.targetClientAddress);
	// #med - might be possible to drop - see pull request 35 - however kept as is to ensure ABI
	// compatibility to RakNet in MaxNet 0.x - see #39
	RakNetGUID targetGuid;
	incomingBs.Read(targetGuid);
	psg->startPingTime= SLNet::GetTimeMS();
	psg->coordinatorAddressForPings=packet->systemAddress;
	unsigned short serverListSize;
	incomingBs.Read(serverListSize);
	SystemAddress serverAddress;
	unsigned short serverListIndex;
	char ipStr[64];
	for (serverListIndex=0; serverListIndex<serverListSize; serverListIndex++)
	{
		incomingBs.Read(swp.serverAddress);
		swp.ping=DEFAULT_UNRESPONSIVE_PING_TIME_COORDINATOR;
		psg->serversToPing.Push(swp, _FILE_AND_LINE_ );
		swp.serverAddress.ToString(false,ipStr,static_cast<size_t>(64));
		rakPeerInterface->Ping(ipStr,swp.serverAddress.GetPort(),false,0);
	}
	pingServerGroups.Push(psg,_FILE_AND_LINE_);
}

bool UDPProxyClient::PingServerGroup::AreAllServersPinged(void) const
{
	unsigned int serversToPingIndex;
	for (serversToPingIndex=0; serversToPingIndex < serversToPing.Size(); serversToPingIndex++)
	{
		if (serversToPing[serversToPingIndex].ping==DEFAULT_UNRESPONSIVE_PING_TIME_COORDINATOR)
			return false;
	}
	return true;
}

void UDPProxyClient::PingServerGroup::SendPingedServersToCoordinator(RakPeerInterface *rakPeer)
{
	BitStream outgoingBs;
	outgoingBs.Write((MessageID)ID_UDP_PROXY_GENERAL);
	outgoingBs.Write((MessageID)ID_UDP_PROXY_PING_SERVERS_REPLY_FROM_CLIENT_TO_COORDINATOR);
	outgoingBs.Write(sata.senderClientAddress);
	outgoingBs.Write(sata.targetClientAddress);
	unsigned short serversToPingSize = (unsigned short) serversToPing.Size();
	outgoingBs.Write(serversToPingSize);
	unsigned int serversToPingIndex;
	for (serversToPingIndex=0; serversToPingIndex < serversToPingSize; serversToPingIndex++)
	{
		outgoingBs.Write(serversToPing[serversToPingIndex].serverAddress);
		outgoingBs.Write(serversToPing[serversToPingIndex].ping);
	}
	rakPeer->Send(&outgoingBs, MEDIUM_PRIORITY, RELIABLE_ORDERED, 0, coordinatorAddressForPings, false);
}
void UDPProxyClient::Clear(void)
{
	for (unsigned int i=0; i < pingServerGroups.Size(); i++)
		SLNet::OP_DELETE(pingServerGroups[i],_FILE_AND_LINE_);
	pingServerGroups.Clear(false, _FILE_AND_LINE_);
}


#endif // _RAKNET_SUPPORT_*

