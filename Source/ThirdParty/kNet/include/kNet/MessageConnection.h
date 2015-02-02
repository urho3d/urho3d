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
#pragma once

/** @file MessageConnection.h
	@brief The MessageConnection and ConnectionStatistics classes. */

#include <vector>
#include <map>
#include <utility>
#include <set>

#include "kNetBuildConfig.h"
#include "WaitFreeQueue.h"
#include "NetworkSimulator.h"
#include "LockFreePoolAllocator.h"
#include "Lockable.h"
#include "Socket.h"
#include "IMessageHandler.h"
#include "BasicSerializedDataTypes.h"
#include "Datagram.h"
#include "FragmentedTransferManager.h"
#include "NetworkMessage.h"
#include "Event.h"
#include "DataSerializer.h"
#include "DataDeserializer.h"

#include "MaxHeap.h"
#include "Clock.h"
#include "PolledTimer.h"
#include "Thread.h"
#include "Types.h"

namespace kNet
{

class MessageConnection;
class UDPMessageConnection;
class TCPMessageConnection;
class NetworkServer;
class Network;
class NetworkWorkerThread;
class FragmentedSendManager;

#ifdef _MSC_VER
struct FragmentedSendManager::FragmentedTransfer;
#endif

/// Stores information about an established MessageConnection.
struct ConnectionStatistics
{
	/// Remembers a ping request that was sent to the other end.
	struct PingTrack
	{
		tick_t pingSentTick;  ///< Timestamp of when the PingRequest was sent.
		tick_t pingReplyTick; ///< If replyReceived==true, contains the timestamp of when PingReply was received as a response.
		unsigned long pingID;      ///< ID of this ping message.
		bool replyReceived;        ///< True of PingReply has already been received for this.
	};
	/// Contains an entry for each recently performed Ping operation, sorted by age (oldest first).
	std::vector<PingTrack> ping;

	/// Remembers both in- and outbound traffic events on the socket.
	struct TrafficTrack
	{
		tick_t tick;          ///< Denotes when this event occurred.
		unsigned long packetsIn;   ///< The number of datagrams in when this event occurred.
		unsigned long packetsOut;  ///< The number of datagrams out when this event occurred.
		unsigned long messagesIn;  ///< The total number of messages the received datagrams contained.
		unsigned long messagesOut; ///< The total number of messages the sent datagrams contained.
		unsigned long bytesIn;     ///< The total number of bytes the received datagrams contained.
		unsigned long bytesOut;    ///< The total number of bytes the sent datagrams contained. 
	};
	/// Contains an entry for each recent traffic event (data in/out) on the connection, sorted by age (oldest first).
	std::vector<TrafficTrack> traffic;

	/// Remembers the send/receive time of a datagram with a certain ID.
	struct DatagramIDTrack
	{
		tick_t tick;
		packet_id_t packetID;
	};
	/// Contains an entry for each recently received packet, sorted by age (oldest first).
	std::vector<DatagramIDTrack> recvPacketIDs;
};

/// Comparison object that sorts the two messages by their priority (higher priority/smaller number first).
class NetworkMessagePriorityCmp
{
public:
	int operator ()(const NetworkMessage *a, const NetworkMessage *b)
	{
		assert(a && b);
		if (a->priority < b->priority) return -1;
		if (b->priority < a->priority) return 1;

		if (a->MessageNumber() < b->MessageNumber()) return 1;
		if (b->MessageNumber() < a->MessageNumber()) return -1;

		return 0;
	}
};

/// Represents the current state of the connection.
enum ConnectionState
{
	ConnectionPending, ///< Waiting for the other end to send an acknowledgement packet to form the connection. No messages may yet be sent or received at this state.
	ConnectionOK,      ///< The connection is bidirectionally open, for both reading and writing. (readOpen=true, writeOpen=true)
	ConnectionDisconnecting, ///< We are closing the connection down. Cannot send any more messages, but can still receive. (readOpen=true, writeOpen=false)
	ConnectionPeerClosed, ///< The other end has closed the connection. No new messages will be received, but can still send messages. (readOpen=false, writeOpen=true)
	ConnectionClosed    ///< The socket is no longer open. A MessageConnection object in this state cannot be reused to open a new connection, but a new connection object must be created.
};

/// Returns a textual representation of a ConnectionState.
std::string ConnectionStateToString(ConnectionState state);

// Prevent confusion with Win32 functions
#ifdef SendMessage
#undef SendMessage
#endif

/// Represents a single established network connection. MessageConnection maintains its own worker thread that manages
/// connection control, the scheduling and prioritization of outbound messages, and receiving inbound messages.
class MessageConnection : public RefCountable
{
public:
	virtual ~MessageConnection();

