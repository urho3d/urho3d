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

#include "slikenet/CCRakNetUDT.h"

#if USE_SLIDING_WINDOW_CONGESTION_CONTROL!=1

#include "slikenet/Rand.h"
#include "slikenet/MTUSize.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
//#include <memory.h>
#include "slikenet/assert.h"
#include "slikenet/alloca.h"

using namespace SLNet;

static const double UNSET_TIME_US=-1;
static const double CWND_MIN_THRESHOLD=2.0;
static const double UNDEFINED_TRANSFER_RATE=0.0;
/// Interval at which to update aspects of the system
/// 1. send acks
/// 2. update time interval between outgoing packets
/// 3, Yodate retransmit timeout
#if CC_TIME_TYPE_BYTES==4
static const CCTimeType SYN=10;
#else
static const CCTimeType SYN=10000;
#endif

#if CC_TIME_TYPE_BYTES==4
#define MAX_RTT 1000
#define RTT_TOLERANCE 30
#else
#define MAX_RTT 1000000
#define RTT_TOLERANCE 30000
#endif


double RTTVarMultiple=4.0;


// ****************************************************** PUBLIC METHODS ******************************************************

CCRakNetUDT::CCRakNetUDT()
{
}

// ----------------------------------------------------------------------------------------------------------------------------

