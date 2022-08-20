#include "lists.h"

#define ZERO_ASCII_CODE 48
#define NINE_ASCII_CODE 57

/*Inserts new label to the labels list*/
responseType create_label_node(char *name, labelType type, multiVars *vars) {
    ptrlabel new_node;

    if (label_exists(name, vars->head_label) || !valid_label_name(name)) {
        /* TODO: check if need to remove the label which alread exists */
        printf("User Error: in %s.am line %d : '%s' is illegal label name\n",
               vars->file_name, vars->line_counter, name);
        return USER_ERROR;
    }

    new_node = (ptrlabel)calloc_with_check(1, sizeof(label));
    if (!new_node) return SYSTEM_ERROR;

    /*Fills the values*/
    if (type == EXTERNAL)
        new_node->dec_address = -1; /*Dummy value*/
    else
        new_node->dec_address = DC + IC + FIRST_MEMORY_CELL;
    strcpy(new_node->name, name);
    new_node->type = type;
    new_node->next = NULL;

    if (!(vars->tail_label)) {
        vars->head_label = new_node;
        vars->tail_label = new_node;
    } else {
        vars->tail_label->next = new_node;
        vars->tail_label = new_node;
    }

    return SUCCESS;
}

/*Inserts new external label to the list*/
responseType create_extern_label_node(char *name, multiVars *vars) {
    ptrExternLabel new_node;

    new_node = (ptrExternLabel)calloc_with_check(1, sizeof(externLabel));
    if (!new_node) return SYSTEM_ERROR;

    /*Fills the value*/
    strcpy(new_node->name, name);
    new_node->next = NULL;

    if (!(vars->tail_extern_label)) {
        vars->head_extern_label = new_node;
        vars->tail_extern_label = new_node;
    } else {
        vars->tail_extern_label->next = new_node;
        vars->tail_extern_label = new_node;
    }

    return SUCCESS;
}

/*Insert new node to the commands list*/
responseType create_commands_node(int code, multiVars *vars) {
    ptrCommand new_node;

    new_node = (ptrCommand)calloc_with_check(1, sizeof(commands));
    if (!new_node) return SYSTEM_ERROR;

    code = (code & TEN_BITS_OF_ONE);

    new_node->code = convertDtoB(code);
    new_node->next = NULL;

    if (!(vars->tail_commands)) {
        vars->head_commands = new_node;
        vars->tail_commands = new_node;
    } else {
        vars->tail_commands->next = new_node;
        vars->tail_commands = new_node;
    }
    IC++;
    return SUCCESS;
}

ptrlabel get_label_by_name(char *name, ptrlabel head) {
    ptrlabel temp = head;

    while (temp) {
        if (!strcmp(name, temp->name)) return temp;
        temp = temp->next;
    }
    return NULL;
}

/*Insert new node to the data list*/
responseType create_data_node(int code, multiVars *vars) {
    ptrData new_node;

    new_node = (ptrData)calloc_with_check(1, sizeof(data));
    if (!new_node) return SYSTEM_ERROR;

    code = (code & TEN_BITS_OF_ONE); /*TODO : need it?*/

    new_node->code = convertDtoB(code);
    new_node->next = NULL;

    if (!(vars->tail_data))
        vars->head_data = vars->tail_data = new_node;
    else {
        vars->tail_data->next = new_node;
        vars->tail_data = new_node;
    }
    DC++;
    return SUCCESS;
}
