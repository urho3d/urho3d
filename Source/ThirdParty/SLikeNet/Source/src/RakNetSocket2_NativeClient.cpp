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

#include "slikenet/EmptyHeader.h"

#ifdef RAKNET_SOCKET_2_INLINE_FUNCTIONS

#ifndef RAKNETSOCKET2_NATIVE_CLIENT_CPP
#define RAKNETSOCKET2_NATIVE_CLIENT_CPP

#if defined(__native_client__)

using namespace pp;

RNS2BindResult RNS2_NativeClient::Bind( NativeClientBindParameters *bindParameters, const char *file, unsigned int line )
{
	memcpy(&binding, bindParameters, sizeof(NativeClientBindParameters));

	if(Module::Get()->GetBrowserInterface(PPB_UDPSOCKET_PRIVATE_INTERFACE_0_4))
	{
		rns2Socket = ((PPB_UDPSocket_Private_0_4*) Module::Get()->GetBrowserInterface(PPB_UDPSOCKET_PRIVATE_INTERFACE_0_4))->Create(bindParameters->nativeClientInstance);
		RAKNET_DEBUG_PRINTF("CreateChromeSocket(%d,%s,0x%08x,%d) ==> 0x%08x\n", bindParameters->port, bindParameters->forceHostAddress?bindParameters->forceHostAddress:"(null)",bindParameters->nativeClientInstance,bindParameters->is_ipv6, rns2Socket);

		// Enable the broadcast feature on the socket (must happen before the
		// bind call)
		((PPB_UDPSocket_Private_0_4*) pp::Module::Get()->GetBrowserInterface(PPB_UDPSOCKET_PRIVATE_INTERFACE_0_4))->SetSocketFeature(rns2Socket, PP_UDPSOCKETFEATURE_BROADCAST, PP_MakeBool(PP_TRUE));

		PP_NetAddress_Private client_addr;
		uint8_t ipv6[16], ipv4[4];
		if (bindParameters->forceHostAddress)
		{
			unsigned int ipIdx=0;
			char * pch;
			pch = strtok ((char*) bindParameters->forceHostAddress,".");
			if (bindParameters->is_ipv6)
			{
				while (pch != NULL && ipIdx<16)
				{
					ipv6[ipIdx++]=atoi(pch);
					pch = strtok (NULL, ".");
				}
				NetAddressPrivate::CreateFromIPv6Address(ipv6,0,bindParameters->port,&client_addr);
			}
			else
			{
				while (pch != NULL && ipIdx<4)
				{
					ipv4[ipIdx++]=atoi(pch);
					pch = strtok (NULL, ".");
				}
				NetAddressPrivate::CreateFromIPv4Address(ipv4,bindParameters->port,&client_addr);
			}
		}
		else
		{
			NetAddressPrivate::GetAnyAddress(bindParameters->is_ipv6, &client_addr);
			NetAddressPrivate::ReplacePort(client_addr, bindParameters->port, &client_addr);
		}

		bindState = BS_IN_PROGRESS;

		RAKNET_DEBUG_PRINTF("attempting to bind to %s\n", NetAddressPrivate::Describe(client_addr, true).c_str());
		PP_CompletionCallback cc = PP_MakeCompletionCallback(RNS2_NativeClient::onSocketBound, this);
		((PPB_UDPSocket_Private_0_4*) Module::Get()->GetBrowserInterface(PPB_UDPSOCKET_PRIVATE_INTERFACE_0_4))->Bind(rns2Socket, &client_addr, cc);
		return BR_SUCCESS;
	}
	return BR_FAILED_TO_BIND_SOCKET;
}

