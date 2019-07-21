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

#include <cat/crypt/symmetric/ChaCha.hpp>
#include <cat/port/EndianNeutral.hpp>
#include <string.h>
using namespace cat;


//// ChaChaKey

ChaChaKey::~ChaChaKey()
{
	CAT_OBJCLR(state);
}

static u32 InitialState[12] = {
	0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a,
	// These are from BLAKE-32:
	0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19,
	// Took the rest of these from the SHA-256 SBOX constants:
	0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13
};

// Key up to 384 bits
void ChaChaKey::Set(const void *key, int bytes)
{
	// Precondition: Bytes must be a multiple of 4
	if (bytes > 48) bytes = 48;

	memcpy(state, InitialState, sizeof(InitialState));

	const u32 *in32 = (const u32 *)key;
	int words = bytes / 4;

	for (int ii = 0; ii < words; ++ii)
	{
		state[ii] ^= getLE(in32[ii]);
	}
}


//// ChaChaOutput

#define QUARTERROUND(a,b,c,d) \
	x[a] += x[b]; x[d] = CAT_ROL32(x[d] ^ x[a], 16); \
	x[c] += x[d]; x[b] = CAT_ROL32(x[b] ^ x[c], 12); \
	x[a] += x[b]; x[d] = CAT_ROL32(x[d] ^ x[a], 8); \
	x[c] += x[d]; x[b] = CAT_ROL32(x[b] ^ x[c], 7);

void ChaChaOutput::GenerateKeyStream(u32 *out_words)
{
	// Update block counter
	if (!++state[12]) state[13]++;

	register u32 x[16];

	// Copy state into work registers
	for (int ii = 0; ii < 16; ++ii)
		x[ii] = state[ii];

	// Mix state for 12 rounds
	for (int round = 12; round > 0; round -= 2)
	{
		QUARTERROUND(0, 4, 8,  12)
		QUARTERROUND(1, 5, 9,  13)
		QUARTERROUND(2, 6, 10, 14)
		QUARTERROUND(3, 7, 11, 15)
		QUARTERROUND(0, 5, 10, 15)
		QUARTERROUND(1, 6, 11, 12)
		QUARTERROUND(2, 7, 8,  13)
		QUARTERROUND(3, 4, 9,  14)
	}

	// Add state to mixed state, little-endian
	for (int jj = 0; jj < 16; ++jj)
		out_words[jj] = getLE(x[jj] + state[jj]);
}

ChaChaOutput::ChaChaOutput(const ChaChaKey &key, u64 iv)
{
	for (int ii = 0; ii < 12; ++ii)
		state[ii] = key.state[ii];

	// Initialize block counter to zero
	state[12] = 0;
	state[13] = 0;

	// Initialize IV
	state[14] = (u32)iv;
	state[15] = (u32)(iv >> 32);
}
ChaChaOutput::~ChaChaOutput()
{
	CAT_OBJCLR(state);
}

// Message with any number of bytes
void ChaChaOutput::Crypt(const void *in_bytes, void *out_bytes, int bytes)
{
	const u32 *in32 = (const u32 *)in_bytes;
	u32 *out32 = (u32 *)out_bytes;

#ifdef CAT_AUDIT
	int initial_bytes = bytes;
	printf("AUDIT: ChaCha input ");
	for (int ii = 0; ii < bytes; ++ii)
	{
		printf("%02x", ((cat::u8*)in_bytes)[ii]);
	}
	printf("\n");
#endif

	while (bytes >= 64)
	{
		u32 key32[16];
		GenerateKeyStream(key32);

		for (int ii = 0; ii < 16; ++ii)
			out32[ii] = in32[ii] ^ key32[ii];

		out32 += 16;
		in32 += 16;
		bytes -= 64;
	}

	if (bytes)
	{
		u32 key32[16];
		GenerateKeyStream(key32);

		int words = bytes / 4;
		for (int ii = 0; ii < words; ++ii)
			out32[ii] = in32[ii] ^ key32[ii];

		const u8 *in8 = (const u8 *)(in32 + words);
		u8 *out8 = (u8 *)(out32 + words);
		const u8 *key8 = (const u8 *)(key32 + words);

		switch (bytes % 4)
		{
		case 3: out8[2] = in8[2] ^ key8[2];
		case 2: out8[1] = in8[1] ^ key8[1];
		case 1: out8[0] = in8[0] ^ key8[0];
		}
	}

#ifdef CAT_AUDIT
	printf("AUDIT: ChaCha output ");
	for (int ii = 0; ii < initial_bytes; ++ii)
	{
		printf("%02x", ((cat::u8*)out_bytes)[ii]);
	}
	printf("\n");
#endif
}

#undef QUARTERROUND
