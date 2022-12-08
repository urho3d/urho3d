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
#if _RAKNET_SUPPORT_UDPProxyCoordinator==1 && _RAKNET_SUPPORT_UDPForwarder==1

#include "slikenet/UDPProxyCoordinator.h"
#include "slikenet/BitStream.h"
#include "slikenet/UDPProxyCommon.h"
#include "slikenet/peerinterface.h"
#include "slikenet/MessageIdentifiers.h"
#include "slikenet/Rand.h"
#include "slikenet/GetTime.h"
#include "slikenet/UDPForwarder.h"

// Larger than the client version
static const int DEFAULT_CLIENT_UNRESPONSIVE_PING_TIME=2000;
static const int DEFAULT_UNRESPONSIVE_PING_TIME_COORDINATOR=DEFAULT_CLIENT_UNRESPONSIVE_PING_TIME+1000;

using namespace SLNet;

// bool operator<( const DataStructures::MLKeyRef<unsigned short> &inputKey, const UDPProxyCoordinator::ServerWithPing &cls ) {return inputKey.Get() < cls.ping;}
// bool operator>( const DataStructures::MLKeyRef<unsigned short> &inputKey, const UDPProxyCoordinator::ServerWithPing &cls ) {return inputKey.Get() > cls.ping;}
// bool operator==( const DataStructures::MLKeyRef<unsigned short> &inputKey, const UDPProxyCoordinator::ServerWithPing &cls ) {return inputKey.Get() == cls.ping;}

int UDPProxyCoordinator::ServerWithPingComp( const unsigned short &key, const UDPProxyCoordinator::ServerWithPing &data )
{
	if (key < data.ping)
		return -1;
	if (key > data.ping)
		return 1;
	return 0;
}

int UDPProxyCoordinator::ForwardingRequestComp( const SenderAndTargetAddress &key, ForwardingRequest* const &data)
{
	if (key.senderClientAddress < data->sata.senderClientAddress )
		return -1;
	if (key.senderClientAddress > data->sata.senderClientAddress )
		return 1;
	if (key.targetClientAddress < data->sata.targetClientAddress )
		return -1;
	if (key.targetClientAddress > data->sata.targetClientAddress )
		return 1;
	return 0;
}
// 
// bool operator<( const DataStructures::MLKeyRef<UDPProxyCoordinator::SenderAndTargetAddress> &inputKey, const UDPProxyCoordinator::ForwardingRequest *cls )
// {
// 	return inputKey.Get().senderClientAddress < cls->sata.senderClientAddress ||
// 		(inputKey.Get().senderClientAddress == cls->sata.senderClientAddress && inputKey.Get().targetClientAddress < cls->sata.targetClientAddress);
// }
// bool operator>( const DataStructures::MLKeyRef<UDPProxyCoordinator::SenderAndTargetAddress> &inputKey, const UDPProxyCoordinator::ForwardingRequest *cls )
// {
// 	return inputKey.Get().senderClientAddress > cls->sata.senderClientAddress ||
// 		(inputKey.Get().senderClientAddress == cls->sata.senderClientAddress && inputKey.Get().targetClientAddress > cls->sata.targetClientAddress);
// }
// bool operator==( const DataStructures::MLKeyRef<UDPProxyCoordinator::SenderAndTargetAddress> &inputKey, const UDPProxyCoordinator::ForwardingRequest *cls )
// {
// 	return inputKey.Get().senderClientAddress == cls->sata.senderClientAddress && inputKey.Get().targetClientAddress == cls->sata.targetClientAddress;
// }

STATIC_FACTORY_DEFINITIONS(UDPProxyCoordinator,UDPProxyCoordinator);

