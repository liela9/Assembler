#include "constants.h"

const char base32[BASE_LENGTH] = {'!', '@', '#', '$', '%', '^', '&', '*', '<', '>', 'a', 'b', 
'c', 'd', 'e', 'f', 'g','h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v'};

const char registers[NUM_OF_REGISTERS][2] = {"r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7"};

const char opcode[OPCODE_LENGTH][3] = {"mov", "cmp", "add", "sub", "not", "clr", "lea", "inc", 
"dec", "jmp", "bne", "get", "prn", "jsr", "rts", "hlt"}; 

const char* saved_words[NUM_OF_SAVED_WORDS] = {"data", "string", "struct", "entry", "extern", "macro", "endmacro"};

