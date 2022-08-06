#include "constants.h"
#include "dataList.h"


/*Insert new macro to the list*/
ptr_data create_data_node(unsigned long code){
    ptr_data new_node;
    new_node = NULL;
    
    if (!(new_node = (ptr_data)malloc_with_check(sizeof(data))))
        return NULL;

    strcpy(new_node->code, code);
    new_node->next = NULL;

    return new_node;
}


