/*
	Copyright (c) 2009-2010 Christopher A. Taylor.  All rights reserved.

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

/*
    Several algorithms based on ideas from the "Handbook of Applied Cryptography"
    http://www.cacr.math.uwaterloo.ca/hac/
*/

#ifndef CAT_BIG_MONTGOMERY_HPP
#define CAT_BIG_MONTGOMERY_HPP

#include <cat/math/BigRTL.hpp>
#include <cat/rand/IRandom.hpp>

namespace cat {


// Performs fast modular arithmetic in the Montgomery Residue Number System
class BigMontgomery : public BigRTL
{
    static const int MON_OVERHEAD = 3 + 4;
    int mon_regs;

protected:
	Leg *TempProduct;
	Leg *TempProductHi;
    Leg *CachedModulus;
	Leg mod_inv;

public:
    BigMontgomery(int regs, int bits);

	// Must call SetModulus() before using this object
	void SetModulus(const Leg *mod);

public:
    const Leg *GetModulus() { return CachedModulus; }
    void CopyModulus(Leg *out);

public:
	// Convert value in register into RNS, stored in out
	void MonInput(const Leg *in, Leg *out);

	// Convert value in register from RNS, stored in out
	void MonOutput(const Leg *in, Leg *out);

	// Note: This will clobber the input product!
	// Reduce a double-register product to a single register in the RNS
	void MonReduceProduct(Leg *inout_product, Leg *out);

public:
	// Inputs and outputs must be in the Montgomery RNS
    void MonAdd(const Leg *in_a, const Leg *in_b, Leg *out);
    void MonSubtract(const Leg *in_a, const Leg *in_b, Leg *out);
    void MonNegate(const Leg *in, Leg *out);
    void MonDouble(const Leg *in, Leg *out);

public:
	// Inputs and outputs must be in the Montgomery RNS
    void MonMultiply(const Leg *in_a, const Leg *in_b, Leg *out);
    void MonSquare(const Leg *in, Leg *out);

public:
	// Base must be in the Montgomery RNS.  in_base != out
	void MonExpMod(const Leg *in_base, const Leg *in_exp, Leg *out);

public:
	// Input is NOT in the RNS (don't call MonInput)
	// Probably a prime, certainty = 4^-trials.  20: %99.9999999999 certainty
	bool IsRabinMillerPrime(IRandom *prng, const Leg *n, int trials = 20);
};


} // namespace cat

#endif // CAT_BIG_MONTGOMERY_HPP
