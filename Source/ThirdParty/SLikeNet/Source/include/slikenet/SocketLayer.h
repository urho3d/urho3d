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

/// \file
/// \brief SocketLayer class implementation
///




#ifndef __SOCKET_LAYER_H
#define __SOCKET_LAYER_H

#include "memoryoverride.h"
#include "types.h"
#include "smartptr.h"
//#include "socket.h"
#include "Export.h"
#include "MTUSize.h"
#include "string.h"

//#include "ClientContextStruct.h"

namespace SLNet
{
/// Forward declarations
class RakPeer;

/*
class RAK_DLL_EXPORT SocketLayerOverride
{
public:
	SocketLayerOverride() {}
	virtual ~SocketLayerOverride() {}

	/// Called when SendTo would otherwise occur.
	virtual int RakNetSendTo( const char *data, int length, const SystemAddress &systemAddress )=0;

	/// Called when RecvFrom would otherwise occur. Return number of bytes read. Write data into dataOut
	// Return -1 to use RakNet's normal recvfrom, 0 to abort RakNet's normal recvfrom, and positive to return data
	virtual int RakNetRecvFrom( char dataOut[ MAXIMUM_MTU_SIZE ], SystemAddress *senderOut, bool calledFromMainThread )=0;
};
*/

// A platform independent implementation of Berkeley sockets, with settings used by RakNet
class RAK_DLL_EXPORT SocketLayer
{

public:
	
	/// Default Constructor
	SocketLayer();
	
	// Destructor	
	~SocketLayer();
	
	/*
	/// Creates a bound socket to listen for incoming connections on the specified port
	/// \param[in] port the port number 
	/// \param[in] blockingSocket 
	/// \return A new socket used for accepting clients 
	static RakNetSocket* CreateBoundSocket( RakPeer *peer, unsigned short port, bool blockingSocket, const char *forceHostAddress, unsigned int sleepOn10048, unsigned int extraSocketOptions, unsigned short socketFamily, _PP_Instance_ chromeInstance );
#if defined(WINDOWS_STORE_RT)
	static RakNetSocket* CreateWindowsStore8Socket( RakPeer *peer, unsigned short port, bool blockingSocket, const char *forceHostAddress, unsigned int sleepOn10048, unsigned int extraSocketOptions, _PP_Instance_ chromeInstance );
#endif
	static RakNetSocket* CreateBoundSocket_IPV4( RakPeer *peer, unsigned short port, bool blockingSocket, const char *forceHostAddress, unsigned int sleepOn10048, unsigned int extraSocketOptions, _PP_Instance_ chromeInstance );
	#if RAKNET_SUPPORT_IPV6==1
		static RakNetSocket* CreateBoundSocket_SupportIPV4And6( RakPeer *peer, unsigned short port, bool blockingSocket, const char *forceHostAddress, unsigned int sleepOn10048, unsigned int extraSocketOptions, unsigned short socketFamily, _PP_Instance_ chromeInstance );
	#endif
	static RakNetSocket* CreateBoundSocket_PS3Lobby( unsigned short port, bool blockingSocket, const char *forceHostAddress, unsigned short socketFamily );
	static RakNetSocket* CreateBoundSocket_PSP2( unsigned short port, bool blockingSocket, const char *forceHostAddress, unsigned short socketFamily );
	*/

	/*
#ifndef WINDOWS_STORE_RT
	/// Returns if this specified port is in use, for UDP
	/// \param[in] port the port number 
	/// \return If this port is already in use
	//static bool IsPortInUse_Old(unsigned short port, const char *hostAddress);
	//static bool IsPortInUse(unsigned short port, const char *hostAddress, unsigned short socketFamily );
	static bool IsSocketFamilySupported(const char *hostAddress, unsigned short socketFamily);
#endif
	*/

//	static const char* DomainNameToIP_Old( const char *domainName );
//	static const char* DomainNameToIP( const char *domainName );
	
	/// Write \a data of length \a length to \a writeSocket
	/// \param[in] writeSocket The socket to write to
	/// \param[in] data The data to write
	/// \param[in] length The length of \a data	
	// static void Write( RakNetSocket*writeSocket, const char* data, const int length );
	
	/// Read data from a socket 
	/// \param[in] s the socket 
	/// \param[in] rakPeer The instance of rakPeer containing the recvFrom C callback
	/// \param[in] errorCode An error code if an error occured .
	/// \param[in] connectionSocketIndex Which of the sockets in RakPeer we are using
	/// \return Returns true if you successfully read data, false on error.
//	static void RecvFromBlocking_IPV4( RakNetSocket *s, RakPeer *rakPeer, char *dataOut, int *bytesReadOut, SystemAddress *systemAddressOut, SLNet::TimeUS *timeRead );
// 	#if RAKNET_SUPPORT_IPV6==1
// 		static void RecvFromBlockingIPV4And6( RakNetSocket *s, RakPeer *rakPeer, char *dataOut, int *bytesReadOut, SystemAddress *systemAddressOut, SLNet::TimeUS *timeRead );
// 	#endif
//	static void RecvFromBlocking( RakNetSocket *s, RakPeer *rakPeer, char *dataOut, int *bytesReadOut, SystemAddress *systemAddressOut, SLNet::TimeUS *timeRead );
#if defined(WINDOWS_STORE_RT)
//	static void RecvFromBlocking_WindowsStore8( RakNetSocket *s, RakPeer *rakPeer, char *dataOut, int *bytesReadOut, SystemAddress *systemAddressOut, SLNet::TimeUS *timeRead );
#endif

