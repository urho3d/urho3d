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
#if _RAKNET_SUPPORT_PacketLogger==1

#include "slikenet/PacketLogger.h"
#include "slikenet/BitStream.h"
#include "slikenet/DS_List.h"
#include "slikenet/InternalPacket.h"
#include "slikenet/peerinterface.h"
#include "slikenet/MessageIdentifiers.h"
#include "slikenet/StringCompressor.h"
#include "slikenet/GetTime.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "slikenet/Itoa.h"
#include <time.h>
#include "slikenet/SocketIncludes.h"
#include "slikenet/gettimeofday.h"
#include "slikenet/linux_adapter.h"
#include "slikenet/osx_adapter.h"

using namespace SLNet;

STATIC_FACTORY_DEFINITIONS(PacketLogger,PacketLogger);

PacketLogger::PacketLogger()
{
	printId=true;
	printAcks=true;
	prefix[0]=0;
	suffix[0]=0;
	logDirectMessages=true;
}
PacketLogger::~PacketLogger()
{
}
void PacketLogger::FormatLine(char* into, const char* dir, const char* type, unsigned int reliableMessageNumber, unsigned int frame
	, unsigned char id, const BitSize_t bitLen, unsigned long long time, const SystemAddress& local, const SystemAddress& remote,
	unsigned int splitPacketId, unsigned int splitPacketIndex, unsigned int splitPacketCount, unsigned int orderingIndex)
{
	char numericID[16];
	const char* idToPrint = NULL;
	if (printId)
	{
		if (splitPacketCount > 0 && splitPacketCount != (unsigned int)-1)
			idToPrint = "(SPLIT PACKET)";
		else
			idToPrint = IDTOString(id);
	}
	// If printId is false, idToPrint will be NULL, as it will
	// in the case of an unrecognized id. Testing printId for false
	// would just be redundant.
	if (idToPrint == NULL)
	{
		sprintf_s(numericID, "%5u", id);
		idToPrint = numericID;
	}

	FormatLine(into, dir, type, reliableMessageNumber, frame, idToPrint, bitLen, time, local, remote, splitPacketId, splitPacketIndex, splitPacketCount, orderingIndex);
}
void PacketLogger::FormatLine(
char* into, size_t intoLength, const char* dir, const char* type, unsigned int reliableMessageNumber, unsigned int frame, unsigned char id
, const BitSize_t bitLen, unsigned long long time, const SystemAddress& local, const SystemAddress& remote,
unsigned int splitPacketId, unsigned int splitPacketIndex, unsigned int splitPacketCount, unsigned int orderingIndex)
{
	char numericID[16];
	const char* idToPrint = NULL;
	if(printId)
	{
		if (splitPacketCount>0 && splitPacketCount!=(unsigned int)-1)
			idToPrint="(SPLIT PACKET)";
		else
			idToPrint =	IDTOString(id);
	}
	// If printId is false, idToPrint will be NULL, as it will
	// in the case of an unrecognized id. Testing printId for false
	// would just be redundant.
	if(idToPrint == NULL)
	{
		sprintf_s(numericID, "%5u", id);
		idToPrint = numericID;
	}

	FormatLine(into, intoLength, dir, type, reliableMessageNumber, frame, idToPrint, bitLen, time, local, remote,splitPacketId,splitPacketIndex,splitPacketCount, orderingIndex);
}

