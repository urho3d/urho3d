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

/// \file CloudServer.h
/// \brief Stores client data, and allows cross-server communication to retrieve this data
/// \details TODO
///


#include "NativeFeatureIncludes.h"
#if _RAKNET_SUPPORT_CloudServer==1

#ifndef __CLOUD_SERVER_H
#define __CLOUD_SERVER_H

#include "PluginInterface2.h"
#include "memoryoverride.h"
#include "NativeTypes.h"
#include "string.h"
#include "DS_Hash.h"
#include "CloudCommon.h"
#include "DS_OrderedList.h"

/// If the data is smaller than this value, an allocation is avoid. However, this value exists for every row
#define CLOUD_SERVER_DATA_STACK_SIZE 32

namespace SLNet
{
/// Forward declarations
class RakPeerInterface;

/// \brief Zero or more instances of CloudServerQueryFilter can be attached to CloudServer to restrict client queries
/// All attached instances of CloudServerQueryFilter on each corresponding operation, from all directly connected clients
/// If any attached instance returns false for a given operation, that operation is silently rejected
/// \ingroup CLOUD_GROUP
class RAK_DLL_EXPORT CloudServerQueryFilter
{
public:
	CloudServerQueryFilter() {}
	virtual ~CloudServerQueryFilter() {}

	/// Called when a local client wants to post data
	/// \return true to allow, false to reject
	virtual bool OnPostRequest(RakNetGUID clientGuid, SystemAddress clientAddress, CloudKey key, uint32_t dataLength, const char *data)=0;

	/// Called when a local client wants to release data that it has previously uploaded
	/// \return true to allow, false to reject
	virtual bool OnReleaseRequest(RakNetGUID clientGuid, SystemAddress clientAddress, DataStructures::List<CloudKey> &cloudKeys)=0;

	/// Called when a local client wants to query data
	/// If you return false, the client will get no response at all
	/// \return true to allow, false to reject
	virtual bool OnGetRequest(RakNetGUID clientGuid, SystemAddress clientAddress, CloudQuery &query, DataStructures::List<RakNetGUID> &specificSystems)=0;

	/// Called when a local client wants to stop getting updates for data
	/// If you return false, the client will keep getting updates for that data
	/// \return true to allow, false to reject
	virtual bool OnUnsubscribeRequest(RakNetGUID clientGuid, SystemAddress clientAddress, DataStructures::List<CloudKey> &cloudKeys, DataStructures::List<RakNetGUID> &specificSystems)=0;
};

/// \brief Stores client data, and allows cross-server communication to retrieve this data
/// \ingroup CLOUD_GROUP
class RAK_DLL_EXPORT CloudServer : public PluginInterface2, CloudAllocator
{
public:
	// GetInstance() and DestroyInstance(instance*)
	STATIC_FACTORY_DECLARATIONS(CloudServer)

	CloudServer();
	virtual ~CloudServer();

	/// \brief Max bytes a client can upload
	/// Data in excess of this value is silently ignored
	/// defaults to 0 (unlimited)
	/// \param[in] bytes Max bytes a client can upload. 0 means unlimited.
	void SetMaxUploadBytesPerClient(uint64_t bytes);

	/// \brief Max bytes returned by a download. If the number of bytes would exceed this amount, the returned list is truncated
	/// However, if this would result in no rows downloaded, then one row will be returned.
	/// \param[in] bytes Max bytes a client can download from a single Get(). 0 means unlimited.
	void SetMaxBytesPerDownload(uint64_t bytes);

	/// \brief Add a server, which is assumed to be connected in a fully connected mesh to all other servers and also running the CloudServer plugin
	/// The other system must also call AddServer before getting the subscription data, or it will be rejected.
	/// Sending a message telling the other system to call AddServer(), followed by calling AddServer() locally, would be sufficient for this to work.
	/// \note This sends subscription data to the other system, using RELIABLE_ORDERED on channel 0
	/// \param[in] systemIdentifier Identifier of the remote system
	void AddServer(RakNetGUID systemIdentifier);

	/// \brief Removes a server added through AddServer()
	/// \param[in] systemIdentifier Identifier of the remote system
	void RemoveServer(RakNetGUID systemIdentifier);

	/// Return list of servers added with AddServer()
	/// \param[out] remoteServers List of servers added
	void GetRemoteServers(DataStructures::List<RakNetGUID> &remoteServersOut);

	/// \brief Frees all memory. Does not remove query filters
	void Clear(void);

