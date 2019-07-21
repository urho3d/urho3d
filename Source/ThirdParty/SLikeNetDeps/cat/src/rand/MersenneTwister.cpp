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

#include <cat/rand/MersenneTwister.hpp>
#include <cat/math/BitMath.hpp>
#include <cstring>
using namespace cat;
using namespace std;

#if defined(CAT_OS_WINDOWS)
# include <cat/port/WindowsInclude.hpp>
# include <wincrypt.h>
# if defined(CAT_COMPILER_MSVC)
#  pragma comment(lib, "advapi32")
# endif
#elif defined(CAT_OS_LINUX)
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
#endif


MersenneTwister::MersenneTwister()
{
    state32 = &state[0].u[0];
}

// fix the initial state to ensure that the full generator period will occur
void MersenneTwister::enforcePeriod()
{
    static const u32 PARITY[4] = {0x00000001U, 0x00000000U, 0x00000000U, 0x13c9e684U};

    u32 inner = 0;

    // An odd number of parity bits set is OK
    inner ^= state32[0] & PARITY[0];
    inner ^= state32[1] & PARITY[1];
    inner ^= state32[2] & PARITY[2];
    inner ^= state32[3] & PARITY[3];
    inner ^= inner >> 16;
    inner ^= inner >> 8;
    inner ^= inner >> 4;
    inner ^= inner >> 2;
    inner ^= inner >> 1;
    if ((inner & 1)) return;

    // Otherwise, flip the lowest parity bit to make it odd
    for (u32 ii = 0; ii < 4; ++ii)
    {
        if (PARITY[ii])
        {
            state32[ii] ^= CAT_LEAST_SIGNIFICANT_BIT(PARITY[ii]);
            break;
        }
    }
}

// initialize the generator with a 32-bit seed
bool MersenneTwister::Initialize(u32 seed)
{
    state32[0] = seed;

    for (u32 ii = 1; ii < N32; ++ii)
        state32[ii] = 1812433253UL * (state32[ii-1] ^ (state32[ii-1] >> 30)) + ii;

    enforcePeriod();
    used = N32;

    return true;
}

// initialize with an array of seeds
bool MersenneTwister::Initialize(u32 *seeds, u32 words)
{
    u32 ii, jj, r, count, mid, lag, size = N32;

    if (size >= 623)        lag = 11;
    else if (size >= 68)    lag = 7;
    else if (size >= 39)    lag = 5;
    else                    lag = 3;

    mid = (size - lag) / 2;

    memset(state, 0x8b, sizeof(state));

    if (words+1 > N32)    count = words+1;
    else                count = N32;

#define FUNC1(x) ( ((x) ^ ((x) >> 27)) * (u32)1664525UL )
#define FUNC2(x) ( ((x) ^ ((x) >> 27)) * (u32)1566083941UL )

    r = FUNC1(state32[0]);
    state32[mid] += r;
    r += words;
    state32[mid + lag] += r;
    state32[0] = r;

    --count;
    for (ii = 1, jj = 0; (jj < count) && (jj < words); ++jj)
    {
        r = FUNC1(state32[ii] ^ state32[(ii + mid) % N32] ^ state32[(ii + N32 - 1) % N32]);
        state32[(ii + mid) % N32] += r;
        r += seeds[jj] + ii;
        state32[(ii + mid + lag) % N32] += r;
        state32[ii] = r;
        ++ii;
        ii %= N32;
    }
    for (; jj < count; ++jj)
    {
        r = FUNC1(state32[ii] ^ state32[(ii + mid) % N32] ^ state32[(ii + N32 - 1) % N32]);
        state32[(ii + mid) % N32] += r;
        r += ii;
        state32[(ii + mid + lag) % N32] += r;
        state32[ii] = r;
        ++ii;
        ii %= N32;
    }
    for (jj = 0; jj < N32; ++jj)
    {
        r = FUNC2(state32[ii] + state32[(ii + mid) % N32] + state32[(ii + N32 - 1) % N32]);
        state32[(ii + mid) % N32] ^= r;
        r -= ii;
        state32[(ii + mid + lag) % N32] ^= r;
        state32[ii] = r;
        ++ii;
        ii %= N32;
    }

#undef FUNC1
#undef FUNC2

    enforcePeriod();
    used = N32;

    return true;
}

