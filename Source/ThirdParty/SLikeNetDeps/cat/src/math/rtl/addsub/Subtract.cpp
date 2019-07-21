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

u8 CAT_FASTCALL BigRTL::Subtract(const Leg *in_a, const Leg *in_b, Leg *out)
{
    return Subtract(library_legs, in_a, in_b, out);
}

u8 CAT_FASTCALL BigRTL::Subtract(int legs, const Leg *in_a, const Leg *in_b, Leg *out)
{
#if !defined(CAT_NO_LEGPAIR)

    // Subtract first two legs without a borrow-in
    LegPairSigned diff = (LegPairSigned)in_a[0] - in_b[0];
    out[0] = (Leg)diff;

    // Subtract remaining legs
    for (int ii = 1; ii < legs; ++ii)
    {
        diff = ((diff >> CAT_LEG_BITS) + in_a[ii]) - in_b[ii];
        out[ii] = (Leg)diff;
    }

    return (u8)(diff >> CAT_LEG_BITS) & 1;

#else

    // Subtract first two legs without a borrow-in
    Leg t = in_a[0];
    Leg s = in_b[0];
    Leg w = t - s;
    u8 c = t < s;

    out[0] = w;

    // Subtract remaining legs
    for (int ii = 1; ii < legs; ++ii)
    {
        // Calculate difference
        Leg a = in_a[ii];
        Leg b = in_b[ii];
        Leg d = a - b - c;

        // Calculate borrow-out
        c = c ? (a < d || b == ~(Leg)0) : (a < b);

        out[ii] = d;
    }

    return c;

#endif
}
