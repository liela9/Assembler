#include "secondPass.h"

/*The second pass of the Assembler*/
responseType second_pass(multiVars *vars) {
    FILE *file;
    char *label_name, *line, *label_type;
    int index = 0, i;
    ptrlabel temp_label;
    ptrExternLabel temp_extern_label;
    bool is_space_flag;
    ptrLabelApearence temp_label_apear = vars->head_label_apear;
    ptrCommand temp_commands = vars->head_commands;
    unsigned long question_mark = convertDtoB('?');
    responseType response = SUCCESS;
    vars->line_counter = 0;

    if (!(file = open_file_with_extension(vars->file_name, AM_EXTENSION, "r")))
        return SYSTEM_ERROR;

    line = (char *)calloc_with_check(MAX_LINE_LENGTH, sizeof(char));
    if (!line) return SYSTEM_ERROR;

    /*Checks if there is a match between the type of the label and its use as operand*/
    while (temp_label_apear) {
        vars->line_counter = vars->line_counter + 1;
        if (temp_label_apear->is_struct) {
            temp_label = get_label_by_name(temp_label_apear->name, vars->head_label);
            if (temp_label && temp_label->type != STRUCT) {
                printf("User Error: in %s.am line %d : '%s' is not a struct label\n",
                       vars->file_name, temp_label_apear->apeared_with_point,
                       temp_label_apear->name);
                free(line);
                return USER_ERROR;
            }
        } else {
            temp_label = get_label_by_name(temp_label_apear->name, vars->head_label);
            if (temp_label && temp_label->type == STRUCT) {
                printf("User Error: in %s.am line %d : '%s' is struct label\n",
                       vars->file_name, vars->line_counter, temp_label_apear->name);
                free(line);
                return USER_ERROR;
            }
        }
        temp_label_apear = temp_label_apear->next;
    }
    temp_label_apear = vars->head_label_apear;
    vars->line_counter = 0;

    while (fgets(line, MAX_LINE_LENGTH, file)) {
        (vars->line_counter)++;
        is_space_flag = true;

        for (i = 0; i < strlen(line); ++i) { /*Checks if the current line is "empty"*/
            if (!isspace(line[i])) {
                is_space_flag = false;
                break;
            }
        }
        if (is_space_flag) /*If the line is "empty" => read the next line*/
            continue;

        label_type = strtok(line, " \t\n\r");
        label_name = strtok(NULL, " \t\n\r");

        if (!strcmp(label_type, ENTRY_WORD)) {
            if (!(temp_label = get_label_by_name(label_name, vars->head_label))) {
                printf("User Error: in %s.am line %d : %s undefined\n", vars->file_name,
                       vars->line_counter, label_name);
                response = USER_ERROR;
            } else if (temp_label->type != EXTERNAL){
                if(temp_label->type == ENTRY){
                    print_user_error(vars, "'%s' already declared as entry", temp_label->name);
                    response = USER_ERROR;
                }
                temp_label->type = ENTRY;
            }
            else {
                printf("User Error: in %s.am line %d : %s already defined as 'extern'\n",
                       vars->file_name, vars->line_counter, label_name);
                response = USER_ERROR;
            }
        }
        if (!strcmp(label_type, EXTERN_WORD)) {
            temp_label = get_label_by_name(label_name, vars->head_label);
            if (!temp_label) {
                continue;
            }
            if (temp_label->type != ENTRY)
                temp_label->type = EXTERNAL;
            else {
                printf("User Error: in %s.am line %d : %s already defined as 'entry'\n",
                       vars->file_name, vars->line_counter, temp_label->name);
                response = USER_ERROR;
            }
        }
    }
    label_name = NULL;

    /*While it is not the end of the list*/
    while (temp_commands) {
        /*Finds the lines without binary code*/
        if (temp_commands->code == question_mark) {
            /* Finds the name of the label */
            while (temp_label_apear) {
                if ((temp_label_apear->index_in_commands_list) == index) {
                    label_name = temp_label_apear->name;
                    break;
                }
                temp_label_apear = temp_label_apear->next;
            }

            temp_label = NULL;
            temp_extern_label = vars->head_extern_label;
            /* Finds the address of the label and replace the '?' by it*/
            while (temp_extern_label) {
                if (!strcmp(temp_extern_label->name, label_name)) {
                    temp_commands->code = (convertDtoB(E));
                    break;
                }
                temp_extern_label = temp_extern_label->next;
            }

            if (temp_commands->code == question_mark) {
                temp_label = get_label_by_name(label_name, vars->head_label);
                temp_commands->code = (convertDtoB(temp_label->dec_address << 2 | R));
            }
            continue;
        }
        temp_commands = temp_commands->next;
        index++;
    }

    while (temp_label) temp_label = temp_label->next;
    while (temp_label_apear) temp_label_apear = temp_label_apear->next;
    free(line);
    return response;
}
