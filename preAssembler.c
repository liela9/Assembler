#include "constants.h"
#include "macro.h"
#include "utils.h"
#include "preAssembler.h"


/*Copeis the input file and pastes the macros*/
responseType pre_assembler(multiVars *vars){
    FILE *file_to_read, *file_to_write;
    char line[MAX_LINE_LENGTH], copy_line[MAX_LINE_LENGTH];
    ptrMacro new_macro, head_macro = NULL, current_macro = NULL;
    bool in_macro_flag = false;
    responseType response = SUCCESS;
    char *current_word = NULL;
    vars->line_counter = 0;

    if (!(file_to_read = open_file_with_extension(vars->file_name, AS_EXTENSION, "r")) || !(file_to_write = open_file_with_extension(vars->file_name, AM_EXTENSION, "w+b")))
        return USER_ERROR;

    /*Reads a line*/
    while(fgets(line, MAX_LINE_LENGTH, file_to_read)){
        (vars->line_counter)++;
        strcpy(copy_line, line);

        current_word = strtok(copy_line, " \t\n");
        if(!current_word)/*If it is empty line*/
            continue;
            
        if (!in_macro_flag) {
            /*If the current word is "macro"*/
            if(!strcmp(current_word, MACRO_WORD)){
                current_word = strtok(NULL, " \t\r\n");
                if(!current_word ){
                    printf("User Error: in %s: line %d : macro must have a name\n", vars->file_name, vars->line_counter);
                    response = USER_ERROR;
                }
                else if(is_reserved_word(current_word)){
                    printf("User Error: can't use reserved word '%s' as macro name.\n", current_word);
                    response = USER_ERROR;
                }   
                else if(macro_exists(head_macro, current_word)){
                    printf("User Error: macro name '%s' is already exist.\n", current_word);
                    response = USER_ERROR;
                }
                
                else {
                    if(strtok(NULL, " \t\r\n")){
                        printf("User Error: in %s: line %d : extra content after macro name!\n", vars->file_name, vars->line_counter);
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
                ptrMacro lookup_macro = NULL;
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
                if(strtok(NULL, " \t\r\n")){
                    printf("User Error: in %s: line %d : extra content after 'endmacro'!\n", vars->file_name, vars->line_counter);
                    response = USER_ERROR;
                }
                in_macro_flag = false;
            }
        }
    }


    fclose(file_to_write);
    fclose(file_to_read);
    free_macro_list(head_macro);
    return response;
}


/*int c = fgetc(file_to_write);
    In case of zero macros
    if(c == EOF){
        char ch;
        Copy the .as file to .am file
        while((ch = fgetc(file_to_read)) != EOF)
            fputc(ch, file_to_write);
    }*/
