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

// 06/15/09 began

#ifndef CAT_I_CRYPT_HASH_HPP
#define CAT_I_CRYPT_HASH_HPP

#include <cat/Platform.hpp>
#include <cstring>

namespace cat {


// Cryptographic hash functions of any size will derive from ICryptoHash and implement its public methods
class CAT_EXPORT ICryptHash
{
protected:
    int digest_bytes;

public:
    virtual ~ICryptHash() {}

    // Returns the number of bytes in a message digest produced by this hash
    CAT_INLINE int GetDigestByteCount() { return digest_bytes; }

	CAT_INLINE void CrunchString(const char *s) { Crunch(s, (int)std::strlen(s) + 1); }

public:
    // Begin a new key
    virtual bool BeginKey(int bits) = 0;

    // Start from an existing key
    virtual bool SetKey(ICryptHash *parent) = 0;

    // Begin hash function in MAC, KDF, or PRNG mode
    virtual bool BeginMAC() = 0;
    virtual bool BeginKDF() = 0;
    virtual bool BeginPRNG() = 0;

    // Crunch some message bytes
    virtual void Crunch(const void *message, int bytes) = 0;

    // Finalize the hash and prepare to generate output
    virtual void End() = 0;

    // Extended hash output mode
    virtual void Generate(void *out, int bytes, int strengthening_rounds = 0) = 0;
};


} // namespace cat

#endif // CAT_I_CRYPT_HASH_HPP
