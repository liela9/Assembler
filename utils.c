#include "constants.h"
#include "utils.h"


/*Checks if the operand is register*/
int is_register(char *op){
    
    int i;
    for(i = 0; i < NUM_OF_REGISTERS; i++){
        if(strcmp(op, registers[i]))
            return i;
    }
    return -1;
}


/*Splits the name of struct and the index after the point*/
char** is_struct(char *op){
    char **struct_val[2];
    
    struct_val[0] = NULL;
    struct_val[1] = NULL;

    while (op){
        if(*op == '.'){
            (*struct_val)[0] = strtok(op, ".");
            (*struct_val)[1] = strtok(NULL, ".");
        }
    }
    return *struct_val;
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



void *calloc_with_check(long units_num, long unit_size) {
	void *ptr = calloc(units_num, unit_size);
	if (ptr == NULL)
		printf("System Error: memory allocation failed\n");
	return ptr;
}

void *malloc_with_check(long size) {
	void *ptr = malloc(size);
	if (ptr == NULL)
		printf("System Error: memory allocation failed\n");
	return ptr;
}

void reset_array(char *array){
    int i;

    for(i = 0; i < strlen(array); ++i)
        array[i] = '\0';
}

FILE *open_file_with_extension(char *file_name, char *extension, char *mode) {
    char new_file_name[FILENAME_MAX]; /* TODO: Find out if can use it */
    FILE *ret_file;

    strcpy(new_file_name, file_name);
    strcat(new_file_name, AM_EXTENSION); /*Linking the extension to the file's name*/
    
    ret_file = fopen(new_file_name, mode);
    if(!ret_file)
        printf("User Error: Could not open file: %s\n", new_file_name);
    return ret_file;
}