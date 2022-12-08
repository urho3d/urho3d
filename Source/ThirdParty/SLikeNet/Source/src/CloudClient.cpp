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

#include "slikenet/NativeFeatureIncludes.h"
#if _RAKNET_SUPPORT_CloudClient==1

#include "slikenet/CloudClient.h"
#include "slikenet/GetTime.h"
#include "slikenet/MessageIdentifiers.h"
#include "slikenet/BitStream.h"
#include "slikenet/peerinterface.h"

using namespace SLNet;

STATIC_FACTORY_DEFINITIONS(CloudClient,CloudClient);

CloudClient::CloudClient()
{
	callback=0;
	allocator=&unsetDefaultAllocator;
}
CloudClient::~CloudClient()
{
}
void CloudClient::SetDefaultCallbacks(CloudAllocator *_allocator, CloudClientCallback *_callback)
{
	callback=_callback;
	allocator=_allocator;
}
void CloudClient::Post(CloudKey *cloudKey, const unsigned char *data, uint32_t dataLengthBytes, RakNetGUID systemIdentifier)
{
	RakAssert(cloudKey);
	
	SLNet::BitStream bsOut;
	bsOut.Write((MessageID)ID_CLOUD_POST_REQUEST);
	cloudKey->Serialize(true,&bsOut);
	if (data==0)
		dataLengthBytes=0;
	bsOut.Write(dataLengthBytes);
	if (dataLengthBytes>0)
		bsOut.WriteAlignedBytes((const unsigned char*) data, dataLengthBytes);
	SendUnified(&bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, systemIdentifier, false);
}
void CloudClient::Release(DataStructures::List<CloudKey> &keys, RakNetGUID systemIdentifier)
{
	SLNet::BitStream bsOut;
	bsOut.Write((MessageID)ID_CLOUD_RELEASE_REQUEST);
	RakAssert(keys.Size() < (uint16_t)-1 );
	bsOut.WriteCasted<uint16_t>(keys.Size());
	for (uint16_t i=0; i < keys.Size(); i++)	
	{
		keys[i].Serialize(true,&bsOut);
	}
	SendUnified(&bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, systemIdentifier, false);
}
bool CloudClient::Get(CloudQuery *keyQuery, RakNetGUID systemIdentifier)
{
	SLNet::BitStream bsOut;
	bsOut.Write((MessageID)ID_CLOUD_GET_REQUEST);
	keyQuery->Serialize(true, &bsOut);
	bsOut.WriteCasted<uint16_t>(0); // Specific systems
	SendUnified(&bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, systemIdentifier, false);
	return true;
}
bool CloudClient::Get(CloudQuery *keyQuery, DataStructures::List<RakNetGUID> &specificSystems, RakNetGUID systemIdentifier)
{
	SLNet::BitStream bsOut;
	bsOut.Write((MessageID)ID_CLOUD_GET_REQUEST);
	keyQuery->Serialize(true, &bsOut);
	bsOut.WriteCasted<uint16_t>(specificSystems.Size());
	RakAssert(specificSystems.Size() < (uint16_t)-1 );
	for (uint16_t i=0; i < specificSystems.Size(); i++)
	{
		bsOut.Write(specificSystems[i]);
	}
	SendUnified(&bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, systemIdentifier, false);
	return true;
}
bool CloudClient::Get(CloudQuery *keyQuery, DataStructures::List<CloudQueryRow*> &specificSystems, RakNetGUID systemIdentifier)
{
	SLNet::BitStream bsOut;
	bsOut.Write((MessageID)ID_CLOUD_GET_REQUEST);
	keyQuery->Serialize(true, &bsOut);
	bsOut.WriteCasted<uint16_t>(specificSystems.Size());
	RakAssert(specificSystems.Size() < (uint16_t)-1 );
	for (uint16_t i=0; i < specificSystems.Size(); i++)
	{
		if (specificSystems[i]->clientGUID!=UNASSIGNED_RAKNET_GUID)
		{
			bsOut.Write(true);
			bsOut.Write(specificSystems[i]->clientGUID);
		}
		else
		{
			bsOut.Write(false);
			bsOut.Write(specificSystems[i]->clientSystemAddress);
		}
	}
	SendUnified(&bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, systemIdentifier, false);
	return true;
}
void CloudClient::Unsubscribe(DataStructures::List<CloudKey> &keys, RakNetGUID systemIdentifier)
{
	SLNet::BitStream bsOut;
	bsOut.Write((MessageID)ID_CLOUD_UNSUBSCRIBE_REQUEST);
	RakAssert(keys.Size() < (uint16_t)-1 );
	bsOut.WriteCasted<uint16_t>(keys.Size());
	for (uint16_t i=0; i < keys.Size(); i++)	
	{
		keys[i].Serialize(true,&bsOut);
	}
	bsOut.WriteCasted<uint16_t>(0);
	SendUnified(&bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, systemIdentifier, false);
}
void CloudClient::Unsubscribe(DataStructures::List<CloudKey> &keys, DataStructures::List<RakNetGUID> &specificSystems, RakNetGUID systemIdentifier)
{
	SLNet::BitStream bsOut;
	bsOut.Write((MessageID)ID_CLOUD_UNSUBSCRIBE_REQUEST);
	RakAssert(keys.Size() < (uint16_t)-1 );
	bsOut.WriteCasted<uint16_t>(keys.Size());
	for (uint16_t i=0; i < keys.Size(); i++)	
	{
		keys[i].Serialize(true,&bsOut);
	}
	bsOut.WriteCasted<uint16_t>(specificSystems.Size());
	RakAssert(specificSystems.Size() < (uint16_t)-1 );
	for (uint16_t i=0; i < specificSystems.Size(); i++)
	{
		bsOut.Write(specificSystems[i]);
	}
	SendUnified(&bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, systemIdentifier, false);
}
void CloudClient::Unsubscribe(DataStructures::List<CloudKey> &keys, DataStructures::List<CloudQueryRow*> &specificSystems, RakNetGUID systemIdentifier)
{
	SLNet::BitStream bsOut;
	bsOut.Write((MessageID)ID_CLOUD_UNSUBSCRIBE_REQUEST);
	RakAssert(keys.Size() < (uint16_t)-1 );
	bsOut.WriteCasted<uint16_t>(keys.Size());
	for (uint16_t i=0; i < keys.Size(); i++)	
	{
		keys[i].Serialize(true,&bsOut);
	}
	bsOut.WriteCasted<uint16_t>(specificSystems.Size());
	RakAssert(specificSystems.Size() < (uint16_t)-1 );
	for (uint16_t i=0; i < specificSystems.Size(); i++)
	{
		if (specificSystems[i]->clientGUID!=UNASSIGNED_RAKNET_GUID)
		{
			bsOut.Write(true);
			bsOut.Write(specificSystems[i]->clientGUID);
		}
		else
		{
			bsOut.Write(false);
			bsOut.Write(specificSystems[i]->clientSystemAddress);
		}
	}
	SendUnified(&bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, systemIdentifier, false);
}
PluginReceiveResult CloudClient::OnReceive(Packet *packet)
{
	(void) packet;

	return RR_CONTINUE_PROCESSING;
}
void CloudClient::OnGetReponse(Packet *packet, CloudClientCallback *_callback, CloudAllocator *_allocator)
{
	if (_callback==0)
		_callback=callback;
	if (_allocator==0)
		_allocator=allocator;

	CloudQueryResult cloudQueryResult;

	SLNet::BitStream bsIn(packet->data, packet->length, false);
	bsIn.IgnoreBytes(sizeof(MessageID));
	cloudQueryResult.Serialize(false,&bsIn,_allocator);
	bool deallocateRowsAfterReturn=true;
	_callback->OnGet(&cloudQueryResult, &deallocateRowsAfterReturn);
	if (deallocateRowsAfterReturn)
	{
		unsigned int i;
		for (i=0; i < cloudQueryResult.rowsReturned.Size(); i++)
		{
			_allocator->DeallocateRowData(cloudQueryResult.rowsReturned[i]->data);
			_allocator->DeallocateCloudQueryRow(cloudQueryResult.rowsReturned[i]);
		}
	}
}
void CloudClient::OnGetReponse(CloudQueryResult *cloudQueryResult, Packet *packet, CloudAllocator *_allocator)
{
	if (_allocator==0)
		_allocator=allocator;

	SLNet::BitStream bsIn(packet->data, packet->length, false);
	bsIn.IgnoreBytes(sizeof(MessageID));
	cloudQueryResult->Serialize(false,&bsIn,_allocator);
}
void CloudClient::OnSubscriptionNotification(Packet *packet, CloudClientCallback *_callback, CloudAllocator *_allocator)
{
	if (_callback==0)
		_callback=callback;
	if (_allocator==0)
		_allocator=allocator;

	bool wasUpdated=false;
	CloudQueryRow row;

	SLNet::BitStream bsIn(packet->data, packet->length, false);
	bsIn.IgnoreBytes(sizeof(MessageID));
	bsIn.Read(wasUpdated);
	row.Serialize(false,&bsIn,_allocator);
	bool deallocateRowAfterReturn=true;
	_callback->OnSubscriptionNotification(&row, wasUpdated, &deallocateRowAfterReturn);
	if (deallocateRowAfterReturn)
	{
		_allocator->DeallocateRowData(row.data);
	}
}
void CloudClient::OnSubscriptionNotification(bool *wasUpdated, CloudQueryRow *row, Packet *packet, CloudAllocator *_allocator)
{
	if (_allocator==0)
		_allocator=allocator;

	SLNet::BitStream bsIn(packet->data, packet->length, false);
	bsIn.IgnoreBytes(sizeof(MessageID));
	bool b=false;
	bsIn.Read(b);
	*wasUpdated=b;
	row->Serialize(false,&bsIn,_allocator);
}
void CloudClient::DeallocateWithDefaultAllocator(CloudQueryResult *cloudQueryResult)
{
	unsigned int i;
	for (i=0; i < cloudQueryResult->rowsReturned.Size(); i++)
	{
		allocator->DeallocateRowData(cloudQueryResult->rowsReturned[i]->data);
		allocator->DeallocateCloudQueryRow(cloudQueryResult->rowsReturned[i]);
	}

	cloudQueryResult->rowsReturned.Clear(false, _FILE_AND_LINE_);
	cloudQueryResult->resultKeyIndices.Clear(false, _FILE_AND_LINE_);
	cloudQueryResult->cloudQuery.keys.Clear(false, _FILE_AND_LINE_);
}
void CloudClient::DeallocateWithDefaultAllocator(CloudQueryRow *row)
{
	allocator->DeallocateRowData(row->data);
}
#endif
