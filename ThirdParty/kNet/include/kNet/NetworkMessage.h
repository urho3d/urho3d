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

/** @file NetworkMessage.h
	@brief The class NetworkMessage. Stores an outbound network message. */

#include "kNetBuildConfig.h"
#include "LockFreePoolAllocator.h"
#include "FragmentedTransferManager.h"

namespace kNet
{

/// Contains 22 actual bits of data.
typedef unsigned long packet_id_t;

/// Performs modular arithmetic comparison to see if newID refers to a PacketID newer than oldID.
/// @return True if newID is newer than oldID, false otherwise.
inline bool PacketIDIsNewerThan(packet_id_t newID, packet_id_t oldID)
{
	if (newID > oldID)
		return true;
	if (oldID - newID >= (1 << 21))
		return true;
	return false;
}

/// Computes the PacketID for the packet (id + increment).
inline packet_id_t AddPacketID(packet_id_t id, int increment)
{
	return (id + increment) & ((1 << 22) - 1);
}

/// Computes the PacketID for the packet (id - sub).
inline packet_id_t SubPacketID(packet_id_t id, int sub)
{
	if ((int)id >= sub)
		return (packet_id_t)(id - sub);
	else
		return (packet_id_t)((1 << 22) - (sub-id));
}

/// NetworkMessage stores the serialized byte data of a single outbound network message, along
/// with fields that specify how itreated by the network connection.
class NetworkMessage : public PoolAllocatable<NetworkMessage>
{
public:
	/// To create a NetworkMessage, call MessageConnection::StartNewMessage() instead of directly instantiating
	/// a message structure. This is because each MessageConnection implements an internal pool of NetworkMessage
	/// structures which are reused between messages, to avoid excessive dynamic memory allocation.
	NetworkMessage();

	NetworkMessage &operator=(const NetworkMessage &rhs);
	NetworkMessage(const NetworkMessage &rhs);

	~NetworkMessage();

	/// Stores the actual data of the message. 
	/// When writing a new message, fill in the data bytes here. This buffer can hold Capacity() amount of bytes. If you need more,
	/// call Reallocate() with the desired amount of bytes.
	/// This field is read-only, do not change this pointer value.
	char *data;

	size_t Capacity() const { return dataCapacity; }

	size_t Size() const { return dataSize; }

	/// Resizes the message to the given amount of bytes. Reallocates the data buffer if it cannot fit into the new size.
	/// @param newBytes The new amount of bytes to use for the message.
	/// @param discard If true, any existing partially filled data will not be copied over, but the new buffer will have its 
	///                bytes left uninitialized. If false, this function preserves any old partially filled data and works
	///                like std::vector::resize(). The intended purpose of this function is to be called prior to filling
	///                in any data, and so the default value is true.
	void Resize(size_t newBytes, bool discard = true);

	/// The send priority of this message with respect to other messages. Priority 0 is the lowest, and 
	/// priority 0xFFFFFFFE is the highest. Priority 0xFFFFFFFF is a special one that means 'don't send this message'.
	unsigned long priority;

	/// The ID of this message. IDs 0 - 5 are reserved for the protocol and may not be used.
	packet_id_t id;

	/// When sending out a message, the application can attach a content ID to the message,
	/// which will effectively replace all the older messages with the same messageID and
	/// contentID.
	unsigned long contentID;

	/// If true, this message should be delivered reliably, possibly resent to guarantee
	/// that the receiving party gets it.
	bool reliable;

	/// If true, this message should be delivered in-order with all the other in-order
	/// messages. The processing order of this message relative to non-in-ordered messages
	/// is not specified and can vary.
	bool inOrder;

	/// If this flag is set, the message will not be sent and will be deleted as soon
	/// as possible. It has been superceded by another message before it had the time
	/// to leave the outbound send queue.
	bool obsolete;

#ifdef KNET_NETWORK_PROFILING
	std::string profilerName;
#endif

	/// Checks if this message is newer than the other message.
	bool IsNewerThan(const NetworkMessage &rhs) const { return (unsigned long)(messageNumber - rhs.messageNumber) < 0x80000000; }

	/// A message with this priority is obsolete and should not be sent through the connection.
	static const unsigned long cPriorityDontSend = 0xFFFFFFFF;
	/// The maximum priority a message can have.
	static const unsigned long cMaxPriority = 0xFFFFFFFE;

	/// Returns the total number of bytes this datagram will take up space when it is serialized to an UDP channel.
	int GetTotalDatagramPackedSize() const;

	/// Returns the number of this message. The message number identifies the admission order of messages to the outbound queue.
	unsigned long MessageNumber() const { return messageNumber; }

private:
	friend class MessageConnection;
	friend class UDPMessageConnection;
	friend class TCPMessageConnection;
	friend class FragmentedSendManager;
	friend struct FragmentedSendManager::FragmentedTransfer;

	/// A running number that is assigned to each message to distinguish the order
	/// the messages were added to the queue. The network layer manages this numbering,
	/// the application can not control it. This is used to break ties on packets
	/// that have the same priority.
	unsigned long messageNumber;

	/// A running number that is assigned to each reliable message. This is used in the
	/// network byte stream to implement ordering of messages.
	unsigned long reliableMessageNumber;

	/// The number of times this message has been sent and not been acked (reliable messages only).
	unsigned long sendCount;

	/// The index of this fragment, or not used (undefined) if totalNumFragments==0.
	unsigned long fragmentIndex;

	/// Tells the number of bytes that have been allocated and can be filled to the data array.
	size_t dataCapacity;

	/// Specifies the number of bytes actually used in the data array.
	size_t dataSize;

	/// If 0, this message is being sent unfragmented. Otherwise, this NetworkMessage is a fragment of the whole
	/// message and transfer points to the data structure that tracks the transfer of a fragmented message.
	FragmentedSendManager::FragmentedTransfer *transfer;
};

} // ~kNet
