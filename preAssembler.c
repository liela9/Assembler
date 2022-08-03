#include "constants.h"
#include "preAssembler.h"
#include "macro.h"


/*Copeis the input file and pastes the macros*/
response_type pre_assembler(char *file_name){
    FILE *file_to_read, *file_to_write;
    char line[MAX_LINE_LENGTH], copy_line[MAX_LINE_LENGTH];
    char *current_word, new_file_name[FILENAME_MAX];
    ptr_macro head_macro, current_macro, new_macro;
    bool in_macro_flag;
    response_type response;

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
        return SYSTEM_ERROR;
    }
    
    in_macro_flag = false;
    response = SUCCESS;
    current_word = NULL;
    head_macro = NULL;
    current_macro = NULL;

    /*Reads a line*/
    while(fgets(line, MAX_LINE_LENGTH, file_to_read)){

        strcpy(copy_line, line);
        current_word = strtok(copy_line, " \t\n");

        if (!in_macro_flag) {
            /*If the current word is "macro"*/
            if(!strcmp(current_word, MACRO_WORD)){

                if(!(current_word = strtok(NULL, " \t\n"))){
                    /* TODO: add function for "user error" */
                    printf("User Error: macro must have a name\n");
                    response = USER_ERROR;
                }
                /*TODO: check valid name for macro*/
                else if((macro_exists(head_macro, current_word))){
                    printf("User Error: can't add new macro %s, macro already exists\n", current_word);
                    response = USER_ERROR;
                }
                /* TODO: can the macro content start in the same line? */
                else if(!(new_macro = create_macro_node(current_word))){
                        fclose(file_to_write);
                        fclose(file_to_read);
                        return SYSTEM_ERROR; 
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
            else
                in_macro_flag = false;
                /* TODO: can be more words in line with endmacro? */
        }
    }

    fclose(file_to_write);
    fclose(file_to_read);
    free_macro_list(head_macro);
    return response;
}