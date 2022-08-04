#ifndef UTILS_H
#define UTILS_H

/*Functions of file 'utils.c'*/
int is_register(char *);
char** is_struct(char *);
unsigned int *realloc_check(int , unsigned int *);
bool is_saved_words(char *);
void *calloc_with_check(long, long);
void *malloc_with_check(long);
void reset_array(char *);


#endif
