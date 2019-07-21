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

bool CAT_FASTCALL BigRTL::Greater(const Leg *in_a, const Leg *in_b)
{
    int legs = library_legs;

    while (legs-- > 0)
    {
        Leg a = in_a[legs];
        Leg b = in_b[legs];
        if (a < b) return false;
        if (a > b) return true;
    }

    return false;
}

bool CAT_FASTCALL BigRTL::GreaterX(const Leg *in, Leg x)
{
    for (int ii = library_legs - 1; ii > 0; --ii)
        if (in[ii]) return true;

    return in[0] > x;
}

bool CAT_FASTCALL BigRTL::Less(const Leg *in_a, const Leg *in_b)
{
    int legs = library_legs;

    while (legs-- > 0)
    {
        Leg a = in_a[legs];
        Leg b = in_b[legs];
        if (a > b) return false;
        if (a < b) return true;
    }

    return false;
}

bool CAT_FASTCALL BigRTL::LessX(const Leg *in, Leg x)
{
    for (int ii = library_legs - 1; ii > 0; --ii)
        if (in[ii]) return false;

    return in[0] < x;
}

bool CAT_FASTCALL BigRTL::Equal(const Leg *in_a, const Leg *in_b)
{
    return 0 == memcmp(in_a, in_b, library_legs * sizeof(Leg));
}

bool CAT_FASTCALL BigRTL::EqualX(const Leg *in, Leg x)
{
    if (in[0] != x) return false;

    for (int ii = 1; ii < library_legs; ++ii)
        if (in[ii]) return false;

    return true;
}

bool CAT_FASTCALL BigRTL::IsZero(const Leg *in)
{
    for (int ii = 0; ii < library_legs; ++ii)
        if (in[ii]) return false;

    return true;
}
