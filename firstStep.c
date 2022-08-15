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
    char *current_word, *label_name, *rest_line;

    if(!(current_word = strtok(line, " \t\r\n")) || ((current_word[0] == ';')))
        /*If it is comment or empty line*/
        return SUCCESS;

    if(current_word[strlen(current_word)-1] == ':') {
        if (strlen(current_word) == 1) {
            printf("User Error: in %s.am line %d : label name is empty\n", file_name, line_number);
            return USER_ERROR;
        }
        label_name = current_word;
        label_name[strlen(label_name)-1] = '\0'; /*Remove the char ':' */
        current_word =  strtok(NULL, " ,\t\r\n");
    }
    else
        label_name = NULL;

    /* TODO:  need to check that .entry and .extern must be at the begining?
        if so, check inside "create_label_node" if all code lists are null*/

    if(!strcmp(current_word, ENTRY_WORD)) 
        return extern_entry_validate(file_name, ENTRY, vars, line_number, strstr(line_copy, strtok(NULL, " \t\r\n")));
    
    if(!strcmp(current_word, EXTERN_WORD)) 
        return extern_entry_validate(file_name, EXTERNAL, vars, line_number, strstr(line_copy, strtok(NULL, " \t\r\n")));
    
    rest_line = strtok(NULL, " \t\r\n");

    if(!strcmp(current_word, DATA_WORD)){
        if(!rest_line){
            printf("User Error in %s.am line %d : missing data arguments\n", file_name, line_number);
            return USER_ERROR;
        }
        return insert_data_line(file_name, line_number, label_name, strstr(line_copy, rest_line), vars);
    }

    if(!strcmp(current_word, STRUCT_WORD)){
        if(!rest_line){
            printf("User Error in %s.am line %d : missing data arguments\n", file_name, line_number);
            return USER_ERROR;
        }
        return insert_struct_line(file_name, line_number, label_name, strstr(line_copy, rest_line), vars);
    }

    if(!strcmp(current_word, STRING_WORD)){
        if(!rest_line){
            printf("User Error in %s.am line %d : missing data arguments\n", file_name, line_number);
            return USER_ERROR;
        }
        return insert_string_line(file_name, line_number, label_name, strstr(line_copy, rest_line), vars);
    }

    if(label_name)
        return insert_opcode_line(file_name, line_number, label_name, strstr(line_copy, current_word), vars);

    return insert_opcode_line(file_name, line_number, label_name, line_copy, vars);

    return SUCCESS;
}

responseType extern_entry_validate(char *file_name, labelType type, multiVars *vars, int line_number, char *line){
    char *current_word;

    current_word =  strtok(line, " ,\t\r\n");
    if (!current_word) {
        printf("User Error: in %s.am line %d : label name is empty\n", file_name, line_number);
        return USER_ERROR;
    }
    if (!strtok(NULL, " ,\t\r\n")) { /* not empty line after the label name*/
        printf("User Error: in %s.am line %d : extra contect in .extern or .entry line\n", file_name, line_number);
        return USER_ERROR;
    }
    if(type == EXTERNAL)
        return create_extern_label_node(current_word, vars);
    
    return SUCCESS;
}

responseType insert_data_label(char* label_name, int address, multiVars *vars) {
    if (label_name)
        return create_label_node(label_name, DATA, vars);
    return SUCCESS;
}

responseType insert_string_line(char* file_name, int line_number, char *label_name, char* line, multiVars *vars) {
    int i, current_dc = DC, len_of_string;
    char *string_part, *rest_line;
    bool is_not_space_flag = false;

    /*Cut the last quotation mark and the other characters after it*/
    rest_line = strrchr(line, '\"');

    if(!rest_line){
        printf("User Error in %s.am line %d : missing quotation mark in string part\n", file_name, line_number);
        return USER_ERROR;
    }

    /*Checs if there are not white-spaces characters after the last quotation mark*/
    for(i = 1; i < strlen(rest_line); ++i){
        if(!isspace(rest_line[i])){
            is_not_space_flag = true;
            break;
        }
    }
    if(is_not_space_flag){
        printf("User Error in %s.am line %d : illegal string argument\n", file_name, line_number);
        return USER_ERROR;
    }

    if(insert_data_label(label_name, current_dc, vars) == SYSTEM_ERROR)
        return SYSTEM_ERROR;


    len_of_string = strlen(line) - strlen(rest_line) + 1;
    string_part = (char *)calloc_with_check(len_of_string, sizeof(char));
    memcpy(string_part, line, len_of_string);
    
    if(string_part[0] != '\"'){
        printf("User Error in %s.am line %d : missing quotation mark in string part\n", file_name, line_number);
        free(string_part);
        return USER_ERROR;
    }


    for(i = 1; i < strlen(string_part)-1; ++i){/*Reads between the "" */
        /*Converts the ASCII code of the letter to binary*/
        if(create_data_node(string_part[i], vars) != SUCCESS){
            free(string_part);
            return SYSTEM_ERROR;
        }
    }

    free(string_part);

    if(create_zero_line(vars) != SUCCESS)
        return SYSTEM_ERROR;

    return SUCCESS;
}

responseType insert_struct_line(char* file_name, int line_number, char *label_name, char* line, multiVars *vars) {
    char *data_part = NULL, *string_part = NULL, line_copy[MAX_LINE_LENGTH];
    int number;

    strcpy(line_copy, line);
    data_part = strtok(line, " ,\t\r\n");
    string_part = strstr(line_copy, strtok(NULL, " ,\t\r\n"));

    /*Handle the data part of the struct*/
    while (data_part){
        if ((number = atoi(data_part)) == 0 && strcmp(data_part, "0")) {
            printf("User Error in %s.am line %d : illegal data argument\n", file_name, line_number);
            return USER_ERROR;
        }
        if(create_data_node(number, vars) == SUCCESS){
            data_part = strtok(NULL, " ,\t\r\n");
        }
        else return SYSTEM_ERROR;
    }

    /*Handle the string part of the struct*/
    return insert_string_line(file_name, line_number, label_name, string_part, vars);
}

responseType insert_opcode_line(char* file_name, int line_number, char *label_name, char* line, multiVars *vars) {
    int op_code_index;
    responseType response = SUCCESS;
    char *op_code = NULL, *first_operand = NULL, *second_operand = NULL, *rest_line = NULL;

    if(label_name && (response = create_label_node(label_name, CODE, vars)) != SUCCESS)
        return response;

    op_code = strtok(line, " ,\t\r\n");
    first_operand = strtok(NULL, " ,\t\r\n");
    second_operand = strtok(NULL, " ,\t\r\n");
    rest_line = strtok(NULL, " ,\t\r\n");
    
    if(rest_line){/*If not null*/
        printf("User Error: in %s.am line %d : extra operands for opcode '%s'\n", file_name, line_number, op_code);
        return USER_ERROR;
    }
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
        printf("User Error: in %s.am line %d : illegal item '%s'\n", file_name, line_number, op_code);
        return USER_ERROR;
    }

    return response;
}

responseType insert_data_line(char* file_name, int line_number, char *label_name, char* line, multiVars *vars) {
    char *token = NULL;
    int number;
    responseType response;

    if((response = create_label_node(label_name, DATA, vars)) != SUCCESS)
        return response;
    
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
