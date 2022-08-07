#ifndef UTILS_H
#define UTILS_H

/*Functions of file 'utils.c'*/
int is_register(char *);
char** is_struct(char *);
void *calloc_with_check(long, long);
void reset_array(char *);
FILE *open_file_with_extension(char *, char *, char *);
bool is_reserved_word(char *);

#endif
