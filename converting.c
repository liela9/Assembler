#include "math.h"
#include "constants.c"

#define NO0 255



/* Converts decimal number to binary */
unsigned long convertDtoB(int n) {
  unsigned long bin;
  int rem, i, numOfBits;
	
  bin = 0;
  i = 1;
  numOfBits = 0;

  if(n < 0)
	{
		n = -n;
		n = n ^ NO0;
		while (n != 0) 
		  {
		    numOfBits++;
		    rem = n % 2;
		    n /= 2;
		    bin += rem * i;
		    i *= BIN_MACHINE_CODE_LENGTH;
		  }
		 bin += 1;
	}
        else while (n != 0) 
	{
	    rem = n % 2;
	    n /= 2;
	    bin += rem * i;
	    i *= BIN_MACHINE_CODE_LENGTH;
	}

  return bin;
}

/* Converts binary number to decimal */
int convertBtoD(unsigned long n) {
  int dec, rem, i;

  dec = 0;
  i = 1;

  while(n > 0) {
    rem = n % BIN_MACHINE_CODE_LENGTH;
    n /= BIN_MACHINE_CODE_LENGTH;
    dec += rem * i;
    i *= 2;
  }

  return dec;
}

/* Revers the string */
char* reverstr(char str[], int index)
{
	int i;
	char *rstr;
	
  i = 0;
  *rstr = malloc(BIN_MACHINE_CODE_LENGTH * sizeof(char));

	/* ignore the '\0' */
	index -= 1;
	while(index > -1){
		*(rstr+i) = str[index--];
		i++;
	}
	return rstr;
}

/* Converts decimal number to base32 */
char* convertDtoB32(int n) 
{
  int rem, index;
  char str[BIN_MACHINE_CODE_LENGTH];
  char *s;

  index = 0;

  while (n > 0) {
    rem = n % 32;
    str[index] = (base32[rem]);
    n /= 32;
	  index++;
  }
  s = reverstr(str, index);
  return s;
}