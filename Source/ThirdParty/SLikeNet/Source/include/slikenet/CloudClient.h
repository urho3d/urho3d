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

/// \file CloudClient.h
/// \brief Queries CloudMemoryServer to download data that other clients have uploaded
///


#include "NativeFeatureIncludes.h"
#if _RAKNET_SUPPORT_CloudClient==1

#ifndef __CLOUD_CLIENT_H
#define __CLOUD_CLIENT_H

#include "PluginInterface2.h"
#include "CloudCommon.h"
#include "memoryoverride.h"
#include "DS_Hash.h"

namespace SLNet
{
/// Forward declarations
class RakPeerInterface;
class CloudClientCallback;

/// \defgroup CLOUD_GROUP CloudComputing
/// \brief Contains the CloudClient and CloudServer plugins
/// \details The CloudServer plugins operates on requests from the CloudClient plugin. The servers are in a fully connected mesh topology, which the clients are connected to any server. Clients can interact with each other by posting and subscribing to memory updates, without being directly connected or even knowing about each other.
/// \ingroup PLUGINS_GROUP

/// \brief Performs Post() and Get() operations on CloudMemoryServer
/// \details A CloudClient is a computer connected to one or more servers in a cloud configuration. Operations by one CloudClient can be received and subscribed to by other instances of CloudClient, without those clients being connected, even on different servers.
/// \ingroup CLOUD_GROUP
class RAK_DLL_EXPORT CloudClient : public PluginInterface2
{
public:
	// GetInstance() and DestroyInstance(instance*)
	STATIC_FACTORY_DECLARATIONS(CloudClient)

	CloudClient();
	virtual ~CloudClient();

	/// \brief Set the default callbacks for OnGetReponse(), OnSubscriptionNotification(), and OnSubscriptionDataDeleted()
	/// \details Pointers to CloudAllocator and CloudClientCallback can be stored by the system if desired. If a callback is not provided to OnGetReponse(), OnSubscriptionNotification(), OnSubscriptionDataDeleted(), the callback passed here will be used instead.
	/// \param[in] _allocator An instance of CloudAllocator
	/// \param[in] _callback An instance of CloudClientCallback
	virtual void SetDefaultCallbacks(CloudAllocator *_allocator, CloudClientCallback *_callback);

	/// \brief Uploads data to the cloud
	/// \details Data uploaded to the cloud will be stored by the server sent to, identified by \a systemIdentifier.
	/// As long as you are connected to this server, the data will persist. Queries for that data by the Get() operation will
	/// return the RakNetGUID and SystemAddress of the uploader, as well as the data itself.
	/// Furthermore, if any clients are subscribed to the particular CloudKey passed, those clients will get update notices that the data has changed
	/// Passing data with the same \a cloudKey more than once will overwrite the prior value.
	/// This call will silently fail if CloudServer::SetMaxUploadBytesPerClient() is exceeded
	/// \param[in] cloudKey Identifies the data being uploaded
	/// \param[in] data A pointer to data to upload. This pointer does not need to persist past the call
	/// \param[in] dataLengthBytes The length in bytes of \a data
	/// \param[in] systemIdentifier A remote system running CloudServer that we are already connected to.
	virtual void Post(CloudKey *cloudKey, const unsigned char *data, uint32_t dataLengthBytes, RakNetGUID systemIdentifier);

	/// \brief Releases one or more data previously uploaded with Post()
	/// \details If a remote system has subscribed to one or more of the \a keys uploaded, they will get ID_CLOUD_SUBSCRIPTION_NOTIFICATION notifications containing the last value uploaded before deletions
	/// \param[in] cloudKey Identifies the data to release. It is possible to remove uploads from multiple Post() calls at once.
	/// \param[in] systemIdentifier A remote system running CloudServer that we are already connected to.
	virtual void Release(DataStructures::List<CloudKey> &keys, RakNetGUID systemIdentifier);