	/// Returns the current connection state.
	ConnectionState GetConnectionState() const; // [main and worker thread]

	/// Returns true if the peer has signalled it will not send any more data (the connection is half-closed or full-closed).
	bool IsReadOpen() const; // [main and worker thread]
	
	/// Returns true if we have signalled not to send any more data (the connection is half-closed or full-closed).
	bool IsWriteOpen() const; // [main and worker thread]

	/// Returns true if the connection is in the ConnectionPending state and waiting for the other end to resolve/establish the connection. 
	/// When this function returns false, the connection may be half-open, bidirectionally open, timed out on ConnectionPending, or closed.
	bool IsPending() const; // [main and worker thread]

	/// Returns true if this socket is connected, i.e. at least half-open in one way.
	bool Connected() const { return IsReadOpen() || IsWriteOpen(); } // [main and worker thread]

	/// Runs a modal processing loop and produces events for all inbound received data. Returns when the connection is closed.
	/// This is an example function mostly useful only for very simple demo applications. In most cases,
	/// you do not want to call this.
	void RunModalClient(); // [main thread]

	/// Blocks for the given amount of time until the connection has transitioned away from ConnectionPending state.
	/// @param maxMSecstoWait A positive value that indicates the maximum time to wait until returning.
	/// @return If the connection was successfully opened, this function returns true. Otherwise returns false, and
	///         either timeout was encountered and the other end has not acknowledged the connection,
	///         or the connection is in ConnectionClosed state.
	bool WaitToEstablishConnection(int maxMSecsToWait = 500); // [main thread]

	/// Starts a benign disconnect procedure. Transitions ConnectionState to ConnectionDisconnecting. This 
	/// function will block until the given period expires or the other end acknowledges and also closes 
	/// down the connection. Currently no guarantee is given for whether previous reliable messages will 
	/// safely reach the destination. To ensure this, do a manual wait to flush the outbound message queue 
	/// before disconnecting.
	/// @param maxMSecsToWait A positive number that indicates the maximum time to wait for a disconnect
	///                       acknowledgement message until returning.
	///                       If 0 is passed, the function will send the Disconnect message and return immediately.
	/// When this function returns, the connection may either be in ConnectionClosing or ConnectionClosed
	/// state, depending on whether the other end has already acknowledged the disconnection.
	/// \note You may not call this function in middle of StartNewMessage() - EndAndQueueMessage() function calls.
	void Disconnect(int maxMSecsToWait = 500); // [main thread]

	/// Starts a forceful disconnect procedure.
	/// @param maxMSecsToWait If a positive number, Disconnect message will be sent to the peer and if no response
	///                       is received in the given time period, the connection is forcefully closed.
	///                       If 0, no Disconnect message will be sent at all, but the connection is torn down
	///                       and the function returns immediately. The other end will remain hanging and will timeout.
	/// When this function returns, the connection is in ConnectionClosed state.
	/// \note You may not call this function in middle of StartNewMessage() - EndAndQueueMessage() function calls.
	void Close(int maxMSecsToWait = 500); // [main thread]

	// There are 3 ways to send messages through a MessageConnection:
	// StartNewMessage/EndAndQueueMessage, SendStruct, and Send. See below.

	/// Start building a new message with the given ID.
	/// @param id The ID for the message you will be sending.
	/// @param numBytes The number of bytes the body of this message will be. This function will pre-allocate the
	///                 NetworkMessage::data field to hold at least that many bytes (Capacity() can also return a larger value).
	///                 This number only needs to be an estimate, since you can later on call NetworkMessage::Reserve()
	///                 to reallocate the message memory. If you pass in the default value 0, no pre-allocation will be performed.
	/// @return The NetworkMessage object that represents the new message to be built. This message is dynamically allocated
	///         from an internal pool of NetworkMessage blocks. For each NetworkMessage pointer obtained, call
	///         EndAndQueueMessage when you have finished building the message to commit the network send and to release the memory.
	///         Alternatively, if after calling StartNewMessage, you decide to abort the network send, free up the NetworkMessage
	///         by calling this->FreeMessage().
	NetworkMessage *StartNewMessage(unsigned long id, size_t numBytes = 0); // [main and worker thread]

