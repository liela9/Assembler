#ifndef consts_H
#define consts_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BASE_LENGTH 32
#define NUM_OF_REGISTERS 8
#define OPCODE_LENGTH 16
#define NUM_OF_SAVED_WORDS 7
#define MAX_LINE_LENGTH 81
#define MAX_LABEL_LENGTH 30
#define AM_FILE ".am"

const char base32[BASE_LENGTH];
const char registers[NUM_OF_REGISTERS][2];

const char opcode[OPCODE_LENGTH][3]; 

/*Used for checking saved words*/
const char* saved_words[NUM_OF_SAVED_WORDS];



/*Uses for the labels table*/
enum {ENTRY, EXTERNAL, DATA};
typedef enum {false, true} bool;


/*
A linked list of macros.
*/
typedef struct macro *ptr_macro;
typedef struct macro{
    char *macro_id; /*Number of the macro*/
    char *macro_content; /*Content of the macro*/

    ptr_macro next;
}macro;


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
A linked list of unknown labels in the orders_table.
Assists to complete the orders_table in second step.
*/
typedef struct labelApearance *ptr_label_apearence;
typedef struct labelApearance{
    char name[MAX_LABEL_LENGTH];/*Label name*/
    int index_in_orders_table;
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
    unsigned int *orders_table;
    unsigned int *data_table;
    int IC;/*Instruction counter*/
    int DC;/*Data counter*/

    bool there_is_error_flag;

}multiVars;



#endif 
