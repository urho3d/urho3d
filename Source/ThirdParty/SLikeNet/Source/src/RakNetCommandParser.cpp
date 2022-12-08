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
#if _RAKNET_SUPPORT_RakNetCommandParser==1

#include "slikenet/commandparser.h"
#include "slikenet/TransportInterface.h"
#include "slikenet/peerinterface.h"
#include "slikenet/BitStream.h"
#include "slikenet/assert.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

using namespace SLNet;

STATIC_FACTORY_DEFINITIONS(RakNetCommandParser,RakNetCommandParser);

RakNetCommandParser::RakNetCommandParser()
{
	RegisterCommand(4, "Startup","( unsigned int maxConnections, unsigned short localPort, const char *forceHostAddress );");
	RegisterCommand(0,"InitializeSecurity","();");
	RegisterCommand(0,"DisableSecurity","( void );");
	RegisterCommand(1,"AddToSecurityExceptionList","( const char *ip );");
	RegisterCommand(1,"RemoveFromSecurityExceptionList","( const char *ip );");
	RegisterCommand(1,"IsInSecurityExceptionList","( const char *ip );");
	RegisterCommand(1,"SetMaximumIncomingConnections","( unsigned short numberAllowed );");
	RegisterCommand(0,"GetMaximumIncomingConnections","( void ) const;");
	RegisterCommand(4,"Connect","( const char* host, unsigned short remotePort, const char *passwordData, int passwordDataLength );");
	RegisterCommand(2,"Disconnect","( unsigned int blockDuration, unsigned char orderingChannel=0 );");
	RegisterCommand(0,"IsActive","( void ) const;");
	RegisterCommand(0,"GetConnectionList","() const;");
	RegisterCommand(3,"CloseConnection","( const SystemAddress target, bool sendDisconnectionNotification, unsigned char orderingChannel=0 );");
	RegisterCommand(2,"IsConnected","( );");
	RegisterCommand(1,"GetIndexFromSystemAddress","( const SystemAddress systemAddress );");
	RegisterCommand(1,"GetSystemAddressFromIndex","( unsigned int index );");
	RegisterCommand(2,"AddToBanList","( const char *IP, SLNet::TimeMS milliseconds=0 );");
	RegisterCommand(1,"RemoveFromBanList","( const char *IP );");
	RegisterCommand(0,"ClearBanList","( void );");
	RegisterCommand(1,"IsBanned","( const char *IP );");
	RegisterCommand(1,"Ping1","( const SystemAddress target );");
	RegisterCommand(3,"Ping2","( const char* host, unsigned short remotePort, bool onlyReplyOnAcceptingConnections );");
	RegisterCommand(1,"GetAveragePing","( const SystemAddress systemAddress );");
	RegisterCommand(1,"GetLastPing","( const SystemAddress systemAddress ) const;");
	RegisterCommand(1,"GetLowestPing","( const SystemAddress systemAddress ) const;");
	RegisterCommand(1,"SetOccasionalPing","( bool doPing );");
	RegisterCommand(2,"SetOfflinePingResponse","( const char *data, const unsigned int length );");
	RegisterCommand(0,"GetInternalID","( void ) const;");
	RegisterCommand(1,"GetExternalID","( const SystemAddress target ) const;");
	RegisterCommand(2,"SetTimeoutTime","( SLNet::TimeMS timeMS, const SystemAddress target );");
//	RegisterCommand(1,"SetMTUSize","( int size );");
	RegisterCommand(0,"GetMTUSize","( void ) const;");
	RegisterCommand(0,"GetNumberOfAddresses","( void );");
	RegisterCommand(1,"GetLocalIP","( unsigned int index );");
	RegisterCommand(1,"AllowConnectionResponseIPMigration","( bool allow );");
	RegisterCommand(4,"AdvertiseSystem","( const char *host, unsigned short remotePort, const char *data, int dataLength );");
	RegisterCommand(2,"SetIncomingPassword","( const char* passwordData, int passwordDataLength );");
	RegisterCommand(0,"GetIncomingPassword","( void );");
	RegisterCommand(0,"IsNetworkSimulatorActive","( void );");
}
RakNetCommandParser::~RakNetCommandParser()
{
}
void RakNetCommandParser::SetRakPeerInterface(SLNet::RakPeerInterface *rakPeer)
{
	peer=rakPeer;
}
bool RakNetCommandParser::OnCommand(const char *command, unsigned numParameters, char **parameterList, TransportInterface *transport, const SystemAddress &systemAddress, const char *originalString)
{
	(void) originalString;
	(void) numParameters;

	if (peer==0)
		return false;

	if (strcmp(command, "Startup")==0)
	{
		SLNet::SocketDescriptor socketDescriptor((unsigned short)atoi(parameterList[1]), parameterList[2]);
		ReturnResult(peer->Startup((unsigned short)atoi(parameterList[0]), &socketDescriptor, 1), command, transport, systemAddress);
	}
	else if (strcmp(command, "InitializeSecurity")==0)
	{
		ReturnResult(peer->InitializeSecurity(parameterList[0],parameterList[1]), command, transport, systemAddress);
	}
	else if (strcmp(command, "DisableSecurity")==0)
	{
		peer->DisableSecurity();
		ReturnResult(command, transport, systemAddress);
	}
	else if (strcmp(command, "AddToSecurityExceptionList")==0)
	{
		peer->AddToSecurityExceptionList(parameterList[1]);
		ReturnResult(command, transport, systemAddress);
	}
	else if (strcmp(command, "RemoveFromSecurityExceptionList")==0)
	{
		peer->RemoveFromSecurityExceptionList(parameterList[1]);
		ReturnResult(command, transport, systemAddress);
	}
	else if (strcmp(command, "IsInSecurityExceptionList")==0)
	{
		ReturnResult(peer->IsInSecurityExceptionList(parameterList[1]),command, transport, systemAddress);
	}
	else if (strcmp(command, "SetMaximumIncomingConnections")==0)
	{
		peer->SetMaximumIncomingConnections((unsigned short)atoi(parameterList[0]));
		ReturnResult(command, transport, systemAddress);
	}
	else if (strcmp(command, "GetMaximumIncomingConnections")==0)
	{
		ReturnResult((int) peer->GetMaximumIncomingConnections(), command, transport, systemAddress);
	}
	else if (strcmp(command, "Connect")==0)
	{
		ReturnResult(peer->Connect(parameterList[0], (unsigned short)atoi(parameterList[1]),parameterList[2],atoi(parameterList[3]))== SLNet::CONNECTION_ATTEMPT_STARTED, command, transport, systemAddress);
	}
	else if (strcmp(command, "Disconnect")==0)
	{
		peer->Shutdown(atoi(parameterList[0]), (unsigned char)atoi(parameterList[1]));
		ReturnResult(command, transport, systemAddress);
	}
	else if (strcmp(command, "IsActive")==0)
	{
		ReturnResult(peer->IsActive(), command, transport, systemAddress);
	}
	else if (strcmp(command, "GetConnectionList")==0)
	{
		SystemAddress remoteSystems[32];
		unsigned short count=32;
		unsigned i;
		if (peer->GetConnectionList(remoteSystems, &count))
		{
			if (count==0)
			{
				transport->Send(systemAddress, "GetConnectionList() returned no systems connected.\r\n");
			}
			else
			{
				transport->Send(systemAddress, "GetConnectionList() returned:\r\n");
				for (i=0; i < count; i++)
				{
					char str1[64];
					remoteSystems[i].ToString(true, str1, static_cast<size_t>(64));
					transport->Send(systemAddress, "%i %s\r\n", i, str1);
				}
			}
		}
		else
			transport->Send(systemAddress, "GetConnectionList() returned false.\r\n");
	}
	else if (strcmp(command, "CloseConnection")==0)
	{
		peer->CloseConnection(SystemAddress(parameterList[0]), atoi(parameterList[1])!=0,(unsigned char)atoi(parameterList[2]));
		ReturnResult(command, transport, systemAddress);
	}
	else if (strcmp(command, "GetConnectionState")==0)
	{
		ReturnResult((int) peer->GetConnectionState(SystemAddress(parameterList[0])), command, transport, systemAddress);
	}
	else if (strcmp(command, "GetIndexFromSystemAddress")==0)
	{
		ReturnResult(peer->GetIndexFromSystemAddress(SystemAddress(parameterList[0])), command, transport, systemAddress);
	}
	else if (strcmp(command, "GetSystemAddressFromIndex")==0)
	{
		ReturnResult(peer->GetSystemAddressFromIndex(atoi(parameterList[0])), command, transport, systemAddress);
	}
	else if (strcmp(command, "AddToBanList")==0)
	{
		peer->AddToBanList(parameterList[0], atoi(parameterList[1]));
		ReturnResult(command, transport, systemAddress);
	}
	else if (strcmp(command, "RemoveFromBanList")==0)
	{
		peer->RemoveFromBanList(parameterList[0]);
		ReturnResult(command, transport, systemAddress);
	}
	else if (strcmp(command, "ClearBanList")==0)
	{
		peer->ClearBanList();
		ReturnResult(command, transport, systemAddress);
	}
	else if (strcmp(command, "IsBanned")==0)
	{
		ReturnResult(peer->IsBanned(parameterList[0]), command, transport, systemAddress);
	}
	else if (strcmp(command, "Ping1")==0)
	{
		peer->Ping(SystemAddress(parameterList[0]));
		ReturnResult(command, transport, systemAddress);
	}
	else if (strcmp(command, "Ping2")==0)
	{
		peer->Ping(parameterList[0], (unsigned short) atoi(parameterList[1]), atoi(parameterList[2])!=0);
		ReturnResult(command, transport, systemAddress);
	}
	else if (strcmp(command, "GetAveragePing")==0)
	{
		ReturnResult(peer->GetAveragePing(SystemAddress(parameterList[0])), command, transport, systemAddress);
	}
	else if (strcmp(command, "GetLastPing")==0)
	{
		ReturnResult(peer->GetLastPing(SystemAddress(parameterList[0])), command, transport, systemAddress);
	}
	else if (strcmp(command, "GetLowestPing")==0)
	{
		ReturnResult(peer->GetLowestPing(SystemAddress(parameterList[0])), command, transport, systemAddress);
	}
	else if (strcmp(command, "SetOccasionalPing")==0)
	{
		peer->SetOccasionalPing(atoi(parameterList[0])!=0);
		ReturnResult(command, transport, systemAddress);
	}
	else if (strcmp(command, "SetOfflinePingResponse")==0)
	{
		peer->SetOfflinePingResponse(parameterList[0], atoi(parameterList[1]));
		ReturnResult(command, transport, systemAddress);
	}
	else if (strcmp(command, "GetInternalID")==0)
	{
		ReturnResult(peer->GetInternalID(), command, transport, systemAddress);
	}
	else if (strcmp(command, "GetExternalID")==0)
	{
		ReturnResult(peer->GetExternalID(SystemAddress(parameterList[0])), command, transport, systemAddress);
	}
	else if (strcmp(command, "SetTimeoutTime")==0)
	{
		peer->SetTimeoutTime(atoi(parameterList[0]), SystemAddress(parameterList[1]));
		ReturnResult(command, transport, systemAddress);
	}
	/*
	else if (strcmp(command, "SetMTUSize")==0)
	{
		ReturnResult(peer->SetMTUSize(atoi(parameterList[0]), UNASSIGNED_SYSTEM_ADDRESS), command, transport, systemAddress);
	}
	*/
	else if (strcmp(command, "GetMTUSize")==0)
	{
		ReturnResult(peer->GetMTUSize(UNASSIGNED_SYSTEM_ADDRESS), command, transport, systemAddress);
	}
	else if (strcmp(command, "GetNumberOfAddresses")==0)
	{
		ReturnResult((int)peer->GetNumberOfAddresses(), command, transport, systemAddress);
	}
	else if (strcmp(command, "GetLocalIP")==0)
	{
		ReturnResult((char*) peer->GetLocalIP(atoi(parameterList[0])), command, transport, systemAddress);
	}
	else if (strcmp(command, "AllowConnectionResponseIPMigration")==0)
	{
		peer->AllowConnectionResponseIPMigration(atoi(parameterList[0])!=0);
		ReturnResult(command, transport, systemAddress);
	}
	else if (strcmp(command, "AdvertiseSystem")==0)
	{
		peer->AdvertiseSystem(parameterList[0], (unsigned short) atoi(parameterList[1]),parameterList[2],atoi(parameterList[3]));
		ReturnResult(command, transport, systemAddress);
	}
	else if (strcmp(command, "SetIncomingPassword")==0)
	{
		peer->SetIncomingPassword(parameterList[0], atoi(parameterList[1]));
		ReturnResult(command, transport, systemAddress);
	}
	else if (strcmp(command, "GetIncomingPassword")==0)
	{
		char password[256];
		int passwordLength;
		peer->GetIncomingPassword(password, &passwordLength);
		if (passwordLength)
			ReturnResult((char*)password, command, transport, systemAddress);
		else
			ReturnResult(0, command, transport, systemAddress);
	}

	return true;
}
const char *RakNetCommandParser::GetName(void) const
{
	return "RakNet";
}
void RakNetCommandParser::SendHelp(TransportInterface *transport, const SystemAddress &systemAddress)
{
	if (peer)
	{
		transport->Send(systemAddress, "The RakNet parser provides mirror functions to RakPeer\r\n");
		transport->Send(systemAddress, "SystemAddresss take two parameters: send <BinaryAddress> <Port>.\r\n");
		transport->Send(systemAddress, "For bool, send 1 or 0.\r\n");
	}
	else
	{
		transport->Send(systemAddress, "Parser not active.  Call SetRakPeerInterface.\r\n");
	}
}

#endif // _RAKNET_SUPPORT_*
