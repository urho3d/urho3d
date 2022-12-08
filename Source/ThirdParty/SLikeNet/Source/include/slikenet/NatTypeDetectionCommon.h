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

/// \defgroup NAT_TYPE_DETECTION_GROUP NatTypeDetection
/// \brief Use a remote server with multiple IP addresses to determine what type of NAT your router is using
/// \details
/// \ingroup PLUGINS_GROUP

#ifndef __NAT_TYPE_DETECTION_COMMON_H
#define __NAT_TYPE_DETECTION_COMMON_H

#include "NativeFeatureIncludes.h"

#if _RAKNET_SUPPORT_NatTypeDetectionServer==1 || _RAKNET_SUPPORT_NatTypeDetectionClient==1

#include "SocketIncludes.h"
#include "types.h"
#include "socket2.h"

namespace SLNet
{

	/// All possible types of NATs (except NAT_TYPE_COUNT, which is an internal value) 
	enum NATTypeDetectionResult
	{
		/// Works with anyone
		NAT_TYPE_NONE,
		/// Accepts any datagrams to a port that has been previously used. Will accept the first datagram from the remote peer.
		NAT_TYPE_FULL_CONE,
		/// Accepts datagrams to a port as long as the datagram source IP address is a system we have already sent to. Will accept the first datagram if both systems send simultaneously. Otherwise, will accept the first datagram after we have sent one datagram.
		NAT_TYPE_ADDRESS_RESTRICTED,
		/// Same as address-restricted cone NAT, but we had to send to both the correct remote IP address and correct remote port. The same source address and port to a different destination uses the same mapping.
		NAT_TYPE_PORT_RESTRICTED,
		/// A different port is chosen for every remote destination. The same source address and port to a different destination uses a different mapping. Since the port will be different, the first external punchthrough attempt will fail. For this to work it requires port-prediction (MAX_PREDICTIVE_PORT_RANGE>1) and that the router chooses ports sequentially.
		NAT_TYPE_SYMMETRIC,
		/// Hasn't been determined. NATTypeDetectionClient does not use this, but other plugins might
		NAT_TYPE_UNKNOWN,
		/// In progress. NATTypeDetectionClient does not use this, but other plugins might
		NAT_TYPE_DETECTION_IN_PROGRESS,
		/// Didn't bother figuring it out, as we support UPNP, so it is equivalent to NAT_TYPE_NONE. NATTypeDetectionClient does not use this, but other plugins might
		NAT_TYPE_SUPPORTS_UPNP,
		/// \internal Must be last
		NAT_TYPE_COUNT
	};

	/// \return Can one system with NATTypeDetectionResult \a type1 connect to \a type2
	bool RAK_DLL_EXPORT CanConnect(NATTypeDetectionResult type1, NATTypeDetectionResult type2);

	/// Return a technical string representin the enumeration
	RAK_DLL_EXPORT const char * NATTypeDetectionResultToString(NATTypeDetectionResult type);

	/// Return a friendly string representing the enumeration
	/// None and relaxed can connect to anything
	/// Moderate can connect to moderate or less
	/// Strict can connect to relaxed or less
	RAK_DLL_EXPORT const char * NATTypeDetectionResultToStringFriendly(NATTypeDetectionResult type);

	/// \internal
	RAK_DLL_EXPORT RakNetSocket2* CreateNonblockingBoundSocket(const char *bindAddr
#ifdef __native_client__
		,_PP_Instance_ chromeInstance
#endif
		, RNS2EventHandler *eventHandler
		);

	/// \internal
	//int NatTypeRecvFrom(char *data, RakNetSocket2* socket, SystemAddress &sender, RNS2EventHandler *eventHandler);
}

#endif // #if _RAKNET_SUPPORT_NatTypeDetectionServer==1 || _RAKNET_SUPPORT_NatTypeDetectionClient==1

#endif
