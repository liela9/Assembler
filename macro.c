#include "macro.h"

/*Insert new macro to the list*/
ptrMacro create_macro_node(char *macro_id, ptrMacro *head_macro, ptrMacro *tail_macro) {
    ptrMacro new_node;

    new_node = (ptrMacro)calloc_with_check(1, sizeof(macro));
    if (!new_node) return NULL;

    new_node->macro_content =
        (char *)calloc_with_check(MAX_LINE_LENGTH * MACRO_MAX_LINE_NUMBER, sizeof(char));
    if (!new_node->macro_content) {
        free(new_node);
        return NULL;
    }

    strcpy(new_node->macro_id, macro_id);
    new_node->next = NULL;

    if (!(*tail_macro)) {
        *head_macro = new_node;
        *tail_macro = new_node;
    } else {
        (*tail_macro)->next = new_node;
        *tail_macro = new_node;
    }

    return new_node;
}

/*Finds macro by it's id and return it's pointer*/
ptrMacro get_macro_by_id(ptrMacro head_macro, char *macro_id) {
    ptrMacro ptr = head_macro;

    while (ptr) {
        if (!strcmp(ptr->macro_id, macro_id)) {
            return ptr;
        }
        ptr = ptr->next;
    }
    return NULL;
}

bool macro_exists(ptrMacro head_macro, char *macro_id) {
    return (get_macro_by_id(head_macro, macro_id) != NULL);
}

/*Free the macro's list*/
void free_macro_list(ptrMacro head_macro) {
    ptrMacro temp;

    while (head_macro) {
        temp = head_macro;
        head_macro = head_macro->next;
        free(temp->macro_content);
        free(temp);
    }
}