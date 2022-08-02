#ifndef LINES_H
#define LINES_H

/*Functions of file 'lines.c'*/
void insert_command( unsigned long , char *, char *, multiVars *);
void create_command_line(unsigned long , long , long , unsigned int *);
void create_registers_line(int , int , unsigned int *);
void create_number_line(int , unsigned int *);
void create_unknown_line(unsigned int *, char *, ptr_label_apearence );
void create_data_line( char *, unsigned int *, char *);
void create_zero_line(unsigned int *);

#endif


