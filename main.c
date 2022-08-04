#include "main.h"
#include "preAssembler.h"
#include "firstStep.h"
#include "secondStep.h"
#include "writeFiles.h"
#include "free.h"
#include "converting.h"
#include "utils.h"

int main(int argc, char *argv[]){
    int index;

    if(argc == 1){/*If there are no names of files in the command line*/
        printf("User Error: Missing name of file/s\n");
        return(1);
    }
    

    for(index = 1; index < argc; index++){
        if (process_file(argv[index]) == SYSTEM_ERROR) {
            printf("Program encountered internal error. Shutting down\n");
            return (1);
        }
    }
    
    return(0);
}


response_type process_file(char *file_name){
    multiVars *vars; 
    response_type response;

    vars = (multiVars *)malloc_with_check(sizeof(multiVars));
    if (!vars)
        return SYSTEM_ERROR;

    vars->head_label = NULL;
    vars->tail_label = NULL;
    vars->head_label_apear = NULL;
    vars->tail_label_apear = NULL;
    vars->data_table = NULL;
    vars->commands_table = NULL;

    if((response = pre_assembler(file_name)) == SUCCESS) { /*Can't proceed if encoutered error */
        if(!first_step(file_name, vars))
            printf("An error occured while processing file %s\n", file_name);
        if(!second_step(vars))
            printf("An error occured while processing file %s\n", file_name);
        if(!write_files(file_name, vars))
            printf("An error occured while processing file %s\n", file_name);
    
        printf("File '%s' compiled successfully!\n", file_name);
        free_lists(vars);
    }
    free(vars);
    return response;
}


