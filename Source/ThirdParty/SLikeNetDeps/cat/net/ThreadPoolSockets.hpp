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

// TODO: Half-open connections can easily DoS the TCP server right now.

#ifndef CAT_THREAD_POOL_SOCKETS_HPP
#define CAT_THREAD_POOL_SOCKETS_HPP

#include <cat/threads/ThreadPool.hpp>
#include <cat/net/Sockets.hpp>

namespace cat {


/*
    Thread Pool Sockets library

    Provides a framework for rapidly developing TCP/UDP server and client objects
    that make use of high performance APIs under various server and desktop
	operating systems.

    All network events are processed by a thread pool managed by ThreadPool.
*/

class TCPServer;
class TCPConnexion;
class TCPClient;
class UDPEndpoint;

void ReportUnexpectedSocketError(int error);


} // namespace cat


#if defined (CAT_OS_WINDOWS) // Windows-style IOCP

#include <MSWSock.h>
#include <cat/port/WindowsInclude.hpp>

#include <cat/net/win/TCPServer.hpp>
#include <cat/net/win/TCPConnexion.hpp>
#include <cat/net/win/TCPClient.hpp>
#include <cat/net/win/UDPEndpoint.hpp>

#elif defined(CAT_OS_LINUX) // Linux-style eventfd

#include <cat/net/linux/TCPServer.hpp>
#include <cat/net/linux/TCPConnexion.hpp>
#include <cat/net/linux/TCPClient.hpp>
#include <cat/net/linux/UDPEndpoint.hpp>

#elif defined(CAT_OS_OSX) || defined(CAT_OS_BSD) // BSD-style kevent

#include <cat/net/bsd/TCPServer.hpp>
#include <cat/net/bsd/TCPConnexion.hpp>
#include <cat/net/bsd/TCPClient.hpp>
#include <cat/net/bsd/UDPEndpoint.hpp>

#else // Fall-back

#include <cat/net/generic/TCPServer.hpp>
#include <cat/net/generic/TCPConnexion.hpp>
#include <cat/net/generic/TCPClient.hpp>
#include <cat/net/generic/UDPEndpoint.hpp>

#endif


#endif // CAT_THREAD_POOL_SOCKETS_HPP
