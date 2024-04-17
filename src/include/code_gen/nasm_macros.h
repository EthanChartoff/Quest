// ==---------------==
//  op-code 
// ==---------------==

#define DATA "section .data\n"
#define TEXT "section .text\n"
#define BSS "section .bss\n"

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

#define MOV "mov %s, %s\n"
#define MOV_MEM "mov [%s], %s\n"


#define NOP "nop\n"



