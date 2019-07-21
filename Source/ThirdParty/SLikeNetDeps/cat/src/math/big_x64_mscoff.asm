;	Copyright (c) 2009-2010 Christopher A. Taylor.  All rights reserved.
;
;	Redistribution and use in source and binary forms, with or without
;	modification, are permitted provided that the following conditions are met:
;
;	* Redistributions of source code must retain the above copyright notice,
;	  this list of conditions and the following disclaimer.
;	* Redistributions in binary form must reproduce the above copyright notice,
;	  this list of conditions and the following disclaimer in the documentation
;	  and/or other materials provided with the distribution.
;	* Neither the name of LibCat nor the names of its contributors may be used
;	  to endorse or promote products derived from this software without
;	  specific prior written permission.
;
;	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
;	AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
;	IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
;	ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
;	LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
;	CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
;	SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
;	INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
;	CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
;	ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
;	POSSIBILITY OF SUCH DAMAGE.

; arith_x64.asm
;
; 64-bit Arithmetic with Big Pseudo-Mersenne (BPM) modulus 2^N-C, for small C
;
; Assembly code written for FASM (flatassembler.net)

format MS64 COFF

section '.code' code readable executable 


;-----------------------------------------------------------------------------
;                           Function Declarations
;-----------------------------------------------------------------------------
public bpm_add_4   as 'bpm_add_4'
public bpm_sub_4   as 'bpm_sub_4'
public bpm_mul_4   as 'bpm_mul_4'
public bpm_mulx_4  as 'bpm_mulx_4'
public bpm_sqr_4   as 'bpm_sqr_4'
public divide_x    as 'divide64_x'
public modulus_x   as 'modulus64_x'
public divide_core as 'divide64_core'


;-----------------------------------------------------------------------------
;                                bpm_add_4
;-----------------------------------------------------------------------------
; Arguments:
;   rcx      (arg 1) : modulus parameter C
;   rdx      (arg 2) : pointer to input A first leg
;   r8       (arg 3) : pointer to input B first leg
;   r9       (arg 4) : pointer to output first leg
; Preconditions:
;   legs per bigint = 4
; Output:
;   out = A + B (mod C)
;-----------------------------------------------------------------------------
bpm_add_4:

    ; perform addition chain
    mov r10, qword[rdx]
    add r10, qword[r8]
    mov qword[r9], r10
    mov r11, qword[rdx+8]
    adc r11, qword[r8+8]
    mov qword[r9+8], r11
    mov rax, qword[rdx+16]
    adc rax, qword[r8+16]
    mov qword[r9+16], rax
    mov rdx, qword[rdx+24]
    adc rdx, qword[r8+24]
    jnc bpm_add_4_done

    ; add C when it overflows
bpm_add_4_mod:
    add r10, rcx
    adc r11, 0
    adc rax, 0
    adc rdx, 0
    jc bpm_add_4_mod

bpm_add_4_done:
    mov qword[r9], r10
    mov qword[r9+8], r11
    mov qword[r9+16], rax
    mov qword[r9+24], rdx

    ret


;-----------------------------------------------------------------------------
;                                bpm_sub_4
;-----------------------------------------------------------------------------
; Arguments:
;   rcx      (arg 1) : modulus parameter C
;   rdx      (arg 2) : pointer to input A first leg
;   r8       (arg 3) : pointer to input B first leg
;   r9       (arg 4) : pointer to output first leg
; Preconditions:
;   legs per bigint = 4
; Output:
;   out = A - B (mod C)
;-----------------------------------------------------------------------------
bpm_sub_4:

    ; perform subtraction chain
    mov r10, qword[rdx]
    sub r10, qword[r8]
    mov qword[r9], r10
    mov r11, qword[rdx+8]
    sbb r11, qword[r8+8]
    mov qword[r9+8], r11
    mov rax, qword[rdx+16]
    sbb rax, qword[r8+16]
    mov qword[r9+16], rax
    mov rdx, qword[rdx+24]
    sbb rdx, qword[r8+24]
    jnc bpm_sub_4_done

    ; subtract C when it overflows
