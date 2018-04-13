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

#include "slikenet/NativeFeatureIncludes.h"
#if _RAKNET_SUPPORT_TCPInterface==1

/// \file
/// \brief A simple TCP based server allowing sends and receives.  Can be connected to by a telnet client.
///



#include "slikenet/TCPInterface.h"
#ifdef _WIN32
	#if !defined (WINDOWS_STORE_RT)
		typedef int socklen_t;
	#endif


#else
#include <sys/time.h>
#include <unistd.h>
#include <pthread.h>
#endif
#include <string.h>
#include "slikenet/assert.h"
#include <stdio.h>
#include "slikenet/assert.h"
#include "slikenet/sleep.h"
#include "slikenet/StringCompressor.h"
#include "slikenet/StringTable.h"
#include "slikenet/Itoa.h"
#include "slikenet/SocketLayer.h"
#include "slikenet/SocketDefines.h"
#if (defined(__GNUC__)  || defined(__GCCXML__)) && !defined(__WIN32__)
#include <netdb.h>
#endif

#ifdef _DO_PRINTF
#endif

#ifdef _WIN32
#include "slikenet/WSAStartupSingleton.h"
#endif
namespace SLNet
{
RAK_THREAD_DECLARATION(UpdateTCPInterfaceLoop);
RAK_THREAD_DECLARATION(ConnectionAttemptLoop);
}
#ifdef _MSC_VER
#pragma warning( push )
#endif
#include "slikenet/linux_adapter.h"
#include "slikenet/osx_adapter.h"

using namespace SLNet;

STATIC_FACTORY_DEFINITIONS(TCPInterface,TCPInterface);

TCPInterface::TCPInterface()
{
#if !defined(WINDOWS_STORE_RT)
	listenSocket=0;
#endif
	remoteClients=0;
	remoteClientsLength=0;

	StringCompressor::AddReference();
	SLNet::StringTable::AddReference();

#if OPEN_SSL_CLIENT_SUPPORT==1
	ctx=0;
	meth=0;
#endif

#ifdef _WIN32
	WSAStartupSingleton::AddRef();
#endif
}
TCPInterface::~TCPInterface()
{
	Stop();
#ifdef _WIN32
	WSAStartupSingleton::Deref();
#endif

	SLNet::OP_DELETE_ARRAY(remoteClients,_FILE_AND_LINE_);

	StringCompressor::RemoveReference();
	SLNet::StringTable::RemoveReference();
}
#if !defined(WINDOWS_STORE_RT)
bool TCPInterface::CreateListenSocket(unsigned short port, unsigned short maxIncomingConnections, unsigned short socketFamily, const char *bindAddress)
{
	(void) maxIncomingConnections;
	(void) socketFamily;
#if RAKNET_SUPPORT_IPV6!=1
	listenSocket = socket__(AF_INET, SOCK_STREAM, 0);
	if ((int)listenSocket ==-1)
		return false;

	struct sockaddr_in serverAddress;
	memset(&serverAddress,0,sizeof(sockaddr_in));
	serverAddress.sin_family = AF_INET;
	if ( bindAddress && bindAddress[0] )
	{





		inet_pton(AF_INET, bindAddress, &serverAddress.sin_addr.s_addr);

	}
	else
		serverAddress.sin_addr.s_addr = INADDR_ANY;

	serverAddress.sin_port = htons(port);

	SocketLayer::SetSocketOptions(listenSocket, false, false);

	if (bind__(listenSocket,(struct sockaddr *) &serverAddress,sizeof(serverAddress)) < 0)
		return false;

	listen__(listenSocket, maxIncomingConnections);
#else
	(void)bindAddress;
	struct addrinfo hints;
	memset(&hints, 0, sizeof (addrinfo)); // make sure the struct is empty
	hints.ai_family = socketFamily;     // don't care IPv4 or IPv6
	hints.ai_socktype = SOCK_STREAM; // TCP sockets
	hints.ai_flags = AI_PASSIVE;     // fill in my IP for me
	struct addrinfo *servinfo=0, *aip;  // will point to the results
	char portStr[32];
	Itoa(port,portStr,10);

	getaddrinfo(0, portStr, &hints, &servinfo);
	for (aip = servinfo; aip != NULL; aip = aip->ai_next)
	{
		// Open socket. The address type depends on what
		// getaddrinfo() gave us.
		listenSocket = socket__(aip->ai_family, aip->ai_socktype, aip->ai_protocol);
		if (listenSocket != 0)
		{
			int ret = bind__( listenSocket, aip->ai_addr, (int) aip->ai_addrlen );
			if (ret>=0)
			{
				break;
			}
			else
			{
				closesocket__(listenSocket);
				listenSocket=0;
			}
		}
	}

	if (listenSocket==0)
		return false;

	SocketLayer::SetSocketOptions(listenSocket, false, false);

	listen__(listenSocket, maxIncomingConnections);
#endif // #if RAKNET_SUPPORT_IPV6!=1

	return true;
}
#endif