UDPProxyCoordinator::UDPProxyCoordinator()
{

}
UDPProxyCoordinator::~UDPProxyCoordinator()
{
	Clear();
}
void UDPProxyCoordinator::SetRemoteLoginPassword(SLNet::RakString password)
{
	remoteLoginPassword=password;
}
void UDPProxyCoordinator::Update(void)
{
	unsigned int idx;
	SLNet::TimeMS curTime = SLNet::GetTimeMS();
	ForwardingRequest *fw;
	idx=0;
	while (idx < forwardingRequestList.Size())
	{
		fw=forwardingRequestList[idx];
		if (fw->timeRequestedPings!=0 &&
			curTime > fw->timeRequestedPings + DEFAULT_UNRESPONSIVE_PING_TIME_COORDINATOR)
		{
			fw->OrderRemainingServersToTry();
			fw->timeRequestedPings=0;
			TryNextServer(fw->sata, fw);
			idx++;
		}
		else if (fw->timeoutAfterSuccess!=0 &&
			curTime > fw->timeoutAfterSuccess)
		{
			// Forwarding request succeeded, we waited a bit to prevent duplicates. Can forget about the entry now.
			SLNet::OP_DELETE(fw,_FILE_AND_LINE_);
			forwardingRequestList.RemoveAtIndex(idx);
		}
		else
			idx++;
	}
}
PluginReceiveResult UDPProxyCoordinator::OnReceive(Packet *packet)
{
	if (packet->data[0]==ID_UDP_PROXY_GENERAL && packet->length>1)
	{
		switch (packet->data[1])
		{
		case ID_UDP_PROXY_FORWARDING_REQUEST_FROM_CLIENT_TO_COORDINATOR:
			OnForwardingRequestFromClientToCoordinator(packet);
			return RR_STOP_PROCESSING_AND_DEALLOCATE;
		case ID_UDP_PROXY_LOGIN_REQUEST_FROM_SERVER_TO_COORDINATOR:
			OnLoginRequestFromServerToCoordinator(packet);
			return RR_STOP_PROCESSING_AND_DEALLOCATE;
		case ID_UDP_PROXY_FORWARDING_REPLY_FROM_SERVER_TO_COORDINATOR:
			OnForwardingReplyFromServerToCoordinator(packet);
			return RR_STOP_PROCESSING_AND_DEALLOCATE;
		case ID_UDP_PROXY_PING_SERVERS_REPLY_FROM_CLIENT_TO_COORDINATOR:
			OnPingServersReplyFromClientToCoordinator(packet);
			return RR_STOP_PROCESSING_AND_DEALLOCATE;
		}
	}
	return RR_CONTINUE_PROCESSING;
}
void UDPProxyCoordinator::OnClosedConnection(const SystemAddress &systemAddress, RakNetGUID rakNetGUID, PI2_LostConnectionReason lostConnectionReason )
{
	(void) lostConnectionReason;
	(void) rakNetGUID;

	unsigned int idx, idx2;

	idx=0;
	while (idx < forwardingRequestList.Size())
	{
		if (forwardingRequestList[idx]->requestingAddress==systemAddress)
		{
			// Guy disconnected before the attempt completed
			SLNet::OP_DELETE(forwardingRequestList[idx], _FILE_AND_LINE_);
			forwardingRequestList.RemoveAtIndex(idx );
		}
		else
			idx++;
	}

	idx = serverList.GetIndexOf(systemAddress);
	if (idx!=(unsigned int)-1)
	{
		ForwardingRequest *fw;
		// For each pending client for this server, choose from remaining servers.
		for (idx2=0; idx2 < forwardingRequestList.Size(); idx2++)
		{
			fw = forwardingRequestList[idx2];
			if (fw->currentlyAttemptedServerAddress==systemAddress)
			{
				// Try the next server
				TryNextServer(fw->sata, fw);
			}
		}

		// Remove dead server
		serverList.RemoveAtIndexFast(idx);
	}
}
void UDPProxyCoordinator::OnForwardingRequestFromClientToCoordinator(Packet *packet)
{
	SLNet::BitStream incomingBs(packet->data, packet->length, false);
	incomingBs.IgnoreBytes(2);
	SystemAddress sourceAddress;
	incomingBs.Read(sourceAddress);
	if (sourceAddress==UNASSIGNED_SYSTEM_ADDRESS)
		sourceAddress=packet->systemAddress;
	SystemAddress targetAddress;
	RakNetGUID targetGuid;
	bool usesAddress=false;
	incomingBs.Read(usesAddress);
	if (usesAddress)
	{
		incomingBs.Read(targetAddress);
		targetGuid=rakPeerInterface->GetGuidFromSystemAddress(targetAddress);
	}
	else
	{
		incomingBs.Read(targetGuid);
		targetAddress=rakPeerInterface->GetSystemAddressFromGuid(targetGuid);
	}
	ForwardingRequest *fw = SLNet::OP_NEW<ForwardingRequest>(_FILE_AND_LINE_);
	fw->timeoutAfterSuccess=0;
	incomingBs.Read(fw->timeoutOnNoDataMS);
	bool hasServerSelectionBitstream=false;
	incomingBs.Read(hasServerSelectionBitstream);
	if (hasServerSelectionBitstream)
		incomingBs.Read(&(fw->serverSelectionBitstream));

	SLNet::BitStream outgoingBs;
	SenderAndTargetAddress sata;
	sata.senderClientAddress=sourceAddress;
	sata.targetClientAddress=targetAddress;
	sata.targetClientGuid=targetGuid;
	sata.senderClientGuid=rakPeerInterface->GetGuidFromSystemAddress(sourceAddress);
	SenderAndTargetAddress sataReversed;
	sataReversed.senderClientAddress=targetAddress;
	sataReversed.targetClientAddress=sourceAddress;
	sataReversed.senderClientGuid=sata.targetClientGuid;
	sataReversed.targetClientGuid=sata.senderClientGuid;

	unsigned int insertionIndex;
	bool objectExists1, objectExists2;
	insertionIndex=forwardingRequestList.GetIndexFromKey(sata, &objectExists1);
	forwardingRequestList.GetIndexFromKey(sataReversed, &objectExists2);

	if (objectExists1 || objectExists2)
	{
		outgoingBs.Write((MessageID)ID_UDP_PROXY_GENERAL);
		outgoingBs.Write((MessageID)ID_UDP_PROXY_IN_PROGRESS);
		outgoingBs.Write(sata.senderClientAddress);
		outgoingBs.Write(targetAddress);
		outgoingBs.Write(targetGuid);
		// Request in progress, not completed
		unsigned short forwardingPort=0;
		RakString serverPublicIp;
		outgoingBs.Write(serverPublicIp);
		outgoingBs.Write(forwardingPort);
		rakPeerInterface->Send(&outgoingBs, MEDIUM_PRIORITY, RELIABLE_ORDERED, 0, packet->systemAddress, false);
		SLNet::OP_DELETE(fw, _FILE_AND_LINE_);
		return;
	}

	if (serverList.Size()==0)
	{
		outgoingBs.Write((MessageID)ID_UDP_PROXY_GENERAL);
		outgoingBs.Write((MessageID)ID_UDP_PROXY_NO_SERVERS_ONLINE);
		outgoingBs.Write(sata.senderClientAddress);
		outgoingBs.Write(targetAddress);
		outgoingBs.Write(targetGuid);
		rakPeerInterface->Send(&outgoingBs, MEDIUM_PRIORITY, RELIABLE_ORDERED, 0, packet->systemAddress, false);
		SLNet::OP_DELETE(fw, _FILE_AND_LINE_);
		return;
	}

	if (rakPeerInterface->GetConnectionState(targetAddress)!=IS_CONNECTED && usesAddress==false)
	{
		outgoingBs.Write((MessageID)ID_UDP_PROXY_GENERAL);
		outgoingBs.Write((MessageID)ID_UDP_PROXY_RECIPIENT_GUID_NOT_CONNECTED_TO_COORDINATOR);
		outgoingBs.Write(sata.senderClientAddress);
		outgoingBs.Write(targetAddress);
		outgoingBs.Write(targetGuid);
		rakPeerInterface->Send(&outgoingBs, MEDIUM_PRIORITY, RELIABLE_ORDERED, 0, packet->systemAddress, false);
		SLNet::OP_DELETE(fw, _FILE_AND_LINE_);
		return;
	}

	fw->sata=sata;
	fw->requestingAddress=packet->systemAddress;

	if (serverList.Size()>1)
	{
		outgoingBs.Write((MessageID)ID_UDP_PROXY_GENERAL);
		outgoingBs.Write((MessageID)ID_UDP_PROXY_PING_SERVERS_FROM_COORDINATOR_TO_CLIENT);
		outgoingBs.Write(sourceAddress);
		outgoingBs.Write(targetAddress);
		outgoingBs.Write(targetGuid);
		unsigned short serverListSize = (unsigned short) serverList.Size();
		outgoingBs.Write(serverListSize);
		unsigned int idx;
		for (idx=0; idx < serverList.Size(); idx++)
			outgoingBs.Write(serverList[idx]);
		rakPeerInterface->Send(&outgoingBs, MEDIUM_PRIORITY, RELIABLE_ORDERED, 0, sourceAddress, false);
		rakPeerInterface->Send(&outgoingBs, MEDIUM_PRIORITY, RELIABLE_ORDERED, 0, targetAddress, false);
		fw->timeRequestedPings= SLNet::GetTimeMS();
		unsigned int copyIndex;
		for (copyIndex=0; copyIndex < serverList.Size(); copyIndex++)
			fw->remainingServersToTry.Push(serverList[copyIndex], _FILE_AND_LINE_ );
		forwardingRequestList.InsertAtIndex(fw, insertionIndex, _FILE_AND_LINE_ );
	}
	else
	{
		fw->timeRequestedPings=0;
		fw->currentlyAttemptedServerAddress=serverList[0];
		forwardingRequestList.InsertAtIndex(fw, insertionIndex, _FILE_AND_LINE_ );
		SendForwardingRequest(sourceAddress, targetAddress, fw->currentlyAttemptedServerAddress, fw->timeoutOnNoDataMS);
	}
}

