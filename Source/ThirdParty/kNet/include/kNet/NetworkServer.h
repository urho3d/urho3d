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

/** @file NetworkServer.h
	@brief The NetworkServer class. The main class for hosting a kNet server. */

#include <list>

#include "kNetBuildConfig.h"
#include "SharedPtr.h"
#include "Socket.h"
#include "MessageConnection.h"
#include "Datagram.h"
#include "INetworkServerListener.h"
#include "Lockable.h"

namespace kNet
{

class Network;

/// Manages all low-level networking required in maintaining a network server and keeps
/// track of all currently established connections.
/// NetworkServer has the 
class NetworkServer : public RefCountable
{
public:
	/// When destroyed, the NetworkServer closes all the server connections it has.
	~NetworkServer();

	/// Enters a stand-alone processing loop that manages incoming connections until server is shut down.
	void RunModalServer();

	/// Enables or disables whether new connection attempts are allowed.
	void SetAcceptNewConnections(bool acceptNewConnections);

	// Returns whether this server is handling new connection attempts.
	bool AcceptsNewConnections() const { return acceptNewConnections; }

	/// Enables or disables whether rejected connection attempts are messaged back to the client (UDP only).
	/// i.e. whether to message "Connection rejected" back to the peer.
	void SetStealthMode(bool stealthModeEnabled);

	/// Handles all new connection attempts and pulls in new messages from all existing connections.
	/// Periodically call this function to update the NetworkServer object.
	void Process();

	/// Broadcasts the given message to all currently active connections, except for the single 'exclude' connection.
	/// If exclude is 0, all clients will receive the message.
	/// @param msg The message to send.
	/// @param exclude The network connection to exclude from the recipient list. All other clients connected to this
	/// server will get the message. This parameter is useful when you are implementing a server that relays messages
	/// between clients and want to avoid "echoing" the original message back to the client who sent it.
	void BroadcastMessage(const NetworkMessage &msg, MessageConnection *exclude = 0);

	/// Creates a NetworkMessage structure with the given data and broadcasts it to all currently active connections,
	/// except to the given excluded connection.
	void BroadcastMessage(unsigned long id, bool reliable, bool inOrder, unsigned long priority, 
	                      unsigned long contentID, const char *data, size_t numBytes,
	                      MessageConnection *exclude = 0);

	template<typename SerializableData>
	void BroadcastStruct(const SerializableData &data, unsigned long id, bool inOrder, 
		bool reliable, unsigned long priority, unsigned long contentID = 0, MessageConnection *exclude = 0);

	template<typename SerializableMessage>
	void Broadcast(const SerializableMessage &data, unsigned long contentID = 0, MessageConnection *exclude = 0);

	/// Sends the given message to the given destination.
	void SendMessage(const NetworkMessage &msg, MessageConnection &destination);

	/// Starts a benign disconnection procedure for all clients (write-closes each connection).
	/// Also calls SetAcceptNewConnections(false), since this function is intended to be used when the server is going down.
	/// It can take an indefinite time for the connections to bidirectionally close, since it is up to the individual
	/// clients to write-close their end of the connections. This function returns immediately.
	void DisconnectAllClients();
		
	/// Forcibly closes down the server. Calls SetAcceptNewConnections(false) so that no new connections are accepted.
	/// @param disconnectWaitMilliseconds If >0, this function calls DisconnectAllClients() and waits for the given amount
	///         of time until calling Close() on each client connection. If 0, MessageConnection::Close(0) will be immediately
	///         called on each client. In that case, this function returns immediately and all active clients will be left
	///         to time out at their end. Calling this function does not guarantee that all outbound data will be received
	///         by the peers.
	void Close(int disconnectWaitMilliseconds);
	
	/// Forcibly erases the given connection from the active connection list. The client will be left to time out.
	void ConnectionClosed(MessageConnection *connection);

	/// Returns all the sockets this server is listening on.
	std::vector<Socket *> &ListenSockets();

	typedef std::map<EndPoint, Ptr(MessageConnection)> ConnectionMap;

	/// Returns all the currently tracked connections.
	ConnectionMap GetConnections();

	/// Returns the number of currently active connections. A connection is active if it is at least read- or write-open.
	int NumConnections() const;

	/// Returns a one-liner textual summary of this server.
	std::string ToString() const;

private:
	/// Private ctor - NetworkServer instances are created by the Network class.
	NetworkServer(Network *owner, std::vector<Socket *> listenSockets);

