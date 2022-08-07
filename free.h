#ifndef FREE_H
#define FREE_H

#define FREE_LIST(type, head)   type temp;\
                                while (head) {\
                                    temp = head;\
                                    head = head->next;\
                                    free(temp);\
                                }


void free_lists(multiVars *);
void free_label_list(ptr_label );
void free_label_apearence_list(ptr_label_apearence );
void free_data_list(ptr_data );
void free_commands_list(ptr_commands );


#endif