bool MersenneTwister::Initialize()
{
    u32 seeds[16];

#ifdef _WIN32
    HCRYPTPROV hCryptProv;

    if (CryptAcquireContext(&hCryptProv, 0, 0, PROV_DSS, CRYPT_VERIFYCONTEXT))
    {
        CryptGenRandom(hCryptProv, sizeof(seeds), (BYTE*)seeds);
        CryptReleaseContext(hCryptProv, 0);
    }
#else
    int fd = open("/dev/urandom", O_RDONLY);
    if (fd >= 0)
    {
        read(fd, seeds, sizeof(seeds));
        close(fd);
    }
#endif // _WIN32

    return Initialize(seeds, 16);
}

// r != n, 0 < bits < 32
void MersenneTwister::shiftLeft128(MT128 *r, MT128 *n, u32 bits)
{
    r->u[0] = n->u[0] << bits;
    r->u[1] = (n->u[1] << bits) | (n->u[0] >> (32 - bits)); 
    r->u[2] = (n->u[2] << bits) | (n->u[1] >> (32 - bits)); 
    r->u[3] = (n->u[3] << bits) | (n->u[2] >> (32 - bits)); 
}

// r != n, 0 < bits < 32
void MersenneTwister::shiftRight128(MT128 *r, MT128 *n, u32 bits)
{
    r->u[0] = (n->u[0] >> bits) | (n->u[1] << (32 - bits));
    r->u[1] = (n->u[1] >> bits) | (n->u[2] << (32 - bits));
    r->u[2] = (n->u[2] >> bits) | (n->u[3] << (32 - bits));
    r->u[3] = n->u[3] >> bits; 
}

// a ^= (a << SL2BITS) ^ ((b >> SR1) & MSK) ^ (c >> SR2BITS) ^ (d{0..3} << SL1)
void MersenneTwister::round(MT128 *a, MT128 *b, MT128 *c, MT128 *d)
{
    MT128 x, y;

    shiftLeft128(&x, a, SL2BITS);
    shiftRight128(&y, c, SR2BITS);

    a->u[0] ^= x.u[0] ^ ((b->u[0] >> SR1) & MSK1) ^ y.u[0] ^ (d->u[0] << SL1);
    a->u[1] ^= x.u[1] ^ ((b->u[1] >> SR1) & MSK2) ^ y.u[1] ^ (d->u[1] << SL1);
    a->u[2] ^= x.u[2] ^ ((b->u[2] >> SR1) & MSK3) ^ y.u[2] ^ (d->u[2] << SL1);
    a->u[3] ^= x.u[3] ^ ((b->u[3] >> SR1) & MSK4) ^ y.u[3] ^ (d->u[3] << SL1);
}

// permute the existing state into a new one
void MersenneTwister::update()
{
    MT128 *r1 = state + N128 - 2;
    MT128 *r2 = state + N128 - 1;
    u32 ii;

    for (ii = 0; ii < N128 - POS1; ++ii)
    {
        round(state + ii, state + ii + POS1, r1, r2);
        r1 = r2;
        r2 = state + ii;
    }

    for (; ii < N128; ++ii)
    {
        round(state + ii, state + ii + POS1 - N128, r1, r2);
        r1 = r2;
        r2 = state + ii;
    }

    used = 0;
}

// generate a 32-bit random number
u32 MersenneTwister::Generate()
{
    if (used >= N32)
        update();

    return state32[used++];
}

// generate a series of random numbers to fill a buffer of any size
void MersenneTwister::Generate(void *buffer, int bytes)
{
    u8 *buffer8 = (u8 *)buffer;
    u32 words = bytes / 4;

    while (words > 0)
    {
        if (used >= N32)
            update();

        u32 remaining = N32 - used;
        u32 copying = words;
        if (copying > remaining) copying = remaining;

        memcpy(buffer8, state32 + used, copying*4);
        used += copying;
        words -= copying;
        buffer8 += copying*4;
    }

    switch (bytes % 4)
    {
    case 1:
        buffer8[0] = (u8)Generate();
        break;
    case 2:
        *(u16*)buffer8 = (u16)Generate();
        break;
    case 3:
        words = Generate();
        buffer8[0] = (u8)words;
        *(u16*)(buffer8+1) = (u16)(words >> 8);
        break;
    }
}
