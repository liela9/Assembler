#include "constants.h"
#include "preAssembler.h"
#include "macro.h"

#define MACRO_LENGTH 5


/*Copeis the input file and pastes the macros*/
bool pre_assembler(FILE *file_to_read, char *file_name){
    FILE *file_to_write;
    char line[MAX_LINE_LENGTH];
    char copy_line[MAX_LINE_LENGTH];
    char *current_word;
    ptr_macro current_macro;
    bool there_is_error_flag;
    bool new_macro_flag;

    new_macro_flag = false;
    there_is_error_flag = false;
    current_word = NULL;
    current_macro = NULL;

    strcat(file_name, AM_FILE);/*Linking the extention .am to the file's name*/
    file_to_write = fopen(file_name, "w");
    if(!file_to_write){
        fprintf(stderr,"Could not create %s file", file_name);
        exit(0);
    }

    /*Reads s line*/
    while(fgets(line, MAX_LINE_LENGTH, file_to_read)){
        strcpy(copy_line, line);
        current_word = strtok(copy_line, " \t\n");

        /*If this is new macro*/
        if(new_macro_flag){
            /*If the current word is not "endmacro"*/
            if(strcmp(current_word, "endmacro")){
                /*Add the content (the line) to the variable "macro_content"*/
                strcat(current_macro->macro_content, line);
                continue;
            }
            else{
                new_macro_flag = false;
                current_macro = NULL;
                continue;
            }
        }
        /*If the current word is "macro"*/
        if(!strcmp(current_word, "macro")){
            current_word = strtok(NULL, " \t\n");
            if(!current_word){
                there_is_error_flag = true;
                printf("Error: Macro must have a name\n");
            }
            else if(!(current_macro = add_macro(current_word))){
                there_is_error_flag = true;
            }
            else
                new_macro_flag = true;
        }
        else{
            ptr_macro lookup_macro = NULL;
            if(!(lookup_macro = get_macro_by_id(current_word))){
                fputs(line, file_to_write);
            }
            else
                fputs(lookup_macro->macro_content, file_to_write);
        }
    }
    fclose(file_to_write);
    free(current_macro);
    free_macro_list();

    return there_is_error_flag;
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




