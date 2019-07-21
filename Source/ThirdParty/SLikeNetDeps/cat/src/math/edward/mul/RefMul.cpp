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

// A reference multiplier to verify that PtMultiply() is functionally the same
void BigTwistedEdwards::RefMul(const Leg *in_p, const Leg *in_k, u8 msb_k, Leg *out)
{
    Leg *one = Get(te_regs - TE_OVERHEAD);

    PtCopy(in_p, one);

    bool seen = false;

    if (msb_k)
    {
        seen = true;
        PtCopy(one, out);
    }

    for (int ii = library_legs - 1; ii >= 0; --ii)
    {
        for (Leg jj = (Leg)1 << (CAT_LEG_BITS-1); jj; jj >>= 1)
        {
            PtEDouble(out, out);
            if (in_k[ii] & jj)
            {
                if (seen)
                    PtEAdd(one, out, out);
                else
                {
                    seen = true;
                    PtCopy(one, out);
                }
            }
        }
    }
}
