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
/// \brief \b [Internal] Datagram reliable, ordered, unordered and sequenced sends.  Flow control.  Message splitting, reassembly, and coalescence.
///


#ifndef __RELIABILITY_LAYER_H
#define __RELIABILITY_LAYER_H

#include "memoryoverride.h"
#include "MTUSize.h"
#include "DS_LinkedList.h"
#include "DS_List.h"
#include "SocketLayer.h"
#include "PacketPriority.h"
#include "DS_Queue.h"
#include "BitStream.h"
#include "InternalPacket.h"
#include "statistics.h"
#include "DR_SHA1.h"
#include "DS_OrderedList.h"
#include "DS_RangeList.h"
#include "DS_BPlusTree.h"
#include "DS_MemoryPool.h"
#include "defines.h"
#include "DS_Heap.h"
#include "BitStream.h"
#include "NativeFeatureIncludes.h"
#include "SecureHandshake.h"
#include "PluginInterface2.h"
#include "Rand.h"
#include "socket2.h"

#if USE_SLIDING_WINDOW_CONGESTION_CONTROL!=1
#include "CCRakNetUDT.h"
#define INCLUDE_TIMESTAMP_WITH_DATAGRAMS 1
#else
#include "CCRakNetSlidingWindow.h"
#define INCLUDE_TIMESTAMP_WITH_DATAGRAMS 0
#endif

/// Number of ordered streams available. You can use up to 32 ordered streams
#define NUMBER_OF_ORDERED_STREAMS 32 // 2^5

#define RESEND_TREE_ORDER 32

namespace SLNet {

	/// Forward declarations
class PluginInterface2;
class RakNetRandom;
typedef uint64_t reliabilityHeapWeightType;

// #med - consider a more suitable name for the class / maybe even make an internal class to SplitPacketChannel?
class SplitPacketSort
{
	// member variables
private:
	InternalPacket **m_data;
	size_t m_allocationSize;
	unsigned int m_addedPacketsCount;
	SplitPacketIdType m_packetId;

	// construction/destruction
public:
	SplitPacketSort();
	~SplitPacketSort();

	// initialization
public:
	void Preallocate(InternalPacket *internalPacket, const char *file, unsigned int line);

	// accessors
public:
	bool AllPacketsAdded() const;
	size_t GetAllocSize() const;
	unsigned int GetNumAddedPackets() const;
	SplitPacketIdType GetPacketId() const;

	// operators
public:
	InternalPacket*& operator[](size_t index);

	// container operations
public:
	bool Add(InternalPacket *internalPacket);
};

// int SplitPacketIndexComp( SplitPacketIndexType const &key, InternalPacket* const &data );
struct SplitPacketChannel//<SplitPacketChannel>
{
	CCTimeType lastUpdateTime;

	SplitPacketSort splitPacketList;

#if PREALLOCATE_LARGE_MESSAGES==1
	InternalPacket *returnedPacket;
	bool gotFirstPacket;
	unsigned int stride;
	unsigned int splitPacketsArrived;
#else
	// This is here for progress notifications, since progress notifications return the first packet data, if available
	InternalPacket *firstPacket;
#endif

};
int RAK_DLL_EXPORT SplitPacketChannelComp( SplitPacketIdType const &key, SplitPacketChannel* const &data );

// Helper class
struct BPSTracker
{
	BPSTracker();
	~BPSTracker();
	void Reset(const char *file, unsigned int line);
	inline void Push1(CCTimeType time, uint64_t value1) {dataQueue.Push(TimeAndValue2(time,value1),_FILE_AND_LINE_); total1+=value1; lastSec1+=value1;}
//	void Push2(SLNet::TimeUS time, uint64_t value1, uint64_t value2);
	inline uint64_t GetBPS1(CCTimeType time) {(void) time; return lastSec1;}
	inline uint64_t GetBPS1Threadsafe(CCTimeType time) {(void) time; return lastSec1;}
//	uint64_t GetBPS2(RakNetTimeUS time);
//	void GetBPS1And2(RakNetTimeUS time, uint64_t &out1, uint64_t &out2);
	uint64_t GetTotal1(void) const;
//	uint64_t GetTotal2(void) const;

