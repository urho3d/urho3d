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
///



#include "slikenet/ReliabilityLayer.h"
#include "slikenet/GetTime.h"
#include "slikenet/SocketLayer.h"
#include "slikenet/PluginInterface2.h"
#include "slikenet/assert.h"
#include "slikenet/Rand.h"
#include "slikenet/MessageIdentifiers.h"
#ifdef USE_THREADED_SEND
#include "slikenet/SendToThread.h"
#endif
#include <math.h>
#include "slikenet/linux_adapter.h"
#include "slikenet/osx_adapter.h"

using namespace SLNet;

// Can't figure out which library has this function on the PS3
double Ceil(double d) {if (((double)((int)d))==d) return d; return (int) (d+1.0);}

// #if defined(new)
// #pragma push_macro("new")
// #undef new
// #define RELIABILITY_LAYER_NEW_UNDEF_ALLOCATING_QUEUE
// #endif


//#define _DEBUG_LOGGER

#if CC_TIME_TYPE_BYTES==4
static const CCTimeType MAX_TIME_BETWEEN_PACKETS= 350; // 350 milliseconds
static const CCTimeType HISTOGRAM_RESTART_CYCLE=10000; // Every 10 seconds reset the histogram
#else
static const CCTimeType MAX_TIME_BETWEEN_PACKETS= 350000; // 350 milliseconds
//static const CCTimeType HISTOGRAM_RESTART_CYCLE=10000000; // Every 10 seconds reset the histogram
#endif
static const int DEFAULT_HAS_RECEIVED_PACKET_QUEUE_SIZE=512;
static const CCTimeType STARTING_TIME_BETWEEN_PACKETS=MAX_TIME_BETWEEN_PACKETS;
//static const long double TIME_BETWEEN_PACKETS_INCREASE_MULTIPLIER_DEFAULT=.02;
//static const long double TIME_BETWEEN_PACKETS_DECREASE_MULTIPLIER_DEFAULT=1.0 / 9.0;

typedef uint32_t BitstreamLengthEncoding;

//#define PRINT_TO_FILE_RELIABLE_ORDERED_TEST
#ifdef PRINT_TO_FILE_RELIABLE_ORDERED_TEST
static unsigned int packetNumber=0;
static FILE *fp=0;
#endif

//#define FLIP_SEND_ORDER_TEST
//#define LOG_TRIVIAL_NOTIFICATIONS

BPSTracker::TimeAndValue2::TimeAndValue2() {}
BPSTracker::TimeAndValue2::~TimeAndValue2() {}
BPSTracker::TimeAndValue2::TimeAndValue2(SLNet::TimeUS t, uint64_t v1) : value1(v1), time(t) {}
//BPSTracker::TimeAndValue2::TimeAndValue2(SLNet::TimeUS t, uint64_t v1, uint64_t v2) : time(t), value1(v1), value2(v2) {}
BPSTracker::BPSTracker() {Reset(_FILE_AND_LINE_);}
BPSTracker::~BPSTracker() {}
//void BPSTracker::Reset(const char *file, unsigned int line) {total1=total2=lastSec1=lastSec2=0; dataQueue.Clear(file,line);}
void BPSTracker::Reset(const char *file, unsigned int line) {total1=lastSec1=0; dataQueue.Clear(file,line);}
//void BPSTracker::Push2(RakNetTimeUS time, uint64_t value1, uint64_t value2) {dataQueue.Push(TimeAndValue2(time,value1,value2),_FILE_AND_LINE_); total1+=value1; lastSec1+=value1;  total2+=value2; lastSec2+=value2;}
//uint64_t BPSTracker::GetBPS2(RakNetTimeUS time) {ClearExpired2(time); return lastSec2;}
//void BPSTracker::GetBPS1And2(RakNetTimeUS time, uint64_t &out1, uint64_t &out2) {ClearExpired2(time); out1=lastSec1; out2=lastSec2;}
uint64_t BPSTracker::GetTotal1(void) const {return total1;}
//uint64_t BPSTracker::GetTotal2(void) const {return total2;}

// void BPSTracker::ClearExpired2(SLNet::TimeUS time) {
// 	SLNet::TimeUS threshold=time;
// 	if (threshold < 1000000)
// 		return;
// 	threshold-=1000000;
// 	while (dataQueue.IsEmpty()==false && dataQueue.Peek().time < threshold)
// 	{
// 		lastSec1-=dataQueue.Peek().value1;
// 		lastSec2-=dataQueue.Peek().value2;
// 		dataQueue.Pop();
// 	}
// }
void BPSTracker::ClearExpired1(SLNet::TimeUS time)
{
	while (dataQueue.IsEmpty()==false &&
#if CC_TIME_TYPE_BYTES==8
		dataQueue.Peek().time+1000000 < time
#else
		dataQueue.Peek().time+1000 < time
#endif
		)
	{
		lastSec1-=dataQueue.Peek().value1;
		dataQueue.Pop();
	}
}

struct DatagramHeaderFormat
{
#if INCLUDE_TIMESTAMP_WITH_DATAGRAMS==1
	CCTimeType sourceSystemTime;
#endif
	DatagramSequenceNumberType datagramNumber;

	// Use floats to save bandwidth
	//	float B; // Link capacity
	float AS; // Data arrival rate
	bool isACK;
	bool isNAK;
	bool isPacketPair;
	bool hasBAndAS;
	bool isContinuousSend;
	bool needsBAndAs;
	bool isValid; // To differentiate between what I serialized, and offline data

	static BitSize_t GetDataHeaderBitLength()
	{
		return BYTES_TO_BITS(GetDataHeaderByteLength());
	}

	static unsigned int GetDataHeaderByteLength()
	{
		//return 2 + 3 + sizeof(SLNet::TimeMS) + sizeof(float)*2;
		return 2 + 3 +
#if INCLUDE_TIMESTAMP_WITH_DATAGRAMS==1
			sizeof(RakNetTimeMS) +
#endif
			sizeof(float)*1;
	}

	void Serialize(SLNet::BitStream *b)
	{
		// Not endian safe
		//		RakAssert(GetDataHeaderByteLength()==sizeof(DatagramHeaderFormat));
		//		b->WriteAlignedBytes((const unsigned char*) this, sizeof(DatagramHeaderFormat));
		//		return;

		b->Write(true); // IsValid
		if (isACK)
		{
			b->Write(true);
			b->Write(hasBAndAS);
			b->AlignWriteToByteBoundary();
#if INCLUDE_TIMESTAMP_WITH_DATAGRAMS==1
			SLNet::TimeMS timeMSLow=(SLNet::TimeMS) sourceSystemTime&0xFFFFFFFF; b->Write(timeMSLow);
#endif
			if (hasBAndAS)
			{
				//		b->Write(B);
				b->Write(AS);
			}
		}
		else if (isNAK)
		{
			b->Write(false);
			b->Write(true);
		}
		else
		{
			b->Write(false);
			b->Write(false);
			b->Write(isPacketPair);
			b->Write(isContinuousSend);
			b->Write(needsBAndAs);
			b->AlignWriteToByteBoundary();
#if INCLUDE_TIMESTAMP_WITH_DATAGRAMS==1
			SLNet::TimeMS timeMSLow=(SLNet::TimeMS) sourceSystemTime&0xFFFFFFFF; b->Write(timeMSLow);
#endif
			b->Write(datagramNumber);
		}
	}
	void Deserialize(SLNet::BitStream *b)
	{
		// Not endian safe
		//		b->ReadAlignedBytes((unsigned char*) this, sizeof(DatagramHeaderFormat));
		//		return;

		b->Read(isValid);
		b->Read(isACK);
		if (isACK)
		{
			isNAK=false;
			isPacketPair=false;
			b->Read(hasBAndAS);
			b->AlignReadToByteBoundary();
#if INCLUDE_TIMESTAMP_WITH_DATAGRAMS==1
			SLNet::TimeMS timeMS; b->Read(timeMS); sourceSystemTime=(CCTimeType) timeMS;
#endif
			if (hasBAndAS)
			{
				//			b->Read(B);
				b->Read(AS);
			}
		}
		else
		{
			b->Read(isNAK);
			if (isNAK)
			{
				isPacketPair=false;
			}
			else
			{
				b->Read(isPacketPair);
				b->Read(isContinuousSend);
				b->Read(needsBAndAs);
				b->AlignReadToByteBoundary();
#if INCLUDE_TIMESTAMP_WITH_DATAGRAMS==1
				SLNet::TimeMS timeMS; b->Read(timeMS); sourceSystemTime=(CCTimeType) timeMS;
#endif
				b->Read(datagramNumber);
			}
		}
	}
};

#ifdef _WIN32
//#define _DEBUG_LOGGER
#ifdef _DEBUG_LOGGER
#include "slikenet/WindowsIncludes.h"
#endif
#endif

//#define DEBUG_SPLIT_PACKET_PROBLEMS
#if defined (DEBUG_SPLIT_PACKET_PROBLEMS)
static int waitFlag=-1;
#endif

using namespace SLNet;

SplitPacketSort::SplitPacketSort() :
	m_data(nullptr),
	m_allocationSize(0),
	m_addedPacketsCount(0)
{
}

SplitPacketSort::~SplitPacketSort()
{
	if (m_allocationSize)
		OP_DELETE_ARRAY(m_data, _FILE_AND_LINE_);
}

void SplitPacketSort::Preallocate(InternalPacket *internalPacket, const char *file, unsigned int line)
{
	RakAssert(m_data == nullptr);
	m_allocationSize = internalPacket->splitPacketCount;
	m_data = OP_NEW_ARRAY<InternalPacket*>(m_allocationSize, file, line);
	m_packetId = internalPacket->splitPacketId;

	for (size_t i = 0; i < m_allocationSize; ++i)
		m_data[i] = nullptr;
}

bool SplitPacketSort::AllPacketsAdded() const
{
	return GetAllocSize() == GetNumAddedPackets();
}

size_t SplitPacketSort::GetAllocSize() const
{
	return m_allocationSize;
}

unsigned int SplitPacketSort::GetNumAddedPackets() const
{
	return m_addedPacketsCount;
}

SplitPacketIdType SplitPacketSort::GetPacketId() const
{
	RakAssert(m_data != nullptr);
	return m_packetId;
}

InternalPacket*& SplitPacketSort::operator[](size_t index)
{
	RakAssert(m_data != nullptr);
	RakAssert(index < m_allocationSize);
	return m_data[index];
}

bool SplitPacketSort::Add(InternalPacket *internalPacket)
{
	RakAssert(m_data != nullptr);
	RakAssert(internalPacket->splitPacketIndex < m_allocationSize);
	RakAssert(m_packetId == internalPacket->splitPacketId);
	RakAssert(m_data[internalPacket->splitPacketIndex] == nullptr);

	if (m_data[internalPacket->splitPacketIndex] == nullptr) {
		m_data[internalPacket->splitPacketIndex] = internalPacket;
		++m_addedPacketsCount;
		return true;
	}
	return false;
}

int SLNet::SplitPacketChannelComp( SplitPacketIdType const &key, SplitPacketChannel* const &data )
{
#if PREALLOCATE_LARGE_MESSAGES==1
	if (key < data->returnedPacket->splitPacketId)
		return -1;
	if (key == data->returnedPacket->splitPacketId)
		return 0;
#else
	if (key < data->splitPacketList.GetPacketId())
		return -1;
	if (key == data->splitPacketList.GetPacketId())
		return 0;
#endif
	return 1;
}

// DEFINE_MULTILIST_PTR_TO_MEMBER_COMPARISONS( InternalPacket, SplitPacketIndexType, splitPacketIndex )
/*
bool operator<( const DataStructures::MLKeyRef<SplitPacketIndexType> &inputKey, const InternalPacket *cls )
{
	return inputKey.Get() < cls->splitPacketIndex;
}
bool operator>( const DataStructures::MLKeyRef<SplitPacketIndexType> &inputKey, const InternalPacket *cls )
{
	return inputKey.Get() > cls->splitPacketIndex;
}
bool operator==( const DataStructures::MLKeyRef<SplitPacketIndexType> &inputKey, const InternalPacket *cls )
{
	return inputKey.Get() == cls->splitPacketIndex;
}
/// Semi-hack: This is necessary to call Sort()
bool operator<( const DataStructures::MLKeyRef<InternalPacket *> &inputKey, const InternalPacket *cls )
{
	return inputKey.Get()->splitPacketIndex < cls->splitPacketIndex;
}
bool operator>( const DataStructures::MLKeyRef<InternalPacket *> &inputKey, const InternalPacket *cls )
{
	return inputKey.Get()->splitPacketIndex > cls->splitPacketIndex;
}
bool operator==( const DataStructures::MLKeyRef<InternalPacket *> &inputKey, const InternalPacket *cls )
{
	return inputKey.Get()->splitPacketIndex == cls->splitPacketIndex;
}
*/

int SplitPacketIndexComp( SplitPacketIndexType const &key, InternalPacket* const &data )
{
if (key < data->splitPacketIndex)
return -1;
if (key == data->splitPacketIndex)
return 0;
return 1;
}

//-------------------------------------------------------------------------------------------------------
// Constructor
//-------------------------------------------------------------------------------------------------------
// Add 21 to the default MTU so if we encrypt it can hold potentially 21 more bytes of extra data + padding.
ReliabilityLayer::ReliabilityLayer()
{

#ifdef _DEBUG
	// Wait longer to disconnect in debug so I don't get disconnected while tracing
	timeoutTime=30000;
#else
	timeoutTime=10000;
#endif

#ifdef _DEBUG
	minExtraPing=extraPingVariance=0;
	packetloss=(double) minExtraPing;	
#endif


#ifdef PRINT_TO_FILE_RELIABLE_ORDERED_TEST
	if (fp==0 && 0)
	{
		fopen_s(&fp, "reliableorderedoutput.txt", "wt");
	}
#endif

	InitializeVariables();
//int i = sizeof(InternalPacket);
	datagramHistoryMessagePool.SetPageSize(sizeof(MessageNumberNode)*128);
	internalPacketPool.SetPageSize(sizeof(InternalPacket)*INTERNAL_PACKET_PAGE_SIZE);
	refCountedDataPool.SetPageSize(sizeof(InternalPacketRefCountedData)*32);
}

//-------------------------------------------------------------------------------------------------------
// Destructor
//-------------------------------------------------------------------------------------------------------
ReliabilityLayer::~ReliabilityLayer()
{
	FreeMemory( true ); // Free all memory immediately
}
//-------------------------------------------------------------------------------------------------------
// Resets the layer for reuse
//-------------------------------------------------------------------------------------------------------
void ReliabilityLayer::Reset( bool resetVariables, int MTUSize, bool _useSecurity )
{

	FreeMemory( true ); // true because making a memory reset pending in the update cycle causes resets after reconnects.  Instead, just call Reset from a single thread
	if (resetVariables)
	{
		InitializeVariables();

#if LIBCAT_SECURITY==1
		useSecurity = _useSecurity;

		if (_useSecurity)
			MTUSize -= cat::AuthenticatedEncryption::OVERHEAD_BYTES;
#else
		(void) _useSecurity;
#endif // LIBCAT_SECURITY
		congestionManager.Init(SLNet::GetTimeUS(), MTUSize - UDP_HEADER_SIZE);
	}
}

//-------------------------------------------------------------------------------------------------------
// Set the time, in MS, to use before considering ourselves disconnected after not being able to deliver a reliable packet
//-------------------------------------------------------------------------------------------------------
void ReliabilityLayer::SetTimeoutTime(SLNet::TimeMS time )
{
	timeoutTime=time;
}

//-------------------------------------------------------------------------------------------------------
// Returns the value passed to SetTimeoutTime. or the default if it was never called
//-------------------------------------------------------------------------------------------------------
SLNet::TimeMS ReliabilityLayer::GetTimeoutTime(void)
{
	return timeoutTime;
}

//-------------------------------------------------------------------------------------------------------
// Initialize the variables
//-------------------------------------------------------------------------------------------------------
void ReliabilityLayer::InitializeVariables( void )
{
	memset( orderedWriteIndex, 0, NUMBER_OF_ORDERED_STREAMS * sizeof(OrderingIndexType));
	memset( sequencedWriteIndex, 0, NUMBER_OF_ORDERED_STREAMS * sizeof(OrderingIndexType) );
	memset( orderedReadIndex, 0, NUMBER_OF_ORDERED_STREAMS * sizeof(OrderingIndexType) );
	memset( highestSequencedReadIndex, 0, NUMBER_OF_ORDERED_STREAMS * sizeof(OrderingIndexType) );
	memset( &statistics, 0, sizeof( statistics ) );
	memset( &heapIndexOffsets, 0, sizeof( heapIndexOffsets ) );
	
	statistics.connectionStartTime = SLNet::GetTimeUS();
	splitPacketId = 0;
	elapsedTimeSinceLastUpdate=0;
	throughputCapCountdown=0;
	sendReliableMessageNumberIndex = 0;
	internalOrderIndex=0;
	timeToNextUnreliableCull=0;
	unreliableLinkedListHead=0;
	lastUpdateTime= SLNet::GetTimeUS();
	bandwidthExceededStatistic=false;
	remoteSystemTime=0;
	unreliableTimeout=0;
	lastBpsClear=0;

	// Disable packet pairs
	countdownToNextPacketPair=15;

	nextAllowedThroughputSample=0;
	deadConnection = cheater = false;
	timeOfLastContinualSend=0;

	// timeResendQueueNonEmpty = 0;
	timeLastDatagramArrived= SLNet::GetTimeMS();
	//	packetlossThisSample=false;
	//	backoffThisSample=0;
	//	packetlossThisSampleResendCount=0;
	//	lastPacketlossTime=0;
	statistics.messagesInResendBuffer=0;
	statistics.bytesInResendBuffer=0;

	receivedPacketsBaseIndex=0;
	resetReceivedPackets=true;
	receivePacketCount=0; 

	//	SetPing( 1000 );

	timeBetweenPackets=STARTING_TIME_BETWEEN_PACKETS;

	ackPingIndex=0;
	ackPingSum=(CCTimeType)0;

	nextSendTime=lastUpdateTime;
	//nextLowestPingReset=(CCTimeType)0;
	//	continuousSend=false;

	//	histogramStart=(CCTimeType)0;
	//	histogramBitsSent=0;
	unacknowledgedBytes=0;
	resendLinkedListHead=0;
	totalUserDataBytesAcked=0;

	datagramHistoryPopCount=0;

	InitHeapWeights();
	for (int i=0; i < NUMBER_OF_PRIORITIES; i++)
	{
		statistics.messageInSendBuffer[i]=0;
		statistics.bytesInSendBuffer[i]=0.0;
	}

	for (int i=0; i < RNS_PER_SECOND_METRICS_COUNT; i++)
	{
		bpsMetrics[i].Reset(_FILE_AND_LINE_);
	}
}

//-------------------------------------------------------------------------------------------------------
// Frees all allocated memory
//-------------------------------------------------------------------------------------------------------
void ReliabilityLayer::FreeMemory( bool freeAllImmediately )
{
	(void) freeAllImmediately;
	FreeThreadSafeMemory();
}

void ReliabilityLayer::FreeThreadSafeMemory( void )
{
	unsigned i,j;
	InternalPacket *internalPacket;

	ClearPacketsAndDatagrams();

	for (i=0; i < splitPacketChannelList.Size(); i++)
	{
		for (j=0; j < splitPacketChannelList[i]->splitPacketList.GetAllocSize(); j++)
		{
			internalPacket = splitPacketChannelList[i]->splitPacketList[j];
			if (internalPacket != nullptr) {
				FreeInternalPacketData(internalPacket, _FILE_AND_LINE_);
				ReleaseToInternalPacketPool(internalPacket);
			}
		}
#if PREALLOCATE_LARGE_MESSAGES==1
		if (splitPacketChannelList[i]->returnedPacket)
		{
			FreeInternalPacketData(splitPacketChannelList[i]->returnedPacket, __FILE__, __LINE__ );
			ReleaseToInternalPacketPool( splitPacketChannelList[i]->returnedPacket );
		}
#endif
		SLNet::OP_DELETE(splitPacketChannelList[i], __FILE__, __LINE__);
	}
	splitPacketChannelList.Clear(false, _FILE_AND_LINE_);

	while ( outputQueue.Size() > 0 )
	{
		internalPacket = outputQueue.Pop();
		FreeInternalPacketData(internalPacket, _FILE_AND_LINE_ );
		ReleaseToInternalPacketPool( internalPacket );
	}

	outputQueue.ClearAndForceAllocation( 32, _FILE_AND_LINE_ );

	/*
	for ( i = 0; i < orderingList.Size(); i++ )
	{
		if ( orderingList[ i ] )
		{
			DataStructures::LinkedList<InternalPacket*>* theList = orderingList[ i ];

			if ( theList )
			{
				while ( theList->Size() )
				{
					internalPacket = orderingList[ i ]->Pop();
					FreeInternalPacketData(internalPacket, _FILE_AND_LINE_ );
					ReleaseToInternalPacketPool( internalPacket );
				}

				SLNet::OP_DELETE(theList, _FILE_AND_LINE_);
			}
		}
	}

	orderingList.Clear(false, _FILE_AND_LINE_);
	*/

	for (i=0; i < NUMBER_OF_ORDERED_STREAMS; i++)
	{
		for (j=0; j < orderingHeaps[i].Size(); j++)
		{
			FreeInternalPacketData(orderingHeaps[i][j], _FILE_AND_LINE_ );
			ReleaseToInternalPacketPool( orderingHeaps[i][j] );
		}
		orderingHeaps[i].Clear(true, _FILE_AND_LINE_);
	}

	//resendList.ForEachData(DeleteInternalPacket);
	//	resendTree.Clear(_FILE_AND_LINE_);
	memset(resendBuffer, 0, sizeof(resendBuffer));
	statistics.messagesInResendBuffer=0;
	statistics.bytesInResendBuffer=0;

	if (resendLinkedListHead)
	{
		InternalPacket *prev;
		InternalPacket *iter = resendLinkedListHead;

		for(;;)
		{
			if (iter->data)
				FreeInternalPacketData(iter, _FILE_AND_LINE_ );
			prev=iter;
			iter=iter->resendNext;
			if (iter==resendLinkedListHead)
			{
				ReleaseToInternalPacketPool(prev);
				break;
			}
			ReleaseToInternalPacketPool(prev);
		}
		resendLinkedListHead=0;
	}
	unacknowledgedBytes=0;

	//	acknowlegements.Clear(_FILE_AND_LINE_);

	for ( j=0 ; j < outgoingPacketBuffer.Size(); j++ )
	{
		if ( outgoingPacketBuffer[ j ]->data)
			FreeInternalPacketData( outgoingPacketBuffer[ j ], _FILE_AND_LINE_ );
		ReleaseToInternalPacketPool( outgoingPacketBuffer[ j ] );
	}

	outgoingPacketBuffer.Clear(true, _FILE_AND_LINE_);

#ifdef _DEBUG
	for (i = 0; i < delayList.Size(); i++ )
		SLNet::OP_DELETE(delayList[ i ], __FILE__, __LINE__);
	delayList.Clear(__FILE__, __LINE__);
#endif

    unreliableWithAckReceiptHistory.Clear(false, _FILE_AND_LINE_);

	packetsToSendThisUpdate.Clear(false, _FILE_AND_LINE_);
	packetsToSendThisUpdate.Preallocate(512, _FILE_AND_LINE_);
	packetsToDeallocThisUpdate.Clear(false, _FILE_AND_LINE_);
	packetsToDeallocThisUpdate.Preallocate(512, _FILE_AND_LINE_);
	packetsToSendThisUpdateDatagramBoundaries.Clear(false, _FILE_AND_LINE_);
	packetsToSendThisUpdateDatagramBoundaries.Preallocate(128, _FILE_AND_LINE_);
	datagramSizesInBytes.Clear(false, _FILE_AND_LINE_);
	datagramSizesInBytes.Preallocate(128, _FILE_AND_LINE_);

	internalPacketPool.Clear(_FILE_AND_LINE_);

	refCountedDataPool.Clear(_FILE_AND_LINE_);

	/*
	DataStructures::Page<DatagramSequenceNumberType, DatagramMessageIDList*, RESEND_TREE_ORDER> *cur = datagramMessageIDTree.GetListHead();
	while (cur)
	{
	int treeIndex;
	for (treeIndex=0; treeIndex < cur->size; treeIndex++)
	ReleaseToDatagramMessageIDPool(cur->data[treeIndex]);
	cur=cur->resendNext;
	}
	datagramMessageIDTree.Clear(_FILE_AND_LINE_);
	datagramMessageIDPool.Clear(_FILE_AND_LINE_);
	*/

	while (datagramHistory.Size())
	{
		RemoveFromDatagramHistory(datagramHistoryPopCount);
		datagramHistory.Pop();
		datagramHistoryPopCount++;
	}
	datagramHistoryMessagePool.Clear(_FILE_AND_LINE_);
	datagramHistoryPopCount=0;

	acknowlegements.Clear();
	NAKs.Clear();

	unreliableLinkedListHead=0;
}

