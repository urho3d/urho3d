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

#ifndef CAT_TCP_SERVER_HPP
#define CAT_TCP_SERVER_HPP

/*
	Windows version of thread pool sockets with IO Completion Ports

	Included from <cat/net/ThreadPoolSockets.hpp>
	Do not include directly
*/

namespace cat {


/*
    class TCPServer

    Object that represents a TCP server bound to a single port

    Overload InstantiateServerConnexion() to subclass connections with the server
*/
class TCPServer : public ThreadRefObject
{
    friend class TCPConnexion;

	Socket _socket;
	LPFN_ACCEPTEX _lpfnAcceptEx;
	LPFN_GETACCEPTEXSOCKADDRS _lpfnGetAcceptExSockAddrs;
	LPFN_DISCONNECTEX _lpfnDisconnectEx;
	Port _port;

	struct AcceptTag
	{
		Socket acceptSocket;

		// Space pre-allocated to receive addresses
		// NOTE: This is not necessarily how the addresses are organized in memory
		struct
		{
			// Not necessarily an IPv6 address
			sockaddr_in6 addr[2];
			u8 padding[2*16];
		} addresses;
	};

	bool PostAccept(AsyncBuffer *buffer = 0);
	bool QueueAccepts();

public:
    TCPServer(int priorityLevel);
    virtual ~TCPServer();

    bool ValidServer();
    Port GetPort();

	bool Bind(bool onlySupportIPv4, Port port = 0);
    void Close();

protected:
	// Return true to release overlapped object memory, or return false to keep it
	virtual bool OnAccept(ThreadPoolLocalStorage *tls, int error, AsyncBuffer *buffer, u32 bytes);

protected:
	virtual TCPConnexion *InstantiateServerConnexion() = 0;
};


} // namespace cat

#endif // CAT_TCP_SERVER_HPP
