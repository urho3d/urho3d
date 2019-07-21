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

void RecvFromOverlapped::Reset()
{
    CAT_OBJCLR(tov.ov);
    addrLen = sizeof(addr);
}


//// UDP Endpoint

UDPEndpoint::UDPEndpoint()
{
    _port = 0;
    _closing = 0;
    _socket = CAT_SOCKET_ERROR;
}

UDPEndpoint::~UDPEndpoint()
{
    if (_socket != CAT_SOCKET_ERROR)
        CloseSocket(_socket);
}

void UDPEndpoint::Close()
{
    // Only allow close to run once
    if (Atomic::Add(&_closing, 1) == 0)
    {
        if (_socket != CAT_SOCKET_ERROR)
        {
            CloseSocket(_socket);
            _socket = CAT_SOCKET_ERROR;
        }

		// Allow the library user to react to closure sooner than the destructor.
        OnClose();

		// Starts with reference count equal 1; so this puts the object in a state
		// where as soon as all of the references are extinguished it is deleted.
        ReleaseRef();
    }
}

bool UDPEndpoint::IgnoreUnreachable()
{
    // FALSE = Disable behavior where, after receiving an ICMP Unreachable message,
    // WSARecvFrom() will fail.  Disables ICMP completely; normally this is good.
    // But when you're writing a client endpoint, you probably want to listen to
    // ICMP Port Unreachable or other failures until you get the first packet.
    // After that call IgnoreUnreachable() to avoid spoofed ICMP exploits.

	if (_socket == CAT_SOCKET_ERROR)
		return false;

	DWORD dwBytesReturned = 0;
    BOOL bNewBehavior = FALSE;
    if (WSAIoctl(_socket, SIO_UDP_CONNRESET, &bNewBehavior,
				 sizeof(bNewBehavior), 0, 0, &dwBytesReturned, 0, 0) == CAT_SOCKET_ERROR)
	{
		WARN("UDPEndpoint") << "Unable to ignore ICMP Unreachable: " << SocketGetLastErrorString();
		return false;
	}

	return true;
}

bool UDPEndpoint::Bind(Port port, bool ignoreUnreachable)
{
    // Create an unbound, overlapped UDP socket for the endpoint
    Socket s;
	bool ipv4;
	if (!CreateSocket(SOCK_DGRAM, IPPROTO_UDP, true, s, ipv4))
	{
		FATAL("UDPEndpoint") << "Unable to create a UDP socket: " << SocketGetLastErrorString();
		return false;
    }
	_ipv6 = !ipv4;

    // Set SO_SNDBUF to zero for a zero-copy network stack (we maintain the buffers)
    int buffsize = 0;
    if (setsockopt(s, SOL_SOCKET, SO_SNDBUF, (char*)&buffsize, sizeof(buffsize)))
    {
		FATAL("UDPEndpoint") << "Unable to zero the send buffer: " << SocketGetLastErrorString();
		CloseSocket(s);
		return false;
    }

    _socket = s;

	// Ignore ICMP Unreachable
    if (ignoreUnreachable) IgnoreUnreachable();

    // Bind the socket to a given port
    if (!NetBind(s, port, ipv4))
    {
        FATAL("UDPEndpoint") << "Unable to bind to port: " << SocketGetLastErrorString();
        CloseSocket(s);
        _socket = CAT_SOCKET_ERROR;
        return false;
    }

    // Prepare to receive completions in the worker threads
    if (!ThreadPool::ref()->Associate((HANDLE)s, this) ||
        !QueueWSARecvFrom())
    {
        CloseSocket(s);
        _socket = CAT_SOCKET_ERROR;
        return false;
    }

    _port = port;

    INANE("UDPEndpoint") << "Open on port " << GetPort();

    return true;
}

bool UDPEndpoint::Valid()
{
    return _socket != CAT_SOCKET_ERROR;
}

Port UDPEndpoint::GetPort()
{
    // Get bound port if it was random
    if (_port == 0)
    {
		_port = GetBoundPort(_socket);

		if (!_port)
        {
            FATAL("UDPEndpoint") << "Unable to get own address: " << SocketGetLastErrorString();
            return 0;
        }
    }

    return _port;
}

bool UDPEndpoint::Post(const NetAddr &addr, void *buffer, u32 bytes)
{
	if (_closing)
		return false;

    // Recover the full overlapped structure from data pointer
    TypedOverlapped *sendOv = reinterpret_cast<TypedOverlapped*>(
		reinterpret_cast<u8*>(buffer) - sizeof(TypedOverlapped) );

    sendOv->Set(OVOP_SENDTO);

    if (!QueueWSASendTo(addr, sendOv, bytes))
    {
        RegionAllocator::ii->Release(sendOv);
        return false;
    }

    return true;
}

