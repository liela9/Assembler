#include "constants.h"
#include "firstStep.h"
#include "converting.h"
#include "lines.h"
#include "lists.h"
#include "utils.h"


/*The first step of the Assembler*/
responseType first_step(char *file_name, multiVars *vars){
    
    FILE *file;
    char *line, *copy_line;
    responseType response = SUCCESS;
    bool user_error_flag = false;
    int line_counter = 0;

    if (!(file = open_file_with_extension(file_name, AM_EXTENSION, "r")))
        return SYSTEM_ERROR;

    line = (char *)calloc_with_check(MAX_LINE_LENGTH, sizeof(char));
    if (!line)
        return SYSTEM_ERROR;
    copy_line = (char *)calloc_with_check(MAX_LINE_LENGTH, sizeof(char));
    if (!copy_line) {
        free(line);
        return SYSTEM_ERROR;
    }

    /*Reads a line*/
    while(fgets(line, MAX_LINE_LENGTH, file)){
        line_counter++;
        strcpy(copy_line, line);
        
        response = handle_line(file_name, line, copy_line, line_counter, vars);
        switch(response) {
            case SYSTEM_ERROR:
                break;
            case SUCCESS:
                continue;
            case USER_ERROR:{
                    user_error_flag = true;
                    continue;
                }
        }
    }
    free(line);
    free(copy_line);
    fclose(file);
    
    if(user_error_flag)
        return USER_ERROR;
    return response;
}


responseType handle_line(char* file_name, char* line, char * line_copy, int line_number, multiVars *vars) {
    char *current_word, *label_name;

    if(!(current_word = strtok(line, " \t\r")) || ((current_word[0] == ';')))
        /*If it is comment or empty line*/
        return SUCCESS;

    if(current_word[strlen(current_word)-1] == ':') {
        if (strlen(current_word) == 1) {
            printf("User Error: in %s.am line %d : label name is empty\n", file_name, line_number);
            return USER_ERROR;
        }
        label_name = current_word;
        label_name[strlen(label_name)-1] = '\0'; /*Remove the char ':' */
        current_word =  strtok(NULL, " ,\t\r");
    }
    else
        label_name = NULL;

    /* TODO:  need to check that .entry and .extern must be at the begining?
        if so, check inside "create_label_node" if all code lists are null*/

    if(!strcmp(current_word, ENTRY_WORD)) 
        return extern_entry_validate(file_name, line_number, vars, ENTRY, strstr(line_copy, strtok(NULL, " ,\t\r")));
    
    if(!strcmp(current_word, EXTERN_WORD)) 
        return extern_entry_validate(file_name, line_number, vars, EXTERNAL, strstr(line_copy, strtok(NULL, " ,\t\r")));
    
    if(!strcmp(current_word, DATA_WORD))
        return insert_data_line(file_name, line_number, label_name, strstr(line_copy, strtok(NULL, " ,\t\r")), vars);

    if(!strcmp(current_word, STRUCT_WORD))
        return insert_struct_line(file_name, line_number, label_name, strstr(line_copy, strtok(NULL, " ,\t\r")), vars);

    if(!strcmp(current_word, STRING_WORD))
        return insert_string_line(file_name, line_number, label_name, strstr(line_copy, strtok(NULL, " ,\t\r")), vars);

    if(label_name)
        return insert_opcode_line(file_name, line_number, label_name, strstr(line_copy, current_word), vars);

    return insert_opcode_line(file_name, line_number, label_name, line_copy, vars);

    return SUCCESS;
}

responseType extern_entry_validate(char *file_name, int line_number, multiVars *vars, labelType type, char *line){
    char *current_word;

    current_word =  strtok(line, " ,\t\r");
    if (!current_word) {
        printf("User Error: in %s.am line %d : label name is empty\n", file_name, line_number);
        return USER_ERROR;
    }
    if (!strtok(NULL, " ,\t\r")) { /* not empty line after the label name*/
        printf("User Error: in %s.am line %d : extra contect in .extern line\n", file_name, line_number);
        return USER_ERROR;
    }
    return create_label_node(current_word, type, vars);
}

responseType insert_data_label(char* label_name, int address, multiVars *vars) {
    if (label_name)
        return create_label_node(label_name, DATA, vars);
    return SUCCESS;
}

