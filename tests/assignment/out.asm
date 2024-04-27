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
cmp eax, ecx
setg al
cmp al, 0
jz else
mov ecx, [tmp]
mov edx, [a]
mov ebx, [b]
sub edx, ebx
mov DWORD [tmp], edx
jmp end
else:
mov ecx, [tmp]
mov edx, [b]
mov ebx, [a]
sub edx, ebx
mov DWORD [tmp], edx
end:

mov eax, [tmp]
mov ecx, 35
mov DWORD [tmp], ecx
mov rax, 60
mov rdi, 0
syscall
