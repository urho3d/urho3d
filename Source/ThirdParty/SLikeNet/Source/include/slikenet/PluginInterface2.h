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
/// \brief \b RakNet's plugin functionality system, version 2.  You can derive from this to create your own plugins.
///


#ifndef __PLUGIN_INTERFACE_2_H
#define __PLUGIN_INTERFACE_2_H

#include "NativeFeatureIncludes.h"
#include "types.h"
#include "Export.h"
#include "PacketPriority.h"

namespace SLNet {

/// Forward declarations
class RakPeerInterface;
class TCPInterface;
struct Packet;
struct InternalPacket;

/// \defgroup PLUGIN_INTERFACE_GROUP PluginInterface2

/// \defgroup PLUGINS_GROUP Plugins
/// \ingroup PLUGIN_INTERFACE_GROUP

/// For each message that arrives on an instance of RakPeer, the plugins get an opportunity to process them first. This enumeration represents what to do with the message
/// \ingroup PLUGIN_INTERFACE_GROUP
enum PluginReceiveResult
{
	/// The plugin used this message and it shouldn't be given to the user.
	RR_STOP_PROCESSING_AND_DEALLOCATE=0,

	/// This message will be processed by other plugins, and at last by the user.
	RR_CONTINUE_PROCESSING,

	/// The plugin is going to hold on to this message.  Do not deallocate it but do not pass it to other plugins either.
	RR_STOP_PROCESSING
};

/// Reasons why a connection was lost
/// \ingroup PLUGIN_INTERFACE_GROUP
enum PI2_LostConnectionReason
{
	/// Called RakPeer::CloseConnection()
	LCR_CLOSED_BY_USER,

	/// Got ID_DISCONNECTION_NOTIFICATION
	LCR_DISCONNECTION_NOTIFICATION,

	/// GOT ID_CONNECTION_LOST
	LCR_CONNECTION_LOST
};

/// Returns why a connection attempt failed
/// \ingroup PLUGIN_INTERFACE_GROUP
enum PI2_FailedConnectionAttemptReason
{
	FCAR_CONNECTION_ATTEMPT_FAILED,
	FCAR_ALREADY_CONNECTED,
	FCAR_NO_FREE_INCOMING_CONNECTIONS,
	FCAR_SECURITY_PUBLIC_KEY_MISMATCH,
	FCAR_CONNECTION_BANNED,
	FCAR_INVALID_PASSWORD,
	FCAR_INCOMPATIBLE_PROTOCOL,
	FCAR_IP_RECENTLY_CONNECTED,
	FCAR_REMOTE_SYSTEM_REQUIRES_PUBLIC_KEY,
	FCAR_OUR_SYSTEM_REQUIRES_SECURITY,
	FCAR_PUBLIC_KEY_MISMATCH
};

/// RakNet's plugin system. Each plugin processes the following events:
/// -Connection attempts
/// -The result of connection attempts
/// -Each incoming message
/// -Updates over time, when RakPeer::Receive() is called
///
/// \ingroup PLUGIN_INTERFACE_GROUP
class RAK_DLL_EXPORT PluginInterface2
{
public:
	PluginInterface2();
	virtual ~PluginInterface2();

	/// Called when the interface is attached
	virtual void OnAttach(void) {}

	/// Called when the interface is detached
	virtual void OnDetach(void) {}

	/// Update is called every time a packet is checked for .
	virtual void Update(void) {}

	/// OnReceive is called for every packet.
	/// \param[in] packet the packet that is being returned to the user
	/// \return True to allow the game and other plugins to get this message, false to absorb it
	virtual PluginReceiveResult OnReceive(Packet *packet) {(void) packet; return RR_CONTINUE_PROCESSING;}

	/// Called when RakPeer is initialized
	virtual void OnRakPeerStartup(void) {}

	/// Called when RakPeer is shutdown
	virtual void OnRakPeerShutdown(void) {}

	/// Called when a connection is dropped because the user called RakPeer::CloseConnection() for a particular system
	/// \param[in] systemAddress The system whose connection was closed
	/// \param[in] rakNetGuid The guid of the specified system
	/// \param[in] lostConnectionReason How the connection was closed: manually, connection lost, or notification of disconnection
	virtual void OnClosedConnection(const SystemAddress &systemAddress, RakNetGUID rakNetGUID, PI2_LostConnectionReason lostConnectionReason ){(void) systemAddress; (void) rakNetGUID; (void) lostConnectionReason;}

	/// Called when we got a new connection
	/// \param[in] systemAddress Address of the new connection
	/// \param[in] rakNetGuid The guid of the specified system
	/// \param[in] isIncoming If true, this is ID_NEW_INCOMING_CONNECTION, or the equivalent
	virtual void OnNewConnection(const SystemAddress &systemAddress, RakNetGUID rakNetGUID, bool isIncoming) {(void) systemAddress; (void) rakNetGUID; (void) isIncoming;}

	/// Called when a connection attempt fails
	/// \param[in] packet Packet to be returned to the user
	/// \param[in] failedConnectionReason Why the connection failed
	virtual void OnFailedConnectionAttempt(Packet *packet, PI2_FailedConnectionAttemptReason failedConnectionAttemptReason) {(void) packet; (void) failedConnectionAttemptReason;}

