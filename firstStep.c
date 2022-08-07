#include "constants.h"
#include "firstStep.h"
#include "converting.h"
#include "lines.h"
#include "label.h"
#include "utils.h"
#include "dataList.h"


/*The first step of the Assembler*/
response_type first_step(char *file_name, multiVars *vars){
    
    FILE *file;
    char *row_content, *first_word, *second_word;
    int op_code_index;
    bool entry_word_flag;
    response_type response = SUCCESS;
    int line_counter = 0;

    if (!(file = open_file_with_extension(file_name, AM_EXTENSION, "r")))
        return SYSTEM_ERROR;


    row_content = (char *)calloc_with_check(MAX_LINE_LENGTH, sizeof(char));
    /*first_word = (char *)calloc_with_check(MAX_LINE_LENGTH, sizeof(char));
    second_word = (char *)calloc_with_check(MAX_LINE_LENGTH, sizeof(char));*/
    

    /*Reads a line*/
    while(fgets(row_content, MAX_LINE_LENGTH, file)){
        line_counter++;
        entry_word_flag = false;

        /*Reads the first word of the line*/
        if((first_word = strtok(row_content, " ,\t\r"))){
            /*If it is comment or empty line*/
            if(!strcmp(first_word, ";") || first_word == NULL)
                continue;/*Continue to the next line*/
            
            /*If it is entry*/
            else if(!strcmp(first_word, ENTRY_WORD)){
                /*Save the entry label name locally and continue to the next line*/
                entry_word_flag = true;
                continue;
            }

            /*Reads the second word of the line*/
            if((second_word = strtok(NULL, " ,\t\r"))){
                
                /*If the first word is extern*/
                if(!strcmp(first_word, EXTERN_WORD)){
                    printf("Warning in %s line %d : %s is extern\n",file_name, line_counter, second_word);
                    if((response = create_label_node(second_word, EXTERNAL, DC, vars)) != SUCCESS)
                        break;
                }
                
                /*If the first word is data/string/struct */
                else if(!strcmp(first_word, DATA_WORD) || !strcmp(first_word, STRING_WORD) ||!strcmp(first_word, STRUCT_WORD)){
                    if((response = create_data_line(row_content, first_word)) != SUCCESS)
                        break;
                }
                    
                /*If the first word is opcode*/    
                else if((op_code_index = find_opcode(first_word)) != -1)
                        find_group(op_code_index, vars);

                /*If the first word is label*/
                else if(strlen(first_word) > 1 && first_word[strlen(first_word)-1] == ':'){
                    
                    /*If the second word is data/string/struct */
                    if(!strcmp(second_word, DATA_WORD) ||
                       !strcmp(second_word, STRING_WORD) ||
                       !strcmp(second_word, STRUCT_WORD)){
                        
                        if(entry_word_flag)
                            create_label_node(first_word, ENTRY, DC, vars);   
                    }

                    /*If the second word is opcode*/
                    if((op_code_index = find_opcode(second_word)) != -1)
                        find_group(op_code_index, vars);

                    else if((response = create_label_node(first_word, DATA, DC, vars)) != SUCCESS)
                        break;

                    else create_data_line(row_content, second_word);
                
                }
                else{
                    /*The first word is not label\opcode\data\extern\entry*/ 
                    printf("User Error in %s line %d : %s is illegal\n", file_name, line_counter, first_word);
                    response = USER_ERROR;
                    break;
                }
            }
        }
    }
    free(row_content);
    free(first_word);
    free(second_word);
    fclose(file);
    return response;
}

/*Finds the group of the opcode by it's index.
Groups: 
    The first group using 2 openads.
    The second group using 1 openad.
    The third group using 0 openads.
*/
void find_group(int op_code_index, multiVars *vars){
    
    /*If belongs to the first opcode group*/
    if(op_code_index == 6 || (0 <= op_code_index && op_code_index <= 3))
        insert_command(convertDtoB(op_code_index), strtok(NULL, " \t\r"),strtok(NULL, " \t\r"), vars);

    /*If belongs to the second opcode group*/
    if((4 <= op_code_index && op_code_index <= 5) || (7 <= op_code_index && op_code_index <= 13))
        insert_command(convertDtoB(op_code_index), strtok(NULL, " \t\r"),NULL, vars);

    /*If belongs to the third opcode group*/
    if(op_code_index == 14 || op_code_index == 15)
        insert_command( convertDtoB(op_code_index), NULL, NULL, vars);

}