//-------------------------------------------------------------------------------------------------------
// Packets are read directly from the socket layer and skip the reliability
//layer  because unconnected players do not use the reliability layer
// This function takes packet data after a player has been confirmed as
//connected.  The game should not use that data directly
// because some data is used internally, such as packet acknowledgment and
//split packets
//-------------------------------------------------------------------------------------------------------
bool ReliabilityLayer::HandleSocketReceiveFromConnectedPlayer(
	const char *buffer, unsigned int length, SystemAddress &systemAddress, DataStructures::List<PluginInterface2*> &messageHandlerList, int MTUSize,
	RakNetSocket2 *s, RakNetRandom *rnr, CCTimeType timeRead,
	BitStream &updateBitStream)
{
#ifdef _DEBUG
	RakAssert( !( buffer == 0 ) );
#endif

#if CC_TIME_TYPE_BYTES==4
	timeRead/=1000;
#endif


	bpsMetrics[(int) ACTUAL_BYTES_RECEIVED].Push1(timeRead,length);

	(void) MTUSize;

	if ( length <= 2 || buffer == 0 )   // Length of 1 is a connection request resend that we just ignore
	{
		for (unsigned int messageHandlerIndex=0; messageHandlerIndex < messageHandlerList.Size(); messageHandlerIndex++)
			messageHandlerList[messageHandlerIndex]->OnReliabilityLayerNotification("length <= 2 || buffer == 0", BYTES_TO_BITS(length), systemAddress, true);
		return true;
	}

	timeLastDatagramArrived= SLNet::GetTimeMS();

	//	CCTimeType time;
//	bool indexFound;
//	int count, size;
	DatagramSequenceNumberType holeCount;
	unsigned i;

#if LIBCAT_SECURITY==1
	if (useSecurity)
	{
		unsigned int received = length;

		if (!auth_enc.Decrypt((cat::u8*)buffer, received))
			return false;

		length = received;
	}
#endif

	SLNet::BitStream socketData( (unsigned char*) buffer, length, false ); // Convert the incoming data to a bitstream for easy parsing
	//	time = SLNet::GetTimeUS();

	// Set to the current time if it is not zero, and we get incoming data
	// 	if (timeResendQueueNonEmpty!=0)
	// 		timeResendQueueNonEmpty=timeRead;

	DatagramHeaderFormat dhf;
	dhf.Deserialize(&socketData);
	if (dhf.isValid==false)
	{
		for (unsigned int messageHandlerIndex=0; messageHandlerIndex < messageHandlerList.Size(); messageHandlerIndex++)
			messageHandlerList[messageHandlerIndex]->OnReliabilityLayerNotification("dhf.isValid==false", BYTES_TO_BITS(length), systemAddress, true);

		return true;
	}
	if (dhf.isACK)
	{
		DatagramSequenceNumberType datagramNumber;
		// datagramNumber=dhf.datagramNumber;

#if INCLUDE_TIMESTAMP_WITH_DATAGRAMS==1
		SLNet::TimeMS timeMSLow=(SLNet::TimeMS) timeRead&0xFFFFFFFF;
		CCTimeType rtt = timeMSLow-dhf.sourceSystemTime;
#if CC_TIME_TYPE_BYTES==4
		if (rtt > 10000)
#else
		if (rtt > 10000000)
#endif
		{
			// Sanity check. This could happen due to type overflow, especially since I only send the low 4 bytes to reduce bandwidth
			rtt=(CCTimeType) congestionManager.GetRTT();
		}
		//	RakAssert(rtt < 500000);
		//	printf("%i ", (SLNet::TimeMS)(rtt/1000));
		ackPing=rtt;
#endif

#ifdef _DEBUG
		if (dhf.hasBAndAS==false)
		{
			//			dhf.B=0;
			dhf.AS=0;
		}
#endif
		//		congestionManager.OnAck(timeRead, rtt, dhf.hasBAndAS, dhf.B, dhf.AS, totalUserDataBytesAcked );

		incomingAcks.Clear();
		if (!incomingAcks.Deserialize(&socketData)) {
			for (unsigned int messageHandlerIndex = 0; messageHandlerIndex < messageHandlerList.Size(); messageHandlerIndex++) {
				messageHandlerList[messageHandlerIndex]->OnReliabilityLayerNotification("incomingAcks.Deserialize failed", BYTES_TO_BITS(length), systemAddress, true);
			}

			return false;
		}

		unsigned int k = 0;
		while (k < unreliableWithAckReceiptHistory.Size()) {
			if (incomingAcks.IsWithinRange(unreliableWithAckReceiptHistory[k].datagramNumber)) {
				InternalPacket *ackReceipt = AllocateFromInternalPacketPool();
				AllocInternalPacketData(ackReceipt, 5, false, _FILE_AND_LINE_);
				ackReceipt->dataBitLength = BYTES_TO_BITS(5);
				ackReceipt->data[0] = (MessageID)ID_SND_RECEIPT_ACKED;
				memcpy(ackReceipt->data + sizeof(MessageID), &unreliableWithAckReceiptHistory[k].sendReceiptSerial, sizeof(uint32_t));
				outputQueue.Push(ackReceipt, _FILE_AND_LINE_);

				// Remove, swap with last
				unreliableWithAckReceiptHistory.RemoveAtIndex(k);
			} else {
				k++;
			}
		}

		// early out, if we've got no outstanding datagramHistory entries
		if (datagramHistory.IsEmpty()) {
			receivePacketCount++;
			return true;
		}

		for (i = 0; i < incomingAcks.ranges.Size(); i++) {
			// note: minIndex is ensured to be always <= maxIndex - otherwise Deserialize() would have failed
			RakAssert(incomingAcks.ranges[i].minIndex <= incomingAcks.ranges[i].maxIndex);

			if (incomingAcks.ranges[i].maxIndex == (uint24_t)(0xFFFFFFFF)) {
				for (unsigned int messageHandlerIndex = 0; messageHandlerIndex < messageHandlerList.Size(); messageHandlerIndex++) {
					messageHandlerList[messageHandlerIndex]->OnReliabilityLayerNotification("incomingAcks maxIndex is max value", BYTES_TO_BITS(length), systemAddress, true);
				}

				// it's an invalid incoming package --- let's abort processing (there's no point in continuing processing other ranges if the package is invalid)
				return false;
			}

			for (datagramNumber = incomingAcks.ranges[i].minIndex; datagramNumber <= incomingAcks.ranges[i].maxIndex; datagramNumber++) {
				const DatagramSequenceNumberType offsetIntoList = datagramNumber - datagramHistoryPopCount;
				if (offsetIntoList >= datagramHistory.Size()) {
					// reached the end of the datagramHistory list - hence, we are done
					receivePacketCount++;
					return true;
				}

				CCTimeType whenSent;
				MessageNumberNode *messageNumberNode = GetMessageNumberNodeByDatagramIndex(datagramNumber, &whenSent);
				if (messageNumberNode) {
				//	printf("%p Got ack for %i\n", this, datagramNumber.val);
#if INCLUDE_TIMESTAMP_WITH_DATAGRAMS==1
					congestionManager.OnAck(timeRead, rtt, dhf.hasBAndAS, 0, dhf.AS, totalUserDataBytesAcked, bandwidthExceededStatistic, datagramNumber);
#else
					CCTimeType ping;
					if (timeRead > whenSent) {
						ping = timeRead - whenSent;
					} else {
						ping = 0;
					}
					congestionManager.OnAck(timeRead, ping, dhf.hasBAndAS, 0, dhf.AS, totalUserDataBytesAcked, bandwidthExceededStatistic, datagramNumber);
#endif
					while (messageNumberNode) {
						// TESTING1
// 						printf("Remove %i on ack for datagramNumber=%i.\n", messageNumberNode->messageNumber.val, datagramNumber.val);

						RemovePacketFromResendListAndDeleteOlderReliableSequenced(messageNumberNode->messageNumber, timeRead, messageHandlerList, systemAddress);
						messageNumberNode = messageNumberNode->next;
					}

					RemoveFromDatagramHistory(datagramNumber);
				}
// 				else if (isReliable) {
// 					// Previously used slot, rather than empty unreliable slot
// 					printf("%p Ack %i is duplicate\n", this, datagramNumber.val);
// 
//  				congestionManager.OnDuplicateAck(timeRead, datagramNumber);
// 				}
			}
		}
	} else if (dhf.isNAK) {
		// early out, if we've got no outstanding datagramHistory entries
		if (datagramHistory.IsEmpty()) {
			receivePacketCount++;
			return true;
		}

		DatagramSequenceNumberType messageNumber;
		DataStructures::RangeList<DatagramSequenceNumberType> incomingNAKs;
		if (!incomingNAKs.Deserialize(&socketData)) {
			for (unsigned int messageHandlerIndex = 0; messageHandlerIndex < messageHandlerList.Size(); messageHandlerIndex++) {
				messageHandlerList[messageHandlerIndex]->OnReliabilityLayerNotification("incomingNAKs.Deserialize failed", BYTES_TO_BITS(length), systemAddress, true);
			}

			// it's an invalid incoming package --- let's abort processing (there's no point in continuing processing other ranges if the package is invalid)
			return false;
		}
		for (i = 0; i < incomingNAKs.ranges.Size(); i++) {
			// note: minIndex is ensured to be always <= maxIndex - otherwise Deserialize() would have failed
			RakAssert(incomingNAKs.ranges[i].minIndex <= incomingNAKs.ranges[i].maxIndex);

			if (incomingNAKs.ranges[i].maxIndex == (uint24_t)(0xFFFFFFFF)) {
				for (unsigned int messageHandlerIndex = 0; messageHandlerIndex < messageHandlerList.Size(); messageHandlerIndex++) {
					messageHandlerList[messageHandlerIndex]->OnReliabilityLayerNotification("incomingNAKs maxIndex is max value", BYTES_TO_BITS(length), systemAddress, true);
				}

				return false;
			}
			// Sanity check
			//RakAssert(incomingNAKs.ranges[i].maxIndex.val-incomingNAKs.ranges[i].minIndex.val<1000);
			for (messageNumber = incomingNAKs.ranges[i].minIndex; messageNumber <= incomingNAKs.ranges[i].maxIndex; messageNumber++) {
				congestionManager.OnNAK(timeRead, messageNumber);

				// REMOVEME
				//				printf("%p NAK %i\n", this, dhf.datagramNumber.val);

				const DatagramSequenceNumberType offsetIntoList = messageNumber - datagramHistoryPopCount;
				if (offsetIntoList >= datagramHistory.Size()) {
					// reached the end of the datagramHistory list - hence, we are done
					receivePacketCount++;
					return true;
				}

				CCTimeType timeSent;
				MessageNumberNode *messageNumberNode = GetMessageNumberNodeByDatagramIndex(messageNumber, &timeSent);
				while (messageNumberNode) {
					// Update timers so resends occur immediately
					InternalPacket *internalPacket = resendBuffer[messageNumberNode->messageNumber & (uint32_t) RESEND_BUFFER_ARRAY_MASK];
					if (internalPacket) {
						if (internalPacket->nextActionTime != 0) {
							internalPacket->nextActionTime = timeRead;
						}
					}				

					messageNumberNode = messageNumberNode->next;
				}
			}
		}
	} else {
		uint32_t skippedMessageCount;
		if (!congestionManager.OnGotPacket(dhf.datagramNumber, dhf.isContinuousSend, timeRead, length, &skippedMessageCount)) {
			for (unsigned int messageHandlerIndex = 0; messageHandlerIndex < messageHandlerList.Size(); messageHandlerIndex++) {
				messageHandlerList[messageHandlerIndex]->OnReliabilityLayerNotification("congestionManager.OnGotPacket failed", BYTES_TO_BITS(length), systemAddress, true);
			}

			return true;
		}
		if (dhf.isPacketPair) {
			congestionManager.OnGotPacketPair(dhf.datagramNumber, length, timeRead);
		}

		DatagramHeaderFormat dhfNAK;
		dhfNAK.isNAK = true;
		uint32_t skippedMessageOffset;
		for (skippedMessageOffset = skippedMessageCount; skippedMessageOffset > 0; skippedMessageOffset--) {
			NAKs.Insert(dhf.datagramNumber - skippedMessageOffset);
		}
		remoteSystemNeedsBAndAS = dhf.needsBAndAs;

		// Ack dhf.datagramNumber
		// Ack even unreliable messages for congestion control, just don't resend them on no ack
#if INCLUDE_TIMESTAMP_WITH_DATAGRAMS==1
		SendAcknowledgementPacket(dhf.datagramNumber, dhf.sourceSystemTime);
#else
		SendAcknowledgementPacket(dhf.datagramNumber, 0);
#endif

		InternalPacket* internalPacket = CreateInternalPacketFromBitStream(&socketData, timeRead);
		if (internalPacket == 0) {
			for (unsigned int messageHandlerIndex = 0; messageHandlerIndex < messageHandlerList.Size(); messageHandlerIndex++) {
				messageHandlerList[messageHandlerIndex]->OnReliabilityLayerNotification("CreateInternalPacketFromBitStream failed", BYTES_TO_BITS(length), systemAddress, true);
			}

			return true;
		}

		while (internalPacket) {
			for (unsigned int messageHandlerIndex=0; messageHandlerIndex < messageHandlerList.Size(); messageHandlerIndex++) {
#if CC_TIME_TYPE_BYTES==4
				messageHandlerList[messageHandlerIndex]->OnInternalPacket(internalPacket, receivePacketCount, systemAddress, timeRead, false);
#else
				messageHandlerList[messageHandlerIndex]->OnInternalPacket(internalPacket, receivePacketCount, systemAddress, (SLNet::TimeMS)(timeRead/(CCTimeType)1000), false);
#endif
			}

			{

				// resetReceivedPackets is set from a non-threadsafe function.
				// We do the actual reset in this function so the data is not modified by multiple threads
				if (resetReceivedPackets) {
					hasReceivedPacketQueue.ClearAndForceAllocation(DEFAULT_HAS_RECEIVED_PACKET_QUEUE_SIZE, _FILE_AND_LINE_);
					receivedPacketsBaseIndex=0;
					resetReceivedPackets=false;
				}

				// Check for corrupt orderingChannel
				if ( 
					internalPacket->reliability == RELIABLE_SEQUENCED ||
					internalPacket->reliability == UNRELIABLE_SEQUENCED ||
					internalPacket->reliability == RELIABLE_ORDERED
					)
				{
					if (internalPacket->orderingChannel >= NUMBER_OF_ORDERED_STREAMS) {
						for (unsigned int messageHandlerIndex = 0; messageHandlerIndex < messageHandlerList.Size(); messageHandlerIndex++) {
							messageHandlerList[messageHandlerIndex]->OnReliabilityLayerNotification("internalPacket->orderingChannel >= NUMBER_OF_ORDERED_STREAMS", BYTES_TO_BITS(length), systemAddress, true);
						}

						bpsMetrics[(int) USER_MESSAGE_BYTES_RECEIVED_IGNORED].Push1(timeRead,BITS_TO_BYTES(internalPacket->dataBitLength));

						FreeInternalPacketData(internalPacket, _FILE_AND_LINE_);
						ReleaseToInternalPacketPool(internalPacket);
						goto CONTINUE_SOCKET_DATA_PARSE_LOOP;
					}
				}

				// 8/12/09 was previously not checking if the message was reliable. However, on packetloss this would mean you'd eventually exceed the
				// hole count because unreliable messages were never resent, and you'd stop getting messages
				if (internalPacket->reliability == RELIABLE || internalPacket->reliability == RELIABLE_SEQUENCED || internalPacket->reliability == RELIABLE_ORDERED) {
					// If the following conditional is true then this either a duplicate packet
					// or an older out of order packet
					// The subtraction unsigned overflow is intentional
					holeCount = (DatagramSequenceNumberType)(internalPacket->reliableMessageNumber - receivedPacketsBaseIndex);
					const DatagramSequenceNumberType typeRange = (DatagramSequenceNumberType)(const uint32_t)-1;

					// TESTING1
// 					printf("waiting on reliableMessageNumber=%i holeCount=%i datagramNumber=%i\n", receivedPacketsBaseIndex.val, holeCount.val, dhf.datagramNumber.val);

					if (holeCount == (DatagramSequenceNumberType)0) {
						// Got what we were expecting
						if (hasReceivedPacketQueue.Size())
							hasReceivedPacketQueue.Pop();
						++receivedPacketsBaseIndex;
					} else if (holeCount > typeRange/(DatagramSequenceNumberType) 2) {
						bpsMetrics[(int) USER_MESSAGE_BYTES_RECEIVED_IGNORED].Push1(timeRead,BITS_TO_BYTES(internalPacket->dataBitLength));

						for (unsigned int messageHandlerIndex = 0; messageHandlerIndex < messageHandlerList.Size(); messageHandlerIndex++) {
							messageHandlerList[messageHandlerIndex]->OnReliabilityLayerNotification("holeCount > typeRange/(DatagramSequenceNumberType) 2", BYTES_TO_BITS(length), systemAddress, false);
						}

						// Duplicate packet
						FreeInternalPacketData(internalPacket, _FILE_AND_LINE_);
						ReleaseToInternalPacketPool(internalPacket);

						goto CONTINUE_SOCKET_DATA_PARSE_LOOP;
					} else if ((unsigned int)holeCount < hasReceivedPacketQueue.Size()) {
						// Got a higher count out of order packet that was missing in the sequence or we already got
						if (hasReceivedPacketQueue[holeCount] != false) { // non-zero means this is a hole
#ifdef LOG_TRIVIAL_NOTIFICATIONS
							for (unsigned int messageHandlerIndex = 0; messageHandlerIndex < messageHandlerList.Size(); messageHandlerIndex++) {
								messageHandlerList[messageHandlerIndex]->OnReliabilityLayerNotification("Higher count pushed to hasReceivedPacketQueue", BYTES_TO_BITS(length), systemAddress, false);
							}
#endif

							// Fill in the hole
							hasReceivedPacketQueue[holeCount] = false; // We got the packet at holeCount
						} else {
							bpsMetrics[(int)USER_MESSAGE_BYTES_RECEIVED_IGNORED].Push1(timeRead,BITS_TO_BYTES(internalPacket->dataBitLength));

#ifdef LOG_TRIVIAL_NOTIFICATIONS
							for (unsigned int messageHandlerIndex = 0; messageHandlerIndex < messageHandlerList.Size(); messageHandlerIndex++) {
								messageHandlerList[messageHandlerIndex]->OnReliabilityLayerNotification("Duplicate packet ignored", BYTES_TO_BITS(length), systemAddress, false);
							}
#endif

							// Duplicate packet
							FreeInternalPacketData(internalPacket, _FILE_AND_LINE_);
							ReleaseToInternalPacketPool(internalPacket);

							goto CONTINUE_SOCKET_DATA_PARSE_LOOP;
						}
					} else { // holeCount>=receivedPackets.Size()
						if (holeCount > (DatagramSequenceNumberType)1000000) {
							RakAssert("Hole count too high. See ReliabilityLayer.h" && 0);

							for (unsigned int messageHandlerIndex = 0; messageHandlerIndex < messageHandlerList.Size(); messageHandlerIndex++) {
								messageHandlerList[messageHandlerIndex]->OnReliabilityLayerNotification("holeCount > 1000000", BYTES_TO_BITS(length), systemAddress, true);
							}

							bpsMetrics[(int)USER_MESSAGE_BYTES_RECEIVED_IGNORED].Push1(timeRead, BITS_TO_BYTES(internalPacket->dataBitLength));

							// Would crash due to out of memory!
							FreeInternalPacketData(internalPacket, _FILE_AND_LINE_);
							ReleaseToInternalPacketPool(internalPacket);

							goto CONTINUE_SOCKET_DATA_PARSE_LOOP;
						}

#ifdef LOG_TRIVIAL_NOTIFICATIONS
						for (unsigned int messageHandlerIndex = 0; messageHandlerIndex < messageHandlerList.Size(); messageHandlerIndex++) {
							messageHandlerList[messageHandlerIndex]->OnReliabilityLayerNotification("Adding to hasReceivedPacketQueue later ordered message", BYTES_TO_BITS(length), systemAddress, false);
						}
#endif

						// Fix - sending on a higher priority gives us a very very high received packets base index if we formerly had pre-split a lot of messages and
						// used that as the message number.  Because of this, a lot of time is spent in this linear loop and the timeout time expires because not
						// all of the message is sent in time.
						// Fixed by late assigning message IDs on the sender

						// Add 0 times to the queue until (reliableMessageNumber - baseIndex) < queue size.
						while ((unsigned int)(holeCount) > hasReceivedPacketQueue.Size()) {
							hasReceivedPacketQueue.Push(true, _FILE_AND_LINE_); // time+(CCTimeType)60 * (CCTimeType)1000 * (CCTimeType)1000); // Didn't get this packet - set the time to give up waiting
						}
						hasReceivedPacketQueue.Push(false, _FILE_AND_LINE_ ); // Got the packet
#ifdef _DEBUG
						// If this assert hits then DatagramSequenceNumberType has overflowed
						RakAssert(hasReceivedPacketQueue.Size() < (unsigned int)((DatagramSequenceNumberType)(const uint32_t)(-1)));
#endif
					}

					while (hasReceivedPacketQueue.Size() > 0 && !hasReceivedPacketQueue.Peek()) {
						hasReceivedPacketQueue.Pop();
						++receivedPacketsBaseIndex;
					}
				}

				// If the allocated buffer is > DEFAULT_HAS_RECEIVED_PACKET_QUEUE_SIZE and it is 3x greater than the number of elements actually being used
				if (hasReceivedPacketQueue.AllocationSize() > (unsigned int)DEFAULT_HAS_RECEIVED_PACKET_QUEUE_SIZE && hasReceivedPacketQueue.AllocationSize() > hasReceivedPacketQueue.Size() * 3) {
					hasReceivedPacketQueue.Compress(_FILE_AND_LINE_);
				}


				/*
				if (internalPacket->reliability == RELIABLE_SEQUENCED || internalPacket->reliability == UNRELIABLE_SEQUENCED) {
#ifdef _DEBUG
					RakAssert(internalPacket->orderingChannel < NUMBER_OF_ORDERED_STREAMS);
#endif

					if (internalPacket->orderingChannel >= NUMBER_OF_ORDERED_STREAMS) {
						FreeInternalPacketData(internalPacket, _FILE_AND_LINE_);
						ReleaseToInternalPacketPool(internalPacket);

						for (unsigned int messageHandlerIndex = 0; messageHandlerIndex < messageHandlerList.Size(); messageHandlerIndex++) {
							messageHandlerList[messageHandlerIndex]->OnReliabilityLayerNotification("internalPacket->orderingChannel >= NUMBER_OF_ORDERED_STREAMS", BYTES_TO_BITS(length), systemAddress);
						}

						bpsMetrics[(int) USER_MESSAGE_BYTES_RECEIVED_IGNORED].Push1(timeRead,BITS_TO_BYTES(internalPacket->dataBitLength));

						goto CONTINUE_SOCKET_DATA_PARSE_LOOP;
					}

					if (!IsOlderOrderedPacket(internalPacket->orderingIndex, waitingForSequencedPacketReadIndex[internalPacket->orderingChannel])) {
						// Is this a split packet?
						if (internalPacket->splitPacketCount > 0) {
							// Generate the split
							// Verify some parameters to make sure we don't get junk data


							// Check for a rebuilt packet
							InsertIntoSplitPacketList(internalPacket, timeRead);
							bpsMetrics[(int) USER_MESSAGE_BYTES_RECEIVED_PROCESSED].Push1(timeRead,BITS_TO_BYTES(internalPacket->dataBitLength));

							// Sequenced
							internalPacket = BuildPacketFromSplitPacketList( internalPacket->splitPacketId, timeRead,
								s, systemAddress, rnr, remotePortRakNetWasStartedOn_PS3, extraSocketOptions);

							if (internalPacket) {
								// Update our index to the newest packet
								waitingForSequencedPacketReadIndex[ internalPacket->orderingChannel ] = internalPacket->orderingIndex + (OrderingIndexType)1;

								// If there is a rebuilt packet, add it to the output queue
								outputQueue.Push(internalPacket, _FILE_AND_LINE_);
								internalPacket = 0;
							}

							// else don't have all the parts yet
						} else {
							// Update our index to the newest packet
							waitingForSequencedPacketReadIndex[ internalPacket->orderingChannel ] = internalPacket->orderingIndex + (OrderingIndexType)1;

							// Not a split packet. Add the packet to the output queue
							bpsMetrics[(int) USER_MESSAGE_BYTES_RECEIVED_PROCESSED].Push1(timeRead,BITS_TO_BYTES(internalPacket->dataBitLength));
							outputQueue.Push( internalPacket, _FILE_AND_LINE_  );
							internalPacket = 0;
						}
					} else {
						// Older sequenced packet. Discard it
						FreeInternalPacketData(internalPacket, _FILE_AND_LINE_ );
						ReleaseToInternalPacketPool( internalPacket );

						bpsMetrics[(int) USER_MESSAGE_BYTES_RECEIVED_IGNORED].Push1(timeRead,BITS_TO_BYTES(internalPacket->dataBitLength));
					}

					goto CONTINUE_SOCKET_DATA_PARSE_LOOP;
				}

				// Is this an unsequenced split packet?
				if ( internalPacket->splitPacketCount > 0 )
				{
					// Check for a rebuilt packet
					if ( internalPacket->reliability != RELIABLE_ORDERED )
						internalPacket->orderingChannel = 255; // Use 255 to designate not sequenced and not ordered

					InsertIntoSplitPacketList( internalPacket, timeRead );

					internalPacket = BuildPacketFromSplitPacketList( internalPacket->splitPacketId, timeRead,
						s, systemAddress, rnr, remotePortRakNetWasStartedOn_PS3, extraSocketOptions);

					if ( internalPacket == 0 )
					{

						// Don't have all the parts yet
						goto CONTINUE_SOCKET_DATA_PARSE_LOOP;
					}
				}
				*/

				/*
				if ( internalPacket->reliability == RELIABLE_ORDERED )
				{
#ifdef _DEBUG
					RakAssert( internalPacket->orderingChannel < NUMBER_OF_ORDERED_STREAMS );
#endif

					if ( internalPacket->orderingChannel >= NUMBER_OF_ORDERED_STREAMS )
					{
						// Invalid packet
						FreeInternalPacketData(internalPacket, _FILE_AND_LINE_ );
						ReleaseToInternalPacketPool( internalPacket );

						bpsMetrics[(int) USER_MESSAGE_BYTES_RECEIVED_IGNORED].Push1(timeRead,BITS_TO_BYTES(internalPacket->dataBitLength));

						goto CONTINUE_SOCKET_DATA_PARSE_LOOP;
					}

					bpsMetrics[(int) USER_MESSAGE_BYTES_RECEIVED_PROCESSED].Push1(timeRead,BITS_TO_BYTES(internalPacket->dataBitLength));

					if ( waitingForOrderedPacketReadIndex[ internalPacket->orderingChannel ] == internalPacket->orderingIndex )
					{
						// Get the list to hold ordered packets for this stream
						DataStructures::LinkedList<InternalPacket*> *orderingListAtOrderingStream;
						unsigned char orderingChannelCopy = internalPacket->orderingChannel;

						// Push the packet for the user to read
						outputQueue.Push( internalPacket, _FILE_AND_LINE_  );
						internalPacket = 0; // Don't reference this any longer since other threads access it

						// Wait for the resendNext ordered packet in sequence
						waitingForOrderedPacketReadIndex[ orderingChannelCopy ] ++; // This wraps

						orderingListAtOrderingStream = GetOrderingListAtOrderingStream( orderingChannelCopy );

						if ( orderingListAtOrderingStream != 0)
						{
							while ( orderingListAtOrderingStream->Size() > 0 )
							{
								// Cycle through the list until nothing is found
								orderingListAtOrderingStream->Beginning();
								indexFound=false;
								size=orderingListAtOrderingStream->Size();
								count=0;

								while (count++ < size)
								{
									if ( orderingListAtOrderingStream->Peek()->orderingIndex == waitingForOrderedPacketReadIndex[ orderingChannelCopy ] )
									{
										outputQueue.Push( orderingListAtOrderingStream->Pop(), _FILE_AND_LINE_  );
										waitingForOrderedPacketReadIndex[ orderingChannelCopy ]++;
										indexFound=true;
									}
									else
										(*orderingListAtOrderingStream)++;
								}

								if (indexFound==false)
									break;
							}
						}
						internalPacket = 0;
					}
					else
					{
						// This is a newer ordered packet than we are waiting for. Store it for future use
						AddToOrderingList( internalPacket );
					}


					goto CONTINUE_SOCKET_DATA_PARSE_LOOP;
				}
				*/

				// Is this a split packet? If so then reassemble
				if ( internalPacket->splitPacketCount > 0 )
				{
					// Check for a rebuilt packet
					if ( internalPacket->reliability != RELIABLE_ORDERED && internalPacket->reliability!=RELIABLE_SEQUENCED && internalPacket->reliability!=UNRELIABLE_SEQUENCED)
						internalPacket->orderingChannel = 255; // Use 255 to designate not sequenced and not ordered

					InsertIntoSplitPacketList( internalPacket, timeRead );

					internalPacket = BuildPacketFromSplitPacketList( internalPacket->splitPacketId, timeRead,
						s, systemAddress, rnr, updateBitStream);

					if ( internalPacket == 0 )
					{
#ifdef LOG_TRIVIAL_NOTIFICATIONS
						for (unsigned int messageHandlerIndex=0; messageHandlerIndex < messageHandlerList.Size(); messageHandlerIndex++)
							messageHandlerList[messageHandlerIndex]->OnReliabilityLayerNotification("BuildPacketFromSplitPacketList did not return anything.", BYTES_TO_BITS(length), systemAddress, false);
#endif

						// Don't have all the parts yet
						goto CONTINUE_SOCKET_DATA_PARSE_LOOP;
					}
				}

#ifdef PRINT_TO_FILE_RELIABLE_ORDERED_TEST
				unsigned char packetId;
				char *type="UNDEFINED";
#endif
				if (internalPacket->reliability == RELIABLE_SEQUENCED ||
					internalPacket->reliability == UNRELIABLE_SEQUENCED ||
					internalPacket->reliability == RELIABLE_ORDERED)
				{
#ifdef PRINT_TO_FILE_RELIABLE_ORDERED_TEST

					// ___________________
					BitStream bitStream(internalPacket->data, BITS_TO_BYTES(internalPacket->dataBitLength), false);
					unsigned int receivedPacketNumber;
					SLNet::Time receivedTime;
					unsigned char streamNumber;
					PacketReliability reliability;
					// ___________________


					bitStream.IgnoreBits(8); // Ignore ID_TIMESTAMP
					bitStream.Read(receivedTime);
					bitStream.Read(packetId);
					bitStream.Read(receivedPacketNumber);
					bitStream.Read(streamNumber);
					bitStream.Read(reliability);
					if (packetId==ID_USER_PACKET_ENUM+1)
					{

						if (reliability==UNRELIABLE_SEQUENCED)
							type="UNRELIABLE_SEQUENCED";
						else if (reliability==RELIABLE_ORDERED)
							type="RELIABLE_ORDERED";
						else
							type="RELIABLE_SEQUENCED";
					}
					// ___________________
#endif


					if (internalPacket->orderingIndex==orderedReadIndex[internalPacket->orderingChannel])
					{
						// Has current ordering index
						if (internalPacket->reliability == RELIABLE_SEQUENCED ||
							internalPacket->reliability == UNRELIABLE_SEQUENCED)
						{
							// Is sequenced
							if (IsOlderOrderedPacket(internalPacket->sequencingIndex,highestSequencedReadIndex[internalPacket->orderingChannel])==false)
							{
								// Expected or highest known value

#ifdef PRINT_TO_FILE_RELIABLE_ORDERED_TEST
								if (packetId==ID_USER_PACKET_ENUM+1 && fp)
								{
									fprintf(fp, "Returning %i, %s by fallthrough. OI=%i. SI=%i.\n", receivedPacketNumber, type, internalPacket->orderingIndex.val, internalPacket->sequencingIndex);
									fflush(fp);
								}

								if (packetId==ID_USER_PACKET_ENUM+1)
								{
									if (receivedPacketNumber<packetNumber)
									{
										if (fp)
										{
											fprintf(fp, "Out of order packet from fallthrough! Expecting %i got %i\n", receivedPacketNumber, packetNumber);
											fflush(fp);
										}
									}
									packetNumber=receivedPacketNumber+1;
								}
#endif
								// Update highest sequence
								// 6/26/2012 - Did not have the +1 in the next statement
								// Means a duplicated RELIABLE_SEQUENCED or UNRELIABLE_SEQUENCED packet would be returned to the user
								highestSequencedReadIndex[internalPacket->orderingChannel] = internalPacket->sequencingIndex+(OrderingIndexType)1;

								// Fallthrough, returned to user below
							}
							else
							{
#ifdef PRINT_TO_FILE_RELIABLE_ORDERED_TEST
								if (packetId==ID_USER_PACKET_ENUM+1 && fp)
								{
								fprintf(fp, "Discarding %i, %s late sequenced. OI=%i. SI=%i.\n", receivedPacketNumber, type, internalPacket->orderingIndex.val, internalPacket->sequencingIndex);
								fflush(fp);
								}
#endif

#ifdef LOG_TRIVIAL_NOTIFICATIONS
								for (unsigned int messageHandlerIndex=0; messageHandlerIndex < messageHandlerList.Size(); messageHandlerIndex++)
									messageHandlerList[messageHandlerIndex]->OnReliabilityLayerNotification("Sequenced rejected: lower than highest known value", BYTES_TO_BITS(length), systemAddress, false);
#endif

								// Lower than highest known value
								FreeInternalPacketData(internalPacket, _FILE_AND_LINE_ );
								ReleaseToInternalPacketPool( internalPacket );

								goto CONTINUE_SOCKET_DATA_PARSE_LOOP;
							}
						}
						else
						{
							// Push to output buffer immediately
							bpsMetrics[(int) USER_MESSAGE_BYTES_RECEIVED_PROCESSED].Push1(timeRead,BITS_TO_BYTES(internalPacket->dataBitLength));
							outputQueue.Push( internalPacket, _FILE_AND_LINE_  );

#ifdef PRINT_TO_FILE_RELIABLE_ORDERED_TEST
							if (packetId==ID_USER_PACKET_ENUM+1 && fp)
							{
								fprintf(fp, "outputting immediate %i, %s. OI=%i. SI=%i.", receivedPacketNumber, type, internalPacket->orderingIndex.val, internalPacket->sequencingIndex);
								if (orderingHeaps[internalPacket->orderingChannel].Size()==0)
									fprintf(fp, "heap empty\n");
								else
									fprintf(fp, "heap head=%i\n", orderingHeaps[internalPacket->orderingChannel].Peek()->orderingIndex.val);

								if (receivedPacketNumber<packetNumber)
								{
									if (packetId==ID_USER_PACKET_ENUM+1 && fp)
									{
										fprintf(fp, "Out of order packet arrived! Expecting %i got %i\n", receivedPacketNumber, packetNumber);
										fflush(fp);
									}
								}
								packetNumber=receivedPacketNumber+1;

								fflush(fp);
							}
#endif

							orderedReadIndex[internalPacket->orderingChannel]++;
							highestSequencedReadIndex[internalPacket->orderingChannel] = 0;

							// Return off heap until order lost
							while (orderingHeaps[internalPacket->orderingChannel].Size()>0 &&
								orderingHeaps[internalPacket->orderingChannel].Peek()->orderingIndex==orderedReadIndex[internalPacket->orderingChannel])
							{
								internalPacket = orderingHeaps[internalPacket->orderingChannel].Pop(0);

#ifdef PRINT_TO_FILE_RELIABLE_ORDERED_TEST
								BitStream bitStream2(internalPacket->data, BITS_TO_BYTES(internalPacket->dataBitLength), false);
								bitStream2.IgnoreBits(8); // Ignore ID_TIMESTAMP
								bitStream2.Read(receivedTime);
								bitStream2.IgnoreBits(8); // Ignore ID_USER_ENUM+1
								bitStream2.Read(receivedPacketNumber);
								bitStream2.Read(streamNumber);
								bitStream2.Read(reliability);
								char *type="UNDEFINED";
								if (reliability==UNRELIABLE_SEQUENCED)
									type="UNRELIABLE_SEQUENCED";
								else if (reliability==RELIABLE_ORDERED)
									type="RELIABLE_ORDERED";

								if (packetId==ID_USER_PACKET_ENUM+1 && fp)
								{
									fprintf(fp, "Heap pop %i, %s. OI=%i. SI=%i.\n", receivedPacketNumber, type, internalPacket->orderingIndex.val, internalPacket->sequencingIndex);
									fflush(fp);

									if (receivedPacketNumber<packetNumber)
									{
										if (packetId==ID_USER_PACKET_ENUM+1 && fp)
										{
											fprintf(fp, "Out of order packet from heap! Expecting %i got %i\n", receivedPacketNumber, packetNumber);
											fflush(fp);
										}
									}
									packetNumber=receivedPacketNumber+1;
								}
#endif

								bpsMetrics[(int) USER_MESSAGE_BYTES_RECEIVED_PROCESSED].Push1(timeRead,BITS_TO_BYTES(internalPacket->dataBitLength));
								outputQueue.Push( internalPacket, _FILE_AND_LINE_  );

								if (internalPacket->reliability == RELIABLE_ORDERED)
								{
									orderedReadIndex[internalPacket->orderingChannel]++;
								}
								else
								{
									highestSequencedReadIndex[internalPacket->orderingChannel] = internalPacket->sequencingIndex;
								}
							}

							// Done
							goto CONTINUE_SOCKET_DATA_PARSE_LOOP;
						}
					}
					else if (IsOlderOrderedPacket(internalPacket->orderingIndex,orderedReadIndex[internalPacket->orderingChannel])==false)
					{
						// internalPacket->_orderingIndex is greater
						// If a message has a greater ordering index, and is sequenced or ordered, buffer it
						// Sequenced has a lower heap weight, ordered has max sequenced weight

						// Keep orderedHoleCount count small
						if (orderingHeaps[internalPacket->orderingChannel].Size()==0)
							heapIndexOffsets[internalPacket->orderingChannel]=orderedReadIndex[internalPacket->orderingChannel];

						reliabilityHeapWeightType orderedHoleCount = internalPacket->orderingIndex-heapIndexOffsets[internalPacket->orderingChannel];
						reliabilityHeapWeightType weight = orderedHoleCount*1048576;
						if (internalPacket->reliability == RELIABLE_SEQUENCED ||
							internalPacket->reliability == UNRELIABLE_SEQUENCED)
							weight+=internalPacket->sequencingIndex;
						else
							weight+=(1048576-1);
						orderingHeaps[internalPacket->orderingChannel].Push(weight, internalPacket, _FILE_AND_LINE_);

#ifdef PRINT_TO_FILE_RELIABLE_ORDERED_TEST
						if (packetId==ID_USER_PACKET_ENUM+1 && fp)
						{
						fprintf(fp, "Heap push %i, %s, weight=%" PRINTF_64_BIT_MODIFIER "u. OI=%i. waiting on %i. SI=%i.\n", receivedPacketNumber, type, weight, internalPacket->orderingIndex.val, orderedReadIndex[internalPacket->orderingChannel].val, internalPacket->sequencingIndex);
						fflush(fp);
						}
#endif

#ifdef LOG_TRIVIAL_NOTIFICATIONS
						for (unsigned int messageHandlerIndex=0; messageHandlerIndex < messageHandlerList.Size(); messageHandlerIndex++)
							messageHandlerList[messageHandlerIndex]->OnReliabilityLayerNotification("Larger number ordered packet leaving holes", BYTES_TO_BITS(length), systemAddress, false);
#endif

						// Buffered, nothing to do
						goto CONTINUE_SOCKET_DATA_PARSE_LOOP;
					}
					else
					{
						// Out of order
						FreeInternalPacketData(internalPacket, _FILE_AND_LINE_ );
						ReleaseToInternalPacketPool( internalPacket );

#ifdef LOG_TRIVIAL_NOTIFICATIONS
						for (unsigned int messageHandlerIndex=0; messageHandlerIndex < messageHandlerList.Size(); messageHandlerIndex++)
							messageHandlerList[messageHandlerIndex]->OnReliabilityLayerNotification("Rejected older resend", BYTES_TO_BITS(length), systemAddress, false);
#endif

						// Ignored, nothing to do
						goto CONTINUE_SOCKET_DATA_PARSE_LOOP;
					}
					
				}

				bpsMetrics[(int) USER_MESSAGE_BYTES_RECEIVED_PROCESSED].Push1(timeRead,BITS_TO_BYTES(internalPacket->dataBitLength));

				// Nothing special about this packet.  Add it to the output queue
				outputQueue.Push( internalPacket, _FILE_AND_LINE_  );

				internalPacket = 0;
			}

			// Used for a goto to jump to the resendNext packet immediately

CONTINUE_SOCKET_DATA_PARSE_LOOP:
			// Parse the bitstream to create an internal packet
			internalPacket = CreateInternalPacketFromBitStream( &socketData, timeRead );
		}

	}

	// #med - review --- is this correct to not increase in error cases?
	receivePacketCount++;

	return true;
}

