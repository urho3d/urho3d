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
/// \brief Contains the NAT-type detection code for the client
///


#include "NativeFeatureIncludes.h"
#if _RAKNET_SUPPORT_NatTypeDetectionClient==1

#ifndef __NAT_TYPE_DETECTION_CLIENT_H
#define __NAT_TYPE_DETECTION_CLIENT_H

#include "types.h"
#include "Export.h"
#include "PluginInterface2.h"
#include "PacketPriority.h"
#include "SocketIncludes.h"
#include "DS_OrderedList.h"
#include "string.h"
#include "NatTypeDetectionCommon.h"

namespace SLNet
{
/// Forward declarations
class RakPeerInterface;
struct Packet;

	/// \brief Client code for NatTypeDetection
	/// \details See NatTypeDetectionServer.h for algorithm
	/// To use, just connect to the server, and call DetectNAT
	/// You will get back ID_NAT_TYPE_DETECTION_RESULT with one of the enumerated values of NATTypeDetectionResult found in NATTypeDetectionCommon.h
	/// See also http://www.jenkinssoftware.com/raknet/manual/natpunchthrough.html
	/// \sa NatPunchthroughClient
	/// \sa NatTypeDetectionServer
	/// \ingroup NAT_TYPE_DETECTION_GROUP
	class RAK_DLL_EXPORT NatTypeDetectionClient : public PluginInterface2, public RNS2EventHandler
	{
	public:

		// GetInstance() and DestroyInstance(instance*)
		STATIC_FACTORY_DECLARATIONS(NatTypeDetectionClient)

		// Constructor
		NatTypeDetectionClient();

		// Destructor
		virtual ~NatTypeDetectionClient();

		/// Send the message to the server to detect the nat type
		/// Server must be running NatTypeDetectionServer
		/// We must already be connected to the server
		/// \param[in] serverAddress address of the server
		void DetectNATType(SystemAddress _serverAddress);

		/// \internal For plugin handling
		virtual void Update(void);

		/// \internal For plugin handling
		virtual PluginReceiveResult OnReceive(Packet *packet);

		virtual void OnClosedConnection(const SystemAddress &systemAddress, RakNetGUID rakNetGUID, PI2_LostConnectionReason lostConnectionReason );
		virtual void OnRakPeerShutdown(void);
		virtual void OnDetach(void);

		virtual void OnRNS2Recv(RNS2RecvStruct *recvStruct);
		virtual void DeallocRNS2RecvStruct(RNS2RecvStruct *s, const char *file, unsigned int line);
		virtual RNS2RecvStruct *AllocRNS2RecvStruct(const char *file, unsigned int line);
	protected:
		DataStructures::Queue<RNS2RecvStruct*> bufferedPackets;
		SimpleMutex bufferedPacketsMutex;
		
		RakNetSocket2* c2;
		//unsigned short c2Port;
		void Shutdown(void);
		void OnCompletion(NATTypeDetectionResult result);
		bool IsInProgress(void) const;

		void OnTestPortRestricted(Packet *packet);
		SystemAddress serverAddress;
	};


}


#endif

#endif // _RAKNET_SUPPORT_*