	/// Queried when attached to RakPeer
	/// Return true to call OnDirectSocketSend(), OnDirectSocketReceive(), OnReliabilityLayerNotification(), OnInternalPacket(), and OnAck()
	/// If true, then you cannot call RakPeer::AttachPlugin() or RakPeer::DetachPlugin() for this plugin, while RakPeer is active
	virtual bool UsesReliabilityLayer(void) const {return false;}

	/// Called on a send to the socket, per datagram, that does not go through the reliability layer
	/// \pre To be called, UsesReliabilityLayer() must return true
	/// \param[in] data The data being sent
	/// \param[in] bitsUsed How many bits long \a data is
	/// \param[in] remoteSystemAddress Which system this message is being sent to
	virtual void OnDirectSocketSend(const char *data, const BitSize_t bitsUsed, SystemAddress remoteSystemAddress) {(void) data; (void) bitsUsed; (void) remoteSystemAddress;}
	
	/// Called on a receive from the socket, per datagram, that does not go through the reliability layer
	/// \pre To be called, UsesReliabilityLayer() must return true
	/// \param[in] data The data being sent
	/// \param[in] bitsUsed How many bits long \a data is
	/// \param[in] remoteSystemAddress Which system this message is being sent to
	virtual void OnDirectSocketReceive(const char *data, const BitSize_t bitsUsed, SystemAddress remoteSystemAddress) {(void) data; (void) bitsUsed; (void) remoteSystemAddress;}

	/// Called when the reliability layer rejects a send or receive
	/// \pre To be called, UsesReliabilityLayer() must return true
	/// \param[in] bitsUsed How many bits long \a data is
	/// \param[in] remoteSystemAddress Which system this message is being sent to
	virtual void OnReliabilityLayerNotification(const char *errorMessage, const BitSize_t bitsUsed, SystemAddress remoteSystemAddress, bool isError)  {(void) errorMessage; (void) bitsUsed; (void) remoteSystemAddress; (void) isError;}
	
	/// Called on a send or receive of a message within the reliability layer
	/// \pre To be called, UsesReliabilityLayer() must return true
	/// \param[in] internalPacket The user message, along with all send data.
	/// \param[in] frameNumber The number of frames sent or received so far for this player depending on \a isSend .  Indicates the frame of this user message.
	/// \param[in] remoteSystemAddress The player we sent or got this packet from
	/// \param[in] time The current time as returned by SLNet::GetTimeMS()
	/// \param[in] isSend Is this callback representing a send event or receive event?
	virtual void OnInternalPacket(InternalPacket *internalPacket, unsigned frameNumber, SystemAddress remoteSystemAddress, SLNet::TimeMS time, int isSend) {(void) internalPacket; (void) frameNumber; (void) remoteSystemAddress; (void) time; (void) isSend;}

	/// Called when we get an ack for a message we reliably sent
	/// \pre To be called, UsesReliabilityLayer() must return true
	/// \param[in] messageNumber The numerical identifier for which message this is
	/// \param[in] remoteSystemAddress The player we sent or got this packet from
	/// \param[in] time The current time as returned by SLNet::GetTimeMS()
	virtual void OnAck(unsigned int messageNumber, SystemAddress remoteSystemAddress, SLNet::TimeMS time) {(void) messageNumber; (void) remoteSystemAddress; (void) time;}

	/// System called RakPeerInterface::PushBackPacket
	/// \param[in] data The data being sent
	/// \param[in] bitsUsed How many bits long \a data is
	/// \param[in] remoteSystemAddress The player we sent or got this packet from
	virtual void OnPushBackPacket(const char *data, const BitSize_t bitsUsed, SystemAddress remoteSystemAddress) {(void) data; (void) bitsUsed; (void) remoteSystemAddress;}

	RakPeerInterface *GetRakPeerInterface(void) const {return rakPeerInterface;}

	RakNetGUID GetMyGUIDUnified(void) const;

	/// \internal
	void SetRakPeerInterface( RakPeerInterface *ptr );

#if _RAKNET_SUPPORT_TCPInterface==1
	/// \internal
	void SetTCPInterface( TCPInterface *ptr );
#endif

protected:
	// Send through either rakPeerInterface or tcpInterface, whichever is available
	void SendUnified( const SLNet::BitStream * bitStream, PacketPriority priority, PacketReliability reliability, char orderingChannel, const AddressOrGUID systemIdentifier, bool broadcast );
	void SendUnified( const char * data, const int length, PacketPriority priority, PacketReliability reliability, char orderingChannel, const AddressOrGUID systemIdentifier, bool broadcast );
	bool SendListUnified( const char **data, const int *lengths, const int numParameters, PacketPriority priority, PacketReliability reliability, char orderingChannel, const AddressOrGUID systemIdentifier, bool broadcast );

	Packet *AllocatePacketUnified(unsigned dataSize);
	void PushBackPacketUnified(Packet *packet, bool pushAtHead);
	void DeallocPacketUnified(Packet *packet);

	// Filled automatically in when attached
	RakPeerInterface *rakPeerInterface;
#if _RAKNET_SUPPORT_TCPInterface==1
	TCPInterface *tcpInterface;
#endif
};

} // namespace SLNet

#endif

