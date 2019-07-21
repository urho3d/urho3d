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

#include <cat/crypt/hash/Skein.hpp>
#include <cat/port/EndianNeutral.hpp>
using namespace cat;

#define THREEFISH(R0, R1, R2, R3) \
    x0 += x1; x1 = CAT_ROL64(x1, R0); x1 ^= x0; \
    x2 += x3; x3 = CAT_ROL64(x3, R1); x3 ^= x2; \
    x0 += x3; x3 = CAT_ROL64(x3, R2); x3 ^= x0; \
    x2 += x1; x1 = CAT_ROL64(x1, R3); x1 ^= x2;

#define INJECTKEY(K0, K1, K2, K3, T0, T1, R) \
    x0 += (K0); \
    x1 += (K1) + (T0); \
    x2 += (K2) + (T1); \
    x3 += (K3) + (R);

void Skein::HashComputation256(const void *_message, int blocks, u32 byte_count, u64 *NextState)
{
    const int BITS = 256;
    const int WORDS = BITS / 64;
    const int BYTES = BITS / 8;
    const u64 *message = (const u64 *)_message;

    // Key schedule: Chaining
    u64 k[5];
    memcpy(k, State, BYTES);

    // Key schedule: Tweak
    u64 t0 = Tweak[0];
    u64 t1 = Tweak[1];

    do
    {
        t0 += byte_count;

        // Parity extension
        u64 t2 = t0 ^ t1;
        k[4] = 0x1BD11BDAA9FC1A22LL ^ k[0] ^ k[1] ^ k[2] ^ k[3];

        // First full key injection
        register u64 x0 = k[0] + getLE(message[0]);
        register u64 x1 = k[1] + getLE(message[1]) + t0;
        register u64 x2 = k[2] + getLE(message[2]) + t1;
        register u64 x3 = k[3] + getLE(message[3]);

        // 72 rounds

		// 10/26/09: Updated for SHA-3 competition Round 2
        enum {
            R_256_0_0=14, R_256_0_1=16,
            R_256_1_0=52, R_256_1_1=57,
            R_256_2_0=23, R_256_2_1=40,
            R_256_3_0= 5, R_256_3_1=37,
            R_256_4_0=25, R_256_4_1=33,
            R_256_5_0=46, R_256_5_1=12,
            R_256_6_0=58, R_256_6_1=22,
            R_256_7_0=32, R_256_7_1=32
        };

        for (int round = 1; round <= 18; round += 6)
        {
            THREEFISH(R_256_0_0, R_256_0_1, R_256_1_0, R_256_1_1);
            THREEFISH(R_256_2_0, R_256_2_1, R_256_3_0, R_256_3_1);

            u64 k1 = k[(round)%5];
            u64 k2 = k[(round+1)%5];
            u64 k3 = k[(round+2)%5];
            u64 k4 = k[(round+3)%5];
            u64 k0 = k[(round+4)%5];

            INJECTKEY(k1, k2, k3, k4, t1, t2, round);
            THREEFISH(R_256_4_0, R_256_4_1, R_256_5_0, R_256_5_1);
            THREEFISH(R_256_6_0, R_256_6_1, R_256_7_0, R_256_7_1);
            INJECTKEY(k2, k3, k4, k0, t2, t0, round+1);
            THREEFISH(R_256_0_0, R_256_0_1, R_256_1_0, R_256_1_1);
            THREEFISH(R_256_2_0, R_256_2_1, R_256_3_0, R_256_3_1);
            INJECTKEY(k3, k4, k0, k1, t0, t1, round+2);
            THREEFISH(R_256_4_0, R_256_4_1, R_256_5_0, R_256_5_1);
            THREEFISH(R_256_6_0, R_256_6_1, R_256_7_0, R_256_7_1);
            INJECTKEY(k4, k0, k1, k2, t1, t2, round+3);
            THREEFISH(R_256_0_0, R_256_0_1, R_256_1_0, R_256_1_1);
            THREEFISH(R_256_2_0, R_256_2_1, R_256_3_0, R_256_3_1);
            INJECTKEY(k0, k1, k2, k3, t2, t0, round+4);
            THREEFISH(R_256_4_0, R_256_4_1, R_256_5_0, R_256_5_1);
            THREEFISH(R_256_6_0, R_256_6_1, R_256_7_0, R_256_7_1);
            INJECTKEY(k1, k2, k3, k4, t0, t1, round+5);
        }
/*
        THREEFISH(R_256_0_0, R_256_0_1, R_256_1_0, R_256_1_1);
        THREEFISH(R_256_2_0, R_256_2_1, R_256_3_0, R_256_3_1);
        INJECTKEY(k1, k2, k3, k4, t1, t2, 1);
        THREEFISH(R_256_4_0, R_256_4_1, R_256_5_0, R_256_5_1);
        THREEFISH(R_256_6_0, R_256_6_1, R_256_7_0, R_256_7_1);
        INJECTKEY(k2, k3, k4, k0, t2, t0, 2);
        THREEFISH(R_256_0_0, R_256_0_1, R_256_1_0, R_256_1_1);
        THREEFISH(R_256_2_0, R_256_2_1, R_256_3_0, R_256_3_1);
        INJECTKEY(k3, k4, k0, k1, t0, t1, 3);
        THREEFISH(R_256_4_0, R_256_4_1, R_256_5_0, R_256_5_1);
        THREEFISH(R_256_6_0, R_256_6_1, R_256_7_0, R_256_7_1);
        INJECTKEY(k4, k0, k1, k2, t1, t2, 4);
        THREEFISH(R_256_0_0, R_256_0_1, R_256_1_0, R_256_1_1);
        THREEFISH(R_256_2_0, R_256_2_1, R_256_3_0, R_256_3_1);
        INJECTKEY(k0, k1, k2, k3, t2, t0, 5);
        THREEFISH(R_256_4_0, R_256_4_1, R_256_5_0, R_256_5_1);
        THREEFISH(R_256_6_0, R_256_6_1, R_256_7_0, R_256_7_1);
        INJECTKEY(k1, k2, k3, k4, t0, t1, 6);
        THREEFISH(R_256_0_0, R_256_0_1, R_256_1_0, R_256_1_1);
        THREEFISH(R_256_2_0, R_256_2_1, R_256_3_0, R_256_3_1);
        INJECTKEY(k2, k3, k4, k0, t1, t2, 7);
        THREEFISH(R_256_4_0, R_256_4_1, R_256_5_0, R_256_5_1);
        THREEFISH(R_256_6_0, R_256_6_1, R_256_7_0, R_256_7_1);
        INJECTKEY(k3, k4, k0, k1, t2, t0, 8);
        THREEFISH(R_256_0_0, R_256_0_1, R_256_1_0, R_256_1_1);
        THREEFISH(R_256_2_0, R_256_2_1, R_256_3_0, R_256_3_1);
        INJECTKEY(k4, k0, k1, k2, t0, t1, 9);
        THREEFISH(R_256_4_0, R_256_4_1, R_256_5_0, R_256_5_1);
        THREEFISH(R_256_6_0, R_256_6_1, R_256_7_0, R_256_7_1);
        INJECTKEY(k0, k1, k2, k3, t1, t2, 10);
        THREEFISH(R_256_0_0, R_256_0_1, R_256_1_0, R_256_1_1);
        THREEFISH(R_256_2_0, R_256_2_1, R_256_3_0, R_256_3_1);
        INJECTKEY(k1, k2, k3, k4, t2, t0, 11);
        THREEFISH(R_256_4_0, R_256_4_1, R_256_5_0, R_256_5_1);
        THREEFISH(R_256_6_0, R_256_6_1, R_256_7_0, R_256_7_1);
        INJECTKEY(k2, k3, k4, k0, t0, t1, 12);
        THREEFISH(R_256_0_0, R_256_0_1, R_256_1_0, R_256_1_1);
        THREEFISH(R_256_2_0, R_256_2_1, R_256_3_0, R_256_3_1);
        INJECTKEY(k3, k4, k0, k1, t1, t2, 13);
        THREEFISH(R_256_4_0, R_256_4_1, R_256_5_0, R_256_5_1);
        THREEFISH(R_256_6_0, R_256_6_1, R_256_7_0, R_256_7_1);
        INJECTKEY(k4, k0, k1, k2, t2, t0, 14);
        THREEFISH(R_256_0_0, R_256_0_1, R_256_1_0, R_256_1_1);
        THREEFISH(R_256_2_0, R_256_2_1, R_256_3_0, R_256_3_1);
        INJECTKEY(k0, k1, k2, k3, t0, t1, 15);
        THREEFISH(R_256_4_0, R_256_4_1, R_256_5_0, R_256_5_1);
        THREEFISH(R_256_6_0, R_256_6_1, R_256_7_0, R_256_7_1);
        INJECTKEY(k1, k2, k3, k4, t1, t2, 16);
        THREEFISH(R_256_0_0, R_256_0_1, R_256_1_0, R_256_1_1);
        THREEFISH(R_256_2_0, R_256_2_1, R_256_3_0, R_256_3_1);
        INJECTKEY(k2, k3, k4, k0, t2, t0, 17);
        THREEFISH(R_256_4_0, R_256_4_1, R_256_5_0, R_256_5_1);
        THREEFISH(R_256_6_0, R_256_6_1, R_256_7_0, R_256_7_1);
        INJECTKEY(k3, k4, k0, k1, t0, t1, 18);
*/
        // Feedforward XOR
        k[0] = x0 ^ getLE(message[0]);
        k[1] = x1 ^ getLE(message[1]);
        k[2] = x2 ^ getLE(message[2]);
        k[3] = x3 ^ getLE(message[3]);

        // Update tweak
        t1 &= ~T1_MASK_FIRST;

        // Eat data bytes
        message += WORDS;
    } while (--blocks > 0);

    // Update tweak
    Tweak[0] = t0;
    Tweak[1] = t1;

    // Update state
    memcpy(NextState, k, BYTES);
}

#undef THREEFISH
#undef INJECTKEY
