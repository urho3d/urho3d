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

/// \file CommandParserInterface.h
/// \brief Contains CommandParserInterface , from which you derive custom command parsers
///


#ifndef __COMMAND_PARSER_INTERFACE
#define __COMMAND_PARSER_INTERFACE

#include "memoryoverride.h"
#include "types.h"
#include "DS_OrderedList.h"
#include "Export.h"

namespace SLNet
{
/// Forward declarations
class TransportInterface;

/// \internal
/// Contains the information related to one command registered with RegisterCommand()
/// Implemented so I can have an automatic help system via SendCommandList()
struct RAK_DLL_EXPORT RegisteredCommand
{
	const char *command;
	const char *commandHelp;
	unsigned char parameterCount;
};

/// List of commands registered with RegisterCommand()
int RAK_DLL_EXPORT RegisteredCommandComp( const char* const & key, const RegisteredCommand &data );

/// \brief The interface used by command parsers.
/// \details CommandParserInterface provides a set of functions and interfaces that plug into the ConsoleServer class.
/// Each CommandParserInterface works at the same time as other interfaces in the system.
class RAK_DLL_EXPORT CommandParserInterface
{
public:
	CommandParserInterface();
	virtual ~CommandParserInterface();

	/// You are responsible for overriding this function and returning a static string, which will identifier your parser.
	/// This should return a static string
	/// \return The name that you return.
	virtual const char *GetName(void) const=0;

	/// \brief A callback for when \a systemAddress has connected to us.
	/// \param[in] systemAddress The player that has connected.
	/// \param[in] transport The transport interface that sent us this information.  Can be used to send messages to this or other players.
	virtual void  OnNewIncomingConnection(const SystemAddress &systemAddress, TransportInterface *transport);

	/// \brief A callback for when \a systemAddress has disconnected, either gracefully or forcefully
	/// \param[in] systemAddress The player that has disconnected.
	/// \param[in] transport The transport interface that sent us this information.
	virtual void OnConnectionLost(const SystemAddress &systemAddress, TransportInterface *transport);

	/// \brief A callback for when you are expected to send a brief description of your parser to \a systemAddress
	/// \param[in] transport The transport interface we can use to write to
	/// \param[in] systemAddress The player that requested help.
	virtual void SendHelp(TransportInterface *transport, const SystemAddress &systemAddress)=0;

	/// \brief Given \a command with parameters \a parameterList , do whatever processing you wish.
	/// \param[in] command The command to process
	/// \param[in] numParameters How many parameters were passed along with the command
	/// \param[in] parameterList The list of parameters.  parameterList[0] is the first parameter and so on.
	/// \param[in] transport The transport interface we can use to write to
	/// \param[in] systemAddress The player that sent this command.
	/// \param[in] originalString The string that was actually sent over the network, in case you want to do your own parsing
	virtual bool OnCommand(const char *command, unsigned numParameters, char **parameterList, TransportInterface *transport, const SystemAddress &systemAddress, const char *originalString)=0;

	/// \brief This is called every time transport interface is registered.  
	/// \details If you want to save a copy of the TransportInterface pointer
	/// This is the place to do it
	/// \param[in] transport The new TransportInterface
	virtual void OnTransportChange(TransportInterface *transport);

	/// \internal
	/// Scan commandList and return the associated array
	/// \param[in] command The string to find
	/// \param[out] rc Contains the result of this operation
	/// \return True if we found the command, false otherwise
	virtual bool GetRegisteredCommand(const char *command, RegisteredCommand *rc);

	/// \internal
	/// Goes through str, replacing the delineating character with 0's.
	/// \param[in] str The string sent by the transport interface
	/// \param[in] delineator The character to scan for to use as a delineator
	/// \param[in] delineatorToggle When encountered the delineator replacement is toggled on and off
	/// \param[out] numParameters How many pointers were written to \a parameterList
	/// \param[out] parameterList An array of pointers to characters.  Will hold pointers to locations inside \a str
	/// \param[in] parameterListLength How big the \a parameterList array is
	static void ParseConsoleString(char *str, const char delineator, unsigned char delineatorToggle, unsigned *numParameters, char **parameterList, unsigned parameterListLength);

	/// \internal
	/// Goes through the variable commandList and sends the command portion of each struct
	/// \param[in] transport The transport interface we can use to write to
	/// \param[in] systemAddress The player to write to
	virtual void SendCommandList(TransportInterface *transport, const SystemAddress &systemAddress);

	static const unsigned char VARIABLE_NUMBER_OF_PARAMETERS;

	// Currently only takes static strings - doesn't make a copy of what you pass.
	// parameterCount is the number of parameters that the sender has to include with the command.
	// Pass 255 to parameterCount to indicate variable number of parameters

	/// Registers a command.
	/// \param[in] parameterCount How many parameters your command requires.  If you want to accept a variable number of commands, pass CommandParserInterface::VARIABLE_NUMBER_OF_PARAMETERS
	/// \param[in] command A pointer to a STATIC string that has your command.  I keep a copy of the pointer here so don't deallocate the string.
	/// \param[in] commandHelp A pointer to a STATIC string that has the help information for your command.  I keep a copy of the pointer here so don't deallocate the string.
	virtual void RegisterCommand(unsigned char parameterCount, const char *command, const char *commandHelp);

	/// \brief Just writes a string to the remote system based on the result ( \a res ) of your operation
	/// \details This is not necessary to call, but makes it easier to return results of function calls.
	/// \param[in] res The result to write
	/// \param[in] command The command that this result came from
	/// \param[in] transport The transport interface that will be written to
	/// \param[in] systemAddress The player this result will be sent to
	virtual void ReturnResult(bool res, const char *command, TransportInterface *transport, const SystemAddress &systemAddress);
	virtual void ReturnResult(char *res, const char *command, TransportInterface *transport, const SystemAddress &systemAddress);
	virtual void ReturnResult(SystemAddress res, const char *command, TransportInterface *transport, const SystemAddress &systemAddress);
	virtual void ReturnResult(int res, const char *command,TransportInterface *transport, const SystemAddress &systemAddress);

	/// \brief Just writes a string to the remote system when you are calling a function that has no return value.
	/// \details This is not necessary to call, but makes it easier to return results of function calls.
	/// \param[in] res The result to write
	/// \param[in] command The command that this result came from
	/// \param[in] transport The transport interface that will be written to
	/// \param[in] systemAddress The player this result will be sent to
	virtual void ReturnResult(const char *command,TransportInterface *transport, const SystemAddress &systemAddress);

protected:
	DataStructures::OrderedList<const char*, RegisteredCommand, RegisteredCommandComp> commandList;
};

} // namespace SLNet

#endif

