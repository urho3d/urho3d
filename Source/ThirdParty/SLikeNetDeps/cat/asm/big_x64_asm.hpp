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

// Forward declaration for assembly routines in big_x64_*.asm

#ifndef CAT_BIG_X64_ASM_HPP
#define CAT_BIG_X64_ASM_HPP

#include <cat/math/Legs.hpp>

#if defined(CAT_WORD_64)

namespace cat {


extern "C" void bpm_add_4(Leg modulus_c, const Leg *in_a, const Leg *in_b, Leg *out);
extern "C" void bpm_sub_4(Leg modulus_c, const Leg *in_a, const Leg *in_b, Leg *out);
extern "C" void bpm_mul_4(Leg modulus_c, const Leg *in_a, const Leg *in_b, Leg *out);
extern "C" void bpm_mulx_4(Leg modulus_c, const Leg *in_a, Leg in_b, Leg *out);
extern "C" void bpm_sqr_4(Leg modulus_c, const Leg *in, Leg *out);

extern "C" Leg divide64_x(Leg legs, const Leg *in_a, const Leg in_b, Leg *out_q);
extern "C" Leg modulus64_x(Leg legs, const Leg *in_a, const Leg in_b);
extern "C" void divide64_core(Leg A_used, Leg A_overflow, const Leg *A, Leg B_used, const Leg *B, Leg *Q);


} // namespace cat

#endif // CAT_WORD_64

#endif // CAT_BIG_X64_ASM_HPP
