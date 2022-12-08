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
#if _RAKNET_SUPPORT_ConsoleServer==1

#include "slikenet/ConsoleServer.h"
#include "slikenet/TransportInterface.h"
#include "slikenet/CommandParserInterface.h"
#include <string.h>
#include <stdlib.h>

#define COMMAND_DELINATOR ' '
#define COMMAND_DELINATOR_TOGGLE '"'

#include "slikenet/LinuxStrings.h"
#include "slikenet/linux_adapter.h"
#include "slikenet/osx_adapter.h"

using namespace SLNet;

STATIC_FACTORY_DEFINITIONS(ConsoleServer,ConsoleServer);

ConsoleServer::ConsoleServer()
{
	transport=0;
	password[0]=0;
	prompt=0;
}
ConsoleServer::~ConsoleServer()
{
	if (prompt)
		rakFree_Ex(prompt, _FILE_AND_LINE_);
}
void ConsoleServer::SetTransportProvider(TransportInterface *transportInterface, unsigned short port)
{
	// Replace the current TransportInterface, stopping the old one, if present, and starting the new one.
	if (transportInterface)
	{
		if (transport)
		{
			RemoveCommandParser(transport->GetCommandParser());
			transport->Stop();
		}
		transport=transportInterface;
		transport->Start(port, true);

		unsigned i;
		for (i=0; i < commandParserList.Size(); i++)
			commandParserList[i]->OnTransportChange(transport);

		//  The transport itself might have a command parser - for example password for the RakNet transport
		AddCommandParser(transport->GetCommandParser());
	}
}
void ConsoleServer::AddCommandParser(CommandParserInterface *commandParserInterface)
{
	if (commandParserInterface==0)
		return;

	// Non-duplicate insertion
	unsigned i;
	for (i=0; i < commandParserList.Size(); i++)
	{
		if (commandParserList[i]==commandParserInterface)
			return;

        if (_stricmp(commandParserList[i]->GetName(), commandParserInterface->GetName())==0)
		{
			// Naming conflict between two command parsers
			RakAssert(0);
			return;
		}
	}

	commandParserList.Insert(commandParserInterface, _FILE_AND_LINE_);
	if (transport)
		commandParserInterface->OnTransportChange(transport);
}
void ConsoleServer::RemoveCommandParser(CommandParserInterface *commandParserInterface)
{
	if (commandParserInterface==0)
		return;

	// Overwrite the element we are removing from the back of the list and delete the back of the list
	unsigned i;
	for (i=0; i < commandParserList.Size(); i++)
	{
		if (commandParserList[i]==commandParserInterface)
		{
			commandParserList[i]=commandParserList[commandParserList.Size()-1];
			commandParserList.RemoveFromEnd();
			return;
		}
	}
}
void ConsoleServer::Update(void)
{
	unsigned i;
	char *parameterList[20]; // Up to 20 parameters
	unsigned numParameters;
	SLNet::SystemAddress newOrLostConnectionId;
	SLNet::Packet *p;
	SLNet::RegisteredCommand rc;

	p = transport->Receive();
	newOrLostConnectionId=transport->HasNewIncomingConnection();

	if (newOrLostConnectionId!=UNASSIGNED_SYSTEM_ADDRESS)
	{
		for (i=0; i < commandParserList.Size(); i++)
		{
			commandParserList[i]->OnNewIncomingConnection(newOrLostConnectionId, transport);
		}

		transport->Send(newOrLostConnectionId, "Connected to remote command console.\r\nType 'help' for help.\r\n");
		ListParsers(newOrLostConnectionId);
		ShowPrompt(newOrLostConnectionId);
	}

	newOrLostConnectionId=transport->HasLostConnection();
	if (newOrLostConnectionId!=UNASSIGNED_SYSTEM_ADDRESS)
	{
		for (i=0; i < commandParserList.Size(); i++)
			commandParserList[i]->OnConnectionLost(newOrLostConnectionId, transport);
	}

	while (p)
	{
		bool commandParsed=false;
		char copy[REMOTE_MAX_TEXT_INPUT];
		memcpy(copy, p->data, p->length);
		copy[p->length]=0;
		SLNet::CommandParserInterface::ParseConsoleString((char*)p->data, COMMAND_DELINATOR, COMMAND_DELINATOR_TOGGLE, &numParameters, parameterList, 20); // Up to 20 parameters
		if (numParameters==0)
		{
			transport->DeallocatePacket(p);
			p = transport->Receive();
			continue;
		}
		if (_stricmp(*parameterList, "help")==0 && numParameters<=2)
		{
			// Find the parser specified and display help for it
			if (numParameters==1)
			{
				transport->Send(p->systemAddress, "\r\nINSTRUCTIONS:\r\n");
				transport->Send(p->systemAddress, "Enter commands on your keyboard, using spaces to delineate parameters.\r\n");
				transport->Send(p->systemAddress, "You can use quotation marks to toggle space delineation.\r\n");
				transport->Send(p->systemAddress, "You can connect multiple times from the same computer.\r\n");
				transport->Send(p->systemAddress, "You can direct commands to a parser by prefixing the parser name or number.\r\n");
				transport->Send(p->systemAddress, "COMMANDS:\r\n");
				transport->Send(p->systemAddress, "help                                        Show this display.\r\n");
				transport->Send(p->systemAddress, "help <ParserName>                           Show help on a particular parser.\r\n");
				transport->Send(p->systemAddress, "help <CommandName>                          Show help on a particular command.\r\n");
				transport->Send(p->systemAddress, "quit                                        Disconnects from the server.\r\n");
				transport->Send(p->systemAddress, "[<ParserName>]   <Command> [<Parameters>]   Execute a command\r\n");
				transport->Send(p->systemAddress, "[<ParserNumber>] <Command> [<Parameters>]   Execute a command\r\n");
				ListParsers(p->systemAddress);
				//ShowPrompt(p->systemAddress);
			}
			else // numParameters == 2, including the help tag
			{
				for (i=0; i < commandParserList.Size(); i++)
				{
					if (_stricmp(parameterList[1], commandParserList[i]->GetName())==0)
					{
						commandParsed=true;
						commandParserList[i]->SendHelp(transport, p->systemAddress);
						transport->Send(p->systemAddress, "COMMAND LIST:\r\n");
						commandParserList[i]->SendCommandList(transport, p->systemAddress);
						transport->Send(p->systemAddress, "\r\n");
						break;
					}
				}

				if (commandParsed==false)
				{
					// Try again, for all commands for all parsers.
					SLNet::RegisteredCommand rc2;
					for (i=0; i < commandParserList.Size(); i++)
					{
						if (commandParserList[i]->GetRegisteredCommand(parameterList[1], &rc2))
						{
							if (rc2.parameterCount== SLNet::CommandParserInterface::VARIABLE_NUMBER_OF_PARAMETERS)
								transport->Send(p->systemAddress, "(Variable parms): %s %s\r\n", rc2.command, rc2.commandHelp);
							else
								transport->Send(p->systemAddress, "(%i parms): %s %s\r\n", rc2.parameterCount, rc2.command, rc2.commandHelp);
							commandParsed=true;
							break;
						}
					}
				}

				if (commandParsed==false)
				{
					// Don't know what to do
					transport->Send(p->systemAddress, "Unknown help topic: %s.\r\n", parameterList[1]);
				}
				//ShowPrompt(p->systemAddress);
			}
		}
		else if (_stricmp(*parameterList, "quit")==0 && numParameters==1)
		{
			transport->Send(p->systemAddress, "Goodbye!\r\n");
			transport->CloseConnection(p->systemAddress);
		}
		else
		{
			bool tryAllParsers=true;
			bool failed=false;

			if (numParameters >=2) // At minimum <CommandParserName> <Command>
			{
				unsigned commandParserIndex=(unsigned)-1;
				// Prefixing with numbers directs to a particular parser
				if (**parameterList>='0' && **parameterList<='9')
				{
					commandParserIndex=atoi(*parameterList); // Use specified parser unless it's an invalid number
					commandParserIndex--; // Subtract 1 since we displayed numbers starting at index+1
					if (commandParserIndex >= commandParserList.Size())
					{
						transport->Send(p->systemAddress, "Invalid index.\r\n");
						failed=true;
					}
				}
				else
				{
					// // Prefixing with the name of a command parser directs to that parser.  See if the first word matches a parser
					for (i=0; i < commandParserList.Size(); i++)
					{
						if (_stricmp(parameterList[0], commandParserList[i]->GetName())==0)
						{
							commandParserIndex=i; // Matches parser at index i
							break;
						}
					}
				}

				if (failed==false)
				{
					// -1 means undirected, so otherwise this is directed to a target
					if (commandParserIndex!=(unsigned)-1)
					{
						// Only this parser should use this command
						tryAllParsers=false;
						if (commandParserList[commandParserIndex]->GetRegisteredCommand(parameterList[1], &rc))
						{
							commandParsed=true;
							if (rc.parameterCount==CommandParserInterface::VARIABLE_NUMBER_OF_PARAMETERS || rc.parameterCount==numParameters-2)
								commandParserList[commandParserIndex]->OnCommand(rc.command, numParameters-2, parameterList+2, transport, p->systemAddress, copy);
							else
								transport->Send(p->systemAddress, "Invalid parameter count.\r\n(%i parms): %s %s\r\n", rc.parameterCount, rc.command, rc.commandHelp);
						}
					}
				}
			}

			if (failed == false && tryAllParsers)
			{
				for (i=0; i < commandParserList.Size(); i++)
				{
					// Undirected command.  Try all the parsers to see if they understand the command
					// Pass the 1nd element as the command, and the remainder as the parameter list
					if (commandParserList[i]->GetRegisteredCommand(parameterList[0], &rc))
					{
						commandParsed=true;

						if (rc.parameterCount==CommandParserInterface::VARIABLE_NUMBER_OF_PARAMETERS || rc.parameterCount==numParameters-1)
							commandParserList[i]->OnCommand(rc.command, numParameters-1, parameterList+1, transport, p->systemAddress, copy);
						else
							transport->Send(p->systemAddress, "Invalid parameter count.\r\n(%i parms): %s %s\r\n", rc.parameterCount, rc.command, rc.commandHelp);
					}
				}
			}
			if (commandParsed==false && commandParserList.Size() > 0)
			{
				transport->Send(p->systemAddress, "Unknown command:  Type 'help' for help.\r\n");
			}

		}

		ShowPrompt(p->systemAddress);

		transport->DeallocatePacket(p);
		p = transport->Receive();
	}
}

void ConsoleServer::ListParsers(SystemAddress systemAddress)
{
	transport->Send(systemAddress,"INSTALLED PARSERS:\r\n");
	unsigned i;
	for (i=0; i < commandParserList.Size(); i++)
	{
        transport->Send(systemAddress, "%i. %s\r\n", i+1, commandParserList[i]->GetName());
	}
}
void ConsoleServer::ShowPrompt(SystemAddress systemAddress)
{
	 transport->Send(systemAddress, prompt);
}
void ConsoleServer::SetPrompt(const char *_prompt)
{
	if (prompt)
		rakFree_Ex(prompt,_FILE_AND_LINE_);
	if (_prompt && _prompt[0])
	{
		size_t len = strlen(_prompt);
		prompt = (char*) rakMalloc_Ex(len+1,_FILE_AND_LINE_);
		strcpy_s(prompt,len+1,_prompt);
	}
	else
		prompt=0;
}

#endif // _RAKNET_SUPPORT_*
