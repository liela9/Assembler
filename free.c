#include "constants.h"
#include "free.h"


/*
#define FREE(type, head)    type temp;\
                            while (head) {\
                                temp = head;\
                                head = head->next;\
                                free(temp);\
                            }
                  


Free all the lists in the project
void free_lists(multiVars *vars){

    FREE(ptr_label, vars->head_label)
    FREE(ptr_label_apearence, vars->head_label_apear)
    free(vars->data_table);
    free(vars->commands_table);
}
*/

/*
void free_label_list(ptr_label head){
    ptr_label temp;

    while (head) {
        temp = head;
        head = head->next;
        free(temp);
    }
}
*/   

void free_lists(multiVars *vars){

    free_label_list(vars->head_label);
    free_labelApearence_list(vars->head_label_apear);
    
    free(vars->data_table);
    free(vars->commands_table);
}


void free_label_list(ptr_label head){
    ptr_label temp;

    while (head) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

void free_labelApearence_list(ptr_label_apearence head){
    ptr_label_apearence temp;

    while (head) {
        temp = head;
        head = head->next;
        free(temp);
    }
}