	struct TimeAndValue2
	{
		TimeAndValue2();
		~TimeAndValue2();
		TimeAndValue2(CCTimeType t, uint64_t v1);
	//	TimeAndValue2(SLNet::TimeUS t, uint64_t v1, uint64_t v2);
	//	uint64_t value1, value2;
		uint64_t value1;
		CCTimeType time;
	};

	uint64_t total1, lastSec1;
//	uint64_t total2, lastSec2;
	DataStructures::Queue<TimeAndValue2> dataQueue;
	void ClearExpired1(CCTimeType time);
//	void ClearExpired2(SLNet::TimeUS time);
};

/// Datagram reliable, ordered, unordered and sequenced sends.  Flow control.  Message splitting, reassembly, and coalescence.
class ReliabilityLayer//<ReliabilityLayer>
{
public:

	// Constructor
	ReliabilityLayer();

	// Destructor
	~ReliabilityLayer();

	/// Resets the layer for reuse
	void Reset( bool resetVariables, int MTUSize, bool _useSecurity );

	/// Set the time, in MS, to use before considering ourselves disconnected after not being able to deliver a reliable packet
	/// Default time is 10,000 or 10 seconds in release and 30,000 or 30 seconds in debug.
	/// \param[in] time Time, in MS
	void SetTimeoutTime(SLNet::TimeMS time );

	/// Returns the value passed to SetTimeoutTime. or the default if it was never called
	/// \param[out] the value passed to SetTimeoutTime
	SLNet::TimeMS GetTimeoutTime(void);

	/// Packets are read directly from the socket layer and skip the reliability layer because unconnected players do not use the reliability layer
	/// This function takes packet data after a player has been confirmed as connected.
	/// \param[in] buffer The socket data
	/// \param[in] length The length of the socket data
	/// \param[in] systemAddress The player that this data is from
	/// \param[in] messageHandlerList A list of registered plugins
	/// \param[in] MTUSize maximum datagram size
	/// \retval true Success
	/// \retval false Modified packet
	bool HandleSocketReceiveFromConnectedPlayer(
		const char *buffer, unsigned int length, SystemAddress &systemAddress, DataStructures::List<PluginInterface2*> &messageHandlerList, int MTUSize,
		RakNetSocket2 *s, RakNetRandom *rnr, CCTimeType timeRead, BitStream &updateBitStream);

	/// This allocates bytes and writes a user-level message to those bytes.
	/// \param[out] data The message
	/// \return Returns number of BITS put into the buffer
	BitSize_t Receive( unsigned char**data );

	/// Puts data on the send queue
	/// \param[in] data The data to send
	/// \param[in] numberOfBitsToSend The length of \a data in bits
	/// \param[in] priority The priority level for the send
	/// \param[in] reliability The reliability type for the send
	/// \param[in] orderingChannel 0 to 31.  Specifies what channel to use, for relational ordering and sequencing of packets.
	/// \param[in] makeDataCopy If true \a data will be copied.  Otherwise, only a pointer will be stored.
	/// \param[in] MTUSize maximum datagram size
	/// \param[in] currentTime Current time, as per SLNet::GetTimeMS()
	/// \param[in] receipt This number will be returned back with ID_SND_RECEIPT_ACKED or ID_SND_RECEIPT_LOSS and is only returned with the reliability types that contain RECEIPT in the name
	/// \return True or false for success or failure.
	bool Send( char *data, BitSize_t numberOfBitsToSend, PacketPriority priority, PacketReliability reliability, unsigned char orderingChannel, bool makeDataCopy, int MTUSize, CCTimeType currentTime, uint32_t receipt );

