#include "math.h"
#include "constants.c"

#define BIN_MACHINE_CODE_LENGTH 10
#define ONLY1 1023

/* Converts decimal number to binary with the Two's complement method */
unsigned long convertDtoB(int dec_num) {
  unsigned long bin_num;
  int rem, i, numOfBits;
	
  bin_num = 0;
  i = 1;
  numOfBits = 0;

  if(dec_num < 0)
	{
		dec_num = -dec_num;
		
		/* Bit conversion */
		dec_num = dec_num ^ ONLY1;
		
		while (dec_num != 0) 
		  {
		    numOfBits++;
		    rem = dec_num % 2;
		    dec_num /= 2;
		    bin_num += rem * i;
		    i *= BIN_MACHINE_CODE_LENGTH;
		  }
		 bin_num += 1;
	}
	/* If the decimal number is positive. */
        else while (dec_num != 0) 
	{
	    rem = dec_num % 2;
	    dec_num /= 2;
	    bin_num += rem * i;
	    i *= BIN_MACHINE_CODE_LENGTH;
	}

  return bin_num;
}

/* Converts binary number to decimal */
int convertBtoD(unsigned long bin_num) {
  int dec_num, rem, i;

  dec_num = 0;
  i = 1;

  while(bin_num > 0) {
    rem = bin_num % BIN_MACHINE_CODE_LENGTH;
    bin_num /= BIN_MACHINE_CODE_LENGTH;
    dec_num += rem * i;
    i *= 2;
  }

  return dec_num;
}

/* Revers the string */
char* reverstr(char str[], int index)
{
	int i;
	char *rstr;
	
  i = 0;
  rstr = malloc(BIN_MACHINE_CODE_LENGTH * sizeof(char));

	/* ignore the '\0' */
	index -= 1;
	while(index > -1){
		*(rstr+i) = str[index--];
		i++;
	}
	return rstr;
}

/* Converts decimal number to base32 */
char* convertDtoB32(int dec_num) 
{
  int rem, index;
  char str[BIN_MACHINE_CODE_LENGTH];
  char *s;

  index = 0;

  while (dec_num > 0) {
    rem = dec_num % 32;
    str[index] = (base32[rem]);
    dec_num /= 32;
	  index++;
  }
  s = reverstr(str, index);
  return s;
}
