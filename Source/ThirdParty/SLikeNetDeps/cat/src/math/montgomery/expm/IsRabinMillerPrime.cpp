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

bool BigMontgomery::IsRabinMillerPrime(IRandom *prng, const Leg *n, int trials)
{
	Leg *d = Get(mon_regs - 4);
	Leg *a = Get(mon_regs - 5);
	Leg *x = Get(mon_regs - 6);
	Leg *n_1 = Get(mon_regs - 7);

	// Returns false for n = 0 and n = 1
	if (!GreaterX(n, 1))
		return false;

	// Use n as the modulus for Montgomery RNS
	SetModulus(n);

	// n_1 = n-1
	Copy(n, n_1);
	SubtractX(n_1, 1);

	// d = n_1 = n-1
	Copy(n_1, d);

	// s = trailing zeroes eatten from d
	int s = EatTrailingZeroes(d);

	// For each trial,
	while (trials--)
	{
		// Generate a random number [2, n-1]
		do prng->Generate(a, library_legs * sizeof(Leg));
		while (!Less(a, n) || !GreaterX(a, 2));

		// Bring a into the RNS
		MonInput(a, x);

		// a = a^d (mod p) in RNS
		MonExpMod(x, d, a);

		// x = a out of RNS
		MonOutput(a, x);

		// Passes this trial if x = 1 or n-1
		if (EqualX(x, 1)) continue;
		if (!AddX(x, 1) && Equal(x, n)) continue;

		// For s-1 times,
		for (int r = 1; r < s; ++r)
		{
			// a = a*a (mod p) in RNS
			MonSquare(a, a);

			// x = a out of RNS
			MonOutput(a, x);

			// If x = 1, it is composite
			if (EqualX(x, 1)) return false;

			// If x = n-1, it could still be prime
			if (Equal(x, n_1)) goto SKIP_TO_NEXT_TRIAL;
		}

		// If we didn't find any x = n-1, it is composite
		return false;

SKIP_TO_NEXT_TRIAL:; // yea i just went there ..|.. sue me
	}

	// It is probably prime
	return true;
}
