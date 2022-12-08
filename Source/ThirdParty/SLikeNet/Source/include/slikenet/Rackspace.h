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

/// \file Rackspace.h
/// \brief Helper to class to manage Rackspace servers
///


#include "NativeFeatureIncludes.h"

#if _RAKNET_SUPPORT_Rackspace==1 && _RAKNET_SUPPORT_TCPInterface==1

#include "Export.h"
#include "DS_List.h"
#include "types.h"
#include "DS_Queue.h"
#include "string.h"

#ifndef __RACKSPACE_H
#define __RACKSPACE_H

namespace SLNet
{

	class TCPInterface;
	struct Packet;

	/// \brief Result codes for Rackspace commands
	/// /sa Rackspace::EventTypeToString()
	enum RackspaceEventType
	{
		RET_Success_200,
		RET_Success_201,
		RET_Success_202,
		RET_Success_203,
		RET_Success_204,
		RET_Cloud_Servers_Fault_500,
		RET_Service_Unavailable_503,
		RET_Unauthorized_401,
		RET_Bad_Request_400,
		RET_Over_Limit_413,
		RET_Bad_Media_Type_415,
		RET_Item_Not_Found_404,
		RET_Build_In_Progress_409,
		RET_Resize_Not_Allowed_403,
		RET_Connection_Closed_Without_Reponse,
		RET_Unknown_Failure,
	};

	/// \internal
	enum RackspaceOperationType
	{
		RO_CONNECT_AND_AUTHENTICATE,
		RO_LIST_SERVERS,
		RO_LIST_SERVERS_WITH_DETAILS,
		RO_CREATE_SERVER,
		RO_GET_SERVER_DETAILS,
		RO_UPDATE_SERVER_NAME_OR_PASSWORD,
		RO_DELETE_SERVER,
		RO_LIST_SERVER_ADDRESSES,
		RO_SHARE_SERVER_ADDRESS,
		RO_DELETE_SERVER_ADDRESS,
		RO_REBOOT_SERVER,
		RO_REBUILD_SERVER,
		RO_RESIZE_SERVER,
		RO_CONFIRM_RESIZED_SERVER,
		RO_REVERT_RESIZED_SERVER,
		RO_LIST_FLAVORS,
		RO_GET_FLAVOR_DETAILS,
		RO_LIST_IMAGES,
		RO_CREATE_IMAGE,
		RO_GET_IMAGE_DETAILS,
		RO_DELETE_IMAGE,
		RO_LIST_SHARED_IP_GROUPS,
		RO_LIST_SHARED_IP_GROUPS_WITH_DETAILS,
		RO_CREATE_SHARED_IP_GROUP,
		RO_GET_SHARED_IP_GROUP_DETAILS,
		RO_DELETE_SHARED_IP_GROUP,

		RO_NONE,
	};

