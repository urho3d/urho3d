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
using namespace cat;

// Extended Twisted Edwards Scalar Multiplication k*p
// CAN *NOT* BE followed by a Pt[E]Add()
void BigTwistedEdwards::PtMultiply(const Leg *in_p, const Leg *in_k, u8 msb_k, Leg *out)
{
    Leg *DefaultPrecomp = Get(te_regs - TE_OVERHEAD);

    PtMultiplyPrecomp(in_p, WINDOW_BITS, DefaultPrecomp);
    PtMultiply(DefaultPrecomp, WINDOW_BITS, in_k, msb_k, out);
}

// w-MOF lookup table for PtMultiply()
struct {
    u8 add_index; // nth odd number to add: 0=0,1=1,2=3,3=5,4=7,...
    u8 doubles_after; // number of doubles to perform after add
} static const MOF_LUT[129] = {
	{0,0},{1,0},{1,1},{2,0},{1,2},{3,0},{2,1},{4,0},{1,3},
	{5,0},{3,1},{6,0},{2,2},{7,0},{4,1},{8,0},{1,4},
	{9,0},{5,1},{10,0},{3,2},{11,0},{6,1},{12,0},{2,3},
	{13,0},{7,1},{14,0},{4,2},{15,0},{8,1},{16,0},{1,5},
	{17,0},{9,1},{18,0},{5,2},{19,0},{10,1},{20,0},{3,3},
	{21,0},{11,1},{22,0},{6,2},{23,0},{12,1},{24,0},{2,4},
	{25,0},{13,1},{26,0},{7,2},{27,0},{14,1},{28,0},{4,3},
	{29,0},{15,1},{30,0},{8,2},{31,0},{16,1},{32,0},{1,6},
	{33,0},{17,1},{34,0},{9,2},{35,0},{18,1},{36,0},{5,3},
	{37,0},{19,1},{38,0},{10,2},{39,0},{20,1},{40,0},{3,4},
	{41,0},{21,1},{42,0},{11,2},{43,0},{22,1},{44,0},{6,3},
	{45,0},{23,1},{46,0},{12,2},{47,0},{24,1},{48,0},{2,5},
	{49,0},{25,1},{50,0},{13,2},{51,0},{26,1},{52,0},{7,3},
	{53,0},{27,1},{54,0},{14,2},{55,0},{28,1},{56,0},{4,4},
	{57,0},{29,1},{58,0},{15,2},{59,0},{30,1},{60,0},{8,3},
	{61,0},{31,1},{62,0},{16,2},{63,0},{32,1},{64,0},{1,7}
};

/*
	The overhead of w-MOF is about 0.002% of the total point multiply,
	so optimizing this function further would be a waste of time.

	It is also constant in runtime, so the side-channel attack resistance
	of the function is already pretty good.

	To make point multiplies faster, speed up PtDouble and PtAdd.

	PtAdd takes up just 17% of the runtime, and it is based on a lot of the
	same operations as PtDouble, so PtDouble is more important to optimize.
	The largest difference is that PtAdd doesn't use MrSquare.
*/

// Extended Twisted Edwards Scalar Multiplication k*p
// CAN *NOT* BE followed by a Pt[E]Add()
void BigTwistedEdwards::PtMultiply(const Leg *in_precomp, int w, const Leg *in_k, u8 msb_k, Leg *out)
{
    // Begin multiplication loop
    int leg = library_legs - 1, offset = CAT_LEG_BITS + w;
    Leg bits, last_leg;
    int doubles_before = 0, doubles_skip = 0;

	// Extend input scalar by one bit so it will work for the sum of two scalars
	last_leg = msb_k;
    if (last_leg)
        PtCopy(in_precomp + POINT_STRIDE, out); // copy base point
    else
        PtCopy(in_precomp, out); // copy additive identity

    for (;;)
    {
        // If still processing bits from current leg of k,
        if (offset <= CAT_LEG_BITS)
        {
            // Select next bits from current leg of k
            bits = last_leg >> (CAT_LEG_BITS - offset);
        }
        else if (leg >= 0)
        {
            // Next bits straddle the previous and next legs of k
            Leg new_leg = in_k[leg--];
            offset -= CAT_LEG_BITS;
            bits = (last_leg << offset) | (new_leg >> (CAT_LEG_BITS - offset));
            last_leg = new_leg;
        }
        else if (offset <= CAT_LEG_BITS + w)
        {
            // Pad zeroes on the right
            bits = last_leg << (offset - CAT_LEG_BITS);

            // Skip padding - 1 doubles after leaving this loop
            doubles_skip = offset - CAT_LEG_BITS - 1;
        }
        else break;

        // Invert low bits if negative, mask out high bit, and get table entry
        Leg z = (((bits ^ (0 - ((bits >> w) & 1))) & ((1 << w) - 1)) + 1) >> 1;

        // Extract the operation for this table entry
        Leg neg_mask = (bits & ((Leg)1 << w)) >> 2;
		if (!z) neg_mask = 0; // "negative zero" -- occurs when bits are all ones
        const Leg *precomp = in_precomp + (MOF_LUT[z].add_index + neg_mask) * POINT_STRIDE;
        int doubles_after = MOF_LUT[z].doubles_after;
		if (!z) doubles_after = w - 1; // fixes trailing doubles for final partial window of all zeroes

		// Perform doubles before addition
		doubles_before += w - doubles_after;

		// There will always be at least one doubling to perform here
		while (--doubles_before)
			PtDouble(out, out);
		PtEDouble(out, out);

		// Perform addition or subtraction from the precomputed table
		PtAdd(out, precomp, out);

		// Accumulate doubles after addition
		doubles_before = doubles_after;

        // Set up offset for next time around
        offset += w;
    }

    // Skip some doubles at the end due to window underrun
    if (doubles_before > doubles_skip)
    {
        doubles_before -= doubles_skip;

        // Perform trailing doubles
        while (doubles_before--)
            PtDouble(out, out);
    }
}


