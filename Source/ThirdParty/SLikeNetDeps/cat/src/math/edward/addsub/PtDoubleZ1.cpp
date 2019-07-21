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

#if defined(EXTENDED_T)
# undef PT_FN
# define PT_FN PtEDoubleZ1 /* Version that does produce the T coord */
#else
# define EXTENDED_T
# include "PtDoubleZ1.cpp"
# undef PT_FN
# define PT_FN PtDoubleZ1 /* Version that does not produce the T coord */
#endif

// Extended Twisted Edwards Dedicated Doubling Formula in 4M 3S 4a
void BigTwistedEdwards::PT_FN(const Leg *in, Leg *out)
{
    // A = X1^2, B = Y1^2, C = 2 * Z1^2 = 2
    MrSquare(in+XOFF, A);
    MrSquare(in+YOFF, B);
    //MrSquare(in+ZOFF, C);
    //MrDouble(C, C);

    // G = -A + B, F = G - C = G - 2, H = -A - B
    MrNegate(A, A);
    MrAdd(A, B, G);
    //MrSubtract(G, C, F);
    Copy(G, F);
    MrSubtractX(F, 2); // C = 2
    MrSubtract(A, B, H);

    // E = (X1 + Y1)^2 + H
    MrAdd(in+XOFF, in+YOFF, E);
    MrSquare(E, E);
    MrAdd(E, H, E);

    // X3 = E * F, Y3 = G * H, T3 = E * H, Z3 = F * G
    MrMultiply(E, F, out+XOFF);
    MrMultiply(G, H, out+YOFF);
#if defined(EXTENDED_T)
    MrMultiply(E, H, out+TOFF);
#endif
    MrMultiply(F, G, out+ZOFF);
}

#undef EXTENDED_T