CCRakNetUDT::~CCRakNetUDT()
{
}
// ----------------------------------------------------------------------------------------------------------------------------
void CCRakNetUDT::Init(CCTimeType curTime, uint32_t maxDatagramPayload)
{
	(void) curTime;

	nextSYNUpdate=0;
	packetPairRecieptHistoryWriteIndex=0;
	packetArrivalHistoryWriteIndex=0;
	packetArrivalHistoryWriteCount=0;
	RTT=UNSET_TIME_US;
	//	RTTVar=UNSET_TIME_US;
	isInSlowStart=true;
	NAKCount=1000;
	AvgNAKNum=1;
	DecInterval=1;
	DecCount=0;
	nextDatagramSequenceNumber=0;
	lastPacketPairPacketArrivalTime=0;
	lastPacketPairSequenceNumber=(DatagramSequenceNumberType)(const uint32_t)-1;
	lastPacketArrivalTime=0;
	CWND=CWND_MIN_THRESHOLD;
	lastUpdateWindowSizeAndAck=0;
	lastTransmitOfBAndAS=0;
	ExpCount=1.0;
	totalUserDataBytesSent=0;
	oldestUnsentAck=0;
	MAXIMUM_MTU_INCLUDING_UDP_HEADER=maxDatagramPayload;
	CWND_MAX_THRESHOLD=RESEND_BUFFER_ARRAY_LENGTH;
#if CC_TIME_TYPE_BYTES==4
	const BytesPerMicrosecond DEFAULT_TRANSFER_RATE=(BytesPerMicrosecond) 3.6;
#else
	const BytesPerMicrosecond DEFAULT_TRANSFER_RATE=(BytesPerMicrosecond) .0036;
#endif

#if CC_TIME_TYPE_BYTES==4
	lastRttOnIncreaseSendRate=1000;
#else
	lastRttOnIncreaseSendRate=1000000;
#endif
	nextCongestionControlBlock=0;
	lastRtt=0;

	//	B=DEFAULT_TRANSFER_RATE;
	AS=UNDEFINED_TRANSFER_RATE;
	const MicrosecondsPerByte DEFAULT_BYTE_INTERVAL=(MicrosecondsPerByte) (1.0/DEFAULT_TRANSFER_RATE);
	SND=DEFAULT_BYTE_INTERVAL;
	expectedNextSequenceNumber=0;
	sendBAndASCount=0;
	packetArrivalHistoryContinuousGapsIndex=0;
	//packetPairRecipetHistoryGapsIndex=0;
	hasWrittenToPacketPairReceiptHistory=false;
	InitPacketArrivalHistory();

	estimatedLinkCapacityBytesPerSecond=0;
	bytesCanSendThisTick=0;
	hadPacketlossThisBlock=false;
	pingsLastInterval.Clear(__FILE__,__LINE__);
}
// ----------------------------------------------------------------------------------------------------------------------------
void CCRakNetUDT::SetMTU(uint32_t bytes)
{
	MAXIMUM_MTU_INCLUDING_UDP_HEADER=bytes;
}
// ----------------------------------------------------------------------------------------------------------------------------
uint32_t CCRakNetUDT::GetMTU(void) const
{
	return MAXIMUM_MTU_INCLUDING_UDP_HEADER;
}
// ----------------------------------------------------------------------------------------------------------------------------
void CCRakNetUDT::Update(CCTimeType curTime, bool hasDataToSendOrResend)
{
	(void) hasDataToSendOrResend;
	(void) curTime;

	return;

	// I suspect this is causing major lag

	/*
	if (hasDataToSendOrResend==false)
	halveSNDOnNoDataTime=0;
	else if (halveSNDOnNoDataTime==0)
	{
	UpdateHalveSNDOnNoDataTime(curTime);
	ExpCount=1.0;
	}

	// If you send, and get no data at all from that time to RTO, then halve send rate7
	if (HasHalveSNDOnNoDataTimeElapsed(curTime))
	{
	/// 2000 bytes per second
	/// 0.0005 seconds per byte
	/// 0.5 milliseconds per byte
	/// 500 microseconds per byte
	// printf("No incoming data, halving send rate\n");
	SND*=2.0;
	CapMinSnd(_FILE_AND_LINE_);
	ExpCount+=1.0;
	if (ExpCount>8.0)
	ExpCount=8.0;

	UpdateHalveSNDOnNoDataTime(curTime);
	}
	*/
}
// ----------------------------------------------------------------------------------------------------------------------------
int CCRakNetUDT::GetRetransmissionBandwidth(CCTimeType curTime, CCTimeType timeSinceLastTick, uint32_t unacknowledgedBytes, bool isContinuousSend)
{
	(void) curTime;

	if (isInSlowStart)
	{
		uint32_t CWNDLimit = (uint32_t) (CWND*MAXIMUM_MTU_INCLUDING_UDP_HEADER);
		return CWNDLimit;
	}
	return GetTransmissionBandwidth(curTime,timeSinceLastTick,unacknowledgedBytes,isContinuousSend);
}
// ----------------------------------------------------------------------------------------------------------------------------
int CCRakNetUDT::GetTransmissionBandwidth(CCTimeType curTime, CCTimeType timeSinceLastTick, uint32_t unacknowledgedBytes, bool isContinuousSend)
{
	(void) curTime;

	if (isInSlowStart)
	{
		uint32_t CWNDLimit = (uint32_t) (CWND*MAXIMUM_MTU_INCLUDING_UDP_HEADER-unacknowledgedBytes);
		return CWNDLimit;
	}
	if (bytesCanSendThisTick>0)
		bytesCanSendThisTick=0;

#if CC_TIME_TYPE_BYTES==4
	if (isContinuousSend==false && timeSinceLastTick>100)
		timeSinceLastTick=100;
#else
	if (isContinuousSend==false && timeSinceLastTick>100000)
		timeSinceLastTick=100000;
#endif

	bytesCanSendThisTick=(int)((double)timeSinceLastTick*((double)1.0/SND)+(double)bytesCanSendThisTick);
	if (bytesCanSendThisTick>0)
		return bytesCanSendThisTick;
	return 0;
}
uint64_t CCRakNetUDT::GetBytesPerSecondLimitByCongestionControl(void) const
{
	if (isInSlowStart)
		return 0;
#if CC_TIME_TYPE_BYTES==4
	return (uint64_t) ((double)1.0/(SND*1000.0));
#else
	return (uint64_t) ((double)1.0/(SND*1000000.0));
#endif
}
// ----------------------------------------------------------------------------------------------------------------------------
bool CCRakNetUDT::ShouldSendACKs(CCTimeType curTime, CCTimeType estimatedTimeToNextTick)
{
	CCTimeType rto = GetSenderRTOForACK();

	// iphone crashes on comparison between double and int64 http://www.jenkinssoftware.com/forum/index.php?topic=2717.0
	if (rto==(CCTimeType) UNSET_TIME_US)
	{
		// Unknown how long until the remote system will retransmit, so better send right away
		return true;
	}


	//	CCTimeType remoteRetransmitTime=oldestUnsentAck+rto-RTT*.5;
	//	CCTimeType ackArrivalTimeIfWeDelay=RTT*.5+estimatedTimeToNextTick+curTime;
	//	return ackArrivalTimeIfWeDelay<remoteRetransmitTime;

	// Simplified equation
	// GU: At least one ACK should be sent per SYN, otherwise your protocol will increase slower.
	return curTime >= oldestUnsentAck + SYN ||
		estimatedTimeToNextTick+curTime < oldestUnsentAck+rto-RTT;
}
// ----------------------------------------------------------------------------------------------------------------------------
DatagramSequenceNumberType CCRakNetUDT::GetNextDatagramSequenceNumber(void)
{
	return nextDatagramSequenceNumber;
}
// ----------------------------------------------------------------------------------------------------------------------------
DatagramSequenceNumberType CCRakNetUDT::GetAndIncrementNextDatagramSequenceNumber(void)
{
	DatagramSequenceNumberType dsnt=nextDatagramSequenceNumber;
	nextDatagramSequenceNumber++;
	return dsnt;
}
// ----------------------------------------------------------------------------------------------------------------------------
void CCRakNetUDT::OnSendBytes(CCTimeType curTime, uint32_t numBytes)
{
	(void) curTime;

	totalUserDataBytesSent+=numBytes;
	if (isInSlowStart==false)
		bytesCanSendThisTick-=numBytes;
}

