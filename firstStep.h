#ifndef FIRST_STEP_H
#define FIRST_STEP_H

#define ENTRY_WORD ".entry"
#define EXTERN_WORD ".extern"

/*Functions of file 'firsStep.c'*/
responseType first_step(char *, multiVars *vrs);
responseType handle_line(char *, char *, char *, int , multiVars *);
responseType extern_entry_validate(char *, int , multiVars *, labelType , char *);
responseType insert_data_label(char* , int , multiVars *);
responseType insert_string_line(char* , int , char *, char* , multiVars *);
responseType insert_struct_line(char* , int , char *, char* , multiVars *);
responseType insert_opcode_line(char* , int , char *, char* , multiVars *);
responseType insert_data_line(char* , int , char *, char* , multiVars *);


#endif


