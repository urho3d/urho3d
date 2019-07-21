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
using namespace std;
using namespace cat;


//// TCPConnection

TCPConnection::TCPConnection(int priorityLevel)
	: ThreadRefObject(priorityLevel)
{
    // Initialize to an invalid state.
    // Connection is invalid until AcceptConnection() runs successfully.
    _socket = SOCKET_ERROR;
    _recvOv = 0;
    _disconnecting = 0;
}

TCPConnection::~TCPConnection()
{
    if (_socket != SOCKET_ERROR)
        CloseSocket(_socket);

    // Release memory for the overlapped structure
    if (_recvOv)
        RegionAllocator::ii->Release(_recvOv);
}

bool TCPConnection::ValidServerConnection()
{
    return _socket != SOCKET_ERROR;
}

void TCPConnection::DisconnectClient()
{
    // Only allow disconnect to run once
    if (Atomic::Add(&_disconnecting, 1) == 0)
    {
        OnDisconnectFromClient();

        if (!QueueDisconnectEx())
        {
            // Release self-reference; will delete this object if no other
            // objects are maintaining a reference to this one.
            ReleaseRef();
        }
    }
}

bool TCPConnection::PostToClient(void *buffer, u32 bytes)
{
    // Recover the full overlapped structure from data pointer
    TypedOverlapped *sendOv = reinterpret_cast<TypedOverlapped*>(
		reinterpret_cast<u8*>(buffer) - sizeof(TypedOverlapped) );

    sendOv->Set(OVOP_SERVER_SEND);

    if (!QueueWSASend(sendOv, bytes))
    {
        RegionAllocator::ii->Release(sendOv);
        return false;
    }

    return true;
}


bool TCPConnection::AcceptConnection(Socket listenSocket, Socket acceptSocket,
                                LPFN_DISCONNECTEX lpfnDisconnectEx,
                                const NetAddr &acceptAddress, const NetAddr &remoteClientAddress)
{
    // If we return false here this object will be deleted.

    // Store parameters
    _socket = acceptSocket;
    _lpfnDisconnectEx = lpfnDisconnectEx;

    // Finalize the accept socket context
    if (setsockopt(acceptSocket, SOL_SOCKET, SO_UPDATE_ACCEPT_CONTEXT,
                    (char *)&listenSocket, sizeof(listenSocket)))
    {
        WARN("TCPConnection")
            << "Unable to update accept socket context: " << SocketGetLastErrorString();
        return false;
    }

    // Set SO_SNDBUF to zero for a zero-copy network stack (we maintain the buffers)
    int bufsize = 0;
    if (setsockopt(acceptSocket, SOL_SOCKET, SO_SNDBUF, (char*)&bufsize, sizeof(bufsize)))
    {
        FATAL("TCPConnection") << "Unable to zero the send buffer: " << SocketGetLastErrorString();
        return false;
    }

    // Create a new overlapped structure for receiving
    _recvOv = AcquireBuffer<TypedOverlapped>(RECV_DATA_SIZE);
    if (!_recvOv)
    {
        FATAL("TCPConnection") << "Unable to allocate a receive buffer: Out of memory";
        return false;
    }
    _recvOv->Set(OVOP_SERVER_RECV);

    // Prepare to receive completions in the worker threads.
    // Do this first so that if the server will send data immediately it
    // won't block or leak memory or fail or whatever would happen.
    if (!ThreadPool::ref()->Associate((HANDLE)acceptSocket, this))
        return false;

    // Return true past this point so connection object will not be deleted
    // and use DisconnectClient() to abort the connection instead now.

    // Let the derived class determine if the connection should be accepted
    if (!OnConnectFromClient(remoteClientAddress))
        DisconnectClient();
    else
    {
        // Queue up a WSARecv() to accept data from the client.
        if (!QueueWSARecv())
            DisconnectClient();
    }

    return true;
}


bool TCPConnection::QueueWSARecv()
{
    if (_disconnecting)
        return false;

    WSABUF wsabuf;
    wsabuf.buf = reinterpret_cast<CHAR*>( GetTrailingBytes(_recvOv) );
    wsabuf.len = RECV_DATA_SIZE;

    AddRef();

    // Queue up a WSARecv()
    DWORD flags = 0, bytes;
	int result = WSARecv(_socket, &wsabuf, 1, &bytes, &flags, &_recvOv->ov, 0); 

    // This overlapped operation will always complete unless
    // we get an error code other than ERROR_IO_PENDING.
    if (result && WSAGetLastError() != ERROR_IO_PENDING)
    {
        FATAL("TCPConnection") << "WSARecv error: " << SocketGetLastErrorString();
        ReleaseRef();
        return false;
    }

    return true;
}

void TCPConnection::OnWSARecvComplete(int error, u32 bytes)
{
    if (_disconnecting)
        return;

    if (error)
    {
        DisconnectClient();
        return;
    }

    // When WSARecv completes with no data, it indicates a graceful disconnect.
    if (!bytes || !OnReadFromClient(GetTrailingBytes(_recvOv), bytes))
        DisconnectClient();
    else
    {
        // Reset the overlapped structure so it can be re-used
        _recvOv->Reset();

        // Queue up the next receive
        if (!QueueWSARecv())
            DisconnectClient();
    }
}


bool TCPConnection::QueueWSASend(TypedOverlapped *sendOv, u32 bytes)
{
    if (_disconnecting)
        return false;

    WSABUF wsabuf;
    wsabuf.buf = reinterpret_cast<CHAR*>( GetTrailingBytes(sendOv) );
    wsabuf.len = bytes;

    AddRef();

    // Fire off a WSASend() and forget about it
    int result = WSASend(_socket, &wsabuf, 1, 0, 0, &sendOv->ov, 0);

    // This overlapped operation will always complete unless
    // we get an error code other than ERROR_IO_PENDING.
    if (result && WSAGetLastError() != ERROR_IO_PENDING)
    {
        FATAL("TCPConnection") << "WSASend error: " << SocketGetLastErrorString();
        // Does not destroy the buffer on error -- just returns false
        ReleaseRef();
        return false;
    }

    return true;
}

void TCPConnection::OnWSASendComplete(int error, u32 bytes)
{
    if (_disconnecting)
        return;

    if (error)
    {
        DisconnectClient();
        return;
    }

    OnWriteToClient(bytes);
}


bool TCPConnection::QueueDisconnectEx()
{
    // Create a new overlapped structure for receiving
    TypedOverlapped *overlapped = AcquireBuffer<TypedOverlapped>();
    if (!overlapped)
    {
        FATAL("TCPConnection") << "Unable to allocate a DisconnectEx overlapped structure: Out of memory";
        return false;
    }
    overlapped->Set(OVOP_SERVER_CLOSE);

    AddRef();

    // Queue up a DisconnectEx()
    BOOL result = _lpfnDisconnectEx(_socket, &overlapped->ov, 0, 0); 

    // This overlapped operation will always complete unless
    // we get an error code other than ERROR_IO_PENDING.
    if (!result && WSAGetLastError() != ERROR_IO_PENDING)
    {
        FATAL("TCPConnection") << "DisconnectEx error: " << SocketGetLastErrorString();
        RegionAllocator::ii->Release(overlapped);
        ReleaseRef();
        return false;
    }

    return true;
}

void TCPConnection::OnDisconnectExComplete(int error)
{
    ReleaseRef();
}