	/// \brief Report the specified SystemAddress to client queries, rather than what RakPeer reads.
	/// This is useful if you already know your public IP
	/// This only applies to future updates, so call it before updating to apply to all queries
	/// \param[in] forcedAddress The systmeAddress to return in queries. Use UNASSIGNED_SYSTEM_ADDRESS (default) to use what RakPeer returns
	void ForceExternalSystemAddress(SystemAddress forcedAddress);

	/// \brief Adds a callback called on each query. If all filters returns true for an operation, the operation is allowed.
	/// If the filter was already added, the function silently fails
	/// \param[in] filter An externally allocated instance of CloudServerQueryFilter. The instance must remain valid until it is removed with RemoveQueryFilter() or RemoveAllQueryFilters()
	void AddQueryFilter(CloudServerQueryFilter* filter);

	/// \brief Removes a callback added with AddQueryFilter()
	/// The instance is not deleted, only unreferenced. It is up to the user to delete the instance, if necessary
	/// \param[in] filter An externally allocated instance of CloudServerQueryFilter. The instance must remain valid until it is removed with RemoveQueryFilter() or RemoveAllQueryFilters()
	void RemoveQueryFilter(CloudServerQueryFilter* filter);

	/// \brief Removes all instances of CloudServerQueryFilter added with AddQueryFilter().
	/// The instances are not deleted, only unreferenced. It is up to the user to delete the instances, if necessary
	void RemoveAllQueryFilters(void);

protected:
	virtual void Update(void);
	virtual PluginReceiveResult OnReceive(Packet *packet);
	virtual void OnClosedConnection(const SystemAddress &systemAddress, RakNetGUID rakNetGUID, PI2_LostConnectionReason lostConnectionReason );
	virtual void OnRakPeerShutdown(void);


	virtual void OnPostRequest(Packet *packet);
	virtual void OnReleaseRequest(Packet *packet);
	virtual void OnGetRequest(Packet *packet);
	virtual void OnUnsubscribeRequest(Packet *packet);
	virtual void OnServerToServerGetRequest(Packet *packet);
	virtual void OnServerToServerGetResponse(Packet *packet);

	uint64_t maxUploadBytesPerClient, maxBytesPerDowload;

	// ----------------------------------------------------------------------------
	// For a given data key, quickly look up one or all systems that have uploaded
	// ----------------------------------------------------------------------------
	struct CloudData
	{
		CloudData() {}
		~CloudData() {if (allocatedData) rakFree_Ex(allocatedData, _FILE_AND_LINE_);}
		bool IsUnused(void) const {return isUploaded==false && specificSubscribers.Size()==0;}
		void Clear(void) {if (dataPtr==allocatedData) rakFree_Ex(allocatedData, _FILE_AND_LINE_); allocatedData=0; dataPtr=0; dataLengthBytes=0; isUploaded=false;}

		unsigned char stackData[CLOUD_SERVER_DATA_STACK_SIZE];
		unsigned char *allocatedData; // Uses allocatedData instead of stackData if length of data exceeds CLOUD_SERVER_DATA_STACK_SIZE
		unsigned char *dataPtr; // Points to either stackData or allocatedData
		uint32_t dataLengthBytes;
		bool isUploaded;

		/// System address of server that is holding this data, and the client is connected to
		SystemAddress serverSystemAddress;

		/// System address of client that uploaded this data
		SystemAddress clientSystemAddress;

		/// RakNetGUID of server that is holding this data, and the client is connected to
		RakNetGUID serverGUID;

		/// RakNetGUID of client that uploaded this data
		RakNetGUID clientGUID;

		/// When the key data changes from this particular system, notify these subscribers
		/// This list mutually exclusive with CloudDataList::nonSpecificSubscribers
		DataStructures::OrderedList<RakNetGUID, RakNetGUID> specificSubscribers;
	};
	void WriteCloudQueryRowFromResultList(unsigned int i, DataStructures::List<CloudData*> &cloudDataResultList, DataStructures::List<CloudKey> &cloudKeyResultList, BitStream *bsOut);
	void WriteCloudQueryRowFromResultList(DataStructures::List<CloudData*> &cloudDataResultList, DataStructures::List<CloudKey> &cloudKeyResultList, BitStream *bsOut);

