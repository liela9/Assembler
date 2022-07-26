#include "assembler.h"
#include "lines.c"
#include "firstStep.c"




/*Free all the lists in the project*/
void free_lists(){
    free_label_list();
    free_labelApearence_list();
    free_data_table();
    free_orders_table();
}


/*Free the labels list */
void free_label_list(){
    ptr_label *temp;
    
    while (head_label) {
        temp = head_label;
        head_label = head_label->next;
        free(temp);
    }
    head_label = NULL;
}
   

/*Free the label_apearences list */
void free_labelApearence_list(){
    ptr_label_apearence *temp;
    
    while (head_label) {
        temp = head_label;
        head_label = head_label->next;
        free(temp);
    }
    head_label = NULL;
}


/*Free the data array*/
void free_data_table(){
    free(data_table);
}


/*Free the orders array*/
void free_orders_table(){
    free(orders_table);
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