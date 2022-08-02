#include "constants.h"
#include "macro.h"

#define MACRO_MAX_LINE_NUMBER 10


/*Insert new macro to the list*/
ptr_macro create_macro_node(char *macro_id){
    ptr_macro new_node;
    new_node = NULL;
    
    new_node = (ptr_macro) malloc(sizeof(macro));
    if (!new_node)
    { 
        /* TODO: memory allocation error message in MACRO */
        printf("System Error: Memory allocation failed\n");
        return NULL;
    }


    new_node->macro_id = (char *)malloc(sizeof(macro_id));
    if (!new_node->macro_id)
    { 
        printf("System Error: Memory allocation failed\n");
        free(new_node);
        return NULL;
    }

    new_node->macro_content = (char *)malloc(sizeof(char) * MAX_LINE_LENGTH * MACRO_MAX_LINE_NUMBER);
    if (!new_node->macro_content)
    { 
        printf("System Error: Memory allocation failed\n");
        free(new_node->macro_id);
        free(new_node);
        return NULL;
    }
    strcpy(new_node->macro_id, macro_id);
    new_node->macro_content[0] = '\0';
    new_node->next = NULL;
    return new_node;
}

/*Finds macro by it's id and return it's pointer*/
ptr_macro get_macro_by_id(ptr_macro head_macro, char *macro_id){
    ptr_macro ptr;
    ptr = head_macro;

    while (ptr){
        if (!strcmp(ptr->macro_id, macro_id)){
            return ptr;
        }
        ptr = ptr->next;
    }
    return NULL;
}


bool macro_exists(ptr_macro head_macro, char *macro_id) {
    return (get_macro_by_id(head_macro, macro_id) != NULL);
}

/*Prints the macro list */
void print_macro_list(ptr_macro head_macro) {
    ptr_macro ptr;

    for (ptr = head_macro; ptr != NULL; ptr = ptr->next)
        printf("Macro id: %s\nMacro content: %s \n", ptr->macro_id, ptr->macro_content);
}


/*Free the macro's list*/
void free_macro_list(ptr_macro head_macro) {
    ptr_macro temp;

    while (head_macro) {
        temp = head_macro;
        head_macro = head_macro->next;
        free(temp->macro_content);
        free(temp->macro_id);
        free(temp);
    }
}