void PacketLogger::FormatLine(
char* into, size_t intoLength, const char* dir, const char* type, unsigned int reliableMessageNumber, unsigned int frame, const char* idToPrint
, const BitSize_t bitLen, unsigned long long time, const SystemAddress& local, const SystemAddress& remote,
unsigned int splitPacketId, unsigned int splitPacketIndex, unsigned int splitPacketCount, unsigned int orderingIndex)
{
	char str1[64], str2[62];
	local.ToString(true, str1, static_cast<size_t>(64));
	remote.ToString(true, str2, static_cast<size_t>(62));
	char localtime[128];
	GetLocalTime(localtime);
	char str3[64];
	if (reliableMessageNumber==(unsigned int)-1)
	{
		str3[0]='N';
		str3[1]='/';
		str3[2]='A';
		str3[3]=0;
	}
	else
	{
		sprintf_s(str3,"%5u",reliableMessageNumber);
	}

	sprintf_s(into, intoLength, "%s,%s%s,%s,%s,%5u,%s,%u,%" PRINTF_64_BIT_MODIFIER "u,%s,%s,%i,%i,%i,%i,%s,"
					, localtime
					, prefix
					, dir
					, type
					, str3
					, frame
					, idToPrint
					, bitLen
					, time
					, str1
					, str2
					, splitPacketId
					, splitPacketIndex
					, splitPacketCount
					, orderingIndex
					, suffix
					);
}
void PacketLogger::FormatLine(char* into, const char* dir, const char* type, unsigned int reliableMessageNumber, unsigned int frame
	, const char* idToPrint, const BitSize_t bitLen, unsigned long long time, const SystemAddress& local, const SystemAddress& remote,
	unsigned int splitPacketId, unsigned int splitPacketIndex, unsigned int splitPacketCount, unsigned int orderingIndex)
{
	char str1[64], str2[62];
	local.ToString(true, str1, static_cast<size_t>(64));
	remote.ToString(true, str2, static_cast<size_t>(62));
	char localtime[128];
	GetLocalTime(localtime);
	char str3[64];
	if (reliableMessageNumber == (unsigned int)-1)
	{
		str3[0] = 'N';
		str3[1] = '/';
		str3[2] = 'A';
		str3[3] = 0;
	}
	else
	{
		sprintf_s(str3, "%5u", reliableMessageNumber);
	}

#pragma warning(push)
#pragma warning(disable:4996)
	sprintf(into, "%s,%s%s,%s,%s,%5u,%s,%u,%" PRINTF_64_BIT_MODIFIER "u,%s,%s,%i,%i,%i,%i,%s,"
		, localtime
		, prefix
		, dir
		, type
		, str3
		, frame
		, idToPrint
		, bitLen
		, time
		, str1
		, str2
		, splitPacketId
		, splitPacketIndex
		, splitPacketCount
		, orderingIndex
		, suffix
	);
#pragma warning(pop)
}
void PacketLogger::OnDirectSocketSend(const char *data, const BitSize_t bitsUsed, SystemAddress remoteSystemAddress)
{
	if (logDirectMessages==false)
		return;

	char str[256];
	FormatLine(str, 256, "Snd", "Raw", 0, 0, data[0], bitsUsed, SLNet::GetTimeMS(), rakPeerInterface->GetExternalID(remoteSystemAddress), remoteSystemAddress, (unsigned int)-1,(unsigned int)-1,(unsigned int)-1,(unsigned int)-1);
	AddToLog(str);
}

