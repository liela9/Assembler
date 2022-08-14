#include "constants.h"
#include "secondStep.h"
#include "converting.h"
#include "utils.h"
#include "lists.h"

/*The second step of the Assembler*/
responseType second_step(char *file_name, multiVars *vars){
	FILE *file;
	char label_name[MAX_LABEL_LENGTH], *line, *token;
	int index = 0, line_counter = 0;
	ptrLabelApearence temp_label_apear = vars->head_label_apear;
	ptrlabel temp_label;
	ptrCommand temp_commands = vars->head_commands;
	unsigned long question_mark = convertDtoB('?');
	responseType response = SUCCESS;
    
    if (!(file = open_file_with_extension(file_name, AM_EXTENSION, "r")))
        return SYSTEM_ERROR;

    line = (char *)calloc_with_check(MAX_LINE_LENGTH, sizeof(char));
    if (!line)
        return SYSTEM_ERROR;
        
    while(fgets(line, MAX_LINE_LENGTH, file)){
        line_counter++;
        token = strtok(line, " \t\n");
        
        if(!strcmp(token, ENTRY_WORD)){
        
            token = strtok(NULL, " \t\n");
            if(!(temp_label = get_label_by_name(token, vars->head_label))){
                printf("User Error in %s.am line %d : %s undefined\n", file_name, line_counter, token);
                response = USER_ERROR;
            }
            else{
                if(temp_label->type != EXTERNAL)
                    temp_label->type = ENTRY;
                else {
                    printf("User Error in %s.am line %d : %s already defined as 'extern'\n", file_name, line_counter, token);
                    response = USER_ERROR;
                }
            } 
                
        }
    }

	/*While it is not the end of the list*/
	while(temp_commands){
		/*Finds the lines without binary code*/
		if(temp_commands->code == question_mark){
		
			/* Finds the name of the label */
			while (temp_label_apear){
				if((temp_label_apear->index_in_commands_list) == index){
					reset_array(label_name);
					strcpy(label_name, temp_label_apear->name);
					break;
				}
				temp_label_apear = temp_label_apear->next;
			}

			temp_label = NULL;
            /* Finds the address of the label and replace the '?' by it*/
			temp_label = get_label_by_name(label_name, vars->head_label);
			if(temp_label->type == EXTERNAL)
				temp_commands->code = (convertDtoB(temp_label->dec_address<<2 | E));
			else temp_commands->code = (convertDtoB(temp_label->dec_address<<2 | R));
			break;
				
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

