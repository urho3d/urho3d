/*
 *  Original work: Copyright (c) 2014, Oculus VR, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the BSD-style license found in the
 *  RakNet License.txt file in the licenses directory of this source tree. An additional grant 
 *  of patent rights can be found in the RakNet Patents.txt file in the same directory.
 *
 *
 *  Modified work: Copyright (c) 2016-2017, SLikeSoft UG (haftungsbeschränkt)
 *
 *  This source code was modified by SLikeSoft. Modifications are licensed under the MIT-style
 *  license found in the license.txt file in the root directory of this source tree.
 */

/// \file
/// \brief This will write all incoming and outgoing network messages to a file
///


#include "NativeFeatureIncludes.h"
#if _RAKNET_SUPPORT_PacketLogger==1

#ifndef __PACKET_FILE_LOGGER_H_
#define __PACKET_FILE_LOGGER_H_

#include "PacketLogger.h"
#include <stdio.h>

namespace SLNet
{

/// \ingroup PACKETLOGGER_GROUP
/// \brief Packetlogger that outputs to a file
class RAK_DLL_EXPORT  PacketFileLogger : public PacketLogger
{
public:
	// GetInstance() and DestroyInstance(instance*)
	STATIC_FACTORY_DECLARATIONS(PacketFileLogger)

	PacketFileLogger();
	virtual ~PacketFileLogger();
	void StartLog(const char *filenamePrefix);
	virtual void WriteLog(const char *str);
protected:
	FILE *packetLogFile;
};

} // namespace SLNet

#endif

#endif // _RAKNET_SUPPORT_*
