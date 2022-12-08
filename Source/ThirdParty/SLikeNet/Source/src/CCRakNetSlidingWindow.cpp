/*
 *  Original work: Copyright (c) 2014, Oculus VR, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the BSD-style license found in the
 *  RakNet License.txt file in the licenses directory of this source tree. An additional grant 
 *  of patent rights can be found in the RakNet Patents.txt file in the same directory.
 *
 *
 *  Modified work: Copyright (c) 2016-2017, SLikeSoft UG (haftungsbeschränkt)
 *
 *  This source code was modified by SLikeSoft. Modifications are licensed under the MIT-style
 *  license found in the license.txt file in the root directory of this source tree.
 */

#include "slikenet/CCRakNetSlidingWindow.h"

#if USE_SLIDING_WINDOW_CONGESTION_CONTROL==1

static const double UNSET_TIME_US=-1;

#if CC_TIME_TYPE_BYTES==4
static const CCTimeType SYN=10;
#else
static const CCTimeType SYN=10000;
#endif

#include "slikenet/MTUSize.h"
#include <stdio.h>
#include <cmath>
#include <stdlib.h>
#include "slikenet/assert.h"
#include "slikenet/alloca.h"

using namespace SLNet;

// ****************************************************** PUBLIC METHODS ******************************************************

