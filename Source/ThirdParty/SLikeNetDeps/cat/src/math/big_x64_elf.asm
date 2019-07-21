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

format ELF64

section '.code' executable 


;-----------------------------------------------------------------------------
;                           Function Declarations
;-----------------------------------------------------------------------------
public bpm_add_4   as 'bpm_add_4'
public bpm_sub_4   as 'bpm_sub_4'
public bpm_mul_4   as 'bpm_mul_4'
public bpm_mulx_4  as 'bpm_mulx_4'
public bpm_sqr_4   as 'bpm_sqr_4'
; Does not provide these -- just extra complexity i don't need
;public divide_x    as 'divide64_x'
;public modulus_x   as 'modulus64_x'
;public divide_core as 'divide64_core'





;-----------------------------------------------------------------------------
;                                bpm_add_4
;-----------------------------------------------------------------------------
; Arguments:
;   rdi      (arg 1) : modulus parameter C
;   rsi      (arg 2) : pointer to input A first leg
;   rdx      (arg 3) : pointer to input B first leg
;   rcx      (arg 4) : pointer to output first leg
; Preconditions:
;   legs per bigint = 4
; Output:
;   out = A + B (mod C)
;-----------------------------------------------------------------------------
bpm_add_4:

    ; perform addition chain
    mov r8, qword[rsi]
    add r8, qword[rdx]
    mov qword[rcx], r8
    mov r9, qword[rsi+8]
    adc r9, qword[rdx+8]
    mov qword[rcx+8], r9
    mov r10, qword[rsi+16]
    adc r10, qword[rdx+16]
    mov qword[rcx+16], r10
    mov r11, qword[rsi+24]
    adc r11, qword[rdx+24]
    jnc bpm_add_4_done

    ; add C when it overflows
bpm_add_4_mod:
    add r8, rdi
    adc r9, 0
    adc r10, 0
    adc r11, 0
    jc bpm_add_4_mod

bpm_add_4_done:
    mov qword[rcx], r8
    mov qword[rcx+8], r9
    mov qword[rcx+16], r10
    mov qword[rcx+24], r11

    ret


;-----------------------------------------------------------------------------
;                                bpm_sub_4
;-----------------------------------------------------------------------------
; Arguments:
;   rdi      (arg 1) : modulus parameter C
;   rsi      (arg 2) : pointer to input A first leg
;   rdx      (arg 3) : pointer to input B first leg
;   rcx      (arg 4) : pointer to output first leg
; Preconditions:
;   legs per bigint = 4
; Output:
;   out = A - B (mod C)
;-----------------------------------------------------------------------------
bpm_sub_4:

    ; perform subtraction chain
    mov r8, qword[rsi]
    sub r8, qword[rdx]
    mov qword[rcx], r8
    mov r9, qword[rsi+8]
    sbb r9, qword[rdx+8]
    mov qword[rcx+8], r9
    mov r10, qword[rsi+16]
    sbb r10, qword[rdx+16]
    mov qword[rcx+16], r10
    mov r11, qword[rsi+24]
    sbb r11, qword[rdx+24]
    jnc bpm_sub_4_done

    ; subtract C when it overflows
bpm_sub_4_mod:
    sub r8, rdi
    sbb r9, 0
    sbb r10, 0
    sbb r11, 0
    jc bpm_sub_4_mod

bpm_sub_4_done:
    mov qword[rcx], r8
    mov qword[rcx+8], r9
    mov qword[rcx+16], r10
    mov qword[rcx+24], r11

    ret


