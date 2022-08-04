#ifndef UTILS_H
#define UTILS_H

/*Functions of file 'utils.c'*/
int is_register(char *);
char** is_struct(char *);
bool is_saved_words(char *);
unsigned int *realloc_with_check(int , unsigned int *);
void *calloc_with_check(long, long);
void *malloc_with_check(long);
void reset_array(char *);


#endif
