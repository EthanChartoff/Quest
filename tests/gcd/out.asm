section .bss
a resd 1
b resd 1
tmp resd 1
section .text
global _start
_start:
mov eax, 94
mov [a], eax
mov eax, 3
mov [b], eax
mov eax, 0
mov [tmp], eax
