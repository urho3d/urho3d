/*
	Copyright (c) 2009 Christopher A. Taylor.  All rights reserved.

	Redistribution and use in source and binary forms, with or without
	modification, are permitted provided that the following conditions are met:

	* Redistributions of source code must retain the above copyright notice,
	  this list of conditions and the following disclaimer.
	* Redistributions in binary form must reproduce the above copyright notice,
	  this list of conditions and the following disclaimer in the documentation
	  and/or other materials provided with the distribution.
	* Neither the name of LibCat nor the names of its contributors may be used
	  to endorse or promote products derived from this software without
	  specific prior written permission.

	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
	AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
	IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
	ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
	LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
	CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
	SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
	INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
	CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
	ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
	POSSIBILITY OF SUCH DAMAGE.
*/

#include <cat/net/ThreadPoolSockets.hpp>
#include <cat/io/Logging.hpp>
#include <cat/io/Settings.hpp>
#include <cat/threads/RegionAllocator.hpp>
#include <cat/threads/Atomic.hpp>
#include <process.h>
#include <algorithm>
using namespace std;
using namespace cat;


//// Overlapped types

void AcceptExOverlapped::Set(Socket s)
{
    tov.Set(OVOP_ACCEPT_EX);
    acceptSocket = s;
}


//// TCPServer

TCPServer::TCPServer()
{
    _socket = CAT_SOCKET_ERROR;
}

TCPServer::~TCPServer()
{
    Close();
}

bool TCPServer::Bind(Port port)
{
    // Create an unbound, overlapped TCP socket for the listen port
	bool ipv4;
	Socket s;
	if (!CreateSocket(SOCK_STREAM, IPPROTO_TCP, true, s, ipv4))
	{
		FATAL("TCPServer") << "Unable to create a TCP socket: " << SocketGetLastErrorString();
		return false;
	}

    // Set SO_SNDBUF to zero for a zero-copy network stack (we maintain the buffers)
    int buffsize = 0;
    if (setsockopt(s, SOL_SOCKET, SO_SNDBUF, (char*)&buffsize, sizeof(buffsize)))
    {
        FATAL("TCPServer") << "Unable to zero the send buffer: " << SocketGetLastErrorString();
        CloseSocket(s);
        return false;
    }

    // Do not allow other applications to bind over us with SO_REUSEADDR
    int exclusive = TRUE;
    if (setsockopt(s, SOL_SOCKET, SO_EXCLUSIVEADDRUSE, (char*)&exclusive, sizeof(exclusive)))
    {
        FATAL("TCPServer") << "Unable to get exclusive port: " << SocketGetLastErrorString();
        CloseSocket(s);
        return false;
    }

    // Get AcceptEx() interface
    GUID GuidAcceptEx = WSAID_ACCEPTEX;
    DWORD copied;

    if (WSAIoctl(s, SIO_GET_EXTENSION_FUNCTION_POINTER, &GuidAcceptEx, sizeof(GuidAcceptEx),
                 &_lpfnAcceptEx, sizeof(_lpfnAcceptEx), &copied, 0, 0))
    {
        FATAL("TCPServer") << "Unable to get AcceptEx interface: " << SocketGetLastErrorString();
        CloseSocket(s);
        return false;
    }

    // Get GetAcceptExSockaddrs() interface
    GUID GuidGetAcceptExSockAddrs = WSAID_GETACCEPTEXSOCKADDRS;

    if (WSAIoctl(s, SIO_GET_EXTENSION_FUNCTION_POINTER, &GuidGetAcceptExSockAddrs,
				 sizeof(GuidGetAcceptExSockAddrs), &_lpfnGetAcceptExSockAddrs,
				 sizeof(_lpfnGetAcceptExSockAddrs), &copied, 0, 0))
    {
        FATAL("TCPServer") << "Unable to get GetAcceptExSockAddrs interface: " << SocketGetLastErrorString();
        CloseSocket(s);
        return false;
    }

    // Get DisconnectEx() interface
    GUID GuidDisconnectEx = WSAID_DISCONNECTEX;

    if (WSAIoctl(s, SIO_GET_EXTENSION_FUNCTION_POINTER, &GuidDisconnectEx,
				 sizeof(GuidDisconnectEx), &_lpfnDisconnectEx, sizeof(_lpfnDisconnectEx),
				 &copied, 0, 0))
    {
        FATAL("TCPServer") << "Unable to get DisconnectEx interface: " << SocketGetLastErrorString();
        CloseSocket(s);
        return false;
    }

    // Bind socket to port
    if (!NetBind(s, port, ipv4))
    {
        FATAL("TCPServer") << "Unable to bind to port " << port << ": " << SocketGetLastErrorString();
        CloseSocket(s);
        return false;
    }

    // Listen on this socket
    if (listen(s, SOMAXCONN))
    {
        FATAL("TCPServer") << "Unable to listen on socket: " << SocketGetLastErrorString();
        CloseSocket(s);
        return false;
    }

    _socket = s;

    // Prepare to receive completions in the worker threads
    // Queue a bunch of AcceptEx() calls
    if (!ThreadPool::ref()->Associate((HANDLE)s, this) ||
        !QueueAccepts())
    {
        Close();
        return false;
    }

    _port = port;

    INFO("TCPServer") << "Listening on port " << GetPort();

    return true;
}

