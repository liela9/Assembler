
#include "assembler.h"

int first_translation(FILE *f){
    
    char *row_content, *first_word, *second_word;
    int op_code_index, IC, DC;
    unsigned int *data_table;
    ptr_label head_label;
    ptr_label tail_label;  

    data_table = (unsigned int*)malloc(5 * sizeof(unsigned int));
    head_label = (ptr_label)malloc(sizeof(label));
    tail_label = head_label;

    IC = 0;
    DC = 0;

    /*Reads a line*/
    while(fgets(row_content, row_content_LENGTH, f)){
        
        /*Read the first word of the line*/
        if(first_word = strtok(row_content, ' \t\r')){
            if(!strcmp(first_word, ';') || first_word == NULL || !strcmp(first_word, ".entry"))/*If note or empty line or entry*/
                continue;
            
            /*Read the second word of the line*/
            if(second_word = strtok(NULL, ' \t\r')){
                
                /*If the first word is extern*/
                if(!strcmp(first_word, ".extern")){
                    printf("Warning: %s is extern\n", first_word);
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
                        }
            }
            
        }
        
    }
    return ;
}



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
            IC = insert_order( IC, convertDtoB(op_code_index), strtok(NULL, ' \t\r'), strtok(NULL, ' \t\r'), &head_label);

        /*If belongs to the second orders group*/
        if((4 <= op_code_index && op_code_index <= 5) || (7 <= op_code_index && op_code_index <= 13))
            IC = insert_order( IC, convertDtoB(op_code_index), strtok(NULL, ' \t\r'), NULL, &head_label);

        /*If belongs to the third orders group*/
        if(op_code_index == 14 || op_code_index == 15)
            IC = insert_order( IC, convertDtoB(op_code_index), NULL, NULL, &head_label);
    return IC;
}