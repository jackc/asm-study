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
    xor rax, rax
    ret

print_newline:
    xor rax, rax
    ret


print_uint:
    xor rax, rax
    ret


print_int:
    xor rax, rax
    ret

string_equals:
    xor rax, rax
    ret


read_char:
    xor rax, rax
    ret

section .data
word_buffer times 256 db 0

section .text

read_word:
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


string_copy:
    ret
