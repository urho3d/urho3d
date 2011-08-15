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

// Modified by Lasse Öörni for Urho3D

#ifdef KNET_USE_BOOST
#include <boost/thread/thread.hpp>
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

NetworkServer::NetworkServer(Network *owner_, Vector<Socket *> listenSockets_)
:owner(owner_), listenSockets(listenSockets_), acceptNewConnections(true), networkServerListener(0),
udpConnectionAttempts(64), workerThread(0)
#ifdef KNET_THREAD_CHECKING_ENABLED
,workerThreadId(Thread::NullThreadId())
#endif
{
	assert(owner);
	assert(listenSockets.Size() > 0);
}

NetworkServer::~NetworkServer()
{
	LOG(LogObjectAlloc, "Deleting NetworkServer %p.", this);
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

void NetworkServer::CloseListenSockets()
{
	assert(owner);

	for(size_t i = 0; i < listenSockets.Size(); ++i)
	{
		if (listenSockets[i]->TransportLayer() == SocketOverUDP)
			acceptNewConnections = false; ///\todo At this point, if in UDP mode, we should have destroyed all connections that use this socket!
		else
			owner->DeleteSocket(listenSockets[i]); 
	}

	// Now forget all sockets - not getting them back in any way.
	listenSockets.Clear();
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
			LOG(LogError, "NetworkServer::AcceptConnections: accept failed: %s", Network::GetErrorString(error).CString());
			closesocket(listenSock);
			listenSock = INVALID_SOCKET;
		}
		return 0;
	}

	EndPoint remoteEndPoint = EndPoint::FromSockAddrIn(remoteAddress);
	String remoteHostName = remoteEndPoint.IPToString();

	LOG(LogInfo, "Accepted incoming TCP connection from %s:%d.", remoteHostName.CString(), (int)remoteEndPoint.port);

	EndPoint localEndPoint;
	sockaddr_in localSockAddr;
	socklen_t namelen = sizeof(localSockAddr);
	int sockRet = getsockname(acceptSocket, (sockaddr*)&localSockAddr, &namelen); // Note: This works only if family==INETv4
	localEndPoint = EndPoint::FromSockAddrIn(localSockAddr);
	String localHostName = owner->LocalAddress();

	const size_t maxTcpSendSize = 65536;
	Socket *socket = owner->StoreSocket(Socket(acceptSocket, localEndPoint, localHostName.CString(), remoteEndPoint, remoteHostName.CString(), SocketOverTCP, ServerClientSocket, maxTcpSendSize));
	socket->SetBlocking(false);

	return socket;
}

void NetworkServer::CleanupDeadConnections()
{
	// When we acquire the list of client connections, don't hold on to it for long, so that the worker thread can properly detach from it.
	ConnectionMap clientsMap = *clients.Acquire();

	// Clean up all disconnected/timed out connections.
	ConnectionMap::Iterator iter = clientsMap.Begin();
	while(iter != clientsMap.End())
	{
		ConnectionMap::Iterator next = iter;
		++next;
		if (!iter->second_->Connected())
		{
			LOG(LogInfo, "Client %s disconnected.", iter->second_->ToString().CString());
			if (networkServerListener)
				networkServerListener->ClientDisconnected(iter->second_);
			if (iter->second_->GetSocket() && iter->second_->GetSocket()->TransportLayer() == SocketOverTCP)
				owner->CloseConnection(iter->second_);

			{
				Lockable<ConnectionMap>::LockType clientsLock = clients.Acquire();
				clientsLock->Erase(iter->first_);
			}
		}
		iter = next;
	}
}

