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

#ifndef CAT_LEGS_HPP
#define CAT_LEGS_HPP

#include <cat/Platform.hpp>

namespace cat {


#if defined(CAT_WORD_64)

#define CAT_LEG_BITS 64
#define CAT_USED_BITS(x) BSR64(x) /* does not work if x = 0 */
#define CAT_TRAILING_ZEROES(x) BSF64(x) /* does not work if x = 0 */
    typedef u64 Leg;
    typedef s64 LegSigned;
#if !defined(CAT_COMPILER_MSVC)
    typedef u128 LegPair;
    typedef s128 LegPairSigned;
# define CAT_LEG_PAIRMUL(A, B) ((LegPair)A * B)
#else
# define CAT_NO_LEGPAIR
#endif

// If x86-64 and MSVC
#if defined(CAT_ISA_X86) && defined(CAT_COMPILER_MSVC)
#define CAT_USE_LEGS_ASM64 /* use 64-bit assembly code inner loops */
#endif

#elif defined(CAT_WORD_32)

#define CAT_LEG_BITS 32
#define CAT_USED_BITS(x) BSR32(x) /* does not work if x = 0 */
#define CAT_TRAILING_ZEROES(x) BSF32(x) /* does not work if x = 0 */
    typedef u32 Leg;
    typedef s32 LegSigned;
    typedef u64 LegPair;
    typedef s64 LegPairSigned;

#if defined(CAT_COMPILER_MSVC)
# define CAT_LEG_PAIRMUL(A, B) __emulu(A, B) /* slightly faster in ICC */
#else
# define CAT_LEG_PAIRMUL(A, B) ((LegPair)A * B)
#endif

#endif // CAT_WORD_32

// Largest value that can be taken on by a Leg
const Leg CAT_LEG_LARGEST = ~(Leg)0;

// MSB of a leg
const Leg CAT_LEG_MSB = (Leg)1 << (CAT_LEG_BITS - 1);


#if defined(CAT_NO_LEGPAIR)

////
// Platforms that do not have LegPair (assumes 64-bit MSVC)
////


// p(hi:lo) = A * B
#define CAT_LEG_MUL(A, B, p_hi, p_lo)    \
{                                        \
    p_lo = _umul128(A, B, &p_hi);        \
}

// p(hi:lo) = A * B + C
#define CAT_LEG_MULADD(A, B, C, p_hi, p_lo) \
{                                           \
    u64 _C0 = C;                            \
    p_lo = _umul128(A, B, &p_hi);           \
    p_hi += ((p_lo += _C0) < _C0);          \
}

// p(hi:lo) = A * B + C + D
#define CAT_LEG_MULADD2(A, B, C, D, p_hi, p_lo) \
{                                               \
    u64 _C0 = C, _D0 = D;                       \
    p_lo = _umul128(A, B, &p_hi);               \
    p_hi += ((p_lo += _C0) < _C0);              \
    p_hi += ((p_lo += _D0) < _D0);              \
}

// p(C2:C1:C0) = A * B + (C1:C0)
#define CAT_LEG_COMBA2(A, B, C0, C1, C2)     \
{                                            \
    u64 _p_hi, _p_lo;                        \
    _p_lo = _umul128(A, B, &_p_hi);          \
    _p_hi += ((C0 += _p_lo) < _p_lo);        \
    C2 = ((C1 += _p_hi) < _p_hi);            \
}

// p(C2:C1:C0) = A * B + (C2:C1:C0)
#define CAT_LEG_COMBA3(A, B, C0, C1, C2)     \
{                                            \
    u64 _p_hi, _p_lo;                        \
    _p_lo = _umul128(A, B, &_p_hi);          \
    _p_hi += ((C0 += _p_lo) < _p_lo);        \
    C2 += ((C1 += _p_hi) < _p_hi);           \
}


#else // has LegPair

////
// Platforms that have LegPair (assumes 32-bit MSVC or any-bit GCC)
////


// p(hi:lo) = A * B
#define CAT_LEG_MUL(A, B, p_hi, p_lo)      \
{                                          \
    LegPair _mt = CAT_LEG_PAIRMUL(A, B);   \
    (p_lo) = (Leg)_mt;                     \
    (p_hi) = (Leg)(_mt >> CAT_LEG_BITS);   \
}

// p(hi:lo) = A * B + C
#define CAT_LEG_MULADD(A, B, C, p_hi, p_lo)           \
{                                                     \
    LegPair _mt = CAT_LEG_PAIRMUL(A, B) + (Leg)(C);   \
    (p_lo) = (Leg)_mt;                                \
    (p_hi) = (Leg)(_mt >> CAT_LEG_BITS);              \
}

// p(hi:lo) = A * B + C + D
#define CAT_LEG_MULADD2(A, B, C, D, p_hi, p_lo)                  \
{                                                                \
    LegPair _mt = CAT_LEG_PAIRMUL(A, B) + (Leg)(C) + (Leg)(D);   \
    (p_lo) = (Leg)_mt;                                           \
    (p_hi) = (Leg)(_mt >> CAT_LEG_BITS);                         \
}

// p(C2:C1:C0) = A * B + (C1:C0)
#define CAT_LEG_COMBA2(A, B, C0, C1, C2)        \
{                                               \
	LegPair _cp = CAT_LEG_PAIRMUL(A, B) + (C0); \
	(C0) = (Leg)_cp;                            \
	_cp = (_cp >> CAT_LEG_BITS) + (C1);         \
	(C1) = (Leg)_cp;                            \
	(C2) = (Leg)(_cp >> CAT_LEG_BITS);          \
}

// p(C2:C1:C0) = A * B + (C2:C1:C0)
#define CAT_LEG_COMBA3(A, B, C0, C1, C2)        \
{                                               \
	LegPair _cp = CAT_LEG_PAIRMUL(A, B) + (C0); \
	(C0) = (Leg)_cp;                            \
	_cp = (_cp >> CAT_LEG_BITS) + (C1);         \
	(C1) = (Leg)_cp;                            \
	(C2) += (Leg)(_cp >> CAT_LEG_BITS);         \
}

// Q(hi:lo) = A(hi:lo) / B
#define CAT_LEG_DIV(A_hi, A_lo, B, Q_hi, Q_lo)                    \
{                                                                 \
    LegPair _Ax = ((LegPair)(A_hi) << CAT_LEG_BITS) | (Leg)(A_lo); \
    LegPair _qt = (LegPair)(_Ax / (B));                            \
    (Q_hi) = (Leg)(_qt >> CAT_LEG_BITS);                          \
    (Q_lo) = (Leg)_qt;                                            \
}

#endif // CAT_NO_LEGPAIR


} // namespace cat

#endif // CAT_LEGS_HPP
