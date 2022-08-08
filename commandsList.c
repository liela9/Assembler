#include "constants.h"
#include "commandsList.h"
#include "utils.h"

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