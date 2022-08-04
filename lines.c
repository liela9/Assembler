#include "constants.h"
#include "lines.h"
#include "utils.h"
#include "converting.h"
#include "label.h"


/*Gets information about the line and classify it's parts*/
void insert_command(unsigned long op_code, char *source_op, char *dest_op, multiVars *vars){
    int source, dest;
    char **first_struct_access, **second_struct_access;/*Access to a struct*/
    

    /*Default value for missing operand is zero*/
    source = 0;
    dest = 0;


    /*
    Finds the addressing type. 
    Examples-
        Label: X, STR
        Struct: S.1
        register: r1, r2
        Value: #-5, #2
    */
    if((source = is_register(source_op)) != -1){
        if((dest = is_register(dest_op)) != -1){/*Two registers*/
            create_command_line( op_code, convertDtoB(3), convertDtoB(3), vars->commands_table);
            create_registers_line(source, dest, vars->commands_table);
        }
        else if(label_exists(dest_op, vars->head_label)){/*Register and label*/
                create_command_line(op_code, convertDtoB(3), convertDtoB(1), vars->commands_table);
                create_registers_line(source, 0, vars->commands_table);
                create_unknown_line(vars->commands_table, dest_op, vars->tail_label_apear);
            }
            else if((first_struct_access = is_struct(dest_op))){/*Register and struct*/
                    create_command_line(op_code, convertDtoB(3), convertDtoB(2), vars->commands_table);
                    create_registers_line(source, 0, vars->commands_table);
                    create_unknown_line(vars->commands_table, dest_op, vars->tail_label_apear);
                    create_number_line(atoi(first_struct_access[1]), vars->commands_table);
                }
    }
        
    else if(label_exists(source_op, vars->head_label)){
        if((dest = is_register(dest_op)) != -1){/*Label and register*/
            create_command_line(op_code, convertDtoB(1), convertDtoB(3), vars->commands_table);
            create_unknown_line(vars->commands_table, dest_op, vars->tail_label_apear);
            create_registers_line(0, dest, vars->commands_table);
        }
        else if((first_struct_access = is_struct(dest_op))){/*Label and struct*/
                create_command_line(op_code, convertDtoB(1), convertDtoB(2), vars->commands_table);
                create_unknown_line(vars->commands_table, dest_op, vars->tail_label_apear);
                create_unknown_line(vars->commands_table, dest_op, vars->tail_label_apear);
                create_number_line(atoi(first_struct_access[1]), vars->commands_table);
            }
            else if(label_exists(dest_op, vars->head_label)){/*Label and label*/
                    create_command_line(op_code, convertDtoB(1), convertDtoB(1), vars->commands_table);
                    create_unknown_line(vars->commands_table, dest_op, vars->tail_label_apear);
                    create_unknown_line(vars->commands_table, dest_op, vars->tail_label_apear);
                }
    }
        
    else if(source_op[0] == '#'){
        source_op[0] = '\0'; /*Removes the charactar # */

        if((dest = is_register(dest_op)) != -1){/*Value and register*/
            create_command_line(op_code, convertDtoB(0), convertDtoB(3), vars->commands_table);
            create_number_line(atoi(source_op), vars->commands_table);
            create_registers_line(0, dest, vars->commands_table);
        }
        else if(label_exists(dest_op, vars->head_label)){/*Value and label*/
                create_command_line(op_code, convertDtoB(0), convertDtoB(1), vars->commands_table);
                create_number_line(atoi(source_op), vars->commands_table);
                create_unknown_line(vars->commands_table, dest_op, vars->tail_label_apear);
            }
            else if((first_struct_access = is_struct(dest_op))){/*Value and struct*/
                    create_command_line(op_code, convertDtoB(0), convertDtoB(2), vars->commands_table);
                    create_number_line(atoi(source_op), vars->commands_table);
                    create_unknown_line(vars->commands_table, dest_op, vars->tail_label_apear);
                    create_number_line(atoi(first_struct_access[1]), vars->commands_table);
                }
    }
        
    
    else if((first_struct_access = is_struct(source_op))){
        if((dest = is_register(dest_op)) != -1){/*Struct and register*/
            create_command_line(op_code, convertDtoB(2), convertDtoB(3), vars->commands_table);
            create_unknown_line(vars->commands_table, dest_op, vars->tail_label_apear);
            create_number_line(atoi(first_struct_access[1]), vars->commands_table);
            create_registers_line(0, dest, vars->commands_table);
        }
        else if(label_exists(dest_op, vars->head_label)){/*Struct and label*/
                create_command_line(op_code, convertDtoB(2), convertDtoB(1), vars->commands_table);
                create_unknown_line(vars->commands_table, dest_op, vars->tail_label_apear);
                create_number_line(atoi(first_struct_access[1]), vars->commands_table);
                create_unknown_line(vars->commands_table, dest_op, vars->tail_label_apear);
            }
            else if((second_struct_access = is_struct(dest_op))){/*Struct and struct*/
                    create_command_line(op_code, convertDtoB(2), convertDtoB(2), vars->commands_table);
                    create_unknown_line(vars->commands_table, dest_op, vars->tail_label_apear);
                    create_number_line(atoi(first_struct_access[1]), vars->commands_table);
                    create_unknown_line(vars->commands_table, dest_op, vars->tail_label_apear);
                    create_number_line(atoi(second_struct_access[1]), vars->commands_table);
                }
    }
}


