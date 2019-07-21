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

Leg CAT_FASTCALL BigRTL::MultiplyXAdd(const Leg *in_a, Leg in_b, const Leg *in_c, Leg *out)
{
    return MultiplyXAdd(library_legs, in_a, in_b, in_c, out);
}

// out = A * B + C
Leg CAT_FASTCALL BigRTL::MultiplyXAdd(int legs, const Leg *in_a, Leg in_b, const Leg *in_c, Leg *output)
{
    // ICC does a better job than my hand-written version by using SIMD instructions,
    // so I use its optimizer instead.
#if !defined(CAT_COMPILER_ICC) && defined(CAT_ASM_INTEL) && \
	 defined(CAT_ISA_X86) && defined(CAT_WORD_32)

    CAT_ASM_BEGIN
        mov esi, [in_a]       ; esi = in_a
        mov edi, [in_c]       ; edi = in_c
        mov ecx, [output]     ; ecx = output

        ; edx:eax = A[0] * B + C
        mov eax, [esi]
        mul [in_b]
        add eax, [edi]
        adc edx, 0

        mov [ecx], eax        ; output[0] = eax
        sub [legs], 1
        jbe loop_done

loop_head:
            lea esi, [esi + 4]
            mov ebx, edx
            mov eax, [esi]
            lea edi, [edi + 4]
            mul [in_b]
            add eax, [edi]
            adc edx, 0
            lea ecx, [ecx + 4]
            add eax, ebx
            adc edx, 0
            mov [ecx], eax

        sub [legs], 1
        ja loop_head

loop_done:
        mov eax, edx
    CAT_ASM_END

#else

    Leg p_hi;

    CAT_LEG_MULADD(in_a[0], in_b, in_c[0], p_hi, output[0]);

    for (int ii = 1; ii < legs; ++ii)
        CAT_LEG_MULADD2(in_a[ii], in_b, in_c[ii], p_hi, p_hi, output[ii]);

    return p_hi;

#endif
}
