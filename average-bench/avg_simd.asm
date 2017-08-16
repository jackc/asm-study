global avg_simd

section .text

avg_simd:
    ; initialize xmmX to 0 -- I'm sure there's a better way to do this
    mov rax, 0
    cvtsi2sd xmm0, rax
    shufpd xmm0, xmm0, 1
    cvtsi2sd xmm0, rax

    cvtsi2sd xmm1, rax
    shufpd xmm1, xmm1, 1
    cvtsi2sd xmm1, rax

    cvtsi2sd xmm2, rax
    shufpd xmm2, xmm2, 1
    cvtsi2sd xmm2, rax

    cvtsi2sd xmm3, rax
    shufpd xmm3, xmm3, 1
    cvtsi2sd xmm3, rax

    ; if we were given 0 values abort
    test rsi, rsi
    jnz .a
    ret

    ; should check for proper number of size of count

    .a:
    mov rcx, 0

    .loop:
    addpd xmm0, [rdi]
    addpd xmm1, [rdi + 16]
    addpd xmm2, [rdi + 32]
    addpd xmm3, [rdi + 48]

    add rcx, 8
    add rdi, 64
    cmp rcx, rsi
    jl .loop

    addpd xmm0, xmm1
    addpd xmm0, xmm2
    addpd xmm0, xmm3

    movapd xmm1, xmm0
    shufpd xmm1, xmm1, 1
    addsd xmm0, xmm1
    cvtsi2sd xmm2, rsi
    divsd xmm0, xmm2

    ret
