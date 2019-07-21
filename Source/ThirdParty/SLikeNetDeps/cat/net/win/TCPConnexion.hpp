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

#ifndef CAT_TCP_CONNEXION_HPP
#define CAT_TCP_CONNEXION_HPP

/*
	Windows version of thread pool sockets with IO Completion Ports

	Included from <cat/net/ThreadPoolSockets.hpp>
	Do not include directly
*/

namespace cat {


/*
    class TCPConnexion

    Object that represents a TCPServer's connection from a TCPClient

    Object is instantiated just before accepting a connection

    Disconnect()	: Disconnect the client
    Post()			: Send a message to the client
    Valid()			: Returns true if the connection is valid

    OnConnectFromClient()   : Return false to deny this connection
    OnReadFromClient()      : Return false to disconnect the client in response to a message
    OnWriteToClient()       : Informs the derived class that data has been sent
    OnDisconectFromClient() : Informs the derived class that the client has disconnected
*/
class TCPConnexion : public ThreadRefObject
{
    friend class TCPServer;

	Socket _socket;
	LPFN_DISCONNECTEX _lpfnDisconnectEx;
	volatile u32 _disconnecting;

	bool Accept(ThreadPoolLocalStorage *tls, Socket listenSocket, Socket acceptSocket,
		LPFN_DISCONNECTEX lpfnDisconnectEx, const NetAddr &acceptAddress,
		const NetAddr &remoteClientAddress);

public:
    TCPConnexion(int priorityLevel);
    virtual ~TCPConnexion();

	CAT_INLINE bool Valid() { return _socket != SOCKET_ERROR; }

    void Disconnect();
    bool Post(u8 *data, u32 data_bytes, u32 skip_bytes = 0);

private:
	bool Read(AsyncBuffer *buffer = 0);
	bool Disco(AsyncBuffer *buffer = 0);

private:
	bool OnRead(ThreadPoolLocalStorage *tls, int error, AsyncBuffer *buffer, u32 bytes);
	bool OnWrite(ThreadPoolLocalStorage *tls, int error, AsyncBuffer *buffer, u32 bytes);
	bool OnDisco(ThreadPoolLocalStorage *tls, int error, AsyncBuffer *buffer, u32 bytes);

protected:
    virtual bool OnConnectFromClient(ThreadPoolLocalStorage *tls, const NetAddr &remoteClientAddress) = 0; // false = disconnect
    virtual bool OnReadFromClient(ThreadPoolLocalStorage *tls, u8 *data, u32 bytes) = 0; // false = disconnect
    virtual bool OnWriteToClient(ThreadPoolLocalStorage *tls, AsyncBuffer *buffer, u32 bytes) = 0; // true = delete AsyncBuffer
    virtual void OnDisconnectFromClient() = 0;
};


} // namespace cat

#endif // CAT_TCP_CONNEXION_HPP
