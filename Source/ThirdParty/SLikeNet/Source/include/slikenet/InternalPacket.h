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
/// \brief \b [Internal] A class which stores a user message, and all information associated with sending and receiving that message.
///

#ifndef __INTERNAL_PACKET_H
#define __INTERNAL_PACKET_H

#include "PacketPriority.h"
#include "types.h"
#include "memoryoverride.h"
#include "defines.h"
#include "NativeTypes.h"
#include "defines.h"
#if USE_SLIDING_WINDOW_CONGESTION_CONTROL!=1
#include "CCRakNetUDT.h"
#else
#include "CCRakNetSlidingWindow.h"
#endif

namespace SLNet {

typedef uint16_t SplitPacketIdType;
typedef uint32_t SplitPacketIndexType;

/// This is the counter used for holding packet numbers, so we can detect duplicate packets.  It should be large enough that if the variables
/// Internally assumed to be 4 bytes, but written as 3 bytes in ReliabilityLayer::WriteToBitStreamFromInternalPacket
typedef uint24_t MessageNumberType;

/// This is the counter used for holding ordered packet numbers, so we can detect out-of-order packets.  It should be large enough that if the variables
/// were to wrap, the newly wrapped values would no longer be in use.  Warning: Too large of a value wastes bandwidth!
typedef MessageNumberType OrderingIndexType;

typedef SLNet::TimeUS RemoteSystemTimeType;

struct InternalPacketFixedSizeTransmissionHeader
{
	/// A unique numerical identifier given to this user message. Used to identify reliable messages on the network
	MessageNumberType reliableMessageNumber;
	///The ID used as identification for ordering messages. Also included in sequenced messages
	OrderingIndexType orderingIndex;
	// Used only with sequenced messages
	OrderingIndexType sequencingIndex;
	///What ordering channel this packet is on, if the reliability type uses ordering channels
	unsigned char orderingChannel;
	///The ID of the split packet, if we have split packets.  This is the maximum number of split messages we can send simultaneously per connection.
	SplitPacketIdType splitPacketId;
	///If this is a split packet, the index into the array of subsplit packets
	SplitPacketIndexType splitPacketIndex;
	///The size of the array of subsplit packets
	SplitPacketIndexType splitPacketCount;;
	///How many bits long the data is
	BitSize_t dataBitLength;
	///What type of reliability algorithm to use with this packet
	PacketReliability reliability;
	// Not endian safe
	// unsigned char priority : 3;
	// unsigned char reliability : 5;
};

/// Used in InternalPacket when pointing to sharedDataBlock, rather than allocating itself
struct InternalPacketRefCountedData
{
	unsigned char *sharedDataBlock;
	unsigned int refCount;
};

/// Holds a user message, and related information
/// Don't use a constructor or destructor, due to the memory pool I am using
struct InternalPacket : public InternalPacketFixedSizeTransmissionHeader
{
	/// Identifies the order in which this number was sent. Used locally
	MessageNumberType messageInternalOrder;
	/// Has this message number been assigned yet?  We don't assign until the message is actually sent.
	/// This fixes a bug where pre-determining message numbers and then sending a message on a different channel creates a huge gap.
	/// This causes performance problems and causes those messages to timeout.
	bool messageNumberAssigned;
	/// Was this packet number used this update to track windowing drops or increases?  Each packet number is only used once per update.
//	bool allowWindowUpdate;
	///When this packet was created
	SLNet::TimeUS creationTime;
	///The resendNext time to take action on this packet
	SLNet::TimeUS nextActionTime;
	// For debugging
	SLNet::TimeUS retransmissionTime;
	// Size of the header when encoded into a bitstream
	BitSize_t headerLength;
	/// Buffer is a pointer to the actual data, assuming this packet has data at all
	unsigned char *data;
	/// How to alloc and delete the data member
	enum AllocationScheme
	{
		/// Data is allocated using rakMalloc. Just free it
		NORMAL,

		/// data points to a larger block of data, where the larger block is reference counted. internalPacketRefCountedData is used in this case
		REF_COUNTED,
	
		/// If allocation scheme is STACK, data points to stackData and should not be deallocated
		/// This is only used when sending. Received packets are deallocated in RakPeer
		STACK
	} allocationScheme;
	InternalPacketRefCountedData *refCountedData;
	/// How many attempts we made at sending this message
	unsigned char timesSent;
	/// The priority level of this packet
	PacketPriority priority;
	/// If the reliability type requires a receipt, then return this number with it
	uint32_t sendReceiptSerial;

	// Used for the resend queue
	// Linked list implementation so I can remove from the list via a pointer, without finding it in the list
	InternalPacket *resendPrev, *resendNext,*unreliablePrev,*unreliableNext;

	unsigned char stackData[128];
};

} // namespace SLNet

#endif