	/// \brief Gets data from the cloud
	/// \details For a given query containing one or more keys, return data that matches those keys.
	/// The values will be returned in the ID_CLOUD_GET_RESPONSE packet, which should be passed to OnGetReponse() and will invoke CloudClientCallback::OnGet()
	/// CloudQuery::startingRowIndex is used to skip the first n values that would normally be returned..
	/// CloudQuery::maxRowsToReturn is used to limit the number of rows returned. The number of rows returned may also be limited by CloudServer::SetMaxBytesPerDownload();
	/// CloudQuery::subscribeToResults if set to true, will cause ID_CLOUD_SUBSCRIPTION_NOTIFICATION to be returned to us when any of the keys in the query are updated or are deleted.
	/// ID_CLOUD_GET_RESPONSE will be returned even if subscribing to the result list. Only later updates will return ID_CLOUD_SUBSCRIPTION_NOTIFICATION.
	/// Calling Get() with CloudQuery::subscribeToResults false, when you are already subscribed, does not remove the subscription. Use Unsubscribe() for this.
	/// Resubscribing using the same CloudKey but a different or no \a specificSystems overwrites the subscribed systems for those keys.
	/// \param[in] cloudQuery One or more keys, and optional parameters to perform with the Get
	/// \param[in] systemIdentifier A remote system running CloudServer that we are already connected to.
	/// \param[in] specificSystems It is possible to get or subscribe to updates only for specific uploading CloudClient instances. Pass the desired instances here. The overload that does not have the specificSystems parameter is treated as subscribing to all updates from all clients.
	virtual bool Get(CloudQuery *cloudQuery, RakNetGUID systemIdentifier);
	virtual bool Get(CloudQuery *cloudQuery, DataStructures::List<RakNetGUID> &specificSystems, RakNetGUID systemIdentifier);
	virtual bool Get(CloudQuery *cloudQuery, DataStructures::List<CloudQueryRow*> &specificSystems, RakNetGUID systemIdentifier);

	/// \brief Unsubscribe from updates previously subscribed to using Get() with the CloudQuery::subscribeToResults set to true
	/// The \a keys and \a specificSystems parameters are logically treated as AND when checking subscriptions on the server
	/// The overload that does not take specificSystems unsubscribes to all passed keys, regardless of system
	/// You cannot unsubscribe specific systems when previously subscribed to updates from any system. To do this, first Unsubscribe() from all systems, and call Get() with the \a specificSystems parameter explicilty listing the systems you want to subscribe to.
	virtual void Unsubscribe(DataStructures::List<CloudKey> &keys, RakNetGUID systemIdentifier);
	virtual void Unsubscribe(DataStructures::List<CloudKey> &keys, DataStructures::List<RakNetGUID> &specificSystems, RakNetGUID systemIdentifier);
	virtual void Unsubscribe(DataStructures::List<CloudKey> &keys, DataStructures::List<CloudQueryRow*> &specificSystems, RakNetGUID systemIdentifier);

	/// \brief Call this when you get ID_CLOUD_GET_RESPONSE
	/// If \a callback or \a allocator are 0, the default callbacks passed to SetDefaultCallbacks() are used
	/// \param[in] packet Packet structure returned from RakPeerInterface
	/// \param[in] _callback Callback to be called from the function containing output parameters. If 0, default is used.
	/// \param[in] _allocator Allocator to be used to allocate data. If 0, default is used.
	virtual void OnGetReponse(Packet *packet, CloudClientCallback *_callback=0, CloudAllocator *_allocator=0);

	/// \brief Call this when you get ID_CLOUD_GET_RESPONSE
	/// Different form of OnGetReponse that returns to a structure that you pass, instead of using a callback
	/// You are responsible for deallocation with this form
	/// If \a allocator is 0, the default callback passed to SetDefaultCallbacks() are used
	/// \param[out] cloudQueryResult A pointer to a structure that will be filled out with data
	/// \param[in] packet Packet structure returned from RakPeerInterface
	/// \param[in] _allocator Allocator to be used to allocate data. If 0, default is used.
	virtual void OnGetReponse(CloudQueryResult *cloudQueryResult, Packet *packet, CloudAllocator *_allocator=0);

