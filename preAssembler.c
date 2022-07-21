
#include "assembler.h"

#define MACRO_LENGTH 5
#define ENDMACRO_LENGTH 8


/*Copeis the input file and pastes the macro*/
FILE * first_copy_file(FILE *f){
    FILE *copy;
    long int *macro_pos, *endmacro_pos;
    char *row, *word, **macro_name, **macro_content;
    int index;

    index = 0;
    there_is_error = 0;    
    
    
    /*Saving all the macro's positions and contents*/
    while(*macro_pos = find_word("macro", f) -MACRO_LENGTH){
        fscanf(f, "%s", *macro_name);

        if(!(endmacro_pos = find_word("endmacro", f))){
            there_is_error = 1;
            printf("Missing 'endmacro'\n");
        }
        else{
            fread(*macro_content, endmacro_pos - macro_pos +1, 1, f);
            *macro_content++;
            *endmacro_pos++;
        }
        *macro_pos++;
        *macro_name++;
    }
    rewind(f);

    /*Reads every row frow f and pastes the relavents into 'copy'*/
    while(row = fgets(row, ROW_LENGTH, f)){

        while(fscanf(f, "%s", word)){
            if(strcmp(*macro_name, word) && macro_pos < ftell(f)){
                fputs(*macro_content, copy);
                fsetpos(f, &*endmacro_pos);
                *macro_name++;
                *macro_content++;
                *endmacro_pos++;
            }
            else {
                fputs(row, copy);
                fputc('\n', copy);
            }
        }
    }
    return &copy;
}



/*Finds specific word in file*/
long int find_word(char *word, FILE *file){
    char *s;

    while(fscanf(file, "%s", s))
        if(!strcmp(word, s))
            return ftell(file); /*Return the word's position*/
    
    return 0;
}





