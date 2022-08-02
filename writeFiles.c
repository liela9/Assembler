#include "constants.h"
#include "writeFiles.h"
#include "converting.h"

#define ENT_FILE ".ent"
#define EXT_FILE ".ext"
#define OB_FILE ".ob"
#define FIRST_MEMORY_CELL 100


/*Calls the functions of writing the three files*/
bool write_files(char *file_name, multiVars *vars){
    
    return (write_ob_file(file_name, vars) && write_ext_ent_files(file_name, vars));
}


/*Creates and writes the .ob file*/
bool write_ob_file(char *file_name, multiVars *vars){
    FILE *file;
    int index;
	char *temp_char, new_file_name[FILENAME_MAX];

	strcpy(new_file_name, file_name);
    strcat(new_file_name, OB_FILE);/*Linking the extention .ob to the file's name*/
    
    file = fopen(new_file_name, "w");
    if(!file){
        printf("System Error: Could not create new file!\n");
        return false;
    }

    /*
    The first row_content => 
    IC   DC 
    */
	add_line_to_ob(convertDtoB32(IC), convertDtoB32(DC), file);


    for(index = 0; index < sizeof(vars->commands_table)/4; index++)/*TODO : change the sizeof*/
        add_line_to_ob(convertBtoB32(index + FIRST_MEMORY_CELL) 
        ,convertBtoB32(vars->commands_table[index]), file);
    
    
    for(index = 0; index < sizeof(vars->data_table)/4; index++)/*TODO : change the sizeof*/
        add_line_to_ob(convertDtoB32(index + FIRST_MEMORY_CELL)
        ,convertBtoB32(vars->data_table[index]), file);
		

    fclose(file);
    return true;
}


/*Creates and writes the .ent and .ext files*/
bool write_ext_ent_files(char *file_name, multiVars *vars){
    ptr_label h_label;
    ptr_label_apearence h_label_apear;
    FILE *fext, *fent;
    int count_ext, count_ent;
    char ext_name[FILENAME_MAX], ent_name[FILENAME_MAX];
    
    count_ext = 0;
    count_ent = 0;
    fext = NULL;
    fent = NULL;

    h_label = vars->head_label;
    h_label_apear = vars->head_label_apear;
    
	strcpy(ext_name, file_name);
	strcpy(ent_name, file_name);

    /*Linking the extention .ext .ent to the file's name*/
    strcat(ext_name, EXT_FILE);
    strcat(ent_name, ENT_FILE);

    fext = fopen(ext_name, "w");
    fent = fopen(ent_name, "w");

    if(!fext || !fent){
        printf("System Error: Could not create new file!\n");
        return false;
    }

    
    while (h_label){
        while(h_label_apear){
            /*If h_label->name equals to h_label_apear->name*/
            if(!strcmp(h_label->name, h_label_apear->name)){
                if(h_label->type == EXTERNAL){
                    count_ext++;
                    fputs(h_label->name, fext);
                    fputc('\t', fext); 
                    fputs(convertDtoB32(h_label->dec_address), fext);
                    fputc('\n', fext);
                }
                else if(h_label->type == ENTRY){
                    count_ent++;
                    fputs(h_label->name, fent);
                    fputc('\t', fent);
                    fputs(convertDtoB32(h_label->dec_address), fent);
                    fputc('\n', fent);
                }
            }
            h_label_apear = h_label_apear->next;
        }
        h_label = h_label->next;
    }

    if(count_ext == 0)
        remove(ext_name);
    if(count_ent == 0)
        remove(ent_name);
    else{
        fclose(fext);
        fclose(fent);
    }
    return true; 
}



void add_line_to_ob(char *first_item, char *second_item, FILE *file){
   
    fputs(convertDtoB32(first_item), file);
    fputc('\t', file);
    fputs(convertBtoB32(second_item), file);
    fputc('\n', file);
}

