#include "constants.h"
#include "utils.h"

const char registers[NUM_OF_REGISTERS][2] = {"r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7"};

const char opcode[NUM_OF_OPCODES][3] = {"mov", "cmp", "add", "sub", "not", "clr", "lea", "inc", 
"dec", "jmp", "bne", "get", "prn", "jsr", "rts", "hlt"}; 

static const char *reserved_words[NUM_OF_RESERVED_WORDS] = {"data", "string", "struct", "entry", "extern", "macro", "endmacro"};

bool is_reserved_word(char *word) {
    int i;

    /*Checks if it is a name of register*/
    for(i = 0; i < NUM_OF_REGISTERS; ++i){
        if(!strcmp(word, registers[i]))
            return true;
    }

    /*Checks if it is a name of opcode*/
    for(i = 0; i < NUM_OF_OPCODES; ++i){
        if(!strcmp(word, opcode[i]))
            return true;
    }
        /*Checks if it is a guidance word*/
    for(i = 0; i < NUM_OF_RESERVED_WORDS; ++i){
        if(!strcmp(word, reserved_words[i]))
            return true;
    }
    return false;
}


/*Finds opcode index by opcode name*/
int find_opcode(char *str){
    int i;

    for(i = 0; i < NUM_OF_OPCODES; ++i)
        if(!strcmp(str, opcode[i]))
            return i;
    
    return -1;
}

/*Checks if the operand is register*/
int is_register(char *operand){
    
    int i;
    for(i = 0; i < NUM_OF_REGISTERS; ++i){
        if(!strcmp(operand, registers[i]))
            return i;
    }
    return -1;
}


/*Splits the name of the struct and the index after the point*/
char** is_struct(char *operand){
    char **struct_val[2];
    
    struct_val[0] = NULL;
    struct_val[1] = NULL;

    while (operand){
        if(*operand == '.'){
            (*struct_val)[0] = strtok(operand, ".");
            (*struct_val)[1] = strtok(NULL, ".");
        }
    }
    return *struct_val;
}



void *calloc_with_check(long units_num, long unit_size) {
	void *ptr = calloc(units_num, unit_size);
	
    if (!ptr)
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
    strcat(new_file_name, extension); /*Linking the extension to the file's name*/
    
    ret_file = fopen(new_file_name, mode);
    if(!ret_file)
        printf("User Error: Could not open file: %s\n", new_file_name);
    return ret_file;
}