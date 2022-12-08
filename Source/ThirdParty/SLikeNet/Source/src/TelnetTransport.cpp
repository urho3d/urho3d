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
#if _RAKNET_SUPPORT_TelnetTransport==1 && _RAKNET_SUPPORT_TCPInterface==1

#include "slikenet/TelnetTransport.h"
#include "slikenet/TCPInterface.h"
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include "slikenet/LinuxStrings.h"
#include "slikenet/linux_adapter.h"
#include "slikenet/osx_adapter.h"

// #define _PRINTF_DEBUG

#define ECHO_INPUT

using namespace SLNet;

STATIC_FACTORY_DEFINITIONS(TelnetTransport,TelnetTransport);

TelnetTransport::TelnetTransport()
{
	tcpInterface=0;
	sendSuffix=0;
	sendPrefix=0;
}
TelnetTransport::~TelnetTransport()
{
	Stop();
	if (sendSuffix)
		rakFree_Ex(sendSuffix, _FILE_AND_LINE_ );
	if (sendPrefix)
		rakFree_Ex(sendPrefix, _FILE_AND_LINE_ );
}
bool TelnetTransport::Start(unsigned short port, bool serverMode)
{
	(void) serverMode;
    AutoAllocate();
	RakAssert(serverMode);
	return tcpInterface->Start(port, 64);
}
void TelnetTransport::Stop(void)
{
	if (tcpInterface==0) return;
	tcpInterface->Stop();
	unsigned i;
	for (i=0; i < remoteClients.Size(); i++)
		SLNet::OP_DELETE(remoteClients[i], _FILE_AND_LINE_);
	remoteClients.Clear(false, _FILE_AND_LINE_);
	SLNet::OP_DELETE(tcpInterface, _FILE_AND_LINE_);
	tcpInterface=0;
}
void TelnetTransport::Send(  SystemAddress systemAddress, const char *data,... )
{
	if (tcpInterface==0) return;

	if (data==0 || data[0]==0)
		return;

	char text[REMOTE_MAX_TEXT_INPUT];
	size_t prefixLength;
	if (sendPrefix)
	{
		strcpy_s(text, sendPrefix);
		prefixLength = strlen(sendPrefix);
	}
	else
	{
		text[0]=0;
		prefixLength=0;
	}
	va_list ap;
	va_start(ap, data);
	vsnprintf_s(text+prefixLength, REMOTE_MAX_TEXT_INPUT-prefixLength, REMOTE_MAX_TEXT_INPUT-prefixLength-1, data, ap);
	va_end(ap);

	if (sendSuffix)
	{
		size_t length = strlen(text);
		size_t availableChars = REMOTE_MAX_TEXT_INPUT-length-1;
		strncat_s(text, sendSuffix, availableChars);
	}

	tcpInterface->Send(text, (unsigned int) strlen(text), systemAddress, false);
}
void TelnetTransport::CloseConnection( SystemAddress systemAddress )
{
	tcpInterface->CloseConnection(systemAddress);
}
Packet* TelnetTransport::Receive( void )
{
	if (tcpInterface==0) return 0;
	Packet *p = tcpInterface->Receive();
	if (p==0)
		return 0;

	/*
	if (p->data[0]==255)
	{
		unsigned i;
		for (i=0; i < p->length; i++)
		{
			RAKNET_DEBUG_PRINTF("%i ", p->data[i]);
		}
		RAKNET_DEBUG_PRINTF("\n");
		tcpInterface->DeallocatePacket(p);
		return 0;
	}
	*/

	// Get this guy's cursor buffer.  This is real bullcrap that I have to do this.
	unsigned i;
	TelnetClient *remoteClient=0;
	for (i=0; i < remoteClients.Size(); i++)
	{
		if (remoteClients[i]->systemAddress==p->systemAddress)
			remoteClient=remoteClients[i];
	}
	//RakAssert(remoteClient);
	if (remoteClient==0)
	{
		tcpInterface->DeallocatePacket(p);
		return 0;
	}


	if (p->length==3 && p->data[0]==27 && p->data[1]==91 && p->data[2]==65)
	{
		if (remoteClient->lastSentTextInput[0])
		{
			// Up arrow, return last string
			for (i=0; remoteClient->textInput[i]; i++)
				remoteClient->textInput[i]=8;
			strcat_s(remoteClient->textInput, remoteClient->lastSentTextInput);
			tcpInterface->Send((const char *)remoteClient->textInput, (unsigned int) strlen(remoteClient->textInput), p->systemAddress, false);
			strcpy_s(remoteClient->textInput,remoteClient->lastSentTextInput);
			remoteClient->cursorPosition=(unsigned int) strlen(remoteClient->textInput);
		}
		
		return 0;
	}


	// 127 is delete - ignore that
	// 9 is tab
	// 27 is escape
	if (p->data[0]>=127 || p->data[0]==9 || p->data[0]==27)
	{
		tcpInterface->DeallocatePacket(p);
		return 0;
	}

	// Hack - I don't know what the hell this is about but cursor keys send 3 characters at a time.  I can block these
	//Up=27,91,65
	//Down=27,91,66
	//Right=27,91,67
	//Left=27,91,68
	if (p->length==3 && p->data[0]==27 && p->data[1]==91 && p->data[2]>=65 && p->data[2]<=68)
	{
		tcpInterface->DeallocatePacket(p);
		return 0;
	}



	// Echo
#ifdef ECHO_INPUT
	tcpInterface->Send((const char *)p->data, p->length, p->systemAddress, false);
#endif

	bool gotLine;
	// Process each character in turn
	for (i=0; i < p->length; i++)
	{

#ifdef ECHO_INPUT
		if (p->data[i]==8)
		{
			char spaceThenBack[2];
			spaceThenBack[0]=' ';
			spaceThenBack[1]=8;
			tcpInterface->Send((const char *)spaceThenBack, 2, p->systemAddress, false);
		}
#endif

		gotLine=ReassembleLine(remoteClient, p->data[i]);
		if (gotLine && remoteClient->textInput[0])
		{

			Packet *reassembledLine = (Packet*) rakMalloc_Ex(sizeof(Packet), _FILE_AND_LINE_);
			reassembledLine->length=(unsigned int) strlen(remoteClient->textInput);
			memcpy(remoteClient->lastSentTextInput, remoteClient->textInput, reassembledLine->length+1);
			RakAssert(reassembledLine->length < REMOTE_MAX_TEXT_INPUT);
			reassembledLine->data= (unsigned char*) rakMalloc_Ex( reassembledLine->length+1, _FILE_AND_LINE_ );
			memcpy(reassembledLine->data, remoteClient->textInput, reassembledLine->length);
#ifdef _PRINTF_DEBUG
			memset(remoteClient->textInput, 0, REMOTE_MAX_TEXT_INPUT);
#endif
			reassembledLine->data[reassembledLine->length]=0;
			reassembledLine->systemAddress=p->systemAddress;
			tcpInterface->DeallocatePacket(p);
			return reassembledLine;
		}
	}

	tcpInterface->DeallocatePacket(p);
	return 0;
}
void TelnetTransport::DeallocatePacket( Packet *packet )
{
	if (tcpInterface==0) return;
	rakFree_Ex(packet->data, _FILE_AND_LINE_ );
	rakFree_Ex(packet, _FILE_AND_LINE_ );
}
SystemAddress TelnetTransport::HasNewIncomingConnection(void)
{
	unsigned i;
	SystemAddress newConnection;
	newConnection = tcpInterface->HasNewIncomingConnection();
	// 03/16/06 Can't force the stupid windows telnet to use line mode or local echo so now I have to track all the remote players and their
	// input buffer
	if (newConnection != UNASSIGNED_SYSTEM_ADDRESS)
	{
		unsigned char command[10];
		// http://www.pcmicro.com/netfoss/RFC857.html
		// IAC WON'T ECHO
		command[0]=255; // IAC
		//command[1]=253; // WON'T
		command[1]=251; // WILL
		command[2]=1; // ECHO
		tcpInterface->Send((const char*)command, 3, newConnection, false);

		/*
		// Tell the other side to use line mode
		// http://www.faqs.org/rfcs/rfc1184.html
		// IAC DO LINEMODE
	//	command[0]=255; // IAC
	//	command[1]=252; // DO
	//	command[2]=34; // LINEMODE
	//	tcpInterface->Send((const char*)command, 3, newConnection);

	*/

		TelnetClient *remoteClient=0;
		for (i=0; i < remoteClients.Size(); i++)
		{
			if (remoteClients[i]->systemAddress==newConnection)
			{
				remoteClient=remoteClients[i];
				remoteClient->cursorPosition=0;
			}
		}

		if (remoteClient==0)
		{
			remoteClient=new TelnetClient;
			remoteClient->lastSentTextInput[0]=0;
			remoteClient->cursorPosition=0;
			remoteClient->systemAddress=newConnection;
#ifdef _PRINTF_DEBUG
			memset(remoteClient->textInput, 0, REMOTE_MAX_TEXT_INPUT);
#endif
		}

		remoteClients.Insert(remoteClient, _FILE_AND_LINE_);
	}
	return newConnection;
}
SystemAddress TelnetTransport::HasLostConnection(void)
{
	SystemAddress systemAddress;
	unsigned i;
	systemAddress=tcpInterface->HasLostConnection();
	if (systemAddress!=UNASSIGNED_SYSTEM_ADDRESS)
	{
		for (i=0; i < remoteClients.Size(); i++)
		{
			if (remoteClients[i]->systemAddress==systemAddress)
			{
				SLNet::OP_DELETE(remoteClients[i], _FILE_AND_LINE_);
				remoteClients[i]=remoteClients[remoteClients.Size()-1];
				remoteClients.RemoveFromEnd();
			}
		}
	}
	return systemAddress;
}
CommandParserInterface* TelnetTransport::GetCommandParser(void)
{
	return 0;
}
void TelnetTransport::SetSendSuffix(const char *suffix)
{
	if (sendSuffix)
	{
		rakFree_Ex(sendSuffix, _FILE_AND_LINE_ );
		sendSuffix=0;
	}
	if (suffix)
	{
		sendSuffix = (char*) rakMalloc_Ex(strlen(suffix)+1, _FILE_AND_LINE_);
		strcpy_s(sendSuffix, strlen(suffix)+1, suffix);
	}
}
void TelnetTransport::SetSendPrefix(const char *prefix)
{
	if (sendPrefix)
	{
		rakFree_Ex(sendPrefix, _FILE_AND_LINE_ );
		sendPrefix=0;
	}
	if (prefix)
	{
		sendPrefix = (char*) rakMalloc_Ex(strlen(prefix)+1, _FILE_AND_LINE_);
		strcpy_s(sendPrefix, strlen(prefix)+1, prefix);
	}
}
void TelnetTransport::AutoAllocate(void)
{
	if (tcpInterface==0)
		tcpInterface=new TCPInterface;
}
bool TelnetTransport::ReassembleLine(TelnetTransport::TelnetClient* remoteClient, unsigned char c)
{
	if (c=='\n')
	{
		remoteClient->textInput[remoteClient->cursorPosition]=0;
		remoteClient->cursorPosition=0;
#ifdef _PRINTF_DEBUG
		RAKNET_DEBUG_PRINTF("[Done] %s\n", remoteClient->textInput);
#endif
		return true;
	}
	else if (c==8) // backspace
	{
		if (remoteClient->cursorPosition>0)
		{
			remoteClient->textInput[--remoteClient->cursorPosition]=0;
#ifdef _PRINTF_DEBUG
			RAKNET_DEBUG_PRINTF("[Back] %s\n", remoteClient->textInput);
#endif
		}
	}
	else if (c>=32 && c <127)
	{
		if (remoteClient->cursorPosition < REMOTE_MAX_TEXT_INPUT)
		{
			remoteClient->textInput[remoteClient->cursorPosition++]=c;
#ifdef _PRINTF_DEBUG
			RAKNET_DEBUG_PRINTF("[Norm] %s\n", remoteClient->textInput);
#endif
		}
	}
	return false;
}

#endif // _RAKNET_SUPPORT_*
