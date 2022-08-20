#ifndef CONVERSION_UTILS_H
#define CONVERSION_UTILS_H

#include <math.h>

#include "constants.h"
#include "utils.h"

#define LENGTH_OF_32_ITEM 2
#define BIN_MACHINE_CODE_LENGTH 10
#define TEN_BITS_OF_ONE 1023
#define BASE_LENGTH 32

static const char base32[BASE_LENGTH] = {
    '!', '@', '#', '$', '%', '^', '&', '*', '<', '>', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v'};

unsigned long convertDtoB(int);
int convertBtoD(unsigned long);
char* convertDtoB32(int);
char* convertBtoB32(unsigned long);

#endif /* CONVERSION_UTILS_H */
