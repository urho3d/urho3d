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

#include <cat/crypt/tunnel/KeyAgreementInitiator.hpp>
#include <cat/crypt/SecureCompare.hpp>
#include <cat/port/AlignedAlloc.hpp>
using namespace cat;

bool KeyAgreementInitiator::AllocateMemory()
{
    FreeMemory();

    B = new (Aligned::ii) Leg[KeyLegs * 17];
    a = B + KeyLegs*4;
    A = a + KeyLegs;
    hB = A + KeyLegs*4;
	A_neutral = hB + KeyLegs*4;
	B_neutral = A_neutral + KeyLegs*2;

    return !!B;
}

void KeyAgreementInitiator::FreeMemory()
{
    if (B)
    {
        CAT_CLR(a, KeyBytes);
        Aligned::Delete(B);
        B = 0;
    }

	if (G_MultPrecomp)
	{
		Aligned::Delete(G_MultPrecomp);
		G_MultPrecomp = 0;
 	}

	if (B_MultPrecomp)
	{
		Aligned::Delete(B_MultPrecomp);
		B_MultPrecomp = 0;
	}

	if (Y_MultPrecomp)
	{
		Aligned::Delete(Y_MultPrecomp);
		Y_MultPrecomp = 0;
	}

	if (I_private)
	{
		Aligned::Delete(I_private);
		I_private = 0;
	}

	if (I_public)
	{
		Aligned::Delete(I_public);
		I_public = 0;
	}
}

KeyAgreementInitiator::KeyAgreementInitiator()
{
    B = 0;
    G_MultPrecomp = 0;
    B_MultPrecomp = 0;
    Y_MultPrecomp = 0;
	I_private = 0;
	I_public = 0;
}

KeyAgreementInitiator::~KeyAgreementInitiator()
{
    FreeMemory();
}

void KeyAgreementInitiator::SecureErasePrivateKey()
{
	if (B) CAT_CLR(a, KeyBytes);
}

bool KeyAgreementInitiator::Initialize(BigTwistedEdwards *math, const u8 *responder_public_key, int public_bytes)
{
#if defined(CAT_USER_ERROR_CHECKING)
	if (!math) return false;
#endif

	int bits = math->RegBytes() * 8;

    // Validate and accept number of bits
    if (!KeyAgreementCommon::Initialize(bits))
        return false;

    // Allocate memory space for the responder's key pair and generator point
    if (!AllocateMemory())
        return false;

    // Verify that inputs are of the correct length
    if (public_bytes != KeyBytes*2) return false;

	// Precompute a table for multiplication
	G_MultPrecomp = math->PtMultiplyPrecompAlloc(6);
    if (!G_MultPrecomp) return false;
    math->PtMultiplyPrecomp(math->GetGenerator(), 6, G_MultPrecomp);

    // Unpack the responder's public key
    if (!math->LoadVerifyAffineXY(responder_public_key, responder_public_key + KeyBytes, B))
        return false;

	// Verify public point is not identity element
	if (math->IsAffineIdentity(B))
		return false;

	memcpy(B_neutral, responder_public_key, KeyBytes*2);

	// Precompute a table for multiplication
	B_MultPrecomp = math->PtMultiplyPrecompAlloc(6);
	if (!B_MultPrecomp) return false;
	math->PtUnpack(B);
    math->PtMultiplyPrecomp(B, 6, B_MultPrecomp);

    // hB = h * B for small subgroup attack resistance
    math->PtDoubleZ1(B, hB);
    math->PtEDouble(hB, hB);

    return true;
}

bool KeyAgreementInitiator::SetIdentity(BigTwistedEdwards *math,
										const u8 *initiator_public_key, int public_bytes,
										const u8 *initiator_private_key, int private_bytes)
{
#if defined(CAT_USER_ERROR_CHECKING)
	if (!math || public_bytes != KeyBytes*2 || private_bytes != KeyBytes) return false;
#endif

	Leg *I_temp = math->Get(0);

	// Unpack the initiator's public key
	if (!math->LoadVerifyAffineXY(initiator_public_key, initiator_public_key + KeyBytes, I_temp))
		return false;

	// Verify public point is not identity element
	if (math->IsAffineIdentity(I_temp))
		return false;

	// Allocate space for private key if needed
	if (!I_private)
	{
		I_private = (Leg*)Aligned::Acquire(KeyBytes);
		if (!I_private) return false;
	}

	// Allocate space for public key if needed
	if (!I_public)
	{
		I_public = (Leg*)Aligned::Acquire(KeyBytes*2);
		if (!I_public) return false;
	}

	// Copy the endian-neutral public key
	memcpy(I_public, initiator_public_key, KeyBytes*2);

	// Load the private key
	math->Load(initiator_private_key, KeyBytes, I_private);

	return true;
}

