#include "constants.h"
#include "preAssembler.h"
#include "firstStep.h"
#include "secondStep.h"
#include "writeFiles.h"
#include "free.h"


#define ERROR(name_of_file) printf("An error occured while processing file %s\n", #name_of_file);
                            



int main(int argc, char *argv[]){
    FILE *f;
    int index;
    multiVars *vars; // TODO: Change to contextVars

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

        /*If there was an error in the pre_assembler*/
        if(pre_assembler(f, argv[index])){
            ERROR(argv[index])
            continue;
        }

        vars = first_step(argv[index]);


        if(vars->there_is_error_flag){
            ERROR(argv[index])
            continue;
        }

        second_step(vars);

	    write_files(argv[index], vars);

        fclose(f);
        // TODO: everything that is freed in "main" should be allocated in "main"
        // The allocating function is the releasing
        free_lists(vars);
        printf("File: %s run successfully!\n", argv[index]);
    }
    
    return(0);
}


