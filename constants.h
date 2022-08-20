#ifndef consts_H
#define consts_H

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* constant numbers */
#define NUM_OF_REGISTERS 8
#define NUM_OF_OPCODES 16
#define NUM_OF_RESERVED_WORDS 7
#define MAX_LINE_LENGTH 81
#define MAX_LABEL_LENGTH 30
#define FIRST_MEMORY_CELL 100

/* reserved words */
#define AM_EXTENSION ".am"
#define ENTRY_WORD ".entry"
#define EXTERN_WORD ".extern"

#define CHECK_RESPONSE(result) \
    if ((response = result) != SUCCESS) return response;

typedef enum { false, true } bool;

typedef enum { SUCCESS, SYSTEM_ERROR, USER_ERROR } responseType;

int IC; /* instruction counter*/
int DC; /* data counter*/

/* used for construction of labels table */
typedef enum { CODE, ENTRY, EXTERNAL, DATA, STRING, STRUCT } labelType;

/* linked list of macros */
typedef struct macro *ptrMacro;
typedef struct macro {
    char macro_id[MAX_LABEL_LENGTH]; /* macro name*/
    char *macro_content;
    ptrMacro next;
} macro;

/* linked list of data code lines */
typedef struct data *ptrData;
typedef struct data {
    unsigned long code;
    ptrData next;
} data;

/* linked list of commands code lines */
typedef struct commands *ptrCommand;
typedef struct commands {
    unsigned long code;
    ptrCommand next;
} commands;

/* linked list of labels */
typedef struct label *ptrlabel;
typedef struct label {
    char name[MAX_LABEL_LENGTH];
    labelType type;
    int dec_address; /* decimal address */
    ptrlabel next;
} label;

/*
linked list of unknown labels in the commands list
used to construct the commands list in second pass
*/
typedef struct labelApearance *ptrLabelApearence;
typedef struct labelApearance {
    char name[MAX_LABEL_LENGTH];
    /* contains the index of unknown label line, found at the first pass */
    int index_in_commands_list;
    int apeared_with_point;
    bool is_struct;
    ptrLabelApearence next;
} labelApearance;

/* linked list of external labels */
typedef struct externLabel *ptrExternLabel;
typedef struct externLabel {
    char name[MAX_LABEL_LENGTH];
    ptrExternLabel next;
} externLabel;

/*
context (state) variables
used to transfer state information between functions and steps
*/
typedef struct multiVars {
    ptrlabel head_label;
    ptrlabel tail_label;
    ptrLabelApearence head_label_apear;
    ptrLabelApearence tail_label_apear;
    ptrData head_data;
    ptrData tail_data;
    ptrCommand head_commands;
    ptrCommand tail_commands;
    ptrExternLabel head_extern_label;
    ptrExternLabel tail_extern_label;
    char file_name[FILENAME_MAX]; /* current file being processed */
    int line_counter;             /* current line being processed */
} multiVars;

#endif /* consts_H */
