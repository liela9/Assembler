#include "assembler.h"

#define MACRO_MAX_LINE_NUMBER 10


/* macro linked list head pointer */
static ptr_macro head_macro = NULL;


/*Add new macro to the list*/
ptr_macro add_macro(char *macro_id){
    ptr_macro new;

    new = NULL;

    /*TODO: check valid name for macro*/
    if((new = get_macro_by_id(macro_id))){
        fprintf(stderr, "Cannot add new macro %s, macro already exist\n", macro_id);
        return NULL;
    }

    new = malloc(sizeof(macro));
    if (!new){
        fprintf(stderr,"Could not allocate memory ");
        exit(0);
    }

    new->macro_id = malloc(sizeof(char) * MAX_LINE_LENGTH);
    strcpy(new->macro_id,macro_id);

    new->macro_content = (char *)malloc(sizeof(char) * MAX_LINE_LENGTH * MACRO_MAX_LINE_NUMBER);
    new->macro_content[0] = '\0';
    new->next = NULL;

    if(!head_macro)
        head_macro = new;
    
    else {
        ptr_macro ptr = head_macro;
        while (ptr->next){
            ptr = ptr->next;
        }
        ptr->next = new;
    }
    return new;
}

/*Finds macro by it's id and return it's pointer*/
ptr_macro get_macro_by_id(char *macro_id){
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
void print_macro_list() {
    ptr_macro ptr;

    for (ptr = head_macro; ptr != NULL; ptr = ptr->next)
        printf("macro id: %s\nmacro content: %s \n", ptr->macro_id, ptr->macro_content);
}


/*Free the macro list*/
void free_macro_list() {
    ptr_macro it = head_macro, temp;

    while (it != NULL) {
        temp = it;
        it = it->next;
        free(temp->macro_id);
        free(temp->macro_content);
        free(temp);
    }
    head_macro = NULL;
}

