section .text

string_length:
    mov rax, -1
    .loop:
    inc rax
    cmp byte[rdi + rax], 0
    jne .loop
    ret

print_string:
    push rdi ; save pointer to string
    call string_length
    mov rdx, rax ; return value of string_length is in rax - we need it in rdx
    mov rax, 1 ; write syscall
    mov rdi, 1 ; fd 1 -- stdout
    pop rsi ; restore pointer to string
    syscall
    ret

print_char:
    push rdi
    mov rax, 1 ; write syscall
    mov rdi, 1 ; fd 1 -- stdout
    mov rdx, 1 ; 1 byte length
    mov rsi, rsp ; the memory where the char was pushed
    syscall
    pop rdi
    ret

print_newline:
    xor rax, rax
    ret


print_uint:
    mov rsi, rsp ; save current stack pointer / rsi stores current write position for string
    sub rsp, 24 ; allocate space for string

    mov r8, 10 ; division will always be by 10
    mov rax, rdi ; set lower bits with number

    .loop:
    dec rsi
    xor rdx, rdx ; clear top bits for div
    div r8 ; divide rdx:rax by r8
    add rdx, 48 ; character 0 is 48 in ASCII / UTF8
    mov [rsi], dl
    test rax, rax
    jnz .loop

    ; write the results
    mov rax, 1 ; write syscall
    mov rdi, 1 ; fd 1 -- stdout
    ; rsi already points to string location

    mov rdx, 24 ; compute length
    add rdx, rsp
    sub rdx, rsi

    syscall

    add rsp, 24 ; release space for string on stack

    ret


print_int:
    mov rsi, rsp ; save current stack pointer / rsi stores current write position for string
    sub rsp, 24 ; allocate space for string

    mov r9, rdi
    cmp r9, 0
    jge .after_save_neg
    mov r9, -1 ; remember number is negative
    neg rdi ; negate value to make positive

    .after_save_neg:

    mov r8, 10 ; division will always be by 10
    mov rax, rdi ; set lower bits with number

    .loop:
    dec rsi
    xor rdx, rdx ; clear top bits for div
    div r8 ; divide rdx:rax by r8
    add rdx, 48 ; character 0 is 48 in ASCII / UTF8
    mov [rsi], dl
    test rax, rax
    jnz .loop

    cmp r9, 0
    jge .print
    dec rsi
    mov byte[rsi], '-'

    .print:

    ; write the results
    mov rax, 1 ; write syscall
    mov rdi, 1 ; fd 1 -- stdout
    ; rsi already points to string location

    mov rdx, 24 ; compute length
    add rdx, rsp
    sub rdx, rsi

    syscall

    add rsp, 24 ; release space for string on stack

    ret

string_equals:
    xor rax, rax
    ret


read_char:
    sub rsp, 8 ; make some room on the stack
    mov rax, 0 ; read syscall
    mov rdi, 0 ; fd 0 -- stdin
    mov rsi, rsp ; read to space allocated on stack
    mov rdx, 1 ; read a single byte
    syscall

    xor rax, rax
    mov al, [rsp]
    add rsp, 8

    ret

section .data
word_buffer times 256 db 0

section .text

read_word:
    mov r12, rdi ; save initial buffer location
    mov r13, rdi ; current buffer pointer
    mov r14, rsi ; save buffer length

    .loop:
    call read_char
    mov [r13], al
    inc r13
    cmp al, 0
    je .done
    cmp al, 0x20
    je .done
    cmp al, 0x9
    je .done
    cmp al, 0x10
    je .done
    mov rax, r13
    sub rax, r12
    cmp rax, rsi
    jl .loop

    .done:
    mov rax, r12
    ret

; rdi points to a string
; returns rax: number, rdx : length
parse_uint:
    xor rax, rax
    ret

; rdi points to a string
; returns rax: number, rdx : length
parse_int:
    xor rax, rax
    ret

; version taken from teacher dir
string_copy:
    mov dl, byte[rdi]
    mov byte[rsi], dl
    inc rdi
    inc rsi
    test dl, dl
    jnz string_copy
    ret


; my (hopefully correct implementation)
; string_copy:
;     ; check for buffer size <= 0
;     cmp rdx, 0
;     jg .start
;     mov rax, 0
;     ret

;     .start:
;     push rdi ; pointer to string
;     push rsi ; pointer to buffer
;     push rdx ; buffer size
;     call string_length
;     pop rdx ; restore buffer size
;     pop rsi ; restore pointer to buffer
;     pop rdi ; restore pointer to string

;     ; check if string is too big
;     cmp rdx, rax
;     jl .copy
;     mov rax, 0
;     ret

;     ; rax number of bytes to copy
;     ; rcx current idx
;     ; cl - current byte
;     .copy:
;     mov rcx, 0
;     .loop:
;     mov cl, [rdi + rcx]
;     mov [rsi + rcx], cl
;     inc rcx
;     cmp rax, rcx
;     jge .loop

;     mov rax, rsi ; return buffer pointer
;     ret