// ****************************************************** PROTECTED METHODS ******************************************************

void CCRakNetUDT::SetNextSYNUpdate(CCTimeType currentTime)
{
	nextSYNUpdate+=SYN;
	if (nextSYNUpdate < currentTime)
		nextSYNUpdate=currentTime+SYN;
}
// ----------------------------------------------------------------------------------------------------------------------------
BytesPerMicrosecond CCRakNetUDT::ReceiverCalculateDataArrivalRate(CCTimeType curTime) const
{
	(void) curTime;
	// Not an instantaneous measurement
	/*
	if (continuousBytesReceivedStartTime!=0 && curTime>continuousBytesReceivedStartTime)
	{
	#if CC_TIME_TYPE_BYTES==4
	const CCTimeType threshold=100;
	#else
	const CCTimeType threshold=100000;
	#endif
	if (curTime-continuousBytesReceivedStartTime>threshold)
	return (BytesPerMicrosecond) continuousBytesReceived/(BytesPerMicrosecond) (curTime-continuousBytesReceivedStartTime);
	}

	return UNDEFINED_TRANSFER_RATE;
	*/


	if (packetArrivalHistoryWriteCount<CC_RAKNET_UDT_PACKET_HISTORY_LENGTH)
		return UNDEFINED_TRANSFER_RATE;

	BytesPerMicrosecond median = ReceiverCalculateDataArrivalRateMedian();
	int i;
	const BytesPerMicrosecond oneEighthMedian=median*(1.0/8.0);
	const BytesPerMicrosecond eightTimesMedian=median*8.0f;
	BytesPerMicrosecond medianListLength=0.0;
	BytesPerMicrosecond sum=0.0;
	// Find average of acceptedMedianValues
	for (i=0; i < CC_RAKNET_UDT_PACKET_HISTORY_LENGTH; i++)
	{
		if (packetArrivalHistory[i]>=oneEighthMedian &&
			packetArrivalHistory[i]<eightTimesMedian)
		{
			medianListLength=medianListLength+1.0;
			sum+=packetArrivalHistory[i];
		}
	}
	if (medianListLength==0.0)
		return UNDEFINED_TRANSFER_RATE;
	return sum/medianListLength;
}
// ----------------------------------------------------------------------------------------------------------------------------
BytesPerMicrosecond CCRakNetUDT::ReceiverCalculateDataArrivalRateMedian(void) const
{
	return CalculateListMedianRecursive(packetArrivalHistory, CC_RAKNET_UDT_PACKET_HISTORY_LENGTH, 0, 0);
}
// ----------------------------------------------------------------------------------------------------------------------------
BytesPerMicrosecond CCRakNetUDT::CalculateListMedianRecursive(const BytesPerMicrosecond inputList[CC_RAKNET_UDT_PACKET_HISTORY_LENGTH], int inputListLength, int lessThanSum, int greaterThanSum)
{
	BytesPerMicrosecond lessThanMedian[CC_RAKNET_UDT_PACKET_HISTORY_LENGTH], greaterThanMedian[CC_RAKNET_UDT_PACKET_HISTORY_LENGTH];
	int lessThanMedianListLength=0, greaterThanMedianListLength=0;
	BytesPerMicrosecond median=inputList[0];
	int i;
	for (i=1; i < inputListLength; i++)
	{
		// If same value, spread among lists evenly
		if (inputList[i]<median || ((i&1)==0 && inputList[i]==median))
			lessThanMedian[lessThanMedianListLength++]=inputList[i];
		else
			greaterThanMedian[greaterThanMedianListLength++]=inputList[i];
	}
	RakAssert(CC_RAKNET_UDT_PACKET_HISTORY_LENGTH%2==0);
	if (lessThanMedianListLength+lessThanSum==greaterThanMedianListLength+greaterThanSum+1 ||
		lessThanMedianListLength+lessThanSum==greaterThanMedianListLength+greaterThanSum-1)
		return median;

	if (lessThanMedianListLength+lessThanSum < greaterThanMedianListLength+greaterThanSum)
	{
		lessThanMedian[lessThanMedianListLength++]=median;
		return CalculateListMedianRecursive(greaterThanMedian, greaterThanMedianListLength, lessThanMedianListLength+lessThanSum, greaterThanSum);
	}
	else
	{
		greaterThanMedian[greaterThanMedianListLength++]=median;
		return CalculateListMedianRecursive(lessThanMedian, lessThanMedianListLength, lessThanSum, greaterThanMedianListLength+greaterThanSum);		
	}
}