#if defined(WINDOWS_STORE_RT)
bool TCPInterface::CreateListenSocket_WinStore8(unsigned short port, unsigned short maxIncomingConnections, unsigned short socketFamily, const char *bindAddress)
{
	listenSocket = WinRTCreateStreamSocket(AF_INET, SOCK_STREAM, 0);
	return true;
}
#endif
bool TCPInterface::Start(unsigned short port, unsigned short maxIncomingConnections, unsigned short maxConnections, int _threadPriority, unsigned short socketFamily, const char *bindAddress)
{
#ifdef __native_client__
	return false;
#else
	(void) socketFamily;

	if (isStarted.GetValue()>0)
		return false;

	threadPriority=_threadPriority;

	if (threadPriority==-99999)
	{


#if   defined(_WIN32)
		threadPriority=0;


#else
		threadPriority=1000;
#endif
	}

	isStarted.Increment();
	if (maxConnections==0)
		maxConnections=maxIncomingConnections;
	if (maxConnections==0)
		maxConnections=1;
	remoteClientsLength=maxConnections;
	remoteClients= SLNet::OP_NEW_ARRAY<RemoteClient>(maxConnections,_FILE_AND_LINE_);


	listenSocket=0;
	if (maxIncomingConnections>0)
	{
#if defined(WINDOWS_STORE_RT)
		CreateListenSocket_WinStore8(port, maxIncomingConnections, socketFamily, bindAddress);
#else
		CreateListenSocket(port, maxIncomingConnections, socketFamily, bindAddress);
#endif
	}


	// Start the update thread
	int errorCode;





	errorCode = SLNet::RakThread::Create(UpdateTCPInterfaceLoop, this, threadPriority);


	if (errorCode!=0)
		return false;

	while (threadRunning.GetValue()==0)
		RakSleep(0);
	
	unsigned int i;
	for (i=0; i < messageHandlerList.Size(); i++)
		messageHandlerList[i]->OnRakPeerStartup();

	return true;
#endif  // __native_client__
}
void TCPInterface::Stop(void)
{
	unsigned int i;
	for (i=0; i < messageHandlerList.Size(); i++)
		messageHandlerList[i]->OnRakPeerShutdown();

#ifndef __native_client__
	if (isStarted.GetValue()==0)
		return;

#if OPEN_SSL_CLIENT_SUPPORT==1
	for (i=0; i < remoteClientsLength; i++)
		remoteClients[i].DisconnectSSL();
#endif

	isStarted.Decrement();

#if !defined(WINDOWS_STORE_RT)
	if (listenSocket!=0)
#endif
	{
#ifdef _WIN32
		shutdown__(listenSocket, SD_BOTH);

#else		
		shutdown__(listenSocket, SHUT_RDWR);
#endif
		closesocket__(listenSocket);
	}

	// Abort waiting connect calls
	blockingSocketListMutex.Lock();
	for (i=0; i < blockingSocketList.Size(); i++)
	{
		closesocket__(blockingSocketList[i]);
	}
	blockingSocketListMutex.Unlock();

	// Wait for the thread to stop
	while ( threadRunning.GetValue()>0 )
		RakSleep(15);

	RakSleep(100);

	#if !defined(WINDOWS_STORE_RT)
		listenSocket=0;
	#endif

	// Stuff from here on to the end of the function is not threadsafe
	for (i=0; i < remoteClientsLength; i++)
	{
		closesocket__(remoteClients[i].socket);
#if OPEN_SSL_CLIENT_SUPPORT==1
		remoteClients[i].FreeSSL();
#endif
	}
	remoteClientsLength=0;
	SLNet::OP_DELETE_ARRAY(remoteClients,_FILE_AND_LINE_);
	remoteClients=0;

	// #low review whether we'd rather use PopInaccurate() here (i.e. check whether related threads accessing the queue terminated already)
	// consider even adding a dtor to Packet which would then clear its data (at this point drop this explicit packet deallocation here)
	SLNet::Packet* packet = incomingMessages.Pop();
	while (packet != nullptr) {
		DeallocatePacket(packet);
		packet = incomingMessages.Pop();
	}
	incomingMessages.Clear(_FILE_AND_LINE_);
	newIncomingConnections.Clear(_FILE_AND_LINE_);
	newRemoteClients.Clear(_FILE_AND_LINE_);
	lostConnections.Clear(_FILE_AND_LINE_);
	requestedCloseConnections.Clear(_FILE_AND_LINE_);
	failedConnectionAttempts.Clear(_FILE_AND_LINE_);
	completedConnectionAttempts.Clear(_FILE_AND_LINE_);
	failedConnectionAttempts.Clear(_FILE_AND_LINE_);
	for (i=0; i < headPush.Size(); i++)
		DeallocatePacket(headPush[i]);
	headPush.Clear(_FILE_AND_LINE_);
	for (i=0; i < tailPush.Size(); i++)
		DeallocatePacket(tailPush[i]);
	tailPush.Clear(_FILE_AND_LINE_);

#if OPEN_SSL_CLIENT_SUPPORT==1
	SSL_CTX_free (ctx);
	startSSL.Clear(_FILE_AND_LINE_);
	activeSSLConnections.Clear(false, _FILE_AND_LINE_);
#endif





#endif  // __native_client__
}
SystemAddress TCPInterface::Connect(const char* host, unsigned short remotePort, bool block, unsigned short socketFamily, const char *bindAddress)
{
	if (threadRunning.GetValue()==0)
		return UNASSIGNED_SYSTEM_ADDRESS;

	int newRemoteClientIndex=-1;
	for (newRemoteClientIndex=0; newRemoteClientIndex < remoteClientsLength; newRemoteClientIndex++)
	{
		remoteClients[newRemoteClientIndex].isActiveMutex.Lock();
		if (remoteClients[newRemoteClientIndex].isActive==false)
		{
			remoteClients[newRemoteClientIndex].SetActive(true);
			remoteClients[newRemoteClientIndex].isActiveMutex.Unlock();
			break;
		}
		remoteClients[newRemoteClientIndex].isActiveMutex.Unlock();
	}
	if (newRemoteClientIndex==-1)
		return UNASSIGNED_SYSTEM_ADDRESS;

	if (block)
	{
		SystemAddress systemAddress;
		systemAddress.FromString(host);
		systemAddress.SetPortHostOrder(remotePort);
		systemAddress.systemIndex=(SystemIndex) newRemoteClientIndex;
		char buffout[128];
		systemAddress.ToString(false,buffout, static_cast<size_t>(128));

		__TCPSOCKET__ sockfd = SocketConnect(buffout, remotePort, socketFamily, bindAddress);
		// Windows RT TODO
#if !defined(WINDOWS_STORE_RT)
		if (sockfd==0)
#endif
		{
			remoteClients[newRemoteClientIndex].isActiveMutex.Lock();
			remoteClients[newRemoteClientIndex].SetActive(false);
			remoteClients[newRemoteClientIndex].isActiveMutex.Unlock();

			failedConnectionAttemptMutex.Lock();
			failedConnectionAttempts.Push(systemAddress, _FILE_AND_LINE_ );
			failedConnectionAttemptMutex.Unlock();

			return UNASSIGNED_SYSTEM_ADDRESS;
		}

		remoteClients[newRemoteClientIndex].socket=sockfd;
		remoteClients[newRemoteClientIndex].systemAddress=systemAddress;

		completedConnectionAttemptMutex.Lock();
		completedConnectionAttempts.Push(remoteClients[newRemoteClientIndex].systemAddress, _FILE_AND_LINE_ );
		completedConnectionAttemptMutex.Unlock();

		return remoteClients[newRemoteClientIndex].systemAddress;
	}
	else
	{
		ThisPtrPlusSysAddr *s = SLNet::OP_NEW<ThisPtrPlusSysAddr>( _FILE_AND_LINE_ );
		s->systemAddress.FromStringExplicitPort(host,remotePort);
		s->systemAddress.systemIndex=(SystemIndex) newRemoteClientIndex;
		if (bindAddress)
			strcpy_s(s->bindAddress, bindAddress);
		else
			s->bindAddress[0]=0;
		s->tcpInterface=this;
		s->socketFamily=socketFamily;

		// Start the connection thread
		int errorCode;




		errorCode = SLNet::RakThread::Create(ConnectionAttemptLoop, s, threadPriority);

		if (errorCode!=0)
		{
			SLNet::OP_DELETE(s, _FILE_AND_LINE_);
			failedConnectionAttempts.Push(s->systemAddress, _FILE_AND_LINE_ );
		}
		return UNASSIGNED_SYSTEM_ADDRESS;
	}	
}
#if OPEN_SSL_CLIENT_SUPPORT==1
void TCPInterface::StartSSLClient(SystemAddress systemAddress)
{
	if (ctx==0)
	{
		sharedSslMutex.Lock();
		SSLeay_add_ssl_algorithms();
		meth = (SSL_METHOD*) SSLv23_client_method();
		SSL_load_error_strings();
		ctx = SSL_CTX_new (meth);
		RakAssert(ctx!=0);
		sharedSslMutex.Unlock();
	}

	SystemAddress *id = startSSL.Allocate( _FILE_AND_LINE_ );
	*id=systemAddress;
	startSSL.Push(id);
	unsigned index = activeSSLConnections.GetIndexOf(systemAddress);
	if (index==(unsigned)-1)
		activeSSLConnections.Insert(systemAddress,_FILE_AND_LINE_);
}
bool TCPInterface::IsSSLActive(SystemAddress systemAddress)
{
	return activeSSLConnections.GetIndexOf(systemAddress)!=-1;
}
#endif
void TCPInterface::Send( const char *data, unsigned length, const SystemAddress &systemAddress, bool broadcast )
{
	SendList( &data, &length, 1, systemAddress,broadcast );
}
bool TCPInterface::SendList( const char **data, const unsigned int *lengths, const int numParameters, const SystemAddress &systemAddress, bool broadcast )
{
	if (isStarted.GetValue()==0)
		return false;
	if (data==0)
		return false;
	if (systemAddress==UNASSIGNED_SYSTEM_ADDRESS && broadcast==false)
		return false;
	unsigned int totalLength=0;
	int i;
	for (i=0; i < numParameters; i++)
	{
		if (lengths[i]>0)
			totalLength+=lengths[i];
	}
	if (totalLength==0)
		return false;

	if (broadcast)
	{
		// Send to all, possible exception system
		for (i=0; i < remoteClientsLength; i++)
		{
			if (remoteClients[i].systemAddress!=systemAddress)
			{
				remoteClients[i].SendOrBuffer(data, lengths, numParameters);
			}
		}
	}
	else
	{
		// Send to this player
		if (systemAddress.systemIndex<remoteClientsLength &&
			remoteClients[systemAddress.systemIndex].systemAddress==systemAddress)
		{
			remoteClients[systemAddress.systemIndex].SendOrBuffer(data, lengths, numParameters);
		}
		else
		{
			for (i=0; i < remoteClientsLength; i++)
			{
				if (remoteClients[i].systemAddress==systemAddress )
				{
					remoteClients[i].SendOrBuffer(data, lengths, numParameters);
				}
			}
		}
	}


	return true;
}
bool TCPInterface::ReceiveHasPackets( void )
{
	return headPush.IsEmpty()==false || incomingMessages.IsEmpty()==false || tailPush.IsEmpty()==false;
}
Packet* TCPInterface::Receive( void )
{
	unsigned int i;
	for (i=0; i < messageHandlerList.Size(); i++)
		messageHandlerList[i]->Update();

	Packet* outgoingPacket = ReceiveInt();

	if (outgoingPacket)
	{
		PluginReceiveResult pluginResult;
		for (i=0; i < messageHandlerList.Size(); i++)
		{
			pluginResult=messageHandlerList[i]->OnReceive(outgoingPacket);
			if (pluginResult==RR_STOP_PROCESSING_AND_DEALLOCATE)
			{
				DeallocatePacket( outgoingPacket );
				outgoingPacket=0; // Will do the loop again and get another packet
				break; // break out of the enclosing for
			}
			else if (pluginResult==RR_STOP_PROCESSING)
			{
				outgoingPacket=0;
				break;
			}
		}
	}
	

	return outgoingPacket;
}
Packet* TCPInterface::ReceiveInt( void )
{
	if (isStarted.GetValue()==0)
		return 0;
	if (headPush.IsEmpty()==false)
		return headPush.Pop();
	Packet *p = incomingMessages.PopInaccurate();
	if (p)
		return p;
	if (tailPush.IsEmpty()==false)
		return tailPush.Pop();
	return 0;
}


