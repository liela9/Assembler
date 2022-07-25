#include "assembler.h"



int main(int argc, char *argv[]){
    
    FILE *f;
    int i;
     

    if(argc == 1){
        printf("\nMissing name of file/s\n");
        exit(0);
    }
    
    for(i = 0; i < argc - 1; i++){
        
        if((f = fopen(argv[i], "r")) == NULL){
            printf("Cannot open %s\n", argv[i]);
            continue;
        }
        
        pre_assembler(f, argv[i]);
        

        if(first_translation(&am)){
            printf("There is error in file %s\n", argv[i]);
            continue;
        }

        if(second_translation(&am)){
            printf("There is error in file %s\n", argv[i]);
            continue;
        }

        fclose(f);
        void write_files(char *, ptr_label );
        free_linked_lists();
    }
    
    return(0);
}