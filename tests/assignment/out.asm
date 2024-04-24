section .bss
a resd 1
b resd 1
tmp resd 1
section .text
global _start
_start:
mov eax, [a]
mov ecx, 94
mov DWORD [a], ecx
mov eax, [b]
mov ecx, 3
mov edx, 4
add edx, ecx
mov DWORD [b], edx
mov eax, [tmp]
mov ecx, 1
mov DWORD [tmp], ecx
mov rax, 60
mov rdi, 0
syscall
