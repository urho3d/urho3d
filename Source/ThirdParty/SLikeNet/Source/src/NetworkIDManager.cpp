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

/// \file
///


#include "slikenet/NetworkIDManager.h"
#include "slikenet/NetworkIDObject.h"
#include "slikenet/assert.h"
#include "slikenet/GetTime.h"
#include "slikenet/sleep.h"
#include "slikenet/SuperFastHash.h"
#include "slikenet/peerinterface.h"

using namespace SLNet;

STATIC_FACTORY_DEFINITIONS(NetworkIDManager,NetworkIDManager)

NetworkIDManager::NetworkIDManager()
{
	startingOffset = RakPeerInterface::Get64BitUniqueRandomNumber();
	Clear();
}
NetworkIDManager::~NetworkIDManager(void)
{

}
void NetworkIDManager::Clear(void)
{
	memset(networkIdHash,0,sizeof(networkIdHash));
}
NetworkIDObject *NetworkIDManager::GET_BASE_OBJECT_FROM_ID(NetworkID x)
{
	unsigned int hashIndex=NetworkIDToHashIndex(x);
	NetworkIDObject *nio=networkIdHash[hashIndex];
	while (nio)
	{
		if (nio->GetNetworkID()==x)
			return nio;
		nio=nio->nextInstanceForNetworkIDManager;
	}
	return 0;
}
NetworkID NetworkIDManager::GetNewNetworkID(void)
{
    while (GET_BASE_OBJECT_FROM_ID(++startingOffset))
        ;
	if (startingOffset==UNASSIGNED_NETWORK_ID)
	{
		while (GET_BASE_OBJECT_FROM_ID(++startingOffset))
			;
	}
    return startingOffset;
}
unsigned int NetworkIDManager::NetworkIDToHashIndex(NetworkID networkId)
{
//	return SuperFastHash((const char*) &networkId.guid.g,sizeof(networkId.guid.g)) % NETWORK_ID_MANAGER_HASH_LENGTH;
	return (unsigned int) (networkId % NETWORK_ID_MANAGER_HASH_LENGTH);
}
void NetworkIDManager::TrackNetworkIDObject(NetworkIDObject *networkIdObject)
{
	RakAssert(networkIdObject->GetNetworkIDManager()==this);
	NetworkID rawId = networkIdObject->GetNetworkID();
	RakAssert(rawId!=UNASSIGNED_NETWORK_ID);

	networkIdObject->nextInstanceForNetworkIDManager=0;

	unsigned int hashIndex=NetworkIDToHashIndex(rawId);
//	printf("TrackNetworkIDObject hashIndex=%i guid=%s\n",hashIndex, networkIdObject->GetNetworkID().guid.ToString()); // removeme
	if (networkIdHash[hashIndex]==0)
	{
		networkIdHash[hashIndex]=networkIdObject;
		return;
	}
	NetworkIDObject *nio=networkIdHash[hashIndex];
	// Duplicate insertion?
	RakAssert(nio!=networkIdObject);
	// Random GUID conflict?
	RakAssert(nio->GetNetworkID()!=rawId);

	while (nio->nextInstanceForNetworkIDManager!=0)
	{		
		nio=nio->nextInstanceForNetworkIDManager;

		// Duplicate insertion?
		RakAssert(nio!=networkIdObject);
		// Random GUID conflict?
		RakAssert(nio->GetNetworkID()!=rawId);
	}

	nio->nextInstanceForNetworkIDManager=networkIdObject;
}
void NetworkIDManager::StopTrackingNetworkIDObject(NetworkIDObject *networkIdObject)
{
	RakAssert(networkIdObject->GetNetworkIDManager()==this);
	NetworkID rawId = networkIdObject->GetNetworkID();
	RakAssert(rawId!=UNASSIGNED_NETWORK_ID);

	// RakAssert(networkIdObject->GetNetworkID()!=UNASSIGNED_NETWORK_ID);
	unsigned int hashIndex=NetworkIDToHashIndex(rawId);
//	printf("hashIndex=%i\n",hashIndex); // removeme
	NetworkIDObject *nio=networkIdHash[hashIndex];
	if (nio==0)
	{
		RakAssert("NetworkIDManager::StopTrackingNetworkIDObject didn't find object" && 0);
		return;
	}
	if (nio==networkIdObject)
	{
		networkIdHash[hashIndex]=nio->nextInstanceForNetworkIDManager;
		return;
	}

	while (nio)
	{
		if (nio->nextInstanceForNetworkIDManager==networkIdObject)
		{
			nio->nextInstanceForNetworkIDManager=networkIdObject->nextInstanceForNetworkIDManager;
			return;
		}
		nio=nio->nextInstanceForNetworkIDManager;
	}

	RakAssert("NetworkIDManager::StopTrackingNetworkIDObject didn't find object" && 0);
}