// Extended Twisted Edwards Simultaneous Scalar Multiplication k*P + l*Q
// Requires precomputation with PtMultiplyPrecomp()
// CAN *NOT* BE followed by a Pt[E]Add()
void BigTwistedEdwards::PtSiMultiply(const Leg *precomp_p, const Leg *precomp_q, int w,
									 const Leg *in_k, u8 msb_k, const Leg *in_l, u8 msb_l, Leg *out)
{
    // Begin multiplication loop
    int leg = library_legs - 1, offset = CAT_LEG_BITS + w;
    Leg bits_k, last_leg_k, bits_l, last_leg_l;
    int doubles_before = 0, doubles_skip = 0;

	// Extend input scalar by one bit so it will work for the sum of two scalars
	last_leg_k = msb_k;
    if (last_leg_k)
        PtCopy(precomp_p + POINT_STRIDE, out); // copy base point
    else
        PtCopy(precomp_p, out); // copy additive identity

	last_leg_l = msb_l;
    if (last_leg_l)
        PtAdd(out, precomp_q + POINT_STRIDE, out); // add base point
    else
        PtAdd(out, precomp_q, out); // add additive identity

    for (;;)
    {
        // If still processing bits from current leg of k,
        if (offset <= CAT_LEG_BITS)
        {
            // Select next bits from current leg of k
            bits_k = last_leg_k >> (CAT_LEG_BITS - offset);
            bits_l = last_leg_l >> (CAT_LEG_BITS - offset);
        }
        else if (leg >= 0)
        {
            // Next bits straddle the previous and next legs of k
            Leg new_leg_k = in_k[leg];
            Leg new_leg_l = in_l[leg--];
            offset -= CAT_LEG_BITS;
            bits_k = (last_leg_k << offset) | (new_leg_k >> (CAT_LEG_BITS - offset));
            last_leg_k = new_leg_k;
            bits_l = (last_leg_l << offset) | (new_leg_l >> (CAT_LEG_BITS - offset));
            last_leg_l = new_leg_l;
        }
        else if (offset <= CAT_LEG_BITS + w)
        {
            // Pad zeroes on the right
            bits_k = last_leg_k << (offset - CAT_LEG_BITS);
            bits_l = last_leg_l << (offset - CAT_LEG_BITS);

            // Skip padding - 1 doubles after leaving this loop
            doubles_skip = offset - CAT_LEG_BITS - 1;
        }
        else break;

        // Invert low bits if negative, mask out high bit, and get table entry
        Leg z_k = (((bits_k ^ (0 - ((bits_k >> w) & 1))) & ((1 << w) - 1)) + 1) >> 1;
        Leg z_l = (((bits_l ^ (0 - ((bits_l >> w) & 1))) & ((1 << w) - 1)) + 1) >> 1;

        // Extract the operation for this table entry
        Leg neg_mask_k = (bits_k & ((Leg)1 << w)) >> 2;
        Leg neg_mask_l = (bits_l & ((Leg)1 << w)) >> 2;
		if (!z_k) neg_mask_k = 0; // "negative zero" -- occurs when bits are all ones
		if (!z_l) neg_mask_l = 0; // "negative zero" -- occurs when bits are all ones
        const Leg *precomp_k = precomp_p + (MOF_LUT[z_k].add_index + neg_mask_k) * POINT_STRIDE;
        const Leg *precomp_l = precomp_q + (MOF_LUT[z_l].add_index + neg_mask_l) * POINT_STRIDE;
        int doubles_after_k = MOF_LUT[z_k].doubles_after;
        int doubles_after_l = MOF_LUT[z_l].doubles_after;
		if (!z_k) doubles_after_k = w - 1; // fixes trailing doubles for final partial window of all zeroes
		if (!z_l) doubles_after_l = w - 1; // fixes trailing doubles for final partial window of all zeroes

		int after1, after2;
		const Leg *add1, *add2;

		if (doubles_after_k >= doubles_after_l)
		{
			after1 = doubles_after_k;
			after2 = doubles_after_l;
			add1 = precomp_k;
			add2 = precomp_l;
		}
		else
		{
			after1 = doubles_after_l;
			after2 = doubles_after_k;
			add1 = precomp_l;
			add2 = precomp_k;
		}

		// Perform doubles before addition
		doubles_before += w - after1;

		// There will always be at least one doubling to perform here
		while (--doubles_before)
			PtDouble(out, out);
		PtEDouble(out, out);

		doubles_before = after1 - after2;
		if (doubles_before)
		{
			// Perform addition or subtraction from the precomputed table
			PtAdd(out, add1, out);

			// Perform doubles between the two interleaved adds
			while (--doubles_before)
				PtDouble(out, out);
			PtEDouble(out, out);
		}
		else
		{
			// Perform addition or subtraction from the precomputed table
			PtEAdd(out, add1, out);

			// Note: Has resistance from timing attack since PtEAdd() and
			// PtEDouble() both have just one multiply more than usual.
		}

		// Perform addition or subtraction from the precomputed table
		PtAdd(out, add2, out);

		// Accumulate doubles after addition
		doubles_before = after2;

        // Set up offset for next time around
        offset += w;
    }

    // Skip some doubles at the end due to window underrun
    if (doubles_before > doubles_skip)
    {
        doubles_before -= doubles_skip;

        // Perform trailing doubles
        while (doubles_before--)
            PtDouble(out, out);
    }
}
