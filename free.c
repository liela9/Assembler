#include "constants.h"
#include "free.h"


void free_lists(multiVars *vars){
    free_label_list(vars->head_label);
    free_label_apearence_list(vars->head_label_apear);
    free_data_list(vars->head_data);
    free_commands_list(vars->head_commands);
}

void free_label_list(ptrlabel head){
    FREE_LIST(ptrlabel, head)
}

void free_label_apearence_list(ptrLabelApearence head){
    FREE_LIST(ptrLabelApearence, head)
}

void free_data_list(ptrData head){
    FREE_LIST(ptrData, head)
}

void free_commands_list(ptrCommand head){
    FREE_LIST(ptrCommand, head)
}

