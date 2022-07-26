#include "lines.c"
#include "firstStep.c"

#define ENT_FILE ".ent"
#define EXT_FILE ".ext"
#define OB_FILE ".ob"
#define FIRST_MEMORY_CELL 100


/*Call the functions of writing the three files*/
void write_files(char *file_name){
    
    write_ob_file(file_name);
    write_ext_ent_file(file_name);
}


/*Creates and writes the .ob file*/
void write_ob_file(char *file_name){
    FILE *file;
    int index;
    char *new_file_name;

    /*Defines the file's name .ob*/
    sprintf(new_file_name, "%s%s", file_name, OB_FILE);

    file = fopen(file_name, "w");
    if(!file){
        printf("System Error: Could not create new file!\n");
        exit(0);
    }

    /*
    The first row_content => 
    IC   DC 
    */
    fputs(IC, new_file_name);
    fputc('\t', new_file_name);
    fputs(DC, new_file_name);

    for(index = 0; index < sizeof(orders_table); index++){
        fputs(index + FIRST_MEMORY_CELL, new_file_name);
        fputc('\t', new_file_name);
        fputs(orders_table[index], new_file_name);
    }

    for(index = 0; index < sizeof(data_table); index++){
        fputs(index + FIRST_MEMORY_CELL, new_file_name);
        fputc('\t', new_file_name);
        fputs(data_table[index], new_file_name);
    }

    fclose(file);
    free_orders_table();
    free_data_table();
}


/*Creates and writes the .ent and .ext files*/
void write_ext_ent_files(char *file_name){
    FILE *fext, *fent, *fob;
    ptr_label h_label;
    int count_ext, count_ent;
    char *ext_name, *ent_name, *ob_file_name;
    ptr_label_apearence temp_ptr;
    
    temp_ptr = label_apear_head;
    count_ext = 0;
    count_ent = 0;

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
    ob_file_name = strcat(file_name, OB_FILE);
    /*Assumes the file .ob created and open correctly*/
    fob = fopen(ob_file_name, "r");
    
    h_label = head_label;
    while (h_label){
        while(temp_ptr){
            /*If h_label->name equals to temp_ptr->name*/
            if(!strcmp(h_label->name, temp_ptr->name)){
                if(h_label->type == EXTERNAL){
                    count_ext++;
                    fputs(h_label->name, ext_name);
                    fputc('\t', ext_name); 
                    fputs(convertDtoB32(h_label->dec_address), ext_name);
                }
                else if(h_label->type == ENTRY){
                    count_ent++;
                    fputs(h_label->name, ent_name);
                    fputc('\t', ent_name);
                    fputs(convertDtoB32(h_label->dec_address), ent_name);
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




