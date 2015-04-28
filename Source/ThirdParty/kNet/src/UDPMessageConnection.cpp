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

/** @file UDPMessageConnection.cpp
	@brief Implements the UDP-specific code of MessageConnection.
	\todo Flow control currently disabled since testing out the performance of UDT. */

// Modified by Lasse Oorni for Urho3D

#include <cmath>
#include <cstdio>
#include <sstream>

#include "kNet/Allocator.h"
#ifdef KNET_USE_BOOST
#include <boost/thread/thread.hpp>
#endif

#include "kNet/DebugMemoryLeakCheck.h"
#include "kNet/MessageConnection.h"
#include "kNet/UDPMessageConnection.h"

#include "kNet/NetworkLogging.h"
#include "kNet/DataSerializer.h"
#include "kNet/DataDeserializer.h"
#include "kNet/VLEPacker.h"
#include "kNet/NetException.h"
#include "kNet/Network.h"
#include "kNet/Sort.h"

using namespace std;

namespace kNet
{

/// The maximum time to wait before acking a packet. If there are enough packets to ack for a full ack message,
/// acking will be performed earlier. (milliseconds)
static const float maxAckDelay = 33.f; // (1/30th of a second)
/// The maximum number of datagrams to read in from the socket at one go - after this reads will be throttled
/// to give time for data sending as well.
static const int cMaxDatagramsToReadInOneFrame = 2048;

static const u32 cMaxUDPMessageFragmentSize = 470;

/// Minimum retransmission timeout value (milliseconds)
static const float minRTOTimeoutValue = 500.f;
/// Maximum retransmission timeout value (milliseconds)
static const float maxRTOTimeoutValue = 5000.f;

UDPMessageConnection::UDPMessageConnection(Network *owner, NetworkServer *ownerServer, Socket *socket, ConnectionState startingState)
:MessageConnection(owner, ownerServer, socket, startingState),
retransmissionTimeout(1000.f), numAcksLastFrame(0), numLossesLastFrame(0), smoothedRTT(1000.f), rttVariation(0.f), rttCleared(true), // Set RTT initial values as per RFC 2988.
lastReceivedInOrderPacketID(0), 
lastSentInOrderPacketID(0), datagramPacketIDCounter(1),
packetLossRate(0.f), packetLossCount(0.f), 
datagramSendRate(50.f), lowestDatagramSendRateOnPacketLoss(50.f), slowModeDelay(0),
receivedPacketIDs(64 * 1024), outboundPacketAckTrack(1024),
previousReceivedPacketID(0), queuedInboundDatagrams(128)
{
	KNET_LOG(LogObjectAlloc, "Allocated UDPMessageConnection %p.", this);

	lastFrameTime = Clock::Tick();
	lastDatagramSendTime = Clock::Tick();
}

UDPMessageConnection::~UDPMessageConnection()
{
	KNET_LOG(LogObjectAlloc, "Deleted UDPMessageConnection %p.", this);

	// The first thing we do when starting to close down a connection is to ensure that this connection gets detached from its worker thread.
	// Therefore, as the first thing, invoke CloseConnection which achieves this.
	if (owner)
		owner->CloseConnection(this);

	assert(!workerThread);

	while(outboundPacketAckTrack.Size() > 0)
		FreeOutboundPacketAckTrack(outboundPacketAckTrack.Front()->packetID);

	outboundPacketAckTrack.Clear();
}

void UDPMessageConnection::QueueInboundDatagram(const char *data, size_t numBytes)
{
	if (!data || numBytes == 0)
	{
		KNET_LOG(LogError, "UDPMessageConnection::QueueInboundDatagram: Ignoring received zero-sized datagram!");
		return;
	}
	if (numBytes > cDatagramBufferSize)
	{
		KNET_LOG(LogError, "UDPMessageConnection::QueueInboundDatagram: Discarding received over-sized datagram (%d bytes)!", (int)numBytes);
		return;
	}

	Datagram d;
	memcpy(d.data, data, numBytes);
	d.size = numBytes;
	bool success = queuedInboundDatagrams.Insert(d);
	if (!success)
	{
		KNET_LOG(LogError, "UDPMessageConnection::QueueInboundDatagram: Dropping received datagram, since the client receive buffer is full!");
		return;
	}
}

void UDPMessageConnection::ProcessQueuedDatagrams()
{
	AssertInWorkerThreadContext();

	while(queuedInboundDatagrams.Size() > 0)
	{
		Datagram *d = queuedInboundDatagrams.Front();
		ExtractMessages((const char*)d->data, d->size);
		queuedInboundDatagrams.PopFront();
	}
}

UDPMessageConnection::SocketReadResult UDPMessageConnection::ReadSocket(size_t &bytesRead)
{
	AssertInWorkerThreadContext();

	assert(!socket || socket->TransportLayer() == SocketOverUDP);

	SocketReadResult readResult = UDPReadSocket(bytesRead);

	///\todo Replace with ConnectSyn,ConnectSynAck and ConnectAck.
	if (bytesRead > 0 && connectionState == ConnectionPending)
	{
		connectionState = ConnectionOK;
		KNET_LOG(LogUser, "UDPMessageConnection::ReadSocket: Received data from socket %s. Transitioned from ConnectionPending to ConnectionOK state.", 
			(socket ? socket->ToString().c_str() : "(null)"));
	}
	if (readResult == SocketReadError)
		return SocketReadError;
	if (readResult == SocketReadThrottled)
		return SocketReadThrottled;
	if (bytesRead > 0)
		KNET_LOG(LogData, "Received %d bytes from UDP socket.", (int)bytesRead);
	return SocketReadOK;
}

void UDPMessageConnection::PerformPacketAckSends()
{
	AssertInWorkerThreadContext();

	tick_t now = Clock::Tick();
	while(!inboundPacketAckTrack.empty())
	{
		if (Clock::TimespanToMillisecondsF(inboundPacketAckTrack.begin()->second.sentTick, now) < maxAckDelay &&
			inboundPacketAckTrack.size() < 33)
			break;

		SendPacketAckMessage();
	}
}

UDPMessageConnection::SocketReadResult UDPMessageConnection::UDPReadSocket(size_t &totalBytesRead)
{
	AssertInWorkerThreadContext();

	if (!socket || !socket->IsReadOpen())
		return SocketReadError;

	totalBytesRead = 0;

	// Read in all the bytes that are available in the socket.

	// Cap the number of datagrams to read in a single loop to perform throttling.
	int maxReads = cMaxDatagramsToReadInOneFrame;
	while(maxReads-- > 0)
	{
		assert(socket);
		OverlappedTransferBuffer *data = socket->BeginReceive();
		if (!data || data->bytesContains == 0)
			break;

		totalBytesRead += data->bytesContains;

		KNET_LOG(LogData, "UDPReadSocket: Received %d bytes from Begin/EndReceive.", data->bytesContains);
		ExtractMessages(data->buffer.buf, data->bytesContains);

		// Done with the received data buffer. Free it up for a future socket read.
		socket->EndReceive(data);
	}

	if (maxReads == 0)
	{
		KNET_LOG(LogError, "Warning: Too many inbound messages: Datagram read loop throttled!");
		return SocketReadThrottled;
	}
	else
		return SocketReadOK;
}

/// Checks whether any reliably sent packets have timed out.
void UDPMessageConnection::ProcessPacketTimeouts() // [worker thread]
{
	AssertInWorkerThreadContext();

	if (!socket || !socket->IsWriteOpen())
		return;

	assert(socket->TransportLayer() == SocketOverUDP);

	const tick_t now = Clock::Tick();

	int numPacketsTimedOut = 0;

	// Check whether any reliable packets have timed out and not acked.
	while(outboundPacketAckTrack.Size() > 0)
	{
		PacketAckTrack *track = outboundPacketAckTrack.Front();
		if (!track || Clock::IsNewer(track->timeoutTick, now))
			return; // Note here: for optimization purposes, the packets will time out in the order they were sent.

		++numPacketsTimedOut;
			
		KNET_LOG(LogVerbose, "A packet with ID %d timed out. Age: %.2fms. Contains %d messages.", 
			(int)track->packetID, (float)Clock::TimespanToMillisecondsD(track->sentTick, now), (int)track->messages.size());
		ADDEVENT("datagramsLost", 1, "");

		// Store a new suggestion for a lowered datagram send rate.
		lowestDatagramSendRateOnPacketLoss = min(lowestDatagramSendRateOnPacketLoss, track->datagramSendRate);

		// Adjust the flow control values on this event.
		UpdateRTOCounterOnPacketLoss();

		// Put all messages back into the outbound queue for send repriorisation.
		for(size_t i = 0; i < track->messages.size(); ++i)
#ifdef KNET_NO_MAXHEAP
			outboundQueue.InsertWithResize(track->messages[i]);
#else
			outboundQueue.Insert(track->messages[i]);
#endif

		// We are not going to resend the old timed out packet as-is with the old packet ID. Instead, just forget about it.
		// The messages will go to a brand new packet with new packet ID.
		outboundPacketAckTrack.PopFront();
	}
}

void UDPMessageConnection::HandleFlowControl()
{
	AssertInWorkerThreadContext();

	// In packets/second.
	const float minBandwidthOnLoss = 10.f;
	const float minBandwidth = 50.f;
	const float maxBandwidth = 10000.f;
	const int framesPerSec = 10;
	const int maxSlowModeDelay = 10 * framesPerSec;

	const tick_t frameLength = Clock::TicksPerSec() / framesPerSec; // in ticks
	const tick_t now = Clock::Tick();

	unsigned long numFrames = (unsigned long)(Clock::TicksInBetween(now, lastFrameTime) / frameLength);
	if (numFrames > 0)
	{
		if (numFrames >= framesPerSec)
			numFrames = framesPerSec;

		int numUnacked = NumOutboundUnackedDatagrams();

		// Reduce sendrate on significant loss
		if (numLossesLastFrame > 2)
		{
			float oldRate = datagramSendRate;
			datagramSendRate = min(datagramSendRate, max(minBandwidthOnLoss, lowestDatagramSendRateOnPacketLoss * 0.9f)); // Multiplicative decreases.
			KNET_LOG(LogVerbose, "Received %d losses. datagramSendRate backed to %.2f from %.2f", (int)numLossesLastFrame, datagramSendRate, oldRate);
		}
		else
		{
			// Check if more or less bandwidth is needed
			///\todo Very simple logic for now, can be improved
			bool needMore = outboundQueue.Size() > 10;
			bool needLess = outboundQueue.Size() == 0;
			float maxRTT = max(rtt, smoothedRTT);

			// Need more: increase sendrate. Factor in RTT and acks
			if (needMore && numLossesLastFrame == 0)
		{
				float delta = (50.f + 2.f * numAcksLastFrame) / maxRTT;
				if (slowModeDelay > 0)
					delta *= 0.2f;
				datagramSendRate = min(datagramSendRate + delta, maxBandwidth);
			lowestDatagramSendRateOnPacketLoss = datagramSendRate;
//			KNET_LOG(LogVerbose, "Incremented sendRate by %.2f to %.2f", increment, datagramSendRate);
		}
			// Need less: decrease sendrate if not already at minimum
			else if (needLess && datagramSendRate > minBandwidth)
				datagramSendRate = max(datagramSendRate * 0.98f, minBandwidth);

			// Whenever slow mode or slight loss is occurring and RTT is more than the minimum RTO value, back off slowly
			// This is to ensure we do not stay "balanced" in a state where slight loss occurs constantly due to sending too much
			if ((numLossesLastFrame > 0 || slowModeDelay > 0) && maxRTT > minRTOTimeoutValue && datagramSendRate > minBandwidth)
				datagramSendRate = max(datagramSendRate * 0.999f, minBandwidth);
		}

		// Update the slow mode timer
		if (numLossesLastFrame > 1)
			slowModeDelay = min(slowModeDelay + numLossesLastFrame * framesPerSec, maxSlowModeDelay);
		else if (slowModeDelay > 0)
			--slowModeDelay;

		numAcksLastFrame = 0;
		numLossesLastFrame = 0;
		lastFrameTime = now;
	}
}

void UDPMessageConnection::SendOutPackets()
{
	AssertInWorkerThreadContext();

	if (!socket || !socket->IsWriteOpen())
		return;

	PacketSendResult result = PacketSendOK;
	int maxSends = 50;
	while(result == PacketSendOK && TimeUntilCanSendPacket() == 0 && maxSends-- > 0)
		result = SendOutPacket();
}

/// Returns the 'earlier' of the two message numbers, taking number wrap-around into account.
unsigned long PrecedingMessageNumber(unsigned long num1, unsigned long num2)
{
	if ((unsigned long)(num2 - num1) < 0x80000000)
		return num1;
	else
		return num2;
}

/// Packs several messages from the outbound priority queue into a single packet and sends it out the wire.
/// @return False if the send was a failure and sending should not be tried again at this time, true otherwise.
MessageConnection::PacketSendResult UDPMessageConnection::SendOutPacket()
{
	AssertInWorkerThreadContext();

	if (!socket || !socket->IsWriteOpen())
		return PacketSendSocketClosed;

	// If the main thread has asked the worker thread to hold sending any messages, stop here already.
	if (bOutboundSendsPaused)
		return PacketSendNoMessages;

	if (outboundQueue.Size() == 0)
		return PacketSendNoMessages;

	// If we aren't yet allowed to send out the next datagram, return.
	if (!CanSendOutNewDatagram())
		return PacketSendThrottled;

    OverlappedTransferBuffer *data = socket->BeginSend(socket->MaxSendSize());
	if (!data)
		return PacketSendThrottled;

//	const size_t minSendSize = 1;
	const size_t maxSendSize = socket->MaxSendSize();

	// Push out all the pending data to the socket.
	datagramSerializedMessages.clear();

	// If true, the receiver needs to Ack the packet we are now crafting.
	bool reliable = false;
	// If true, the packet contains in-order deliverable messages.
	bool inOrder = false;

	int packetSizeInBytes = 7; // The datagram header takes up 3-7 bytes. (PacketID + Flags take at least three bytes to start with)
	const int cBytesForInOrderDeltaCounter = 2;

	unsigned long smallestReliableMessageNumber = 0xFFFFFFFF;

	skippedMessages.clear();

	// Fill up the rest of the packet from messages from the outbound queue.
	while(outboundQueue.Size() > 0)
	{
#ifdef KNET_NO_MAXHEAP
		NetworkMessage *msg = *outboundQueue.Front();
#else
		NetworkMessage *msg = outboundQueue.Front();
#endif
		if (msg->obsolete)
		{
			outboundQueue.PopFront();
			ClearOutboundMessageWithContentID(msg);
			FreeMessage(msg);
			continue;
		}

		// If we're sending a fragmented message, allocate a new transferID for that message,
		// or skip it if there are no transferIDs free.
		if (msg->transfer)
		{
			KNET_LOG(LogVerbose, "Sending out a fragmented transfer.");
			Lock<FragmentedSendManager> sends = fragmentedSends.Acquire();
			if (msg->transfer->id == -1)
			{
				bool success = sends->AllocateFragmentedTransferID(*msg->transfer);

				if (!success) // No transferIDs free - skip this message for now.
				{
					KNET_LOG(LogError, "Throttling fragmented transfer send! No free TransferID to start a new fragmented transfer with!");
					outboundQueue.PopFront();
					skippedMessages.push_back(msg);
					continue;
				}
			}
		}

		// We need to add extra 2 bytes for the VLE-encoded InOrder PacketID delta counter.
		// Estimate the size the per-message header consumes at most.
		// This computation is not exact, but as it only needs to be an upper bound, keeping it simple is good. \todo Can be more precise here.
		int totalMessageSize = msg->GetTotalDatagramPackedSize();// + ((msg->inOrder && !inOrder) ? cBytesForInOrderDeltaCounter : 0);

		// If this message won't fit into the buffer, send out all the previously gathered messages (there must at least be one previously submitted message).		
		if (!datagramSerializedMessages.empty() && (size_t)packetSizeInBytes + totalMessageSize >= maxSendSize)
			break;

		if (totalMessageSize > (int)maxSendSize)
			KNET_LOG(LogError, "Warning: Sending out a message of ID %d and size %d bytes, but UDP socket max send size is only %d bytes!", (int)msg->id, totalMessageSize, (int)maxSendSize);

		datagramSerializedMessages.push_back(msg);
		outboundQueue.PopFront();

		packetSizeInBytes += totalMessageSize;

		if (msg->reliable)
		{
			reliable = true;
			smallestReliableMessageNumber = (smallestReliableMessageNumber == 0xFFFFFFFF) ? msg->reliableMessageNumber : PrecedingMessageNumber(smallestReliableMessageNumber, msg->reliableMessageNumber);
		}

		if (msg->inOrder)
			inOrder = true;
	}

	// Ensure that the range of the message numbers is within the capacity that the protocol can represent in the byte stream.
	for(size_t i = 0; i < datagramSerializedMessages.size(); ++i)
		if (datagramSerializedMessages[i]->reliable)
		{
			u32 reliableDelta = (u32)(datagramSerializedMessages[i]->reliableMessageNumber - smallestReliableMessageNumber);
			if (reliableDelta > VLE8_16::maxValue) // We use a VLE8_16 to store deltas, so 32767 is the largest delta we can store. If two messages have a delta larger than this,
			{                                      // they will have to be serialized in separate datagrams.
				KNET_LOG(LogError, "UDPMessageConnection::SendOutPacket: Too large msgnum delta present - skipping serialization of message with ID %d (lowest: %d, delta: %d)",
					(int)datagramSerializedMessages[i]->reliableMessageNumber, (int)smallestReliableMessageNumber, (int)reliableDelta);
				skippedMessages.push_back(datagramSerializedMessages[i]);
				datagramSerializedMessages.erase(datagramSerializedMessages.begin() + i);
				--i;
			}
		}

	// If we had skipped any messages from the outbound queue while looking for good messages to send, put all the messages
	// we skipped back to the outbound queue to wait to be processed during subsequent frames.
	for(size_t i = 0; i < skippedMessages.size(); ++i)
#ifdef KNET_NO_MAXHEAP
		outboundQueue.InsertWithResize(skippedMessages[i]);
#else
		outboundQueue.Insert(skippedMessages[i]);
#endif

	// Finally proceed to crafting the actual UDP packet.
	DataSerializer writer(data->buffer.buf, data->buffer.len);

	const packet_id_t packetID = datagramPacketIDCounter;
	writer.Add<u8>((u8)((packetID & 63) | ((reliable ? 1 : 0) << 6)  | ((inOrder ? 1 : 0) << 7)));
	writer.Add<u16>((u16)(packetID >> 6));
	if (reliable)
	{
		assert((smallestReliableMessageNumber & 0x80000000) == 0);
		writer.AddVLE<VLE16_32>(smallestReliableMessageNumber);
	}

	bool sentDisconnectMessage = false;
	bool sentDisconnectAckMessage = false;

	// Write all the messages in this UDP packet.
	for(size_t i = 0; i < datagramSerializedMessages.size(); ++i)
	{
		NetworkMessage *msg = datagramSerializedMessages[i];
		assert(!msg->transfer || msg->transfer->id != -1);

		const int encodedMsgIdLength = (msg->transfer == 0 || msg->fragmentIndex == 0) ? VLE8_16_32::GetEncodedBitLength(msg->id)/8 : 0;
		const size_t messageContentSize = msg->dataSize + encodedMsgIdLength; // 1/2/4 bytes: Message ID. X bytes: Content.
		assert(messageContentSize < (1 << 11));

		if (msg->id == MsgIdDisconnect)
			sentDisconnectMessage = true;
		else if (msg->id == MsgIdDisconnectAck)
			sentDisconnectAckMessage = true;

		const u16 reliable = (msg->reliable ? 1 : 0) << 12;
		const u16 inOrder = (msg->inOrder ? 1 : 0) << 13;
		const u16 fragmentedTransfer = (msg->transfer != 0 ? 1 : 0) << 14;
		const u16 firstFragment = (msg->transfer != 0 && msg->fragmentIndex == 0 ? 1 : 0) << 15;
		writer.Add<u16>((u16)messageContentSize | reliable | inOrder | fragmentedTransfer | firstFragment);

		if (msg->reliable)
			writer.AddVLE<VLE8_16>((u32)(msg->reliableMessageNumber - smallestReliableMessageNumber));

		///\todo Add the InOrder index here to track which datagram/message we depended on.

		assert((!firstFragment && !fragmentedTransfer) || msg->transfer);

		if (firstFragment != 0)
			writer.AddVLE<VLE8_16_32>(msg->transfer->totalNumFragments);
		if (fragmentedTransfer != 0)
			writer.Add<u8>((u8)msg->transfer->id);
		if (firstFragment == 0 && fragmentedTransfer != 0)
			writer.AddVLE<VLE8_16_32>(msg->fragmentIndex); // The message fragment number.
		if (msg->transfer == 0 || msg->fragmentIndex == 0)
			writer.AddVLE<VLE8_16_32>(msg->id); // Add the message ID number.
		if (msg->dataSize > 0) // Add the actual message payload data.
		{
			if (networkSendSimulator.enabled && 
				(networkSendSimulator.corruptionType == NetworkSimulator::CorruptPayload ||
				(networkSendSimulator.corruptionType == NetworkSimulator::CorruptMessageType &&
				 msg->id == networkSendSimulator.corruptMessageId)))
				 networkSendSimulator.MaybeCorruptBufferToggleBits(msg->data, msg->dataSize);
			writer.AddAlignedByteArray(msg->data, msg->dataSize);
		}
	}

	// Send the crafted packet out to the socket.
	data->bytesContains = writer.BytesFilled();
	bool success;

	if (!networkSendSimulator.enabled)
		success = socket->EndSend(data); // Send the data out.
	else
	{
		// We're running a network simulator. Pass the buffer to networkSendSimulator for delayed sending.
		networkSendSimulator.SubmitSendBuffer(data, socket);
		success = true; // Act here as if we succeeded.
	}

	if (!success)
	{
		// We failed, so put all messages back to the outbound queue, except for those that are from old in-order packet,
		// since they need to be resent with the old packet ID and not as fresh messages.
		for(size_t i = 0; i < datagramSerializedMessages.size(); ++i)
			outboundQueue.Insert(datagramSerializedMessages[i]);

		KNET_LOG(LogError, "UDPMessageConnection::SendOutPacket: Socket::EndSend failed to socket %s!", socket->ToString().c_str());
		return PacketSendSocketFull;
	}

	// Sending the datagram succeeded - increment the send count of each message by one, to remember the retry timeout count.
	for(size_t i = 0; i < datagramSerializedMessages.size(); ++i)
	{
		++datagramSerializedMessages[i]->sendCount;

#ifdef KNET_NETWORK_PROFILING
		std::stringstream ss;
		if (!datagramSerializedMessages[i]->profilerName.empty())
			ss << "messageOut." << datagramSerializedMessages[i]->profilerName;
		else
			ss << "messageOut." << datagramSerializedMessages[i]->id;
		ADDEVENT(ss.str().c_str(), (float)datagramSerializedMessages[i]->Size(), "bytes");
		if (datagramSerializedMessages[i]->transfer)
		{
			if (datagramSerializedMessages[i]->fragmentIndex > 0)
				ADDEVENT("FragmentedSend_Fragment", 1, "");
			ADDEVENT("FragmentedSend_Start", 1, "");
		}
#endif
	}

	assert(socket->TransportLayer() == SocketOverUDP);

	// Now we have to wait 1/datagramSendRate seconds again until we can send the next datagram.
	NewDatagramSent();

	// The send was successful, we can increment our next free PacketID counter to use for the next packet.
	lastSentInOrderPacketID = datagramPacketIDCounter;
	datagramPacketIDCounter = AddPacketID(datagramPacketIDCounter, 1);

	AddOutboundStats(writer.BytesFilled(), 1, datagramSerializedMessages.size());
	ADDEVENT("datagramOut", (float)writer.BytesFilled(), "bytes");

	if (reliable)
	{
		// Now that we have sent a reliable datagram, remember all messages that were
		// serialized into this datagram so that we can properly resend the messages in the datagram if it times out.
		PacketAckTrack ack;
		ack.packetID = packetID;
		const tick_t now = Clock::Tick();
		ack.sendCount = 1;
		ack.sentTick = now;
		retransmissionTimeout = 5000.f; ///\todo Remove this.
		ack.timeoutTick = now + (tick_t)((double)retransmissionTimeout * Clock::TicksPerMillisecond());
		ack.datagramSendRate = datagramSendRate;

		for(size_t i = 0; i < datagramSerializedMessages.size(); ++i)
		{
			if (datagramSerializedMessages[i]->reliable)
				ack.messages.push_back(datagramSerializedMessages[i]); // The ownership of these messages is transferred into this struct.
			else
			{
				ClearOutboundMessageWithContentID(datagramSerializedMessages[i]);
				FreeMessage(datagramSerializedMessages[i]);
			}
		}
		outboundPacketAckTrack.InsertWithResize(ack);
	}
	else // We sent an unreliable datagram.
	{
		// This is send-and-forget, we can free all the message data we just sent.
		for(size_t i = 0; i < datagramSerializedMessages.size(); ++i)
		{
			ClearOutboundMessageWithContentID(datagramSerializedMessages[i]);
			FreeMessage(datagramSerializedMessages[i]);
		}
	}

	// If we sent out the Disconnect message, it means we have closed our write connection, but are still
	// half-open to receive data.
	if (sentDisconnectMessage)
	{
		if (connectionState != ConnectionClosed && connectionState != ConnectionPeerClosed)
			connectionState = ConnectionDisconnecting;
		if (connectionState == ConnectionPeerClosed)
			connectionState = ConnectionClosed;
		if (socket)
			socket->MarkWriteClosed();
		KNET_LOG(LogInfo, "UDPMessageConnection::SendOutPacket: Send Disconnect from connection %s.", ToString().c_str());
	}
	// If we sent out the DisconnectAck message, we can tear down the connection right now - we're finished.
	if (sentDisconnectAckMessage)
	{
		if (socket)
		{
			socket->MarkReadClosed();
			socket->MarkWriteClosed();
		}
		connectionState = ConnectionClosed;
		KNET_LOG(LogInfo, "UDPMessageConnection::SendOutPacket: Send DisconnectAck from connection %s.", ToString().c_str());
	}

	KNET_LOG(LogVerbose, "UDPMessageConnection::SendOutPacket: Socket::EndSend succeeded with %d bytes.", (int)writer.BytesFilled());
	return PacketSendOK;
}

void UDPMessageConnection::DoUpdateConnection()
{
	AssertInWorkerThreadContext();

	ProcessQueuedDatagrams();

	if (udpUpdateTimer.TriggeredOrNotRunning())
	{
		// We can send out data now. Perform connection management before sending out any messages.
		ProcessPacketTimeouts();
		HandleFlowControl();

		// Generate an Ack message if we've accumulated enough reliable messages to make it
		// worthwhile or if some of them are timing out.
		PerformPacketAckSends();

		ADDEVENT("retransmissionTimeout", RetransmissionTimeout(), "msecs");
		ADDEVENT("datagramSendRate", DatagramSendRate(), "msgs");
		ADDEVENT("smoothedRtt", SmoothedRtt(), "msecs");
		ADDEVENT("rttVariation", RttVariation(), "");
		ADDEVENT("numOutboundUnackedDatagrams", (float)NumOutboundUnackedDatagrams(), "");
		ADDEVENT("numReceivedUnackedDatagrams", (float)NumReceivedUnackedDatagrams(), "");
		ADDEVENT("packetLossCount", PacketLossCount(), "");
		ADDEVENT("packetLossRate", PacketLossRate(), "");

		udpUpdateTimer.StartMSecs(10.f);
	}

/*
	if (statsUpdateTimer.TriggeredOrNotRunning())
	{
		///\todo Put this behind a timer - update only once every 1 sec or so.
		ComputePacketLoss();
		statsUpdateTimer.StartMSecs(1000.f);
	}
*/
}

unsigned long UDPMessageConnection::TimeUntilCanSendPacket() const
{
	const tick_t now = Clock::Tick();

	// The interval at which we send out datagrams.
	const tick_t datagramSendTickDelay = (tick_t)(Clock::TicksPerSec() / datagramSendRate);

	const tick_t nextDatagramSendTime = lastDatagramSendTime + datagramSendTickDelay;

	if (Clock::IsNewer(now, nextDatagramSendTime))
		return 0; // We are already due to send out the next datagram?

	return (unsigned long)Clock::TimespanToMillisecondsF(now, nextDatagramSendTime);
}

bool UDPMessageConnection::HaveReceivedPacketID(packet_id_t packetID) const
{
	return receivedPacketIDs.Exists(packetID);
}

void UDPMessageConnection::AddReceivedPacketIDStats(packet_id_t packetID)
{
	AssertInWorkerThreadContext();

	/* \todo add back to enable packet loss computations.
	ConnectionStatistics &cs = statistics.Lock();

	// Simple method to prevent computation errors caused by wraparound - we start from scratch when packet with ID 0 is received.
//	if (packetID == 0)
//		cs.recvPacketIDs.clear();

	cs.recvPacketIDs.push_back(ConnectionStatistics::DatagramIDTrack());
	ConnectionStatistics::DatagramIDTrack &t = cs.recvPacketIDs.back();
	t.tick = Clock::Tick();
	t.packetID = packetID;
//	KNET_LOG(LogVerbose, "Marked packet with ID %d received.", (int)packetID);
	statistics.Unlock();
*/
	// Remember this packet ID for duplicacy detection and pruning purposes.
	receivedPacketIDs.Add(packetID);

	previousReceivedPacketID = packetID;
}

void UDPMessageConnection::ExtractMessages(const char *data, size_t numBytes)
{
	AssertInWorkerThreadContext();

	assert(data);
	assert(numBytes > 0);

	ADDEVENT("datagramIn", (float)numBytes, "bytes");

	// Immediately discard this datagram if it might contain more messages than we can handle. Otherwise
	// we might end up in a situation where we have already applied some of the messages in the datagram
	// and realize we don't have space to take in the rest, which would require a "partial ack" of sorts.
	if (inboundMessageQueue.CapacityLeft() < 64)
	{
		ADDEVENT("inputDiscarded", (float)numBytes, "bytes");
		return;
	}

	lastHeardTime = Clock::Tick();

	if (numBytes < 3)
	{
		KNET_LOG(LogError, "Malformed UDP packet when reading packet header! Size = %d bytes, no space for packet header, which is at least 3 bytes.", (int)numBytes);
		throw NetException("Malformed UDP packet received! No packed header present.");
	}

	DataDeserializer reader(data, numBytes);

	// Start by reading the packet header (flags, packetID).
	u8 flags = reader.Read<u8>();
	bool inOrder = (flags & (1 << 7)) != 0;
	bool packetReliable = (flags & (1 << 6)) != 0;
	packet_id_t packetID = (reader.Read<u16>() << 6) | (flags & 63);

	unsigned long reliableMessageIndexBase = (packetReliable ? reader.ReadVLE<VLE16_32>() : 0); ///\todo sanitize input length.

	// If the 'reliable'-flag is set, remember this PacketID, we need to Ack it later on.
	if (packetReliable)
	{
		PacketAckTrack &t = inboundPacketAckTrack[packetID];
		t.packetID = packetID;
		// The following are not used right now.
		///\todo If we want to queue up a few acks before sending an ack message, we should possibly save here
		// the time when we received the packet.
		t.sentTick = Clock::Tick();
	}

	// Note that this check must be after the ack check (above), since we still need to ack the new packet as well (our
	// previous ack might not have reached the sender or was delayed, which is why the peer is resending it).
	if (HaveReceivedPacketID(packetID))
	{
		ADDEVENT("duplicateReceived", (float)numBytes, "bytes");
		KNET_LOG(LogVerbose, "Duplicate datagram with packet ID %d received!", (int)packetID);
		return;
	}
	if (packetID != previousReceivedPacketID + 1)
		ADDEVENT("outOfOrderReceived", fabs((float)(packetID - (previousReceivedPacketID + 1))), "");

	// If the 'inOrder'-flag is set, there's an extra 'Order delta counter' field present,
	// that specifies the processing ordering of this packet.
	packet_id_t inOrderID = 0;
	if (inOrder)
	{
//		inOrderID = reader.ReadVLE<VLE8_16>();
		if (inOrderID == DataDeserializer::VLEReadError)
		{
			KNET_LOG(LogError, "Malformed UDP packet! Size = %d bytes, no space for packet header field 'inOrder'!", (int)numBytes);
			throw NetException("Malformed UDP packet received! The inOrder field was invalid.");
		}
	}

	size_t numMessagesReceived = 0;
	while(reader.BytesLeft() > 0)
	{
		if (reader.BytesLeft() < 2)
		{
			KNET_LOG(LogError, "Malformed UDP packet! Parsed %d messages ok, but after that there's not enough space for UDP message header! BytePos %d, total size %d",
				(int)reader.BytePos(), (int)numBytes);
			throw NetException("Malformed UDP packet received! Message header was not present.");
		}

		// Read the message header (2 bytes at least).
		u16 contentLength = reader.Read<u16>();
		bool fragmentStart = (contentLength & (1 << 15)) != 0;
		bool fragment = (contentLength & (1 << 14)) != 0 || fragmentStart; // If fragmentStart is set, then fragment is set.
		bool inOrder = (contentLength & (1 << 13)) != 0;
		bool messageReliable = (contentLength & (1 << 12)) != 0;
		contentLength &= (1 << 11) - 1;

		// If true, this message is a duplicate one we've received, and will be discarded. We need to parse it fully though,
		// to be able to parse the messages that come after it.
		bool duplicateMessage = false; 

		unsigned long reliableMessageNumber = 0;
		if (messageReliable)
		{
			if (!packetReliable)
				KNET_LOG(LogError, "Received reliable message on a packet that is not reliable!");

			reliableMessageNumber = reliableMessageIndexBase + reader.ReadVLE<VLE8_16>();

			if (receivedReliableMessages.find(reliableMessageNumber) != receivedReliableMessages.end())
				duplicateMessage = true;
			else 
				receivedReliableMessages.insert(reliableMessageNumber);
		}

		if (contentLength == 0)
		{
			KNET_LOG(LogError, "Malformed UDP packet! Byteofs %d, Packet length %d. Message had zero length (Length must be at least one byte)!", (int)reader.BytePos(), (int)numBytes);
			throw NetException("Malformed UDP packet received! Messages with zero content length are not valid.");
		}

		u32 numTotalFragments = (fragmentStart ? reader.ReadVLE<VLE8_16_32>() : 0);
		u8 fragmentTransferID = (fragment ? reader.Read<u8>() : 0);
		u32 fragmentNumber = (fragment && !fragmentStart ? reader.ReadVLE<VLE8_16_32>() : 0);

		if (reader.BytesLeft() < contentLength)
		{
			KNET_LOG(LogError, "Malformed UDP packet! Byteofs %d, Packet length %d. Expected %d bytes of message content, but only %d bytes left!",
				(int)reader.BytePos(), (int)numBytes, (int)contentLength, (int)reader.BytesLeft());
			throw NetException("Malformed UDP packet received! Message payload missing.");
		}

		if (!duplicateMessage)
		{
			// If we received the start of a new fragment, start tracking a new fragmented transfer.
			if (fragmentStart)
			{
				if (numTotalFragments == DataDeserializer::VLEReadError || numTotalFragments <= 1)
				{
					KNET_LOG(LogError, "Malformed UDP packet! This packet had fragmentStart bit on, but parsing numTotalFragments VLE failed!");
					throw NetException("Malformed UDP packet received! This packet had fragmentStart bit on, but parsing numTotalFragments VLE failed!");
				}

				fragmentedReceives.NewFragmentStartReceived(fragmentTransferID, numTotalFragments, &data[reader.BytePos()], contentLength);
				ADDEVENT("FragmentStartReceived", 1, "");

			}
			// If we received a fragment that is a part of an old fragmented transfer, pass it to the fragmented transfer manager
			// so that it can reconstruct the final stream when the transfer finishes.
			else if (fragment)
			{
				if (fragmentNumber == DataDeserializer::VLEReadError)
				{
					KNET_LOG(LogError, "Malformed UDP packet! This packet has fragment flag on, but parsing the fragment number failed!");
					throw NetException("Malformed UDP packet received! This packet has fragment flag on, but parsing the fragment number failed!");
				}

				ADDEVENT("FragmentReceived", 1, "");

				bool messageReady = fragmentedReceives.NewFragmentReceived(fragmentTransferID, fragmentNumber, &data[reader.BytePos()], contentLength);
				if (messageReady)
				{
					// This was the last fragment of the whole message - reconstruct the message from the fragments and pass it on to
					// the client to handle.
					assembledData.clear();
					fragmentedReceives.AssembleMessage(fragmentTransferID, assembledData);
					assert(!assembledData.empty());
					///\todo InOrder.
					HandleInboundMessage(packetID, &assembledData[0], assembledData.size());
					++numMessagesReceived;
					fragmentedReceives.FreeMessage(fragmentTransferID);
				}
			}
			else
			{
				// Not a fragment, so directly call the handling code.
				HandleInboundMessage(packetID, &data[reader.BytePos()], contentLength);
				++numMessagesReceived;
			}
		}
		else // this is a duplicate reliable message, ignore it.
		{
			///\todo Can we remove this duplicate reliable message checking?
			KNET_LOG(LogVerbose, "Received a duplicate reliable message with message number %d!", (int)reliableMessageNumber);
		}

		reader.SkipBytes(contentLength);
	}

	// Store the packetID for inbound packet loss statistics purposes.
	AddReceivedPacketIDStats(packetID);
	// Save general statistics (bytes, packets, messages rate).
	AddInboundStats(numBytes, 1, numMessagesReceived);
}

void UDPMessageConnection::PerformDisconnection()
{
	AssertInMainThreadContext();

	SendDisconnectMessage(false);
}

bool UDPMessageConnection::CanSendOutNewDatagram() const
{
	const tick_t now = Clock::Tick();

	const tick_t datagramSendTickDelay = (tick_t)(Clock::TicksPerSec() / datagramSendRate);

	return Clock::TicksInBetween(now, lastDatagramSendTime) >= datagramSendTickDelay;
}

void UDPMessageConnection::NewDatagramSent()
{
	const tick_t datagramSendTickDelay = (tick_t)(Clock::TicksPerSec() / datagramSendRate);
	const tick_t now = Clock::Tick();

	if (Clock::TicksInBetween(now, lastDatagramSendTime) / datagramSendTickDelay < 20)
		lastDatagramSendTime += datagramSendTickDelay;
	else
		lastDatagramSendTime = now;
}

void UDPMessageConnection::SendDisconnectMessage(bool isInternal)
{
	AssertInMainThreadContext();

	NetworkMessage *msg = StartNewMessage(MsgIdDisconnect, 0);
	msg->priority = NetworkMessage::cMaxPriority; ///\todo Highest or lowest priority depending on whether to finish all pending messages?
	msg->reliable = true;
#ifdef KNET_NETWORK_PROFILING
	msg->profilerName = "Disconnect (0x3FFFFFFF)";
#endif
	EndAndQueueMessage(msg, 0, isInternal);

	KNET_LOG(LogInfo, "UDPMessageConnection::SendDisconnectMessage: Sent Disconnect.");
}

void UDPMessageConnection::SendDisconnectAckMessage()
{
	AssertInWorkerThreadContext();

	NetworkMessage *msg = StartNewMessage(MsgIdDisconnectAck, 0);
	msg->priority = NetworkMessage::cMaxPriority; ///\todo Highest or lowest priority depending on whether to finish all pending messages?
	msg->reliable = false;
#ifdef KNET_NETWORK_PROFILING
	msg->profilerName = "DisconnectAck (0x3FFFFFFE)";
#endif
	EndAndQueueMessage(msg, 0, true); ///\todo Check this flag!

	KNET_LOG(LogInfo, "UDPMessageConnection::SendDisconnectAckMessage: Sent DisconnectAck.");
}

int UDPMessageConnection::BiasedBinarySearchFindPacketIndex(PacketAckTrackQueue &queue, packet_id_t packetID)
{
	///\bug Make this all packetID wrap-around -aware.

	int headIdx = 0;
	PacketAckTrack *headItem = queue.ItemAt(headIdx);
	if (headItem->packetID == packetID)
		return headIdx;
	int tailIdx = queue.Size()-1;
	PacketAckTrack *tailItem = queue.ItemAt(tailIdx);
	if (tailItem->packetID == packetID)
		return tailIdx;
	assert(headItem->packetID < tailItem->packetID);
	if (headItem->packetID > packetID || tailItem->packetID < packetID)
		return -1;
	while(headIdx < tailIdx)
	{
		int newIdx = (tailIdx - headIdx) * (packetID - headItem->packetID) / (tailItem->packetID - headItem->packetID);
		newIdx = max(headIdx+1, min(tailIdx-1, newIdx));
		PacketAckTrack *newItem = queue.ItemAt(newIdx);
		if (newItem->packetID == packetID)
			return newIdx;
		else if (newItem->packetID < packetID)
		{
			headIdx = newIdx;
			headItem = newItem;
		}
		else
		{
			tailIdx = newIdx;
			tailItem = newItem;
		}
	}
	return -1;
}

void UDPMessageConnection::FreeOutboundPacketAckTrack(packet_id_t packetID)
{
	AssertInWorkerThreadContext();

	int itemIndex = 0;
	for(; itemIndex < outboundPacketAckTrack.Size(); ++itemIndex)
		if (outboundPacketAckTrack.ItemAt(itemIndex)->packetID == packetID)
			break;
	if (itemIndex >= outboundPacketAckTrack.Size())
		return;

	// Free up all the messages in the acked packet. We don't need to keep track of those any more (to be sent to peer).
	PacketAckTrack &track = *outboundPacketAckTrack.ItemAt(itemIndex);
	for(size_t i = 0; i < track.messages.size(); ++i)
	{
		// If the message was part of a fragmented transfer, remove the message from that data structure.
		if (track.messages[i]->transfer)
		{
			Lock<FragmentedSendManager> sends = fragmentedSends.Acquire();
			sends->RemoveMessage(track.messages[i]->transfer, track.messages[i]);
		}

		// Free up the message, the peer acked this message and we're now free from having to resend it (again).
		ClearOutboundMessageWithContentID(track.messages[i]);
		FreeMessage(track.messages[i]);
	}

	if (track.sendCount <= 1)
	{
		UpdateRTOCounterOnPacketAck((float)Clock::TimespanToSecondsD(track.sentTick, Clock::Tick()));
		++numAcksLastFrame;
	}

	outboundPacketAckTrack.EraseItemAt(itemIndex);
}

/// Adjusts the retransmission timer values as per RFC 2988.
/// @param rtt The round trip time that was measured on the packet that was just acked.
void UDPMessageConnection::UpdateRTOCounterOnPacketAck(float rtt)
{
	AssertInWorkerThreadContext();

	using namespace std;

	const float alpha = 1.f / 8.f;
	const float beta = 1.f / 4.f;

	if (rttCleared)
	{
		rttCleared = false;
		rttVariation = rtt / 2.f;
		smoothedRTT = rtt;
	}
	else
	{
		rttVariation = (1.f - beta) * rttVariation + beta * fabs(smoothedRTT - rtt);
		smoothedRTT = (1.f - alpha) * smoothedRTT + alpha * rtt;
	}
	// We add this much constant delay to all RTO timers to avoid too optimistic RTO values
	// in excellent conditions (localhost, LAN).
	const float safetyThresholdMul = 2.f;

	retransmissionTimeout = min(maxRTOTimeoutValue, max(minRTOTimeoutValue, safetyThresholdMul * (smoothedRTT + rttVariation)));
}

void UDPMessageConnection::UpdateRTOCounterOnPacketLoss()
{
	AssertInWorkerThreadContext();

	using namespace std;

	retransmissionTimeout = smoothedRTT = min(maxRTOTimeoutValue, max(minRTOTimeoutValue, smoothedRTT * 2.f));
	// The variation just gives bogus values, so clear it altogether.
	rttVariation = 0.f;

	++numLossesLastFrame;

//	KNET_LOG(LogVerbose, "Packet loss event: RTO: %.3f sec. datagramSendRate: %.2f", retransmissionTimeout, datagramSendRate);
}

void UDPMessageConnection::SendPacketAckMessage()
{
	AssertInWorkerThreadContext();

	while(!inboundPacketAckTrack.empty())
	{
		packet_id_t packetID = inboundPacketAckTrack.begin()->first;
		u32 sequence = 0;

		inboundPacketAckTrack.erase(packetID);
		for(int i = 0; i < 32; ++i)
		{
			packet_id_t id = AddPacketID(packetID, i + 1);
			
			PacketAckTrackMap::iterator iter = inboundPacketAckTrack.find(id);
			if (iter != inboundPacketAckTrack.end())
			{
				sequence |= 1 << i;
				inboundPacketAckTrack.erase(id);
			}
		}

		NetworkMessage *msg = StartNewMessage(MsgIdPacketAck, 7);
		DataSerializer mb(msg->data, 7);
		mb.Add<u8>((u8)(packetID & 0xFF));
		mb.Add<u16>((u16)(packetID >> 8));
		mb.Add<u32>(sequence);
		msg->priority = NetworkMessage::cMaxPriority - 1;
#ifdef KNET_NETWORK_PROFILING
		msg->profilerName = "PacketAck (4)";
#endif
		EndAndQueueMessage(msg, mb.BytesFilled(), true);
	}
}

void UDPMessageConnection::HandlePacketAckMessage(const char *data, size_t numBytes)
{
	AssertInWorkerThreadContext();

	if (numBytes != 7)
	{
		KNET_LOG(LogError, "Malformed PacketAck message received! Size was %d bytes, expected 7 bytes!", (int)numBytes);
		throw NetException("Received a PacketAck message of wrong size! (expected 7 bytes)");
	}

	DataDeserializer mr(data, numBytes);
	packet_id_t packetIDLow = (packet_id_t)mr.Read<u8>();
	packet_id_t packetIDHigh = (packet_id_t)mr.Read<u16>();
	packet_id_t packetID = packetIDLow | (packetIDHigh << 8);
	u32 sequence = mr.Read<u32>();

	FreeOutboundPacketAckTrack(packetID);
	for(size_t i = 0; i < 32; ++i)
		if ((sequence & (1 << i)) != 0)
		{
			packet_id_t id = AddPacketID(packetID, 1 + i);
			FreeOutboundPacketAckTrack(id);
		}
}

void UDPMessageConnection::HandleDisconnectMessage()
{
	AssertInWorkerThreadContext();

	if (connectionState != ConnectionClosed)
		connectionState = ConnectionDisconnecting;
	else
		KNET_LOG(LogError, "UDPMessageConnection::HandleDisconnectMessage: Received Disconnect message when in ConnectionClosed state!");

	if (socket)
	{
		socket->MarkReadClosed();
		SendDisconnectAckMessage();
	}
}

void UDPMessageConnection::HandleDisconnectAckMessage()
{
	AssertInWorkerThreadContext();

	if (socket)
	{
		socket->MarkReadClosed();
		socket->MarkWriteClosed();
	}

	if (connectionState != ConnectionDisconnecting)
		KNET_LOG(LogInfo, "Received DisconnectAck message on a MessageConnection not in ConnectionDisconnecting state! (state was %d)",
		(int)connectionState);
	else
		KNET_LOG(LogInfo, "UDPMessageConnection::HandleDisconnectAckMessage: Connection closed to %s.", ToString().c_str());

	connectionState = ConnectionClosed;
}

void UDPMessageConnection::ComputePacketLoss()
{
	AssertInWorkerThreadContext();

	Lockable<ConnectionStatistics>::LockType cs = statistics.Acquire();

	if (cs->recvPacketIDs.size() <= 1)
	{
		packetLossRate = packetLossCount = 0.f;
		return;
	}

	const tick_t maxEntryAge = Clock::TicksPerSec() * 5;
	const tick_t timeNow = Clock::Tick();
	const tick_t maxTickAge = timeNow - maxEntryAge;

	// Remove old entries.
	for(size_t i = 0; i < cs->recvPacketIDs.size(); ++i)
		if (Clock::IsNewer(cs->recvPacketIDs[i].tick, maxTickAge))
		{
			cs->recvPacketIDs.erase(cs->recvPacketIDs.begin(), cs->recvPacketIDs.begin() + i);
			break;
		}

	if (cs->recvPacketIDs.size() <= 1)
	{
		packetLossRate = packetLossCount = 0.f;
		return;
	}

	// Find the oldest packet (in terms of messageID)
	int oldestIndex = 0;
	for(size_t i = 1; i < cs->recvPacketIDs.size(); ++i)
		if (PacketIDIsNewerThan(cs->recvPacketIDs[oldestIndex].packetID, cs->recvPacketIDs[i].packetID))
			oldestIndex = i;

	std::vector<packet_id_t> relIDs;
	relIDs.reserve(cs->recvPacketIDs.size());
	for(size_t i = 0; i < cs->recvPacketIDs.size(); ++i)
		relIDs.push_back(SubPacketID(cs->recvPacketIDs[i].packetID, cs->recvPacketIDs[oldestIndex].packetID));

	sort::CocktailSort(&relIDs[0], relIDs.size());

	int numMissedPackets = 0;
	for(size_t i = 0; i+1 < cs->recvPacketIDs.size(); ++i)
	{
		assert(relIDs[i+1] > relIDs[i]);
		numMissedPackets += relIDs[i+1] - relIDs[i] - 1;
	}

	packetLossRate = (float)numMissedPackets / (cs->recvPacketIDs.size() + numMissedPackets);
	packetLossCount = (float)numMissedPackets * 1000.f / (float)Clock::TimespanToMillisecondsD(maxTickAge, timeNow);
}

void AppendU16ToVector(std::vector<char> &data, unsigned long value)
{
	data.insert(data.end(), (const char *)&value, (const char *)&value + 2);
}

bool UDPMessageConnection::HandleMessage(packet_id_t packetID, message_id_t messageID, const char *data, size_t numBytes)
{
	AssertInWorkerThreadContext();

	switch(messageID)
	{
	case MsgIdPingRequest:
	case MsgIdPingReply:
		return false; // We don't do anything with these messages, the MessageConnection base class handles these.

	case MsgIdPacketAck:
		HandlePacketAckMessage(data, numBytes);
		return true;
	case MsgIdDisconnect:
		HandleDisconnectMessage();
		return true;
	case MsgIdDisconnectAck:
		HandleDisconnectAckMessage();
		return true;
	default:
		// For each application-level message received, ask the application to extract the Content ID of the message from the
		// message to us, so that we can track obsolete data receivals and discard such messages.
		if (!inboundMessageHandler)
			return false;
		else
		{
			u32 contentID = inboundMessageHandler->ComputeContentID(messageID, data, numBytes);
			if (contentID != 0 && CheckAndSaveContentIDStamp(messageID, contentID, packetID) == false)
			{
				KNET_LOG(LogVerbose, "MessageID %d in packetID %d and contentID %d is obsolete! Skipped.", (int)messageID, (int)packetID, (int)contentID);
				return true;
			}
			return false;
		}
	}
}

void UDPMessageConnection::DumpConnectionStatus() const
{
	char str[2048];
	sprintf(str,
		"\tRetransmission timeout: %.2fms.\n"
		"\tDatagram send rate: %.2f/sec.\n"
		"\tSmoothed RTT: %.2fms.\n"
		"\tRTT variation: %.2f.\n"
		"\tOutbound reliable datagrams in flight: %d.\n"
		"\tReceived unacked datagrams: %d.\n"
		"\tPacket loss count: %.2f.\n"
		"\tPacket loss rate: %.2f.\n"
		"\tDatagrams in: %.2f/sec.\n"
		"\tDatagrams out: %.2f/sec.\n",
	retransmissionTimeout,
	datagramSendRate,
	smoothedRTT,
	rttVariation,
	(int)outboundPacketAckTrack.Size(), ///\todo Accessing this variable is not thread-safe.
	(int)inboundPacketAckTrack.size(), ///\todo Accessing this variable is not thread-safe.
	packetLossCount,
	packetLossRate,
	PacketsInPerSec(), 
	PacketsOutPerSec());

	KNET_LOGUSER(str);
}

} // ~kNet