	/// \brief Callback interface to receive the results of operations
	class RAK_DLL_EXPORT Rackspace2EventCallback
	{
	public:
		Rackspace2EventCallback() {}
		virtual ~Rackspace2EventCallback() {}
		virtual void OnAuthenticationResult(RackspaceEventType eventType, const char *htmlAdditionalInfo)=0;
		virtual void OnListServersResult(RackspaceEventType eventType, const char *htmlAdditionalInfo)=0;
		virtual void OnListServersWithDetailsResult(RackspaceEventType eventType, const char *htmlAdditionalInfo)=0;
		virtual void OnCreateServerResult(RackspaceEventType eventType, const char *htmlAdditionalInfo)=0;
		virtual void OnGetServerDetails(RackspaceEventType eventType, const char *htmlAdditionalInfo)=0;
		virtual void OnUpdateServerNameOrPassword(RackspaceEventType eventType, const char *htmlAdditionalInfo)=0;
		virtual void OnDeleteServer(RackspaceEventType eventType, const char *htmlAdditionalInfo)=0;
		virtual void OnListServerAddresses(RackspaceEventType eventType, const char *htmlAdditionalInfo)=0;
		virtual void OnShareServerAddress(RackspaceEventType eventType, const char *htmlAdditionalInfo)=0;
		virtual void OnDeleteServerAddress(RackspaceEventType eventType, const char *htmlAdditionalInfo)=0;
		virtual void OnRebootServer(RackspaceEventType eventType, const char *htmlAdditionalInfo)=0;
		virtual void OnRebuildServer(RackspaceEventType eventType, const char *htmlAdditionalInfo)=0;
		virtual void OnResizeServer(RackspaceEventType eventType, const char *htmlAdditionalInfo)=0;
		virtual void OnConfirmResizedServer(RackspaceEventType eventType, const char *htmlAdditionalInfo)=0;
		virtual void OnRevertResizedServer(RackspaceEventType eventType, const char *htmlAdditionalInfo)=0;
		virtual void OnListFlavorsResult(RackspaceEventType eventType, const char *htmlAdditionalInfo)=0;
		virtual void OnGetFlavorDetailsResult(RackspaceEventType eventType, const char *htmlAdditionalInfo)=0;
		virtual void OnListImagesResult(RackspaceEventType eventType, const char *htmlAdditionalInfo)=0;
		virtual void OnCreateImageResult(RackspaceEventType eventType, const char *htmlAdditionalInfo)=0;
		virtual void OnGetImageDetailsResult(RackspaceEventType eventType, const char *htmlAdditionalInfo)=0;
		virtual void OnDeleteImageResult(RackspaceEventType eventType, const char *htmlAdditionalInfo)=0;
		virtual void OnListSharedIPGroups(RackspaceEventType eventType, const char *htmlAdditionalInfo)=0;
		virtual void OnListSharedIPGroupsWithDetails(RackspaceEventType eventType, const char *htmlAdditionalInfo)=0;
		virtual void OnCreateSharedIPGroup(RackspaceEventType eventType, const char *htmlAdditionalInfo)=0;
		virtual void OnGetSharedIPGroupDetails(RackspaceEventType eventType, const char *htmlAdditionalInfo)=0;
		virtual void OnDeleteSharedIPGroup(RackspaceEventType eventType, const char *htmlAdditionalInfo)=0;

		virtual void OnConnectionAttemptFailure(RackspaceOperationType operationType, const char *url)=0;
	};

	/// \brief Callback interface to receive the results of operations, with a default result
	class RAK_DLL_EXPORT RackspaceEventCallback_Default : public Rackspace2EventCallback
	{
	public:
		virtual void ExecuteDefault(const char *callbackName, RackspaceEventType eventType, const char *htmlAdditionalInfo) {(void) callbackName; (void) eventType; (void) htmlAdditionalInfo;}

