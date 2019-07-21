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

#include <cat/math/BigPseudoMersenne.hpp>
using namespace cat;

void CAT_FASTCALL BigPseudoMersenne::MrReduceProductX(Leg overflow, Leg *inout)
{
    // Pseudo-Mersenne reduction
    Leg p_hi, p_lo;
    CAT_LEG_MULADD(overflow, modulus_c, inout[0], p_hi, p_lo);

    inout[0] = p_lo;

    // If the initial sum carried out,
    if ((inout[1] += p_hi) < p_hi)
    {
        // Ripple the carry out as far as needed
        for (int ii = 2; ii < library_legs; ++ii)
            if (++inout[ii]) return;

		while (AddX(inout, modulus_c));
    }
}


void CAT_FASTCALL BigPseudoMersenne::MrReduceProduct(const Leg *in_hi, const Leg *in_lo, Leg *output)
{
	// Pseudo-Mersenne reduction
	Leg overflow = MultiplyXAdd(in_hi, modulus_c, in_lo, output);

	MrReduceProductX(overflow, output);
}
