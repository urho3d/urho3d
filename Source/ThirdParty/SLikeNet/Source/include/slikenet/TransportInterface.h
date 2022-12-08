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
/// \brief Contains TransportInterface from which you can derive custom transport providers for ConsoleServer.
///



#ifndef __TRANSPORT_INTERFACE_H
#define __TRANSPORT_INTERFACE_H

#include "types.h"
#include "Export.h"
#include "memoryoverride.h"

#define REMOTE_MAX_TEXT_INPUT 2048

namespace SLNet
{

class CommandParserInterface;


/// \brief Defines an interface that is used to send and receive null-terminated strings.
/// \details In practice this is only used by the CommandParser system for for servers.
class RAK_DLL_EXPORT TransportInterface
{
public:
	TransportInterface() {}
	virtual ~TransportInterface() {}

	/// Start the transport provider on the indicated port.
	/// \param[in] port The port to start the transport provider on
	/// \param[in] serverMode If true, you should allow incoming connections (I don't actually use this anywhere)
	/// \return Return true on success, false on failure.
	virtual bool Start(unsigned short port, bool serverMode)=0;

	/// Stop the transport provider.  You can clear memory and shutdown threads here.
	virtual void Stop(void)=0;

	/// Send a null-terminated string to \a systemAddress
	/// If your transport method requires particular formatting of the outgoing data (e.g. you don't just send strings) you can do it here
	/// and parse it out in Receive().
	/// \param[in] systemAddress The player to send the string to
	/// \param[in] data format specifier - same as RAKNET_DEBUG_PRINTF
	/// \param[in] ... format specification arguments - same as RAKNET_DEBUG_PRINTF
	virtual void Send( SystemAddress systemAddress, const char *data, ... )=0;

	/// Disconnect \a systemAddress .  The binary address and port defines the SystemAddress structure.
	/// \param[in] systemAddress The player/address to disconnect
	virtual void CloseConnection( SystemAddress systemAddress )=0;

	/// Return a string. The string should be allocated and written to Packet::data .
	/// The byte length should be written to Packet::length .  The player/address should be written to Packet::systemAddress
	/// If your transport protocol adds special formatting to the data stream you should parse it out before returning it in the packet
	/// and thus only return a string in Packet::data
	/// \return The packet structure containing the result of Receive, or 0 if no data is available
	virtual Packet* Receive( void )=0;

	/// Deallocate the Packet structure returned by Receive
	/// \param[in] The packet to deallocate
	virtual void DeallocatePacket( Packet *packet )=0;

	/// If a new system connects to you, you should queue that event and return the systemAddress/address of that player in this function.
	/// \return The SystemAddress/address of the system
	virtual SystemAddress HasNewIncomingConnection(void)=0;

	/// If a system loses the connection, you should queue that event and return the systemAddress/address of that player in this function.
	/// \return The SystemAddress/address of the system
	virtual SystemAddress HasLostConnection(void)=0;

	/// Your transport provider can itself have command parsers if the transport layer has user-modifiable features
	/// For example, your transport layer may have a password which you want remote users to be able to set or you may want
	/// to allow remote users to turn on or off command echo
	/// \return 0 if you do not need a command parser - otherwise the desired derivation of CommandParserInterface
	virtual CommandParserInterface* GetCommandParser(void)=0;
protected:
};

} // namespace SLNet

#endif

