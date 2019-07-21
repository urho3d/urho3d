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

#ifndef CAT_EASY_HANDSHAKE_HPP
#define CAT_EASY_HANDSHAKE_HPP

#include <cat/crypt/tunnel/KeyAgreementInitiator.hpp>
#include <cat/crypt/tunnel/KeyAgreementResponder.hpp>
#include <cat/crypt/cookie/CookieJar.hpp>

namespace cat {


/*
	The EasyHandshake classes implement a simplified version of my Tunnel protocol.

	This only works for single-threaded servers and only produces a single authenticated encryption
	object for each handshake.  Explanations on how to use the library with a multi-threaded
	server, and how to use one handshake to secure several TCP streams, are documented in the
	comments of these classes.


	Over the network, the handshake will look like this:

	client --> server : CHALLENGE (64 random-looking bytes)

	server --> client : ANSWER (128 random-looking bytes)

	client --> server : PROOF (32 random-looking bytes) + first encrypted packet can be appended here


	As far as coding goes, the function calls fit into the protocol like this:

	server is offline:

		During startup, both the client and server should initialize the library.
		This is necessary also just for generating keys:
		----------------------------------------------------------------
		#include <cat/AllTunnel.hpp>
		using namespace cat;

		if (!EasyHandshake::Initialize())
		{
			printf("ERROR:Unable to initialize crypto subsystem\n");
		}
		----------------------------------------------------------------

		Generate the server public and private key pairs:
		----------------------------------------------------------------
		u8 public_key[EasyHandshake::PUBLIC_KEY_BYTES];
		u8 private_key[EasyHandshake::PRIVATE_KEY_BYTES];

		EasyHandshake temp;
		temp.GenerateServerKey(public_key, private_key);
		----------------------------------------------------------------

		(keys are stored to disk for reading on start-up)

		(public key is given to the client somehow)
			+ built into the client code
			+ provided by a trusted server

	server comes online:

		----------------------------------------------------------------
		ServerEasyHandshake server_handshake;

		server_handshake.Initialize(public_key, private_key);
		----------------------------------------------------------------

	client comes online:

		----------------------------------------------------------------
		ClientEasyHandshake client_handshake;

		client_handshake.Initialize(public_key);

		u8 challenge[EasyHandshake::CHALLENGE_BYTES];

		client_handshake.GenerateChallenge(challenge);
		----------------------------------------------------------------

	client --> server : CHALLENGE (64 random-looking bytes)

		----------------------------------------------------------------
		AuthenticatedEncryption server_e;

		u8 answer[EasyHandshake::ANSWER_BYTES];

		server_handshake.ProcessChallenge(challenge, answer, &server_e);
		----------------------------------------------------------------

	server --> client : ANSWER (128 random-looking bytes)

		----------------------------------------------------------------
		AuthenticatedEncryption client_e;

		client_handshake.ProcessAnswer(answer, &client_e);

		u8 proof[EasyHandshake::PROOF_BYTES];

		client_e.GenerateProof(proof, EasyHandshake::PROOF_BYTES);
		----------------------------------------------------------------

		Encryption example:
		----------------------------------------------------------------
		// Example message encryption of "Hello".  Note that encryption
		// inflates the size of the message by OVERHEAD_BYTES.
		const int PLAINTEXT_BYTES = 5;
		const int BUFFER_BYTES = \
			PLAINTEXT_BYTES + AuthenticatedEncryption::OVERHEAD_BYTES;
		int msg_bytes = PLAINTEXT_BYTES;

		// Note that it makes room for message inflation
		const u8 message[CIPHERTEXT_BYTES] = {
			'H', 'e', 'l', 'l', 'o'
		};

		// Note the second parameter is the size of the buffer, and
		// the third parameter will be adjusted to the size of the
		// encrypted message:

		if (client_e.Encrypt(message, BUFFER_BYTES, msg_bytes))
		{
			// msg_bytes is now adjusted to be the size of the ciphertext
		}
		----------------------------------------------------------------

	client --> server : PROOF (32 random-looking bytes) + first encrypted packet can be appended here

		----------------------------------------------------------------
		server_e.ValidateProof(proof, EasyHandshake::PROOF_BYTES);
		----------------------------------------------------------------

		Decryption example:
		----------------------------------------------------------------
		int buf_bytes = msg_bytes;

		// The second parameter is the number of bytes in the encrypted message
		if (server_e.Decrypt(message, buf_bytes))
		{
			// buf_bytes is now adjusted to be the size of the plaintext
		}
		----------------------------------------------------------------

		During program termination, the client and server should clean up:
		----------------------------------------------------------------
		EasyHandshake::Shutdown();
		----------------------------------------------------------------

	NOTES:

		Once the authenticated encryption objects are created, if the messages received are always
		guaranteed to be in order, then the following flag can be set to make the object reject
		packets received out of order, which would indicate tampering:
			auth_enc.AllowOutOfOrder(false);
		By default the messages are assumed to arrive in any order up to 1024 messages out of order.

		The server similarly can encrypt messages the same way the client does in the examples.

		Encrypted messages are inflated by 11 random-looking bytes for a MAC and an IV.
		Modifications to the code can allow lower overhead if needed.

		The EasyHandshake classes are *NOT* THREAD-SAFE.

		The AuthenticatedEncryption class is *NOT* THREAD-SAFE.  Simultaneously, only ONE thread
		can be encrypting messages.  And only ONE thread can be decrypting messages.  Encryption
		and decryption are separate and safe to perform simultaneously.
*/


/*
	Common data needed for handshaking
*/
class CAT_EXPORT EasyHandshake
{
protected:
	// Normally these would be created per-thread.
	// To free memory associated with these objects just delete them.
	BigTwistedEdwards *tls_math;
	FortunaOutput *tls_csprng;

public:
	static const int BITS = 256;
	static const int BYTES = BITS / 8;
	static const int PUBLIC_KEY_BYTES = BYTES * 2;
	static const int PRIVATE_KEY_BYTES = BYTES;
	static const int CHALLENGE_BYTES = BYTES * 2; // Packet # 1 in handshake, sent to server
	static const int ANSWER_BYTES = BYTES * 4; // Packet # 2 in handshake, sent to client
	static const int PROOF_BYTES = BYTES; // Packet # 3 in handshake, sent to server
	static const int IDENTITY_BYTES = BYTES * 5; // [optional] Packet # 3 in handshake, sent to server, proves identity of client also

public:
	// Demonstrates how to allocate and free the math and prng objects
	EasyHandshake();
	~EasyHandshake();

public:
	static bool Initialize();
	static void Shutdown();

public:
	// Generate a server (public, private) key pair
	// Connecting clients will need to know the public key in order to connect
	bool GenerateServerKey(void *out_public_key /* EasyHandshake::PUBLIC_KEY_BYTES */,
						   void *out_private_key /* EasyHandshake::PRIVATE_KEY_BYTES */);

