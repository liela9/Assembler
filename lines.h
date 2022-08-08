#ifndef LINES_H
#define LINES_H

#define DATA_WORD ".data"
#define STRING_WORD ".string"
#define STRUCT_WORD ".struct"

/*Functions of file 'lines.c'*/
responseType create_two_operands_command(unsigned long , char *, char *, multiVars *);
responseType create_no_operands_command(unsigned long , multiVars *);
responseType create_one_operand_command(unsigned long , char *, multiVars *)
responseType create_command_line(unsigned long , long , long, ptrCommand, ptrCommand);
responseType create_registers_line(int , int, ptrCommand, ptrCommand);
responseType create_number_line(int, ptrCommand, ptrCommand);
responseType create_unknown_line(char *, ptrLabelApearence, ptrCommand, ptrCommand);
responseType create_data_line( char *, char *, ptrData, ptrData);
responseType create_zero_line(ptrData, ptrData);

#endif


