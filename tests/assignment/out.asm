section .bss
a resd 1
b resd 1
section .text
global _start
_start:
mov eax, 94
mov DWORD [a], eax
mov eax, 3
mov ecx, 4
add ecx, eax
mov DWORD [b], ecx
mov rax, 60
mov rdi, 0
syscall
