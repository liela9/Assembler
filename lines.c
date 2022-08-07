#include "constants.h"
#include "lines.h"
#include "utils.h"
#include "converting.h"
#include "label.h"
#include "dataList.h"
#include "commandsList.h"


/*Gets information about the line and classify it's parts*/
void insert_command(unsigned long op_code, char *source_op, char *dest_op, multiVars *vars){
    char **first_struct_access, **second_struct_access;/*Access to a struct*/
    int source = 0, dest = 0;/*Default value for missing operand is zero*/
    
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
            create_command_line(op_code, convertDtoB(3), convertDtoB(3) );
            create_registers_line(source, dest );
        }
        else if(label_exists(dest_op, vars->head_label)){/*Register and label*/
                create_command_line(op_code, convertDtoB(3), convertDtoB(1) );
                create_registers_line(source, 0 );
                create_unknown_line( dest_op, vars->tail_label_apear);
            }
            else if((first_struct_access = is_struct(dest_op))){/*Register and struct*/
                    create_command_line(op_code, convertDtoB(3), convertDtoB(2) );
                    create_registers_line(source, 0 );
                    create_unknown_line(dest_op, vars->tail_label_apear);
                    create_number_line(atoi(first_struct_access[1]) );
                }
    }
        
    else if(label_exists(source_op, vars->head_label)){
        if((dest = is_register(dest_op)) != -1){/*Label and register*/
            create_command_line(op_code, convertDtoB(1), convertDtoB(3) );
            create_unknown_line(dest_op, vars->tail_label_apear);
            create_registers_line(0, dest );
        }
        else if((first_struct_access = is_struct(dest_op))){/*Label and struct*/
                create_command_line(op_code, convertDtoB(1), convertDtoB(2) );
                create_unknown_line(dest_op, vars->tail_label_apear);
                create_unknown_line(dest_op, vars->tail_label_apear);
                create_number_line(atoi(first_struct_access[1]) );
            }
            else if(label_exists(dest_op, vars->head_label)){/*Label and label*/
                    create_command_line(op_code, convertDtoB(1), convertDtoB(1) );
                    create_unknown_line(dest_op, vars->tail_label_apear);
                    create_unknown_line(dest_op, vars->tail_label_apear);
                }
    }
        
    else if(source_op[0] == '#'){
        source_op[0] = '\0'; /*Removes the charactar # */

        if((dest = is_register(dest_op)) != -1){/*Value and register*/
            create_command_line(op_code, convertDtoB(0), convertDtoB(3) );
            create_number_line(atoi(source_op) );
            create_registers_line(0, dest );
        }
        else if(label_exists(dest_op, vars->head_label)){/*Value and label*/
                create_command_line(op_code, convertDtoB(0), convertDtoB(1) );
                create_number_line(atoi(source_op) );
                create_unknown_line(dest_op, vars->tail_label_apear);
            }
            else if((first_struct_access = is_struct(dest_op))){/*Value and struct*/
                    create_command_line(op_code, convertDtoB(0), convertDtoB(2) );
                    create_number_line(atoi(source_op) );
                    create_unknown_line(dest_op, vars->tail_label_apear);
                    create_number_line(atoi(first_struct_access[1]) );
                }
    }
        
    
    else if((first_struct_access = is_struct(source_op))){
        if((dest = is_register(dest_op)) != -1){/*Struct and register*/
            create_command_line(op_code, convertDtoB(2), convertDtoB(3) );
            create_unknown_line(dest_op, vars->tail_label_apear);
            create_number_line(atoi(first_struct_access[1]) );
            create_registers_line(0, dest );
        }
        else if(label_exists(dest_op, vars->head_label)){/*Struct and label*/
                create_command_line(op_code, convertDtoB(2), convertDtoB(1) );
                create_unknown_line(dest_op, vars->tail_label_apear);
                create_number_line(atoi(first_struct_access[1]) );
                create_unknown_line(dest_op, vars->tail_label_apear);
            }
            else if((second_struct_access = is_struct(dest_op))){/*Struct and struct*/
                    create_command_line(op_code, convertDtoB(2), convertDtoB(2) );
                    create_unknown_line(dest_op, vars->tail_label_apear);
                    create_number_line(atoi(first_struct_access[1]) );
                    create_unknown_line(dest_op, vars->tail_label_apear);
                    create_number_line(atoi(second_struct_access[1]) );
                }
    }
}


/*Creates new machine code line (binary) in commandd_table*/
void create_command_line(unsigned long op_code, long source_op_addressing, long dest_op_addressing){

    create_commands_node((~0<<2) & (dest_op_addressing<<2) & (source_op_addressing<<4) & (op_code<<6));
    IC++;
}

/*Creates new machine code line (binary) for registers*/
void create_registers_line(int source, int dest){

    create_commands_node(~0 & (convertDtoB(source)<<6) & (convertDtoB(dest)<<2));
    IC++;
}


/*
Gets numeric value
And puts it as binary in new line
*/
void create_number_line(int number){
    create_commands_node(convertDtoB(number));
    IC++;
}


/*At this point, the address of the label (data type) is unknown*/
void create_unknown_line(char *label, ptr_label_apearence tail_label_apear){
    ptr_label_apearence temp_node = NULL;

    /*Saves the location of the label/struct apearence*/
    strcpy(temp_node->name, label);
    temp_node-> index_in_commands_list = IC; 
    temp_node->next = NULL;
    tail_label_apear->next = temp_node;
    tail_label_apear = temp_node;

    /*Fills the unknown line with the char '?' for now*/
    create_commands_node('?'); 
    IC++;
}


/*Creates new machine (binary) code line in data_table*/
response_type create_data_line(char *row_content, char *type){
    char *token;
    int number;

    token = calloc_with_check(MAX_LINE_LENGTH, sizeof(char));
    if(!token)
        return SYSTEM_ERROR;

    strcpy(token, strtok(row_content, " ,\t\r"));

    if(!strcmp(type, DATA_WORD)){
        while (token){
            number = atoi(token);
            create_data_node(convertDtoB(number));
            DC++;

            reset_array(token);
            strcpy(token, strtok(row_content, " ,\t\r"));
        }
    }

    if(!strcmp(type, STRING_WORD)){
        int i;
        
        for(i = 1; i < strlen(token)-1; ++i){/*Reads between the ""*/
            create_data_node(convertDtoB(token[i])) ;/*Converts the ASCII code of the letter to binary*/
            DC++;
        }

        create_zero_line();
        DC++;
    }

    if(!strcmp(type, STRUCT_WORD)){
        int i;

        number = atoi(token);
        reset_array(token);
        strcpy(token, strtok(NULL, " ,\t\r"));
        create_data_node(convertDtoB(number));
        DC++;

        for(i = 1; i < strlen(token)-1; ++i){/*Reads between the ""*/
            create_data_node(convertDtoB(token[i]));/*Converts the ASCII code of the letter to binary*/
            DC++;
        }

        create_zero_line();
        DC++;
    }
    return SUCCESS;
}


/*Creates zero line for '\0' at the end of a string*/
void create_zero_line(){
    create_data_node(convertDtoB(0));
    DC++;
}




