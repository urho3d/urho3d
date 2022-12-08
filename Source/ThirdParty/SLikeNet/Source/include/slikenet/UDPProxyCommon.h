/*
 *  Copyright (c) 2014, Oculus VR, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the BSD-style license found in the
 *  RakNet License.txt file in the licenses directory of this source tree. An additional grant 
 *  of patent rights can be found in the RakNet Patents.txt file in the same directory.
 *
 */

#ifndef __UDP_PROXY_COMMON_H
#define __UDP_PROXY_COMMON_H

// System flow:
/*
UDPProxyClient: End user
UDPProxyServer: open server, to route messages from end users that can't connect to each other using UDPForwarder class.
UDPProxyCoordinator: Server somewhere, connected to by RakNet, to maintain a list of UDPProxyServer

UDPProxyServer
 On startup, log into UDPProxyCoordinator and register self

UDPProxyClient
 Wish to open route to X
 Send message to UDPProxyCoordinator containing X, desired timeout
 Wait for success or failure

UDPProxyCoordinator:
* Get openRouteRequest
 If no servers registered, return failure
 Add entry to memory
 chooseBestUDPProxyServer() (overridable, chooses at random by default)
 Query this server to StartForwarding(). Return success or failure
 If failure, choose another server from the remaining list. If none remaining, return failure. Else return success.
* Disconnect:
 If disconnected system is pending client on openRouteRequest, delete that request
 If disconnected system is UDPProxyServer, remove from list. For each pending client for this server, choose from remaining servers.
* Login:
 Add to UDPProxyServer list, validating password if set
*/

// Stored in the second byte after ID_UDP_PROXY_GENERAL
// Otherwise MessageIdentifiers.h is too cluttered and will hit the limit on enumerations in a single byte
enum UDPProxyMessages
{
	ID_UDP_PROXY_FORWARDING_SUCCEEDED,
	ID_UDP_PROXY_FORWARDING_NOTIFICATION,
	ID_UDP_PROXY_NO_SERVERS_ONLINE,
	ID_UDP_PROXY_RECIPIENT_GUID_NOT_CONNECTED_TO_COORDINATOR,
	ID_UDP_PROXY_ALL_SERVERS_BUSY,
	ID_UDP_PROXY_IN_PROGRESS,
	ID_UDP_PROXY_FORWARDING_REQUEST_FROM_CLIENT_TO_COORDINATOR,
	ID_UDP_PROXY_PING_SERVERS_FROM_COORDINATOR_TO_CLIENT,
	ID_UDP_PROXY_PING_SERVERS_REPLY_FROM_CLIENT_TO_COORDINATOR,
	ID_UDP_PROXY_FORWARDING_REQUEST_FROM_COORDINATOR_TO_SERVER,
	ID_UDP_PROXY_FORWARDING_REPLY_FROM_SERVER_TO_COORDINATOR,
	ID_UDP_PROXY_LOGIN_REQUEST_FROM_SERVER_TO_COORDINATOR,
	ID_UDP_PROXY_LOGIN_SUCCESS_FROM_COORDINATOR_TO_SERVER,
	ID_UDP_PROXY_ALREADY_LOGGED_IN_FROM_COORDINATOR_TO_SERVER,
	ID_UDP_PROXY_NO_PASSWORD_SET_FROM_COORDINATOR_TO_SERVER,
	ID_UDP_PROXY_WRONG_PASSWORD_FROM_COORDINATOR_TO_SERVER
};


#define UDP_FORWARDER_MAXIMUM_TIMEOUT (60000 * 10)

#endif