bool KeyAgreementInitiator::GenerateChallenge(BigTwistedEdwards *math, FortunaOutput *csprng,
											  u8 *initiator_challenge, int challenge_bytes)
{
#if defined(CAT_USER_ERROR_CHECKING)
	// Verify that inputs are of the correct length
	if (!math || !csprng || challenge_bytes != KeyBytes*2) return false;
#endif

    // a = initiator private key
	GenerateKey(math, csprng, a);

    // A = a * G
    math->PtMultiply(G_MultPrecomp, 6, a, 0, A);
    math->PtNormalize(A, A);

    math->SaveAffineXY(A, initiator_challenge, initiator_challenge + KeyBytes);

	memcpy(A_neutral, initiator_challenge, KeyBytes*2);

    return true;
}

bool KeyAgreementInitiator::ProcessAnswer(BigTwistedEdwards *math,
										  const u8 *responder_answer, int answer_bytes,
                                          Skein *key_hash)
{
#if defined(CAT_USER_ERROR_CHECKING)
	// Verify that inputs are of the correct length
	if (!math || answer_bytes < KeyBytes*3) return false;
#endif

    Leg *Y = math->Get(0);
    Leg *S = math->Get(4);
    Leg *T = math->Get(8);
    Leg *hY = math->Get(12);
    Leg *ah = math->Get(16);

    // Load the responder's affine point Y
    if (!math->LoadVerifyAffineXY(responder_answer, responder_answer + KeyBytes, Y))
        return false;

	// Verify the point is not the additive identity (will never happen unless being attacked)
	if (math->IsAffineIdentity(Y))
		return false;

    // hY = h * Y for small subgroup attack resistance
    math->PtDoubleZ1(Y, hY);
    math->PtEDouble(hY, hY);

	// Precompute a table for multiplication
	if (!Y_MultPrecomp)
	{
		Y_MultPrecomp = math->PtMultiplyPrecompAlloc(6);
		if (!Y_MultPrecomp) return false;
	}

	// S = H(A,B,Y,r)
	if (!key_hash->BeginKey(KeyBits))
		return false;
	key_hash->Crunch(A_neutral, KeyBytes*2); // A
	key_hash->Crunch(B_neutral, KeyBytes*2); // B
	key_hash->Crunch(responder_answer, KeyBytes*3); // Y,r
	key_hash->End();
	key_hash->Generate(S, KeyBytes);
	math->Load(S, KeyBytes, S);

	// Insure S >= 1000
	if (math->LessX(S, 1000))
		return false;

	// ah = a*h
	if (math->Double(a, ah))
		math->Subtract(ah, math->GetCurveQ(), ah);
	if (math->Double(ah, ah))
		math->Subtract(ah, math->GetCurveQ(), ah);

	// T = AffineX(ah * B + S*a * hY)
	math->MulMod(S, a, math->GetCurveQ(), S);
	math->PtMultiplyPrecomp(hY, 6, Y_MultPrecomp);
	math->PtSiMultiply(B_MultPrecomp, Y_MultPrecomp, 6, ah, 0, S, 0, T);
	math->SaveAffineX(T, T);

	// k = H(d,T)
	if (!key_hash->BeginKDF())
		return false;
	key_hash->Crunch(T, KeyBytes);
	key_hash->End();

	// Verify initiator proof of key
	Skein mac;

	if (!mac.SetKey(key_hash) || !mac.BeginMAC()) return false;
	mac.CrunchString("shfolder.dll");
	mac.End();

	u8 expected[KeyAgreementCommon::MAX_BYTES];
	mac.Generate(expected, KeyBytes);

	return SecureEqual(expected, responder_answer + KeyBytes * 3, KeyBytes);
}