CCRakNetSlidingWindow::CCRakNetSlidingWindow()
{
}
// ----------------------------------------------------------------------------------------------------------------------------
CCRakNetSlidingWindow::~CCRakNetSlidingWindow()
{

}
// ----------------------------------------------------------------------------------------------------------------------------
void CCRakNetSlidingWindow::Init(CCTimeType curTime, uint32_t maxDatagramPayload)
{
	(void) curTime;

	lastRtt=estimatedRTT=deviationRtt=UNSET_TIME_US;
	RakAssert(maxDatagramPayload <= MAXIMUM_MTU_SIZE);
	MAXIMUM_MTU_INCLUDING_UDP_HEADER=maxDatagramPayload;
	cwnd=maxDatagramPayload;
	ssThresh=0.0;
	oldestUnsentAck=0;
	nextDatagramSequenceNumber=0;
	nextCongestionControlBlock=0;
	backoffThisBlock=speedUpThisBlock=false;
	expectedNextSequenceNumber=0;
	_isContinuousSend=false;
}
// ----------------------------------------------------------------------------------------------------------------------------
void CCRakNetSlidingWindow::Update(CCTimeType curTime, bool hasDataToSendOrResend)
{
	(void) curTime;
	(void) hasDataToSendOrResend;
}
// ----------------------------------------------------------------------------------------------------------------------------
int CCRakNetSlidingWindow::GetRetransmissionBandwidth(CCTimeType curTime, CCTimeType timeSinceLastTick, uint32_t unacknowledgedBytes, bool isContinuousSend)
{
	(void) curTime;
	(void) isContinuousSend;
	(void) timeSinceLastTick;

	return unacknowledgedBytes;
}
// ----------------------------------------------------------------------------------------------------------------------------
int CCRakNetSlidingWindow::GetTransmissionBandwidth(CCTimeType curTime, CCTimeType timeSinceLastTick, uint32_t unacknowledgedBytes, bool isContinuousSend)
{
	(void) curTime;
	(void) timeSinceLastTick;

	_isContinuousSend=isContinuousSend;

	if (unacknowledgedBytes<=cwnd)
		return (int) (cwnd-unacknowledgedBytes);
	else
		return 0;
}
// ----------------------------------------------------------------------------------------------------------------------------
bool CCRakNetSlidingWindow::ShouldSendACKs(CCTimeType curTime, CCTimeType estimatedTimeToNextTick)
{
	CCTimeType rto = GetSenderRTOForACK();
	(void) estimatedTimeToNextTick;

	// iphone crashes on comparison between double and int64 http://www.jenkinssoftware.com/forum/index.php?topic=2717.0
	if (rto==(CCTimeType) UNSET_TIME_US)
	{
		// Unknown how long until the remote system will retransmit, so better send right away
		return true;
	}

	return curTime >= oldestUnsentAck + SYN;
}
// ----------------------------------------------------------------------------------------------------------------------------
DatagramSequenceNumberType CCRakNetSlidingWindow::GetNextDatagramSequenceNumber(void)
{
	return nextDatagramSequenceNumber;
}
// ----------------------------------------------------------------------------------------------------------------------------
DatagramSequenceNumberType CCRakNetSlidingWindow::GetAndIncrementNextDatagramSequenceNumber(void)
{
	DatagramSequenceNumberType dsnt=nextDatagramSequenceNumber;
	nextDatagramSequenceNumber++;
	return dsnt;
}
// ----------------------------------------------------------------------------------------------------------------------------
void CCRakNetSlidingWindow::OnSendBytes(CCTimeType curTime, uint32_t numBytes)
{
	(void) curTime;
	(void) numBytes;
}
// ----------------------------------------------------------------------------------------------------------------------------
void CCRakNetSlidingWindow::OnGotPacketPair(DatagramSequenceNumberType datagramSequenceNumber, uint32_t sizeInBytes, CCTimeType curTime)
{
	(void) curTime;
	(void) sizeInBytes;
	(void) datagramSequenceNumber;
}
// ----------------------------------------------------------------------------------------------------------------------------
bool CCRakNetSlidingWindow::OnGotPacket(DatagramSequenceNumberType datagramSequenceNumber, bool isContinuousSend, CCTimeType curTime, uint32_t sizeInBytes, uint32_t *skippedMessageCount)
{
	(void) curTime;
	(void) sizeInBytes;
	(void) isContinuousSend;

	if (oldestUnsentAck==0)
		oldestUnsentAck=curTime;

	if (datagramSequenceNumber==expectedNextSequenceNumber)
	{
		*skippedMessageCount=0;
		expectedNextSequenceNumber=datagramSequenceNumber+(DatagramSequenceNumberType)1;
	}
	else if (GreaterThan(datagramSequenceNumber, expectedNextSequenceNumber))
	{
		*skippedMessageCount=datagramSequenceNumber-expectedNextSequenceNumber;
		// Sanity check, just use timeout resend if this was really valid
		if (*skippedMessageCount>1000)
		{
			// During testing, the nat punchthrough server got 51200 on the first packet. I have no idea where this comes from, but has happened twice
			if (*skippedMessageCount>(uint32_t)50000)
				return false;
			*skippedMessageCount=1000;
		}
		expectedNextSequenceNumber=datagramSequenceNumber+(DatagramSequenceNumberType)1;
	}
	else
	{
		*skippedMessageCount=0;
	}

	return true;
}
// ----------------------------------------------------------------------------------------------------------------------------
void CCRakNetSlidingWindow::OnResend(CCTimeType curTime, SLNet::TimeUS nextActionTime)
{
	(void) curTime;
	(void) nextActionTime;

	if (_isContinuousSend && backoffThisBlock==false && cwnd>MAXIMUM_MTU_INCLUDING_UDP_HEADER*2)
	{
		// Spec says 1/2 cwnd, but it never recovers because cwnd increases too slowly
		//ssThresh=cwnd-8.0 * (MAXIMUM_MTU_INCLUDING_UDP_HEADER*MAXIMUM_MTU_INCLUDING_UDP_HEADER/cwnd);
		ssThresh=cwnd/2;
		if (ssThresh<MAXIMUM_MTU_INCLUDING_UDP_HEADER)
			ssThresh=MAXIMUM_MTU_INCLUDING_UDP_HEADER;
		cwnd=MAXIMUM_MTU_INCLUDING_UDP_HEADER;

		// Only backoff once per period
		nextCongestionControlBlock=nextDatagramSequenceNumber;
		backoffThisBlock=true;

		// CC PRINTF
		//printf("-- %.0f (Resend) Enter slow start.\n", cwnd);
	}
}
// ----------------------------------------------------------------------------------------------------------------------------
void CCRakNetSlidingWindow::OnNAK(CCTimeType curTime, DatagramSequenceNumberType nakSequenceNumber)
{
	(void) nakSequenceNumber;
	(void) curTime;

	if (_isContinuousSend && backoffThisBlock==false)
	{
		// Start congestion avoidance
		ssThresh=cwnd/2;

		// CC PRINTF
		//printf("- %.0f (NAK) Set congestion avoidance.\n", cwnd);
	}
}
// ----------------------------------------------------------------------------------------------------------------------------
void CCRakNetSlidingWindow::OnAck(CCTimeType curTime, CCTimeType rtt, bool hasBAndAS, BytesPerMicrosecond _B, BytesPerMicrosecond _AS, double totalUserDataBytesAcked, bool isContinuousSend, DatagramSequenceNumberType sequenceNumber )
{
	(void) _B;
	(void) totalUserDataBytesAcked;
	(void) _AS;
	(void) hasBAndAS;
	(void) curTime;
	(void) rtt;

	lastRtt=(double) rtt;
	if (estimatedRTT==UNSET_TIME_US)
	{
		estimatedRTT=(double) rtt;
		deviationRtt=(double)rtt;
	}
	else
	{
		double d = .05;
		double difference = rtt - estimatedRTT;
		estimatedRTT = estimatedRTT + d * difference;
		deviationRtt = deviationRtt + d * (std::abs(difference) - deviationRtt);
	}

	_isContinuousSend=isContinuousSend;

	if (isContinuousSend==false)
		return;

	bool isNewCongestionControlPeriod;
	isNewCongestionControlPeriod = GreaterThan(sequenceNumber, nextCongestionControlBlock);

	if (isNewCongestionControlPeriod)
	{
		backoffThisBlock=false;
		speedUpThisBlock=false;
		nextCongestionControlBlock=nextDatagramSequenceNumber;
	}

	if (IsInSlowStart())
	{
		cwnd+=MAXIMUM_MTU_INCLUDING_UDP_HEADER;
		if (cwnd > ssThresh && ssThresh!=0)
			cwnd = ssThresh + MAXIMUM_MTU_INCLUDING_UDP_HEADER*MAXIMUM_MTU_INCLUDING_UDP_HEADER/cwnd;

		// CC PRINTF
	//	printf("++ %.0f Slow start increase.\n", cwnd);

	}
	else if (isNewCongestionControlPeriod)
	{
		cwnd+=MAXIMUM_MTU_INCLUDING_UDP_HEADER*MAXIMUM_MTU_INCLUDING_UDP_HEADER/cwnd;

		// CC PRINTF
		// printf("+ %.0f Congestion avoidance increase.\n", cwnd);
	}
}
// ----------------------------------------------------------------------------------------------------------------------------
void CCRakNetSlidingWindow::OnDuplicateAck( CCTimeType curTime, DatagramSequenceNumberType sequenceNumber )
{
	(void) curTime;
	(void) sequenceNumber;
}
// ----------------------------------------------------------------------------------------------------------------------------
void CCRakNetSlidingWindow::OnSendAckGetBAndAS(CCTimeType curTime, bool *hasBAndAS, BytesPerMicrosecond *_B, BytesPerMicrosecond *_AS)
{
	(void) curTime;
	(void) _B;
	(void) _AS;

	*hasBAndAS=false;
}
// ----------------------------------------------------------------------------------------------------------------------------
void CCRakNetSlidingWindow::OnSendAck(CCTimeType curTime, uint32_t numBytes)
{
	(void) curTime;
	(void) numBytes;

	oldestUnsentAck=0;
}
// ----------------------------------------------------------------------------------------------------------------------------
void CCRakNetSlidingWindow::OnSendNACK(CCTimeType curTime, uint32_t numBytes)
{
	(void) curTime;
	(void) numBytes;

}
// ----------------------------------------------------------------------------------------------------------------------------
CCTimeType CCRakNetSlidingWindow::GetRTOForRetransmission(unsigned char timesSent) const
{
	(void) timesSent;

#if CC_TIME_TYPE_BYTES==4
	const CCTimeType maxThreshold=2000;
	//const CCTimeType minThreshold=100;
	const CCTimeType additionalVariance=30;
#else
	const CCTimeType maxThreshold=2000000;
	//const CCTimeType minThreshold=100000;
	const CCTimeType additionalVariance=30000;
#endif


	if (estimatedRTT==UNSET_TIME_US)
		return maxThreshold;

 	//double u=1.0f;
	double u=2.0f;
 	double q=4.0f;

	CCTimeType threshhold = (CCTimeType) (u * estimatedRTT + q * deviationRtt) + additionalVariance;
	if (threshhold > maxThreshold)
		return maxThreshold;
	return threshhold;
}
// ----------------------------------------------------------------------------------------------------------------------------
void CCRakNetSlidingWindow::SetMTU(uint32_t bytes)
{
	RakAssert(bytes < MAXIMUM_MTU_SIZE);
	MAXIMUM_MTU_INCLUDING_UDP_HEADER=bytes;
}
// ----------------------------------------------------------------------------------------------------------------------------
uint32_t CCRakNetSlidingWindow::GetMTU(void) const
{
	return MAXIMUM_MTU_INCLUDING_UDP_HEADER;
}
// ----------------------------------------------------------------------------------------------------------------------------
BytesPerMicrosecond CCRakNetSlidingWindow::GetLocalReceiveRate(CCTimeType currentTime) const
{
	(void) currentTime;

	return 0; // TODO
}
// ----------------------------------------------------------------------------------------------------------------------------
double CCRakNetSlidingWindow::GetRTT(void) const
{
	if (lastRtt==UNSET_TIME_US)
		return 0.0;
	return lastRtt;
}
// ----------------------------------------------------------------------------------------------------------------------------
bool CCRakNetSlidingWindow::GreaterThan(DatagramSequenceNumberType a, DatagramSequenceNumberType b)
{
	// a > b?
	const DatagramSequenceNumberType halfSpan =(DatagramSequenceNumberType) (((DatagramSequenceNumberType)(const uint32_t)-1)/(DatagramSequenceNumberType)2);
	return b!=a && b-a>halfSpan;
}
// ----------------------------------------------------------------------------------------------------------------------------
bool CCRakNetSlidingWindow::LessThan(DatagramSequenceNumberType a, DatagramSequenceNumberType b)
{
	// a < b?
	const DatagramSequenceNumberType halfSpan = ((DatagramSequenceNumberType)(const uint32_t)-1)/(DatagramSequenceNumberType)2;
	return b!=a && b-a<halfSpan;
}
// ----------------------------------------------------------------------------------------------------------------------------
uint64_t CCRakNetSlidingWindow::GetBytesPerSecondLimitByCongestionControl(void) const
{
	return 0; // TODO
}
// ----------------------------------------------------------------------------------------------------------------------------
CCTimeType CCRakNetSlidingWindow::GetSenderRTOForACK(void) const
{
	if (lastRtt==UNSET_TIME_US)
		return (CCTimeType) UNSET_TIME_US;
	return (CCTimeType)(lastRtt + SYN);
}
// ----------------------------------------------------------------------------------------------------------------------------
bool CCRakNetSlidingWindow::IsInSlowStart(void) const
{
	return cwnd <= ssThresh || ssThresh==0;
}
// ----------------------------------------------------------------------------------------------------------------------------
#endif
