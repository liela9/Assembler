#include "assembler.h"
#include "lines.c"


/*The second step of the Assembler*/
void second_step(ptr_label_apearence head_label_apear, ptr_label head_label){
	int index;
	char *label_name;

	/* Pointers to temporery labelApearance and label_table */
	ptr_label_apearence temp_label_apear;
	ptr_label temp_label;

	temp_label_apear = (ptr_label_apearence) malloc(sizeof(labelApearance));
    temp_label = (ptr_label) malloc(sizeof(label));

	if(!temp_label_apear || !temp_label){
		printf("Memory allocation failed\n");
		exit(0);
	}

	temp_label = head_label;
	
	/*While it is not the end of the list*/
	for(index = 0; !orders_table[index]; index++){
		/*Finds the lines without binary code*/
		if(orders_table[index] == '?'){
			/* Finds the name of label */
			temp_label_apear = head_label_apear;
			while (temp_label_apear){
				if((temp_label_apear->index_in_orders_table) != index)
					temp_label_apear = temp_label_apear->next;
				else
					strcpy(label_name, temp_label_apear->name);

				temp_label_apear = temp_label_apear->next;
			}

			/* Finds the eddress of the label */
			temp_label = head_label;

			while(temp_label){
				/*If temp_label->name != label_name*/
				if(strcmp(temp_label->name, label_name))
      				temp_label = temp_label->next;
      			else/*If they are equals*/
      				orders_table[index] = convertDtB(temp_label->dec_address);

				temp_label = temp_label->next;
      		}


		}
	}

	/* Finds the address of the label and replace the '?' by it*/
	while(temp_label){
		if(strcmp(temp_label->name, label_name))
			temp_label = temp_label->next;
		else
			orders_table[index] = convertDtB(temp_label->dec_address);
	}

	free(temp_label);
	free(temp_label_apear);
}
