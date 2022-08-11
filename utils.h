#ifndef UTILS_H
#define UTILS_H

#include <ctype.h>

#define FREE_LIST(type, head)   type temp;\
                                while (head) {\
                                    temp = head;\
                                    head = head->next;\
                                    free(temp);\
                                }

const char registers[NUM_OF_REGISTERS][3];
const char *opcode[NUM_OF_OPCODES];
const char *reserved_words[NUM_OF_RESERVED_WORDS];

/*Functions of file 'utils.c'*/
int is_register(char *);
int is_struct(char *);
void *calloc_with_check(long, long);
void reset_array(char *);
FILE *open_file_with_extension(char *, char *, char *);
bool is_reserved_word(char *);
int find_opcode(char *);
void free_lists(multiVars *);
void free_label_list(ptrlabel );
void free_label_apearence_list(ptrLabelApearence );
void free_data_list(ptrData );
void free_commands_list(ptrCommand );
bool label_exists(char *, ptrlabel);
bool valid_label_name(char *);

#endif
