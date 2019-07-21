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
# define PT_FN PtEDouble /* Version that does produce the T coord */
#else
# define EXTENDED_T
# include "PtDouble.cpp"
# undef PT_FN
# define PT_FN PtDouble /* Version that does not produce the T coord */
#endif

/*
	The group laws used for point addition/doubling are the best in the
	literature at this time, requiring no branches just a straight shot
	through field operations.

	I have tweaked the order of operations to improve cache locality.

	On 32-bit platforms CPU time is broken down as:

	[PtDouble] time spent in misc operations: 1350
	[PtDouble] time spent in multiplies: 2707
	[PtDouble] time spent in squares: 2078
	[PtDouble] MrAdd 1: 390
	[PtDouble] MrDouble: 157
	[PtDouble] MrNegate: 120
	[PtDouble] MrAdd 2: 120
	[PtDouble] MrSubtract 1: 285
	[PtDouble] MrSubtract 2: 165
	[PtDouble] MrAdd 3: 113

	[PtEDouble] time spent in misc operations: 1320
	[PtEDouble] time spent in multiplies: 3083
	[PtEDouble] time spent in squares: 2032
	[PtEDouble] MrAdd 1: 405
	[PtEDouble] MrDouble: 150
	[PtEDouble] MrNegate: 120
	[PtEDouble] MrAdd 2: 135
	[PtEDouble] MrSubtract 1: 225
	[PtEDouble] MrSubtract 2: 150
	[PtEDouble] MrAdd 3: 135
*/

//#define CAT_DISPLAY_CYCLE_COUNT

#if defined(CAT_DISPLAY_CYCLE_COUNT)
#define CAT_CYCLE_COUNT(x) x
#include <cat/time/Clock.hpp>
#include <iostream>
using namespace std;
#else
#define CAT_CYCLE_COUNT(x)
#endif

// Extended Twisted Edwards Dedicated Doubling Formula in 4M 4S 5a
void BigTwistedEdwards::PT_FN(const Leg *in, Leg *out)
{
	CAT_CYCLE_COUNT(u32 t0 = Clock::cycles());

    // E = (X1 + Y1)^2 + H
    MrAdd(in+XOFF, in+YOFF, E);

	CAT_CYCLE_COUNT(u32 t1 = Clock::cycles());

	MrSquare(E, E); // Keep MrSquare() in cache

	// A = X1^2, B = Y1^2, C = 2 * Z1^2
    MrSquare(in+XOFF, A);
    MrSquare(in+YOFF, B);
    MrSquare(in+ZOFF, C);

	CAT_CYCLE_COUNT(u32 t2 = Clock::cycles());

	MrDouble(C, C);

	CAT_CYCLE_COUNT(u32 t2a = Clock::cycles());

	// G = -A + B, F = G - C, H = -A - B
    MrNegate(A, A);

	CAT_CYCLE_COUNT(u32 t2b = Clock::cycles());

	MrAdd(A, B, G);

	CAT_CYCLE_COUNT(u32 t2c = Clock::cycles());

    MrSubtract(A, B, H);

	CAT_CYCLE_COUNT(u32 t2d = Clock::cycles());

    MrSubtract(G, C, F);

	CAT_CYCLE_COUNT(u32 t2e = Clock::cycles());

    MrAdd(E, H, E);

	CAT_CYCLE_COUNT(u32 t3 = Clock::cycles());

    // X3 = E * F, Y3 = G * H, T3 = E * H, Z3 = F * G
    MrMultiply(E, F, out+XOFF);
    MrMultiply(G, H, out+YOFF);
#if defined(EXTENDED_T)
    MrMultiply(E, H, out+TOFF);
#endif
    MrMultiply(F, G, out+ZOFF);

	CAT_CYCLE_COUNT(u32 t4 = Clock::cycles());

#if defined(CAT_DISPLAY_CYCLE_COUNT)
#if defined(EXTENDED_T)

	cout << "[PtEDouble] time spent in misc operations: " << t1 - t0 + t3 - t2 << endl;
	cout << "[PtEDouble] time spent in multiplies: " << t4-t3 << endl;
	cout << "[PtEDouble] time spent in squares: " << t2 - t1 << endl;
	cout << "[PtEDouble] MrAdd 1: " << t1 - t0 << endl;
	cout << "[PtEDouble] MrDouble: " << t2a - t2 << endl;
	cout << "[PtEDouble] MrNegate: " << t2b - t2a << endl;
	cout << "[PtEDouble] MrAdd 2: " << t2c - t2b << endl;
	cout << "[PtEDouble] MrSubtract 1: " << t2d - t2c << endl;
	cout << "[PtEDouble] MrSubtract 2: " << t2e - t2d << endl;
	cout << "[PtEDouble] MrAdd 3: " << t3 - t2e << endl;

#else

	cout << "[PtDouble] time spent in misc operations: " << t1 - t0 + t3 - t2 << endl;
	cout << "[PtDouble] time spent in multiplies: " << t4-t3 << endl;
	cout << "[PtDouble] time spent in squares: " << t2 - t1 << endl;
	cout << "[PtDouble] MrAdd 1: " << t1 - t0 << endl;
	cout << "[PtDouble] MrDouble: " << t2a - t2 << endl;
	cout << "[PtDouble] MrNegate: " << t2b - t2a << endl;
	cout << "[PtDouble] MrAdd 2: " << t2c - t2b << endl;
	cout << "[PtDouble] MrSubtract 1: " << t2d - t2c << endl;
	cout << "[PtDouble] MrSubtract 2: " << t2e - t2d << endl;
	cout << "[PtDouble] MrAdd 3: " << t3 - t2e << endl;

#endif
#endif
}

#undef EXTENDED_T
