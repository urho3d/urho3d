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

/// \file ConsoleServer.h
/// \brief Contains ConsoleServer , used to plugin to your game to accept remote console-based connections
///


#include "NativeFeatureIncludes.h"
#if _RAKNET_SUPPORT_ConsoleServer==1

#ifndef __CONSOLE_SERVER_H
#define __CONSOLE_SERVER_H

#include "memoryoverride.h"
#include "DS_List.h"
#include "types.h"
#include "Export.h"

namespace SLNet
{
/// Forward declarations
class TransportInterface;
class CommandParserInterface;


/// \brief The main entry point for the server portion of your remote console application support.
/// \details ConsoleServer takes one TransportInterface and one or more CommandParserInterface (s)
/// The TransportInterface will be used to send data between the server and the client.  The connecting client must support the
/// protocol used by your derivation of TransportInterface . TelnetTransport and RakNetTransport are two such derivations .
/// When a command is sent by a remote console, it will be processed by your implementations of CommandParserInterface
class RAK_DLL_EXPORT ConsoleServer
{
public:
	// GetInstance() and DestroyInstance(instance*)
	STATIC_FACTORY_DECLARATIONS(ConsoleServer)

	ConsoleServer();
	~ConsoleServer();

	/// \brief Call this with a derivation of TransportInterface so that the console server can send and receive commands
	/// \param[in] transportInterface Your interface to use.
	/// \param[in] port The port to host on.  Telnet uses port 23 by default.  RakNet can use whatever you want.
	void SetTransportProvider(TransportInterface *transportInterface, unsigned short port);

	/// \brief Add an implementation of CommandParserInterface to the list of command parsers.
	/// \param[in] commandParserInterface The command parser referred to
	void AddCommandParser(CommandParserInterface *commandParserInterface);

	/// \brief Remove an implementation of CommandParserInterface previously added with AddCommandParser().
	/// \param[in] commandParserInterface The command parser referred to
	void RemoveCommandParser(CommandParserInterface *commandParserInterface);

	/// \brief Call update to read packet sent from your TransportInterface.
	/// You should do this fairly frequently.
	void Update(void);

	/// \brief Sets a prompt to show when waiting for user input.
	/// \details Pass an empty string to clear the prompt
	/// Defaults to no prompt
	/// \param[in] _prompt Null-terminated string of the prompt to use. If you want a newline, be sure to use /r/n
	void SetPrompt(const char *_prompt);

protected:
	void ListParsers(SystemAddress systemAddress);
	void ShowPrompt(SystemAddress systemAddress);
	TransportInterface *transport;
	DataStructures::List<CommandParserInterface *> commandParserList;
	char* password[256];
	char *prompt;
};

} // namespace SLNet

#endif

#endif // _RAKNET_SUPPORT_*
