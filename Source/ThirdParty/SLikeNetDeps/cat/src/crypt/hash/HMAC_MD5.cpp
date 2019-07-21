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

#include <cat/crypt/hash/HMAC_MD5.hpp>
#include <cat/math/BitMath.hpp>
#include <cat/port/EndianNeutral.hpp>
using namespace cat;

#define F(x, y, z) (((x) & (y)) | (~(x) & (z)))
#define G(x, y, z) (((x) & (z)) | ((y) & ~(z)))
#define H(x, y, z) ((x) ^ (y) ^ (z))
#define I(x, y, z) ((y) ^ ((x) | ~(z)))

// NOTE: Uses little-endian integers instead of big-endian as in standard MD5
#define ROUND(a, b, Fbcd, x, o, s, ac) \
    (a) += Fbcd + getLE(x[o]) + (u32)(ac); \
    (a) = CAT_ROL32((a), (s)); \
    (a) += (b);

#define FF(a, b, c, d, x,o, s, ac) ROUND(a, b, F(b,c,d), x, o, s, ac)
#define GG(a, b, c, d, x,o, s, ac) ROUND(a, b, G(b,c,d), x, o, s, ac)
#define HH(a, b, c, d, x,o, s, ac) ROUND(a, b, H(b,c,d), x, o, s, ac)
#define II(a, b, c, d, x,o, s, ac) ROUND(a, b, I(b,c,d), x, o, s, ac)


//// HMAC_MD5