void TCPInterface::AttachPlugin( PluginInterface2 *plugin )
{
	if (messageHandlerList.GetIndexOf(plugin)==MAX_UNSIGNED_LONG)
	{
		messageHandlerList.Insert(plugin, _FILE_AND_LINE_);
		plugin->SetTCPInterface(this);
		plugin->OnAttach();
	}
}
void TCPInterface::DetachPlugin( PluginInterface2 *plugin )
{
	if (plugin==0)
		return;

	unsigned int index;
	index = messageHandlerList.GetIndexOf(plugin);
	if (index!=MAX_UNSIGNED_LONG)
	{
		messageHandlerList[index]->OnDetach();
		// Unordered list so delete from end for speed
		messageHandlerList[index]=messageHandlerList[messageHandlerList.Size()-1];
		messageHandlerList.RemoveFromEnd();
		plugin->SetTCPInterface(0);
	}
}
void TCPInterface::CloseConnection( SystemAddress systemAddress )
{
	if (isStarted.GetValue()==0)
		return;
	if (systemAddress==UNASSIGNED_SYSTEM_ADDRESS)
		return;

	unsigned int i;
	for (i=0; i < messageHandlerList.Size(); i++)
		messageHandlerList[i]->OnClosedConnection(systemAddress, UNASSIGNED_RAKNET_GUID, LCR_CLOSED_BY_USER);

	if (systemAddress.systemIndex<remoteClientsLength && remoteClients[systemAddress.systemIndex].systemAddress==systemAddress)
	{
		remoteClients[systemAddress.systemIndex].isActiveMutex.Lock();
		remoteClients[systemAddress.systemIndex].SetActive(false);
		remoteClients[systemAddress.systemIndex].isActiveMutex.Unlock();
	}
	else
	{
		for (i=0; i < remoteClientsLength; i++)
		{
			remoteClients[i].isActiveMutex.Lock();
			if (remoteClients[i].isActive && remoteClients[i].systemAddress==systemAddress)
			{
				remoteClients[systemAddress.systemIndex].SetActive(false);
				remoteClients[i].isActiveMutex.Unlock();
				break;
			}
			remoteClients[i].isActiveMutex.Unlock();
		}
	}


#if OPEN_SSL_CLIENT_SUPPORT==1
	unsigned index = activeSSLConnections.GetIndexOf(systemAddress);
	if (index!=(unsigned)-1)
		activeSSLConnections.RemoveAtIndex(index);
#endif
}
void TCPInterface::DeallocatePacket( Packet *packet )
{
	if (packet==0)
		return;
	if (packet->deleteData)
	{
		rakFree_Ex(packet->data, _FILE_AND_LINE_ );
		incomingMessages.Deallocate(packet, _FILE_AND_LINE_);
	}
	else
	{
		// Came from userspace AllocatePacket
		rakFree_Ex(packet->data, _FILE_AND_LINE_ );
		SLNet::OP_DELETE(packet, _FILE_AND_LINE_);
	}
}
Packet* TCPInterface::AllocatePacket(unsigned dataSize)
{
	Packet*p = SLNet::OP_NEW<Packet>(_FILE_AND_LINE_);
	p->data=(unsigned char*) rakMalloc_Ex(dataSize,_FILE_AND_LINE_);
	p->length=dataSize;
	p->bitSize=BYTES_TO_BITS(dataSize);
	p->deleteData=false;
	p->guid=UNASSIGNED_RAKNET_GUID;
	p->systemAddress=UNASSIGNED_SYSTEM_ADDRESS;
	p->systemAddress.systemIndex=(SystemIndex)-1;
	return p;
}
void TCPInterface::PushBackPacket( Packet *packet, bool pushAtHead )
{
	if (pushAtHead)
		headPush.Push(packet, _FILE_AND_LINE_ );
	else
		tailPush.Push(packet, _FILE_AND_LINE_ );
}
bool TCPInterface::WasStarted(void) const
{
	return threadRunning.GetValue()>0;
}
SystemAddress TCPInterface::HasCompletedConnectionAttempt(void)
{
	SystemAddress sysAddr=UNASSIGNED_SYSTEM_ADDRESS;
	completedConnectionAttemptMutex.Lock();
	if (completedConnectionAttempts.IsEmpty()==false)
		sysAddr=completedConnectionAttempts.Pop();
	completedConnectionAttemptMutex.Unlock();

	if (sysAddr!=UNASSIGNED_SYSTEM_ADDRESS)
	{
		unsigned int i;
		for (i=0; i < messageHandlerList.Size(); i++)
			messageHandlerList[i]->OnNewConnection(sysAddr, UNASSIGNED_RAKNET_GUID, true);
	}

	return sysAddr;
}
SystemAddress TCPInterface::HasFailedConnectionAttempt(void)
{
	SystemAddress sysAddr=UNASSIGNED_SYSTEM_ADDRESS;
	failedConnectionAttemptMutex.Lock();
	if (failedConnectionAttempts.IsEmpty()==false)
		sysAddr=failedConnectionAttempts.Pop();
	failedConnectionAttemptMutex.Unlock();

	if (sysAddr!=UNASSIGNED_SYSTEM_ADDRESS)
	{
		unsigned int i;
		for (i=0; i < messageHandlerList.Size(); i++)
		{
			Packet p;
			p.systemAddress=sysAddr;
			p.data=0;
			p.length=0;
			p.bitSize=0;
			messageHandlerList[i]->OnFailedConnectionAttempt(&p, FCAR_CONNECTION_ATTEMPT_FAILED);
		}
	}

	return sysAddr;
}
SystemAddress TCPInterface::HasNewIncomingConnection(void)
{
	SystemAddress *out, out2;
	out = newIncomingConnections.PopInaccurate();
	if (out)
	{
		out2=*out;
		newIncomingConnections.Deallocate(out, _FILE_AND_LINE_);

		unsigned int i;
		for (i=0; i < messageHandlerList.Size(); i++)
			messageHandlerList[i]->OnNewConnection(out2, UNASSIGNED_RAKNET_GUID, true);

		return *out;
	}
	else
	{
		return UNASSIGNED_SYSTEM_ADDRESS;
	}
}
SystemAddress TCPInterface::HasLostConnection(void)
{
	SystemAddress *out, out2;
	out = lostConnections.PopInaccurate();
	if (out)
	{
		out2=*out;
		lostConnections.Deallocate(out, _FILE_AND_LINE_);

		unsigned int i;
		for (i=0; i < messageHandlerList.Size(); i++)
			messageHandlerList[i]->OnClosedConnection(out2, UNASSIGNED_RAKNET_GUID, LCR_DISCONNECTION_NOTIFICATION);

		return *out;
	}
	else
	{
		return UNASSIGNED_SYSTEM_ADDRESS;
	}
}
void TCPInterface::GetConnectionList( SystemAddress *remoteSystems, unsigned short *numberOfSystems ) const
{
	unsigned short systemCount=0;
	unsigned short maxToWrite=*numberOfSystems;
	for (int i=0; i < remoteClientsLength; i++)
	{
		if (remoteClients[i].isActive)
		{
			if (systemCount < maxToWrite)
				remoteSystems[systemCount]=remoteClients[i].systemAddress;
			systemCount++;
		}
	}
	*numberOfSystems=systemCount;
}
unsigned short TCPInterface::GetConnectionCount(void) const
{
	unsigned short systemCount=0;
	for (int i=0; i < remoteClientsLength; i++)
	{
		if (remoteClients[i].isActive)
			systemCount++;
	}
	return systemCount;
}