	/// Call once per game cycle.  Handles internal lists and actually does the send.
	/// \param[in] s the communication  end point
	/// \param[in] systemAddress The Unique Player Identifier who shouldhave sent some packets
	/// \param[in] MTUSize maximum datagram size
	/// \param[in] time current system time
	/// \param[in] maxBitsPerSecond if non-zero, enforces that outgoing bandwidth does not exceed this amount
	/// \param[in] messageHandlerList A list of registered plugins
	void Update( RakNetSocket2 *s, SystemAddress &systemAddress, int MTUSize, CCTimeType time,
		unsigned bitsPerSecondLimit,
		DataStructures::List<PluginInterface2*> &messageHandlerList,
		RakNetRandom *rnr, BitStream &updateBitStream );

	// #med 0.2.0 - review whether we'd rather have this defined as a private method and declare RakPeer a friend of ReliabilityLayer
	/// @since 0.2.0: added
	/// Same as \see Update() except that outstanding ACKs are ensured to be sent.
	void UpdateAndForceACKs( RakNetSocket2 *s, SystemAddress &systemAddress, int MTUSize, CCTimeType time,
		unsigned bitsPerSecondLimit,
		DataStructures::List<PluginInterface2*> &messageHandlerList,
		RakNetRandom *rnr, BitStream &updateBitStream );
	
	/// Were you ever unable to deliver a packet despite retries?
	/// \return true means the connection has been lost.  Otherwise not.
	bool IsDeadConnection( void ) const;

	/// Causes IsDeadConnection to return true
	void KillConnection(void);

	/// Get Statistics
	/// \return A pointer to a static struct, filled out with current statistical information.
	RakNetStatistics * GetStatistics( RakNetStatistics *rns );

	///Are we waiting for any data to be sent out or be processed by the player?
	bool IsOutgoingDataWaiting(void);
	bool AreAcksWaiting(void);

	// Set outgoing lag and packet loss properties
	void ApplyNetworkSimulator( double _maxSendBPS, SLNet::TimeMS _minExtraPing, SLNet::TimeMS _extraPingVariance );

	/// Returns if you previously called ApplyNetworkSimulator
	/// \return If you previously called ApplyNetworkSimulator
	bool IsNetworkSimulatorActive( void );

	void SetSplitMessageProgressInterval(int interval);
	void SetUnreliableTimeout(SLNet::TimeMS timeoutMS);
	/// Has a lot of time passed since the last ack
	bool AckTimeout(SLNet::Time curTime);
	CCTimeType GetNextSendTime(void) const;
	CCTimeType GetTimeBetweenPackets(void) const;
#if INCLUDE_TIMESTAMP_WITH_DATAGRAMS==1
	CCTimeType GetAckPing(void) const;
#endif
	SLNet::TimeMS GetTimeLastDatagramArrived(void) const {return timeLastDatagramArrived;}

	// If true, will update time between packets quickly based on ping calculations
	//void SetDoFastThroughputReactions(bool fast);

	// Encoded as numMessages[unsigned int], message1BitLength[unsigned int], message1Data (aligned), ...
	//void GetUndeliveredMessages(SLNet::BitStream *messages, int MTUSize);

private:
	/// Send the contents of a bitstream to the socket
	/// \param[in] s The socket used for sending data
	/// \param[in] systemAddress The address and port to send to
	/// \param[in] bitStream The data to send.
	void SendBitStream( RakNetSocket2 *s, SystemAddress &systemAddress, SLNet::BitStream *bitStream, RakNetRandom *rnr, CCTimeType currentTime);

	///Parse an internalPacket and create a bitstream to represent this data
	/// \return Returns number of bits used
	BitSize_t WriteToBitStreamFromInternalPacket(SLNet::BitStream *bitStream, const InternalPacket *const internalPacket, CCTimeType curTime );


	/// Parse a bitstream and create an internal packet to represent this data
	InternalPacket* CreateInternalPacketFromBitStream(SLNet::BitStream *bitStream, CCTimeType time );

	/// Does what the function name says
	unsigned RemovePacketFromResendListAndDeleteOlderReliableSequenced( const MessageNumberType messageNumber, CCTimeType time, DataStructures::List<PluginInterface2*> &messageHandlerList, const SystemAddress &systemAddress );

