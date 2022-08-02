#ifndef MACRO_H
#define MACRO_H

/*Functions of file 'macro.c'*/
ptr_macro create_macro_node(char *);
ptr_macro get_macro_by_id(ptr_macro, char *);
bool macro_exists(ptr_macro, char *);
void print_macro_list(ptr_macro);
void free_macro_list(ptr_macro);

#endif
