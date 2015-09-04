/* Copyright The kNet Project.

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

/** @file UDPMessageConnection.h
	@brief The UDPMessageConnection class. */

// Modified by Lasse Oorni for Urho3D

#include "MessageConnection.h"
#include "SequentialIntegerSet.h"
#include "Array.h"
#include "OrderedHashTable.h"

/*
UDP packet format: 3 bytes if InOrder=false. 5-6 bytes if InOrder=true.
1bit   - InOrder packet.   This packet contains InOrder messages.
1bit   - Reliable packet.  This packet is expected to be Acked by the receiver.
6 bits - The six lowest bits of the PacketID.
u16      The 16 next bits of the PacketID. This gives 22 bits of the PacketID in total.
* u8       InOrder array length.
* N x u8-u16   InOrder PacketID delta counter. VLE-encoded 1.7/8 Only present if InOrder=true.
.Message.
.Message.
...
.Message.


Message format: 2 bytes if FRGSTART=FRAGMENT=false.
1bit - FRGSTART. This is the first fragment of the message (offset=0)
1bit - FRAGMENT. This message is a fragment of a bigger message -flag. If FRGSTART=true, this field is not read and is assumed to be true.
1bit - InOrder. This message may be processed by the application only after all the previous InOrder messages have been processed.
* 1bit - InOrder. This message may be processed by the application only after all the previous InOrder messages have been processed.
* 1bit - InOrder. This message may be processed by the application only after all the previous InOrder messages have been processed.
(Old: 1bit - Unused.)
(Old: 1bit - Unused.)
11 bits Content length (includes both the length of MessageID and Content Data fields)
* u8 InOrder array index.                                         Only present if InOrder=7 (111 in base 2).
u8-u32 # of Fragments in whole message  VLE-encoded 1.7/1.7/16    Only present if FRGSTART=true.
u8 Fragment Transfer ID                                           Only present if FRAGMENT=true or FRGSTART=true.
* New: u8-u32 Fragment number           VLE-encoded 1.7/1.7/16    Only present if FRAGMENT=true and FRGSTART=false.
(Old: u8-u16 Fragment number            VLE-encoded 1.7/8         Only present if FRAGMENT=true.)
.Content.

Content format:
u8-u32 MessageID			      VLE-encoded 1.7/1.7/16
N bytes Content data

*/

namespace kNet
{

class UDPMessageConnection : public MessageConnection
{
public:
	UDPMessageConnection(Network *owner, NetworkServer *ownerServer, Socket *socket, ConnectionState startingState);
	~UDPMessageConnection();

	float RetransmissionTimeout() const { return retransmissionTimeout; }

	float DatagramSendRate() const { return datagramSendRate; }

	void SetDatagramSendRate(float newRateDgramsPerSecond) { datagramSendRate = newRateDgramsPerSecond; }

	float SmoothedRtt() const { return smoothedRTT; }

	float RttVariation() const { return rttVariation; }

	size_t NumOutboundUnackedDatagrams() const { return outboundPacketAckTrack.Size(); }

	size_t NumReceivedUnackedDatagrams() const { return inboundPacketAckTrack.size(); }

	float PacketLossCount() const { return packetLossCount; }

	float PacketLossRate() const { return packetLossRate; }

private:
	/// Reads all the new bytes available in the socket.
	/// @return The number of bytes successfully read.
	virtual SocketReadResult ReadSocket(size_t &bytesRead); // [worker thread]

	/// Parses bytes with have previously been read from the socket to actual application-level messages.
	void ExtractMessages(const char *data, size_t numBytes); // [worker thread]

	/// Reads all available bytes from a datagram socket. This function will read in multiple datagrams
	/// as long as there are available ones to process.
	/// @param bytesRead [out] Returns the total number of bytes containes in the datagrams that were read.
	SocketReadResult UDPReadSocket(size_t &bytesRead); // [worker thread]

	void UpdateRTOCounterOnPacketAck(float rtt); // [worker thread]
	void UpdateRTOCounterOnPacketLoss(); // [worker thread]

	// Closing down the connection:
	void SendDisconnectMessage(bool isInternal); // [main thread]
	void HandleDisconnectMessage(); // [worker thread]
	void SendDisconnectAckMessage(); // [worker thread]
	void HandleDisconnectAckMessage(); // [worker thread]

	// Acknowledging reliable datagrams:
	void PerformPacketAckSends(); // [worker thread]
	void SendPacketAckMessage(); // [worker thread]
	void HandlePacketAckMessage(const char *data, size_t numBytes); // [worker thread]
	
	bool HandleMessage(packet_id_t packetID, message_id_t messageID, const char *data, size_t numBytes); // [worker thread]

	/// Refreshes Packet Loss related statistics.
	void ComputePacketLoss(); // [worker thread]

	/// Marks that we have received a datagram with the given ID.
	void AddReceivedPacketIDStats(packet_id_t packetID); // [worker thread]
	/// @return True if we have received a packet with the given packetID already.
	bool HaveReceivedPacketID(packet_id_t packetID) const; // [worker thread]

	/// Copies the given message to an internal queue to wait to be processed by the worker thread that owns this connection.
	void QueueInboundDatagram(const char *data, size_t numBytes); // [thread-safe].

	/// Handles all the previously queued datagrams this connection has received.
	void ProcessQueuedDatagrams(); // [worker thread]

	/// Specifies the PacketID of the last received datagram with InOrder flag set.
	packet_id_t lastReceivedInOrderPacketID;

