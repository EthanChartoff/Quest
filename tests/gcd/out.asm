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
mov DWORD [b], ecx
mov eax, [tmp]
mov ecx, 0
mov DWORD [tmp], ecx
mov eax, [a]
mov ecx, [b]
cmp ecx, eax
setl al
cmp al, 0
jz end_if
mov ecx, [tmp]
mov edx, [a]
mov DWORD [tmp], edx
mov ecx, [a]
mov edx, [b]
mov DWORD [a], edx
mov ecx, [b]
mov edx, [tmp]
mov DWORD [b], edx
end_if:
mov eax, [b]
mov ecx, 0
cmp ecx, eax
setg al
mov ecx, [a]
mov edx, [a]
mov ebx, [b]
sub edx, ebx
mov DWORD [a], edx
cmp ah, 0
jz else
mov ecx, [b]
mov edx, [b]
mov ebx, [a]
sub edx, ebx
mov DWORD [b], edx
else:
mov rax, 60
mov rdi, 0
syscall
