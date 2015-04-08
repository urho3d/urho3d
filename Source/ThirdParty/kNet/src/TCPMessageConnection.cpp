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

/** @file TCPMessageConnection.cpp
	@brief */

#include <sstream>

#ifdef KNET_USE_BOOST
#include <boost/thread/thread.hpp>
#endif
#include "kNet/Allocator.h"

#include "kNet/DebugMemoryLeakCheck.h"
#include "kNet/TCPMessageConnection.h"
#include "kNet/NetworkLogging.h"
#include "kNet/DataSerializer.h"
#include "kNet/DataDeserializer.h"
#include "kNet/VLEPacker.h"
#include "kNet/NetException.h"
#include "kNet/Network.h"

namespace kNet
{

/// The maximum size for a TCP message we will allow to be received. If we receive a message larger than this, we consider
/// it as a protocol violation and kill the connection.
static const u32 cMaxReceivableTCPMessageSize = 10 * 1024 * 1024; ///\todo Make this configurable for the connection.

TCPMessageConnection::TCPMessageConnection(Network *owner, NetworkServer *ownerServer, Socket *socket, ConnectionState startingState)
:MessageConnection(owner, ownerServer, socket, startingState),
tcpInboundSocketData(64 * 1024)
{
}

TCPMessageConnection::~TCPMessageConnection()
{
	if (owner)
		owner->CloseConnection(this);
}

MessageConnection::SocketReadResult TCPMessageConnection::ReadSocket(size_t &totalBytesRead)
{
	AssertInWorkerThreadContext();

	totalBytesRead = 0;

	if (!socket || !socket->IsReadOpen())
		return SocketReadError;

	using namespace std;

	// This is a limit on how many messages we keep in the inbound application buffer at maximum.
	// If we receive data from the TCP socket faster than this limit, we stop reading until
	// the application handles the previous messages first.
	const int arbitraryInboundMessageCapacityLimit = 2048;

	if (inboundMessageQueue.CapacityLeft() < arbitraryInboundMessageCapacityLimit) 
	{
		KNET_LOG(LogVerbose, "TCPMessageConnection::ReadSocket: Read throttled! Application cannot consume data fast enough.");
		return SocketReadThrottled; // Can't read in new data, since the client app can't process it so fast.
	}

	// This is an arbitrary throttle limit on how much data we read in this function at once. Without this limit, 
	// a slow computer with a fast network connection and a fast sender at the other end could flood this end 
	// with so many messages that we wouldn't ever return from the loop below until the sender stops. This would
	// starve the processing of all other connections this worker thread has to manage.
	const size_t maxBytesToRead = 1024 * 1024;

	// Pump the socket's receiving end until it's empty or can't process any more for now.
	while(totalBytesRead < maxBytesToRead)
	{
		assert(socket);

		// If we don't have enough free space in the ring buffer (even after compacting), throttle the reading of data.
		if (tcpInboundSocketData.ContiguousFreeBytesLeft() < 16384 && tcpInboundSocketData.Capacity() > 1048576)
		{
			tcpInboundSocketData.Compact();
			if (tcpInboundSocketData.ContiguousFreeBytesLeft() < 16384)
				return SocketReadThrottled;
		}

		OverlappedTransferBuffer *buffer = socket->BeginReceive();
		if (!buffer)
			break; // Nothing to receive.

		// If we can't fit the data we got, compact the ring buffer.
		if (buffer->bytesContains > tcpInboundSocketData.ContiguousFreeBytesLeft())
		{
			tcpInboundSocketData.Compact();
			if (buffer->bytesContains > tcpInboundSocketData.ContiguousFreeBytesLeft())
			{
				// Even compacting didn't get enough space to fit the message, so resize the ring buffer to be able to contain the message.
				// At least always double the capacity of the buffer, so that we don't waste effort incrementing the capacity by too small amounts at a time.
				tcpInboundSocketData.Resize(max(tcpInboundSocketData.Capacity()*2, tcpInboundSocketData.Capacity() + buffer->bytesContains - tcpInboundSocketData.ContiguousFreeBytesLeft()));
				KNET_LOG(LogWaits, "TCPMessageConnection::ReadSocket: Performance warning! Resized the capacity of the receive ring buffer to %d bytes to accommodate a message of size %d (now have %d bytes of free space)",
					tcpInboundSocketData.Capacity(), buffer->bytesContains, tcpInboundSocketData.ContiguousFreeBytesLeft());
			}
		}

		KNET_LOG(LogData, "TCPMessageConnection::ReadSocket: Received %d bytes from the network from peer %s.", 
			buffer->bytesContains, socket->ToString().c_str());

		assert((size_t)buffer->bytesContains <= (size_t)tcpInboundSocketData.ContiguousFreeBytesLeft());
		///\todo For performance, this memcpy can be optimized away. We can parse the message directly
		/// from this buffer without copying it to a temporary working buffer. Detect if message straddles
		/// two OverlappedTransferBuffers and only in that case memcpy that message to form a
		/// single contiguous memory area.
		memcpy(tcpInboundSocketData.End(), buffer->buffer.buf, buffer->bytesContains);
		tcpInboundSocketData.Inserted(buffer->bytesContains); // Mark the memory area in the ring buffer as used.

		totalBytesRead += buffer->bytesContains;
		socket->EndReceive(buffer);
	}

	// Update statistics about the connection.
	if (totalBytesRead > 0)
	{
		lastHeardTime = Clock::Tick();
		ADDEVENT("tcpDataIn", (float)totalBytesRead, "bytes");
		AddInboundStats(totalBytesRead, 1, 0);
	}

	// Finally, try to parse any bytes we received to complete messages. Any bytes consisting a partial
	// message will be left into the tcpInboundSocketData partial buffer to wait for more bytes to be received later.
	ExtractMessages();

	if (totalBytesRead >= maxBytesToRead)
		return SocketReadThrottled;
	else
		return SocketReadOK;
}

/// Checks that the specified conditions for the container apply.
/// Warning: This is a non-threadsafe check for the container, only to be used for debugging.
/// Warning #2: This function is very slow, as it performs a N^2 search through the container.
template<typename T>
bool ContainerUniqueAndNoNullElements(const std::vector<T> &cont)
{
	for(size_t i = 0; i < cont.size(); ++i)
		for(size_t j = i+1; j < cont.size(); ++j)
			if (cont[i] == cont[j] || cont[i] == 0)
				return false;
	return true;
}

/// Packs several messages from the outbound priority queue into a single packet and sends it out the wire.
/// @return False if the send was a failure and sending should not be tried again at this time, true otherwise.
MessageConnection::PacketSendResult TCPMessageConnection::SendOutPacket()
{
	AssertInWorkerThreadContext();

	if (bOutboundSendsPaused || outboundQueue.Size() == 0)
		return PacketSendNoMessages;

	if (!socket || !socket->IsWriteOpen())
	{
		KNET_LOG(LogVerbose, "TCPMessageConnection::SendOutPacket: Socket is not write open %p!", socket);
		if (connectionState == ConnectionOK) ///\todo This is slightly annoying to manually update the state here,
			connectionState = ConnectionPeerClosed; /// reorganize to be able to have this automatically apply.
		if (connectionState == ConnectionDisconnecting)
			connectionState = ConnectionClosed;
		return PacketSendSocketClosed;
	}

    // 'serializedMessages' is a temporary data structure used only by this member function.
    // It caches a list of all the messages we are pushing out during this call.
	serializedMessages.clear();

	// In the following, we start coalescing multiple messages into a single socket send() calls.
	// Get the maximum number of bytes we can coalesce for the send() call. This is only a soft limit
	// in the sense that if we encounter a single message that is larger than this limit, then we try
	// to send that through in one send() call.
//	const size_t maxSendSize = socket->MaxSendSize();

	// Push out all the pending data to the socket.
	OverlappedTransferBuffer *overlappedTransfer = 0;

	int numMessagesPacked = 0;
	DataSerializer writer;
//	assert(ContainerUniqueAndNoNullElements(outboundQueue)); // This precondition should always hold (but very heavy to test, uncomment to debug)
	while(outboundQueue.Size() > 0)
	{
#ifdef KNET_NO_MAXHEAP
		NetworkMessage *msg = *outboundQueue.Front();
#else
		NetworkMessage *msg = outboundQueue.Front();
#endif

		if (msg->obsolete)
		{
			ClearOutboundMessageWithContentID(msg);
			FreeMessage(msg);
			outboundQueue.PopFront();
			continue;
		}

		const int encodedMsgIdLength = VLE8_16_32::GetEncodedBitLength(msg->id) / 8;
		const size_t messageContentSize = msg->dataSize + encodedMsgIdLength; // 1 byte: Message ID. X bytes: Content.
		const int encodedMsgSizeLength = VLE8_16_32::GetEncodedBitLength(messageContentSize) / 8;
		const size_t totalMessageSize = messageContentSize + encodedMsgSizeLength; // 2 bytes: Content length. X bytes: Content.

        if (!overlappedTransfer)
        {
            overlappedTransfer = socket->BeginSend(std::max<size_t>(socket->MaxSendSize(), totalMessageSize));
	        if (!overlappedTransfer)
	        {
		        KNET_LOG(LogError, "TCPMessageConnection::SendOutPacket: Starting an overlapped send failed!");
                assert(serializedMessages.empty());
		        return PacketSendSocketClosed;
	        }
            writer = DataSerializer(overlappedTransfer->buffer.buf, overlappedTransfer->buffer.len);
        }

		// If this message won't fit into the buffer, send out all previously gathered messages.
        if (writer.BytesLeft() < totalMessageSize)
			break;

		writer.AddVLE<VLE8_16_32>(messageContentSize);
		writer.AddVLE<VLE8_16_32>(msg->id);
		if (msg->dataSize > 0)
			writer.AddAlignedByteArray(msg->data, msg->dataSize);
		++numMessagesPacked;

		serializedMessages.push_back(msg);
#ifdef KNET_NO_MAXHEAP
		assert(*outboundQueue.Front() == msg);
#else
		assert(outboundQueue.Front() == msg);
#endif
		outboundQueue.PopFront();
	}
//	assert(ContainerUniqueAndNoNullElements(serializedMessages)); // This precondition should always hold (but very heavy to test, uncomment to debug)

	if (writer.BytesFilled() == 0 && outboundQueue.Size() > 0)
		KNET_LOG(LogError, "Failed to send any messages to socket %s! (Probably next message was too big to fit in the buffer).", socket->ToString().c_str());

	overlappedTransfer->bytesContains = writer.BytesFilled();
	bool success = socket->EndSend(overlappedTransfer);

	if (!success) // If we failed to send, put all the messages back into the outbound queue to wait for the next send round.
	{
		for(size_t i = 0; i < serializedMessages.size(); ++i)
#ifdef KNET_NO_MAXHEAP
			outboundQueue.InsertWithResize(serializedMessages[i]);
#else
			outboundQueue.Insert(serializedMessages[i]);
#endif
//		assert(ContainerUniqueAndNoNullElements(outboundQueue));

		KNET_LOG(LogError, "TCPMessageConnection::SendOutPacket() failed: Could not initiate overlapped transfer!");

		return PacketSendSocketFull;
	}

	KNET_LOG(LogData, "TCPMessageConnection::SendOutPacket: Sent %d bytes (%d messages) to peer %s.", (int)writer.BytesFilled(), (int)serializedMessages.size(), socket->ToString().c_str());
	AddOutboundStats(writer.BytesFilled(), 1, numMessagesPacked);
	ADDEVENT("tcpDataOut", (float)writer.BytesFilled(), "bytes");

	// The messages in serializedMessages array are now in the TCP driver to handle. It will guarantee
	// delivery if possible, so we can free the messages already.
	for(size_t i = 0; i < serializedMessages.size(); ++i)
	{
#ifdef KNET_NETWORK_PROFILING
		std::stringstream ss;
		if (!serializedMessages[i]->profilerName.empty())
			ss << "messageOut." << serializedMessages[i]->profilerName;
		else
			ss << "messageOut." << serializedMessages[i]->id;
		ADDEVENT(ss.str().c_str(), (float)serializedMessages[i]->Size(), "bytes");
#endif
		ClearOutboundMessageWithContentID(serializedMessages[i]);
		FreeMessage(serializedMessages[i]);
	}

	return PacketSendOK;
}

void TCPMessageConnection::DoUpdateConnection() // [worker thread]
{
	ExtractMessages();
}

void TCPMessageConnection::SendOutPackets()
{
	AssertInWorkerThreadContext();

	if (!socket || !socket->IsWriteOpen() || !socket->IsOverlappedSendReady())
		return;

	PacketSendResult result = PacketSendOK;
	int maxSends = 500; // Place an arbitrary limit to how many packets we will send at a time.
	while(result == PacketSendOK && maxSends-- > 0)
		result = SendOutPacket();

	// Thread-safely clear the eventMsgsOutAvailable event if we don't have any messages to process.
	if (NumOutboundMessagesPending() == 0)
		eventMsgsOutAvailable.Reset();
	if (NumOutboundMessagesPending() > 0)
		eventMsgsOutAvailable.Set();
}

void TCPMessageConnection::ExtractMessages()
{
	AssertInWorkerThreadContext();

	try
	{
		size_t numMessagesReceived = 0;
		for(;;)
		{
			if (tcpInboundSocketData.Size() == 0) // No new packets in yet.
				break;

			if (inboundMessageQueue.CapacityLeft() == 0) // If the application can't take in any new messages, abort.
				break;

			DataDeserializer reader(tcpInboundSocketData.Begin(), tcpInboundSocketData.Size());
			u32 messageSize = reader.ReadVLE<VLE8_16_32>();
			if (messageSize == DataDeserializer::VLEReadError)
				break; // The packet hasn't yet been streamed in.

			if (messageSize == 0 || messageSize > cMaxReceivableTCPMessageSize)
			{
				KNET_LOG(LogError, "Received an invalid message size %d!", (int)messageSize);
				throw NetException("Malformed TCP data! Received an invalid message size!");
			}

			if (reader.BytesLeft() < messageSize)
				break; // We haven't yet received the whole message, have to abort parsing for now and wait for the whole message.

			HandleInboundMessage(0, reader.CurrentData(), messageSize);
			reader.SkipBytes(messageSize);

			assert(reader.BitPos() == 0);
			u32 bytesConsumed = reader.BytePos();

			// Erase the bytes we just processed from the ring buffer.
			tcpInboundSocketData.Consumed(bytesConsumed);

			++numMessagesReceived;
		}
		AddInboundStats(0, 0, numMessagesReceived);
	} catch(const NetException &e)
	{
		KNET_LOG(LogError, "TCPMessageConnection::ExtractMessages() caught a network exception: \"%s\"!", e.what());
		if (socket)
			socket->Close();
		connectionState = ConnectionClosed;
	}
}

void TCPMessageConnection::PerformDisconnection()
{
	AssertInMainThreadContext();

	if (socket)
		socket->Disconnect();
}

void TCPMessageConnection::DumpConnectionStatus() const
{
	AssertInMainThreadContext();

	char str[2048];
	sprintf(str,
		"\ttcpInboundSocketData.Capacity(): %d\n"
		"\ttcpInboundSocketData.Size(): %d\n"
		"\ttcpInboundSocketData.ContiguousFreeBytesLeft(): %d\n",
		tcpInboundSocketData.Capacity(), // Note: This accesses a shared variable from the worker thread in a thread-unsafe way, and can crash. Therefore only use this function for debugging.
		tcpInboundSocketData.Size(), 
		tcpInboundSocketData.ContiguousFreeBytesLeft());

	KNET_LOGUSER(str);


}

unsigned long TCPMessageConnection::TimeUntilCanSendPacket() const
{
	// For TCPMessageConnection, this throttling logic is not used. Perhaps will not be used ever, as the
	// TCP driver does all send throttling already.
	return 0;
}

} // ~kNet
