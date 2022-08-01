#include "constants.h"
#include "preAssembler.h"
#include "firstStep.h"
#include "secondStep.h"
#include "writeFiles.h"
#include "free.h"

int main(int argc, char *argv[]){
    FILE *file;
    int index;

    if(argc == 1){/*If there are no names of files in the command line*/
        printf("\nMissing name of file/s\n");
        return(-1);
    }
    

    for(index = 1; index < argc; index++){       
        if(!(file = fopen(argv[index], "r"))){
            printf("Cannot open %s\n", argv[index]);
            continue;
        }
        process_file(file, argv[index]);
        fclose(file);
    }
    
    return(0);
}



void process_file(FILE *file, char *file_name){
    multiVars *vars; /* TODO: Change to contextVars*/

    vars = (multiVars *)malloc(sizeof(multiVars));
    if (!vars) {
        printf("System Error: Memory allocation failed");
        return false;
    }

    vars->head_label = NULL;
    vars->head_label_apear = NULL;
    vars->tail_label_apear = NULL;
    vars->tail_label = NULL;
    vars->data_table = NULL;
    vars->commands_table = NULL;
    
    /*If there was an error in the pre_assembler*/
    if(!pre_assembler(file, file_name) || !first_step(file, file_name) || !second_step(vars) || !write_files(file_name, vars))
        printf("An error occured while processing file %s\n", file_name);
    else
        printf("File: %s run successfully!\n", file_name);
    
    free_lists(vars);
}