	/// Given a socket and IP, retrieves the subnet mask, on linux the socket is unused
	/// \param[in] inSock the socket 
	/// \param[in] inIpString The ip of the interface you wish to retrieve the subnet mask from
	/// \return Returns the ip dotted subnet mask if successful, otherwise returns empty string ("")
	static SLNet::RakString GetSubNetForSocketAndIp(__UDPSOCKET__ inSock, SLNet::RakString inIpString);


	/// Sets the socket flags to nonblocking 
	/// \param[in] listenSocket the socket to set
//	static void SetNonBlocking( RakNetSocket* listenSocket);


	/// Retrieve all local IP address in a string format.
	/// \param[in] s The socket whose port we are referring to
	/// \param[in] ipList An array of ip address in dotted notation.
	static void GetMyIP( SystemAddress addresses[MAXIMUM_NUMBER_OF_INTERNAL_IDS] );

	
	/// Call sendto (UDP obviously)
	/// \param[in] s the socket
	/// \param[in] data The byte buffer to send 
	/// \param[in] length The length of the \a data in bytes
	/// \param[in] ip The address of the remote host in dotted notation.
	/// \param[in] port The port number to send to.
	/// \return 0 on success, nonzero on failure.
//	static int SendTo( UDPSOCKET s, const char *data, int length, const char ip[ 16 ], unsigned short port, unsigned short remotePortRakNetWasStartedOn_PS3, unsigned int extraSocketOptions, const char *file, const long line );

	/// Call sendto' (UDP obviously)
	/// It won't reach the recipient, except on a LAN
	/// However, this is good for opening routers / firewalls
	/// \param[in] s the socket
	/// \param[in] data The byte buffer to send 
	/// \param[in] length The length of the \a data in bytes
	/// \param[in] ip The address of the remote host in dotted notation.
	/// \param[in] port The port number to send to.
	/// \param[in] ttl Max hops of datagram
	/// \return 0 on success, nonzero on failure.
//	static int SendToTTL( RakNetSocket *s, const char *data, int length, SystemAddress &systemAddress, int ttl );

	/// Call sendto (UDP obviously)
	/// \param[in] s the socket
	/// \param[in] data The byte buffer to send 
	/// \param[in] length The length of the \a data in bytes
	/// \param[in] binaryAddress The address of the remote host in binary format.
	/// \param[in] port The port number to send to.
	/// \return 0 on success, nonzero on failure.
//	static int SendTo( RakNetSocket *s, const char *data, int length, SystemAddress systemAddress, const char *file, const long line );

//	static unsigned short GetLocalPort(RakNetSocket *s);
	static unsigned short GetLocalPort( __UDPSOCKET__ s);
//	static void GetSystemAddress_Old ( RakNetSocket *s, SystemAddress *systemAddressOut );
	static void GetSystemAddress_Old ( __UDPSOCKET__ s, SystemAddress *systemAddressOut );
//	static void GetSystemAddress ( RakNetSocket *s, SystemAddress *systemAddressOut );
	static void GetSystemAddress ( __UDPSOCKET__ s, SystemAddress *systemAddressOut );

//	static void SetSocketLayerOverride(SocketLayerOverride *_slo);
//	static SocketLayerOverride* GetSocketLayerOverride(void) {return slo;}

// 	static int SendTo_PS3Lobby( RakNetSocket *s, const char *data, int length, const SystemAddress &systemAddress );
// 	static int SendTo_PSP2( RakNetSocket *s, const char *data, int length, const SystemAddress &systemAddress );
// 	static int SendTo_360( RakNetSocket *s, const char *data, int length, const char *voiceData, int voiceLength, const SystemAddress &systemAddress );
// 	static int SendTo_PC( RakNetSocket *s, const char *data, int length, const SystemAddress &systemAddress, const char *file, const long line );
// #if defined(WINDOWS_STORE_RT)
// 	static int SendTo_WindowsStore8( RakNetSocket *s, const char *data, int length, const SystemAddress &systemAddress, const char *file, const long line );
// #endif
// 
// 	static void SetDoNotFragment( RakNetSocket* listenSocket, int opt );
// 	static void SetSocketOptions( RakNetSocket* listenSocket, bool blockingSocket, bool setBroadcast);
	static void SetSocketOptions( __UDPSOCKET__ listenSocket, bool blockingSocket, bool setBroadcast);
	

	// AF_INET (default). For IPV6, use AF_INET6. To autoselect, use AF_UNSPEC.
	static bool GetFirstBindableIP(char firstBindable[128], int ipProto);

private:

//	static SocketLayerOverride *slo;
};

} // namespace SLNet

#endif
