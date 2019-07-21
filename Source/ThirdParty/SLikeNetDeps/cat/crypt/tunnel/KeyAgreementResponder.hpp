/*
	Copyright (c) 2009-2010 Christopher A. Taylor.  All rights reserved.

	Redistribution and use in source and binary forms, with or without
	modification, are permitted provided that the following conditions are met:

	* Redistributions of source code must retain the above copyright notice,
	  this list of conditions and the following disclaimer.
	* Redistributions in binary form must reproduce the above copyright notice,
	  this list of conditions and the following disclaimer in the documentation
	  and/or other materials provided with the distribution.
	* Neither the name of LibCat nor the names of its contributors may be used
	  to endorse or promote products derived from this software without
	  specific prior written permission.

	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
	AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
	IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
	ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
	LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
	CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
	SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
	INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
	CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
	ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
	POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef CAT_KEY_AGREEMENT_RESPONDER_HPP
#define CAT_KEY_AGREEMENT_RESPONDER_HPP

#include <cat/crypt/tunnel/KeyAgreement.hpp>
#include <cat/crypt/tunnel/AuthenticatedEncryption.hpp>
#include <cat/threads/Atomic.hpp>

#if defined(CAT_NO_ATOMIC_ADD) || defined(CAT_NO_ATOMIC_SET)
# include <cat/threads/Mutex.hpp>
# define CAT_NO_ATOMIC_RESPONDER
#endif

namespace cat {


class CAT_EXPORT KeyAgreementResponder : public KeyAgreementCommon
{
    Leg *b; // Responder's private key (kept secret)
    Leg *B; // Responder's public key (pre-shared with initiator)
	Leg *B_neutral; // Endian-neutral B
    Leg *G_MultPrecomp; // 8-bit table for multiplication
    Leg *y[2]; // Responder's ephemeral private key (kept secret)
    Leg *Y_neutral[2]; // Responder's ephemeral public key (shared online with initiator)

#if defined(CAT_NO_ATOMIC_RESPONDER)
	Mutex m_thread_id_mutex;
#endif // CAT_NO_ATOMIC_RESPONDER

	volatile u32 ChallengeCount;
	volatile u32 ActiveY;

	void Rekey(BigTwistedEdwards *math, FortunaOutput *csprng);
    bool AllocateMemory();
    void FreeMemory();

public:
    KeyAgreementResponder();
    ~KeyAgreementResponder();

    bool Initialize(BigTwistedEdwards *math, FortunaOutput *csprng,
					const u8 *responder_public_key, int public_bytes,
                    const u8 *responder_private_key, int private_bytes);

public:
    bool ProcessChallenge(BigTwistedEdwards *math, FortunaOutput *csprng,
						  const u8 *initiator_challenge, int challenge_bytes,
                          u8 *responder_answer, int answer_bytes, Skein *key_hash);

	inline bool KeyEncryption(Skein *key_hash, AuthenticatedEncryption *auth_enc, const char *key_name)
	{
		return auth_enc->SetKey(KeyBytes, key_hash, false, key_name);
	}

	// Public key is filled if proof succeeds, and will return true
	bool VerifyInitiatorIdentity(BigTwistedEdwards *math,
								 const u8 *responder_answer, int answer_bytes,
								 const u8 *proof, int proof_bytes,
								 u8 *public_key, int public_bytes);

public:
    bool Sign(BigTwistedEdwards *math, FortunaOutput *csprng,
			  const u8 *message, int message_bytes,
			  u8 *signature, int signature_bytes);
};


} // namespace cat

#endif // CAT_KEY_AGREEMENT_RESPONDER_HPP
