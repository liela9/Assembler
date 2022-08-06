#include "constants.h"
#include "free.h"


void free_lists(multiVars *vars){
    free_label_list(vars->head_label);
    free_label_apearence_list(vars->head_label_apear);
    free_data_list(vars->head_data);
    free_commands_list(vars->head_commands);
}

void free_label_list(ptr_label head){
    FREE_LIST(ptr_label, head)
}

void free_label_apearence_list(ptr_label_apearence head){
    FREE_LIST(ptr_label_apearence, head)
}

void free_data_list(ptr_data head){
    FREE_LIST(ptr_data, head)
}

void free_commands_list(ptr_commands head){
    FREE_LIST(ptr_commands, head)
}

