#ifndef LINES_H
#define LINES_H

/*Functions of file 'lines.c'*/
int insert_order(int , unsigned long , char *, char *, ptr_label, ptr_label_apearence);
int create_order_line(int , unsigned long , long , long , unsigned int *);
int create_registers_line(int , int , int , unsigned int *);
int create_value_line(char *, int , unsigned int *);
int create_index_line(int , int , unsigned int *);
int create_unknown_line(int , unsigned int *, char *, ptr_label_apearence );
int create_data_line(int , char *, unsigned int *, char *);
void create_zero_line(unsigned int *, int DC);

#endif
