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

#include <cat/crypt/pass/Passwords.hpp>
#include <cat/crypt/hash/Skein.hpp>
#include <cat/lang/Strings.hpp>
using namespace cat;

//// PasswordCreator

bool PasswordCreator::HashPassword(const void *in_name, int name_bytes,
								   const void *in_password, int password_bytes,
								   void *out_hash /* 32 bytes */)
{
#if defined(CAT_USER_ERROR_CHECKING)
	if (!in_name || !in_password || !out_hash || name_bytes < 0 || password_bytes < 0) return false;
#endif

	Skein hash;

	if (!hash.BeginKey(HASH_BITS)) return false;
	hash.Crunch(in_name, name_bytes);
	hash.Crunch("\r:\n", 3);
	hash.Crunch(in_password, password_bytes);
	hash.End();
	hash.Generate(out_hash, HASH_BYTES, STRENGTHENING_FACTOR);

	return true;
}

bool PasswordCreator::HashPasswordString(const char *in_name,
										 const char *in_password,
										 void *out_hash /* 32 bytes */)
{
	int name_bytes = (int)strlen(in_name);
	int password_bytes = (int)strlen(in_password);

	// Convert name to lower case and count characters
	char *lcase_name = new char[name_bytes + 1];

	CopyToLowercaseString(in_name, lcase_name);

	bool success = HashPassword(lcase_name, name_bytes, in_password, password_bytes, out_hash);

	delete []lcase_name;

	return success;
}

//// PasswordVerifier

bool PasswordVerifier::SaltHash(IRandom *prng,
								const void *in_hash /* 32 bytes */,
								void *out_salted_hash /* 32 bytes */,
								u32 *out_salt /* 4 bytes */)
{
#if defined(CAT_USER_ERROR_CHECKING)
	if (!prng || !in_hash || !out_salted_hash || !out_salt) return false;
#endif

	Skein hash;

	*out_salt = prng->Generate();

	if (!hash.BeginKey(HASH_BITS)) return false;
	hash.Crunch(in_hash, HASH_BYTES);
	hash.Crunch(out_salt, sizeof(*out_salt));
	hash.End();
	hash.Generate(out_salted_hash, HASH_BYTES);

	return true;
}

bool PasswordVerifier::VerifyHash(const void *in_hash /* 32 bytes */,
								  const void *in_salted_hash /* 32 bytes */,
								  u32 in_salt /* 4 bytes */)
{
#if defined(CAT_USER_ERROR_CHECKING)
	if (!in_hash || !in_salted_hash) return false;
#endif

	Skein hash;
	u8 Jp[HASH_BYTES];

	if (!hash.BeginKey(HASH_BITS)) return false;
	hash.Crunch(&in_salt, sizeof(in_salt));
	hash.Crunch(in_hash, HASH_BYTES);
	hash.End();
	hash.Generate(Jp, HASH_BYTES);

	return cat::SecureEqual(in_salted_hash, Jp, HASH_BYTES);
}
