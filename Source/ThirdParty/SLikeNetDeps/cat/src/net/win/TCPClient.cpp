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

TCPClient::TCPClient(int priorityLevel)
	: ThreadRefObject(priorityLevel)
{
    // Initialize to invalid socket
    _socket = SOCKET_ERROR;
    _disconnecting = 0;
}

TCPClient::~TCPClient()
{
    if (_socket != SOCKET_ERROR)
        CloseSocket(_socket);
}

bool TCPClient::Connect(bool onlySupportIPv4, const NetAddr &remoteServerAddress)
{
    // Create an unbound, overlapped TCP socket for the listen port
	Socket s;
	if (!CreateSocket(SOCK_STREAM, IPPROTO_TCP, true, s, onlySupportIPv4))
	{
		FATAL("TCPClient") << "Unable to create a TCP socket: " << SocketGetLastErrorString();
		return false;
    }
	_ipv6 = !onlySupportIPv4;

    // Set SO_SNDBUF to zero for a zero-copy network stack (we maintain the buffers)
    int buffsize = 0;
    if (setsockopt(s, SOL_SOCKET, SO_SNDBUF, (char*)&buffsize, sizeof(buffsize)))
    {
        FATAL("TCPClient") << "Unable to zero the send buffer: " << SocketGetLastErrorString();
        CloseSocket(s);
        return false;
    }

    // Bind the socket to a random port as required by ConnectEx()
    if (!NetBind(s, 0, onlySupportIPv4))
    {
        FATAL("TCPClient") << "Unable to bind to port: " << SocketGetLastErrorString();
        CloseSocket(s);
        return false;
    }

    _socket = s;

    // Prepare to receive completions in the worker threads
    // Connect to server asynchronously
    if (!ThreadPool::ref()->Associate((HANDLE)s, this) ||
        !ConnectEx(remoteServerAddress))
    {
        CloseSocket(s);
        _socket = SOCKET_ERROR;
        return false;
    }

    return true;
}

void TCPClient::Disconnect()
{
    // Only allow disconnect to run once
    if (Atomic::Add(&_disconnecting, 1) == 0)
    {
        OnDisconnectFromServer();

		if (!Disco())
		{
			// Release self-reference; will delete this object if no other
			// objects are maintaining a reference to this one.
			ReleaseRef();
		}
    }
}


//// Begin Event

bool TCPClient::ConnectEx(const NetAddr &remoteServerAddress)
{
    // Get ConnectEx() interface
    GUID GuidConnectEx = WSAID_CONNECTEX;
    LPFN_CONNECTEX lpfnConnectEx;
    DWORD copied;

    if (WSAIoctl(_socket, SIO_GET_EXTENSION_FUNCTION_POINTER, &GuidConnectEx,
                 sizeof(GuidConnectEx), &lpfnConnectEx, sizeof(lpfnConnectEx), &copied, 0, 0))
    {
        FATAL("TCPClient") << "Unable to get ConnectEx interface: " << SocketGetLastErrorString();
        return false;
    }

	// Unwrap NetAddr
	NetAddr::SockAddr addr_out;
	int addr_len;
	if (!remoteServerAddress.Unwrap(addr_out, addr_len, _ipv6))
	{
		FATAL("TCPClient") << "Unable to execute ConnectEx: Server address invalid";
		return false;
	}

	// If unable to get an AsyncServerAccept object,
	AsyncBuffer *buffer;
	if (!AsyncBuffer::Acquire(buffer))
	{
		FATAL("TCPClient") << "Out of memory: Unable to allocate ConnectEx overlapped structure";
		return false;
	}

	buffer->Reset(fastdelegate::MakeDelegate(this, &TCPClient::OnConnectEx));

    AddRef();

    // Queue up a ConnectEx()
    BOOL result = lpfnConnectEx(_socket, reinterpret_cast<sockaddr*>( &addr_out ),
                                addr_len, 0, 0, 0, buffer->GetOv()); 

    // This overlapped operation will always complete unless
    // we get an error code other than ERROR_IO_PENDING.
    if (!result && WSAGetLastError() != ERROR_IO_PENDING)
    {
        FATAL("TCPClient") << "ConnectEx error: " << SocketGetLastErrorString();
        buffer->Release();
        ReleaseRef();
        return false;
    }

    return true;
}

bool TCPClient::Post(u8 *data, u32 data_bytes, u32 skip_bytes)
{
	AsyncBuffer *buffer = AsyncBuffer::Promote(data);

	if (_disconnecting)
	{
		buffer->Release();
		return false;
	}

	buffer->Reset(fastdelegate::MakeDelegate(this, &TCPClient::OnWrite));

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
		FATAL("TCPClient") << "WSASend error: " << SocketGetLastErrorString();
		buffer->Release();
		ReleaseRef();
		return false;
	}

	return true;
}

bool TCPClient::Read(AsyncBuffer *buffer)
{
	if (_disconnecting)
	{
		if (buffer) buffer->Release();
		return false;
	}

	// If unable to get an AsyncSimpleData object,
	if (!buffer && !AsyncBuffer::Acquire(buffer, 2048 - AsyncBuffer::OVERHEAD() - 8))
	{
		WARN("TCPClient") << "Out of memory: Unable to allocate AcceptEx overlapped structure";
		return false;
	}

	buffer->Reset(fastdelegate::MakeDelegate(this, &TCPClient::OnRead));

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
		FATAL("TCPClient") << "WSARecv error: " << SocketGetLastErrorString();
		buffer->Release();
		ReleaseRef();
		return false;
	}

	return true;
}

