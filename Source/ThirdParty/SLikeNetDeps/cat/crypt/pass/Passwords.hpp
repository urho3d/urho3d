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

#ifndef CAT_PASSWORDS_HPP
#define CAT_PASSWORDS_HPP

#include <cat/rand/IRandom.hpp>

namespace cat {


/*
	Why are passwords needed?

		Passwords allow the client identity to be proved to the server.  Usually
		the server identity is already proven by a secure connection, but the
		client identity is unproven until a password is provided.

		This could be done using signatures with two-way authentication in the
		secure connection establishment, however this is very slow and roughly
		doubles the work a server has to do to accept a connection.

	Passwords seem simple to implement at first but then you start imagining all
	the "what ifs":

	What if the password database is stolen?

		The user passwords had better not be stored in plaintext!
		So they must be hashed.

	What if two users have the same password?

		They would look the same hashed, so hash in the name with the password.

	What if name:password for two users is "me : pass" and "m : epass" ?

		They would look the same hashed, so insert a separator between the two
		before hashing, as in "me\r\npass" instead of just hashing "mepass".

	What if someone tries to crack the passwords?

		The password hash should be strengthened to make it harder to crack,
		by applying the hash function repeatedly.  This does reduce the number of
		bits of entropy due to non-ideal hash function collisions, but this small
		effect is offset by the added difficulty to crack the password.

	What if the user has a common name like "dave"?

		The password hash should be salted to avoid falling to rainbow tables.

	What if the attacker tries to use the stolen password hash to log into the server?

		The client provides a hash pre-image during login, so the attacker would need
		to reverse the hash to do this, which is harder than cracking the password.

	What if an attacker has a way to actively or passively listen to login attempts?

		Then they would be able to steal the hash pre-image which would offer some
		amount of text password protection but would allow the attacker to log in
		as the user without knowing the password.

		Rainbow tables can be used to crack the pre-image to determine the password.

		If the connection is secure then the client has verified the server identity
		and these attacks are only possible through software bugs in the server.


	Protocol Description:

		H: 256-bit hash function Skein-256
		c: Client
		s: Server
		X: Strengthening factor


	Protocol 1: Creating a User Account

		c: Choose a name N
		c: Choose a password P
		c: Calculate I = H("N\r\nP") strengthened X times

		c2s CREATE_ACCOUNT || N || I (32 by)

		s: Verify account is not taken, then creates an account in the database
		s: Generate a 32-bit random salt S
		s: Calculate J = H(S || I)
		s: Store N, J and S in the account

		s2c ACCOUNT_CREATE_SUCCESS


	Protocol 2: Logging into a User Account

		c: Choose a name N
		c: Choose a password P
		c: Calculate I = H("N\r\nP") strengthened X times

		c2s LOGIN_REQUEST || N || I (32 by)

		s: Verify user name exists in account database
		s: Retrieve J, S from the account database
		s: Calculate J' = H(S || I)
		s: Verify J = J'

		s2c LOGIN_SUCCESS


	What if the user creates an account through a website?

		The server-side script on the website should execute a program that runs
		Protocol 1 to create the user account.

	Why use this sort of password authentication + Tunnel instead of SRP?

		Performance.  The Tunnel key agreement takes much less CPU time than SRP
		and authenticates the server, which allows this protocol to be run without
		any disadvantages.
*/


class PasswordBase
{
public:
	static const int HASH_BITS = 256;
	static const int HASH_BYTES = HASH_BITS / 8;
	static const int STRENGTHENING_FACTOR = 1000;
};


class PasswordCreator : public PasswordBase
{
public:
	// Hash a password for transmission to the server during account creation or login
	// NOTE: You should make the name all lowercase before passing it in
	// Returns false on failure
	bool HashPassword(const void *in_name, int name_bytes,
					  const void *in_password, int password_bytes,
					  void *out_hash /* 32 bytes */);

	// This version accepts non-unicode C strings with nul-terminators
	// It converts the name to lowercase internally
	bool HashPasswordString(const char *in_name,
							const char *in_password,
							void *out_hash /* 32 bytes */);
};

class PasswordVerifier : public PasswordBase
{
public:
	// Salt a hash for storage in the account database during account creation
	// Generates a 32-bit salt and a 256-bit hash for storage
	// Returns false on failure
	bool SaltHash(IRandom *prng,
				  const void *in_hash /* 32 bytes */,
				  void *out_salted_hash /* 32 bytes */,
				  u32 *out_salt /* 4 bytes */);

	// Given the stored salted hash and salt, verify the client's password hash during login
	// Returns false if password is incorrect
	bool VerifyHash(const void *in_hash /* 32 bytes */,
					const void *in_salted_hash /* 32 bytes */,
					u32 in_salt /* 4 bytes */);
};


} // namespace cat

#endif // CAT_PASSWORDS_HPP
