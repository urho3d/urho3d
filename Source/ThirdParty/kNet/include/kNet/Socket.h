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

/** @file Socket.h
	@brief The Socket class. */

#ifdef WIN32

#include "kNetBuildConfig.h"
#include "win32/WS2Include.h"
#define KNET_EWOULDBLOCK WSAEWOULDBLOCK
#define KNET_SOCKET_ERROR SOCKET_ERROR
#define KNET_ACCEPT_FAILURE SOCKET_ERROR

namespace kNet
{
typedef int socklen_t;
}

#elif defined(KNET_UNIX) || defined(ANDROID)

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <errno.h>

#define INVALID_SOCKET ((SOCKET)0)
#define KNET_SOCKET_ERROR ((SOCKET)-1)
#define KNET_ACCEPT_FAILURE ((SOCKET)-1)
#define KNET_EWOULDBLOCK EWOULDBLOCK
#define closesocket close
#define TIMEVAL timeval
#define SD_SEND SHUT_WR
#define SD_BOTH SHUT_RDWR
#define _stricmp strcasecmp

namespace kNet
{
typedef int SOCKET;
}
#endif

#include <vector>
#include <list>

#include "SharedPtr.h"
#include "EndPoint.h"
#include "WaitFreeQueue.h"
#include "Event.h"

namespace kNet
{

/// Identifiers for the possible bottom-level tranport layers.
enum SocketTransportLayer
{
	InvalidTransportLayer = 0, ///< A default invalid value for uninitialized sockets.
	SocketOverUDP,
	SocketOverTCP
};

std::string SocketTransportLayerToString(SocketTransportLayer transport);

/// Converts the given string (case-insensitive parsing) to the corresponding SocketTransportLayer enum.
/// "tcp" & "socketovertcp" -> SocketOverTCP.
/// "udp" & "socketoverudp" -> SocketOverUDP.
/// Other strings -> InvalidTransportLayer.
SocketTransportLayer StringToSocketTransportLayer(const char *str);

enum SocketType
{
	InvalidSocketType = 0, ///< A default invalid value for uninitialized sockets.
	ServerListenSocket, ///< For TCP: a listen socket. For UDP: the single master socket handle that is used to send & receive all data.
	ServerClientSocket, ///< For TCP: a client data socket. For UDP: a slave-mode Socket object that shares the underlying socket handle with the UDP master Socket.
	ClientSocket ///< A client-side socket.
};

std::string SocketTypeToString(SocketType type);

typedef int OverlappedTransferTag;

#ifdef WIN32
typedef WSABUF kNetBuffer;
#else
struct kNetBuffer
{
	/// Stores the number of bytes allocated to buf.
	/// When sending out a message, this field specifies the number of bytes the client
	/// can write to buf, at maximum.
	unsigned long len;

	char *buf;
};
#endif

struct OverlappedTransferBuffer
{
	kNetBuffer buffer;
#ifdef WIN32
	WSAOVERLAPPED overlapped;
#endif

	/// Stores the number of bytes actually in use in buffer.buf. When sending out a message,
	/// specify the actual number of bytes filled to buffer.buf here.
	int bytesContains;

    /// Stores the total number of bytes allocated to the buffer in the overlapped structure.
    int bytesAllocated;

	sockaddr_in from;
	socklen_t fromLen;
};

/// Represents a low-level network socket.
class Socket : public RefCountable
{
public:
	Socket();

	Socket(SOCKET connection, const EndPoint &localEndPoint, const char *localHostName,
		const EndPoint &remoteEndPoint, const char *remoteHostName, 
		SocketTransportLayer transport, SocketType type, size_t maxSendSize);

	Socket(const Socket &);
	~Socket();

	Socket &operator=(const Socket &);

	/// Sets the underlying socket send buffer (SO_SNDBUF) size.
	void SetSendBufferSize(int bytes);
	/// Sets the underlying socket receive buffer (SO_RCVBUF) size.
	void SetReceiveBufferSize(int bytes);

	/// Returns the current value for the send buffer of this socket.
	int SendBufferSize() const;
	/// Returns the current value for the receive buffer of this socket.
	int ReceiveBufferSize() const;

	/// Returns true if the connection is both write-open AND read-open.
	bool Connected() const;
	/// Returns true if the connection is open for reading from. This does not mean that there necessarily is new data
	/// to be immediately read - it only means that the socket is open for receiving data.
	bool IsReadOpen() const { return IsOverlappedReceiveReady() || readOpen; }
	/// Returns true if the connection is open for writing to.
	bool IsWriteOpen() const { return writeOpen; }
	/// Forces this socket to be treated as if it has been read-closed.
	void MarkReadClosed() { readOpen = false; }
	/// Forces this socket to be treated as if it has been write-closed.
	void MarkWriteClosed() { writeOpen = false; }

