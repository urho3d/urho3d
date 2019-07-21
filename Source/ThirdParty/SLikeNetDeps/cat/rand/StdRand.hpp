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

#ifndef CAT_STDRAND_HPP
#define CAT_STDRAND_HPP

#include <cat/Platform.hpp>

namespace cat {


// Microsoft VC++ 7.0 stdlib srand(), rand(), old RANDU()
class StandardRand
{
protected:
    s32 seed;

public:
    StandardRand(u32 ns = 0) { seed = ns; }

    inline void srand32(u32 ns) { seed = ns; } // 32-bit version
    inline void srand16(u16 ns) { seed = ns; } // 16-bit version (yup)

    u16 rand();		// Linear Congruential Generator: X = X * M + A (mod N)
    u16 randu();	// RANDU LCG: X = X * M (mod N)
	float sfrand();	// Fast [-1.f,1.f] generator from Inigo Quilez (2005)
};


// Non-linear congruential 32-bit random mixing function for given x, y and seed
// This function is used in every example of Perlin noise I found online for some reason!
u32 NLCRand32(int x, int y, u32 seed);

// Uses NLCRand32 as a front-end, and then maps the output to a number between -1 and 1
float NLCRandNorm(int x, int y, u32 seed);



} // namespace cat

#endif // CAT_STDRAND_HPP
