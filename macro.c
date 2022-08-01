#include "constants.h"
#include "macro.h"

#define MACRO_MAX_LINE_NUMBER 10


/*Insert new macro to the list*/
bool insert_macro(ptr_macro head_macro, ptr_macro *macro_pointer, char *macro_id){
    ptr_macro temp;

    temp = NULL;
    /*TODO: check valid name for macro*/
    if((*macro_pointer = get_macro_by_id(head_macro, macro_id))){
        fprintf(stderr, "Can not add new macro %s, Macro already exists\n", macro_id);
        return false;
    }

    (*macro_pointer)->macro_id = (char *)malloc(sizeof(char) * MAX_LINE_LENGTH);
    strcpy((*macro_pointer)->macro_id, macro_id);
    (*macro_pointer)->macro_content = (char *)malloc(sizeof(char) * MAX_LINE_LENGTH * MACRO_MAX_LINE_NUMBER);
    (*macro_pointer)->macro_content[0] = '\0';
    (*macro_pointer)->next = NULL;

    if(!head_macro)
        head_macro = *macro_pointer;
    
    else {/*Insert the new node to the end of the list*/
        temp = head_macro;
        while (temp->next)
            temp = temp->next;
        temp->next = *macro_pointer;
    }
    return true;
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


