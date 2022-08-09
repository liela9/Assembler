#ifndef LINES_H
#define LINES_H

#define DATA_WORD ".data"
#define STRING_WORD ".string"
#define STRUCT_WORD ".struct"

/*Functions of file 'lines.c'*/
responseType create_two_operands_command(int , char *, char *, multiVars *);
responseType create_no_operands_command(int , multiVars *);
responseType create_one_operand_command(int , char *, multiVars *);
responseType create_command_line(int , int , int, multiVars *);
responseType create_registers_line(int , int, multiVars *);
responseType create_number_line(int, multiVars *);
responseType create_unknown_line(char *, multiVars *);
responseType create_data_line( char *, char *, multiVars *);
responseType create_zero_line(multiVars *);

#endif


