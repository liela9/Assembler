#include "assembler.h"



int main(int argc, char *argv[]){
    
    FILE *f;
    int index;
     

    if(argc == 1){/*If there are no names of files in the command line*/
        printf("\nMissing name of file/s\n");
        exit(0);
    }
    
    for(index = 1; index < argc; index++){
        
        if(!(f = fopen(argv[index], "r"))){
            printf("Cannot open %s\n", argv[index]);
            continue;
        }
        
        pre_assembler(f, argv[index]);

        
        if(first_step(argv[index])){/*If there was error at the first step*/
            printf("There is error in file %s\n", argv[index]);
            continue;/*Continue to the next assembler file*/
        }

	    write_files(argv[index]);

        fclose(f);
        free_linked_lists();
        printf("File:  %s run successfully!\n", argv[index]);
    }
    
    return(0);
}