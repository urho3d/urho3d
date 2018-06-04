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
#if _RAKNET_SUPPORT_ReplicaManager3==1

#include "slikenet/ReplicaManager3.h"
#include "slikenet/GetTime.h"
#include "slikenet/MessageIdentifiers.h"
#include "slikenet/peerinterface.h"
#include "slikenet/NetworkIDManager.h"

using namespace SLNet;

// DEFINE_MULTILIST_PTR_TO_MEMBER_COMPARISONS(LastSerializationResult,Replica3*,replica);

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

bool PRO::operator==( const PRO& right ) const
{
	return priority == right.priority && reliability == right.reliability && orderingChannel == right.orderingChannel && sendReceipt == right.sendReceipt;
}

bool PRO::operator!=( const PRO& right ) const
{
	return priority != right.priority || reliability != right.reliability || orderingChannel != right.orderingChannel || sendReceipt != right.sendReceipt;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int Connection_RM3::Replica3LSRComp( Replica3 * const &replica3, LastSerializationResult * const &data )
{
	/*
	if (replica3->GetNetworkID() < data->replica->GetNetworkID())
		return -1;
	if (replica3->GetNetworkID() > data->replica->GetNetworkID())
		return 1;
		*/

	// 7/28/2013 - If GetNetworkID chagned during runtime, the list would be out of order and lookup would always fail or go out of bounds
	// I remember before that I could not directly compare 
	if (replica3->referenceIndex < data->replica->referenceIndex)
		return -1;
	if (replica3->referenceIndex > data->replica->referenceIndex)
		return 1;
	return 0;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

LastSerializationResult::LastSerializationResult()
{
	replica=0;
	lastSerializationResultBS=0;
	whenLastSerialized = SLNet::GetTime();
}
LastSerializationResult::~LastSerializationResult()
{
	if (lastSerializationResultBS)
		SLNet::OP_DELETE(lastSerializationResultBS,_FILE_AND_LINE_);
}
void LastSerializationResult::AllocBS(void)
{
	if (lastSerializationResultBS==0)
	{
		lastSerializationResultBS= SLNet::OP_NEW<LastSerializationResultBS>(_FILE_AND_LINE_);
	}
}
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

ReplicaManager3::ReplicaManager3()
{
	defaultSendParameters.orderingChannel=0;
	defaultSendParameters.priority=HIGH_PRIORITY;
	defaultSendParameters.reliability=RELIABLE_ORDERED;
	defaultSendParameters.sendReceipt=0;
	autoSerializeInterval=30;
	lastAutoSerializeOccurance=0;
	autoCreateConnections=true;
	autoDestroyConnections=true;
	currentlyDeallocatingReplica=0;

	for (unsigned int i=0; i < 255; i++)
		worldsArray[i]=0;

	AddWorld(0);
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

ReplicaManager3::~ReplicaManager3()
{
	if (autoDestroyConnections)
	{
		for (unsigned int i=0; i < worldsList.Size(); i++)
		{
			RakAssert(worldsList[i]->connectionList.Size()==0);
		}
	}
	Clear(true);
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void ReplicaManager3::SetAutoManageConnections(bool autoCreate, bool autoDestroy)
{
	autoCreateConnections=autoCreate;
	autoDestroyConnections=autoDestroy;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

bool ReplicaManager3::GetAutoCreateConnections(void) const
{
	return autoCreateConnections;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

bool ReplicaManager3::GetAutoDestroyConnections(void) const
{
	return autoDestroyConnections;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void ReplicaManager3::AutoCreateConnectionList(
	DataStructures::List<RakNetGUID> &participantListIn,
	DataStructures::List<Connection_RM3*> &participantListOut,
	WorldId worldId)
{
	for (unsigned int index=0; index < participantListIn.Size(); index++)
	{
		if (GetConnectionByGUID(participantListIn[index], worldId)==NULL)
		{
			Connection_RM3 *connection = AllocConnection(rakPeerInterface->GetSystemAddressFromGuid(participantListIn[index]), participantListIn[index]);
			if (connection)
			{
				PushConnection(connection);
				participantListOut.Push(connection, _FILE_AND_LINE_);
			}
		}
	}
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

bool ReplicaManager3::PushConnection(SLNet::Connection_RM3 *newConnection, WorldId worldId)
{
	if (newConnection==0)
		return false;
	if (GetConnectionByGUID(newConnection->GetRakNetGUID(), worldId))
		return false;
	// Was this intended?
	RakAssert(newConnection->GetRakNetGUID()!=rakPeerInterface->GetMyGUID());
	
	RakAssert(worldsArray[worldId]!=0 && "World not in use");
	RM3World *world = worldsArray[worldId];

	unsigned int index = world->connectionList.GetIndexOf(newConnection);
	if (index==(unsigned int)-1)
	{
		world->connectionList.Push(newConnection,_FILE_AND_LINE_);

		// Send message to validate the connection
		newConnection->SendValidation(rakPeerInterface, worldId);

		Connection_RM3::ConstructionMode constructionMode = newConnection->QueryConstructionMode();
		if (constructionMode==Connection_RM3::QUERY_REPLICA_FOR_CONSTRUCTION || constructionMode==Connection_RM3::QUERY_REPLICA_FOR_CONSTRUCTION_AND_DESTRUCTION)
		{
			unsigned int pushIdx;
			for (pushIdx=0; pushIdx < world->userReplicaList.Size(); pushIdx++)
				newConnection->OnLocalReference(world->userReplicaList[pushIdx], this);
		}
	}
	return true;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void ReplicaManager3::DeallocReplicaNoBroadcastDestruction(SLNet::Connection_RM3 *connection, SLNet::Replica3 *replica3)
{
	currentlyDeallocatingReplica=replica3;
	replica3->DeallocReplica(connection);
	currentlyDeallocatingReplica=0;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

SLNet::Connection_RM3 * ReplicaManager3::PopConnection(unsigned int index, WorldId worldId)
{
	DataStructures::List<Replica3*> replicaList;
	DataStructures::List<NetworkID> destructionList;
	DataStructures::List<Replica3*> broadcastList;
	SLNet::Connection_RM3 *connection;
	unsigned int index2;
	RM3ActionOnPopConnection action;

	RakAssert(worldsArray[worldId]!=0 && "World not in use");
	RM3World *world = worldsArray[worldId];

	connection=world->connectionList[index];

	// Clear out downloadGroup
	connection->ClearDownloadGroup(rakPeerInterface);

	RakNetGUID guid = connection->GetRakNetGUID();
	// This might be wrong, I am relying on the variable creatingSystemGuid which is transmitted
	// automatically from the first system to reference the object. However, if an object changes
	// owners then it is not going to be returned here, and therefore QueryActionOnPopConnection()
	// will not be called for the new owner.
	GetReplicasCreatedByGuid(guid, replicaList);

	for (index2=0; index2 < replicaList.Size(); index2++)
	{
		action = replicaList[index2]->QueryActionOnPopConnection(connection);
		replicaList[index2]->OnPoppedConnection(connection);
		if (action==RM3AOPC_DELETE_REPLICA)
		{
			if (replicaList[index2]->GetNetworkIDManager())
				destructionList.Push( replicaList[index2]->GetNetworkID(), _FILE_AND_LINE_  );
		}
		else if (action==RM3AOPC_DELETE_REPLICA_AND_BROADCAST_DESTRUCTION)
		{
			if (replicaList[index2]->GetNetworkIDManager())
				destructionList.Push( replicaList[index2]->GetNetworkID(), _FILE_AND_LINE_  );

			broadcastList.Push( replicaList[index2], _FILE_AND_LINE_  );
		}
		else if (action==RM3AOPC_DO_NOTHING)
		{
			for (unsigned int index3 = 0; index3 < connection->queryToSerializeReplicaList.Size(); index3++)
			{
				LastSerializationResult *lsr = connection->queryToSerializeReplicaList[index3];
				lsr->whenLastSerialized=0;
				if (lsr->lastSerializationResultBS)
				{
					for (int z=0; z < RM3_NUM_OUTPUT_BITSTREAM_CHANNELS; z++)
						lsr->lastSerializationResultBS->bitStream[z].Reset();
				}
			}
		}
	}

	BroadcastDestructionList(broadcastList, connection->GetSystemAddress());
	for (index2=0; index2 < destructionList.Size(); index2++)
	{
		// Do lookup in case DeallocReplica destroyed one of of the later Replica3 instances in the list
		Replica3* replicaToDestroy = world->networkIDManager->GET_OBJECT_FROM_ID<Replica3*>(destructionList[index2]);
		if (replicaToDestroy)
		{
			replicaToDestroy->PreDestruction(connection);
			replicaToDestroy->DeallocReplica(connection);
		}
	}

	world->connectionList.RemoveAtIndex(index);
	return connection;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

SLNet::Connection_RM3 * ReplicaManager3::PopConnection(RakNetGUID guid, WorldId worldId)
{
	unsigned int index;

	RakAssert(worldsArray[worldId]!=0 && "World not in use");
	RM3World *world = worldsArray[worldId];

	for (index=0; index < world->connectionList.Size(); index++)
	{
		if (world->connectionList[index]->GetRakNetGUID()==guid)
		{
			return PopConnection(index, worldId);
		}
	}
	return 0;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void ReplicaManager3::Reference(SLNet::Replica3 *replica3, WorldId worldId)
{
	RakAssert(worldsArray[worldId]!=0 && "World not in use");
	RM3World *world = worldsArray[worldId];

	unsigned int index = ReferenceInternal(replica3, worldId);

	if (index!=(unsigned int)-1)
	{
		unsigned int pushIdx;
		for (pushIdx=0; pushIdx < world->connectionList.Size(); pushIdx++)
		{
			Connection_RM3::ConstructionMode constructionMode = world->connectionList[pushIdx]->QueryConstructionMode();
			if (constructionMode==Connection_RM3::QUERY_REPLICA_FOR_CONSTRUCTION || constructionMode==Connection_RM3::QUERY_REPLICA_FOR_CONSTRUCTION_AND_DESTRUCTION)
			{
				world->connectionList[pushIdx]->OnLocalReference(replica3, this);
			}
		}
	}
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

unsigned int ReplicaManager3::ReferenceInternal(SLNet::Replica3 *replica3, WorldId worldId)
{
	RakAssert(worldsArray[worldId]!=0 && "World not in use");
	RM3World *world = worldsArray[worldId];

	unsigned int index;
	index = world->userReplicaList.GetIndexOf(replica3);
	if (index==(unsigned int)-1)
	{
		RakAssert(world->networkIDManager);
		replica3->SetNetworkIDManager(world->networkIDManager);
		// If it crashes on rakPeerInterface==0 then you didn't call RakPeerInterface::AttachPlugin()
		if (replica3->creatingSystemGUID==UNASSIGNED_RAKNET_GUID)
			replica3->creatingSystemGUID=rakPeerInterface->GetGuidFromSystemAddress(UNASSIGNED_SYSTEM_ADDRESS);
		replica3->replicaManager=this;
		if (replica3->referenceIndex==(uint32_t)-1)
		{
			replica3->referenceIndex=nextReferenceIndex++;
		}
		world->userReplicaList.Push(replica3,_FILE_AND_LINE_);
		return world->userReplicaList.Size()-1;
	}
	return (unsigned int) -1;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void ReplicaManager3::Dereference(SLNet::Replica3 *replica3, WorldId worldId)
{
	RakAssert(worldsArray[worldId]!=0 && "World not in use");
	RM3World *world = worldsArray[worldId];

	unsigned int index, index2;
	for (index=0; index < world->userReplicaList.Size(); index++)
	{
		if (world->userReplicaList[index]==replica3)
		{
			world->userReplicaList.RemoveAtIndex(index);
			break;
		}
	}

	// Remove from all connections
	for (index2=0; index2 < world->connectionList.Size(); index2++)
	{
		world->connectionList[index2]->OnDereference(replica3, this);
	}
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void ReplicaManager3::DereferenceList(DataStructures::List<Replica3*> &replicaListIn, WorldId worldId)
{
	unsigned int index;
	for (index=0; index < replicaListIn.Size(); index++)
		Dereference(replicaListIn[index], worldId);
}


// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void ReplicaManager3::GetReplicasCreatedByMe(DataStructures::List<Replica3*> &replicaListOut, WorldId worldId)
{
	//RakNetGUID myGuid = rakPeerInterface->GetGuidFromSystemAddress(UNASSIGNED_SYSTEM_ADDRESS);
	GetReplicasCreatedByGuid(rakPeerInterface->GetGuidFromSystemAddress(UNASSIGNED_SYSTEM_ADDRESS), replicaListOut, worldId);
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void ReplicaManager3::GetReferencedReplicaList(DataStructures::List<Replica3*> &replicaListOut, WorldId worldId)
{
	RakAssert(worldsArray[worldId]!=0 && "World not in use");
	RM3World *world = worldsArray[worldId];

	replicaListOut=world->userReplicaList;
}
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void ReplicaManager3::GetReplicasCreatedByGuid(RakNetGUID guid, DataStructures::List<Replica3*> &replicaListOut, WorldId worldId)
{
	RakAssert(worldsArray[worldId]!=0 && "World not in use");
	RM3World *world = worldsArray[worldId];

	replicaListOut.Clear(false,_FILE_AND_LINE_);
	unsigned int index;
	for (index=0; index < world->userReplicaList.Size(); index++)
	{
		if (world->userReplicaList[index]->creatingSystemGUID==guid)
			replicaListOut.Push(world->userReplicaList[index],_FILE_AND_LINE_);
	}
}


// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

unsigned ReplicaManager3::GetReplicaCount(WorldId worldId) const
{
	RakAssert(worldsArray[worldId]!=0 && "World not in use");
	RM3World *world = worldsArray[worldId];

	return world->userReplicaList.Size();
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Replica3 *ReplicaManager3::GetReplicaAtIndex(unsigned index, WorldId worldId)
{
	RakAssert(worldsArray[worldId]!=0 && "World not in use");
	RM3World *world = worldsArray[worldId];

	return world->userReplicaList[index];
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

unsigned int ReplicaManager3::GetConnectionCount(WorldId worldId) const
{
	RakAssert(worldsArray[worldId]!=0 && "World not in use");
	RM3World *world = worldsArray[worldId];

	return world->connectionList.Size();
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Connection_RM3* ReplicaManager3::GetConnectionAtIndex(unsigned index, WorldId worldId) const
{
	RakAssert(worldsArray[worldId]!=0 && "World not in use");
	RM3World *world = worldsArray[worldId];

	return world->connectionList[index];
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Connection_RM3* ReplicaManager3::GetConnectionBySystemAddress(const SystemAddress &sa, WorldId worldId) const
{
	RakAssert(worldsArray[worldId]!=0 && "World not in use");
	RM3World *world = worldsArray[worldId];

	unsigned int index;
	for (index=0; index < world->connectionList.Size(); index++)
	{
		if (world->connectionList[index]->GetSystemAddress()==sa)
		{
			return world->connectionList[index];
		}
	}
	return 0;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Connection_RM3* ReplicaManager3::GetConnectionByGUID(RakNetGUID guid, WorldId worldId) const
{
	RakAssert(worldsArray[worldId]!=0 && "World not in use");
	RM3World *world = worldsArray[worldId];

	unsigned int index;
	for (index=0; index < world->connectionList.Size(); index++)
	{
		if (world->connectionList[index]->GetRakNetGUID()==guid)
		{
			return world->connectionList[index];
		}
	}
	return 0;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void ReplicaManager3::SetDefaultOrderingChannel(char def)
{
	defaultSendParameters.orderingChannel=def;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void ReplicaManager3::SetDefaultPacketPriority(PacketPriority def)
{
	defaultSendParameters.priority=def;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void ReplicaManager3::SetDefaultPacketReliability(PacketReliability def)
{
	defaultSendParameters.reliability=def;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void ReplicaManager3::SetAutoSerializeInterval(SLNet::Time intervalMS)
{
	autoSerializeInterval=intervalMS;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void ReplicaManager3::GetConnectionsThatHaveReplicaConstructed(Replica3 *replica, DataStructures::List<Connection_RM3*> &connectionsThatHaveConstructedThisReplica, WorldId worldId)
{
	RakAssert(worldsArray[worldId]!=0 && "World not in use");
	RM3World *world = worldsArray[worldId];

	connectionsThatHaveConstructedThisReplica.Clear(false,_FILE_AND_LINE_);
	unsigned int index;
	for (index=0; index < world->connectionList.Size(); index++)
	{
		if (world->connectionList[index]->HasReplicaConstructed(replica))
			connectionsThatHaveConstructedThisReplica.Push(world->connectionList[index],_FILE_AND_LINE_);
	}
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

bool ReplicaManager3::GetAllConnectionDownloadsCompleted(WorldId worldId) const
{
	RakAssert(worldsArray[worldId]!=0 && "World not in use");
	RM3World *world = worldsArray[worldId];

	unsigned int index;
	for (index=0; index < world->connectionList.Size(); index++)
	{
		if (world->connectionList[index]->GetDownloadWasCompleted()==false)
			return false;
	}
	return true;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void ReplicaManager3::Clear(bool deleteWorlds)
{
	for (unsigned int i=0; i < worldsList.Size(); i++)
	{
		worldsList[i]->Clear(this);
		if (deleteWorlds)
		{
			worldsArray[worldsList[i]->worldId]=0;
			delete worldsList[i];
		}
	} 
	if (deleteWorlds)
		worldsList.Clear(false, _FILE_AND_LINE_);
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

ReplicaManager3::RM3World::RM3World()
{
	networkIDManager=0;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void ReplicaManager3::RM3World::Clear(ReplicaManager3 *replicaManager3)
{
	if (replicaManager3->GetAutoDestroyConnections())
	{
		for (unsigned int i=0; i < connectionList.Size(); i++)
			replicaManager3->DeallocConnection(connectionList[i]);
	}
	else
	{
		// Clear out downloadGroup even if not auto destroying the connection, since the packets need to go back to RakPeer
		for (unsigned int i=0; i < connectionList.Size(); i++)
			connectionList[i]->ClearDownloadGroup(replicaManager3->GetRakPeerInterface());
	}
	
	for (unsigned int i=0; i < userReplicaList.Size(); i++)
	{
		userReplicaList[i]->replicaManager=0;
		userReplicaList[i]->SetNetworkIDManager(0);
	}
	connectionList.Clear(true,_FILE_AND_LINE_);
	userReplicaList.Clear(true,_FILE_AND_LINE_);
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

PRO ReplicaManager3::GetDefaultSendParameters(void) const
{
	return defaultSendParameters;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void ReplicaManager3::AddWorld(WorldId worldId)
{
	RakAssert(worldsArray[worldId]==0 && "World already in use");

	RM3World *newWorld = SLNet::OP_NEW<RM3World>(_FILE_AND_LINE_);
	newWorld->worldId=worldId;
	worldsArray[worldId]=newWorld;
	worldsList.Push(newWorld,_FILE_AND_LINE_);
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void ReplicaManager3::RemoveWorld(WorldId worldId)
{
	RakAssert(worldsArray[worldId]!=0 && "World not in use");
	for (unsigned int i=0; i < worldsList.Size(); i++)
	{
		if (worldsList[i]==worldsArray[worldId])
		{
			SLNet::OP_DELETE(worldsList[i],_FILE_AND_LINE_);
			worldsList.RemoveAtIndexFast(i);
			break;
		}
	}
	worldsArray[worldId]=0;

}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

NetworkIDManager *ReplicaManager3::GetNetworkIDManager(WorldId worldId) const
{
	RakAssert(worldsArray[worldId]!=0 && "World not in use");
	RM3World *world = worldsArray[worldId];

	return world->networkIDManager;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void ReplicaManager3::SetNetworkIDManager(NetworkIDManager *_networkIDManager, WorldId worldId)
{
	RakAssert(worldsArray[worldId]!=0 && "World not in use");
	RM3World *world = worldsArray[worldId];

	world->networkIDManager=_networkIDManager;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

PluginReceiveResult ReplicaManager3::OnReceive(Packet *packet)
{
	if (packet->length<2)
		return RR_CONTINUE_PROCESSING;

	WorldId incomingWorldId;

	SLNet::Time timestamp=0;
	unsigned char packetIdentifier, packetDataOffset;
	if ( ( unsigned char ) packet->data[ 0 ] == ID_TIMESTAMP )
	{
		if ( packet->length > sizeof( unsigned char ) + sizeof(SLNet::Time ) )
		{
			packetIdentifier = ( unsigned char ) packet->data[ sizeof( unsigned char ) + sizeof(SLNet::Time ) ];
			// Required for proper endian swapping
			SLNet::BitStream tsBs(packet->data+sizeof(MessageID),packet->length-1,false);
			tsBs.Read(timestamp);
			// Next line assumes worldId is only 1 byte
			RakAssert(sizeof(WorldId)==1);
			incomingWorldId=packet->data[sizeof( unsigned char )*2 + sizeof(SLNet::Time )];
			packetDataOffset=sizeof( unsigned char )*3 + sizeof(SLNet::Time );
		}
		else
			return RR_STOP_PROCESSING_AND_DEALLOCATE;
	}
	else
	{
		packetIdentifier = ( unsigned char ) packet->data[ 0 ];
		// Next line assumes worldId is only 1 byte
		RakAssert(sizeof(WorldId)==1);
		incomingWorldId=packet->data[sizeof( unsigned char )];
		packetDataOffset=sizeof( unsigned char )*2;
	}

	if (worldsArray[incomingWorldId]==0)
		return RR_CONTINUE_PROCESSING;

	switch (packetIdentifier)
	{
	case ID_REPLICA_MANAGER_CONSTRUCTION:
		return OnConstruction(packet, packet->data, packet->length, packet->guid, packetDataOffset, incomingWorldId);
	case ID_REPLICA_MANAGER_SERIALIZE:
		return OnSerialize(packet, packet->data, packet->length, packet->guid, timestamp, packetDataOffset, incomingWorldId);
	case ID_REPLICA_MANAGER_DOWNLOAD_STARTED:
		if (packet->wasGeneratedLocally==false)
		{
			return OnDownloadStarted(packet, packet->data, packet->length, packet->guid, packetDataOffset, incomingWorldId);
		}
		else
			break;
	case ID_REPLICA_MANAGER_DOWNLOAD_COMPLETE:
		if (packet->wasGeneratedLocally==false)
		{
			return OnDownloadComplete(packet, packet->data, packet->length, packet->guid, packetDataOffset, incomingWorldId);
		}
		else
			break;
	case ID_REPLICA_MANAGER_SCOPE_CHANGE:
		{
			Connection_RM3 *connection = GetConnectionByGUID(packet->guid, incomingWorldId);
			if (connection && connection->isValidated==false)
			{
				// This connection is now confirmed bidirectional
				connection->isValidated=true;
				// Reply back on validation
				connection->SendValidation(rakPeerInterface,incomingWorldId);
			}
		}
	}

	return RR_CONTINUE_PROCESSING;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void Connection_RM3::AutoConstructByQuery(ReplicaManager3 *replicaManager3, WorldId worldId)
{
	ValidateLists(replicaManager3);

	ConstructionMode curConstructionMode = QueryConstructionMode();

	unsigned int index;
	RM3ConstructionState constructionState;
	LastSerializationResult *lsr;
	index=0;

	constructedReplicasCulled.Clear(false,_FILE_AND_LINE_);
	destroyedReplicasCulled.Clear(false,_FILE_AND_LINE_);

	if (curConstructionMode==QUERY_REPLICA_FOR_CONSTRUCTION || curConstructionMode==QUERY_REPLICA_FOR_CONSTRUCTION_AND_DESTRUCTION)
	{
		while (index < queryToConstructReplicaList.Size())
		{
			lsr=queryToConstructReplicaList[index];
			constructionState=lsr->replica->QueryConstruction(this, replicaManager3);
			if (constructionState==RM3CS_ALREADY_EXISTS_REMOTELY || constructionState==RM3CS_ALREADY_EXISTS_REMOTELY_DO_NOT_CONSTRUCT)
			{
				OnReplicaAlreadyExists(index, replicaManager3);
				if (constructionState==RM3CS_ALREADY_EXISTS_REMOTELY)
					constructedReplicasCulled.Push(lsr->replica,_FILE_AND_LINE_);

				/*
				if (constructionState==RM3CS_ALREADY_EXISTS_REMOTELY)
				{
					// Serialize construction data to this connection
					SLNet::BitStream bsOut;
					bsOut.Write((MessageID)ID_REPLICA_MANAGER_3_SERIALIZE_CONSTRUCTION_EXISTING);
					bsOut.Write(replicaManager3->GetWorldID());
					NetworkID networkId;
					networkId=lsr->replica->GetNetworkID();
					bsOut.Write(networkId);
					BitSize_t bitsWritten = bsOut.GetNumberOfBitsUsed();
					lsr->replica->SerializeConstructionExisting(&bsOut, this);
					if (bsOut.GetNumberOfBitsUsed()!=bitsWritten)
						replicaManager3->SendUnified(&bsOut,HIGH_PRIORITY,RELIABLE_ORDERED,0,GetSystemAddress(), false);
				}

				// Serialize first serialization to this connection.
				// This is done here, as it isn't done in PushConstruction
				SerializeParameters sp;
				SLNet::BitStream emptyBs;
				for (index=0; index < (unsigned int) RM3_NUM_OUTPUT_BITSTREAM_CHANNELS; index++)
				{
					sp.lastSentBitstream[index]=&emptyBs;
					sp.pro[index]=replicaManager3->GetDefaultSendParameters();
				}
				sp.bitsWrittenSoFar=0;
				sp.destinationConnection=this;
				sp.messageTimestamp=0;
				sp.whenLastSerialized=0;

				SLNet::Replica3 *replica = lsr->replica;

				RM3SerializationResult res = replica->Serialize(&sp);
				if (res!=RM3SR_NEVER_SERIALIZE_FOR_THIS_CONNECTION &&
					res!=RM3SR_DO_NOT_SERIALIZE &&
					res!=RM3SR_SERIALIZED_UNIQUELY)
				{
					bool allIndices[RM3_NUM_OUTPUT_BITSTREAM_CHANNELS];
					for (int z=0; z < RM3_NUM_OUTPUT_BITSTREAM_CHANNELS; z++)
					{
						sp.bitsWrittenSoFar+=sp.outputBitstream[z].GetNumberOfBitsUsed();
						allIndices[z]=true;
					}
					if (SendSerialize(replica, allIndices, sp.outputBitstream, sp.messageTimestamp, sp.pro, replicaManager3->GetRakPeerInterface(), replicaManager3->GetWorldID())==SSICR_SENT_DATA)
						lsr->replica->whenLastSerialized=SLNet::GetTimeMS();
				}
				*/
			}
			else if (constructionState==RM3CS_SEND_CONSTRUCTION)
			{
				OnConstructToThisConnection(index, replicaManager3);
				RakAssert(lsr->replica);
				constructedReplicasCulled.Push(lsr->replica,_FILE_AND_LINE_);
			}
			else if (constructionState==RM3CS_NEVER_CONSTRUCT)
			{
				OnNeverConstruct(index, replicaManager3);
			}
			else//  if (constructionState==RM3CS_NO_ACTION)
			{
				// Do nothing
				index++;
			}
		}

		if (curConstructionMode==QUERY_REPLICA_FOR_CONSTRUCTION_AND_DESTRUCTION)
		{
			RM3DestructionState destructionState;
			index=0;
			while (index < queryToDestructReplicaList.Size())
			{
				lsr=queryToDestructReplicaList[index];
				destructionState=lsr->replica->QueryDestruction(this, replicaManager3);
				if (destructionState==RM3DS_SEND_DESTRUCTION)
				{
					OnSendDestructionFromQuery(index, replicaManager3);
					destroyedReplicasCulled.Push(lsr->replica,_FILE_AND_LINE_);
				}
				else if (destructionState==RM3DS_DO_NOT_QUERY_DESTRUCTION)
				{
					OnDoNotQueryDestruction(index, replicaManager3);
				}
				else//  if (destructionState==RM3CS_NO_ACTION)
				{
					// Do nothing
					index++;
				}
			}
		}
	}
	else if (curConstructionMode==QUERY_CONNECTION_FOR_REPLICA_LIST)
	{
		QueryReplicaList(constructedReplicasCulled,destroyedReplicasCulled);

		unsigned int idx1, idx2;

		// Create new
		for (idx2=0; idx2 < constructedReplicasCulled.Size(); idx2++)
			OnConstructToThisConnection(constructedReplicasCulled[idx2], replicaManager3);

		bool exists;
		for (idx2=0; idx2 < destroyedReplicasCulled.Size(); idx2++)
		{
			exists=false;
			bool objectExists;
			idx1=constructedReplicaList.GetIndexFromKey(destroyedReplicasCulled[idx2], &objectExists);
			if (objectExists)
			{
				constructedReplicaList.RemoveAtIndex(idx1);

				unsigned int j;
				for (j=0; j < queryToSerializeReplicaList.Size(); j++)
				{
					if (queryToSerializeReplicaList[j]->replica==destroyedReplicasCulled[idx2] )
					{
						queryToSerializeReplicaList.RemoveAtIndex(j);
						break;
					}
				}
			}
		}
	}

	SendConstruction(constructedReplicasCulled,destroyedReplicasCulled,replicaManager3->defaultSendParameters,replicaManager3->rakPeerInterface,worldId,replicaManager3);
}
void ReplicaManager3::Update(void)
{
	unsigned int index,index2,index3;

	WorldId worldId;
	RM3World *world;
	SLNet::Time time = SLNet::GetTime();

	for (index3=0; index3 < worldsList.Size(); index3++)
	{
		world = worldsList[index3];
		worldId = world->worldId;

		for (index=0; index < world->connectionList.Size(); index++)
		{
			if (world->connectionList[index]->isValidated==false)
				continue;
			world->connectionList[index]->AutoConstructByQuery(this, worldId);
		}
	}

	if (time - lastAutoSerializeOccurance >= autoSerializeInterval)
	{
		for (index3=0; index3 < worldsList.Size(); index3++)
		{
			world = worldsList[index3];
			worldId = world->worldId;

			for (index=0; index < world->userReplicaList.Size(); index++)
			{
				world->userReplicaList[index]->forceSendUntilNextUpdate=false;
				world->userReplicaList[index]->OnUserReplicaPreSerializeTick();
			}

			SerializeParameters sp;
			sp.curTime=time;
			Connection_RM3 *connection;
			SendSerializeIfChangedResult ssicr;
			LastSerializationResult *lsr;

			sp.messageTimestamp=0;
			for (int i=0; i < RM3_NUM_OUTPUT_BITSTREAM_CHANNELS; i++)
				sp.pro[i]=defaultSendParameters;
			index2=0;
			for (index=0; index < world->connectionList.Size(); index++)
			{
				connection = world->connectionList[index];
				sp.bitsWrittenSoFar=0;
				index2=0;
				sp.destinationConnection=connection;

				DataStructures::List<Replica3*> replicasToSerialize;
				replicasToSerialize.Clear(true, _FILE_AND_LINE_);
				if (connection->QuerySerializationList(replicasToSerialize))
				{
					// Update replica->lsr so we can lookup in the next block
					// lsr is per connection / per replica
					while (index2 < connection->queryToSerializeReplicaList.Size())
					{
						connection->queryToSerializeReplicaList[index2]->replica->lsr=connection->queryToSerializeReplicaList[index2];
						index2++;
					}


					// User is manually specifying list of replicas to serialize
					index2=0;
					while (index2 < replicasToSerialize.Size())
					{
						lsr=replicasToSerialize[index2]->lsr;
						RakAssert(lsr->replica==replicasToSerialize[index2]);

						sp.whenLastSerialized=lsr->whenLastSerialized;
						ssicr=connection->SendSerializeIfChanged(lsr, &sp, GetRakPeerInterface(), worldId, this, time);
						if (ssicr==SSICR_SENT_DATA)
							lsr->whenLastSerialized=time;
						index2++;
					}
				}
				else
				{
					while (index2 < connection->queryToSerializeReplicaList.Size())
					{
						lsr=connection->queryToSerializeReplicaList[index2];

						sp.destinationConnection=connection;
						sp.whenLastSerialized=lsr->whenLastSerialized;
						ssicr=connection->SendSerializeIfChanged(lsr, &sp, GetRakPeerInterface(), worldId, this, time);
						if (ssicr==SSICR_SENT_DATA)
						{
							lsr->whenLastSerialized=time;
							index2++;
						}
						else if (ssicr==SSICR_NEVER_SERIALIZE)
						{
							// Removed from the middle of the list
						}
						else
							index2++;
					}
				}
			}
		}

		lastAutoSerializeOccurance=time;
	}
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void ReplicaManager3::OnClosedConnection(const SystemAddress &systemAddress, RakNetGUID rakNetGUID, PI2_LostConnectionReason lostConnectionReason )
{
	(void) lostConnectionReason;
	(void) systemAddress;
	if (autoDestroyConnections)
	{
		Connection_RM3 *connection = PopConnection(rakNetGUID);
		if (connection)
			DeallocConnection(connection);
	}
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void ReplicaManager3::OnNewConnection(const SystemAddress &systemAddress, RakNetGUID rakNetGUID, bool isIncoming)
{
	(void) isIncoming;
	if (autoCreateConnections)
	{
		Connection_RM3 *connection = AllocConnection(systemAddress, rakNetGUID);
		if (connection)
			PushConnection(connection);
	}
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void ReplicaManager3::OnRakPeerShutdown(void)
{
	if (autoDestroyConnections)
	{
		RM3World *world;
		unsigned int index3;
		for (index3=0; index3 < worldsList.Size(); index3++)
		{
			world = worldsList[index3];

			while (world->connectionList.Size())
			{
				Connection_RM3 *connection = PopConnection(world->connectionList.Size()-1, world->worldId);
				if (connection)
					DeallocConnection(connection);
			}
		}
	}


	Clear(false);
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void ReplicaManager3::OnDetach(void)
{
	OnRakPeerShutdown();
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

PluginReceiveResult ReplicaManager3::OnConstruction(Packet *packet, unsigned char *packetData, int packetDataLength, RakNetGUID senderGuid, unsigned char packetDataOffset, WorldId worldId)
{
	RM3World *world = worldsArray[worldId];

	Connection_RM3 *connection = GetConnectionByGUID(senderGuid, worldId);
	if (connection==0)
	{
		// Almost certainly a bug
		RakAssert("Got OnConstruction but no connection yet" && 0);
		return RR_CONTINUE_PROCESSING;
	}
	if (connection->groupConstructionAndSerialize)
	{
		connection->downloadGroup.Push(packet, __FILE__, __LINE__);
		return RR_STOP_PROCESSING;
	}

	SLNet::BitStream bsIn(packetData,packetDataLength,false);
	bsIn.IgnoreBytes(packetDataOffset);
	uint16_t constructionObjectListSize, destructionObjectListSize, index, index2;
	BitSize_t streamEnd, writeAllocationIDEnd;
	Replica3 *replica;
	NetworkID networkId;
	RakNetGUID creatingSystemGuid;
	bool actuallyCreateObject=false;

	DataStructures::List<bool> actuallyCreateObjectList;
	DataStructures::List<Replica3*> constructionTickStack;

	RakAssert(world->networkIDManager);

	bsIn.Read(constructionObjectListSize);
	for (index=0; index < constructionObjectListSize; index++)
	{
		bsIn.Read(streamEnd);
		bsIn.Read(networkId);
		Replica3* existingReplica = world->networkIDManager->GET_OBJECT_FROM_ID<Replica3*>(networkId);
		bsIn.Read(actuallyCreateObject);
		actuallyCreateObjectList.Push(actuallyCreateObject, _FILE_AND_LINE_);
		bsIn.AlignReadToByteBoundary();

		if (actuallyCreateObject)
		{
			bsIn.Read(creatingSystemGuid);
			bsIn.Read(writeAllocationIDEnd);

			//printf("OnConstruction: %i\n",networkId.guid.g); // Removeme
			if (existingReplica)
			{
				existingReplica->replicaManager=this;

				// Network ID already in use
				connection->OnDownloadExisting(existingReplica, this);

				constructionTickStack.Push(0, _FILE_AND_LINE_);
				bsIn.SetReadOffset(streamEnd);
				continue;
			}

			bsIn.AlignReadToByteBoundary();
			replica = connection->AllocReplica(&bsIn, this);
			if (replica==0)
			{
				constructionTickStack.Push(0, _FILE_AND_LINE_);
				bsIn.SetReadOffset(streamEnd);
				continue;
			}

			// Go past the bitStream written to with WriteAllocationID(). Necessary in case the user didn't read out the bitStream the same way it was written
			// bitOffset2 is already aligned
			bsIn.SetReadOffset(writeAllocationIDEnd);

			replica->SetNetworkIDManager(world->networkIDManager);
			replica->SetNetworkID(networkId);

			replica->replicaManager=this;
			replica->creatingSystemGUID=creatingSystemGuid;

			if (!replica->QueryRemoteConstruction(connection) ||
				!replica->DeserializeConstruction(&bsIn, connection))
			{
				DeallocReplicaNoBroadcastDestruction(connection, replica);
				bsIn.SetReadOffset(streamEnd);
				constructionTickStack.Push(0, _FILE_AND_LINE_);
				continue;
			}

			constructionTickStack.Push(replica, _FILE_AND_LINE_);

			// Register the replica
			ReferenceInternal(replica, worldId);
		}
		else
		{
			if (existingReplica)
			{
				existingReplica->DeserializeConstructionExisting(&bsIn, connection);
				constructionTickStack.Push(existingReplica, _FILE_AND_LINE_);
			}
			else
			{
				constructionTickStack.Push(0, _FILE_AND_LINE_);
			}
		}


		bsIn.SetReadOffset(streamEnd);
		bsIn.AlignReadToByteBoundary();
	}

    RakAssert(constructionTickStack.Size()==constructionObjectListSize);
	RakAssert(actuallyCreateObjectList.Size()==constructionObjectListSize);

	SLNet::BitStream empty;
	for (index=0; index < constructionObjectListSize; index++)
	{
		bool pdcWritten=false;
		bsIn.Read(pdcWritten);
		if (pdcWritten)
		{
			bsIn.AlignReadToByteBoundary();
			bsIn.Read(streamEnd);
			bsIn.Read(networkId);
			if (constructionTickStack[index]!=0)
			{
				bsIn.AlignReadToByteBoundary();
				if (actuallyCreateObjectList[index])
					constructionTickStack[index]->PostDeserializeConstruction(&bsIn, connection);
				else
					constructionTickStack[index]->PostDeserializeConstructionExisting(&bsIn, connection);
			}
			bsIn.SetReadOffset(streamEnd);
		}
		else
		{
			if (constructionTickStack[index]!=0)
			{
				if (actuallyCreateObjectList[index])
					constructionTickStack[index]->PostDeserializeConstruction(&empty, connection);
				else
					constructionTickStack[index]->PostDeserializeConstructionExisting(&empty, connection);
			}
		}
	}
	bsIn.AlignReadToByteBoundary();

	for (index=0; index < constructionObjectListSize; index++)
	{
		if (constructionTickStack[index]!=0)
		{
			if (actuallyCreateObjectList[index])
			{
				// Tell the connection(s) that this object exists since they just sent it to us
				connection->OnDownloadFromThisSystem(constructionTickStack[index], this);

				for (index2=0; index2 < world->connectionList.Size(); index2++)
				{
					if (world->connectionList[index2]!=connection)
						world->connectionList[index2]->OnDownloadFromOtherSystem(constructionTickStack[index], this);
				}
			}
		}
	}

	// Destructions
	bool b = bsIn.Read(destructionObjectListSize);
	(void) b;
	RakAssert(b);
	for (index=0; index < destructionObjectListSize; index++)
	{
		bsIn.Read(networkId);
		bsIn.Read(streamEnd);
		replica = world->networkIDManager->GET_OBJECT_FROM_ID<Replica3*>(networkId);
		if (replica==0)
		{
			// Unknown object
			bsIn.SetReadOffset(streamEnd);
			continue;
		}
		bsIn.Read(replica->deletingSystemGUID);
		if (replica->DeserializeDestruction(&bsIn,connection))
		{
			// Make sure it wasn't deleted in DeserializeDestruction
			if (world->networkIDManager->GET_OBJECT_FROM_ID<Replica3*>(networkId))
			{
				replica->PreDestruction(connection);

				// Forward deletion by remote system
				if (replica->QueryRelayDestruction(connection))
					BroadcastDestruction(replica,connection->GetSystemAddress());
				Dereference(replica);
				DeallocReplicaNoBroadcastDestruction(connection, replica);
			}
		}
		else
		{
			replica->PreDestruction(connection);
			connection->OnDereference(replica, this);
		}

		bsIn.AlignReadToByteBoundary();
	}
	return RR_CONTINUE_PROCESSING;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

PluginReceiveResult ReplicaManager3::OnSerialize(Packet *packet, unsigned char *packetData, int packetDataLength, RakNetGUID senderGuid, SLNet::Time timestamp, unsigned char packetDataOffset, WorldId worldId)
{
	Connection_RM3 *connection = GetConnectionByGUID(senderGuid, worldId);
	if (connection==0)
		return RR_CONTINUE_PROCESSING;
	if (connection->groupConstructionAndSerialize)
	{
		connection->downloadGroup.Push(packet, __FILE__, __LINE__);
		return RR_STOP_PROCESSING;
	}

	RM3World *world = worldsArray[worldId];
	RakAssert(world->networkIDManager);
	SLNet::BitStream bsIn(packetData,packetDataLength,false);
	bsIn.IgnoreBytes(packetDataOffset);

	struct DeserializeParameters ds;
	ds.timeStamp=timestamp;
	ds.sourceConnection=connection;

	Replica3 *replica;
	NetworkID networkId;
	BitSize_t bitsUsed;
	bsIn.Read(networkId);
	//printf("OnSerialize: %i\n",networkId.guid.g); // Removeme
	replica = world->networkIDManager->GET_OBJECT_FROM_ID<Replica3*>(networkId);
	if (replica)
	{
		for (int z=0; z < RM3_NUM_OUTPUT_BITSTREAM_CHANNELS; z++)
		{
			bsIn.Read(ds.bitstreamWrittenTo[z]);
			if (ds.bitstreamWrittenTo[z])
			{
				bsIn.ReadCompressed(bitsUsed);
				bsIn.AlignReadToByteBoundary();
				bsIn.Read(ds.serializationBitstream[z], bitsUsed);
			}
		}
		replica->Deserialize(&ds);
	}
	return RR_CONTINUE_PROCESSING;
}
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

PluginReceiveResult ReplicaManager3::OnDownloadStarted(Packet *packet, unsigned char *packetData, int packetDataLength, RakNetGUID senderGuid, unsigned char packetDataOffset, WorldId worldId)
{
	Connection_RM3 *connection = GetConnectionByGUID(senderGuid, worldId);
	if (connection==0)
		return RR_CONTINUE_PROCESSING;
	if (connection->QueryGroupDownloadMessages() &&
		// ID_DOWNLOAD_STARTED will be processed twice, being processed the second time once ID_DOWNLOAD_COMPLETE arrives.
		// However, the second time groupConstructionAndSerialize will be set to true so it won't be processed a third time
		connection->groupConstructionAndSerialize==false
		)
	{
		// These messages will be held by the plugin and returned when the download is complete
		connection->groupConstructionAndSerialize=true;
		RakAssert(connection->downloadGroup.Size()==0);
		connection->downloadGroup.Push(packet, __FILE__, __LINE__);
		return RR_STOP_PROCESSING;
	}

	connection->groupConstructionAndSerialize=false;
	SLNet::BitStream bsIn(packetData,packetDataLength,false);
	bsIn.IgnoreBytes(packetDataOffset);
	connection->DeserializeOnDownloadStarted(&bsIn);
	return RR_CONTINUE_PROCESSING;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

PluginReceiveResult ReplicaManager3::OnDownloadComplete(Packet *packet, unsigned char *packetData, int packetDataLength, RakNetGUID senderGuid, unsigned char packetDataOffset, WorldId worldId)
{
	Connection_RM3 *connection = GetConnectionByGUID(senderGuid, worldId);
	if (connection==0)
		return RR_CONTINUE_PROCESSING;

	if (connection->groupConstructionAndSerialize==true && connection->downloadGroup.Size()>0)
	{
		// Push back buffered packets in front of this one
		unsigned int i;
		for (i=0; i < connection->downloadGroup.Size(); i++)
			rakPeerInterface->PushBackPacket(connection->downloadGroup[i],false);

		// Push this one to be last too. It will be processed again, but the second time 
		// groupConstructionAndSerialize will be false and downloadGroup will be empty, so it will go past this block
		connection->downloadGroup.Clear(__FILE__,__LINE__);
		rakPeerInterface->PushBackPacket(packet,false);

		return RR_STOP_PROCESSING;
	}

	SLNet::BitStream bsIn(packetData,packetDataLength,false);
	bsIn.IgnoreBytes(packetDataOffset);
	connection->gotDownloadComplete=true;
	connection->DeserializeOnDownloadComplete(&bsIn);
	return RR_CONTINUE_PROCESSING;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Replica3* ReplicaManager3::GetReplicaByNetworkID(NetworkID networkId, WorldId worldId)
{
	RM3World *world = worldsArray[worldId];

	unsigned int i;
	for (i=0; i < world->userReplicaList.Size(); i++)
	{
		if (world->userReplicaList[i]->GetNetworkID()==networkId)
			return world->userReplicaList[i];
	}
	return 0;
}


// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


void ReplicaManager3::BroadcastDestructionList(DataStructures::List<Replica3*> &replicaListSource, const SystemAddress &exclusionAddress, WorldId worldId)
{
	SLNet::BitStream bsOut;
	unsigned int i,j;

	RakAssert(worldsArray[worldId]!=0 && "World not in use");
	RM3World *world = worldsArray[worldId];

	DataStructures::List<Replica3*> replicaList;

	for (i=0; i < replicaListSource.Size(); i++)
	{
		if (replicaListSource[i]==currentlyDeallocatingReplica)
			continue;
		replicaList.Push(replicaListSource[i], __FILE__, __LINE__);
	}

	if (replicaList.Size()==0)
		return;

	for (i=0; i < replicaList.Size(); i++)
	{
		if (replicaList[i]->deletingSystemGUID==UNASSIGNED_RAKNET_GUID)
			replicaList[i]->deletingSystemGUID=GetRakPeerInterface()->GetGuidFromSystemAddress(UNASSIGNED_SYSTEM_ADDRESS);
	}

	for (j=0; j < world->connectionList.Size(); j++)
	{
		if (world->connectionList[j]->GetSystemAddress()==exclusionAddress)
			continue;

		bsOut.Reset();
		bsOut.Write((MessageID)ID_REPLICA_MANAGER_CONSTRUCTION);
		bsOut.Write(worldId);
		uint16_t cnt=0;
		bsOut.Write(cnt); // No construction
		cnt=(uint16_t) replicaList.Size();
		BitSize_t cntOffset=bsOut.GetWriteOffset();;
		bsOut.Write(cnt); // Overwritten at send call
		cnt=0;

		for (i=0; i < replicaList.Size(); i++)
		{
			if (world->connectionList[j]->HasReplicaConstructed(replicaList[i])==false)
				continue;
			cnt++;

			NetworkID networkId;
			networkId=replicaList[i]->GetNetworkID();
			bsOut.Write(networkId);
			BitSize_t offsetStart, offsetEnd;
			offsetStart=bsOut.GetWriteOffset();
			bsOut.Write(offsetStart);
			bsOut.Write(replicaList[i]->deletingSystemGUID);
			replicaList[i]->SerializeDestruction(&bsOut, world->connectionList[j]);
			bsOut.AlignWriteToByteBoundary();
			offsetEnd=bsOut.GetWriteOffset();
			bsOut.SetWriteOffset(offsetStart);
			bsOut.Write(offsetEnd);
			bsOut.SetWriteOffset(offsetEnd);
		}

		if (cnt>0)
		{
			BitSize_t curOffset=bsOut.GetWriteOffset();
			bsOut.SetWriteOffset(cntOffset);
			bsOut.Write(cnt);
			bsOut.SetWriteOffset(curOffset);
			rakPeerInterface->Send(&bsOut,defaultSendParameters.priority,defaultSendParameters.reliability,defaultSendParameters.orderingChannel,world->connectionList[j]->GetSystemAddress(),false, defaultSendParameters.sendReceipt);
		}
	}
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


void ReplicaManager3::BroadcastDestruction(Replica3 *replica, const SystemAddress &exclusionAddress)
{
	DataStructures::List<Replica3*> replicaList;
	replicaList.Push(replica, _FILE_AND_LINE_ );
	BroadcastDestructionList(replicaList,exclusionAddress);
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Connection_RM3::Connection_RM3(const SystemAddress &_systemAddress, RakNetGUID _guid)
: systemAddress(_systemAddress), guid(_guid)
{
	isValidated=false;
	isFirstConstruction=true;
	groupConstructionAndSerialize=false;
	gotDownloadComplete=false;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Connection_RM3::~Connection_RM3()
{
	unsigned int i;
	for (i=0; i < constructedReplicaList.Size(); i++)
		SLNet::OP_DELETE(constructedReplicaList[i], _FILE_AND_LINE_);
	for (i=0; i < queryToConstructReplicaList.Size(); i++)
		SLNet::OP_DELETE(queryToConstructReplicaList[i], _FILE_AND_LINE_);
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void Connection_RM3::GetConstructedReplicas(DataStructures::List<Replica3*> &objectsTheyDoHave)
{
	objectsTheyDoHave.Clear(true,_FILE_AND_LINE_);
	for (unsigned int idx=0; idx < constructedReplicaList.Size(); idx++)
	{
		objectsTheyDoHave.Push(constructedReplicaList[idx]->replica, _FILE_AND_LINE_ );
	}
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

bool Connection_RM3::HasReplicaConstructed(SLNet::Replica3 *replica)
{
	bool objectExists;
	constructedReplicaList.GetIndexFromKey(replica, &objectExists);
	return objectExists;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Connection_RM3::SendSerializeHeader(SLNet::Replica3 *replica, SLNet::Time timestamp, SLNet::BitStream *bs, WorldId worldId)
{
	bs->Reset();

	if (timestamp!=0)
	{
		bs->Write((MessageID)ID_TIMESTAMP);
		bs->Write(timestamp);
	}
	bs->Write((MessageID)ID_REPLICA_MANAGER_SERIALIZE);
	bs->Write(worldId);
	bs->Write(replica->GetNetworkID());
}
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Connection_RM3::ClearDownloadGroup(RakPeerInterface *rakPeerInterface)
{
	unsigned int i;
	for (i=0; i < downloadGroup.Size(); i++)
		rakPeerInterface->DeallocatePacket(downloadGroup[i]);
	downloadGroup.Clear(__FILE__,__LINE__);
}
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
SendSerializeIfChangedResult Connection_RM3::SendSerialize(SLNet::Replica3 *replica, bool indicesToSend[RM3_NUM_OUTPUT_BITSTREAM_CHANNELS], SLNet::BitStream serializationData[RM3_NUM_OUTPUT_BITSTREAM_CHANNELS], SLNet::Time timestamp, PRO sendParameters[RM3_NUM_OUTPUT_BITSTREAM_CHANNELS], RakPeerInterface *rakPeer, unsigned char worldId, SLNet::Time curTime)
{
	bool channelHasData;
	BitSize_t sum=0;
	for (int z=0; z < RM3_NUM_OUTPUT_BITSTREAM_CHANNELS; z++)
	{
		if (indicesToSend[z])
			sum+=serializationData[z].GetNumberOfBitsUsed();
	}

	SLNet::BitStream out;
	BitSize_t bitsPerChannel[RM3_NUM_OUTPUT_BITSTREAM_CHANNELS];

	if (sum==0)
	{
		memset(bitsPerChannel, 0, sizeof(bitsPerChannel));
		replica->OnSerializeTransmission(&out, this, bitsPerChannel, curTime);
		return SSICR_DID_NOT_SEND_DATA;
	}

	RakAssert(replica->GetNetworkID()!=UNASSIGNED_NETWORK_ID);

	BitSize_t bitsUsed;

	int channelIndex;
	PRO lastPro=sendParameters[0];

	for (channelIndex=0; channelIndex < RM3_NUM_OUTPUT_BITSTREAM_CHANNELS; channelIndex++)
	{
		if (channelIndex==0)
		{
			SendSerializeHeader(replica, timestamp, &out, worldId);
		}
		else if (lastPro!=sendParameters[channelIndex])
		{
			// Write out remainder
			for (int channelIndex2=channelIndex; channelIndex2 < RM3_NUM_OUTPUT_BITSTREAM_CHANNELS; channelIndex2++)
			{
				bitsPerChannel[channelIndex2]=0;
				out.Write(false);
			}

			// Send remainder
			replica->OnSerializeTransmission(&out, this, bitsPerChannel, curTime);
			rakPeer->Send(&out,lastPro.priority,lastPro.reliability,lastPro.orderingChannel,systemAddress,false,lastPro.sendReceipt);

			// If no data left to send, quit out
			bool anyData=false;
			for (int channelIndex2=channelIndex; channelIndex2 < RM3_NUM_OUTPUT_BITSTREAM_CHANNELS; channelIndex2++)
			{
				if (serializationData[channelIndex2].GetNumberOfBitsUsed()>0)
				{
					anyData=true;
					break;
				}
			}
			if (anyData==false)
				return SSICR_SENT_DATA;

			// Restart stream
			SendSerializeHeader(replica, timestamp, &out, worldId);

			for (int channelIndex2=0; channelIndex2 < channelIndex; channelIndex2++)
			{
				bitsPerChannel[channelIndex2]=0;
				out.Write(false);
			}
			lastPro=sendParameters[channelIndex];
		}

		bitsUsed=serializationData[channelIndex].GetNumberOfBitsUsed();
		channelHasData = indicesToSend[channelIndex]==true && bitsUsed>0;
		out.Write(channelHasData);
		if (channelHasData)
		{
			bitsPerChannel[channelIndex] = bitsUsed;
			out.WriteCompressed(bitsUsed);
			out.AlignWriteToByteBoundary();
			out.Write(serializationData[channelIndex]);
			// Crap, forgot this line, was a huge bug in that I'd only send to the first 3 systems
			serializationData[channelIndex].ResetReadPointer();
		}
		else
		{
			bitsPerChannel[channelIndex] = 0;
		}
	}
	replica->OnSerializeTransmission(&out, this, bitsPerChannel, curTime);
	rakPeer->Send(&out,lastPro.priority,lastPro.reliability,lastPro.orderingChannel,systemAddress,false,lastPro.sendReceipt);
	return SSICR_SENT_DATA;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

SendSerializeIfChangedResult Connection_RM3::SendSerializeIfChanged(LastSerializationResult *lsr, SerializeParameters *sp, SLNet::RakPeerInterface *rakPeer, unsigned char worldId, ReplicaManager3 *replicaManager, SLNet::Time curTime)
{
	SLNet::Replica3 *replica = lsr->replica;

	if (replica->GetNetworkID()==UNASSIGNED_NETWORK_ID)
		return SSICR_DID_NOT_SEND_DATA;

	RM3QuerySerializationResult rm3qsr = replica->QuerySerialization(this);
	if (rm3qsr==RM3QSR_NEVER_CALL_SERIALIZE)
	{
		// Never again for this connection and replica pair
		OnNeverSerialize(lsr, replicaManager);
		return SSICR_NEVER_SERIALIZE;
	}

	if (rm3qsr==RM3QSR_DO_NOT_CALL_SERIALIZE)
		return SSICR_DID_NOT_SEND_DATA;

	if (replica->forceSendUntilNextUpdate)
	{
		for (int z=0; z < RM3_NUM_OUTPUT_BITSTREAM_CHANNELS; z++)
		{
			if (replica->lastSentSerialization.indicesToSend[z])
				sp->bitsWrittenSoFar+=replica->lastSentSerialization.bitStream[z].GetNumberOfBitsUsed();
		}
		return SendSerialize(replica, replica->lastSentSerialization.indicesToSend, replica->lastSentSerialization.bitStream, sp->messageTimestamp, sp->pro, rakPeer, worldId, curTime);
	}

	for (int i=0; i < RM3_NUM_OUTPUT_BITSTREAM_CHANNELS; i++)
	{
		sp->outputBitstream[i].Reset();
		if (lsr->lastSerializationResultBS)
			sp->lastSentBitstream[i]=&lsr->lastSerializationResultBS->bitStream[i];
		else
			sp->lastSentBitstream[i]=&replica->lastSentSerialization.bitStream[i];
	}

	RM3SerializationResult serializationResult = replica->Serialize(sp);

	if (serializationResult==RM3SR_NEVER_SERIALIZE_FOR_THIS_CONNECTION)
	{
		// Never again for this connection and replica pair
		OnNeverSerialize(lsr, replicaManager);
		return SSICR_NEVER_SERIALIZE;
	}

	if (serializationResult==RM3SR_DO_NOT_SERIALIZE)
	{
		// Don't serialize this tick only
		return SSICR_DID_NOT_SEND_DATA;
	}

	// This is necessary in case the user in the Serialize() function for some reason read the bitstream they also wrote
	// WIthout this code, the Write calls to another bitstream would not write the entire bitstream
	BitSize_t sum=0;
	for (int z=0; z < RM3_NUM_OUTPUT_BITSTREAM_CHANNELS; z++)
	{
		sp->outputBitstream[z].ResetReadPointer();
		sum+=sp->outputBitstream[z].GetNumberOfBitsUsed();
	}

	if (sum==0)
	{
		// Don't serialize this tick only
		return SSICR_DID_NOT_SEND_DATA;
	}

	if (serializationResult==RM3SR_SERIALIZED_ALWAYS)
	{
		bool allIndices[RM3_NUM_OUTPUT_BITSTREAM_CHANNELS];
		for (int z=0; z < RM3_NUM_OUTPUT_BITSTREAM_CHANNELS; z++)
		{
			sp->bitsWrittenSoFar+=sp->outputBitstream[z].GetNumberOfBitsUsed();
			allIndices[z]=true;

			lsr->AllocBS();
			lsr->lastSerializationResultBS->bitStream[z].Reset();
			lsr->lastSerializationResultBS->bitStream[z].Write(&sp->outputBitstream[z]);
			sp->outputBitstream[z].ResetReadPointer();
		}
		return SendSerialize(replica, allIndices, sp->outputBitstream, sp->messageTimestamp, sp->pro, rakPeer, worldId, curTime);
	}

	if (serializationResult==RM3SR_SERIALIZED_ALWAYS_IDENTICALLY)
	{
		for (int z=0; z < RM3_NUM_OUTPUT_BITSTREAM_CHANNELS; z++)
		{
			replica->lastSentSerialization.indicesToSend[z]=sp->outputBitstream[z].GetNumberOfBitsUsed()>0;
			sp->bitsWrittenSoFar+=sp->outputBitstream[z].GetNumberOfBitsUsed();
			replica->lastSentSerialization.bitStream[z].Reset();
			replica->lastSentSerialization.bitStream[z].Write(&sp->outputBitstream[z]);
			sp->outputBitstream[z].ResetReadPointer();
			replica->forceSendUntilNextUpdate=true;
		}
		return SendSerialize(replica, replica->lastSentSerialization.indicesToSend, sp->outputBitstream, sp->messageTimestamp, sp->pro, rakPeer, worldId, curTime);
	}

	bool indicesToSend[RM3_NUM_OUTPUT_BITSTREAM_CHANNELS];
	if (serializationResult==RM3SR_BROADCAST_IDENTICALLY || serializationResult==RM3SR_BROADCAST_IDENTICALLY_FORCE_SERIALIZATION)
	{
		for (int z=0; z < RM3_NUM_OUTPUT_BITSTREAM_CHANNELS; z++)
		{
			if (sp->outputBitstream[z].GetNumberOfBitsUsed() > 0 &&
				(serializationResult==RM3SR_BROADCAST_IDENTICALLY_FORCE_SERIALIZATION ||
				((sp->outputBitstream[z].GetNumberOfBitsUsed()!=replica->lastSentSerialization.bitStream[z].GetNumberOfBitsUsed() ||
				memcmp(sp->outputBitstream[z].GetData(), replica->lastSentSerialization.bitStream[z].GetData(), sp->outputBitstream[z].GetNumberOfBytesUsed())!=0))))
			{
				indicesToSend[z]=true;
				replica->lastSentSerialization.indicesToSend[z]=true;
				sp->bitsWrittenSoFar+=sp->outputBitstream[z].GetNumberOfBitsUsed();
				replica->lastSentSerialization.bitStream[z].Reset();
				replica->lastSentSerialization.bitStream[z].Write(&sp->outputBitstream[z]);
				sp->outputBitstream[z].ResetReadPointer();
				replica->forceSendUntilNextUpdate=true;
			}
			else
			{
				indicesToSend[z]=false;
				replica->lastSentSerialization.indicesToSend[z]=false;
			}
		}
	}
	else
	{
		lsr->AllocBS();

		// RM3SR_SERIALIZED_UNIQUELY
		for (int z=0; z < RM3_NUM_OUTPUT_BITSTREAM_CHANNELS; z++)
		{
			if (sp->outputBitstream[z].GetNumberOfBitsUsed() > 0 &&
				(sp->outputBitstream[z].GetNumberOfBitsUsed()!=lsr->lastSerializationResultBS->bitStream[z].GetNumberOfBitsUsed() ||
				memcmp(sp->outputBitstream[z].GetData(), lsr->lastSerializationResultBS->bitStream[z].GetData(), sp->outputBitstream[z].GetNumberOfBytesUsed())!=0)
				)
			{
				indicesToSend[z]=true;
				sp->bitsWrittenSoFar+=sp->outputBitstream[z].GetNumberOfBitsUsed();
				lsr->lastSerializationResultBS->bitStream[z].Reset();
				lsr->lastSerializationResultBS->bitStream[z].Write(&sp->outputBitstream[z]);
				sp->outputBitstream[z].ResetReadPointer();
			}
			else
			{
				indicesToSend[z]=false;
			}
		}
	}


	if (serializationResult==RM3SR_BROADCAST_IDENTICALLY || serializationResult==RM3SR_BROADCAST_IDENTICALLY_FORCE_SERIALIZATION)
		replica->forceSendUntilNextUpdate=true;

	// Send out the data
	return SendSerialize(replica, indicesToSend, sp->outputBitstream, sp->messageTimestamp, sp->pro, rakPeer, worldId, curTime);
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Connection_RM3::OnLocalReference(Replica3* replica3, ReplicaManager3 *replicaManager)
{
	ConstructionMode curConstructionMode = QueryConstructionMode();
	RakAssert(curConstructionMode==QUERY_REPLICA_FOR_CONSTRUCTION || curConstructionMode==QUERY_REPLICA_FOR_CONSTRUCTION_AND_DESTRUCTION);
	RakAssert(replica3);
	(void) replicaManager;
	(void) curConstructionMode;

#ifdef _DEBUG
	for (unsigned int i=0; i < queryToConstructReplicaList.Size(); i++)
	{
		if (queryToConstructReplicaList[i]->replica==replica3)
		{
			RakAssert("replica added twice to queryToConstructReplicaList" && 0);
		}
	}

	if (constructedReplicaList.HasData(replica3)==true)
	{
		RakAssert("replica added to queryToConstructReplicaList when already in constructedReplicaList" && 0);
	}
#endif

	LastSerializationResult* lsr= SLNet::OP_NEW<LastSerializationResult>(_FILE_AND_LINE_);
	lsr->replica=replica3;
	queryToConstructReplicaList.Push(lsr,_FILE_AND_LINE_);
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void Connection_RM3::OnDereference(Replica3* replica3, ReplicaManager3 *replicaManager)
{
	ValidateLists(replicaManager);

	if (replica3->GetNetworkIDManager() == 0)
		return;

	LastSerializationResult* lsr=0;
	unsigned int idx;

	bool objectExists;
	idx=constructedReplicaList.GetIndexFromKey(replica3, &objectExists);
	if (objectExists)
	{
		lsr=constructedReplicaList[idx];
		constructedReplicaList.RemoveAtIndex(idx);
	}

	for (idx=0; idx < queryToConstructReplicaList.Size(); idx++)
	{
		if (queryToConstructReplicaList[idx]->replica==replica3)
		{
			lsr=queryToConstructReplicaList[idx];
			queryToConstructReplicaList.RemoveAtIndex(idx);
			break;
		}
	}

	for (idx=0; idx < queryToSerializeReplicaList.Size(); idx++)
	{
		if (queryToSerializeReplicaList[idx]->replica==replica3)
		{
			lsr=queryToSerializeReplicaList[idx];
			queryToSerializeReplicaList.RemoveAtIndex(idx);
			break;
		}
	}

	for (idx=0; idx < queryToDestructReplicaList.Size(); idx++)
	{
		if (queryToDestructReplicaList[idx]->replica==replica3)
		{
			lsr=queryToDestructReplicaList[idx];
			queryToDestructReplicaList.RemoveAtIndex(idx);
			break;
		}
	}

	ValidateLists(replicaManager);

	if (lsr)
		SLNet::OP_DELETE(lsr,_FILE_AND_LINE_);

	ValidateLists(replicaManager);
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void Connection_RM3::OnDownloadFromThisSystem(Replica3* replica3, ReplicaManager3 *replicaManager)
{
	RakAssert(replica3);

	ValidateLists(replicaManager);
	LastSerializationResult* lsr= SLNet::OP_NEW<LastSerializationResult>(_FILE_AND_LINE_);
	lsr->replica=replica3;

	ConstructionMode curConstructionMode = QueryConstructionMode();
	if (curConstructionMode==QUERY_REPLICA_FOR_CONSTRUCTION || curConstructionMode==QUERY_REPLICA_FOR_CONSTRUCTION_AND_DESTRUCTION)
	{
		unsigned int j;
		for (j=0; j < queryToConstructReplicaList.Size(); j++)
		{
			if (queryToConstructReplicaList[j]->replica==replica3 )
			{
				queryToConstructReplicaList.RemoveAtIndex(j);
				break;
			}
		}

		queryToDestructReplicaList.Push(lsr,_FILE_AND_LINE_);
	}

	if (constructedReplicaList.Insert(lsr->replica, lsr, true, _FILE_AND_LINE_) != (unsigned) -1)
	{
		//assert(queryToSerializeReplicaList.GetIndexOf(replica3)==(unsigned int)-1);
		queryToSerializeReplicaList.Push(lsr,_FILE_AND_LINE_);
	}

	ValidateLists(replicaManager);
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void Connection_RM3::OnDownloadFromOtherSystem(Replica3* replica3, ReplicaManager3 *replicaManager)
{
	ConstructionMode curConstructionMode = QueryConstructionMode();
	if (curConstructionMode==QUERY_REPLICA_FOR_CONSTRUCTION || curConstructionMode==QUERY_REPLICA_FOR_CONSTRUCTION_AND_DESTRUCTION)
	{
		unsigned int j;
		for (j=0; j < queryToConstructReplicaList.Size(); j++)
		{
			if (queryToConstructReplicaList[j]->replica==replica3 )
			{
				return;
			}
		}

		OnLocalReference(replica3, replicaManager);
	}
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void Connection_RM3::OnNeverConstruct(unsigned int queryToConstructIdx, ReplicaManager3 *replicaManager)
{
	ConstructionMode curConstructionMode = QueryConstructionMode();
	RakAssert(curConstructionMode==QUERY_REPLICA_FOR_CONSTRUCTION || curConstructionMode==QUERY_REPLICA_FOR_CONSTRUCTION_AND_DESTRUCTION);
	(void) curConstructionMode;

	ValidateLists(replicaManager);
	LastSerializationResult* lsr = queryToConstructReplicaList[queryToConstructIdx];
	queryToConstructReplicaList.RemoveAtIndex(queryToConstructIdx);
	SLNet::OP_DELETE(lsr,_FILE_AND_LINE_);
	ValidateLists(replicaManager);
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void Connection_RM3::OnConstructToThisConnection(unsigned int queryToConstructIdx, ReplicaManager3 *replicaManager)
{
	ConstructionMode curConstructionMode = QueryConstructionMode();
	RakAssert(curConstructionMode==QUERY_REPLICA_FOR_CONSTRUCTION || curConstructionMode==QUERY_REPLICA_FOR_CONSTRUCTION_AND_DESTRUCTION);
	(void) curConstructionMode;

	ValidateLists(replicaManager);
	LastSerializationResult* lsr = queryToConstructReplicaList[queryToConstructIdx];
	queryToConstructReplicaList.RemoveAtIndex(queryToConstructIdx);
	//assert(constructedReplicaList.GetIndexOf(lsr->replica)==(unsigned int)-1);
	constructedReplicaList.Insert(lsr->replica,lsr,true,_FILE_AND_LINE_);
	//assert(queryToDestructReplicaList.GetIndexOf(lsr->replica)==(unsigned int)-1);
	queryToDestructReplicaList.Push(lsr,_FILE_AND_LINE_);
	//assert(queryToSerializeReplicaList.GetIndexOf(lsr->replica)==(unsigned int)-1);
	queryToSerializeReplicaList.Push(lsr,_FILE_AND_LINE_);
	ValidateLists(replicaManager);
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void Connection_RM3::OnConstructToThisConnection(Replica3 *replica, ReplicaManager3 *replicaManager)
{
	RakAssert(replica);
	RakAssert(QueryConstructionMode()==QUERY_CONNECTION_FOR_REPLICA_LIST);
	(void) replicaManager;

	LastSerializationResult* lsr= SLNet::OP_NEW<LastSerializationResult>(_FILE_AND_LINE_);
	lsr->replica=replica;
	constructedReplicaList.Insert(replica,lsr,true,_FILE_AND_LINE_);
	queryToSerializeReplicaList.Push(lsr,_FILE_AND_LINE_);
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void Connection_RM3::OnNeverSerialize(LastSerializationResult *lsr, ReplicaManager3 *replicaManager)
{
	ValidateLists(replicaManager);

	unsigned int j;
	for (j=0; j < queryToSerializeReplicaList.Size(); j++)
	{
		if (queryToSerializeReplicaList[j]==lsr )
		{
			queryToSerializeReplicaList.RemoveAtIndex(j);
			break;
		}
	}

	ValidateLists(replicaManager);
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void Connection_RM3::OnReplicaAlreadyExists(unsigned int queryToConstructIdx, ReplicaManager3 *replicaManager)
{
	ConstructionMode curConstructionMode = QueryConstructionMode();
	RakAssert(curConstructionMode==QUERY_REPLICA_FOR_CONSTRUCTION || curConstructionMode==QUERY_REPLICA_FOR_CONSTRUCTION_AND_DESTRUCTION);
	(void) curConstructionMode;

	ValidateLists(replicaManager);
	LastSerializationResult* lsr = queryToConstructReplicaList[queryToConstructIdx];
	queryToConstructReplicaList.RemoveAtIndex(queryToConstructIdx);
	//assert(constructedReplicaList.GetIndexOf(lsr->replica)==(unsigned int)-1);
	constructedReplicaList.Insert(lsr->replica,lsr,true,_FILE_AND_LINE_);
	//assert(queryToDestructReplicaList.GetIndexOf(lsr->replica)==(unsigned int)-1);
	queryToDestructReplicaList.Push(lsr,_FILE_AND_LINE_);
	//assert(queryToSerializeReplicaList.GetIndexOf(lsr->replica)==(unsigned int)-1);
	queryToSerializeReplicaList.Push(lsr,_FILE_AND_LINE_);
	ValidateLists(replicaManager);
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void Connection_RM3::OnDownloadExisting(Replica3* replica3, ReplicaManager3 *replicaManager)
{
	ValidateLists(replicaManager);

	ConstructionMode curConstructionMode = QueryConstructionMode();
	if (curConstructionMode==QUERY_REPLICA_FOR_CONSTRUCTION || curConstructionMode==QUERY_REPLICA_FOR_CONSTRUCTION_AND_DESTRUCTION)
	{
		unsigned int idx;
		for (idx=0; idx < queryToConstructReplicaList.Size(); idx++)
		{
			if (queryToConstructReplicaList[idx]->replica==replica3)
			{
				OnConstructToThisConnection(idx, replicaManager);
				return;
			}
		}
	}
	else
	{
		OnConstructToThisConnection(replica3, replicaManager);
	}
}
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void Connection_RM3::OnSendDestructionFromQuery(unsigned int queryToDestructIdx, ReplicaManager3 *replicaManager)
{
	ConstructionMode curConstructionMode = QueryConstructionMode();
	RakAssert(curConstructionMode==QUERY_REPLICA_FOR_CONSTRUCTION || curConstructionMode==QUERY_REPLICA_FOR_CONSTRUCTION_AND_DESTRUCTION);
	(void) curConstructionMode;

	ValidateLists(replicaManager);
	LastSerializationResult* lsr = queryToDestructReplicaList[queryToDestructIdx];
	queryToDestructReplicaList.RemoveAtIndex(queryToDestructIdx);
	unsigned int j;
	for (j=0; j < queryToSerializeReplicaList.Size(); j++)
	{
		if (queryToSerializeReplicaList[j]->replica==lsr->replica )
		{
			queryToSerializeReplicaList.RemoveAtIndex(j);
			break;
		}
	}
	for (j=0; j < constructedReplicaList.Size(); j++)
	{
		if (constructedReplicaList[j]->replica==lsr->replica )
		{
			constructedReplicaList.RemoveAtIndex(j);
			break;
		}
	}
	//assert(queryToConstructReplicaList.GetIndexOf(lsr->replica)==(unsigned int)-1);
	queryToConstructReplicaList.Push(lsr,_FILE_AND_LINE_);
	ValidateLists(replicaManager);
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void Connection_RM3::OnDoNotQueryDestruction(unsigned int queryToDestructIdx, ReplicaManager3 *replicaManager)
{
	ValidateLists(replicaManager);
	queryToDestructReplicaList.RemoveAtIndex(queryToDestructIdx);
	ValidateLists(replicaManager);
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void Connection_RM3::ValidateLists(ReplicaManager3 *replicaManager) const
{
	(void) replicaManager;
	/*
#ifdef _DEBUG
	// Each object should exist only once in either constructedReplicaList or queryToConstructReplicaList
	// replicaPointer from LastSerializationResult should be same among all lists
	unsigned int idx, idx2;
	for (idx=0; idx < constructedReplicaList.Size(); idx++)
	{
		idx2=queryToConstructReplicaList.GetIndexOf(constructedReplicaList[idx]->replica);
		if (idx2!=(unsigned int)-1)
		{
			int a=5;
			assert(a==0);
			int *b=0;
			*b=5;
		}
	}

	for (idx=0; idx < queryToConstructReplicaList.Size(); idx++)
	{
		idx2=constructedReplicaList.GetIndexOf(queryToConstructReplicaList[idx]->replica);
		if (idx2!=(unsigned int)-1)
		{
			int a=5;
			assert(a==0);
			int *b=0;
			*b=5;
		}
	}

	LastSerializationResult *lsr, *lsr2;
	for (idx=0; idx < constructedReplicaList.Size(); idx++)
	{
		lsr=constructedReplicaList[idx];

		idx2=queryToSerializeReplicaList.GetIndexOf(lsr->replica);
		if (idx2!=(unsigned int)-1)
		{
			lsr2=queryToSerializeReplicaList[idx2];
			if (lsr2!=lsr)
			{
				int a=5;
				assert(a==0);
				int *b=0;
				*b=5;
			}
		}

		idx2=queryToDestructReplicaList.GetIndexOf(lsr->replica);
		if (idx2!=(unsigned int)-1)
		{
			lsr2=queryToDestructReplicaList[idx2];
			if (lsr2!=lsr)
			{
				int a=5;
				assert(a==0);
				int *b=0;
				*b=5;
			}
		}
	}
	for (idx=0; idx < queryToConstructReplicaList.Size(); idx++)
	{
		lsr=queryToConstructReplicaList[idx];

		idx2=queryToSerializeReplicaList.GetIndexOf(lsr->replica);
		if (idx2!=(unsigned int)-1)
		{
			lsr2=queryToSerializeReplicaList[idx2];
			if (lsr2!=lsr)
			{
				int a=5;
				assert(a==0);
				int *b=0;
				*b=5;
			}
		}

		idx2=queryToDestructReplicaList.GetIndexOf(lsr->replica);
		if (idx2!=(unsigned int)-1)
		{
			lsr2=queryToDestructReplicaList[idx2];
			if (lsr2!=lsr)
			{
				int a=5;
				assert(a==0);
				int *b=0;
				*b=5;
			}
		}
	}

	// Verify pointer integrity
	for (idx=0; idx < constructedReplicaList.Size(); idx++)
	{
		if (constructedReplicaList[idx]->replica->replicaManager!=replicaManager)
		{
			int a=5;
			assert(a==0);
			int *b=0;
			*b=5;
		}
	}

	// Verify pointer integrity
	for (idx=0; idx < queryToConstructReplicaList.Size(); idx++)
	{
		if (queryToConstructReplicaList[idx]->replica->replicaManager!=replicaManager)
		{
			int a=5;
			assert(a==0);
			int *b=0;
			*b=5;
		}
	}
#endif
	*/
}
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void Connection_RM3::SendConstruction(DataStructures::List<Replica3*> &newObjects, DataStructures::List<Replica3*> &deletedObjects, PRO sendParameters, SLNet::RakPeerInterface *rakPeer, unsigned char worldId, ReplicaManager3 *replicaManager3)
{
	if (newObjects.Size()==0 && deletedObjects.Size()==0)
		return;

	// All construction and destruction takes place in the same network message
	// Otherwise, if objects rely on each other being created the same tick to be valid, this won't always be true
	//	DataStructures::List<LastSerializationResult* > serializedObjects;
	BitSize_t offsetStart, offsetStart2, offsetEnd;
	unsigned int newListIndex, oldListIndex;
	SLNet::BitStream bsOut;
	NetworkID networkId;
	if (isFirstConstruction)
	{
		bsOut.Write((MessageID)ID_REPLICA_MANAGER_DOWNLOAD_STARTED);
		bsOut.Write(worldId);
		SerializeOnDownloadStarted(&bsOut);
		rakPeer->Send(&bsOut,sendParameters.priority,RELIABLE_ORDERED,sendParameters.orderingChannel,systemAddress,false,sendParameters.sendReceipt);
	}

	//	LastSerializationResult* lsr;
	bsOut.Reset();
	bsOut.Write((MessageID)ID_REPLICA_MANAGER_CONSTRUCTION);
	bsOut.Write(worldId);
	uint16_t objectSize = (uint16_t) newObjects.Size();
	bsOut.Write(objectSize);

	// Construction
	for (newListIndex=0; newListIndex < newObjects.Size(); newListIndex++)
	{
		offsetStart=bsOut.GetWriteOffset();
		bsOut.Write(offsetStart); // overwritten to point to the end of the stream
		networkId=newObjects[newListIndex]->GetNetworkID();
		bsOut.Write(networkId);

		RM3ConstructionState cs = newObjects[newListIndex]->QueryConstruction(this, replicaManager3);
		bool actuallyCreateObject = cs==RM3CS_SEND_CONSTRUCTION;
		bsOut.Write(actuallyCreateObject);
		bsOut.AlignWriteToByteBoundary();

		if (actuallyCreateObject)
		{
			// Actually create the object
			bsOut.Write(newObjects[newListIndex]->creatingSystemGUID);
			offsetStart2=bsOut.GetWriteOffset();
			bsOut.Write(offsetStart2); // overwritten to point to after the call to WriteAllocationID
			bsOut.AlignWriteToByteBoundary(); // Give the user an aligned bitStream in case they use memcpy
			newObjects[newListIndex]->WriteAllocationID(this, &bsOut);
			bsOut.AlignWriteToByteBoundary();  // Give the user an aligned bitStream in case they use memcpy
			offsetEnd=bsOut.GetWriteOffset();
			bsOut.SetWriteOffset(offsetStart2);
			bsOut.Write(offsetEnd);
			bsOut.SetWriteOffset(offsetEnd);
			newObjects[newListIndex]->SerializeConstruction(&bsOut, this);
		}
		else
		{
			newObjects[newListIndex]->SerializeConstructionExisting(&bsOut, this);
		}

		bsOut.AlignWriteToByteBoundary();
		offsetEnd=bsOut.GetWriteOffset();
		bsOut.SetWriteOffset(offsetStart);
		bsOut.Write(offsetEnd);
		bsOut.SetWriteOffset(offsetEnd);
	}

	SLNet::BitStream bsOut2;
	for (newListIndex=0; newListIndex < newObjects.Size(); newListIndex++)
	{
		bsOut2.Reset();
		RM3ConstructionState cs = newObjects[newListIndex]->QueryConstruction(this, replicaManager3);
		if (cs==RM3CS_SEND_CONSTRUCTION)
		{
			newObjects[newListIndex]->PostSerializeConstruction(&bsOut2, this);
		}
		else
		{
			RakAssert(cs==RM3CS_ALREADY_EXISTS_REMOTELY);
			newObjects[newListIndex]->PostSerializeConstructionExisting(&bsOut2, this);
		}
		if (bsOut2.GetNumberOfBitsUsed()>0)
		{
			bsOut.Write(true);
			bsOut.AlignWriteToByteBoundary();
			offsetStart=bsOut.GetWriteOffset();
			bsOut.Write(offsetStart); // overwritten to point to the end of the stream
			networkId=newObjects[newListIndex]->GetNetworkID();
			bsOut.Write(networkId);
			bsOut.AlignWriteToByteBoundary(); // Give the user an aligned bitStream in case they use memcpy
			bsOut.Write(&bsOut2);
			bsOut.AlignWriteToByteBoundary(); // Give the user an aligned bitStream in case they use memcpy
			offsetEnd=bsOut.GetWriteOffset();
			bsOut.SetWriteOffset(offsetStart);
			bsOut.Write(offsetEnd);
			bsOut.SetWriteOffset(offsetEnd);
		}
		else
			bsOut.Write(false);
	}
	bsOut.AlignWriteToByteBoundary();

	// Destruction
	objectSize = (uint16_t) deletedObjects.Size();
	bsOut.Write(objectSize);
	for (oldListIndex=0; oldListIndex < deletedObjects.Size(); oldListIndex++)
	{
		networkId=deletedObjects[oldListIndex]->GetNetworkID();
		bsOut.Write(networkId);
		offsetStart=bsOut.GetWriteOffset();
		bsOut.Write(offsetStart);
		deletedObjects[oldListIndex]->deletingSystemGUID=rakPeer->GetGuidFromSystemAddress(UNASSIGNED_SYSTEM_ADDRESS);
		bsOut.Write(deletedObjects[oldListIndex]->deletingSystemGUID);
		deletedObjects[oldListIndex]->SerializeDestruction(&bsOut, this);
		bsOut.AlignWriteToByteBoundary();
		offsetEnd=bsOut.GetWriteOffset();
		bsOut.SetWriteOffset(offsetStart);
		bsOut.Write(offsetEnd);
		bsOut.SetWriteOffset(offsetEnd);
	}
	rakPeer->Send(&bsOut,sendParameters.priority,RELIABLE_ORDERED,sendParameters.orderingChannel,systemAddress,false,sendParameters.sendReceipt);

	// TODO - shouldn't this be part of construction?

	// Initial Download serialize to a new system
	// Immediately send serialize after construction if the replica object already has saved data
	// If the object was serialized identically, and does not change later on, then the new connection never gets the data
	SerializeParameters sp;
	sp.whenLastSerialized=0;
	SLNet::BitStream emptyBs;
	for (int index=0; index < RM3_NUM_OUTPUT_BITSTREAM_CHANNELS; index++)
	{
		sp.lastSentBitstream[index]=&emptyBs;
		sp.pro[index]=sendParameters;
		sp.pro[index].reliability=RELIABLE_ORDERED;
	}

	sp.bitsWrittenSoFar=0;
//	SLNet::Time t = SLNet::GetTimeMS();
	for (newListIndex=0; newListIndex < newObjects.Size(); newListIndex++)
	{
		sp.destinationConnection=this;
		sp.messageTimestamp=0;
		SLNet::Replica3 *replica = newObjects[newListIndex];
		// 8/22/09 Forgot ResetWritePointer
		for (int z=0; z < RM3_NUM_OUTPUT_BITSTREAM_CHANNELS; z++)
		{
			sp.outputBitstream[z].ResetWritePointer();
		}

		RM3SerializationResult res = replica->Serialize(&sp);
		if (res!=RM3SR_NEVER_SERIALIZE_FOR_THIS_CONNECTION &&
			res!=RM3SR_DO_NOT_SERIALIZE &&
			res!=RM3SR_SERIALIZED_UNIQUELY)
		{
			bool allIndices[RM3_NUM_OUTPUT_BITSTREAM_CHANNELS];
			for (int z=0; z < RM3_NUM_OUTPUT_BITSTREAM_CHANNELS; z++)
			{
				sp.bitsWrittenSoFar+=sp.outputBitstream[z].GetNumberOfBitsUsed();
				allIndices[z]=true;
			}
			SendSerialize(replica, allIndices, sp.outputBitstream, sp.messageTimestamp, sp.pro, rakPeer, worldId, GetTime());
///			newObjects[newListIndex]->whenLastSerialized=t;

		}
		// else wait for construction request accepted before serializing
	}

	if (isFirstConstruction)
	{
		bsOut.Reset();
		bsOut.Write((MessageID)ID_REPLICA_MANAGER_DOWNLOAD_COMPLETE);
		bsOut.Write(worldId);
		SerializeOnDownloadComplete(&bsOut);
		rakPeer->Send(&bsOut,sendParameters.priority,RELIABLE_ORDERED,sendParameters.orderingChannel,systemAddress,false,sendParameters.sendReceipt);
	}

	isFirstConstruction=false;

}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void Connection_RM3::SendValidation(SLNet::RakPeerInterface *rakPeer, WorldId worldId)
{
	// Hijack to mean sendValidation
	SLNet::BitStream bsOut;
	bsOut.Write((MessageID)ID_REPLICA_MANAGER_SCOPE_CHANGE);
	bsOut.Write(worldId);
	rakPeer->Send(&bsOut,HIGH_PRIORITY,RELIABLE_ORDERED,0,systemAddress,false);
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Replica3::Replica3()
{
	creatingSystemGUID=UNASSIGNED_RAKNET_GUID;
	deletingSystemGUID=UNASSIGNED_RAKNET_GUID;
	replicaManager=0;
	forceSendUntilNextUpdate=false;
	lsr=0;
	referenceIndex = (uint32_t)-1;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Replica3::~Replica3()
{
	if (replicaManager)
	{
		replicaManager->Dereference(this);
	}
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void Replica3::BroadcastDestruction(void)
{
	replicaManager->BroadcastDestruction(this,UNASSIGNED_SYSTEM_ADDRESS);
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

RakNetGUID Replica3::GetCreatingSystemGUID(void) const
{
	return creatingSystemGUID;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

RM3ConstructionState Replica3::QueryConstruction_ClientConstruction(SLNet::Connection_RM3 *destinationConnection, bool isThisTheServer)
{
	(void) destinationConnection;
	if (creatingSystemGUID==replicaManager->GetRakPeerInterface()->GetGuidFromSystemAddress(UNASSIGNED_SYSTEM_ADDRESS))
		return RM3CS_SEND_CONSTRUCTION;
	// Send back to the owner client too, because they couldn't assign the network ID
	if (isThisTheServer)
		return RM3CS_SEND_CONSTRUCTION;
	return RM3CS_NEVER_CONSTRUCT;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

bool Replica3::QueryRemoteConstruction_ClientConstruction(SLNet::Connection_RM3 *sourceConnection, bool isThisTheServer)
{
	(void) sourceConnection;
	(void) isThisTheServer;

	// OK to create
	return true;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

RM3ConstructionState Replica3::QueryConstruction_ServerConstruction(SLNet::Connection_RM3 *destinationConnection, bool isThisTheServer)
{
	(void) destinationConnection;

	if (isThisTheServer)
		return RM3CS_SEND_CONSTRUCTION;
	return RM3CS_NEVER_CONSTRUCT;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

bool Replica3::QueryRemoteConstruction_ServerConstruction(SLNet::Connection_RM3 *sourceConnection, bool isThisTheServer)
{
	(void) sourceConnection;
	if (isThisTheServer)
		return false;
	return true;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

RM3ConstructionState Replica3::QueryConstruction_PeerToPeer(SLNet::Connection_RM3 *destinationConnection, Replica3P2PMode p2pMode)
{
	(void) destinationConnection;

	if (p2pMode==R3P2PM_SINGLE_OWNER)
	{
		// We send to all, others do nothing
		if (creatingSystemGUID==replicaManager->GetRakPeerInterface()->GetGuidFromSystemAddress(UNASSIGNED_SYSTEM_ADDRESS))
			return RM3CS_SEND_CONSTRUCTION;

		// RM3CS_NEVER_CONSTRUCT will not send the object, and will not Serialize() it
		return RM3CS_NEVER_CONSTRUCT;
	}
	else if (p2pMode==R3P2PM_MULTI_OWNER_CURRENTLY_AUTHORITATIVE)
	{
		return RM3CS_SEND_CONSTRUCTION;
	}
	else if (p2pMode==R3P2PM_STATIC_OBJECT_CURRENTLY_AUTHORITATIVE)
	{
		return RM3CS_ALREADY_EXISTS_REMOTELY;
	}
	else if (p2pMode==R3P2PM_STATIC_OBJECT_NOT_CURRENTLY_AUTHORITATIVE)
	{
		return RM3CS_ALREADY_EXISTS_REMOTELY_DO_NOT_CONSTRUCT;
	}
	else
	{
		RakAssert(p2pMode==R3P2PM_MULTI_OWNER_NOT_CURRENTLY_AUTHORITATIVE);

		// RM3CS_ALREADY_EXISTS_REMOTELY will not send the object, but WILL call QuerySerialization() and Serialize() on it.
		return RM3CS_ALREADY_EXISTS_REMOTELY;
	}
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

bool Replica3::QueryRemoteConstruction_PeerToPeer(SLNet::Connection_RM3 *sourceConnection)
{
	(void) sourceConnection;

	return true;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

RM3QuerySerializationResult Replica3::QuerySerialization_ClientSerializable(SLNet::Connection_RM3 *destinationConnection, bool isThisTheServer)
{
	// Owner client sends to all
	if (creatingSystemGUID==replicaManager->GetRakPeerInterface()->GetGuidFromSystemAddress(UNASSIGNED_SYSTEM_ADDRESS))
		return RM3QSR_CALL_SERIALIZE;
	// Server sends to all but owner client
	if (isThisTheServer && destinationConnection->GetRakNetGUID()!=creatingSystemGUID)
		return RM3QSR_CALL_SERIALIZE;
	// Remote clients do not send
	return RM3QSR_NEVER_CALL_SERIALIZE;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

RM3QuerySerializationResult Replica3::QuerySerialization_ServerSerializable(SLNet::Connection_RM3 *destinationConnection, bool isThisTheServer)
{
	(void) destinationConnection;
	// Server sends to all
	if (isThisTheServer)
		return RM3QSR_CALL_SERIALIZE;

	// Clients do not send
	return RM3QSR_NEVER_CALL_SERIALIZE;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

RM3QuerySerializationResult Replica3::QuerySerialization_PeerToPeer(SLNet::Connection_RM3 *destinationConnection, Replica3P2PMode p2pMode)
{
	(void) destinationConnection;

	if (p2pMode==R3P2PM_SINGLE_OWNER)
	{
		// Owner peer sends to all
		if (creatingSystemGUID==replicaManager->GetRakPeerInterface()->GetGuidFromSystemAddress(UNASSIGNED_SYSTEM_ADDRESS))
			return RM3QSR_CALL_SERIALIZE;

		// Remote peers do not send
		return RM3QSR_NEVER_CALL_SERIALIZE;
	}
	else if (p2pMode==R3P2PM_MULTI_OWNER_CURRENTLY_AUTHORITATIVE)
	{
		return RM3QSR_CALL_SERIALIZE;
	}
	else if (p2pMode==R3P2PM_STATIC_OBJECT_CURRENTLY_AUTHORITATIVE)
	{
		return RM3QSR_CALL_SERIALIZE;
	}
	else if (p2pMode==R3P2PM_STATIC_OBJECT_NOT_CURRENTLY_AUTHORITATIVE)
	{
		return RM3QSR_DO_NOT_CALL_SERIALIZE;
	}
	else
	{
		RakAssert(p2pMode==R3P2PM_MULTI_OWNER_NOT_CURRENTLY_AUTHORITATIVE);
		return RM3QSR_DO_NOT_CALL_SERIALIZE;
	}
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

RM3ActionOnPopConnection Replica3::QueryActionOnPopConnection_Client(SLNet::Connection_RM3 *droppedConnection) const
{
	(void) droppedConnection;
	return RM3AOPC_DELETE_REPLICA;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

RM3ActionOnPopConnection Replica3::QueryActionOnPopConnection_Server(SLNet::Connection_RM3 *droppedConnection) const
{
	(void) droppedConnection;
	return RM3AOPC_DELETE_REPLICA_AND_BROADCAST_DESTRUCTION;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

RM3ActionOnPopConnection Replica3::QueryActionOnPopConnection_PeerToPeer(SLNet::Connection_RM3 *droppedConnection) const
{
	(void) droppedConnection;
	return RM3AOPC_DELETE_REPLICA;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#endif // _RAKNET_SUPPORT_*