bool KeyAgreementInitiator::ProcessAnswerWithIdentity(BigTwistedEdwards *math, FortunaOutput *csprng,
													  const u8 *responder_answer, int answer_bytes,
													  Skein *key_hash,
													  u8 *identity_proof, int proof_bytes)
{
	// Process answer first and fail out if needed
	if (!ProcessAnswer(math, responder_answer, answer_bytes, key_hash))
		return false;

#if defined(CAT_USER_ERROR_CHECKING)
	// Verify that inputs are of the correct length
	if (!csprng || proof_bytes != KeyBytes*5) return false;
#endif

	// Fill endian-neutral public key for initiator
	memcpy(identity_proof, I_public, KeyBytes * 2);

	// Fill initiator's random nonce
	csprng->Generate(identity_proof + KeyBytes * 2, KeyBytes);

	// Sign() code from KeyAgreementResponder.cpp:

	Leg *k = math->Get(0);
	Leg *K = math->Get(1);
	Leg *e = math->Get(5);
	Leg *s = math->Get(6);

	do {

		do {

			// k = ephemeral key
			GenerateKey(math, csprng, k);

			// K = k * G
			math->PtMultiply(G_MultPrecomp, 6, k, 0, K);
			math->SaveAffineX(K, K);

			// e = H(IRN || RRN || K)
			Skein H;

			if (!H.BeginKey(KeyBits)) return false;
			H.Crunch(identity_proof + KeyBytes * 2, KeyBytes); // client random number
			H.Crunch(responder_answer + KeyBytes * 2, KeyBytes); // server random number
			H.Crunch(K, KeyBytes);
			H.End();
			H.Generate(identity_proof + KeyBytes * 3, KeyBytes);

			math->Load(identity_proof + KeyBytes * 3, KeyBytes, e);

			// e = e (mod q), for checking if it is congruent to q
			while (!math->Less(e, math->GetCurveQ()))
				math->Subtract(e, math->GetCurveQ(), e);

		} while (math->IsZero(e));

		// s = I_private * e (mod q)
		math->MulMod(I_private, e, math->GetCurveQ(), s);

		// s = -s (mod q)
		if (!math->IsZero(s)) math->Subtract(math->GetCurveQ(), s, s);

		// s = s + k (mod q)
		if (math->Add(s, k, s))
			while (!math->Subtract(s, math->GetCurveQ(), s));
		while (!math->Less(s, math->GetCurveQ()))
			math->Subtract(s, math->GetCurveQ(), s);

	} while (math->IsZero(s));

	math->Save(s, identity_proof + KeyBytes * 4, KeyBytes);

	// Erase the ephemeral secret from memory
	math->CopyX(0, k);

	/*
		Format of identity buffer:

		256-bit security: [Initiator Public Key] (64) || [Initiator Random Number] (32) || [Signature] (64)
	*/

	return true;
}

bool KeyAgreementInitiator::Verify(BigTwistedEdwards *math,
								   const u8 *message, int message_bytes,
								   const u8 *signature, int signature_bytes)
{
#if defined(CAT_USER_ERROR_CHECKING)
	// Verify that inputs are of the correct length
	if (!math || signature_bytes != KeyBytes*2) return false;
#endif

    Leg *e = math->Get(0);
    Leg *s = math->Get(1);
    Leg *Kp = math->Get(2);
    Leg *ep = math->Get(6);

	// Load e, s from signature
	math->Load(signature, KeyBytes, e);
	math->Load(signature + KeyBytes, KeyBytes, s);

	// e = e (mod q), for checking if it is congruent to q
	while (!math->Less(e, math->GetCurveQ()))
		math->Subtract(e, math->GetCurveQ(), e);

	// Check e, s are in the range [1,q-1]
	if (math->IsZero(e) || math->IsZero(s) ||
		!math->Less(e, math->GetCurveQ()) ||
		!math->Less(s, math->GetCurveQ()))
	{
		return false;
	}

	// K' = s*G + e*B
	math->PtSiMultiply(G_MultPrecomp, B_MultPrecomp, 6, s, 0, e, 0, Kp);
	math->SaveAffineX(Kp, Kp);

	// e' = H(M || K')
	Skein H;
	if (!H.BeginKey(KeyBits)) return false;
	H.Crunch(message, message_bytes);
	H.Crunch(Kp, KeyBytes);
	H.End();
	H.Generate(ep, KeyBytes);

	// Verify that e' == e
	return SecureEqual(signature, ep, KeyBytes);
}
