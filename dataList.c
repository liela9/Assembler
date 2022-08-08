#include "constants.h"
#include "dataList.h"
#include "utils.h"

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