;-----------------------------------------------------------------------------
;                                bpm_mul_4
;-----------------------------------------------------------------------------
; Arguments:
;   rcx->rdi      (arg 1) : modulus parameter C
;   rdx->rsi      (arg 2) : pointer to input A first leg
;   r8->rdx       (arg 3) : pointer to input B first leg
;   r9->rcx       (arg 4) : pointer to output first leg
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
    push r12 r13 r14 r15

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

    mov qword[.modc], rdi
    mov qword[.out], rcx

    ; ---- 4x4 comba multiply

    mov r8, [rsi]
    mov r9, [rsi+8]
    mov r10, [rsi+16]
    mov r11, [rsi+24]
    mov r12, [rdx]
    mov r13, [rdx+8]
    mov r14, [rdx+16]
    mov r15, [rdx+24]

    ; column 1
    mov rax, r8
    xor rcx, rcx
    mul r12 ; dh

    mov qword[.pro1], rax
        mov rdi, rdx

    ; column 2
    mov rax, r9
    xor rsi, rsi
    mul r12 ; ch
        add rdi, rax
        adc rcx, rdx
        adc rsi, 0

    mov rax, r8
    mul r13 ; dg
        add rdi, rax
        adc rcx, rdx
        adc rsi, 0

    mov qword[.pro2], rdi

    ; column 3
    mov rax, r10
    xor rdi, rdi
    mul r12 ; bh
        add rcx, rax
        adc rsi, rdx
        adc rdi, 0

    mov rax, r9
    mul r13 ; cg
        add rcx, rax
        adc rsi, rdx
        adc rdi, 0

    mov rax, r8
    mul r14 ; df
        add rcx, rax
        adc rsi, rdx
        adc rdi, 0

    mov qword[.pro3], rcx

    ; column 4
    mov rax, r11
    xor rcx, rcx
    mul r12 ; ah
        add rsi, rax
        adc rdi, rdx
        adc rcx, 0

    mov rax, r10
    mul r13 ; bg
        add rsi, rax
        adc rdi, rdx
        adc rcx, 0

    mov rax, r9
    mul r14 ; cf
        add rsi, rax
        adc rdi, rdx
        adc rcx, 0

    mov rax, r8
    mul r15 ; de
        add rsi, rax
        adc rdi, rdx
        adc rcx, 0

    mov rax, r11
    mov qword[.pro4], rsi

    ; column 5
    xor rsi, rsi
    mul r13 ; ag
        add rdi, rax
        adc rcx, rdx
        adc rsi, 0

    mov rax, r10
    mul r14 ; bf
        add rdi, rax
        adc rcx, rdx
        adc rsi, 0

    mov rax, r9
    mul r15 ; ce
        add rdi, rax
        adc rcx, rdx
        adc rsi, 0

    ; mov qword[.pro5], rbx
    mov r8, rdi

    ; column 6
    mov rax, r11
    xor rdi, rdi
    mul r14 ; af
        add rcx, rax
        adc rsi, rdx
        adc rdi, 0

    mov rax, r10
    mul r15 ; be
        add rcx, rax
        adc rsi, rdx
        adc rdi, 0

    ; mov qword[.pro6], rcx
    mov r12, rcx ; r12 gets .pro6 from rcx

    ; column 7
    mov rax, r11
    mul r15 ; ae
        add rsi, rax
        adc rdi, rdx

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

    mov rax, rdi
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

    pop r15 r14 r13 r12
    mov rsp, rbp
    pop rbp

    ret


;-----------------------------------------------------------------------------
;                                bpm_mulx_4
;-----------------------------------------------------------------------------
; Arguments:
;   rcx->rdi      (arg 1) : modulus parameter C
;   rdx->rsi      (arg 2) : pointer to input A first leg
;   r8->rdx       (arg 3) : single leg input B
;   r9->rcx       (arg 4) : pointer to output first leg
; Preconditions:
;   legs per bigint = 4
; Output:
;   out = A * B (mod C)
;-----------------------------------------------------------------------------
bpm_mulx_4:

    mov r8, rdx

    mov rax, qword[rsi]
    mul r8
        mov r9, rax
        mov r10, rdx

    mov rax, qword[rsi+8]
    mul r8
        xor r11, r11
        add r10, rax
        adc r11, rdx

    mov rax, qword[rsi+16]
    mul r8
        add r11, rax
        adc rdx, 0

    mov rax, qword[rsi+24]
    mov rsi, rdx
    mul r8
        add rsi, rax
        adc rdx, 0

    ; ---- modular reduction 5->4

    mov rax, rdi
    mul rdx
        add r9, rax
        adc r10, rdx
        adc r11, 0
        adc rsi, 0

    ; ---- modular reduction 4.1->4

    jnc bpm_mulx_4_out

    ; final add carried out so add once more
bpm_mulx_4_mod:
    add r9, rdi
    adc r10, 0
    adc r11, 0
    adc rsi, 0
    jc bpm_mulx_4_mod

