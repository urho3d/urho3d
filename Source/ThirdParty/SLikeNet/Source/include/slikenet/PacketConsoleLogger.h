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
/// \brief This will write all incoming and outgoing network messages to the log command parser, which can be accessed through Telnet
///

#include "NativeFeatureIncludes.h"
#if _RAKNET_SUPPORT_LogCommandParser==1 && _RAKNET_SUPPORT_PacketLogger==1

#ifndef __PACKET_CONSOLE_LOGGER_H_
#define __PACKET_CONSOLE_LOGGER_H_

#include "PacketLogger.h"

namespace SLNet
{
/// Forward declarations
class LogCommandParser;

/// \ingroup PACKETLOGGER_GROUP
/// \brief Packetlogger that logs to a remote command console
class RAK_DLL_EXPORT  PacketConsoleLogger : public PacketLogger
{
public:
	PacketConsoleLogger();
	// Writes to the command parser used for logging, which is accessed through a secondary communication layer (such as Telnet or RakNet) - See ConsoleServer.h
	virtual void SetLogCommandParser(LogCommandParser *lcp);
	virtual void WriteLog(const char *str);
protected:
	LogCommandParser *logCommandParser;
};

} // namespace SLNet

#endif

#endif // _RAKNET_SUPPORT_*
