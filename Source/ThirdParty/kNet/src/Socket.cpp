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

/** @file Socket.cpp
	@brief */

#include <string>
#include <cassert>
#include <utility>
#include <sstream>

#ifdef KNET_USE_BOOST
#include <boost/thread/thread.hpp>
#endif

#include "kNet/DebugMemoryLeakCheck.h"

#include "kNet/Network.h"

#include "kNet/Socket.h"
#include "kNet/NetworkLogging.h"
#include "kNet/EventArray.h"

using namespace std;

// Urho3D: removed the KNET_UNIX definition
#ifndef _WIN32
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/tcp.h>
#include <unistd.h>
#endif

#ifdef _WIN32
const int numConcurrentReceiveBuffers = 4;
const int numConcurrentSendBuffers = 4;
#endif

namespace kNet
{

std::string SocketTransportLayerToString(SocketTransportLayer transport)
{
	switch(transport)
	{
	case SocketOverUDP: return "UDP";
	case SocketOverTCP: return "TCP";
	default:
		{
			std::stringstream ss;
			ss << "Invalid SocketTransportLayer (" << (int)transport << ")!";
			return ss.str();
		}
	}
}

SocketTransportLayer StringToSocketTransportLayer(const char *str)
{
	if (!str)
		return InvalidTransportLayer;
	if (!_stricmp(str, "tcp") || !_stricmp(str, "SocketOverTCP"))
		return SocketOverTCP;
	if (!_stricmp(str, "udp") || !_stricmp(str, "SocketOverUDP"))
		return SocketOverUDP;
	return InvalidTransportLayer;
}


std::string SocketTypeToString(SocketType type)
{
	switch(type)
	{
	case ServerListenSocket: return "Server listen socket";
	case ServerClientSocket: return "Server client socket";
	case ClientSocket: return "Client socket";
	default:
		{
			std::stringstream ss;
			ss << "Invalid SocketType (" << (int)type << ")!";
			return ss.str();
		}
	}
}

Socket::Socket()
:connectSocket(INVALID_SOCKET),
transport(InvalidTransportLayer),
type(InvalidSocketType),
maxSendSize(0),
writeOpen(false),
readOpen(false)
#ifdef _WIN32
,queuedReceiveBuffers(numConcurrentReceiveBuffers)
,queuedSendBuffers(numConcurrentSendBuffers)
#endif
{
	localEndPoint.Reset();
	remoteEndPoint.Reset();
}

Socket::~Socket()
{
	// We cannot Close() the socket here, since the same underlying BSD SOCKET handle can be shared
	// between multiple Socket objects. We rely instead to non-RAII behavior and manually remembering to 
	// Close().
#ifdef _WIN32
	FreeOverlappedTransferBuffers();
#endif
}

Socket::Socket(SOCKET connection, const EndPoint &localEndPoint_, const char *localHostName_,
	const EndPoint &remoteEndPoint_, const char *remoteHostName_, 
	SocketTransportLayer transport_, SocketType type_, size_t maxSendSize_)
:connectSocket(connection), localEndPoint(localEndPoint_), localHostName(localHostName_),
remoteEndPoint(remoteEndPoint_), remoteHostName(remoteHostName_), 
transport(transport_), type(type_), maxSendSize(maxSendSize_),
writeOpen(true), readOpen(true)
#ifdef _WIN32
,queuedReceiveBuffers(numConcurrentReceiveBuffers)
,queuedSendBuffers(numConcurrentSendBuffers)
#endif
{
	SetSendBufferSize(512 * 1024);
	SetReceiveBufferSize(512 * 1024);
	udpPeerAddress = remoteEndPoint.ToSockAddrIn();
}

Socket::Socket(const Socket &rhs)
#ifdef _WIN32
:queuedReceiveBuffers(numConcurrentReceiveBuffers)
,queuedSendBuffers(numConcurrentSendBuffers)
#endif
{
	*this = rhs;
}

Socket &Socket::operator=(const Socket &rhs)
{
#ifdef _WIN32
	// We would be losing data if Socket is copied from old to new when data is present in the receive buffers,
	// since the receive buffers are not moved or copied to the new Socket.
	assert(queuedReceiveBuffers.Size() == 0);
#endif

	if (this == &rhs)
		return *this;

	connectSocket = rhs.connectSocket;
	localEndPoint = rhs.localEndPoint;
	localHostName = rhs.localHostName;
	remoteEndPoint = rhs.remoteEndPoint;
	remoteHostName = rhs.remoteHostName;
	transport = rhs.transport;
	type = rhs.type;
	maxSendSize = rhs.maxSendSize;
	writeOpen = rhs.writeOpen;
	readOpen = rhs.readOpen;
	udpPeerAddress = rhs.udpPeerAddress;

	return *this;
}

bool Socket::Connected() const
{
	return connectSocket != INVALID_SOCKET;
}

OverlappedTransferBuffer *AllocateOverlappedTransferBuffer(int bytes)
{
	OverlappedTransferBuffer *buffer = new OverlappedTransferBuffer;
	memset(buffer, 0, sizeof(OverlappedTransferBuffer));
	buffer->buffer.buf = new char[bytes];
	buffer->buffer.len = bytes;
	buffer->bytesContains = 0;
    buffer->bytesAllocated = bytes;
#ifdef _WIN32
	buffer->overlapped.hEvent = WSACreateEvent();
	if (buffer->overlapped.hEvent == WSA_INVALID_EVENT)
	{
		KNET_LOG(LogError, "Socket.cpp:AllocateOverlappedTransferBuffer: WSACreateEvent failed!");
		delete[] buffer->buffer.buf;
		delete buffer;
		return 0;
	}
#endif

	return buffer;
}

void DeleteOverlappedTransferBuffer(OverlappedTransferBuffer *buffer)
{
	if (!buffer)
		return;
	delete[] buffer->buffer.buf;
#ifdef _WIN32
	BOOL success = WSACloseEvent(buffer->overlapped.hEvent);
	if (success == FALSE)
		KNET_LOG(LogError, "Socket.cpp:DeleteOverlappedTransferBuffer: WSACloseEvent failed!");
	buffer->overlapped.hEvent = WSA_INVALID_EVENT;
#endif
	delete buffer;
}

void Socket::SetSendBufferSize(int bytes)
{
	socklen_t len = sizeof(bytes);
	if (setsockopt(connectSocket, SOL_SOCKET, SO_SNDBUF, (char*)&bytes, len))
		KNET_LOG(LogError, "Socket::SetSendBufferSize: setsockopt failed with error %s!", Network::GetLastErrorString().c_str());
}

void Socket::SetReceiveBufferSize(int bytes)
{
	socklen_t len = sizeof(bytes);
	if (setsockopt(connectSocket, SOL_SOCKET, SO_RCVBUF, (char*)&bytes, len))
		KNET_LOG(LogError, "Socket::SetReceiveBufferSize: setsockopt failed with error %s!", Network::GetLastErrorString().c_str());
}

int Socket::SendBufferSize() const
{
	int bytes = 0;
	socklen_t len = sizeof(bytes);
	if (getsockopt(connectSocket, SOL_SOCKET, SO_SNDBUF, (char*)&bytes, &len))
	{
		KNET_LOG(LogError, "Socket::SendBufferSize: getsockopt failed with error %s!", Network::GetLastErrorString().c_str());
		return 0;
	}
	return bytes;
}

int Socket::ReceiveBufferSize() const
{
	int bytes = 0;
	socklen_t len = sizeof(bytes);
	if (getsockopt(connectSocket, SOL_SOCKET, SO_RCVBUF, (char*)&bytes, &len))
	{
		KNET_LOG(LogError, "Socket::ReceiveBufferSize: getsockopt failed with error %s!", Network::GetLastErrorString().c_str());
		return 0;
	}

	return bytes;
}

#ifdef _WIN32
void Socket::EnqueueNewReceiveBuffer(OverlappedTransferBuffer *buffer)
{
	if (!readOpen || queuedReceiveBuffers.CapacityLeft() == 0 || IsUDPSlaveSocket())
	{
		DeleteOverlappedTransferBuffer(buffer); // buffer may be a zero pointer, but that is alright.
		return;
	}

	if (!buffer)
	{
		const int receiveBufferSize = 16384; // This is best to be at least 9K (the largest size of jumbo datagrams commonly supported)
		buffer = AllocateOverlappedTransferBuffer(receiveBufferSize);
		if (!buffer)
		{
			KNET_LOG(LogError, "Socket::EnqueueNewReceiveBuffer: Call to AllocateOverlappedTransferBuffer failed!");
			return;
		}
	}

	if (WSAResetEvent(buffer->overlapped.hEvent) != TRUE)
		KNET_LOG(LogError, "Socket::EnqueueNewReceiveBuffer: WSAResetEvent failed!");

	unsigned long flags = 0;
	int ret;

	if (IsUDPServerSocket())
	{
		buffer->fromLen = sizeof(buffer->from);
		ret = WSARecvFrom(connectSocket, &buffer->buffer, 1, (LPDWORD)&buffer->bytesContains, &flags, (sockaddr*)&buffer->from, &buffer->fromLen, &buffer->overlapped, 0);
	}
	else
	{
		ret = WSARecv(connectSocket, &buffer->buffer, 1, (LPDWORD)&buffer->bytesContains, &flags, &buffer->overlapped, 0);
	}

	int error = (ret == 0) ? 0 : Network::GetLastError();
	if (ret == 0 || (ret == SOCKET_ERROR && error == WSA_IO_PENDING)) // If ret is not 0, ret == SOCKET_ERROR according to MSDN. http://msdn.microsoft.com/en-us/library/ms741688(VS.85).aspx
	{
		if (ret == 0 && buffer->bytesContains == 0)
		{
			if (IsUDPServerSocket())
				KNET_LOG(LogError, "Unexpected: Received a message of 0 bytes on a UDP server socket!");

			KNET_LOG(LogInfo, "Socket::EnqueueNewReceiveBuffer: Received 0 bytes from the network. Read connection closed in socket %s.", ToString().c_str());
			readOpen = false;
			DeleteOverlappedTransferBuffer(buffer);
			return;
		}
		// Return value 0: The operation completed and we have received new data. Push it to a queue for the user to receive.
		// WSA_IO_PENDING: The operation was successfully enqueued.
		bool success = queuedReceiveBuffers.Insert(buffer);
		if (!success)
		{
			KNET_LOG(LogError, "Socket::EnqueueNewReceiveBuffer: queuedReceiveBuffers.Insert(buffer); failed!");
			DeleteOverlappedTransferBuffer(buffer);
		}
	}
	else if (error == WSAEDISCON)
	{
		if (IsUDPServerSocket())
			KNET_LOG(LogError, "Unexpected: Received WSAEDISCON on a UDP server socket!");

		KNET_LOG(LogError, "Socket::EnqueueNewReceivebuffer: WSAEDISCON. Connection closed in socket %s.", ToString().c_str());
		readOpen = false;
		///\todo Should do writeOpen = false; here as well?
		DeleteOverlappedTransferBuffer(buffer);
		return;
	}
	else
	{
		if (error != WSAEWOULDBLOCK && error != 0)
		{
			KNET_LOG(LogError, "Socket::EnqueueNewReceiveBuffer: %s for overlapped socket %s failed! Error: %s.", IsUDPServerSocket() ? "WSARecvFrom" : "WSARecv", ToString().c_str(), Network::GetErrorString(error).c_str());

			// We never close the server socket as a reaction on any error, since an error on one client could shut down
			// the whole server for all clients. This check is mainly here to ignore the 10054 error (WSAECONNRESET) which
			// is returned when UDP clients give back a ICMP Host Unreachable message, but since there may be other
			// client-specific errors, we don't explicitly check for the 10054 case only.
			if (!IsUDPServerSocket())
			{
				KNET_LOG(LogError, "Socket::EnqueueNewReceiveBuffer: Closing down socket.",  Network::GetErrorString(error).c_str());
				readOpen = false;
				writeOpen = false;
				Close();
			}
		}

		DeleteOverlappedTransferBuffer(buffer); // We failed to queue the buffer, free it up immediately to avoid leaking memory.
		return;
	}
}
#endif

void DumpBuffer(const char *description, const char *data, int size)
{
	printf("%s (%d bytes): ", description, size);
	for(int i = 0; i < min(size, 50); ++i)
		printf("%02X ", (unsigned int)(unsigned char)data[i]);
	printf("\n");
}

size_t Socket::Receive(char *dst, size_t maxBytes, EndPoint *endPoint)
{
	assert(dst);
	assert(maxBytes > 0);
	if (maxBytes == 0)
		return 0;

	if (connectSocket == INVALID_SOCKET)
		return 0;

	if (!readOpen)
		return 0;

	if (IsUDPSlaveSocket()) // UDP slave sockets are never read directly. Instead the UDP server socket reads all client data.
		return 0; // So, if we accidentally come here to read a UDP slave socket, act as if it never received any data.

	if (IsUDPServerSocket())
	{
		sockaddr_in from;
		socklen_t fromLen = sizeof(from);
		int numBytesRead = recvfrom(connectSocket, dst, maxBytes, 0, (sockaddr*)&from, &fromLen);
		if (numBytesRead == KNET_SOCKET_ERROR)
		{
			int error = Network::GetLastError();
			if (error != KNET_EWOULDBLOCK && error != 0)
				KNET_LOG(LogError, "Socket::Receive: recvfrom failed: %s in socket %s", Network::GetErrorString(error).c_str(), ToString().c_str());

			return 0;
		}
		if (numBytesRead > 0)
			KNET_LOG(LogData, "recvfrom (%d) in socket %s", numBytesRead, ToString().c_str());

		if (endPoint)
			*endPoint = EndPoint::FromSockAddrIn(from);

		return numBytesRead;
	}

	// If we reach here, this socket is a tcp connection socket (server->client or client->server), or a udp client->server socket.

	int ret = recv(connectSocket, dst, maxBytes, 0);

	if (ret > 0)
	{
		KNET_LOG(LogData, "Received %d bytes of data from socket 0x%X.", ret, (unsigned int)connectSocket);
		return (size_t)ret;
	}
	else if (ret == 0)
	{
		KNET_LOG(LogInfo, "Socket::Receive: Received 0 bytes from network. Read-connection closed to socket %s.", ToString().c_str());
		readOpen = false;
		return 0;
	}
	else
	{
		int error = Network::GetLastError();
		if (error != KNET_EWOULDBLOCK && error != 0)
		{
			KNET_LOG(LogError, "Socket::Receive: recv failed in socket %s. Error %s", ToString().c_str(), Network::GetErrorString(error).c_str());

			// We never close the server socket as a reaction on any error, since an error on one client could shut down
			// the whole server for all clients. This check is mainly here to ignore the 10054 error (WSAECONNRESET) which
			// is returned when UDP clients give back a ICMP Host Unreachable message, but since there may be other
			// client-specific errors, we don't explicitly check for the 10054 case only.
			if (!IsUDPServerSocket())
			{
				readOpen = false;
				writeOpen = false;
				Close();
			}
		}
		return 0;
	}
}

bool Socket::IsOverlappedReceiveReady() const
{
	if (IsUDPSlaveSocket()) // UDP slave sockets are never read directly. For these sockets, act as if they're never ready for reads.
		return false;

#ifdef _WIN32
	if (queuedReceiveBuffers.Size() == 0)
		return false;
	return Event((*queuedReceiveBuffers.Front())->overlapped.hEvent, EventWaitRead).Test();
#else
	if (!readOpen)
		return false;

	EventArray ea;
	ea.AddEvent(Event(connectSocket, EventWaitRead));
	return ea.Wait(0) == 0;
#endif
}

Event Socket::GetOverlappedReceiveEvent()
{
	if (IsUDPSlaveSocket()) // UDP slave sockets are never read directly. For these sockets, return a null event that never fires.
		return Event();

#ifdef _WIN32
	if (readOpen)
	{
		/// Prime the receive buffers to the full capacity if they weren't so yet.
		const int capacityLeft = queuedReceiveBuffers.CapacityLeft();
		for(int i = 0; i < capacityLeft; ++i)
			EnqueueNewReceiveBuffer();
	}

	if (queuedReceiveBuffers.Size() == 0)
		return Event();

	OverlappedTransferBuffer *receivedData = *queuedReceiveBuffers.Front();
	assert(receivedData);

	return Event(receivedData->overlapped.hEvent, EventWaitRead);
#else
	return Event(connectSocket, EventWaitRead);
#endif
}

Event Socket::GetOverlappedSendEvent()
{
	if (!writeOpen)
		return Event();

#ifdef _WIN32
	if (queuedSendBuffers.Size() == 0)
		return Event();

	OverlappedTransferBuffer *sentData = *queuedSendBuffers.Front();
	assert(sentData);

	return Event(sentData->overlapped.hEvent, EventWaitWrite);
#else
	return Event(connectSocket, EventWaitWrite);
#endif
}

OverlappedTransferBuffer *Socket::BeginReceive()
{
	// UDP 'slave socket' is a socket descriptor on the server side that is a copy of the single UDP server listen socket.
	// The slave sockets don't receive data directly, but the server socket is used instead to receive data for them.
	if (IsUDPSlaveSocket())
	{
#ifdef _WIN32
		assert(queuedReceiveBuffers.Size() == 0); // We shouldn't ever have queued a single receive buffer for this Socket.
#endif
		return 0; // If we happen to come here, act as if the socket never received any data.
	}

#ifdef _WIN32
	if (readOpen)
	{
		// Insert new empty receive buffers to the Overlapped Transfer receive queue until we have a full capacity queue primed.
		const int capacityLeft = queuedReceiveBuffers.CapacityLeft();
		for(int i = 0; i < capacityLeft; ++i)
			EnqueueNewReceiveBuffer();
	}

	if (queuedReceiveBuffers.Size() == 0)
		return 0;

	OverlappedTransferBuffer *receivedData = *queuedReceiveBuffers.Front();
	DWORD flags = 0;
	BOOL ret = WSAGetOverlappedResult(connectSocket, &receivedData->overlapped, (LPDWORD)&receivedData->bytesContains, FALSE, &flags);
	int error = (ret == TRUE) ? 0 : Network::GetLastError();
	if (ret == TRUE)
	{
		queuedReceiveBuffers.PopFront();

		// Successfully receiving zero bytes with overlapped sockets means the same as recv() of 0 bytes,
		// peer has closed the write connection (but can still recv() until we also close the write connection).
		if (receivedData->bytesContains == 0)
		{
			DeleteOverlappedTransferBuffer(receivedData);
			if (!IsUDPServerSocket())
			{
				if (readOpen)
				{
					KNET_LOG(LogInfo, "Socket::BeginReceive: Received 0 bytes from the network. Read connection closed in socket %s.", ToString().c_str());
					readOpen = false;
				}
			}
			else
				KNET_LOG(LogVerbose, "Socket::BeginReceive: Server received a UDP datagram of 0 bytes from a client! This is a malformed kNet UDP datagram!");
			return 0;
		}

		return receivedData;
	}
	else if (error == WSAEDISCON)
	{
		queuedReceiveBuffers.PopFront();
		DeleteOverlappedTransferBuffer(receivedData);
		if (readOpen || writeOpen)
			KNET_LOG(LogError, "Socket::BeginReceive: WSAEDISCON. Bidirectionally closing connection in socket %s.", ToString().c_str());
		if (IsUDPServerSocket())
			KNET_LOG(LogError, "Socket::BeginReceive: Unexpected: Received WSAEDISCON on UDP server socket!");
		Close();
		return 0;
	}
	else if (error != WSA_IO_INCOMPLETE)
	{
		queuedReceiveBuffers.PopFront();
		if (readOpen || writeOpen)
			if (!(IsUDPServerSocket() && error == 10054)) // If we are running both UDP server and client on localhost, we can receive 10054 (Peer closed connection) on the server side, in which case, we ignore this error print.
				KNET_LOG(LogError, "Socket::BeginReceive: WSAGetOverlappedResult failed with code %d when reading from an overlapped socket! Reason: %s.", error, Network::GetErrorString(error).c_str());
		DeleteOverlappedTransferBuffer(receivedData);
		// Mark this socket closed, unless the read error was on a UDP server socket, in which case we must ignore
		// the read error on this buffer (an error on a single client connection cannot shut down the whole server!)
		if (!IsUDPServerSocket() && (readOpen || writeOpen))
		{
			KNET_LOG(LogError, "Socket::BeginReceive: Closing socket due to read error!");
			Close();
		}
	}
	return 0;
#else
	if (!readOpen)
		return 0;

	const int receiveBufferSize = 4096;
	OverlappedTransferBuffer *buffer = AllocateOverlappedTransferBuffer(receiveBufferSize);
	EndPoint source;
	buffer->bytesContains = Receive(buffer->buffer.buf, buffer->buffer.len, &source);
	if (buffer->bytesContains > 0)
	{
		buffer->fromLen = sizeof(buffer->from);
		buffer->from = source.ToSockAddrIn();
		return buffer;
	}
	else
	{
		// Did not get any data. Delete the buffer immediately.
		DeleteOverlappedTransferBuffer(buffer);
		return 0;
	}
#endif
}

void Socket::EndReceive(OverlappedTransferBuffer *buffer)
{
#ifdef _WIN32
	if (readOpen)
	{
		EnqueueNewReceiveBuffer(buffer);
		return;
	}
#endif

	DeleteOverlappedTransferBuffer(buffer);
}

void Socket::Disconnect()
{
	if (connectSocket == INVALID_SOCKET)
		return;

	KNET_LOG(LogVerbose, "Socket::Disconnect(), this: %p.", this);

	if (transport == SocketOverTCP)
	{
		int result = shutdown(connectSocket, SD_SEND);
		if (result == KNET_SOCKET_ERROR)
			KNET_LOG(LogError, "Socket::Disconnect(): TCP socket shutdown(SD_SEND) failed: %s in socket %s.", Network::GetLastErrorString().c_str(), ToString().c_str());
		else
			KNET_LOG(LogInfo, "Socket::Disconnect(): TCP socket shutdown(SD_SEND) succeeded on socket %s.", ToString().c_str());
	}

	writeOpen = false;
}

void Socket::Close()
{
	if (connectSocket == INVALID_SOCKET)
	{
		assert(!readOpen && !writeOpen);
		return;
	}

	KNET_LOG(LogInfo, "Socket::Close(): Closing socket %s.", ToString().c_str());

	if (!IsUDPSlaveSocket())
	{
		// For UDP client sockets on the server side, the same SOCKET object is shared by 
		// all other client sockets and the UDP server socket. For those sockets, the UDP server socket is the owner
		// of the socket object, so the clients cannot close their sockets, as closing one would close them all.

		int result = shutdown(connectSocket, SD_BOTH);
		if (result == KNET_SOCKET_ERROR)
			KNET_LOG(LogError, "Socket::Close(): Socket shutdown(SD_BOTH) failed: %s in socket %s.", Network::GetLastErrorString().c_str(), ToString().c_str());
		else
			KNET_LOG(LogInfo, "Socket::Close(): Socket shutdown(SD_BOTH) succeeded on socket %s.", ToString().c_str());

		result = closesocket(connectSocket);
		if (result == KNET_SOCKET_ERROR)
			KNET_LOG(LogError, "Socket::Close(): closesocket() failed: %s in socket %s.", Network::GetLastErrorString().c_str(), ToString().c_str());
	}

	connectSocket = INVALID_SOCKET;
	localEndPoint.Reset();
	localHostName = "";
	remoteEndPoint.Reset();
	remoteHostName = "";
	transport = InvalidTransportLayer;
	type = InvalidSocketType;
	readOpen = false;
	writeOpen = false;

#ifdef _WIN32
	FreeOverlappedTransferBuffers();
#endif
}

#ifdef _WIN32
void Socket::FreeOverlappedTransferBuffers()
{
	KNET_LOG(LogVerbose, "Socket::FreeOverlappedTransferBuffers(), this: %p.", this);
/// \todo Use CancelIo to tear-down commited OverlappedTransferBuffers before freeing data. http://msdn.microsoft.com/en-us/library/aa363792(VS.85).aspx
	while(queuedReceiveBuffers.Size() > 0)
		DeleteOverlappedTransferBuffer(queuedReceiveBuffers.TakeFront());

	while(queuedSendBuffers.Size() > 0)
		DeleteOverlappedTransferBuffer(queuedSendBuffers.TakeFront());
}
#endif

void Socket::SetBlocking(bool isBlocking)
{
	if (connectSocket == INVALID_SOCKET)
		return;

#ifdef _WIN32
	u_long nonBlocking = (isBlocking == false) ? 1 : 0;
	if (ioctlsocket(connectSocket, FIONBIO, &nonBlocking))
		KNET_LOG(LogError, "Socket::SetBlocking: ioctlsocket failed with error %s!", Network::GetLastErrorString().c_str());
#else
	int flags = fcntl(connectSocket, F_GETFL, 0);
	if (!isBlocking)
		fcntl(connectSocket, F_SETFL, flags | O_NONBLOCK);
	else
		fcntl(connectSocket, F_SETFL, flags & ~O_NONBLOCK);
#endif
}

/// @return True on success, false otherwise.
bool Socket::Send(const char *data, size_t numBytes)
{
	if (connectSocket == INVALID_SOCKET)
	{
		KNET_LOG(LogError, "Trying to send a datagram to INVALID_SOCKET!");
		return false;
	}

	// Server listen sockets are *not* for sending data. They only accept incoming connections.
	if (type == ServerListenSocket)
	{
		KNET_LOG(LogError, "Trying to send data through a server listen socket!");
		return false;
	}

	if (!writeOpen)
	{
		KNET_LOG(LogError, "Trying to send data to a socket that is not open for writing!");
		return false;
	}

	int bytesSent = 0;
	// sendto() to a connected socket causes EISCONN on OSX, so avoid it for client UDP sockets
	if (transport == SocketOverUDP && type != ClientSocket)
		bytesSent = sendto(connectSocket, data, numBytes, 0, (sockaddr*)&udpPeerAddress, sizeof(udpPeerAddress));
	else
		bytesSent = send(connectSocket, data, numBytes, 0);

	if (bytesSent == (int)numBytes)
	{
		KNET_LOG(LogData, "Socket::EndSend: Sent out %d bytes to socket %s.", bytesSent, ToString().c_str());
		return true;
	}
	else if (bytesSent > 0) // Managed to send some data, but not all bytes.
	{
		assert(transport == SocketOverTCP); // Only TCP sockets should ever succeed 'partially'.
		// Our Socket::Send tries to guarantee that either all or nothing of the data is sent. We don't want
		// to report back to the upper layer that only part of the data was successfully sent. So, try to
		// re-issue the remainining bytes, but now in blocking mode, so we can wait for the rest of the data to
		// be sent.
		const int socketWriteTimeout = 5000; // msecs.
		bool waitSuccess = WaitForSendReady(socketWriteTimeout);
		if (!waitSuccess)
		{
			KNET_LOG(LogError, "Socket::Send: Warning! Managed to only partially send out %d bytes out of %d bytes in the buffer, and socket did not transition to write-ready in the timeout period. Closing connection.", 
				bytesSent, (int)numBytes);
			Close();
			return false;
		}
		// Recursively call back to this function to process the remainder of the data.
		// Since bytesSent > 0, we should be making progress at each step of recursion, so there is no
		// danger of crashing the stack.
		return Send(data+bytesSent, numBytes-bytesSent);
	}
	else // Some kind of error occurred.
	{
		int error = Network::GetLastError();

		if (error != KNET_EWOULDBLOCK)
		{
			KNET_LOG(LogError, "Socket::Send() failed! Error: %s.", Network::GetErrorString(error).c_str());
			if (type == ServerClientSocket && transport == SocketOverUDP)
			{
				// UDP client sockets are shared between each client (and by the server socket),
				// so we can't actually call close() on the socket handle. Instead, resort
				// to a soft close as follows.
				readOpen = false;
				writeOpen = false;
			}
			else // For all other sockets, it's ok to close (socket is not shared).
				Close();
		}

		return false;
	}
}

bool Socket::WaitForSendReady(int msecs)
{
#ifdef _WIN32
	fd_set writeSet;
	FD_ZERO(&writeSet);
	FD_SET(connectSocket, &writeSet);
	TIMEVAL tv = { msecs / 1000, (msecs % 1000) * 1000 };
	int ret = select(0, NULL, &writeSet, NULL, &tv);
	return ret != KNET_SOCKET_ERROR && ret != 0;
#else
	Event waitEvent(connectSocket, EventWaitWrite);
	return waitEvent.Wait(msecs);
#endif
}

bool Socket::IsOverlappedSendReady()
{
	if (!writeOpen)
		return false;

#ifdef _WIN32
	if (queuedSendBuffers.CapacityLeft() > 0)
		return true;

	OverlappedTransferBuffer *sentData = *queuedSendBuffers.Front();
	DWORD flags = 0;
	BOOL ret = WSAGetOverlappedResult(connectSocket, &sentData->overlapped, (LPDWORD)&sentData->bytesContains, 
		FALSE, &flags);
	return ret == TRUE;
#else
	EventArray ea;
	ea.AddEvent(Event(connectSocket, EventWaitWrite));
	return ea.Wait(0) == 0;
#endif
}

OverlappedTransferBuffer *Socket::BeginSend(int maxBytesToSend)
{
	if (!writeOpen)
		return 0;

	// See if the oldest one of the previously submitted transfers has now finished,
	// and reuse that buffer without allocating a new one, if so.
#ifdef _WIN32
	if (queuedSendBuffers.Size() > 0)
	{
		OverlappedTransferBuffer *sentData = *queuedSendBuffers.Front();
		DWORD flags = 0;
		BOOL ret = WSAGetOverlappedResult(connectSocket, &sentData->overlapped, (LPDWORD)&sentData->bytesContains, 
			(queuedSendBuffers.CapacityLeft() == 0) ? TRUE : FALSE, &flags);
		int error = (ret == TRUE) ? 0 : Network::GetLastError();
		if (ret == TRUE)
		{
			queuedSendBuffers.PopFront();

            // If the buffer we pulled off was too small, free it and allocate a new one which is of the desired size.
            if (sentData->bytesAllocated < maxBytesToSend)
            {
                DeleteOverlappedTransferBuffer(sentData);
	            return AllocateOverlappedTransferBuffer(maxBytesToSend); ///\todo In debug mode - track this pointer.
            }
            else
            {
                // The existing transfer buffer is large enough. Prepare it for reuse and pass back to caller.
			    sentData->buffer.len = sentData->bytesAllocated; // This is the number of bytes that the client is allowed to fill.
			    sentData->bytesContains = 0; // No bytes currently in use.

			    return sentData;
            }
		}
		if (ret == FALSE && error != WSA_IO_INCOMPLETE)
		{
			KNET_LOG(LogError, "Socket::BeginSend: WSAGetOverlappedResult failed with an error %s, code %d != WSA_IO_INCOMPLETE!", 
				Network::GetErrorString(error).c_str(), error);
			writeOpen = false;
			return 0;
		}
	}

	if (queuedSendBuffers.CapacityLeft() == 0)
		return 0;
#endif

	// No previous send buffer has finished from use (or not using overlapped transfers) - allocate a new buffer.
	return AllocateOverlappedTransferBuffer(maxBytesToSend);
}

bool Socket::EndSend(OverlappedTransferBuffer *sendBuffer)
{
	assert(sendBuffer);
	if (!sendBuffer)
		return false;

	// For the purposes of this send, mark the allocated length of the send buffer equal to the 
	// number of bytes the user had filled into the buffer.
	sendBuffer->buffer.len = sendBuffer->bytesContains;

#ifdef _WIN32
	// Clear the event flag so that the completion of WSASend can trigger this and signal us.
	WSAResetEvent(sendBuffer->overlapped.hEvent);

	unsigned long bytesSent = 0;

	int ret;

	if (transport == SocketOverUDP)
		ret = WSASendTo(connectSocket, &sendBuffer->buffer, 1, (LPDWORD)&bytesSent, 0, (sockaddr*)&udpPeerAddress, sizeof(udpPeerAddress), &sendBuffer->overlapped, 0);
	else
		ret = WSASend(connectSocket, &sendBuffer->buffer, 1, (LPDWORD)&bytesSent, 0, &sendBuffer->overlapped, 0);

	int error = (ret == 0) ? 0 : Network::GetLastError();
	if (ret != 0 && error != WSA_IO_PENDING)
	{
		if (error != KNET_EWOULDBLOCK)
		{
			KNET_LOG(LogError, "Socket::EndSend() failed! Error: %s.", Network::GetErrorString(error).c_str());
			if (!IsUDPServerSocket())
				writeOpen = false;
		}
		DeleteOverlappedTransferBuffer(sendBuffer);
		return false;
	}

	bool success = queuedSendBuffers.Insert(sendBuffer);
	if (!success)
	{
		KNET_LOG(LogError, "queuedSendBuffers.Insert(send); failed!");
		///\todo WARNING: Deleting a buffer that is submitted to WSASend. This crashes. The alternative
		/// is to leak. Refactor so that the above queuedSendBuffers.Insert is tried for success before calling WSASend.
		DeleteOverlappedTransferBuffer(sendBuffer);
		return false;
	}
	return true;

// Urho3D: removed the KNET_UNIX definition
#else
	bool success = Send(sendBuffer->buffer.buf, sendBuffer->buffer.len);
	DeleteOverlappedTransferBuffer(sendBuffer);
	return success;
#endif
}

void Socket::AbortSend(OverlappedTransferBuffer *send)
{
	if (!writeOpen)
	{
		DeleteOverlappedTransferBuffer(send);
		return;
	}

#ifdef _WIN32
	// Set the event flag so as to signal that this buffer is completed immediately.
	if (WSASetEvent(send->overlapped.hEvent) != TRUE)
	{
		KNET_LOG(LogError, "Socket::AbortSend: WSASetEvent failed!");
		DeleteOverlappedTransferBuffer(send);
		return;
	}
	bool success = queuedSendBuffers.Insert(send);
	if (!success)
	{
		KNET_LOG(LogError, "queuedSendBuffers.Insert(send); failed! AbortOverlappedSend");
		DeleteOverlappedTransferBuffer(send);
	}
#else
	DeleteOverlappedTransferBuffer(send);
#endif
}

std::string Socket::ToString() const
{
	sockaddr_in addr;
	socklen_t namelen = sizeof(addr);
	int peerRet = getpeername(connectSocket, (sockaddr*)&addr, &namelen); // Note: This works only if family==INETv4
	EndPoint peerName = EndPoint::FromSockAddrIn(addr);

	int sockRet = getsockname(connectSocket, (sockaddr*)&addr, &namelen); // Note: This works only if family==INETv4
	EndPoint sockName = EndPoint::FromSockAddrIn(addr);

	char str[256];
	sprintf(str, "%s:%d (%s, connected=%s, readOpen: %s, writeOpen: %s, maxSendSize=%d, sock: %s, peer: %s, socket: %d, this: %p)", 
		DestinationAddress(), (int)DestinationPort(), 
		(transport == SocketOverTCP) ? "TCP" : (IsUDPServerSocket() ? "UDP server" : (IsUDPSlaveSocket() ? "UDP Slave" : "UDP")), 
		Connected() ? "true" : "false", readOpen ? "true" : "false", writeOpen ? "true" : "false",
		(int)maxSendSize, sockRet == 0 ? sockName.ToString().c_str() : "(-)", 
		peerRet == 0 ? peerName.ToString().c_str() : "(-)", (int)connectSocket,
		this);

	return std::string(str);
}

void Socket::SetNaglesAlgorithmEnabled(bool enabled)
{
	if (connectSocket == INVALID_SOCKET)
	{
		KNET_LOG(LogError, "Socket::SetNaglesAlgorithmEnabled called for invalid socket object!");
		return;
	}
	if (transport != SocketOverTCP)
	{
		KNET_LOG(LogError, "Calling Socket::SetNaglesAlgorithmEnabled is only valid for TCP sockets!");
		return;
	}

#ifdef _WIN32
	BOOL nagleEnabled = enabled ? TRUE : FALSE;
	int ret = setsockopt(connectSocket, IPPROTO_TCP, TCP_NODELAY, (const char *)&nagleEnabled, sizeof(nagleEnabled));
#else
	int nagleEnabled = enabled ? 1 : 0;
	int ret = setsockopt(connectSocket, IPPROTO_TCP, TCP_NODELAY, &nagleEnabled, sizeof(nagleEnabled));
#endif
	if (ret != 0)
		KNET_LOG(LogError, "Setting TCP_NODELAY=%s for socket %d failed. Reason: %s.",
			enabled ? "true" : "false", (int)connectSocket, Network::GetLastErrorString().c_str());
}

} // ~kNet
