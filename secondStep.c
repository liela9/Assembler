#include "assembler.h"


int second_translation(FILE *f)
{
	int i;
	char *entryLable;
	ptr_label_apearence temp;
	ptr_label temp_label;

   

	/* pointer to labelApearance */
	temp = (ptr_label_apearence) malloc(sizeof(label));

	if(!temp)
	{

		printf("Memory allocation failed\n");

		exit(0);

	}


	/* pointer to label_table */

        temp_label = (ptr_label) malloc(sizeof(label));

        if(!temp_label)
        {

		printf("Memory allocation failed\n");

		exit(0);

        }

	
	/* take care in lebel as type entry */
	for(i = 0; i < strlen(orders_table); i++)
	{
		if(orders_table[i] == '?')
		{
			/* find the name of label */
			temp = labelApearance;
			while (temp)
			{
				if((temp->index_in_orders_table) != i)
					temp = temp->next;
				else
					entryLable = temp->name;
			}
			

			/* find the eddress of the label */
			temp_label = head_label;

			while(temp_label)
			{

				if(strcmp(temp_label->name, entryLable))

      					temp_label = temp_label->next;
      				else
      					orders_table[i] == temp_label->dec_address;
      			}


		}
	}

}
