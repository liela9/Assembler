#ifndef MACRO_H
#define MACRO_H

#define MACRO_MAX_LINE_NUMBER 10
#define MACRO_WORD "macro"
#define ENDMACRO_WORD "endmacro"

/*Functions of file 'macro.c'*/
ptr_macro create_macro_node(char *);
ptr_macro get_macro_by_id(ptr_macro, char *);
bool macro_exists(ptr_macro, char *);

#endif