	// Fills the given buffer with a variable number of random bytes
	// Returns false on failure
	bool GenerateRandomNumber(void *out_num, int bytes);
};

/*
	Implements the simple case of a server that performs handshakes with clients
	from a single thread.  Note that this implementation is not thread-safe.
*/
class CAT_EXPORT ServerEasyHandshake : public EasyHandshake
{
	KeyAgreementResponder tun_server;

public:
	ServerEasyHandshake();
	~ServerEasyHandshake();

	// Prepare a cookie jar for hungry consumers
	void FillCookieJar(CookieJar *jar);

	// Provide the public and private key for the server, previously generated offline
	bool Initialize(const void *in_public_key /* EasyHandshake::PUBLIC_KEY_BYTES */,
					const void *in_private_key /* EasyHandshake::PRIVATE_KEY_BYTES */);

	// Process a client challenge and generate a server answer
	// Returns false if challenge was invalid
	bool ProcessChallenge(const void *in_challenge /* EasyHandshake::CHALLENGE_BYTES */,
						  void *out_answer /* EasyHandshake::ANSWER_BYTES */,
						  AuthenticatedEncryption *auth_enc);

	// Validate a client proof of identity
	// Returns false if proof was invalid
	bool VerifyInitiatorIdentity(const void *in_answer /* EasyHandshake::ANSWER_BYTES */,
								 const void *in_proof /* EasyHandshake::IDENTITY_BYTES */,
								 void *out_public_key /* EasyHandshake::PUBLIC_KEY_BYTES */);
};

/*
	Implements the simple case of a client that performs handshakes with servers
	from a single thread.  Note that this implementation is not thread-safe.
*/
class CAT_EXPORT ClientEasyHandshake : public EasyHandshake
{
	KeyAgreementInitiator tun_client;

public:
	ClientEasyHandshake();
	~ClientEasyHandshake();

	// Provide the public key for the server, acquired through some secure means
	bool Initialize(const void *in_public_key /* EasyHandshake::PUBLIC_KEY_BYTES */);

	// (optional) Provide the identity for the client
	bool SetIdentity(const void *in_public_key /* EasyHandshake::PUBLIC_KEY_BYTES */,
					 const void *in_private_key /* EasyHandshake::PRIVATE_KEY_BYTES */);

	// Generate a challenge for the server to answer
	bool GenerateChallenge(void *out_challenge /* EasyHandshake::CHALLENGE_BYTES */);

	// Process a server answer to our challenge
	// Returns false if answer was invalid
	bool ProcessAnswer(const void *in_answer /* EasyHandshake::ANSWER_BYTES */,
					   AuthenticatedEncryption *auth_enc);

	// Process a server answer to our challenge and provide a proof of client identity
	// Returns false if answer was invalid
	bool ProcessAnswerWithIdentity(const void *in_answer /* EasyHandshake::ANSWER_BYTES */,
								   void *out_identity /* EasyHandshake::IDENTITY_BYTES */,
								   AuthenticatedEncryption *auth_enc);
};


} // namespace cat

#endif // CAT_EASY_HANDSHAKE_HPP
