#include "main.c"
#include "constants.c"

#define ZERO_ASCII_CODE 48
#define NINE_ASCII_CODE 57



/*Inserts new label to the labels list*/
bool insert_new_label(char *name, int type, int address, ptr_label head_label, ptr_label tail_label){
    ptr_label temp_label;
    bool there_is_error_flag;

    there_is_error_flag = false;

    temp_label = (ptr_label) malloc(sizeof(label));
    if(!temp_label){
        printf("System Error: Memory allocation failed!\n");
        exit(0);
    }

    name[sizeof(name)-1] = '\0'; /*Remove the char ':' */

    if(label_exists(name, &head_label) || !valid_label_name(name)){
        printf("Error: %s Illegal label name!\n", name);
        there_is_error_flag = true;
    }

    else{
        /*Fills the values*/
        strcpy(temp_label->name, name);
        strcpy(temp_label->type, type);
        temp_label->dec_address = address;
        temp_label->next = NULL;
        
        tail_label->next = temp_label;
        tail_label = temp_label;
    }
    
    free(temp_label);
    return there_is_error_flag;   
}


/*Checks if this label exists in this file*/
bool label_exists(char *name, ptr_label head_label){
    ptr_label temp_label;

    temp_label = head_label;

    while(temp_label){
        if(strcmp(temp_label->name, name))
            return true;
        temp_label = temp_label->next;
    }

    free(temp_label);
    return false;
}


/*Checks if it is a valid label name*/
bool valid_label_name(char *name){
	/* Checks: 
        the length is at most 30
        the first char is alpha 
        all the others are alphanumeric, and not saved word */
	return name[0] && strlen(name) <= MAX_LABEL_LENGTH && isalpha(name[0]) && alphanumeric_str(name + 1) &&
	       !is_saved_words(name);
}

