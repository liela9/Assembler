#include "constants.h"
#include "utils.h"


/*Checks if the operand is register*/
int is_register(char *op){
    
    int i;
    for(i = 0; i < NUM_OF_REGISTERS; i++){
        if(strcmp(op, *registers[i]))
            return i;
    }
    return -1;
}


/*Splits the name of struct and the index after the point*/
char** is_struct(char *op){
    
    char *struct_val[2];
    struct_val[0] = NULL;
    struct_val[1] = NULL;

    while (op)
    {
        if(*op == '.'){
            struct_val[0] = strtok(op, ".");
            struct_val[1] = strtok(NULL, ".");
        }
    }
    return struct_val;
}


/*Tries to do realoc*/
void realloc_check(int index, unsigned int *table){
    unsigned int *ptr;
    
    ptr = (unsigned int*)realloc(table, index + sizeof(unsigned int));
    if(!ptr){
        printf("System Error: Memory allocation faild!\n");
        exit(0);
    }
    table = ptr;
}
    

/*Checks if it is a saved word of the system*/
bool is_saved_words(char *name){ 
    int index;
    
    /*Checks if it is a name of register*/
    for(index = 0; index < NUM_OF_REGISTERS; index++){
        if(!strcmp(name, registers[index]))
            return true;
    }

    /*Checks if it is a name of opcode*/
    for(index = 0; index < OPCODE_LENGTH; index++){
        if(!strcmp(name, opcode[index]))
            return true;
    }

    /*Checks if it is a guidance word*/
    for(index = 0; index < NUM_OF_SAVED_WORDS; index++){
        if(!strcmp(name, saved_words[index]))
            return true;
    }

    return false;
}

/*checks for every char in the string if it is non alphanumeric char*/
bool alphanumeric_str(char *string){
	int index;

	for(index = 0; string[index]; index++){
		if (!isalpha(string[index]) && !isdigit(string[index]))
            return false;
	}
	return true;
}


