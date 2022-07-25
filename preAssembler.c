#include "assembler.h"

#define MACRO_LENGTH 5



/*Copeis the input file and pastes the macros*/
void pre_assembler(FILE *file_to_read, char *file_name){
    FILE *file_to_write;
    char line[MAX_LINE_LENGTH];
    char copy_line[MAX_LINE_LENGTH];
    char *current_word;
    ptr_macro current_macro;
    int new_macro_flag;

    current_word = NULL;
    new_macro_flag = 0;
    current_macro = NULL;

    strcat(file_name, AM_FILE);/*Linking the extention .am to the file's name*/
    file_to_write = fopen(file_name, "w");
    if(!file_to_write){
        fprintf(stderr,"Could not create %s file", file_name);
        exit(0);
    }

    
    while(fgets(line, MAX_LINE_LENGTH, file_to_read)){
        strcpy(copy_line, line);
        current_word = strtok(copy_line, " \t\n");
        if(new_macro_flag){
            if(strcmp(current_word, "endmacro")){
                strcat(current_macro->macro_content, line);/*Add the relavent content (the line) to the variable "macro_content"*/
                continue;
            }
            else{
                new_macro_flag = 0;
                current_macro = NULL;
                continue;
            }
        }

        if(!strcmp(current_word, "macro")){
            current_word = strtok(NULL, " \t\n");
            if(!current_word){
                /*TODO: error - macro must have a name*/
                return;
            }
            else if(!(current_macro = add_macro(current_word))){
                /*TODO: error - cannot add new macro*/
                return;
            }
            else
                new_macro_flag = 1;
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
}



/*Finds specific word in file*/
long int find_word(char *word, FILE *file){
    char *string = NULL;

    while(fscanf(file, "%s", string))
        if(!strcmp(word, string))
            return ftell(file); /*Return the word's position*/
    
    return 0;
}



