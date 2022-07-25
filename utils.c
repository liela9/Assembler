#include "assembler.h"


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

void realloc_check(int index, unsigned int *table){
    unsigned int *ptr;
    
    ptr = (unsigned int*)realloc(table, index + sizeof(unsigned int));
    if(!ptr){
        printf("Memory allocation faild!");
        exit(0);
    }
    table = ptr;
}
    

/*Checks if it is a saved word of the system*/
bool saved_words(char *name){ 
    int i;
    
    for(i = 0; i < NUM_OF_REGISTERS; i++){
        if(!strcmp(name, registers[i]))
            return true;
    }

    for(i = 0; i < OPCODE_LENGTH; i++){
        if(!strcmp(name, opcode[i]))
            return true;
    }

    for(i = 0; i < NUM_OF_GUIDANCE_NAME; i++){
        if(!strcmp(name, guidance[i]))
            return true;
    }

    return false;
}

/*checks for every char in the string if it is non alphanumeric char*/
bool alphanumeric_str(char *string){
	int i;

	for(i = 0; string[i]; i++){
		if (!isalpha(string[i]) && !isdigit(string[i]))
            return false;
	}
	return true;
}
