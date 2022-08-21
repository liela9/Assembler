#ifndef UTILS_H
#define UTILS_H

#include <ctype.h>
#include <stdarg.h>

#include "constants.h"
#include "lines.h"

#define FREE_LIST(type, head) \
    type temp;                \
    while (head) {            \
        temp = head;          \
        head = head->next;    \
        free(temp);           \
    }

#define LABEL_EXISTS(name, ptrType, head)           \
    ptrType temp = head;                            \
    while (temp) {                                  \
        if (!strcmp(name, temp->name)) return true; \
        temp = temp->next;                          \
    }                                               \
    return false;

const char registers[NUM_OF_REGISTERS][3];
const char *opcode[NUM_OF_OPCODES];
const char *reserved_words[NUM_OF_RESERVED_WORDS];

void print_user_error(multiVars *, const char *, ...);
int is_register(char *);
int is_struct(char *);
void *calloc_with_check(long, long);
void reset_array(char *);
FILE *open_file_with_extension(char *, char *, char *);
bool is_reserved_word(char *);
int find_opcode(char *);
void free_lists(multiVars *);
void free_label_list(ptrlabel);
void free_extern_label_list(ptrExternLabel);
void free_label_apearence_list(ptrLabelApearence);
void free_data_list(ptrData);
void free_commands_list(ptrCommand);
void free_extern_label_list(ptrExternLabel);
bool label_exists(char *, ptrlabel);
ptrlabel get_label_by_name(char *, ptrlabel);
bool extern_label_exists(char *, ptrExternLabel);
bool valid_label_name(char *);
char *clear_white_spaces(char *);
int get_required_operands(int);

#endif