unsigned int TCPInterface::GetOutgoingDataBufferSize(SystemAddress systemAddress) const
{
	unsigned bytesWritten=0;
	if (systemAddress.systemIndex<remoteClientsLength &&
		remoteClients[systemAddress.systemIndex].isActive &&
		remoteClients[systemAddress.systemIndex].systemAddress==systemAddress)
	{
		remoteClients[systemAddress.systemIndex].outgoingDataMutex.Lock();
		bytesWritten=remoteClients[systemAddress.systemIndex].outgoingData.GetBytesWritten();
		remoteClients[systemAddress.systemIndex].outgoingDataMutex.Unlock();
		return bytesWritten;
	}

	for (int i=0; i < remoteClientsLength; i++)
	{
		if (remoteClients[i].isActive && remoteClients[i].systemAddress==systemAddress)
		{
			remoteClients[i].outgoingDataMutex.Lock();
			bytesWritten+=remoteClients[i].outgoingData.GetBytesWritten();
			remoteClients[i].outgoingDataMutex.Unlock();
		}
	}
	return bytesWritten;
}
__TCPSOCKET__ TCPInterface::SocketConnect(const char* host, unsigned short remotePort, unsigned short socketFamily, const char *bindAddress)
{
#ifdef __native_client__
	return 0;
#else
	int connectResult;
	(void) connectResult;
	(void) socketFamily;

#if RAKNET_SUPPORT_IPV6!=1
	sockaddr_in serverAddress;

	struct addrinfo *curAddress = NULL;
	int err = getaddrinfo(host, NULL, NULL, &curAddress);

	// #med This should also work with IPv6 addresses in principle. However the old code in RakNet only worked with IPv4. Hence this behavior change won't be in MaxNet 0.1.
	// get the (first) IPv4 address
	while(curAddress != NULL) {
		if (curAddress->ai_family == AF_INET) {
			break; // found an IPv4 address
		}
		curAddress = curAddress->ai_next;
	}

	if (curAddress == NULL)
		return 0;

	if (err != 0)
		return 0;


	#if defined(WINDOWS_STORE_RT)
		__TCPSOCKET__ sockfd = WinRTCreateStreamSocket(AF_INET, SOCK_STREAM, 0);
	#else
		__TCPSOCKET__ sockfd = socket__(AF_INET, SOCK_STREAM, 0);
		if (sockfd < 0) 
			return 0;
	#endif

	memset(&serverAddress, 0, sizeof(serverAddress));
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons( remotePort );
	

	if ( bindAddress && bindAddress[0] )
	{





		inet_pton(AF_INET, bindAddress, &serverAddress.sin_addr.s_addr);

	}
	else
		serverAddress.sin_addr.s_addr = INADDR_ANY;

	int sock_opt=1024*256;
	setsockopt__(sockfd, SOL_SOCKET, SO_RCVBUF, ( char * ) & sock_opt, sizeof ( sock_opt ) );

	serverAddress.sin_addr = ((struct sockaddr_in *)curAddress->ai_addr)->sin_addr;










	blockingSocketListMutex.Lock();
	blockingSocketList.Insert(sockfd, _FILE_AND_LINE_);
	blockingSocketListMutex.Unlock();

	// This is blocking
	connectResult = connect__( sockfd, ( struct sockaddr * ) &serverAddress, sizeof( struct sockaddr ) );

#else

	(void)bindAddress;
	struct addrinfo hints, *res;
	__TCPSOCKET__ sockfd;
	memset(&hints, 0, sizeof hints);
	hints.ai_family = socketFamily;
	hints.ai_socktype = SOCK_STREAM;
	char portStr[32];
	Itoa(remotePort,portStr,10);
	getaddrinfo(host, portStr, &hints, &res);
	sockfd = socket__(res->ai_family, res->ai_socktype, res->ai_protocol);
	blockingSocketListMutex.Lock();
	blockingSocketList.Insert(sockfd, _FILE_AND_LINE_);
	blockingSocketListMutex.Unlock();
	// #low - review usage of static cast here
	connectResult=connect__(sockfd, res->ai_addr, static_cast<int>(res->ai_addrlen));
	freeaddrinfo(res); // free the linked-list

#endif // #if RAKNET_SUPPORT_IPV6!=1

	if (connectResult==-1)
	{
		unsigned sockfdIndex;
		blockingSocketListMutex.Lock();
		sockfdIndex=blockingSocketList.GetIndexOf(sockfd);
		if (sockfdIndex!=(unsigned)-1)
			blockingSocketList.RemoveAtIndexFast(sockfdIndex);
		blockingSocketListMutex.Unlock();

		closesocket__(sockfd);
		return 0;
	}

	return sockfd;
#endif  // __native_client__
}

