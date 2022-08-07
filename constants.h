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

const char base32[BASE_LENGTH];
const char registers[NUM_OF_REGISTERS][2];
const char opcode[NUM_OF_OPCODES][3];

int IC; /*Instruction counter*/
int DC;/*Data counter*/


/*Uses for the labels table*/
enum {ENTRY, EXTERNAL, DATA};
typedef enum {false, true} bool;
typedef enum {SUCCESS, SYSTEM_ERROR, USER_ERROR} response_type;


/*
A linked list of macros.
*/
typedef struct macro *ptr_macro;
typedef struct macro{
    
    char macro_id[MAX_LABEL_LENGTH]; /*Name of the macro*/
    char *macro_content; /*Content of the macro*/
    ptr_macro next;
}macro;



/*
A linked list of data code lines.
*/
typedef struct data *ptr_data;
typedef struct data{
    
    unsigned long code;
    ptr_data next;
}data;



/*
A linked list of commands code lines.
*/
typedef struct commands *ptr_commands;
typedef struct commands{
    
    unsigned long code;
    ptr_commands next;
}commands;


/*
A linked list of labels.
*/
typedef struct label *ptr_label;
typedef struct label{
    
    char name[MAX_LABEL_LENGTH];/*Label name*/
    int type; /*Options: 0 == ENTRY, 1 == EXTERNAL, 2 == DATA*/
    int dec_address; /*Decimal address*/
    ptr_label next;
}label;


/*
A linked list of unknown labels in the commands list.
Assists to complete the commands list in second step.
*/
typedef struct labelApearance *ptr_label_apearence;
typedef struct labelApearance{
    
    char name[MAX_LABEL_LENGTH];/*Label name*/
    int index_in_commands_list;
    /*Contains the index of unknown label line at the first step*/
    ptr_label_apearence next;
}labelApearance;


/*
A structure of multiple types of variables.
Assists to save and move variables from first step to second step.
*/
typedef struct multiVars{
    
    ptr_label head_label;
    ptr_label tail_label;
    ptr_label_apearence head_label_apear;
    ptr_label_apearence tail_label_apear;
    ptr_data head_data;
    ptr_commands head_commands;
}multiVars;


#endif 