/*Creates new machine code line (binary) in commandd_table*/
void create_command_line(unsigned long op_code, long source_op_addressing, long dest_op_addressing, 
unsigned int *commands_table){
    realloc_with_check(IC, commands_table);

    *(commands_table + IC) = ~0<<2; /*Two zeros in the right*/
    *(commands_table + IC) = *(commands_table + IC)&(dest_op_addressing<<2);
    *(commands_table + IC) = *(commands_table + IC)&(source_op_addressing<<4);
    *(commands_table + IC) = *(commands_table + IC)&(op_code<<6);
    IC++;
}

/*Creates new machine code line (binary) for registers*/
void create_registers_line(int source, int dest, unsigned int *commands_table){
    realloc_with_check(IC, commands_table);

    *(commands_table + IC) = *(commands_table + IC)&(convertDtoB(source)<<6);
    *(commands_table + IC) = *(commands_table + IC)&(convertDtoB(dest)<<2);
    IC++;
}


/*
Gets numeric value
And puts it as binary in new line
*/
void create_number_line(int number, unsigned int *commands_table){
    realloc_with_check(IC, commands_table);
    *(commands_table + IC) = convertDtoB(number);
    IC++;
}


/*At this point, the address of the label (data type) is unknown*/
void create_unknown_line(unsigned int *commands_table, char *label, ptr_label_apearence tail_label_apear){
    ptr_label_apearence temp_node;
    
    temp_node = NULL;
    realloc_with_check(IC, commands_table);

    /*Saves the location of the label/struct apearence*/
    strcpy(temp_node->name, label);
    temp_node-> index_in_commands_table = IC; 
    temp_node->next = NULL;
    tail_label_apear->next = temp_node;
    tail_label_apear = temp_node;

    /*Fills the unknown line with the char '?' for now*/
    *(commands_table + IC) = '?'; 
    IC++;
}

/*Creates new machine (binary) code line in data_table*/
response_type create_data_line(char *row_content, unsigned int *data_table, char *type){
    char *token;
    int number;

    if(!realloc_with_check(DC, data_table))
        return SYSTEM_ERROR;

    token = calloc_with_check(MAX_LINE_LENGTH, sizeof(char));
    strcpy(token, strtok(row_content, " ,\t\r"));

    if(!strcmp(type, ".data")){
        while (token){
            number = atoi(token);
            *(data_table + DC) = convertDtoB(number);
            DC++;

            reset_array(token);
            strcpy(token, strtok(row_content, " ,\t\r"));
        }
    }

    if(!strcmp(type, ".string")){
        int i;
        
        for(i = 1; i < strlen(token)-1; i++){/*Reads between the ""*/
            *(data_table + DC) = convertDtoB(token[i]);/*Converts the ASCII code of the letter to binary*/
            DC++;
        }

        create_zero_line(data_table);
        DC++;
    }

    if(!strcmp(type, ".struct")){
        int i;

        number = atoi(token);
        reset_array(token);
        strcpy(token, strtok(NULL, " ,\t\r"));

        *(data_table + DC) = convertDtoB(number);
        DC++;

        for(i = 1; i < sizeof(token)-1; i++){/*Reads between the ""*/
            *(data_table + DC) = convertDtoB(token[i]);/*Converts the ASCII code of the letter to binary*/
            DC++;
        }

        create_zero_line(data_table);
        DC++;
    }
    return SUCCESS;
}


/*Create zero line for '\0' at the end of string*/
void create_zero_line(unsigned int *data_table){
    realloc_with_check(DC, data_table);
    *(data_table + DC) = convertDtoB(0);
    DC++;
}




