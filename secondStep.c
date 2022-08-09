#include "constants.h"
#include "secondStep.h"
#include "converting.h"
#include "utils.h"

/*The second step of the Assembler*/
bool second_step(multiVars *vars){
	char label_name[MAX_LABEL_LENGTH];
	int index = 0;
	ptrLabelApearence temp_label_apear = vars->head_label_apear;
	ptrlabel temp_label;
	ptrCommand temp_commands = vars->head_commands;
	unsigned long question_mark = convertDtoB('?');


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

			temp_label = vars->head_label;
            /* Finds the address of the label and replace the '?' by it*/
			while(temp_label){
				if(!strcmp(temp_label->name, label_name)){
					if(temp_label->type == EXTERNAL)
						temp_commands->code = (convertDtoB(temp_label->dec_address<<2 | E));
      				else temp_commands->code = (convertDtoB(temp_label->dec_address<<2 | R));
      				break;
				}
      			temp_label = temp_label->next;
      		}
		}
		temp_commands = temp_commands->next;
		index++;
	}
	free(temp_label);
	free(temp_label_apear);
	free(temp_commands);
	return true;
}

