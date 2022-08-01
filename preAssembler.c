#include "constants.h"
#include "preAssembler.h"
#include "macro.h"


/*Copeis the input file and pastes the macros*/
bool pre_assembler(FILE *file_to_read, char *file_name){
    FILE *file_to_write;
    char line[MAX_LINE_LENGTH], copy_line[MAX_LINE_LENGTH];
    char *current_word, new_file_name[FILENAME_MAX];
    ptr_macro *current_macro, head_macro;
    bool there_is_error_flag, in_macro_flag;
   
    strcpy(new_file_name, file_name);
    strcat(new_file_name, AM_EXTENSION); /*Linking the extension .am to the file's name*/
    file_to_write = fopen(new_file_name, "w");
    if(!file_to_write){
        /* TODO: replace all system errors */
        printf("System Error: Could not create %s file", new_file_name);
        return false;
    }
    
    in_macro_flag = false;
    there_is_error_flag = false;
    current_word = NULL;
    current_macro = NULL;
    head_macro = NULL;

    /*Reads a line*/
    while(fgets(line, MAX_LINE_LENGTH, file_to_read)){
        strcpy(copy_line, line);
        current_word = strtok(copy_line, " \t\n");

        if (!in_macro_flag) {
            /*If the current word is "macro"*/
            if(!strcmp(current_word, "macro")){
                current_macro = (ptr_macro *)malloc(sizeof(ptr_macro));

                if(!(current_word = strtok(NULL, " \t\n"))){
                    /* TODO: add function for "user error" */
                    printf("Error: Macro must have a name\n");
                    return false;
                }
                /* TODO: can the macro content start in the same line? */
                else if(!(insert_macro(head_macro, *current_macro, current_word))){
                    return false;
                }
                else
                    in_macro_flag = true;
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
            if(strcmp(current_word, "endmacro")){
                /*Add the content (the line) to the variable "macro_content"*/
                strcat((*current_macro)->macro_content, line);
                continue;
            }
            else{
                in_macro_flag = false;
                current_macro = NULL;
                continue;
            }
        }
    }
    fclose(file_to_write);
    free_macro_list(head_macro);

    return !there_is_error_flag;
}



/*Finds specific word in file*/
long int find_word(char *word, FILE *file){
    char *string = NULL;

    while(fscanf(file, "%s", string))
        /*If 'word' equals to 'string'*/
        if(!strcmp(word, string))
            return ftell(file); /*Return the word's position*/
    
    return 0;
}




