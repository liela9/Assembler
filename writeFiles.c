#include "lines.c"
#include "free.c"

#define ENT_FILE ".ent"
#define EXT_FILE ".ext"
#define OB_FILE ".ob"
#define FIRST_MEMORY_CELL 100


void write_files(char *file_name, ptr_label head_label){
    write_ob_file(file_name);
    write_ext_ent_file(file_name, head_label);
}


void write_ob_file(char *file_name){
    FILE *f;
    int i;
    char *new_file;

    /*Defines the file's name .ob*/
    sprintf(new_file, "%s%s", file_name, OB_FILE);

    f = fopen(file_name, "w");
    if(!f){
        printf("Could not create new file!\n");
        exit(0);
    }

    /*The first row => IC   DC */
    fputs(IC, new_file);
    fputc('\t', new_file);
    fputs(DC, new_file);

    for(i = 0; i < sizeof(binar_lines); i++){
        fputs(i + FIRST_MEMORY_CELL, new_file);
        fputc('\t', new_file);
        fputs(binar_lines[i], new_file);
    }

    fclose(f);
    free_binar_lines(binar_lines);
}


void write_ext_ent_files(char *file_name, ptr_label head_label){
    FILE *fext, *fent, *fob;
    ptr_label h_label;
    int count_ext, count_ent, i;
    char *ext_name, *ent_name, *row, *ob_file_name;
    
    count_ext = 0;
    count_ent = 0;

    /*Defines the file's name .ext / .ent */
    sprintf(ext_name, "%s%s", file_name, EXT_FILE);
    sprintf(ent_name, "%s%s", file_name, ENT_FILE);

    fext = fopen(ext_name, "w");
    fent = fopen(ent_name, "w");

    if(!fext || !fent){
        printf("Could not create new file!\n");
        exit(0);
    }

    ob_file_name = strcat(file_name, OB_FILE);
    fob = fopen(ob_file_name, "r");/*Assumes the file .ob created correctly*/
    
    h_label = head_label;
    while (h_label){
        for(i = 0; i < sizeof(label_apearances); i++){
            if(!strcmp(h_label->name, label_apearances[i])){
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




