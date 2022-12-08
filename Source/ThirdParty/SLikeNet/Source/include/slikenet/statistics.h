/*
 *  Original work: Copyright (c) 2014, Oculus VR, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the BSD-style license found in the
 *  RakNet License.txt file in the licenses directory of this source tree. An additional grant 
 *  of patent rights can be found in the RakNet Patents.txt file in the same directory.
 *
 *
 *  Modified work: Copyright (c) 2016-2018, SLikeSoft UG (haftungsbeschränkt)
 *
 *  This source code was modified by SLikeSoft. Modifications are licensed under the MIT-style
 *  license found in the license.txt file in the root directory of this source tree.
 */

/// \file
/// \brief A structure that holds all statistical data returned by RakNet.
///



#ifndef __RAK_NET_STATISTICS_H
#define __RAK_NET_STATISTICS_H

#include "PacketPriority.h"
#include "Export.h"
#include "types.h"

namespace SLNet
{

enum RNSPerSecondMetrics
{
	/// How many bytes per pushed via a call to RakPeerInterface::Send()
	USER_MESSAGE_BYTES_PUSHED,

	/// How many user message bytes were sent via a call to RakPeerInterface::Send(). This is less than or equal to USER_MESSAGE_BYTES_PUSHED.
	/// A message would be pushed, but not yet sent, due to congestion control
	USER_MESSAGE_BYTES_SENT,

	/// How many user message bytes were resent. A message is resent if it is marked as reliable, and either the message didn't arrive or the message ack didn't arrive.
	USER_MESSAGE_BYTES_RESENT,

	/// How many user message bytes were received, and returned to the user successfully.
	USER_MESSAGE_BYTES_RECEIVED_PROCESSED,

	/// How many user message bytes were received, but ignored due to data format errors. This will usually be 0.
	USER_MESSAGE_BYTES_RECEIVED_IGNORED,

	/// How many actual bytes were sent, including per-message and per-datagram overhead, and reliable message acks
	ACTUAL_BYTES_SENT,

	/// How many actual bytes were received, including overead and acks.
	ACTUAL_BYTES_RECEIVED,

	/// \internal
	RNS_PER_SECOND_METRICS_COUNT
};

/// \brief Network Statisics Usage 
///
/// Store Statistics information related to network usage 
struct RAK_DLL_EXPORT RakNetStatistics
{
	/// For each type in RNSPerSecondMetrics, what is the value over the last 1 second?
	uint64_t valueOverLastSecond[RNS_PER_SECOND_METRICS_COUNT];

	/// For each type in RNSPerSecondMetrics, what is the total value over the lifetime of the connection?
	uint64_t runningTotal[RNS_PER_SECOND_METRICS_COUNT];
	
	/// When did the connection start?
	/// \sa SLNet::GetTimeUS()
	SLNet::TimeUS connectionStartTime;

	/// Is our current send rate throttled by congestion control?
	/// This value should be true if you send more data per second than your bandwidth capacity
	bool isLimitedByCongestionControl;

	/// If \a isLimitedByCongestionControl is true, what is the limit, in bytes per second?
	uint64_t BPSLimitByCongestionControl;

	/// Is our current send rate throttled by a call to RakPeer::SetPerConnectionOutgoingBandwidthLimit()?
	bool isLimitedByOutgoingBandwidthLimit;

	/// If \a isLimitedByOutgoingBandwidthLimit is true, what is the limit, in bytes per second?
	uint64_t BPSLimitByOutgoingBandwidthLimit;

	/// For each priority level, how many messages are waiting to be sent out?
	unsigned int messageInSendBuffer[NUMBER_OF_PRIORITIES];

	/// For each priority level, how many bytes are waiting to be sent out?
	double bytesInSendBuffer[NUMBER_OF_PRIORITIES];

	/// How many messages are waiting in the resend buffer? This includes messages waiting for an ack, so should normally be a small value
	/// If the value is rising over time, you are exceeding the bandwidth capacity. See BPSLimitByCongestionControl 
	unsigned int messagesInResendBuffer;

	/// How many bytes are waiting in the resend buffer. See also messagesInResendBuffer
	uint64_t bytesInResendBuffer;

	/// Over the last second, what was our packetloss? This number will range from 0.0 (for none) to 1.0 (for 100%)
	float packetlossLastSecond;

	/// What is the average total packetloss over the lifetime of the connection?
	float packetlossTotal;

	RakNetStatistics& operator +=(const RakNetStatistics& other)
	{
		unsigned i;
		for (i=0; i < NUMBER_OF_PRIORITIES; i++)
		{
			messageInSendBuffer[i]+=other.messageInSendBuffer[i];
			bytesInSendBuffer[i]+=other.bytesInSendBuffer[i];
		}

		for (i=0; i < RNS_PER_SECOND_METRICS_COUNT; i++)
		{
			valueOverLastSecond[i]+=other.valueOverLastSecond[i];
			runningTotal[i]+=other.runningTotal[i];
		}

		return *this;
	}
};

/// Verbosity level currently supports 0 (low), 1 (medium), 2 (high)
/// \param[in] s The Statistical information to format out
/// \param[in] buffer The buffer containing a formated report
/// \param[in] bufferLength The size (in characters) of the buffer
/// \param[in] verbosityLevel 
/// 0 low
/// 1 medium 
/// 2 high 
/// 3 debugging congestion control
void RAK_DLL_EXPORT StatisticsToString(RakNetStatistics *s, char *buffer, int verbosityLevel);
void RAK_DLL_EXPORT StatisticsToString( RakNetStatistics *s, char *buffer, size_t bufferLength, int verbosityLevel );

} // namespace SLNet

#endif
