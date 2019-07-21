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

Leg CAT_FASTCALL BigRTL::ShiftLeft(const Leg *in, int shift, Leg *out)
{
    return ShiftLeft(library_legs, in, shift, out);
}

Leg CAT_FASTCALL BigRTL::ShiftLeft(int legs, const Leg *in, int shift, Leg *out)
{
    if (!shift)
    {
        memcpy(out, in, legs * sizeof(Leg));
        return 0;
    }

    Leg carry = in[0];

    out[0] = carry << shift;

    for (int ii = 1; ii < legs; ++ii)
    {
        Leg x = in[ii];
        out[ii] = (x << shift) | (carry >> (CAT_LEG_BITS - shift));
        carry = x;
    }

    return carry >> (CAT_LEG_BITS - shift);
}

Leg CAT_FASTCALL BigRTL::ShiftRight(int legs, const Leg *in, int shift, Leg *out)
{
    if (!shift)
    {
        memcpy(out, in, legs * sizeof(Leg));
        return 0;
    }

    Leg carry = in[legs-1];

    out[legs-1] = carry >> shift;

    for (int ii = legs-2; ii >= 0; --ii)
    {
        Leg x = in[ii];
        out[ii] = (x >> shift) | (carry << (CAT_LEG_BITS - shift));
        carry = x;
    }

    return carry << (CAT_LEG_BITS - shift);
}

void CAT_FASTCALL BigRTL::MoveLegsRight(const Leg *in, int legs, Leg *out)
{
	memmove(out, in + legs, (library_legs - legs) * sizeof(Leg));
	memset(out + library_legs - legs, 0, legs * sizeof(Leg));
}
