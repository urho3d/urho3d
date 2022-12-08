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
/// \brief Essentially maintains a list of servers running UDPProxyServer, and some state management for UDPProxyClient to find a free server to forward datagrams
///


#include "NativeFeatureIncludes.h"
#if _RAKNET_SUPPORT_UDPProxyCoordinator==1 && _RAKNET_SUPPORT_UDPForwarder==1

#ifndef __UDP_PROXY_COORDINATOR_H
#define __UDP_PROXY_COORDINATOR_H

#include "Export.h"
#include "types.h"
#include "PluginInterface2.h"
#include "string.h"
#include "BitStream.h"
#include "DS_Queue.h"
#include "DS_OrderedList.h"

namespace SLNet
{
	/// When NAT Punchthrough fails, it is possible to use a non-NAT system to forward messages from us to the recipient, and vice-versa
	/// The class to forward messages is UDPForwarder, and it is triggered over the network via the UDPProxyServer plugin.
	/// The UDPProxyClient connects to UDPProxyCoordinator to get a list of servers running UDPProxyServer, and the coordinator will relay our forwarding request
	/// \brief Middleman between UDPProxyServer and UDPProxyClient, maintaining a list of UDPProxyServer, and managing state for clients to find an available forwarding server.
	/// \ingroup NAT_PUNCHTHROUGH_GROUP
	class RAK_DLL_EXPORT UDPProxyCoordinator : public PluginInterface2
	{
	public:
		// GetInstance() and DestroyInstance(instance*)
		STATIC_FACTORY_DECLARATIONS(UDPProxyCoordinator)

		UDPProxyCoordinator();
		virtual ~UDPProxyCoordinator();

		/// For UDPProxyServers logging in remotely, they must pass a password to UDPProxyServer::LoginToCoordinator(). It must match the password set here.
		/// If no password is set, they cannot login remotely.
		/// By default, no password is set
		void SetRemoteLoginPassword(SLNet::RakString password);

		/// \internal
		virtual void Update(void);
		virtual PluginReceiveResult OnReceive(Packet *packet);
		virtual void OnClosedConnection(const SystemAddress &systemAddress, RakNetGUID rakNetGUID, PI2_LostConnectionReason lostConnectionReason );

		struct SenderAndTargetAddress
		{
			SystemAddress senderClientAddress;
			RakNetGUID senderClientGuid;
			SystemAddress targetClientAddress;
			RakNetGUID targetClientGuid;
		};

		struct ServerWithPing
		{
			unsigned short ping;
			SystemAddress serverAddress;
		};

		struct ForwardingRequest
		{
			SLNet::TimeMS timeoutOnNoDataMS;
			SLNet::TimeMS timeoutAfterSuccess;
			SenderAndTargetAddress sata;
			SystemAddress requestingAddress; // Which system originally sent the network message to start forwarding
			SystemAddress currentlyAttemptedServerAddress;
			DataStructures::Queue<SystemAddress> remainingServersToTry;
			SLNet::BitStream serverSelectionBitstream;

			DataStructures::List<ServerWithPing> sourceServerPings, targetServerPings;
			SLNet::TimeMS timeRequestedPings;
			// Order based on sourceServerPings and targetServerPings
			void OrderRemainingServersToTry(void);
		
		};
	protected:

		static int ServerWithPingComp( const unsigned short &key, const UDPProxyCoordinator::ServerWithPing &data );
		static int ForwardingRequestComp( const SenderAndTargetAddress &key, ForwardingRequest* const &data);

		void OnForwardingRequestFromClientToCoordinator(Packet *packet);
		void OnLoginRequestFromServerToCoordinator(Packet *packet);
		void OnForwardingReplyFromServerToCoordinator(Packet *packet);
		void OnPingServersReplyFromClientToCoordinator(Packet *packet);
		void TryNextServer(SenderAndTargetAddress sata, ForwardingRequest *fw);
		void SendAllBusy(SystemAddress senderClientAddress, SystemAddress targetClientAddress, RakNetGUID targetClientGuid, SystemAddress requestingAddress);
		void Clear(void);

		void SendForwardingRequest(SystemAddress sourceAddress, SystemAddress targetAddress, SystemAddress serverAddress, SLNet::TimeMS timeoutOnNoDataMS);

		// Logged in servers
		//DataStructures::Multilist<ML_UNORDERED_LIST, SystemAddress> serverList;
		DataStructures::List<SystemAddress> serverList;

		// Forwarding requests in progress
		//DataStructures::Multilist<ML_ORDERED_LIST, ForwardingRequest*, SenderAndTargetAddress> forwardingRequestList;
		DataStructures::OrderedList<SenderAndTargetAddress, ForwardingRequest*, ForwardingRequestComp> forwardingRequestList;

		SLNet::RakString remoteLoginPassword;

	};

} // End namespace

#endif

#endif // _RAKNET_SUPPORT_*