	/// Acknowledge receipt of the packet with the specified messageNumber
	void SendAcknowledgementPacket( const DatagramSequenceNumberType messageNumber, CCTimeType time);

	/// This will return true if we should not send at this time
	bool IsSendThrottled( int MTUSize );

	/// We lost a packet
	void UpdateWindowFromPacketloss( CCTimeType time );

	/// Increase the window size
	void UpdateWindowFromAck( CCTimeType time );

	/// Parse an internalPacket and figure out how many header bits would be written.  Returns that number
	BitSize_t GetMaxMessageHeaderLengthBits( void );
	BitSize_t GetMessageHeaderLengthBits( const InternalPacket *const internalPacket );

	/// Get the SHA1 code
	void GetSHA1( unsigned char * const buffer, unsigned int nbytes, char code[ SHA1_LENGTH ] );

	/// Check the SHA1 code
	bool CheckSHA1( char code[ SHA1_LENGTH ], unsigned char * const buffer, unsigned int nbytes );

	/// Search the specified list for sequenced packets on the specified ordering channel, optionally skipping those with splitPacketId, and delete them
//	void DeleteSequencedPacketsInList( unsigned char orderingChannel, DataStructures::List<InternalPacket*>&theList, int splitPacketId = -1 );

	/// Search the specified list for sequenced packets with a value less than orderingIndex and delete them
//	void DeleteSequencedPacketsInList( unsigned char orderingChannel, DataStructures::Queue<InternalPacket*>&theList );

	/// Returns true if newPacketOrderingIndex is older than the waitingForPacketOrderingIndex
	bool IsOlderOrderedPacket( OrderingIndexType newPacketOrderingIndex, OrderingIndexType waitingForPacketOrderingIndex );

	/// Split the passed packet into chunks under MTU_SIZE bytes (including headers) and save those new chunks
	void SplitPacket( InternalPacket *internalPacket );

	/// Insert a packet into the split packet list
	void InsertIntoSplitPacketList( InternalPacket * internalPacket, CCTimeType time );

	/// Take all split chunks with the specified splitPacketId and try to reconstruct a packet. If we can, allocate and return it.  Otherwise return 0
	InternalPacket * BuildPacketFromSplitPacketList( SplitPacketIdType inSplitPacketId, CCTimeType time,
		RakNetSocket2 *s, SystemAddress &systemAddress, RakNetRandom *rnr, BitStream &updateBitStream);
	InternalPacket * BuildPacketFromSplitPacketList( SplitPacketChannel *splitPacketChannel, CCTimeType time );

	/// Delete any unreliable split packets that have long since expired
	//void DeleteOldUnreliableSplitPackets( CCTimeType time );

	/// Creates a copy of the specified internal packet with data copied from the original starting at dataByteOffset for dataByteLength bytes.
	/// Does not copy any split data parameters as that information is always generated does not have any reason to be copied
	InternalPacket * CreateInternalPacketCopy( InternalPacket *original, int dataByteOffset, int dataByteLength, CCTimeType time );

	/// Get the specified ordering list
	// DataStructures::LinkedList<InternalPacket*> *GetOrderingListAtOrderingStream( unsigned char orderingChannel );

	/// Add the internal packet to the ordering list in order based on order index
	// void AddToOrderingList( InternalPacket * internalPacket );

	/// Inserts a packet into the resend list in order
	void InsertPacketIntoResendList( InternalPacket *internalPacket, CCTimeType time, bool firstResend, bool modifyUnacknowledgedBytes );

	/// Memory handling
	void FreeMemory( bool freeAllImmediately );

	/// Memory handling
	void FreeThreadSafeMemory( void );

	// Initialize the variables
	void InitializeVariables( void );

	/// Given the current time, is this time so old that we should consider it a timeout?
	bool IsExpiredTime(unsigned int input, CCTimeType currentTime) const;

	// Make it so we don't do resends within a minimum threshold of time
	void UpdateNextActionTime(void);