bool TCPClient::Disco(AsyncBuffer *buffer)
{
    // Get DisconnectEx() interface
    GUID GuidDisconnectEx = WSAID_DISCONNECTEX;
    LPFN_DISCONNECTEX lpfnDisconnectEx;
    DWORD copied;

    if (WSAIoctl(_socket, SIO_GET_EXTENSION_FUNCTION_POINTER, &GuidDisconnectEx,
                 sizeof(GuidDisconnectEx), &lpfnDisconnectEx, sizeof(lpfnDisconnectEx),
				 &copied, 0, 0))
    {
        FATAL("TCPClient") << "Unable to get DisconnectEx interface: " << SocketGetLastErrorString();
		if (buffer) buffer->Release();
        return false;
    }

	if (!buffer && !AsyncBuffer::Acquire(buffer))
	{
		WARN("TCPClient") << "Out of memory: Unable to allocate overlapped structure";
		return false;
	}

	buffer->Reset(fastdelegate::MakeDelegate(this, &TCPClient::OnDisco));

	AddRef();

	// Queue up a DisconnectEx()
	BOOL result = lpfnDisconnectEx(_socket, buffer->GetOv(), 0, 0); 

	// This overlapped operation will always complete unless
	// we get an error code other than ERROR_IO_PENDING.
	if (!result && WSAGetLastError() != ERROR_IO_PENDING)
	{
		FATAL("TCPClient") << "DisconnectEx error: " << SocketGetLastErrorString();
		buffer->Release();
		ReleaseRef();
		return false;
	}

	return true;
}


//// Event Completion

bool TCPClient::OnConnectEx(ThreadPoolLocalStorage *tls, int error, AsyncBuffer *buffer, u32 bytes)
{
	if (_disconnecting)
		return true;

	if (error)
	{
		ReportUnexpectedSocketError(error);
		Disconnect();
		return true;
	}

	// Finish socket creation by updating the connection context
	if (setsockopt(_socket, SOL_SOCKET, SO_UPDATE_CONNECT_CONTEXT, 0, 0))
	{
		WARN("TCPClient") << "Unable to update connect socket context: " << SocketGetLastErrorString();
		Disconnect();
		return true;
	}

	// Notify the derived class that we connected
	OnConnectToServer(tls);

	// Queue up a receive
	if (!Read())
		Disconnect();

	return true;
}

bool TCPClient::OnRead(ThreadPoolLocalStorage *tls, int error, AsyncBuffer *buffer, u32 bytes)
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
	if (!bytes || !OnReadFromServer(tls, buffer->GetData(), bytes))
		Disconnect();
	else
	{
		// Queue up the next receive
		if (Read(buffer))
			Disconnect();

		return false; // Do not delete overlapped object
	}

	return true;
}

bool TCPClient::OnWrite(ThreadPoolLocalStorage *tls, int error, AsyncBuffer *buffer, u32 bytes)
{
	if (_disconnecting)
		return true;

	if (error)
	{
		ReportUnexpectedSocketError(error);
		Disconnect();
		return true;
	}

	return OnWriteToServer(tls, buffer, bytes);
}

bool TCPClient::OnDisco(ThreadPoolLocalStorage *tls, int error, AsyncBuffer *buffer, u32 bytes)
{
	if (error) ReportUnexpectedSocketError(error);

	// Release final reference
	ReleaseRef();

	return true; // Delete overlapped object
}


//// TCPClientQueued

TCPClientQueued::TCPClientQueued(int priorityLevel)
	: TCPClient(priorityLevel)
{
    _queueBuffer = 0;
    _queuing = true;
}

TCPClientQueued::~TCPClientQueued()
{
    if (_queueBuffer) _queueBuffer->Release();
}

bool TCPClientQueued::Post(u8 *data, u32 data_bytes, u32 skip_bytes)
{
    // Try not to hold a lock if we can help it
    if (!_queuing) return TCPClient::Post(data, data_bytes, skip_bytes);

    AutoMutex lock(_queueLock);

    // Check to make sure we're still queuing
    if (!_queuing)
    {
        lock.Release();

		return TCPClient::Post(data, data_bytes, skip_bytes);
    }

	AsyncBuffer *buffer = AsyncBuffer::Promote(data);

	// If queue buffer has not been created,
    if (!_queueBuffer)
	{
		_queueBuffer = buffer;
	}
	else
    {
		// Otherwise append to the end of the queue buffer,
		u32 queue_bytes = _queueBuffer->GetDataBytes();
		u32 bytes = buffer->GetDataBytes();

        _queueBuffer = _queueBuffer->Resize(queue_bytes + bytes);

		if (_queueBuffer)
		{
			memcpy(_queueBuffer->GetData() + queue_bytes, data, bytes);
		}

		buffer->Release();

		return !!_queueBuffer;
	}

    return true;
}

void TCPClientQueued::PostQueuedToServer()
{
	// Try not to hold a lock if we can help it
	if (!_queuing) return;

    AutoMutex lock(_queueLock);

	// If queue buffer exists,
    if (_queueBuffer)
    {
		TCPClient::Post(_queueBuffer->GetData(), _queueBuffer->GetDataBytes());
        _queueBuffer = 0;
    }

    _queuing = false;
}
