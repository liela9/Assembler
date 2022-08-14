#include "constants.h"
#include "writeFiles.h"
#include "converting.h"
#include "utils.h"

/*Calls the functions for writing the three files*/
bool write_files(char *file_name, multiVars *vars){
    
    return (write_ob_file(file_name, vars) && write_ext_file(file_name, vars) && write_ent_file(file_name, vars));
}

/*Creates and writes the .ob file*/
bool write_ob_file(char *file_name, multiVars *vars){
    FILE *file;
    int index = 0;
    ptrCommand temp_commands = vars->head_commands;
    ptrData temp_data = vars->head_data;
    char *c;

    file = open_file_with_extension(file_name, OB_EXTENSION, "w");
    if(!file)
        return false;

    /*
    The first line => 
    IC   DC 
    */
    c = convertDtoB32(IC);
	fputs(c, file);
    fputc('\t', file);
    fputs(convertDtoB32(DC), file);
    fputc('\n', file);
	

    while(temp_commands){
        add_line_to_ob(index + FIRST_MEMORY_CELL, temp_commands->code, file);
        index++;
        temp_commands = temp_commands->next;
    }
    
    while(temp_data){
        add_line_to_ob(index + FIRST_MEMORY_CELL, temp_data->code, file);
        index++;
        temp_data = temp_data->next;
    }

    fclose(file);
    return true;
}

bool write_ext_file(char *file_name, multiVars *vars){
    FILE *fext = NULL;
    ptrLabelApearence h_label_apear;
    ptrExternLabel h_extern_label;
    int count_ext = 0;
    char ext_name[FILENAME_MAX];

    strcpy(ext_name, file_name);
    strcat(ext_name, EXT_EXTENSION);/*Linking the extention .ext to the file's name*/

    fext = fopen(ext_name, "w");
    if(!fext){
        printf("System Error: Could not create new file!\n");
        return false;
    }

    h_extern_label = vars->head_extern_label;

    while(h_extern_label){
        h_label_apear = vars->head_label_apear;
        while(h_label_apear){
            /*If h_label->name equals to h_label_apear->name*/
            if(!strcmp(h_extern_label->name, h_label_apear->name)){
                
                count_ext++;
                fputs(h_extern_label->name, fext);
                fputc('\t', fext); 
                fputs(convertDtoB32(h_label_apear->index_in_commands_list + FIRST_MEMORY_CELL), fext);
                fputc('\n', fext);
            }
            h_label_apear = h_label_apear->next;
        }
        h_extern_label = h_extern_label->next;
    }

    if(count_ext == 0)
        remove(ext_name);
    else
        fclose(fext);
    return true; 
}

/*Creates and writes the .ent and .ext files*/
bool write_ent_file(char *file_name, multiVars *vars){
    ptrlabel h_label;
    FILE *fent = NULL;
    int count_ent = 0;
    char ent_name[FILENAME_MAX];
    
    h_label = vars->head_label;
	
	strcpy(ent_name, file_name);
    /*Linking the extention .ent to the file's name*/
    strcat(ent_name, ENT_EXTENSION);
    
    fent = fopen(ent_name, "w");

    if(!fent){
        printf("System Error: Could not create new file!\n");
        return false;
    }

    while (h_label){
        if(h_label->type == ENTRY){
            count_ent++;
            fputs(h_label->name, fent);
            fputc('\t', fent);
            fputs(convertDtoB32(h_label->dec_address), fent);
            fputc('\n', fent);
        }
        h_label = h_label->next;    
    }
    
    if(count_ent == 0)
        remove(ent_name);
    else
        fclose(fent);
    return true; 
}



void add_line_to_ob(int first_item, unsigned long second_item, FILE *file){
   
    fputs(convertDtoB32(first_item), file);
    fputc('\t', file);
    fputs(convertBtoB32(second_item), file);
    fputc('\n', file);
}




