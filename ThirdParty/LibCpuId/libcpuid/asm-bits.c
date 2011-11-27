/*
 * Copyright 2008  Veselin Georgiev,
 * anrieffNOSPAM @ mgail_DOT.com (convert to gmail)
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "libcpuid.h"
#include "asm-bits.h"

int cpuid_exists_by_eflags(void)
{
#ifdef PLATFORM_X64
	return 1; /* CPUID is always present on the x86_64 */
#else
#  ifdef COMPILER_GCC
	int result;
	__asm __volatile(
		"	pushfl\n"
		"	pop	%%eax\n"
		"	mov	%%eax,	%%ecx\n"
		"	xor	$0x200000,	%%eax\n"
		"	push	%%eax\n"
		"	popfl\n"
		"	pushfl\n"
		"	pop	%%eax\n"
		"	xor	%%ecx,	%%eax\n"
		"	mov	%%eax,	%0\n"
		"	push	%%ecx\n"
		"	popfl\n"
		: "=m"(result)
		: :"eax", "ecx", "memory");
	return (result != 0);
#  else
#    ifdef COMPILER_MICROSOFT
	int result;
	__asm {
		pushfd
		pop	eax
		mov	ecx,	eax
		xor	eax,	0x200000
		push	eax
		popfd
		pushfd
		pop	eax
		xor	eax,	ecx
		mov	result,	eax
		push	ecx
		popfd
	};
	return (result != 0);
#    else
#      error "Unsupported compiler"
#    endif /* COMPILER_MICROSOFT */
#  endif /* COMPILER_GCC */
#endif /* PLATFORM_X64 */
}

/* 
 * with MSVC/AMD64, the exec_cpuid() and cpu_rdtsc() functions
 * are implemented in separate .asm files. Otherwise, use inline assembly
 */
#ifdef INLINE_ASM_SUPPORTED
void exec_cpuid(uint32_t *regs)
{
#ifdef COMPILER_GCC
#	ifdef PLATFORM_X64
	__asm __volatile(
		"	push	%%rbx\n"
		"	push	%%rcx\n"
		"	push	%%rdx\n"
		"	push	%%rdi\n"
		
		"	mov	%0,	%%rdi\n"
		
		"	mov	(%%rdi),	%%eax\n"
		"	mov	4(%%rdi),	%%ebx\n"
		"	mov	8(%%rdi),	%%ecx\n"
		"	mov	12(%%rdi),	%%edx\n"
		
		"	cpuid\n"
		
		"	movl	%%eax,	(%%rdi)\n"
		"	movl	%%ebx,	4(%%rdi)\n"
		"	movl	%%ecx,	8(%%rdi)\n"
		"	movl	%%edx,	12(%%rdi)\n"
		"	pop	%%rdi\n"
		"	pop	%%rdx\n"
		"	pop	%%rcx\n"
		"	pop	%%rbx\n"
		:
		:"rdi"(regs)
		:"memory", "eax"
	);
#	else
	__asm __volatile(
		"	push	%%ebx\n"
		"	push	%%ecx\n"
		"	push	%%edx\n"
		"	push	%%edi\n"
		"	mov	%0,	%%edi\n"
		
		"	mov	(%%edi),	%%eax\n"
		"	mov	4(%%edi),	%%ebx\n"
		"	mov	8(%%edi),	%%ecx\n"
		"	mov	12(%%edi),	%%edx\n"
		
		"	cpuid\n"
		
		"	mov	%%eax,	(%%edi)\n"
		"	mov	%%ebx,	4(%%edi)\n"
		"	mov	%%ecx,	8(%%edi)\n"
		"	mov	%%edx,	12(%%edi)\n"
		"	pop	%%edi\n"
		"	pop	%%edx\n"
		"	pop	%%ecx\n"
		"	pop	%%ebx\n"
		:
		:"m"(regs)
		:"memory", "eax"
	);
#	endif /* COMPILER_GCC */
#else
#  ifdef COMPILER_MICROSOFT
	__asm {
		push	ebx
		push	ecx
		push	edx
		push	edi
		mov	edi,	regs
		
		mov	eax,	[edi]
		mov	ebx,	[edi+4]
		mov	ecx,	[edi+8]
		mov	edx,	[edi+12]
		
		cpuid
		
		mov	[edi],		eax
		mov	[edi+4],	ebx
		mov	[edi+8],	ecx
		mov	[edi+12],	edx
		
		pop	edi
		pop	edx
		pop	ecx
		pop	ebx
	}
#  else
#    error "Unsupported compiler"
#  endif /* COMPILER_MICROSOFT */
#endif
}
#endif /* INLINE_ASSEMBLY_SUPPORTED */

#ifdef INLINE_ASM_SUPPORTED
void cpu_rdtsc(uint64_t* result)
{
	uint32_t low_part, hi_part;
#ifdef COMPILER_GCC
	__asm __volatile (
		"	rdtsc\n"
		"	mov	%%eax,	%0\n"
		"	mov	%%edx,	%1\n"
		:"=m"(low_part), "=m"(hi_part)::"memory", "eax", "edx"
	);
#else
#  ifdef COMPILER_MICROSOFT
	__asm {
		rdtsc
		mov	low_part,	eax
		mov	hi_part,	edx
	};
#  else
#    error "Unsupported compiler"
#  endif /* COMPILER_MICROSOFT */
#endif /* COMPILER_GCC */
	*result = (uint64_t)low_part + (((uint64_t) hi_part) << 32);
}
#endif /* INLINE_ASM_SUPPORTED */