bpm_sub_4_mod:
    sub r10, rcx
    sbb r11, 0
    sbb rax, 0
    sbb rdx, 0
    jc bpm_sub_4_mod

bpm_sub_4_done:
    mov qword[r9], r10
    mov qword[r9+8], r11
    mov qword[r9+16], rax
    mov qword[r9+24], rdx

    ret


;-----------------------------------------------------------------------------
;                                bpm_mul_4
;-----------------------------------------------------------------------------
; Arguments:
;   rcx      (arg 1) : modulus parameter C
;   rdx      (arg 2) : pointer to input A first leg
;   r8       (arg 3) : pointer to input B first leg
;   r9       (arg 4) : pointer to output first leg
; Preconditions:
;   legs per bigint = 4
; Output:
;   out = A * B (mod C)
;-----------------------------------------------------------------------------
bpm_mul_4:

    ;               a  b  c  d : A
    ; x             e  f  g  h : B
    ; ------------------------
    ;              ah bh ch dh
    ;           ag bg cg dg
    ;        af bf cf df
    ; +   ae be ce de
    ; ------------------------

    push rbp
    mov rbp, rsp
    sub    rsp, 8*10
    push r12 r13 r14 r15 rbx rsi

label .pro1 qword at rbp-8
label .pro2 qword at rbp-16
label .pro3 qword at rbp-24
label .pro4 qword at rbp-32
label .pro5 qword at rbp-40
label .pro6 qword at rbp-48
label .pro7 qword at rbp-56
label .pro8 qword at rbp-64
label .modc qword at rbp-72
label .out qword at rbp-80

    mov qword[.modc], rcx
    mov qword[.out], r9

    ; ---- 4x4 comba multiply

    mov r9, [rdx+8]
    mov r10, [rdx+16]
    mov r11, [rdx+24]
    mov r12, [r8]
    mov r13, [r8+8]
    mov r14, [r8+16]
    mov r15, [r8+24]
    mov r8, [rdx]

    ; column 1
    mov rax, r8
    xor rcx, rcx
    mul r12 ; dh

    mov qword[.pro1], rax
        mov rbx, rdx

    ; column 2
    mov rax, r9
    xor rsi, rsi
    mul r12 ; ch
        add rbx, rax
        adc rcx, rdx
        adc rsi, 0

    mov rax, r8
    mul r13 ; dg
        add rbx, rax
        adc rcx, rdx
        adc rsi, 0

    mov qword[.pro2], rbx

    ; column 3
    mov rax, r10
    xor rbx, rbx
    mul r12 ; bh
        add rcx, rax
        adc rsi, rdx
        adc rbx, 0

    mov rax, r9
    mul r13 ; cg
        add rcx, rax
        adc rsi, rdx
        adc rbx, 0

    mov rax, r8
    mul r14 ; df
        add rcx, rax
        adc rsi, rdx
        adc rbx, 0

    mov qword[.pro3], rcx

    ; column 4
    mov rax, r11
    xor rcx, rcx
    mul r12 ; ah
        add rsi, rax
        adc rbx, rdx
        adc rcx, 0

    mov rax, r10
    mul r13 ; bg
        add rsi, rax
        adc rbx, rdx
        adc rcx, 0

    mov rax, r9
    mul r14 ; cf
        add rsi, rax
        adc rbx, rdx
        adc rcx, 0

    mov rax, r8
    mul r15 ; de
        add rsi, rax
        adc rbx, rdx
        adc rcx, 0

    mov rax, r11
    mov qword[.pro4], rsi

    ; column 5
    xor rsi, rsi
    mul r13 ; ag
        add rbx, rax
        adc rcx, rdx
        adc rsi, 0

    mov rax, r10
    mul r14 ; bf
        add rbx, rax
        adc rcx, rdx
        adc rsi, 0

    mov rax, r9
    mul r15 ; ce
        add rbx, rax
        adc rcx, rdx
        adc rsi, 0

    ; mov qword[.pro5], rbx
    mov r8, rbx

    ; column 6
    mov rax, r11
    xor rbx, rbx
    mul r14 ; af
        add rcx, rax
        adc rsi, rdx
        adc rbx, 0

    mov rax, r10
    mul r15 ; be
        add rcx, rax
        adc rsi, rdx
        adc rbx, 0

    ; mov qword[.pro6], rcx
    mov r12, rcx ; r12 gets .pro6 from rcx

    ; column 7
    mov rax, r11
    mul r15 ; ae
        add rsi, rax
        adc rbx, rdx

    ; mov qword[.pro7], rsi

    ; column 8
    ; mov qword[.pro8], rbx

    ; ---- modular reduction 8->5

    mov rcx, qword[.modc]

    ; generate r12..8 = .pro8..5 * c + .pro4..1
    mov rax, r8
    mul rcx
        mov r8, rax
        mov r9, rdx
        add r8, qword[.pro1]
        adc r9, 0

    mov rax, r12
    mul rcx
        xor r10, r10
        add r9, rax
        adc r10, rdx
        add r9, qword[.pro2]
        adc r10, 0

    mov rax, rsi
    mul rcx
        xor r11, r11
        add r10, rax
        adc r11, rdx
        add r10, qword[.pro3]
        adc r11, 0

    mov rax, rbx
    mul rcx
        xor r12, r12
        add r11, rax
        adc r12, rdx
        add r11, qword[.pro4]
        adc r12, 0

    ; ---- modular reduction 5->4

    ; generate r11..8 = r12 * c + r11..8
    mov rax, r12
    mul rcx
        add r8, rax
        adc r9, rdx
        adc r10, 0
        adc r11, 0

    mov rsi, qword[.out]

    ; ---- modular reduction 4.1->4

    jnc bpm_mul_4_out

    ; final add carried out so add once more
