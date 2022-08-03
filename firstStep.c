#include "constants.h"
#include "firstStep.h"
#include "converting.h"
#include "lines.h"
#include "label.h"

/*The first step of the Assembler*/
bool first_step(char *file_name, multiVars *vars){
    
    FILE *file;
    char *row_content, *first_word, *second_word, *entry_word;
    char new_file_name[FILENAME_MAX];
    int op_code_index;
    bool there_is_error_flag;
    
	row_content	= NULL;
	first_word = NULL;
	second_word = NULL;

    there_is_error_flag = false;

    strcpy(new_file_name, file_name);
    strcat(new_file_name, AM_EXTENSION);/*Add the extension ".am" to the name of the file*/
    
    file = fopen(new_file_name, "r");

    /*Reads a line*/
    while(fgets(row_content, MAX_LINE_LENGTH, file)){
        entry_word = NULL;

        /*Reads the first word of the line*/
        if((first_word = strtok(row_content, " \t\r"))){
            /*If it is comment or empty line*/
            if(!strcmp(first_word, ";") || first_word == NULL)
                continue;/*Continue to the next line*/
            
            /*If it is entry*/
            else if(!strcmp(first_word, ".entry")){
                /*Save the entry label name locally and continue to the next line*/
                entry_word = strtok(NULL, " \t\r");
                continue;
            }

            /*Reads the second word of the line*/
            if((second_word = strtok(NULL, " \t\r"))){
                
                /*If the first word is extern*/
                if(!strcmp(first_word, ".extern")){
                    printf("Warning: %s is extern\n", second_word);
                    if(!insert_new_label(second_word, EXTERNAL, DC, vars))
                        there_is_error_flag = true;
                }
                
                /*If the first word is data/string/struct */
                else if(!strcmp(first_word, ".data") || 
                    !strcmp(first_word, ".string") ||!strcmp(first_word, ".struct"))
                    create_data_line(row_content, vars->data_table, first_word);

                    
                /*If the first word is opcode*/    
                else if((op_code_index = find_opcode(first_word)) != -1)
                        find_group(op_code_index, vars);

                /*If the first word is label*/
                else if(strlen(first_word) > 1 && first_word[strlen(first_word)-1] == ':'){
                    
                    /*If the second word is data/string/struct */
                    if(!strcmp(second_word, ".data") ||
                       !strcmp(second_word, ".string") ||
                       !strcmp(second_word, ".struct")){
                        
                        if(entry_word)
                            insert_new_label(first_word, ENTRY, DC, vars);   

                        else if(insert_new_label(first_word, DATA, DC, vars))
                            vars->there_is_error_flag = true;
                            
                        create_data_line(row_content, vars->data_table, second_word);
                    }

                    /*If the second word is opcode*/
                    else if((op_code_index = find_opcode(second_word)) != -1)
                        find_group(op_code_index, vars);
                
                }
                else{
                    /*The first word is not label\opcode\data\extern\entry*/ 
                    printf("Error: %s is illegal\n", first_word);
                    there_is_error_flag = true;
                }
            }
        }
    }
    fclose(file);
    return !there_is_error_flag;
}


/*Finds opcode index by opcode name*/
int find_opcode(char *str){
    int i;

    for(i = 0; i < OPCODE_LENGTH; i++)
        if(!strcmp(str, opcode[i]))
            return i;
    
    return -1;
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



