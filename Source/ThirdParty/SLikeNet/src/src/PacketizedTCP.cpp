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
#if _RAKNET_SUPPORT_PacketizedTCP==1 && _RAKNET_SUPPORT_TCPInterface==1

#include "slikenet/PacketizedTCP.h"
#include "slikenet/NativeTypes.h"
#include "slikenet/BitStream.h"
#include "slikenet/MessageIdentifiers.h"
#include "slikenet/alloca.h"

using namespace SLNet;

typedef uint32_t PTCPHeader;

STATIC_FACTORY_DEFINITIONS(PacketizedTCP,PacketizedTCP);

PacketizedTCP::PacketizedTCP()
{

}
PacketizedTCP::~PacketizedTCP()
{
	ClearAllConnections();
}

void PacketizedTCP::Stop(void)
{
	unsigned int i;
	TCPInterface::Stop();
	for (i=0; i < waitingPackets.Size(); i++)
		DeallocatePacket(waitingPackets[i]);
	ClearAllConnections();
}

void PacketizedTCP::Send( const char *data, unsigned length, const SystemAddress &systemAddress, bool broadcast )
{
	PTCPHeader dataLength;
	dataLength=length;
#ifndef __BITSTREAM_NATIVE_END
	if (SLNet::BitStream::DoEndianSwap())
		SLNet::BitStream::ReverseBytes((unsigned char*) &length,(unsigned char*) &dataLength,sizeof(dataLength));
#else
		dataLength=length;
#endif

	unsigned int lengthsArray[2];
	const char *dataArray[2];
	dataArray[0]=(char*) &dataLength;
	dataArray[1]=data;
	lengthsArray[0]=sizeof(dataLength);
	lengthsArray[1]=length;
	TCPInterface::SendList(dataArray,lengthsArray,2,systemAddress,broadcast);
}
bool PacketizedTCP::SendList( const char **data, const unsigned int *lengths, const int numParameters, const SystemAddress &systemAddress, bool broadcast )
{
	if (isStarted.GetValue()==0)
		return false;
	if (data==0)
		return false;
	if (systemAddress==UNASSIGNED_SYSTEM_ADDRESS && broadcast==false)
		return false;
	PTCPHeader totalLengthOfUserData=0;
	int i;
	for (i=0; i < numParameters; i++)
	{
		if (lengths[i]>0)
			totalLengthOfUserData+=lengths[i];
	}
	if (totalLengthOfUserData==0)
		return false;

	PTCPHeader dataLength;
#ifndef __BITSTREAM_NATIVE_END
	if (SLNet::BitStream::DoEndianSwap())
		SLNet::BitStream::ReverseBytes((unsigned char*) &totalLengthOfUserData,(unsigned char*) &dataLength,sizeof(dataLength));
#else
	dataLength=totalLengthOfUserData;
#endif
	

	unsigned int lengthsArray[513];
	const char *dataArray[513];
	dataArray[0]=(char*) &dataLength;
	lengthsArray[0]=sizeof(dataLength);
	for (i=0; i < 512 && i < numParameters; i++)
	{
		dataArray[i+1]=data[i];
		lengthsArray[i+1]=lengths[i];
	}	
	return TCPInterface::SendList(dataArray,lengthsArray,numParameters+1,systemAddress,broadcast);
}
void PacketizedTCP::PushNotificationsToQueues(void)
{
	SystemAddress sa;
	sa = TCPInterface::HasNewIncomingConnection();
	if (sa!=UNASSIGNED_SYSTEM_ADDRESS)
	{
		_newIncomingConnections.Push(sa, _FILE_AND_LINE_ );
		AddToConnectionList(sa);
	}

	sa = TCPInterface::HasFailedConnectionAttempt();
	if (sa!=UNASSIGNED_SYSTEM_ADDRESS)
	{
		_failedConnectionAttempts.Push(sa, _FILE_AND_LINE_ );
	}

	sa = TCPInterface::HasLostConnection();
	if (sa!=UNASSIGNED_SYSTEM_ADDRESS)
	{
		_lostConnections.Push(sa, _FILE_AND_LINE_ );
		RemoveFromConnectionList(sa);
	}

	sa = TCPInterface::HasCompletedConnectionAttempt();
	if (sa!=UNASSIGNED_SYSTEM_ADDRESS)
	{
		_completedConnectionAttempts.Push(sa, _FILE_AND_LINE_ );
		AddToConnectionList(sa);
	}
}
Packet* PacketizedTCP::Receive( void )
{
	PushNotificationsToQueues();

	unsigned int i;
	for (i=0; i < messageHandlerList.Size(); i++)
		messageHandlerList[i]->Update();

	Packet *outgoingPacket=ReturnOutgoingPacket();
	if (outgoingPacket)
		return outgoingPacket;

	Packet *incomingPacket;
	incomingPacket = TCPInterface::ReceiveInt();
	unsigned int index;

	while (incomingPacket)
	{
		if (connections.Has(incomingPacket->systemAddress))
			index = connections.GetIndexAtKey(incomingPacket->systemAddress);
		else
			index=(unsigned int) -1;
		if ((unsigned int)index==(unsigned int)-1)
		{
			DeallocatePacket(incomingPacket);
			incomingPacket = TCPInterface::ReceiveInt();
			continue;
		}


		if (incomingPacket->deleteData==true)
		{
			// Came from network
			SystemAddress systemAddressFromPacket;
			if (index < connections.Size())
			{
				DataStructures::ByteQueue *bq = connections[index];
				// Buffer data
				bq->WriteBytes((const char*) incomingPacket->data,incomingPacket->length, _FILE_AND_LINE_);
				systemAddressFromPacket=incomingPacket->systemAddress;
				PTCPHeader dataLength;

				// Peek the header to see if a full message is waiting
				bq->ReadBytes((char*) &dataLength,sizeof(PTCPHeader),true);
				if (SLNet::BitStream::DoEndianSwap())
					SLNet::BitStream::ReverseBytesInPlace((unsigned char*) &dataLength,sizeof(dataLength));
				// Header indicates packet length. If enough data is available, read out and return one packet
				if (bq->GetBytesWritten()>=dataLength+sizeof(PTCPHeader))
				{
					do 
					{
						bq->IncrementReadOffset(sizeof(PTCPHeader));
						outgoingPacket = SLNet::OP_NEW<Packet>(_FILE_AND_LINE_);
						outgoingPacket->length=dataLength;
						outgoingPacket->bitSize=BYTES_TO_BITS(dataLength);
						outgoingPacket->guid=UNASSIGNED_RAKNET_GUID;
						outgoingPacket->systemAddress=systemAddressFromPacket;
						outgoingPacket->deleteData=false; // Did not come from the network
						outgoingPacket->data=(unsigned char*) rakMalloc_Ex(dataLength, _FILE_AND_LINE_);
						if (outgoingPacket->data==0)
						{
							notifyOutOfMemory(_FILE_AND_LINE_);
							SLNet::OP_DELETE(outgoingPacket,_FILE_AND_LINE_);
							return 0;
						}
						bq->ReadBytes((char*) outgoingPacket->data,dataLength,false);

						waitingPackets.Push(outgoingPacket, _FILE_AND_LINE_ );

						// Peek the header to see if a full message is waiting
						if (bq->ReadBytes((char*) &dataLength,sizeof(PTCPHeader),true))
						{
							if (SLNet::BitStream::DoEndianSwap())
								SLNet::BitStream::ReverseBytesInPlace((unsigned char*) &dataLength,sizeof(dataLength));
						}
						else
							break;
					} while (bq->GetBytesWritten()>=dataLength+sizeof(PTCPHeader));
				}
				else
				{

					unsigned int oldWritten = bq->GetBytesWritten()-incomingPacket->length;
					unsigned int newWritten = bq->GetBytesWritten();

					// Return ID_DOWNLOAD_PROGRESS
					if (newWritten/65536!=oldWritten/65536)
					{
						outgoingPacket = SLNet::OP_NEW<Packet>(_FILE_AND_LINE_);
						outgoingPacket->length=sizeof(MessageID) +
							sizeof(unsigned int)*2 +
							sizeof(unsigned int) +
							65536;
						outgoingPacket->bitSize=BYTES_TO_BITS(incomingPacket->length);
						outgoingPacket->guid=UNASSIGNED_RAKNET_GUID;
						outgoingPacket->systemAddress=incomingPacket->systemAddress;
						outgoingPacket->deleteData=false;
						outgoingPacket->data=(unsigned char*) rakMalloc_Ex(outgoingPacket->length, _FILE_AND_LINE_);
						if (outgoingPacket->data==0)
						{
							notifyOutOfMemory(_FILE_AND_LINE_);
							SLNet::OP_DELETE(outgoingPacket,_FILE_AND_LINE_);
							return 0;
						}

						outgoingPacket->data[0]=(MessageID)ID_DOWNLOAD_PROGRESS;
						unsigned int totalParts=dataLength/65536;
						unsigned int partIndex=newWritten/65536;
						unsigned int oneChunkSize=65536;
						memcpy(outgoingPacket->data+sizeof(MessageID), &partIndex, sizeof(unsigned int));
						memcpy(outgoingPacket->data+sizeof(MessageID)+sizeof(unsigned int)*1, &totalParts, sizeof(unsigned int));
						memcpy(outgoingPacket->data+sizeof(MessageID)+sizeof(unsigned int)*2, &oneChunkSize, sizeof(unsigned int));
						bq->IncrementReadOffset(sizeof(PTCPHeader));
						bq->ReadBytes((char*) outgoingPacket->data+sizeof(MessageID)+sizeof(unsigned int)*3,oneChunkSize,true);
						bq->DecrementReadOffset(sizeof(PTCPHeader));

						waitingPackets.Push(outgoingPacket, _FILE_AND_LINE_ );
					}
				}

			}

			DeallocatePacket(incomingPacket);
			incomingPacket=0;
		}
		else
			waitingPackets.Push(incomingPacket, _FILE_AND_LINE_ );

		incomingPacket = TCPInterface::ReceiveInt();
	}

	return ReturnOutgoingPacket();
}
Packet *PacketizedTCP::ReturnOutgoingPacket(void)
{
	Packet *outgoingPacket=0;
	unsigned int i;
	while (outgoingPacket==0 && waitingPackets.IsEmpty()==false)
	{
		outgoingPacket=waitingPackets.Pop();
		PluginReceiveResult pluginResult;
		for (i=0; i < messageHandlerList.Size(); i++)
		{
			pluginResult=messageHandlerList[i]->OnReceive(outgoingPacket);
			if (pluginResult==RR_STOP_PROCESSING_AND_DEALLOCATE)
			{
				DeallocatePacket( outgoingPacket );
				outgoingPacket=0; // Will do the loop again and get another packet
				break; // break out of the enclosing for
			}
			else if (pluginResult==RR_STOP_PROCESSING)
			{
				outgoingPacket=0;
				break;
			}
		}
	}

	return outgoingPacket;
}
void PacketizedTCP::CloseConnection( SystemAddress systemAddress )
{
	RemoveFromConnectionList(systemAddress);
	TCPInterface::CloseConnection(systemAddress);
}
void PacketizedTCP::RemoveFromConnectionList(const SystemAddress &sa)
{
	if (sa==UNASSIGNED_SYSTEM_ADDRESS)
		return;
	if (connections.Has(sa))
	{
		unsigned int index = connections.GetIndexAtKey(sa);
		if (index!=(unsigned int)-1)
		{
			SLNet::OP_DELETE(connections[index],_FILE_AND_LINE_);
			connections.RemoveAtIndex(index);
		}
	}
}
void PacketizedTCP::AddToConnectionList(const SystemAddress &sa)
{
	if (sa==UNASSIGNED_SYSTEM_ADDRESS)
		return;
	connections.SetNew(sa, SLNet::OP_NEW<DataStructures::ByteQueue>(_FILE_AND_LINE_));
}
void PacketizedTCP::ClearAllConnections(void)
{
	unsigned int i;
	for (i=0; i < connections.Size(); i++)
		SLNet::OP_DELETE(connections[i],_FILE_AND_LINE_);
	connections.Clear();
}
SystemAddress PacketizedTCP::HasCompletedConnectionAttempt(void)
{
	PushNotificationsToQueues();

	if (_completedConnectionAttempts.IsEmpty()==false)
		return _completedConnectionAttempts.Pop();
	return UNASSIGNED_SYSTEM_ADDRESS;
}
SystemAddress PacketizedTCP::HasFailedConnectionAttempt(void)
{
	PushNotificationsToQueues();

	if (_failedConnectionAttempts.IsEmpty()==false)
		return _failedConnectionAttempts.Pop();
	return UNASSIGNED_SYSTEM_ADDRESS;
}
SystemAddress PacketizedTCP::HasNewIncomingConnection(void)
{
	PushNotificationsToQueues();

	if (_newIncomingConnections.IsEmpty()==false)
		return _newIncomingConnections.Pop();
	return UNASSIGNED_SYSTEM_ADDRESS;
}
SystemAddress PacketizedTCP::HasLostConnection(void)
{
	PushNotificationsToQueues();

	if (_lostConnections.IsEmpty()==false)
		return _lostConnections.Pop();
	return UNASSIGNED_SYSTEM_ADDRESS;
}

#endif // _RAKNET_SUPPORT_*
