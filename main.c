#include "assembler.h"


#define error(a) if(there_is_error){ \
            printf("Error: cannot contuniue compiling the file:  %s\n", #a);\
            continue;\
        }

/*global => NULL*/
ptr_label head_label;
ptr_label tail_label;


int main(int argc, char argv[]){
    
    FILE *f, *am;
    int i;
     

    if(argc == 1){
        printf("\nMissing name of file/s\n");
        exit(0);
    }
    
    for(i = 0; i < argc - 1; i++){
        
        there_is_error = 0;
        if((f = fopen(argv[i], "r")) == NULL){
            printf("Cannot open %s\n", argv[i]);
            continue;
        }
        
        am = first_copy_file(f);
        error(argv[i])

        if(first_translation(&am)){
            printf("There is error in file %s\n", argv[i]);
            continue;
        }

        if(second_translation(&am)){
            printf("There is error in file %s\n", argv[i]);
            continue;
        }

        write_files(argv[i], head_label);
        fclose(f);

        free_label_table(head_label);
    }
    printf("Succsessed Compiling for: %s\n", argv[i]);
    
    return(0);
}