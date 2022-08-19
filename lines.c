#include "constants.h"
#include "lines.h"
#include "utils.h"
#include "converting.h"
#include "lists.h"


responseType create_two_operands_command(int op_code, char *source_op, char *dest_op, multiVars *vars){
    int index_of_source_struct, index_of_dest_struct;
    int source, dest;
    responseType response = SUCCESS;
    
    strtok(dest_op, "\n");/*Remove the '\n' character*/
    /*
    Finds the addressing type. 
    Examples
        Label: X, STR
        Struct: S.1
        register: r1, r2
        Value: #-5, #2
    */
    if((source = is_register(source_op)) != -1){

        if((dest = is_register(dest_op)) != -1){/*Two registers*/
            CHECK_RESPONSE(create_command_line(op_code, 3, 3, vars))
            CHECK_RESPONSE(create_registers_line(source, dest, vars))
        }
        else if((index_of_dest_struct = is_struct(dest_op))){/*Register and struct*/
            CHECK_RESPONSE(create_command_line(op_code, 3, 2, vars))
            CHECK_RESPONSE(create_registers_line(source, 0, vars))
            CHECK_RESPONSE(create_unknown_line(dest_op, vars))
            CHECK_RESPONSE(create_number_line(index_of_dest_struct, vars))
        }
        else {/*Register and label*/
            CHECK_RESPONSE(create_command_line(op_code, 3, 1, vars))
            CHECK_RESPONSE(create_registers_line(source, 0, vars))
            CHECK_RESPONSE(create_unknown_line(dest_op, vars))
        }
    }
        
    else if(source_op[0] == '#'){
        source_op[0] = '\0'; /*Removes the charactar # */

        if((dest = is_register(dest_op)) != -1){/*Value and register*/
            CHECK_RESPONSE(create_command_line(op_code, 0, 3, vars))
            CHECK_RESPONSE(create_number_line(atoi(source_op), vars))
            CHECK_RESPONSE(create_registers_line(0, dest, vars))
        }
        else if((index_of_dest_struct = is_struct(dest_op))){/*Value and struct*/
            CHECK_RESPONSE(create_command_line(op_code, 0, 2, vars))
            CHECK_RESPONSE(create_number_line(atoi(source_op) , vars))
            CHECK_RESPONSE(create_unknown_line(dest_op, vars))
            CHECK_RESPONSE(create_number_line(index_of_dest_struct, vars))
        }
        else{/*Value and label*/
            CHECK_RESPONSE(create_command_line(op_code, 0, 1, vars))
            CHECK_RESPONSE(create_number_line(atoi(source_op), vars))
            CHECK_RESPONSE(create_unknown_line(dest_op, vars))
        }
    }

    else if((index_of_source_struct = is_struct(source_op))){
        if((dest = is_register(dest_op)) != -1){/*Struct and register*/
            CHECK_RESPONSE(create_command_line(op_code, 2, 3, vars))
            CHECK_RESPONSE(create_unknown_line(source_op, vars))
            CHECK_RESPONSE(create_number_line(index_of_source_struct, vars))
            CHECK_RESPONSE(create_registers_line(0, dest, vars))
        }
        else if((index_of_dest_struct = is_struct(dest_op))){/*Struct and struct*/
            CHECK_RESPONSE(create_command_line(op_code, 2, 2, vars))
            CHECK_RESPONSE(create_unknown_line(source_op, vars))
            CHECK_RESPONSE(create_number_line(index_of_source_struct, vars))
            CHECK_RESPONSE(create_unknown_line(dest_op, vars))
            CHECK_RESPONSE(create_number_line(index_of_dest_struct, vars))
        }
        else{/*Struct and label*/
            CHECK_RESPONSE(create_command_line(op_code, 2, 1, vars))
            CHECK_RESPONSE(create_unknown_line(source_op, vars))
            CHECK_RESPONSE(create_number_line(index_of_source_struct, vars))
            CHECK_RESPONSE(create_unknown_line(dest_op, vars))
            
        }
    }

    else {/*The source operand is label*/
        if((dest = is_register(dest_op)) != -1){/*Label and register*/
            CHECK_RESPONSE(create_command_line(op_code, 1, 3, vars))
            CHECK_RESPONSE(create_unknown_line(source_op, vars))
            CHECK_RESPONSE(create_registers_line(0, dest, vars))
        }
        else if((index_of_dest_struct = is_struct(dest_op))){/*Label and struct*/
            CHECK_RESPONSE(create_command_line(op_code, 1, 2, vars))
            CHECK_RESPONSE(create_unknown_line(source_op, vars))
            CHECK_RESPONSE(create_unknown_line(dest_op, vars))
            CHECK_RESPONSE(create_number_line(index_of_dest_struct, vars))
        }
        else {/*Label and label*/
            CHECK_RESPONSE(create_command_line(op_code, 1, 1 , vars))
            CHECK_RESPONSE(create_unknown_line(source_op, vars))
            CHECK_RESPONSE(create_unknown_line(dest_op, vars))
            
        }
    }
    return response;
}

responseType create_no_operands_command(int op_code, multiVars *vars){
    return create_commands_node((op_code<<6), vars);
}