	/// We store possibly multiple listening sockets so that the server
	/// can listen on several sockets (UDP or TCP) at once, making it
	/// possible for clients to bypass firewalls and/or mix UDP and TCP use.
	std::vector<Socket *> listenSockets;

	/// The list of active client connections.
	Lockable<ConnectionMap> clients;

	/// The Network object this NetworkServer was spawned from.
	Network *owner;

	/// Stores the thread that manages the background processing of this server. The same thread can manage multiple
	/// connections and servers, and not just this one.
	NetworkWorkerThread *workerThread; // [set and read only by worker thread]

#ifdef KNET_THREAD_CHECKING_ENABLED
	/// In debug mode, we track and enforce thread safety constraints through this ID. 
	ThreadId workerThreadId; // [set by worker thread on thread startup, read by both main and worker thread]
#endif

	/// If true, new connection attempts are processed. Otherwise, just discard all connection packets.
	bool acceptNewConnections;

	INetworkServerListener *networkServerListener;

	/// Sets the worker thread object that will handle this server.
	void SetWorkerThread(NetworkWorkerThread *thread); // [main thread]

	NetworkWorkerThread *WorkerThread() const { return workerThread; }

	/// If the server is running in UDP mode, the listenSocket is the socket that receives all application data.
	/// This function pulls all new data from the socket and sends it to MessageConnection instances for deserialization and processing.
	void ReadUDPSocketData(Socket *listenSocket); // [worker thread]

	void RegisterServerListener(INetworkServerListener *listener);

	/// Shuts down all listen sockets used by this server.
	/// This function is to be called only at destruction time when no network communication is being performed anymore.
	void CloseSockets();

	void CleanupDeadConnections();

	Socket *AcceptConnections(Socket *listenSocket);

	struct ConnectionAttemptDescriptor
	{
		Socket *listenSocket;
		EndPoint peer;
		Datagram data;
	};

	WaitFreeQueue<ConnectionAttemptDescriptor> udpConnectionAttempts;

	/// Called from the network worker thread.
	void EnqueueNewUDPConnectionAttempt(Socket *listenSocket, const EndPoint &endPoint, const char *data, size_t numBytes);

	bool ProcessNewUDPConnectionAttempt(Socket *listenSocket, const EndPoint &endPoint, const char *data, size_t numBytes);

	friend class Network;
	friend class NetworkWorkerThread;
};

template<typename SerializableData>
void NetworkServer::BroadcastStruct(const SerializableData &data, unsigned long id, bool inOrder, 
	bool reliable, unsigned long priority, unsigned long contentID, MessageConnection *exclude)
{
	PolledTimer timer;
	Lockable<ConnectionMap>::LockType clientsLock = clients.Acquire();
	if (timer.MSecsElapsed() >= 50.f)
	{
		KNET_LOG(LogWaits, "NetworkServer::BroadcastMessage: Accessing the connection list took %f msecs.",
			timer.MSecsElapsed());
	}

	const size_t dataSize = data.Size();

	for(ConnectionMap::iterator iter = clientsLock->begin(); iter != clientsLock->end(); ++iter)
	{
		MessageConnection *connection = iter->second;
		assert(connection);
		if (connection == exclude || !connection->IsWriteOpen())
			continue;

		NetworkMessage *msg = connection->StartNewMessage(id, dataSize);

		if (dataSize > 0)
		{
			DataSerializer mb(msg->data, dataSize);
			data.SerializeTo(mb);
			assert(mb.BytesFilled() == dataSize); // The SerializableData::Size() estimate must be exact!
		}

		msg->id = id;
		msg->reliable = reliable;
		msg->inOrder = inOrder;
		msg->priority = priority;
		msg->contentID = contentID;

#ifdef KNET_NETWORK_PROFILING
		char str[512];
		sprintf(str, "%s (%u)", SerializableData::Name(), (unsigned int)id);
		msg->profilerName = str;
#endif

		connection->EndAndQueueMessage(msg);
	}
}

template<typename SerializableMessage>
void NetworkServer::Broadcast(const SerializableMessage &data, unsigned long contentID, MessageConnection *exclude)
{
	BroadcastStruct(data, SerializableMessage::messageID, data.inOrder, data.reliable, data.priority, contentID, exclude);
}

} // ~kNet
