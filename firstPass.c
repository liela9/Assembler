#include "firstPass.h"

#include "constants.h"
#include "conversionUtils.h"
#include "lines.h"
#include "lists.h"
#include "utils.h"

/* the first pass of the assembler */
responseType first_pass(multiVars *vars) {
    FILE *file;
    char *line, *copy_line;
    responseType response = SUCCESS;
    bool user_error_flag = false;
    vars->line_counter = 0;

    IC = 0;
    DC = 0;

    if (!(file = open_file_with_extension(vars->file_name, AM_EXTENSION, "r")))
        return SYSTEM_ERROR; /* can't open file */

    line = (char *)calloc_with_check(MAX_LINE_LENGTH, sizeof(char));
    if (!line) return SYSTEM_ERROR;
    copy_line = (char *)calloc_with_check(MAX_LINE_LENGTH, sizeof(char));
    if (!copy_line) {
        free(line);
        return SYSTEM_ERROR;
    }

    /* reads a line*/
    while (fgets(line, MAX_LINE_LENGTH, file)) {
        (vars->line_counter)++;
        strcpy(copy_line, line);

        response = handle_line(line, copy_line, vars);
        switch (response) {
            case SYSTEM_ERROR:
                break;
            case SUCCESS:
                continue;
            case USER_ERROR: {
                user_error_flag = true;
                continue;
            }
        }
    }
    free(line);
    free(copy_line);
    fclose(file);

    if (user_error_flag) return USER_ERROR;
    return response;
}

responseType handle_line(char *line, char *line_copy, multiVars *vars) {
    char *current_word, *label_name, *rest_line;
    responseType response;

    if (!(current_word = strtok(line, " \t\r\n")) || ((current_word[0] == ';')))
        /* if the line is a comment or empty */
        return SUCCESS;

    if (current_word[strlen(current_word) - 1] == ':') { /* label declaration */
        if (strlen(current_word) == 1) {
            print_user_error(vars, "label name is empty");
            return USER_ERROR;
        }
        label_name = current_word;
        label_name[strlen(label_name) - 1] = '\0'; /* remove the char ':' */
        current_word = strtok(NULL, " ,\t\r\n");
    } else /* no label for current line */
        label_name = NULL;

    if (!strcmp(current_word, ENTRY_WORD))
        return extern_entry_validate(ENTRY, vars,
                                     strstr(line_copy, strtok(NULL, " \t\r\n")));

    if (!strcmp(current_word, EXTERN_WORD))
        return extern_entry_validate(EXTERNAL, vars,
                                     strstr(line_copy, strtok(NULL, " \t\r\n")));

    rest_line = strtok(NULL, " \t\r\n");
    if (!strcmp(current_word, DATA_WORD)) {
        CHECK_DATA_ARGUMENT
        return insert_data_line(label_name, strstr(line_copy, rest_line), vars);
    }

    if (!strcmp(current_word, STRUCT_WORD)) {
        CHECK_DATA_ARGUMENT
        return insert_struct_line(label_name, strstr(line_copy, rest_line), vars);
    }

    if (!strcmp(current_word, STRING_WORD)) {
        CHECK_DATA_ARGUMENT
        CHECK_RESPONSE(insert_data_label(label_name, DC, STRING, vars))
        return insert_string_line(label_name, strstr(line_copy, rest_line), vars);
    }

    /* if it's a code line */
    if (label_name)
        return insert_opcode_line(label_name, strstr(line_copy, current_word), vars);

    return insert_opcode_line(label_name, line_copy, vars);
}

responseType extern_entry_validate(labelType type, multiVars *vars, char *line) {
    char *current_word, *rest_line;

    current_word = strtok(line, " ,\t\r\n");
    if (!current_word) {
        print_user_error(vars, "label name is empty");
        return USER_ERROR;
    }

    if (strtok(NULL, " \t\r\n")) {
        print_user_error(vars, "extra content in .extern or .entry line");
        return USER_ERROR;
    }
    if (type == EXTERNAL) return create_extern_label_node(current_word, vars);
    /* .Entry will be inserted upon its defintion */

    return SUCCESS;
}

responseType insert_data_label(char *label_name, int address, labelType type,
                               multiVars *vars) {
    if (label_name) return create_label_node(label_name, type, vars);
    return SUCCESS;
}