	void UpdateInternal( RakNetSocket2 *s, SystemAddress &systemAddress, int MTUSize, CCTimeType time,
		unsigned bitsPerSecondLimit,
		DataStructures::List<PluginInterface2*> &messageHandlerList,
		RakNetRandom *rnr, BitStream &updateBitStream, bool forceSendACKs );

	/// Does this packet number represent a packet that was skipped (out of order?)
	//unsigned int IsReceivedPacketHole(unsigned int input, SLNet::TimeMS currentTime) const;

	/// Skip an element in the received packets list
	//unsigned int MakeReceivedPacketHole(unsigned int input) const;

	/// How many elements are waiting to be resent?
	unsigned int GetResendListDataSize(void) const;

	/// Update all memory which is not threadsafe
	void UpdateThreadedMemory(void);

	void CalculateHistogramAckSize(void);

	// Used ONLY for RELIABLE_ORDERED
	// RELIABLE_SEQUENCED just returns the newest one
	// DataStructures::List<DataStructures::LinkedList<InternalPacket*>*> orderingList;
	DataStructures::Queue<InternalPacket*> outputQueue;
	int splitMessageProgressInterval;
	CCTimeType unreliableTimeout;

	struct MessageNumberNode
	{
		DatagramSequenceNumberType messageNumber;
		MessageNumberNode *next;
	};
	struct DatagramHistoryNode
	{
		DatagramHistoryNode() {}
		DatagramHistoryNode(MessageNumberNode *_head, CCTimeType ts
			) :
		head(_head), timeSent(ts)
		{}
		MessageNumberNode *head;
		CCTimeType timeSent;
	};
	// Queue length is programmatically restricted to DATAGRAM_MESSAGE_ID_ARRAY_LENGTH
	// This is essentially an O(1) lookup to get a DatagramHistoryNode given an index
	// datagramHistory holds a linked list of MessageNumberNode. Each MessageNumberNode refers to one element in resendList which can be cleared on an ack.
	DataStructures::Queue<DatagramHistoryNode> datagramHistory;
	DataStructures::MemoryPool<MessageNumberNode> datagramHistoryMessagePool;

	struct UnreliableWithAckReceiptNode
	{
		UnreliableWithAckReceiptNode() {}
		UnreliableWithAckReceiptNode(DatagramSequenceNumberType _datagramNumber, uint32_t _sendReceiptSerial, SLNet::TimeUS _nextActionTime) :
			datagramNumber(_datagramNumber), sendReceiptSerial(_sendReceiptSerial), nextActionTime(_nextActionTime)
		{}
		DatagramSequenceNumberType datagramNumber;
		uint32_t sendReceiptSerial;
		SLNet::TimeUS nextActionTime;
	};
	DataStructures::List<UnreliableWithAckReceiptNode> unreliableWithAckReceiptHistory;

	void RemoveFromDatagramHistory(DatagramSequenceNumberType index);
	MessageNumberNode* GetMessageNumberNodeByDatagramIndex(DatagramSequenceNumberType index, CCTimeType *timeSent);
	void AddFirstToDatagramHistory(DatagramSequenceNumberType datagramNumber, CCTimeType timeSent);
	MessageNumberNode* AddFirstToDatagramHistory(DatagramSequenceNumberType datagramNumber, DatagramSequenceNumberType messageNumber, CCTimeType timeSent);
	MessageNumberNode* AddSubsequentToDatagramHistory(MessageNumberNode *messageNumberNode, DatagramSequenceNumberType messageNumber);
	DatagramSequenceNumberType datagramHistoryPopCount;
	
	DataStructures::MemoryPool<InternalPacket> internalPacketPool;
	// DataStructures::BPlusTree<DatagramSequenceNumberType, InternalPacket*, RESEND_TREE_ORDER> resendTree;
	InternalPacket *resendBuffer[RESEND_BUFFER_ARRAY_LENGTH];
	InternalPacket *resendLinkedListHead;
	InternalPacket *unreliableLinkedListHead;
	void RemoveFromUnreliableLinkedList(InternalPacket *internalPacket);
	void AddToUnreliableLinkedList(InternalPacket *internalPacket);
//	unsigned int numPacketsOnResendBuffer;
	//unsigned int blockWindowIncreaseUntilTime;
	//	DataStructures::RangeList<DatagramSequenceNumberType> acknowlegements;
	// Resend list is a tree of packets we need to resend

