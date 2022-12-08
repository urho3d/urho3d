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
#if _RAKNET_SUPPORT_Router2==1 && _RAKNET_SUPPORT_UDPForwarder==1

#include "slikenet/Router2.h"
#include "slikenet/peerinterface.h"
#include "slikenet/BitStream.h"
#include "slikenet/time.h"
#include "slikenet/GetTime.h"
#include "slikenet/DS_OrderedList.h"
#include "slikenet/SocketLayer.h"
#include "slikenet/FormatString.h"
#include "slikenet/SocketDefines.h"

using namespace SLNet;

#ifndef INVALID_SOCKET
#define INVALID_SOCKET -1
#endif

/*
Algorithm:

1. Sender calls ConnectInternal(). A ConnnectRequest structure is allocated and stored in the connectionRequests list, containing a list of every system we are connected to. ID_ROUTER_2_QUERY_FORWARDING is sent to all connected systems.

2. Upon the router getting ID_ROUTER_2_QUERY_FORWARDING, ID_ROUTER_2_REPLY_FORWARDING is sent to the sender indicating if that router is connected to the endpoint, along with the ping from the router to the endpoint.

3. Upon the sender getting ID_ROUTER_2_REPLY_FORWARDING, the connection request structure is looked up in Router2::UpdateForwarding. The ping is stored in that structure. Once all systems have replied, the system continues to the next state. If every system in step 1 has been exhausted, and routing has occured at least once, then ID_CONNECTION_LOST is returned. If every system in step 1 has been exhausted and routing has never occured, then ID_ROUTER_2_FORWARDING_NO_PATH is returned. Otherwise, the router with the lowest ping is chosen, and RequestForwarding() is called with that system, which sends ID_ROUTER_2_REQUEST_FORWARDING to the router.

4. When the router gets ID_ROUTER_2_REQUEST_FORWARDING, a MiniPunchRequest structure is allocated and stored in the miniPunchesInProgress list. The function SendOOBMessages() sends ID_ROUTER_2_REPLY_TO_SENDER_PORT from the routing sockets to both the sender and endpoint. It also sends ID_ROUTER_2_REPLY_TO_SPECIFIED_PORT through the regular RakNet connection.

5. The sender and endpoint should get ID_ROUTER_2_REPLY_TO_SENDER_PORT and/or ID_ROUTER_2_REPLY_TO_SPECIFIED_PORT depending on what type of router they have. If ID_ROUTER_2_REPLY_TO_SENDER_PORT arrives, then this will reply back to the routing socket directly. If ID_ROUTER_2_REPLY_TO_SPECIFIED_PORT arrives, then the reply port is modified to be the port specified by the router system. In both cases, ID_ROUTER_2_MINI_PUNCH_REPLY is sent. As the router has already setup the forwarding, ID_ROUTER_2_MINI_PUNCH_REPLY will actually arrive to the endpoint from the sender, and from the sender to the endpoint.

6. When ID_ROUTER_2_MINI_PUNCH_REPLY arrives, ID_ROUTER_2_MINI_PUNCH_REPLY_BOUNCE will be sent to the router. This is to tell the router that the forwarding has succeeded.

7. When ID_ROUTER_2_MINI_PUNCH_REPLY_BOUNCE arrives on the router, the router will find the two systems in the miniPunchesInProgress list, which was added in step 4 (See OnMiniPunchReplyBounce()). gotReplyFromSource or gotReplyFromEndpoint will be set to true, depending on the sender. When both gotReplyFromSource and gotReplyFromEndpoint have replied, then ID_ROUTER_2_REROUTE is sent to the endpoint, and ID_ROUTER_2_FORWARDING_ESTABLISHED is sent to the sender.

8. When the endpoint gets ID_ROUTER_2_REROUTE, the system address is updated for the guid of the sender using RakPeer::ChangeSystemAddress(). This happens in OnRerouted().

9. When the sender gets ID_ROUTER_2_FORWARDING_ESTABLISHED, then in OnForwardingSuccess() the endpoint is removed from the connectionRequest list and moved to the forwardedConnectionList.

10. In OnClosedConnection(), for the sender, if the closed connection is the endpoint, then the endpoint is removed from the forwardedConnectionList (this is a graceful disconnect). If the connection was instead lost to the router, then ConnectInternal() gets called, which goes back to step 1. If instead this was a connection requset in progress, then UpdateForwarding() gets called, which goes back to step 3.

11. When the user connects the endpoint and sender, then the sender will get ID_CONNECTION_REQUEST_ACCEPTED. The sender will look up the endpoint in the forwardedConnectionList, and send ID_ROUTER_2_INCREASE_TIMEOUT to the endpoint. This message will call SetTimeoutTime() on the endpoint, so that if the router disconnects, enough time is available for the reroute to complete.
*/

#define MIN_MINIPUNCH_TIMEOUT	5000




void Router2DebugInterface::ShowFailure(const char *message)
{
	printf("%s", message);
}
void Router2DebugInterface::ShowDiagnostic(const char *message)
{
	printf("%s", message);
}

enum Router2MessageIdentifiers
{
	ID_ROUTER_2_QUERY_FORWARDING,
	ID_ROUTER_2_REPLY_FORWARDING,
	ID_ROUTER_2_REQUEST_FORWARDING,
	ID_ROUTER_2_INCREASE_TIMEOUT,
};
Router2::ConnnectRequest::ConnnectRequest()
{

}
Router2::ConnnectRequest::~ConnnectRequest()
{

}

STATIC_FACTORY_DEFINITIONS(Router2,Router2);