bpm_mul_4_mod:
    add r8, rcx
    adc r9, 0
    adc r10, 0
    adc r11, 0
    jc bpm_mul_4_mod

bpm_mul_4_out:
    mov qword[rsi], r8
    mov qword[rsi+8], r9
    mov qword[rsi+16], r10
    mov qword[rsi+24], r11

    pop rsi rbx r15 r14 r13 r12
    mov rsp, rbp
    pop rbp

    ret


;-----------------------------------------------------------------------------
;                                bpm_mulx_4
;-----------------------------------------------------------------------------
; Arguments:
;   rcx      (arg 1) : modulus parameter C
;   rdx      (arg 2) : pointer to input A first leg
;   r8       (arg 3) : single leg input B
;   r9       (arg 4) : pointer to output first leg
; Preconditions:
;   legs per bigint = 4
; Output:
;   out = A * B (mod C)
;-----------------------------------------------------------------------------
bpm_mulx_4:

    push rsi r12 r13

    mov rsi, rdx

    mov rax, qword[rdx]
    mul r8
        mov r10, rax
        mov r11, rdx

    mov rax, qword[rsi+8]
    mul r8
        xor r12, r12
        add r11, rax
        adc r12, rdx

    mov rax, qword[rsi+16]
    mul r8
        xor r13, r13
        add r12, rax
        adc r13, rdx

    mov rax, qword[rsi+24]
    mul r8
        add r13, rax
        adc rdx, 0

    ; ---- modular reduction 5->4

    mov rax, rdx
    mul rcx
        add r10, rax
        adc r11, rdx
        adc r12, 0
        adc r13, 0

    ; ---- modular reduction 4.1->4

    jnc bpm_mulx_4_out

    ; final add carried out so add once more
bpm_mulx_4_mod:
    add r10, rcx
    adc r11, 0
    adc r12, 0
    adc r13, 0
    jc bpm_mulx_4_mod

bpm_mulx_4_out:
    mov qword[r9], r10
    mov qword[r9+8], r11
    mov qword[r9+16], r12
    mov qword[r9+24], r13

    pop r13 r12 rsi

    ret