	/// If this function returns true, this socket represents a UDP server socket instance. For a UDP server,
	/// the data for all clients is received through this same socket, and there are no individual sockets created for
	/// each new connection, like is done with TCP.
	bool IsUDPServerSocket() const { return transport == SocketOverUDP && type == ServerListenSocket; }
	/// Returns whether this socket is a UDP slave socket. [worker thread]
	bool IsUDPSlaveSocket() const { return transport == SocketOverUDP && type == ServerClientSocket; }

	/// Performs a write close operation on the socket, signalling the other end that no more data will be sent. Any data
	/// currently left in the send buffers will be sent over to the other side, but no new data can be sent. The connection
	/// will remain half-open for reading, and Receive() calls may still be made to the socket. When a read returns 0, the
	/// connection will be transitioned to bidirectionally closed state (Connected() will return false).
	void Disconnect();
	/// Performs an immediate write and read close on the socket, without waiting for the connection to gracefully shut down.
	void Close();

	/// Sends the given data through the socket. This function may only be called if Socket::IsWriteOpen() returns true. If
	/// the socket is not write-open, calls to this function will fail.
	/// This function is an orthogonal API to the overlapped IO Send routines. Do not mix these API calls when doing
	/// networking, but instead choose one preferred method and consistently use it.
	bool Send(const char *data, size_t numBytes);

	/// Waits until the Socket is ready for sending. Returns true if the socket transitioned to write-ready state in the given
	/// time period, or false if the wait timed out or if some other error occurred.
	/// This function is an orthogonal API to the overlapped IO Send routines. Do not mix these API calls when doing
	/// networking, but instead choose one preferred method and consistently use it.
	bool WaitForSendReady(int msecs);

	/// Starts the sending of new data. After having filled the data to send to the OverlappedTransferBuffer that is
	/// returned here, commit the send by calling EndSend. If you have called BeginSend, but decide not to send any data,
	/// call AbortSend instead (otherwise memory will leak).
    /// @param maxBytesToSend Specifies the size of the buffer that must be returned. Specify the size (or at least an 
    ///         upper limit) of the message you are sending here. Specify the actual number of bytes filled in the resulting
    ///         structure.
	/// @return A transfer buffer where the data to send is to be filled in. If no new data can be sent at this time,
	///         this function returns 0.
	OverlappedTransferBuffer *BeginSend(int maxBytesToSend);
	/// Finishes and queues up the given transfer that was created with a call to BeginSend.
	/// @return True if send succeeded, false otherwise. In either case, the ownership of the passed buffer send
	///         is taken by this Socket and may not be accessed anymore. Discard the pointer after calling this function.
	bool EndSend(OverlappedTransferBuffer *send);
	/// Cancels the sending of data. Call this function if you first call BeginSend, but decide you don't want to send the data.
	/// This frees the given buffer, do not dereference it after calling this function.
	void AbortSend(OverlappedTransferBuffer *send);

#ifdef WIN32
	/// Returns the number of sends in the send queue.
	int NumOverlappedSendsInProgress() const { return queuedSendBuffers.Size(); }
	/// Returns the maximum number of sends that can be queued up simultaneously.
	int MaxOverlappedSendsInProgress() const { return queuedSendBuffers.Capacity(); }
#endif
	/// Returns true if it is possible to send out new data. In this case, a call to BeginSend will succeed.
	bool IsOverlappedSendReady();
	/// Returns the event object that should be waited on to receive a notification when it is possible to send out new data.
	Event GetOverlappedSendEvent();

	/// Waits for the max given amount of time for new data to be received from the socket.
	/// @return True if new data was received, false if the timeout period elapsed.
//	bool WaitForData(int msecs); // this will be removed completely.

	/// Reads in data from the socket. If there is no data available, this function will not block, but will immediately
	/// return 0.
	/// This function issues an immediate recv() call to the socket and is not compatible with the Overlapped Transfer API
	/// above. Do not mix the use of these two APIs, but pick one method to use and stay with it.
	/// @param endPoint [out] If the socket is an UDP socket that is not bound to an address, this will contain the source address.
	/// @return The number of bytes that were successfully read.
	size_t Receive(char *dst, size_t maxBytes, EndPoint *endPoint = 0);

	/// Call to receive new data from the socket.
	/// @return A buffer that contains the data, or 0 if no new data was available. When you are finished reading the buffer, call
	///         EndReceive to free up the buffer, or memory will leak.
	OverlappedTransferBuffer *BeginReceive();
	/// Finishes a read operation on the socket. Frees the given buffer to be re-queued for a future socket read operation.
	void EndReceive(OverlappedTransferBuffer *buffer);
#ifdef WIN32
	/// Returns the number of receive buffers that have been queued for the socket.
	int NumOverlappedReceivesInProgress() const { return queuedReceiveBuffers.Size(); }
	/// Returns the maximum number of receive buffers that can be queued for the socket.
	int MaxOverlappedReceivesInProgress() const { return queuedReceiveBuffers.Capacity(); }
#endif
	/// Returns true if there is new data to be read in. In that case, BeginReceive() will not return 0.
	bool IsOverlappedReceiveReady() const;
	/// Returns the event object that will be notified whenever data is available to be read from the socket.
	Event GetOverlappedReceiveEvent(); // [worker thread]

