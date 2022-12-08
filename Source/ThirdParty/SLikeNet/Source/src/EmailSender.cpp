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
#if _RAKNET_SUPPORT_EmailSender==1 && _RAKNET_SUPPORT_TCPInterface==1 && _RAKNET_SUPPORT_FileOperations==1

// Useful sites
// http://www.faqs.org\rfcs\rfc2821.html
// http://www2.rad.com\networks/1995/mime/examples.htm

#include "slikenet/EmailSender.h"
#include "slikenet/TCPInterface.h"
#include "slikenet/GetTime.h"
#include "slikenet/Rand.h"
#include "slikenet/FileList.h"
#include "slikenet/BitStream.h"
#include "slikenet/Base64Encoder.h"
#include <stdio.h>
#include "slikenet/linux_adapter.h"
#include "slikenet/osx_adapter.h"





#include "slikenet/sleep.h"

using namespace SLNet;


STATIC_FACTORY_DEFINITIONS(EmailSender,EmailSender);

const char *EmailSender::Send(const char *hostAddress, unsigned short hostPort, const char *sender, const char *recipient, const char *senderName, const char *recipientName, const char *subject, const char *body, FileList *attachedFiles, bool doPrintf, const char *password)
{
	SLNet::Packet *packet;
	char query[1024];
	TCPInterface tcpInterface;
	SystemAddress emailServer;
	if (tcpInterface.Start(0, 0)==false)
		return "Unknown error starting TCP";
	emailServer=tcpInterface.Connect(hostAddress, hostPort,true);
	if (emailServer==UNASSIGNED_SYSTEM_ADDRESS)
		return "Failed to connect to host";
#if  OPEN_SSL_CLIENT_SUPPORT==1
	tcpInterface.StartSSLClient(emailServer);
#endif
	SLNet::TimeMS timeoutTime = SLNet::GetTimeMS()+3000;
	packet=0;
	while (SLNet::GetTimeMS() < timeoutTime)
	{
		packet = tcpInterface.Receive();
		if (packet)
		{
			if (doPrintf)
			{
				RAKNET_DEBUG_PRINTF("%s", packet->data);
				tcpInterface.DeallocatePacket(packet);
			}
			break;
		}
		RakSleep(250);
	}

	if (packet==0)
		return "Timeout while waiting for initial data from server.";
	
	tcpInterface.Send("EHLO\r\n", 6, emailServer,false);
	const char *response;
	bool authenticate=false;
	for(;;)
	{
		response=GetResponse(&tcpInterface, emailServer, doPrintf);

		if (response!=0 && strcmp(response, "AUTHENTICATE")==0)
		{
			authenticate=true;
			break;
		}

		// Something other than continue?
		if (response!=0 && strcmp(response, "CONTINUE")!=0)
			return response;

		// Success?
		if (response==0)
			break;
	}

	if (authenticate)
	{
		sprintf_s(query, "EHLO %s\r\n", sender);
		tcpInterface.Send(query, (unsigned int)strlen(query), emailServer,false);
		response=GetResponse(&tcpInterface, emailServer, doPrintf);
		if (response!=0)
			return response;
		if (password==0)
			return "Password needed";
		char *outputData = SLNet::OP_NEW_ARRAY<char >((const int) (strlen(sender)+strlen(password)+2)*3, _FILE_AND_LINE_ );
		SLNet::BitStream bs;
		char zero=0;
		bs.Write(&zero,1);
		bs.Write(sender,(const unsigned int)strlen(sender));
		//bs.Write("jms1@jms1.net",(const unsigned int)strlen("jms1@jms1.net"));
		bs.Write(&zero,1);
		bs.Write(password,(const unsigned int)strlen(password));
		bs.Write(&zero,1);
		//bs.Write("not.my.real.password",(const unsigned int)strlen("not.my.real.password"));
		Base64Encoding((const unsigned char*)bs.GetData(), bs.GetNumberOfBytesUsed(), outputData);
		sprintf_s(query, "AUTH PLAIN %s", outputData);
		tcpInterface.Send(query, (unsigned int)strlen(query), emailServer,false);
		response=GetResponse(&tcpInterface, emailServer, doPrintf);
		if (response!=0)
			return response;
	}


	if (sender)
		sprintf_s(query, "MAIL From: <%s>\r\n", sender);
	else
		sprintf_s(query, "MAIL From: <>\r\n");
	tcpInterface.Send(query, (unsigned int)strlen(query), emailServer,false);
	response=GetResponse(&tcpInterface, emailServer, doPrintf);
	if (response!=0)
		return response;

	if (recipient)
		sprintf_s(query, "RCPT TO: <%s>\r\n", recipient);
	else
		sprintf_s(query, "RCPT TO: <>\r\n");
	tcpInterface.Send(query, (unsigned int)strlen(query), emailServer,false);
	response=GetResponse(&tcpInterface, emailServer, doPrintf);
	if (response!=0)
		return response;

	tcpInterface.Send("DATA\r\n", (unsigned int)strlen("DATA\r\n"), emailServer,false);

	// Wait for 354...

	response=GetResponse(&tcpInterface, emailServer, doPrintf);
	if (response!=0)
		return response;

	if (subject)
	{
		sprintf_s(query, "Subject: %s\r\n", subject);
		tcpInterface.Send(query, (unsigned int)strlen(query), emailServer,false);
	}
	if (senderName)
	{
		sprintf_s(query, "From: %s\r\n", senderName);
		tcpInterface.Send(query, (unsigned int)strlen(query), emailServer,false);
	}
	if (recipientName)
	{
		sprintf_s(query, "To: %s\r\n", recipientName);
		tcpInterface.Send(query, (unsigned int)strlen(query), emailServer,false);
	}

	const int boundarySize=60;
	char boundary[boundarySize+1];
	int i,j;
	if (attachedFiles && attachedFiles->fileList.Size())
	{
		rakNetRandom.SeedMT((unsigned int)SLNet::GetTimeMS());
		// Random multipart message boundary
		for (i=0; i < boundarySize; i++)
			boundary[i]=Base64Map()[rakNetRandom.RandomMT()%64];
		boundary[boundarySize]=0;
	}

	sprintf_s(query, "MIME-version: 1.0\r\n");
	tcpInterface.Send(query, (unsigned int)strlen(query), emailServer,false);

	if (attachedFiles && attachedFiles->fileList.Size())
	{
		sprintf_s(query, "Content-type: multipart/mixed; BOUNDARY=\"%s\"\r\n\r\n", boundary);
		tcpInterface.Send(query, (unsigned int)strlen(query), emailServer,false);

		sprintf_s(query, "This is a multi-part message in MIME format.\r\n\r\n--%s\r\n", boundary);
		tcpInterface.Send(query, (unsigned int)strlen(query), emailServer,false);
	}
	
	sprintf_s(query, "Content-Type: text/plain; charset=\"US-ASCII\"\r\n\r\n");
	tcpInterface.Send(query, (unsigned int)strlen(query), emailServer,false);

	// Write the body of the email, doing some lame shitty shit where I have to make periods at the start of a newline have a second period.
	char *newBody;
	int bodyLength;
	bodyLength=(int)strlen(body);
	newBody = (char*) rakMalloc_Ex( bodyLength*3, _FILE_AND_LINE_ );
	if (bodyLength>=0)
		newBody[0]=body[0];
	for (i=1, j=1; i < bodyLength; i++)
	{
		// Transform \n . \r \n into \n . . \r \n
		if (i < bodyLength-2 &&
			body[i-1]=='\n' &&
			body[i+0]=='.' &&
			body[i+1]=='\r' &&
			body[i+2]=='\n')
		{
			newBody[j++]='.';
			newBody[j++]='.';
			newBody[j++]='\r';
			newBody[j++]='\n';
			i+=2;
		}
		// Transform \n . . \r \n into \n . . . \r \n
		// Having to process .. is a bug in the mail server - the spec says ONLY \r\n.\r\n should be transformed
		else if (i <= bodyLength-3 &&
			body[i-1]=='\n' &&
			body[i+0]=='.' &&
			body[i+1]=='.' &&
			body[i+2]=='\r' &&
			body[i+3]=='\n')
		{
			newBody[j++]='.';
			newBody[j++]='.';
			newBody[j++]='.';
			newBody[j++]='\r';
			newBody[j++]='\n';
			i+=3;
		}
		// Transform \n . \n into \n . . \r \n (this is a bug in the mail server - the spec says do not count \n alone but it does)
		else if (i < bodyLength-1 &&
			body[i-1]=='\n' &&
			body[i+0]=='.' &&
			body[i+1]=='\n')
		{
			newBody[j++]='.';
			newBody[j++]='.';
			newBody[j++]='\r';
			newBody[j++]='\n';
			i+=1;
		}
		// Transform \n . . \n into \n . . . \r \n (this is a bug in the mail server - the spec says do not count \n alone but it does)
		// In fact having to process .. is a bug too - because the spec says ONLY \r\n.\r\n should be transformed
		else if (i <= bodyLength-2 &&
			body[i-1]=='\n' &&
			body[i+0]=='.' &&
			body[i+1]=='.' &&
			body[i+2]=='\n')
		{
			newBody[j++]='.';
			newBody[j++]='.';
			newBody[j++]='.';
			newBody[j++]='\r';
			newBody[j++]='\n';
			i+=2;
		}
		else
			newBody[j++]=body[i];
	}
	
	newBody[j++]='\r';
	newBody[j++]='\n';
	tcpInterface.Send(newBody, j, emailServer,false);

	rakFree_Ex(newBody, _FILE_AND_LINE_ );
	int outputOffset;

	// What a pain in the rear.  I have to map the binary to printable characters using 6 bits per character.
	if (attachedFiles && attachedFiles->fileList.Size())
	{
		for (i=0; i < (int) attachedFiles->fileList.Size(); i++)
		{
			// Write boundary
			sprintf_s(query, "\r\n--%s\r\n", boundary);
			tcpInterface.Send(query, (unsigned int)strlen(query), emailServer,false);

			sprintf_s(query, "Content-Type: APPLICATION/Octet-Stream; SizeOnDisk=%i; name=\"%s\"\r\nContent-Transfer-Encoding: BASE64\r\nContent-Description: %s\r\n\r\n", attachedFiles->fileList[i].dataLengthBytes, attachedFiles->fileList[i].filename.C_String(), attachedFiles->fileList[i].filename.C_String());
			tcpInterface.Send(query, (unsigned int)strlen(query), emailServer,false);

			newBody = (char*) rakMalloc_Ex( (size_t) (attachedFiles->fileList[i].dataLengthBytes*3)/2, _FILE_AND_LINE_ );

			outputOffset=Base64Encoding((const unsigned char*) attachedFiles->fileList[i].data, (int) attachedFiles->fileList[i].dataLengthBytes, newBody);

			// Send the base64 mapped file.
			tcpInterface.Send(newBody, outputOffset, emailServer,false);
			rakFree_Ex(newBody, _FILE_AND_LINE_ );

		}

		// Write last boundary
		sprintf_s(query, "\r\n--%s--\r\n", boundary);
		tcpInterface.Send(query, (unsigned int)strlen(query), emailServer,false);
	}


	sprintf_s(query, "\r\n.\r\n");
	tcpInterface.Send(query, (unsigned int)strlen(query), emailServer,false);
	response=GetResponse(&tcpInterface, emailServer, doPrintf);
	if (response!=0)
		return response;

	tcpInterface.Send("QUIT\r\n", (unsigned int)strlen("QUIT\r\n"), emailServer,false);

	RakSleep(30);
	if (doPrintf)
	{
		packet = tcpInterface.Receive();
		while (packet)
		{
			RAKNET_DEBUG_PRINTF("%s", packet->data);
			tcpInterface.DeallocatePacket(packet);
			packet = tcpInterface.Receive();
		}
	}
	tcpInterface.Stop();
	return 0; // Success
}

