#include "preAssembler.h"

/* replaces macro symbols with their content */
responseType pre_assembler(multiVars *vars) {
    FILE *file_to_read, *file_to_write;
    char line[MAX_LINE_LENGTH], copy_line[MAX_LINE_LENGTH], *current_word = NULL;
    ptrMacro head_macro = NULL, tail_macro = NULL, current_macro = NULL, lookup_macro;
    responseType response = SUCCESS;
    vars->line_counter = 0;

    if (!(file_to_read = open_file_with_extension(vars->file_name, AS_EXTENSION, "r")) ||
        !(file_to_write = open_file_with_extension(vars->file_name, AM_EXTENSION, "w+b")))
        return USER_ERROR;

    /* reads a line */
    while (fgets(line, MAX_LINE_LENGTH, file_to_read)) {
        (vars->line_counter)++;
        strcpy(copy_line, line);

        current_word = strtok(copy_line, " \t\n");
        if (!current_word) /* if it's an empty line */
            continue;

        if (!current_macro) /* not in the middle of processing a macro statement */
        {
            /* if current_word is "macro" */
            if (!strcmp(current_word, MACRO_WORD)) {
                current_word = strtok(NULL, " \t\r\n");

                if (!current_word) {
                    print_user_error(vars, "macro must have a name");
                    response = USER_ERROR;
                } else if (is_reserved_word(current_word)) {
                    print_user_error(vars, "can't use reserved word '%s' as macro name",
                                     current_word);
                    response = USER_ERROR;
                } else if (macro_exists(head_macro, current_word)) {
                    print_user_error(vars, "macro name '%s' is already exist",
                                     current_word);
                    response = USER_ERROR;
                }

                else { /* macro has a valid name */
                    if (strtok(NULL, " \t\r\n")) {
                        print_user_error(vars, "extra content after macro name");
                        response = USER_ERROR;
                    } else if (!(current_macro = create_macro_node(
                                     current_word, &head_macro, &tail_macro))) {
                        response = SYSTEM_ERROR;
                        break;
                    }
                }
            } else { /* current_word is not "macro" */
                if (!(lookup_macro = get_macro_by_id(head_macro, current_word))) {
                    fputs(line, file_to_write);
                } else /* current_word is a macro name */
                    fputs(lookup_macro->macro_content, file_to_write);
            }
        }

        else { /* we're in the middle of a macro statement */
            /* if the current word is NOT "endmacro" */
            if (strcmp(current_word, ENDMACRO_WORD))
                strcat(current_macro->macro_content, line);
            /* add the content (the line) to macro_content */
            else {
                if (strtok(NULL, " \t\r\n")) {
                    print_user_error(vars, "extra content after 'endmacro'");
                    response = USER_ERROR;
                }
                current_macro = NULL;
            }
        }
    }
    fclose(file_to_write);
    fclose(file_to_read);
    free_macro_list(head_macro);
    return response;
}