	static int KeyDataPtrComp( const RakNetGUID &key, CloudData* const &data );
	struct CloudDataList
	{
		bool IsUnused(void) const {return keyData.Size()==0 && nonSpecificSubscribers.Size()==0;}
		bool IsNotUploaded(void) const {return uploaderCount==0;}
		bool RemoveSubscriber(RakNetGUID g) {
			bool objectExists;
			unsigned int index;
			index = nonSpecificSubscribers.GetIndexFromKey(g, &objectExists);
			if (objectExists)
			{
				subscriberCount--;
				nonSpecificSubscribers.RemoveAtIndex(index);
				return true;
			}
			return false;
		}

		unsigned int uploaderCount, subscriberCount;
		CloudKey key;

		// Data uploaded from or subscribed to for various systems
		DataStructures::OrderedList<RakNetGUID, CloudData*, CloudServer::KeyDataPtrComp> keyData;

		/// When the key data changes from any system, notify these subscribers
		/// This list mutually exclusive with CloudData::specificSubscribers
		DataStructures::OrderedList<RakNetGUID, RakNetGUID> nonSpecificSubscribers;
	};

	static int KeyDataListComp( const CloudKey &key, CloudDataList * const &data );
	DataStructures::OrderedList<CloudKey, CloudDataList*, CloudServer::KeyDataListComp> dataRepository;

	struct KeySubscriberID
	{
		CloudKey key;
		DataStructures::OrderedList<RakNetGUID, RakNetGUID> specificSystemsSubscribedTo;
	};
	static int KeySubscriberIDComp(const CloudKey &key, KeySubscriberID * const &data );

	// Remote systems
	struct RemoteCloudClient
	{
		bool IsUnused(void) const {return uploadedKeys.Size()==0 && subscribedKeys.Size()==0;}

		DataStructures::OrderedList<CloudKey,CloudKey,CloudKeyComp> uploadedKeys;
		DataStructures::OrderedList<CloudKey,KeySubscriberID*,CloudServer::KeySubscriberIDComp> subscribedKeys;
		uint64_t uploadedBytes;
	};
	DataStructures::Hash<RakNetGUID, RemoteCloudClient*, 2048, RakNetGUID::ToUint32> remoteSystems;

	// For a given user, release all subscribed and uploaded keys
	void ReleaseSystem(RakNetGUID clientAddress );

	// For a given user, release a set of keys
	void ReleaseKeys(RakNetGUID clientAddress, DataStructures::List<CloudKey> &keys );

	void NotifyClientSubscribersOfDataChange( CloudData *cloudData, CloudKey &key, DataStructures::OrderedList<RakNetGUID, RakNetGUID> &subscribers, bool wasUpdated );
	void NotifyClientSubscribersOfDataChange( CloudQueryRow *row, DataStructures::OrderedList<RakNetGUID, RakNetGUID> &subscribers, bool wasUpdated );
	void NotifyServerSubscribersOfDataChange( CloudData *cloudData, CloudKey &key, bool wasUpdated );

	struct RemoteServer
	{
		RakNetGUID serverAddress;
		// This server needs to know about these keys when they are updated or deleted
		DataStructures::OrderedList<CloudKey,CloudKey,CloudKeyComp> subscribedKeys;
		// This server has uploaded these keys, and needs to know about Get() requests
		DataStructures::OrderedList<CloudKey,CloudKey,CloudKeyComp> uploadedKeys;

		// Just for processing
		bool workingFlag;

		// If false, we don't know what keys they have yet, so send everything
		bool gotSubscribedAndUploadedKeys;
	};

	static int RemoteServerComp(const RakNetGUID &key, RemoteServer* const &data );
	DataStructures::OrderedList<RakNetGUID, RemoteServer*, CloudServer::RemoteServerComp> remoteServers;

	struct BufferedGetResponseFromServer
	{
		void Clear(CloudAllocator *allocator);

		RakNetGUID serverAddress;
		CloudQueryResult queryResult;
		bool gotResult;
	};

	struct CloudQueryWithAddresses
	{
		// Inputs
		CloudQuery cloudQuery;
		DataStructures::List<RakNetGUID> specificSystems;

		void Serialize(bool writeToBitstream, BitStream *bitStream);
	};

	static int BufferedGetResponseFromServerComp(const RakNetGUID &key, BufferedGetResponseFromServer* const &data );
	struct GetRequest
	{
		void Clear(CloudAllocator *allocator);
		bool AllRemoteServersHaveResponded(void) const;
		CloudQueryWithAddresses cloudQueryWithAddresses;