	/// Returns which transport layer the connection is using. This value is either SocketOverUDP or SocketOverTCP.
	SocketTransportLayer TransportLayer() const { return transport; }

	/// Returns the type of this socket object.
	SocketType Type() const { return type; }

	/// Returns the maximum amount of bytes that can be sent through to the network in one call. If you try sending
	/// more data than specified by this value, the result is undefined.
	size_t MaxSendSize() const { return maxSendSize; }

	/// Returns the local EndPoint this socket is bound to.
	const EndPoint &LocalEndPoint() const { return localEndPoint; }
	/// Returns the local address (local hostname) of the local end point this socket is bound to.
	const char *LocalAddress() const { return localHostName.c_str(); }
	/// Returns the local port that this socket is bound to.
	unsigned short LocalPort() const { return localEndPoint.port; }

	/// Returns the remote EndPoint this socket is connected to.
	/// If SocketType == ServerListenSocket, this socket is not bound
	/// to any remote end point, and so the returned struct is uninitialized (filled with zeroes).
	const EndPoint &RemoteEndPoint() const { return remoteEndPoint; }
	/// Returns the destination address (destination hostname) of the remote end point this socket is connected to.
	/// If SocketType == ServerListenSocket, returns an empty string.
	const char *DestinationAddress() const { return remoteHostName.c_str(); }
	/// Returns the destination port of the remote end point this socket is connected to.
	/// If SocketType == ServerListenSocket, returns 0.
	unsigned short DestinationPort() const { return remoteEndPoint.port; }

	/// Returns a human-readable representation of this socket, specifying the peer address and port this socket is
	/// connected to.
	std::string ToString() const;

	/// Sets the socket to blocking or nonblocking state.
	void SetBlocking(bool isBlocking);

	SOCKET &GetSocketHandle() { return connectSocket; }

	/// Enables or disables the use of Nagle's algorithm (TCP_NODELAY) for this socket.
	/// Nagle's algorithm reduces the bandwidth consumption of the channel, but can increase latency.
	/// Conversely, disabling Nagle's algorithm improves the latency, but increases the number of IP packets sent to the network.
	/// By default, Nagle's algorithm is enabled.
	/// Read more about Nagle's algorithm here: http://msdn.microsoft.com/en-us/library/ms817942.aspx
	void SetNaglesAlgorithmEnabled(bool enabled);

private:
	/// Stores the handle to the underlying BSD socket object. Has the value INVALID_SOCKET if uninitialized.
	SOCKET connectSocket;

	/// Specifies the local system end point (IP and port) this socket is bound to.
	EndPoint localEndPoint;

	/// Specifies the network host name of the local end point (the local system).
	/// If the local end point does not have a hostname, this field is the string representation of the
	/// system IP address (one of them, there may be multiple IPs).
	std::string localHostName;
	
	/// Specifies the remote system end point (IP and port) this socket is bound to (== the "peer" address).
	/// If SocketType == ServerListenSocket or transport == SocketOverUDP, this socket is not bound
	/// to any remote end point, and so this struct is uninitialized (filled with zeroes).
	EndPoint remoteEndPoint;

	/// If this socket is a UDP socket, the remoteEndPoint variable is copied (cached) to the variable
	/// udpPeerAddress to avoid having to reconstruct it at each Socket::Send() call (this is an optimization).
	/// This field is only used if this socket is a UDP socket.
	sockaddr_in udpPeerAddress;

	/// Specifies the network host name of the remote end point (== the remote system == the "peer").
	/// If the remote end point does not have a known hostname, this field is the string representation of the
	/// remote IP address. If SocketType == ServerListenSocket, this field is empty.
	std::string remoteHostName;

	/// Specifies the underlying transport protocol that this Socket is using (TCP or UDP).
	SocketTransportLayer transport;

	/// Specifies the type of this SOCKET object.
	/// UDP server sockets are never bound to a remote, since the same socket is used to send and receive data to and 
	/// from all client addresses. UDP client sockets and TCP sockets on the other hand are always bound to a peer.
	/// UDP client sockets are shared slave copies of the single UDP server socket. In this case, this field is used 
	/// to remember that this Socket object is not authoritative over the OS socket object and should not close it 
	/// when tearing down this socket.
	SocketType type;

	/// Specifies the maximum amount of data that can be sent to the socket at one call to send().
	size_t maxSendSize;

	/// Tracks whether data can be sent through this socket.
	bool writeOpen;

	/// Tracks whether the socket is open for receiving data (doesn't mean that there necessarily exists new data to be read).
	bool readOpen;

#ifdef WIN32
	WaitFreeQueue<OverlappedTransferBuffer*> queuedReceiveBuffers;
	WaitFreeQueue<OverlappedTransferBuffer*> queuedSendBuffers;

	/// Frees all allocated data in the queuedReceiveBuffers and queuedSendBuffers queues.
	void FreeOverlappedTransferBuffers();

	void EnqueueNewReceiveBuffer(OverlappedTransferBuffer *buffer = 0);
#endif
};

} // ~kNet
