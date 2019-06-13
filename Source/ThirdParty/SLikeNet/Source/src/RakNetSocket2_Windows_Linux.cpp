/*
 *  Original work: Copyright (c) 2014, Oculus VR, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the BSD-style license found in the
 *  RakNet License.txt file in the licenses directory of this source tree. An additional grant 
 *  of patent rights can be found in the RakNet Patents.txt file in the same directory.
 *
 *
 *  Modified work: Copyright (c) 2016-2018, SLikeSoft UG (haftungsbeschränkt)
 *
 *  This source code was modified by SLikeSoft. Modifications are licensed under the MIT-style
 *  license found in the license.txt file in the root directory of this source tree.
 */

#include "slikenet/EmptyHeader.h"

#ifdef RAKNET_SOCKET_2_INLINE_FUNCTIONS

#ifndef RAKNETSOCKET2_WINDOWS_LINUX_CPP
#define RAKNETSOCKET2_WINDOWS_LINUX_CPP

#if !defined(_WIN32) && !defined(__ANDROID__)
#include <sys/types.h> // used for getifaddrs()
#include <ifaddrs.h>   // used for getifaddrs()
#endif // _WIN32

#include <string> // used for std::string

#if !defined(WINDOWS_STORE_RT) && !defined(__native_client__)

#ifdef _WIN32

// #med - consider replacing addressFamility parameter with includeIPv6 parameter for consistency with GetMyIP_Linux()
// based on https://stackoverflow.com/questions/122208/get-the-ip-address-of-local-computer#1317284
void GetMyIP_Windows(SystemAddress addresses[MAXIMUM_NUMBER_OF_INTERNAL_IDS], const ULONG addressFamily)
{
	ULONG outBufLen = 45 * 1024; // reserve 45 KB of memory which is the upper limit taken from the sample in MSDN (ie. 15 KB * 3 iterations)
	PIP_ADAPTER_ADDRESSES pAddresses = static_cast<IP_ADAPTER_ADDRESSES*>(rakMalloc_Ex(outBufLen, _FILE_AND_LINE_));
	if (pAddresses == nullptr) {
		// #med - error logging and/or throw exception?
		return;
	}

	DWORD error = GetAdaptersAddresses(addressFamily, GAA_FLAG_SKIP_ANYCAST | GAA_FLAG_SKIP_MULTICAST | GAA_FLAG_SKIP_FRIENDLY_NAME, nullptr, pAddresses, &outBufLen);
	if (error != ERROR_SUCCESS) {
		// #med - error logging and/or throw exception?
		rakFree_Ex(pAddresses, _FILE_AND_LINE_);
		return;
	}

	PIP_ADAPTER_ADDRESSES pCurAdapter = pAddresses;
	size_t outAddressIndex = 0;
	while ((pCurAdapter != nullptr) && (outAddressIndex < MAXIMUM_NUMBER_OF_INTERNAL_IDS)) {
		// skip loopback adapters
		if (pCurAdapter->IfType != IF_TYPE_SOFTWARE_LOOPBACK) {

			// parse the adapter's unicast addresses
			PIP_ADAPTER_UNICAST_ADDRESS curAddress = pCurAdapter->FirstUnicastAddress;
			while (curAddress != nullptr) {
				// note: we'd only requested IPV4 addresses, so this check should be redundant - double-check just to be on the safe side
				// #med - log a warning
				const ADDRESS_FAMILY curAddressFamily = curAddress->Address.lpSockaddr->sa_family;
				if (curAddressFamily == AF_INET) {
					const sockaddr_in*const curSocketAddress = reinterpret_cast<const sockaddr_in*>(curAddress->Address.lpSockaddr);

					// #med - review, is this really necessary?
					// skip source only addresses (aka: 0.0.0.0/8 - see RFC1700 p.4)
					if (curSocketAddress->sin_addr.S_un.S_un_b.s_b1 != 0) {
						// store the adapter's address
						addresses[outAddressIndex++].address.addr4 = *curSocketAddress;
					}
				}
#if RAKNET_SUPPORT_IPV6 == 1
				else if (curAddressFamily == AF_INET6) {
					// note: not const ptr since inet_ntop() requires non-const ptr
					sockaddr_in6*const curSocketAddress = reinterpret_cast<sockaddr_in6*>(curAddress->Address.lpSockaddr);

					char buffer[INET6_ADDRSTRLEN] = { 0 };
					// #med - add return value check
					inet_ntop(AF_INET6, &(curSocketAddress->sin6_addr), buffer, INET6_ADDRSTRLEN);

					const std::string ipv6String(buffer);

					// detect and skip non-external addresses
					bool isLocal = false;
					bool isSpecial = false;
					if (ipv6String.find("fe") == 0) {
						const char c = ipv6String[2];
						if (c == '8' || c == '9' || c == 'a' || c == 'b') {
							isLocal = true;
						}
					}
					else if (ipv6String.find("2001:0:") == 0) {
						isSpecial = true;
					}

					if (!(isLocal || isSpecial)) {
						// store the adapter's address
						addresses[outAddressIndex++].address.addr6 = *curSocketAddress;
					}
				}
#endif // RAKNET_SUPPORT_IPV6 == 1
				// else skip the address (neither IPv4 nor IPv6 address)

				// continue with next address
				curAddress = curAddress->Next;
			}
		}

		// continue with next adapter's addresses
		pCurAdapter = pCurAdapter->Next;
	}
	rakFree_Ex(pAddresses, _FILE_AND_LINE_);

	while (outAddressIndex < MAXIMUM_NUMBER_OF_INTERNAL_IDS) {
		addresses[outAddressIndex++] = UNASSIGNED_SYSTEM_ADDRESS;
	}
}

