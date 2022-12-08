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

/// \file
/// \brief This will write all incoming and outgoing network messages to the local console screen.  See derived functions for other outputs
///


#include "NativeFeatureIncludes.h"
#if _RAKNET_SUPPORT_PacketLogger==1

#ifndef __PACKET_LOGGER_H
#define __PACKET_LOGGER_H

#include "types.h"
#include "PluginInterface2.h"
#include "Export.h"

namespace SLNet
{
/// Forward declarations
class RakPeerInterface;

/// \defgroup PACKETLOGGER_GROUP PacketLogger
/// \brief Print out incoming messages to a target destination
/// \details
/// \ingroup PLUGINS_GROUP

/// \brief Writes incoming and outgoing messages to the screen.
/// This will write all incoming and outgoing messages to the console window, or to a file if you override it and give it this functionality.
/// \ingroup PACKETLOGGER_GROUP
class RAK_DLL_EXPORT PacketLogger : public PluginInterface2
{
public:
	// GetInstance() and DestroyInstance(instance*)
	STATIC_FACTORY_DECLARATIONS(PacketLogger)

	PacketLogger();
	virtual ~PacketLogger();

	// Translate the supplied parameters into an output line - overloaded version that takes a MessageIdentifier
	// and translates it into a string (numeric or textual representation based on printId); this calls the
	// second version which takes a const char* argument for the messageIdentifier
	virtual void FormatLine(char* into, size_t intoLength, const char* dir, const char* type, unsigned int reliableMessageNumber, unsigned int frame
		, unsigned char id, const BitSize_t bitLen, unsigned long long time, const SystemAddress& local, const SystemAddress& remote,
		unsigned int splitPacketId, unsigned int splitPacketIndex, unsigned int splitPacketCount, unsigned int orderingIndex);
	virtual void FormatLine(char* into, const char* dir, const char* type, unsigned int reliableMessageNumber, unsigned int frame
		, unsigned char id, const BitSize_t bitLen, unsigned long long time, const SystemAddress& local, const SystemAddress& remote,
		unsigned int splitPacketId, unsigned int splitPacketIndex, unsigned int splitPacketCount, unsigned int orderingIndex);
	virtual void FormatLine(char* into, size_t intoLength, const char* dir, const char* type, unsigned int reliableMessageNumber, unsigned int frame
		, const char* idToPrint, const BitSize_t bitLen, unsigned long long time, const SystemAddress& local, const SystemAddress& remote,
		unsigned int splitPacketId, unsigned int splitPacketIndex, unsigned int splitPacketCount, unsigned int orderingIndex);
	virtual void FormatLine(char* into, const char* dir, const char* type, unsigned int reliableMessageNumber, unsigned int frame
		, const char* idToPrint, const BitSize_t bitLen, unsigned long long time, const SystemAddress& local, const SystemAddress& remote,
		unsigned int splitPacketId, unsigned int splitPacketIndex, unsigned int splitPacketCount, unsigned int orderingIndex);

	/// Events on low level sends and receives.  These functions may be called from different threads at the same time.
	virtual void OnDirectSocketSend(const char *data, const BitSize_t bitsUsed, SystemAddress remoteSystemAddress);
	virtual void OnDirectSocketReceive(const char *data, const BitSize_t bitsUsed, SystemAddress remoteSystemAddress);
	virtual void OnReliabilityLayerNotification(const char *errorMessage, const BitSize_t bitsUsed, SystemAddress remoteSystemAddress, bool isError);
	virtual void OnInternalPacket(InternalPacket *internalPacket, unsigned frameNumber, SystemAddress remoteSystemAddress, SLNet::TimeMS time, int isSend);
	virtual void OnAck(unsigned int messageNumber, SystemAddress remoteSystemAddress, SLNet::TimeMS time);
	virtual void OnPushBackPacket(const char *data, const BitSize_t bitsUsed, SystemAddress remoteSystemAddress);

	/// Logs out a header for all the data
	virtual void LogHeader(void);

	/// Override this to log strings to wherever.  Log should be threadsafe
	virtual void WriteLog(const char *str);

	// Write informational messages
	virtual void WriteMiscellaneous(const char *type, const char *msg);


	// Set to true to print ID_* instead of numbers
	virtual void SetPrintID(bool print);
	// Print or hide acks (clears up the screen not to print them but is worse for debugging)
	virtual void SetPrintAcks(bool print);

	/// Prepend this string to output logs.
	virtual void SetPrefix(const char *_prefix);

	/// Append this string to output logs. (newline is useful here)
	virtual void SetSuffix(const char *_suffix);
	static const char* BaseIDTOString(unsigned char Id);

	/// Log the direct sends and receives or not. Default true
	void SetLogDirectMessages(bool send);
protected:

	virtual bool UsesReliabilityLayer(void) const {return true;}
	const char* IDTOString(unsigned char Id);
	virtual void AddToLog(const char *str);
	// Users should override this
	virtual const char* UserIDTOString(unsigned char Id);
	void GetLocalTime(char buffer[128]);
	bool logDirectMessages;

	bool printId, printAcks;
	char prefix[256];
	char suffix[256];
};

} // namespace SLNet

#endif

#endif // _RAKNET_SUPPORT_*
