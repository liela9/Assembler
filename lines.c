#include "constants.h"
#include "lines.h"
#include "utils.h"
#include "converting.h"
#include "label.h"
#include "dataList.h"
#include "commandsList.h"



responseType create_two_operands_command(unsigned long op_code, char *source_op, char *dest_op, multiVars *vars){
    int index_of_source_struct, index_of_dest_struct;
    int source, dest;
    
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
            create_command_line(op_code, convertDtoB(3), convertDtoB(3), vars->tail_commands, vars->head_commands);
            create_registers_line(source, dest, vars->tail_commands, vars->head_commands);
        }
        else if(label_exists(dest_op, vars->head_label)){/*Register and label*/
                create_command_line(op_code, convertDtoB(3), convertDtoB(1), vars->tail_commands, vars->head_commands);
                create_registers_line(source, 0, vars->tail_commands, vars->head_commands);
                create_unknown_line( dest_op, vars->tail_label_apear, vars->tail_commands, vars->head_commands);
            }
            else if((index_of_dest_struct = is_struct(dest_op))){/*Register and struct*/
                    create_command_line(op_code, convertDtoB(3), convertDtoB(2), vars->tail_commands, vars->head_commands);
                    create_registers_line(source, 0, vars->tail_commands, vars->head_commands);
                    create_unknown_line(dest_op, vars->tail_label_apear, vars->tail_commands, vars->head_commands);
                    create_number_line(index_of_dest_struct, vars->tail_data, vars->head_commands);
                }
    }
        
    else if(label_exists(source_op, vars->head_label)){
        if((dest = is_register(dest_op)) != -1){/*Label and register*/
            create_command_line(op_code, convertDtoB(1), convertDtoB(3), vars->tail_commands, vars->head_commands);
            create_unknown_line(dest_op, vars->tail_label_apear, vars->tail_commands, vars->head_commands);
            create_registers_line(0, dest, vars->tail_commands, vars->head_commands);
        }
        else if((index_of_dest_struct = is_struct(dest_op))){/*Label and struct*/
                create_command_line(op_code, convertDtoB(1), convertDtoB(2), vars->tail_commands, vars->head_commands);
                create_unknown_line(dest_op, vars->tail_label_apear, vars->tail_commands, vars->head_commands);
                create_unknown_line(dest_op, vars->tail_label_apear, vars->tail_commands, vars->head_commands);
                create_number_line(index_of_dest_struct, vars, vars->head_commands);
            }
            else if(label_exists(dest_op, vars->head_label)){/*Label and label*/
                    create_command_line(op_code, convertDtoB(1), convertDtoB(1) , vars->tail_commands, vars->head_commands);
                    create_unknown_line(dest_op, vars->tail_label_apear, vars->tail_commands, vars->head_commands);
                    create_unknown_line(dest_op, vars->tail_label_apear, vars->tail_commands, vars->head_commands);
                }
    }
        
    else if(source_op[0] == '#'){
        source_op[0] = '\0'; /*Removes the charactar # */

        if((dest = is_register(dest_op)) != -1){/*Value and register*/
            create_command_line(op_code, convertDtoB(0), convertDtoB(3), vars->tail_commands, vars->head_commands);
            create_number_line(atoi(source_op), vars->tail_commands, vars->head_commands);
            create_registers_line(0, dest, vars->tail_commands, vars->head_commands);
        }
        else if(label_exists(dest_op, vars->head_label)){/*Value and label*/
                create_command_line(op_code, convertDtoB(0), convertDtoB(1), vars->tail_commands, vars->head_commands);
                create_number_line(atoi(source_op), vars->tail_commands, vars->head_commands);
                create_unknown_line(dest_op, vars->tail_label_apear, vars->tail_commands, vars->head_commands);
            }
            else if((index_of_dest_struct = is_struct(dest_op))){/*Value and struct*/
                    create_command_line(op_code, convertDtoB(0), convertDtoB(2), vars->tail_commands, vars->head_commands);
                    create_number_line(atoi(source_op) , vars->tail_commands, vars->head_commands);
                    create_unknown_line(dest_op, vars->tail_label_apear, vars->tail_commands, vars->head_commands);
                    create_number_line(index_of_dest_struct, vars->tail_commands, vars->head_commands);
                }
    }
        
    
    else if((index_of_source_struct = is_struct(source_op))){
        if((dest = is_register(dest_op)) != -1){/*Struct and register*/
            create_command_line(op_code, convertDtoB(2), convertDtoB(3), vars->tail_commands, vars->head_commands);
            create_unknown_line(dest_op, vars->tail_label_apear, vars->tail_commands, vars->head_commands);
            create_number_line(index_of_source_struct, vars->tail_commands, vars->head_commands);
            create_registers_line(0, dest , vars->tail_commands, vars->head_commands);
        }
        else if((index_of_dest_struct = is_struct(dest_op))){/*Struct and struct*/
                create_command_line(op_code, convertDtoB(2), convertDtoB(2), vars->tail_commands, vars->head_commands);
                create_unknown_line(dest_op, vars->tail_label_apear, vars->tail_commands, vars->head_commands);
                create_number_line(index_of_source_struct, vars->tail_commands, vars->head_commands);
                create_unknown_line(dest_op, vars->tail_label_apear, vars->tail_commands, vars->head_commands);
                create_number_line(index_of_dest_struct, vars->tail_commands, vars->head_commands);
        }
        else{/*Struct and label*/
            create_command_line(op_code, convertDtoB(2), convertDtoB(1), vars->tail_commands, vars->head_commands);
            create_unknown_line(dest_op, vars->tail_label_apear, vars->tail_commands, vars->head_commands);
            create_number_line(index_of_source_struct, vars->tail_commands, vars->head_commands);
            create_unknown_line(dest_op, vars->tail_label_apear, vars->tail_commands, vars->head_commands);
        }
    }

}

