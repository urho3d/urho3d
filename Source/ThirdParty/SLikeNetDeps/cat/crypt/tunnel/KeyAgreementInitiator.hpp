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

#ifndef CAT_KEY_AGREEMENT_INITIATOR_HPP
#define CAT_KEY_AGREEMENT_INITIATOR_HPP

#include <cat/crypt/tunnel/KeyAgreement.hpp>
#include <cat/crypt/tunnel/AuthenticatedEncryption.hpp>

namespace cat {


class CAT_EXPORT KeyAgreementInitiator : public KeyAgreementCommon
{
    Leg *B; // Responder's public key (pre-shared with initiator)
    Leg *a; // Initiator's private key (kept secret)
    Leg *A; // Initiator's public key (shared with responder in Challenge message)
    Leg *hB; // h*B
    Leg *G_MultPrecomp; // Precomputed table for multiplication
    Leg *B_MultPrecomp; // Precomputed table for multiplication
    Leg *Y_MultPrecomp; // Precomputed table for multiplication
	Leg *A_neutral; // Endian-neutral A
	Leg *B_neutral; // Endian-neutral B

	// Identity data
	Leg *I_private; // Initiator's identity private key
	Leg *I_public; // Endian-neutral initiator's identity public key

    bool AllocateMemory();
    void FreeMemory();

public:
    KeyAgreementInitiator();
    ~KeyAgreementInitiator();

    bool Initialize(BigTwistedEdwards *math,
					const u8 *responder_public_key, int public_bytes);

	// Call after Initialize()
	bool SetIdentity(BigTwistedEdwards *math,
					 const u8 *initiator_public_key, int public_bytes,
					 const u8 *initiator_private_key, int private_bytes);

public:
    bool GenerateChallenge(BigTwistedEdwards *math, FortunaOutput *csprng,
						   u8 *initiator_challenge, int challenge_bytes);

    bool ProcessAnswer(BigTwistedEdwards *math,
					   const u8 *responder_answer, int answer_bytes,
                       Skein *key_hash);

	// Will fail if SetIdentity() has not been called
    bool ProcessAnswerWithIdentity(BigTwistedEdwards *math, FortunaOutput *csprng,
								   const u8 *responder_answer, int answer_bytes,
								   Skein *key_hash,
								   u8 *identity_proof, int proof_bytes);

	CAT_INLINE bool KeyEncryption(Skein *key_hash, AuthenticatedEncryption *auth_enc, const char *key_name)
	{
		return auth_enc->SetKey(KeyBytes, key_hash, true, key_name);
	}

	// Erase the private key after handshake completes
	// Also done as this object is destroyed
	void SecureErasePrivateKey();

public:
	bool Verify(BigTwistedEdwards *math,
				const u8 *message, int message_bytes,
				const u8 *signature, int signature_bytes);
};


} // namespace cat

#endif // CAT_KEY_AGREEMENT_INITIATOR_HPP