	// Set to the current time when the resend queue is no longer empty
	// Set to zero when it becomes empty
	// Set to the current time if it is not zero, and we get incoming data
	// If the current time - timeResendQueueNonEmpty is greater than a threshold, we are disconnected
//	CCTimeType timeResendQueueNonEmpty;
	SLNet::TimeMS timeLastDatagramArrived;


	// If we backoff due to packetloss, don't remeasure until all waiting resends have gone out or else we overcount
//	bool packetlossThisSample;
//	int backoffThisSample;
//	unsigned packetlossThisSampleResendCount;
//	CCTimeType lastPacketlossTime;

	//DataStructures::Queue<InternalPacket*> sendPacketSet[ NUMBER_OF_PRIORITIES ];
	DataStructures::Heap<reliabilityHeapWeightType, InternalPacket*, false> outgoingPacketBuffer;
	reliabilityHeapWeightType outgoingPacketBufferNextWeights[NUMBER_OF_PRIORITIES];
	void InitHeapWeights(void);
	reliabilityHeapWeightType GetNextWeight(int priorityLevel);
//	unsigned int messageInSendBuffer[NUMBER_OF_PRIORITIES];
//	double bytesInSendBuffer[NUMBER_OF_PRIORITIES];


    DataStructures::OrderedList<SplitPacketIdType, SplitPacketChannel*, SplitPacketChannelComp> splitPacketChannelList;

	MessageNumberType sendReliableMessageNumberIndex;
	MessageNumberType internalOrderIndex;
	//unsigned int windowSize;
	//SLNet::BitStream updateBitStream;
	bool deadConnection, cheater;
	SplitPacketIdType splitPacketId;
	SLNet::TimeMS timeoutTime; // How long to wait in MS before timing someone out
	//int MAX_AVERAGE_PACKETS_PER_SECOND; // Name says it all
//	int RECEIVED_PACKET_LOG_LENGTH, requestedReceivedPacketLogLength; // How big the receivedPackets array is
//	unsigned int *receivedPackets;
	RakNetStatistics statistics;

	// Algorithm for blending ordered and sequenced on the same channel:
	// 1. Each ordered message transmits OrderingIndexType orderedWriteIndex. There are NUMBER_OF_ORDERED_STREAMS independent values of these. The value
	//    starts at 0. Every time an ordered message is sent, the value increments by 1
	// 2. Each sequenced message contains the current value of orderedWriteIndex for that channel, and additionally OrderingIndexType sequencedWriteIndex. 
	//    sequencedWriteIndex resets to 0 every time orderedWriteIndex increments. It increments by 1 every time a sequenced message is sent.
	// 3. The receiver maintains the next expected value for the orderedWriteIndex, stored in orderedReadIndex.
	// 4. As messages arrive:
	//    If a message has the current ordering index, and is sequenced, and is < the current highest sequence value, discard
	//    If a message has the current ordering index, and is sequenced, and is >= the current highest sequence value, return immediately
	//    If a message has a greater ordering index, and is sequenced or ordered, buffer it
	//    If a message has the current ordering index, and is ordered, buffer, then push off messages from buffer
	// 5. Pushing off messages from buffer:
	//    Messages in buffer are put in a minheap. The value of each node is calculated such that messages are returned:
	//    A. (lowest ordering index, lowest sequence index)
	//    B. (lowest ordering index, no sequence index)
	//    Messages are pushed off until the heap is empty, or the next message to be returned does not preserve the ordered index
	//    For an empty heap, the heap weight should start at the lowest value based on the next expected ordering index, to avoid variable overflow

