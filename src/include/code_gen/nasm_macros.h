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

// ==---------------==
//  Instructions 
// ==---------------==

#define MOV "mov %s, %s\n"
#define MOV_MEM "mov [%s], %s\n"
#define MOV_MEM_TYPE "mov %s PTR [%s], %s\n"


#define NOP "nop\n"





#endif /* QUEST_NASM_MACROS_H */