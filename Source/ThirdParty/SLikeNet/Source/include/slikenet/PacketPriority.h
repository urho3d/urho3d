/*
 *  Copyright (c) 2014, Oculus VR, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the BSD-style license found in the
 *  RakNet License.txt file in the licenses directory of this source tree. An additional grant 
 *  of patent rights can be found in the RakNet Patents.txt file in the same directory.
 *
 */

/// \file
/// \brief This file contains enumerations for packet priority and reliability enumerations.
///



#ifndef __PACKET_PRIORITY_H
#define __PACKET_PRIORITY_H 

/// These enumerations are used to describe when packets are delivered.
enum PacketPriority
{
	/// The highest possible priority. These message trigger sends immediately, and are generally not buffered or aggregated into a single datagram.
	IMMEDIATE_PRIORITY,

	/// For every 2 IMMEDIATE_PRIORITY messages, 1 HIGH_PRIORITY will be sent.
	/// Messages at this priority and lower are buffered to be sent in groups at 10 millisecond intervals to reduce UDP overhead and better measure congestion control. 
	HIGH_PRIORITY,

	/// For every 2 HIGH_PRIORITY messages, 1 MEDIUM_PRIORITY will be sent.
	/// Messages at this priority and lower are buffered to be sent in groups at 10 millisecond intervals to reduce UDP overhead and better measure congestion control. 
	MEDIUM_PRIORITY,   

	/// For every 2 MEDIUM_PRIORITY messages, 1 LOW_PRIORITY will be sent.
	/// Messages at this priority and lower are buffered to be sent in groups at 10 millisecond intervals to reduce UDP overhead and better measure congestion control. 
	LOW_PRIORITY,

	/// \internal
	NUMBER_OF_PRIORITIES
};

/// These enumerations are used to describe how packets are delivered.
/// \note  Note to self: I write this with 3 bits in the stream.  If I add more remember to change that
/// \note In ReliabilityLayer::WriteToBitStreamFromInternalPacket I assume there are 5 major types
/// \note Do not reorder, I check on >= UNRELIABLE_WITH_ACK_RECEIPT
enum PacketReliability
{
	/// Same as regular UDP, except that it will also discard duplicate datagrams.  RakNet adds (6 to 17) + 21 bits of overhead, 16 of which is used to detect duplicate packets and 6 to 17 of which is used for message length.
	UNRELIABLE,

	/// Regular UDP with a sequence counter.  Out of order messages will be discarded.
	/// Sequenced and ordered messages sent on the same channel will arrive in the order sent.
	UNRELIABLE_SEQUENCED,

	/// The message is sent reliably, but not necessarily in any order.  Same overhead as UNRELIABLE.
	RELIABLE,

	/// This message is reliable and will arrive in the order you sent it.  Messages will be delayed while waiting for out of order messages.  Same overhead as UNRELIABLE_SEQUENCED.
	/// Sequenced and ordered messages sent on the same channel will arrive in the order sent.
	RELIABLE_ORDERED,

	/// This message is reliable and will arrive in the sequence you sent it.  Out or order messages will be dropped.  Same overhead as UNRELIABLE_SEQUENCED.
	/// Sequenced and ordered messages sent on the same channel will arrive in the order sent.
	RELIABLE_SEQUENCED,

	/// Same as UNRELIABLE, however the user will get either ID_SND_RECEIPT_ACKED or ID_SND_RECEIPT_LOSS based on the result of sending this message when calling RakPeerInterface::Receive(). Bytes 1-4 will contain the number returned from the Send() function. On disconnect or shutdown, all messages not previously acked should be considered lost.
	UNRELIABLE_WITH_ACK_RECEIPT,

	/// Same as UNRELIABLE_SEQUENCED, however the user will get either ID_SND_RECEIPT_ACKED or ID_SND_RECEIPT_LOSS based on the result of sending this message when calling RakPeerInterface::Receive(). Bytes 1-4 will contain the number returned from the Send() function. On disconnect or shutdown, all messages not previously acked should be considered lost.
	/// 05/04/10 You can't have sequenced and ack receipts, because you don't know if the other system discarded the message, meaning you don't know if the message was processed
	// UNRELIABLE_SEQUENCED_WITH_ACK_RECEIPT,

	/// Same as RELIABLE. The user will also get ID_SND_RECEIPT_ACKED after the message is delivered when calling RakPeerInterface::Receive(). ID_SND_RECEIPT_ACKED is returned when the message arrives, not necessarily the order when it was sent. Bytes 1-4 will contain the number returned from the Send() function. On disconnect or shutdown, all messages not previously acked should be considered lost. This does not return ID_SND_RECEIPT_LOSS.
	RELIABLE_WITH_ACK_RECEIPT,

	/// Same as RELIABLE_ORDERED_ACK_RECEIPT. The user will also get ID_SND_RECEIPT_ACKED after the message is delivered when calling RakPeerInterface::Receive(). ID_SND_RECEIPT_ACKED is returned when the message arrives, not necessarily the order when it was sent. Bytes 1-4 will contain the number returned from the Send() function. On disconnect or shutdown, all messages not previously acked should be considered lost. This does not return ID_SND_RECEIPT_LOSS.
	RELIABLE_ORDERED_WITH_ACK_RECEIPT,

	/// Same as RELIABLE_SEQUENCED. The user will also get ID_SND_RECEIPT_ACKED after the message is delivered when calling RakPeerInterface::Receive(). Bytes 1-4 will contain the number returned from the Send() function. On disconnect or shutdown, all messages not previously acked should be considered lost.
	/// 05/04/10 You can't have sequenced and ack receipts, because you don't know if the other system discarded the message, meaning you don't know if the message was processed
	// RELIABLE_SEQUENCED_WITH_ACK_RECEIPT,

	/// \internal
	NUMBER_OF_RELIABILITIES
};

#endif
