#ifndef LABEL_H
#define LABEL_H


/*Functions of file 'label.c'*/
response_type insert_new_label(char [], int , int , multiVars *);
bool label_exists(char *, ptr_label);
bool valid_label_name(char *);

#endif
