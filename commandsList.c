#include "constants.h"
#include "commandsList.h"


/*Insert new macro to the list*/
ptr_commands create_commands_node(unsigned long code){
    ptr_commands new_node;
    new_node = NULL;
    
    if (!(new_node = (ptr_commands)malloc_with_check(sizeof(commands))))
        return NULL;

    strcpy(new_node->code, code);
    new_node->next = NULL;

    return new_node;
}