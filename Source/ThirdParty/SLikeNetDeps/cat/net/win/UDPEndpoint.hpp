/*
	Copyright (c) 2009-2010 Christopher A. Taylor.  All rights reserved.

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

#ifndef CAT_UDP_ENDPOINT_HPP
#define CAT_UDP_ENDPOINT_HPP

/*
	Windows version of thread pool sockets with IO Completion Ports

	Included from <cat/net/ThreadPoolSockets.hpp>
	Do not include directly
*/

namespace cat {


/*
    class UDPEndpoint

    Object that represents a UDP endpoint bound to a single port
*/
class UDPEndpoint : public ThreadRefObject
{
	Socket _socket;
	Port _port;
	volatile u32 _closing;
	bool _ipv6;

	struct RecvFromTag
	{
		// Not necessarily an IPv6 address, but we allocate enough space for one
		int addrLen;
		sockaddr_in6 addr;
	};

public:
    UDPEndpoint(int priorityLevel);
    virtual ~UDPEndpoint();

	CAT_INLINE bool Valid() { return _socket != SOCKET_ERROR; }
    Port GetPort();

	// Is6() result is only valid AFTER Bind()
	CAT_INLINE bool Is6() { return _ipv6; }
	CAT_INLINE bool IsClosed() { return _closing != 0; }

    // For servers: Bind() with ignoreUnreachable = true ((default))
    // For clients: Bind() with ignoreUnreachable = false and call this
    //              after the first packet from the server is received.
    bool IgnoreUnreachable();

	// Disabled by default; useful for MTU discovery
	bool DontFragment(bool df = true);

    void Close(); // Invalidates this object
    bool Bind(bool onlySupportIPv4, Port port = 0, bool ignoreUnreachable = true, int kernelReceiveBufferBytes = 0);
    bool QueueWSARecvFrom();

	// If Is6() == true, the address must be promoted to IPv6
	// before calling PostWrite() with addr.PromoteTo6()
	// skip_bytes: Number of bytes to skip at the start of the post buffer
	bool Post(const NetAddr &addr, u8 *data, u32 data_bytes, u32 skip_bytes = 0);

private:
	bool Read(AsyncBuffer *buffer = 0);

	bool OnReadComplete(ThreadPoolLocalStorage *tls, int error, AsyncBuffer *buffer, u32 bytes);
	bool OnWriteComplete(ThreadPoolLocalStorage *tls, int error, AsyncBuffer *buffer, u32 bytes);

protected:
	virtual void OnRead(ThreadPoolLocalStorage *tls, const NetAddr &addr, u8 *data, u32 bytes) = 0; // false = close
	virtual bool OnWrite(ThreadPoolLocalStorage *tls, AsyncBuffer *buffer, u32 bytes) { return true; } // false = do not delete AsyncBase object
	virtual void OnClose() = 0;
    virtual void OnUnreachable(const NetAddr &addr) {} // Only IP is valid
};


} // namespace cat

#endif // CAT_UDP_ENDPOINT_HPP
