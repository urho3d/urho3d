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

#include <cstdio>
#include <cstring>
#include <stdlib.h>
#include "slikenet/GetTime.h"
#include "slikenet/Rand.h"
#include "slikenet/Rand.h"
#include "slikenet/peerinterface.h"
#include "slikenet/MessageIdentifiers.h"

#include "slikenet/types.h"
#include "slikenet/NativeFeatureIncludes.h"
#include <assert.h>
#include "slikenet/sleep.h"
#include "slikenet/BitStream.h"
#include "slikenet/SecureHandshake.h" // Include header for secure handshake
#include "slikenet/Gets.h"
#include "slikenet/linux_adapter.h"
#include "slikenet/osx_adapter.h"
using namespace SLNet;

#if LIBCAT_SECURITY!=1
#error "Define LIBCAT_SECURITY 1 in NativeFeatureIncludesOverrides.h to enable Encryption"
#endif

void PrintOptions(void)
{
	printf("1. Generate keys and save to disk.\n");
	printf("2. Load keys from disk.\n");
	printf("3. Test peers with key.\n");
	printf("4. Test peers with key and use two-way authentication.\n");
	printf("(H)elp.\n");
	printf("(Q)uit.\n");
}

#define TEST_SERVER_ADDRSTR "127.0.0.1"
#define TEST_SERVER_PORT 6842

RakPeerInterface *rakPeer1, *rakPeer2;

void PrintPacketHeader(Packet *packet)
{
	switch (packet->data[0])
	{
		case ID_REMOTE_SYSTEM_REQUIRES_PUBLIC_KEY:
			printf("Connection request failed - Remote system requires secure connections, pass a public key to RakPeerInterface::Connect()\n");
			break;
		case ID_OUR_SYSTEM_REQUIRES_SECURITY:
			printf("Connection request failed - We passed a public key to RakPeerInterface::Connect(), but the other system did not have security turned on\n");
			break;
		case ID_PUBLIC_KEY_MISMATCH:
			printf("Connection request failed - Wrong public key passed to Connect().\n");
			break;
		case ID_CONNECTION_REQUEST_ACCEPTED:
			printf("Connection request accepted.\n");
			break;
		case ID_CONNECTION_ATTEMPT_FAILED:
			printf("Connection request FAILED.\n");
			break;
		case ID_NEW_INCOMING_CONNECTION:
			{
				char client_public_key[cat::EasyHandshake::PUBLIC_KEY_BYTES];

				printf("New incoming connection.\n");

				if (rakPeer1->GetClientPublicKeyFromSystemAddress(packet->systemAddress, client_public_key))
				{
					printf("Client public key:\n");
					for (int ii = 0; ii < (int)sizeof(client_public_key); ++ii)
						printf("%02x ", (cat::u8)client_public_key[ii]);
					printf("\n");
				}
				else
				{
					printf("Server: New connected client provided no public key. (This is an error if you are doing two-way authentication)\n");
				}

				// Transmit test message
				SLNet::BitStream testBlockLargerThanMTU;
				testBlockLargerThanMTU.Write((MessageID) ID_USER_PACKET_ENUM);
				testBlockLargerThanMTU.PadWithZeroToByteLength(10000);
				rakPeer1->Send(&testBlockLargerThanMTU, HIGH_PRIORITY, RELIABLE_ORDERED, 0, packet->systemAddress, false);
			}
			break;
		case ID_USER_PACKET_ENUM:
			printf("Got test message\n");
			break;
		case ID_DISCONNECTION_NOTIFICATION:
			printf("RakPeer - The system specified in Packet::systemAddress has disconnected from us.  For the client, this would mean the server has shutdown.\n");
			break;
		default:
			printf("Got type %i : ", (int)packet->data[0]);
			for (int ii = 0; ii < (int)packet->length; ++ii)
				printf("%02x ", (cat::u8)packet->data[ii]);
			printf("\n");
			break;
	}
}