		// When request started. If takes too long for a response from another system, can abort remaining systems
		SLNet::Time requestStartTime;

		// Assigned by server that gets the request to identify response. See nextGetRequestId
		uint32_t requestId;

		RakNetGUID requestingClient;

		DataStructures::OrderedList<RakNetGUID, BufferedGetResponseFromServer*, CloudServer::BufferedGetResponseFromServerComp> remoteServerResponses;
	};
	static int GetRequestComp(const uint32_t &key, GetRequest* const &data );
	DataStructures::OrderedList<uint32_t, GetRequest*, CloudServer::GetRequestComp> getRequests;
	SLNet::Time nextGetRequestsCheck;

	uint32_t nextGetRequestId;

	void ProcessAndTransmitGetRequest(GetRequest *getRequest);

	void ProcessCloudQueryWithAddresses(
		CloudServer::CloudQueryWithAddresses &cloudQueryWithAddresses,
		DataStructures::List<CloudData*> &cloudDataResultList,
		DataStructures::List<CloudKey> &cloudKeyResultList
		);

	void SendUploadedAndSubscribedKeysToServer( RakNetGUID systemAddress );
	void SendUploadedKeyToServers( CloudKey &cloudKey );
	void SendSubscribedKeyToServers( CloudKey &cloudKey );
	void RemoveUploadedKeyFromServers( CloudKey &cloudKey );
	void RemoveSubscribedKeyFromServers( CloudKey &cloudKey );

	void OnSendUploadedAndSubscribedKeysToServer( Packet *packet );
	void OnSendUploadedKeyToServers( Packet *packet );
	void OnSendSubscribedKeyToServers( Packet *packet );
	void OnRemoveUploadedKeyFromServers( Packet *packet );
	void OnRemoveSubscribedKeyFromServers( Packet *packet );
	void OnServerDataChanged( Packet *packet );

	void GetServersWithUploadedKeys(
		DataStructures::List<CloudKey> &keys,
		DataStructures::List<RemoteServer*> &remoteServersWithData
		);

	CloudServer::CloudDataList *GetOrAllocateCloudDataList(CloudKey key, bool *dataRepositoryExists, unsigned int &dataRepositoryIndex);

	void UnsubscribeFromKey(RemoteCloudClient *remoteCloudClient, RakNetGUID remoteCloudClientGuid, unsigned int keySubscriberIndex, CloudKey &cloudKey, DataStructures::List<RakNetGUID> &specificSystems);
	void RemoveSpecificSubscriber(RakNetGUID specificSubscriber, CloudDataList *cloudDataList, RakNetGUID remoteCloudClientGuid);

	DataStructures::List<CloudServerQueryFilter*> queryFilters;

	SystemAddress forceAddress;
};


} // namespace SLNet

#endif


// Key subscription
//
// A given system can subscribe to one or more keys.
// The subscription can be further be defined as only subscribing to keys uploaded by or changed by a given system.
// It is possible to subscribe to keys not yet uploaded, or uploaded to another system
//
// Operations:
//
// 1. SubscribeToKey() - Get() operation with subscription
// A. Add to key subscription list for the client, which contains a keyId / specificUploaderList pair
// B. Send to remote servers that for this key, they should send us updates
// C. (Done, get operation returns current values)
//
// 2. UpdateData() - Post() operation
// A. Find all subscribers to this data, for the uploading system.
// B. Send them the uploaded data
// C. Find all servers that subscribe to this data
// D. Send them the uploaded data
//
// 3. DeleteData() - Release() operation
// A. Find all subscribers to this data, for the deleting system.
// B. Inform them of the deletion
// C. Find all servers that subscribe to this data
// D. Inform them of the deletion
//
// 4. Unsubscribe()
// A. Find this subscriber, and remove their subscription
// B. If no one else is subscribing to this key for any system, notify remote servers we no longer need subscription updates
//
// Internal operations:
//
// 1. Find if any connected client has subscribed to a given key
// A. This is used add and remove our subscription for this key to remote servers
//
// 2. For a given key and updating address, find all connected clients that care
// A. First find connected clients that have subscribed to this key, regardless of address
// B. Then find connected clients that have subscribed to this key for this particular address
//
// 3. Find all remote servers that have subscribed to a given key
// A. This is so when the key is updated or deleted, we know who to send it to
//
// 4. For a given client (such as on disconnect), remove all records of their subscriptions

#endif // _RAKNET_SUPPORT_*