	/// \brief Call this when you get ID_CLOUD_SUBSCRIPTION_NOTIFICATION
	/// If \a callback or \a allocator are 0, the default callbacks passed to SetDefaultCallbacks() are used
	/// \param[in] packet Packet structure returned from RakPeerInterface
	/// \param[in] _callback Callback to be called from the function containing output parameters. If 0, default is used.
	/// \param[in] _allocator Allocator to be used to allocate data. If 0, default is used.
	virtual void OnSubscriptionNotification(Packet *packet, CloudClientCallback *_callback=0, CloudAllocator *_allocator=0);

	/// \brief Call this when you get ID_CLOUD_SUBSCRIPTION_NOTIFICATION
	/// Different form of OnSubscriptionNotification that returns to a structure that you pass, instead of using a callback
	/// You are responsible for deallocation with this form
	/// If \a allocator is 0, the default callback passed to SetDefaultCallbacks() are used
	/// \param[out] wasUpdated If true, the row was updated. If false, it was deleted. \a result will contain the last value just before deletion
	/// \param[out] row A pointer to a structure that will be filled out with data
	/// \param[in] packet Packet structure returned from RakPeerInterface
	/// \param[in] _allocator Allocator to be used to allocate data. If 0, default is used.
	virtual void OnSubscriptionNotification(bool *wasUpdated, CloudQueryRow *row, Packet *packet, CloudAllocator *_allocator=0);

	/// If you never specified an allocator, and used the non-callback form of OnGetReponse(), deallocate cloudQueryResult with this function
	virtual void DeallocateWithDefaultAllocator(CloudQueryResult *cloudQueryResult);

	/// If you never specified an allocator, and used the non-callback form of OnSubscriptionNotification(), deallocate row with this function
	virtual void DeallocateWithDefaultAllocator(CloudQueryRow *row);

protected:
	PluginReceiveResult OnReceive(Packet *packet);

	CloudClientCallback *callback;
	CloudAllocator *allocator;

	CloudAllocator unsetDefaultAllocator;
};

/// \ingroup CLOUD_GROUP
/// Parses ID_CLOUD_GET_RESPONSE and ID_CLOUD_SUBSCRIPTION_NOTIFICATION in a convenient callback form
class RAK_DLL_EXPORT CloudClientCallback
{
public:
	CloudClientCallback() {}
	virtual ~CloudClientCallback() {}

	/// \brief Called in response to ID_CLOUD_GET_RESPONSE
	/// \param[out] result Contains the original query passed to Get(), and a list of rows returned.
	/// \param[out] deallocateRowsAfterReturn CloudQueryResult::rowsReturned will be deallocated after the function returns by default. Set to false to not deallocate these pointers. The pointers are allocated through CloudAllocator.
	virtual void OnGet(SLNet::CloudQueryResult *result, bool *deallocateRowsAfterReturn) {(void) result; (void) deallocateRowsAfterReturn;}

	/// \brief Called in response to ID_CLOUD_SUBSCRIPTION_NOTIFICATION
	/// \param[out] result Contains the row updated
	/// \param[out] wasUpdated If true, the row was updated. If false, it was deleted. \a result will contain the last value just before deletion
	/// \param[out] deallocateRowAfterReturn \a result will be deallocated after the function returns by default. Set to false to not deallocate these pointers. The pointers are allocated through CloudAllocator.
	virtual void OnSubscriptionNotification(SLNet::CloudQueryRow *result, bool wasUpdated, bool *deallocateRowAfterReturn) {(void) result; (void) wasUpdated; (void) deallocateRowAfterReturn;}
};

} // namespace SLNet

#endif

#endif // _RAKNET_SUPPORT_*
