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
add ecx, edx
mov DWORD [b], ecx
mov eax, [tmp]
mov ecx, 1
mov DWORD [tmp], ecx
mov eax, [a]
mov ecx, [b]
cmp ecx, eax
setl al
cmp al, 0
jz end_if
mov ecx, [tmp]
mov edx, [a]
mov ebx, [b]
sub edx, ebx
mov DWORD [tmp], edx
end_if:
mov rax, 60
mov rdi, 0
syscall
