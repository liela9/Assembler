#include "assembler.h"



int main(int argc, char *argv[]){
    
    FILE *f;
    int i;
     

    if(argc == 1){
        printf("\nMissing name of file/s\n");
        exit(0);
    }
    
    for(i = 1; i < argc; i++){
        
        if(!(f = fopen(argv[i], "r"))){
            printf("Cannot open %s\n", argv[i]);
            continue;
        }
        
        pre_assembler(f, argv[i]);

        if(first_translation(argv[i]) || second_translation()){
            printf("There is error in file %s\n", argv[i]);
            continue;
        }

        fclose(f);
        free_linked_lists();
        printf("File:  %s run successfully!\n", argv[i]);
    }
    
    return(0);
}