		virtual void OnAuthenticationResult(RackspaceEventType eventType, const char *htmlAdditionalInfo) {ExecuteDefault("OnAuthenticationResult", eventType, htmlAdditionalInfo);}
		virtual void OnListServersResult(RackspaceEventType eventType, const char *htmlAdditionalInfo) {ExecuteDefault("OnListServersResult", eventType, htmlAdditionalInfo);}
		virtual void OnListServersWithDetailsResult(RackspaceEventType eventType, const char *htmlAdditionalInfo) {ExecuteDefault("OnListServersWithDetailsResult", eventType, htmlAdditionalInfo);}
		virtual void OnCreateServerResult(RackspaceEventType eventType, const char *htmlAdditionalInfo) {ExecuteDefault("OnCreateServerResult", eventType, htmlAdditionalInfo);}
		virtual void OnGetServerDetails(RackspaceEventType eventType, const char *htmlAdditionalInfo) {ExecuteDefault("OnGetServerDetails", eventType, htmlAdditionalInfo);}
		virtual void OnUpdateServerNameOrPassword(RackspaceEventType eventType, const char *htmlAdditionalInfo) {ExecuteDefault("OnUpdateServerNameOrPassword", eventType, htmlAdditionalInfo);}
		virtual void OnDeleteServer(RackspaceEventType eventType, const char *htmlAdditionalInfo) {ExecuteDefault("OnDeleteServer", eventType, htmlAdditionalInfo);}
		virtual void OnListServerAddresses(RackspaceEventType eventType, const char *htmlAdditionalInfo) {ExecuteDefault("OnListServerAddresses", eventType, htmlAdditionalInfo);}
		virtual void OnShareServerAddress(RackspaceEventType eventType, const char *htmlAdditionalInfo) {ExecuteDefault("OnShareServerAddress", eventType, htmlAdditionalInfo);}
		virtual void OnDeleteServerAddress(RackspaceEventType eventType, const char *htmlAdditionalInfo) {ExecuteDefault("OnDeleteServerAddress", eventType, htmlAdditionalInfo);}
		virtual void OnRebootServer(RackspaceEventType eventType, const char *htmlAdditionalInfo) {ExecuteDefault("OnRebootServer", eventType, htmlAdditionalInfo);}
		virtual void OnRebuildServer(RackspaceEventType eventType, const char *htmlAdditionalInfo) {ExecuteDefault("OnRebuildServer", eventType, htmlAdditionalInfo);}
		virtual void OnResizeServer(RackspaceEventType eventType, const char *htmlAdditionalInfo) {ExecuteDefault("OnResizeServer", eventType, htmlAdditionalInfo);}
		virtual void OnConfirmResizedServer(RackspaceEventType eventType, const char *htmlAdditionalInfo) {ExecuteDefault("OnConfirmResizedServer", eventType, htmlAdditionalInfo);}
		virtual void OnRevertResizedServer(RackspaceEventType eventType, const char *htmlAdditionalInfo) {ExecuteDefault("OnRevertResizedServer", eventType, htmlAdditionalInfo);}
		virtual void OnListFlavorsResult(RackspaceEventType eventType, const char *htmlAdditionalInfo) {ExecuteDefault("OnListFlavorsResult", eventType, htmlAdditionalInfo);}
		virtual void OnGetFlavorDetailsResult(RackspaceEventType eventType, const char *htmlAdditionalInfo) {ExecuteDefault("OnGetFlavorDetailsResult", eventType, htmlAdditionalInfo);}
		virtual void OnListImagesResult(RackspaceEventType eventType, const char *htmlAdditionalInfo) {ExecuteDefault("OnListImagesResult", eventType, htmlAdditionalInfo);}
		virtual void OnCreateImageResult(RackspaceEventType eventType, const char *htmlAdditionalInfo) {ExecuteDefault("OnCreateImageResult", eventType, htmlAdditionalInfo);}
		virtual void OnGetImageDetailsResult(RackspaceEventType eventType, const char *htmlAdditionalInfo) {ExecuteDefault("OnGetImageDetailsResult", eventType, htmlAdditionalInfo);}
		virtual void OnDeleteImageResult(RackspaceEventType eventType, const char *htmlAdditionalInfo) {ExecuteDefault("OnDeleteImageResult", eventType, htmlAdditionalInfo);}
		virtual void OnListSharedIPGroups(RackspaceEventType eventType, const char *htmlAdditionalInfo) {ExecuteDefault("OnListSharedIPGroups", eventType, htmlAdditionalInfo);}
		virtual void OnListSharedIPGroupsWithDetails(RackspaceEventType eventType, const char *htmlAdditionalInfo) {ExecuteDefault("OnListSharedIPGroupsWithDetails", eventType, htmlAdditionalInfo);}
		virtual void OnCreateSharedIPGroup(RackspaceEventType eventType, const char *htmlAdditionalInfo) {ExecuteDefault("OnCreateSharedIPGroup", eventType, htmlAdditionalInfo);}
		virtual void OnGetSharedIPGroupDetails(RackspaceEventType eventType, const char *htmlAdditionalInfo) {ExecuteDefault("OnGetSharedIPGroupDetails", eventType, htmlAdditionalInfo);}
		virtual void OnDeleteSharedIPGroup(RackspaceEventType eventType, const char *htmlAdditionalInfo) {ExecuteDefault("OnDeleteSharedIPGroup", eventType, htmlAdditionalInfo);}