responseType insert_string_line(char *label_name, char *line, multiVars *vars) {
    int i, str_len;
    char *rest_line, *string_part, *c;
    responseType response;

    /* pointer to the first quotation mark */
    string_part = strchr(line, '\"');
    /* pointer to the last quotation mark */
    rest_line = strrchr(line, '\"');

    /* if there're 0 or 1 quotation mark */
    if (!rest_line || (string_part == rest_line)) {
        print_user_error(vars, "missing quotation mark in string part");
        return USER_ERROR;
    }

    /* if the first non-whitespace letter is not the first quotation mark */
    if (strtok(line, " \t\r") != string_part) {
        print_user_error(vars, "extra content before string argument");
        return USER_ERROR;
    }

    /* if after the second quotation mark there's chars other than spaces */
    if (strtok(rest_line + sizeof(char), " \t\r\n")) {
        print_user_error(vars, "extra content after string argument");
        return USER_ERROR;
    }

    for (c = string_part + sizeof(char); c != rest_line; c += sizeof(char))
        /* creates ascii representation of the character */
        CHECK_RESPONSE(create_data_node(string_part[i], vars))

    return create_zero_line(vars);
}

responseType insert_struct_line(char *label_name, char *line, multiVars *vars) {
    char *data_part = NULL, *string_part = NULL;
    int number, line_length = strlen(line);
    responseType response;

    CHECK_RESPONSE(insert_data_label(label_name, DC, STRUCT, vars))
    data_part = strtok(line, ",");
    string_part = strtok(NULL, "");

    if (strlen(data_part) == line_length) {
        print_user_error(vars, "missing comma");
        return USER_ERROR;
    }
    CHECK_RESPONSE(check_and_insert_data_item(data_part, vars))

    /* handle the string part of the struct */
    return insert_string_line(label_name, string_part, vars);
}

responseType check_and_insert_data_item(char *data_item, multiVars *vars) {
    int number;
    responseType response;

    data_item = strtok(data_item, " \t\r\n");
    if (!data_item) {
        print_user_error(vars, "empty data item");
        return USER_ERROR;
    }

    if (strtok(NULL, " \t\r\n")) {
        print_user_error(vars, "extra content in data item");
        return USER_ERROR;
    }

    while (data_item) {
        if ((number = atoi(data_item)) == 0 && (*data_item != '0')) {
            print_user_error(vars, "illegal data item");
            return USER_ERROR;
        }
        CHECK_RESPONSE(create_data_node(number, vars))
        data_item += sizeof(char);
    }
}

responseType insert_opcode_line(char *label_name, char *line, multiVars *vars) {
    int op_code_index, number_of_operands;
    char *op_code = NULL, *first_operand = NULL, *second_operand = NULL,
         *rest_line = NULL;
    responseType response;

    if (label_name) {
        CHECK_RESPONSE(create_label_node(label_name, CODE, vars))
    }

    op_code = strtok(line, " \t\r\n");
    rest_line = strtok(NULL, "");

    if (rest_line) {
        first_operand = strtok(rest_line, ",");
        second_operand = strtok(NULL, "");
    }
    CHECK_OPERAND_ARGUMENT(first_operand)
    CHECK_OPERAND_ARGUMENT(second_operand)

    if ((op_code_index = find_opcode(op_code)) == -1) {
        print_user_error(vars, "illegal item '%s'", op_code);
        return USER_ERROR;
    }

    number_of_operands = (first_operand) ? 1 : 0;
    number_of_operands += (second_operand) ? 1 : 0;
    if (number_of_operands != get_required_operands(op_code_index)) {
        print_user_error(vars, "illegal number of operands for opcode %s", op_code);
        return USER_ERROR;
    }

    switch (number_of_operands) {
        case 0:
            return create_no_operands_command(op_code_index, vars);
        case 1:
            return create_one_operand_command(op_code_index, first_operand, vars);
        case 2:
            return create_two_operands_command(op_code_index, first_operand,
                                               second_operand, vars);
    }
}

responseType insert_data_line(char *label_name, char *line, multiVars *vars) {
    char *token = NULL;
    int number, i = 0;
    bool is_comma = false, is_space_after_digit = false;

    char *data_item;
    responseType response;

    CHECK_RESPONSE(create_label_node(label_name, DATA, vars))

    data_item = strtok(line, ",");
    while (data_item) {
        CHECK_RESPONSE(check_and_insert_data_item(data_item, vars))
        data_item = strtok(NULL, ",");
    }
    return SUCCESS;
}
