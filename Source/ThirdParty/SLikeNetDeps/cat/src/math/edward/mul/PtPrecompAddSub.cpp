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

// Simultaneous Add and Subtract for efficient precomputation (A +/- B) in 14M 1D 11a (versus 16M 2D 16a)
void BigTwistedEdwards::PtPrecompAddSub(const Leg *in_a, const Leg *in_b, Leg *sum, Leg *diff, int neg_offset)
{
    // A = (Y1 - X1) * (Y2 - X2)
    MrSubtract(in_a+YOFF, in_a+XOFF, C);
    MrSubtract(in_b+YOFF, in_b+XOFF, D);
    MrMultiply(C, D, F);

    // B = (Y1 + X1) * (Y2 + X2)
    MrAdd(in_a+YOFF, in_a+XOFF, E);
    MrAdd(in_b+YOFF, in_b+XOFF, H);
    MrMultiply(E, H, G);

    // I = (Y1 - X1) * (Y2 + X2)
    MrMultiply(C, H, A);

    // J = (Y1 + X1) * (Y2 - X2)
    MrMultiply(E, D, B);

    // C = 2 * d * T1 * T2 (can remove multiplication by d if inputs are known to be different)
    MrMultiply(in_a+TOFF, in_b+TOFF, C);
    MrMultiplyX(C, curve_d * 2, C);

    // D = 2 * Z1 * Z2
    MrMultiply(in_a+ZOFF, in_b+ZOFF, D);
    MrDouble(D, D);

    // E = B - A, F = D - C, G = D + C, H = B + A
    MrSubtract(G, F, E);
    MrAdd(G, F, H);
    MrSubtract(D, C, F);
    MrAdd(D, C, G);

    // X3 = E * F, Y3 = G * H, T3 = E * H, Z3 = F * G
    MrMultiply(E, F, sum+XOFF);
    MrMultiply(G, H, sum+YOFF);
    MrMultiply(E, H, sum+TOFF);
    MrMultiply(F, G, sum+ZOFF);
    PtNegate(sum, sum + neg_offset);

    // E = J - I, F <-> G, H = J + I
    MrSubtract(B, A, E);
    MrAdd(B, A, H);

    // X3 = E * F, Y3 = G * H, T3 = E * H, Z3 = F * G
    MrMultiply(E, G, diff+XOFF);
    MrMultiply(F, H, diff+YOFF);
    MrMultiply(E, H, diff+TOFF);
    MrMultiply(G, F, diff+ZOFF);
    PtNegate(diff, diff + neg_offset);
}
