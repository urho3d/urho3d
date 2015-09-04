/* Copyright The kNet Project.

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License. */
#pragma once

/** @file EndPoint.h
	@brief The class \ref kNet::EndPoint Endpoint. Represents an endpoint of a network connection. */

#if defined(KNET_UNIX) || defined(ANDROID)
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#endif

#include <cstring>
#include <cstdio>
#include <string>

namespace kNet
{

/// EndPoint represents a (ip, port) source or destination of a socket.
struct EndPoint
{
	/// The IPv4 address of the endpoint, stored in big-endian. ///\todo Not IPv6-capable.
	unsigned char ip[4];

	unsigned short port;

	EndPoint()
	{
		Reset();
	}

	/// Clears all fields of this structure to zero.
	void Reset()
	{
		memset(this, 0, sizeof(EndPoint));
	}

	///\todo Not IPv6-capable.
	bool operator < (const EndPoint &rhs) const
	{
		if (ip[0] < rhs.ip[0]) return true;
		if (ip[0] > rhs.ip[0]) return false;
		if (ip[1] < rhs.ip[1]) return true;
		if (ip[1] > rhs.ip[1]) return false;
		if (ip[2] < rhs.ip[2]) return true;
		if (ip[2] > rhs.ip[2]) return false;
		if (ip[3] < rhs.ip[3]) return true;
		if (ip[3] > rhs.ip[3]) return false;
		if (port < rhs.port) return true;
		if (port > rhs.port) return false;

		return false;
	}

	///\todo Not IPv6-capable.
	static EndPoint FromSockAddrIn(const sockaddr_in &addr)
	{
		EndPoint endPoint;
#ifdef WIN32
		endPoint.ip[0] = addr.sin_addr.S_un.S_un_b.s_b1;
		endPoint.ip[1] = addr.sin_addr.S_un.S_un_b.s_b2;
		endPoint.ip[2] = addr.sin_addr.S_un.S_un_b.s_b3;
		endPoint.ip[3] = addr.sin_addr.S_un.S_un_b.s_b4;
#else
		endPoint.ip[0] = addr.sin_addr.s_addr & 0xFF;
		endPoint.ip[1] = (addr.sin_addr.s_addr >> 8) & 0xFF;
		endPoint.ip[2] = (addr.sin_addr.s_addr >> 16) & 0xFF;
		endPoint.ip[3] = (addr.sin_addr.s_addr >> 24) & 0xFF;
#endif
		endPoint.port = ntohs(addr.sin_port);

		return endPoint;
	}

	///\todo Not IPv6-capable.
	sockaddr_in ToSockAddrIn() const
	{
		using namespace std;

		sockaddr_in address;
		memset(&address, 0, sizeof(address));
		address.sin_family = AF_INET;
		address.sin_port = htons(port);
#ifdef WIN32
		address.sin_addr.S_un.S_un_b.s_b1 = ip[0];
		address.sin_addr.S_un.S_un_b.s_b2 = ip[1];
		address.sin_addr.S_un.S_un_b.s_b3 = ip[2];
		address.sin_addr.S_un.S_un_b.s_b4 = ip[3];
#else
		address.sin_addr.s_addr = ip[0] | (ip[1] << 8) | (ip[2] << 16) | (ip[3] << 24);
#endif

		return address;
	}

	///\todo Not IPv6-capable.
	std::string IPToString() const
	{
		char str[256];
		sprintf(str, "%d.%d.%d.%d", (unsigned int)ip[0], (unsigned int)ip[1], (unsigned int)ip[2], (unsigned int)ip[3]);
		return std::string(str);
	}

	///\todo Not IPv6-capable.
	std::string ToString() const
	{
		char str[256];
		sprintf(str, "%d.%d.%d.%d:%d", (unsigned int)ip[0], (unsigned int)ip[1], (unsigned int)ip[2], (unsigned int)ip[3], (unsigned int)port);
		return std::string(str);
	}
};

} // ~kNet