	/// Specifies the PacketID of the last sent datagram with InOrder flag set.
	packet_id_t lastSentInOrderPacketID;

	/// A running index to identify packet datagrams as they are send out to the stream.
	packet_id_t datagramPacketIDCounter;

	/// Specifies in milliseconds the currently recommended datagram timeout value for any packet that is sent out at the present time.
	float retransmissionTimeout;

	/// The flow control operates on fixed time window intervals called 'frames'. This variable remembers
	/// when the previous frame ended, and the currently elapsed frame starts.
	tick_t lastFrameTime;
	int numAcksLastFrame;
	int numLossesLastFrame;

	/// The flow control algorithm:
	float datagramSendRate; ///< The number of datagrams/second to send.

	float lowestDatagramSendRateOnPacketLoss;
	int slowModeDelay; ///< Go into slow increase mode for some time on receiving loss

	// These variables correspond to RFC2988, http://tools.ietf.org/html/rfc2988 , section 2.
	bool rttCleared; ///< If true, smoothedRTT and rttVariation do not contain meaningful values, but "are clear".
	float smoothedRTT;
	float rttVariation;

	// The following are used for statistics purposes:

	float packetLossRate; ///< The currently estimated datagram packet loss rate, [0, 1].	
	float packetLossCount; ///< The current packet loss in absolute packets/sec.

	/// Info struct used to track acks of reliable packets.
	struct PacketAckTrack
	{
		PacketAckTrack()
		:sendCount(0)
		{
		}

		/// The timestamp of when a packet with this ID was last sent out.
		tick_t sentTick;

		/// The timestamp of when this packet will time out and can be resent (at the earliest. It will get queued and be resent later)
		tick_t timeoutTick;

		/// The packet ID of the packet that was sent out.
		packet_id_t packetID;

		/// The packet send rate we had when this packet was sent out.
		float datagramSendRate;

		/// The number of times this packet has been sent. 1 denotes no resends. 2 - this packet's been resent once, and so on.
		int sendCount;

		/// If true, the packet with this ID was an inOrder packet.
		bool inOrder;

		/// if inOrder==true, this tells the packetID of the previous in-order packet that was transmitted.
		packet_id_t previousInOrderPacketID;

		Array<NetworkMessage*> messages;

		static int Hash(const PacketAckTrack &item, int maxElemsMask) { return item.packetID & maxElemsMask; }
		static int Hash(int key, int maxElemsMask) { return key & maxElemsMask; }
	};

	void ProcessPacketTimeouts(); // [worker thread]
	void HandleFlowControl(); // [worker thread]

	void DoUpdateConnection(); // [worker thread]

	PacketSendResult SendOutPacket(); // [worker thread]
	void SendOutPackets(); // [worker thread]
	unsigned long TimeUntilCanSendPacket() const; // [worker thread]

	void PerformDisconnection(); // [main thread]

	/// Returns OK if it is acceptable by the flow control timer to send out a new datagram.
	bool CanSendOutNewDatagram() const; // [worker thread]

	/// Called whenever we have sent a new datagram to recompute the datagram send throttle timer.
	void NewDatagramSent(); // [worker thread]

	/// Used to perform flow control on outbound UDP messages.
	mutable tick_t lastDatagramSendTime; ///\todo. No mutable. Rename to nextDatagramSendTime.

	/// Connection control update timer.
	PolledTimer udpUpdateTimer;

	PolledTimer statsUpdateTimer;

	typedef std::map<packet_id_t, PacketAckTrack> PacketAckTrackMap;
	/// Contains the messages we have sent out that we are waiting for the other party to Ack.
//	PacketAckTrackMap outboundPacketAckTrack;
	typedef WaitFreeQueue<PacketAckTrack> PacketAckTrackQueue;
	PacketAckTrackQueue outboundPacketAckTrack;
//	typedef OrderedHashTable<PacketAckTrack, PacketAckTrack> PacketAckTrackTable;
//	PacketAckTrackTable outboundPacketAckTrack;

	static int BiasedBinarySearchFindPacketIndex(UDPMessageConnection::PacketAckTrackQueue &queue, packet_id_t packetID);

	WaitFreeQueue<Datagram> queuedInboundDatagrams;

	void FreeOutboundPacketAckTrack(packet_id_t packetID); // [worker thread]

	// Contains a list of all messages we've received that we need to Ack at some point.
	PacketAckTrackMap inboundPacketAckTrack;

	/// Contains the reliable message numbers of all reliable messages we've received.
	/// Used to detect and discard duplicate messages we've received.
	std::set<unsigned long> receivedReliableMessages;

	SequentialIntegerSet receivedPacketIDs;
	/// Specifies the packet ID of the most recent datagram we sent. Used currently only
	/// for statistics purposes.
	packet_id_t previousReceivedPacketID;

	// The following are temporary data structures used by various internal routines for processing.
	// They are created here as members to avoid having to create objects on the stack at each call to 
	// time-sensitive functions.
	std::vector<NetworkMessage *> datagramSerializedMessages; // MessageConnection::UDPSendOutPacket()
	std::vector<NetworkMessage *> skippedMessages; // MessageConnection::UDPSendOutPacket()
	std::vector<char> assembledData; // MessageConnection::DatagramExtractMessages

	/// Returns the average number of inbound packet loss, packets/sec.
	float GetPacketLossCount() const { return packetLossCount; }

	/// Returns the percentage of inbound packets that are being lost, [0, 1].
	float GetPacketLossRate() const { return packetLossRate; }

	void DumpConnectionStatus() const;

	friend class NetworkServer;
};

} // ~kNet