		virtual void OnConnectionAttemptFailure(RackspaceOperationType operationType, const char *url) {(void) operationType; (void) url;}
	};

	/// \brief Code that uses the TCPInterface class to communicate with the Rackspace API servers
	/// \pre Compile RakNet with OPEN_SSL_CLIENT_SUPPORT set to 1
	/// \pre Packets returned from TCPInterface::OnReceive() must be passed to Rackspace::OnReceive()
	/// \pre Packets returned from TCPInterface::HasLostConnection() must be passed to Rackspace::OnClosedConnection()
	class RAK_DLL_EXPORT Rackspace
	{
	public:
		Rackspace();
		~Rackspace();

		/// \brief Authenticate with Rackspace servers, required before executing any commands.
		/// \details All requests to authenticate and operate against Cloud Servers are performed using SSL over HTTP (HTTPS) on TCP port 443.
		/// Times out after 24 hours - if you get RET_Authenticate_Unauthorized in the RackspaceEventCallback callback, call again
		/// \sa RackspaceEventCallback::OnAuthenticationResult()
		/// \param[in] _tcpInterface An instance of TCPInterface, build with OPEN_SSL_CLIENT_SUPPORT 1 and already started
		/// \param[in] _authenticationURL See http://docs.rackspacecloud.com/servers/api/v1.0/cs-devguide-20110112.pdf . US-based accounts authenticate through auth.api.rackspacecloud.com. UK-based accounts authenticate through lon.auth.api.rackspacecloud.com
		/// \param[in] _rackspaceCloudUsername Username you registered with Rackspace on their website
		/// \param[in] _apiAccessKey Obtain your API access key from the Rackspace Cloud Control Panel in the Your Account API Access section.
		/// \return The address of the authentication server, or UNASSIGNED_SYSTEM_ADDRESS if the connection attempt failed
		SystemAddress Authenticate(TCPInterface *_tcpInterface, const char *_authenticationURL, const char *_rackspaceCloudUsername, const char *_apiAccessKey);

		/// \brief Get a list of running servers
		/// \sa http://docs.rackspacecloud.com/servers/api/v1.0/cs-devguide-20110112.pdf
		/// \sa RackspaceEventCallback::OnListServersResult()
		void ListServers(void);

		/// \brief Get a list of running servers, with extended details on each server
		/// \sa GetServerDetails()
		/// \sa http://docs.rackspacecloud.com/servers/api/v1.0/cs-devguide-20110112.pdf
		/// \sa RackspaceEventCallback::OnListServersWithDetailsResult()
		void ListServersWithDetails(void);

		/// \brief Create a server
		/// \details Create a server with a given image (harddrive contents) and flavor (hardware configuration)
		/// Get the available images with ListImages()
		/// Get the available flavors with ListFlavors()
		/// It is possible to configure the server in more detail. See the XML schema at http://docs.rackspacecloud.com/servers/api/v1.0
		/// You can execute such a custom command by calling AddOperation() manually. See the implementation of CreateServer for how to do so.
		/// The server takes a while to build. Call GetServerDetails() to get the current build status. Server id to pass to GetServerDetails() is returned in the field <server ... id="1234">
		/// \sa http://docs.rackspacecloud.com/servers/api/v1.0/cs-devguide-20110112.pdf
		/// \sa RackspaceEventCallback::OnCreateServerResult()
		/// \param[in] name Name of the server. Only alphanumeric characters, periods, and hyphens are valid. Server Name cannot start or end with a period or hyphen.
		/// \param[in] imageId Which image (harddrive contents, including OS) to use
		/// \param[in] flavorId Which flavor (hardware config) to use, primarily how much memory is available.
		void CreateServer(SLNet::RakString name, SLNet::RakString imageId, SLNet::RakString flavorId);

