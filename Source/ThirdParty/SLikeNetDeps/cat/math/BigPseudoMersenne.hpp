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

    Several algorithms based on ideas from the
    "Handbook of Elliptic and Hyperelliptic Curve Cryptography"
    http://www.hyperelliptic.org/HEHCC/
*/

#ifndef CAT_BIG_PSEUDO_MERSENNE_HPP
#define CAT_BIG_PSEUDO_MERSENNE_HPP

#include <cat/math/BigRTL.hpp>

namespace cat {


// Performs fast arithmetic modulo 2^bits-C, C = 1 (mod 4) or 3 (mod 8), C < 16384
class BigPseudoMersenne : public BigRTL
{
    static const int PM_OVERHEAD = 6; // overhead for MrSquareRoot()
    int pm_regs;

protected:
    Leg *CachedModulus;
    Leg modulus_c;

    void CAT_FASTCALL MrReduceProductX(Leg overflow, Leg *inout);
    void CAT_FASTCALL MrReduceProduct(const Leg *in_hi, const Leg *in_lo, Leg *out);

public:
    BigPseudoMersenne(int regs, int bits, int C);

public:
    const Leg *GetModulus() { return CachedModulus; }
    void CAT_FASTCALL CopyModulus(Leg *out);

public:
    // Result may be one modulus too large, so efficiently correct that
    void CAT_FASTCALL MrReduce(Leg *inout);

public:
    void CAT_FASTCALL MrAdd(const Leg *in_a, const Leg *in_b, Leg *out);
    void CAT_FASTCALL MrAddX(Leg *inout, Leg x);
    void CAT_FASTCALL MrSubtract(const Leg *in_a, const Leg *in_b, Leg *out);
    void CAT_FASTCALL MrSubtractX(Leg *inout, Leg x);
    void CAT_FASTCALL MrNegate(const Leg *in, Leg *out);

public:
    void CAT_FASTCALL MrDouble(const Leg *in, Leg *out);

public:
    void CAT_FASTCALL MrMultiply(const Leg *in_a, const Leg *in_b, Leg *out);
    void CAT_FASTCALL MrMultiplyX(const Leg *in_a, Leg in_b, Leg *out);
    void CAT_FASTCALL MrSquare(const Leg *in, Leg *out);

public:
    void CAT_FASTCALL MrInvert(const Leg *in, Leg *out);

public:
    void CAT_FASTCALL MrSquareRoot(const Leg *in, Leg *out);
};


} // namespace cat

#endif // CAT_BIG_PSEUDO_MERSENNE_HPP