//-------------------------------------------------------------------------------------------------------
// This gets an end-user packet already parsed out. Returns number of BITS put into the buffer
//-------------------------------------------------------------------------------------------------------
BitSize_t ReliabilityLayer::Receive( unsigned char **data )
{
	InternalPacket * internalPacket;

	if ( outputQueue.Size() > 0 )
	{
		//  #ifdef _DEBUG
		//  RakAssert(bitStream->GetNumberOfBitsUsed()==0);
		//  #endif
		internalPacket = outputQueue.Pop();

		BitSize_t bitLength;
		*data = internalPacket->data;
		bitLength = internalPacket->dataBitLength;
		ReleaseToInternalPacketPool( internalPacket );
		return bitLength;
	}

	else
	{
		return 0;
	}

}

//-------------------------------------------------------------------------------------------------------
// Puts data on the send queue
// bitStream contains the data to send
// priority is what priority to send the data at
// reliability is what reliability to use
// ordering channel is from 0 to 255 and specifies what stream to use
//-------------------------------------------------------------------------------------------------------
bool ReliabilityLayer::Send( char *data, BitSize_t numberOfBitsToSend, PacketPriority priority, PacketReliability reliability, unsigned char orderingChannel, bool makeDataCopy, int MTUSize, CCTimeType currentTime, uint32_t receipt )
{
#ifdef _DEBUG
	RakAssert( !( reliability >= NUMBER_OF_RELIABILITIES || reliability < 0 ) );
	RakAssert( !( priority > NUMBER_OF_PRIORITIES || priority < 0 ) );
	RakAssert( !( orderingChannel >= NUMBER_OF_ORDERED_STREAMS ) );
	RakAssert( numberOfBitsToSend > 0 );
#endif

#if CC_TIME_TYPE_BYTES==4
	currentTime/=1000;
#endif

	(void) MTUSize;

	//	int a = BITS_TO_BYTES(numberOfBitsToSend);

	// Fix any bad parameters
	if ( reliability > RELIABLE_ORDERED_WITH_ACK_RECEIPT || reliability < 0 )
		reliability = RELIABLE;

	if ( priority > NUMBER_OF_PRIORITIES || priority < 0 )
		priority = HIGH_PRIORITY;

	if ( orderingChannel >= NUMBER_OF_ORDERED_STREAMS )
		orderingChannel = 0;

	unsigned int numberOfBytesToSend=(unsigned int) BITS_TO_BYTES(numberOfBitsToSend);
	if ( numberOfBitsToSend == 0 )
	{
		return false;
	}
	InternalPacket * internalPacket = AllocateFromInternalPacketPool();
	if (internalPacket==0)
	{
		notifyOutOfMemory(_FILE_AND_LINE_);
		return false; // Out of memory
	}

	bpsMetrics[(int) USER_MESSAGE_BYTES_PUSHED].Push1(currentTime,numberOfBytesToSend);

	internalPacket->creationTime = currentTime;

	if ( makeDataCopy )
	{
		AllocInternalPacketData(internalPacket, numberOfBytesToSend, true, _FILE_AND_LINE_ );
		//internalPacket->data = (unsigned char*) rakMalloc_Ex( numberOfBytesToSend, _FILE_AND_LINE_ );
		memcpy( internalPacket->data, data, numberOfBytesToSend );
	}
	else
	{
		// Allocated the data elsewhere, delete it in here
		//internalPacket->data = ( unsigned char* ) data;
		AllocInternalPacketData(internalPacket, (unsigned char*) data );
	}

	internalPacket->dataBitLength = numberOfBitsToSend;
	internalPacket->messageInternalOrder = internalOrderIndex++;
	internalPacket->priority = priority;
	internalPacket->reliability = reliability;
	internalPacket->sendReceiptSerial=receipt;

	// Calculate if I need to split the packet
	//	int headerLength = BITS_TO_BYTES( GetMessageHeaderLengthBits( internalPacket, true ) );

	unsigned int maxDataSizeBytes = GetMaxDatagramSizeExcludingMessageHeaderBytes() - BITS_TO_BYTES(GetMaxMessageHeaderLengthBits());

	bool splitPacket = numberOfBytesToSend > maxDataSizeBytes;

	// If a split packet, we might have to upgrade the reliability
	if ( splitPacket )
	{
		// Split packets cannot be unreliable, in case that one part doesn't arrive and the whole cannot be reassembled.
		// One part could not arrive either due to packetloss or due to unreliable discard
		if (internalPacket->reliability==UNRELIABLE)
			internalPacket->reliability=RELIABLE;
		else if (internalPacket->reliability==UNRELIABLE_WITH_ACK_RECEIPT)
			internalPacket->reliability=RELIABLE_WITH_ACK_RECEIPT;
		else if (internalPacket->reliability==UNRELIABLE_SEQUENCED)
			internalPacket->reliability=RELIABLE_SEQUENCED;
//		else if (internalPacket->reliability==UNRELIABLE_SEQUENCED_WITH_ACK_RECEIPT)
//			internalPacket->reliability=RELIABLE_SEQUENCED_WITH_ACK_RECEIPT;
	}

	//	++sendMessageNumberIndex;

	if ( internalPacket->reliability == RELIABLE_SEQUENCED ||
		internalPacket->reliability == UNRELIABLE_SEQUENCED
//		||
//		internalPacket->reliability == RELIABLE_SEQUENCED_WITH_ACK_RECEIPT ||
//		internalPacket->reliability == UNRELIABLE_SEQUENCED_WITH_ACK_RECEIPT
		)
	{
		// Assign the sequence stream and index
		internalPacket->orderingChannel = orderingChannel;
		internalPacket->orderingIndex = orderedWriteIndex[ orderingChannel ];
		internalPacket->sequencingIndex = sequencedWriteIndex[ orderingChannel ]++;

		// This packet supersedes all other sequenced packets on the same ordering channel
		// Delete all packets in all send lists that are sequenced and on the same ordering channel
		// UPDATE:
		// Disabled.  We don't have enough info to consistently do this.  Sometimes newer data does supercede
		// older data such as with constantly declining health, but not in all cases.
		// For example, with sequenced unreliable sound packets just because you send a newer one doesn't mean you
		// don't need the older ones because the odds are they will still arrive in order
		/*
		for (int i=0; i < NUMBER_OF_PRIORITIES; i++)
		{
		DeleteSequencedPacketsInList(orderingChannel, sendQueue[i]);
		}
		*/
	}
	else if ( internalPacket->reliability == RELIABLE_ORDERED || internalPacket->reliability == RELIABLE_ORDERED_WITH_ACK_RECEIPT )
	{
		// Assign the ordering channel and index
		internalPacket->orderingChannel = orderingChannel;
		internalPacket->orderingIndex = orderedWriteIndex[ orderingChannel ] ++;
		sequencedWriteIndex[ orderingChannel ]=0;
	}

	if ( splitPacket )   // If it uses a secure header it will be generated here
	{
		// Must split the packet.  This will also generate the SHA1 if it is required. It also adds it to the send list.
		//InternalPacket packetCopy;
		//memcpy(&packetCopy, internalPacket, sizeof(InternalPacket));
		//sendPacketSet[priority].CancelWriteLock(internalPacket);
		//SplitPacket( &packetCopy, MTUSize );
		SplitPacket( internalPacket );
		//SLNet::OP_DELETE_ARRAY(packetCopy.data, _FILE_AND_LINE_);
		return true;
	}

	RakAssert(internalPacket->dataBitLength<BYTES_TO_BITS(MAXIMUM_MTU_SIZE));
	AddToUnreliableLinkedList(internalPacket);

	RakAssert(internalPacket->dataBitLength<BYTES_TO_BITS(MAXIMUM_MTU_SIZE));
	RakAssert(internalPacket->messageNumberAssigned==false);
	outgoingPacketBuffer.Push( GetNextWeight(internalPacket->priority), internalPacket, _FILE_AND_LINE_  );
	RakAssert(outgoingPacketBuffer.Size()==0 || outgoingPacketBuffer.Peek()->dataBitLength<BYTES_TO_BITS(MAXIMUM_MTU_SIZE));
	statistics.messageInSendBuffer[(int)internalPacket->priority]++;
	statistics.bytesInSendBuffer[(int)internalPacket->priority]+=(double) BITS_TO_BYTES(internalPacket->dataBitLength);

	//	sendPacketSet[priority].WriteUnlock();
	return true;
}
//-------------------------------------------------------------------------------------------------------
// Run this once per game cycle.  Handles internal lists and actually does the send
//-------------------------------------------------------------------------------------------------------
void ReliabilityLayer::Update( RakNetSocket2 *s, SystemAddress &systemAddress, int MTUSize, CCTimeType time,
							  unsigned bitsPerSecondLimit,
							  DataStructures::List<PluginInterface2*> &messageHandlerList,
							  RakNetRandom *rnr,
							  BitStream &updateBitStream)
{
	UpdateInternal(s, systemAddress, MTUSize, time, bitsPerSecondLimit, messageHandlerList, rnr, updateBitStream, false);
}

