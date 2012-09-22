/*
  AngelCode Scripting Library
  Copyright (c) 2003-2012 Andreas Jonsson

  This software is provided 'as-is', without any express or implied
  warranty. In no event will the authors be held liable for any
  damages arising from the use of this software.

  Permission is granted to anyone to use this software for any
  purpose, including commercial applications, and to alter it and
  redistribute it freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you
     must not claim that you wrote the original software. If you use
     this software in a product, an acknowledgment in the product
     documentation would be appreciated but is not required.

  2. Altered source versions must be plainly marked as such, and
     must not be misrepresented as being the original software.

  3. This notice may not be removed or altered from any source
     distribution.

  The original version of this library can be located at:
  http://www.angelcode.com/angelscript/

  Andreas Jonsson
  andreas@angelcode.com
*/

// Assembly routines for the ARM call convention
// Written by Fredrik Ehnbom in June 2009

// Adapted to GNUC by darktemplar216 in September 2009

// Modified by Lasse Öörni for 8-byte stack alignment in May 2012

#if defined(__arm__) || defined(__ARM__)

.global armFunc
.global armFuncR0
.global armFuncR0R1
.global armFuncObjLast
.global armFuncR0ObjLast
    
armFunc:
    stmdb   sp!, {r4-r8, lr}
    mov     r6, r0  // arg table
    movs    r7, r1  // arg size (also set the condition code flags so that we detect if there are no arguments)
    mov     r4, r2  // function address
    mov     r8, #0

    beq     nomoreargs

    // Load the first 4 arguments into r0-r3
    cmp     r7, #4
    ldrge   r0, [r6],#4
    cmp     r7, #2*4
    ldrge   r1, [r6],#4
    cmp     r7, #3*4
    ldrge   r2, [r6],#4
    cmp     r7, #4*4
    ldrge   r3, [r6],#4
    ble     nomoreargs

    // Load the rest of the arguments onto the stack
    sub     r7, r7, #4*4      // skip the 4 registers already loaded into r0-r3
    add     r8, r7, #4        // ensure 8-byte stack alignment
    bic     r8, r8, #4
    sub     sp, sp, r8
    mov     r12, sp           // copy size != frame size, so store frame start sp
stackargsloop:
    ldr     r5, [r6], #4
    str     r5, [sp], #4
    subs    r7, r7, #4
    bne     stackargsloop
    mov     sp, r12
nomoreargs:
    blx     r4
    add     sp, sp, r8
    ldmia   sp!, {r4-r8, pc}