;-----------------------------------------------------------------------------
;                                bpm_sqr_4
;-----------------------------------------------------------------------------
; Arguments:
;   rcx      (arg 1) : modulus parameter C
;   rdx      (arg 2) : pointer to input first leg
;   r8       (arg 3) : pointer to output first leg
; Preconditions:
;   legs per bigint = 4
; Output:
;   out = in*in (mod C)
;-----------------------------------------------------------------------------
bpm_sqr_4:

    ;               a  b  c  d
    ; x             a  b  c  d
    ; ------------------------
    ;              ad bd cd dd
    ;           ac bc cc dc
    ;        ab bb cb db
    ; +   aa ba ca da
    ; ------------------------
    ;                2bd    dd
    ;             2ad   2cd
    ;          2ac    cc
    ;       2ab   2bc
    ;           bb
    ; +   aa
    ; ------------------------

    push rbp
    mov rbp, rsp
    sub    rsp, 8*10
    push r12 r13 r14

label .pro1 qword at rbp-8
label .pro2 qword at rbp-16
label .pro3 qword at rbp-24
label .pro4 qword at rbp-32
label .pro5 qword at rbp-40
label .pro6 qword at rbp-48
label .pro7 qword at rbp-56
label .pro8 qword at rbp-64
label .modc qword at rbp-72
label .out qword at rbp-80

    mov qword[.modc], rcx
    mov qword[.out], r8

    ; ---- 4x4 comba square

    mov r8, qword[rdx]
    mov r9, qword[rdx+8]
    mov r10, qword[rdx+16]
    mov r11, qword[rdx+24]

    ; column 1
    mov rax, r8
    mul r8 ; dd
        mov qword[.pro1], rax
        mov r12, rdx
        xor r13, r13
        xor r14, r14

    ; column 2
    mov rax, r8
    mul r9 ; cd
        ; r14:r13:r12 = 2(rdx:rax) + r12
        add r12, rax
        adc r13, rdx
        adc r14, 0
        add r12, rax
        adc r13, rdx
        adc r14, 0
        mov qword[.pro2], r12

    ; column 3
    mov rax, r8
    xor r12, r12
    mul r10 ; bd
        ; r12:r14:r13 = 2(rdx:rax) + 0:r14:r13
        add r13, rax
        adc r14, rdx
        adc r12, 0
        add r13, rax
        adc r14, rdx
        adc r12, 0

    mov rax, r9
    mul r9 ; cc
        ; r12:r14:r13 += 0:rdx:rax
        add r13, rax
        adc r14, rdx
        adc r12, 0
        mov qword[.pro3], r13

    ; column 4
    mov rax, r8
    xor r13, r13
    mul r11 ; ad
        ; r13:r12:r14 = 2(rdx:rax) + 0:r12:r14
        add r14, rax
        adc r12, rdx
        adc r13, 0
        add r14, rax
        adc r12, rdx
        adc r13, 0

    mov rax, r9
    mul r10 ; bc
        ; r13:r12:r14 += 2(rdx:rax)
        add r14, rax
        adc r12, rdx
        adc r13, 0
        add r14, rax
        adc r12, rdx
        adc r13, 0
        mov qword[.pro4], r14

    ; column 5
    mov rax, r9
    xor r14, r14
    mul r11 ; ac
        ; r14:r13:r12 = 2(rdx:rax) + 0:r13:r12
        add r12, rax
        adc r13, rdx
        adc r14, 0
        add r12, rax
        adc r13, rdx
        adc r14, 0

    mov rax, r10
    mul r10 ; bb
        ; r14:r13:r12 += 0:rdx:rax
        add r12, rax
        adc r13, rdx
        adc r14, 0
        ; mov qword[.pro5], r12
        mov r8, r12

    ; column 6
    mov rax, r10
    xor r12, r12
    mul r11 ; ab
        ; r12:r14:r13 = 2(rdx:rax) + 0:r14:r13
        add r13, rax
        adc r14, rdx
        adc r12, 0
        add r13, rax
        adc r14, rdx
        adc r12, 0
        ; mov qword[.pro6], r13

    ; column 7
    mov rax, r11
    mul r11 ; aa
        ; r13:r12:r14 = rdx:rax + 0:r12:r14
        add r14, rax
        adc r12, rdx
        ; mov qword[.pro7], r14

    ; column 8
    ; mov qword[.pro8], r12

    ; ---- modular reduction 8->5

    mov rcx, qword[.modc]

    ; generate r12..8 = .pro8..5 * c + .pro4..1
    mov rax, r8
    mul rcx
        mov r8, rax
        mov r9, rdx
        add r8, qword[.pro1]
        adc r9, 0

    mov rax, r13
    mul rcx
        xor r10, r10
        add r9, rax
        adc r10, rdx
        add r9, qword[.pro2]
        adc r10, 0

    mov rax, r14
    mul rcx
        xor r11, r11
        add r10, rax
        adc r11, rdx
        add r10, qword[.pro3]
        adc r11, 0

    mov rax, r12
    mul rcx
        xor r12, r12
        add r11, rax
        adc r12, rdx
        add r11, qword[.pro4]
        adc r12, 0

    ; ---- modular reduction 5->4

    ; generate r11..8 = r12 * c + r11..8
    mov rax, r12
    mul rcx
        add r8, rax
        adc r9, rdx
        adc r10, 0
        adc r11, 0

    mov r13, qword[.out]

    ; ---- modular reduction 4.1->4

    jnc bpm_sqr_4_out

    ; final add carried out so add once more
