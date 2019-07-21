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

#if !defined(CAT_NO_LEGPAIR)

/*
	For MSVC, I've been able to get about a 3% overall improvement by
	implementing a huge, specialized Comba square function.
	It's really not worth the complexity.

	Instead I have implemented a Karatsuba squaring algorithm specialized
	for 256-bit inputs on a 32-bit processor without using the Comba method.

	8x8 Karatsuba squaring takes 67% of the time of an 8x8 Comba multiply.
*/

// This is (slightly) faster than normal 4x4 multiplication
CAT_INLINE void CAT_FASTCALL Square4(const Leg * CAT_RESTRICT input, Leg * CAT_RESTRICT output)
{
	Leg a = input[3], b = input[2], c = input[1], d = input[0];

	// Calculate square products
	CAT_LEG_MUL(d, d, output[1], output[0]);
	CAT_LEG_MUL(c, c, output[3], output[2]);
	CAT_LEG_MUL(b, b, output[5], output[4]);
	CAT_LEG_MUL(a, a, output[7], output[6]);

	Leg cross1, cross2, cross3, cross4, cross4a, cross5, cross6;

	// Calculate cross products
	CAT_LEG_MUL(c, d, cross2, cross1);
	CAT_LEG_MULADD(b, d, cross2, cross3, cross2);
	CAT_LEG_MULADD(a, d, cross3, cross4, cross3);
	CAT_LEG_MULADD(b, c, cross3, cross4a, cross3);
	CAT_LEG_MULADD2(a, c, cross4, cross4a, cross5, cross4);
	CAT_LEG_MULADD(a, b, cross5, cross6, cross5);

	// Multiply the cross product by 2 and add it to the square products
	LegPair x = ((LegPair)cross1 << 1) + output[1];
	output[1] = (Leg)x;
	x = (x >> CAT_LEG_BITS) + ((LegPair)cross2 << 1) + output[2];
	output[2] = (Leg)x;
	x = (x >> CAT_LEG_BITS) + ((LegPair)cross3 << 1) + output[3];
	output[3] = (Leg)x;
	x = (x >> CAT_LEG_BITS) + ((LegPair)cross4 << 1) + output[4];
	output[4] = (Leg)x;
	x = (x >> CAT_LEG_BITS) + ((LegPair)cross5 << 1) + output[5];
	output[5] = (Leg)x;
	x = (x >> CAT_LEG_BITS) + ((LegPair)cross6 << 1) + output[6];
	output[6] = (Leg)x;
	output[7] += (Leg)(x >> CAT_LEG_BITS);
}

// This is significantly faster than normal 8x8 Comba multiplication (67% runtime)
CAT_INLINE void CAT_FASTCALL Square8(const Leg * CAT_RESTRICT input, Leg * CAT_RESTRICT output)
{
	// Calculate square products
	Square4(input, output);
	Square4(input + 4, output + 8);

	// Calculate cross products
	// Depends on BigRTL.cpp including Multiply.cpp before Square.cpp
	Leg cross[8];
	SchoolbookMultiply4(input, input + 4, cross);

	// Multiply the cross product by 2 and add it to the square products
	LegPair x = ((LegPair)cross[0] << 1) + output[4];
	output[4] = (Leg)x;
	x = (x >> CAT_LEG_BITS) + ((LegPair)cross[1] << 1) + output[5];
	output[5] = (Leg)x;
	x = (x >> CAT_LEG_BITS) + ((LegPair)cross[2] << 1) + output[6];
	output[6] = (Leg)x;
	x = (x >> CAT_LEG_BITS) + ((LegPair)cross[3] << 1) + output[7];
	output[7] = (Leg)x;
	x = (x >> CAT_LEG_BITS) + ((LegPair)cross[4] << 1) + output[8];
	output[8] = (Leg)x;
	x = (x >> CAT_LEG_BITS) + ((LegPair)cross[5] << 1) + output[9];
	output[9] = (Leg)x;
	x = (x >> CAT_LEG_BITS) + ((LegPair)cross[6] << 1) + output[10];
	output[10] = (Leg)x;
	x = (x >> CAT_LEG_BITS) + ((LegPair)cross[7] << 1) + output[11];
	output[11] = (Leg)x;
	x = (x >> CAT_LEG_BITS) + output[12];
	output[12] = (Leg)x;
	x = (x >> CAT_LEG_BITS) + output[13];
	output[13] = (Leg)x;
	x = (x >> CAT_LEG_BITS) + output[14];
	output[14] = (Leg)x;
	x = (x >> CAT_LEG_BITS) + output[15];
	output[15] = (Leg)x;
}

#endif // CAT_NO_LEGPAIR


void CAT_FASTCALL BigRTL::Square(const Leg *input, Leg *output)
{
#if !defined(CAT_NO_LEGPAIR)
	if (library_legs == 8)
	{
		// Speeds up a 256-bit PtMultiply() by 8%
		Square8(input, output);
		return;
	}
#endif // CAT_NO_LEGPAIR

	Leg *cross = Get(library_regs - 2);

    // Calculate square products
    for (int ii = 0; ii < library_legs; ++ii)
        CAT_LEG_MUL(input[ii], input[ii], output[ii*2+1], output[ii*2]);

    // Calculate cross products
    cross[library_legs] = MultiplyX(library_legs-1, input+1, input[0], cross+1);
    for (int ii = 1; ii < library_legs-1; ++ii)
        cross[library_legs + ii] = MultiplyXAdd(library_legs-1-ii, input+1+ii, input[ii], cross+1+ii*2, cross+1+ii*2);

    // Multiply the cross product by 2 and add it to the square products
    output[library_legs*2-1] += DoubleAdd(library_legs*2-2, cross+1, output+1, output+1);
}
