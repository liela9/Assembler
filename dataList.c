#include "constants.h"
#include "dataList.h"
#include "utils.h"

/*Insert new node to the data list*/
ptr_data create_data_node(unsigned long code){
    ptr_data new_node;
    
    new_node = (ptr_data)calloc_with_check(1, sizeof(data));
    if (!new_node)
        return NULL;

    new_node->code = code;
    new_node->next = NULL;

    return new_node;
}


