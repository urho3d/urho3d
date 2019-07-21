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

#ifndef CAT_BIG_RTL_HPP
#define CAT_BIG_RTL_HPP

#include <cat/math/Legs.hpp>

namespace cat {


// Implements a register transfer language (RTL) for big integer arithmetic
class BigRTL
{
    static const int BIG_OVERHEAD = 7; // overhead for ModularInverse()
    int library_regs;

protected:
    int library_legs;
    Leg *library_memory;

protected:
    static Leg CAT_FASTCALL ShiftRight(int legs, const Leg *in, int shift, Leg *out);
    static Leg CAT_FASTCALL ShiftLeft(int legs, const Leg *in, int shift, Leg *out);

protected:
    static u8 CAT_FASTCALL Add(int legs, const Leg *in_a, const Leg *in_b, Leg *out);
    static u8 CAT_FASTCALL Add(int legs_a, const Leg *in_a, int legs_b, const Leg *in_b, Leg *out); // legs_b <= legs_a
    static u8 CAT_FASTCALL Subtract(int legs, const Leg *in_a, const Leg *in_b, Leg *out);

protected:
    static Leg CAT_FASTCALL MultiplyX(int legs, const Leg *in_a, Leg in_b, Leg *out);
    static Leg CAT_FASTCALL MultiplyXAdd(int legs, const Leg *in_a, Leg in_b, const Leg *in_c, Leg *out);
    static Leg CAT_FASTCALL DoubleAdd(int legs, const Leg *in_a, const Leg *in_b, Leg *out);

protected:
	static void CAT_FASTCALL DivideCore(int A_used, Leg A_overflow, Leg *A, int B_used, Leg *B, Leg *Q); // A = remainder

public:
    BigRTL(int regs, int bits);
    ~BigRTL();

public:
    Leg * CAT_FASTCALL Get(int reg_index);
    CAT_INLINE int Legs() { return library_legs; }
    CAT_INLINE int RegBytes() { return library_legs * sizeof(Leg); }

public:
	// Save one single register to an endian-neutral byte array
    void CAT_FASTCALL Save(const Leg *in, void *out, int bytes);

	// Load one single register from an endian-neutral byte array
    void CAT_FASTCALL Load(const void *in, int bytes, Leg *out);

    bool CAT_FASTCALL LoadFromString(const char *in, int base, Leg *out);

public:
    void CAT_FASTCALL Copy(const Leg *in, Leg *out);
    void CAT_FASTCALL CopyX(Leg in, Leg *out);

public:
    int CAT_FASTCALL LegsUsed(const Leg *in);

public:
    bool CAT_FASTCALL Greater(const Leg *in_a, const Leg *in_b);
    bool CAT_FASTCALL GreaterX(const Leg *in, Leg x);
    bool CAT_FASTCALL Less(const Leg *in_a, const Leg *in_b);
    bool CAT_FASTCALL LessX(const Leg *in, Leg x);
    bool CAT_FASTCALL Equal(const Leg *in_a, const Leg *in_b);
    bool CAT_FASTCALL EqualX(const Leg *in, Leg x);
    bool CAT_FASTCALL IsZero(const Leg *in);

public:
    Leg CAT_FASTCALL ShiftLeft(const Leg *in, int shift, Leg *out);
	void CAT_FASTCALL MoveLegsRight(const Leg *in, int legs, Leg *out);

public:
    u8 CAT_FASTCALL Add(const Leg *in_a, const Leg *in_b, Leg *out);
    u8 CAT_FASTCALL AddX(Leg *inout, Leg x);
    u8 CAT_FASTCALL Subtract(const Leg *in_a, const Leg *in_b, Leg *out);
    u8 CAT_FASTCALL SubtractX(Leg *inout, Leg x);
    void CAT_FASTCALL Negate(const Leg *in, Leg *out);

public:
    u8 CAT_FASTCALL Double(const Leg *in, Leg *out);

public:
	// Eat all trailing least significant zeroes from the argument and return the number eatten
	int CAT_FASTCALL EatTrailingZeroes(Leg *inout);

public:
    Leg CAT_FASTCALL MultiplyX(const Leg *in_a, Leg in_b, Leg *out); // out = a[] * b
    Leg CAT_FASTCALL MultiplyXAdd(const Leg *in_a, Leg in_b, const Leg *in_c, Leg *out); // out = a[] * b + c[]
    Leg CAT_FASTCALL DoubleAdd(const Leg *in_a, const Leg *in_b, Leg *out); // out = a[] * 2 + b[]

public:
    void CAT_FASTCALL MultiplyLow(const Leg *in_a, const Leg *in_b, Leg *out); // out = a[] * b[], low half

public:
    // out[] gets the low part of the product, next reg gets high part
	// note: in_a != out, in_b != out
    void CAT_FASTCALL Multiply(const Leg *in_a, const Leg *in_b, Leg *out); // out+1:out = a[] * b[]
    void CAT_FASTCALL Square(const Leg *in, Leg *out); // out+1:out = in[] * in[]

public:
    Leg CAT_FASTCALL DivideX(const Leg *in_a, Leg in_b, Leg *out); // out = a[] / b, returns modulus
    Leg CAT_FASTCALL ModulusX(const Leg *in_a, Leg in_b); // returns a[] % b

public:
    bool CAT_FASTCALL Divide(const Leg *in_a, const Leg *in_b, Leg *out_q, Leg *out_r);

	// Divide the product of two registers (a+1:a) by single register (b)
	// Resulting quotient is two registers (q+1:q) and remainder is one register (r)
    bool CAT_FASTCALL DivideProduct(const Leg *in_a, const Leg *in_b, Leg *out_q, Leg *out_r);

public:
	// r = a * b (mod m)
	void CAT_FASTCALL MulMod(const Leg *in_a, const Leg *in_b, const Leg *in_m, Leg *r);

public:
    void CAT_FASTCALL ModularInverse(const Leg *x, const Leg *modulus, Leg *inverse);

public:
	Leg CAT_FASTCALL MultiplicativeInverseX(Leg x);
};


} // namespace cat

#endif // CAT_BIG_RTL_HPP