armFuncObjLast:
    stmdb   sp!, {r4-r8, lr}
    mov     r6, r0  // arg table
    movs    r7, r1  // arg size (also set the condition code flags so that we detect if there are no arguments)
    mov     r4, r2  // function address
    mov     r8, #0

    mov     r0, r3          // objlast. might get overwritten
    mov     r5, r3          // objlast to temp reg

    beq     nomoreargsarmFuncObjLast

    // Load the first 4 arguments into r0-r3
    cmp     r7, #4
    ldrge   r0, [r6],#4
    cmp     r7, #2*4
    ldrge   r1, [r6],#4
    movlt   r1, r5
    cmp     r7, #3*4
    ldrge   r2, [r6],#4
    movlt   r2, r5
    cmp     r7, #4*4
    ldrge   r3, [r6],#4
    movlt   r3, r5
    blt     nomoreargsarmFuncObjLast

    // Load the rest of the arguments onto the stack
    sub     r7, r7, #4*4    // skip the 4 registers already loaded into r0-r3
    add     r8, r7, #8      // account for the objlast pointer, ensure 8-byte stack alignment
    bic     r8, r8, #4
    str     r5, [sp,#-4]    // store the objlast on stack, twice in case we adjusted alignment
    str     r5, [sp,#-8]
    sub     sp, sp, r8      // adjust frame
    cmp     r7, #0          // we may also have come here with no extra params
    beq     nomoreargsarmFuncObjLast
    mov     r12, sp         // copy size != frame size, so store frame start sp
stackargslooparmFuncObjLast:
    ldr     r5, [r6], #4
    str     r5, [sp], #4
    subs    r7, r7, #4
    bne     stackargslooparmFuncObjLast
    mov     sp, r12
nomoreargsarmFuncObjLast:
    blx     r4
    add     sp, sp, r8
    ldmia   sp!, {r4-r8, pc}

armFuncR0ObjLast:
    stmdb   sp!, {r4-r8, lr}
    ldr     r5, [sp,#6*4]   // objlast to temp reg

    mov     r6, r0  // arg table
    movs    r7, r1  // arg size (also set the condition code flags so that we detect if there are no arguments)
    mov     r4, r2  // function address
    mov     r8, #0

    mov     r0, r3      // r0 explicitly set
    mov     r1, r5      // objlast.  might get overwritten

    beq     nomoreargsarmFuncR0ObjLast

    // Load the first 3 arguments into r1-r3
    cmp     r7, #1*4
    ldrge   r1, [r6],#4
    cmp     r7, #2*4
    ldrge   r2, [r6],#4
    movlt   r2, r5
    cmp     r7, #3*4
    ldrge   r3, [r6],#4
    movlt   r3, r5
    blt     nomoreargsarmFuncR0ObjLast

    // Load the rest of the arguments onto the stack
    sub     r7, r7, #3*4    // skip the 3 registers already loaded into r1-r3
    add     r8, r7, #8      // account for the objlast pointer, ensure 8-byte stack alignment
    bic     r8, r8, #4
    str     r5, [sp,#-4]    // store the objlast on stack, twice in case we adjusted alignment
    str     r5, [sp,#-8]
    sub     sp, sp, r8      // adjust frame
    cmp     r7, #0          // we may also have come here with no extra params
    beq     nomoreargsarmFuncR0ObjLast
    mov     r12, sp         // copy size != frame size, so store frame start sp
stackargslooparmFuncR0ObjLast:
    ldr     r5, [r6], #4
    str     r5, [sp], #4
    subs    r7, r7, #4
    bne     stackargslooparmFuncR0ObjLast
    mov     sp, r12
nomoreargsarmFuncR0ObjLast:
    blx     r4
    add     sp, sp, r8
    ldmia   sp!, {r4-r8, pc}


armFuncR0:
    stmdb   sp!, {r4-r8, lr}
    mov     r6, r0  // arg table
    movs    r7, r1  // arg size (also set the condition code flags so that we detect if there are no arguments)
    mov     r4, r2  // function address
    mov     r8, #0

    mov     r0, r3  // r0 explicitly set

    beq     nomoreargsarmFuncR0

    // Load the first 3 arguments into r1-r3
    cmp     r7, #1*4
    ldrge   r1, [r6],#4
    cmp     r7, #2*4
    ldrge   r2, [r6],#4
    cmp     r7, #3*4
    ldrge   r3, [r6],#4
    ble     nomoreargsarmFuncR0

    // Load the rest of the arguments onto the stack
    sub     r7, r7, #3*4    // skip the 3 registers already loaded into r1-r3
    add     r8, r7, #4      // ensure 8-byte stack alignment
    bic     r8, r8, #4
    sub     sp, sp, r8
    mov     r12, sp         // copy size != frame size, so store frame start sp
stackargslooparmFuncR0:
    ldr     r5, [r6], #4
    str     r5, [sp], #4
    subs    r7, r7, #4
    bne     stackargslooparmFuncR0
    mov     sp, r12
nomoreargsarmFuncR0:
    blx     r4
    add     sp, sp, r8
    ldmia   sp!, {r4-r8, pc}


armFuncR0R1:
    stmdb   sp!, {r4-r8, lr}
    mov     r6, r0  // arg table
    movs    r7, r1  // arg size (also set the condition code flags so that we detect if there are no arguments)
    mov     r4, r2  // function address
    mov     r8, #0

    mov     r0, r3          // r0 explicitly set
    ldr     r1, [sp, #6*4]  // r1 explicitly set too

    beq     nomoreargsarmFuncR0R1

    // Load the first 2 arguments into r2-r3
    cmp     r7, #1*4
    ldrge   r2, [r6],#4
    cmp     r7, #2*4
    ldrge   r3, [r6],#4
    ble     nomoreargsarmFuncR0R1

    // Load the rest of the arguments onto the stack
    sub     r7, r7, #2*4    // skip the 2 registers already loaded into r2-r3
    add     r8, r7, #4      // ensure 8-byte stack alignment
    bic     r8, r8, #4
    sub     sp, sp, r8
    mov     r12, sp         // copy size != frame size, so store frame start sp
stackargslooparmFuncR0R1:
    ldr     r5, [r6], #4
    str     r5, [sp], #4
    subs    r7, r7, #4
    bne     stackargslooparmFuncR0R1
    mov     sp, r12
nomoreargsarmFuncR0R1:
    blx     r4
    add     sp, sp, r8
    ldmia   sp!, {r4-r8, pc}

#endif
