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

#include "slikenet/NativeFeatureIncludes.h"
#if _RAKNET_SUPPORT_LogCommandParser==1

#include "slikenet/LogCommandParser.h"
#include "slikenet/TransportInterface.h"

#include <memory.h>

#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#include "slikenet/LinuxStrings.h"
#include "slikenet/linux_adapter.h"
#include "slikenet/osx_adapter.h"

using namespace SLNet;

STATIC_FACTORY_DEFINITIONS(LogCommandParser,LogCommandParser);

LogCommandParser::LogCommandParser()
{
	RegisterCommand(CommandParserInterface::VARIABLE_NUMBER_OF_PARAMETERS,"Subscribe","[<ChannelName>] - Subscribes to a named channel, or all channels");
	RegisterCommand(CommandParserInterface::VARIABLE_NUMBER_OF_PARAMETERS,"Unsubscribe","[<ChannelName>] - Unsubscribes from a named channel, or all channels");
	memset(channelNames,0,sizeof(channelNames));
}
LogCommandParser::~LogCommandParser()
{
}
bool LogCommandParser::OnCommand(const char *command, unsigned numParameters, char **parameterList, TransportInterface *transport, const SystemAddress &systemAddress, const char *originalString)
{
	(void) originalString;

	if (strcmp(command, "Subscribe")==0)
	{
		unsigned channelIndex;
		if (numParameters==0)
		{
			Subscribe(systemAddress, 0);
			transport->Send(systemAddress, "Subscribed to all channels.\r\n");
		}
		else if (numParameters==1)
		{
			if ((channelIndex=Subscribe(systemAddress, parameterList[0]))!=(unsigned)-1)
			{
				transport->Send(systemAddress, "You are now subscribed to channel %s.\r\n", channelNames[channelIndex]);
			}
			else
			{
				transport->Send(systemAddress, "Cannot find channel %s.\r\n", parameterList[0]);
				PrintChannels(systemAddress, transport);
			}
		}
		else
		{
			transport->Send(systemAddress, "Subscribe takes either 0 or 1 parameters.\r\n");
		}
	}
	else if (strcmp(command, "Unsubscribe")==0)
	{
		unsigned channelIndex;
		if (numParameters==0)
		{
			Unsubscribe(systemAddress, 0);
			transport->Send(systemAddress, "Unsubscribed from all channels.\r\n");
		}
		else if (numParameters==1)
		{
			if ((channelIndex=Unsubscribe(systemAddress, parameterList[0]))!=(unsigned)-1)
			{
				transport->Send(systemAddress, "You are now unsubscribed from channel %s.\r\n", channelNames[channelIndex]);
			}
			else
			{
				transport->Send(systemAddress, "Cannot find channel %s.\r\n", parameterList[0]);
				PrintChannels(systemAddress, transport);
			}
		}
		else
		{
			transport->Send(systemAddress, "Unsubscribe takes either 0 or 1 parameters.\r\n");
		}
	}

	return true;
}
const char *LogCommandParser::GetName(void) const
{
	return "Logger";
}
void LogCommandParser::SendHelp(TransportInterface *transport, const SystemAddress &systemAddress)
{
	transport->Send(systemAddress, "The logger will accept user log data via the Log(...) function.\r\n");
	transport->Send(systemAddress, "Each log is associated with a named channel.\r\n");
	transport->Send(systemAddress, "You can subscribe to or unsubscribe from named channels.\r\n");
	PrintChannels(systemAddress, transport);
}
void LogCommandParser::AddChannel(const char *channelName)
{
	unsigned channelIndex=0;
	channelIndex = GetChannelIndexFromName(channelName);
	// Each channel can only be added once.
	RakAssert(channelIndex==(unsigned)-1);

	unsigned i;
	for (i=0; i < 32; i++)
	{
		if (channelNames[i]==0)
		{
			// Assuming a persistent static string.
			channelNames[i]=channelName;
			return;
		}
	}

	// No more available channels - max 32 with this implementation where I save subscribed channels with bit operations
	RakAssert(0);
}
void LogCommandParser::WriteLog(const char *channelName, const char *format, ...)
{
	if (channelName==0 || format==0)
		return;

	unsigned channelIndex;
	channelIndex = GetChannelIndexFromName(channelName);
	if (channelIndex==(unsigned)-1)
	{
		AddChannel(channelName);
	}

	char text[REMOTE_MAX_TEXT_INPUT];
	va_list ap;
	va_start(ap, format);
	vsnprintf_s(text, REMOTE_MAX_TEXT_INPUT-1, format, ap);
	va_end(ap);

	// Make sure that text ends in \r\n
	int textLen;
	textLen=(int)strlen(text);
	if (textLen==0)
		return;
	if (text[textLen-1]=='\n')
	{
		text[textLen-1]=0;
	}
	if (textLen < REMOTE_MAX_TEXT_INPUT-4)
		strcat_s(text, "\r\n");
	else
	{
		text[textLen-3]='\r';
		text[textLen-2]='\n';
		text[textLen-1]=0;
	}

	// For each user that subscribes to this channel, send to them.
	unsigned i;
	for (i=0; i < remoteUsers.Size(); i++)
	{
		if (remoteUsers[i].channels & (1 << channelIndex))
		{
			trans->Send(remoteUsers[i].systemAddress, text);
		}
	}
}
void LogCommandParser::PrintChannels(const SystemAddress &systemAddress, TransportInterface *transport) const
{
	unsigned i;
	bool anyChannels=false;
	transport->Send(systemAddress, "CHANNELS:\r\n");
	for (i=0; i < 32; i++)
	{
		if (channelNames[i])
		{
			transport->Send(systemAddress, "%i. %s\r\n", i+1,channelNames[i]);
			anyChannels=true;
		}
	}
	if (anyChannels==false)
		transport->Send(systemAddress, "None.\r\n");
}
void LogCommandParser::OnNewIncomingConnection(const SystemAddress &systemAddress, TransportInterface *transport)
{
	(void) systemAddress;
	(void) transport;
}
void LogCommandParser::OnConnectionLost(const SystemAddress &systemAddress, TransportInterface *transport)
{
	(void) transport;
	Unsubscribe(systemAddress, 0);
}
unsigned LogCommandParser::Unsubscribe(const SystemAddress &systemAddress, const char *channelName)
{
	unsigned i;
	for (i=0; i < remoteUsers.Size(); i++)
	{
		if (remoteUsers[i].systemAddress==systemAddress)
		{
			if (channelName==0)
			{
				// Unsubscribe from all and delete this user.
				remoteUsers[i]=remoteUsers[remoteUsers.Size()-1];
				remoteUsers.RemoveFromEnd();
				return 0;
			}
			else
			{
				unsigned channelIndex;
				channelIndex = GetChannelIndexFromName(channelName);
				if (channelIndex!=(unsigned)-1)
				{
					remoteUsers[i].channels&=0xFFFF ^ (1<<channelIndex); // Unset this bit
				}
				return channelIndex;
			}
		}
	}
	return (unsigned)-1;
}
unsigned LogCommandParser::Subscribe(const SystemAddress &systemAddress, const char *channelName)
{
	unsigned i;
	unsigned channelIndex=(unsigned)-1;
	if (channelName)
	{
		channelIndex = GetChannelIndexFromName(channelName);
		if (channelIndex==(unsigned)-1)
			return channelIndex;
	}

	for (i=0; i < remoteUsers.Size(); i++)
	{
		if (remoteUsers[i].systemAddress==systemAddress)
		{
			if (channelName)
				remoteUsers[i].channels|=1<<channelIndex; // Set this bit for an existing user
			else
				remoteUsers[i].channels=0xFFFF;
			return channelIndex;
		}
	}

	// Make a new user
	SystemAddressAndChannel newUser;
	newUser.systemAddress = systemAddress;
	if (channelName)
		newUser.channels=1<<channelIndex;
	else
		newUser.channels=0xFFFF;
	remoteUsers.Insert(newUser, _FILE_AND_LINE_);
	return channelIndex;
}
unsigned LogCommandParser::GetChannelIndexFromName(const char *channelName)
{
	unsigned i;
	for (i=0; i < 32; i++)
	{
		if (channelNames[i]==0)
			return (unsigned) -1;

		if (_stricmp(channelNames[i], channelName)==0)
			return i;
	}
	return (unsigned)-1;
}

void LogCommandParser::OnTransportChange(TransportInterface *transport)
{
	// I don't want users to have to pass TransportInterface *transport to Log.
	trans=transport;
}

#endif // _RAKNET_SUPPORT_*
