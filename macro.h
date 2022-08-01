#ifndef MACRO_H
#define MACRO_H

/*Functions of file 'macro.c'*/
bool insert_macro(ptr_macro, ptr_macro *, char *);
ptr_macro get_macro_by_id(ptr_macro, char *);
void print_macro_list(ptr_macro);
void free_macro_list(ptr_macro);

#endif
