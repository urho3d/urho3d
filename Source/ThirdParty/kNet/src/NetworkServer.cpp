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

/** @file NetworkServer.cpp
	@brief */

#ifdef KNET_USE_BOOST
#include <boost/thread/thread.hpp>
#endif
#ifdef KNET_UNIX
#include <unistd.h>
#endif
#include "kNet/DebugMemoryLeakCheck.h"

#include "kNet/Network.h"
#include "kNet/NetworkServer.h"
#include "kNet/TCPMessageConnection.h"
#include "kNet/UDPMessageConnection.h"
#include "kNet/Datagram.h"
#include "kNet/NetworkWorkerThread.h"
#include "kNet/NetworkLogging.h"
#include "kNet/Clock.h"

#include <iostream>
#include <sstream>

namespace kNet
{

NetworkServer::NetworkServer(Network *owner_, std::vector<Socket *> listenSockets_)
:listenSockets(listenSockets_), 
owner(owner_), 
workerThread(0), 
#ifdef KNET_THREAD_CHECKING_ENABLED
workerThreadId(Thread::NullThreadId()),
#endif
acceptNewConnections(true), 
networkServerListener(0),
udpConnectionAttempts(64)
{
	assert(owner);
	assert(!listenSockets.empty());
}

NetworkServer::~NetworkServer()
{
	KNET_LOG(LogObjectAlloc, "Deleting NetworkServer %p.", this);
	CloseSockets();
}

void NetworkServer::RegisterServerListener(INetworkServerListener *listener)
{
	networkServerListener = listener;
}

void NetworkServer::SetAcceptNewConnections(bool acceptNewConnections_)
{
	acceptNewConnections = acceptNewConnections_;
}

void NetworkServer::SetWorkerThread(NetworkWorkerThread *thread) // [main thread]
{
	workerThread = thread;
#ifdef KNET_THREAD_CHECKING_ENABLED
	workerThreadId = thread ? thread->ThreadObject().Id() : Thread::NullThreadId();
#endif
}

void NetworkServer::CloseSockets()
{
	KNET_LOG(LogInfo, "NetworkServer::CloseSockets(): Network server is terminated. (%p)", this);
	assert(owner);

	acceptNewConnections = false;

	for(size_t i = 0; i < listenSockets.size(); ++i)
		owner->DeleteSocket(listenSockets[i]); 

	// Now forget all sockets - not getting them back in any way.
	listenSockets.clear();
}

Socket *NetworkServer::AcceptConnections(Socket *listenSocket)
{
	if (!listenSocket || !listenSocket->Connected())
		return 0;

	sockaddr_in remoteAddress;
	memset(&remoteAddress, 0, sizeof(remoteAddress));
	socklen_t remoteAddressLen = sizeof(remoteAddress);
	SOCKET &listenSock = listenSocket->GetSocketHandle();
	SOCKET acceptSocket = accept(listenSock, (sockaddr*)&remoteAddress, &remoteAddressLen);
	if (acceptSocket == KNET_ACCEPT_FAILURE)
	{
		int error = Network::GetLastError();
		if (error != KNET_EWOULDBLOCK)
		{
			KNET_LOG(LogError, "NetworkServer::AcceptConnections: accept failed: %s", Network::GetErrorString(error).c_str());
			closesocket(listenSock);
			listenSock = INVALID_SOCKET;
		}
		return 0;
	}

	EndPoint remoteEndPoint = EndPoint::FromSockAddrIn(remoteAddress);
	std::string remoteHostName = remoteEndPoint.IPToString();

	KNET_LOG(LogInfo, "Accepted incoming TCP connection from %s:%d.", remoteHostName.c_str(), (int)remoteEndPoint.port);

	EndPoint localEndPoint;
	sockaddr_in localSockAddr;
	socklen_t namelen = sizeof(localSockAddr);
	int sockRet = getsockname(acceptSocket, (sockaddr*)&localSockAddr, &namelen); // Note: This works only if family==INETv4
	if (sockRet != 0)
		KNET_LOG(LogError, "getsockname failed!");
	localEndPoint = EndPoint::FromSockAddrIn(localSockAddr);
	std::string localHostName = owner->LocalAddress();

	const size_t maxTcpSendSize = 65536;
	Socket *socket = owner->StoreSocket(Socket(acceptSocket, localEndPoint, localHostName.c_str(), remoteEndPoint, remoteHostName.c_str(), SocketOverTCP, ServerClientSocket, maxTcpSendSize));
	socket->SetBlocking(false);

	return socket;
}

void NetworkServer::CleanupDeadConnections()
{
	// When we acquire the list of client connections, don't hold on to it for long, so that the worker thread can properly detach from it.
	ConnectionMap clientsMap = *clients.Acquire();

	// Clean up all disconnected/timed out connections.
	ConnectionMap::iterator iter = clientsMap.begin();
	while(iter != clientsMap.end())
	{
		ConnectionMap::iterator next = iter;
		++next;
		if (!iter->second->Connected())
		{
			KNET_LOG(LogInfo, "Client %s disconnected.", iter->second->ToString().c_str());
			if (networkServerListener)
				networkServerListener->ClientDisconnected(iter->second);
			if (iter->second->GetSocket() && iter->second->GetSocket()->TransportLayer() == SocketOverTCP)
				owner->CloseConnection(iter->second);

			{
				Lockable<ConnectionMap>::LockType clientsLock = clients.Acquire();
				clientsLock->erase(iter->first);
			}
		}
		iter = next;
	}
}

void NetworkServer::Process()
{
	CleanupDeadConnections();

	for(size_t i = 0; i < listenSockets.size(); ++i)
	{
		Socket *listen = listenSockets[i];

		if (listen->TransportLayer() == SocketOverTCP)
		{
			// Accept the first inbound connection.
			Socket *client = AcceptConnections(listen);
			if (client)
			{
				if (!client->Connected())
					KNET_LOG(LogError, "Warning: Accepted an already closed connection!");

				KNET_LOG(LogInfo, "Client connected from %s.", client->ToString().c_str());

				// Build a MessageConnection on top of the raw socket.
				assert(listen->TransportLayer() == SocketOverTCP);
				Ptr(MessageConnection) clientConnection = new TCPMessageConnection(owner, this, client, ConnectionOK);
				assert(owner);
				owner->AssignConnectionToWorkerThread(clientConnection);

				if (networkServerListener)
					networkServerListener->NewConnectionEstablished(clientConnection);

				{
					PolledTimer timer;
					Lockable<ConnectionMap>::LockType clientsLock = clients.Acquire();
					(*clientsLock)[clientConnection->RemoteEndPoint()] = clientConnection;
					KNET_LOG(LogWaits, "NetworkServer::Process: Adding new accepted TCP connection to connection list took %f msecs.",
						timer.MSecsElapsed());
				}

				owner->NewMessageConnectionCreated(clientConnection);
			}
		}
	}

	// Note that the above loop will only accept one new connection/socket/iteration, so if there are multiple
	// pending new connections, they will only get accepted at a rate of one per each frame.

	// Process a new UDP connection attempt.
	ConnectionAttemptDescriptor *desc = udpConnectionAttempts.Front();
	if (desc)
	{
		ProcessNewUDPConnectionAttempt(desc->listenSocket, desc->peer, (const char *)desc->data.data, desc->data.size);
		udpConnectionAttempts.PopFront();
	}

	// Process all new inbound data for each connection handled by this server.
	ConnectionMap clientMap = *clients.Acquire();
	for(ConnectionMap::iterator iter = clientMap.begin(); iter != clientMap.end(); ++iter)
		iter->second->Process();
}

void NetworkServer::ReadUDPSocketData(Socket *listenSocket) // [worker thread]
{
	using namespace std;

	assert(listenSocket);

	OverlappedTransferBuffer *recvData = listenSocket->BeginReceive();
	if (!recvData)
		return; // No datagram available, return.
	if (recvData->bytesContains == 0)
	{
		listenSocket->EndReceive(recvData);
		KNET_LOG(LogError, "Received 0 bytes of data in NetworkServer::ReadUDPSocketData!");
		return;
	}
	EndPoint endPoint = EndPoint::FromSockAddrIn(recvData->from); // This conversion is quite silly, perhaps it could be removed to gain performance?
	KNET_LOG(LogData, "Received a datagram of size %d to socket %s from endPoint %s.", recvData->bytesContains, listenSocket->ToString().c_str(),
		endPoint.ToString().c_str());

	PolledTimer timer;
	MessageConnection *receiverConnection = 0;

	{
		Lockable<ConnectionMap>::LockType clientsLock = clients.Acquire();
		if (timer.MSecsElapsed() > 50.f)
		{
			KNET_LOG(LogWaits, "NetworkServer::ReadUDPSocketData: Accessing the connection list in UDP server receive code took %f msecs.",
			timer.MSecsElapsed());
		}

		ConnectionMap::iterator iter = clientsLock->find(endPoint); ///\todo HashTable for performance.
		if (iter != clientsLock->end())
			receiverConnection = iter->second;
	}

	if (receiverConnection)
	{
		// If the datagram came from a known endpoint, pass it to the connection object that handles that endpoint.
		UDPMessageConnection *udpConnection = dynamic_cast<UDPMessageConnection *>(receiverConnection);
		if (udpConnection)
			udpConnection->QueueInboundDatagram(recvData->buffer.buf, recvData->bytesContains);
		else
			KNET_LOG(LogError, "Critical! UDP socket data received into a TCP socket!");
	}
	else
	{
		// The endpoint for this datagram is not known, deserialize it as a new connection attempt packet.
		EnqueueNewUDPConnectionAttempt(listenSocket, endPoint, recvData->buffer.buf, recvData->bytesContains);
	}
	listenSocket->EndReceive(recvData);
}

void NetworkServer::EnqueueNewUDPConnectionAttempt(Socket *listenSocket, const EndPoint &endPoint, const char *data, size_t numBytes)
{
	ConnectionAttemptDescriptor desc;
	desc.data.size = std::min<int>(cDatagramBufferSize, numBytes);
	memcpy(&desc.data.data[0], data, desc.data.size);
	desc.peer = endPoint;
	desc.listenSocket = listenSocket;

	///\todo Check IP banlist.
	///\todo Check that the maximum number of active concurrent connections is not exceeded.

	bool success = udpConnectionAttempts.Insert(desc);
	if (!success)
		KNET_LOG(LogError, "Too many connection attempts!");
	else
		KNET_LOG(LogInfo, "Queued new connection attempt from %s.", endPoint.ToString().c_str());
}

bool NetworkServer::ProcessNewUDPConnectionAttempt(Socket *listenSocket, const EndPoint &endPoint, const char *data, size_t numBytes)
{
	KNET_LOG(LogInfo, "New inbound connection attempt from %s with datagram of size %d.", endPoint.ToString().c_str(), (int)numBytes);
	if (!acceptNewConnections)
	{
		KNET_LOG(LogError, "Ignored a new connection attempt since server is set not to accept new connections.");
		return false;
	}

	// Pass the datagram contents to a callback that decides whether this connection is allowed.
	if (networkServerListener)
	{
		bool connectionAccepted = networkServerListener->NewConnectionAttempt(endPoint, data, numBytes);
		if (!connectionAccepted)
		{
			KNET_LOG(LogError, "Server listener did not accept the new connection.");
			return false;
		}
	}

	///\todo Check IP banlist.
	///\todo Check that the maximum number of active concurrent connections is not exceeded.

	std::string remoteHostName = endPoint.IPToString();

	// Accept the connection and create a new UDP socket that communicates to that endpoint.
	Socket *socket = owner->CreateUDPSlaveSocket(listenSocket, endPoint, remoteHostName.c_str());
	if (!socket)
	{
		KNET_LOG(LogError, "Network::ConnectUDP failed! Cannot accept new UDP connection.");
		return false;
	}

	UDPMessageConnection *udpConnection = new UDPMessageConnection(owner, this, socket, ConnectionOK);
	Ptr(MessageConnection) connection(udpConnection);
	{
		PolledTimer timer;
		Lockable<ConnectionMap>::LockType clientsLock = clients.Acquire();
		if (clientsLock->find(endPoint) == clientsLock->end())
			(*clientsLock)[endPoint] = connection;
		else
			KNET_LOG(LogError, "NetworkServer::ProcessNewUDPConnectionAttempt: Trying to overwrite an old connection with a new one! Discarding connection attempt datagram!",
				timer.MSecsElapsed());


		KNET_LOG(LogWaits, "NetworkServer::ProcessNewUDPConnectionAttempt: Accessing the connection list took %f msecs.",
			timer.MSecsElapsed());
	}

	// Pass the MessageConnection to the main application so it can hook the inbound packet stream.
	if (networkServerListener)
		networkServerListener->NewConnectionEstablished(connection);

	connection->SendPingRequestMessage(false);

	owner->AssignConnectionToWorkerThread(connection);

	owner->NewMessageConnectionCreated(connection);

	KNET_LOG(LogInfo, "Accepted new UDP connection.");
	return true;
}

void NetworkServer::BroadcastMessage(const NetworkMessage &msg, MessageConnection *exclude)
{
	PolledTimer timer;
	Lockable<ConnectionMap>::LockType clientsLock = clients.Acquire();
	if (timer.MSecsElapsed() >= 50.f)
	{
		KNET_LOG(LogWaits, "NetworkServer::BroadcastMessage: Accessing the connection list took %f msecs.",
			timer.MSecsElapsed());
	}

	for(ConnectionMap::iterator iter = clientsLock->begin(); iter != clientsLock->end(); ++iter)
	{
		MessageConnection *connection = iter->second;
		if (connection == exclude)
			continue;

		SendMessage(msg, *connection);
	}
}

void NetworkServer::BroadcastMessage(unsigned long id, bool reliable, bool inOrder, unsigned long priority, 
                                     unsigned long contentID, const char *data, size_t numBytes,
                                     MessageConnection *exclude)
{
	PolledTimer timer;
	Lockable<ConnectionMap>::LockType clientsLock = clients.Acquire();
	if (timer.MSecsElapsed() >= 50.f)
	{
		KNET_LOG(LogWaits, "NetworkServer::BroadcastMessage: Accessing the connection list took %f msecs.",
			timer.MSecsElapsed());
	}

	for(ConnectionMap::iterator iter = clientsLock->begin(); iter != clientsLock->end(); ++iter)
	{
		MessageConnection *connection = iter->second;
		assert(connection);
		if (connection == exclude || !connection->IsWriteOpen())
			continue;

		NetworkMessage *msg = connection->StartNewMessage(id, numBytes);
		msg->reliable = reliable;
		msg->inOrder = inOrder;
		msg->priority = priority;
		msg->contentID = contentID;
		assert(msg->data);
		assert(msg->Size() == numBytes);
		memcpy(msg->data, data, numBytes);
		connection->EndAndQueueMessage(msg);
	}
}

void NetworkServer::SendMessage(const NetworkMessage &msg, MessageConnection &destination)
{
	if (!destination.IsWriteOpen())
		return;

	NetworkMessage *cloned = destination.StartNewMessage(msg.id);
	*cloned = msg;
	destination.EndAndQueueMessage(cloned);
}

void NetworkServer::DisconnectAllClients()
{
	SetAcceptNewConnections(false);

	PolledTimer timer;
	Lockable<ConnectionMap>::LockType clientsLock = clients.Acquire();
	KNET_LOG(LogWaits, "NetworkServer::DisconnectAllClients: Accessing the connection list took %f msecs.",
		timer.MSecsElapsed());

	for(ConnectionMap::iterator iter = clientsLock->begin(); iter != clientsLock->end(); ++iter)
		iter->second->Disconnect(0); // Do not wait for any client.
}

void NetworkServer::Close(int disconnectWaitMilliseconds)
{
	DisconnectAllClients();

	///\todo Re-implement this function to remove the monolithic Sleep here. Instead of this,
	/// wait for the individual connections to finish.
	if (GetConnections().size() > 0)
	{
		Clock::Sleep(disconnectWaitMilliseconds);
		KNET_LOG(LogVerbose, "NetworkServer::Close: Waited a fixed period of %d msecs for all connections to disconnect.",
			disconnectWaitMilliseconds);
	}

	PolledTimer timer;
	Lockable<ConnectionMap>::LockType clientsLock = clients.Acquire();
	KNET_LOG(LogWaits, "NetworkServer::Close: Accessing the connection list took %f msecs.",
		timer.MSecsElapsed());
	for(ConnectionMap::iterator iter = clientsLock->begin(); iter != clientsLock->end(); ++iter)
		iter->second->Close(0); // Do not wait for any client.
}

void NetworkServer::RunModalServer()
{
	assert(this);

	///\todo Loop until StopModalServer() is called.
	for(;;)
	{
		Process();

		///\todo WSACreateEvent/WSAWaitForMultipleEvents for improved responsiveness and performance.
		Clock::Sleep(1);
	}
}

void NetworkServer::ConnectionClosed(MessageConnection *connection)
{
	PolledTimer timer;
	Lockable<ConnectionMap>::LockType clientsLock = clients.Acquire();
	KNET_LOG(LogWaits, "NetworkServer::ConnectionClosed: Accessing the connection list took %f msecs.",
		timer.MSecsElapsed());
	for(ConnectionMap::iterator iter = clientsLock->begin(); iter != clientsLock->end(); ++iter)
		if (iter->second == connection)
		{
			if (networkServerListener)
				networkServerListener->ClientDisconnected(connection);

			if (connection->GetSocket() && connection->GetSocket()->TransportLayer() == SocketOverTCP)
			{
				owner->DeleteSocket(connection->socket);
				connection->socket = 0;
			}

			clientsLock->erase(iter);

			return;
		}

	KNET_LOG(LogError, "Unknown MessageConnection passed to NetworkServer::Disconnect!");
}

std::vector<Socket *> &NetworkServer::ListenSockets()
{
	return listenSockets;
}

NetworkServer::ConnectionMap NetworkServer::GetConnections()
{
	PolledTimer timer;
	Lockable<ConnectionMap>::LockType lock = clients.Acquire();
	if (timer.MSecsElapsed() > 50.f)
	{
		KNET_LOG(LogWaits, "NetworkServer::GetConnections: Accessing the connection list took %f msecs.",
			timer.MSecsElapsed());
	}
	return *lock;
}

int NetworkServer::NumConnections() const
{
	int numConnections = 0;
	Lockable<ConnectionMap>::ConstLockType lock = clients.Acquire();
	for(ConnectionMap::const_iterator iter = lock->begin(); iter != lock->end(); ++iter)
	{
		const MessageConnection *connection = iter->second.ptr();
		if (connection && (connection->IsPending() || connection->IsReadOpen() || connection->IsWriteOpen()))
			++numConnections;
	}
	return numConnections;
}

std::string NetworkServer::ToString() const
{
	bool isUdp = false;
	bool isTcp = false;
	for(size_t i = 0; i < listenSockets.size(); ++i)
		if (listenSockets[i]->TransportLayer() == SocketOverUDP)
			isUdp = true;
		else
			isTcp = true;

	std::stringstream ss;
	if (isUdp && isTcp)
		ss << "TCP+UDP server";
	else if (isUdp)
		ss << "UDP server";
	else if (isTcp)
		ss << "TCP server";
	else ss << "Server (no listen sockets open)";

	if (listenSockets.size() == 1)
	{
		int port = (int)listenSockets[0]->LocalPort();
		ss << " at local port " << port;
	}
	else if (listenSockets.size() > 1)
	{
		ss << " (" << (int)listenSockets.size() << " listen sockets at local ports ";
		for(size_t i = 0; i < listenSockets.size() && i < 3; ++i)
		{
			if (i > 0)
				ss << ", ";
			ss << listenSockets[i]->LocalPort();
		}
		if (listenSockets.size() > 3)
			ss << ", ...";
		ss << ")";
	}
	ss << ": ";

	int numConnections = 0;
	{
		Lockable<ConnectionMap>::ConstLockType lock = clients.Acquire();
		numConnections = lock->size();
	}
	ss << numConnections << " connections.";

	if (!acceptNewConnections)
		ss << " (not accepting new connections)";

	///\todo Add note about stealth mode.

	return ss.str();
}

} // ~kNet
