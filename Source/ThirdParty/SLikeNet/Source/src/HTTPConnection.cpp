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
/// \brief Contains HTTPConnection, used to communicate with web servers
///

#include "slikenet/NativeFeatureIncludes.h"
#if _RAKNET_SUPPORT_HTTPConnection==1 && _RAKNET_SUPPORT_TCPInterface==1

#include "slikenet/TCPInterface.h"
#include "slikenet/HTTPConnection.h"
#include "slikenet/sleep.h"
#include "slikenet/string.h"
#include "slikenet/assert.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>

using namespace SLNet;

STATIC_FACTORY_DEFINITIONS(HTTPConnection,HTTPConnection);

HTTPConnection::HTTPConnection() : connectionState(CS_NONE)
{
	tcp=0;
}

void HTTPConnection::Init(TCPInterface* _tcp, const char *_host, unsigned short _port)
{
	tcp=_tcp;
	host=_host;
	port=_port;
}

void HTTPConnection::Post(const char *remote_path, const char *data, const char *_contentType)
{
	OutgoingCommand op;
	op.contentType=_contentType;
	op.data=data;
	op.remotePath=remote_path;
	op.isPost=true;
	outgoingCommand.Push(op, _FILE_AND_LINE_ );
	//printf("Adding outgoing post\n");
}

void HTTPConnection::Get(const char *path)
{
	OutgoingCommand op;
	op.remotePath=path;
	op.isPost=false;
	outgoingCommand.Push(op, _FILE_AND_LINE_ );
}