void ReliabilityLayer::UpdateAndForceACKs( RakNetSocket2 *s, SystemAddress &systemAddress, int MTUSize, CCTimeType time,
							  unsigned bitsPerSecondLimit,
							  DataStructures::List<PluginInterface2*> &messageHandlerList,
							  RakNetRandom *rnr,
							  BitStream &updateBitStream)
{
	UpdateInternal(s, systemAddress, MTUSize, time, bitsPerSecondLimit, messageHandlerList, rnr, updateBitStream, true);
}

void ReliabilityLayer::UpdateInternal( RakNetSocket2 *s, SystemAddress &systemAddress, int MTUSize, CCTimeType time,
							  unsigned bitsPerSecondLimit,
							  DataStructures::List<PluginInterface2*> &messageHandlerList,
							  RakNetRandom *rnr,
							  BitStream &updateBitStream, bool forceSendACKs)
{
	(void) MTUSize;

	SLNet::TimeMS timeMs;
#if CC_TIME_TYPE_BYTES==4
	time/=1000;
	timeMs=time;
#else
	timeMs=(SLNet::TimeMS) (time/(CCTimeType)1000);
#endif

#ifdef _DEBUG
	while (delayList.Size())
	{
		if (delayList.Peek()->sendTime <= timeMs)
		{
			DataAndTime *dat = delayList.Pop();
//			SocketLayer::SendTo( dat->s, dat->data, dat->length, systemAddress, __FILE__, __LINE__  );

			RNS2_SendParameters bsp;
			bsp.data = (char*) dat->data;
			bsp.length = dat->length;
			bsp.systemAddress = systemAddress;
			dat->s->Send(&bsp, _FILE_AND_LINE_);

			SLNet::OP_DELETE(dat,__FILE__,__LINE__);
		}
		else
		{
			break;
		}
	}
#endif

	// This line is necessary because the timer isn't accurate
	if ((!forceSendACKs) && (time <= lastUpdateTime))
	{
		// Always set the last time in case of overflow
		lastUpdateTime=time;
		return;
	}

	CCTimeType timeSinceLastTick = time - lastUpdateTime;
	lastUpdateTime=time;
#if CC_TIME_TYPE_BYTES==4
	if (timeSinceLastTick>100)
		timeSinceLastTick=100;
#else
	if (timeSinceLastTick>100000)
		timeSinceLastTick=100000;
#endif

	if (unreliableTimeout>0)
	{
		if (timeSinceLastTick>=timeToNextUnreliableCull)
		{
			if (unreliableLinkedListHead)
			{
				// Cull out all unreliable messages that have exceeded the timeout
				InternalPacket *cur = unreliableLinkedListHead;
				InternalPacket *end = unreliableLinkedListHead->unreliablePrev;

				for(;;)
				{
					if (time > cur->creationTime+(CCTimeType)unreliableTimeout)
					{
						// Flag invalid, and clear the memory. Still needs to be removed from the sendPacketSet later
						// This fixes a problem where a remote system disconnects, but we don't know it yet, and memory consumption increases to a huge value
						FreeInternalPacketData(cur, _FILE_AND_LINE_ );
						cur->data=0;
						InternalPacket *next = cur->unreliableNext;
						RemoveFromUnreliableLinkedList(cur);

						if (cur==end)
							break;

						cur=next;
					}
					else
					{
						// 						if (cur==end)
						// 							break;
						// 
						// 						cur=cur->unreliableNext;

						// They should be inserted in-order, so no need to iterate past the first failure
						break;
					}
				}
			}

			timeToNextUnreliableCull=unreliableTimeout/(CCTimeType)2;
		}
		else
		{
			timeToNextUnreliableCull-=timeSinceLastTick;
		}
	}


	// Due to thread vagarities and the way I store the time to avoid slow calls to SLNet::GetTime
	// time may be less than lastAck
#if CC_TIME_TYPE_BYTES==4
	if ( statistics.messagesInResendBuffer!=0 && AckTimeout(time) )
#else
	if ( statistics.messagesInResendBuffer!=0 && AckTimeout(SLNet::TimeMS(time/(CCTimeType)1000)) )
#endif
	{
		// SHOW - dead connection
		// We've waited a very long time for a reliable packet to get an ack and it never has
		deadConnection = true;
		return;
	}

	if (forceSendACKs || congestionManager.ShouldSendACKs(time,timeSinceLastTick))
	{
		SendACKs(s, systemAddress, time, rnr, updateBitStream);
	}

	if (NAKs.Size()>0)
	{
		updateBitStream.Reset();
		DatagramHeaderFormat dhfNAK;
		dhfNAK.isNAK=true;
		dhfNAK.isACK=false;
		dhfNAK.isPacketPair=false;
		dhfNAK.Serialize(&updateBitStream);
		NAKs.Serialize(&updateBitStream, GetMaxDatagramSizeExcludingMessageHeaderBits(), true);
		SendBitStream( s, systemAddress, &updateBitStream, rnr, time );
	}

	DatagramHeaderFormat dhf;
	dhf.needsBAndAs=congestionManager.GetIsInSlowStart();
	dhf.isContinuousSend=bandwidthExceededStatistic;
	// 	bandwidthExceededStatistic=sendPacketSet[0].IsEmpty()==false ||
	// 		sendPacketSet[1].IsEmpty()==false ||
	// 		sendPacketSet[2].IsEmpty()==false ||
	// 		sendPacketSet[3].IsEmpty()==false;
	bandwidthExceededStatistic=outgoingPacketBuffer.Size()>0;

	const bool hasDataToSendOrResend = IsResendQueueEmpty()==false || bandwidthExceededStatistic;
	RakAssert(NUMBER_OF_PRIORITIES==4);
	congestionManager.Update(time, hasDataToSendOrResend);

	statistics.BPSLimitByOutgoingBandwidthLimit = BITS_TO_BYTES(bitsPerSecondLimit);
	statistics.BPSLimitByCongestionControl = congestionManager.GetBytesPerSecondLimitByCongestionControl();

	unsigned int i;
	if (time > lastBpsClear+
#if CC_TIME_TYPE_BYTES==4
		100
#else
		100000
#endif
		)
	{
		for (i=0; i < RNS_PER_SECOND_METRICS_COUNT; i++)
		{
			bpsMetrics[i].ClearExpired1(time);
		}

		lastBpsClear=time;
	}

	if (unreliableWithAckReceiptHistory.Size()>0)
	{
		i=0;
		while (i < unreliableWithAckReceiptHistory.Size())
		{
			//if (unreliableWithAckReceiptHistory[i].nextActionTime < time)
			if (time - unreliableWithAckReceiptHistory[i].nextActionTime < (((CCTimeType)-1)/2) )
			{
				InternalPacket *ackReceipt = AllocateFromInternalPacketPool();
				AllocInternalPacketData(ackReceipt, 5,  false, _FILE_AND_LINE_ );
				ackReceipt->dataBitLength=BYTES_TO_BITS(5);
				ackReceipt->data[0]=(MessageID)ID_SND_RECEIPT_LOSS;
				memcpy(ackReceipt->data+sizeof(MessageID), &unreliableWithAckReceiptHistory[i].sendReceiptSerial, sizeof(uint32_t));
				outputQueue.Push(ackReceipt, _FILE_AND_LINE_ );

				// Remove, swap with last
				unreliableWithAckReceiptHistory.RemoveAtIndex(i);
			}
			else
				i++;
		}
	}

	if (hasDataToSendOrResend==true)
	{
		InternalPacket *internalPacket;
		//		bool forceSend=false;
		bool pushedAnything;
		BitSize_t nextPacketBitLength;
		dhf.isACK=false;
		dhf.isNAK=false;
		dhf.hasBAndAS=false;
		ResetPacketsAndDatagrams();

		int transmissionBandwidth = congestionManager.GetTransmissionBandwidth(time, timeSinceLastTick, unacknowledgedBytes,dhf.isContinuousSend);
		int retransmissionBandwidth = congestionManager.GetRetransmissionBandwidth(time, timeSinceLastTick, unacknowledgedBytes,dhf.isContinuousSend);
		if (retransmissionBandwidth>0 || transmissionBandwidth>0)
		{
			statistics.isLimitedByCongestionControl=false;

			allDatagramSizesSoFar=0;

			// Keep filling datagrams until we exceed retransmission bandwidth
			while ((int)BITS_TO_BYTES(allDatagramSizesSoFar)<retransmissionBandwidth)
			{
				pushedAnything=false;

				// Fill one datagram, then break
				while ( IsResendQueueEmpty()==false )
				{
					internalPacket = resendLinkedListHead;
					RakAssert(internalPacket->messageNumberAssigned==true);

					//if ( internalPacket->nextActionTime < time )
					if ( time - internalPacket->nextActionTime < (((CCTimeType)-1)/2) )
					{
						nextPacketBitLength = internalPacket->headerLength + internalPacket->dataBitLength;
						if ( datagramSizeSoFar + nextPacketBitLength > GetMaxDatagramSizeExcludingMessageHeaderBits() )
						{
							// Gathers all PushPackets()
							PushDatagram();
							break;
						}

						PopListHead(false);

						CC_DEBUG_PRINTF_2("Rs %i ", internalPacket->reliableMessageNumber.val);

						bpsMetrics[(int) USER_MESSAGE_BYTES_RESENT].Push1(time,BITS_TO_BYTES(internalPacket->dataBitLength));

						// Testing1
// 						if (internalPacket->reliability==RELIABLE_ORDERED || internalPacket->reliability==RELIABLE_ORDERED_WITH_ACK_RECEIPT)
// 							printf("RESEND reliableMessageNumber %i with datagram %i\n", internalPacket->reliableMessageNumber.val, congestionManager.GetNextDatagramSequenceNumber().val);

						PushPacket(time,internalPacket,true); // Affects GetNewTransmissionBandwidth()
						internalPacket->timesSent++;
						congestionManager.OnResend(time, internalPacket->nextActionTime);
						internalPacket->retransmissionTime = congestionManager.GetRTOForRetransmission(internalPacket->timesSent);
						internalPacket->nextActionTime = internalPacket->retransmissionTime+time;

						pushedAnything=true;

						for (unsigned int messageHandlerIndex=0; messageHandlerIndex < messageHandlerList.Size(); messageHandlerIndex++)
						{
#if CC_TIME_TYPE_BYTES==4
							messageHandlerList[messageHandlerIndex]->OnInternalPacket(internalPacket, packetsToSendThisUpdateDatagramBoundaries.Size()+congestionManager.GetNextDatagramSequenceNumber(), systemAddress, (SLNet::TimeMS) time, true);
#else
							messageHandlerList[messageHandlerIndex]->OnInternalPacket(internalPacket, packetsToSendThisUpdateDatagramBoundaries.Size()+congestionManager.GetNextDatagramSequenceNumber(), systemAddress, (SLNet::TimeMS)(time/(CCTimeType)1000), true);
#endif
						}

						// Put the packet back into the resend list at the correct spot
						// Don't make a copy since I'm reinserting an allocated struct
						InsertPacketIntoResendList( internalPacket, time, false, false );

						// Removeme
						//						printf("Resend:%i ", internalPacket->reliableMessageNumber);
					}
					else
					{
						// Filled one datagram.
						// If the 2nd and it's time to send a datagram pair, will be marked as a pair
						PushDatagram();
						break;
					}
				}

				if (pushedAnything==false)
					break;
			}
		}
		else
		{
			statistics.isLimitedByCongestionControl=true;
		}

		if ((int)BITS_TO_BYTES(allDatagramSizesSoFar)<transmissionBandwidth)
		{
			//	printf("S+ ");
			allDatagramSizesSoFar=0;

			// Keep filling datagrams until we exceed transmission bandwidth
			while (
				ResendBufferOverflow()==false &&
				((int)BITS_TO_BYTES(allDatagramSizesSoFar)<transmissionBandwidth ||
				// This condition means if we want to send a datagram pair, and only have one datagram buffered, exceed bandwidth to add another
				(countdownToNextPacketPair==0 &&
				datagramsToSendThisUpdateIsPair.Size()==1))
				)
			{
				// Fill with packets until MTU is reached
				//	for ( i = 0; i < NUMBER_OF_PRIORITIES; i++ )
				//	{
				pushedAnything=false;

				statistics.isLimitedByOutgoingBandwidthLimit=bitsPerSecondLimit!=0 && BITS_TO_BYTES(bitsPerSecondLimit) < bpsMetrics[USER_MESSAGE_BYTES_SENT].GetBPS1(time);


				while (outgoingPacketBuffer.Size() &&
					statistics.isLimitedByOutgoingBandwidthLimit==false)
					//while ( sendPacketSet[ i ].Size() )
				{
					internalPacket=outgoingPacketBuffer.Peek();
					RakAssert(internalPacket->messageNumberAssigned==false);
					RakAssert(outgoingPacketBuffer.Size()==0 || outgoingPacketBuffer.Peek()->dataBitLength<BYTES_TO_BITS(MAXIMUM_MTU_SIZE));

					// internalPacket = sendPacketSet[ i ].Peek();
					if (internalPacket->data==0)
					{
						//sendPacketSet[ i ].Pop();
						outgoingPacketBuffer.Pop(0);
						RakAssert(outgoingPacketBuffer.Size()==0 || outgoingPacketBuffer.Peek()->dataBitLength<BYTES_TO_BITS(MAXIMUM_MTU_SIZE));
						statistics.messageInSendBuffer[(int)internalPacket->priority]--;
						statistics.bytesInSendBuffer[(int)internalPacket->priority]-=(double) BITS_TO_BYTES(internalPacket->dataBitLength);
						ReleaseToInternalPacketPool( internalPacket );
						continue;
					}

					internalPacket->headerLength=GetMessageHeaderLengthBits(internalPacket);
					nextPacketBitLength = internalPacket->headerLength + internalPacket->dataBitLength;
					if ( datagramSizeSoFar + nextPacketBitLength > GetMaxDatagramSizeExcludingMessageHeaderBits() )
					{
						// Hit MTU. May still push packets if smaller ones exist at a lower priority
						RakAssert(datagramSizeSoFar!=0);
						RakAssert(internalPacket->dataBitLength<BYTES_TO_BITS(MAXIMUM_MTU_SIZE));
						break;
					}

					bool isReliable;
					if ( internalPacket->reliability == RELIABLE ||
						internalPacket->reliability == RELIABLE_SEQUENCED ||
						internalPacket->reliability == RELIABLE_ORDERED ||
						internalPacket->reliability == RELIABLE_WITH_ACK_RECEIPT  ||
//						internalPacket->reliability == RELIABLE_SEQUENCED_WITH_ACK_RECEIPT  ||
						internalPacket->reliability == RELIABLE_ORDERED_WITH_ACK_RECEIPT
						)
						isReliable = true;
					else
						isReliable = false;

					//sendPacketSet[ i ].Pop();
					outgoingPacketBuffer.Pop(0);
					RakAssert(outgoingPacketBuffer.Size()==0 || outgoingPacketBuffer.Peek()->dataBitLength<BYTES_TO_BITS(MAXIMUM_MTU_SIZE));
					RakAssert(internalPacket->messageNumberAssigned==false);
					statistics.messageInSendBuffer[(int)internalPacket->priority]--;
					statistics.bytesInSendBuffer[(int)internalPacket->priority]-=(double) BITS_TO_BYTES(internalPacket->dataBitLength);
					if (isReliable
						/*
						I thought about this and agree that UNRELIABLE_SEQUENCED_WITH_ACK_RECEIPT and RELIABLE_SEQUENCED_WITH_ACK_RECEIPT is not useful unless you also know if the message was discarded.

						The problem is that internally, message numbers are only assigned to reliable messages, because message numbers are only used to discard duplicate message receipt and only reliable messages get sent more than once. However, without message numbers getting assigned and transmitted, there is no way to tell the sender about which messages were discarded. In fact, in looking this over I realized that UNRELIABLE_SEQUENCED_WITH_ACK_RECEIPT introduced a bug, because the remote system assumes all message numbers are used (no holes). With that send type, on packetloss, a permanent hole would have been created which eventually would cause the system to discard all further packets.

						So I have two options. Either do not support ack receipts when sending sequenced, or write complex and major new systems. UNRELIABLE_SEQUENCED_WITH_ACK_RECEIPT would need to send the message ID number on a special channel which allows for non-delivery. And both of them would need to have a special range list to indicate which message numbers were not delivered, so when acks are sent that can be indicated as well. A further problem is that the ack itself can be lost - it is possible that the message can arrive but be discarded, yet the ack is lost. On resend, the resent message would be ignored as duplicate, and you'd never get the discard message either (unless I made a special buffer for that case too). 
*/
//						||
						// If needs an ack receipt, keep the internal packet around in the list
//						internalPacket->reliability == UNRELIABLE_WITH_ACK_RECEIPT ||
//						internalPacket->reliability == UNRELIABLE_SEQUENCED_WITH_ACK_RECEIPT
						)
					{
						internalPacket->messageNumberAssigned=true;
						internalPacket->reliableMessageNumber=sendReliableMessageNumberIndex;
						internalPacket->retransmissionTime = congestionManager.GetRTOForRetransmission(internalPacket->timesSent+1);
						internalPacket->nextActionTime = internalPacket->retransmissionTime+time;
#if CC_TIME_TYPE_BYTES==4
						const CCTimeType threshhold = 10000;
#else
						const CCTimeType threshhold = 10000000;
#endif
						if (internalPacket->nextActionTime-time > threshhold)
						{
							//								int a=5;
							RakAssert(time-internalPacket->nextActionTime < threshhold);
						}
						//resendTree.Insert( internalPacket->reliableMessageNumber, internalPacket);
						if (resendBuffer[internalPacket->reliableMessageNumber & (uint32_t) RESEND_BUFFER_ARRAY_MASK]!=0)
						{
							//								bool overflow = ResendBufferOverflow();
							RakAssert(0);
						}
						resendBuffer[internalPacket->reliableMessageNumber & (uint32_t) RESEND_BUFFER_ARRAY_MASK] = internalPacket;
						statistics.messagesInResendBuffer++;
						statistics.bytesInResendBuffer+=BITS_TO_BYTES(internalPacket->dataBitLength);

						//		printf("pre:%i ", unacknowledgedBytes);

						InsertPacketIntoResendList( internalPacket, time, true, isReliable);


						//		printf("post:%i ", unacknowledgedBytes);
						sendReliableMessageNumberIndex++;
					}
					else if (internalPacket->reliability == UNRELIABLE_WITH_ACK_RECEIPT)
					{
						unreliableWithAckReceiptHistory.Push(UnreliableWithAckReceiptNode(
							congestionManager.GetNextDatagramSequenceNumber() + packetsToSendThisUpdateDatagramBoundaries.Size(),
							internalPacket->sendReceiptSerial,
							congestionManager.GetRTOForRetransmission(internalPacket->timesSent+1)+time
							), _FILE_AND_LINE_);
					}

					// If isReliable is false, the packet and its contents will be added to a list to be freed in ClearPacketsAndDatagrams
					// However, the internalPacket structure will remain allocated and be in the resendBuffer list if it requires a receipt
					bpsMetrics[(int) USER_MESSAGE_BYTES_SENT].Push1(time,BITS_TO_BYTES(internalPacket->dataBitLength));

					// Testing1
// 					if (internalPacket->reliability==RELIABLE_ORDERED || internalPacket->reliability==RELIABLE_ORDERED_WITH_ACK_RECEIPT)
// 						printf("SEND reliableMessageNumber %i in datagram %i\n", internalPacket->reliableMessageNumber.val, congestionManager.GetNextDatagramSequenceNumber().val);

					PushPacket(time,internalPacket, isReliable);
					internalPacket->timesSent++;

					for (unsigned int messageHandlerIndex=0; messageHandlerIndex < messageHandlerList.Size(); messageHandlerIndex++)
					{
#if CC_TIME_TYPE_BYTES==4
						messageHandlerList[messageHandlerIndex]->OnInternalPacket(internalPacket, packetsToSendThisUpdateDatagramBoundaries.Size()+congestionManager.GetNextDatagramSequenceNumber(), systemAddress, (SLNet::TimeMS)time, true);
#else
						messageHandlerList[messageHandlerIndex]->OnInternalPacket(internalPacket, packetsToSendThisUpdateDatagramBoundaries.Size()+congestionManager.GetNextDatagramSequenceNumber(), systemAddress, (SLNet::TimeMS)(time/(CCTimeType)1000), true);
#endif
					}
					pushedAnything=true;

					if (ResendBufferOverflow())
						break;
				}
				//	if (ResendBufferOverflow())
				//		break;
				//	}z

				// No datagrams pushed?
				if (datagramSizeSoFar==0)
					break;

				// Filled one datagram.
				// If the 2nd and it's time to send a datagram pair, will be marked as a pair
				PushDatagram();
			}
		}


		for (unsigned int datagramIndex=0; datagramIndex < packetsToSendThisUpdateDatagramBoundaries.Size(); datagramIndex++)
		{
			if (datagramIndex>0)
				dhf.isContinuousSend=true;
			MessageNumberNode* messageNumberNode = 0;
			dhf.datagramNumber=congestionManager.GetAndIncrementNextDatagramSequenceNumber();
			dhf.isPacketPair=datagramsToSendThisUpdateIsPair[datagramIndex];

			//printf("%p pushing datagram %i\n", this, dhf.datagramNumber.val);

			bool isSecondOfPacketPair=dhf.isPacketPair && datagramIndex>0 &&  datagramsToSendThisUpdateIsPair[datagramIndex-1];
			unsigned int msgIndex, msgTerm;
			if (datagramIndex==0)
			{
				msgIndex=0;
				msgTerm=packetsToSendThisUpdateDatagramBoundaries[0];
			}
			else
			{
				msgIndex=packetsToSendThisUpdateDatagramBoundaries[datagramIndex-1];
				msgTerm=packetsToSendThisUpdateDatagramBoundaries[datagramIndex];
			}

			// More accurate time to reset here
#if INCLUDE_TIMESTAMP_WITH_DATAGRAMS==1
			dhf.sourceSystemTime= SLNet::GetTimeUS();
#endif
			updateBitStream.Reset();
			dhf.Serialize(&updateBitStream);
			CC_DEBUG_PRINTF_2("S%i ",dhf.datagramNumber.val);

			while (msgIndex < msgTerm)
			{
				// If reliable or needs receipt
				if ( packetsToSendThisUpdate[msgIndex]->reliability != UNRELIABLE &&
					packetsToSendThisUpdate[msgIndex]->reliability != UNRELIABLE_SEQUENCED
					)
				{
					if (messageNumberNode==0)
					{
						messageNumberNode = AddFirstToDatagramHistory(dhf.datagramNumber, packetsToSendThisUpdate[msgIndex]->reliableMessageNumber, time);
					}
					else
					{
						messageNumberNode = AddSubsequentToDatagramHistory(messageNumberNode, packetsToSendThisUpdate[msgIndex]->reliableMessageNumber);
					}
				}

				RakAssert(updateBitStream.GetNumberOfBytesUsed()<=MAXIMUM_MTU_SIZE-UDP_HEADER_SIZE);
				WriteToBitStreamFromInternalPacket( &updateBitStream, packetsToSendThisUpdate[msgIndex], time );
				RakAssert(updateBitStream.GetNumberOfBytesUsed()<=MAXIMUM_MTU_SIZE-UDP_HEADER_SIZE);
				msgIndex++;
			}

			if (isSecondOfPacketPair)
			{
				// Pad to size of first datagram
				RakAssert(updateBitStream.GetNumberOfBytesUsed()<=MAXIMUM_MTU_SIZE-UDP_HEADER_SIZE);
				updateBitStream.PadWithZeroToByteLength(datagramSizesInBytes[datagramIndex-1]);
				RakAssert(updateBitStream.GetNumberOfBytesUsed()<=MAXIMUM_MTU_SIZE-UDP_HEADER_SIZE);
			}

			if (messageNumberNode==0)
			{
				// Unreliable, add dummy node
				AddFirstToDatagramHistory(dhf.datagramNumber, time);
			}

			// Store what message ids were sent with this datagram
			//	datagramMessageIDTree.Insert(dhf.datagramNumber,idList);

			congestionManager.OnSendBytes(time,UDP_HEADER_SIZE+DatagramHeaderFormat::GetDataHeaderByteLength());

			SendBitStream( s, systemAddress, &updateBitStream, rnr, time );

			bandwidthExceededStatistic=outgoingPacketBuffer.Size()>0;
			// 			bandwidthExceededStatistic=sendPacketSet[0].IsEmpty()==false ||
			// 				sendPacketSet[1].IsEmpty()==false ||
			// 				sendPacketSet[2].IsEmpty()==false ||
			// 				sendPacketSet[3].IsEmpty()==false;



			if (bandwidthExceededStatistic==true)
				timeOfLastContinualSend=time;
			else
				timeOfLastContinualSend=0;
		}

		ClearPacketsAndDatagrams();

		// Any data waiting to send after attempting to send, then bandwidth is exceeded
		bandwidthExceededStatistic=outgoingPacketBuffer.Size()>0;
		// 		bandwidthExceededStatistic=sendPacketSet[0].IsEmpty()==false ||
		// 			sendPacketSet[1].IsEmpty()==false ||
		// 			sendPacketSet[2].IsEmpty()==false ||
		// 			sendPacketSet[3].IsEmpty()==false;
	}


	// Keep on top of deleting old unreliable split packets so they don't clog the list.
	//DeleteOldUnreliableSplitPackets( time );
}

