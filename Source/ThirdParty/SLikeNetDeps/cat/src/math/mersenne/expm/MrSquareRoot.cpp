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

void CAT_FASTCALL BigPseudoMersenne::MrSquareRoot(const Leg *in, Leg *out)
{
	// Uses the left-to-right square and multiply exponentiation algorithm,
	// which is sped up a bit by recognizing that the exponent is all one bits
	// until about the last 13 bits.  So it avoids a lot of multiplies.

	Leg *T = Get(pm_regs - 4);
	Leg *S = Get(pm_regs - 5);
	Leg *D = Get(pm_regs - 6);

	// Optimal window size is sqrt(bits-16)
	const int w = 16; // Constant window size, optimal for 256-bit modulus

	if ((CachedModulus[0] & 3) == 3)
	{
	    // Square root for modulus p = 3 mod 4
		// out = in ^ (p + 1)/4

		// Perform exponentiation for the first w bits
		Copy(in, S);
		int ctr = w - 1;
		while (ctr--)
		{
			MrSquare(S, S);
			MrMultiply(S, in, S);
		}

		// Store result in a temporary register
		Copy(S, T);

		// NOTE: This assumes that modulus_c < 16384 = 2^(w-2)
		int one_frames = (RegBytes()*8 - w*2) / w;
		while (one_frames--)
		{
			// Just multiply once re-using the first result, every 16 bits
			MrSquare(S, S); MrSquare(S, S); MrSquare(S, S); MrSquare(S, S);
			MrSquare(S, S); MrSquare(S, S); MrSquare(S, S); MrSquare(S, S);
			MrSquare(S, S); MrSquare(S, S); MrSquare(S, S); MrSquare(S, S);
			MrSquare(S, S); MrSquare(S, S); MrSquare(S, S); MrSquare(S, S);
			MrMultiply(S, T, S);
		}

		// For the final leg just do bitwise exponentiation
		// NOTE: Makes use of the fact that the window size is a power of two
		Leg m_low = 1 - modulus_c;
		for (Leg bit = (Leg)1 << (w - 1); bit >= 4; bit >>= 1)
		{
			MrSquare(S, S);

			if (m_low & bit)
				MrMultiply(S, in, S);
		}

		Copy(S, out);
	}
	else if ((CachedModulus[0] & 7) == 5)
	{
	    // Square root for modulus p = 5 mod 8 using Atkin's method:
		// D = 2 * in
		// S = D ^ (p - 5)/8
		// out = in * S * ((D * S^2) - 1)

		// Perform exponentiation for the first w bits
		MrDouble(in, D);
		MrSquare(D, S);
		MrMultiply(S, D, S);
		int ctr = w - 2;
		while (ctr--)
		{
			MrSquare(S, S);
			MrMultiply(S, D, S);
		}

		// Store result in a temporary register
		Copy(S, T);

		// NOTE: This assumes that modulus_c < 8192 = 2^(w-3)
		int one_frames = (RegBytes()*8 - w*2) / w;
		while (one_frames--)
		{
			// Just multiply once re-using the first result, every 16 bits
			MrSquare(S, S); MrSquare(S, S); MrSquare(S, S); MrSquare(S, S);
			MrSquare(S, S); MrSquare(S, S); MrSquare(S, S); MrSquare(S, S);
			MrSquare(S, S); MrSquare(S, S); MrSquare(S, S); MrSquare(S, S);
			MrSquare(S, S); MrSquare(S, S); MrSquare(S, S); MrSquare(S, S);
			MrMultiply(S, T, S);
		}

		// For the final leg just do bitwise exponentiation
		// NOTE: Makes use of the fact that the window size is a power of two
		Leg m_low = 0 - modulus_c;
		for (Leg bit = (Leg)1 << (w - 1); bit >= 8; bit >>= 1)
		{
			MrSquare(S, S);

			if (m_low & bit)
				MrMultiply(S, D, S);
		}

		// T = S^2 * D - 1
		MrSquare(S, T);
		MrMultiply(T, D, T);
		MrSubtractX(T, 1);

		// out = in * S * T
		MrMultiply(in, S, out);
		MrMultiply(out, T, out);
	}
}