responseType insert_string_line(char* file_name, int line_number, char *label_name, char* line, multiVars *vars) {
    int i, current_dc = DC;

    if(insert_data_label(label_name, current_dc, vars) == SYSTEM_ERROR)
        return SYSTEM_ERROR;

    strtok(line, "\"");
    for(i = 1; i < strlen(line); ++i){/*Reads between the ""*/
        /*Converts the ASCII code of the letter to binary*/
        if(create_data_node(line[i], vars) != SUCCESS)
            return SYSTEM_ERROR;
    }

    if(create_zero_line(vars) != SUCCESS)
        return SYSTEM_ERROR;

    return SUCCESS;
}

responseType insert_struct_line(char* file_name, int line_number, char *label_name, char* line, multiVars *vars) {
    int i, number, current_dc = DC;
    char token[MAX_LINE_LENGTH];
    char *string_part = NULL;

    if(insert_data_label(label_name, current_dc, vars) == SYSTEM_ERROR)
        return SYSTEM_ERROR;

    string_part = strstr(line, "\"");
    /*The firt argument is data(number)*/
    strcpy(token, strtok(line, " ,\t\r"));
    if ((number = atoi(token)) == 0 && strcmp(token, "0")) {
            printf("User Error in %s.am line %d : illegal data argument\n", file_name, line_number);
            return USER_ERROR;
    }
    if(create_data_node(atoi(token), vars) != SUCCESS)
        return SYSTEM_ERROR;

    strtok(string_part, "\"");
    /*The second argument is string*/
    for(i = 1; i < strlen(string_part); ++i){/*Reads between the ""*/
        if(create_data_node(string_part[i], vars) != SUCCESS)
            return SYSTEM_ERROR;
    }
    
    if(create_zero_line(vars) != SUCCESS)
        return SYSTEM_ERROR;

    return SUCCESS;
}

responseType insert_opcode_line(char* file_name, int line_number, char *label_name, char* line, multiVars *vars) {
    int op_code_index;
    char *op_code = NULL, *first_operand = NULL, *second_operand = NULL;

    if (label_name && (create_label_node(label_name, CODE, vars) == SYSTEM_ERROR))
        return SYSTEM_ERROR;

    op_code = strtok(line, " ,\t\r\n");
    first_operand = strtok(NULL, " ,\t\r\n");
    second_operand = strtok(NULL, " ,\t\r\n");

    if((op_code_index = find_opcode(op_code)) != -1){

        /*If there are two arguments after opcode word*/
        if(first_operand && second_operand){
            if((0 <= op_code_index && op_code_index <= 3) || op_code_index == 6)
                create_two_operands_command(op_code_index, first_operand, second_operand, vars);
            else{
                printf("User Error: in %s.am line %d : extra operands for opcode '%s'\n", file_name, line_number, op_code);
                return USER_ERROR;
            }    
        }
    
        /*If there are no arguments after opcode word*/
        else if(!first_operand && !second_operand){
            
            if(op_code_index == 14 || op_code_index == 15)
                create_no_operands_command(op_code_index, vars);
            else{
                printf("User Error: in %s.am line %d : missing operands for opcode '%s'\n", file_name, line_number, op_code);
                return USER_ERROR;
            }
        }
        
        /*If there is one argument after opcode word*/
        else if(first_operand && !second_operand){
            if((4 <= op_code_index && op_code_index <= 5) || (7 <= op_code_index && op_code_index <= 13))
                create_one_operand_command(op_code_index, first_operand, vars);
            else{
                printf("User Error: in %s.am line %d : too many or too few operands for opcode '%s'\n", file_name, line_number, op_code);
                return USER_ERROR;
            }
        }
    }
    else{
        printf("User Error: in %s.am line %d : illegal opcode '%s'\n", file_name, line_number, op_code);
        return USER_ERROR;
    }

    return SUCCESS;
}

responseType insert_data_line(char* file_name, int line_number, char *label_name, char* line, multiVars *vars) {
    char *token = NULL;
    int number;

    if(create_label_node(label_name, DATA, vars) == SYSTEM_ERROR)
        return SYSTEM_ERROR;

    if (!line){
        printf("User Error in %s.am line %d : missing data arguments\n", file_name, line_number);
        return USER_ERROR;
    }
    
    token = strtok(line, " ,\t\r\n");
    while (token){
        if ((number = atoi(token)) == 0 && strcmp(token, "0")) {
            printf("User Error in %s.am line %d : illegal data argument\n", file_name, line_number);
            return USER_ERROR;
        }
        if(create_data_node(number, vars) == SUCCESS){
            token = strtok(NULL, " ,\t\r\n");
        }
        else return SYSTEM_ERROR;
    }
    return SUCCESS;
}