bpm_sqr_4_mod:
    add r8, rcx
    adc r9, 0
    adc r10, 0
    adc r11, 0
	jc bpm_sqr_4_mod

bpm_sqr_4_out:
    mov qword[r13], r8
    mov qword[r13+8], r9
    mov qword[r13+16], r10
    mov qword[r13+24], r11

    pop r14 r13 r12
    mov rsp, rbp
    pop rbp

    ret


;-----------------------------------------------------------------------------
;                                divide_x
;-----------------------------------------------------------------------------
; Arguments:
;   rcx      (arg 1) : leg count
;   rdx      (arg 2) : pointer to input A first leg
;   r8       (arg 3) : input B leg
;   r9       (arg 4) : pointer to output quotient
; Output:
;   out = A / B, return A % B
;-----------------------------------------------------------------------------
divide_x:

    mov r10, rdx
    xor rdx, rdx

    lea r10, [r10 + (rcx-1)*8]
    lea r9, [r9 + (rcx-1)*8]

divide_x_loop:
    mov rax, qword[r10]
    div r8
    mov qword[r9], rax
    lea r10, [r10-8]
    lea r9, [r9-8]
    sub rcx, 1
    jg divide_x_loop

    mov rax, rdx

    ret


;-----------------------------------------------------------------------------
;                                modulus_x
;-----------------------------------------------------------------------------
; Arguments:
;   rcx      (arg 1) : leg count
;   rdx      (arg 2) : pointer to input A first leg
;   r8       (arg 3) : input B leg
; Output:
;   return A % B
;-----------------------------------------------------------------------------
modulus_x:

    mov r10, rdx
    xor rdx, rdx

    lea r10, [r10 + (rcx-1)*8]

modulus_x_loop:
    mov rax, qword[r10]
    div r8
    lea r10, [r10-8]
    sub rcx, 1
    jg modulus_x_loop

    mov rax, rdx

    ret