responseType create_one_operand_command(int op_code, char *operand, multiVars *vars){
    int register_num, struct_index, dest_op_addressing = 0, source_op_addressing = 0;
    responseType response;

    strtok(operand, "\n");/*Remove the '\n' character*/

    if((register_num = is_register(operand)) != -1){
        dest_op_addressing = 3;
        if(create_commands_node((op_code<<6) | (source_op_addressing<<4) | (dest_op_addressing<<2), vars) == SUCCESS){
            CHECK_RESPONSE(create_registers_line(register_num, 0 , vars))
        }
        else return SYSTEM_ERROR;
    }

    else if((struct_index = is_struct(operand))){
        dest_op_addressing = 2;
        if(create_commands_node((op_code<<6) | (source_op_addressing<<4) | (dest_op_addressing<<2), vars) == SUCCESS){
            CHECK_RESPONSE(create_unknown_line(operand, vars))
            CHECK_RESPONSE(create_number_line(struct_index, vars))
        }
        else return SYSTEM_ERROR;
    }

    else if(operand[0] == '#'){
        operand = strtok(operand, "#");
        dest_op_addressing = 0;
        if(create_commands_node((op_code<<6) | (source_op_addressing<<4) | (dest_op_addressing<<2), vars) == SUCCESS){
            CHECK_RESPONSE(create_number_line(atoi(operand), vars))
        }
        else return SYSTEM_ERROR;
    }

    else {
        dest_op_addressing = 1;
        if(create_commands_node((op_code<<6) | (source_op_addressing<<4) | (dest_op_addressing<<2), vars) == SUCCESS){
            CHECK_RESPONSE(create_unknown_line(operand, vars))
        }
        else return SYSTEM_ERROR;
    }
    
    return SUCCESS;
}



/*Creates new machine code line (binary) in commandd_table*/
responseType create_command_line(int op_code, int source_op_addressing, 
int dest_op_addressing, multiVars *vars){
    return create_commands_node((op_code<<6) | (source_op_addressing<<4) | (dest_op_addressing<<2), vars);
}


/*Creates new machine code line (binary) for registers*/
responseType create_registers_line(int source, int dest, multiVars *vars){
    return create_commands_node((source<<6) | (dest<<2),  vars);
}


/*Gets numeric value and inserts it as binary to the commands list*/
responseType create_number_line(int number, multiVars *vars){
    return create_commands_node(number<<2, vars);
}


/*At this point, the address of the label (data type) is unknown*/
responseType create_unknown_line(char *label_name, multiVars *vars){
    ptrLabelApearence new_node;
    char *check_number_after_point = NULL;

	check_number_after_point = strchr(label_name, '.');
	strtok(label_name, "."); /*If there is'nt '.' => label_name will stay the same*/

    if(!valid_label_name(label_name)) {
        printf("User Error: in %s.am line %d : '%s' is illegal label name\n", vars->file_name, vars->line_counter, label_name);
        return USER_ERROR;
    }
	new_node = (ptrLabelApearence)calloc_with_check(1, sizeof(labelApearance));
    if(!new_node)
        return SYSTEM_ERROR;
    
	/* Check that there is only 1 or 2 after the '.' */
    if(check_number_after_point) {
    	 check_number_after_point = check_number_after_point+1;
   
    	if(strcmp(check_number_after_point, "1") && strcmp(check_number_after_point, "2")) {
			printf("User Error: in %s.am line %d : '%s' is illegal char after label name'\n", vars->file_name, vars->line_counter, check_number_after_point);
		    return USER_ERROR;
        }
        strcpy(new_node->name, label_name);/*Saves the location of the struct apearence*/
        new_node->is_struct = true;/*Saves the operand as struct*/
        new_node->apeared_with_point = vars->line_counter; /* Saves the line number it found as struct */
    }
    else {
        strcpy(new_node->name, label_name);/*Saves the location of the label apearence*/
        new_node->is_struct = false;/*Saves the operand as not struct*/
    }
    new_node-> index_in_commands_list = IC; 
    new_node->next = NULL;

    if(!(vars->tail_label_apear)){
        vars->head_label_apear = new_node;
        vars->tail_label_apear = new_node;
    }
    else{
        vars->tail_label_apear->next = new_node;
        vars->tail_label_apear = new_node;
    }

    /*Fills the unknown line with the char '?' for now*/
    return create_commands_node('?', vars);
}


/*Creates new machine (binary) code line in data_table*/
responseType create_data_line(char *line, char *type, multiVars *vars){
    char *token = NULL;

    strcpy(token, strtok(line, " ,\t\r\n"));

    /*The type is ".data"*/
    if(!strcmp(type, DATA_WORD)){
        while (token){
            if(create_data_node(atoi(token), vars) == SUCCESS)
                strcpy(token, strtok(NULL, " ,\t\r\n"));
            
            else return SYSTEM_ERROR;
        }
    }

    /*The type is ".string"*/
    if(!strcmp(type, STRING_WORD)){
        int i;
        
        for(i = 1; i < strlen(token)-1; ++i){/*Reads between the ""*/
            /*Converts the ASCII code of the letter to binary*/
            if(create_data_node(token[i], vars) != SUCCESS)
                return SYSTEM_ERROR;
        }
        return create_zero_line(vars);
    }

    /*The type is ".struct"*/
    if(!strcmp(type, STRUCT_WORD)){
        int i;

        strcpy(token, strtok(NULL, " ,\t\r\n"));
        if(create_data_node(atoi(token), vars) != SUCCESS)
            return SYSTEM_ERROR;

        for(i = 1; i < strlen(token)-1; ++i){/*Reads between the ""*/
            if(create_data_node(token[i], vars) != SUCCESS)
                return SYSTEM_ERROR;
        }
        
        if(create_zero_line(vars) != SUCCESS)
            return SYSTEM_ERROR;
    }
    return SUCCESS;
}


/*Creates zero line for '\0' at the end of a string*/
responseType create_zero_line(multiVars *vars){
    return create_data_node(0, vars);
}




