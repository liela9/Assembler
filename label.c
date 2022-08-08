#include "constants.h"
#include "label.h"
#include "utils.h"

#include <ctype.h>

#define ZERO_ASCII_CODE 48
#define NINE_ASCII_CODE 57



/*Inserts new label to the labels list*/
responseType create_label_node(char *name, labelType type, int address, multiVars *vars){
    ptrlabel new_node;    

    if(label_exists(name, vars->head_label) || !valid_label_name(name)){
        /* TODO: check if need to remove the label which alread exists */
        printf("User Error: Illegal label name: %s!\n", name);
        return USER_ERROR;
    }

    new_node = (ptrlabel) calloc_with_check(1, sizeof(label));
    if(!new_node)
        return SYSTEM_ERROR;
    
    /*Fills the values*/
    strcpy(new_node->name, name);
    new_node->type = type;
    new_node->dec_address = address;
    new_node->next = NULL;

    if(!(vars->head_label)){
        vars->head_label = new_node;
        vars->tail_label = new_node;
    }
    
    vars->tail_label->next = new_node;
    *vars->tail_label = *new_node;
    
    return SUCCESS;   
}


/*Checks if this label exists in this file*/
bool label_exists(char *name, ptrlabel head_label){
    ptrlabel temp_label;

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

	return name[0] && len <= MAX_LABEL_LENGTH && !is_reserved_word(name);
}


