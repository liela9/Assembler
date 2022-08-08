#ifndef MACRO_H
#define MACRO_H

#define MACRO_MAX_LINE_NUMBER 10
#define MACRO_WORD "macro"
#define ENDMACRO_WORD "endmacro"

/*Functions of file 'macro.c'*/
ptrMacro create_macro_node(char *);
ptrMacro get_macro_by_id(ptrMacro, char *);
bool macro_exists(ptrMacro, char *);
void free_macro_list(ptrMacro);

#endif