//-------------------------------------------------------------------------------------------------------
// Writes a bitstream to the socket
//-------------------------------------------------------------------------------------------------------
void ReliabilityLayer::SendBitStream( RakNetSocket2 *s, SystemAddress &systemAddress, SLNet::BitStream *bitStream, RakNetRandom *rnr, CCTimeType currentTime)
{
	(void) systemAddress;
	(void) rnr;

	unsigned int length;

	length = (unsigned int) bitStream->GetNumberOfBytesUsed();


#ifdef _DEBUG
	if (packetloss > 0.0)
	{
		if (frandomMT() < packetloss)
			return;
	}

	if (minExtraPing > 0 || extraPingVariance > 0)
	{
#ifdef FLIP_SEND_ORDER_TEST
		// Flip order of sends without delaying them for testing
		DataAndTime *dat = SLNet::OP_NEW<DataAndTime>(__FILE__,__LINE__);
		memcpy(dat->data, ( char* ) bitStream->GetData(), length );
		dat->s=s;
		dat->length=length;
		dat->sendTime = 0;
		dat->remotePortRakNetWasStartedOn_PS3=remotePortRakNetWasStartedOn_PS3;
		dat->extraSocketOptions=extraSocketOptions;
		delayList.PushAtHead(dat, 0, _FILE_AND_LINE_);
#else
		SLNet::TimeMS delay = minExtraPing;
		if (extraPingVariance>0)
			delay += (randomMT() % extraPingVariance);
		if (delay > 0)
		{
			DataAndTime *dat = SLNet::OP_NEW<DataAndTime>(__FILE__,__LINE__);
			memcpy(dat->data, ( char* ) bitStream->GetData(), length );
			dat->s=s;
			dat->length=length;
			dat->sendTime = SLNet::GetTimeMS() + delay;
			for (unsigned int i=0; i < delayList.Size(); i++)
			{
				if (dat->sendTime < delayList[i]->sendTime)
				{
					delayList.PushAtHead(dat, i, __FILE__, __LINE__);
					dat=0;
					break;
				}
			}
			if (dat!=0)
				delayList.Push(dat,__FILE__,__LINE__);
			return;
		}
#endif
	}
#endif

#if LIBCAT_SECURITY==1
	if (useSecurity)
	{
		unsigned char *buffer = reinterpret_cast<unsigned char*>( bitStream->GetData() );

		int buffer_size = bitStream->GetNumberOfBitsAllocated() / 8;

		// Verify there is enough room for encrypted output and encrypt
		// Encrypt() will increase length
		SLNET_VERIFY(auth_enc.Encrypt(buffer, buffer_size, length));
	}
#endif

	bpsMetrics[(int) ACTUAL_BYTES_SENT].Push1(currentTime,length);

	RakAssert(length <= congestionManager.GetMTU());

#ifdef USE_THREADED_SEND
	SendToThread::SendToThreadBlock *block =  SendToThread::AllocateBlock();
	memcpy(block->data, bitStream->GetData(), length);
	block->dataWriteOffset=length;
	block->extraSocketOptions=extraSocketOptions;
	block->remotePortRakNetWasStartedOn_PS3=remotePortRakNetWasStartedOn_PS3;
	block->s=s;
	block->systemAddress=systemAddress;
	SendToThread::ProcessBlock(block);
#else
	// SocketLayer::SendTo( s, ( char* ) bitStream->GetData(), length, systemAddress, __FILE__, __LINE__  );

	RNS2_SendParameters bsp;
	bsp.data = (char*) bitStream->GetData();
	bsp.length = length;
	bsp.systemAddress = systemAddress;
	s->Send(&bsp, _FILE_AND_LINE_);
#endif
}

//-------------------------------------------------------------------------------------------------------
// Are we waiting for any data to be sent out or be processed by the player?
//-------------------------------------------------------------------------------------------------------
bool ReliabilityLayer::IsOutgoingDataWaiting(void)
{
	if (outgoingPacketBuffer.Size()>0)
		return true;

	// 	unsigned i;
	// 	for ( i = 0; i < NUMBER_OF_PRIORITIES; i++ )
	// 	{
	// 		if (sendPacketSet[ i ].Size() > 0)
	// 			return true;
	// 	}

	return 
		//acknowlegements.Size() > 0 ||
		//resendTree.IsEmpty()==false;// || outputQueue.Size() > 0 || orderingList.Size() > 0 || splitPacketChannelList.Size() > 0;
		statistics.messagesInResendBuffer!=0;
}
bool ReliabilityLayer::AreAcksWaiting(void)
{
	return acknowlegements.Size() > 0;
}
//-------------------------------------------------------------------------------------------------------
void ReliabilityLayer::ApplyNetworkSimulator( double _packetloss, SLNet::TimeMS _minExtraPing, SLNet::TimeMS _extraPingVariance )
{
#ifndef _DEBUG
	// unused parameters
	(void)_packetloss;
	(void)_minExtraPing;
	(void)_extraPingVariance;
#endif

#ifdef _DEBUG
	packetloss=_packetloss;
	minExtraPing=_minExtraPing;
	extraPingVariance=_extraPingVariance;
	//	if (ping < (unsigned int)(minExtraPing+extraPingVariance)*2)
	//		ping=(minExtraPing+extraPingVariance)*2;
#endif
}
//-------------------------------------------------------------------------------------------------------
void ReliabilityLayer::SetSplitMessageProgressInterval(int interval)
{
	splitMessageProgressInterval=interval;
}
//-------------------------------------------------------------------------------------------------------
void ReliabilityLayer::SetUnreliableTimeout(SLNet::TimeMS timeoutMS)
{
#if CC_TIME_TYPE_BYTES==4
	unreliableTimeout=timeoutMS;
#else
	unreliableTimeout=(CCTimeType)timeoutMS*(CCTimeType)1000;
#endif
}

//-------------------------------------------------------------------------------------------------------
// This will return true if we should not send at this time
//-------------------------------------------------------------------------------------------------------
bool ReliabilityLayer::IsSendThrottled( int MTUSize )
{
	(void) MTUSize;

	return false;
	//	return resendList.Size() > windowSize;

	// Disabling this, because it can get stuck here forever
	/*
	unsigned packetsWaiting;
	unsigned resendListDataSize=0;
	unsigned i;
	for (i=0; i < resendList.Size(); i++)
	{
	if (resendList[i])
	resendListDataSize+=resendList[i]->dataBitLength;
	}
	packetsWaiting = 1 + ((BITS_TO_BYTES(resendListDataSize)) / (MTUSize - UDP_HEADER_SIZE - 10)); // 10 to roughly estimate the raknet header

	return packetsWaiting >= windowSize;
	*/
}

//-------------------------------------------------------------------------------------------------------
// We lost a packet
//-------------------------------------------------------------------------------------------------------
void ReliabilityLayer::UpdateWindowFromPacketloss( CCTimeType time )
{
	(void) time;
}

//-------------------------------------------------------------------------------------------------------
// Increase the window size
//-------------------------------------------------------------------------------------------------------
void ReliabilityLayer::UpdateWindowFromAck( CCTimeType time )
{
	(void) time;
}

//-------------------------------------------------------------------------------------------------------
// Does what the function name says
//-------------------------------------------------------------------------------------------------------
unsigned ReliabilityLayer::RemovePacketFromResendListAndDeleteOlderReliableSequenced( const MessageNumberType messageNumber, CCTimeType time, DataStructures::List<PluginInterface2*> &messageHandlerList, const SystemAddress &systemAddress )
{
	(void) time;
	(void) messageNumber;
	InternalPacket * internalPacket;
	//InternalPacket *temp;
//	PacketReliability reliability; // What type of reliability algorithm to use with this packet
//	unsigned char orderingChannel; // What ordering channel this packet is on, if the reliability type uses ordering channels
//	OrderingIndexType orderingIndex; // The ID used as identification for ordering channels
	//	unsigned j;

	for (unsigned int messageHandlerIndex=0; messageHandlerIndex < messageHandlerList.Size(); messageHandlerIndex++)
	{
#if CC_TIME_TYPE_BYTES==4
		messageHandlerList[messageHandlerIndex]->OnAck(messageNumber, systemAddress, time);
#else
		messageHandlerList[messageHandlerIndex]->OnAck(messageNumber, systemAddress, (SLNet::TimeMS)(time/(CCTimeType)1000));
#endif
	}

	// Testing1
// 	if (resendLinkedListHead)
// 	{
// 		InternalPacket *internalPacket = resendLinkedListHead;
// 		do 
// 		{
// 			internalPacket=internalPacket->resendNext;
// 			printf("%i ", internalPacket->reliableMessageNumber.val);
// 		} while (internalPacket!=resendLinkedListHead);
// 		printf("\n");
// 	}

	//	bool deleted;
	//	deleted=resendTree.Delete(messageNumber, internalPacket);
	internalPacket = resendBuffer[messageNumber & RESEND_BUFFER_ARRAY_MASK];
	// May ask to remove twice, for example resend twice, then second ack
	if (internalPacket && internalPacket->reliableMessageNumber==messageNumber)
	{
	//	ValidateResendList();
		resendBuffer[messageNumber & RESEND_BUFFER_ARRAY_MASK]=0;
		CC_DEBUG_PRINTF_2("AckRcv %i ", messageNumber);

		statistics.messagesInResendBuffer--;
		statistics.bytesInResendBuffer-=BITS_TO_BYTES(internalPacket->dataBitLength);

//		orderingIndex = internalPacket->orderingIndex;
		totalUserDataBytesAcked+=(double) BITS_TO_BYTES(internalPacket->headerLength+internalPacket->dataBitLength);

		// Return receipt if asked for
		if (internalPacket->reliability>=RELIABLE_WITH_ACK_RECEIPT && 
			(internalPacket->splitPacketCount==0 || internalPacket->splitPacketIndex+1==internalPacket->splitPacketCount)
			)
		{
			InternalPacket *ackReceipt = AllocateFromInternalPacketPool();
			AllocInternalPacketData(ackReceipt, 5,  false, _FILE_AND_LINE_ );
			ackReceipt->dataBitLength=BYTES_TO_BITS(5);
			ackReceipt->data[0]=(MessageID)ID_SND_RECEIPT_ACKED;
			memcpy(ackReceipt->data+sizeof(MessageID), &internalPacket->sendReceiptSerial, sizeof(internalPacket->sendReceiptSerial));
			outputQueue.Push(ackReceipt, _FILE_AND_LINE_ );
		}

		bool isReliable;
		if ( internalPacket->reliability == RELIABLE ||
			internalPacket->reliability == RELIABLE_SEQUENCED ||
			internalPacket->reliability == RELIABLE_ORDERED ||
			internalPacket->reliability == RELIABLE_WITH_ACK_RECEIPT  ||
//			internalPacket->reliability == RELIABLE_SEQUENCED_WITH_ACK_RECEIPT  ||
			internalPacket->reliability == RELIABLE_ORDERED_WITH_ACK_RECEIPT
			)
			isReliable = true;
		else
			isReliable = false;

		RemoveFromList(internalPacket, isReliable);
		FreeInternalPacketData(internalPacket, _FILE_AND_LINE_ );
		ReleaseToInternalPacketPool( internalPacket );


		return 0;
	}
	else
	{

	}

	return (unsigned)-1;
}

//-------------------------------------------------------------------------------------------------------
// Acknowledge receipt of the packet with the specified messageNumber
//-------------------------------------------------------------------------------------------------------
void ReliabilityLayer::SendAcknowledgementPacket( const DatagramSequenceNumberType messageNumber, CCTimeType time )
{

	// REMOVEME
	// printf("%p Send ack %i\n", this, messageNumber.val);

	nextAckTimeToSend=time;
	acknowlegements.Insert(messageNumber);

	//printf("ACK_DG:%i ", messageNumber.val);

	CC_DEBUG_PRINTF_2("AckPush %i ", messageNumber);

}