responseType create_no_operands_command(unsigned long op_code, multiVars *vars){
    IC++;
    return create_commands_node(op_code, vars->tail_commands, vars->head_commands);
}

responseType create_one_operand_command(unsigned long op_code, char *operand, multiVars *vars){
    bool operand_type;
    responseType response;

    IC++;
    if(create_commands_node(op_code, vars->tail_commands, vars->head_commands) != SUCCESS)
        return SYSTEM_ERROR;

    if((operand_type = is_register(operand)) != -1)
        response = create_registers_line(operand, 0 , vars->tail_commands, vars->head_commands);

    if(operand_type = is_struct(operand))
        response = create_unknown_line(strtok(operand, "."), vars->tail_label_apear, vars->tail_commands, vars->head_commands);

    if(operand_type = label_exists(operand, vars->head_label))
        response = create_unknown_line(operand, vars->tail_label_apear, vars->tail_commands, vars->head_commands);

    return response;
}



/*Creates new machine code line (binary) in commandd_table*/
responseType create_command_line(unsigned long op_code, long source_op_addressing, 
long dest_op_addressing, ptrCommand tail_commands, ptrCommand head_commands){
    IC++;
    return create_commands_node((op_code<<6) & (source_op_addressing<<4) & 
    (dest_op_addressing<<2) & (convertDtoB(~0)<<2), tail_commands, head_commands);
}


/*Creates new machine code line (binary) for registers*/
responseType create_registers_line(int source, int dest, ptrCommand tail_commands, 
ptrCommand head_commands){
    IC++;
    return create_commands_node((convertDtoB(source)<<6) & 
    (convertDtoB(dest)<<2) & (convertDtoB(~0)<<2), tail_commands, head_commands);
}


/*
Gets numeric value
And insert it as binary to the commands list
*/
responseType create_number_line(int number, ptrCommand tail_commands, ptrCommand head_commands){
    IC++;
    return create_commands_node(convertDtoB(number), tail_commands, head_commands);
}


/*At this point, the address of the label (data type) is unknown*/
responseType create_unknown_line(char *label_name, ptrLabelApearence tail_label_apear, 
ptrCommand tail_commands, ptrCommand head_commands){
    ptrLabelApearence temp_node;

    IC++;
    temp_node = (ptrLabelApearence)calloc_with_check(1, sizeof(labelApearance));
    if(!temp_node)
        return SYSTEM_ERROR;

    /*Saves the location of the label/struct apearence*/
    strcpy(temp_node->name, label_name);
    temp_node-> index_in_commands_list = IC; 
    temp_node->next = NULL;

    /*Fills the unknown line with the char '?' for now*/
    return create_commands_node('?', tail_commands, head_commands);
}


/*Creates new machine (binary) code line in data_table*/
responseType create_data_line(char *line, char *type, ptrData tail_data, ptrData head_data){
    char *token = NULL;

    strcpy(token, strtok(line, " ,\t\r"));

    /*The type is ".data"*/
    if(!strcmp(type, DATA_WORD)){
        while (token){
            if(create_data_node(convertDtoB(atoi(token)), tail_data, head_data) == SUCCESS){
                DC++;
                strcpy(token, strtok(NULL, " ,\t\r"));
            }
            else return SYSTEM_ERROR;
        }
    }

    /*The type is ".string"*/
    if(!strcmp(type, STRING_WORD)){
        int i;
        
        for(i = 1; i < strlen(token)-1; ++i){/*Reads between the ""*/
            /*Converts the ASCII code of the letter to binary*/
            if(create_data_node(convertDtoB(token[i]), tail_data, head_data) == SUCCESS)
                DC++;
            else return SYSTEM_ERROR;
        }

        DC++;
        return create_zero_line(tail_data, head_data);
    }

    /*The type is ".struct"*/
    if(!strcmp(type, STRUCT_WORD)){
        int i;

        strcpy(token, strtok(NULL, " ,\t\r"));
        if(create_data_node(convertDtoB(atoi(token)), tail_data, head_data) == SUCCESS)
            DC++;
        else return SYSTEM_ERROR;

        for(i = 1; i < strlen(token)-1; ++i){/*Reads between the ""*/
            if(create_data_node(convertDtoB(token[i]), tail_data, head_data) == SUCCESS)
                DC++;
            else return SYSTEM_ERROR;
        }
        
        if(create_zero_line(tail_data, head_data) == SUCCESS)
            DC++;
        else return SYSTEM_ERROR;
    }
    return SUCCESS;
}


/*Creates zero line for '\0' at the end of a string*/
responseType create_zero_line(ptrData tail_data, ptrData head_data){
    DC++;
    return create_data_node(convertDtoB(0), tail_data, head_data);
}




