#include "constants.h"
#include "lists.h"
#include "utils.h"
#include "converting.h"
#include <ctype.h>

#define ZERO_ASCII_CODE 48
#define NINE_ASCII_CODE 57


/*Inserts new label to the labels list*/
responseType create_label_node(char *name, labelType type, multiVars *vars){
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
    new_node->dec_address = DC + IC + FIRST_MEMORY_CELL;
    new_node->next = NULL;

    if(!(vars->tail_label)){
        vars->head_label = new_node;
        vars->tail_label = new_node;
    }
    else{
        vars->tail_label->next = new_node;
        vars->tail_label = new_node;
    }
    
    return SUCCESS;   
}


/*Insert new node to the commands list*/
responseType create_commands_node(int code, multiVars *vars){
    ptrCommand new_node;
    
    new_node = (ptrCommand)calloc_with_check(1, sizeof(commands));
    if (!new_node)
        return SYSTEM_ERROR;

    code = (code & TEN_BITS_OF_ONE);

    new_node->code = convertDtoB(code);
    new_node->next = NULL;

    if(!(vars->tail_commands)){
        vars->head_commands = new_node;
        vars->tail_commands = new_node;
    }
    else{
        vars->tail_commands->next = new_node;
        vars->tail_commands = new_node;
    }    
    IC++;
    return SUCCESS;
}

/*Insert new node to the data list*/
responseType create_data_node(int code, multiVars *vars){
    ptrData new_node;
    
    new_node = (ptrData)calloc_with_check(1, sizeof(data));
    if (!new_node)
        return SYSTEM_ERROR;

    code = (code & TEN_BITS_OF_ONE);/*TODO : need it?*/

    new_node->code = convertDtoB(code);
    new_node->next = NULL;

    if(!(vars->tail_data))
        vars->head_data = vars->tail_data = new_node;
    else{
        vars->tail_data->next = new_node;
        vars->tail_data = new_node;
    }
    DC++;
    return SUCCESS;
}