bool TCPServer::ValidServer()
{
    return _socket != CAT_SOCKET_ERROR;
}

Port TCPServer::GetPort()
{
    // Get bound port if it was random
    if (_port == 0)
    {
		_port = GetBoundPort(_socket);

        if (!_port)
        {
            FATAL("TCPServer") << "Unable to get own address: " << SocketGetLastErrorString();
            return 0;
        }
    }

    return _port;
}

void TCPServer::Close()
{
    if (_socket != CAT_SOCKET_ERROR)
    {
        CloseSocket(_socket);
        _socket = CAT_SOCKET_ERROR;
    }
}


bool TCPServer::QueueAcceptEx()
{
    // Create an unbound overlapped TCP socket for AcceptEx()
	bool ipv4;
	Socket s;
	if (!CreateSocket(SOCK_STREAM, IPPROTO_TCP, false, s, ipv4))
	{
		WARN("TCPServer") << "Unable to create an accept socket: " << SocketGetLastErrorString();
		return false;
	}

    // Create a new AcceptExOverlapped structure
    AcceptExOverlapped *overlapped = reinterpret_cast<AcceptExOverlapped*>(
		RegionAllocator::ii->Acquire(sizeof(AcceptExOverlapped)) );
    if (!overlapped)
    {
        WARN("TCPServer") << "Unable to allocate AcceptEx overlapped structure: Out of memory.";
        CloseSocket(s);
        return false;
    }
    overlapped->Set(s);

    // Queue up an AcceptEx()
    // AcceptEx will complete on the listen socket, not the socket
    // created above that accepts the connection.
    DWORD received;

    AddRef();

	const int addr_buf_len = sizeof(overlapped->addresses.addr) + 16;

	BOOL result = _lpfnAcceptEx(_socket, s, &overlapped->addresses, 0,
							   addr_buf_len, addr_buf_len,
							   &received, &overlapped->tov.ov);

    // This overlapped operation will always complete unless
    // we get an error code other than ERROR_IO_PENDING.
    if (!result && WSAGetLastError() != ERROR_IO_PENDING)
    {
        WARN("TCPServer") << "AcceptEx error: " << SocketGetLastErrorString();
        CloseSocket(s);
        RegionAllocator::ii->Release(overlapped);
        ReleaseRef();
        return false;
    }

    return true;
}

bool TCPServer::QueueAccepts()
{
    u32 queueSize = Settings::ref()->getInt("TCPServer.AcceptQueueSize", 8);
    if (queueSize > 1000) queueSize = 1000;

    u32 queued = queueSize;
    while (QueueAcceptEx() && queueSize--);
    queued -= queueSize;

    if (!queued)
    {
        FATAL("TCPServer") << "error to pre-accept any connections: Server cannot accept connections";
        return false;
    }

    INFO("TCPServer") << "Queued " << queued << " pre-accepted connections";
    return true;
}

void TCPServer::OnAcceptExComplete(int error, AcceptExOverlapped *overlapped)
{
    if (error)
    {
        // ERROR_SEM_TIMEOUT     : This means a half-open connection has reset
        // ERROR_NETNAME_DELETED : This means a three-way handshake reset before completion
        if (error == ERROR_SEM_TIMEOUT ||
			error == ERROR_NETNAME_DELETED)
        {
            // Queue up another AcceptEx to fill in for this one
            QueueAcceptEx();
        }

        return;
    }

    // Get local and remote socket addresses
    int localLen = 0, remoteLen = 0;
	sockaddr *local, *remote;

	const int addr_buf_len = sizeof(overlapped->addresses.addr) + 16;

	_lpfnGetAcceptExSockAddrs(&overlapped->addresses, 0, addr_buf_len, addr_buf_len,
							  &local, &localLen, &remote, &remoteLen);

    // Instantiate a server connection
    TCPServerConnection *conn = InstantiateServerConnection();
    if (!conn) return;

    // Pass the connection parameters to the connection instance for acceptance
    if (!conn->AcceptConnection(_socket, overlapped->acceptSocket, _lpfnDisconnectEx,
								NetAddr(local), NetAddr(remote)))
        conn->ReleaseRef();

    // Queue up another AcceptEx to fill in for this one
    QueueAcceptEx();
}
