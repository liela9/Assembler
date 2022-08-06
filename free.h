#ifndef FREE_H
#define FREE_H

#define FREE_LIST(type, head)   #type temp;\
                                while (head) {\
                                    temp = head;\
                                    head = head->next;\
                                    free(temp);\
                                }


#endif


