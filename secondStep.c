#include "constants.h"
#include "secondStep.h"
#include "converting.h"
#include "utils.h"
#include "lists.h"

/*The second step of the Assembler*/
responseType second_step(multiVars *vars){
	FILE *file;
	char *label_name, *line, *label_type;
	int index = 0, i;
	ptrLabelApearence temp_label_apear = vars->head_label_apear;
	ptrlabel temp_label;
	ptrExternLabel temp_extern_label;
	ptrCommand temp_commands = vars->head_commands;
	unsigned long question_mark = convertDtoB('?');
	responseType response = SUCCESS;
	bool is_space_flag;
    vars->line_counter = 0;
    
    if (!(file = open_file_with_extension(vars->file_name, AM_EXTENSION, "r")))
        return SYSTEM_ERROR;
     
    line = (char *)calloc_with_check(MAX_LINE_LENGTH, sizeof(char));
    if (!line)
        return SYSTEM_ERROR;
       
    while(fgets(line, MAX_LINE_LENGTH, file)){
        (vars->line_counter)++;
        is_space_flag = true;
        
        for(i = 0; i < strlen(line); ++i){/*Checks if the current line is "empty"*/
            if(!isspace(line[i])){
                is_space_flag = false;
                break;
            }
        }
        if(is_space_flag)/*If the line is "empty" => read the next line*/
            continue;
        
        label_type = strtok(line, " \t\n\r");
        label_name = strtok(NULL, " \t\n\r");
        
        if(!strcmp(label_type, ENTRY_WORD)){
            
            if(!(temp_label = get_label_by_name(label_name, vars->head_label))){
                printf("User Error: in %s.am line %d : %s 111undefined\n", vars->file_name, vars->line_counter, label_name);
                response = USER_ERROR;
            }
            else if(temp_label->type != EXTERNAL)
                    temp_label->type = ENTRY;
            else{
                 printf("User Error: in %s.am line %d : %s already defined as 'extern'\n", vars->file_name, vars->line_counter, label_name);
                    response = USER_ERROR;
            }
        } 
		if(!strcmp(label_type, EXTERN_WORD)){ 
			
            temp_label = get_label_by_name(label_name, vars->head_label);
            if(!temp_label){
                continue;
            }
            if(temp_label->type != ENTRY)
                    temp_label->type = EXTERNAL;
            else{
                 printf("User Error: in %s.am line %d : %s already defined as 'entry'\n", vars->file_name, vars->line_counter, temp_label->name);
                    response = USER_ERROR;
            }
        }
    }
    label_name = NULL;

	/*While it is not the end of the list*/
	while(temp_commands){
		/*Finds the lines without binary code*/
		if(temp_commands->code == question_mark){
		
			/* Finds the name of the label */
			while (temp_label_apear){
				if((temp_label_apear->index_in_commands_list) == index){
                    
					label_name = temp_label_apear->name;
					break;
				}
				temp_label_apear = temp_label_apear->next;
			}

			temp_label = NULL;
			temp_extern_label = vars->head_extern_label;
            /* Finds the address of the label and replace the '?' by it*/
			while(temp_extern_label){
			    if(!strcmp(temp_extern_label->name, label_name)){
			        temp_commands->code = (convertDtoB(E));
			        break;
			    }
			    temp_extern_label = temp_extern_label->next;
			}
			
			if(temp_commands->code == question_mark){    
                temp_label = get_label_by_name(label_name, vars->head_label);
                temp_commands->code = (convertDtoB(temp_label->dec_address<<2 | R));
            }
			continue;
				
		}
		temp_commands = temp_commands->next;
		index++;
	}

	while(temp_label)
		temp_label = temp_label->next;
	while(temp_label_apear)
		temp_label_apear = temp_label_apear->next;
    free(line);
	return response;
}


