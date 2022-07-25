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
    