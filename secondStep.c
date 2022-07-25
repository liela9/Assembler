#include "assembler.h"


void second_translation(ptr_label_apearence head, ptr_label head_label, unsigned int *orders_table)
{
	int index;
	char *lable_name;
	ptr_label_apearence temp;
	ptr_label temp_label;

   

	/* pointers to labelApearance and label_table */
	temp = (ptr_label_apearence) malloc(sizeof(label));
        temp_label = (ptr_label) malloc(sizeof(label));

	if(!temp || !temp_label)
	{

		printf("Memory allocation failed\n");

		exit(0);

	}

        
	
	/* take care in lebel as type entry */
	for(index = 0; !orders_table[index]; index++)
	{
		if(orders_table[index] == '?')
		{
			/* find the name of label */
			temp = head;
			while (temp)
			{
				if((temp->index_in_orders_table) != index)
					temp = temp->next;
				else
					strcpy(lable_name, temp->name);
			}
			

			/* find the eddress of the label */
			temp_label = head_label;

			while(temp_label)
			{

				if(strcmp(temp_label->name, lable_name))

      					temp_label = temp_label->next;
      				else
      					orders_table[index] = convertDtB(temp_label->dec_address);
      			}


		}
	}

}
