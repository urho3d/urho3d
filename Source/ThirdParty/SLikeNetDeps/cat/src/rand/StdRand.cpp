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

#include <cat/rand/StdRand.hpp>
using namespace cat;

static const s32 STDLIB_RAND_MULTIPLIER = 214013;
static const s32 STDLIB_RAND_ADDEND = 2531011;
static const s32 STDLIB_RANDU_MULTIPLIER = 65539;

u16 StandardRand::rand()
{
    seed = STDLIB_RAND_MULTIPLIER * seed + STDLIB_RAND_ADDEND;
    return (u16)((seed >> 16) & 0x7fff);
}

u16 StandardRand::randu()
{
    seed *= STDLIB_RANDU_MULTIPLIER;
    return (u16)((seed >> 16) & 0x7fff);
}

// Fast [-1.f,1.f] generator from Inigo Quilez (2005)
float StandardRand::sfrand()
{
	float r;

	seed *= 16807;

	*( (u32*)&r ) = ( (u32)seed >> 9 ) | 0x40000000;

	return r - 3.f;
}

u32 cat::NLCRand32(int x, int y, u32 seed)
{
    // Map 2D->1D
    // To avoid repetitive output, adjust pitch constant (271) higher if needed
    u32 n = x + y * 271 + seed;

    // Mixing step
    n = (n << 13) ^ n;

    // Non-linear congruential mixing step
    n *= (n * n * 15731 + 789221) + 1376312589;

    return n;
}


float cat::NLCRandNorm(int x, int y, u32 seed)
{
    u32 n = NLCRand32(x, y, seed);

    // Clamp to -1..1 (mode preferred by my Perlin noise code)
    return 1.0f - n / 2147483647.5f;
}
