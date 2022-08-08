#ifndef FREE_H
#define FREE_H

#define FREE_LIST(type, head)   type temp;\
                                while (head) {\
                                    temp = head;\
                                    head = head->next;\
                                    free(temp);\
                                }


void free_lists(multiVars *);
void free_label_list(ptrlabel );
void free_label_apearence_list(ptrLabelApearence );
void free_data_list(ptrData );
void free_commands_list(ptrCommand );


#endif