bool HTTPConnection::HasBadResponse(int *code, SLNet::RakString *data)
{
    if(badResponses.IsEmpty())
        return false;

	if (code)
		*code = badResponses.Peek().code;
	if (data)
		*data = badResponses.Pop().data;
   return true;
}
void HTTPConnection::CloseConnection()
{
	connectionState=CS_DISCONNECTING;
}
void HTTPConnection::Update(void)
{
	SystemAddress sa;
	sa = tcp->HasCompletedConnectionAttempt();
	while (sa!=UNASSIGNED_SYSTEM_ADDRESS)
	{
//		printf("Connected\n");
		connectionState=CS_CONNECTED;
		server=sa;
		sa = tcp->HasCompletedConnectionAttempt();
	}

	sa = tcp->HasFailedConnectionAttempt();
	while (sa!=UNASSIGNED_SYSTEM_ADDRESS)
	{
		//printf("Failed connected\n");
		CloseConnection();
		sa = tcp->HasFailedConnectionAttempt();
	}

	sa = tcp->HasLostConnection();
	while (sa!=UNASSIGNED_SYSTEM_ADDRESS)
	{
		//printf("Lost connection\n");
		CloseConnection();
		sa = tcp->HasLostConnection();
	}


	switch (connectionState)
	{
	case CS_NONE:
		{
			if (outgoingCommand.IsEmpty())
				return;

			//printf("Connecting\n");
			server = tcp->Connect(host, port, false);
			connectionState = CS_CONNECTING;
		}
		break;
	case CS_DISCONNECTING:
		{
			if (tcp->ReceiveHasPackets()==false)
			{
				if (incomingData.IsEmpty()==false)
				{
					results.Push(incomingData, _FILE_AND_LINE_ );
				}
				incomingData.Clear();
				tcp->CloseConnection(server);
				connectionState=CS_NONE;
			}
		}
		break;
	case CS_CONNECTING:
		{
		}
		break;
	case CS_CONNECTED:
		{
			//printf("Connected\n");
			if (outgoingCommand.IsEmpty())
			{
				//printf("Closed connection (nothing to do)\n");
				CloseConnection();
				return;
			}

#if OPEN_SSL_CLIENT_SUPPORT==1
			tcp->StartSSLClient(server);
#endif

			//printf("Sending request\n");
			currentProcessingCommand = outgoingCommand.Pop();
			RakString request;
			if (currentProcessingCommand.isPost)
			{
				request.Set("POST %s HTTP/1.0\r\n"
					"Host: %s:%i\r\n"
					"Content-Type: %s\r\n"
					"Content-Length: %u\r\n"
					"\r\n"
					"%s",
					currentProcessingCommand.remotePath.C_String(),
					host.C_String(),
					port,
					currentProcessingCommand.contentType.C_String(),
					(unsigned) currentProcessingCommand.data.GetLength(),
					currentProcessingCommand.data.C_String());
			}
			else
			{
				// request.Set("GET %s\r\n", host.C_String());
				// http://www.jenkinssoftware.com/forum/index.php?topic=4601.0;topicseen
				request.Set("GET %s HTTP/1.0\r\n"
					"Host: %s:%i\r\n"
					"\r\n",
					currentProcessingCommand.remotePath.C_String(),
					host.C_String(),
					port);
			}
			
		//	printf(request.C_String());
	//		request.URLEncode();
			tcp->Send(request.C_String(), (unsigned int) request.GetLength(), server,false);
			connectionState=CS_PROCESSING;
		}
		break;
	case CS_PROCESSING:
		{
		}
	}

//	if (connectionState==CS_PROCESSING && currentProcessingCommand.data.IsEmpty()==false)
//		outgoingCommand.PushAtHead(currentProcessingCommand);
}
bool HTTPConnection::HasRead(void) const
{
	return results.IsEmpty()==false;
}
RakString HTTPConnection::Read(void)
{
	if (results.IsEmpty())
		return RakString();

	SLNet::RakString resultStr = results.Pop();
    // const char *start_of_body = strstr(resultStr.C_String(), "\r\n\r\n");
	const char *start_of_body = strpbrk(resultStr.C_String(), "\001\002\003%");
    
    if(start_of_body)
		return SLNet::RakString::NonVariadic(start_of_body);
	else
		return resultStr;
}
SystemAddress HTTPConnection::GetServerAddress(void) const
{
	return server;
}
void HTTPConnection::ProcessTCPPacket(Packet *packet)
{
	RakAssert(packet);

	// read all the packets possible
	if(packet->systemAddress == server)
	{
		if(incomingData.GetLength() == 0)
		{
			int response_code = atoi((char *)packet->data + strlen("HTTP/1.0 "));

			if(response_code > 299)
			{
				badResponses.Push(BadResponse(packet->data, response_code), _FILE_AND_LINE_ );
				//printf("Closed connection (Bad response 2)\n");
				CloseConnection();
				return;
			}
		}

		SLNet::RakString incomingTemp = SLNet::RakString::NonVariadic((const char*) packet->data);
		incomingTemp.URLDecode();
		incomingData += incomingTemp;

	//	printf((const char*) packet->data);
	//	printf("\n");

		RakAssert(strlen((char *)packet->data) == packet->length); // otherwise it contains Null bytes

		const char *start_of_body = strstr(incomingData, "\r\n\r\n");

		// besides having the server close the connection, they may
		// provide a length header and supply that many bytes
		if(
			// Why was start_of_body here? Makes the GET command fail
			// start_of_body && 
			connectionState == CS_PROCESSING)
		{
			/*
			// The stupid programmer that wrote this originally didn't think that just because the header contains this value doesn't mean you got the whole message
			if (strstr((const char*) packet->data, "\r\nConnection: close\r\n"))
			{
				CloseConnection();
			}
			else
			{
			*/
				long length_of_headers;
				if (start_of_body)
				{
					length_of_headers = (long)(start_of_body + 4 - incomingData.C_String());
					const char *length_header = strstr(incomingData, "\r\nLength: ");

					if(length_header)
					{
						long length = atol(length_header + 10) + length_of_headers;

						if((long) incomingData.GetLength() >= length)
						{
							//printf("Closed connection (Got all data due to length header)\n");
							CloseConnection();
						}
					}
				}
				else
				{
					// No processing needed
				}

				
			//}
		}
	}
}

bool HTTPConnection::IsBusy(void) const
{
	return connectionState != CS_NONE;
}

int HTTPConnection::GetState(void) const
{
	return connectionState;
}


HTTPConnection::~HTTPConnection(void)
{
	if (tcp)
		tcp->CloseConnection(server);
}


#endif // _RAKNET_SUPPORT_*
