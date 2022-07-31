#include "constants.h"
#include "preAssembler.h"
#include "firstStep.h"
#include "secondStep.h"
#include "writeFiles.h"
#include "free.h"


int main(int argc, char *argv[]){
    FILE *f;
    int index;
    multiVars *vars;

    vars = (multiVars *)malloc(sizeof(multiVars));
     

    if(argc == 1){/*If there are no names of files in the command line*/
        printf("\nMissing name of file/s\n");
        exit(0);
    }
    
    for(index = 1; index < argc; index++){
        
        if(!(f = fopen(argv[index], "r"))){
            printf("Cannot open %s\n", argv[index]);
            continue;
        }

        /*If there was error at the pre Assembler*/
        if(pre_assembler(f, argv[index])){
            printf("There is error in file %s\n", argv[index]);
            continue;
            /*Continue to the next assembler file*/
        }

        vars = first_step(argv[index]);

        if(vars->there_is_error_flag){
            printf("There is error in file %s\n", argv[index]);
            continue;
            /*Continue to the next assembler file*/
        }

        second_step(vars);

	    write_files(argv[index], vars);

        fclose(f);
        free_lists(vars);
        printf("File: %s run successfully!\n", argv[index]);
    }
    
    return(0);
}