RAK_THREAD_DECLARATION(SLNet::ConnectionAttemptLoop)
{



	TCPInterface::ThisPtrPlusSysAddr *s = (TCPInterface::ThisPtrPlusSysAddr *) arguments;



	SystemAddress systemAddress = s->systemAddress;
	TCPInterface *tcpInterface = s->tcpInterface;
	int newRemoteClientIndex=systemAddress.systemIndex;
	unsigned short socketFamily = s->socketFamily;
	SLNet::OP_DELETE(s, _FILE_AND_LINE_);

	char str1[64];
	systemAddress.ToString(false, str1, static_cast<size_t>(64));
	__TCPSOCKET__ sockfd = tcpInterface->SocketConnect(str1, systemAddress.GetPort(), socketFamily, s->bindAddress);
	if (sockfd==0)
	{
		tcpInterface->remoteClients[newRemoteClientIndex].isActiveMutex.Lock();
		tcpInterface->remoteClients[newRemoteClientIndex].SetActive(false);
		tcpInterface->remoteClients[newRemoteClientIndex].isActiveMutex.Unlock();

		tcpInterface->failedConnectionAttemptMutex.Lock();
		tcpInterface->failedConnectionAttempts.Push(systemAddress, _FILE_AND_LINE_ );
		tcpInterface->failedConnectionAttemptMutex.Unlock();
		return 0;
	}

	tcpInterface->remoteClients[newRemoteClientIndex].socket=sockfd;
	tcpInterface->remoteClients[newRemoteClientIndex].systemAddress=systemAddress;

	// Notify user that the connection attempt has completed.
	if (tcpInterface->threadRunning.GetValue()>0)
	{
		tcpInterface->completedConnectionAttemptMutex.Lock();
		tcpInterface->completedConnectionAttempts.Push(systemAddress, _FILE_AND_LINE_ );
		tcpInterface->completedConnectionAttemptMutex.Unlock();
	}	




	return 0;

}

