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

TCPConnexion::TCPConnexion(int priorityLevel)
	: ThreadRefObject(priorityLevel)
{
    // Initialize to an invalid state.
    // Connection is invalid until AcceptConnection() runs successfully.
    _socket = SOCKET_ERROR;
    _disconnecting = 0;
}

TCPConnexion::~TCPConnexion()
{
    if (_socket != SOCKET_ERROR)
        CloseSocket(_socket);
}

bool TCPConnexion::Accept(ThreadPoolLocalStorage *tls, Socket listenSocket, Socket acceptSocket,
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
        WARN("TCPConnexion")
            << "Unable to update accept socket context: " << SocketGetLastErrorString();
        return false;
    }

    // Set SO_SNDBUF to zero for a zero-copy network stack (we maintain the buffers)
    int bufsize = 0;
    if (setsockopt(acceptSocket, SOL_SOCKET, SO_SNDBUF, (char*)&bufsize, sizeof(bufsize)))
    {
        FATAL("TCPConnexion") << "Unable to zero the send buffer: " << SocketGetLastErrorString();
        return false;
    }

    // Prepare to receive completions in the worker threads.
    // Do this first so that if the server will send data immediately it
    // won't block or leak memory or fail or whatever would happen.
    if (!ThreadPool::ref()->Associate((HANDLE)acceptSocket, this))
	{
		FATAL("TCPConnexion") << "Unable to associate with the thread pool";
        return false;
	}

    // Return true past this point so connection object will not be deleted
    // and use DisconnectClient() to abort the connection instead now.

    // Let the derived class determine if the connection should be accepted
    if (!OnConnectFromClient(tls, remoteClientAddress) ||
		!Read())
	{
        Disconnect();
	}

    return true;
}

void TCPConnexion::Disconnect()
{
	// Only allow disconnect to run once
	if (Atomic::Add(&_disconnecting, 1) == 0)
	{
		OnDisconnectFromClient();

		if (!Disco())
		{
			// Release self-reference; will delete this object if no other
			// objects are maintaining a reference to this one.
			ReleaseRef();
		}
	}
}


//// Begin Event

bool TCPConnexion::Post(u8 *data, u32 data_bytes, u32 skip_bytes)
{
	AsyncBuffer *buffer = AsyncBuffer::Promote(data);

	if (_disconnecting)
	{
		buffer->Release();
		return false;
	}

	buffer->Reset(fastdelegate::MakeDelegate(this, &TCPConnexion::OnWrite));

	WSABUF wsabuf;
	wsabuf.buf = reinterpret_cast<CHAR*>( data + skip_bytes );
	wsabuf.len = data_bytes;

	AddRef();

	// Fire off a WSASend() and forget about it
	int result = WSASend(_socket, &wsabuf, 1, 0, 0, buffer->GetOv(), 0);

	// This overlapped operation will always complete unless
	// we get an error code other than ERROR_IO_PENDING.
	if (result && WSAGetLastError() != ERROR_IO_PENDING)
	{
		FATAL("TCPConnexion") << "WSASend error: " << SocketGetLastErrorString();
		buffer->Release();
		ReleaseRef();
		return false;
	}

	return true;
}

bool TCPConnexion::Read(AsyncBuffer *buffer)
{
	if (_disconnecting)
	{
		if (buffer) buffer->Release();
		return false;
	}

	// If unable to get an AsyncSimpleData object,
	if (!buffer && !AsyncBuffer::Acquire(buffer, 2048 - AsyncBuffer::OVERHEAD() - 8))
	{
		WARN("TCPConnexion") << "Out of memory: Unable to allocate AcceptEx overlapped structure";
		return false;
	}

	buffer->Reset(fastdelegate::MakeDelegate(this, &TCPConnexion::OnRead));

	WSABUF wsabuf;
	wsabuf.buf = reinterpret_cast<CHAR*>( buffer->GetData() );
	wsabuf.len = buffer->GetDataBytes();

	AddRef();

	// Queue up a WSARecv()
	DWORD flags = 0, bytes;
	int result = WSARecv(_socket, &wsabuf, 1, &bytes, &flags, buffer->GetOv(), 0); 

	// This overlapped operation will always complete unless
	// we get an error code other than ERROR_IO_PENDING.
	if (result && WSAGetLastError() != ERROR_IO_PENDING)
	{
		FATAL("TCPConnexion") << "WSARecv error: " << SocketGetLastErrorString();
		buffer->Release();
		ReleaseRef();
		return false;
	}

	return true;
}

bool TCPConnexion::Disco(AsyncBuffer *buffer)
{
	if (!buffer && !AsyncBuffer::Acquire(buffer))
	{
		WARN("TCPConnexion") << "Out of memory: Unable to allocate overlapped structure";
		return false;
	}

	buffer->Reset(fastdelegate::MakeDelegate(this, &TCPConnexion::OnDisco));

    AddRef();

    // Queue up a DisconnectEx()
    BOOL result = _lpfnDisconnectEx(_socket, buffer->GetOv(), 0, 0); 

    // This overlapped operation will always complete unless
    // we get an error code other than ERROR_IO_PENDING.
    if (!result && WSAGetLastError() != ERROR_IO_PENDING)
    {
        FATAL("TCPConnexion") << "DisconnectEx error: " << SocketGetLastErrorString();
		buffer->Release();
        ReleaseRef();
        return false;
    }

    return true;
}


//// Event Completion

bool TCPConnexion::OnRead(ThreadPoolLocalStorage *tls, int error, AsyncBuffer *buffer, u32 bytes)
{
	if (_disconnecting)
		return true;

	if (error)
	{
		ReportUnexpectedSocketError(error);
		Disconnect();
		return true;
	}

	// When WSARecv completes with no data, it indicates a graceful disconnect.
	if (!bytes || !OnReadFromClient(tls, buffer->GetData(), bytes))
		Disconnect();
	else
	{
		// Queue up the next receive
		if (!Read(buffer))
			Disconnect();

		return false; // Do not delete overlapped object
	}

	return true; // Delete overlapped object
}

bool TCPConnexion::OnWrite(ThreadPoolLocalStorage *tls, int error, AsyncBuffer *buffer, u32 bytes)
{
	if (_disconnecting)
		return true;

	if (error)
	{
		ReportUnexpectedSocketError(error);
		Disconnect();
		return true;
	}

	return OnWriteToClient(tls, buffer, bytes);
}

bool TCPConnexion::OnDisco(ThreadPoolLocalStorage *tls, int error, AsyncBuffer *buffer, u32 bytes)
{
	if (error) ReportUnexpectedSocketError(error);

	// Release final reference
	ReleaseRef();

	return true; // Delete overlapped object
}