void NetworkServer::Process()
{
	CleanupDeadConnections();

	for(size_t i = 0; i < listenSockets.Size(); ++i)
	{
		Socket *listen = listenSockets[i];

		if (listen->TransportLayer() == SocketOverTCP)
		{
			// Accept the first inbound connection.
			Socket *client = AcceptConnections(listen);
			if (client)
			{
				if (!client->Connected())
					LOG(LogError, "Warning: Accepted an already closed connection!");

				LOG(LogInfo, "Client connected from %s.", client->ToString().CString());

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
					LOG(LogWaits, "NetworkServer::Process: Adding new accepted TCP connection to connection list took %f msecs.",
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
	for(ConnectionMap::Iterator iter = clientMap.Begin(); iter != clientMap.End(); ++iter)
		iter->second_->Process();
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
		LOG(LogError, "Received 0 bytes of data in NetworkServer::ReadUDPSocketData!");
		return;
	}
	EndPoint endPoint = EndPoint::FromSockAddrIn(recvData->from); // This conversion is quite silly, perhaps it could be removed to gain performance?
	LOG(LogData, "Received a datagram of size %d to socket %s from endPoint %s.", recvData->bytesContains, listenSocket->ToString().CString(),
		endPoint.ToString().CString());

	PolledTimer timer;
	MessageConnection *receiverConnection = 0;

	{
		Lockable<ConnectionMap>::LockType clientsLock = clients.Acquire();
		if (timer.MSecsElapsed() > 50.f)
		{
			LOG(LogWaits, "NetworkServer::ReadUDPSocketData: Accessing the connection list in UDP server receive code took %f msecs.",
			timer.MSecsElapsed());
		}

		ConnectionMap::Iterator iter = clientsLock->Find(endPoint); ///\todo HashTable for performance.
		if (iter != clientsLock->End())
			receiverConnection = iter->second_;
	}

	if (receiverConnection)
	{
		// If the datagram came from a known endpoint, pass it to the connection object that handles that endpoint.
		UDPMessageConnection *udpConnection = dynamic_cast<UDPMessageConnection *>(receiverConnection);
		if (udpConnection)
			udpConnection->QueueInboundDatagram(recvData->buffer.buf, recvData->bytesContains);
		else
			LOG(LogError, "Critical! UDP socket data received into a TCP socket!");
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
		LOG(LogError, "Too many connection attempts!");
	else
		LOG(LogInfo, "Queued new connection attempt from %s.", endPoint.ToString().CString());
}

bool NetworkServer::ProcessNewUDPConnectionAttempt(Socket *listenSocket, const EndPoint &endPoint, const char *data, size_t numBytes)
{
	LOG(LogInfo, "New inbound connection attempt from %s with datagram of size %d.", endPoint.ToString().CString(), (int)numBytes);
	if (!acceptNewConnections)
	{
		LOG(LogError, "Ignored a new connection attempt since server is set not to accept new connections.");
		return false;
	}

	// Pass the datagram contents to a callback that decides whether this connection is allowed.
	if (networkServerListener)
	{
		bool connectionAccepted = networkServerListener->NewConnectionAttempt(endPoint, data, numBytes);
		if (!connectionAccepted)
		{
			LOG(LogError, "Server listener did not accept the new connection.");
			return false;
		}
	}

	///\todo Check IP banlist.
	///\todo Check that the maximum number of active concurrent connections is not exceeded.

	String remoteHostName = endPoint.IPToString();

	// Accept the connection and create a new UDP socket that communicates to that endpoint.
	Socket *socket = owner->CreateUDPSlaveSocket(listenSocket, endPoint, remoteHostName.CString());
	if (!socket)
	{
		LOG(LogError, "Network::ConnectUDP failed! Cannot accept new UDP connection.");
		return false;
	}

	UDPMessageConnection *udpConnection = new UDPMessageConnection(owner, this, socket, ConnectionOK);
	Ptr(MessageConnection) connection(udpConnection);
	{
		PolledTimer timer;
		Lockable<ConnectionMap>::LockType clientsLock = clients.Acquire();
		(*clientsLock)[endPoint] = connection;

		LOG(LogWaits, "NetworkServer::ProcessNewUDPConnectionAttempt: Accessing the connection list took %f msecs.",
			timer.MSecsElapsed());
	}

	// Pass the MessageConnection to the main application so it can hook the inbound packet stream.
	if (networkServerListener)
		networkServerListener->NewConnectionEstablished(connection);

	connection->SendPingRequestMessage(false);

	owner->AssignConnectionToWorkerThread(connection);

	owner->NewMessageConnectionCreated(connection);

	LOG(LogInfo, "Accepted new UDP connection.");
	return true;
}

void NetworkServer::BroadcastMessage(const NetworkMessage &msg, MessageConnection *exclude)
{
	PolledTimer timer;
	Lockable<ConnectionMap>::LockType clientsLock = clients.Acquire();
	if (timer.MSecsElapsed() >= 50.f)
	{
		LOG(LogWaits, "NetworkServer::BroadcastMessage: Accessing the connection list took %f msecs.",
			timer.MSecsElapsed());
	}

	for(ConnectionMap::Iterator iter = clientsLock->Begin(); iter != clientsLock->End(); ++iter)
	{
		MessageConnection *connection = iter->second_;
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
		LOG(LogWaits, "NetworkServer::BroadcastMessage: Accessing the connection list took %f msecs.",
			timer.MSecsElapsed());
	}

	for(ConnectionMap::Iterator iter = clientsLock->Begin(); iter != clientsLock->End(); ++iter)
	{
		MessageConnection *connection = iter->second_;
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
	LOG(LogWaits, "NetworkServer::DisconnectAllClients: Accessing the connection list took %f msecs.",
		timer.MSecsElapsed());

	for(ConnectionMap::Iterator iter = clientsLock->Begin(); iter != clientsLock->End(); ++iter)
		iter->second_->Disconnect(0); // Do not wait for any client.
}

void NetworkServer::Close(int disconnectWaitMilliseconds)
{
	DisconnectAllClients();

	///\todo Re-implement this function to remove the monolithic Sleep here. Instead of this,
	/// wait for the individual connections to finish.
	if (GetConnections().Size() > 0)
	{
		Clock::Sleep(disconnectWaitMilliseconds);
		LOG(LogVerbose, "NetworkServer::Close: Waited a fixed period of %d msecs for all connections to disconnect.",
			disconnectWaitMilliseconds);
	}

	PolledTimer timer;
	Lockable<ConnectionMap>::LockType clientsLock = clients.Acquire();
	LOG(LogWaits, "NetworkServer::Close: Accessing the connection list took %f msecs.",
		timer.MSecsElapsed());
	for(ConnectionMap::Iterator iter = clientsLock->Begin(); iter != clientsLock->End(); ++iter)
		iter->second_->Close(0); // Do not wait for any client.
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
	LOG(LogWaits, "NetworkServer::ConnectionClosed: Accessing the connection list took %f msecs.",
		timer.MSecsElapsed());
	for(ConnectionMap::Iterator iter = clientsLock->Begin(); iter != clientsLock->End(); ++iter)
		if (iter->second_ == connection)
		{
			if (networkServerListener)
				networkServerListener->ClientDisconnected(connection);

			if (connection->GetSocket() && connection->GetSocket()->TransportLayer() == SocketOverTCP)
			{
				owner->DeleteSocket(connection->socket);
				connection->socket = 0;
			}

			clientsLock->Erase(iter);

			return;
		}

	LOG(LogError, "Unknown MessageConnection passed to NetworkServer::Disconnect!");
}

Vector<Socket *> &NetworkServer::ListenSockets()
{
	return listenSockets;
}

NetworkServer::ConnectionMap NetworkServer::GetConnections()
{
	PolledTimer timer;
	Lockable<ConnectionMap>::LockType lock = clients.Acquire();
	if (timer.MSecsElapsed() > 50.f)
	{
		LOG(LogWaits, "NetworkServer::GetConnections: Accessing the connection list took %f msecs.",
			timer.MSecsElapsed());
	}
	return *lock;
}

int NetworkServer::NumConnections() const
{
	int numConnections = 0;
	Lockable<ConnectionMap>::ConstLockType lock = clients.Acquire();
	for(ConnectionMap::ConstIterator iter = lock->Begin(); iter != lock->End(); ++iter)
	{
		const MessageConnection *connection = iter->second_.ptr();
		if (connection && (connection->IsPending() || connection->IsReadOpen() || connection->IsWriteOpen()))
			++numConnections;
	}
	return numConnections;
}

String NetworkServer::ToString() const
{
	bool isUdp = false;
	bool isTcp = false;
	for(size_t i = 0; i < listenSockets.Size(); ++i)
		if (listenSockets[i]->TransportLayer() == SocketOverUDP)
			isUdp = true;
		else
			isTcp = true;

	String str;
	if (isUdp && isTcp)
		str += "TCP+UDP server";
	else if (isUdp)
		str += "UDP server";
	else if (isTcp)
		str += "TCP server";
	else str += "Server (no listen sockets open)";

	if (listenSockets.Size() == 1)
	{
		int port = (int)listenSockets[0]->LocalPort();
		str += " at local port " + String(port);
	}
	else if (listenSockets.Size() > 1)
	{
		str += " (" + String((int)listenSockets.Size()) + " listen sockets at local ports ";
		for(size_t i = 0; i < listenSockets.Size() && i < 3; ++i)
		{
			if (i > 0)
				str += ", ";
			str += String(listenSockets[i]->LocalPort());
		}
		if (listenSockets.Size() > 3)
			str += ", ...";
		str += ")";
	}
	str += ": ";

	int numConnections = 0;
	{
		Lockable<ConnectionMap>::ConstLockType lock = clients.Acquire();
		numConnections = lock->Size();
	}
	str += String(numConnections) + " connections.";

	if (!acceptNewConnections)
		str += " (not accepting new connections)";

	///\todo Add note about stealth mode.

	return str;
}

} // ~kNet
