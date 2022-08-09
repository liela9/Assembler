#ifndef consts_H
#define consts_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BASE_LENGTH 32
#define NUM_OF_REGISTERS 8
#define NUM_OF_OPCODES 16
#define NUM_OF_RESERVED_WORDS 7
#define MAX_LINE_LENGTH 81
#define MAX_LABEL_LENGTH 30
#define AM_EXTENSION ".am"
#define FIRST_MEMORY_CELL 100

int IC; /*Instruction counter*/
int DC;/*Data counter*/


/*Uses for the labels table*/
typedef enum {CODE, ENTRY, EXTERNAL, DATA} labelType;
typedef enum {false, true} bool;
typedef enum {SUCCESS, SYSTEM_ERROR, USER_ERROR} responseType;


/*
A linked list of macros.
*/
typedef struct macro *ptrMacro;
typedef struct macro{
    
    char macro_id[MAX_LABEL_LENGTH]; /*Name of the macro*/
    char *macro_content; /*Content of the macro*/
    ptrMacro next;
}macro;



/*
A linked list of data code lines.
*/
typedef struct data *ptrData;
typedef struct data{
    
    unsigned long code;
    ptrData next;
}data;



/*
A linked list of commands code lines.
*/
typedef struct commands *ptrCommand;
typedef struct commands{
    
    unsigned long code;
    ptrCommand next;
}commands;


/*
A linked list of labels.
*/
typedef struct label *ptrlabel;
typedef struct label{
    
    char name[MAX_LABEL_LENGTH];/*Label name*/
    labelType type;
    int dec_address; /*Decimal address*/
    ptrlabel next;
}label;


/*
A linked list of unknown labels in the commands list.
Assists to complete the commands list in second step.
*/
typedef struct labelApearance *ptrLabelApearence;
typedef struct labelApearance{
    
    char name[MAX_LABEL_LENGTH];/*Label name*/
    int index_in_commands_list;
    /*Contains the index of unknown label line at the first step*/
    ptrLabelApearence next;
}labelApearance;


/*
A structure of multiple types of variables.
Assists to save and move variables from first step to second step.
*/
typedef struct multiVars{
    
    ptrlabel head_label;
    ptrlabel tail_label;
    ptrLabelApearence head_label_apear;
    ptrLabelApearence tail_label_apear;
    ptrData head_data;
    ptrData tail_data;
    ptrCommand head_commands;
    ptrCommand tail_commands;
}multiVars;


typedef struct struct_access{
    
    char label_name[MAX_LABEL_LENGTH];
    int index;
}struct_access;

#endif 