Router2::Router2()
{
	udpForwarder=0;
	maximumForwardingRequests=0;
	debugInterface=0;
	socketFamily=AF_INET;
}
Router2::~Router2()
{
	ClearAll();

	if (udpForwarder)
	{
		udpForwarder->Shutdown();
		SLNet::OP_DELETE(udpForwarder,_FILE_AND_LINE_);
	}
}
void Router2::ClearMinipunches(void)
{
	miniPunchesInProgressMutex.Lock();
	miniPunchesInProgress.Clear(false,_FILE_AND_LINE_);
	miniPunchesInProgressMutex.Unlock();
}
void Router2::ClearConnectionRequests(void)
{
	connectionRequestsMutex.Lock();
	for (unsigned int i=0; i < connectionRequests.Size(); i++)
	{
		SLNet::OP_DELETE(connectionRequests[i],_FILE_AND_LINE_);
	}
	connectionRequests.Clear(false,_FILE_AND_LINE_);
	connectionRequestsMutex.Unlock();
}
bool Router2::ConnectInternal(RakNetGUID endpointGuid, bool returnConnectionLostOnFailure)
{
	int largestPing = GetLargestPingAmongConnectedSystems();
	if (largestPing<0)
	{
		char buff[512];
		if (debugInterface)	debugInterface->ShowFailure(FormatStringTS(buff,"Router2: ConnectInternal(%I64d) failed at %s:%i\n", endpointGuid.g, __FILE__, __LINE__));

		// Not connected to anyone
		return false;
	}

	// ALready in progress?
	connectionRequestsMutex.Lock();
	if (GetConnectionRequestIndex(endpointGuid)!=(unsigned int)-1)
	{
		connectionRequestsMutex.Unlock();
		char buff[512];
		if (debugInterface)	debugInterface->ShowFailure(FormatStringTS(buff,"Router2: ConnectInternal(%I64d) failed at %s:%i\n", endpointGuid.g, __FILE__, __LINE__));

		return false;
	}
	connectionRequestsMutex.Unlock();

	// StoreRequest(endpointGuid, Largest(ping*2), systemsSentTo). Set state REQUEST_STATE_QUERY_FORWARDING
	Router2::ConnnectRequest *cr = SLNet::OP_NEW<Router2::ConnnectRequest>(_FILE_AND_LINE_);
	DataStructures::List<SystemAddress> addresses;
	DataStructures::List<RakNetGUID> guids;
	rakPeerInterface->GetSystemList(addresses, guids);
	if (guids.Size()==0)
	{
		char buff[512];
		if (debugInterface)	debugInterface->ShowFailure(FormatStringTS(buff,"Router2 failed at %s:%i\n", _FILE_AND_LINE_));

		return false;
	}
	cr->requestState=R2RS_REQUEST_STATE_QUERY_FORWARDING;
	cr->pingTimeout= SLNet::GetTimeMS()+largestPing*2+1000;
	cr->endpointGuid=endpointGuid;
	cr->returnConnectionLostOnFailure=returnConnectionLostOnFailure;
	for (unsigned int i=0; i < guids.Size(); i++)
	{
		ConnectionRequestSystem crs;
		if (guids[i]!=endpointGuid)
		{
			crs.guid=guids[i];
			crs.pingToEndpoint=-1;
			cr->connectionRequestSystemsMutex.Lock();
			cr->connectionRequestSystems.Push(crs,_FILE_AND_LINE_);
			cr->connectionRequestSystemsMutex.Unlock();

			// Broadcast(ID_ROUTER_2_QUERY_FORWARDING, endpointGuid);
			SLNet::BitStream bsOut;
			bsOut.Write((MessageID)ID_ROUTER_2_INTERNAL);
			bsOut.Write((unsigned char) ID_ROUTER_2_QUERY_FORWARDING);
			bsOut.Write(endpointGuid);
			uint32_t pack_id = rakPeerInterface->Send(&bsOut,MEDIUM_PRIORITY,RELIABLE_ORDERED,0,crs.guid,false);

        	if (debugInterface)
        	{
        		char buff[512];
        		debugInterface->ShowDiagnostic(FormatStringTS(buff,"Router2::ConnectInternal: at %s:%i, pack_id = %d", __FILE__, __LINE__,pack_id));
        	}

		}
		else
		{
        	if (debugInterface)
        	{
        		char buff[512];
        		debugInterface->ShowDiagnostic(FormatStringTS(buff,"Router2::ConnectInternal: at %s:%i [else ..].: %I64d==%I64d", __FILE__, __LINE__,
        			guids[i].g,endpointGuid.g));
        	}                                                                                              
		}
	}
	connectionRequestsMutex.Lock();
	connectionRequests.Push(cr,_FILE_AND_LINE_);
	connectionRequestsMutex.Unlock();

	if (debugInterface)
	{
		char buff[512];
		debugInterface->ShowDiagnostic(FormatStringTS(buff,"Broadcasting ID_ROUTER_2_QUERY_FORWARDING to %I64d at %s:%i\n", endpointGuid.g , __FILE__, __LINE__));
	}

	return true;
}
void Router2::SetSocketFamily(unsigned short _socketFamily)
{
	socketFamily=_socketFamily;
}
void Router2::EstablishRouting(RakNetGUID endpointGuid)
{
	ConnectionState cs = rakPeerInterface->GetConnectionState(endpointGuid);
	if (cs!=IS_DISCONNECTED && cs!=IS_NOT_CONNECTED)
	{
		char buff[512];
		if (debugInterface)	debugInterface->ShowFailure(FormatStringTS(buff,"Router2 failed at %s:%i "
                "(already connected to the %I64d)\n", __FILE__, __LINE__, endpointGuid.g ));
		return;
	}

	ConnectInternal(endpointGuid,false);
}
void Router2::SetMaximumForwardingRequests(int max)
{
	if (max>0 && maximumForwardingRequests<=0)
	{
		udpForwarder = SLNet::OP_NEW<UDPForwarder>(_FILE_AND_LINE_);
		udpForwarder->Startup();
	}
	else if (max<=0 && maximumForwardingRequests>0)
	{
		udpForwarder->Shutdown();
		SLNet::OP_DELETE(udpForwarder,_FILE_AND_LINE_);
		udpForwarder=0;
	}

	maximumForwardingRequests=max;
}
PluginReceiveResult Router2::OnReceive(Packet *packet)
{
	SystemAddress sa;
	SLNet::BitStream bs(packet->data,packet->length,false);
	if (packet->data[0]==ID_ROUTER_2_INTERNAL)
	{
		switch (packet->data[1])
		{
		case ID_ROUTER_2_QUERY_FORWARDING:
			{
				OnQueryForwarding(packet);
				return RR_STOP_PROCESSING_AND_DEALLOCATE;
			}
		case ID_ROUTER_2_REPLY_FORWARDING:
			{
				OnQueryForwardingReply(packet);
				return RR_STOP_PROCESSING_AND_DEALLOCATE;
			}
		case ID_ROUTER_2_REQUEST_FORWARDING:
			{

                if (debugInterface)
                {
                    char buff[512];
                    char buff2[32];
                    packet->systemAddress.ToString(true,buff2,static_cast<size_t>(32));
                    debugInterface->ShowDiagnostic(FormatStringTS(buff,"Got ID_ROUTER_2_REQUEST_FORWARDING on ip %s from %I64d, ",
                        buff2,packet->guid.g));
                }

				OnRequestForwarding(packet);
				return RR_STOP_PROCESSING_AND_DEALLOCATE;
			}
		case ID_ROUTER_2_INCREASE_TIMEOUT:
			{
				/// The routed system wants more time to stay alive on no communication, in case the router drops or crashes
				rakPeerInterface->SetTimeoutTime(rakPeerInterface->GetTimeoutTime(packet->systemAddress)+10000, packet->systemAddress);
				return RR_STOP_PROCESSING_AND_DEALLOCATE;
			}
		}
	}
	else if (packet->data[0]==ID_OUT_OF_BAND_INTERNAL && packet->length>=2)
	{
		switch (packet->data[1])
		{
			case ID_ROUTER_2_REPLY_TO_SENDER_PORT:
				{
				SLNet::BitStream bsOut;
					bsOut.Write(packet->guid);
					SendOOBFromRakNetPort(ID_ROUTER_2_MINI_PUNCH_REPLY, &bsOut, packet->systemAddress);

					if (debugInterface)
					{
						char buff[512];
						char buff2[32];
						sa.ToString(false,buff2,static_cast<size_t>(32));
						debugInterface->ShowDiagnostic(FormatStringTS(buff,"Got ID_ROUTER_2_REPLY_TO_SENDER_PORT %i on address %s, replying with ID_ROUTER_2_MINI_PUNCH_REPLY at %s:%i\n", sa.GetPort(), buff2, _FILE_AND_LINE_));

//						packet->systemAddress.ToString(true,buff2);
//						debugInterface->ShowDiagnostic(FormatStringTS(buff,"Got ID_ROUTER_2_REPLY_TO_SENDER_PORT on address %s (%I64d), "
//                                       "replying with ID_ROUTER_2_MINI_PUNCH_REPLY at %s:%i\n", buff2,packet->guid.g, __FILE__, __LINE__));
					}

					return RR_STOP_PROCESSING_AND_DEALLOCATE;
				}
			case ID_ROUTER_2_REPLY_TO_SPECIFIED_PORT:
				{
				SLNet::BitStream bsOut;
					bsOut.Write(packet->guid);
					bs.IgnoreBytes(2);
					sa=packet->systemAddress;
					unsigned short port;
					bs.Read(port);
					sa.SetPortHostOrder(port);
					RakAssert(sa.GetPort()!=0);
					SendOOBFromRakNetPort(ID_ROUTER_2_MINI_PUNCH_REPLY, &bsOut, sa);

					if (debugInterface)
					{
						char buff[512];
						char buff2[32];
						sa.ToString(false,buff2,static_cast<size_t>(32));
						debugInterface->ShowDiagnostic(FormatStringTS(buff,"Got ID_ROUTER_2_REPLY_TO_SPECIFIED_PORT %i on address %s, "
                                        "replying with ID_ROUTER_2_MINI_PUNCH_REPLY at %s:%i\n", sa.GetPort(), buff2, __FILE__, __LINE__));
					}

					return RR_STOP_PROCESSING_AND_DEALLOCATE;
				}
			case ID_ROUTER_2_MINI_PUNCH_REPLY:
				OnMiniPunchReply(packet);
				return RR_STOP_PROCESSING_AND_DEALLOCATE;
			case ID_ROUTER_2_MINI_PUNCH_REPLY_BOUNCE:
				OnMiniPunchReplyBounce(packet);
				return RR_STOP_PROCESSING_AND_DEALLOCATE;
		}
	}
	else if (packet->data[0]==ID_ROUTER_2_FORWARDING_ESTABLISHED)
	{
//		printf("Got ID_ROUTER_2_FORWARDING_ESTABLISHED\n");
		if (OnForwardingSuccess(packet)==false)
			return RR_STOP_PROCESSING_AND_DEALLOCATE;
	}
	else if (packet->data[0]==ID_ROUTER_2_REROUTED)
	{
		OnRerouted(packet);
	}
	else if (packet->data[0]==ID_CONNECTION_REQUEST_ACCEPTED)
	{
		unsigned int forwardingIndex;
		forwardedConnectionListMutex.Lock();
		for (forwardingIndex=0; forwardingIndex < forwardedConnectionList.Size(); forwardingIndex++)
		{
			if (forwardedConnectionList[forwardingIndex].endpointGuid==packet->guid && forwardedConnectionList[forwardingIndex].weInitiatedForwarding)
				break;
		}

		if (forwardingIndex<forwardedConnectionList.Size())
		{
            forwardedConnectionListMutex.Unlock();

			// We connected to this system through a forwarding system
			// Have the endpoint take longer to drop us, in case the intermediary system drops
			SLNet::BitStream bsOut;
			bsOut.Write((MessageID)ID_ROUTER_2_INTERNAL);
			bsOut.Write((unsigned char) ID_ROUTER_2_INCREASE_TIMEOUT);
			rakPeerInterface->Send(&bsOut,HIGH_PRIORITY,RELIABLE,0,packet->guid,false);

			if (debugInterface)
			{
				char buff[512];
				debugInterface->ShowDiagnostic(FormatStringTS(buff,"Got ID_CONNECTION_REQUEST_ACCEPTED, "
                    "sending ID_ROUTER_2_INCREASE_TIMEOUT to the %I64d at %s:%i\n", packet->guid.g, __FILE__, __LINE__));
			}

			// Also take longer ourselves
			rakPeerInterface->SetTimeoutTime(rakPeerInterface->GetTimeoutTime(packet->systemAddress)+10000, packet->systemAddress);
		}
        else  {
        	// ~Gwynn: Fix for Receive hanging up problem on Windows XP
		    // See http://blog.delphi-jedi.net/2008/04/23/the-case-of-the-unexplained-dead-lock-in-a-single-thread/ for details
            forwardedConnectionListMutex.Unlock();
        }
	}
	else if (packet->data[0]==ID_ROUTER_2_FORWARDING_NO_PATH)
	{
		if (packet->wasGeneratedLocally==false)
			return RR_STOP_PROCESSING_AND_DEALLOCATE;
	}

	return RR_CONTINUE_PROCESSING;
}
void Router2::Update(void)
{
	SLNet::TimeMS curTime = SLNet::GetTimeMS();
	unsigned int connectionRequestIndex=0;
	connectionRequestsMutex.Lock();
	while (connectionRequestIndex < connectionRequests.Size())
	{
		ConnnectRequest* connectionRequest = connectionRequests[connectionRequestIndex];

		// pingTimeout is only used with R2RS_REQUEST_STATE_QUERY_FORWARDING
		if (connectionRequest->requestState==R2RS_REQUEST_STATE_QUERY_FORWARDING &&
			connectionRequest->pingTimeout < curTime)
		{
			bool anyRemoved=false;
			unsigned int connectionRequestGuidIndex=0;
			connectionRequest->connectionRequestSystemsMutex.Lock();
			while (connectionRequestGuidIndex < connectionRequest->connectionRequestSystems.Size())
			{
				if (connectionRequest->connectionRequestSystems[connectionRequestGuidIndex].pingToEndpoint<0)
				{
					anyRemoved=true;
					connectionRequest->connectionRequestSystems.RemoveAtIndexFast(connectionRequestGuidIndex);
				}
				else
				{
					connectionRequestGuidIndex++;
				}
			}
			connectionRequest->connectionRequestSystemsMutex.Unlock();

			if (anyRemoved)
			{				
				if (connectionRequestIndex!=(unsigned int)-1)
				{
					// connectionRequestsMutex should be locked before calling this function
					if (UpdateForwarding(connectionRequest)==false)
					{
						RemoveConnectionRequest(connectionRequestIndex);
					}
					else
					{
						connectionRequestIndex++;
					}
				}
				else
				{
					connectionRequestIndex++;
				}
			}
			else
			{
				connectionRequestIndex++;
			}
		}
		else
		{
			connectionRequestIndex++;
		}
	}
	connectionRequestsMutex.Unlock();

	unsigned int i=0;
	miniPunchesInProgressMutex.Lock();
	while (i < miniPunchesInProgress.Size())
	{
		if (miniPunchesInProgress[i].timeout<curTime)
		{
			SendFailureOnCannotForward(miniPunchesInProgress[i].sourceGuid, miniPunchesInProgress[i].endpointGuid);
			miniPunchesInProgress.RemoveAtIndexFast(i);
		}
		else if (curTime>miniPunchesInProgress[i].nextAction)
		{
			miniPunchesInProgress[i].nextAction=curTime+100;
			SendOOBMessages(&miniPunchesInProgress[i]);
		}
		else
			i++;
	}
	miniPunchesInProgressMutex.Unlock();

}
void Router2::OnClosedConnection(const SystemAddress &systemAddress, RakNetGUID rakNetGUID, PI2_LostConnectionReason lostConnectionReason )
{
	(void) lostConnectionReason;
	(void) systemAddress;


	unsigned int forwardedConnectionIndex=0;
	forwardedConnectionListMutex.Lock();
	while (forwardedConnectionIndex<forwardedConnectionList.Size())
	{
		if (forwardedConnectionList[forwardedConnectionIndex].endpointGuid==rakNetGUID)
		{
			if (debugInterface)
			{
				char buff[512];
				debugInterface->ShowDiagnostic(FormatStringTS(buff,"Closed connection to the %I64d, removing forwarding from list at %s:%i\n", rakNetGUID.g, __FILE__, __LINE__));
			}

			// No longer need forwarding
			forwardedConnectionList.RemoveAtIndexFast(forwardedConnectionIndex);
		}
		else if (forwardedConnectionList[forwardedConnectionIndex].intermediaryGuid==rakNetGUID && forwardedConnectionList[forwardedConnectionIndex].weInitiatedForwarding)
		{
			// Lost connection to intermediary. Restart process to connect to endpoint. If failed, push ID_CONNECTION_LOST. Also remove connection request if it already is in the list, to restart it
            connectionRequestsMutex.Lock();
			unsigned int pos = GetConnectionRequestIndex(forwardedConnectionList[forwardedConnectionIndex].endpointGuid);
			if((unsigned int)-1 != pos) { SLNet::OP_DELETE(connectionRequests[pos], __FILE__, __LINE__); connectionRequests.RemoveAtIndexFast(pos);}
			connectionRequestsMutex.Unlock();
            
			ConnectInternal(forwardedConnectionList[forwardedConnectionIndex].endpointGuid, true);

			forwardedConnectionIndex++;

			if (debugInterface)
			{
				char buff[512];
				debugInterface->ShowDiagnostic(FormatStringTS(buff,"Closed connection %I64d, restarting forwarding at %s:%i\n",rakNetGUID.g, __FILE__, __LINE__));
			}

			// This should not be removed - the connection is still forwarded, but perhaps through another system
//			forwardedConnectionList.RemoveAtIndexFast(forwardedConnectionIndex);
		}
		else
			forwardedConnectionIndex++;
	}
	forwardedConnectionListMutex.Unlock();

	unsigned int connectionRequestIndex=0;
	connectionRequestsMutex.Lock();
	while (connectionRequestIndex < connectionRequests.Size())
	{
		ConnnectRequest *cr = connectionRequests[connectionRequestIndex];
		cr->connectionRequestSystemsMutex.Lock();
		unsigned int connectionRequestGuidIndex = cr->GetGuidIndex(rakNetGUID);
		if (connectionRequestGuidIndex!=(unsigned int)-1)
		{
			cr->connectionRequestSystems.RemoveAtIndexFast(connectionRequestGuidIndex);
			cr->connectionRequestSystemsMutex.Unlock();
			if (UpdateForwarding(cr)==false) // If returns false, no connection request systems left
			{
				if (debugInterface)
				{
					char buff[512];
					debugInterface->ShowDiagnostic(FormatStringTS(buff,"Aborted connection to the %I64d, aborted forwarding at %s:%i\n", rakNetGUID.g, __FILE__, __LINE__));
				}

				RemoveConnectionRequest(connectionRequestIndex);
			}
			else // Else a system in the connection request list dropped. If cr->requestState==R2RS_REQUEST_STATE_QUERY_FORWARDING then we are still waiting for other systems to respond.
			{
				if (debugInterface)
				{
					char buff[512];
					debugInterface->ShowDiagnostic(FormatStringTS(buff,"Aborted connection attempt to %I64d, restarting forwarding to %I64d at %s:%i\n", rakNetGUID.g,cr->endpointGuid.g,__FILE__, __LINE__));
				}
//                 if(volatile bool is_my_fix_a_truth = true) { // A system in the list of potential systems to try routing to dropped. There is no need to restart the whole process.
//                     connectionRequestsMutex.Lock();
//                     connectionRequests.RemoveAtIndexFast(connectionRequestIndex);
//                     connectionRequestsMutex.Unlock();
// 
//                     if(false == ConnectInternal(cr->endpointGuid,cr->returnConnectionLostOnFailure))
//                         if (debugInterface)
//                         {
//                             char buff[512];
//                             debugInterface->ShowDiagnostic(FormatStringTS(buff,"ConnectInternal(cr->endpointGuid,cr->returnConnectionLostOnFailure) is false. at %s:%i\n", __FILE__, __LINE__));
//                         }
//                 }
                        
				connectionRequestIndex++;
			}
		}
		else
		{
			cr->connectionRequestSystemsMutex.Unlock();
			connectionRequestIndex++;
		}
	}
	connectionRequestsMutex.Unlock();


	unsigned int i=0;
	miniPunchesInProgressMutex.Lock();
	while (i < miniPunchesInProgress.Size())
	{
		if (miniPunchesInProgress[i].sourceGuid==rakNetGUID || miniPunchesInProgress[i].endpointGuid==rakNetGUID)
		{
			if (miniPunchesInProgress[i].sourceGuid!=rakNetGUID)
			{
				SendFailureOnCannotForward(miniPunchesInProgress[i].sourceGuid, miniPunchesInProgress[i].endpointGuid);
			}
			miniPunchesInProgress.RemoveAtIndexFast(i);
		}
		else
			i++;
	}
	miniPunchesInProgressMutex.Unlock();
}
void Router2::OnFailedConnectionAttempt(Packet *packet, PI2_FailedConnectionAttemptReason failedConnectionAttemptReason)
{
	(void) failedConnectionAttemptReason;
	(void) packet;

	unsigned int forwardedConnectionIndex=0;
	forwardedConnectionListMutex.Lock();
	while (forwardedConnectionIndex<forwardedConnectionList.Size())
	{
		if (forwardedConnectionList[forwardedConnectionIndex].intermediaryAddress==packet->systemAddress)
		{
			if (debugInterface)
			{
				char buff[512];
				debugInterface->ShowDiagnostic(FormatStringTS(buff,"Failed connection attempt to forwarded system (%I64d : %s) at %s:%i\n",
                        forwardedConnectionList[forwardedConnectionIndex].endpointGuid.g, packet->systemAddress.ToString(true), __FILE__, __LINE__));
			}

			packet->guid=forwardedConnectionList[forwardedConnectionIndex].endpointGuid;
			forwardedConnectionList.RemoveAtIndexFast(forwardedConnectionIndex);
		}
		else
			forwardedConnectionIndex++;
	}
	forwardedConnectionListMutex.Unlock();
}
void Router2::OnRakPeerShutdown(void)
{
	ClearAll();
}
// connectionRequestsMutex should already be locked
bool Router2::UpdateForwarding(ConnnectRequest* connectionRequest)
{
	connectionRequest->connectionRequestSystemsMutex.Lock();

 //   RAKNET_DEBUG_PRINTF(__FUNCTION__": connectionRequest->connectionRequestSystems.Size = %d", connectionRequest->connectionRequestSystems.Size());

	if (connectionRequest->connectionRequestSystems.Size()==0)
	{
		connectionRequest->connectionRequestSystemsMutex.Unlock();

	//	printf("Router2 failed at %s:%i\n", __FILE__, __LINE__);
		if (connectionRequest->returnConnectionLostOnFailure) {
			ReturnToUser(ID_CONNECTION_LOST, connectionRequest->endpointGuid, UNASSIGNED_SYSTEM_ADDRESS, true); // This is a connection which was previously established. Rerouting is not possible.
//             bool sendDisconnectionNotification = false;
//             rakPeerInterface->CloseConnection(rakPeerInterface->GetSystemAddressFromGuid(connectionRequest->endpointGuid), sendDisconnectionNotification);
//             RAKNET_DEBUG_PRINTF(__FUNCTION__": call rakPeerInterface->CloseConnection(%I64d)" , connectionRequest->endpointGuid.g);
        }
		else
			ReturnToUser(ID_ROUTER_2_FORWARDING_NO_PATH, connectionRequest->endpointGuid, UNASSIGNED_SYSTEM_ADDRESS, false);

		if (debugInterface)
		{
			char buff[512];
			debugInterface->ShowDiagnostic(FormatStringTS(buff,"Forwarding failed, no remaining systems at %s:%i\n", _FILE_AND_LINE_));
		}

		forwardedConnectionListMutex.Lock();

		for (unsigned int forwardedConnectionIndex=0; forwardedConnectionIndex < forwardedConnectionList.Size(); forwardedConnectionIndex++)
		{
			if (forwardedConnectionList[forwardedConnectionIndex].endpointGuid==connectionRequest->endpointGuid && forwardedConnectionList[forwardedConnectionIndex].weInitiatedForwarding)
			{
				forwardedConnectionList.RemoveAtIndexFast(forwardedConnectionIndex);
				break;
			}
		}
		forwardedConnectionListMutex.Unlock();

		return false;
	}
	connectionRequest->connectionRequestSystemsMutex.Unlock();

	if (connectionRequest->requestState==R2RS_REQUEST_STATE_QUERY_FORWARDING)
	{
		connectionRequest->connectionRequestSystemsMutex.Lock();

		for (unsigned int i=0; i < connectionRequest->connectionRequestSystems.Size(); i++)
		{
			if (connectionRequest->connectionRequestSystems[i].pingToEndpoint<0)
			{
				connectionRequest->connectionRequestSystemsMutex.Unlock();
				return true; // Forward query still in progress, just return
			}
		}
		connectionRequest->connectionRequestSystemsMutex.Unlock();

		RequestForwarding(connectionRequest);
	}
// 	else if (connectionRequest->requestState==REQUEST_STATE_REQUEST_FORWARDING)
// 	{
// 		RequestForwarding(connectionRequestIndex);
// 	}

	return true;
}
// connectionRequestsMutex should already be locked
void Router2::RemoveConnectionRequest(unsigned int connectionRequestIndex)
{
	SLNet::OP_DELETE(connectionRequests[connectionRequestIndex],_FILE_AND_LINE_);
	connectionRequests.RemoveAtIndexFast(connectionRequestIndex);
}
int ConnectionRequestSystemComp( const Router2::ConnectionRequestSystem & key, const Router2::ConnectionRequestSystem &data )
{
	if (key.pingToEndpoint * (key.usedForwardingEntries+1) < data.pingToEndpoint * (data.usedForwardingEntries+1))
		return -1;
	if (key.pingToEndpoint * (key.usedForwardingEntries+1) == data.pingToEndpoint * (data.usedForwardingEntries+1))
		return 1;
	if (key.guid < data.guid)
		return -1;
	if (key.guid > data.guid)
		return -1;
	return 0;
}
// connectionRequestsMutex should already be locked
void Router2::RequestForwarding(ConnnectRequest* connectionRequest)
{
	RakAssert(connectionRequest->requestState==R2RS_REQUEST_STATE_QUERY_FORWARDING);
	connectionRequest->requestState=REQUEST_STATE_REQUEST_FORWARDING;

	if (connectionRequest->GetGuidIndex(connectionRequest->lastRequestedForwardingSystem)!=(unsigned int)-1)
	{
		char buff[512];
		if (debugInterface)	debugInterface->ShowFailure(FormatStringTS(buff,"Router2 failed at %s:%i\n", _FILE_AND_LINE_));
		return;
	}

	// Prioritize systems to request forwarding
	DataStructures::OrderedList<ConnectionRequestSystem, ConnectionRequestSystem, ConnectionRequestSystemComp> commandList;
	unsigned int connectionRequestGuidIndex;
	connectionRequest->connectionRequestSystemsMutex.Lock();
	for (connectionRequestGuidIndex=0; connectionRequestGuidIndex < connectionRequest->connectionRequestSystems.Size(); connectionRequestGuidIndex++)
	{
		RakAssert(connectionRequest->connectionRequestSystems[connectionRequestGuidIndex].pingToEndpoint>=0);
		commandList.Insert(connectionRequest->connectionRequestSystems[connectionRequestGuidIndex],
			connectionRequest->connectionRequestSystems[connectionRequestGuidIndex],
			true,
			_FILE_AND_LINE_);
	}
	connectionRequest->connectionRequestSystemsMutex.Unlock();

	connectionRequest->lastRequestedForwardingSystem=commandList[0].guid;

	SLNet::BitStream bsOut;
	bsOut.Write((MessageID)ID_ROUTER_2_INTERNAL);
	bsOut.Write((unsigned char) ID_ROUTER_2_REQUEST_FORWARDING);
	bsOut.Write(connectionRequest->endpointGuid);
	rakPeerInterface->Send(&bsOut,MEDIUM_PRIORITY,RELIABLE_ORDERED,0,connectionRequest->lastRequestedForwardingSystem,false);

	if (debugInterface)
	{
		char buff[512];
		debugInterface->ShowDiagnostic(FormatStringTS(buff,"Sending ID_ROUTER_2_REQUEST_FORWARDING "
            "(connectionRequest->lastRequestedForwardingSystem = %I64d, connectionRequest->endpointGuid = %I64d) at %s:%i\n", 
            connectionRequest->lastRequestedForwardingSystem.g,connectionRequest->endpointGuid.g, __FILE__, __LINE__));
	}
}
void Router2::SendFailureOnCannotForward(RakNetGUID sourceGuid, RakNetGUID endpointGuid)
{
	SLNet::BitStream bsOut;
	bsOut.Write((MessageID)ID_ROUTER_2_INTERNAL);
	bsOut.Write((unsigned char) ID_ROUTER_2_REPLY_FORWARDING);
	bsOut.Write(endpointGuid);
	bsOut.Write(false);
	rakPeerInterface->Send(&bsOut,MEDIUM_PRIORITY,RELIABLE_ORDERED,0,sourceGuid,false);
}
int Router2::ReturnFailureOnCannotForward(RakNetGUID sourceGuid, RakNetGUID endpointGuid)
{
	// If the number of systems we are currently forwarding>=maxForwarding, return ID_ROUTER_2_REPLY_FORWARDING,endpointGuid,false
	if (udpForwarder==0 || udpForwarder->GetUsedForwardEntries()/2>maximumForwardingRequests)
	{
		char buff[512];
		if (debugInterface)	debugInterface->ShowFailure(FormatStringTS(buff,"Router2 failed (%I64d -> %I64d) at %s:%i\n", 
                   sourceGuid.g, endpointGuid.g,__FILE__, __LINE__));
		SendFailureOnCannotForward(sourceGuid,endpointGuid);
		return -1;
	}

	// We cannot forward connections which are themselves forwarded. Return fail in that case
	forwardedConnectionListMutex.Lock();
	for (unsigned int i=0; i < forwardedConnectionList.Size(); i++)
	{
		if ((forwardedConnectionList[i].endpointGuid==endpointGuid) 
			|| (forwardedConnectionList[i].endpointGuid==sourceGuid)) // sourceGuid is here so you do not respond to routing requests from systems you are already routing through.
		{
			forwardedConnectionListMutex.Unlock();

			char buff[512];
			if (debugInterface)	debugInterface->ShowFailure(FormatStringTS(buff,"Router2 failed at %s:%i\n", __FILE__, __LINE__));
			SendFailureOnCannotForward(sourceGuid,endpointGuid);
			return -1;
		}
	}
	forwardedConnectionListMutex.Unlock();

	int pingToEndpoint;
	pingToEndpoint = rakPeerInterface->GetAveragePing(endpointGuid);
	if (pingToEndpoint==-1)
	{
		char buff[512];
		if (debugInterface)	debugInterface->ShowFailure(FormatStringTS(buff,"Router2 failed (%I64d -> %I64d)  at %s:%i\n", 
            sourceGuid.g, endpointGuid.g,__FILE__, __LINE__));

		SendFailureOnCannotForward(sourceGuid,endpointGuid);
		return -1;
	}
	return pingToEndpoint;
}
void Router2::OnQueryForwarding(Packet *packet)
{
	SLNet::BitStream bs(packet->data, packet->length, false);
	bs.IgnoreBytes(sizeof(MessageID) + sizeof(unsigned char));
	RakNetGUID endpointGuid;
	// Read endpointGuid
	bs.Read(endpointGuid);

	int pingToEndpoint = ReturnFailureOnCannotForward(packet->guid, endpointGuid);
	if (pingToEndpoint==-1)
	{
		char buff[512];
		if (debugInterface)	debugInterface->ShowFailure(FormatStringTS(buff,"Router2 failed (%I64d) at %s:%i\n", packet->guid.g, __FILE__, __LINE__));
		return;
	}

	// If we are connected to endpointGuid, reply ID_ROUTER_2_REPLY_FORWARDING,endpointGuid,true,ping,numCurrentlyForwarding
	SLNet::BitStream bsOut;
	bsOut.Write((MessageID)ID_ROUTER_2_INTERNAL);
	bsOut.Write((unsigned char) ID_ROUTER_2_REPLY_FORWARDING);
	bsOut.Write(endpointGuid);
	bsOut.Write(true);
	bsOut.Write((unsigned short) pingToEndpoint);
	bsOut.Write((unsigned short) udpForwarder->GetUsedForwardEntries()/2);
	rakPeerInterface->Send(&bsOut,MEDIUM_PRIORITY,RELIABLE_ORDERED,0,packet->guid,false);

	if (debugInterface)
	{
		char buff[512];
		debugInterface->ShowDiagnostic(FormatStringTS(buff,"Sending ID_ROUTER_2_REPLY_FORWARDING to the %I64d at %s:%i\n", packet->guid.g, __FILE__, __LINE__));
	}
}
void Router2::OnQueryForwardingReply(Packet *packet)
{
	SLNet::BitStream bs(packet->data, packet->length, false);
	bs.IgnoreBytes(sizeof(MessageID) + sizeof(unsigned char));
	RakNetGUID endpointGuid;
	bs.Read(endpointGuid);
	// Find endpointGuid among stored requests
	bool canForward=false;
	bs.Read(canForward);


	connectionRequestsMutex.Lock();
	unsigned int connectionRequestIndex = GetConnectionRequestIndex(endpointGuid);
	if (connectionRequestIndex==(unsigned int)-1)
	{
		connectionRequestsMutex.Unlock();
		char buff[512];
		if (debugInterface)	debugInterface->ShowFailure(FormatStringTS(buff,"Router2 failed (%I64d) at %s:%i\n", endpointGuid.g, __FILE__, __LINE__));
		return;
	}

	connectionRequests[connectionRequestIndex]->connectionRequestSystemsMutex.Lock();
	unsigned int connectionRequestGuidIndex = connectionRequests[connectionRequestIndex]->GetGuidIndex(packet->guid);
	if (connectionRequestGuidIndex==(unsigned int)-1)
	{
		connectionRequests[connectionRequestIndex]->connectionRequestSystemsMutex.Unlock();
		connectionRequestsMutex.Unlock();
		char buff[512];
		if (debugInterface)	debugInterface->ShowFailure(FormatStringTS(buff,"Router2 failed (%I64d) at %s:%i\n", endpointGuid.g, __FILE__, __LINE__));
		return;
	}

	if (debugInterface)
	{
		char buff[512];
        char buff2[512];
        packet->systemAddress.ToString(true,buff2,static_cast<size_t>(512));
		debugInterface->ShowDiagnostic(FormatStringTS(buff,"Got ID_ROUTER_2_REPLY_FORWARDING on address %s(%I64d -> %I64d) canForward=%i at %s:%i\n",
            buff2, packet->guid.g, endpointGuid.g, canForward, __FILE__, __LINE__));
	}

	if (canForward)
	{
		unsigned short pingToEndpoint;
		unsigned short usedEntries;
		bs.Read(pingToEndpoint);
		bs.Read(usedEntries);
		connectionRequests[connectionRequestIndex]->connectionRequestSystems[connectionRequestGuidIndex].usedForwardingEntries=usedEntries;
		connectionRequests[connectionRequestIndex]->connectionRequestSystems[connectionRequestGuidIndex].pingToEndpoint=rakPeerInterface->GetAveragePing(packet->guid)+pingToEndpoint;
	}
	else
	{
		connectionRequests[connectionRequestIndex]->connectionRequestSystems.RemoveAtIndex(connectionRequestGuidIndex);
	}
	connectionRequests[connectionRequestIndex]->connectionRequestSystemsMutex.Unlock();

	if (UpdateForwarding(connectionRequests[connectionRequestIndex])==false)
	{
		RemoveConnectionRequest(connectionRequestIndex);
	}
	connectionRequestsMutex.Unlock();
}
void Router2::SendForwardingSuccess(MessageID messageId, RakNetGUID sourceGuid, RakNetGUID endpointGuid, unsigned short sourceToDstPort)
{
	SLNet::BitStream bsOut;
	bsOut.Write(messageId);
	bsOut.Write(endpointGuid);
	bsOut.Write(sourceToDstPort);
	rakPeerInterface->Send(&bsOut,MEDIUM_PRIORITY,RELIABLE_ORDERED,0,sourceGuid,false);

	if (debugInterface)
	{
		char buff[512];
		if (messageId==ID_ROUTER_2_FORWARDING_ESTABLISHED)
			debugInterface->ShowDiagnostic(FormatStringTS(buff,"Sending ID_ROUTER_2_FORWARDING_ESTABLISHED at %s:%i\n", _FILE_AND_LINE_ ));
		else
			debugInterface->ShowDiagnostic(FormatStringTS(buff,"Sending ID_ROUTER_2_REROUTED at %s:%i\n", _FILE_AND_LINE_ ));
	}
}
void Router2::SendOOBFromRakNetPort(OutOfBandIdentifiers oob, BitStream *extraData, SystemAddress sa)
{
	SLNet::BitStream oobBs;
	oobBs.Write((unsigned char)oob);
	if (extraData)
	{
		extraData->ResetReadPointer();
		oobBs.Write(*extraData);
	}
	char ipAddressString[32];
	sa.ToString(false, ipAddressString,static_cast<size_t>(32));
	rakPeerInterface->SendOutOfBand((const char*) ipAddressString,sa.GetPort(),(const char*) oobBs.GetData(),oobBs.GetNumberOfBytesUsed());
}
void Router2::SendOOBFromSpecifiedSocket(OutOfBandIdentifiers oob, SystemAddress sa, __UDPSOCKET__ socket)
{
	SLNet::BitStream bs;
	rakPeerInterface->WriteOutOfBandHeader(&bs);
	bs.Write((unsigned char) oob);
	// SocketLayer::SendTo_PC( socket, (const char*) bs.GetData(), bs.GetNumberOfBytesUsed(), sa, __FILE__, __LINE__  );


	if (sa.address.addr4.sin_family==AF_INET)
	{
		sendto__( socket, (const char*) bs.GetData(), bs.GetNumberOfBytesUsed(), 0, ( const sockaddr* ) & sa.address.addr4, sizeof( sockaddr_in ) );
	}
	else
	{
		#if RAKNET_SUPPORT_IPV6==1
		sendto__( socket, (const char*) bs.GetData(), bs.GetNumberOfBytesUsed(), 0, ( const sockaddr* ) & sa.address.addr6, sizeof( sockaddr_in6 ) );
		#endif
	}












}
void Router2::SendOOBMessages(Router2::MiniPunchRequest *mpr)
{
	// Mini NAT punch
	// Send from srcToDestPort to packet->systemAddress (source). If the message arrives, the remote system should reply.
	SendOOBFromSpecifiedSocket(ID_ROUTER_2_REPLY_TO_SENDER_PORT, mpr->sourceAddress, mpr->forwardingSocket);

	// Send from destToSourcePort to endpointSystemAddress (destination). If the message arrives, the remote system should reply.
	SendOOBFromSpecifiedSocket(ID_ROUTER_2_REPLY_TO_SENDER_PORT, mpr->endpointAddress, mpr->forwardingSocket);


    if (debugInterface) {
        char buff [512];

        char buff2[128];

        mpr->sourceAddress   .ToString(true,buff2,static_cast<size_t>(128));

        debugInterface->ShowDiagnostic(FormatStringTS(buff,"call SendOOBFromSpecifiedSocket(...,%s,...)", buff2));

        mpr->endpointAddress .ToString(true,buff2,static_cast<size_t>(128));

        debugInterface->ShowDiagnostic(FormatStringTS(buff,"call SendOOBFromSpecifiedSocket(...,%s,...)", buff2));
    }                                              

	// Tell source to send to forwardingPort
	SLNet::BitStream extraData;
	extraData.Write(mpr->forwardingPort);
	RakAssert(mpr->forwardingPort!=0);
	SendOOBFromRakNetPort(ID_ROUTER_2_REPLY_TO_SPECIFIED_PORT, &extraData, mpr->sourceAddress);

	// Tell destination to send to forwardingPort
	extraData.Reset();
	extraData.Write(mpr->forwardingPort);
	RakAssert(mpr->forwardingPort);
	SendOOBFromRakNetPort(ID_ROUTER_2_REPLY_TO_SPECIFIED_PORT, &extraData, mpr->endpointAddress);
}
void Router2::OnRequestForwarding(Packet *packet)
{
	SLNet::BitStream bs(packet->data, packet->length, false);
	bs.IgnoreBytes(sizeof(MessageID) + sizeof(unsigned char));
	RakNetGUID endpointGuid;
	bs.Read(endpointGuid);

	int pingToEndpoint = ReturnFailureOnCannotForward(packet->guid, endpointGuid);
	if (pingToEndpoint==-1)
	{
		char buff[512];
		if (debugInterface)	debugInterface->ShowFailure(FormatStringTS(buff,"Router2 failed (packet->guid =%I64d, endpointGuid = %I64d) at %s:%i\n", 
                packet->guid.g, endpointGuid.g, __FILE__, __LINE__));
		return;
	}

	unsigned short forwardingPort=0;
	__UDPSOCKET__ forwardingSocket=INVALID_SOCKET;
	SystemAddress endpointSystemAddress = rakPeerInterface->GetSystemAddressFromGuid(endpointGuid);
	UDPForwarderResult result = udpForwarder->StartForwarding(
		packet->systemAddress, endpointSystemAddress, 30000, 0, socketFamily,
		&forwardingPort, &forwardingSocket);

	if (result==UDPFORWARDER_FORWARDING_ALREADY_EXISTS)
	{
		if (debugInterface)
		{
			char buff[512];
			debugInterface->ShowDiagnostic(FormatStringTS(buff,"Got ID_ROUTER_2_REQUEST_FORWARDING, result=UDPFORWARDER_FORWARDING_ALREADY_EXISTS "
                    "(packet->guid =%I64d, endpointGuid = %I64d) at %s:%i\n", 
                packet->guid.g, endpointGuid.g,__FILE__, __LINE__));
		}

		SendForwardingSuccess(ID_ROUTER_2_FORWARDING_ESTABLISHED, packet->guid, endpointGuid, forwardingPort);
	}
	else if (result==UDPFORWARDER_NO_SOCKETS)
	{
		char buff[512];
		char buff2[64];
		char buff3[64];
		packet->systemAddress.ToString(true,buff2,static_cast<size_t>(64));
		endpointSystemAddress.ToString(true,buff3,static_cast<size_t>(64));
		if (debugInterface)
			debugInterface->ShowFailure(FormatStringTS(buff,"Router2 failed at %s:%i with UDPFORWARDER_NO_SOCKETS, packet->systemAddress=%s, endpointSystemAddress=%s, forwardingPort=%i, forwardingSocket=%i\n",
			__FILE__, __LINE__, buff2, buff3, forwardingPort, forwardingSocket));
		SendFailureOnCannotForward(packet->guid, endpointGuid);
	}
	else if (result==UDPFORWARDER_INVALID_PARAMETERS)
	{
		char buff[512];
		char buff2[64];
		char buff3[64];
		packet->systemAddress.ToString(true,buff2,static_cast<size_t>(64));
		endpointSystemAddress.ToString(true,buff3,static_cast<size_t>(64));
		if (debugInterface)
			debugInterface->ShowFailure(FormatStringTS(buff,"Router2 failed at %s:%i with UDPFORWARDER_INVALID_PARAMETERS, packet->systemAddress=%s, endpointSystemAddress=%s, forwardingPort=%i, forwardingSocket=%i\n",
			__FILE__, __LINE__, buff2, buff3, forwardingPort, forwardingSocket));
		SendFailureOnCannotForward(packet->guid, endpointGuid);
	}
	else if (result==UDPFORWARDER_BIND_FAILED)
	{
		char buff[512];
		char buff2[64];
		char buff3[64];
		packet->systemAddress.ToString(true,buff2,static_cast<size_t>(64));
		endpointSystemAddress.ToString(true,buff3,static_cast<size_t>(64));
		if (debugInterface)
			debugInterface->ShowFailure(FormatStringTS(buff,"Router2 failed at %s:%i with UDPFORWARDER_BIND_FAILED, packet->systemAddress=%s, endpointSystemAddress=%s, forwardingPort=%i, forwardingSocket=%i\n",
			__FILE__, __LINE__, buff2, buff3, forwardingPort, forwardingSocket));
		SendFailureOnCannotForward(packet->guid, endpointGuid);
	}
	else
	{
		if (debugInterface)
		{
			char buff2[32];
			char buff3[32];
			endpointSystemAddress.ToString(true,buff2,static_cast<size_t>(32));
			packet->systemAddress.ToString(true,buff3,static_cast<size_t>(32));
			char buff[512];
			debugInterface->ShowDiagnostic(FormatStringTS(buff,"Got ID_ROUTER_2_REQUEST_FORWARDING.\n"
				"endpointAddress=%s\nsourceAddress=%s\nforwardingPort=%i\n "				
				"calling SendOOBMessages at %s:%i\n", buff2,buff3,forwardingPort,_FILE_AND_LINE_));
		}

		// Store the punch request
		MiniPunchRequest miniPunchRequest;
		miniPunchRequest.endpointAddress=endpointSystemAddress;
		miniPunchRequest.endpointGuid=endpointGuid;
		miniPunchRequest.gotReplyFromEndpoint=false;
		miniPunchRequest.gotReplyFromSource=false;
		miniPunchRequest.sourceGuid=packet->guid;
		miniPunchRequest.sourceAddress=packet->systemAddress;
		miniPunchRequest.forwardingPort=forwardingPort;
		miniPunchRequest.forwardingSocket=forwardingSocket;
		int ping1 = rakPeerInterface->GetAveragePing(packet->guid);
		int ping2 = rakPeerInterface->GetAveragePing(endpointGuid);
		if (ping1>ping2)
			miniPunchRequest.timeout= SLNet::GetTimeMS() + ping1*8+300;
		else
			miniPunchRequest.timeout= SLNet::GetTimeMS() + ping2*8+300;
		miniPunchRequest.nextAction= SLNet::GetTimeMS()+100;
		SendOOBMessages(&miniPunchRequest);
		miniPunchesInProgressMutex.Lock();
		miniPunchesInProgress.Push(miniPunchRequest,_FILE_AND_LINE_);
		miniPunchesInProgressMutex.Unlock();
	}
}
void Router2::OnMiniPunchReplyBounce(Packet *packet)
{
	// Find stored punch request
	unsigned int i=0;

	if (debugInterface)
	{
		char buff[512];
		debugInterface->ShowDiagnostic(FormatStringTS(buff,"Got ID_ROUTER_2_MINI_PUNCH_REPLY_BOUNCE from guid=%I64d (miniPunchesInProgress.Size() = %d)", 
			packet->guid.g, miniPunchesInProgress.Size()));
	}

	miniPunchesInProgressMutex.Lock();
	while (i < miniPunchesInProgress.Size())
	{
		if (miniPunchesInProgress[i].sourceGuid==packet->guid || miniPunchesInProgress[i].endpointGuid==packet->guid)
		{
			if (miniPunchesInProgress[i].sourceGuid==packet->guid)
				miniPunchesInProgress[i].gotReplyFromSource=true;
			if (miniPunchesInProgress[i].endpointGuid==packet->guid)
				miniPunchesInProgress[i].gotReplyFromEndpoint=true;

			if (debugInterface)
			{
				char buff[512];
				debugInterface->ShowDiagnostic(FormatStringTS(buff,"Processing ID_ROUTER_2_MINI_PUNCH_REPLY_BOUNCE, gotReplyFromSource=%i gotReplyFromEndpoint=%i at %s:%i\n", miniPunchesInProgress[i].gotReplyFromSource, miniPunchesInProgress[i].gotReplyFromEndpoint, __FILE__, __LINE__));
			}

			if (miniPunchesInProgress[i].gotReplyFromEndpoint==true &&
				miniPunchesInProgress[i].gotReplyFromSource==true)
			{
				SendForwardingSuccess(ID_ROUTER_2_REROUTED,               miniPunchesInProgress[i].endpointGuid, miniPunchesInProgress[i].sourceGuid,   miniPunchesInProgress[i].forwardingPort);
				SendForwardingSuccess(ID_ROUTER_2_FORWARDING_ESTABLISHED, miniPunchesInProgress[i].sourceGuid,   miniPunchesInProgress[i].endpointGuid, miniPunchesInProgress[i].forwardingPort);
				miniPunchesInProgress.RemoveAtIndexFast(i);
			}
			else
			{
				i++;
			}
		}
		else
			i++;
	}
	miniPunchesInProgressMutex.Unlock();
}
void Router2::OnMiniPunchReply(Packet *packet)
{
	SLNet::BitStream bs(packet->data, packet->length, false);
	bs.IgnoreBytes(sizeof(MessageID) + sizeof(unsigned char));
	RakNetGUID routerGuid;
	bs.Read(routerGuid);
	SendOOBFromRakNetPort(ID_ROUTER_2_MINI_PUNCH_REPLY_BOUNCE, 0, rakPeerInterface->GetSystemAddressFromGuid(routerGuid));

	if (debugInterface)
	{
		char buff[512];

        char buff2[512];

        rakPeerInterface->GetSystemAddressFromGuid(routerGuid).ToString(true,buff2,static_cast<size_t>(512));

		debugInterface->ShowDiagnostic(FormatStringTS(buff,"Sending ID_ROUTER_2_MINI_PUNCH_REPLY_BOUNCE (%s) at %s:%i\n", buff2, __FILE__, __LINE__));
	}
}
void Router2::OnRerouted(Packet *packet)
{
	SLNet::BitStream bs(packet->data, packet->length, false);
	bs.IgnoreBytes(sizeof(MessageID));
	RakNetGUID endpointGuid;
	bs.Read(endpointGuid);
	unsigned short sourceToDestPort;
	bs.Read(sourceToDestPort);

	// Return rerouted notice
	SystemAddress intermediaryAddress=packet->systemAddress;
	intermediaryAddress.SetPortHostOrder(sourceToDestPort);
	rakPeerInterface->ChangeSystemAddress(endpointGuid, intermediaryAddress);

    unsigned int forwardingIndex;
	forwardedConnectionListMutex.Lock();
	for (forwardingIndex=0; forwardingIndex < forwardedConnectionList.Size(); forwardingIndex++)
	{
		if (forwardedConnectionList[forwardingIndex].endpointGuid==endpointGuid)
			break;
	}

	if (forwardingIndex<forwardedConnectionList.Size())
	{
		ForwardedConnection& ref_fc     = forwardedConnectionList[forwardingIndex];
		forwardedConnectionListMutex.Unlock();

    	ref_fc.intermediaryAddress      = packet->systemAddress;
		ref_fc.intermediaryAddress.SetPortHostOrder(sourceToDestPort);
		ref_fc.intermediaryGuid         = packet->guid;

        rakPeerInterface->ChangeSystemAddress(endpointGuid, intermediaryAddress);

        if (debugInterface)
        {
            char buff[512];
            debugInterface->ShowDiagnostic(FormatStringTS(buff,"FIX: Got ID_ROUTER_2_REROUTE, returning ID_ROUTER_2_REROUTED,"
                " Calling RakPeer::ChangeSystemAddress(%I64d, %s) at %s:%i\n",endpointGuid.g, intermediaryAddress.ToString(true), __FILE__, __LINE__));
        }
    }
    else
    {
        ForwardedConnection fc;
        fc.endpointGuid=endpointGuid;
        fc.intermediaryAddress=packet->systemAddress;
        fc.intermediaryAddress.SetPortHostOrder(sourceToDestPort);
        fc.intermediaryGuid=packet->guid;
        fc.weInitiatedForwarding=false;
        // add to forwarding list. This is only here to avoid reporting direct connections in Router2::ReturnFailureOnCannotForward
        forwardedConnectionList.Push (fc,__FILE__, __LINE__);
        forwardedConnectionListMutex.Unlock();

        rakPeerInterface->ChangeSystemAddress(endpointGuid, intermediaryAddress);

        if (debugInterface)
        {
            char buff[512];
            debugInterface->ShowDiagnostic(FormatStringTS(buff,"Got ID_ROUTER_2_REROUTE, returning ID_ROUTER_2_REROUTED, Calling RakPeer::ChangeSystemAddress at %s:%i\n", __FILE__, __LINE__));
        }
    }

}
bool Router2::OnForwardingSuccess(Packet *packet)
{
	SLNet::BitStream bs(packet->data, packet->length, false);
	bs.IgnoreBytes(sizeof(MessageID));
	RakNetGUID endpointGuid;
	bs.Read(endpointGuid);
	unsigned short sourceToDestPort;
	bs.Read(sourceToDestPort);

	unsigned int forwardingIndex;
	forwardedConnectionListMutex.Lock();
	for (forwardingIndex=0; forwardingIndex < forwardedConnectionList.Size(); forwardingIndex++)
	{
		if (forwardedConnectionList[forwardingIndex].endpointGuid==endpointGuid)
			break;
	}

	if (forwardingIndex<forwardedConnectionList.Size())
	{
		// Return rerouted notice
		SystemAddress intermediaryAddress=packet->systemAddress;
		intermediaryAddress.SetPortHostOrder(sourceToDestPort);
		rakPeerInterface->ChangeSystemAddress(endpointGuid, intermediaryAddress);

        ////////////////////////////////////////////////////////////////////////////
        ForwardedConnection& ref_fc     = forwardedConnectionList[forwardingIndex];
    	ref_fc.intermediaryAddress      = packet->systemAddress;
		ref_fc.intermediaryAddress.SetPortHostOrder(sourceToDestPort);
		ref_fc.intermediaryGuid         = packet->guid;
        ////////////////////////////////////////////////////////////////////////////

		if (debugInterface)
		{
			char buff[512];
			debugInterface->ShowDiagnostic(FormatStringTS(buff,"Got ID_ROUTER_2_FORWARDING_ESTABLISHED, returning ID_ROUTER_2_REROUTED, Calling RakPeer::ChangeSystemAddress at %s:%i\n", _FILE_AND_LINE_));
		}

		packet->data[0]=ID_ROUTER_2_REROUTED;

    	forwardedConnectionListMutex.Unlock();
		return true; // Return packet to user
	}
	else
	{
		forwardedConnectionListMutex.Unlock();

		// removeFrom connectionRequests;
		ForwardedConnection fc;
		connectionRequestsMutex.Lock();
		unsigned int connectionRequestIndex = GetConnectionRequestIndex(endpointGuid);
		fc.returnConnectionLostOnFailure=connectionRequests[connectionRequestIndex]->returnConnectionLostOnFailure;
		connectionRequests.RemoveAtIndexFast(connectionRequestIndex);
		connectionRequestsMutex.Unlock();
		fc.endpointGuid=endpointGuid;
		fc.intermediaryAddress=packet->systemAddress;
		fc.intermediaryAddress.SetPortHostOrder(sourceToDestPort);
		fc.intermediaryGuid=packet->guid;
		fc.weInitiatedForwarding=true;

		// add to forwarding list
		forwardedConnectionListMutex.Lock();
		forwardedConnectionList.Push (fc,_FILE_AND_LINE_);
		forwardedConnectionListMutex.Unlock();

		if (debugInterface)
		{
			char buff[512];
			debugInterface->ShowDiagnostic(FormatStringTS(buff,"Got and returning to user ID_ROUTER_2_FORWARDING_ESTABLISHED at %s:%i\n", _FILE_AND_LINE_));
		}

	}
	return true; // Return packet to user
}
int Router2::GetLargestPingAmongConnectedSystems(void) const
{
	int avePing;
	int largestPing=-1;
	unsigned int maxPeers = rakPeerInterface->GetMaximumNumberOfPeers();
	if (maxPeers==0)
		return 9999;
	unsigned int index;
	for (index=0; index < rakPeerInterface->GetMaximumNumberOfPeers(); index++)
	{
		RakNetGUID g = rakPeerInterface->GetGUIDFromIndex(index);
		if (g!=UNASSIGNED_RAKNET_GUID)
		{
			avePing=rakPeerInterface->GetAveragePing(rakPeerInterface->GetGUIDFromIndex(index));
			if (avePing>largestPing)
				largestPing=avePing;
		}
	}
	return largestPing;
}

