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
#if _RAKNET_SUPPORT_NatTypeDetectionServer==1

#include "slikenet/NatTypeDetectionServer.h"
#include "slikenet/SocketLayer.h"
#include "slikenet/smartptr.h"
#include "slikenet/SocketIncludes.h"
#include "slikenet/peerinterface.h"
#include "slikenet/MessageIdentifiers.h"
#include "slikenet/GetTime.h"
#include "slikenet/BitStream.h"
#include "slikenet/SocketDefines.h"
#include "slikenet/linux_adapter.h"
#include "slikenet/osx_adapter.h"

// #define NTDS_VERBOSE

using namespace SLNet;

STATIC_FACTORY_DEFINITIONS(NatTypeDetectionServer,NatTypeDetectionServer);

NatTypeDetectionServer::NatTypeDetectionServer()
{
	s1p2=s2p3=s3p4=s4p5=0;
}
NatTypeDetectionServer::~NatTypeDetectionServer()
{
	Shutdown();
}
void NatTypeDetectionServer::Startup(
									 const char *nonRakNetIP2,
									 const char *nonRakNetIP3,
									 const char *nonRakNetIP4
#ifdef __native_client__
									 ,_PP_Instance_ chromeInstance
#endif
									 )
{
	DataStructures::List<RakNetSocket2* > sockets;
	rakPeerInterface->GetSockets(sockets);
	char str[64];
	sockets[0]->GetBoundAddress().ToString(false,str,static_cast<size_t>(64));
	s1p2=
		CreateNonblockingBoundSocket(str,
#ifdef __native_client__
		chromeInstance, 
#endif
		this);

	s2p3=
		CreateNonblockingBoundSocket(nonRakNetIP2,
#ifdef __native_client__
		chromeInstance, 
#endif
		this);


	s3p4=
		CreateNonblockingBoundSocket(nonRakNetIP3,
#ifdef __native_client__
		chromeInstance, 
#endif
		this);

	s4p5=
		CreateNonblockingBoundSocket(nonRakNetIP4,
#ifdef __native_client__
		chromeInstance, 
#endif
		this);

	strcpy_s(s3p4Address, nonRakNetIP3);


	#if !defined(__native_client__) && !defined(WINDOWS_STORE_RT)
	if (s3p4->IsBerkleySocket())
		((RNS2_Berkley*) s3p4)->CreateRecvPollingThread(0);
	#endif
}
void NatTypeDetectionServer::Shutdown()
{
	if (s1p2!=0)
	{
		SLNet::OP_DELETE(s1p2,_FILE_AND_LINE_);
		s1p2=0;
	}
	if (s2p3!=0)
	{
		SLNet::OP_DELETE(s2p3,_FILE_AND_LINE_);
		s2p3=0;
	}
	if (s3p4!=0)
	{
#if !defined(__native_client__) && !defined(WINDOWS_STORE_RT)
		if (s3p4->IsBerkleySocket())
			((RNS2_Berkley *)s3p4)->BlockOnStopRecvPollingThread();
#endif

		SLNet::OP_DELETE(s3p4,_FILE_AND_LINE_);
		s3p4=0;
	}
	if (s4p5!=0)
	{
		SLNet::OP_DELETE(s4p5,_FILE_AND_LINE_);
		s4p5=0;
	}
	bufferedPacketsMutex.Lock();
	while (bufferedPackets.Size())
		SLNet::OP_DELETE(bufferedPackets.Pop(), _FILE_AND_LINE_);
	bufferedPacketsMutex.Unlock();
}
void NatTypeDetectionServer::Update(void)
{
	int i=0;
	SLNet::TimeMS time = SLNet::GetTimeMS();
	SLNet::BitStream bs;
	SystemAddress boundAddress;

	RNS2RecvStruct *recvStruct;
	bufferedPacketsMutex.Lock();
	if (bufferedPackets.Size()>0)
		recvStruct=bufferedPackets.Pop();
	else
		recvStruct=0;
	bufferedPacketsMutex.Unlock();
	while (recvStruct)
	{
		SystemAddress senderAddr = recvStruct->systemAddress;
		char *data = recvStruct->data;
		if (data[0]==NAT_TYPE_PORT_RESTRICTED && recvStruct->socket==s3p4)
		{
			SLNet::BitStream bsIn((unsigned char*) data,recvStruct->bytesRead,false);
			RakNetGUID senderGuid;
			bsIn.IgnoreBytes(sizeof(MessageID));
			bool readSuccess = bsIn.Read(senderGuid);
			RakAssert(readSuccess);
			if (readSuccess)
			{
				unsigned int j = GetDetectionAttemptIndex(senderGuid);
				if (j!=(unsigned int)-1)
				{
					bs.Reset();
					bs.Write((unsigned char) ID_NAT_TYPE_DETECTION_RESULT);
					// If different, then symmetric
					if (senderAddr!=natDetectionAttempts[j].systemAddress)
					{

#ifdef NTDS_VERBOSE
						printf("Determined client is symmetric\n");
#endif
						bs.Write((unsigned char) NAT_TYPE_SYMMETRIC);
					}
					else
					{
						// else port restricted
#ifdef NTDS_VERBOSE

						printf("Determined client is port restricted\n");
#endif
						bs.Write((unsigned char) NAT_TYPE_PORT_RESTRICTED);
					}

					rakPeerInterface->Send(&bs,HIGH_PRIORITY,RELIABLE,0,natDetectionAttempts[j].systemAddress,false);

					// Done
					natDetectionAttempts.RemoveAtIndexFast(j);
				}
				else
				{
					//		RakAssert("j==0 in Update when looking up GUID in NatTypeDetectionServer.cpp. Either a bug or a late resend" && 0);
				}
			}
			else
			{
				//	RakAssert("Didn't read GUID in Update in NatTypeDetectionServer.cpp. Message format error" && 0);
			}
		}

		DeallocRNS2RecvStruct(recvStruct, _FILE_AND_LINE_);
		bufferedPacketsMutex.Lock();
		if (bufferedPackets.Size()>0)
			recvStruct=bufferedPackets.Pop();
		else
			recvStruct=0;
		bufferedPacketsMutex.Unlock();
	}

	/*

	// Only socket that receives messages is s3p4, to see if the external address is different than that of the connection to rakPeerInterface
	char data[ MAXIMUM_MTU_SIZE ];
	int len;
	SystemAddress senderAddr;
	len=NatTypeRecvFrom(data, s3p4, senderAddr);
	// Client is asking us if this is port restricted. Only client requests of this type come in on s3p4
	while (len>0 && data[0]==NAT_TYPE_PORT_RESTRICTED)
	{
		SLNet::BitStream bsIn((unsigned char*) data,len,false);
		RakNetGUID senderGuid;
		bsIn.IgnoreBytes(sizeof(MessageID));
		bool readSuccess = bsIn.Read(senderGuid);
		RakAssert(readSuccess);
		if (readSuccess)
		{
			unsigned int i = GetDetectionAttemptIndex(senderGuid);
			if (i!=(unsigned int)-1)
			{
				bs.Reset();
				bs.Write((unsigned char) ID_NAT_TYPE_DETECTION_RESULT);
				// If different, then symmetric
				if (senderAddr!=natDetectionAttempts[i].systemAddress)
				{

				#ifdef NTDS_VERBOSE
					printf("Determined client is symmetric\n");
				#endif
					bs.Write((unsigned char) NAT_TYPE_SYMMETRIC);
				}
				else
				{
					// else port restricted

					#ifdef NTDS_VERBOSE
					printf("Determined client is port restricted\n");
					#endif
					bs.Write((unsigned char) NAT_TYPE_PORT_RESTRICTED);
				}

				rakPeerInterface->Send(&bs,HIGH_PRIORITY,RELIABLE,0,natDetectionAttempts[i].systemAddress,false);

				// Done
				natDetectionAttempts.RemoveAtIndexFast(i);
			}
			else
			{
		//		RakAssert("i==0 in Update when looking up GUID in NatTypeDetectionServer.cpp. Either a bug or a late resend" && 0);
			}
		}
		else
		{
		//	RakAssert("Didn't read GUID in Update in NatTypeDetectionServer.cpp. Message format error" && 0);
		}

		len=NatTypeRecvFrom(data, s3p4, senderAddr);
	}
	*/


	while (i < (int) natDetectionAttempts.Size())
	{
		if (time > natDetectionAttempts[i].nextStateTime)
		{
			RNS2_SendParameters bsp;
			natDetectionAttempts[i].detectionState=(NATDetectionState)((int)natDetectionAttempts[i].detectionState+1);
			natDetectionAttempts[i].nextStateTime=time+natDetectionAttempts[i].timeBetweenAttempts;
			SystemAddress saOut;
			unsigned char c;
			bs.Reset();
			switch (natDetectionAttempts[i].detectionState)
			{
			case STATE_TESTING_NONE_1:
			case STATE_TESTING_NONE_2:
				c = NAT_TYPE_NONE;

#ifdef NTDS_VERBOSE
				printf("Testing NAT_TYPE_NONE\n");
#endif
				// S4P5 sends to C2. If arrived, no NAT. Done. (Else S4P5 potentially banned, do not use again).
				saOut=natDetectionAttempts[i].systemAddress;
				saOut.SetPortHostOrder(natDetectionAttempts[i].c2Port);
				// SocketLayer::SendTo_PC( s4p5, (const char*) &c, 1, saOut, __FILE__, __LINE__  );
				bsp.data = (char*) &c;
				bsp.length = 1;
				bsp.systemAddress = saOut;
				s4p5->Send(&bsp, _FILE_AND_LINE_);
				break;
			case STATE_TESTING_FULL_CONE_1:
			case STATE_TESTING_FULL_CONE_2:

#ifdef NTDS_VERBOSE
				printf("Testing NAT_TYPE_FULL_CONE\n");
#endif
				rakPeerInterface->WriteOutOfBandHeader(&bs);
				bs.Write((unsigned char) ID_NAT_TYPE_DETECT);
				bs.Write((unsigned char) NAT_TYPE_FULL_CONE);
				// S2P3 sends to C1 (Different address, different port, to previously used port on client). If received, Full-cone nat. Done.  (Else S2P3 potentially banned, do not use again).
				saOut=natDetectionAttempts[i].systemAddress;
				saOut.SetPortHostOrder(natDetectionAttempts[i].systemAddress.GetPort());
				// SocketLayer::SendTo_PC( s2p3, (const char*) bs.GetData(), bs.GetNumberOfBytesUsed(), saOut, __FILE__, __LINE__  );
				bsp.data = (char*) bs.GetData();
				bsp.length = bs.GetNumberOfBytesUsed();
				bsp.systemAddress = saOut;
				s2p3->Send(&bsp, _FILE_AND_LINE_);
				break;
			case STATE_TESTING_ADDRESS_RESTRICTED_1:
			case STATE_TESTING_ADDRESS_RESTRICTED_2:

#ifdef NTDS_VERBOSE
				printf("Testing NAT_TYPE_ADDRESS_RESTRICTED\n");
#endif
				rakPeerInterface->WriteOutOfBandHeader(&bs);
				bs.Write((unsigned char) ID_NAT_TYPE_DETECT);
				bs.Write((unsigned char) NAT_TYPE_ADDRESS_RESTRICTED);
				// S1P2 sends to C1 (Same address, different port, to previously used port on client). If received, address-restricted cone nat. Done.
				saOut=natDetectionAttempts[i].systemAddress;
				saOut.SetPortHostOrder(natDetectionAttempts[i].systemAddress.GetPort());
				//SocketLayer::SendTo_PC( s1p2, (const char*) bs.GetData(), bs.GetNumberOfBytesUsed(), saOut, __FILE__, __LINE__  );
				bsp.data = (char*) bs.GetData();
				bsp.length = bs.GetNumberOfBytesUsed();
				bsp.systemAddress = saOut;
				s1p2->Send(&bsp, _FILE_AND_LINE_);
				break;
			case STATE_TESTING_PORT_RESTRICTED_1:
			case STATE_TESTING_PORT_RESTRICTED_2:
				// C1 sends to S3P4. If address of C1 as seen by S3P4 is the same as the address of C1 as seen by S1P1, then port-restricted cone nat. Done

#ifdef NTDS_VERBOSE
				printf("Testing NAT_TYPE_PORT_RESTRICTED\n");
#endif
				bs.Write((unsigned char) ID_NAT_TYPE_DETECTION_REQUEST);
				bs.Write(RakString::NonVariadic(s3p4Address));
				bs.Write(s3p4->GetBoundAddress().GetPort());
				rakPeerInterface->Send(&bs,HIGH_PRIORITY,RELIABLE,0,natDetectionAttempts[i].systemAddress,false);
				break;
			default:

#ifdef NTDS_VERBOSE
				printf("Warning, exceeded final check STATE_TESTING_PORT_RESTRICTED_2.\nExpected that client would have sent NAT_TYPE_PORT_RESTRICTED on s3p4.\nDefaulting to Symmetric\n");
#endif
				bs.Write((unsigned char) ID_NAT_TYPE_DETECTION_RESULT);
				bs.Write((unsigned char) NAT_TYPE_SYMMETRIC);
				rakPeerInterface->Send(&bs,HIGH_PRIORITY,RELIABLE,0,natDetectionAttempts[i].systemAddress,false);
				natDetectionAttempts.RemoveAtIndexFast(i);
				i--;
				break;
			}

		}
		i++;
	}
}
PluginReceiveResult NatTypeDetectionServer::OnReceive(Packet *packet)
{
	switch (packet->data[0])
	{
	case ID_NAT_TYPE_DETECTION_REQUEST:
		OnDetectionRequest(packet);
		return RR_STOP_PROCESSING_AND_DEALLOCATE;
	}
	return RR_CONTINUE_PROCESSING;
}
void NatTypeDetectionServer::OnClosedConnection(const SystemAddress &systemAddress, RakNetGUID rakNetGUID, PI2_LostConnectionReason lostConnectionReason )
{
	(void) lostConnectionReason;
	(void) rakNetGUID;

	unsigned int i = GetDetectionAttemptIndex(systemAddress);
	if (i==(unsigned int)-1)
		return;
	natDetectionAttempts.RemoveAtIndexFast(i);
}
void NatTypeDetectionServer::OnDetectionRequest(Packet *packet)
{
	unsigned int i = GetDetectionAttemptIndex(packet->systemAddress);

	SLNet::BitStream bsIn(packet->data, packet->length, false);
	bsIn.IgnoreBytes(1);
	bool isRequest=false;
	bsIn.Read(isRequest);
	if (isRequest)
	{
		if (i!=(unsigned int)-1)
			return; // Already in progress

		NATDetectionAttempt nda;
		nda.detectionState=STATE_NONE;
		nda.systemAddress=packet->systemAddress;
		nda.guid=packet->guid;
		bsIn.Read(nda.c2Port);
		nda.nextStateTime=0;
		nda.timeBetweenAttempts=rakPeerInterface->GetLastPing(nda.systemAddress)*3+50;
		natDetectionAttempts.Push(nda, _FILE_AND_LINE_);
	}
	else
	{
		if (i==(unsigned int)-1)
			return; // Unknown
		// They are done
		natDetectionAttempts.RemoveAtIndexFast(i);
	}

}
unsigned int NatTypeDetectionServer::GetDetectionAttemptIndex(const SystemAddress &sa)
{
	for (unsigned int i=0; i < natDetectionAttempts.Size(); i++)
	{
		if (natDetectionAttempts[i].systemAddress==sa)
			return i;
	}
	return (unsigned int) -1;
}
unsigned int NatTypeDetectionServer::GetDetectionAttemptIndex(RakNetGUID guid)
{
	for (unsigned int i=0; i < natDetectionAttempts.Size(); i++)
	{
		if (natDetectionAttempts[i].guid==guid)
			return i;
	}
	return (unsigned int) -1;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void NatTypeDetectionServer::DeallocRNS2RecvStruct(RNS2RecvStruct *s, const char *file, unsigned int line)
{
	SLNet::OP_DELETE(s, file, line);
}
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
RNS2RecvStruct *NatTypeDetectionServer::AllocRNS2RecvStruct(const char *file, unsigned int line)
{
	return SLNet::OP_NEW<RNS2RecvStruct>(file,line);
}

void NatTypeDetectionServer::OnRNS2Recv(RNS2RecvStruct *recvStruct)
{
	bufferedPacketsMutex.Lock();
	bufferedPackets.Push(recvStruct,_FILE_AND_LINE_);
	bufferedPacketsMutex.Unlock();
}

#endif // _RAKNET_SUPPORT_*
