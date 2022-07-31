#include "constants.h"
#include "writeFiles.h"
#include "converting.h"

#define ENT_FILE ".ent"
#define EXT_FILE ".ext"
#define OB_FILE ".ob"
#define FIRST_MEMORY_CELL 100


/*Call the functions of writing the three files*/
void write_files(char *file_name, multiVars *vars){
    
    write_ob_file(file_name, vars);
    write_ext_ent_files(file_name, vars);
}


/*Creates and writes the .ob file*/
void write_ob_file(char *file_name, multiVars *vars){
    FILE *file;
    int index;
    char *new_file_name;
	char *temp_char;

	new_file_name = NULL;	
	
    /*Defines the file's name .ob*/
    sprintf(new_file_name, "%s%s", file_name, OB_FILE);

    file = fopen(new_file_name, "w");
    if(!file){
        printf("System Error: Could not create new file!\n");
        exit(0);
    }

    /*
    The first row_content => 
    IC   DC 
    */
	temp_char = convertDtoB32(vars->IC);
    fputs(temp_char, file);
    fputc('\t', file);
	temp_char = convertDtoB32(vars->DC);
    fputs(temp_char, file);

    for(index = 0; index < sizeof(vars->orders_table); index++){/*TODO : change the sizeof*/
		temp_char = convertDtoB32(index + FIRST_MEMORY_CELL);
        fputs(temp_char, file);
        fputc('\t', file);
		temp_char = convertDtoB32(vars->orders_table[index]);
        fputs(temp_char, file);
    }

    for(index = 0; index < sizeof(vars->data_table); index++){/*TODO : change the sizeof*/
		temp_char = convertDtoB32(index + FIRST_MEMORY_CELL);
        fputs(temp_char, file);
        fputc('\t', file);
		temp_char = convertDtoB32(vars->data_table[index]);
        fputs(temp_char, file);
    }

    fclose(file);
}


/*Creates and writes the .ent and .ext files*/
void write_ext_ent_files(char *file_name, multiVars *vars){
    FILE *fext, *fent /*,*fob*/;
    ptr_label h_label;
    ptr_label_apearence temp_ptr;
    int count_ext, count_ent;
    char *ext_name, *ent_name/*, *ob_file_name*/;
    
    temp_ptr = vars->head_label_apear;
    count_ext = 0;
    count_ent = 0;
	ext_name = NULL;
	ent_name = NULL;

    /*Defines the file's name .ext /.ent */
    sprintf(ext_name, "%s%s", file_name, EXT_FILE);
    sprintf(ent_name, "%s%s", file_name, ENT_FILE);

    fext = fopen(ext_name, "w");
    fent = fopen(ent_name, "w");

    if(!fext || !fent){
        printf("System Error: Could not create new file!\n");
        exit(0);
    }

    /*Linking the extention .ob to the file's name*/
    /*ob_file_name = strcat(file_name, OB_FILE);*/
    /*Assumes the file .ob created and open correctly*/
    /*fob = fopen(ob_file_name, "r");*/
    
    h_label = vars->head_label;
    while (h_label){
        while(temp_ptr){
            /*If h_label->name equals to temp_ptr->name*/
            if(!strcmp(h_label->name, temp_ptr->name)){
                if(h_label->type == EXTERNAL){
                    count_ext++;
                    fputs(h_label->name, fext);
                    fputc('\t', fext); 
                    fputs(convertDtoB32(h_label->dec_address), fext);
                }
                else if(h_label->type == ENTRY){
                    count_ent++;
                    fputs(h_label->name, fent);
                    fputc('\t', fent);
                    fputs(convertDtoB32(h_label->dec_address), fent);
                }
            }
            temp_ptr = temp_ptr->next;
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
}