	/// Finishes building the message and submits it to the outbound send queue.
	/// @param msg The message to send. After calling this function, this pointer should be considered freed and may not be
	///            dereferenced or passed to any other member function of this MessageConnection. Only pass in here 
	///            NetworkMessage pointers obtained by a call to StartNewMessage() of the same MessageConnection instance.
	/// @param numBytes Specify here the number of actual bytes you filled in into the msg.data field. A size of 0
	///                 is valid, and can be used in cases the message ID itself is the whole message. Passing in the default 
	///                 value of this parameter will use the size value that was specified in the call to StartNewMessage().
	/// @param internalQueue If true, specifies that this message was submitted from the network worker thread and not the application
	///                 thread. Pass in the value 'false' here in the client application, or there is a chance of a race condition.
	void EndAndQueueMessage(NetworkMessage *msg, size_t numBytes = (size_t)(-1), bool internalQueue = false); // [main and worker thread]

	/// This is a conveniency function to access the above StartNewMessage/EndAndQueueMessage pair. The performance of this
	/// function call is not as good, since a memcpy of the message will need to be made. For performance-critical messages,
	/// it is better to craft the message directly into the buffer area provided by StartNewMessage.
	void SendMessage(unsigned long id, bool reliable, bool inOrder, unsigned long priority, unsigned long contentID, 
	                 const char *data, size_t numBytes); // [main thread]

	/// Sends a message using a serializable structure.
	template<typename SerializableData>
	void SendStruct(const SerializableData &data, unsigned long id, bool inOrder, 
		bool reliable, unsigned long priority, unsigned long contentID = 0); // [main thread]

	/// Sends a message using a compiled message structure.
	template<typename SerializableMessage>
	void Send(const SerializableMessage &data, unsigned long contentID = 0); // [main thread]

	/// Stops all outbound sends until ResumeOutboundSends is called. Use if you need to guarantee that some messages be sent in the same datagram.
	/// Do not stop outbound sends for long periods, or the other end may time out the connection.
	void PauseOutboundSends(); // [main thread]

	/// Resumes sending of outbound messages.
	void ResumeOutboundSends(); // [main thread]

	/// Returns the number of messages that have been received from the network but haven't been handled by the application yet.
	size_t NumInboundMessagesPending() const { return inboundMessageQueue.Size(); } // [main and worker thread]

	/// Returns the total number of messages pending to be sent out.
	size_t NumOutboundMessagesPending() const { return outboundQueue.Size() + outboundAcceptQueue.Size(); } // [main and worker thread]

	/// Returns the number of outbound messages the main thread has queued for the worker thread to send out. (still unaccepted by the worker thread).
	size_t OutboundAcceptQueueSize() const { return outboundAcceptQueue.Size(); } // [main and worker thread]

	/// Returns the number of outbound messages in the worker thread outbound message queue (already accepted and pending a send by the worker thread).
	size_t OutboundQueueSize() const { return outboundQueue.Size(); } // [main and worker thread]

	/// Returns the underlying raw socket. [main and worker thread]
	Socket *GetSocket() { return socket; }

	/// Returns an object that identifies the local endpoint (IP and port) this connection is connected to.
	EndPoint LocalEndPoint() const; // [main and worker thread]

	/// Returns an object that identifies the remote endpoint (IP and port) this connection is connected to.
	EndPoint RemoteEndPoint() const; // [main and worker thread]

	/// Sets an upper limit to the data send rate for this connection.
	/// The default is not to have an upper limit at all.
	/// @param numBytesPerSec The upper limit for the number of bytes to send per second. This limit includes the message header
	///                       bytes as well and not just the payload. Set to 0 to force no limit.
	/// @param numDatagramsPerSec The maximum number of datagrams (UDP packets) to send per second. Set to 0 to force no limit.
	///                       If the connection is operating on top of TCP, this field has no effect.
	///\todo Implement.
	void SetMaximumDataSendRate(int numBytesPerSec, int numDatagramsPerSec);

