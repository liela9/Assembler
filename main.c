#include "main.h"
#include "preAssembler.h"
#include "firstStep.h"
#include "secondStep.h"
#include "writeFiles.h"
#include "converting.h"
#include "utils.h"

int main(int argc, char *argv[]){

    int i;

    if(argc == 1){/*If there are no names of files in the command line*/
        printf("User Error: Missing name of file/s\n");
        return(1);
    }

    for(i = 1; i < argc; ++i){
        if (process_file(argv[i]) == SYSTEM_ERROR) {
            printf("Program encountered internal error. Shutting down\n");
            return (1);
        }
    }
    
    return(0);
}


responseType process_file(char *file_name){
    multiVars *vars; 
    responseType response;

    vars = (multiVars *)calloc_with_check(1, sizeof(multiVars));
    if (!vars)
        return SYSTEM_ERROR;

    vars->head_label = NULL;
    vars->tail_label = NULL;
    vars->head_label_apear = NULL;
    vars->tail_label_apear = NULL;
    vars->head_data = NULL;
    vars->tail_data = NULL;
    vars->head_commands = NULL;
    vars->tail_commands = NULL;
    vars->head_extern_label = NULL;
    vars->tail_extern_label = NULL;

    if((response = pre_assembler(file_name)) == SUCCESS) { /*Can't proceed if encoutered error */

        if(first_step(file_name, vars) != SUCCESS)
            printf("An error occured while processing file %s in first step\n", file_name);

        
        else if(second_step(file_name, vars) != SUCCESS)
            printf("An error occured while processing file %s in second step\n", file_name);
            
         
        else if(!write_files(file_name, vars))
            printf("An error occured while processing file %s in 'write files'\n", file_name);
            
        else
            printf("File '%s' successfully compiled !\n", file_name);
            
    }
    free_lists(vars);
    free(vars);
    return response;
}