//-------------------------------------------------------------------------------------------------------
// Parse an internalPacket and figure out how many header bits would be
// written.  Returns that number
//-------------------------------------------------------------------------------------------------------
BitSize_t ReliabilityLayer::GetMaxMessageHeaderLengthBits( void )
{
	InternalPacket ip;
	ip.reliability=RELIABLE_SEQUENCED;
	ip.splitPacketCount=1;
	return GetMessageHeaderLengthBits(&ip);
}
//-------------------------------------------------------------------------------------------------------
BitSize_t ReliabilityLayer::GetMessageHeaderLengthBits( const InternalPacket *const internalPacket )
{	
	BitSize_t bitLength;

	//	bitStream->AlignWriteToByteBoundary(); // Potentially unaligned
	//	tempChar=(unsigned char)internalPacket->reliability; bitStream->WriteBits( (const unsigned char *)&tempChar, 3, true ); // 3 bits to write reliability.
	//	bool hasSplitPacket = internalPacket->splitPacketCount>0; bitStream->Write(hasSplitPacket); // Write 1 bit to indicate if splitPacketCount>0
	bitLength = 8*1;

	//	bitStream->AlignWriteToByteBoundary();
	//	RakAssert(internalPacket->dataBitLength < 65535);
	//	unsigned short s; s = (unsigned short) internalPacket->dataBitLength; bitStream->WriteAlignedVar16((const char*)& s);
	bitLength += 8*2;

	if ( internalPacket->reliability == RELIABLE ||
		internalPacket->reliability == RELIABLE_SEQUENCED ||
		internalPacket->reliability == RELIABLE_ORDERED ||
		internalPacket->reliability == RELIABLE_WITH_ACK_RECEIPT ||
//		internalPacket->reliability == RELIABLE_SEQUENCED_WITH_ACK_RECEIPT ||
		internalPacket->reliability == RELIABLE_ORDERED_WITH_ACK_RECEIPT
		)
		bitLength += 8*3; // bitStream->Write(internalPacket->reliableMessageNumber); // Message sequence number
	// bitStream->AlignWriteToByteBoundary(); // Potentially nothing else to write



	if ( internalPacket->reliability == UNRELIABLE_SEQUENCED ||
		internalPacket->reliability == RELIABLE_SEQUENCED
		)
	{
		bitLength += 8*3;; // bitStream->Write(internalPacket->_sequencingIndex); // Used for UNRELIABLE_SEQUENCED, RELIABLE_SEQUENCED, RELIABLE_ORDERED.
	}

	if ( internalPacket->reliability == UNRELIABLE_SEQUENCED ||
		internalPacket->reliability == RELIABLE_SEQUENCED ||
		internalPacket->reliability == RELIABLE_ORDERED ||
		internalPacket->reliability == RELIABLE_ORDERED_WITH_ACK_RECEIPT
		)
	{
		bitLength += 8*3; // bitStream->Write(internalPacket->orderingIndex); // Used for UNRELIABLE_SEQUENCED, RELIABLE_SEQUENCED, RELIABLE_ORDERED.
		bitLength += 8*1; // tempChar=internalPacket->orderingChannel; bitStream->WriteAlignedVar8((const char*)& tempChar); // Used for UNRELIABLE_SEQUENCED, RELIABLE_SEQUENCED, RELIABLE_ORDERED. 5 bits needed, write one byte
	}
	if (internalPacket->splitPacketCount>0)
	{
		bitLength += 8*4; // bitStream->WriteAlignedVar32((const char*)& internalPacket->splitPacketCount); RakAssert(sizeof(SplitPacketIndexType)==4); // Only needed if splitPacketCount>0. 4 bytes
		bitLength += 8*sizeof(SplitPacketIdType); // bitStream->WriteAlignedVar16((const char*)& internalPacket->splitPacketId); RakAssert(sizeof(SplitPacketIdType)==2); // Only needed if splitPacketCount>0.
		bitLength += 8*4; // bitStream->WriteAlignedVar32((const char*)& internalPacket->splitPacketIndex); // Only needed if splitPacketCount>0. 4 bytes
	}

	return bitLength;
}

//-------------------------------------------------------------------------------------------------------
// Parse an internalPacket and create a bitstream to represent this data
//-------------------------------------------------------------------------------------------------------
BitSize_t ReliabilityLayer::WriteToBitStreamFromInternalPacket(SLNet::BitStream *bitStream, const InternalPacket *const internalPacket, CCTimeType curTime )
{
	(void) curTime;

	BitSize_t start = bitStream->GetNumberOfBitsUsed();
	unsigned char tempChar;

	// (Incoming data may be all zeros due to padding)
	bitStream->AlignWriteToByteBoundary(); // Potentially unaligned
	if (internalPacket->reliability==UNRELIABLE_WITH_ACK_RECEIPT)
		tempChar=UNRELIABLE;
	else if (internalPacket->reliability==RELIABLE_WITH_ACK_RECEIPT)
		tempChar=RELIABLE;
	else if (internalPacket->reliability==RELIABLE_ORDERED_WITH_ACK_RECEIPT)
		tempChar=RELIABLE_ORDERED;
	else
		tempChar=(unsigned char)internalPacket->reliability;

	bitStream->WriteBits( (const unsigned char *)&tempChar, 3, true ); // 3 bits to write reliability.

	bool hasSplitPacket = internalPacket->splitPacketCount>0; bitStream->Write(hasSplitPacket); // Write 1 bit to indicate if splitPacketCount>0
	bitStream->AlignWriteToByteBoundary();
	RakAssert(internalPacket->dataBitLength < 65535);
	unsigned short s; s = (unsigned short) internalPacket->dataBitLength; bitStream->WriteAlignedVar16((const char*)& s);
	if ( internalPacket->reliability == RELIABLE ||
		internalPacket->reliability == RELIABLE_SEQUENCED ||
		internalPacket->reliability == RELIABLE_ORDERED ||
		internalPacket->reliability == RELIABLE_WITH_ACK_RECEIPT ||
		internalPacket->reliability == RELIABLE_ORDERED_WITH_ACK_RECEIPT
		)
		bitStream->Write(internalPacket->reliableMessageNumber); // Used for all reliable types
	bitStream->AlignWriteToByteBoundary(); // Potentially nothing else to write

	if ( internalPacket->reliability == UNRELIABLE_SEQUENCED ||
		internalPacket->reliability == RELIABLE_SEQUENCED
		)
	{
		bitStream->Write(internalPacket->sequencingIndex); // Used for UNRELIABLE_SEQUENCED, RELIABLE_SEQUENCED, RELIABLE_ORDERED.
	}

	if ( internalPacket->reliability == UNRELIABLE_SEQUENCED ||
		internalPacket->reliability == RELIABLE_SEQUENCED ||
		internalPacket->reliability == RELIABLE_ORDERED ||
		internalPacket->reliability == RELIABLE_ORDERED_WITH_ACK_RECEIPT
		)
	{
		bitStream->Write(internalPacket->orderingIndex); // Used for UNRELIABLE_SEQUENCED, RELIABLE_SEQUENCED, RELIABLE_ORDERED.
		tempChar=internalPacket->orderingChannel; bitStream->WriteAlignedVar8((const char*)& tempChar); // Used for UNRELIABLE_SEQUENCED, RELIABLE_SEQUENCED, RELIABLE_ORDERED. 5 bits needed, write one byte
	}

	if (internalPacket->splitPacketCount>0)
	{
	//	printf("Write before\n");
	//	bitStream->PrintBits();

		bitStream->WriteAlignedVar32((const char*)& internalPacket->splitPacketCount); RakAssert(sizeof(SplitPacketIndexType)==4); // Only needed if splitPacketCount>0. 4 bytes
		bitStream->WriteAlignedVar16((const char*)& internalPacket->splitPacketId); RakAssert(sizeof(SplitPacketIdType)==2); // Only needed if splitPacketCount>0.
		bitStream->WriteAlignedVar32((const char*)& internalPacket->splitPacketIndex); // Only needed if splitPacketCount>0. 4 bytes

	//	printf("Write after\n");
	//	bitStream->PrintBits();
	}

	// Write the actual data.
	bitStream->WriteAlignedBytes( ( unsigned char* ) internalPacket->data, BITS_TO_BYTES( internalPacket->dataBitLength ) );

	return bitStream->GetNumberOfBitsUsed() - start;
}

//-------------------------------------------------------------------------------------------------------
// Parse a bitstream and create an internal packet to represent this data
//-------------------------------------------------------------------------------------------------------
InternalPacket* ReliabilityLayer::CreateInternalPacketFromBitStream(SLNet::BitStream *bitStream, CCTimeType time )
{
	bool bitStreamSucceeded;
	InternalPacket* internalPacket;
	unsigned char tempChar;
	bool hasSplitPacket=false;
	bool readSuccess;

	if ( bitStream->GetNumberOfUnreadBits() < (int) sizeof( internalPacket->reliableMessageNumber ) * 8 )
		return 0; // leftover bits

	internalPacket = AllocateFromInternalPacketPool();
	if (internalPacket==0)
	{
		// Out of memory
		RakAssert(0);
		return 0;
	}
	internalPacket->creationTime = time;

	// (Incoming data may be all zeros due to padding)
	bitStream->AlignReadToByteBoundary(); // Potentially unaligned
	bitStream->ReadBits( ( unsigned char* ) ( &( tempChar ) ), 3 );
	internalPacket->reliability = ( const PacketReliability ) tempChar;
	readSuccess=bitStream->Read(hasSplitPacket); // Read 1 bit to indicate if splitPacketCount>0
	bitStream->AlignReadToByteBoundary();
	unsigned short s; bitStream->ReadAlignedVar16((char*)&s); internalPacket->dataBitLength=s; // Length of message (2 bytes)
	if ( internalPacket->reliability == RELIABLE ||
		internalPacket->reliability == RELIABLE_SEQUENCED ||
		internalPacket->reliability == RELIABLE_ORDERED
		// I don't write ACK_RECEIPT to the remote system
// 		||
// 		internalPacket->reliability == RELIABLE_WITH_ACK_RECEIPT ||
// 		internalPacket->reliability == RELIABLE_SEQUENCED_WITH_ACK_RECEIPT ||
// 		internalPacket->reliability == RELIABLE_ORDERED_WITH_ACK_RECEIPT
		)
		bitStream->Read(internalPacket->reliableMessageNumber); // Message sequence number
	else
		internalPacket->reliableMessageNumber=(MessageNumberType)(const uint32_t)-1;
	bitStream->AlignReadToByteBoundary(); // Potentially nothing else to Read

	if ( internalPacket->reliability == UNRELIABLE_SEQUENCED ||
		internalPacket->reliability == RELIABLE_SEQUENCED
		)
	{
		bitStream->Read(internalPacket->sequencingIndex); // Used for UNRELIABLE_SEQUENCED, RELIABLE_SEQUENCED, RELIABLE_ORDERED.
	}

	if ( internalPacket->reliability == UNRELIABLE_SEQUENCED ||
		internalPacket->reliability == RELIABLE_SEQUENCED ||
		internalPacket->reliability == RELIABLE_ORDERED ||
		internalPacket->reliability == RELIABLE_ORDERED_WITH_ACK_RECEIPT
		)
	{
		bitStream->Read(internalPacket->orderingIndex); // Used for UNRELIABLE_SEQUENCED, RELIABLE_SEQUENCED, RELIABLE_ORDERED. 4 bytes.
		readSuccess=bitStream->ReadAlignedVar8((char*)& internalPacket->orderingChannel); // Used for UNRELIABLE_SEQUENCED, RELIABLE_SEQUENCED, RELIABLE_ORDERED. 5 bits needed, Read one byte
	}
	else
		internalPacket->orderingChannel=0;

	if (hasSplitPacket)
	{
// 		printf("Read before\n");
// 		bitStream->PrintBits();

		bitStream->ReadAlignedVar32((char*)& internalPacket->splitPacketCount); // Only needed if splitPacketCount>0. 4 bytes
		bitStream->ReadAlignedVar16((char*)& internalPacket->splitPacketId); // Only needed if splitPacketCount>0.
		readSuccess=bitStream->ReadAlignedVar32((char*)& internalPacket->splitPacketIndex); // Only needed if splitPacketCount>0. 4 bytes
		RakAssert(readSuccess);

// 		printf("Read after\n");
// 		bitStream->PrintBits();
	}
	else
	{
		internalPacket->splitPacketCount=0;
	}

	if (readSuccess==false ||
		internalPacket->dataBitLength==0 ||
		internalPacket->reliability>=NUMBER_OF_RELIABILITIES ||
		internalPacket->orderingChannel>=32 || 
		(hasSplitPacket && (internalPacket->splitPacketIndex >= internalPacket->splitPacketCount)))
	{
		// If this assert hits, encoding is garbage
		RakAssert("Encoding is garbage" && 0);
		ReleaseToInternalPacketPool( internalPacket );
		return 0;
	}

	// Allocate memory to hold our data
	AllocInternalPacketData(internalPacket, BITS_TO_BYTES( internalPacket->dataBitLength ), false, _FILE_AND_LINE_ );
	RakAssert(BITS_TO_BYTES( internalPacket->dataBitLength )<MAXIMUM_MTU_SIZE);

	if (internalPacket->data == 0)
	{
		RakAssert("Out of memory in ReliabilityLayer::CreateInternalPacketFromBitStream" && 0);
		notifyOutOfMemory(_FILE_AND_LINE_);
		ReleaseToInternalPacketPool( internalPacket );
		return 0;
	}

	// Set the last byte to 0 so if ReadBits does not read a multiple of 8 the last bits are 0'ed out
	internalPacket->data[ BITS_TO_BYTES( internalPacket->dataBitLength ) - 1 ] = 0;

	// Read the data the packet holds
	bitStreamSucceeded = bitStream->ReadAlignedBytes( ( unsigned char* ) internalPacket->data, BITS_TO_BYTES( internalPacket->dataBitLength ) );

	if ( bitStreamSucceeded == false )
	{
		// If this hits, most likely the variable buff is too small in RunUpdateCycle in RakPeer.cpp
		RakAssert("Couldn't read all the data"  && 0);

		FreeInternalPacketData(internalPacket, _FILE_AND_LINE_ );
		ReleaseToInternalPacketPool( internalPacket );
		return 0;
	}

	return internalPacket;
}


//-------------------------------------------------------------------------------------------------------
// Get the SHA1 code
//-------------------------------------------------------------------------------------------------------
void ReliabilityLayer::GetSHA1( unsigned char * const buffer, unsigned int
							   nbytes, char code[ SHA1_LENGTH ] )
{
	CSHA1 sha1;

	sha1.Reset();
	sha1.Update( ( unsigned char* ) buffer, nbytes );
	sha1.Final();
	memcpy( code, sha1.GetHash(), SHA1_LENGTH );
}

//-------------------------------------------------------------------------------------------------------
// Check the SHA1 code
//-------------------------------------------------------------------------------------------------------
bool ReliabilityLayer::CheckSHA1( char code[ SHA1_LENGTH ], unsigned char *
								 const buffer, unsigned int nbytes )
{
	char code2[ SHA1_LENGTH ];
	GetSHA1( buffer, nbytes, code2 );

	for ( int i = 0; i < SHA1_LENGTH; i++ )
		if ( code[ i ] != code2[ i ] )
			return false;

	return true;
}

/*
//-------------------------------------------------------------------------------------------------------
// Search the specified list for sequenced packets on the specified ordering
// stream, optionally skipping those with splitPacketId, and delete them
//-------------------------------------------------------------------------------------------------------
void ReliabilityLayer::DeleteSequencedPacketsInList( unsigned char orderingChannel, DataStructures::List<InternalPacket*>&theList, int splitPacketId )
{
	unsigned i = 0;

	while ( i < theList.Size() )
	{
		if ( ( 
			theList[ i ]->reliability == RELIABLE_SEQUENCED ||
			theList[ i ]->reliability == UNRELIABLE_SEQUENCED 
//			||
//			theList[ i ]->reliability == RELIABLE_SEQUENCED_WITH_ACK_RECEIPT ||
//			theList[ i ]->reliability == UNRELIABLE_SEQUENCED_WITH_ACK_RECEIPT
			) &&
			theList[ i ]->orderingChannel == orderingChannel && ( splitPacketId == -1 || theList[ i ]->splitPacketId != (unsigned int) splitPacketId ) )
		{
			InternalPacket * internalPacket = theList[ i ];
			theList.RemoveAtIndex( i );
			FreeInternalPacketData(internalPacket, _FILE_AND_LINE_ );
			ReleaseToInternalPacketPool( internalPacket );
		}

		else
			i++;
	}
}

//-------------------------------------------------------------------------------------------------------
// Search the specified list for sequenced packets with a value less than orderingIndex and delete them
// Note - I added functionality so you can use the Queue as a list (in this case for searching) but it is less efficient to do so than a regular list
//-------------------------------------------------------------------------------------------------------
void ReliabilityLayer::DeleteSequencedPacketsInList( unsigned char orderingChannel, DataStructures::Queue<InternalPacket*>&theList )
{
	InternalPacket * internalPacket;
	int listSize = theList.Size();
	int i = 0;

	while ( i < listSize )
	{
		if ( (
			theList[ i ]->reliability == RELIABLE_SEQUENCED ||
			theList[ i ]->reliability == UNRELIABLE_SEQUENCED
//			||
//			theList[ i ]->reliability == RELIABLE_SEQUENCED_WITH_ACK_RECEIPT ||
//			theList[ i ]->reliability == UNRELIABLE_SEQUENCED_WITH_ACK_RECEIPT
			) && theList[ i ]->orderingChannel == orderingChannel )
		{
			internalPacket = theList[ i ];
			theList.RemoveAtIndex( i );
			FreeInternalPacketData(internalPacket, _FILE_AND_LINE_ );
			ReleaseToInternalPacketPool( internalPacket );
			listSize--;
		}

		else
			i++;
	}
}
*/

//-------------------------------------------------------------------------------------------------------
// Returns true if newPacketOrderingIndex is older than the waitingForPacketOrderingIndex
//-------------------------------------------------------------------------------------------------------
bool ReliabilityLayer::IsOlderOrderedPacket( OrderingIndexType newPacketOrderingIndex, OrderingIndexType waitingForPacketOrderingIndex )
{
	OrderingIndexType maxRange = (OrderingIndexType) (const uint32_t)-1;

	if ( waitingForPacketOrderingIndex > maxRange/(OrderingIndexType)2 )
	{
		if ( newPacketOrderingIndex >= waitingForPacketOrderingIndex - maxRange/(OrderingIndexType)2+(OrderingIndexType)1 && newPacketOrderingIndex < waitingForPacketOrderingIndex )
		{
			return true;
		}
	}

	else
		if ( newPacketOrderingIndex >= ( OrderingIndexType ) ( waitingForPacketOrderingIndex - (( OrderingIndexType ) maxRange/(OrderingIndexType)2+(OrderingIndexType)1) ) ||
			newPacketOrderingIndex < waitingForPacketOrderingIndex )
		{
			return true;
		}

		// Old packet
		return false;
}

//-------------------------------------------------------------------------------------------------------
// Split the passed packet into chunks under MTU_SIZEbytes (including headers) and save those new chunks
// Optimized version
//-------------------------------------------------------------------------------------------------------
void ReliabilityLayer::SplitPacket( InternalPacket *internalPacket )
{
	// Doing all sizes in bytes in this function so I don't write partial bytes with split packets
	internalPacket->splitPacketCount = 1; // This causes GetMessageHeaderLengthBits to account for the split packet header
	unsigned int headerLength = (unsigned int) BITS_TO_BYTES( GetMessageHeaderLengthBits( internalPacket ) );
	unsigned int dataByteLength = (unsigned int) BITS_TO_BYTES( internalPacket->dataBitLength );
	int maximumSendBlockBytes, byteOffset, bytesToSend;
	SplitPacketIndexType splitPacketIndex;
	int i;
	InternalPacket **internalPacketArray;

	maximumSendBlockBytes = GetMaxDatagramSizeExcludingMessageHeaderBytes() - BITS_TO_BYTES(GetMaxMessageHeaderLengthBits());

	// Calculate how many packets we need to create
	internalPacket->splitPacketCount = ( ( dataByteLength - 1 ) / ( maximumSendBlockBytes ) + 1 );

	// Optimization
	// internalPacketArray = SLNet::OP_NEW<InternalPacket*>(internalPacket->splitPacketCount, _FILE_AND_LINE_ );
	bool usedAlloca=false;
#if USE_ALLOCA==1
	if (sizeof( InternalPacket* ) * internalPacket->splitPacketCount < MAX_ALLOCA_STACK_ALLOCATION)
	{
		internalPacketArray = ( InternalPacket** ) alloca( sizeof( InternalPacket* ) * internalPacket->splitPacketCount );
		usedAlloca=true;
	}
	else
#endif
		internalPacketArray = (InternalPacket**) rakMalloc_Ex( sizeof(InternalPacket*) * internalPacket->splitPacketCount, _FILE_AND_LINE_ );

	for ( i = 0; i < ( int ) internalPacket->splitPacketCount; i++ )
	{
		internalPacketArray[ i ] = AllocateFromInternalPacketPool();

		//internalPacketArray[ i ] = (InternalPacket*) alloca( sizeof( InternalPacket ) );
		//		internalPacketArray[ i ] = sendPacketSet[internalPacket->priority].WriteLock();
		*internalPacketArray[ i ]=*internalPacket;
		internalPacketArray[ i ]->messageNumberAssigned=false;

		if (i!=0)
			internalPacket->messageInternalOrder = internalOrderIndex++;
	}

	// This identifies which packet this is in the set
	splitPacketIndex = 0;

	InternalPacketRefCountedData *refCounter=0;

	// Do a loop to send out all the packets
	do
	{
		byteOffset = splitPacketIndex * maximumSendBlockBytes;
		bytesToSend = dataByteLength - byteOffset;

		if ( bytesToSend > maximumSendBlockBytes )
			bytesToSend = maximumSendBlockBytes;

		// Copy over our chunk of data

		AllocInternalPacketData(internalPacketArray[ splitPacketIndex ], &refCounter, internalPacket->data, internalPacket->data + byteOffset);
		//		internalPacketArray[ splitPacketIndex ]->data = (unsigned char*) rakMalloc_Ex( bytesToSend, _FILE_AND_LINE_ );
		//		memcpy( internalPacketArray[ splitPacketIndex ]->data, internalPacket->data + byteOffset, bytesToSend );

		if ( bytesToSend != maximumSendBlockBytes )
			internalPacketArray[ splitPacketIndex ]->dataBitLength = internalPacket->dataBitLength - splitPacketIndex * ( maximumSendBlockBytes << 3 );
		else
			internalPacketArray[ splitPacketIndex ]->dataBitLength = bytesToSend << 3;

		internalPacketArray[ splitPacketIndex ]->splitPacketIndex = splitPacketIndex;
		internalPacketArray[ splitPacketIndex ]->splitPacketId = splitPacketId;
		internalPacketArray[ splitPacketIndex ]->splitPacketCount = internalPacket->splitPacketCount;
		RakAssert(internalPacketArray[ splitPacketIndex ]->dataBitLength<BYTES_TO_BITS(MAXIMUM_MTU_SIZE));
	} while ( ++splitPacketIndex < internalPacket->splitPacketCount );

	splitPacketId++; // It's ok if this wraps to 0

	//	InternalPacket *workingPacket;

	// Tell the heap we are going to push a list of elements where each element in the list follows the heap order
	RakAssert(outgoingPacketBuffer.Size()==0 || outgoingPacketBuffer.Peek()->dataBitLength<BYTES_TO_BITS(MAXIMUM_MTU_SIZE));
	outgoingPacketBuffer.StartSeries();

	// Copy all the new packets into the split packet list
	for ( i = 0; i < ( int ) internalPacket->splitPacketCount; i++ )
	{
		internalPacketArray[ i ]->headerLength=headerLength;
		RakAssert(internalPacketArray[ i ]->dataBitLength<BYTES_TO_BITS(MAXIMUM_MTU_SIZE));
		AddToUnreliableLinkedList(internalPacketArray[ i ]);
		//		sendPacketSet[ internalPacket->priority ].Push( internalPacketArray[ i ], _FILE_AND_LINE_  );
		RakAssert(internalPacketArray[ i ]->dataBitLength<BYTES_TO_BITS(MAXIMUM_MTU_SIZE));
		RakAssert(internalPacketArray[ i ]->messageNumberAssigned==false);
		outgoingPacketBuffer.PushSeries(GetNextWeight(internalPacketArray[ i ]->priority), internalPacketArray[ i ], _FILE_AND_LINE_);
		RakAssert(outgoingPacketBuffer.Size()==0 || outgoingPacketBuffer.Peek()->dataBitLength<BYTES_TO_BITS(MAXIMUM_MTU_SIZE));
		statistics.messageInSendBuffer[(int)internalPacketArray[ i ]->priority]++;
		statistics.bytesInSendBuffer[(int)(int)internalPacketArray[ i ]->priority]+=(double) BITS_TO_BYTES(internalPacketArray[ i ]->dataBitLength);
		//		workingPacket=sendPacketSet[internalPacket->priority].WriteLock();
		//		memcpy(workingPacket, internalPacketArray[ i ], sizeof(InternalPacket));
		//		sendPacketSet[internalPacket->priority].WriteUnlock();
	}

	// Do not delete, original is referenced by all split packets to avoid numerous allocations. See AllocInternalPacketData above
	//	FreeInternalPacketData(internalPacket, _FILE_AND_LINE_ );
	ReleaseToInternalPacketPool( internalPacket );

	if (usedAlloca==false)
		rakFree_Ex(internalPacketArray, _FILE_AND_LINE_ );
}

