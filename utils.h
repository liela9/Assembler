#ifndef UTILS_H
#define UTILS_H

const char registers[NUM_OF_REGISTERS][3];
const char *opcode[NUM_OF_OPCODES];
static const char *reserved_words[NUM_OF_RESERVED_WORDS];

/*Functions of file 'utils.c'*/
int is_register(char *);
int is_struct(char *);
void *calloc_with_check(long, long);
void reset_array(char *);
FILE *open_file_with_extension(char *, char *, char *);
bool is_reserved_word(char *);
int find_opcode(char *);

#endif
