/*
	Copyright (c) 2009 Christopher A. Taylor.  All rights reserved.

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

#include <cat/math/BigRTL.hpp>
using namespace cat;

#include "CombaMul.cpp"

// Unrolled schoolbook method with special attention to carries
// This 4x4 multiply is (slightly) faster than using Comba method
// An 8x8 Comba multiply is significantly faster than this method
CAT_INLINE void CAT_FASTCALL SchoolbookMultiply4(const Leg *a, const Leg *b, Leg *output)
{
	Leg p0, p1, p2, p3, p4;

	CAT_LEG_MUL(a[0], b[0], p0, output[0]);

	CAT_LEG_MULADD(a[1], b[0], p0, p1, p0);
	CAT_LEG_MULADD(a[0], b[1], p0, p2, p0);
	output[1] = p0;

	CAT_LEG_MULADD2(a[2], b[0], p1, p2, p1, p0);
	CAT_LEG_MULADD(a[1], b[1], p0, p2, p0);
	CAT_LEG_MULADD(a[0], b[2], p0, p3, p0);
	output[2] = p0;

	CAT_LEG_MULADD2(a[3], b[0], p1, p2, p1, p0);
	CAT_LEG_MULADD2(a[2], b[1], p0, p3, p2, p0);
	CAT_LEG_MULADD(a[1], b[2], p0, p3, p0);
	CAT_LEG_MULADD(a[0], b[3], p0, p4, p0);
	output[3] = p0;

	CAT_LEG_MULADD2(a[3], b[1], p1, p2, p1, p0);
	CAT_LEG_MULADD2(a[2], b[2], p0, p3, p2, p0);
	CAT_LEG_MULADD2(a[1], b[3], p0, p4, p3, p0);
	output[4] = p0;

	CAT_LEG_MULADD2(a[3], b[2], p1, p2, p1, p0);
	CAT_LEG_MULADD2(a[2], b[3], p0, p3, p2, p0);
	output[5] = p0;

	CAT_LEG_MULADD2(a[3], b[3], p1, p2, p1, p0);
	output[6] = p0;
	output[7] = p1;
}

void CAT_FASTCALL BigRTL::Multiply(const Leg *in_a, const Leg *in_b, Leg *out)
{
	// ICC improves performance of multiplication by about 15% over MSVC, and it compiles the template metaprogramming very fast
	switch (library_legs)
	{
	// MSVC really grinds to build this, so I have limited the number of cases that use template metaprogramming
#if defined(CAT_WORD_64)
	case 4: SchoolbookMultiply4(in_a, in_b, out); return;
	case 6: CombaMul<6>(in_a, in_b, out); return;
#endif
	case 8: CombaMul<8>(in_a, in_b, out); return;
#if defined(CAT_WORD_32) && defined(CAT_UNROLL_OVER_256_BITS)
	case 12: CombaMul<12>(in_a, in_b, out); return;
	case 16: CombaMul<16>(in_a, in_b, out); return;
#endif
	}

    out[library_legs] = MultiplyX(in_a, in_b[0], out);

    for (int ii = 1; ii < library_legs; ++ii)
        out[library_legs + ii] = MultiplyXAdd(in_a, in_b[ii], out + ii, out + ii);
}

void CAT_FASTCALL BigRTL::MultiplyLow(const Leg *in_a, const Leg *in_b, Leg *out)
{
    MultiplyX(in_a, in_b[0], out);

    for (int ii = 1; ii < library_legs; ++ii)
        MultiplyXAdd(library_legs - ii, in_a, in_b[ii], out + ii, out + ii);
}