//-------------------------------------------------------------------------------------------------------
// Insert a packet into the split packet list
//-------------------------------------------------------------------------------------------------------
void ReliabilityLayer::InsertIntoSplitPacketList( InternalPacket * internalPacket, CCTimeType time )
{
	bool objectExists;
	unsigned index;
	// Find in splitPacketChannelList if a SplitPacketChannel with this splitPacketId was already allocated. If not, allocate and insert the channel into the list.
	index=splitPacketChannelList.GetIndexFromKey(internalPacket->splitPacketId, &objectExists);
	if (objectExists==false)
	{
		SplitPacketChannel *newChannel = SLNet::OP_NEW<SplitPacketChannel>( __FILE__, __LINE__ );
#if PREALLOCATE_LARGE_MESSAGES==1
		index=splitPacketChannelList.Insert(internalPacket->splitPacketId, newChannel, true, __FILE__,__LINE__);
		newChannel->returnedPacket=CreateInternalPacketCopy( internalPacket, 0, 0, time );
		newChannel->gotFirstPacket=false;
		newChannel->splitPacketsArrived=0;
		AllocInternalPacketData(newChannel->returnedPacket, BITS_TO_BYTES( internalPacket->dataBitLength*internalPacket->splitPacketCount ),  false, __FILE__, __LINE__ );
		RakAssert(newChannel->returnedPacket->data);
#else
		newChannel->firstPacket=0;
		index=splitPacketChannelList.Insert(internalPacket->splitPacketId, newChannel, true, __FILE__,__LINE__);
		// Preallocate to the final size, to avoid runtime copies
		newChannel->splitPacketList.Preallocate(internalPacket, __FILE__,__LINE__);

#endif
	}

#if PREALLOCATE_LARGE_MESSAGES==1
	splitPacketChannelList[index]->lastUpdateTime=time;
	splitPacketChannelList[index]->splitPacketsArrived++;
	splitPacketChannelList[index]->returnedPacket->dataBitLength+=internalPacket->dataBitLength;

	bool dealloc;
	if (internalPacket->splitPacketIndex==0)
	{
		splitPacketChannelList[index]->gotFirstPacket=true;
		splitPacketChannelList[index]->stride=BITS_TO_BYTES(internalPacket->dataBitLength);

		for (unsigned int j=0; j < splitPacketChannelList[index]->splitPacketList.Size(); j++)
		{
			memcpy(splitPacketChannelList[index]->returnedPacket->data+internalPacket->splitPacketIndex*splitPacketChannelList[index]->stride, internalPacket->data, (size_t) BITS_TO_BYTES(internalPacket->dataBitLength));
			FreeInternalPacketData(splitPacketChannelList[index]->splitPacketList[j], __FILE__, __LINE__ );
			ReleaseToInternalPacketPool(splitPacketChannelList[index]->splitPacketList[j]);
		}

		memcpy(splitPacketChannelList[index]->returnedPacket->data, internalPacket->data, (size_t) BITS_TO_BYTES(internalPacket->dataBitLength));
		splitPacketChannelList[index]->splitPacketList.Clear(true,__FILE__,__LINE__);
		dealloc=true;
	}
	else
	{
		if (splitPacketChannelList[index]->gotFirstPacket==true)
		{
			memcpy(splitPacketChannelList[index]->returnedPacket->data+internalPacket->splitPacketIndex*splitPacketChannelList[index]->stride, internalPacket->data, (size_t) BITS_TO_BYTES(internalPacket->dataBitLength));
			dealloc=true;
		}
		else
		{
			splitPacketChannelList[index]->splitPacketList.Push(internalPacket,__FILE__,__LINE__);
			dealloc=false;
		}
	}

	if (splitPacketChannelList[index]->gotFirstPacket==true &&
		splitMessageProgressInterval &&
		// 		splitPacketChannelList[index]->firstPacket &&
		// 		splitPacketChannelList[index]->splitPacketList.Size()!=splitPacketChannelList[index]->firstPacket->splitPacketCount &&
		// 		(splitPacketChannelList[index]->splitPacketList.Size()%splitMessageProgressInterval)==0
		splitPacketChannelList[index]->gotFirstPacket &&
		splitPacketChannelList[index]->splitPacketsArrived!=splitPacketChannelList[index]->returnedPacket->splitPacketCount &&
		(splitPacketChannelList[index]->splitPacketsArrived%splitMessageProgressInterval)==0
		)
	{
		// Return ID_DOWNLOAD_PROGRESS
		// Write splitPacketIndex (SplitPacketIndexType)
		// Write splitPacketCount (SplitPacketIndexType)
		// Write byteLength (4)
		// Write data, splitPacketChannelList[index]->splitPacketList[0]->data
		InternalPacket *progressIndicator = AllocateFromInternalPacketPool();
		//		unsigned int len = sizeof(MessageID) + sizeof(unsigned int)*2 + sizeof(unsigned int) + (unsigned int) BITS_TO_BYTES(splitPacketChannelList[index]->firstPacket->dataBitLength);
		unsigned int l = (unsigned int) splitPacketChannelList[index]->stride;
		const unsigned int len = sizeof(MessageID) + sizeof(unsigned int)*2 + sizeof(unsigned int) + l;
		AllocInternalPacketData(progressIndicator, len,  false, __FILE__, __LINE__ );
		progressIndicator->dataBitLength=BYTES_TO_BITS(len);
		progressIndicator->data[0]=(MessageID)ID_DOWNLOAD_PROGRESS;
		unsigned int temp;
		//	temp=splitPacketChannelList[index]->splitPacketList.Size();
		temp=splitPacketChannelList[index]->splitPacketsArrived;
		memcpy(progressIndicator->data+sizeof(MessageID), &temp, sizeof(unsigned int));
		temp=(unsigned int)internalPacket->splitPacketCount;
		memcpy(progressIndicator->data+sizeof(MessageID)+sizeof(unsigned int)*1, &temp, sizeof(unsigned int));
		//		temp=(unsigned int) BITS_TO_BYTES(splitPacketChannelList[index]->firstPacket->dataBitLength);
		temp=(unsigned int) BITS_TO_BYTES(l);
		memcpy(progressIndicator->data+sizeof(MessageID)+sizeof(unsigned int)*2, &temp, sizeof(unsigned int));
		//memcpy(progressIndicator->data+sizeof(MessageID)+sizeof(unsigned int)*3, splitPacketChannelList[index]->firstPacket->data, (size_t) BITS_TO_BYTES(splitPacketChannelList[index]->firstPacket->dataBitLength));
		memcpy(progressIndicator->data+sizeof(MessageID)+sizeof(unsigned int)*3, splitPacketChannelList[index]->returnedPacket->data, (size_t) BITS_TO_BYTES(l));
	}

	if (dealloc)
	{
		FreeInternalPacketData(internalPacket, __FILE__, __LINE__ );
		ReleaseToInternalPacketPool(internalPacket);
	}
#else
	// Insert the packet into the SplitPacketChannel
	if (!splitPacketChannelList[index]->splitPacketList.Add(internalPacket)) {
		FreeInternalPacketData(internalPacket, _FILE_AND_LINE_);
		ReleaseToInternalPacketPool(internalPacket);
		return;
	}

	splitPacketChannelList[index]->lastUpdateTime=time;

	// If the index is 0, then this is the first packet. Record this so it can be returned to the user with download progress
	if (internalPacket->splitPacketIndex==0)
		splitPacketChannelList[index]->firstPacket=internalPacket;
	
	// Return download progress if we have the first packet, the list is not complete, and there are enough packets to justify it
	if (splitMessageProgressInterval &&
		splitPacketChannelList[index]->firstPacket &&
		splitPacketChannelList[index]->splitPacketList.GetNumAddedPackets()!=splitPacketChannelList[index]->firstPacket->splitPacketCount &&
		(splitPacketChannelList[index]->splitPacketList.GetNumAddedPackets()%splitMessageProgressInterval)==0)
	{
		// Return ID_DOWNLOAD_PROGRESS
		// Write splitPacketIndex (SplitPacketIndexType)
		// Write splitPacketCount (SplitPacketIndexType)
		// Write byteLength (4)
		// Write data, splitPacketChannelList[index]->splitPacketList[0]->data
		InternalPacket *progressIndicator = AllocateFromInternalPacketPool();
		unsigned int length = sizeof(MessageID) + sizeof(unsigned int)*2 + sizeof(unsigned int) + (unsigned int) BITS_TO_BYTES(splitPacketChannelList[index]->firstPacket->dataBitLength);
		AllocInternalPacketData(progressIndicator, length,  false, __FILE__, __LINE__ );
		progressIndicator->dataBitLength=BYTES_TO_BITS(length);
		progressIndicator->data[0]=(MessageID)ID_DOWNLOAD_PROGRESS;
		unsigned int temp;
		temp=splitPacketChannelList[index]->splitPacketList.GetNumAddedPackets();
		memcpy(progressIndicator->data+sizeof(MessageID), &temp, sizeof(unsigned int));
		temp=(unsigned int)internalPacket->splitPacketCount;
		memcpy(progressIndicator->data+sizeof(MessageID)+sizeof(unsigned int)*1, &temp, sizeof(unsigned int));
		temp=(unsigned int) BITS_TO_BYTES(splitPacketChannelList[index]->firstPacket->dataBitLength);
		memcpy(progressIndicator->data+sizeof(MessageID)+sizeof(unsigned int)*2, &temp, sizeof(unsigned int));

		memcpy(progressIndicator->data+sizeof(MessageID)+sizeof(unsigned int)*3, splitPacketChannelList[index]->firstPacket->data, (size_t) BITS_TO_BYTES(splitPacketChannelList[index]->firstPacket->dataBitLength));
		outputQueue.Push(progressIndicator, __FILE__, __LINE__ );
	}

#endif
}

//-------------------------------------------------------------------------------------------------------
// Take all split chunks with the specified splitPacketId and try to
//reconstruct a packet.  If we can, allocate and return it.  Otherwise return 0
// Optimized version
//-------------------------------------------------------------------------------------------------------
InternalPacket * ReliabilityLayer::BuildPacketFromSplitPacketList( SplitPacketChannel *splitPacketChannel, CCTimeType time )
{
#if PREALLOCATE_LARGE_MESSAGES==1
	InternalPacket *returnedPacket=splitPacketChannel->returnedPacket;
	SLNet::OP_DELETE(splitPacketChannel, __FILE__, __LINE__);
	(void) time;
	return returnedPacket;
#else
	size_t j;
	InternalPacket * internalPacket, *splitPacket;
	// int splitPacketPartLength;

	// Reconstruct
	internalPacket = CreateInternalPacketCopy( splitPacketChannel->splitPacketList[0], 0, 0, time );
	internalPacket->dataBitLength=0;
	for (j=0; j < splitPacketChannel->splitPacketList.GetAllocSize(); j++)
		internalPacket->dataBitLength+=splitPacketChannel->splitPacketList[j]->dataBitLength;
	// splitPacketPartLength=BITS_TO_BYTES(splitPacketChannel->firstPacket->dataBitLength);

	internalPacket->data = (unsigned char*) rakMalloc_Ex( (size_t) BITS_TO_BYTES( internalPacket->dataBitLength ), _FILE_AND_LINE_ );
	internalPacket->allocationScheme=InternalPacket::NORMAL;

    BitSize_t offset = 0;
	for (j=0; j < splitPacketChannel->splitPacketList.GetAllocSize(); j++)
	{
		splitPacket = splitPacketChannel->splitPacketList[j];
		memcpy(internalPacket->data + BITS_TO_BYTES(offset), splitPacket->data, (size_t)BITS_TO_BYTES(splitPacket->dataBitLength));
		offset += splitPacket->dataBitLength;
	}

	for (j=0; j < splitPacketChannel->splitPacketList.GetAllocSize(); j++)
	{
		FreeInternalPacketData(splitPacketChannel->splitPacketList[j], _FILE_AND_LINE_ );
		ReleaseToInternalPacketPool(splitPacketChannel->splitPacketList[j]);
	}
	SLNet::OP_DELETE(splitPacketChannel, __FILE__, __LINE__);

	return internalPacket;
#endif
}
//-------------------------------------------------------------------------------------------------------
InternalPacket * ReliabilityLayer::BuildPacketFromSplitPacketList( SplitPacketIdType inSplitPacketId, CCTimeType time,
																  RakNetSocket2 *s, SystemAddress &systemAddress, RakNetRandom *rnr, 
																  BitStream &updateBitStream)
{
	unsigned int i;
	bool objectExists;
	SplitPacketChannel *splitPacketChannel;
	InternalPacket * internalPacket;

	// Find in splitPacketChannelList the SplitPacketChannel with this splitPacketId
	i=splitPacketChannelList.GetIndexFromKey(inSplitPacketId, &objectExists);
	splitPacketChannel=splitPacketChannelList[i];
	
#if PREALLOCATE_LARGE_MESSAGES==1
	if (splitPacketChannel->splitPacketsArrived==splitPacketChannel->returnedPacket->splitPacketCount)
#else
	if (splitPacketChannel->splitPacketList.AllPacketsAdded())
#endif
	{
		// Ack immediately, because for large files this can take a long time
		SendACKs(s, systemAddress, time, rnr, updateBitStream);
		internalPacket=BuildPacketFromSplitPacketList(splitPacketChannel,time);
		splitPacketChannelList.RemoveAtIndex(i);
		return internalPacket;
	}
	else
	{
		return 0;
	}
}
/*
//-------------------------------------------------------------------------------------------------------
// Delete any unreliable split packets that have long since expired
void ReliabilityLayer::DeleteOldUnreliableSplitPackets( CCTimeType time )
{
unsigned i,j;
i=0;
while (i < splitPacketChannelList.Size())
{
#if CC_TIME_TYPE_BYTES==4
if (time > splitPacketChannelList[i]->lastUpdateTime + timeoutTime &&
#else
if (time > splitPacketChannelList[i]->lastUpdateTime + (CCTimeType)timeoutTime*(CCTimeType)1000 &&
#endif
(splitPacketChannelList[i]->splitPacketList[0]->reliability==UNRELIABLE || splitPacketChannelList[i]->splitPacketList[0]->reliability==UNRELIABLE_SEQUENCED))
{
for (j=0; j < splitPacketChannelList[i]->splitPacketList.Size(); j++)
{
SLNet::OP_DELETE_ARRAY(splitPacketChannelList[i]->splitPacketList[j]->data, _FILE_AND_LINE_);
ReleaseToInternalPacketPool(splitPacketChannelList[i]->splitPacketList[j]);
}
SLNet::OP_DELETE(splitPacketChannelList[i], _FILE_AND_LINE_);
splitPacketChannelList.RemoveAtIndex(i);
}
else
i++;
}
}
*/

//-------------------------------------------------------------------------------------------------------
// Creates a copy of the specified internal packet with data copied from the original starting at dataByteOffset for dataByteLength bytes.
// Does not copy any split data parameters as that information is always generated does not have any reason to be copied
//-------------------------------------------------------------------------------------------------------
InternalPacket * ReliabilityLayer::CreateInternalPacketCopy( InternalPacket *original, int dataByteOffset, int dataByteLength, CCTimeType time )
{
	InternalPacket * copy = AllocateFromInternalPacketPool();
#ifdef _DEBUG
	// Remove accessing undefined memory error
	memset( copy, 255, sizeof( InternalPacket ) );
#endif
	// Copy over our chunk of data

	if ( dataByteLength > 0 )
	{
		AllocInternalPacketData(copy, BITS_TO_BYTES(dataByteLength ),  false, _FILE_AND_LINE_ );
		memcpy( copy->data, original->data + dataByteOffset, dataByteLength );
	}
	else
		copy->data = 0;

	copy->dataBitLength = dataByteLength << 3;
	copy->creationTime = time;
	copy->nextActionTime = 0;
	copy->orderingIndex = original->orderingIndex;
	copy->sequencingIndex = original->sequencingIndex;
	copy->orderingChannel = original->orderingChannel;
	copy->reliableMessageNumber = original->reliableMessageNumber;
	copy->priority = original->priority;
	copy->reliability = original->reliability;
#if PREALLOCATE_LARGE_MESSAGES==1
	copy->splitPacketCount = original->splitPacketCount;
	copy->splitPacketId = original->splitPacketId;
	copy->splitPacketIndex = original->splitPacketIndex;
#endif

	return copy;
}

//-------------------------------------------------------------------------------------------------------
// Get the specified ordering list
//-------------------------------------------------------------------------------------------------------
/*
DataStructures::LinkedList<InternalPacket*> *ReliabilityLayer::GetOrderingListAtOrderingStream( unsigned char orderingChannel )
{
	if ( orderingChannel >= orderingList.Size() )
		return 0;

	return orderingList[ orderingChannel ];
}

//-------------------------------------------------------------------------------------------------------
// Add the internal packet to the ordering list in order based on order index
//-------------------------------------------------------------------------------------------------------
void ReliabilityLayer::AddToOrderingList( InternalPacket * internalPacket )
{
	}
*/

//-------------------------------------------------------------------------------------------------------
// Inserts a packet into the resend list in order
//-------------------------------------------------------------------------------------------------------
void ReliabilityLayer::InsertPacketIntoResendList( InternalPacket *internalPacket, CCTimeType time, bool firstResend, bool modifyUnacknowledgedBytes )
{
	(void) firstResend;
	(void) time;
	(void) internalPacket;

	AddToListTail(internalPacket, modifyUnacknowledgedBytes);
	RakAssert(internalPacket->nextActionTime!=0);

}

//-------------------------------------------------------------------------------------------------------
//  Were you ever unable to deliver a packet despite retries?
//-------------------------------------------------------------------------------------------------------
bool ReliabilityLayer::IsDeadConnection( void ) const
{
	return deadConnection;
}

//-------------------------------------------------------------------------------------------------------
//  Causes IsDeadConnection to return true
//-------------------------------------------------------------------------------------------------------
void ReliabilityLayer::KillConnection( void )
{
	deadConnection=true;
}


//-------------------------------------------------------------------------------------------------------
// Statistics
//-------------------------------------------------------------------------------------------------------
RakNetStatistics * ReliabilityLayer::GetStatistics( RakNetStatistics *rns )
{
	unsigned i;
	SLNet::TimeUS time = SLNet::GetTimeUS();
	uint64_t uint64Denominator;
	double doubleDenominator;

	for (i=0; i < RNS_PER_SECOND_METRICS_COUNT; i++)
	{
		statistics.valueOverLastSecond[i]=bpsMetrics[i].GetBPS1Threadsafe(time);
		statistics.runningTotal[i]=bpsMetrics[i].GetTotal1();
	}

	memcpy(rns, &statistics, sizeof(statistics));

	if (rns->valueOverLastSecond[USER_MESSAGE_BYTES_SENT]+rns->valueOverLastSecond[USER_MESSAGE_BYTES_RESENT]>0)
		rns->packetlossLastSecond=(float)((double) rns->valueOverLastSecond[USER_MESSAGE_BYTES_RESENT]/((double) rns->valueOverLastSecond[USER_MESSAGE_BYTES_SENT]+(double) rns->valueOverLastSecond[USER_MESSAGE_BYTES_RESENT]));
	else
		rns->packetlossLastSecond=0.0f;

	rns->packetlossTotal=0.0f;
	uint64Denominator=(rns->runningTotal[USER_MESSAGE_BYTES_SENT]+rns->runningTotal[USER_MESSAGE_BYTES_RESENT]);
	if (uint64Denominator!=0&&rns->runningTotal[USER_MESSAGE_BYTES_SENT]/uint64Denominator>0)
	{
		doubleDenominator=((double) rns->runningTotal[USER_MESSAGE_BYTES_SENT]+(double) rns->runningTotal[USER_MESSAGE_BYTES_RESENT]);
		if(doubleDenominator!=0)
		{
			rns->packetlossTotal=(float)((double) rns->runningTotal[USER_MESSAGE_BYTES_RESENT]/doubleDenominator);
		}
	}

	rns->isLimitedByCongestionControl=statistics.isLimitedByCongestionControl;
	rns->BPSLimitByCongestionControl=statistics.BPSLimitByCongestionControl;
	rns->isLimitedByOutgoingBandwidthLimit=statistics.isLimitedByOutgoingBandwidthLimit;
	rns->BPSLimitByOutgoingBandwidthLimit=statistics.BPSLimitByOutgoingBandwidthLimit;

	return rns;
}

//-------------------------------------------------------------------------------------------------------
// Returns the number of packets in the resend queue, not counting holes
//-------------------------------------------------------------------------------------------------------
unsigned int ReliabilityLayer::GetResendListDataSize(void) const
{
	// Not accurate but thread-safe.  The commented version might crash if the queue is cleared while we loop through it
	// return resendTree.Size();
	return statistics.messagesInResendBuffer;
}

