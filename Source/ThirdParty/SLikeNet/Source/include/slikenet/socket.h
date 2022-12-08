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
#ifndef __RAKNET_SOCKET_H
#define __RAKNET_SOCKET_H

#include "types.h"
#include "defines.h"
#include "Export.h"
#include "SocketIncludes.h"
#include "assert.h"
#include "SocketDefines.h"
#include "MTUSize.h"

namespace SLNet
{

struct RAK_DLL_EXPORT RakNetSocket
{
public:
	RakNetSocket();
	~RakNetSocket();

// 	void Accept(
// 		struct sockaddr *addr,
// 		int *addrlen);

	inline int Connect(
		const struct sockaddr *name,
		int namelen) {return connect__(s,name,namelen);}

	static RakNetSocket* Create
#ifdef __native_client__
		(_PP_Instance_ _chromeInstance);
#else
		(int af,
		int type,
		int protocol);
#endif

	int Bind(		
		const struct sockaddr *addr,
		int namelen);

	inline int GetSockName(		
		struct sockaddr *name,
			socklen_t * namelen) {return getsockname__(s,name,namelen);}

	inline int GetSockOpt (
		int level,
		int optname,
		char * optval,
		socklen_t *optlen) {return getsockopt__(s,level,optname,optval,optlen);}


	int IOCTLSocket(		
		long cmd,
		unsigned long *argp);

	int Listen (		
		int backlog);

	inline int Recv(		
		char * buf,
		int len,
		int flags) {return recv__(s,buf,len,flags);}

	inline int RecvFrom(		
		char * buf,
		int len,
		int flags,
		struct sockaddr * from,
			socklen_t * fromlen) {return recvfrom__(s,buf,len,flags,from,fromlen);}

// 	inline int Select(
// 		int nfds,
// 		fd_set *readfds,
// 		fd_set *writefds,
// 		fd_set *exceptfds,
// 		struct timeval *timeout) {return select__(nfds,readfds,writefds,exceptfds,timeout);}

	inline int Send(		
		const char * buf,
		int len,
		int flags) {return send__(s,buf,len,flags);}

	inline int SendTo(		
		const char * buf,
		int len,
		int flags,
		const struct sockaddr *to,
		int tolen) {return sendto__(s,buf,len,flags,to,tolen);}

	#ifdef _WIN32
	#elif defined(_PS3) || defined(__PS3__) || defined(SN_TARGET_PS3) || defined(_PS4) || defined(SN_TARGET_PSP2)
	#else
	inline int Fcntl(int cmd, int arg) {return fcntl(s,cmd,arg);}
	#endif


#if defined(_WIN32) && !defined(WINDOWS_STORE_RT)
	inline int _WSASendTo(
    LPWSABUF lpBuffers,
    DWORD dwBufferCount,
    LPDWORD lpNumberOfBytesSent,
    DWORD dwFlags,
    const struct sockaddr FAR * lpTo,
    int iTolen,
    LPWSAOVERLAPPED lpOverlapped,
    LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine
    )
	{ return WSASendTo(s,lpBuffers,dwBufferCount,lpNumberOfBytesSent,dwFlags,lpTo,iTolen,lpOverlapped,lpCompletionRoutine);}

#endif
	
	int SetSockOpt(		
		int level,
		int optname,
		const char * optval,
		int optlen);

	int Shutdown(		
		int how);


	inline void SetRemotePortRakNetWasStartedOn(unsigned short i) {remotePortRakNetWasStartedOn_PS3_PSP2=i;}
	inline void SetUserConnectionSocketIndex(unsigned int i) {userConnectionSocketIndex=i;}
	inline void SetBoundAddress(SystemAddress i) {boundAddress=i;}
	inline void SetSocketFamily(unsigned short i) {socketFamily=i;}
	inline void SetBlockingSocket(bool i) {blockingSocket=i;}
	inline void SetExtraSocketOptions(unsigned int i) {extraSocketOptions=i;}
	inline void SetChromeInstance(_PP_Instance_ i) {chromeInstance=i;}
	inline void SetBoundAddressToLoopback(unsigned char ipVersion) {boundAddress.SetToLoopback(ipVersion);}

	inline SystemAddress GetBoundAddress(void) const {return boundAddress;}
	inline unsigned short GetRemotePortRakNetWasStartedOn(void) const {return remotePortRakNetWasStartedOn_PS3_PSP2;}
	inline bool GetBlockingSocket(void) {return blockingSocket;}
	inline unsigned int GetExtraSocketOptions(void) const {return extraSocketOptions;}
	inline unsigned short GetSocketFamily(void) const {return socketFamily;}
	inline _PP_Instance_ GetChromeInstance(void) const {return chromeInstance;}
	inline unsigned int GetUserConnectionSocketIndex(void) const {
		RakAssert(userConnectionSocketIndex!=(unsigned int)-1);
		return userConnectionSocketIndex;}


#ifdef __native_client__
		// Flag indicating if a SendTo is currently in progress
		bool sendInProgress;

		// Data for next queued packet to send, if nextSendSize > 0
		char nextSendBuffer[MAXIMUM_MTU_SIZE];

		// Size of next queued packet to send, or 0 if no queued packet
		int nextSendSize;

		// Destination address of queued packet
		PP_NetAddress_Private nextSendAddr;
#endif

		__UDPSOCKET__ s;

protected:

#if defined (_WIN32) && defined(USE_WAIT_FOR_MULTIPLE_EVENTS)
	void* recvEvent;
#endif

	#if defined(_PS3) || defined(__PS3__) || defined(SN_TARGET_PS3) || defined(_PS4) || defined(SN_TARGET_PSP2)
	/// PS3: Set for the PS3, when using signaling.
	/// PS3: Connect with the port returned by signaling. Set this to whatever port RakNet was actually started on
	/// PSP2: Set non-zero to use SCE_NET_SOCK_DGRAM_P2P. This should be done for ad-hoc or with 
	#endif

	unsigned short remotePortRakNetWasStartedOn_PS3_PSP2;
	unsigned int userConnectionSocketIndex;
	SystemAddress boundAddress;
	unsigned short socketFamily;
	bool blockingSocket;
	unsigned int extraSocketOptions;
	_PP_Instance_ chromeInstance;
};

} // namespace SLNet

#endif
*/
