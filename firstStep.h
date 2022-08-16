#ifndef FIRST_STEP_H
#define FIRST_STEP_H



/*Functions of file 'firsStep.c'*/
responseType first_step(multiVars *);
responseType handle_line(char *, char * , multiVars *);
responseType extern_entry_validate(labelType, multiVars *, char *);
responseType insert_data_label(char* , int, multiVars *);
responseType insert_string_line(char *, char* , multiVars *);
responseType insert_struct_line(char *, char* , multiVars *);
responseType insert_opcode_line(char *, char* , multiVars *);
responseType insert_data_line(char *, char* , multiVars *);


#endif