	/// Registers a new listener object for the events of this connection.
	void RegisterInboundMessageHandler(IMessageHandler *handler); // [main thread]

	/// Fetches all newly received messages waiting in the inbound queue, and passes each of these
	/// to the message handler registered using RegisterInboundMessageHandler.
	/// Call this function periodically to receive new data from the network if you are using the Observer pattern.
	/// Alternatively, use the immediate-mode ReceiveMessage function to receive messages directly one at a time.
	/// @param maxMessageToProcess If the inbound queue contains more than this amount of new messages,
	///                            the processing loop will return to give processing time to other parts of the application.
	///                            If 0 is passed, messages are processed until the queue is empty.
	/// \note It is important to have a non-zero limit in maxMessagesToProcess (unless you're sure what you are doing), since
	///       otherwise an attacker might affect the performance of the application main loop by sending messages so fast that
	///       the queue never has time to exhaust, thus giving an infinite loop in practice.
	void Process(int maxMessagesToProcess = 100); // [main thread]
	
	/// Waits for at most the given amount of time until a new message is received for processing.
	/// @param maxMSecsToWait If 0, the call will wait indefinitely until a message is received or the connection transitions to
	///                       closing state.
	///                       If a positive value is passed, at most that many milliseconds is waited for a new message to be received.
	void WaitForMessage(int maxMSecsToWait); // [main thread]

	/// Returns the next message in the inbound queue. This is an alternative API to RegisterInboundMessageHandler/Process.
	/// \note When using this function to receive messages, remember to call FreeMessage for each NetworkMessage returned, or you
	/// will have a major size memory leak, fast.
	/// @param maxMSecsToWait If a negative number, the call will not wait at all if there are no new messages to process, but 
	///                       returns 0 immediately.
	///                       If 0, the call will wait indefinitely until a message is received or the connection transitions to
	///                       closing state.
	///                       If a positive value is passed, at most that many milliseconds is waited for a new message to be received.
	/// @return A newly allocated object to the received message, or 0 if the queue was empty and no messages were received during
	///         the wait period, or if the connection transitioned to closing state. When you are finished reading the message,
	///         call FreeMessage for the returned pointer.
	NetworkMessage *ReceiveMessage(int maxMSecsToWait = -1); // [main thread]

	/// Frees up a NetworkMessage struct when it is no longer needed.
	/// You need to call this for each message that you received from a call to ReceiveMessage.
	void FreeMessage(NetworkMessage *msg); // [main and worker thread]
	
	/// Returns a single-line message describing the connection state.
	std::string ToString() const; // [main and worker thread]

	/// Dumps a long multi-line status message of this connection state to stdout.
	void DumpStatus() const; // [main thread]

	// MessageConnection Statistics -related functions:

	/// Returns the estimated RTT of the connection, in milliseconds. RTT is the time taken to communicate a message from client->host->client.
	float RoundTripTime() const { return rtt; } // [main and worker thread]

	/// Returns the number of milliseconds since we last received data from the socket.
	float LastHeardTime() const { return Clock::TicksToMillisecondsF(Clock::TicksInBetween(Clock::Tick(), lastHeardTime)); } // [main and worker thread]

	float PacketsInPerSec() const { return packetsInPerSec; } // [main and worker thread]
	float PacketsOutPerSec() const { return packetsOutPerSec; } // [main and worker thread]
	float MsgsInPerSec() const { return msgsInPerSec; } // [main and worker thread]
	float MsgsOutPerSec() const { return msgsOutPerSec; } // [main and worker thread]
	float BytesInPerSec() const { return bytesInPerSec; } // [main and worker thread]
	float BytesOutPerSec() const { return bytesOutPerSec; } // [main and worker thread]

	/// Returns the total number of bytes (excluding IP and TCP/UDP headers) that have been received from this connection.
	u64 BytesInTotal() const { return bytesInTotal; } // [main and worker thread]

	/// Returns the total number of bytes (excluding IP and TCP/UDP headers) that have been sent from this connection.
	u64 BytesOutTotal() const { return bytesOutTotal; } // [main and worker thread]

	/// Returns the simulator object which can be used to apply network condition simulations to this connection.
	NetworkSimulator &NetworkSendSimulator() { return networkSendSimulator; }

