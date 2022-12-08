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
/// \brief Derivation of the packet logger to defer the call to WriteLog until the user thread.
///


#include "NativeFeatureIncludes.h"
#if _RAKNET_SUPPORT_PacketLogger==1

#ifndef __THREADSAFE_PACKET_LOGGER_H
#define __THREADSAFE_PACKET_LOGGER_H

#include "PacketLogger.h"
#include "SingleProducerConsumer.h"

namespace SLNet
{

/// \ingroup PACKETLOGGER_GROUP
/// \brief Same as PacketLogger, but writes output in the user thread.
class RAK_DLL_EXPORT ThreadsafePacketLogger : public PacketLogger
{
public:
	ThreadsafePacketLogger();
	virtual ~ThreadsafePacketLogger();

	virtual void Update(void);

protected:
	virtual void AddToLog(const char *str);

	DataStructures::SingleProducerConsumer<char*> logMessages;
};

} // namespace SLNet

#endif

#endif // _RAKNET_SUPPORT_*
