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
#if _RAKNET_SUPPORT_TelnetTransport==1

#include "slikenet/transport2.h"

#include "slikenet/peerinterface.h"
#include "slikenet/BitStream.h"
#include "slikenet/MessageIdentifiers.h"
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include "slikenet/LinuxStrings.h"
#include "slikenet/linux_adapter.h"
#include "slikenet/osx_adapter.h"

using namespace SLNet;

STATIC_FACTORY_DEFINITIONS(RakNetTransport2,RakNetTransport2);

RakNetTransport2::RakNetTransport2()
{
}
RakNetTransport2::~RakNetTransport2()
{
	Stop();
}
bool RakNetTransport2::Start(unsigned short port, bool serverMode)
{
	(void) port;
	(void) serverMode;
	return true;
}
void RakNetTransport2::Stop(void)
{
	newConnections.Clear(_FILE_AND_LINE_);
	lostConnections.Clear(_FILE_AND_LINE_);
	for (unsigned int i=0; i < packetQueue.Size(); i++)
	{
		rakFree_Ex(packetQueue[i]->data,_FILE_AND_LINE_);
		SLNet::OP_DELETE(packetQueue[i],_FILE_AND_LINE_);
	}
	packetQueue.Clear(_FILE_AND_LINE_);
}
void RakNetTransport2::Send( SystemAddress systemAddress, const char *data, ... )
{
	if (data==0 || data[0]==0) return;

	char text[REMOTE_MAX_TEXT_INPUT];
	va_list ap;
	va_start(ap, data);
	vsnprintf_s(text, REMOTE_MAX_TEXT_INPUT-1, data, ap);
	va_end(ap);

	SLNet::BitStream str;
	str.Write((MessageID)ID_TRANSPORT_STRING);
	str.Write(text, (int) strlen(text));
	str.Write((unsigned char) 0); // Null terminate the string
	rakPeerInterface->Send(&str, MEDIUM_PRIORITY, RELIABLE_ORDERED, 0, systemAddress, (systemAddress==UNASSIGNED_SYSTEM_ADDRESS)!=0);
}
void RakNetTransport2::CloseConnection( SystemAddress systemAddress )
{
	rakPeerInterface->CloseConnection(systemAddress, true, 0);
}
Packet* RakNetTransport2::Receive( void )
{
	if (packetQueue.Size()==0)
		return 0;
	return packetQueue.Pop();
}
SystemAddress RakNetTransport2::HasNewIncomingConnection(void)
{
	if (newConnections.Size())
		return newConnections.Pop();
	return UNASSIGNED_SYSTEM_ADDRESS;
}
SystemAddress RakNetTransport2::HasLostConnection(void)
{
	if (lostConnections.Size())
		return lostConnections.Pop();
	return UNASSIGNED_SYSTEM_ADDRESS;
}
void RakNetTransport2::DeallocatePacket( Packet *packet )
{
	rakFree_Ex(packet->data, _FILE_AND_LINE_ );
	SLNet::OP_DELETE(packet, _FILE_AND_LINE_ );
}
PluginReceiveResult RakNetTransport2::OnReceive(Packet *packet)
{
	switch (packet->data[0])
	{
	case ID_TRANSPORT_STRING:
		{
			if (packet->length==sizeof(MessageID))
				return RR_STOP_PROCESSING_AND_DEALLOCATE;

			Packet *p = SLNet::OP_NEW<Packet>(_FILE_AND_LINE_);
			*p=*packet;
			p->bitSize-=8;
			p->length--;
			p->data=(unsigned char*) rakMalloc_Ex(p->length,_FILE_AND_LINE_);
			memcpy(p->data, packet->data+1, p->length);
			packetQueue.Push(p, _FILE_AND_LINE_ );

		}
		return RR_STOP_PROCESSING_AND_DEALLOCATE;
	}
	return RR_CONTINUE_PROCESSING;
}
void RakNetTransport2::OnClosedConnection(const SystemAddress &systemAddress, RakNetGUID rakNetGUID, PI2_LostConnectionReason lostConnectionReason )
{
	(void) rakNetGUID;
	(void) lostConnectionReason;
	lostConnections.Push(systemAddress, _FILE_AND_LINE_ );
}
void RakNetTransport2::OnNewConnection(const SystemAddress &systemAddress, RakNetGUID rakNetGUID, bool isIncoming)
{
	(void) rakNetGUID;
	(void) isIncoming;
	newConnections.Push(systemAddress, _FILE_AND_LINE_ );
}

#endif // _RAKNET_SUPPORT_*
