#include "constants.h"
#include "preAssembler.h"
#include "macro.h"
#include "utils.h"


/*Copeis the input file and pastes the macros*/
response_type pre_assembler(char *file_name){
    FILE *file_to_read, *file_to_write;
    char line[MAX_LINE_LENGTH], copy_line[MAX_LINE_LENGTH];
    char *current_word, new_file_name[FILENAME_MAX];
    ptr_macro head_macro, current_macro, new_macro;
    bool in_macro_flag;
    response_type response;
    int line_counter = 0;


    file_to_read = fopen(file_name, "r");
    if(!file_to_read) {
        printf("User Error: Could not open file: %s\n", file_name);
        return USER_ERROR;
    }

    strcpy(new_file_name, file_name);
    strcat(new_file_name, AM_EXTENSION); /*Linking the extension .am to the file's name*/
    file_to_write = fopen(new_file_name, "w");
    if(!file_to_write){
        printf("System Error: Could not create file: %s\n", new_file_name);
        fclose(file_to_read);
        return SYSTEM_ERROR;
    }
    
    in_macro_flag = false;
    response = SUCCESS;
    head_macro = NULL;
    current_macro = NULL;

    current_word = calloc_with_check(MAX_LINE_LENGTH, sizeof(char));

    reset_array(line);
    /*Reads a line*/
    while(fgets(line, MAX_LINE_LENGTH, file_to_read)){
        line_counter++;
        reset_array(copy_line);
        strcpy(copy_line, line);

        reset_array(current_word);
        strcpy(current_word, strtok(copy_line, " \t\n"));

        if (!in_macro_flag) {
            /*If the current word is "macro"*/
            if(!strcmp(current_word, MACRO_WORD)){
                reset_array(current_word);
                strcpy(current_word, strtok(NULL, " \t\n"));

                if(!current_word ){
                    printf("User Error in %s: line %d : macro must have a name\n", file_name, line_counter);
                    response = USER_ERROR;
                }
                else if((macro_exists(head_macro, current_word)) || is_saved_words(current_word)){
                    printf("User Error: can't add new macro '%s'.\n", current_word);
                    response = USER_ERROR;
                }
                else {
                    reset_array(current_word);
                    strcpy(current_word, strtok(NULL, " \t\n"));
                    if(current_word){
                        printf("User Error in %s: line %d : extra content after macro name!\n", file_name, line_counter);
                        response = USER_ERROR;
                    }
                    else if(!(new_macro = create_macro_node(current_word))){
                            response = SYSTEM_ERROR; 
                            break;
                    }
                    else{
                        in_macro_flag = true;
                        if (!current_macro)
                            head_macro = current_macro = new_macro;
                        else {
                            current_macro->next = new_macro;
                            current_macro = new_macro;
                        }
                    }
                }
            }
            else{
                ptr_macro lookup_macro = NULL;
                if(!(lookup_macro = get_macro_by_id(head_macro, current_word))){
                    fputs(line, file_to_write);
                }
                else
                    fputs(lookup_macro->macro_content, file_to_write);
            }
        }

        /*If we're in the middle of a macro*/
        else{
            /*If the current word is not "endmacro"*/
            if(strcmp(current_word, ENDMACRO_WORD))
                strcat(current_macro->macro_content, line);
                /*Add the content (the line) to the variable "macro_content"*/
            else{
                reset_array(current_word);
                strcpy(current_word, strtok(NULL, " \t\n"));
                if(current_word){
                    printf("User Error in %s: line %d : extra content after 'endmacro'!\n", file_name, line_counter);
                    response = USER_ERROR;
                }
                in_macro_flag = false;
            }
        }
        reset_array(line);
    }

    fclose(file_to_write);
    fclose(file_to_read);
    free_macro_list(head_macro);
    return response;
}