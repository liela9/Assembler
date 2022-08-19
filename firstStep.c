#include "constants.h"
#include "firstStep.h"
#include "converting.h"
#include "lines.h"
#include "lists.h"
#include "utils.h"


/*The first step of the Assembler*/
responseType first_step(multiVars *vars){
    
    FILE *file;
    char *line, *copy_line;
    responseType response = SUCCESS;
    bool user_error_flag = false;
    vars->line_counter = 0;
    
    IC = 0;
    DC = 0;

    if (!(file = open_file_with_extension(vars->file_name, AM_EXTENSION, "r")))
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
        (vars->line_counter)++;
        strcpy(copy_line, line);
        
        response = handle_line(line, copy_line, vars);
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


responseType handle_line(char *line, char *line_copy, multiVars *vars) {
    char *current_word, *label_name, *rest_line;
    responseType response;

    if(!(current_word = strtok(line, " \t\r\n")) || ((current_word[0] == ';')))
        /*If it is comment or empty line*/
        return SUCCESS;

    if(current_word[strlen(current_word)-1] == ':') {
        if (strlen(current_word) == 1) {
            printf("User Error: in %s.am line %d : label name is empty\n", vars->file_name, vars->line_counter);
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
        return extern_entry_validate(ENTRY, vars, strstr(line_copy, strtok(NULL, " \t\r\n")));
    
    if(!strcmp(current_word, EXTERN_WORD)) 
        return extern_entry_validate(EXTERNAL, vars, strstr(line_copy, strtok(NULL, " \t\r\n")));
    
    rest_line = strtok(NULL, " \t\r\n");

    if(!strcmp(current_word, DATA_WORD)){
        if(!rest_line){
            printf("User Error: in %s.am line %d : missing data arguments\n", vars->file_name, vars->line_counter);
            return USER_ERROR;
        }
        return insert_data_line(label_name, strstr(line_copy, rest_line), vars);
    }

    if(!strcmp(current_word, STRUCT_WORD)){
        if(!rest_line){
            printf("User Error: in %s.am line %d : missing data arguments\n", vars->file_name, vars->line_counter);
            return USER_ERROR;
        }
        return insert_struct_line(label_name, strstr(line_copy, rest_line), vars);
    }

    if(!strcmp(current_word, STRING_WORD)){
        if(!rest_line){
            printf("User Error: in %s.am line %d : missing data arguments\n", vars->file_name, vars->line_counter);
            return USER_ERROR;
        }
        CHECK_RESPONSE(insert_data_label(label_name, DC, STRING, vars))
        return insert_string_line(label_name, strstr(line_copy, rest_line), vars);
    }

    if(label_name)
        return insert_opcode_line(label_name, strstr(line_copy, current_word), vars);

    return insert_opcode_line(label_name, line_copy, vars);

    return SUCCESS;
}

responseType extern_entry_validate(labelType type, multiVars *vars, char *line){
    char *current_word, *rest_line;

    current_word =  strtok(line, " ,\t\r\n");
    if (!current_word) {
        printf("User Error: in %s.am line %d : label name is empty\n", vars->file_name, vars->line_counter);
        return USER_ERROR;
    }
    
    rest_line = clear_white_spaces(strtok(NULL, ""));
    if (rest_line) { /* not empty line after the label name*/
        printf("User Error: in %s.am line %d : extra contect in .extern or .entry line\n", vars->file_name, vars->line_counter);
        free(rest_line);
        return USER_ERROR;
    }
    if(type == EXTERNAL)
        return create_extern_label_node(current_word, vars);

    return SUCCESS;
}

responseType insert_data_label(char* label_name, int address,labelType type, multiVars *vars) {
    if (label_name)
        return create_label_node(label_name, type, vars);
    return SUCCESS;
}

responseType insert_string_line(char *label_name, char* line, multiVars *vars) {
    int i, str_len;
    char *rest_line, *string_part;
    responseType response;

    /*Pointer to the last quotation mark*/
    rest_line = strrchr(line, '\"');
    /*Pointer to the first quotation mark*/
    string_part = strchr(line, '\"');

    if(!rest_line || !strcmp(string_part, rest_line)){/*if there are one or zero quotation marks*/
        printf("User Error: in %s.am line %d : missing quotation mark in string part\n", vars->file_name, vars->line_counter);
        return USER_ERROR;
    }

    for(i = 0; line[i] != '\"'; i++){/*Checks if there are characters before the first quotation mark*/
        if(!isspace(line[i])){
            printf("User Error: in %s.am line %d : illegal string argument\n", vars->file_name, vars->line_counter);
            return USER_ERROR;
        }
    }

    str_len = strlen(line) - strlen(rest_line);/*The length of string_part (quotation only)*/
    rest_line = clear_white_spaces(rest_line);/*Remove white spaces from the rest_line*/
    
    if(strcmp(rest_line, "\"")){/*If they are NOT equals*/
        printf("User Error: in %s.am line %d : illegal string argument\n", vars->file_name, vars->line_counter);
        free(rest_line);
        return USER_ERROR;
    }
    free(rest_line);

    for(i = 1; i < str_len; ++i){/*Reads between the "" */
        /*Converts the ASCII code of the letter to binary*/
        CHECK_RESPONSE(create_data_node(string_part[i], vars))
    }
    CHECK_RESPONSE(create_zero_line(vars))

    return SUCCESS;
}

responseType insert_struct_line(char *label_name, char* line, multiVars *vars) {
    char *data_part = NULL, *string_part = NULL, line_copy[MAX_LINE_LENGTH];
    int number;
    responseType response;

    CHECK_RESPONSE(insert_data_label(label_name, DC, STRUCT, vars))

    strcpy(line_copy, line);
    data_part = strtok(line, ",");
    if(!strcmp(data_part, line_copy)){
        printf("User Error: in %s.am line %d : missing comma\n", vars->file_name, vars->line_counter);
        return USER_ERROR;
    }
    string_part = strstr(line_copy, strtok(NULL, " ,\t\r\n"));
    data_part = clear_white_spaces(data_part);

    /*Handle the data part of the struct*/
    while (data_part){
        if ((number = atoi(data_part)) == 0 && strcmp(data_part, "0")) {
            printf("User Error: in %s.am line %d : illegal data argument\n", vars->file_name, vars->line_counter);
            return USER_ERROR;
        }
        CHECK_RESPONSE(create_data_node(number, vars))
        data_part = strtok(NULL, " ,\t\r\n");
    }
    
    /*Handle the string part of the struct*/
    return insert_string_line(label_name, string_part, vars);
}

responseType insert_opcode_line(char *label_name, char* line, multiVars *vars) {
    int op_code_index;
    char *op_code = NULL, *first_operand = NULL, *second_operand = NULL, *rest_line = NULL;
    responseType response;

    if(label_name){
        CHECK_RESPONSE(create_label_node(label_name, CODE, vars))
    }

    op_code = strtok(line, " \t\r\n");
    rest_line = strtok(NULL, ""); 

    if (rest_line) {
        first_operand = strtok(rest_line, ",");
        second_operand = strtok(NULL, "");
    }
    if (first_operand) {
        first_operand = strtok(first_operand, " \t\r\n");
        if (strtok(NULL, " \t\r\n")) {
            printf("User Error: in %s.am line %d : extra character after first oprand\n", vars->file_name, vars->line_counter);
            return USER_ERROR;
        }
    }
    if (second_operand) {
        second_operand = strtok(second_operand, " \t\r\n");
        if (strtok(NULL, " \t\r\n")) {
            printf("User Error: in %s.am line %d : extra character after second oprand\n", vars->file_name, vars->line_counter);
            return USER_ERROR;
        }
    }

    if((op_code_index = find_opcode(op_code)) != -1){

        /*If there are two arguments after opcode word*/
        if(first_operand && second_operand){
            if((0 <= op_code_index && op_code_index <= 3) || op_code_index == 6){
               CHECK_RESPONSE(create_two_operands_command(op_code_index, first_operand, second_operand, vars))
            }
            else{
                printf("User Error: in %s.am line %d : extra operands for opcode '%s'\n", vars->file_name, vars->line_counter, op_code);
                return USER_ERROR;
            }    
        }

        /*If there are no arguments after opcode word*/
        else if(!first_operand && !second_operand){
            
            if(op_code_index == 14 || op_code_index == 15){
                CHECK_RESPONSE(create_no_operands_command(op_code_index, vars))
            }
            else{
                printf("User Error: in %s.am line %d : missing operands for opcode '%s'\n", vars->file_name, vars->line_counter, op_code);
                return USER_ERROR;
            }
        }
        
        /*If there is one argument after opcode word*/
        else if(first_operand && !second_operand){
            if((4 <= op_code_index && op_code_index <= 5) || (7 <= op_code_index && op_code_index <= 13)){
                CHECK_RESPONSE(create_one_operand_command(op_code_index, first_operand, vars))
            }
            else{
                printf("User Error: in %s.am line %d : too many or too few operands for opcode '%s'\n", vars->file_name, vars->line_counter, op_code);
                return USER_ERROR;
            }
        }
    }
    else{
        printf("User Error: in %s.am line %d : illegal item '%s'\n", vars->file_name, vars->line_counter, op_code);
        return USER_ERROR;
    }
    return SUCCESS;
}

responseType insert_data_line(char *label_name, char* line, multiVars *vars) {
    char *token = NULL;
    int number, i = 0;
    bool is_comma = false, is_space_after_digit = false;
    responseType response;

    CHECK_RESPONSE(create_label_node(label_name, DATA, vars))
    
    while(!isdigit(line[i])){
        if(!isspace(line[i])){
            printf("User Error: in %s.am line %d : illegal character before data\n", vars->file_name, vars->line_counter);
            return USER_ERROR;
        }
        i++;
    }

    for(i = 0; i < strlen(line) ; ++i){/*Checks validation of the commas*/
        if(line[i] == ','){
            if(is_comma){
                printf("User Error: in %s.am line %d : illegal data argument\n", vars->file_name, vars->line_counter);
                return USER_ERROR;
            }
            is_comma = true;
            is_space_after_digit = false;
        }
        else if(isdigit(line[i]) && is_comma){
                is_comma = false;
                is_space_after_digit = false;
        }
        else if(is_space_after_digit && isdigit(line[i]) && !is_comma){
            printf("User Error: in %s.am line %d : missing comma\n", vars->file_name, vars->line_counter);
            return USER_ERROR;
        }
        else if(isspace(line[i]))
                is_space_after_digit = true;
    }

    i = strlen(line) -1;
    while(!isdigit(line[i])){
        if(!isspace(line[i])){
            printf("User Error: in %s.am line %d : illegal character after data\n", vars->file_name, vars->line_counter);
            return USER_ERROR;
        }
        i--;
    }

    token = strtok(line, ","); 
    while (token){
        if ((number = atoi(token)) == 0 && strcmp(token, "0")) {
            printf("User Error: in %s.am line %d : extra comma\n", vars->file_name, vars->line_counter);
            return USER_ERROR;
        }

        CHECK_RESPONSE(create_data_node(number, vars))
        token = strtok(NULL, " ,\n\t\r");
        
    }
    return SUCCESS;
}
