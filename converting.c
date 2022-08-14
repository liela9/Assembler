#include <math.h>
#include "constants.h"
#include "converting.h"
#include "utils.h"


/* Converts decimal number to binary with the Two's complement method */
unsigned long convertDtoB(int decimal_number){
    unsigned long bin_number = 0;
    int remainder, index = 1, num_of_bits = 0;

    if(decimal_number < 0){
    decimal_number = -decimal_number;
    
    /* Bit conversion */
    decimal_number = decimal_number ^ TEN_BITS_OF_ONE;
    
    while (decimal_number != 0 && num_of_bits < BIN_MACHINE_CODE_LENGTH){
        num_of_bits++;
        remainder = decimal_number % 2;
        decimal_number /= 2;
        bin_number += remainder * index;
        index *= BIN_MACHINE_CODE_LENGTH;
        }
        bin_number += 1;
    }

    /* If the decimal number is positive. */
    else while (decimal_number != 0) {
        remainder = decimal_number % 2;
        decimal_number /= 2;
        bin_number += remainder * index;
        index *= BIN_MACHINE_CODE_LENGTH;
    }

    return bin_number;
}


int convertBtoD(unsigned long bin_number)  
{  
    int decimal_num = 0, temp = 0, reminder;

    while (bin_number != 0 && temp < BIN_MACHINE_CODE_LENGTH)  
    {  
        reminder = bin_number % 10;
        bin_number = bin_number / 10;
        decimal_num = decimal_num + reminder * pow(2, temp);
        temp++;  
    }  
    return decimal_num;  
}  


/* Converts decimal number to base32 */
char *convertDtoB32(int decimal_number) {
    static char str[LENGTH_OF_32_ITEM];
    
    str[0] = base32[decimal_number / 32];
    str[1] = base32[decimal_number % 32];

    return str;
}

/* Converts binary number to base32 */
char *convertBtoB32(unsigned long binary_number) {
    return convertDtoB32(convertBtoD(binary_number));
}