void PacketLogger::LogHeader(void)
{
	// Last 5 are splitpacket id, split packet index, split packet count, ordering index, suffix
	AddToLog("Clock,S|R,Typ,Reliable#,Frm #,PktID,BitLn,Time     ,Local IP:Port   ,RemoteIP:Port,SPID,SPIN,SPCO,OI,Suffix,Miscellaneous\n");
}
void PacketLogger::OnDirectSocketReceive(const char *data, const BitSize_t bitsUsed, SystemAddress remoteSystemAddress)
{
	if (logDirectMessages==false)
		return;

	char str[256];
	FormatLine(str, 256, "Rcv", "Raw", 0, 0, data[0], bitsUsed, SLNet::GetTime(), rakPeerInterface->GetInternalID(UNASSIGNED_SYSTEM_ADDRESS), remoteSystemAddress,(unsigned int)-1,(unsigned int)-1,(unsigned int)-1,(unsigned int)-1);
	AddToLog(str);
}
void PacketLogger::OnReliabilityLayerNotification(const char *errorMessage, const BitSize_t bitsUsed, SystemAddress remoteSystemAddress, bool isError)
{
	char str[1024];
	char *type;
	if (isError)
		type=(char*) "RcvErr";
	else
		type=(char*) "RcvWrn";
	FormatLine(str, 1024, type, errorMessage, 0, 0, "", bitsUsed, SLNet::GetTime(), rakPeerInterface->GetInternalID(UNASSIGNED_SYSTEM_ADDRESS), remoteSystemAddress,(unsigned int)-1,(unsigned int)-1,(unsigned int)-1,(unsigned int)-1);
	AddToLog(str);
	RakAssert(isError==false);
}
void PacketLogger::OnAck(unsigned int messageNumber, SystemAddress remoteSystemAddress, SLNet::TimeMS time)
{
	char str[256];
	char str1[64], str2[62];
	SystemAddress localSystemAddress = rakPeerInterface->GetExternalID(remoteSystemAddress);
	localSystemAddress.ToString(true, str1, static_cast<size_t>(64));
	remoteSystemAddress.ToString(true, str2, static_cast<size_t>(62));
	char localtime[128];
	GetLocalTime(localtime);

	sprintf_s(str, "%s,Rcv,Ack,%i,,,,%" PRINTF_64_BIT_MODIFIER "u,%s,%s,,,,,,"
					, localtime
					, messageNumber
					, (unsigned long long) time
					, str1
					, str2
					);
	AddToLog(str);
}
void PacketLogger::OnPushBackPacket(const char *data, const BitSize_t bitsUsed, SystemAddress remoteSystemAddress)
{
	char str[256];
	char str1[64], str2[62];
	SystemAddress localSystemAddress = rakPeerInterface->GetExternalID(remoteSystemAddress);
	localSystemAddress.ToString(true, str1, static_cast<size_t>(64));
	remoteSystemAddress.ToString(true, str2, static_cast<size_t>(62));
	SLNet::TimeMS time = SLNet::GetTimeMS();
	char localtime[128];
	GetLocalTime(localtime);

	sprintf_s(str, "%s,Lcl,PBP,,,%s,%i,%" PRINTF_64_BIT_MODIFIER "u,%s,%s,,,,,,"
					, localtime
					, BaseIDTOString(data[0])
					, bitsUsed
					, (unsigned long long) time
					, str1
					, str2
					);
	AddToLog(str);
}
void PacketLogger::OnInternalPacket(InternalPacket *internalPacket, unsigned frameNumber, SystemAddress remoteSystemAddress, SLNet::TimeMS time, int isSend)
{
	char str[256];
	const char *sendTypes[] =
	{
		"Rcv",
		"Snd",
		"Err1",
		"Err2",
		"Err3",
		"Err4",
		"Err5",
		"Err6",
	};
	const char *sendType = sendTypes[isSend];
	SystemAddress localSystemAddress = rakPeerInterface->GetExternalID(remoteSystemAddress);

	unsigned int reliableMessageNumber;
	if (internalPacket->reliability==UNRELIABLE || internalPacket->reliability==UNRELIABLE_SEQUENCED || internalPacket->reliability==UNRELIABLE_WITH_ACK_RECEIPT)
		reliableMessageNumber=(unsigned int)-1;
	else
		reliableMessageNumber=internalPacket->reliableMessageNumber;

	if (internalPacket->data[0]==ID_TIMESTAMP)
	{
		FormatLine(str, 256, sendType, "Tms", reliableMessageNumber, frameNumber, internalPacket->data[1+sizeof(SLNet::Time)], internalPacket->dataBitLength, (unsigned long long)time, localSystemAddress, remoteSystemAddress, internalPacket->splitPacketId, internalPacket->splitPacketIndex, internalPacket->splitPacketCount, internalPacket->orderingIndex);
	}
	else
	{
		FormatLine(str, 256, sendType, "Nrm", reliableMessageNumber, frameNumber, internalPacket->data[0], internalPacket->dataBitLength, (unsigned long long)time, localSystemAddress, remoteSystemAddress, internalPacket->splitPacketId, internalPacket->splitPacketIndex, internalPacket->splitPacketCount, internalPacket->orderingIndex);
	}

	AddToLog(str);
}
void PacketLogger::AddToLog(const char *str)
{
	WriteLog(str);
}
void PacketLogger::WriteLog(const char *str)
{
	RAKNET_DEBUG_PRINTF("%s\n", str);
}
void PacketLogger::WriteMiscellaneous(const char *type, const char *msg)
{
	char str[1024];
	char str1[64];
	SystemAddress localSystemAddress = rakPeerInterface->GetInternalID();
	localSystemAddress.ToString(true, str1, static_cast<size_t>(64));
	SLNet::TimeMS time = SLNet::GetTimeMS();
	char localtime[128];
	GetLocalTime(localtime);

	sprintf_s(str, "%s,Lcl,%s,,,,,%" PRINTF_64_BIT_MODIFIER "u,%s,,,,,,,%s"
					, localtime
					, type
					, (unsigned long long) time
					, str1
					, msg
					);

	AddToLog(msg);
}
void PacketLogger::SetPrintID(bool print)
{
	printId=print;
}
void PacketLogger::SetPrintAcks(bool print)
{
	printAcks=print;
}
const char* PacketLogger::BaseIDTOString(unsigned char Id)
{
	if (Id >= ID_USER_PACKET_ENUM)
        return 0;

	const char *IDTable[((int)ID_USER_PACKET_ENUM)+1]=
	{
		"ID_CONNECTED_PING",
		"ID_UNCONNECTED_PING",
		"ID_UNCONNECTED_PING_OPEN_CONNECTIONS",
		"ID_CONNECTED_PONG",
		"ID_DETECT_LOST_CONNECTIONS",
		"ID_OPEN_CONNECTION_REQUEST_1",
		"ID_OPEN_CONNECTION_REPLY_1",
		"ID_OPEN_CONNECTION_REQUEST_2",
		"ID_OPEN_CONNECTION_REPLY_2",
		"ID_CONNECTION_REQUEST",
		"ID_REMOTE_SYSTEM_REQUIRES_PUBLIC_KEY",
		"ID_OUR_SYSTEM_REQUIRES_SECURITY",
		"ID_PUBLIC_KEY_MISMATCH",
		"ID_OUT_OF_BAND_INTERNAL",
		"ID_SND_RECEIPT_ACKED",
		"ID_SND_RECEIPT_LOSS",
		"ID_CONNECTION_REQUEST_ACCEPTED",
		"ID_CONNECTION_ATTEMPT_FAILED",
		"ID_ALREADY_CONNECTED",
		"ID_NEW_INCOMING_CONNECTION",
		"ID_NO_FREE_INCOMING_CONNECTIONS",
		"ID_DISCONNECTION_NOTIFICATION",
		"ID_CONNECTION_LOST",
		"ID_CONNECTION_BANNED",
		"ID_INVALID_PASSWORD",
		"ID_INCOMPATIBLE_PROTOCOL_VERSION",
		"ID_IP_RECENTLY_CONNECTED",
		"ID_TIMESTAMP",
		"ID_UNCONNECTED_PONG",
		"ID_ADVERTISE_SYSTEM",
		"ID_DOWNLOAD_PROGRESS",
		"ID_REMOTE_DISCONNECTION_NOTIFICATION",
		"ID_REMOTE_CONNECTION_LOST",
		"ID_REMOTE_NEW_INCOMING_CONNECTION",
		"ID_FILE_LIST_TRANSFER_HEADER",
		"ID_FILE_LIST_TRANSFER_FILE",
		"ID_FILE_LIST_REFERENCE_PUSH_ACK",
		"ID_DDT_DOWNLOAD_REQUEST",
		"ID_TRANSPORT_STRING",
		"ID_REPLICA_MANAGER_CONSTRUCTION",
		"ID_REPLICA_MANAGER_SCOPE_CHANGE",
		"ID_REPLICA_MANAGER_SERIALIZE",
		"ID_REPLICA_MANAGER_DOWNLOAD_STARTED",
		"ID_REPLICA_MANAGER_DOWNLOAD_COMPLETE",
		"ID_RAKVOICE_OPEN_CHANNEL_REQUEST",
		"ID_RAKVOICE_OPEN_CHANNEL_REPLY",
		"ID_RAKVOICE_CLOSE_CHANNEL",
		"ID_RAKVOICE_DATA",
		"ID_AUTOPATCHER_GET_CHANGELIST_SINCE_DATE",
		"ID_AUTOPATCHER_CREATION_LIST",
		"ID_AUTOPATCHER_DELETION_LIST",
		"ID_AUTOPATCHER_GET_PATCH",
		"ID_AUTOPATCHER_PATCH_LIST",
		"ID_AUTOPATCHER_REPOSITORY_FATAL_ERROR",
		"ID_AUTOPATCHER_CANNOT_DOWNLOAD_ORIGINAL_UNMODIFIED_FILES",
		"ID_AUTOPATCHER_FINISHED_INTERNAL",
		"ID_AUTOPATCHER_FINISHED",
		"ID_AUTOPATCHER_RESTART_APPLICATION",
		"ID_NAT_PUNCHTHROUGH_REQUEST",
		"ID_NAT_CONNECT_AT_TIME",
		"ID_NAT_GET_MOST_RECENT_PORT",
		"ID_NAT_CLIENT_READY",
		"ID_NAT_TARGET_NOT_CONNECTED",
		"ID_NAT_TARGET_UNRESPONSIVE",
		"ID_NAT_CONNECTION_TO_TARGET_LOST",
		"ID_NAT_ALREADY_IN_PROGRESS",
		"ID_NAT_PUNCHTHROUGH_FAILED",
		"ID_NAT_PUNCHTHROUGH_SUCCEEDED",
		"ID_READY_EVENT_SET",
		"ID_READY_EVENT_UNSET",
		"ID_READY_EVENT_ALL_SET",
		"ID_READY_EVENT_QUERY",
		"ID_LOBBY_GENERAL",
		"ID_RPC_REMOTE_ERROR",
		"ID_RPC_PLUGIN",
		"ID_FILE_LIST_REFERENCE_PUSH",
		"ID_READY_EVENT_FORCE_ALL_SET",
		"ID_ROOMS_EXECUTE_FUNC",
		"ID_ROOMS_LOGON_STATUS",
		"ID_ROOMS_HANDLE_CHANGE",
		"ID_LOBBY2_SEND_MESSAGE",
		"ID_LOBBY2_SERVER_ERROR",
		"ID_FCM2_NEW_HOST",
		"ID_FCM2_REQUEST_FCMGUID",
		"ID_FCM2_RESPOND_CONNECTION_COUNT",
		"ID_FCM2_INFORM_FCMGUID",
		"ID_FCM2_UPDATE_MIN_TOTAL_CONNECTION_COUNT",
		"ID_FCM2_VERIFIED_JOIN_START",
		"ID_FCM2_VERIFIED_JOIN_CAPABLE",
		"ID_FCM2_VERIFIED_JOIN_FAILED",
		"ID_FCM2_VERIFIED_JOIN_ACCEPTED",
		"ID_FCM2_VERIFIED_JOIN_REJECTED",
		"ID_UDP_PROXY_GENERAL",
		"ID_SQLite3_EXEC",
		"ID_SQLite3_UNKNOWN_DB",
		"ID_SQLLITE_LOGGER",
		"ID_NAT_TYPE_DETECTION_REQUEST",
		"ID_NAT_TYPE_DETECTION_RESULT",
		"ID_ROUTER_2_INTERNAL",
		"ID_ROUTER_2_FORWARDING_NO_PATH",
		"ID_ROUTER_2_FORWARDING_ESTABLISHED",
		"ID_ROUTER_2_REROUTED",
		"ID_TEAM_BALANCER_INTERNAL",
		"ID_TEAM_BALANCER_REQUESTED_TEAM_FULL",
		"ID_TEAM_BALANCER_REQUESTED_TEAM_LOCKED",
		"ID_TEAM_BALANCER_TEAM_REQUESTED_CANCELLED",
		"ID_TEAM_BALANCER_TEAM_ASSIGNED",
		"ID_LIGHTSPEED_INTEGRATION",
		"ID_XBOX_LOBBY",
		"ID_TWO_WAY_AUTHENTICATION_INCOMING_CHALLENGE_SUCCESS",
		"ID_TWO_WAY_AUTHENTICATION_OUTGOING_CHALLENGE_SUCCESS",
		"ID_TWO_WAY_AUTHENTICATION_INCOMING_CHALLENGE_FAILURE",
		"ID_TWO_WAY_AUTHENTICATION_OUTGOING_CHALLENGE_FAILURE",
		"ID_TWO_WAY_AUTHENTICATION_OUTGOING_CHALLENGE_TIMEOUT",
		"ID_TWO_WAY_AUTHENTICATION_NEGOTIATION",
		"ID_CLOUD_POST_REQUEST",
		"ID_CLOUD_RELEASE_REQUEST",
		"ID_CLOUD_GET_REQUEST",
		"ID_CLOUD_GET_RESPONSE",
		"ID_CLOUD_UNSUBSCRIBE_REQUEST",
		"ID_CLOUD_SERVER_TO_SERVER_COMMAND",
		"ID_CLOUD_SUBSCRIPTION_NOTIFICATION",
		"ID_LIB_VOICE",
		"ID_RELAY_PLUGIN",
		"ID_NAT_REQUEST_BOUND_ADDRESSES",
		"ID_NAT_RESPOND_BOUND_ADDRESSES",
		"ID_FCM2_UPDATE_USER_CONTEXT",
		"ID_RESERVED_3",
		"ID_RESERVED_4",
		"ID_RESERVED_5",
		"ID_RESERVED_6",
		"ID_RESERVED_7",
		"ID_RESERVED_8",
		"ID_RESERVED_9",
		"ID_USER_PACKET_ENUM"
	};

	return (char*)IDTable[Id];
}
const char* PacketLogger::UserIDTOString(unsigned char Id)
{
	// Users should override this
	static char str[256];
	Itoa(Id, str, 10);
	return (const char*) str;
}
const char* PacketLogger::IDTOString(unsigned char Id)
{
	const char *out;
	out=BaseIDTOString(Id);
	if (out)
		return out;
	return UserIDTOString(Id);
}
void PacketLogger::SetPrefix(const char *_prefix)
{
	strncpy_s(prefix, _prefix, 255);
	prefix[255]=0;
}
void PacketLogger::SetSuffix(const char *_suffix)
{
	strncpy_s(suffix, _suffix, 255);
	suffix[255]=0;
}
void PacketLogger::GetLocalTime(char buffer[128])
{
#if defined(_WIN32) && !defined(__GNUC__)  && !defined(__GCCXML__)
    time_t rawtime;
	struct timeval tv;
	// If you get an arror about an incomplete type, just delete this file
	struct timezone tz;
	gettimeofday(&tv, &tz);
	// time ( &rawtime );
	rawtime=tv.tv_sec;

	struct tm timeinfo;
	localtime_s ( &timeinfo, &rawtime );
	strftime (buffer,128,"%x %X",&timeinfo);
	char buff[32];
	sprintf_s(buff, ".%i", tv.tv_usec);
	strcat_s(buffer,128,buff);

	// Commented version puts the time first
	/*
	struct tm timeinfo;
	localtime_s ( &timeinfo, &rawtime );
	strftime (buffer,128,"%X",&timeinfo);
	char buff[32];
	sprintf_s(buff, ".%i ", tv.tv_usec);
	strcat_s(buffer,128,buff);
	char buff2[32];
	strftime (buff2,32,"%x",&timeinfo);
	strcat_s(buffer,128,buff2);
	*/
#else
    buffer[0]=0;
#endif
}
void PacketLogger::SetLogDirectMessages(bool send)
{
	logDirectMessages=send;
}

#endif // _RAKNET_SUPPORT_*