void UDPProxyCoordinator::SendForwardingRequest(SystemAddress sourceAddress, SystemAddress targetAddress, SystemAddress serverAddress, SLNet::TimeMS timeoutOnNoDataMS)
{
	SLNet::BitStream outgoingBs;
	// Send request to desired server
	outgoingBs.Write((MessageID)ID_UDP_PROXY_GENERAL);
	outgoingBs.Write((MessageID)ID_UDP_PROXY_FORWARDING_REQUEST_FROM_COORDINATOR_TO_SERVER);
	outgoingBs.Write(sourceAddress);
	outgoingBs.Write(targetAddress);
	outgoingBs.Write(timeoutOnNoDataMS);
	rakPeerInterface->Send(&outgoingBs, MEDIUM_PRIORITY, RELIABLE_ORDERED, 0, serverAddress, false);
}
void UDPProxyCoordinator::OnLoginRequestFromServerToCoordinator(Packet *packet)
{
	SLNet::BitStream incomingBs(packet->data, packet->length, false);
	incomingBs.IgnoreBytes(2);
	SLNet::RakString password;
	incomingBs.Read(password);
	SLNet::BitStream outgoingBs;

	if (remoteLoginPassword.IsEmpty())
	{
		outgoingBs.Write((MessageID)ID_UDP_PROXY_GENERAL);
		outgoingBs.Write((MessageID)ID_UDP_PROXY_NO_PASSWORD_SET_FROM_COORDINATOR_TO_SERVER);
		outgoingBs.Write(password);
		rakPeerInterface->Send(&outgoingBs, MEDIUM_PRIORITY, RELIABLE_ORDERED, 0, packet->systemAddress, false);
		return;
	}

	if (remoteLoginPassword!=password)
	{
		outgoingBs.Write((MessageID)ID_UDP_PROXY_GENERAL);
		outgoingBs.Write((MessageID)ID_UDP_PROXY_WRONG_PASSWORD_FROM_COORDINATOR_TO_SERVER);
		outgoingBs.Write(password);
		rakPeerInterface->Send(&outgoingBs, MEDIUM_PRIORITY, RELIABLE_ORDERED, 0, packet->systemAddress, false);
		return;
	}

	unsigned int insertionIndex;
	insertionIndex=serverList.GetIndexOf(packet->systemAddress);
	if (insertionIndex!=(unsigned int)-1)
	{
		outgoingBs.Write((MessageID)ID_UDP_PROXY_GENERAL);
		outgoingBs.Write((MessageID)ID_UDP_PROXY_ALREADY_LOGGED_IN_FROM_COORDINATOR_TO_SERVER);
		outgoingBs.Write(password);
		rakPeerInterface->Send(&outgoingBs, MEDIUM_PRIORITY, RELIABLE_ORDERED, 0, packet->systemAddress, false);
		return;
	}
	serverList.Push(packet->systemAddress, _FILE_AND_LINE_ );
	outgoingBs.Write((MessageID)ID_UDP_PROXY_GENERAL);
	outgoingBs.Write((MessageID)ID_UDP_PROXY_LOGIN_SUCCESS_FROM_COORDINATOR_TO_SERVER);
	outgoingBs.Write(password);
	rakPeerInterface->Send(&outgoingBs, MEDIUM_PRIORITY, RELIABLE_ORDERED, 0, packet->systemAddress, false);
}
void UDPProxyCoordinator::OnForwardingReplyFromServerToCoordinator(Packet *packet)
{
	SLNet::BitStream incomingBs(packet->data, packet->length, false);
	incomingBs.IgnoreBytes(2);
	SenderAndTargetAddress sata;
	incomingBs.Read(sata.senderClientAddress);
	incomingBs.Read(sata.targetClientAddress);
	bool objectExists;
	unsigned int index = forwardingRequestList.GetIndexFromKey(sata, &objectExists);
	if (objectExists==false)
	{
		// The guy disconnected before the request finished
		return;
	}
	ForwardingRequest *fw = forwardingRequestList[index];
	sata.senderClientGuid = fw->sata.senderClientGuid;
	sata.targetClientGuid = fw->sata.targetClientGuid;

	RakString serverPublicIp;
	incomingBs.Read(serverPublicIp);

	if (serverPublicIp.IsEmpty())
	{
		char serverIP[64];
		packet->systemAddress.ToString(false,serverIP,static_cast<size_t>(64));
		serverPublicIp=serverIP;
	}

	UDPForwarderResult success;
	unsigned char c;
	incomingBs.Read(c);
	success=(UDPForwarderResult)c;

	unsigned short forwardingPort;
	incomingBs.Read(forwardingPort);

	SLNet::BitStream outgoingBs;
	if (success==UDPFORWARDER_SUCCESS)
	{
		outgoingBs.Write((MessageID)ID_UDP_PROXY_GENERAL);
		outgoingBs.Write((MessageID)ID_UDP_PROXY_FORWARDING_SUCCEEDED);
		outgoingBs.Write(sata.senderClientAddress);
		outgoingBs.Write(sata.targetClientAddress);
		outgoingBs.Write(sata.targetClientGuid);
		outgoingBs.Write(serverPublicIp);
		outgoingBs.Write(forwardingPort);
		rakPeerInterface->Send(&outgoingBs, MEDIUM_PRIORITY, RELIABLE_ORDERED, 0, fw->requestingAddress, false);

		outgoingBs.Reset();
		outgoingBs.Write((MessageID)ID_UDP_PROXY_GENERAL);
		outgoingBs.Write((MessageID)ID_UDP_PROXY_FORWARDING_NOTIFICATION);
		outgoingBs.Write(sata.senderClientAddress);
		outgoingBs.Write(sata.targetClientAddress);
		outgoingBs.Write(sata.targetClientGuid);
		outgoingBs.Write(serverPublicIp);
		outgoingBs.Write(forwardingPort);
		rakPeerInterface->Send(&outgoingBs, MEDIUM_PRIORITY, RELIABLE_ORDERED, 0, sata.targetClientAddress, false);

		// 05/18/09 Keep the entry around for some time after success, so duplicates are reported if attempting forwarding from the target system before notification of success
		fw->timeoutAfterSuccess= SLNet::GetTimeMS()+fw->timeoutOnNoDataMS;
		// forwardingRequestList.RemoveAtIndex(index);
		// SLNet::OP_DELETE(fw,_FILE_AND_LINE_);

		return;
	}
	else if (success==UDPFORWARDER_NO_SOCKETS)
	{
		// Try next server
		TryNextServer(sata, fw);
	}
	else
	{
		RakAssert(success==UDPFORWARDER_FORWARDING_ALREADY_EXISTS);

		// Return in progress
		outgoingBs.Write((MessageID)ID_UDP_PROXY_GENERAL);
		outgoingBs.Write((MessageID)ID_UDP_PROXY_IN_PROGRESS);
		outgoingBs.Write(sata.senderClientAddress);
		outgoingBs.Write(sata.targetClientAddress);
		outgoingBs.Write(sata.targetClientGuid);
		outgoingBs.Write(serverPublicIp);
		outgoingBs.Write(forwardingPort);
		rakPeerInterface->Send(&outgoingBs, MEDIUM_PRIORITY, RELIABLE_ORDERED, 0, fw->requestingAddress, false);
		forwardingRequestList.RemoveAtIndex(index);
		SLNet::OP_DELETE(fw,_FILE_AND_LINE_);
	}
}
void UDPProxyCoordinator::OnPingServersReplyFromClientToCoordinator(Packet *packet)
{
	SLNet::BitStream incomingBs(packet->data, packet->length, false);
	incomingBs.IgnoreBytes(2);
	unsigned short serversToPingSize;
	SystemAddress serverAddress;
	SenderAndTargetAddress sata;
	incomingBs.Read(sata.senderClientAddress);
	incomingBs.Read(sata.targetClientAddress);
	bool objectExists;
	unsigned int index = forwardingRequestList.GetIndexFromKey(sata, &objectExists);
	if (objectExists==false)
		return;
	unsigned short idx;
	ServerWithPing swp;
	ForwardingRequest *fw = forwardingRequestList[index];
	if (fw->timeRequestedPings==0)
		return;

	incomingBs.Read(serversToPingSize);
	if (packet->systemAddress==sata.senderClientAddress)
	{
		for (idx=0; idx < serversToPingSize; idx++)
		{
			incomingBs.Read(swp.serverAddress);
			incomingBs.Read(swp.ping);
			unsigned int index2;
			for (index2=0; index2 < fw->sourceServerPings.Size(); index2++)
			{
				if (fw->sourceServerPings[index2].ping >= swp.ping )
					break;
			}
			fw->sourceServerPings.Insert(swp, index2, _FILE_AND_LINE_);
		}
	}
	else
	{
		for (idx=0; idx < serversToPingSize; idx++)
		{
			incomingBs.Read(swp.serverAddress);
			incomingBs.Read(swp.ping);

			unsigned int index2;
			for (index2=0; index2 < fw->targetServerPings.Size(); index2++)
			{
				if (fw->targetServerPings[index2].ping >= swp.ping )
					break;
			}
			fw->sourceServerPings.Insert(swp, index2, _FILE_AND_LINE_);
		}
	}

	// Both systems have to give us pings to progress here. Otherwise will timeout in Update()
	if (fw->sourceServerPings.Size()>0 &&
		fw->targetServerPings.Size()>0)
	{
		fw->OrderRemainingServersToTry();
		fw->timeRequestedPings=0;
		TryNextServer(fw->sata, fw);
	}
}
void UDPProxyCoordinator::TryNextServer(SenderAndTargetAddress sata, ForwardingRequest *fw)
{
	bool pickedGoodServer=false;
	while(fw->remainingServersToTry.Size()>0)
	{
		fw->currentlyAttemptedServerAddress=fw->remainingServersToTry.Pop();
		if (serverList.GetIndexOf(fw->currentlyAttemptedServerAddress)!=(unsigned int)-1)
		{
			pickedGoodServer=true;
			break;
		}
	}

	if (pickedGoodServer==false)
	{
		SendAllBusy(sata.senderClientAddress, sata.targetClientAddress, sata.targetClientGuid, fw->requestingAddress);
		forwardingRequestList.Remove(sata);
		SLNet::OP_DELETE(fw,_FILE_AND_LINE_);
		return;
	}

	SendForwardingRequest(sata.senderClientAddress, sata.targetClientAddress, fw->currentlyAttemptedServerAddress, fw->timeoutOnNoDataMS);
}
void UDPProxyCoordinator::SendAllBusy(SystemAddress senderClientAddress, SystemAddress targetClientAddress, RakNetGUID targetClientGuid, SystemAddress requestingAddress)
{
	SLNet::BitStream outgoingBs;
	outgoingBs.Write((MessageID)ID_UDP_PROXY_GENERAL);
	outgoingBs.Write((MessageID)ID_UDP_PROXY_ALL_SERVERS_BUSY);
	outgoingBs.Write(senderClientAddress);
	outgoingBs.Write(targetClientAddress);
	outgoingBs.Write(targetClientGuid);
	rakPeerInterface->Send(&outgoingBs, MEDIUM_PRIORITY, RELIABLE_ORDERED, 0, requestingAddress, false);
}
void UDPProxyCoordinator::Clear(void)
{
	serverList.Clear(true, _FILE_AND_LINE_);
	for (unsigned int i=0; i < forwardingRequestList.Size(); i++)
	{
		SLNet::OP_DELETE(forwardingRequestList[i],_FILE_AND_LINE_);
	}
	forwardingRequestList.Clear(false, _FILE_AND_LINE_);
}
void UDPProxyCoordinator::ForwardingRequest::OrderRemainingServersToTry(void)
{
	//DataStructures::Multilist<ML_ORDERED_LIST,UDPProxyCoordinator::ServerWithPing,unsigned short> swpList;
	DataStructures::OrderedList<unsigned short, UDPProxyCoordinator::ServerWithPing, ServerWithPingComp> swpList;
	// swpList.SetSortOrder(true);

	if (sourceServerPings.Size()==0 && targetServerPings.Size()==0)
		return;

	unsigned int idx;
	UDPProxyCoordinator::ServerWithPing swp;
	for (idx=0; idx < remainingServersToTry.Size(); idx++)
	{
		swp.serverAddress=remainingServersToTry[idx];
		swp.ping=0;
		if (sourceServerPings.Size())
			swp.ping+=(unsigned short) (sourceServerPings[idx].ping);
		else
			swp.ping+=(unsigned short) (DEFAULT_CLIENT_UNRESPONSIVE_PING_TIME);
		if (targetServerPings.Size())
			swp.ping+=(unsigned short) (targetServerPings[idx].ping);
		else
			swp.ping+=(unsigned short) (DEFAULT_CLIENT_UNRESPONSIVE_PING_TIME);
		swpList.Insert(swp.ping, swp, false, _FILE_AND_LINE_);
	}
	remainingServersToTry.Clear(_FILE_AND_LINE_ );
	for (idx=0; idx < swpList.Size(); idx++)
	{
		remainingServersToTry.Push(swpList[idx].serverAddress, _FILE_AND_LINE_ );
	}
}

#endif // _RAKNET_SUPPORT_*
