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

/*
    HMAC-MD5 is still secure despite the ease of producing collisions in MD5.
    See Mihir Bellare paper "New Proofs for NMAC and HMAC: Security without Collision-Resistance" (June 2006)

    Using HMAC construction:
        HMAC(x) = h(k || p1 || h(k || p2 || x))
        h() = MD5 hash
        p1,p2 = distinct padding to bring k up to the block size
        p1 = 0x36 repeated, p2 = 0x5c repeated

    Diverges from usual implementation by using little-endian rather than big-endian input
*/

#ifndef HMAC_MD5_HPP
#define HMAC_MD5_HPP

#include <cat/crypt/hash/ICryptHash.hpp>

namespace cat {


class CAT_EXPORT HMAC_MD5 : public ICryptHash
{
protected:
    static const int DIGEST_BYTES = 16;
    static const int WORK_BYTES = 64; // bytes in one block
    static const int WORK_WORDS = WORK_BYTES / sizeof(u32);

    u32 CachedInitialState[4]; // Cached state for H(K||inner padding)
    u32 CachedFinalState[4];   // Cached state for H(K||outer padding)

    u64 byte_counter;
    u32 State[4];
    u8 Work[WORK_BYTES];
    int used_bytes;

    void HashComputation(const void *message, int blocks, u32 *NextState);

    // Unsupported modes
    bool BeginKey(int /*bits*/) { return false; }
    bool BeginKDF() { return false; }
    bool BeginPRNG() { return false; }

public:
    ~HMAC_MD5();
    bool SetKey(ICryptHash *parent);
	void RekeyFromMD5(HMAC_MD5 *parent);
    bool BeginMAC();
    void Crunch(const void *message, int bytes);
    void End();

	// TODO: Strengthening is not supported right now
    void Generate(void *out, int bytes, int strengthening_rounds = 0);
};


} // namespace cat

#endif // HMAC_MD5_HPP
