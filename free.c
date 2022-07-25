#include "assembler.h"


/*Free all linked lists in the project*/
void free_linked_lists(){
    free_label_list();
    free_labelApearence_list();
    free_data_table();
    free_orders_table();
}


/*Free the list named "macro"*/
void free_macro_list() {
    ptr_macro it = head_macro, temp;

    while (it != NULL) {
        temp = it;
        it = it->next;
        free(temp->macro_id);
        free(temp->macro_content);
        free(temp);
    }
    head_macro = NULL;
}

