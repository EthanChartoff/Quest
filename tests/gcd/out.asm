section .bss
a resd 1
b resd 1
tmp resd 1
section .text
global _start
_start:
mov eax, [a]
mov ecx, 21
mov DWORD [a], ecx
mov eax, [b]
mov ecx, 14
mov DWORD [b], ecx
mov eax, [tmp]
mov ecx, 0
mov DWORD [tmp], ecx
mov eax, [a]
mov ecx, [b]
cmp eax, ecx
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
mov ecx, [a]
mov edx, [b]
cmp ecx, edx
setg ah
cmp ah, 0
jz else
mov ecx, [a]
mov edx, [a]
mov ebx, [b]
sub edx, ebx
mov DWORD [a], edx
jmp end
else:
mov ecx, [b]
mov edx, [b]
mov ebx, [a]
sub edx, ebx
mov DWORD [b], edx
end:
loop:
cmp al, 0
jz end_loop
jmp loop
mov eax, [b]
mov ecx, 0
cmp eax, ecx
setg al
end_loop:

mov eax, '0'
add [a], eax

mov eax, 1
mov edi, 1
mov esi, a
mov edx, 4
syscall


mov rax, 60
mov rdi, 0
syscall
