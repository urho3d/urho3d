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

/*
 * Modified work: Copyright (c) 2017, SLikeSoft UG (haftungsbeschränkt)
 *
 * This source code was modified by SLikeSoft. Modifications are licensed under the MIT-style
 * license found in the license.txt file in the root directory of this source tree.
 * Alternatively you are permitted to license the modifications under the Modified BSD License.
 */

#ifndef CAT_ATOMIC_HPP
#define CAT_ATOMIC_HPP

#include <cat/Platform.hpp>

#if defined(CAT_OS_WINDOWS)
# include <cat/port/WindowsInclude.hpp>
#endif

namespace cat {


namespace Atomic {


// Compare-and-Swap 2x word size (CAS2)
// On 32-bit architectures, the arguments point to 64-bit values, and must be aligned to 8 byte boundary
// On 64-bit architectures, the arguments point to 128-bit values, and must be aligned to 16 byte boundary
// Returns true if the old value was equal to the expected value
CAT_INLINE bool CAS2(volatile void *x, const void *expected_old_value, const void *new_value);
// Will define CAT_NO_ATOMIC_CAS2 if the platform/compiler does not support atomic CAS2

// Add y to x, returning the previous state of x
CAT_INLINE u32 Add(volatile u32 *x, s32 y);
// Will define CAT_NO_ATOMIC_ADD if the platform/compiler does not support atomic add

// Set x to new value, returning the previous state of x
CAT_INLINE u32 Set(volatile u32 *x, u32 new_value);
// Will define CAT_NO_ATOMIC_SET if the platform/compiler does not support atomic set

// Bit Test and Set (BTS)
// Returns true if the bit was 1 and is still 1, otherwise false
CAT_INLINE bool BTS(volatile u32 *x, int bit);
// Will define CAT_NO_ATOMIC_BTS if the platform/compiler does not support atomic bts

// Bit Test and Reset (BTR)
// Returns true if the bit was 1 and is now 0, otherwise false
CAT_INLINE bool BTR(volatile u32 *x, int bit);
// Will define CAT_NO_ATOMIC_BTR if the platform/compiler does not support atomic btr


} // namespace Atomic


//// Compare-and-Swap

#if defined(CAT_WORD_64)


bool Atomic::CAS2(volatile void *x, const void *expected_old_value, const void *new_value)
{
	CAT_FENCE_COMPILER

#if defined(CAT_COMPILER_MSVC) && (_MSC_VER > 1400) // MSVC 2008+

    __int64 ComparandResult[2] = { ((u64*)expected_old_value)[0],
                                   ((u64*)expected_old_value)[1] };

    // Requires MSVC 2008 or newer
    bool success = 1 == _InterlockedCompareExchange128((s64*)x, ((u64*)new_value)[1],
													   ((u64*)new_value)[0], ComparandResult);

	CAT_FENCE_COMPILER
	return success;

#elif defined(CAT_ASM_ATT) && defined(CAT_ISA_X86)

	u128 *target = (u128*)x;
	u64 *replace = (u64*)new_value;
	u128 *expected = (u128*)expected_old_value;
	bool retval;

    CAT_ASM_BEGIN
		"lock; CMPXCHG16B %0\n\t"
		"sete %%al"
		: "=m" (*target), "=a" (retval)
		: "m" (*target), "b" (replace[0]), "c" (replace[1]), "A" (*expected)
		: "memory", "cc"
    CAT_ASM_END

	CAT_FENCE_COMPILER
    return retval;

#else

#define CAT_NO_ATOMIC_CAS2 /* Platform/compiler does not support CAS2 */

	(void) x; // avoid unused parameter warning
	(void) expected_old_value;
	(void) new_value;

	return true;

#endif
}


#else // 32-bit version:


bool Atomic::CAS2(volatile void *x, const void *expected_old_value, const void *new_value)
{
	CAT_FENCE_COMPILER

#if defined(CAT_COMPILER_MSVC)

	s64 old_value = ((s64*)expected_old_value)[0];

	bool success = (old_value == _InterlockedCompareExchange64((s64*)x, ((s64*)new_value)[0], old_value));

	CAT_FENCE_COMPILER
	return success;

#elif defined(CAT_ASM_INTEL) && defined(CAT_ISA_X86)

    CAT_ASM_BEGIN
		push ebx
        mov eax, new_value
		push esi
        mov ebx, dword ptr[eax]
        mov ecx, dword ptr[eax+4]
        mov edx, expected_old_value
        mov esi, x
        mov eax, dword ptr[edx]
        mov edx, dword ptr[edx+4]
        lock CMPXCHG8B qword ptr[esi]
		pop ebx
        mov eax, 0
		pop esi
        setz al
    CAT_ASM_END

	CAT_FENCE_COMPILER

#elif defined(CAT_ASM_ATT) && defined(CAT_ISA_X86)

	u64 *target = (u64*)x;
	u32 *replace = (u32*)new_value;
	u64 *expected = (u64*)expected_old_value;
	bool retval;

    CAT_ASM_BEGIN
		"lock; CMPXCHG8B %0\n\t"
		"sete %%al"
		: "=m" (*target), "=a" (retval)
		: "m" (*target), "b" (replace[0]), "c" (replace[1]), "A" (*expected)
		: "memory", "cc"
    CAT_ASM_END

	CAT_FENCE_COMPILER
    return retval;

#else

#define CAT_NO_ATOMIC_CAS2 /* Platform/compiler does not support atomic CAS2 */

	(void) x; // avoid unused parameter warning
	(void) expected_old_value;
	(void) new_value;

	return true;

#endif
}


#endif // defined(CAT_WORD_64)


//// Add y to x, returning the previous state of x

u32 Atomic::Add(volatile u32 *x, s32 y)
{
	CAT_FENCE_COMPILER

#if defined(CAT_COMPILER_MSVC) && defined(CAT_WORD_64)

    u32 result = InterlockedAdd((volatile LONG*)x, y) - y;

	CAT_FENCE_COMPILER
	return result;

#elif defined(CAT_ASM_INTEL) && defined(CAT_WORD_32) && defined(CAT_ISA_X86)

    CAT_ASM_BEGIN
        mov edx,x
        mov eax,y
        lock XADD [edx],eax
    CAT_ASM_END

	CAT_FENCE_COMPILER

#elif defined(CAT_ASM_ATT) && defined(CAT_ISA_X86)

	u32 retval;

    CAT_ASM_BEGIN
		"lock; XADDl %%eax, %0\n\t"
		: "=m" (*x), "=a" (retval)
		: "m" (*x), "a" (y)
		: "memory", "cc"
    CAT_ASM_END

	CAT_FENCE_COMPILER
    return retval;

#else

#define CAT_NO_ATOMIC_ADD /* Platform/compiler does not support atomic add */

	u32 old_x = *x;
	*x = old_x + y;

	CAT_FENCE_COMPILER
	return old_x;

#endif
}


//// Set x to new value, returning the previous state of x

u32 Atomic::Set(volatile u32 *x, u32 new_value)
{
	CAT_FENCE_COMPILER

#if defined(CAT_COMPILER_MSVC)

#if (_MSC_VER <= 1400) // MSVC 2005
	u32 result = _InterlockedExchange((long*)x, new_value);
#else // MSVC 2008+
	u32 result = _InterlockedExchange((volatile LONG*)x, new_value);
#endif

	CAT_FENCE_COMPILER
	return result;

#elif defined(CAT_ASM_INTEL) && defined(CAT_WORD_32) && defined(CAT_ISA_X86)

    CAT_ASM_BEGIN
        mov edx,x
        mov eax,new_value
        lock XCHG [edx],eax
    CAT_ASM_END

	CAT_FENCE_COMPILER

#elif defined(CAT_ASM_ATT) && defined(CAT_ISA_X86)

	u32 retval;

    CAT_ASM_BEGIN
		"lock; XCHGl %%eax, %0\n\t"
		: "=m" (*x), "=a" (retval)
		: "m" (*x), "a" (new_value)
		: "memory", "cc"
    CAT_ASM_END

	CAT_FENCE_COMPILER
    return retval;

#else

#define CAT_NO_ATOMIC_SET /* Platform/compiler does not support atomic set */

	u32 old_x = *x;
	*x = new_value;

	CAT_FENCE_COMPILER
	return old_x;

#endif
}


//// Bit Test and Set (BTS)

bool Atomic::BTS(volatile u32 *x, int bit)
{
	CAT_FENCE_COMPILER

#if defined(CAT_COMPILER_MSVC)

#if (_MSC_VER <= 1400) // MSVC 2005
	bool success = !!_interlockedbittestandset((long*)x, bit);
#else // MSVC 2008+
	bool success = !!_interlockedbittestandset((volatile LONG*)x, bit);
#endif

	CAT_FENCE_COMPILER
	return success;

#elif defined(CAT_ASM_INTEL) && defined(CAT_WORD_32) && defined(CAT_ISA_X86)

    CAT_ASM_BEGIN
        mov edx,x
        mov ecx,bit
        lock BTS [edx],ecx
        mov eax,0
        setc al
    CAT_ASM_END

	CAT_FENCE_COMPILER

#elif defined(CAT_ASM_ATT) && defined(CAT_ISA_X86)

	bool retval;

    CAT_ASM_BEGIN
		"lock; BTSl %2, %0\n\t"
		"setc %%al"
		: "=m" (*x), "=a" (retval)
		: "Ir" (bit)
		: "memory", "cc"
    CAT_ASM_END

	CAT_FENCE_COMPILER
    return retval;

#else

#define CAT_NO_ATOMIC_BTS /* Platform/compiler does not support atomic bts */

	u32 mask = 1 << bit;

	u32 old_x = *x;
	*x = old_x | mask;

	CAT_FENCE_COMPILER
	return (old_x & mask) ? true : false;

#endif
}


//// Bit Test and Reset (BTR)

bool Atomic::BTR(volatile u32 *x, int bit)
{
	CAT_FENCE_COMPILER

#if defined(CAT_COMPILER_MSVC)

#if (_MSC_VER <= 1400) // MSVC 2005
	bool success = !!_interlockedbittestandreset((long*)x, bit);
#else // MSVC 2008+
	bool success = !!_interlockedbittestandreset((volatile LONG*)x, bit);
#endif

	CAT_FENCE_COMPILER
	return success;

#elif defined(CAT_ASM_INTEL) && defined(CAT_WORD_32) && defined(CAT_ISA_X86)

    CAT_ASM_BEGIN
        mov edx,x
        mov ecx,bit
        lock BTR [edx],ecx
        mov eax,0
        setc al
    CAT_ASM_END

	CAT_FENCE_COMPILER

#elif defined(CAT_ASM_ATT) && defined(CAT_ISA_X86)

	bool retval;

    CAT_ASM_BEGIN
		"lock; BTRl %2, %0\n\t"
		"setc %%al"
		: "=m" (*x), "=a" (retval)
		: "Ir" (bit)
		: "memory", "cc"
    CAT_ASM_END

	CAT_FENCE_COMPILER
    return retval;

#else

#define CAT_NO_ATOMIC_BTR /* Platform/compiler does not support atomic btr */

	u32 mask = 1 << bit;

	u32 old_x = *x;
	*x = old_x & ~mask;

	CAT_FENCE_COMPILER
	return (old_x & mask) ? true : false;

#endif
}



} // namespace cat

#endif // CAT_ATOMIC_HPP
