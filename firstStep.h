#ifndef FIRST_STEP_H
#define FIRST_STEP_H

#define ENTRY_WORD ".entry"
#define EXTERN_WORD ".extern"

/*Functions of file 'firsStep.c'*/
response_type first_step(char *, multiVars *);
int find_opcode(char *);
void find_group( int , multiVars *);

#endif


