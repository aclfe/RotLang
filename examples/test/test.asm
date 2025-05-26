;Simplest assembly program possible
global _start
_start:
    mov rax, 60 ; syscall number for exit
    mov rdi, 0
    ; The maximum value or rdi is 255 in Linux.
    ; Exit code 0 = success.
    syscall




