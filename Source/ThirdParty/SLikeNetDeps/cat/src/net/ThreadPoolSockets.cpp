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

#include <cat/net/ThreadPoolSockets.hpp>
#include <cat/io/Logging.hpp>
#include <cat/threads/RegionAllocator.hpp>
using namespace std;
using namespace cat;


//// Windows-style IOCP

#if defined (CAT_OS_WINDOWS)

void cat::ReportUnexpectedSocketError(int error)
{
	switch (error)
	{
	case 0:
		// No error
		break;

	case WSA_OPERATION_ABORTED:
	case ERROR_CONNECTION_ABORTED:
	case ERROR_NETNAME_DELETED:  // Operation on closed socket failed
	case ERROR_MORE_DATA:        // UDP buffer not large enough for whole packet
	case ERROR_PORT_UNREACHABLE: // Got an ICMP response back that the destination port is unreachable
	case ERROR_SEM_TIMEOUT:      // Half-open TCP AcceptEx() has reset
		// Operation failure codes (we don't differentiate between them)
		break;

	default:
		// Report other errors this library hasn't been designed to handle yet
		FATAL("TCPConnexion") << "Unexpected failure: " << SocketGetLastErrorString();
		break;
	}
}

#include "win/TCPServer.cpp"
#include "win/TCPConnexion.cpp"
#include "win/TCPClient.cpp"
#include "win/UDPEndpoint.cpp"


//// Linux-style eventfd

#elif defined(CAT_OS_LINUX)

#include "linux/TCPServer.cpp"
#include "linux/TCPConnexion.cpp"
#include "linux/TCPClient.cpp"
#include "linux/UDPEndpoint.cpp"


//// BSD-style kevent

#elif defined(CAT_OS_OSX) || defined(CAT_OS_BSD)

#include "bsd/TCPServer.cpp"
#include "bsd/TCPConnexion.cpp"
#include "bsd/TCPClient.cpp"
#include "bsd/UDPEndpoint.cpp"


//// Fall-back

#else

#include "generic/TCPServer.cpp"
#include "generic/TCPConnexion.cpp"
#include "generic/TCPClient.cpp"
#include "generic/UDPEndpoint.cpp"

#endif