;-----------------------------------------------------------------------------
;                                divide_core
;-----------------------------------------------------------------------------
; Arguments:
;   rcx       (arg 1) : A_used
;   rdx       (arg 2) : A_overflow
;   r8        (arg 3) : pointer to input A first leg
;   r9        (arg 4) : B_used
;   [rsp+28h] (arg 5) : pointer to input B first leg
;   [rsp+32h] (arg 6) : pointer to output quotient
; Preconditions:
;   Same as BigRTL::DivideCore()
; Output:
;   {Q=quotient,A=remainder} = (A_ov | A) / B
;-----------------------------------------------------------------------------
divide_core:

    ; --------
    ; Prologue
    ; --------

    mov r10, qword[rsp+0x28]            ; r10 = B[]
    mov r11, qword[rsp+0x30]            ; r11 = Quotient output

    push r12 r13 r14 r15 rbx rsi rdi

    sub rcx, r9                         ; rcx = offset = A_used - B_used
    mov r12, qword[r10 + (r9-1)*8]      ; r12 = B_high = B[B_used-1]
    lea r8, [r8 + rcx*8]                ; r8 = A_offset = A + offset

    ; --------------------
    ; Set q_hi when A >= B
    ; --------------------

    xor r13, r13                        ; r13 = q_hi = 0
    cmp r12, rdx                        ; compare B_high to A_overflow
    jb divide_core_b_less_a             ; skip if B_high < A_overflow
    ja divide_core_a_less_b             ; skip if B_high > A_overflow

    lea r14, [r9 - 2]                   ; r14 = ii = B_used-2

divide_core_a_comp_b:
    mov rax, qword[r8 + r14*8]          ; rax = a = A_offset[ii]
    cmp qword[r10 + r14*8], rax         ; compare b to a
    jb divide_core_b_less_a             ; done if b < a
    ja divide_core_a_less_b             ; done if b > a

    sub r14, 1                          ; --ii
    jae divide_core_a_comp_b            ; loop while ii >= 0

divide_core_b_less_a:
    lea r13, [r13 + 1]                  ; q_hi = 1

    ; ---------------------------------
    ; If q_hi is set, subtract B from A
    ; ---------------------------------

    lea r14, [r9 - 1]                   ; r14 = B_used-1
    xor r15, r15                        ; r15 = ii = 0
    xor rbx, rbx                        ; rbx = borrow_in = 0

divide_core_sub_b_a:
    add bl, 255                         ; restore carry flag if bl != 0
    mov rax, qword[r10 + r15*8]         ; rax = b = B[ii]
    sbb qword[r8 + (r15+1)*8], rax      ; A_offset[ii+1] -= b + borrow_in
    setc bl                             ; store carry flag in al
    lea r15, [r15+1]                    ; r15 = ii++
    cmp r15, r14                        ; compare ii to B_used-1
    jb divide_core_sub_b_a              ; loop if ii < B_used-1

    sub rdx, r12                        ; A_overflow -= B_high
    sub rdx, rbx                        ; A_overflow -= borrow_in

divide_core_a_less_b:
    mov qword[r11 + (rcx+1)*8], r13     ; Q[offset+1] = q_hi

    ; ---------------------------------
    ; Main divide loop
    ; ---------------------------------

divide_core_loop_head:
    ; going into this loop, rdx = A_overflow
    mov rsi, rdx                        ; rsi = A_overflow
    ; q_hi(1/0), q_lo = A_overflow | A[B_used+offset-1] / B_high
    cmp rdx, r12                        ; compare A_overflow to B_high
    jb divide_core_q_hi_zero            ; skip if q_hi == 0
    sub rdx, r12                        ; rdx -= B_high

    ; ---------------------------------
    ; Main divide loop : q_hi == 1
    ; ---------------------------------
    ; A -= (1 | q_lo) * B

    mov rax, qword[r8 + (r9-1)*8]       ; rax = A_offset[B_used-1]
    div r12                             ; rax = q_lo = rdx:rax/B_high
    mov r13, rax                        ; r13 = q_lo

    xor r14, r14                        ; r14 = ii = 0
    xor r15, r15                        ; r15 = p_hi = 0
    xor rbx, rbx                        ; rbx = borrow-in = 0
    xor rdi, rdi                        ; rdi = B_last = 0

