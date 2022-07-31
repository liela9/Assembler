#include "constants.h"
#include "free.h"


/*Free all the lists in the project*/
void free_lists(multiVars *vars){
    free_label_list(&vars);
    free_labelApearence_list(&vars);
    free_data_table(&vars);
    free_orders_table(&vars);
}


/*Free the labels list */
void free_label_list(multiVars *vars){
    ptr_label *temp;
    
    while (vars->head_label) {
        temp = vars->head_label;
        vars->head_label = vars->head_label->next;
        free(temp);
    }
    vars->head_label = NULL;
}
   

/*Free the label_apearences list */
void free_labelApearence_list(multiVars *vars){
    ptr_label_apearence *temp;
    
    while (vars->head_label) {
        temp = vars->head_label;
        vars->head_label = vars->head_label->next;
        free(temp);
    }
    vars->head_label = NULL;
}


/*Free the data array*/
void free_data_table(multiVars *vars){
    free(vars->data_table);
}


/*Free the orders array*/
void free_orders_table(multiVars *vars){
    free(vars->orders_table);
}













/*


void free_list(char *type, void *head) {
    void *temp;

    
    while (head != NULL) {
        temp = head;
        head = head->next;
        
        free(temp);
    }
    head = NULL;
    
}


*/
