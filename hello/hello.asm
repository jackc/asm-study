BITS 64

global _start

section .data
message: db 'hello, world!', 10 ;10 is newline
section .text
_start:
  mov rax, 1
  mov rdi, 1
  mov rsi, message
  mov rdx, 14
  syscall

  ; needed to add call to exit to avoid segfault
  mov rax, 60
  xor rdi, rdi
  syscall
