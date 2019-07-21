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

#include <cat/math/BigTwistedEdwards.hpp>
#include <cat/port/AlignedAlloc.hpp>
using namespace cat;

// Allocate a precomputed table of odd multiples of input point
// Free the table with Aligned::Delete()
Leg *BigTwistedEdwards::PtMultiplyPrecompAlloc(int w)
{
    int points = 1 + (1 << (w - 1));

    Leg *out = new (Aligned::ii) Leg[points * POINT_STRIDE];

    return out;
}

// Precompute odd multiples of input point
void BigTwistedEdwards::PtMultiplyPrecomp(const Leg *in, int w, Leg *out)
{
    int neg_offset = POINT_STRIDE << (w - 2);

	// Identity
	PtIdentity(out);
	out += POINT_STRIDE;

    // Precompute P and -P
    Leg *pre_a = out;
    PtCopy(in, pre_a);
    PtNegate(in, pre_a+neg_offset);

    Leg *P1 = pre_a;

    // Precompute 2P
    Leg *pre_2 = TempPt;
    PtEDouble(in, pre_2);

    // Precompute 3P and -3P
    Leg *pre_b = pre_a+POINT_STRIDE;
    PtEAdd(pre_a, pre_2, pre_b);
    PtNegate(pre_b, pre_b+neg_offset);

    Leg *P3 = pre_b;

    if (w == 6)
    {
        // More efficient than naive approach by 6M 5D 20a at the cost of 4S
        // Inspired by Longa-Gebotys 2008, but it is original

        // Precompute 5P and -5P
        pre_a = pre_b+POINT_STRIDE;
        PtEAdd(pre_b, pre_2, pre_a);
        PtNegate(pre_a, pre_a+neg_offset);

        Leg *P5 = pre_a;

        // Precompute 7P and -7P
        pre_b = pre_a+POINT_STRIDE;
        PtEAdd(pre_a, pre_2, pre_b);
        PtNegate(pre_b, pre_b+neg_offset);

        Leg *P7 = pre_b;

        // Precompute 9P and -9P
        pre_a = pre_b+POINT_STRIDE;
        PtEAdd(pre_b, pre_2, pre_a);
        PtNegate(pre_a, pre_a+neg_offset);

        Leg *P9 = pre_a;

        // Precompute 11P and -11P
        pre_b = pre_a+POINT_STRIDE;
        PtEAdd(pre_a, pre_2, pre_b);
        PtNegate(pre_b, pre_b+neg_offset);

        // Precompute 22P
        PtEDouble(pre_b, pre_2);

        pre_b += POINT_STRIDE*5;
        pre_a = pre_b + POINT_STRIDE;

        PtPrecompAddSub(pre_2, P1, pre_a, pre_b, neg_offset);
        pre_b -= POINT_STRIDE;
        pre_a += POINT_STRIDE;
        PtPrecompAddSub(pre_2, P3, pre_a, pre_b, neg_offset);
        pre_b -= POINT_STRIDE;
        pre_a += POINT_STRIDE;
        PtPrecompAddSub(pre_2, P5, pre_a, pre_b, neg_offset);
        pre_b -= POINT_STRIDE;
        pre_a += POINT_STRIDE;
        PtPrecompAddSub(pre_2, P7, pre_a, pre_b, neg_offset);
        pre_b -= POINT_STRIDE;
        pre_a += POINT_STRIDE;
        PtPrecompAddSub(pre_2, P9, pre_a, pre_b, neg_offset);
    }
    else // General case:
    {
        // Precompute +/- odd multiples of b by iteratively adding 2b
        int pos_point_count = 1 << (w-2);
        for (int table_index = 2; table_index < pos_point_count; table_index += 2)
        {
            pre_a = pre_b+POINT_STRIDE;
            PtEAdd(pre_b, pre_2, pre_a);
            PtNegate(pre_a, pre_a+neg_offset);

            pre_b = pre_a+POINT_STRIDE;
            PtEAdd(pre_a, pre_2, pre_b);
            PtNegate(pre_b, pre_b+neg_offset);
        }
    }
}