const char *EmailSender::GetResponse(TCPInterface *tcpInterface, const SystemAddress &emailServer, bool doPrintf)
{
	SLNet::Packet *packet;
	SLNet::TimeMS timeout;
	timeout= SLNet::GetTimeMS()+5000;
	for(;;)
	{
		if (tcpInterface->HasLostConnection()==emailServer)
			return "Connection to server lost.";
		packet = tcpInterface->Receive();
		if (packet)
		{
			if (doPrintf)
			{
				RAKNET_DEBUG_PRINTF("%s", packet->data);
			}
#if OPEN_SSL_CLIENT_SUPPORT==1
			if (strstr((const char*)packet->data, "220"))
			{
				tcpInterface->StartSSLClient(packet->systemAddress);
				return "AUTHENTICATE"; // OK
			}
// 			if (strstr((const char*)packet->data, "250-AUTH LOGIN PLAIN"))
// 			{
// 				tcpInterface->StartSSLClient(packet->systemAddress);
// 				return "AUTHENTICATE"; // OK
// 			}
#endif
			if (strstr((const char*)packet->data, "235"))
				return 0; // Authentication accepted
			if (strstr((const char*)packet->data, "354"))
				return 0; // Go ahead
#if OPEN_SSL_CLIENT_SUPPORT==1
			if (strstr((const char*)packet->data, "250-STARTTLS"))
			{
				tcpInterface->Send("STARTTLS\r\n", (unsigned int) strlen("STARTTLS\r\n"), packet->systemAddress, false);
				return "CONTINUE";
			}
#endif
			if (strstr((const char*)packet->data, "250"))
				return 0; // OK
			if (strstr((const char*)packet->data, "550"))
				return "Failed on error code 550";
			if (strstr((const char*)packet->data, "553"))
				return "Failed on error code 553";
		}
		if (SLNet::GetTimeMS() > timeout)
			return "Timed out";
		RakSleep(100);
	}
}


#endif // _RAKNET_SUPPORT_*