	// Sender increments this by 1 for every ordered message sent
	OrderingIndexType orderedWriteIndex[NUMBER_OF_ORDERED_STREAMS];
	// Sender increments by 1 for every sequenced message sent. Resets to 0 when an ordered message is sent
	OrderingIndexType sequencedWriteIndex[NUMBER_OF_ORDERED_STREAMS];
	// Next expected index for ordered messages.
	OrderingIndexType orderedReadIndex[NUMBER_OF_ORDERED_STREAMS];
	// Highest value received for sequencedWriteIndex for the current value of orderedReadIndex on the same channel.
	OrderingIndexType highestSequencedReadIndex[NUMBER_OF_ORDERED_STREAMS];
	DataStructures::Heap<reliabilityHeapWeightType, InternalPacket*, false> orderingHeaps[NUMBER_OF_ORDERED_STREAMS];
	OrderingIndexType heapIndexOffsets[NUMBER_OF_ORDERED_STREAMS];

	





//	CCTimeType histogramStart;
//	unsigned histogramBitsSent;


	/// Memory-efficient receivedPackets algorithm:
	/// receivedPacketsBaseIndex is the packet number we are expecting
	/// Everything under receivedPacketsBaseIndex is a packet we already got
	/// Everything over receivedPacketsBaseIndex is stored in hasReceivedPacketQueue
	/// It stores the time to stop waiting for a particular packet number, where the packet number is receivedPacketsBaseIndex + the index into the queue
	/// If 0, we got got that packet.  Otherwise, the time to give up waiting for that packet.
	/// If we get a packet number where (receivedPacketsBaseIndex-packetNumber) is less than half the range of receivedPacketsBaseIndex then it is a duplicate
	/// Otherwise, it is a duplicate packet (and ignore it).
	// DataStructures::Queue<CCTimeType> hasReceivedPacketQueue;
	DataStructures::Queue<bool> hasReceivedPacketQueue;
	DatagramSequenceNumberType receivedPacketsBaseIndex;
	bool resetReceivedPackets;

	CCTimeType lastUpdateTime;
	CCTimeType timeBetweenPackets, nextSendTime;
#if INCLUDE_TIMESTAMP_WITH_DATAGRAMS==1
	CCTimeType ackPing;
#endif
//	CCTimeType ackPingSamples[ACK_PING_SAMPLES_SIZE]; // Must be range of unsigned char to wrap ackPingIndex properly
	CCTimeType ackPingSum;
	unsigned char ackPingIndex;
	//CCTimeType nextLowestPingReset;
	RemoteSystemTimeType remoteSystemTime;
//	bool continuousSend;
//	CCTimeType lastTimeBetweenPacketsIncrease,lastTimeBetweenPacketsDecrease;
	// Limit changes in throughput to once per ping - otherwise even if lag starts we don't know about it
	// In the meantime the connection is flooded and overrun.
	CCTimeType nextAllowedThroughputSample;
	bool bandwidthExceededStatistic;

	// If Update::maxBitsPerSecond > 0, then throughputCapCountdown is used as a timer to prevent sends for some amount of time after each send, depending on
	// the amount of data sent
	long long throughputCapCountdown;

	unsigned receivePacketCount;

#ifdef _DEBUG
	struct DataAndTime//<InternalPacket>
	{
		RakNetSocket2 *s;
		char data[ MAXIMUM_MTU_SIZE ];
		unsigned int length;
		SLNet::TimeMS sendTime;
		//	SystemAddress systemAddress;
		unsigned short remotePortRakNetWasStartedOn_PS3;
		unsigned int extraSocketOptions;
	};
	DataStructures::Queue<DataAndTime*> delayList;

	// Internet simulator
	double packetloss;
	SLNet::TimeMS minExtraPing, extraPingVariance;
#endif

	CCTimeType elapsedTimeSinceLastUpdate;

	CCTimeType nextAckTimeToSend;

	
#if USE_SLIDING_WINDOW_CONGESTION_CONTROL==1
	SLNet::CCRakNetSlidingWindow congestionManager;
#else
	SLNet::CCRakNetUDT congestionManager;
#endif


