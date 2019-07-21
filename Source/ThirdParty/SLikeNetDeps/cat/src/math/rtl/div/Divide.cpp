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
#include <cat/math/BitMath.hpp>
using namespace cat;

bool CAT_FASTCALL BigRTL::Divide(const Leg *in_a, const Leg *in_b, Leg *out_q, Leg *out_r)
{
    // If a < b, avoid division
    if (Less(in_a, in_b))
    {
        Copy(in_a, out_r);
        CopyX(0, out_q);
        return true;
    }

    // {q, r} = a / b

    int B_used = LegsUsed(in_b);
    if (!B_used) return false;
    int A_used = LegsUsed(in_a);

    // If b is just one leg, use faster DivideX code
    if (B_used == 1)
    {
        Leg R = DivideX(in_a, in_b[0], out_q);
        CopyX(R, out_r);
        return true;
    }

    Leg *A = Get(library_regs - 1); // shifted numerator
    Leg *B = Get(library_regs - 2); // shifted denominator

    // Determine shift required to set high bit of highest leg in b
    int shift = CAT_LEG_BITS - CAT_USED_BITS(in_b[B_used-1]) - 1;

    // Shift a and b by these bits, probably making A one leg larger
    Leg A_overflow = ShiftLeft(A_used, in_a, shift, A);
    ShiftLeft(B_used, in_b, shift, B);

    DivideCore(A_used, A_overflow, A, B_used, B, out_q);

    // Zero the unused legs of the quotient
    int offset = A_used - B_used + 1;
    memset(out_q + offset, 0, (library_legs - offset) * sizeof(Leg));

    // Fix remainder shift and zero its unused legs
    memset(out_r + B_used, 0, (library_legs - B_used) * sizeof(Leg));
    ShiftRight(B_used, A, shift, out_r);

    return true;
}


// Divide the product of two registers (a+1:a) by single register (b)
// Resulting quotient is two registers (q+1:q) and remainder is one register (r)
bool CAT_FASTCALL BigRTL::DivideProduct(const Leg *in_a, const Leg *in_b, Leg *out_q, Leg *out_r)
{
	int B_used = LegsUsed(in_b);
    if (!B_used) return false;

	const Leg *in_a_hi = in_a + library_legs;

    int A_used = LegsUsed(in_a_hi);
	if (A_used) A_used += library_legs;
	else
	{
		// If a < b, avoid division
		if (Less(in_a, in_b))
		{
			Copy(in_a, out_r);
			memset(out_q, 0, library_legs * 2);
			return true;
		}

		A_used = LegsUsed(in_a);
	}

    // {q, r} = a / b
    Leg *A = Get(library_regs - 2); // shifted numerator
    Leg *B = Get(library_regs - 3); // shifted denominator

    // Determine shift required to set high bit of highest leg in b
    int shift = CAT_LEG_BITS - CAT_USED_BITS(in_b[B_used-1]) - 1;

    // Shift a and b by these bits, probably making A one leg larger
    Leg A_overflow = ShiftLeft(A_used, in_a, shift, A);
    ShiftLeft(B_used, in_b, shift, B);

    DivideCore(A_used, A_overflow, A, B_used, B, out_q);

    // Zero the unused legs of the quotient
    int offset = A_used - B_used + 1;
    memset(out_q + offset, 0, (library_legs*2 - offset) * sizeof(Leg));

    // Fix remainder shift and zero its unused legs
    memset(out_r + B_used, 0, (library_legs - B_used) * sizeof(Leg));
    ShiftRight(B_used, A, shift, out_r);

    return true;
}