void HMAC_MD5::HashComputation(const void *message, int blocks, u32 *NextState)
{
	u32 *words = (u32*)message;

    u32 a0 = State[0], b0 = State[1], c0 = State[2], d0 = State[3];

    while (blocks--)
    {
        u32 a = a0, b = b0, c = c0, d = d0;

#ifdef CAT_AUDIT
		printf("AUDIT: MD5 ");
		for (int ii = 0; ii < 64; ++ii)
		{
			printf("%02x", ((u8*)words)[ii]);
		}
		printf("\n");
#endif

        // Round 1
		const int S11 = 7;
		const int S12 = 12;
		const int S13 = 17;
		const int S14 = 22;

		FF(a, b, c, d, words,  0, S11, 0xd76aa478); // 1
        FF(d, a, b, c, words,  1, S12, 0xe8c7b756); // 2
        FF(c, d, a, b, words,  2, S13, 0x242070db); // 3
        FF(b, c, d, a, words,  3, S14, 0xc1bdceee); // 4
        FF(a, b, c, d, words,  4, S11, 0xf57c0faf); // 5
        FF(d, a, b, c, words,  5, S12, 0x4787c62a); // 6
        FF(c, d, a, b, words,  6, S13, 0xa8304613); // 7
        FF(b, c, d, a, words,  7, S14, 0xfd469501); // 8
        FF(a, b, c, d, words,  8, S11, 0x698098d8); // 9
        FF(d, a, b, c, words,  9, S12, 0x8b44f7af); // 10
        FF(c, d, a, b, words, 10, S13, 0xffff5bb1); // 11
        FF(b, c, d, a, words, 11, S14, 0x895cd7be); // 12
        FF(a, b, c, d, words, 12, S11, 0x6b901122); // 13
        FF(d, a, b, c, words, 13, S12, 0xfd987193); // 14
        FF(c, d, a, b, words, 14, S13, 0xa679438e); // 15
        FF(b, c, d, a, words, 15, S14, 0x49b40821); // 16

        // Round 2
		const int S21 = 5;
		const int S22 = 9;
		const int S23 = 14;
		const int S24 = 20;

		GG(a, b, c, d, words,  1, S21, 0xf61e2562); // 17
        GG(d, a, b, c, words,  6, S22, 0xc040b340); // 18
        GG(c, d, a, b, words, 11, S23, 0x265e5a51); // 19
        GG(b, c, d, a, words,  0, S24, 0xe9b6c7aa); // 20
        GG(a, b, c, d, words,  5, S21, 0xd62f105d); // 21
        GG(d, a, b, c, words, 10, S22,  0x2441453); // 22
        GG(c, d, a, b, words, 15, S23, 0xd8a1e681); // 23
        GG(b, c, d, a, words,  4, S24, 0xe7d3fbc8); // 24
        GG(a, b, c, d, words,  9, S21, 0x21e1cde6); // 25
        GG(d, a, b, c, words, 14, S22, 0xc33707d6); // 26
        GG(c, d, a, b, words,  3, S23, 0xf4d50d87); // 27
        GG(b, c, d, a, words,  8, S24, 0x455a14ed); // 28
        GG(a, b, c, d, words, 13, S21, 0xa9e3e905); // 29
        GG(d, a, b, c, words,  2, S22, 0xfcefa3f8); // 30
        GG(c, d, a, b, words,  7, S23, 0x676f02d9); // 31
        GG(b, c, d, a, words, 12, S24, 0x8d2a4c8a); // 32

        // Round 3
		const int S31 = 4;
		const int S32 = 11;
		const int S33 = 16;
		const int S34 = 23;

		HH(a, b, c, d, words,  5, S31, 0xfffa3942); // 33
        HH(d, a, b, c, words,  8, S32, 0x8771f681); // 34
        HH(c, d, a, b, words, 11, S33, 0x6d9d6122); // 35
        HH(b, c, d, a, words, 14, S34, 0xfde5380c); // 36
        HH(a, b, c, d, words,  1, S31, 0xa4beea44); // 37
        HH(d, a, b, c, words,  4, S32, 0x4bdecfa9); // 38
        HH(c, d, a, b, words,  7, S33, 0xf6bb4b60); // 39
        HH(b, c, d, a, words, 10, S34, 0xbebfbc70); // 40
        HH(a, b, c, d, words, 13, S31, 0x289b7ec6); // 41
        HH(d, a, b, c, words,  0, S32, 0xeaa127fa); // 42
        HH(c, d, a, b, words,  3, S33, 0xd4ef3085); // 43
        HH(b, c, d, a, words,  6, S34,  0x4881d05); // 44
        HH(a, b, c, d, words,  9, S31, 0xd9d4d039); // 45
        HH(d, a, b, c, words, 12, S32, 0xe6db99e5); // 46
        HH(c, d, a, b, words, 15, S33, 0x1fa27cf8); // 47
        HH(b, c, d, a, words,  2, S34, 0xc4ac5665); // 48

        // Round 4
		const int S41 = 6;
		const int S42 = 10;
		const int S43 = 15;
		const int S44 = 21;

		II(a, b, c, d, words,  0, S41, 0xf4292244); // 49
        II(d, a, b, c, words,  7, S42, 0x432aff97); // 50
        II(c, d, a, b, words, 14, S43, 0xab9423a7); // 51
        II(b, c, d, a, words,  5, S44, 0xfc93a039); // 52
        II(a, b, c, d, words, 12, S41, 0x655b59c3); // 53
        II(d, a, b, c, words,  3, S42, 0x8f0ccc92); // 54
        II(c, d, a, b, words, 10, S43, 0xffeff47d); // 55
        II(b, c, d, a, words,  1, S44, 0x85845dd1); // 56
        II(a, b, c, d, words,  8, S41, 0x6fa87e4f); // 57
        II(d, a, b, c, words, 15, S42, 0xfe2ce6e0); // 58
        II(c, d, a, b, words,  6, S43, 0xa3014314); // 59
        II(b, c, d, a, words, 13, S44, 0x4e0811a1); // 60
        II(a, b, c, d, words,  4, S41, 0xf7537e82); // 61
        II(d, a, b, c, words, 11, S42, 0xbd3af235); // 62
        II(c, d, a, b, words,  2, S43, 0x2ad7d2bb); // 63
        II(b, c, d, a, words,  9, S44, 0xeb86d391); // 64

        a0 += a;
        b0 += b;
        c0 += c;
        d0 += d;

		words += 16;
	}

    NextState[0] = a0;
    NextState[1] = b0;
    NextState[2] = c0;
    NextState[3] = d0;
}

HMAC_MD5::~HMAC_MD5()
{
    CAT_OBJCLR(State);
    CAT_OBJCLR(Work);
    CAT_OBJCLR(CachedInitialState);
    CAT_OBJCLR(CachedFinalState);
    byte_counter = 0;
    used_bytes = 0;
}

bool HMAC_MD5::SetKey(ICryptHash *parent)
{
    State[0] = 0x27b70a85;
    State[1] = 0x2e1b2138;
    State[2] = 0x4d2c6dfc;
    State[3] = 0x53380d13;

    static const int KEY_BYTES = WORK_BYTES / 2;

    u8 Key[KEY_BYTES];

    parent->Generate(Key, KEY_BYTES);

    // Using the parent hash function, generate key bytes to fill half a block
    memcpy(Work, Key, KEY_BYTES);
    memset(Work + KEY_BYTES, 0x36, WORK_BYTES - KEY_BYTES); // Pad to fill a whole block

    // Crunch one whole block
    HashComputation(Work, 1, State);

    // Store this as the cached initial state
    memcpy(CachedInitialState, State, DIGEST_BYTES);

    // Using the parent hash function, generate key bytes to fill half a block
    memcpy(Work, Key, KEY_BYTES);
    memset(Work + KEY_BYTES, 0x5c, WORK_BYTES - KEY_BYTES); // Pad to fill a whole block

    // Crunch one whole block
    HashComputation(Work, 1, CachedFinalState);

    return true;
}

