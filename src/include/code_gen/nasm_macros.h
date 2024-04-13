// ==---------------==
//  op-code 
// ==---------------==

#define DATA "SECTION .DATA\n"

#define TEXT "SECTION .TEXT\n"

#define GLOBAL(x) "GLOBAL " x "\n"

#define EXTERN(x) "EXTERN " x "\n"

#define LABEL(x) x ":"



// ==---------------==
//  Instructions 
// ==---------------==

#define MOV "MOV %s, %s\n"

#define NOP "NOP\n"

#define DB "%s DB ?\n"
#define DQ "%s DQ ?\n"