	/// Stores all the statistics about the current connection. This data is periodically recomputed
	/// by the network worker thread and shared to the client through a lock.
	Lockable<ConnectionStatistics> statistics; // [main and worker thread]

protected:
	friend class NetworkWorkerThread;

	/// The Network object inside which this MessageConnection lives.
	Network *owner; // [set and read only by the main thread]

	/// If this MessageConnection represents a client connection on the server side, this gives the owner.
	NetworkServer *ownerServer; // [set and read only by the main thread]

	/// Stores the thread that manages the background processing of this connection. The same thread can manage multiple
	/// connections and servers, and not just this one.
	NetworkWorkerThread *workerThread; // [set and read only by worker thread]

#ifdef KNET_THREAD_CHECKING_ENABLED
	/// In debug mode, we track and enforce thread safety constraints through this ID. 
	ThreadId workerThreadId; // [set by worker thread on thread startup, read by both main and worker thread]
#endif

	/// Performs a check that asserts that the current thread of execution is in the network worker thread.
	void AssertInWorkerThreadContext() const; // [main and worker thread]

	/// Performs a check that asserts that the current thread of execution is not in the network worker thread (it is the main thread).
	void AssertInMainThreadContext() const; // [main and worker thread]

	/// Returns true if this MessageConnection is associated with a NetworkWorkerThread to maintain.
	bool IsWorkerThreadRunning() const { return workerThread != 0; } // [main and worker thread]

	/// A queue populated by the main thread to give out messages to the MessageConnection work thread to process.
	WaitFreeQueue<NetworkMessage*> outboundAcceptQueue; // [produced by main thread, consumed by worker thread]

	/// A queue populated by the networking thread to hold all the incoming messages until the application can process them.	
	WaitFreeQueue<NetworkMessage*> inboundMessageQueue; // [produced by worker thread, consumed by main thread]

	/// A priority queue that maintains in order all the messages that are going out the pipe.
	///\todo Make the choice of which of the following structures to use a runtime option.
#ifndef KNET_NO_MAXHEAP // If defined, disables message priorization feature to improve client-side CPU performance. By default disabled.
	MaxHeap<NetworkMessage*, NetworkMessagePriorityCmp> outboundQueue; // [worker thread]
#else
	WaitFreeQueue<NetworkMessage*> outboundQueue; // [worker thread]
#endif

	/// Tracks all the message sends that are fragmented.
	Lockable<FragmentedSendManager> fragmentedSends; // [worker thread]

	/// Tracks all the receives of fragmented messages and helps reconstruct the original messages from fragments.
	FragmentedReceiveManager fragmentedReceives; // [worker thread]

	/// Allocations of NetworkMessage structures go through a pool to avoid dynamic new/delete calls when sending messages.
	/// This structure is shared between the main and worker thread through a lockfree construct.
	LockFreePoolAllocator<NetworkMessage> messagePool; // [main and worker thread]

	/// Tracks when it is time to send the next PingRequest to the peer.
	PolledTimer pingTimer; // [worker thread]

	/// Tracks when it is time to update the statistics structure.
	PolledTimer statsRefreshTimer; // [worker thread]

	/// Specifies the return value for the functions that send out network packets.
	enum PacketSendResult
	{
		PacketSendOK, ///< The operating system signalled the packet was successfully sent.
		PacketSendSocketClosed, ///< The packet could not be sent, since the socket was closed.
		PacketSendSocketFull, ///< The packet could not be sent, since the OS outbound buffer was full.
		PacketSendNoMessages, ///< A packet could not be sent, since there was nothing to send.
		PacketSendThrottled   ///< The packet could not be sent right now, since a throttle timer is in effect.
	};

	/// Serializes several messages into a single UDP/TCP packet and sends it out to the wire.
	virtual PacketSendResult SendOutPacket() = 0; // [worker thread]

	/// Sends out as many packets at one go as is allowed by the current send rate of the connection.
	virtual void SendOutPackets() = 0; // [worker thread]

	/// Returns how many milliseconds need to be waited before this socket can try sending data the next time.
	virtual unsigned long TimeUntilCanSendPacket() const = 0; // [worker thread]

	/// Performs the internal work tick that updates this connection.
	void UpdateConnection(); // [worker thread]

