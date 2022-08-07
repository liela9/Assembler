#include "constants.h"
#include "commandsList.h"
#include "utils.h"

/*Insert new node to the commands list*/
ptr_commands create_commands_node(unsigned long code){
    ptr_commands new_node;
    
    new_node = (ptr_commands)calloc_with_check(1, sizeof(commands));
    if (!new_node)
        return NULL;

    new_node->code = code;
    new_node->next = NULL;

    return new_node;
}