//-------------------------------------------------------------------------------------------------------
bool ReliabilityLayer::AckTimeout(SLNet::Time curTime)
{
	// I check timeLastDatagramArrived-curTime because with threading it is possible that timeLastDatagramArrived is
	// slightly greater than curTime, in which case this is NOT an ack timeout
	return (timeLastDatagramArrived-curTime)>10000 && curTime-timeLastDatagramArrived>timeoutTime;
}
//-------------------------------------------------------------------------------------------------------
CCTimeType ReliabilityLayer::GetNextSendTime(void) const
{
	return nextSendTime;
}
//-------------------------------------------------------------------------------------------------------
CCTimeType ReliabilityLayer::GetTimeBetweenPackets(void) const
{
	return timeBetweenPackets;
}
//-------------------------------------------------------------------------------------------------------
#if INCLUDE_TIMESTAMP_WITH_DATAGRAMS==1
CCTimeType ReliabilityLayer::GetAckPing(void) const
{
	return ackPing;
}
#endif
//-------------------------------------------------------------------------------------------------------
void ReliabilityLayer::ResetPacketsAndDatagrams(void)
{
	packetsToSendThisUpdate.Clear(true, _FILE_AND_LINE_);
	packetsToDeallocThisUpdate.Clear(true, _FILE_AND_LINE_);
	packetsToSendThisUpdateDatagramBoundaries.Clear(true, _FILE_AND_LINE_);
	datagramsToSendThisUpdateIsPair.Clear(true, _FILE_AND_LINE_);
	datagramSizesInBytes.Clear(true, _FILE_AND_LINE_);
	datagramSizeSoFar=0;
}
//-------------------------------------------------------------------------------------------------------
void ReliabilityLayer::PushPacket(CCTimeType time, InternalPacket *internalPacket, bool isReliable)
{
	BitSize_t bitsForThisPacket=BYTES_TO_BITS(BITS_TO_BYTES(internalPacket->dataBitLength)+BITS_TO_BYTES(internalPacket->headerLength));
	datagramSizeSoFar+=bitsForThisPacket;
	RakAssert(BITS_TO_BYTES(datagramSizeSoFar)<MAXIMUM_MTU_SIZE-UDP_HEADER_SIZE);
	allDatagramSizesSoFar+=bitsForThisPacket;
	packetsToSendThisUpdate.Push(internalPacket, _FILE_AND_LINE_ );
	packetsToDeallocThisUpdate.Push(isReliable==false, _FILE_AND_LINE_ );
	RakAssert(internalPacket->headerLength==GetMessageHeaderLengthBits(internalPacket));

// This code tells me how much time elapses between when you send, and when the message actually goes out
// 	if (internalPacket->data[0]==0)
// 	{
// 		SLNet::TimeMS t;
// 		SLNet::BitStream bs(internalPacket->data+1,sizeof(t),false);
// 		bs.Read(t);
// 		SLNet::TimeMS curTime=SLNet::GetTimeMS();
// 		SLNet::TimeMS diff = curTime-t;
// 	}

	congestionManager.OnSendBytes(time, BITS_TO_BYTES(internalPacket->dataBitLength)+BITS_TO_BYTES(internalPacket->headerLength));
}
//-------------------------------------------------------------------------------------------------------
void ReliabilityLayer::PushDatagram(void)
{
	if (datagramSizeSoFar>0)
	{
		packetsToSendThisUpdateDatagramBoundaries.Push(packetsToSendThisUpdate.Size(), _FILE_AND_LINE_ );
		datagramsToSendThisUpdateIsPair.Push(false, _FILE_AND_LINE_ );
		RakAssert(BITS_TO_BYTES(datagramSizeSoFar)<MAXIMUM_MTU_SIZE-UDP_HEADER_SIZE);
		datagramSizesInBytes.Push(BITS_TO_BYTES(datagramSizeSoFar), _FILE_AND_LINE_ );
		datagramSizeSoFar=0;

		// Disable packet pairs
		/*
		if (countdownToNextPacketPair==0)
		{
		if (TagMostRecentPushAsSecondOfPacketPair())
		countdownToNextPacketPair=15;
		}
		else
		countdownToNextPacketPair--;
		*/
	}
}
//-------------------------------------------------------------------------------------------------------
bool ReliabilityLayer::TagMostRecentPushAsSecondOfPacketPair(void)
{
	if (datagramsToSendThisUpdateIsPair.Size()>=2)
	{
		datagramsToSendThisUpdateIsPair[datagramsToSendThisUpdateIsPair.Size()-2]=true;
		datagramsToSendThisUpdateIsPair[datagramsToSendThisUpdateIsPair.Size()-1]=true;
		return true;
	}
	return false;
}
//-------------------------------------------------------------------------------------------------------
void ReliabilityLayer::ClearPacketsAndDatagrams(void)
{
	unsigned int i;
	for (i=0; i < packetsToDeallocThisUpdate.Size(); i++)
	{
		// packetsToDeallocThisUpdate holds a boolean indicating if packetsToSendThisUpdate at this index should be freed
		if (packetsToDeallocThisUpdate[i])
		{
			RemoveFromUnreliableLinkedList(packetsToSendThisUpdate[i]);
			FreeInternalPacketData(packetsToSendThisUpdate[i], _FILE_AND_LINE_ );
			// if (keepInternalPacketIfNeedsAck==false || packetsToSendThisUpdate[i]->reliability<RELIABLE_WITH_ACK_RECEIPT)
			ReleaseToInternalPacketPool( packetsToSendThisUpdate[i] );
		}
	}
	packetsToDeallocThisUpdate.Clear(true, _FILE_AND_LINE_);
}
//-------------------------------------------------------------------------------------------------------
void ReliabilityLayer::MoveToListHead(InternalPacket *internalPacket)
{
	if ( internalPacket == resendLinkedListHead )
		return;
	if (resendLinkedListHead==0)
	{
		internalPacket->resendNext=internalPacket;
		internalPacket->resendPrev=internalPacket;
		resendLinkedListHead=internalPacket;
		return;
	}
	internalPacket->resendPrev->resendNext = internalPacket->resendNext;
	internalPacket->resendNext->resendPrev = internalPacket->resendPrev;
	internalPacket->resendNext=resendLinkedListHead;
	internalPacket->resendPrev=resendLinkedListHead->resendPrev;
	internalPacket->resendPrev->resendNext=internalPacket;
	resendLinkedListHead->resendPrev=internalPacket;
	resendLinkedListHead=internalPacket;
	RakAssert(internalPacket->headerLength+internalPacket->dataBitLength>0);

	//ValidateResendList();
}
//-------------------------------------------------------------------------------------------------------
void ReliabilityLayer::RemoveFromList(InternalPacket *internalPacket, bool modifyUnacknowledgedBytes)
{
	InternalPacket *newPosition;
	internalPacket->resendPrev->resendNext = internalPacket->resendNext;
	internalPacket->resendNext->resendPrev = internalPacket->resendPrev;
	newPosition = internalPacket->resendNext;
	if ( internalPacket == resendLinkedListHead )
		resendLinkedListHead = newPosition;
	if (resendLinkedListHead==internalPacket)
		resendLinkedListHead=0;

	if (modifyUnacknowledgedBytes)
	{
		RakAssert(unacknowledgedBytes>=BITS_TO_BYTES(internalPacket->headerLength+internalPacket->dataBitLength));
		unacknowledgedBytes-=BITS_TO_BYTES(internalPacket->headerLength+internalPacket->dataBitLength);
		// printf("-unacknowledgedBytes:%i ", unacknowledgedBytes);


//		ValidateResendList();
	}
}
//-------------------------------------------------------------------------------------------------------
void ReliabilityLayer::AddToListTail(InternalPacket *internalPacket, bool modifyUnacknowledgedBytes)
{
	if (modifyUnacknowledgedBytes)
	{
		unacknowledgedBytes+=BITS_TO_BYTES(internalPacket->headerLength+internalPacket->dataBitLength);
		// printf("+unacknowledgedBytes:%i ", unacknowledgedBytes);
	}

	if (resendLinkedListHead==0)
	{
		internalPacket->resendNext=internalPacket;
		internalPacket->resendPrev=internalPacket;
		resendLinkedListHead=internalPacket;
		return;
	}
	internalPacket->resendNext=resendLinkedListHead;
	internalPacket->resendPrev=resendLinkedListHead->resendPrev;
	internalPacket->resendPrev->resendNext=internalPacket;
	resendLinkedListHead->resendPrev=internalPacket;

//	ValidateResendList();

}
//-------------------------------------------------------------------------------------------------------
void ReliabilityLayer::PopListHead(bool modifyUnacknowledgedBytes)
{
	RakAssert(resendLinkedListHead!=0);
	RemoveFromList(resendLinkedListHead, modifyUnacknowledgedBytes);
}
//-------------------------------------------------------------------------------------------------------
bool ReliabilityLayer::IsResendQueueEmpty(void) const
{
	return resendLinkedListHead==0;
}
//-------------------------------------------------------------------------------------------------------
void ReliabilityLayer::SendACKs(RakNetSocket2 *s, SystemAddress &systemAddress, CCTimeType time, RakNetRandom *rnr, BitStream &updateBitStream)
{
	BitSize_t maxDatagramPayload = GetMaxDatagramSizeExcludingMessageHeaderBits();

	while (acknowlegements.Size()>0)
	{
		// Send acks
		updateBitStream.Reset();
		DatagramHeaderFormat dhf;
		dhf.isACK=true;
		dhf.isNAK=false;
		dhf.isPacketPair=false;
#if INCLUDE_TIMESTAMP_WITH_DATAGRAMS==1
		dhf.sourceSystemTime=time;
#endif
		double B;
		double AS;
		bool hasBAndAS;
		if (remoteSystemNeedsBAndAS)
		{
			congestionManager.OnSendAckGetBAndAS(time, &hasBAndAS,&B,&AS);
			dhf.AS=(float)AS;
			dhf.hasBAndAS=hasBAndAS;
		}
		else
			dhf.hasBAndAS=false;
#if INCLUDE_TIMESTAMP_WITH_DATAGRAMS==1
		dhf.sourceSystemTime=nextAckTimeToSend;
#endif
		//		dhf.B=(float)B;
		updateBitStream.Reset();
		dhf.Serialize(&updateBitStream);
		CC_DEBUG_PRINTF_1("AckSnd ");
		acknowlegements.Serialize(&updateBitStream, maxDatagramPayload, true);
		SendBitStream( s, systemAddress, &updateBitStream, rnr, time );
		congestionManager.OnSendAck(time,updateBitStream.GetNumberOfBytesUsed());

		// I think this is causing a bug where if the estimated bandwidth is very low for the recipient, only acks ever get sent
		//	congestionManager.OnSendBytes(time,UDP_HEADER_SIZE+updateBitStream.GetNumberOfBytesUsed());
	}
}
/*
//-------------------------------------------------------------------------------------------------------
ReliabilityLayer::DatagramMessageIDList* ReliabilityLayer::AllocateFromDatagramMessageIDPool(void)
{
DatagramMessageIDList*s;
s=datagramMessageIDPool.Allocate( _FILE_AND_LINE_ );
// Call new operator, memoryPool doesn't do this
s = new ((void*)s) DatagramMessageIDList;
return s;
}
//-------------------------------------------------------------------------------------------------------
void ReliabilityLayer::ReleaseToDatagramMessageIDPool(DatagramMessageIDList* d)
{
d->~DatagramMessageIDList();
datagramMessageIDPool.Release(d);
}
*/
//-------------------------------------------------------------------------------------------------------
InternalPacket* ReliabilityLayer::AllocateFromInternalPacketPool(void)
{
	InternalPacket *ip = internalPacketPool.Allocate( _FILE_AND_LINE_ );
	ip->reliableMessageNumber = (MessageNumberType) (const uint32_t)-1;
	ip->messageNumberAssigned=false;
	ip->nextActionTime = 0;
	ip->splitPacketCount = 0;
	ip->splitPacketIndex = 0;
	ip->splitPacketId = 0;
	ip->allocationScheme=InternalPacket::NORMAL;
	ip->data=0;
	ip->timesSent=0;
	return ip;
}
//-------------------------------------------------------------------------------------------------------
void ReliabilityLayer::ReleaseToInternalPacketPool(InternalPacket *ip)
{
	internalPacketPool.Release(ip, _FILE_AND_LINE_);
}
//-------------------------------------------------------------------------------------------------------
void ReliabilityLayer::RemoveFromUnreliableLinkedList(InternalPacket *internalPacket)
{
	if (internalPacket->reliability==UNRELIABLE ||
		internalPacket->reliability==UNRELIABLE_SEQUENCED ||
		internalPacket->reliability==UNRELIABLE_WITH_ACK_RECEIPT
//		||
//		internalPacket->reliability==UNRELIABLE_SEQUENCED_WITH_ACK_RECEIPT
		)
	{
		InternalPacket *newPosition;
		internalPacket->unreliablePrev->unreliableNext = internalPacket->unreliableNext;
		internalPacket->unreliableNext->unreliablePrev = internalPacket->unreliablePrev;
		newPosition = internalPacket->unreliableNext;
		if ( internalPacket == unreliableLinkedListHead )
			unreliableLinkedListHead = newPosition;
		if (unreliableLinkedListHead==internalPacket)
			unreliableLinkedListHead=0;
	}
}
//-------------------------------------------------------------------------------------------------------
void ReliabilityLayer::AddToUnreliableLinkedList(InternalPacket *internalPacket)
{
	if (internalPacket->reliability==UNRELIABLE ||
		internalPacket->reliability==UNRELIABLE_SEQUENCED ||
		internalPacket->reliability==UNRELIABLE_WITH_ACK_RECEIPT
//		||
//		internalPacket->reliability==UNRELIABLE_SEQUENCED_WITH_ACK_RECEIPT
		)
	{
		if (unreliableLinkedListHead==0)
		{
			internalPacket->unreliableNext=internalPacket;
			internalPacket->unreliablePrev=internalPacket;
			unreliableLinkedListHead=internalPacket;
			return;
		}
		internalPacket->unreliableNext=unreliableLinkedListHead;
		internalPacket->unreliablePrev=unreliableLinkedListHead->unreliablePrev;
		internalPacket->unreliablePrev->unreliableNext=internalPacket;
		unreliableLinkedListHead->unreliablePrev=internalPacket;
	}
}
//-------------------------------------------------------------------------------------------------------
void ReliabilityLayer::ValidateResendList(void) const
{
// 	unsigned int count1=0, count2=0;
// 	for (unsigned int i=0; i < RESEND_BUFFER_ARRAY_LENGTH; i++)
// 	if (resendBuffer[i])
// 	count1++;
// 
// 	if (resendLinkedListHead)
// 	{
// 	InternalPacket *internalPacket = resendLinkedListHead;
// 	do 
// 	{
// 	count2++;
// 	internalPacket=internalPacket->resendNext;
// 	} while (internalPacket!=resendLinkedListHead);
// 	}
// 	RakAssert(count1==count2);
// 	RakAssert(count2<=RESEND_BUFFER_ARRAY_LENGTH);
}
//-------------------------------------------------------------------------------------------------------
bool ReliabilityLayer::ResendBufferOverflow(void) const
{
	int index1 = sendReliableMessageNumberIndex & (uint32_t) RESEND_BUFFER_ARRAY_MASK;
	//	int index2 = (sendReliableMessageNumberIndex+(uint32_t)1) & (uint32_t) RESEND_BUFFER_ARRAY_MASK;
	RakAssert(index1<RESEND_BUFFER_ARRAY_LENGTH);
	return resendBuffer[index1]!=0; // || resendBuffer[index2]!=0;

}
//-------------------------------------------------------------------------------------------------------
ReliabilityLayer::MessageNumberNode* ReliabilityLayer::GetMessageNumberNodeByDatagramIndex(DatagramSequenceNumberType index, CCTimeType *timeSent)
{
	if (datagramHistory.IsEmpty())
		return nullptr;

	if (congestionManager.LessThan(index, datagramHistoryPopCount))
		return nullptr;

	DatagramSequenceNumberType offsetIntoList = index - datagramHistoryPopCount;
	if (offsetIntoList >= datagramHistory.Size())
		return nullptr;

	*timeSent=datagramHistory[offsetIntoList].timeSent;
	return datagramHistory[offsetIntoList].head;
}
//-------------------------------------------------------------------------------------------------------
void ReliabilityLayer::RemoveFromDatagramHistory(DatagramSequenceNumberType index)
{
	DatagramSequenceNumberType offsetIntoList = index - datagramHistoryPopCount;
	MessageNumberNode *mnm = datagramHistory[offsetIntoList].head;
	MessageNumberNode *next;
	while (mnm)
	{
		next=mnm->next;
		datagramHistoryMessagePool.Release(mnm, _FILE_AND_LINE_);
		mnm=next;
	}
	datagramHistory[offsetIntoList].head=0;
}
//-------------------------------------------------------------------------------------------------------
void ReliabilityLayer::AddFirstToDatagramHistory(DatagramSequenceNumberType datagramNumber, CCTimeType timeSent)
{
	(void) datagramNumber;
	if (datagramHistory.Size()>DATAGRAM_MESSAGE_ID_ARRAY_LENGTH)
	{
		RemoveFromDatagramHistory(datagramHistoryPopCount);
		datagramHistory.Pop();
		datagramHistoryPopCount++;
	}

	datagramHistory.Push(DatagramHistoryNode(0, timeSent), _FILE_AND_LINE_);
	// printf("%p Pushed empty DatagramHistoryNode to datagram history at index %i\n", this, datagramHistory.Size()-1);
}
//-------------------------------------------------------------------------------------------------------
ReliabilityLayer::MessageNumberNode* ReliabilityLayer::AddFirstToDatagramHistory(DatagramSequenceNumberType datagramNumber, DatagramSequenceNumberType messageNumber, CCTimeType timeSent)
{
	(void) datagramNumber;
//	RakAssert(datagramHistoryPopCount+(unsigned int) datagramHistory.Size()==datagramNumber);
	if (datagramHistory.Size()>DATAGRAM_MESSAGE_ID_ARRAY_LENGTH)
	{
		RemoveFromDatagramHistory(datagramHistoryPopCount);
		datagramHistory.Pop();
		datagramHistoryPopCount++;
	}

	MessageNumberNode *mnm = datagramHistoryMessagePool.Allocate(_FILE_AND_LINE_);
	mnm->next=0;
	mnm->messageNumber=messageNumber;
	datagramHistory.Push(DatagramHistoryNode(mnm, timeSent), _FILE_AND_LINE_);
	// printf("%p Pushed message %i to DatagramHistoryNode to datagram history at index %i\n", this, messageNumber.val, datagramHistory.Size()-1);
	return mnm;
}
//-------------------------------------------------------------------------------------------------------
ReliabilityLayer::MessageNumberNode* ReliabilityLayer::AddSubsequentToDatagramHistory(MessageNumberNode *messageNumberNode, DatagramSequenceNumberType messageNumber)
{
	messageNumberNode->next=datagramHistoryMessagePool.Allocate(_FILE_AND_LINE_);
	messageNumberNode->next->messageNumber=messageNumber;
	messageNumberNode->next->next=0;
	return messageNumberNode->next;		
}
//-------------------------------------------------------------------------------------------------------
void ReliabilityLayer::AllocInternalPacketData(InternalPacket *internalPacket, InternalPacketRefCountedData **refCounter, unsigned char *externallyAllocatedPtr, unsigned char *ourOffset)
{
	internalPacket->allocationScheme=InternalPacket::REF_COUNTED;
	internalPacket->data=ourOffset;
	if (*refCounter==0)
	{
		*refCounter = refCountedDataPool.Allocate(_FILE_AND_LINE_);
		// *refCounter = SLNet::OP_NEW<InternalPacketRefCountedData>(_FILE_AND_LINE_);
		(*refCounter)->refCount=1;
		(*refCounter)->sharedDataBlock=externallyAllocatedPtr;
	}
	else
		(*refCounter)->refCount++;
	internalPacket->refCountedData=(*refCounter);
}
//-------------------------------------------------------------------------------------------------------
void ReliabilityLayer::AllocInternalPacketData(InternalPacket *internalPacket, unsigned char *externallyAllocatedPtr)
{
	internalPacket->allocationScheme=InternalPacket::NORMAL;
	internalPacket->data=externallyAllocatedPtr;
}
//-------------------------------------------------------------------------------------------------------
void ReliabilityLayer::AllocInternalPacketData(InternalPacket *internalPacket, unsigned int numBytes, bool allowStack, const char *file, unsigned int line)
{
	if (allowStack && numBytes <= sizeof(internalPacket->stackData))
	{
		internalPacket->allocationScheme=InternalPacket::STACK;
		internalPacket->data=internalPacket->stackData;
	}
	else
	{
		internalPacket->allocationScheme=InternalPacket::NORMAL;
		internalPacket->data=(unsigned char*) rakMalloc_Ex(numBytes,file,line);
	}
}
//-------------------------------------------------------------------------------------------------------
void ReliabilityLayer::FreeInternalPacketData(InternalPacket *internalPacket, const char *file, unsigned int line)
{
	if (internalPacket==0)
		return;

	if (internalPacket->allocationScheme==InternalPacket::REF_COUNTED)
	{
		if (internalPacket->refCountedData==0)
			return;

		internalPacket->refCountedData->refCount--;
		if (internalPacket->refCountedData->refCount==0)
		{
			rakFree_Ex(internalPacket->refCountedData->sharedDataBlock, file, line );
			internalPacket->refCountedData->sharedDataBlock=0;
			// SLNet::OP_DELETE(internalPacket->refCountedData,file, line);
			refCountedDataPool.Release(internalPacket->refCountedData,file, line);
			internalPacket->refCountedData=0;
		}
	}
	else if (internalPacket->allocationScheme==InternalPacket::NORMAL)
	{
		if (internalPacket->data==0)
			return;

		rakFree_Ex(internalPacket->data, file, line );
		internalPacket->data=0;
	}
	else
	{
		// Data was on stack
		internalPacket->data=0;
	}
}
//-------------------------------------------------------------------------------------------------------
unsigned int ReliabilityLayer::GetMaxDatagramSizeExcludingMessageHeaderBytes(void)
{
	unsigned int val = congestionManager.GetMTU() - DatagramHeaderFormat::GetDataHeaderByteLength();

#if LIBCAT_SECURITY==1
	if (useSecurity)
		val -= cat::AuthenticatedEncryption::OVERHEAD_BYTES;
#endif

	return val;
}
//-------------------------------------------------------------------------------------------------------
BitSize_t ReliabilityLayer::GetMaxDatagramSizeExcludingMessageHeaderBits(void)
{
	return BYTES_TO_BITS(GetMaxDatagramSizeExcludingMessageHeaderBytes());
}
//-------------------------------------------------------------------------------------------------------
void ReliabilityLayer::InitHeapWeights(void)
{
	for (int priorityLevel=0; priorityLevel < NUMBER_OF_PRIORITIES; priorityLevel++)
		outgoingPacketBufferNextWeights[priorityLevel]=(1<<priorityLevel)*priorityLevel+priorityLevel;
}
//-------------------------------------------------------------------------------------------------------
reliabilityHeapWeightType ReliabilityLayer::GetNextWeight(int priorityLevel)
{
	uint64_t next = outgoingPacketBufferNextWeights[priorityLevel];
	if (outgoingPacketBuffer.Size()>0)
	{
		int peekPL = outgoingPacketBuffer.Peek()->priority;
		reliabilityHeapWeightType weight = outgoingPacketBuffer.PeekWeight();
		reliabilityHeapWeightType min = weight - (1<<peekPL)*peekPL+peekPL;
		if (next<min)
			next=min + (1<<priorityLevel)*priorityLevel+priorityLevel;
		outgoingPacketBufferNextWeights[priorityLevel]=next+(1<<priorityLevel)*(priorityLevel+1)+priorityLevel;
	}
	else
	{
		InitHeapWeights();
	}
	return next;
}

//-------------------------------------------------------------------------------------------------------
// #if defined(RELIABILITY_LAYER_NEW_UNDEF_ALLOCATING_QUEUE)
// #pragma pop_macro("new")
// #undef RELIABILITY_LAYER_NEW_UNDEF_ALLOCATING_QUEUE
// #endif
