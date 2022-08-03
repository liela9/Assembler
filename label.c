#include "constants.h"
#include "label.h"
#include "utils.h"

#include <ctype.h>

#define ZERO_ASCII_CODE 48
#define NINE_ASCII_CODE 57



/*Inserts new label to the labels list*/
bool insert_new_label(char *name, int type, int address, multiVars *vars){
    ptr_label new_node;
    int i;
    
    new_node = NULL;


    /* TODO: check if putting \0 manualy doesn't screw up "free" */
    name[sizeof(name)-1] = '\0'; /*Remove the char ':' */


    if(label_exists(name, vars->head_label) || !valid_label_name(name)){
        printf("Error: Illegal label name: %s!\n", name);
        return false;
    }

    else{
        new_node = (ptr_label) malloc(sizeof(label));
        if(!new_node){
            printf("System Error: Memory allocation failed!\n");
            return false;
        }

        for(i=0; i<30; ++i) {
            new_node->name[i] = '\0';
        } /* Does it work?*/
        printf("%d", sizeof(new_node->name));

        /*Fills the values*/
        strcpy(new_node->name, name);
        new_node->type = type;
        new_node->dec_address = address;
        new_node->next = NULL;
        
        vars->tail_label->next = new_node;
    }
    return true;   
}


/*Checks if this label exists in this file*/
bool label_exists(char *name, ptr_label head_label){
    ptr_label temp_label;

    temp_label = head_label;

    while(temp_label){
        if(!strcmp(temp_label->name, name))
            return true;
        temp_label = temp_label->next;
    }
    return false;
}


/*Checks if it is a valid label name*/
bool valid_label_name(char *name){
	/* Checks: 
        the length is at most 30
        the first char is alpha 
        all the others are alphanumeric, and not saved word */
    int index, len;
    len = strlen(name);

    for (index = 0; index < len; ++index) {
        if (!isalnum(name[index]))
            return false;
    }

	return name[0] && len <= MAX_LABEL_LENGTH && !is_saved_words(name);
}