		/// \brief Get details on a particular server
		/// \sa http://docs.rackspacecloud.com/servers/api/v1.0/cs-devguide-20110112.pdf
		/// \sa RackspaceEventCallback::OnGetServerDetailsResult()
		/// \param[in] serverId Which server to get details on. You can call ListServers() to get the list of active servers.
		void GetServerDetails(SLNet::RakString serverId);

		/// \brief Changes the name or password for a server
		/// \sa http://docs.rackspacecloud.com/servers/api/v1.0/cs-devguide-20110112.pdf
		/// \sa RackspaceEventCallback::OnUpdateServerNameOrPasswordResult()
		/// \param[in] serverId Which server to get details on. You can call ListServers() to get the list of active servers.
		/// \param[in] newName The new server name. Leave blank to leave unchanged. Only alphanumeric characters, periods, and hyphens are valid. Server Name cannot start or end with a period or hyphen.
		/// \param[in] newPassword The new server password. Leave blank to leave unchanged.
		void UpdateServerNameOrPassword(SLNet::RakString serverId, SLNet::RakString newName, SLNet::RakString newPassword);

		/// \brief Deletes a server
		/// \sa http://docs.rackspacecloud.com/servers/api/v1.0/cs-devguide-20110112.pdf
		/// \sa RackspaceEventCallback::OnDeleteServerResult()
		/// \param[in] serverId Which server to get details on. You can call ListServers() to get the list of active servers.
		void DeleteServer(SLNet::RakString serverId);
		
		/// \brief Lists the IP addresses available to a server
		/// \sa http://docs.rackspacecloud.com/servers/api/v1.0/cs-devguide-20110112.pdf
		/// \sa RackspaceEventCallback::OnListServerAddressesResult()
		/// \param[in] serverId Which server to operate on. You can call ListServers() to get the list of active servers.
		void ListServerAddresses(SLNet::RakString serverId);

		/// \brief Shares an IP address with a server
		/// \sa http://docs.rackspacecloud.com/servers/api/v1.0/cs-devguide-20110112.pdf
		/// \sa RackspaceEventCallback::OnShareServerAddressResult()
		/// \param[in] serverId Which server to operate on. You can call ListServers() to get the list of active servers.
		/// \param[in] ipAddress Which IP address. You can call ListServerAddresses() to get the list of addresses for the specified server
		void ShareServerAddress(SLNet::RakString serverId, SLNet::RakString ipAddress);

		/// \brief Stops sharing an IP address with a server
		/// \sa http://docs.rackspacecloud.com/servers/api/v1.0/cs-devguide-20110112.pdf
		/// \sa RackspaceEventCallback::OnDeleteServerAddressResult()
		/// \param[in] serverId Which server to operate on. You can call ListServers() to get the list of active servers.
		/// \param[in] ipAddress Which IP address. You can call ListServerAddresses() to get the list of addresses for the specified server
		void DeleteServerAddress(SLNet::RakString serverId, SLNet::RakString ipAddress);

		/// \brief Reboots a server
		/// \sa http://docs.rackspacecloud.com/servers/api/v1.0/cs-devguide-20110112.pdf
		/// \sa RackspaceEventCallback::OnRebootServerResult()
		/// \param[in] serverId Which server to operate on. You can call ListServers() to get the list of active servers.
		/// \param[in] rebootType Should be either "HARD" or "SOFT"
		void RebootServer(SLNet::RakString serverId, SLNet::RakString rebootType);

