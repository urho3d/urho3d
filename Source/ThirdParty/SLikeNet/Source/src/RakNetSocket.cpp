/*
 *  Original work: Copyright (c) 2014, Oculus VR, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the BSD-style license found in the
 *  RakNet License.txt file in the licenses directory of this source tree. An additional grant 
 *  of patent rights can be found in the RakNet Patents.txt file in the same directory.
 *
 *
 *  Modified work: Copyright (c) 2017, SLikeSoft UG (haftungsbeschränkt)
 *
 *  This source code was modified by SLikeSoft. Modifications are licensed under the MIT-style
 *  license found in the license.txt file in the root directory of this source tree.
 */

/*
#include "slikenet/socket.h"
#include "slikenet/memoryoverride.h"

using namespace SLNet;

#if defined(__native_client__)
using namespace pp;
#endif

RakNetSocket::RakNetSocket() {
	#if !defined(WINDOWS_STORE_RT)
		s = 0;
	#endif
	remotePortRakNetWasStartedOn_PS3_PSP2 = 0;
	userConnectionSocketIndex = (unsigned int) -1;
	socketFamily = 0;
	blockingSocket = 0;
	extraSocketOptions = 0;
	chromeInstance = 0;

#if defined (_WIN32) && defined(USE_WAIT_FOR_MULTIPLE_EVENTS)
	recvEvent=INVALID_HANDLE_VALUE;
#endif

	#ifdef __native_client__
		s = 0;
		sendInProgress = false;
		nextSendSize = 0;
	#endif
}
RakNetSocket::~RakNetSocket() 
{
	#ifdef __native_client__
		if(s != 0)
			((PPB_UDPSocket_Private_0_4*) pp::Module::Get()->GetBrowserInterface(PPB_UDPSOCKET_PRIVATE_INTERFACE_0_4))->Close(s);
#elif defined(WINDOWS_STORE_RT)
		WinRTClose(s);
	#else
		if ((__UDPSOCKET__)s != 0)
			closesocket__(s);
	#endif
	

#if defined (_WIN32) && defined(USE_WAIT_FOR_MULTIPLE_EVENTS)
	if (recvEvent!=INVALID_HANDLE_VALUE)
	{
		CloseHandle( recvEvent );
		recvEvent = INVALID_HANDLE_VALUE;
	}
#endif
}
// 
// void RakNetSocket::Accept(
// struct sockaddr *addr,
// 	int *addrlen)
// {
// 	accept__(s, addr, addrlen);
// }

// 
// void RakNetSocket::Close( void )
// {
// 	closesocket__(s);
// }

RakNetSocket* RakNetSocket::Create
#ifdef __native_client__
	(_PP_Instance_ _chromeInstance)
#else
	(int af,
	int type,
	int protocol)
#endif
{
	__UDPSOCKET__ sock;

	#ifndef __native_client__
		RakAssert(type==SOCK_DGRAM);
	#endif

	#ifdef __native_client__
		sock = ((PPB_UDPSocket_Private_0_4*) Module::Get()->GetBrowserInterface(PPB_UDPSOCKET_PRIVATE_INTERFACE_0_4))->Create(_chromeInstance);
	#elif defined(SN_TARGET_PSP2)
		sock = sceNetSocket( "RakNetSocket::Create", SCE_NET_AF_INET, SCE_NET_SOCK_DGRAM_P2P, 0 );
	#elif defined(WINDOWS_STORE_RT)
		sock = WinRTCreateDatagramSocket(af,type,protocol);
	#elif defined(_PS3) || defined(__PS3__) || defined(SN_TARGET_PS3) || defined(_PS4)
		sock = socket__( AF_INET, SOCK_DGRAM_P2P, 0 );
	#else
		sock = socket__(af, type, protocol);
	#endif

	#if !defined(WINDOWS_STORE_RT)
	if (sock<0)
		return 0;
	#endif
	RakNetSocket *rns = SLNet::OP_NEW<RakNetSocket>(_FILE_AND_LINE_);
	rns->s = sock;
	#ifdef __native_client__
		rns->chromeInstance = _chromeInstance;
	#endif
	return rns;
}

int RakNetSocket::Bind(		
		  const struct sockaddr *addr,
		  int namelen)
{
	return bind__(s,addr,namelen);
}

int RakNetSocket::IOCTLSocket(		
				 long cmd,
				 unsigned long *argp)
{
	#if defined(_WIN32)
		return ioctlsocket__(s,cmd,argp);
	#else
		return 0;
	#endif
}

int RakNetSocket::Listen (		
			 int backlog)
{
	return listen__(s,backlog);
}

int RakNetSocket::SetSockOpt(		
				int level,
				int optname,
				const char * optval,
				int optlen)
{
	return setsockopt__(s,level,optname,optval,optlen);
}

int RakNetSocket::Shutdown(		
			  int how)
{
	#ifndef SN_TARGET_PSP2
		return shutdown__(s,how);
	#else
		return 0;
	#endif
}
*/
