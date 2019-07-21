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

#include <cat/math/BigPseudoMersenne.hpp>
#include <cstring>
using namespace cat;

BigPseudoMersenne::BigPseudoMersenne(int regs, int bits, int C)
    : BigRTL(regs + PM_OVERHEAD, bits)
{
    pm_regs = regs + PM_OVERHEAD;
    modulus_c = C;

    // Reserve a register to contain the full modulus
    CachedModulus = Get(pm_regs - 1);
    CopyModulus(CachedModulus);
}

void CAT_FASTCALL BigPseudoMersenne::CopyModulus(Leg *out)
{
    // Set low leg to -C, set all bits on the rest
    out[0] = 0 - modulus_c;
    memset(&out[1], 0xFF, (library_legs-1) * sizeof(Leg));
}

// Strangely enough, including these all in the same source file improves performance
// in Visual Studio by almost 50%, which is odd because MSVC was one of the first
// compilers to support "link time optimization."

#include "mersenne/addsub/MrAdd.cpp"
#include "mersenne/addsub/MrNegate.cpp"
#include "mersenne/addsub/MrSubtract.cpp"
#include "mersenne/expm/MrInvert.cpp"
#include "mersenne/expm/MrSquareRoot.cpp"
#include "mersenne/mul/MrMultiply.cpp"
#include "mersenne/mul/MrMultiplyX.cpp"
#include "mersenne/mul/MrSquare.cpp"
#include "mersenne/reduce/MrReduce.cpp"
#include "mersenne/reduce/MrReduceProduct.cpp"
