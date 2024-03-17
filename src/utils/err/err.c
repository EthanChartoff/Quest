//===--= err.c =------------------------------------------------------===
//
// this file deals with error handling. 
//
//===-----------------------------------------------------------------===

#include "err.h"
#include <stdio.h>
#include <stdlib.h>

#define prog "qc"

#define err_msg() printf("%s: error: in file: %s line: %d\n", prog, status.fname, status.linec);


// throw an error corresponding to the exit code and immediately stops the program (treating assembler errors only)
void thrw(int code){
	switch(code){
		case OPEN_FILE_ERR:
			fprintf(stderr, "%s: Error while opening file, terminating\n", prog);
			break;

		case WRT_FILE_ERR:
			fprintf(stderr, "%s: Error while writing file, terminating\n", prog);
			break;

		case ALLOC_ERR:
			fprintf(stderr, "%s: Error while allocating memory, terminating\n", prog);
			break;
	}
	exit(code);
}