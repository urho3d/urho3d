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
    Bruce Schneier's SHA-3 candidate Skein hash function
    http://www.skein-hash.info/
*/

#ifndef CAT_SKEIN_HPP
#define CAT_SKEIN_HPP

#include <cat/crypt/hash/ICryptHash.hpp>

namespace cat {


// Base class for various versions of Skein
class CAT_EXPORT Skein : public ICryptHash
{
protected:
    // Tweak word 1 bit field starting positions
    static const int T1_POS_TREE_LVL = 112-64; // bits 112..118 : level in hash tree
    static const int T1_POS_BIT_PAD = 119-64;  // bit  119      : partial final input byte
    static const int T1_POS_BLK_TYPE = 120-64; // bits 120..125 : type field
    static const int T1_POS_FIRST = 126-64;    // bits 126      : first block flag
    static const int T1_POS_FINAL = 127-64;    // bit  127      : final block flag

    // Tweak word 1 bit field masks
    static const u64 T1_MASK_FIRST = (u64)1 << T1_POS_FIRST;
    static const u64 T1_MASK_FINAL = (u64)1 << T1_POS_FINAL;
    static const u64 T1_MASK_BIT_PAD = (u64)1 << T1_POS_BIT_PAD;
    static const u64 T1_MASK_TREE_LVL = (u64)0x7F << T1_POS_TREE_LVL;
    static const u64 T1_MASK_BLK_TYPE = (u64)63 << T1_POS_BLK_TYPE;

    static const int BLK_TYPE_KEY = 0;    // key, for MAC and KDF
    static const int BLK_TYPE_CFG = 4;    // configuration block
    static const int BLK_TYPE_PERS = 8;   // personalization string
    static const int BLK_TYPE_PK = 12;    // public key (for digital signature hashing)
    static const int BLK_TYPE_KDF = 16;   // key identifier for KDF
    static const int BLK_TYPE_NONCE = 20; // nonce for PRNG
    static const int BLK_TYPE_MSG = 48;   // message processing
    static const int BLK_TYPE_OUT = 63;   // output stage

    static const u32 ID_STRING_LE = 0x33414853;
    static const u32 SKEIN_VERSION = 1;
    static const u64 SCHEMA_VER = ((u64)SKEIN_VERSION << 32) | ID_STRING_LE;

    static const int MAX_BITS = 512;
    static const int MAX_WORDS = MAX_BITS / 64;
    static const int MAX_BYTES = MAX_BITS / 8;

    u64 Tweak[2];
    u64 State[MAX_WORDS];
    u8 Work[MAX_BYTES];
    int used_bytes, digest_words;
    u64 output_block_counter;
    bool output_prng_mode;

    typedef void (Skein::*HashComputation)(const void *message, int blocks, u32 byte_count, u64 *NextState);

    void HashComputation256(const void *message, int blocks, u32 byte_count, u64 *NextState);
    void HashComputation512(const void *message, int blocks, u32 byte_count, u64 *NextState);

    HashComputation hash_func;

    void GenerateInitialState(int bits);

public:
    ~Skein();
    bool BeginKey(int bits);
    bool SetKey(ICryptHash *parent);
    bool BeginMAC();
    bool BeginKDF();
    bool BeginPRNG();
    void Crunch(const void *message, int bytes);
    void End();
    void Generate(void *out, int bytes, int strengthening_rounds = 0);
};


} // namespace cat

#endif // CAT_SKEIN_HPP