	uint32_t unacknowledgedBytes;
	
	bool ResendBufferOverflow(void) const;
	void ValidateResendList(void) const;
	void ResetPacketsAndDatagrams(void);
	void PushPacket(CCTimeType time, InternalPacket *internalPacket, bool isReliable);
	void PushDatagram(void);
	bool TagMostRecentPushAsSecondOfPacketPair(void);
	void ClearPacketsAndDatagrams(void);
	void MoveToListHead(InternalPacket *internalPacket);
	void RemoveFromList(InternalPacket *internalPacket, bool modifyUnacknowledgedBytes);
	void AddToListTail(InternalPacket *internalPacket, bool modifyUnacknowledgedBytes);
	void PopListHead(bool modifyUnacknowledgedBytes);
	bool IsResendQueueEmpty(void) const;
	void SortSplitPacketList(DataStructures::List<InternalPacket*> &data, unsigned int leftEdge, unsigned int rightEdge) const;
	void SendACKs(RakNetSocket2 *s, SystemAddress &systemAddress, CCTimeType time, RakNetRandom *rnr, BitStream &updateBitStream);

	DataStructures::List<InternalPacket*> packetsToSendThisUpdate;
	DataStructures::List<bool> packetsToDeallocThisUpdate;
	// boundary is in packetsToSendThisUpdate, inclusive
	DataStructures::List<unsigned int> packetsToSendThisUpdateDatagramBoundaries;
	DataStructures::List<bool> datagramsToSendThisUpdateIsPair;
	DataStructures::List<unsigned int> datagramSizesInBytes;
	BitSize_t datagramSizeSoFar;
	BitSize_t allDatagramSizesSoFar;
	double totalUserDataBytesAcked;
	CCTimeType timeOfLastContinualSend;
	CCTimeType timeToNextUnreliableCull;

	// This doesn't need to be a member, but I do it to avoid reallocations
	DataStructures::RangeList<DatagramSequenceNumberType> incomingAcks;

	// Every 16 datagrams, we make sure the 17th datagram goes out the same update tick, and is the same size as the 16th
	int countdownToNextPacketPair;
	InternalPacket* AllocateFromInternalPacketPool(void);
	void ReleaseToInternalPacketPool(InternalPacket *ip);

	DataStructures::RangeList<DatagramSequenceNumberType> acknowlegements;
	DataStructures::RangeList<DatagramSequenceNumberType> NAKs;
	bool remoteSystemNeedsBAndAS;

	unsigned int GetMaxDatagramSizeExcludingMessageHeaderBytes(void);
	BitSize_t GetMaxDatagramSizeExcludingMessageHeaderBits(void);

	// ourOffset refers to a section within externallyAllocatedPtr. Do not deallocate externallyAllocatedPtr until all references are lost
	void AllocInternalPacketData(InternalPacket *internalPacket, InternalPacketRefCountedData **refCounter, unsigned char *externallyAllocatedPtr, unsigned char *ourOffset);
	// Set the data pointer to externallyAllocatedPtr, do not allocate
	void AllocInternalPacketData(InternalPacket *internalPacket, unsigned char *externallyAllocatedPtr);
	// Allocate new
	void AllocInternalPacketData(InternalPacket *internalPacket, unsigned int numBytes, bool allowStack, const char *file, unsigned int line);
	void FreeInternalPacketData(InternalPacket *internalPacket, const char *file, unsigned int line);
	DataStructures::MemoryPool<InternalPacketRefCountedData> refCountedDataPool;

	BPSTracker bpsMetrics[RNS_PER_SECOND_METRICS_COUNT];
	CCTimeType lastBpsClear;

#if LIBCAT_SECURITY==1
public:
	cat::AuthenticatedEncryption* GetAuthenticatedEncryption(void) { return &auth_enc; }

protected:
	cat::AuthenticatedEncryption auth_enc;
	bool useSecurity;
#endif // LIBCAT_SECURITY
};

} // namespace SLNet

#endif