RAK_THREAD_DECLARATION(SLNet::UpdateTCPInterfaceLoop)
{



	TCPInterface * sts = ( TCPInterface * ) arguments;


//	const int BUFF_SIZE=8096;
	const unsigned int BUFF_SIZE=1048576;
	//char data[ BUFF_SIZE ];
	char * data = (char*) rakMalloc_Ex(BUFF_SIZE,_FILE_AND_LINE_);
	Packet *incomingMessage;
	fd_set readFD, exceptionFD, writeFD;
	sts->threadRunning.Increment();

#if RAKNET_SUPPORT_IPV6!=1
	sockaddr_in sockAddr;
	int sockAddrSize = sizeof(sockAddr);
#else
	struct sockaddr_storage sockAddr;
	socklen_t sockAddrSize = sizeof(sockAddr);
#endif

	int len;
	__TCPSOCKET__ newSock;
	int selectResult;


	timeval tv;
	tv.tv_sec=0;
	tv.tv_usec=30000;


	while (sts->isStarted.GetValue()>0)
	{
#if OPEN_SSL_CLIENT_SUPPORT==1
		SystemAddress *sslSystemAddress;
		sslSystemAddress = sts->startSSL.PopInaccurate();
		if (sslSystemAddress)
		{
			if (sslSystemAddress->systemIndex>=0 &&
				sslSystemAddress->systemIndex<sts->remoteClientsLength &&
				sts->remoteClients[sslSystemAddress->systemIndex].systemAddress==*sslSystemAddress)
			{
				sts->remoteClients[sslSystemAddress->systemIndex].InitSSL(sts->ctx,sts->meth);
			}
			else
			{
				for (int i=0; i < sts->remoteClientsLength; i++)
				{
					sts->remoteClients[i].isActiveMutex.Lock();
					if (sts->remoteClients[i].isActive && sts->remoteClients[i].systemAddress==*sslSystemAddress)
					{
						if (sts->remoteClients[i].ssl==0)
							sts->remoteClients[i].InitSSL(sts->ctx,sts->meth);
					}
					sts->remoteClients[i].isActiveMutex.Unlock();
				}
			}
			sts->startSSL.Deallocate(sslSystemAddress,_FILE_AND_LINE_);
		}
#endif


		__TCPSOCKET__ largestDescriptor=0; // see select__()'s first parameter's documentation under linux


		// Linux' select__() implementation changes the timeout

		tv.tv_sec=0;
		tv.tv_usec=30000;


#ifdef _MSC_VER
#pragma warning( disable : 4127 ) // warning C4127: conditional expression is constant
#endif
		for(;;)
		{
			// Reset readFD, writeFD, and exceptionFD since select seems to clear it
			FD_ZERO(&readFD);
			FD_ZERO(&exceptionFD);
			FD_ZERO(&writeFD);
			largestDescriptor=0;
			if (sts->listenSocket!=0)
			{
				FD_SET(sts->listenSocket, &readFD);
				FD_SET(sts->listenSocket, &exceptionFD);
				largestDescriptor = sts->listenSocket; // @see largestDescriptor def
			}

			unsigned i;
			for (i=0; i < sts->remoteClientsLength; i++)
			{
				sts->remoteClients[i].isActiveMutex.Lock();
				if (sts->remoteClients[i].isActive)
				{
					// calling FD_ISSET with -1 as socket (that’s what 0 is set to) produces a bus error under Linux 64-Bit
					__TCPSOCKET__ socketCopy = sts->remoteClients[i].socket;
					if (socketCopy != 0)
					{
						FD_SET(socketCopy, &readFD);
						FD_SET(socketCopy, &exceptionFD);
						if (sts->remoteClients[i].outgoingData.GetBytesWritten()>0)
							FD_SET(socketCopy, &writeFD);
						if(socketCopy > largestDescriptor) // @see largestDescriptorDef
							largestDescriptor = socketCopy;
					}
				}
				sts->remoteClients[i].isActiveMutex.Unlock();
			}

#ifdef _MSC_VER
#pragma warning( disable : 4244 ) // warning C4127: conditional expression is constant
#endif


			selectResult=(int) select__(largestDescriptor+1, &readFD, &writeFD, &exceptionFD, &tv);		




			if (selectResult<=0)
				break;

			if (sts->listenSocket!=0 && FD_ISSET(sts->listenSocket, &readFD))
			{
				newSock = accept__(sts->listenSocket, (sockaddr*)&sockAddr, (socklen_t*)&sockAddrSize);

				if (newSock != 0)
				{
					int newRemoteClientIndex=-1;
					for (newRemoteClientIndex=0; newRemoteClientIndex < sts->remoteClientsLength; newRemoteClientIndex++)
					{
						sts->remoteClients[newRemoteClientIndex].isActiveMutex.Lock();
						if (sts->remoteClients[newRemoteClientIndex].isActive==false)
						{
							sts->remoteClients[newRemoteClientIndex].socket=newSock;

#if RAKNET_SUPPORT_IPV6!=1
							sts->remoteClients[newRemoteClientIndex].systemAddress.address.addr4.sin_addr.s_addr=sockAddr.sin_addr.s_addr;
							sts->remoteClients[newRemoteClientIndex].systemAddress.SetPortNetworkOrder( sockAddr.sin_port);
							sts->remoteClients[newRemoteClientIndex].systemAddress.systemIndex=newRemoteClientIndex;
#else
							if (sockAddr.ss_family==AF_INET)
							{
								memcpy(&sts->remoteClients[newRemoteClientIndex].systemAddress.address.addr4,(sockaddr_in *)&sockAddr,sizeof(sockaddr_in));
							//	sts->remoteClients[newRemoteClientIndex].systemAddress.address.addr4.sin_port=ntohs( sts->remoteClients[newRemoteClientIndex].systemAddress.address.addr4.sin_port );
							}
							else
							{
								memcpy(&sts->remoteClients[newRemoteClientIndex].systemAddress.address.addr6,(sockaddr_in6 *)&sockAddr,sizeof(sockaddr_in6));
							//	sts->remoteClients[newRemoteClientIndex].systemAddress.address.addr6.sin6_port=ntohs( sts->remoteClients[newRemoteClientIndex].systemAddress.address.addr6.sin6_port );
							}

#endif // #if RAKNET_SUPPORT_IPV6!=1
							sts->remoteClients[newRemoteClientIndex].SetActive(true);
							sts->remoteClients[newRemoteClientIndex].isActiveMutex.Unlock();


							SystemAddress *newConnectionSystemAddress=sts->newIncomingConnections.Allocate( _FILE_AND_LINE_ );
							*newConnectionSystemAddress=sts->remoteClients[newRemoteClientIndex].systemAddress;
							sts->newIncomingConnections.Push(newConnectionSystemAddress);

							break;
						}
						sts->remoteClients[newRemoteClientIndex].isActiveMutex.Unlock();
					}
					if (newRemoteClientIndex==-1)
					{
						closesocket__(sts->listenSocket);
					}
				}
				else
				{
#ifdef _DO_PRINTF
					RAKNET_DEBUG_PRINTF("Error: connection failed\n");
#endif
				}
			}
			else if (sts->listenSocket!=0 && FD_ISSET(sts->listenSocket, &exceptionFD))
			{
#ifdef _DO_PRINTF
				int err;
				int errlen = sizeof(err);
				getsockopt__(sts->listenSocket, SOL_SOCKET, SO_ERROR,(char*)&err, &errlen);
				RAKNET_DEBUG_PRINTF("Socket error %s on listening socket\n", err);
#endif
			}
			
			{
				i=0;
				while (i < sts->remoteClientsLength)
				{
					if (sts->remoteClients[i].isActive==false)
					{
						i++;
						continue;
					}
					// calling FD_ISSET with -1 as socket (that’s what 0 is set to) produces a bus error under Linux 64-Bit
					__TCPSOCKET__ socketCopy = sts->remoteClients[i].socket;
					if (socketCopy == 0)
					{
						i++;
						continue;
					}

					if (FD_ISSET(socketCopy, &exceptionFD))
					{
// #ifdef _DO_PRINTF
// 						if (sts->listenSocket!=-1)
// 						{
// 							int err;
// 							int errlen = sizeof(err);
// 							getsockopt__(sts->listenSocket, SOL_SOCKET, SO_ERROR,(char*)&err, &errlen);
// 							in_addr in;
// 							in.s_addr = sts->remoteClients[i].systemAddress.binaryAddress;
//							char ip[65];
//							inet_ntop(sts->remoteClients[i].systemAddress.address.addr4.sin_family, &in, ip, 65);
// 							RAKNET_DEBUG_PRINTF("Socket error %i on %s:%i\n", err,ip, sts->remoteClients[i].systemAddress.GetPort() );
// 						}
// 						
// #endif
						// Connection lost abruptly
						SystemAddress *lostConnectionSystemAddress=sts->lostConnections.Allocate( _FILE_AND_LINE_ );
						*lostConnectionSystemAddress=sts->remoteClients[i].systemAddress;
						sts->lostConnections.Push(lostConnectionSystemAddress);
						sts->remoteClients[i].isActiveMutex.Lock();
						sts->remoteClients[i].SetActive(false);
						sts->remoteClients[i].isActiveMutex.Unlock();
					}
					else
					{
						if (FD_ISSET(socketCopy, &readFD))
						{
							// if recv returns 0 this was a graceful close
							len = sts->remoteClients[i].Recv(data,BUFF_SIZE);

						
							// removeme
// 								data[len]=0;
// 								printf(data);
							
							if (len>0)
							{
								incomingMessage=sts->incomingMessages.Allocate( _FILE_AND_LINE_ );
								incomingMessage->data = (unsigned char*) rakMalloc_Ex( len+1, _FILE_AND_LINE_ );
								memcpy(incomingMessage->data, data, len);
								incomingMessage->data[len]=0; // Null terminate this so we can print it out as regular strings.  This is different from RakNet which does not do this.
								// printf("RECV: %s\n",incomingMessage->data);
								/*
								if (1)
								{
									static FILE *fp=0;
									if (fp==0)
									{
										fopen_s(&fp, "tcpRcv.txt", "wb");
									}
									fwrite(data,1,len,fp);
								}
								*/
								incomingMessage->length=len;
								incomingMessage->deleteData=true; // actually means came from SPSC, rather than AllocatePacket
								incomingMessage->systemAddress=sts->remoteClients[i].systemAddress;
								sts->incomingMessages.Push(incomingMessage);
							}
							else
							{
								// Connection lost gracefully
								SystemAddress *lostConnectionSystemAddress=sts->lostConnections.Allocate( _FILE_AND_LINE_ );
								*lostConnectionSystemAddress=sts->remoteClients[i].systemAddress;
								sts->lostConnections.Push(lostConnectionSystemAddress);
								sts->remoteClients[i].isActiveMutex.Lock();
								sts->remoteClients[i].SetActive(false);
								sts->remoteClients[i].isActiveMutex.Unlock();
								continue;
							}
						}
						if (FD_ISSET(socketCopy, &writeFD))
						{
							RemoteClient *rc = &sts->remoteClients[i];
							unsigned int bytesInBuffer;
							int bytesAvailable;
							int bytesSent;
							rc->outgoingDataMutex.Lock();
							bytesInBuffer=rc->outgoingData.GetBytesWritten();
							if (bytesInBuffer>0)
							{
								unsigned int contiguousLength;
								char* contiguousBytesPointer = rc->outgoingData.PeekContiguousBytes(&contiguousLength);
								if (contiguousLength < (unsigned int) BUFF_SIZE && contiguousLength<bytesInBuffer)
								{
									if (bytesInBuffer > BUFF_SIZE)
										bytesAvailable=BUFF_SIZE;
									else
										bytesAvailable=bytesInBuffer;
									rc->outgoingData.ReadBytes(data,bytesAvailable,true);
									bytesSent=rc->Send(data,bytesAvailable);
								}
								else
								{
									bytesSent=rc->Send(contiguousBytesPointer,contiguousLength);
								}

								if (bytesSent>0)
									rc->outgoingData.IncrementReadOffset(bytesSent);
								bytesInBuffer=rc->outgoingData.GetBytesWritten();
							}
							rc->outgoingDataMutex.Unlock();
						}
							
						i++; // Nothing deleted so increment the index
					}
				}
			}
		}

		// Sleep 0 on Linux monopolizes the CPU
		RakSleep(30);
	}
	sts->threadRunning.Decrement();

	rakFree_Ex(data,_FILE_AND_LINE_);




	return 0;

}

