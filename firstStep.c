
#include "assembler.h"

int first_translation(FILE *f){
    
    char *row, *str1, *str2;
    int op_code_index;;
    
    
    there_is_error = 0; 
    IC = 0;
    DC = 0;

    /*Reads a line*/
    while(fgets(row, ROW_LENGTH, f)){
        L = 0;
        /*Read the first word of the line*/
        if(str1 = strtok(row, ' \t\r')){
            if(!strcmp(str1, ';') || str1 == NULL || !strcmp(str1, ".entry"))/*If note or empty line or entry*/
                continue;
            
            /*Read the second word of the line*/
            if(str2 = strtok(NULL, ' \t\r')){
                
                /*If the first word is extern*/
                if(!strcmp(str1, ".extern")){
                    printf("Warning: %s is extern\n", str1);
                    insert_new_label(str2, EXTERNAL, -1);
                }
                
                /*If the first word is data/string/struct */
                else if(!strcmp(str1, ".data") || !strcmp(str1, ".string") ||!strcmp(str1, ".struct")){
                        create_new_line(NULL, DC, 0, 0, 0);// TODO: fill data content

                        if(!strcmp(str1, ".string") ||!strcmp(str1, ".struct"))
                            create_zero_line(DC);
                    }
                    
                    /*If the first word is opcode*/    
                    else if(op_code_index = find_opcode(str1) != -1)
                            find_group(op_code_index, str1, IC);

                        /*If the first word is label*/
                        else if(strlen(str1) > 1 && str1[strlen(str1)-1] == ':'){
                            
                                /*If the second word is data/string/struct */
                                if(!strcmp(str2, ".data") || !strcmp(str2, ".string") || !strcmp(str2, ".struct")){
                                    insert_new_label(str1, DATA, DC);// TODO: fill data straight as binary
                                    create_new_line(str1, DC, 0, 0, 0);

                                    if(!strcmp(str1, ".string") ||!strcmp(str1, ".struct"))
                                        create_zero_line(DC);
                                }

                                /*If the second word is opcode*/
                                else if(op_code_index = find_opcode(str2) != -1)
                                    find_group(op_code_index, str2, IC);
                     
                        }
                        else{
                            /*The first word is not label\opcode\data\extern\entry*/ 
                            printf("Error: %s is illegal\n", str1);
                            there_is_error = 1;
                        }
            }
            IC++;
        }
        IC = IC + L;
    }
    return &f;
}



int find_opcode(char *str){
    int i;

    for(i = 0; i < OPCODE_LENGTH; i++)
        if(!strcmp(str, opcode[i]))
            return i;
    
    return -1;
}


void find_group(int op_code_index, char *str, int IC){
    
    /*If belongs to the first orders group*/
        if(op_code_index == 6 || (0 <= op_code_index && op_code_index <= 3))
            insert_new_order(str, IC, convertDtoB(op_code_index), strtok(NULL, ' \t\r'), strtok(NULL, ' \t\r'));

        /*If belongs to the second orders group*/
        if((4 <= op_code_index && op_code_index <= 5) || (7 <= op_code_index && op_code_index <= 13))
            insert_new_order(str, IC, convertDtoB(op_code_index), strtok(NULL, ' \t\r'), NULL);

        /*If belongs to the third orders group*/
        if(op_code_index == 14 || op_code_index == 15)
            insert_new_order(str, IC, convertDtoB(op_code_index), NULL, NULL);
}