		/// \brief Rebuilds a server with a different image (harddrive contents)
		/// \sa http://docs.rackspacecloud.com/servers/api/v1.0/cs-devguide-20110112.pdf
		/// \sa RackspaceEventCallback::OnRebuildServerResult()
		/// \param[in] serverId Which server to operate on. You can call ListServers() to get the list of active servers.
		/// \param[in] imageId Which image (harddrive contents, including OS) to use
		void RebuildServer(SLNet::RakString serverId, SLNet::RakString imageId);

		/// \brief Changes the hardware configuration of a server. This does not take effect until you call ConfirmResizedServer()
		/// \sa http://docs.rackspacecloud.com/servers/api/v1.0/cs-devguide-20110112.pdf
		/// \sa RackspaceEventCallback::OnResizeServerResult()
		/// \sa RevertResizedServer()
		/// \param[in] serverId Which server to operate on. You can call ListServers() to get the list of active servers.
		/// \param[in] flavorId Which flavor (hardware config) to use, primarily how much memory is available.
		void ResizeServer(SLNet::RakString serverId, SLNet::RakString flavorId);

		/// \brief Confirm a resize for the specified server
		/// \sa http://docs.rackspacecloud.com/servers/api/v1.0/cs-devguide-20110112.pdf
		/// \sa RackspaceEventCallback::OnConfirmResizedServerResult()
		/// \sa ResizeServer()
		/// \param[in] serverId Which server to operate on. You can call ListServers() to get the list of active servers.
		void ConfirmResizedServer(SLNet::RakString serverId);

		/// \brief Reverts a resize for the specified server
		/// \sa http://docs.rackspacecloud.com/servers/api/v1.0/cs-devguide-20110112.pdf
		/// \sa RackspaceEventCallback::OnRevertResizedServerResult()
		/// \sa ResizeServer()
		/// \param[in] serverId Which server to operate on. You can call ListServers() to get the list of active servers.
		void RevertResizedServer(SLNet::RakString serverId);

		/// \brief List all flavors (hardware configs, primarily memory)
		/// \sa http://docs.rackspacecloud.com/servers/api/v1.0/cs-devguide-20110112.pdf
		/// \sa RackspaceEventCallback::OnListFlavorsResult()
		void ListFlavors(void);

		/// \brief Get extended details about a specific flavor
		/// \sa http://docs.rackspacecloud.com/servers/api/v1.0/cs-devguide-20110112.pdf
		/// \sa RackspaceEventCallback::OnGetFlavorDetailsResult()
		/// \sa ListFlavors()
		/// \param[in] flavorId Which flavor (hardware config)
		void GetFlavorDetails(SLNet::RakString flavorId);

		/// \brief List all images (software configs, including operating systems), which includes images you create yourself
		/// \sa http://docs.rackspacecloud.com/servers/api/v1.0/cs-devguide-20110112.pdf
		/// \sa RackspaceEventCallback::OnListImagesResult()
		/// \sa CreateImage()
		void ListImages(void);

		/// \brief Images a running server. This essentially copies the harddrive, and lets you start a server with the same harddrive contents later
		/// \sa http://docs.rackspacecloud.com/servers/api/v1.0/cs-devguide-20110112.pdf
		/// \sa RackspaceEventCallback::OnCreateImageResult()
		/// \sa ListImages()
		/// \param[in] serverId Which server to operate on. You can call ListServers() to get the list of active servers.
		/// \param[in] imageName What to call this image
		void CreateImage(SLNet::RakString serverId, SLNet::RakString imageName);

		/// \brief Get extended details about a particular image
		/// \sa http://docs.rackspacecloud.com/servers/api/v1.0/cs-devguide-20110112.pdf
		/// \sa RackspaceEventCallback::OnGetImageDetailsResult()
		/// \sa ListImages()
		/// \param[in] imageId Which image
		void GetImageDetails(SLNet::RakString imageId);

		/// \brief Delete a custom image created with CreateImage()
		/// \sa http://docs.rackspacecloud.com/servers/api/v1.0/cs-devguide-20110112.pdf
		/// \sa RackspaceEventCallback::OnDeleteImageResult()
		/// \sa ListImages()
		/// \param[in] imageId Which image
		void DeleteImage(SLNet::RakString imageId);

