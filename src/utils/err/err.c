//===--= err.c =------------------------------------------------------===
//
// this file deals with error handling. 
//
//===-----------------------------------------------------------------===

#include "err.h"
#include <stdio.h>
#include <stdlib.h>


// throw an error corresponding to the exit code and immediately stops the program (treating assembler errors only)
void thrw(int code) {
	char *errs[] = {
    	#define ERR(name, msg) msg,
		#include "errors.h"
		#undef ERR		
	};

	PERROR_PROG(errs[code]);
	exit(code);	
}