int main(void)
{
	char str[256];
	bool keyLoaded;

	bool doTwoWayAuthentication;
	FILE *fp;
	rakPeer1=RakPeerInterface::GetInstance();
	rakPeer2=RakPeerInterface::GetInstance();
	Packet *packet;
	bool peer1GotMessage, peer2GotMessage;

	keyLoaded=false;

	printf("Demonstrates how to setup RakNet to use secure connections\n");
	printf("Also shows how to read and write keys to and from disk\n");
	printf("Difficulty: Intermediate\n\n");

	printf("Select option:\n");
	PrintOptions();

	cat::EasyHandshake handshake;
	char public_key[cat::EasyHandshake::PUBLIC_KEY_BYTES];
	char private_key[cat::EasyHandshake::PRIVATE_KEY_BYTES];

	// Optional: used only for two-way authentication mode (a slower mode not recommended for normal client-server or peer-peer connections)
	char client_public_key[cat::EasyHandshake::PUBLIC_KEY_BYTES];
	char client_private_key[cat::EasyHandshake::PRIVATE_KEY_BYTES];

	for(;;)
	{
		Gets(str, sizeof(str));

		if (str[0]=='1')
		{
			printf("Generating keys...");

			// Generate a (public, private) server key pair
			if (!handshake.GenerateServerKey(public_key, private_key))
			{
				printf("ERROR:Unable to generate server keys for some reason!\n");
				keyLoaded=false;
			}
			else
			{
				keyLoaded=true;
				printf("Keys generated.  Save to disk? (y/n)\n");

				Gets(str, sizeof(str));
				if (str[0]=='y' || str[0]=='Y')
				{
						printf("Enter filename to save public key to: ");
					Gets(str, sizeof(str));
					if (str[0])
					{
						printf("Writing public key... ");
						fopen_s(&fp, str, "wb");
							fwrite(public_key, sizeof(public_key), 1, fp);
						fclose(fp);
						printf("Done.\n");
					}
					else
						printf("\nKey not written.\n");

					printf("Enter filename to save private key to: ");
					Gets(str, sizeof(str));
					if (str[0])
					{
						printf("Writing private key... ");
						fopen_s(&fp, str, "wb");
							fwrite(private_key, sizeof(private_key), 1, fp);
						fclose(fp);
						printf("Done.\n");
					}
					else
						printf("\nKey not written.\n");
				}
			}
			PrintOptions();
		}
		else if (str[0]=='2')
		{
			printf("Enter filename to load public key from: ");
			Gets(str, sizeof(str));
			if (str[0])
			{
				if (fopen_s(&fp, str, "rb") == 0)
				{
					printf("Loading public key... ");
					fread(public_key, sizeof(public_key), 1, fp);
					fclose(fp);
					printf("Done.\n");

					printf("Enter filename to load private key from: ");
					Gets(str, sizeof(str));
					if (str[0])
					{
						if (fopen_s(&fp, str, "rb") == 0)
						{
							printf("Loading private key... ");
							fread(private_key, sizeof(private_key), 1, fp);
							fclose(fp);
							printf("Done.\n");
							keyLoaded=true;
						}
						else
						{
							printf("ERROR:Failed to open %s.\n", str);
						}
					}
					else
						printf("Not loading private key.\n");
				}
				else
				{
					printf("ERROR:Failed to open %s.\n", str);
				}
			}
			else
				printf("Not loading public keys.\n");

			PrintOptions();
		}
		else if (str[0]=='3' || str[0] == '4')
		{
			bool run_test = true;

			// NOTE: Reiterating, normally you should not use two-way authentication for client-server or peer-peer applications
			// as it only makes sense for server-server connections that rarely occur or if you know what you are doing.
			doTwoWayAuthentication = (str[0] == '4');

			if (keyLoaded)
			{
				// Tell Peer1 to use the key pair
				if (!rakPeer1->InitializeSecurity(public_key, private_key, doTwoWayAuthentication))
				{
					printf("ERROR:Public/private keys are invalid!\n");

					run_test = false;
				}
			}
			else
			{
				printf("Generating server keys...");

				// Generate a (public, private) server key pair
				if (!handshake.GenerateServerKey(public_key, private_key))
				{
					printf("ERROR:Unable to generate server keys for some reason!\n");

					run_test = false;
				}
				else
				{
					printf("Key generation complete.\n");

					// Tell Peer1 to use the key pair
					if (!rakPeer1->InitializeSecurity(public_key, private_key, doTwoWayAuthentication))
					{
						printf("ERROR:Public/private keys are invalid!\n");

						run_test = false;
					}
				}
			}

			if (str[0] == '4')
			{
				printf("Generating client keys...");

				// Generate a (public, private) server key pair
				if (!handshake.GenerateServerKey(client_public_key, client_private_key))
				{
					printf("ERROR:Unable to generate client keys for some reason!\n");

					run_test = false;
				}
				else
				{
					printf("Key generation complete.\n");
				}
			}

			if (!run_test)
			{
				printf("Unable to run test due to error\n");
			}
			else
			{
				printf("Initializing peers.\n");
				SocketDescriptor socketDescriptor(TEST_SERVER_PORT,0);
				rakPeer1->Startup(8,&socketDescriptor, 1);
				rakPeer1->SetMaximumIncomingConnections(8);
				socketDescriptor.port=0;
				rakPeer2->Startup(1,&socketDescriptor, 1);
				printf("Connecting to server with known public key...\n");

				// Pass in the public key on Connect()
				PublicKey pk;
				pk.remoteServerPublicKey = public_key;

				if (str[0] == '4')
				{
					pk.publicKeyMode = PKM_USE_TWO_WAY_AUTHENTICATION; // Optional not recommended mode
					pk.myPublicKey = client_public_key;
					pk.myPrivateKey = client_private_key;
				}
				else
				{
					pk.publicKeyMode = PKM_USE_KNOWN_PUBLIC_KEY; // Recommended mode
				}

				if (CONNECTION_ATTEMPT_STARTED != rakPeer2->Connect(TEST_SERVER_ADDRSTR, TEST_SERVER_PORT, 0, 0, &pk))
				{
					printf("ERROR: Connect() returned false - invalid public key most likely\n");
				}
				printf("Running connection for 12 seconds.\n");

				peer1GotMessage=false;
				peer2GotMessage=false;
				TimeMS time = SLNet::GetTimeMS() + 12000;
				while (SLNet::GetTimeMS() < time)
				{
					packet=rakPeer1->Receive();
					if (packet)
					{
						peer1GotMessage=true;
						printf("Host got: ");
						PrintPacketHeader(packet);
#if defined(_DEBUG) && !defined(__native_client__)
						if (doTwoWayAuthentication)
						{
							char client_public_key_copy[cat::EasyHandshake::PUBLIC_KEY_BYTES];
							RakAssert(rakPeer1->GetClientPublicKeyFromSystemAddress(packet->systemAddress, client_public_key_copy)==true)
						}
#endif
						rakPeer1->DeallocatePacket(packet);
					}
					packet=rakPeer2->Receive();
					if (packet)
					{
						peer2GotMessage=true;
						printf("Connecting system got: ");
						PrintPacketHeader(packet);
#if defined(_DEBUG) && !defined(__native_client__)
						if (doTwoWayAuthentication)
						{
							char client_public_key_copy[cat::EasyHandshake::PUBLIC_KEY_BYTES];
							RakAssert(rakPeer2->GetClientPublicKeyFromSystemAddress(packet->systemAddress, client_public_key_copy)==true)
						}
#endif
						rakPeer2->DeallocatePacket(packet);
					}

					RakSleep(30);
				}

				if (peer1GotMessage==false)
						printf("ERROR: Host got no packets\n");
				if (peer2GotMessage==false)
						printf("ERROR: Connecting system got no packets\n");

				if (peer1GotMessage && peer2GotMessage)
						printf("Test successful as long as you got no error messages\n");
				rakPeer2->Shutdown(0);
				rakPeer1->Shutdown(0);
			}
			PrintOptions();
		}
		else if (str[0]=='h' || str[0]=='H')
		{
			PrintOptions();
		}
		else if (str[0]=='q' || str[0]=='Q')
			break;

		str[0]=0;
	}

	RakPeerInterface::DestroyInstance(rakPeer1);
	RakPeerInterface::DestroyInstance(rakPeer2);
}
