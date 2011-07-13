/* Copyright 2010 Jukka Jylänki

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License. */
#pragma once

/** @file TCPMessageConnection.h
	@brief The TCPMessageConnection class.*/

#include "MessageConnection.h"
#include "RingBuffer.h"

/*
TCP stream format:
.Message.
.Message.
...
.Message.

Message format:
u8-u32 Whole Message length (including MessageID + ContentData, but not this field itself)  VLE-encoded 1.7/1.7/16
u8-u32 MessageID			      VLE-encoded 1.7/1.7/16
N bytes Content data

*/

namespace kNet
{

class TCPMessageConnection : public MessageConnection
{
public:
	TCPMessageConnection(Network *owner, NetworkServer *ownerServer, Socket *socket, ConnectionState startingState);
	~TCPMessageConnection();

private:
	/// Maintains a byte buffer that contains partial messages. [worker thread]
	RingBuffer tcpInboundSocketData;

	/// Reads all available bytes from a stream socket.
	SocketReadResult ReadSocket(size_t &bytesRead); // [worker thread]

	PacketSendResult SendOutPacket(); // [worker thread]
	void SendOutPackets(); // [worker thread]

	void DoUpdateConnection(); // [worker thread]

	unsigned long TimeUntilCanSendPacket() const;

	/// Parses the raw inbound byte stream into messages. [used internally by worker thread]
	void ExtractMessages();

	// The following are temporary data structures used by various internal routines for processing.
	std::vector<NetworkMessage*> serializedMessages; // MessageConnection::TCPSendOutPacket()

	void PerformDisconnection();

	void DumpConnectionStatus() const; // [main thread]
};

} // ~kNet