divide_core_q_hi_one_loop:
    mov rax, qword[r10 + r14*8]         ; rax = B[ii]
    mul r13                             ; rdx:rax = B[ii] * q_lo
    add rax, r15                        ; rdx:rax += p_hi
    adc rdx, 0                          ; "
    add rax, rdi                        ; rdx:rax += B_last
    adc rdx, 0                          ; p_lo = rax
    mov r15, rdx                        ; r15 = p_hi = rdx
    mov rdi, qword[r10 + r14*8]         ; rdi = B[ii]

    add bl, 255                         ; restore borrow-in from bl
    sbb qword[r8 + r14*8], rax          ; A_offset[ii] -= p_lo
    setc bl                             ; store borrow-in to bl

    lea r14, [r14+1]                    ; r14 = ii++
    cmp r14, r9                         ; compare ii to B_used
    jb divide_core_q_hi_one_loop        ; loop while ii < B_used

    sub rsi, rdi                        ; A_overflow -= B_last

    jmp divide_core_fix_up              ; skip the q_hi == 0 case

    ; ---------------------------------
    ; Main divide loop : q_hi == 0
    ; ---------------------------------
    ; A -= q_lo * B

divide_core_q_hi_zero:
    mov rax, qword[r8 + (r9-1)*8]       ; rax = A_offset[B_used-1]
    div r12                             ; rax = q_lo = rdx:rax/B_high
    mov r13, rax                        ; r13 = q_lo

    xor r14, r14                        ; r14 = ii = 0
    xor r15, r15                        ; r15 = p_hi = 0
    xor rbx, rbx                        ; rbx = borrow-in = 0

divide_core_q_hi_zero_loop:
    mov rax, qword[r10 + r14*8]         ; rax = B[ii]
    mul r13                             ; rdx:rax = B[ii] * q_lo
    add rax, r15                        ; p_lo = rax
    adc rdx, 0                          ; rdx:rax += p_hi
    mov r15, rdx                        ; r15 = p_hi = rdx

    add bl, 255                         ; restore borrow-in from bl
    sbb qword[r8 + r14*8], rax          ; A_offset[ii] -= p_lo
    setc bl                             ; store borrow-in to bl

    lea r14, [r14+1]                    ; r14 = ii++
    cmp r14, r9                         ; compare ii to B_used
    jb divide_core_q_hi_zero_loop       ; loop while ii < B_used

    ; --------------------------------------------
    ; Main divide loop : Fix until A_overflow == 0
    ; --------------------------------------------

divide_core_fix_up:
    sub rsi, r15                        ; A_overflow -= p_hi
    sub rsi, rbx                        ; A_overflow -= borrow-in

    jz divide_core_fix_up_tail          ; if A_overflow == 0, go to tail

divide_core_fix_up_head:
    lea r13, [r13 - 1]                  ; --q_lo
    xor r14, r14                        ; r14 = ii = 0
    xor rbx, rbx                        ; rbx = borrow-in = 0

divide_core_fix_up_add:
    mov rax, qword[r10 + r14*8]         ; rax = B[ii]
    add bl, 255                         ; restore carry-out from bl
    adc qword[r8 + r14*8], rax          ; A_offset[ii] += B[ii] + carry-in
    setc bl                             ; store carry-out to bl

    lea r14, [r14+1]                    ; r14 = ii++
    cmp r14, r9                         ; compare ii to B_used
    jb divide_core_fix_up_add           ; loop while ii < B_used

    add rsi, rbx                        ; A_overflow += carry-in
    jnz divide_core_fix_up_head         ; if A_overflow is still not zero, loop

divide_core_fix_up_tail:
    mov qword[r11 + rcx*8], r13         ; Q[offset] = q_lo
    
    mov rdx, qword[r8 + (r9-1)*8]       ; rdx = A_overflow = A_offset[B_used-1]
    sub rcx, 1                          ; rcx = offset--
    lea r8, [r8 - 8]                    ; A_offset = A + offset
    jae divide_core_loop_head           ; loop while offset >= 0

    ; --------
    ; Epilogue
    ; --------

    pop rdi rsi rbx r15 r14 r13 r12

    ret


;-----------------------------------------------------------------------------
;                    Appendix: x86-64 Calling Convention
;-----------------------------------------------------------------------------
; Callee save: rsp(stack), rbx(base), rbp(frame), r12-r15, rdi, rsi
; Caller save: rax(ret), rcx, rdx, r8-r11
