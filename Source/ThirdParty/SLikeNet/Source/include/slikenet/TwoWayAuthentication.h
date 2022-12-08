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

/// \file TwoWayAuthentication.h
/// \brief Implements two way authentication
/// \details Given two systems, each of whom known a common password, verify the password without transmitting it
/// This can be used to determine what permissions are should be allowed to the other system
///


#include "NativeFeatureIncludes.h"
#if _RAKNET_SUPPORT_TwoWayAuthentication==1

#ifndef __TWO_WAY_AUTHENTICATION_H
#define __TWO_WAY_AUTHENTICATION_H

// How often to change the nonce.
#define NONCE_TIMEOUT_MS 10000
// How often to check for ID_TWO_WAY_AUTHENTICATION_OUTGOING_CHALLENGE_TIMEOUT, and the minimum timeout time. Maximum is double this value.
#define CHALLENGE_MINIMUM_TIMEOUT 3000

#if LIBCAT_SECURITY==1
// From CPP FILE:
// static const int HASH_BITS = 256;
// static const int HASH_BYTES = HASH_BITS / 8;
// static const int STRENGTHENING_FACTOR = 1000;
#define TWO_WAY_AUTHENTICATION_NONCE_LENGTH 32
#define HASHED_NONCE_AND_PW_LENGTH 32
#else
#include "DR_SHA1.h"
#define TWO_WAY_AUTHENTICATION_NONCE_LENGTH 20
#define HASHED_NONCE_AND_PW_LENGTH SHA1_LENGTH
#endif

#include "PluginInterface2.h"
#include "memoryoverride.h"
#include "NativeTypes.h"
#include "string.h"
#include "DS_Hash.h"
#include "DS_Queue.h"

typedef int64_t FCM2Guid;

namespace SLNet
{
/// Forward declarations
class RakPeerInterface;

/// \brief Implements two way authentication
/// \details Given two systems, each of whom known a common password / identifier pair, verify the password without transmitting it
/// This can be used to determine what permissions are should be allowed to the other system
/// If the other system should not send any data until authentication passes, you can use the MessageFilter plugin for this. Call MessageFilter::SetAllowMessageID() including ID_TWO_WAY_AUTHENTICATION_NEGOTIATION when doing so. Also attach MessageFilter first in the list of plugins
/// \note If other systems challenges us, and fails, you will get ID_TWO_WAY_AUTHENTICATION_INCOMING_CHALLENGE_FAILED.
/// \ingroup PLUGINS_GROUP
class RAK_DLL_EXPORT TwoWayAuthentication : public PluginInterface2
{
public:
	// GetInstance() and DestroyInstance(instance*)
	STATIC_FACTORY_DECLARATIONS(TwoWayAuthentication)

	TwoWayAuthentication();
	virtual ~TwoWayAuthentication();

	/// \brief Adds a password to the list of passwords the system will accept
	/// \details Each password, which is secret and not transmitted, is identified by \a identifier.
	/// \a identifier is transmitted in plaintext with the request. It is only needed because the system supports multiple password.
	/// It is used to only hash against once password on the remote system, rather than having to hash against every known password.
	/// \param[in] identifier A unique identifier representing this password. This is transmitted in plaintext and should be considered insecure
	/// \param[in] password The password to add
	/// \return True on success, false on identifier==password, either identifier or password is blank, or identifier is already in use
	bool AddPassword(SLNet::RakString identifier, SLNet::RakString password);

	/// \brief Challenge another system for the specified identifier
	/// \details After calling Challenge, you will get back ID_TWO_WAY_AUTHENTICATION_SUCCESS, ID_TWO_WAY_AUTHENTICATION_OUTGOING_CHALLENGE_TIMEOUT, or ID_TWO_WAY_AUTHENTICATION_OUTGOING_CHALLENGE_FAILED
	/// ID_TWO_WAY_AUTHENTICATION_SUCCESS will be returned if and only if the other system has called AddPassword() with the same identifier\password pair as this system.
	/// \param[in] identifier A unique identifier representing this password. This is transmitted in plaintext and should be considered insecure
	/// \return True on success, false on remote system not connected, or identifier not previously added with AddPassword()
	bool Challenge(SLNet::RakString identifier, AddressOrGUID remoteSystem);

	/// \brief Free all memory
	void Clear(void);

	/// \internal
	virtual void Update(void);
	/// \internal
	virtual PluginReceiveResult OnReceive(Packet *packet);
	/// \internal
	virtual void OnRakPeerShutdown(void);
	/// \internal
	virtual void OnClosedConnection(const SystemAddress &systemAddress, RakNetGUID rakNetGUID, PI2_LostConnectionReason lostConnectionReason );

	/// \internal
	struct PendingChallenge
	{
		SLNet::RakString identifier;
		AddressOrGUID remoteSystem;
		SLNet::Time time;
		bool sentHash;
	};

	DataStructures::Queue<PendingChallenge> outgoingChallenges;

	/// \internal
	struct NonceAndRemoteSystemRequest
	{
		char nonce[TWO_WAY_AUTHENTICATION_NONCE_LENGTH];
		SLNet::AddressOrGUID remoteSystem;
		unsigned short requestId;
		SLNet::Time whenGenerated;
	};
	/// \internal
	struct RAK_DLL_EXPORT NonceGenerator
	{
		NonceGenerator();
		~NonceGenerator();
		void GetNonce(char nonce[TWO_WAY_AUTHENTICATION_NONCE_LENGTH], unsigned short *requestId, SLNet::AddressOrGUID remoteSystem);
		void GenerateNonce(char nonce[TWO_WAY_AUTHENTICATION_NONCE_LENGTH]);
		bool GetNonceById(char nonce[TWO_WAY_AUTHENTICATION_NONCE_LENGTH], unsigned short requestId, SLNet::AddressOrGUID remoteSystem, bool popIfFound);
		void Clear(void);
		void ClearByAddress(SLNet::AddressOrGUID remoteSystem);
		void Update(SLNet::Time curTime);

		DataStructures::List<TwoWayAuthentication::NonceAndRemoteSystemRequest*> generatedNonces;
		unsigned short nextRequestId;
	};

protected:
	void PushToUser(MessageID messageId, SLNet::RakString password, SLNet::AddressOrGUID remoteSystem);
	// Key is identifier, data is password
	DataStructures::Hash<SLNet::RakString, SLNet::RakString, 16, SLNet::RakString::ToInteger > passwords;

	SLNet::Time whenLastTimeoutCheck;

	NonceGenerator nonceGenerator;

	void OnNonceRequest(Packet *packet);
	void OnNonceReply(Packet *packet);
	PluginReceiveResult OnHashedNonceAndPassword(Packet *packet);
	void OnPasswordResult(Packet *packet);
	void Hash(char thierNonce[TWO_WAY_AUTHENTICATION_NONCE_LENGTH], SLNet::RakString password, char out[HASHED_NONCE_AND_PW_LENGTH]);
};

} // namespace SLNet

#endif

#endif // _RAKNET_SUPPORT_*
