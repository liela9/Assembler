#include "constants.h"
#include "secondStep.h"
#include "converting.h"


/*The second step of the Assembler*/
bool second_step(multiVars *vars){
	int index;
	char *label_name;
	ptr_label_apearence temp_label_apear;
	ptr_label temp_label;

	label_name = NULL;

	temp_label = vars->head_label;
	temp_label_apear = vars->head_label_apear;
	
	/*While it is not the end of the list*/
	for(index = 0; !vars->commands_table[index]; index++){
		/*Finds the lines without binary code*/
		if(vars->commands_table[index] == '?'){
			temp_label_apear = vars->head_label_apear;

			/* Finds the name of label */
			while (temp_label_apear){
				if((temp_label_apear->index_in_commands_table) == index){
					strcpy(label_name, temp_label_apear->name);
					continue;
				}
				temp_label_apear = temp_label_apear->next;
			}

			/* Finds the eddress of the label */
			temp_label = vars->head_label;
            /* Finds the address of the label and replace the '?' by it*/
			while(temp_label){
				if(!strcmp(temp_label->name, label_name))
      				vars->commands_table[index] = convertDtoB(temp_label->dec_address);
      				continue;
      			temp_label = temp_label->next;
      		}
		}
	}

	free(temp_label);
	free(temp_label_apear);
	return true;
}