// ----------------------------------------------------------------------------------------------------------------------------
bool CCRakNetUDT::GreaterThan(DatagramSequenceNumberType a, DatagramSequenceNumberType b)
{
	// a > b?
	const DatagramSequenceNumberType halfSpan =(DatagramSequenceNumberType) (((DatagramSequenceNumberType)(const uint32_t)-1)/(DatagramSequenceNumberType)2);
	return b!=a && b-a>halfSpan;
}
// ----------------------------------------------------------------------------------------------------------------------------
bool CCRakNetUDT::LessThan(DatagramSequenceNumberType a, DatagramSequenceNumberType b)
{
	// a < b?
	const DatagramSequenceNumberType halfSpan = ((DatagramSequenceNumberType)(const uint32_t)-1)/(DatagramSequenceNumberType)2;
	return b!=a && b-a<halfSpan;
}
// ----------------------------------------------------------------------------------------------------------------------------
CCTimeType CCRakNetUDT::GetSenderRTOForACK(void) const
{
	if (RTT==UNSET_TIME_US)
		return (CCTimeType) UNSET_TIME_US;
	double RTTVar = maxRTT-minRTT;
	return (CCTimeType)(RTT + RTTVarMultiple * RTTVar + SYN);
}
// ----------------------------------------------------------------------------------------------------------------------------
CCTimeType CCRakNetUDT::GetRTOForRetransmission(unsigned char timesSent) const
{
#if CC_TIME_TYPE_BYTES==4
	const CCTimeType maxThreshold=10000;
	const CCTimeType minThreshold=100;
#else
	const CCTimeType maxThreshold=1000000;
	const CCTimeType minThreshold=100000;
#endif

	if (RTT==UNSET_TIME_US)
	{
		return (CCTimeType) maxThreshold;
	}

	CCTimeType ret = lastRttOnIncreaseSendRate*2;

	if (ret<minThreshold)
		return minThreshold;
	if (ret>maxThreshold)
		return maxThreshold;
	return ret;
}
// ----------------------------------------------------------------------------------------------------------------------------
void CCRakNetUDT::OnResend(CCTimeType curTime, SLNet::TimeUS nextActionTime)
{
	(void) curTime;

	if (isInSlowStart)
	{
		if (AS!=UNDEFINED_TRANSFER_RATE)
			EndSlowStart();
		return;
	}

	if (hadPacketlossThisBlock==false)
	{
		// Logging
		// printf("Sending SLOWER due to Resend, Rate=%f MBPS. Rtt=%i\n", GetLocalSendRate(),  lastRtt );

		IncreaseTimeBetweenSends();
		hadPacketlossThisBlock=true;
	}
}
// ----------------------------------------------------------------------------------------------------------------------------
void CCRakNetUDT::OnNAK(CCTimeType curTime, DatagramSequenceNumberType nakSequenceNumber)
{
	(void) nakSequenceNumber;
	(void) curTime;

	if (isInSlowStart)
	{
		if (AS!=UNDEFINED_TRANSFER_RATE)
			EndSlowStart();
		return;
	}

	if (hadPacketlossThisBlock==false)
	{
		// Logging
		//printf("Sending SLOWER due to NAK, Rate=%f MBPS. Rtt=%i\n", GetLocalSendRate(),  lastRtt );
		if (pingsLastInterval.Size()>10)
		{
			for (int i=0; i < 10; i++)
				printf("%i, ", pingsLastInterval[pingsLastInterval.Size()-1-i]/1000);
		}
		printf("\n");
		IncreaseTimeBetweenSends();

		hadPacketlossThisBlock=true;
	}
}
// ----------------------------------------------------------------------------------------------------------------------------
void CCRakNetUDT::EndSlowStart(void)
{
	RakAssert(isInSlowStart==true);
	RakAssert(AS!=UNDEFINED_TRANSFER_RATE);

	// This overestimates
	estimatedLinkCapacityBytesPerSecond=AS * 1000000.0;

	isInSlowStart=false;
	SND=1.0/AS;
	CapMinSnd(_FILE_AND_LINE_);

	// printf("ENDING SLOW START\n");
#if CC_TIME_TYPE_BYTES==4
	//	printf("Initial SND=%f Kilobytes per second\n", 1.0/SND);
#else
	//	printf("Initial SND=%f Megabytes per second\n", 1.0/SND);
#endif
	if (SND > .1)
		PrintLowBandwidthWarning();
}
// ----------------------------------------------------------------------------------------------------------------------------
void CCRakNetUDT::OnGotPacketPair(DatagramSequenceNumberType datagramSequenceNumber, uint32_t sizeInBytes, CCTimeType curTime)
{
	(void) datagramSequenceNumber;
	(void) sizeInBytes;
	(void) curTime;

}
// ----------------------------------------------------------------------------------------------------------------------------
bool CCRakNetUDT::OnGotPacket(DatagramSequenceNumberType datagramSequenceNumber, bool isContinuousSend, CCTimeType curTime, uint32_t sizeInBytes, uint32_t *skippedMessageCount)
{	
	CC_DEBUG_PRINTF_2("R%i ",datagramSequenceNumber.val);

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

	if (curTime>lastPacketArrivalTime)
	{
		CCTimeType interval = curTime-lastPacketArrivalTime;

		//		printf("Packet arrival gap is %I64u\n", (interval));

		if (isContinuousSend)
		{
			continuousBytesReceived+=sizeInBytes;
			if (continuousBytesReceivedStartTime==0)
				continuousBytesReceivedStartTime=lastPacketArrivalTime;


			mostRecentPacketArrivalHistory=(BytesPerMicrosecond)sizeInBytes/(BytesPerMicrosecond)interval;

			//		if (mostRecentPacketArrivalHistory < (BytesPerMicrosecond)0.0035)
			//		{
			//			printf("%s:%i LIKELY BUG: Calculated packetArrivalHistory is below 28.8 Kbps modem\nReport to rakkar@jenkinssoftware.com with file and line number\n", _FILE_AND_LINE_);
			//		}

			packetArrivalHistoryContinuousGaps[packetArrivalHistoryContinuousGapsIndex++]=(int) interval;
			packetArrivalHistoryContinuousGapsIndex&=(CC_RAKNET_UDT_PACKET_HISTORY_LENGTH-1);

			packetArrivalHistoryWriteCount++;
			packetArrivalHistory[packetArrivalHistoryWriteIndex++]=mostRecentPacketArrivalHistory;
			// Wrap to 0 at the end of the range
			// Assumes power of 2 for CC_RAKNET_UDT_PACKET_HISTORY_LENGTH
			packetArrivalHistoryWriteIndex&=(CC_RAKNET_UDT_PACKET_HISTORY_LENGTH-1);
		}
		else
		{
			continuousBytesReceivedStartTime=0;
			continuousBytesReceived=0;
		}

		lastPacketArrivalTime=curTime;
	}
	return true;
}
// ----------------------------------------------------------------------------------------------------------------------------
void CCRakNetUDT::OnAck(CCTimeType curTime, CCTimeType rtt, bool hasBAndAS, BytesPerMicrosecond _B, BytesPerMicrosecond _AS, double totalUserDataBytesAcked, bool isContinuousSend, DatagramSequenceNumberType sequenceNumber )
{
#if CC_TIME_TYPE_BYTES==4
	RakAssert(rtt < 10000);
#else
	RakAssert(rtt < 10000000);
#endif
	(void) _B;

	if (hasBAndAS)
	{
		///	RakAssert(_B!=UNDEFINED_TRANSFER_RATE && _AS!=UNDEFINED_TRANSFER_RATE);
		//	B=B * .875 + _B * .125;
		// AS is packet arrival rate
		RakAssert(_AS!=UNDEFINED_TRANSFER_RATE);
		AS=_AS;
		CC_DEBUG_PRINTF_4("ArrivalRate=%f linkCap=%f incomingLinkCap=%f\n", _AS,B,_B);
	}

	if (oldestUnsentAck==0)
		oldestUnsentAck=curTime;

	if (isInSlowStart==true)
	{
		nextCongestionControlBlock=nextDatagramSequenceNumber;
		lastRttOnIncreaseSendRate=rtt;
		UpdateWindowSizeAndAckOnAckPreSlowStart(totalUserDataBytesAcked);
	}
	else
	{
		UpdateWindowSizeAndAckOnAckPerSyn(curTime, rtt, isContinuousSend, sequenceNumber);
	}

	lastUpdateWindowSizeAndAck=curTime;
}
// ----------------------------------------------------------------------------------------------------------------------------
void CCRakNetUDT::OnSendAckGetBAndAS(CCTimeType curTime, bool *hasBAndAS, BytesPerMicrosecond *_B, BytesPerMicrosecond *_AS)
{
	if (curTime>lastTransmitOfBAndAS+SYN)
	{
		*_B=0;
		*_AS=ReceiverCalculateDataArrivalRate(curTime);

		if (*_AS==UNDEFINED_TRANSFER_RATE)
		{
			*hasBAndAS=false;
		}
		else
		{
			*hasBAndAS=true;
		}
	}
	else
	{
		*hasBAndAS=false;
	}
}
// ----------------------------------------------------------------------------------------------------------------------------
void CCRakNetUDT::OnSendAck(CCTimeType curTime, uint32_t numBytes)
{
	(void) numBytes;
	(void) curTime;

	// This is not accounted for on the remote system, and thus causes bandwidth to be underutilized
	//UpdateNextAllowedSend(curTime, numBytes+UDP_HEADER_SIZE);

	oldestUnsentAck=0;
}
// ----------------------------------------------------------------------------------------------------------------------------
void CCRakNetUDT::OnSendNACK(CCTimeType curTime, uint32_t numBytes)
{
	(void) numBytes;
	(void) curTime;

	// This is not accounted for on the remote system, and thus causes bandwidth to be underutilized
	//	UpdateNextAllowedSend(curTime, numBytes+UDP_HEADER_SIZE);
}
// ----------------------------------------------------------------------------------------------------------------------------
void CCRakNetUDT::UpdateWindowSizeAndAckOnAckPreSlowStart(double totalUserDataBytesAcked)
{
	// During slow start, max window size is the number of full packets that have been sent out
	// CWND=(double) ((double)totalUserDataBytesSent/(double)MAXIMUM_MTU_INCLUDING_UDP_HEADER);
	CC_DEBUG_PRINTF_3("CWND increasing from %f to %f\n", CWND, (double) ((double)totalUserDataBytesAcked/(double)MAXIMUM_MTU_INCLUDING_UDP_HEADER));
	CWND=(double) ((double)totalUserDataBytesAcked/(double)MAXIMUM_MTU_INCLUDING_UDP_HEADER);
	if (CWND>=CWND_MAX_THRESHOLD)
	{
		CWND=CWND_MAX_THRESHOLD;

		if (AS!=UNDEFINED_TRANSFER_RATE)
			EndSlowStart();
	}
	if (CWND<CWND_MIN_THRESHOLD)
		CWND=CWND_MIN_THRESHOLD;
}
// ----------------------------------------------------------------------------------------------------------------------------
void CCRakNetUDT::UpdateWindowSizeAndAckOnAckPerSyn(CCTimeType curTime, CCTimeType rtt, bool isContinuousSend, DatagramSequenceNumberType sequenceNumber)
{	
	(void) curTime;
	(void) sequenceNumber;
	if (isContinuousSend==false)
	{
		nextCongestionControlBlock=nextDatagramSequenceNumber;
		pingsLastInterval.Clear(__FILE__,__LINE__);
		return;
	}

	pingsLastInterval.Push(rtt,__FILE__,__LINE__);
	static const int intervalSize=33; // Should be odd
	if (pingsLastInterval.Size()>intervalSize)
		pingsLastInterval.Pop();
	if (GreaterThan(sequenceNumber, nextCongestionControlBlock) &&
		sequenceNumber-nextCongestionControlBlock>=intervalSize &&
		pingsLastInterval.Size()==intervalSize)
	{
		double slopeSum=0.0;
		double average=(double) pingsLastInterval[0];
		int sampleSize=pingsLastInterval.Size();
		for (int i=1; i < sampleSize; i++)
		{
			slopeSum+=(double)pingsLastInterval[i]-(double)pingsLastInterval[i-1];
			average+=pingsLastInterval[i];
		}
		average/=sampleSize;
		
		if (hadPacketlossThisBlock==true)
		{
		}
		else if (slopeSum < -.10*average)
		{
			// Logging
			//printf("Ping dropping. slope=%f%%. Rate=%f MBPS. Rtt=%i\n", 100.0*slopeSum/average, GetLocalSendRate(),  rtt );
		}
		else if (slopeSum > .10*average)
		{
			// Logging
			//printf("Ping rising. slope=%f%%. Rate=%f MBPS. Rtt=%i\n", 100.0*slopeSum/average, GetLocalSendRate(),  rtt );
			IncreaseTimeBetweenSends();
		}
		else
		{
			// Logging
			//printf("Ping stable. slope=%f%%. Rate=%f MBPS. Rtt=%i\n", 100.0*slopeSum/average, GetLocalSendRate(),  rtt );

			// No packetloss over time threshhold, and rtt decreased, so send faster
			lastRttOnIncreaseSendRate=rtt;
			DecreaseTimeBetweenSends();
		}

		pingsLastInterval.Clear(__FILE__,__LINE__);
		hadPacketlossThisBlock=false;
		nextCongestionControlBlock=nextDatagramSequenceNumber;
	}

	lastRtt=rtt;
}