void RemoteClient::SetActive(bool a)
{
	if (isActive != a)
	{
		isActive=a;
		Reset();
		if (isActive==false && socket!=0)
		{
			closesocket__(socket);
			socket=0;
		}
	}
}
void RemoteClient::SendOrBuffer(const char **data, const unsigned int *lengths, const int numParameters)
{
	// True can save memory and buffer copies, but gives worse performance overall
	// Do not use true for the XBOX, as it just locks up
	const bool ALLOW_SEND_FROM_USER_THREAD=false;

	int parameterIndex;
	if (isActive==false)
		return;
	parameterIndex=0;
	for (; parameterIndex < numParameters; parameterIndex++)
	{
		outgoingDataMutex.Lock();
		if (ALLOW_SEND_FROM_USER_THREAD && outgoingData.GetBytesWritten()==0)
		{
			outgoingDataMutex.Unlock();
			int bytesSent = Send(data[parameterIndex],lengths[parameterIndex]);
			if (bytesSent<(int) lengths[parameterIndex])
			{
				// Push remainder
				outgoingDataMutex.Lock();
				outgoingData.WriteBytes(data[parameterIndex]+bytesSent,lengths[parameterIndex]-bytesSent,_FILE_AND_LINE_);
				outgoingDataMutex.Unlock();
			}
		}
		else
		{
			outgoingData.WriteBytes(data[parameterIndex],lengths[parameterIndex],_FILE_AND_LINE_);
			outgoingDataMutex.Unlock();
		}
	}
}
#if OPEN_SSL_CLIENT_SUPPORT==1
bool RemoteClient::InitSSL(SSL_CTX* ctx, SSL_METHOD *meth)
{
	(void) meth;

	ssl = SSL_new (ctx);                         
	RakAssert(ssl);    
	int res;
	res = SSL_set_fd (ssl, socket);
	if (res!=1)
	{
		printf("SSL_set_fd error: %s\n", ERR_reason_error_string(ERR_get_error()));
		SSL_free(ssl);
		ssl=0;
		return false;
	}
	RakAssert(res==1);
	res = SSL_connect (ssl);
	if (res<0)
	{
		unsigned long err = ERR_get_error();
		printf("SSL_connect error: %s\n", ERR_reason_error_string(err));
		SSL_free(ssl);
		ssl=0;
		return false;
	}
	else if (res==0)
	{
		// The TLS/SSL handshake was not successful but was shut down controlled and by the specifications of the TLS/SSL protocol. Call SSL_get_error() with the return value ret to find out the reason. 
		int err = SSL_get_error(ssl, res);
		switch (err)
		{
		case SSL_ERROR_NONE:
			printf("SSL_ERROR_NONE\n");
			break;
		case SSL_ERROR_ZERO_RETURN:
			printf("SSL_ERROR_ZERO_RETURN\n");
			break;
		case SSL_ERROR_WANT_READ:
			printf("SSL_ERROR_WANT_READ\n");
			break;
		case SSL_ERROR_WANT_WRITE:
			printf("SSL_ERROR_WANT_WRITE\n");
			break;
		case SSL_ERROR_WANT_CONNECT:
			printf("SSL_ERROR_WANT_CONNECT\n");
			break;
		case SSL_ERROR_WANT_ACCEPT:
			printf("SSL_ERROR_WANT_ACCEPT\n");
			break;
		case SSL_ERROR_WANT_X509_LOOKUP:
			printf("SSL_ERROR_WANT_X509_LOOKUP\n");
			break;
		case SSL_ERROR_SYSCALL:
			{
				// http://www.openssl.org/docs/ssl/SSL_get_error.html
				char buff[1024];
				unsigned long ege = ERR_get_error();
				if (ege==0 && res==0)
					printf("SSL_ERROR_SYSCALL EOF in violation of the protocol\n");
				else if (ege==0 && res==-1) {
					strerror_s(buff, errno);
					printf("SSL_ERROR_SYSCALL %s\n", buff);
				}
				else
					printf("SSL_ERROR_SYSCALL %s\n", ERR_error_string(ege, buff));
			}
			break;
		case SSL_ERROR_SSL:
			printf("SSL_ERROR_SSL\n");
			break;
		}

	}

	if (res!=1)
	{
		SSL_free(ssl);
		ssl=0;
		return false;
	}
	return true;
}
void RemoteClient::DisconnectSSL(void)
{
	if (ssl)
		SSL_shutdown (ssl);  /* send SSL/TLS close_notify */
}
void RemoteClient::FreeSSL(void)
{
	if (ssl)
		SSL_free (ssl);
}
int RemoteClient::Send(const char *data, unsigned int length)
{
	if (ssl)
		return SSL_write (ssl, data, length);
	else
		return send__(socket, data, length, 0);
}
int RemoteClient::Recv(char *data, const int dataSize)
{
	if (ssl)
		return SSL_read (ssl, data, dataSize);
	else
		return recv__(socket, data, dataSize, 0);
}
#else
int RemoteClient::Send(const char *data, unsigned int length)
{
#ifdef __native_client__
	return -1;
#else
	return send__(socket, data, length, 0);
#endif
}
int RemoteClient::Recv(char *data, const int dataSize)
{
#ifdef __native_client__
	return -1;
#else
	return recv__(socket, data, dataSize, 0);
#endif
}
#endif

#ifdef _MSC_VER
#pragma warning( pop )
#endif

#endif // _RAKNET_SUPPORT_*