		/// \brief List IP groups
		/// \sa http://docs.rackspacecloud.com/servers/api/v1.0/cs-devguide-20110112.pdf
		/// \sa RackspaceEventCallback::OnListSharedIPGroupsResult()
		void ListSharedIPGroups(void);

		/// \brief List IP groups with extended details
		/// \sa http://docs.rackspacecloud.com/servers/api/v1.0/cs-devguide-20110112.pdf
		/// \sa RackspaceEventCallback::OnListSharedIPGroupsWithDetailsResult()
		void ListSharedIPGroupsWithDetails(void);

		// I don't know what this does
		void CreateSharedIPGroup(SLNet::RakString name, SLNet::RakString optionalServerId);
		// I don't know what this does
		void GetSharedIPGroupDetails(SLNet::RakString groupId);
		// I don't know what this does
		void DeleteSharedIPGroup(SLNet::RakString groupId);

		/// \brief Adds a callback to the list of callbacks to be called when any of the above functions finish executing
		/// The callbacks are called in the order they are added
		void AddEventCallback(Rackspace2EventCallback *callback);
		/// \brief Removes a callback from the list of callbacks to be called when any of the above functions finish executing
		/// The callbacks are called in the order they are added
		void RemoveEventCallback(Rackspace2EventCallback *callback);
		/// \brief Removes all callbacks
		void ClearEventCallbacks(void);

		/// Call this anytime TCPInterface returns a packet
		void OnReceive(Packet *packet);

		/// Call this when TCPInterface returns something other than UNASSIGNED_SYSTEM_ADDRESS from HasLostConnection()
		void OnClosedConnection(SystemAddress systemAddress);

		/// String representation of each RackspaceEventType
		static const char * EventTypeToString(RackspaceEventType eventType);

		/// \brief Mostly for internal use, but you can use it to execute an operation with more complex xml if desired
		/// See the Rackspace.cpp on how to use it
		void AddOperation(RackspaceOperationType type, SLNet::RakString httpCommand, SLNet::RakString operation, SLNet::RakString xml);
	protected:

		DataStructures::List<Rackspace2EventCallback*> eventCallbacks;

		struct RackspaceOperation
		{
			RackspaceOperationType type;
		//	SLNet::RakString stringInfo;
			SystemAddress connectionAddress;
			bool isPendingAuthentication;
			SLNet::RakString incomingStream;
			SLNet::RakString httpCommand;
			SLNet::RakString operation;
			SLNet::RakString xml;
		};

		TCPInterface *tcpInterface;

		// RackspaceOperationType currentOperation;
		// DataStructures::Queue<RackspaceOperation> nextOperationQueue;

		DataStructures::List<RackspaceOperation> operations;
		bool HasOperationOfType(RackspaceOperationType t);
		unsigned int GetOperationOfTypeIndex(RackspaceOperationType t);

		SLNet::RakString serverManagementURL;
		SLNet::RakString serverManagementDomain;
		SLNet::RakString serverManagementPath;
		SLNet::RakString storageURL;
		SLNet::RakString storageDomain;
		SLNet::RakString storagePath;
		SLNet::RakString cdnManagementURL;
		SLNet::RakString cdnManagementDomain;
		SLNet::RakString cdnManagementPath;

		SLNet::RakString storageToken;
		SLNet::RakString authToken;
		SLNet::RakString rackspaceCloudUsername;
		SLNet::RakString apiAccessKey;

		bool ExecuteOperation(RackspaceOperation &ro);
		void ReadLine(const char *data, const char *stringStart, SLNet::RakString &output);
		bool ConnectToServerManagementDomain(RackspaceOperation &ro);


	};

} // namespace SLNet

#endif // __RACKSPACE_API_H

#endif // _RAKNET_SUPPORT_Rackspace