// ----------------------------------------------------------------------------------------------------------------------------
double CCRakNetUDT::BytesPerMicrosecondToPacketsPerMillisecond(BytesPerMicrosecond in)
{
#if CC_TIME_TYPE_BYTES==4
	const BytesPerMicrosecond factor = 1.0 / (BytesPerMicrosecond) MAXIMUM_MTU_INCLUDING_UDP_HEADER;
#else
	const BytesPerMicrosecond factor = 1000.0 / (BytesPerMicrosecond) MAXIMUM_MTU_INCLUDING_UDP_HEADER;
#endif
	return in * factor;
}
// ----------------------------------------------------------------------------------------------------------------------------
void CCRakNetUDT::InitPacketArrivalHistory(void)
{
	unsigned int i;
	for (i=0; i < CC_RAKNET_UDT_PACKET_HISTORY_LENGTH; i++)
	{
		packetArrivalHistory[i]=UNDEFINED_TRANSFER_RATE;
		packetArrivalHistoryContinuousGaps[i]=0;
	}

	packetArrivalHistoryWriteCount=0;
	continuousBytesReceived=0;
	continuousBytesReceivedStartTime=0;
}
// ----------------------------------------------------------------------------------------------------------------------------
void CCRakNetUDT::PrintLowBandwidthWarning(void)
{

	/*
	printf("\n-------LOW BANDWIDTH -----\n");
	if (isInSlowStart==false)
	printf("SND=%f Megabytes per second\n", 1.0/SND);
	printf("Window size=%f\n", CWND);
	printf("Pipe from packet pair = %f megabytes per second\n", B);
	printf("RTT=%f milliseconds\n", RTT/1000.0);
	printf("RTT Variance=%f milliseconds\n", RTTVar/1000.0);
	printf("Retransmission=%i milliseconds\n", GetRTOForRetransmission(1)/1000);
	printf("Packet arrival rate on the remote system=%f megabytes per second\n", AS);
	printf("Packet arrival rate on our system=%f megabytes per second\n", ReceiverCalculateDataArrivalRate());
	printf("isInSlowStart=%i\n", isInSlowStart);
	printf("---------------\n");
	*/
}
BytesPerMicrosecond CCRakNetUDT::GetLocalReceiveRate(CCTimeType currentTime) const
{
	return ReceiverCalculateDataArrivalRate(currentTime);
}
double CCRakNetUDT::GetRTT(void) const
{
	if (RTT==UNSET_TIME_US)
		return 0.0;
	return RTT;
}
void CCRakNetUDT::CapMinSnd(const char *file, int line)
{
	(void) file;
	(void) line;

	if (SND > 500)
	{
		SND=500;
		CC_DEBUG_PRINTF_3("%s:%i LIKELY BUG: SND has gotten above 500 microseconds between messages (28.8 modem)\nReport to rakkar@jenkinssoftware.com with file and line number\n", file, line);
	}
}
void CCRakNetUDT::IncreaseTimeBetweenSends(void)
{
	// In order to converge, bigger numbers have to increase slower and decrease faster
	// SND==500 then increment is .02
	// SND==0 then increment is near 0
	// (SND+1.0) brings it to the range of 1 to 501
	// Square the number, which is the range of 1 to 251001
	// Divide by 251001, which is the range of 1/251001 to 1

	double increment;
	increment = .02 * ((SND+1.0) * (SND+1.0)) / (501.0*501.0) ;
	// SND=500 then increment=.02
	// SND=0 then increment=near 0
	SND*=(1.02 - increment);

	// SND=0 then fast increase, slow decrease
	// SND=500 then slow increase, fast decrease
	CapMinSnd(__FILE__,__LINE__);
}
void CCRakNetUDT::DecreaseTimeBetweenSends(void)
{
	double increment;
	increment = .01 * ((SND+1.0) * (SND+1.0)) / (501.0*501.0) ;
	// SND=500 then increment=.01
	// SND=0 then increment=near 0
	SND*=(.99 - increment);
}
/*
void CCRakNetUDT::SetTimeBetweenSendsLimit(unsigned int bitsPerSecond)
{
// 	bitsPerSecond / 1000000 = bitsPerMicrosecond
// 	bitsPerMicrosecond / 8 = BytesPerMicrosecond
// 	1 / BytesPerMicrosecond = MicrosecondsPerByte
// 	1 / ( (bitsPerSecond / 1000000)  / 8 ) = 
// 	1 / (bitsPerSecond / 8000000) =
// 	8000000 / bitsPerSecond

#if CC_TIME_TYPE_BYTES==4
	MicrosecondsPerByte limit = (MicrosecondsPerByte) 8000 / (MicrosecondsPerByte)bitsPerSecond;
#else
	MicrosecondsPerByte limit = (MicrosecondsPerByte) 8000000 / (MicrosecondsPerByte)bitsPerSecond;
#endif
	if (limit > SND)
		SND=limit;
}
*/

#endif
