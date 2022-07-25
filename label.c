#include "main.c"


#define ZERO_ASCII_CODE 48
#define NINE_ASCII_CODE 57



/*Inserts new label to the label list*/
int insert_new_label(char *name, int type, int address, ptr_label head_label, ptr_label tail_label){
    ptr_label temp_label;

    temp_label = (ptr_label) malloc(sizeof(label));
    if(!temp_label){
        printf("Memory allocation failed\n");
        exit(0);
    }

    name[sizeof(name)-1] = '\0'; /*Remove the char ':' */

    if(label_exists(name, &head_label) || !valid_label_name(name)){
        printf("Error: %s Illegal label name!\n", name);
        
    }
    
    if(saved_words(name)){
        printf("Error: label name (%s) is not possible\n", name);
        return 0;
    }

    else{
        strcpy(temp_label->name, name);
        strcpy(temp_label->type, type);
        temp_label->dec_address = address;
        temp_label->next = NULL;
        
        tail_label->next = temp_label;
        tail_label = temp_label;
    }
    
    return address;   
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
    return false;
}


/*Checks if it is a valid label name*/
bool valid_label_name(char *name){
	/* Checks: length, first char is alpha and all the others are alphanumeric, and not saved word */
	return name[0] && strlen(name) <= 31 && isalpha(name[0]) && alphanumeric_str(name + 1) &&
	       !saved_words(name);
}


/*Checks if it is a saved word of the system*/
bool saved_words(char *name){ 
    int i;
    
    for(i = 0; i < NUM_OF_REGISTERS; i++){
        if(!strcmp(name, registers[i]))
            return true;
    }

    for(i = 0; i < OPCODE_LENGTH; i++){
        if(!strcmp(name, opcode[i]))
            return true;
    }

    for(i = 0; i < NUM_OF_GUIDANCE_NAME; i++){
        if(!strcmp(name, guidance[i]))
            return true;
    }

    return false;
}

/*checks for every char in the string if it is non alphanumeric char*/
bool alphanumeric_str(char *string){
	int i;

	for(i = 0; string[i]; i++){
		if (!isalpha(string[i]) && !isdigit(string[i]))
            return false;
	}
	return true;
}
