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
    Addition and doubling formulas using Extended Twisted Edwards coordinates from
    Hisil–Wong–Carter–Dawson paper "Twisted Edwards Curves Revisited" (Asiacrypt 2008)

    w-MOF scalar multiplication from http://www.sdl.hitachi.co.jp/crypto/mof/index-e.html

    Scalar multiplication precomputation with "conjugate addition" inspired by
    Longa-Gebotys paper "Novel Precomputation Schemes for Elliptic Curve Cryptosystems" (2008)
*/

/*
    Twisted Edwards E(p) Curve: a * x^2 + y^2 = 1 + d * x^2 * y^2, a = -1, p = 2^256 - c, c small

    Edwards coordinates: (X : Y : Z)
    Extended Edwards coordinates: (X : Y : T : Z), T = XY
    Edwards to Extended Edwards: (X : Y : Z) -> (XZ : YZ : XY : ZZ)
    Extended Edwards to Edwards: (X : Y : T : Z) -> (X : Y : Z)

    -(X : Y : T : Z) = (-X : Y : -T : Z)

    Additive Identity element: X = 0

    When Z = 1, a multiplication can be omitted

    Mixing operations for more speed:
        doubling, doubling -> E = 2E
        doubling, add      -> Ee = 2E, E = Ee + Ee
*/

#ifndef CAT_BIG_TWISTED_EDWARDS_HPP
#define CAT_BIG_TWISTED_EDWARDS_HPP

#include <cat/math/BigPseudoMersenne.hpp>
#include <cat/rand/IRandom.hpp>

namespace cat {


class BigTwistedEdwards : public BigPseudoMersenne
{
    static const int POINT_REGS = 4;
    static const int XOFF = 0;
    int YOFF, TOFF, ZOFF, POINT_STRIDE;

    // Point multiplication default window
    static const int WINDOW_BITS = 6;
    static const int PRECOMP_POINTS = 1 << (WINDOW_BITS-1);
    static const int PRECOMP_NEG_OFFSET = PRECOMP_POINTS / 2;

    static const int TE_OVERHEAD = (1 + PRECOMP_POINTS) * POINT_REGS + 9 + POINT_REGS * 2;
    int te_regs;

    // Local workspace
    Leg *A, *B, *C, *D, *E, *F, *G, *H, *CurveQ, *Generator;
    Leg *TempPt;

protected:
    Leg curve_d;

    // Simultaneous Add and Subtract for efficient precomputation (A +/- B) in 14M 1D 11a (versus 16M 2D 16a)
    void PtPrecompAddSub(const Leg *in_a, const Leg *in_b, Leg *sum, Leg *diff, int neg_offset);

public:
    BigTwistedEdwards(int regs, int bits, int C, int D, const u8 *Q, const u8 *GenPt);

    int PtLegs() { return Legs() * POINT_REGS; }

	Leg GetCurveD() { return curve_d; }
	const Leg *GetCurveQ() { return CurveQ; }
	const Leg *GetGenerator() { return Generator; }

public:
    // Unpack an Extended Projective point (X,Y,T,Z) from affine point (x,y)
    void PtUnpack(Leg *inout);

	// Set a point to the identity
	void PtIdentity(Leg *inout);

	// Check if the affine point (x,y) is the additive identity x=0
	bool IsAffineIdentity(const Leg *in);

public:
    void PtCopy(const Leg *in, Leg *out);

    // Fill the X coordinate of the point with a random value
    void PtFillRandomX(IRandom *prng, Leg *out);

    // Generate a random point on the curve that is not part of a small subgroup
    void PtGenerate(IRandom *prng, Leg *out);

public:
    // Solve for Y given the X point on a curve
    void PtSolveAffineY(Leg *inout);

    // Verify that the point (x,y) exists on the given curve
    bool PtValidAffine(const Leg *in);

public:
    // out(x) = X/Z
    void SaveAffineX(const Leg *in, void *out_x);

    // out(x,y) = (X/Z,Y/Z)
    void SaveAffineXY(const Leg *in, void *out_x, void *out_y);

    // out(X,Y) = (X,Y) without attempting to convert to affine from projective
    void SaveProjectiveXY(const Leg *in, void *out_x, void *out_y);

    // out(X,Y,Z,T) = (in_x,in_y), returns false if the coordinates are invalid
    bool LoadVerifyAffineXY(const void *in_x, const void *in_y, Leg *out);

    // Compute affine coordinates for (X,Y), set Z=1, and compute T = xy
    void PtNormalize(const Leg *in, Leg *out);

public:
    // Extended Twisted Edwards Negation Formula
    void PtNegate(const Leg *in, Leg *out);

    // Extended Twisted Edwards Unified Addition Formula (works when both inputs are the same) in 8M 1D 9a
    void PtEAdd(const Leg *in_a, const Leg *in_b, Leg *out);
    void PtAdd(const Leg *in_a, const Leg *in_b, Leg *out); // -1M, cannot be followed by PtAdd

    // Extended Twisted Edwards Unified Subtraction Formula (works when both inputs are the same) in 8M 1D 9a
    void PtESubtract(const Leg *in_a, const Leg *in_b, Leg *out);
    void PtSubtract(const Leg *in_a, const Leg *in_b, Leg *out); // -1M, cannot be followed by PtAdd

    // Extended Twisted Edwards Dedicated Doubling Formula in 4M 4S 5a
    void PtEDouble(const Leg *in, Leg *out);
    void PtDouble(const Leg *in, Leg *out); // -1M, cannot be followed by PtAdd

    // Extended Twisted Edwards Dedicated Doubling Formula Assuming Z=1, in 4M 3S 4a
    void PtEDoubleZ1(const Leg *in, Leg *out);
    void PtDoubleZ1(const Leg *in, Leg *out); // -1M, cannot be followed by PtAdd

public:
    // Allocate a table for use with PtMultiplyPrecomp()
    // Free the table with Aligned::Delete()
    Leg *PtMultiplyPrecompAlloc(int w);

    // Precompute odd multiples of input point
    void PtMultiplyPrecomp(const Leg *in, int w, Leg *table);

public:
    // Extended Twisted Edwards Scalar Multiplication k*p
    // Requires precomputation with PtMultiplyPrecomp()
    // CAN *NOT* BE followed by a Pt[E]Add()
    void PtMultiply(const Leg *in_precomp, int w, const Leg *in_k, u8 msb_k, Leg *out);

    // Extended Twisted Edwards Scalar Multiplication k*p
    // Uses default precomputation
    // CAN *NOT* BE followed by a Pt[E]Add()
    void PtMultiply(const Leg *in_p, const Leg *in_k, u8 msb_k, Leg *out);

    // A reference multiplier to verify that PtMultiply() is functionally the same
    void RefMul(const Leg *in_p, const Leg *in_k, u8 msb_k, Leg *out);

public:
    // Extended Twisted Edwards Simultaneous Scalar Multiplication k*P + l*Q
    // Requires precomputation with PtMultiplyPrecomp()
    // CAN *NOT* BE followed by a Pt[E]Add()
    void PtSiMultiply(const Leg *precomp_p, const Leg *precomp_q, int w,
					  const Leg *in_k, u8 msb_k, const Leg *in_l, u8 msb_l, Leg *out);
};


} // namespace cat

#endif // CAT_BIG_TWISTED_EDWARDS_HPP
