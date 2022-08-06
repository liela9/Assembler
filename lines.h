#ifndef LINES_H
#define LINES_H

#define DATA_WORD ".data"
#define STRING_WORD ".string"
#define STRUCT_WORD ".struct"

/*Functions of file 'lines.c'*/
void insert_command( unsigned long , char *, char *, multiVars *);
void create_command_line(unsigned long , long , long);
void create_registers_line(int , int);
void create_number_line(int);
void create_unknown_line(char *, ptr_label_apearence);
response_type create_data_line( char *, char *);
void create_zero_line();

#endif


