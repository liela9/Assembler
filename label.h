#ifndef LABEL_H
#define LABEL_H


/*Functions of file 'label.c'*/
response_type create_label_node(char [], int , int , multiVars *);
bool label_exists(char *, ptr_label);
bool valid_label_name(char *);

#endif
