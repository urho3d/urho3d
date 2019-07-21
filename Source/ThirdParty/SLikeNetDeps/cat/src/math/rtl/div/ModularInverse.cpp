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

#include <cat/math/BigRTL.hpp>
using namespace cat;

void CAT_FASTCALL BigRTL::ModularInverse(const Leg *x, const Leg *modulus, Leg *inverse)
{
    if (EqualX(x, 1))
    {
        CopyX(1, inverse);
        return;
    }

    Leg *t1 = inverse;
    Leg *t0 = Get(library_regs - 3);
    Leg *b = Get(library_regs - 4);
    Leg *c = Get(library_regs - 5);
    Leg *q = Get(library_regs - 6);
    Leg *p = Get(library_regs - 7);

    Copy(x, b);
    Divide(modulus, b, t0, c);
    CopyX(1, t1);

    while (!EqualX(c, 1))
    {
        Divide(b, c, q, b);
        MultiplyLow(q, t0, p);
        Add(t1, p, t1);

        if (EqualX(b, 1))
            return;

        Divide(c, b, q, c);
        MultiplyLow(q, t1, p);
        Add(t0, p, t0);
    }

    Subtract(modulus, t0, inverse);
}
