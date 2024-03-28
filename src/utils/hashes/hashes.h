//===--= hashes.h =---------------------------------------------------===
//
// hashes for veriuos purposes. special hashes for different purposes, 
// like JOAAT hash for the symbol table.
//
//===-----------------------------------------------------------------===

#ifndef QUEST_HASHES_H
#define QUEST_HASHES_H

#include <stddef.h>
#include <stdint.h>

uint32_t hash_JOAAT(char *key, size_t length);

#endif