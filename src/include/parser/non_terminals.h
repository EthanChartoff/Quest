#ifndef NON_TERM
#define NON_TERM(name, symbol)
#endif

NON_TERM(null, "")
NON_TERM(start, "S'")
NON_TERM(S, "S")
NON_TERM(E, "E")
NON_TERM(E_, "E'")
NON_TERM(F, "F")
NON_TERM(T, "T")
NON_TERM(C, "C")


#undef NON_TERM