unsigned int Router2::GetConnectionRequestIndex(RakNetGUID endpointGuid)
{
	unsigned int i;
	for (i=0; i < connectionRequests.Size(); i++)
	{
		if (connectionRequests[i]->endpointGuid==endpointGuid)
			return i;
	}
	return (unsigned int) -1;
}
unsigned int Router2::ConnnectRequest::GetGuidIndex(RakNetGUID guid)
{
	unsigned int i;
	for (i=0; i < connectionRequestSystems.Size(); i++)
	{
		if (connectionRequestSystems[i].guid==guid)
			return i;
	}
	return (unsigned int) -1;
}
void Router2::ReturnToUser(MessageID messageId, RakNetGUID endpointGuid, const SystemAddress &systemAddress, bool wasGeneratedLocally)
{
	Packet *p = AllocatePacketUnified(sizeof(MessageID)+sizeof(unsigned char));
	p->data[0]=messageId;
	p->systemAddress=systemAddress;
	p->systemAddress.systemIndex=(SystemIndex)-1;
	p->guid=endpointGuid;
	p->wasGeneratedLocally=wasGeneratedLocally;
	rakPeerInterface->PushBackPacket(p, true);
}
void Router2::ClearForwardedConnections(void)
{
	forwardedConnectionListMutex.Lock();
	forwardedConnectionList.Clear(false,_FILE_AND_LINE_);
	forwardedConnectionListMutex.Unlock();
}
void Router2::ClearAll(void)
{
	ClearConnectionRequests();
	ClearMinipunches();
	ClearForwardedConnections();
}
void Router2::SetDebugInterface(Router2DebugInterface *_debugInterface)
{
	debugInterface=_debugInterface;
}
Router2DebugInterface *Router2::GetDebugInterface(void) const
{
	return debugInterface;
}

#endif // _RAKNET_SUPPORT_*
