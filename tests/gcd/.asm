section .bss
a resd 1
b resd 1
tmp resd 1
section .text
global _start
_start:
mov ax, 94
mov [a], ax
mov ax, 3
mov [b], ax
mov ax, 0
mov [tmp], ax
