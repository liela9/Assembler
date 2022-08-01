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
    multiVars *vars; /* TODO: Change to contextVars*/
    ptr_label head_label;/*Head node of the list "label"*/
    ptr_label tail_label;/*Tail node of the list "label"*/
    ptr_label_apearence head_label_apear;/*Head node of the list "label_apearence"*/
    ptr_label_apearence tail_label_apear;/*Tail node of the list "label_apearence"*/
    
    unsigned int *orders_table;/*A table of binary machine code for orders*/
    unsigned int *data_table;/*A table of binary machine code for data*/


    if(argc == 1){/*If there are no names of files in the command line*/
        printf("\nMissing name of file/s\n");
        exit(0);
    }

    head_label = NULL;
    tail_label = NULL;
    head_label_apear = NULL;
    tail_label_apear = NULL;
    orders_table = NULL;
    data_table = NULL;


    vars = (multiVars *)malloc(sizeof(multiVars));
    vars->head_label = head_label;
    vars->head_label = tail_label;
    vars->head_label_apear = head_label_apear;
    vars->data_table = data_table;
    vars->tail_label_apear = tail_label_apear;

    vars->head_label = (ptr_label)malloc(sizeof(label));
    vars->head_label_apear = (ptr_label_apearence)malloc(sizeof(labelApearance));
    vars->tail_label = vars->head_label;
    vars->tail_label_apear = vars->head_label_apear;

    vars->orders_table = (unsigned int*)malloc(5 * sizeof(unsigned int));
    vars->data_table = (unsigned int*)malloc(5 * sizeof(unsigned int));

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

        vars = first_step(argv[index], vars);


        if(vars->there_is_error_flag){
            ERROR(argv[index])
            continue;
        }

        second_step(vars);

	    write_files(argv[index], vars);

        fclose(f);
        free_lists(vars);
        printf("File: %s run successfully!\n", argv[index]);
    }
    
    return(0);
}

