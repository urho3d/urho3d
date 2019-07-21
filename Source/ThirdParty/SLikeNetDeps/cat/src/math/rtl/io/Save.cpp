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
#include <cat/port/EndianNeutral.hpp>
using namespace cat;

void CAT_FASTCALL BigRTL::Save(const Leg *in_leg, void *out, int bytes)
{
    // Prepare to copy
    Leg *out_leg = (Leg*)out;
    int ii, legs = bytes / sizeof(Leg);

    // Copy 4 legs at a time
    for (ii = 4; ii <= legs; ii += 4)
    {
        out_leg[ii - 4] = getLE(in_leg[ii - 4]);
        out_leg[ii - 3] = getLE(in_leg[ii - 3]);
        out_leg[ii - 2] = getLE(in_leg[ii - 2]);
        out_leg[ii - 1] = getLE(in_leg[ii - 1]);
    }

    // Copy remaining legs
    switch (legs % 4)
    {
    case 3: out_leg[legs - 3] = getLE(in_leg[legs - 3]);
    case 2: out_leg[legs - 2] = getLE(in_leg[legs - 2]);
    case 1: out_leg[legs - 1] = getLE(in_leg[legs - 1]);
    }

    // Zero remaining buffer bytes
    memset(&out_leg[legs], 0, bytes - legs * sizeof(Leg));
}