	/// Overridden by a subclass of MessageConnection to do protocol-specific updates (private implementation -pattern)
	virtual void DoUpdateConnection() {} // [worker thread]

	/// Marks that the peer has closed the connection and will not send any more application-level data.
	void SetPeerClosed(); // [worker thread]

	virtual void DumpConnectionStatus() const {} // [main thread]

	/// Posted when the application has pushed us some messages to handle.
	Event NewOutboundMessagesEvent() const; // [main and worker thread]

	/// Specifies the result of a Socket read activity.
	enum SocketReadResult
	{
		SocketReadOK,        ///< All data was read from the socket and it is empty for now.
		SocketReadError,     ///< An error occurred - probably the connection is dead.
		SocketReadThrottled, ///< There was so much data to read that we need to pause and make room for sends as well.
	};

	/// Reads all the new bytes available in the socket.
	/// This data will be read into the connection's internal data queue, where it will be 
	/// parsed to messages.
	/// @param bytesRead [out] This field will get the number of bytes successfully read.
	/// @return The return code of the operation.
	virtual SocketReadResult ReadSocket(size_t &bytesRead) = 0; // [worker thread]

	SocketReadResult ReadSocket(); // [worker thread]

	/// Sets the worker thread object that will handle this connection.
	void SetWorkerThread(NetworkWorkerThread *thread); // [main thread]

	NetworkWorkerThread *WorkerThread() const { return workerThread; }

	void HandleInboundMessage(packet_id_t packetID, const char *data, size_t numBytes); // [worker thread]

	/// Allocates a new NetworkMessage struct. [both worker and main thread]
	NetworkMessage *AllocateNewMessage();

	// Ping/RTT management operations:
	void SendPingRequestMessage(bool internalQueue); // [main or worker thread]

	void HandlePingRequestMessage(const char *data, size_t numBytes); // [worker thread]

	void HandlePingReplyMessage(const char *data, size_t numBytes); // [worker thread]

	// Frees all internal dynamically allocated message data.
	void FreeMessageData(); // [main thread]

	/// Checks if the connection has been silent too long and has now timed out.
	void DetectConnectionTimeOut(); // [worker thread]

	/// Refreshes RTT and other connection related statistics.
	void ComputeStats(); // [worker thread]
	
	/// Adds a new entry for outbound data statistics.
	void AddOutboundStats(unsigned long numBytes, unsigned long numPackets, unsigned long numMessages); // [worker thread]

	/// Adds a new entry for inbound data statistics.
	void AddInboundStats(unsigned long numBytes, unsigned long numPackets, unsigned long numMessages); // [worker thread]

	/// Pulls in all new messages from the main thread to the worker thread side and admits them to the send priority queue.
	void AcceptOutboundMessages(); // [worker thread]

	/// Starts the socket-specific disconnection procedure.
	virtual void PerformDisconnection() = 0; 

	/// The object that receives notifications of all received data.
	IMessageHandler *inboundMessageHandler; // [main thread]

	/// The underlying socket on top of which this connection operates.
	Socket *socket; // [set by main thread before the worker thread is running. Read-only when worker thread is running. Read by main and worker thread]

	/// Specifies the current connection state.
	ConnectionState connectionState; // [main and worker thread]

	/// If true, all sends to the socket are on hold, until ResumeOutboundSends() is called.
	bool bOutboundSendsPaused; // [set by main thread, read by worker thread]

	friend class NetworkServer;
	friend class Network;

	/// Posted when the application has pushed us some messages to handle.
	Event eventMsgsOutAvailable; // [main and worker thread]

	float rtt; ///< The currently estimated round-trip time, in milliseconds. [main and worker thread]
	tick_t lastHeardTime; ///< The tick since last successful receive from the socket. [main and worker thread]
	float packetsInPerSec; ///< The average number of datagrams we are receiving/second. [main and worker thread]
	float packetsOutPerSec; ///< The average number of datagrams we are sending/second. [main and worker thread]
	float msgsInPerSec; ///< The average number of kNet messages we are receiving/second. [main and worker thread]
	float msgsOutPerSec; ///< The average number of kNet messages we are sending/second. [main and worker thread]
	float bytesInPerSec; ///< The average number of bytes we are receiving/second. This includes kNet headers. [main and worker thread]
	float bytesOutPerSec; ///< The average number of bytes we are sending/second. This includes kNet headers. [main and worker thread]
	u64 bytesInTotal;
	u64 bytesOutTotal;

