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

#include <cat/crypt/tunnel/EasyHandshake.hpp>
#include <cat/crypt/tunnel/KeyMaker.hpp>
#include <cat/time/Clock.hpp>
using namespace cat;

//// EasyHandshake

static Mutex handshake_lock;
static u32 handshake_references = 0;
static bool handshake_init_success;

bool EasyHandshake::Initialize()
{
	AutoMutex lock(handshake_lock);

	// If this is the first reference,
	if (!handshake_references++)
	{
		handshake_init_success = Clock::Initialize() && FortunaFactory::ref()->Initialize();
	}

	return handshake_init_success;
}

void EasyHandshake::Shutdown()
{
	AutoMutex lock(handshake_lock);

	// Reduce reference count; if no references remain,
	if (handshake_references > 0 && !--handshake_references)
	{
		FortunaFactory::ref()->Shutdown();
		FortunaFactory::deallocate();
		Clock::Shutdown();
	}
}

EasyHandshake::EasyHandshake()
{
	EasyHandshake::Initialize();

	// We really only need one of these per thread
	tls_math = KeyAgreementCommon::InstantiateMath(BITS);

	// Since ref() is not thread-safe usually it is called once
	// during startup before multiple threads start using this object
	tls_csprng = FortunaFactory::ref()->Create();
}

EasyHandshake::~EasyHandshake()
{
	if (tls_math) delete tls_math;
	if (tls_csprng) delete tls_csprng;

	EasyHandshake::Shutdown();
}

bool EasyHandshake::GenerateServerKey(void *out_public_key, void *out_private_key)
{
	u8 *public_key = reinterpret_cast<u8*>( out_public_key );
	u8 *private_key = reinterpret_cast<u8*>( out_private_key );

	KeyMaker bob;

	// Generate a random key pair
	return bob.GenerateKeyPair(tls_math, tls_csprng,
							   public_key, PUBLIC_KEY_BYTES,
							   private_key, PRIVATE_KEY_BYTES);
}

bool EasyHandshake::GenerateRandomNumber(void *out_num, int bytes)
{
	if (!tls_csprng) return false;

	tls_csprng->Generate(out_num, bytes);
	return true;
}


//// ServerEasyHandshake

ServerEasyHandshake::ServerEasyHandshake()
{
}

ServerEasyHandshake::~ServerEasyHandshake()
{
}

void ServerEasyHandshake::FillCookieJar(CookieJar *jar)
{
	if (tls_csprng) jar->Initialize(tls_csprng);
}

bool ServerEasyHandshake::Initialize(const void *in_public_key, const void *in_private_key)
{
	const u8 *public_key = reinterpret_cast<const u8*>( in_public_key );
	const u8 *private_key = reinterpret_cast<const u8*>( in_private_key );

	// Initialize the tunnel server object using the provided key
    return tun_server.Initialize(tls_math, tls_csprng,
								 public_key, PUBLIC_KEY_BYTES,
								 private_key, PRIVATE_KEY_BYTES);
}

bool ServerEasyHandshake::ProcessChallenge(const void *in_challenge, void *out_answer, AuthenticatedEncryption *auth_enc)
{
	const u8 *challenge = reinterpret_cast<const u8*>( in_challenge );
	u8 *answer = reinterpret_cast<u8*>( out_answer );

	// Create a key hash object on the stack
	Skein key_hash;

	// Process and validate the client challenge.  This is an expensive operation
	// where most of the magic of the handshake occurs
	if (!tun_server.ProcessChallenge(tls_math, tls_csprng,
									 challenge, CHALLENGE_BYTES,
									 answer, ANSWER_BYTES, &key_hash))
	{
		return false;
	}

	// Normally you would have the ability to key several authenticated encryption
	// objects from the same handshake, and give each one a different name.  For
	// simplicity I only allow one authenticated encryption object to be created per
	// handshake.  This would be useful for encrypting several different channels,
	// such as one handshake being used to key and encrypt a TCP stream and UDP
	// packets, or multiple TCP streams keyed from the same handshake, etc
	if (!tun_server.KeyEncryption(&key_hash, auth_enc, "NtQuerySystemInformation"))
		return false;

	return true;
}

