#ifndef LABEL_H
#define LABEL_H


/*Functions of file 'label.c'*/
responseType create_label_node(char [], int , int , multiVars *);
bool label_exists(char *, ptrlabel);
bool valid_label_name(char *);

#endif
