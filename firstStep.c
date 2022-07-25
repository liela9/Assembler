#include "assembler.h"
#include "constants.c"


static ptr_label head_label;
static ptr_label tail_label;
static ptr_label_apearence label_apear_head;

/*A table of binary machine code for data*/
static unsigned int *data_table;


bool first_step(char *file_name){
    FILE *f;
    char *row_content, *first_word, *second_word;
    int op_code_index, IC, DC;
    bool there_is_error;

    there_is_error = 0;

    strcat(file_name, AM_FILE);/*Add the extention ".am" to the name of the file*/
    f = fopen(file_name, "w");

    data_table = (unsigned int*)malloc(5 * sizeof(unsigned int));
    head_label = (ptr_label)malloc(sizeof(label));
    tail_label = head_label;

    IC = 0;
    DC = 0;

    /*Reads a line*/
    while(fgets(row_content, MAX_LINE_LENGTH, f)){
        
        /*Read the first word of the line*/
        if(first_word = strtok(row_content, ' \t\r')){
            if(!strcmp(first_word, ';') || first_word == NULL || !strcmp(first_word, ".entry"))/*If note or empty line or entry*/
                continue;
            
            /*Read the second word of the line*/
            if(second_word = strtok(NULL, ' \t\r')){
                
                /*If the first word is extern*/
                if(!strcmp(first_word, ".extern")){
                    printf("Warning: %s is extern\n", first_word);
                    there_is_error = 1;
                }
                
                /*If the first word is data/string/struct */
                else if(!strcmp(first_word, ".data") || !strcmp(first_word, ".string") ||!strcmp(first_word, ".struct"))
                        DC = create_data_line(DC, row_content, &data_table, first_word);

                    
                    /*If the first word is opcode*/    
                    else if(op_code_index = find_opcode(first_word) != -1)
                            IC = find_group(op_code_index, IC, &head_label);

                        /*If the first word is label*/
                        else if(strlen(first_word) > 1 && first_word[strlen(first_word)-1] == ':'){
                            
                                /*If the second word is data/string/struct */
                                if(!strcmp(second_word, ".data") || !strcmp(second_word, ".string") || !strcmp(second_word, ".struct")){
                                    insert_new_label(first_word, DATA, DC, &head_label, &tail_label);// TODO: fill data straight as binary
                                    DC = create_data_line(DC, row_content, &data_table, second_word);

                                }

                                /*If the second word is opcode*/
                                else if(op_code_index = find_opcode(second_word) != -1)
                                    IC = find_group(op_code_index, IC, &head_label);
                     
                        }
                        else{
                            /*The first word is not label\opcode\data\extern\entry*/ 
                            printf("Error: %s is illegal\n", first_word);
                            there_is_error = 1;
                        }
            }
            
        }
        
    }
    fclose(f);
    second_translation(&label_apear_head, &head_label);
    return there_is_error;
}


/*Finds opcode index by opcode name*/
int find_opcode(char *str){
    int i;

    for(i = 0; i < OPCODE_LENGTH; i++)
        if(!strcmp(str, opcode[i]))
            return i;
    
    return -1;
}


int find_group(int IC, int op_code_index, ptr_label head_label){
    
    /*If belongs to the first orders group*/
        if(op_code_index == 6 || (0 <= op_code_index && op_code_index <= 3))
            IC = insert_order( IC, convertDtoB(op_code_index), strtok(NULL, ' \t\r'), strtok(NULL, ' \t\r'), &head_label, &label_apear_head);

        /*If belongs to the second orders group*/
        if((4 <= op_code_index && op_code_index <= 5) || (7 <= op_code_index && op_code_index <= 13))
            IC = insert_order( IC, convertDtoB(op_code_index), strtok(NULL, ' \t\r'), NULL, &head_label, &label_apear_head);

        /*If belongs to the third orders group*/
        if(op_code_index == 14 || op_code_index == 15)
            IC = insert_order( IC, convertDtoB(op_code_index), NULL, NULL, &head_label, &label_apear_head);
    return IC;
}


/*Free the labels list */
void free_label_list() {
    ptr_label it = head_label, temp;

    while (it != NULL) {
        temp = it;
        it = it->next;
        free(temp->name);
        free(temp->type);
        free(temp);
    }
    head_label = NULL;
    tail_label = NULL;
}


/*Free the data array*/
void free_data_table(){
    free(data_table);
}