void RNS2_NativeClient::SendImmediate(RNS2_SendParameters_NativeClient *sp)
{
	// Assuming data does not have to remain valid until callback called
	PP_NetAddress_Private client_addr;
#if RAKNET_SUPPORT_IPV6==1
	NetAddressPrivate::CreateFromIPv6Address(sp->systemAddress.address.addr6.sin6_addr.u.Byte,0,sp->systemAddress.GetPort(),&client_addr);
#else
	NetAddressPrivate::CreateFromIPv4Address((const uint8_t*) &sp->systemAddress.address.addr4.sin_addr,sp->systemAddress.GetPort(),&client_addr);
#endif

	// sp remains in memory until the callback completes
	PP_CompletionCallback cc = PP_MakeCompletionCallback(onSendTo, sp);
	((PPB_UDPSocket_Private_0_4*) Module::Get()->GetBrowserInterface(PPB_UDPSOCKET_PRIVATE_INTERFACE_0_4))->SendTo(sp->socket2->rns2Socket, sp->data, sp->length, &client_addr, cc);
}

void RNS2_NativeClient::onRecvFrom(void* pData, int32_t dataSize)
{
	RNS2RecvStruct *recvStruct = (RNS2RecvStruct *) pData;
	RNS2_NativeClient *socket2 = (RNS2_NativeClient *) recvStruct->socket;

	//any error codes will be given to us in the dataSize value; see pp_errors.h for a list of errors
	if(dataSize <=0 || !pData )
	{
		// Free data
		socket2->eventHandler->DeallocRNS2RecvStruct(recvStruct, _FILE_AND_LINE_);

		// This value indicates failure due to an asynchronous operation being
		// interrupted. The most common cause of this error code is destroying
		// a resource that still has a callback pending. All callbacks are
		// guaranteed to execute, so any callbacks pending on a destroyed
		// resource will be issued with PP_ERROR_ABORTED.
		if(dataSize==PP_ERROR_ABORTED)
		{
			RAKNET_DEBUG_PRINTF("onRecvFrom error PP_ERROR_ABORTED, killing recvfrom loop\n");
		}
		else
		{
			RAKNET_DEBUG_PRINTF("onRecvFrom error %d\n", dataSize);

			// Reissue call
			socket2->IssueReceiveCall();
		}

		return;
	}

	recvStruct->bytesRead=dataSize;
	recvStruct->timeRead= SLNet::GetTimeUS();


	PP_NetAddress_Private addr;
	bool ok=false;
	if(((PPB_UDPSocket_Private_0_4*) Module::Get()->GetBrowserInterface(PPB_UDPSOCKET_PRIVATE_INTERFACE_0_4))->GetRecvFromAddress(socket2->rns2Socket, &addr) == PP_TRUE)
	{
		PP_NetAddressFamily_Private family = NetAddressPrivate::GetFamily(addr);
		if (family == PP_NETADDRESSFAMILY_IPV4)
		{
			ok = NetAddressPrivate::GetAddress(addr, &recvStruct->systemAddress.address.addr4.sin_addr, sizeof(in_addr));
		}
#if RAKNET_SUPPORT_IPV6==1
		else
		{
			ok = NetAddressPrivate::GetAddress(addr, &recvStruct->systemAddress.address.addr6.sin6_addr, sizeof(in6_addr));
		}
#endif
	}

	if(ok)
	{
		recvStruct->systemAddress.SetPortHostOrder(pp::NetAddressPrivate::GetPort(addr));
		socket2->binding.eventHandler->OnRNS2Recv(recvStruct);				
	}

	// Reissue call
	socket2->IssueReceiveCall();
}
void RNS2_NativeClient::IssueReceiveCall(void)
{
	RNS2RecvStruct *recvFromStruct;
	recvFromStruct=binding.eventHandler->AllocRNS2RecvStruct(_FILE_AND_LINE_);
	if (recvFromStruct != NULL)
	{
		recvFromStruct->socket=this;
		PP_CompletionCallback cc = PP_MakeCompletionCallback(onRecvFrom, recvFromStruct);
		((PPB_UDPSocket_Private_0_4*) Module::Get()->GetBrowserInterface(PPB_UDPSOCKET_PRIVATE_INTERFACE_0_4))->RecvFrom(rns2Socket, recvFromStruct->data, MAXIMUM_MTU_SIZE, cc);
	}	
}

#endif // defined(__native_client__)

#endif // file header

#endif // #ifdef RAKNET_SOCKET_2_INLINE_FUNCTIONS
