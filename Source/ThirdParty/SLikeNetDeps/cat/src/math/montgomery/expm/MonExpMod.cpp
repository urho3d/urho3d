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

#include <cat/math/BigMontgomery.hpp>
using namespace cat;

// Base must be in the Montgomery RNS.  in_base != out
void BigMontgomery::MonExpMod(const Leg *in_base, const Leg *in_exp, Leg *out)
{
	bool seen_high_bit = false;

	// Left-to-right square and multiply method
	for (int ii = library_legs - 1; ii >= 0; --ii)
	{
		Leg e_i = in_exp[ii];

		for (Leg mask = CAT_LEG_MSB; mask; mask >>= 1)
		{
			if (seen_high_bit)
			{
				// out = out*out (mod p)
				MonSquare(out, out);

				if (e_i & mask)
				{
					// out *= base (mod p)
					MonMultiply(out, in_base, out);
				}
			}
			else
			{
				if (e_i & mask)
				{
					// out = base
					Copy(in_base, out);
					seen_high_bit = true;
				}
			}
		}
	}

	// 0^e = 0
	if (!seen_high_bit)
		CopyX(0, out);
}
