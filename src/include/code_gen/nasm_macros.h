#ifndef QUEST_NASM_MACROS_H
#define QUEST_NASM_MACROS_H

// ==---------------==
//  op-code 
// ==---------------==

#define DATA_SECTION "section .data\n"
#define TEXT_SECTION "section .text\n"
#define BSS_SECTION "section .bss\n"

#define GLOBAL(x) "global " x "\n"
#define EXTERN(x) "extern " x "\n"

#define LABEL(x) x ":\n"

#define DB(x) "%s db " x "\n"
#define DW(x) "%s dw " x "\n"
#define DD(x) "%s dd " x "\n"
#define DQ(x) "%s dq " x "\n"

#define RESB(x) "%s resb " x "\n"
#define RESW(x) "%s resw " x "\n"
#define RESD(x) "%s resd " x "\n"
#define RESQ(x) "%s resq " x "\n"

#define MEM(x) "[" (x) "]"

// ==---------------==
//  Instructions 
// ==---------------==

#define NOP "nop\n"

#define MOV "mov %s, %s\n"
#define MOV_MEM "mov [%s], %s\n"
#define MOV_MEM_TYPE "mov %s [%s], %s\n"

#define OR "or %s, %s\n"
#define XOR "xor %s, %s\n"
#define AND "and %s, %s\n"
#define NOT "not %s\n"
#define NEG "neg %s\n"

#define ADD "add %s, %s\n"
#define SUB "sub %s, %s\n"
#define MUL "mul %s\n"
#define DIV "div %s\n"

#define SHL "shl %s, %s\n"
#define SHR "shr %s, %s\n"
#define SAR "sar %s, %s\n"

#define CMP "cmp %s, %s\n"

#define JE "je %s\n"
#define JNE "jne %s\n"
#define JG "jg %s\n"
#define JL "jl %s\n"
#define JGE "jge %s\n"
#define JLE "jle %s\n"
#define JZ "jz %s\n"
#define JNZ "jnz %s\n"
#define JMP "jmp %s\n"

#define PUSH "push %s\n"
#define POP "pop %s\n"

// ==---------------==
//  misc
// ==---------------==
#define TYPE_TO_SIZE(type) (    \
    type == TOK_INT ? DWORD :   \
    type == TOK_CHAR ? BYTE :   \
    0                           \
) 

#define SIZE_TO_STR(size) (    \
    size == DWORD ? "DWORD" : \
    size == WORD ? "WORD" :   \
    size == BYTE ? "BYTE" :   \
    0                         \
)

#define END_PROGRAM "mov rax, 60\n" "mov rdi, 0\n" "syscall\n"


#endif /* QUEST_NASM_MACROS_H */