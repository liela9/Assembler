#include "main.c"


#define ZERO_ASCII_CODE 48
#define NINE_ASCII_CODE 57



/*Inserts new label to the label list*/
int insert_new_label(char *name, int type, int address){
    ptr_label lab;

    lab = (ptr_label) malloc(sizeof(label));
    if(!lab){
        printf("Memory allocation failed\n");
        exit(0);
    }

    
    name[sizeof(name)-1] = '\0'; /*Remove the char ':' */

    if(label_exists(name)){
        printf("Error: %s label already exists!\n", name);
        there_is_error = 1;
    }
    
    if(saved_words(name)){
        printf("Error: label name (%s) is not possible\n", name);
        return 0;
    }

    else{
        strcpy(lab->name, name);
        strcpy(lab->type, type);
        lab->dec_address = address;
        lab->next = NULL;
        
        tail_label->next = lab;
        tail_label = lab;
    }
    
    
    return address;   
}


/*Checks if this label exists in this file*/
int label_exists(char *name){
    ptr_label local_label;

    local_label = head_label;

    while(local_label){
        if(strcmp(local_label->name, name))
            return 1;
        local_label = local_label->next;
    }
    return 0;
}

int saved_words(char *name){ 
    int i;
    
    for(i = 0; i < NUM_OF_REGISTERS; i++){
        if(!strcmp(name, registers[i]))
            return 1;
    }

    for(i = 0; i < OPCODE_LENGTH; i++){
        if(!strcmp(name, opcode[i]))
            return 1;
    }

    for(i = 0; i < NUM_OF_GUIDANCE_NAME; i++){
        if(!strcmp(name, guidance[i]))
            return 1;
    }

    return 0;
}


/*Fills the values for specific row*/
int *fill_values(FILE *f, long int pos){
    char token[];
    int c, *val;

    fseek(f, pos, SEEK_SET);
    strtok(fgets(token, ROW_LENGTH, f), ' \t');
    
    
    while(token != "\n"){
        L++;
        if((ZERO_ASCII_CODE <= token && token <= NINE_ASCII_CODE) || token[0] == '-' || token[0] == '+'){ /*If thats a number*/
            *val = decimal_to_binary(token);
            *val++;
        }
        else{ /*If thats a string*/
            /*Remove the "" of the string*/
            token[strlen(token)-1] = '\0';
            *token++;

            /*Read char by char*/
            while(*token != '\0'){
                c = *token;
                *val = decimal_to_binary(c); 
                *val++;
                *token++;
            }

        }  
        token = strtok(NULL, ', \t');
    }
    return 
}