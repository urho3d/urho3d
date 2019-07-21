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

/*
	As discussed in the 2008 Fouque-Lercier-Real-Valette paper
	"Fault Attack on Elliptic Curve with Montgomery Ladder Implementation",
	some implementations of ECC are vulnerable to active attack that cause
	the	victim to compute a scalar point multiply on the quadratic twist.
	The twist will usually be of insecure group order unless the designer
	spends extra time insuring both the curve and its twist have large
	prime group order.  Bernstein's Curve25519 prevents this attack by
	being twist-secure, for example, rather than validating the input.

	My curves are actually quadratic twists of Edwards curves by design. =)
	In my case the twisted curve has secure group order and the twist of my
	twist is back to an Edwards curve again, which is of insecure order.

	To avoid any invalid point fault attacks in my cryptosystem, I validate
	that the input point (x,y) is on the curve.  I further check that the
	point is not x=0, which would be another way to introduce a fault,
	since x=0 is the identity element in Twisted Edwards coordinates and
	any multiple of x=0 is itself.

	I'm actually not sure if my code would be able to multiply a point
	that is not on the curve, but let's not find out!
*/

// Verify that the affine point (x,y) exists on the given curve
bool BigTwistedEdwards::PtValidAffine(const Leg *in)
{
    // 0 = 1 + d*x^2*y^2 + x^2 - y^2

    // A = x^2
    MrSquare(in+XOFF, A);

    // B = y^2
    MrSquare(in+YOFF, B);

    // C = A * B * d + 1 + A - B
    MrMultiply(A, B, C);
    MrMultiplyX(C, curve_d, C);
    MrAddX(C, 1);
    MrAdd(C, A, C);
    MrSubtract(C, B, C);
    MrReduce(C);

    // If the result is zero, it is on the curve
    return IsZero(C);
}

// Check if the affine point (x,y) is the additive identity x=0
bool BigTwistedEdwards::IsAffineIdentity(const Leg *in)
{
	return EqualX(in+XOFF, 0);
}