#else // _WIN32

// based on https://stackoverflow.com/questions/212528/get-the-ip-address-of-the-machine#265978
void GetMyIP_Linux(SystemAddress addresses[MAXIMUM_NUMBER_OF_INTERNAL_IDS], const bool includeIPv6)
{
	struct ifaddrs *pAddresses = nullptr;

	// #med - add error check to getifaddrs()-call
	getifaddrs(&pAddresses);

	struct ifaddrs *pCurAdapter = pAddresses;
	size_t outAddressIndex = 0;
	while ((pCurAdapter != nullptr) && (outAddressIndex < MAXIMUM_NUMBER_OF_INTERNAL_IDS)) {
		// skip interfaces which don't have any address assigned (according to the manual, this would only apply for BSD, but still we'd check for null here just in case)
		if (pCurAdapter->ifa_addr != nullptr) {
			// skip loopback adapters
			if ((pCurAdapter->ifa_flags & IFF_LOOPBACK) == 0) {
				if (pCurAdapter->ifa_addr->sa_family == AF_INET) {
					const sockaddr_in*const curSocketAddress = reinterpret_cast<const sockaddr_in*>(pCurAdapter->ifa_addr);

					char buffer[INET_ADDRSTRLEN] = { 0 };
					// #med - add return value check
					inet_ntop(AF_INET, &(curSocketAddress->sin_addr), buffer, INET_ADDRSTRLEN);

					const std::string ipv4String(buffer);

					// #med - review, is this really necessary?
					// skip source only addresses (aka: 0.0.0.0/8 - see RFC1700 p.4)
					if (ipv4String.find("0.") != 0) {
						// store the adapter's address
						addresses[outAddressIndex++].address.addr4 = *curSocketAddress;
					}
				}
#if RAKNET_SUPPORT_IPV6 == 1
				else if (includeIPv6 && pCurAdapter->ifa_addr->sa_family == AF_INET6) {
					const sockaddr_in6*const curSocketAddress = reinterpret_cast<const sockaddr_in6*>(pCurAdapter->ifa_addr);

					char buffer[INET6_ADDRSTRLEN] = { 0 };
					// #med - add return value check
					inet_ntop(AF_INET6, &(curSocketAddress->sin6_addr), buffer, INET6_ADDRSTRLEN);

					const std::string ipv6String(buffer);

					// detect and skip non-external addresses
					bool isLocal = false;
					bool isSpecial = false;
					if (ipv6String.find("fe") == 0) {
						const char c = ipv6String[2];
						if (c == '8' || c == '9' || c == 'a' || c == 'b') {
							isLocal = true;
						}
					}
					else if (ipv6String.find("2001:0:") == 0) {
						isSpecial = true;
					}

					if (!(isLocal || isSpecial)) {
						// store the adapter's address
						addresses[outAddressIndex++].address.addr6 = *curSocketAddress;
					}
				}
#endif // RAKNET_SUPPORT_IPV6 == 1
				// else skip the address (neither IPv4 nor IPv6 address)
			}
		}

		pCurAdapter = pCurAdapter->ifa_next;
	}

	if (pAddresses != nullptr)
		freeifaddrs(pAddresses);

	while (outAddressIndex < MAXIMUM_NUMBER_OF_INTERNAL_IDS) {
		addresses[outAddressIndex++] = UNASSIGNED_SYSTEM_ADDRESS;
	}
}

#endif // _WIN32

void GetMyIP_Windows_Linux(SystemAddress addresses[MAXIMUM_NUMBER_OF_INTERNAL_IDS])
{
#if RAKNET_SUPPORT_IPV6 == 1

#ifdef _WIN32
	GetMyIP_Windows(addresses, AF_UNSPEC);
#else // _WIN32
	GetMyIP_Linux(addresses, true);
#endif // _WIN32

#else // RAKNET_SUPPORT_IPV6 == 1

#ifdef _WIN32
	GetMyIP_Windows(addresses, AF_INET);
#else // _WIN32
	GetMyIP_Linux(addresses, false);
#endif // _WIN32

#endif // RAKNET_SUPPORT_IPV6 == 1
}

#endif // !defined(WINDOWS_STORE_RT) && !defined(__native_client__)

#endif // RAKNETSOCKET2_WINDOWS_LINUX_CPP

#endif // RAKNET_SOCKET_2_INLINE_FUNCTIONS
