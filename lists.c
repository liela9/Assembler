#include "constants.h"
#include "lists.h"
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


/*Insert new node to the commands list*/
responseType create_commands_node(unsigned long code, ptrCommand tail_commands, ptrCommand head_commands){
    ptrCommand new_node;
    
    new_node = (ptrCommand)calloc_with_check(1, sizeof(commands));
    if (!new_node)
        return SYSTEM_ERROR;

    new_node->code = code;
    new_node->next = NULL;

    if(!tail_commands)
        head_commands = tail_commands = new_node;
    else{
        tail_commands->next = new_node;
        *tail_commands = *new_node;
    }    

    return SUCCESS;
}

/*Insert new node to the data list*/
responseType create_data_node(unsigned long code, ptrData tail_data, ptrData head_data){
    ptrData new_node;
    
    new_node = (ptrData)calloc_with_check(1, sizeof(data));
    if (!new_node)
        return SYSTEM_ERROR;

    new_node->code = code;
    new_node->next = NULL;

    if(!tail_data)
        head_data = tail_data = new_node;
    else{
        tail_data->next = new_node;
        *tail_data = *new_node;
    }

    return SUCCESS;
}