bool ServerEasyHandshake::VerifyInitiatorIdentity(const void *in_answer /* EasyHandshake::ANSWER_BYTES */,
												  const void *in_proof /* EasyHandshake::IDENTITY_BYTES */,
												  void *out_public_key /* EasyHandshake::PUBLIC_KEY_BYTES */)
{
	const u8 *answer = reinterpret_cast<const u8*>( in_answer );
	const u8 *ident = reinterpret_cast<const u8*>( in_proof );
	u8 *public_key = reinterpret_cast<u8*>( out_public_key );

	return tun_server.VerifyInitiatorIdentity(tls_math, answer, ANSWER_BYTES, ident, IDENTITY_BYTES, public_key, PUBLIC_KEY_BYTES);
}


//// ClientEasyHandshake

ClientEasyHandshake::ClientEasyHandshake()
{
}

ClientEasyHandshake::~ClientEasyHandshake()
{
}

bool ClientEasyHandshake::Initialize(const void *in_public_key)
{
	const u8 *public_key = reinterpret_cast<const u8*>( in_public_key );

	// Initialize the tunnel client with the given public key
	return tun_client.Initialize(tls_math, public_key, PUBLIC_KEY_BYTES);
}

bool ClientEasyHandshake::SetIdentity(const void *in_public_key /* EasyHandshake::PUBLIC_KEY_BYTES */,
									  const void *in_private_key /* EasyHandshake::PRIVATE_KEY_BYTES */)
{
	const u8 *public_key = reinterpret_cast<const u8*>( in_public_key );
	const u8 *private_key = reinterpret_cast<const u8*>( in_private_key );

	// Initialize the tunnel client's identity
	return tun_client.SetIdentity(tls_math, public_key, PUBLIC_KEY_BYTES, private_key, PRIVATE_KEY_BYTES);
}

bool ClientEasyHandshake::GenerateChallenge(void *out_challenge)
{
	u8 *challenge = reinterpret_cast<u8*>( out_challenge );

	// Generate a challenge
    return tun_client.GenerateChallenge(tls_math, tls_csprng, challenge, CHALLENGE_BYTES);
}

bool ClientEasyHandshake::ProcessAnswer(const void *in_answer, AuthenticatedEncryption *auth_enc)
{
	const u8 *answer = reinterpret_cast<const u8*>( in_answer );

	// Create a key hash object on the stack
	Skein key_hash;

	// Process and validate the server's answer to our challenge.
	// This is an expensive operation
	if (!tun_client.ProcessAnswer(tls_math, answer, ANSWER_BYTES, &key_hash))
		return false;

	// Normally you would have the ability to key several authenticated encryption
	// objects from the same handshake, and give each one a different name.  For
	// simplicity I only allow one authenticated encryption object to be created per
	// handshake.  This would be useful for encrypting several different channels,
	// such as one handshake being used to key and encrypt a TCP stream and UDP
	// packets, or multiple TCP streams keyed from the same handshake, etc
	if (!tun_client.KeyEncryption(&key_hash, auth_enc, "NtQuerySystemInformation"))
		return false;

	// Erase the ephemeral private key we used for the handshake now that it is done
	tun_client.SecureErasePrivateKey();

	return true;
}

bool ClientEasyHandshake::ProcessAnswerWithIdentity(const void *in_answer, void *out_identity, AuthenticatedEncryption *auth_enc)
{
	const u8 *answer = reinterpret_cast<const u8*>( in_answer );
	u8 *ident = reinterpret_cast<u8*>( out_identity );

	// Create a key hash object on the stack
	Skein key_hash;

	// Process and validate the server's answer to our challenge.
	// This is an expensive operation
	if (!tun_client.ProcessAnswerWithIdentity(tls_math, tls_csprng, answer, ANSWER_BYTES, &key_hash, ident, IDENTITY_BYTES))
		return false;

	// Normally you would have the ability to key several authenticated encryption
	// objects from the same handshake, and give each one a different name.  For
	// simplicity I only allow one authenticated encryption object to be created per
	// handshake.  This would be useful for encrypting several different channels,
	// such as one handshake being used to key and encrypt a TCP stream and UDP
	// packets, or multiple TCP streams keyed from the same handshake, etc
	if (!tun_client.KeyEncryption(&key_hash, auth_enc, "NtQuerySystemInformation"))
		return false;

	// Erase the ephemeral private key we used for the handshake now that it is done
	tun_client.SecureErasePrivateKey();

	return true;
}
