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
/// \brief A simple TCP based server allowing sends and receives.  Can be connected by any TCP client, including telnet.
///


#include "NativeFeatureIncludes.h"
#if _RAKNET_SUPPORT_PacketizedTCP==1 && _RAKNET_SUPPORT_TCPInterface==1

#ifndef __PACKETIZED_TCP
#define __PACKETIZED_TCP

#include "TCPInterface.h"
#include "DS_ByteQueue.h"
#include "DS_Map.h"

namespace SLNet
{

class RAK_DLL_EXPORT PacketizedTCP : public TCPInterface
{
public:
	// GetInstance() and DestroyInstance(instance*)
	STATIC_FACTORY_DECLARATIONS(PacketizedTCP)

	PacketizedTCP();
	virtual ~PacketizedTCP();

	/// Stops the TCP server
	void Stop(void);

	/// Sends a byte stream
	void Send( const char *data, unsigned length, const SystemAddress &systemAddress, bool broadcast );

	// Sends a concatenated list of byte streams
	bool SendList( const char **data, const unsigned int *lengths, const int numParameters, const SystemAddress &systemAddress, bool broadcast );

	/// Returns data received
	Packet* Receive( void );

	/// Disconnects a player/address
	void CloseConnection( SystemAddress systemAddress );

	/// Has a previous call to connect succeeded?
	/// \return UNASSIGNED_SYSTEM_ADDRESS = no. Anything else means yes.
	SystemAddress HasCompletedConnectionAttempt(void);

	/// Has a previous call to connect failed?
	/// \return UNASSIGNED_SYSTEM_ADDRESS = no. Anything else means yes.
	SystemAddress HasFailedConnectionAttempt(void);

	/// Queued events of new incoming connections
	SystemAddress HasNewIncomingConnection(void);

	/// Queued events of lost connections
	SystemAddress HasLostConnection(void);

protected:
	void ClearAllConnections(void);
	void RemoveFromConnectionList(const SystemAddress &sa);
	void AddToConnectionList(const SystemAddress &sa);
	void PushNotificationsToQueues(void);
	Packet *ReturnOutgoingPacket(void);

	// A single TCP recieve may generate multiple split packets. They are stored in the waitingPackets list until Receive is called
	DataStructures::Queue<Packet*> waitingPackets;
	DataStructures::Map<SystemAddress, DataStructures::ByteQueue *> connections;

	// Mirrors single producer / consumer, but processes them in Receive() before returning to user
	DataStructures::Queue<SystemAddress> _newIncomingConnections, _lostConnections, _failedConnectionAttempts, _completedConnectionAttempts;
};

} // namespace SLNet

#endif

#endif // _RAKNET_SUPPORT_*
