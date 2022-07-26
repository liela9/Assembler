#include "utils.h"

const char registers[NUM_OF_REGISTERS][3] = {"r0", "r1", "r2", "r3",
                                             "r4", "r5", "r6", "r7"};

const char *opcode[NUM_OF_OPCODES] = {"mov", "cmp", "add", "sub", "not", "clr",
                                      "lea", "inc", "dec", "jmp", "bne", "get",
                                      "prn", "jsr", "rts", "hlt"};

const char *reserved_words[NUM_OF_RESERVED_WORDS] = {
    "data", "string", "struct", "entry", "extern", "macro", "endmacro"};

void print_user_error(multiVars *vars, const char *fmt, ...) {
    va_list args;

    printf("User Error - in %s, line %d: ", vars->file_name, vars->line_counter);

    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);

    printf("\n");
}

bool is_reserved_word(char *word) {
    int i;

    /*Checks if it is a name of register*/
    for (i = 0; i < NUM_OF_REGISTERS; ++i) {
        if (!strcmp(word, registers[i])) return true;
    }

    /*Checks if it is a name of opcode*/
    for (i = 0; i < NUM_OF_OPCODES; ++i) {
        if (!strcmp(word, opcode[i])) return true;
    }
    /*Checks if it is a guidance word*/
    for (i = 0; i < NUM_OF_RESERVED_WORDS; ++i) {
        if (!strcmp(word, reserved_words[i])) return true;
    }
    return false;
}

/*Finds opcode index by opcode name*/
int find_opcode(char *str) {
    int i;

    for (i = 0; i < NUM_OF_OPCODES; ++i)
        if (!strcmp(str, opcode[i])) return i;

    return -1;
}

/*Checks if the operand is register*/
int is_register(char *operand) {
    int i;
    for (i = 0; i < NUM_OF_REGISTERS; ++i) {
        if (!strcmp(operand, registers[i])) return i;
    }
    return -1;
}

/*Returns the index of the struct operand in case of struct*/
int is_struct(char *operand) {
    char *index;

    if ((index = strstr(operand, "."))) {
        if (index[1] == '1') return 1;
        if (index[1] == '2') return 2;
        return -1;
    }

    /*If it is not struct, there is no "." ==> return 0*/
    return 0;
}

void *calloc_with_check(long units_num, long unit_size) {
    void *ptr = calloc(units_num, unit_size);

    if (!ptr) printf("System Error: memory allocation failed\n");
    return ptr;
}

void reset_array(char *array) {
    int i;

    for (i = 0; i < strlen(array); ++i) array[i] = '\0';
}

FILE *open_file_with_extension(char *file_name, char *extension, char *mode) {
    char new_file_name[FILENAME_MAX]; /* TODO: Find out if can use it */
    FILE *ret_file;

    strcpy(new_file_name, file_name);
    strcat(new_file_name, extension); /*Linking the extension to the file's name*/

    ret_file = fopen(new_file_name, mode);
    if (!ret_file) printf("Error: Could not open file: %s\n", new_file_name);
    return ret_file;
}

void free_lists(multiVars *vars) {
    free_label_list(vars->head_label);
    free_label_apearence_list(vars->head_label_apear);
    free_data_list(vars->head_data);
    free_commands_list(vars->head_commands);
    free_extern_label_list(vars->head_extern_label);
}

void free_label_list(ptrlabel head) { FREE_LIST(ptrlabel, head) }

void free_extern_label_list(ptrExternLabel head) { FREE_LIST(ptrExternLabel, head) }

void free_label_apearence_list(ptrLabelApearence head) {
    FREE_LIST(ptrLabelApearence, head)
}

void free_data_list(ptrData head) { FREE_LIST(ptrData, head) }

void free_commands_list(ptrCommand head) { FREE_LIST(ptrCommand, head) }

/*Checks if this label exists in this file*/
bool label_exists(char *name, ptrlabel head_label) {
    LABEL_EXISTS(name, ptrlabel, head_label)
}
bool extern_label_exists(char *name,
                         ptrExternLabel head){LABEL_EXISTS(name, ptrExternLabel, head)}

ptrlabel get_label_by_name(char *name, ptrlabel head) {
    ptrlabel temp = head;

    while (temp) {
        if (!strcmp(name, temp->name)) return temp;
        temp = temp->next;
    }
    return NULL;
}

/*Checks if it is a valid label name*/
bool valid_label_name(char *name) {
    int index, len;
    /* Checks:
    the length is at most 30
    the first char is alpha
    all the others are alphanumeric, and not saved word */

    if (!name) return false;

    len = strlen(name);

    for (index = 0; index < len; ++index) {
        if (!isalnum(name[index])) return false;
    }

    return isalpha(name[0]) && len <= MAX_LABEL_LENGTH && !is_reserved_word(name);
}

char *clear_white_spaces(char *string) {
    int i, j = 0;
    char *new;

    if (!string) return NULL;

    new = (char *)calloc_with_check(strlen(string), sizeof(char));
    for (i = 0; i < strlen(string); ++i) {
        if (!isspace(string[i])) {
            new[j] = string[i];
            j++;
        }
    }
    if (strlen(new) == 0) {
        free(new);
        return NULL;
    }
    return new;
}

int get_required_operands(int op_code_index) {
    if (op_code_index == 14 || op_code_index == 15) return 0;
    if ((4 <= op_code_index && op_code_index <= 5) ||
        (7 <= op_code_index && op_code_index <= 13))
        return 1;
    if ((0 <= op_code_index && op_code_index <= 3) || op_code_index == 6) return 2;
    return -1;
}
