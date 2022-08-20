#include "conversionUtils.h"

#include <math.h>

#include "constants.h"
#include "utils.h"

/* converts decimal number to binary representation using the two's complement method */
unsigned long convertDtoB(int decimal_number) {
    unsigned long bin_number = 0;
    int remainder, index = 1, num_of_bits = 0;

    if (decimal_number < 0) {
        decimal_number = -decimal_number;

        /* bit conversion */
        decimal_number = decimal_number ^ TEN_BITS_OF_ONE;

        while (decimal_number != 0 && num_of_bits < BIN_MACHINE_CODE_LENGTH) {
            num_of_bits++;
            remainder = decimal_number % 2;
            decimal_number /= 2;
            bin_number += remainder * index;
            index *= BIN_MACHINE_CODE_LENGTH;
        }
        bin_number += 1;
    }

    /* if the decimal number is positive */
    else {
        while (decimal_number != 0) {
            remainder = decimal_number % 2;
            decimal_number /= 2;
            bin_number += remainder * index;
            index *= BIN_MACHINE_CODE_LENGTH;
        }
    }

    return bin_number;
}

/* converts binary number to decimal representation */
int convertBtoD(unsigned long bin_number) {
    int decimal_num = 0, temp = 0, reminder;

    while (bin_number != 0 && temp < BIN_MACHINE_CODE_LENGTH) {
        reminder = bin_number % 10;
        bin_number = bin_number / 10;
        decimal_num = decimal_num + reminder * pow(2, temp);
        temp++;
    }
    return decimal_num;
}

/* converts decimal number to base32 representation */
char *convertDtoB32(int decimal_number) {
    static char str[LENGTH_OF_32_ITEM];

    str[0] = base32[decimal_number / 32];
    str[1] = base32[decimal_number % 32];

    return str;
}

/* converts binary number to base32 representation */
char *convertBtoB32(unsigned long binary_number) {
    return convertDtoB32(convertBtoD(binary_number));
}