	/// Stores the current settigns related to network conditions testing.
	/// By default, the simulator is disabled.
	NetworkSimulator networkSendSimulator;

	/// A running number attached to each outbound message (not present in network stream) to 
	/// break ties when deducing which message should come before which.
	unsigned long outboundMessageNumberCounter; // [worker thread]

	/// A running number that is assigned to each outbound reliable message. This is used to
	/// enforce proper ordering of ordered messages.
	unsigned long outboundReliableMessageNumberCounter; // [worker thread]

	/// A (messageID, contentID) pair.
	typedef std::pair<u32, u32> MsgContentIDPair;

	typedef std::map<MsgContentIDPair, std::pair<packet_id_t, tick_t> > ContentIDReceiveTrack;

	/// Each (messageID, contentID) pair has a packetID "stamp" associated to them to track 
	/// and decimate out-of-order received obsoleted messages.
	ContentIDReceiveTrack inboundContentIDStamps; // [worker thread]

	typedef std::map<MsgContentIDPair, NetworkMessage*> ContentIDSendTrack;

	ContentIDSendTrack outboundContentIDMessages; // [worker thread]

	void CheckAndSaveOutboundMessageWithContentID(NetworkMessage *msg); // [worker thread]

	void ClearOutboundMessageWithContentID(NetworkMessage *msg); // [worker thread]

	/// Checks whether the given (messageID, contentID)-pair is already out-of-date and obsoleted
	/// by a newer packet and should not be processed.
	/// @return True if the packet should be processed (there was no superceding record), and
	///         false if the packet is old and should be discarded.
	bool CheckAndSaveContentIDStamp(message_id_t messageID, u32 contentID, packet_id_t packetID); // [worker thread]

	void SplitAndQueueMessage(NetworkMessage *message, bool internalQueue, size_t maxFragmentSize); // [main and worker thread]

	static const unsigned long MsgIdPingRequest = 1;
	static const unsigned long MsgIdPingReply = 2;
	static const unsigned long MsgIdFlowControlRequest = 3;
	static const unsigned long MsgIdPacketAck = 4;
	static const unsigned long MsgIdDisconnect = 0x3FFFFFFF;
	static const unsigned long MsgIdDisconnectAck = 0x3FFFFFFE;

	/// Private ctor - MessageConnections are instantiated by Network and NetworkServer classes.
	explicit MessageConnection(Network *owner, NetworkServer *ownerServer, Socket *socket, ConnectionState startingState);

	virtual bool HandleMessage(packet_id_t /*packetID*/, message_id_t /*messageID*/, const char * /*data*/, size_t /*numBytes*/) { return false; } // [main thread]

private:
	void operator=(const MessageConnection &); ///< Noncopyable, N/I.
	MessageConnection(const MessageConnection &); ///< Noncopyable, N/I.
};

template<typename SerializableData>
void MessageConnection::SendStruct(const SerializableData &data, unsigned long id, bool inOrder, 
		bool reliable, unsigned long priority, unsigned long contentID)
{
	AssertInMainThreadContext();

	const size_t dataSize = data.Size();

	NetworkMessage *msg = StartNewMessage(id, dataSize);

	if (dataSize > 0)
	{
		DataSerializer mb(msg->data, dataSize);
		data.SerializeTo(mb);
		assert(mb.BytesFilled() == dataSize); // The SerializableData::Size() estimate must be exact!
	}

	msg->id = id;
	msg->contentID = contentID;
	msg->inOrder = inOrder;
	msg->priority = priority;
	msg->reliable = reliable;
#ifdef KNET_NETWORK_PROFILING
	char str[512];
	sprintf(str, "%s (%u)", SerializableData::Name(), (unsigned int)id);
	msg->profilerName = str;
#endif

	EndAndQueueMessage(msg);
}

template<typename SerializableMessage>
void MessageConnection::Send(const SerializableMessage &data, unsigned long contentID)
{
	SendStruct(data, SerializableMessage::messageID, data.inOrder, data.reliable, data.priority, contentID);
}

} // ~kNet
