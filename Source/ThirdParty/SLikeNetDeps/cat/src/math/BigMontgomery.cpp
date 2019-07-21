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

#include <cat/math/BigMontgomery.hpp>
#include <cstring>
using namespace cat;

BigMontgomery::BigMontgomery(int regs, int bits)
    : BigRTL(regs + MON_OVERHEAD, bits)
{
    mon_regs = regs + MON_OVERHEAD;

    // Reserve a register to contain the full modulus
    CachedModulus = Get(mon_regs - 1);
	TempProduct = Get(mon_regs - 3);
	TempProductHi = TempProduct + library_legs;
}

void BigMontgomery::SetModulus(const Leg *mod)
{
	Copy(mod, CachedModulus);
	mod_inv = MultiplicativeInverseX(-(LegSigned)mod[0]);
}

void BigMontgomery::CopyModulus(Leg *out)
{
	Copy(CachedModulus, out);
}

// Strangely enough, including these all in the same source file improves performance
// in Visual Studio by almost 50%, which is odd because MSVC was one of the first
// compilers to support "link time optimization."

#include "montgomery/reduce/MonInput.cpp"
#include "montgomery/reduce/MonOutput.cpp"
#include "montgomery/reduce/MonReduceProduct.cpp"
#include "montgomery/addsub/MonAdd.cpp"
#include "montgomery/addsub/MonNegate.cpp"
#include "montgomery/addsub/MonSubtract.cpp"
#include "montgomery/mul/MonMultiply.cpp"
#include "montgomery/mul/MonSquare.cpp"
#include "montgomery/expm/MonExpMod.cpp"
#include "montgomery/expm/IsRabinMillerPrime.cpp"