bool UDPEndpoint::QueueWSARecvFrom(RecvFromOverlapped *recvOv)
{
	if (_closing)
		return false;

	AddRef();

    recvOv->Reset();

    WSABUF wsabuf;
    wsabuf.buf = reinterpret_cast<CHAR*>( GetTrailingBytes(recvOv) );
    wsabuf.len = RECVFROM_DATA_SIZE;

    // Queue up a WSARecvFrom()
    DWORD flags = 0, bytes;
    int result = WSARecvFrom(_socket, &wsabuf, 1, &bytes, &flags,
							 reinterpret_cast<sockaddr*>( &recvOv->addr ),
							 &recvOv->addrLen, &recvOv->tov.ov, 0); 

    // This overlapped operation will always complete unless
    // we get an error code other than ERROR_IO_PENDING.
    if (result && WSAGetLastError() != ERROR_IO_PENDING)
    {
        FATAL("UDPEndpoint") << "WSARecvFrom error: " << SocketGetLastErrorString();
		ReleaseRef();
        return false;
    }

    return true;
}

bool UDPEndpoint::QueueWSARecvFrom()
{
    if (_closing)
        return false;

    // Create a new RecvFromOverlapped structure for receiving
    RecvFromOverlapped *recvOv = reinterpret_cast<RecvFromOverlapped*>(
		RegionAllocator::ii->Acquire(sizeof(RecvFromOverlapped) + RECVFROM_DATA_SIZE) );
    if (!recvOv)
    {
        FATAL("UDPEndpoint") << "Unable to allocate a receive buffer: Out of memory";
        return false;
    }
    recvOv->tov.opcode = OVOP_RECVFROM;

    if (!QueueWSARecvFrom(recvOv))
	{
		RegionAllocator::ii->Release(recvOv);
		return false;
	}

	return true;
}

void UDPEndpoint::OnWSARecvFromComplete(ThreadPoolLocalStorage *tls, int error, RecvFromOverlapped *recvOv, u32 bytes)
{
    switch (error)
    {
    case 0:
    case ERROR_MORE_DATA: // Truncated packet
        OnRead(tls, recvOv->addr,
			   GetTrailingBytes(recvOv), bytes);
        break;

    case ERROR_NETWORK_UNREACHABLE:
    case ERROR_HOST_UNREACHABLE:
    case ERROR_PROTOCOL_UNREACHABLE:
    case ERROR_PORT_UNREACHABLE:
        // ICMP Errors:
        // These can be easily spoofed and should never be used to terminate a protocol.
        // This callback should be ignored after the first packet is received from the remote host.
        OnUnreachable(recvOv->addr);
    }

	if (!QueueWSARecvFrom(recvOv))
    {
        RegionAllocator::ii->Release(recvOv);
        Close();
    }
}

bool UDPEndpoint::QueueWSASendTo(const NetAddr &addr, TypedOverlapped *sendOv, u32 bytes)
{
    if (_closing)
        return false;

	// Unwrap NetAddr object to something sockaddr-compatible
	NetAddr::SockAddr out_addr;
	int addr_len;
	if (!addr.Unwrap(out_addr, addr_len))
		return false;

    WSABUF wsabuf;
    wsabuf.buf = reinterpret_cast<CHAR*>( GetTrailingBytes(sendOv) );
    wsabuf.len = bytes;

    AddRef();

    // Fire off a WSASendTo() and forget about it
    int result = WSASendTo(_socket, &wsabuf, 1, 0, 0,
						   reinterpret_cast<const sockaddr*>( &out_addr ),
						   addr_len, &sendOv->ov, 0);

    // This overlapped operation will always complete unless
    // we get an error code other than ERROR_IO_PENDING.
    if (result && WSAGetLastError() != ERROR_IO_PENDING)
    {
        FATAL("UDPEndpoint") << "WSASendTo error: " << SocketGetLastErrorString();
        ReleaseRef();
        // Does not destroy the buffer on error -- just returns false
        return false;
    }

    return true;
}

void UDPEndpoint::OnWSASendToComplete(int error, u32 bytes)
{
    if (_closing)
        return;

    if (error)
    {
        Close();
        return;
    }

    OnWrite(bytes);
}
