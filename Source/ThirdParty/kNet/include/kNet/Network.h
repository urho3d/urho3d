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

/** @file Network.h
	@brief The class Network. The root point for creating client and server objects. */

// Modified by Lasse Oorni for Urho3D

#if defined(KNET_UNIX) || defined(ANDROID)
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
// Urho3D: include also unistd.h
#include <unistd.h>
#endif

#include "kNetBuildConfig.h"
#include "Socket.h"
#include "NetworkServer.h"
#include "MessageConnection.h"
#include "StatsEventHierarchy.h"

namespace kNet
{

class NetworkWorkerThread;

/// Provides the application an interface for both client and server networking.
class Network
{
public:
	Network();
	~Network();

	static void PrintAddrInfo(const addrinfo *address);

	void PrintHostNameInfo(const char *hostname, const char *port);

	/// Starts a network server that listens to the given local port.
	/// @param serverListener [in] A pointer to the listener object that will be registered to receive notifications
	///	about incoming connections.
	/// @param allowAddressReuse If true, kNet passes the SO_REUSEADDR parameter to the server listen socket before binding 
	///        the socket to a local port (== before starting the server). This allows the same port to be forcibly reused
	///        when restarting the server if a crash occurs, without having to wait for the operating system to free up the port.
	NetworkServer *StartServer(unsigned short port, SocketTransportLayer transport, INetworkServerListener *serverListener, bool allowAddressReuse);

	/// Starts a network server that listens to multiple local ports.
	/// This version of the function is given a list of pairs (port, UDP|TCP) values
	/// and the server will start listening on each of them.
	/// @param allowAddressReuse If true, kNet passes the SO_REUSEADDR parameter to the server listen socket before binding 
	///        the socket to a local port (== before starting the server). This allows the same port to be forcibly reused
	///        when restarting the server if a crash occurs, without having to wait for the operating system to free up the port.
	NetworkServer *StartServer(const std::vector<std::pair<unsigned short, SocketTransportLayer> > &listenPorts, INetworkServerListener *serverListener, bool allowAddressReuse);

	void StopServer();

	/// Connects a raw socket (low-level, no MessageConnection abstraction) to the given destination.
	Socket *ConnectSocket(const char *address, unsigned short port, SocketTransportLayer transport);

	/// Frees the given Socket object (performs an immediate bidirectional shutdown and frees the socket). After calling 
	/// this function, do not dereference that Socket pointer, as it is deleted.
	void DeleteSocket(Socket *socket);

	/// Closes the given MessageConnection object. 
	void CloseConnection(MessageConnection *connection);

	/** Connects to the given address:port using kNet over UDP or TCP. When you are done with the connection,
		free it by letting the refcount go to 0. */
	Ptr(MessageConnection) Connect(const char *address, unsigned short port, SocketTransportLayer transport, IMessageHandler *messageHandler, Datagram *connectMessage = 0);

	/// Returns the local host name of the system (the local machine name or the local IP, whatever is specified by the system).
	const char *LocalAddress() const { return localHostName.c_str(); }

	/// Returns the error string associated with the given networking error id.
	static std::string GetErrorString(int error);

	/// Returns the error string corresponding to the last error that occurred in the networking library.
	static std::string GetLastErrorString();

	/// Returns the error id corresponding to the last error that occurred in the networking library.
	static int GetLastError();

	/// Returns the amount of currently executing background network worker threads.
	int NumWorkerThreads() const { return (int)workerThreads.size(); }

	/// Returns the NetworkServer object, or null if no server has been started.
	Ptr(NetworkServer) GetServer() { return server; }

	/// Returns all current connections in the system.
	std::set<MessageConnection *> Connections() const { return connections; }

	/// Returns the data structure that collects statistics about the whole Network.
	Lock<StatsEventHierarchyNode> Statistics() { return statistics.Acquire(); }

private:
	/// Specifies the local network address of the system. This name is cached here on initialization
	/// to avoid multiple queries to namespace providers whenever the name is needed.
	std::string localHostName;

	/// Maintains the server-related data structures if this computer
	/// is acting as a server. Otherwise this data is not used.
	Ptr(NetworkServer) server;

	/// Contains all active sockets in the system.
	std::list<Socket> sockets;

	/// Tracks all existing connections in the system.
	std::set<MessageConnection *> connections;

	Lockable<StatsEventHierarchyNode> statistics;

	/// Takes the ownership of the given socket, and returns a pointer to the owned one.
	Socket *StoreSocket(const Socket &cp);

	friend class NetworkServer;

	void SendUDPConnectDatagram(Socket &socket, Datagram *connectMessage);

	/// Returns a new UDP socket that is bound to communicating with the given endpoint, under
	/// the given UDP master server socket.
	/// The returned pointer is owned by this class.
	Socket *CreateUDPSlaveSocket(Socket *serverListenSocket, const EndPoint &remoteEndPoint, const char *remoteHostName);

	/// Opens a new socket that listens on the given port using the given transport.
	/// @param allowAddressReuse If true, kNet passes the SO_REUSEADDR parameter to the server listen socket before binding 
	///        the socket to a local port (== before starting the server). This allows the same port to be forcibly reused
	///        when restarting the server if a crash occurs, without having to wait for the operating system to free up the port.
	Socket *OpenListenSocket(unsigned short port, SocketTransportLayer transport, bool allowAddressReuse);

	/// Stores all the currently running network worker threads. Each thread is assigned
	/// a list of MessageConnections and NetworkServers to oversee. The worker threads
	/// then manage the socket reads and writes on these connections.
	std::vector<NetworkWorkerThread*> workerThreads;

	/// Examines each currently running worker thread and returns one that has sufficiently low load,
	/// or creates a new thread and returns it if no such thread exists. The thread is added and maintained
	/// in the workerThreads list.
	NetworkWorkerThread *GetOrCreateWorkerThread();

	/// A notification function that is called by NetworkServer whenever it creates a new MessageConnection object.
	/// The Network subsystem will store this new connection for tracking purposes.
	void NewMessageConnectionCreated(MessageConnection *connection);

	/// Takes the given MessageConnection and associates a NetworkWorkerThread for it.
	void AssignConnectionToWorkerThread(MessageConnection *connection);

	/// Takes the given server and associates a NetworkWorkerThread for it.
	void AssignServerToWorkerThread(NetworkServer *server);

	/// Closes the given workerThread and deletes it (do not reference the passed pointer afterwards). 
	/// Call this function only after first removing all MessageConnections and NetworkServers from the thread.
	void CloseWorkerThread(NetworkWorkerThread *workerThread);

	/// Dissociates the given connection from its worker thread, and closes the worker thread if it does not
	/// have any servers or connections to work on any more.
	void RemoveConnectionFromItsWorkerThread(MessageConnection *connection);

	/// Dissociates the given server from its worker thread, and closes the worker thread if it does not
	/// have any servers or connections to work on any more.
	void RemoveServerFromItsWorkerThread(NetworkServer *server);

	void Init();
	void DeInit();

#ifdef WIN32
	WSADATA wsaData;
#endif
};

/// Outputs the given number of bytes formatted to KB or MB suffix for readability.
std::string FormatBytes(u64 numBytes);

std::string FormatBytes(double numBytes);

} // ~kNet