bpm_mulx_4_out:
    mov qword[rcx], r9
    mov qword[rcx+8], r10
    mov qword[rcx+16], r11
    mov qword[rcx+24], rsi

    ret


;-----------------------------------------------------------------------------
;                                bpm_sqr_4
;-----------------------------------------------------------------------------
; Arguments:
;   rcx->rdi      (arg 1) : modulus parameter C
;   rdx->rsi      (arg 2) : pointer to input first leg
;   r8->rdx       (arg 3) : pointer to output first leg
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
    push r12

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

    mov qword[.modc], rdi
    mov qword[.out], rdx

    ; ---- 4x4 comba square

    mov r8, qword[rsi]
    mov r9, qword[rsi+8]
    mov r10, qword[rsi+16]
    mov r11, qword[rsi+24]

    ; column 1
    mov rax, r8
    mul r8 ; dd
        mov qword[.pro1], rax
        mov r12, rdx
        xor rsi, rsi
        xor rdi, rdi

    ; column 2
    mov rax, r8
    mul r9 ; cd
        ; r14:r13:r12 = 2(rdx:rax) + r12
        add r12, rax
        adc rsi, rdx
        adc rdi, 0
        add r12, rax
        adc rsi, rdx
        adc rdi, 0
        mov qword[.pro2], r12

    ; column 3
    mov rax, r8
    xor r12, r12
    mul r10 ; bd
        ; r12:r14:r13 = 2(rdx:rax) + 0:r14:r13
        add rsi, rax
        adc rdi, rdx
        adc r12, 0
        add rsi, rax
        adc rdi, rdx
        adc r12, 0

    mov rax, r9
    mul r9 ; cc
        ; r12:r14:r13 += 0:rdx:rax
        add rsi, rax
        adc rdi, rdx
        adc r12, 0
        mov qword[.pro3], rsi

    ; column 4
    mov rax, r8
    xor rsi, rsi
    mul r11 ; ad
        ; r13:r12:r14 = 2(rdx:rax) + 0:r12:r14
        add rdi, rax
        adc r12, rdx
        adc rsi, 0
        add rdi, rax
        adc r12, rdx
        adc rsi, 0

    mov rax, r9
    mul r10 ; bc
        ; r13:r12:r14 += 2(rdx:rax)
        add rdi, rax
        adc r12, rdx
        adc rsi, 0
        add rdi, rax
        adc r12, rdx
        adc rsi, 0
        mov qword[.pro4], rdi

    ; column 5
    mov rax, r9
    xor rdi, rdi
    mul r11 ; ac
        ; r14:r13:r12 = 2(rdx:rax) + 0:r13:r12
        add r12, rax
        adc rsi, rdx
        adc rdi, 0
        add r12, rax
        adc rsi, rdx
        adc rdi, 0

    mov rax, r10
    mul r10 ; bb
        ; r14:r13:r12 += 0:rdx:rax
        add r12, rax
        adc rsi, rdx
        adc rdi, 0
        ; mov qword[.pro5], r12
        mov r8, r12

    ; column 6
    mov rax, r10
    xor r12, r12
    mul r11 ; ab
        ; r12:r14:r13 = 2(rdx:rax) + 0:r14:r13
        add rsi, rax
        adc rdi, rdx
        adc r12, 0
        add rsi, rax
        adc rdi, rdx
        adc r12, 0
        ; mov qword[.pro6], r13

    ; column 7
    mov rax, r11
    mul r11 ; aa
        ; r13:r12:r14 = rdx:rax + 0:r12:r14
        add rdi, rax
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

    mov rax, rsi
    mul rcx
        xor r10, r10
        add r9, rax
        adc r10, rdx
        add r9, qword[.pro2]
        adc r10, 0

    mov rax, rdi
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

    mov rsi, qword[.out]

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
    mov qword[rsi], r8
    mov qword[rsi+8], r9
    mov qword[rsi+16], r10
    mov qword[rsi+24], r11

    pop r12
    mov rsp, rbp
    pop rbp

    ret


;-----------------------------------------------------------------------------
;                    Appendix: x86-ELF64 Calling Convention
;-----------------------------------------------------------------------------
; Callee save: rsp(stack), rbx(base), rbp(frame), r12-r15
; Caller save: rax(ret), rcx, rdx, r8-r11, rdi, rsi
