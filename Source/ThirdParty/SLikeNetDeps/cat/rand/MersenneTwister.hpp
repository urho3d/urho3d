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
    Algorithm by Makoto Matsumoto
    http://www.math.sci.hiroshima-u.ac.jp/~m-mat/MT/emt.html
*/

#ifndef CAT_MERSENNE_TWISTER_HPP
#define CAT_MERSENNE_TWISTER_HPP

#include <cat/rand/IRandom.hpp>

namespace cat {


// Noncryptographic pseudo-random number generator
class MersenneTwister : public IRandom
{
    static const u32 MEXP = 19937;
    static const u32 N128 = MEXP/128 + 1;
    static const u32 N64 = N128 * 2;
    static const u32 N32 = N128 * 4;
    static const u32 POS1 = 122;
    static const u32 SL1 = 18;
    static const u32 SL2 = 1;
    static const u32 SL2BITS = SL2*8;
    static const u32 SR1 = 11;
    static const u32 SR2 = 1;
    static const u32 SR2BITS = SR2*8;
    static const u32 MSK1 = 0xdfffffefU;
    static const u32 MSK2 = 0xddfecb7fU;
    static const u32 MSK3 = 0xbffaffffU;
    static const u32 MSK4 = 0xbffffff6U;

    struct MT128 {
        u32 u[4];
    };

    MT128 state[19937/128 + 1];
    u32 *state32;
    u32 used;

    CAT_INLINE void shiftLeft128(MT128 *r, MT128 *n, u32 bits);
    CAT_INLINE void shiftRight128(MT128 *r, MT128 *n, u32 bits);

    void enforcePeriod(); // make corrections to ensure that the generator has the full period
    void round(MT128 *a, MT128 *b, MT128 *c, MT128 *d); // a = MTMIX(a,b,c,d)
    void update(); // permute the existing state into a new one

public:
    MersenneTwister();

    bool Initialize(u32 seed);
    bool Initialize(u32 *seeds, u32 words);
    bool Initialize();

    u32 Generate(); // generate a 32-bit number
    void Generate(void *buffer, int bytes); // generate a series of random numbers
};


} // namespace cat

#endif // CAT_MERSENNE_TWISTER_HPP