void HMAC_MD5::RekeyFromMD5(HMAC_MD5 *parent)
{
	memcpy(CachedInitialState, parent->CachedInitialState, sizeof(CachedInitialState));
	memcpy(CachedFinalState, parent->CachedFinalState, sizeof(CachedFinalState));
}

bool HMAC_MD5::BeginMAC()
{
    memcpy(State, CachedInitialState, DIGEST_BYTES);

    byte_counter = WORK_BYTES;

    used_bytes = 0;

    return true;
}

void HMAC_MD5::Crunch(const void *_message, int bytes)
{
    const u8 *buffer = (const u8*)_message;

    byte_counter += bytes;

    // If there are bytes left to hash from last time,
    if (used_bytes)
    {
        // If we still cannot overflow the workspace,
        if (used_bytes + bytes <= WORK_BYTES)
        {
            // Just append the new message bytes
            memcpy(Work + used_bytes, buffer, bytes);
            used_bytes += bytes;
            return;
        }

        // Fill the rest of the workspace
        u32 copied = WORK_BYTES - used_bytes;

        memcpy(Work + used_bytes, buffer, copied);

        HashComputation(Work, 1, State);

        // Eat those bytes of the message
        bytes -= copied;
        buffer += copied;
    }

    // If the remaining bytes of the message overflows the workspace,
    if (bytes > WORK_BYTES)
    {
        int eat_bytes = bytes - 1;

        // Hash directly from the message
        HashComputation(buffer, eat_bytes / WORK_BYTES, State);

        // Eat those bytes of the message
        eat_bytes &= ~(WORK_BYTES-1);
        buffer += eat_bytes;
        bytes -= eat_bytes;
    }

    // Copy what remains into the workspace
    memcpy(Work, buffer, bytes);
    used_bytes = bytes;
}

void HMAC_MD5::End()
{
    // NOTE: We should always have at least one message hash to perform here

    if (used_bytes >= WORK_BYTES)
    {
        HashComputation(Work, 1, State);

        Work[0] = 0x80;

        used_bytes = 1;
    }
    else if (used_bytes > (WORK_BYTES - 9))
    {
        Work[used_bytes++] = 0x80;

        // Pad with zeros
        CAT_CLR(Work + used_bytes, WORK_BYTES - used_bytes);

        HashComputation(Work, 1, State);

        used_bytes = 0;
    }

    // Pad out zeros
    CAT_CLR(Work + used_bytes, (WORK_BYTES - 8) - used_bytes);

    // Attach bit count to the end
	u64 bit_counter = byte_counter << 3;
	*(u32*)&Work[WORK_BYTES - 8] = getLE((u32)bit_counter);
	*(u32*)&Work[WORK_BYTES - 4] = getLE((u32)(bit_counter >> 32));

    u32 *Output = (u32 *)Work;

    // Intermediate hash, output to start of workspace
    HashComputation(Work, 1, Output);

    memcpy(State, CachedFinalState, DIGEST_BYTES);

    // Convert Intermediate State to an endian-neutral byte array
    swapLE(Output[0]);
    swapLE(Output[1]);
    swapLE(Output[2]);
    swapLE(Output[3]);

    // Pad the hash-as-message as normal and crown it with a byte counter
    byte_counter = 16;
    Work[16] = 0x80;
    CAT_CLR(Work + 17, (WORK_BYTES - 8) - 17);

	*(u32*)&Work[WORK_BYTES - 8] = getLE32(16 << 3);
	*(u32*)&Work[WORK_BYTES - 4] = 0;

    // Final output hash
    HashComputation(Work, 1, State);

    // Convert Final State to an endian-neutral byte array
    swapLE(State[0]);
    swapLE(State[1]);
    swapLE(State[2]);
    swapLE(State[3]);
}

void HMAC_MD5::Generate(void *out, int bytes, int /*strengthening_rounds*/)
{
    if (bytes > 16) bytes = 16;

    memcpy(out, State, bytes);
}

#undef F
#undef G
#undef H
#undef I

#undef ROUND

#undef FF
#undef GG
#undef HH
#undef II
