#include "constants.h"
#include "lines.h"
#include "utils.h"
#include "converting.h"


/*Gets information about the line and classify it's parts*/
int insert_order(int IC, unsigned long op_code, char *source_op, char *dest_op, 
ptr_label head_label, ptr_label_apearence label_apear_head){
    int source, dest;
    char **first_struct_access, **second_struct_access;/*Access to a struct*/
    ptr_label_apearence label_apear_tail;/*Tail node of the list "label_apearence"*/
    /*A table of binary machine code for orders*/
    static unsigned int *orders_table;

    orders_table = (unsigned int*)malloc(sizeof(unsigned int));
    label_apear_head = (ptr_label_apearence)malloc(sizeof(labelApearance));

    label_apear_tail = label_apear_head;

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
    if(source = is_register(source_op) != -1){
        if(dest = is_register(dest_op) != -1){/*Two registers*/
            IC = create_order_line( IC, op_code, convertDtoB(3), convertDtoB(3), &orders_table);
            IC = create_registers_line(source, dest, IC, &orders_table);
        }
        else if(label_exists(dest_op, &head_label)){/*Register and label*/
                IC = create_order_line( IC, op_code, convertDtoB(3), convertDtoB(1), &orders_table);
                IC = create_registers_line(source, 0, IC, &orders_table);
                IC = create_unknown_line(IC, &orders_table, dest_op, &label_apear_tail);
            }
            else if(first_struct_access = is_struct(dest_op)){/*Register and struct*/
                    IC = create_order_line( IC, op_code, convertDtoB(3), convertDtoB(2), &orders_table);
                    IC = create_registers_line(source, 0, IC, &orders_table);
                    IC = create_unknown_line(IC, &orders_table, dest_op, &label_apear_tail);
                    IC = create_index_line(first_struct_access[1], IC, &orders_table);
                }
    }
        
    else if(label_exists(source_op, &head_label), &head_label){
        if(dest = is_register(dest_op) != -1){/*Label and register*/
            IC = create_order_line( IC, op_code, convertDtoB(1), convertDtoB(3), &orders_table);
            IC = create_unknown_line(IC, &orders_table, dest_op, &label_apear_tail);
            IC = create_registers_line(0, dest, IC, &orders_table);
        }
        else if(first_struct_access = is_struct(dest_op)){/*Label and struct*/
                IC = create_order_line( IC, op_code, convertDtoB(1), convertDtoB(2), &orders_table);
                IC = create_unknown_line(IC, &orders_table, dest_op, &label_apear_tail);
                IC = create_unknown_line(IC, &orders_table, dest_op, &label_apear_tail);
                IC = create_index_line(first_struct_access[1], IC, &orders_table);
            }
            else if(label_exists(dest_op, &head_label)){/*Label and label*/
                    IC = create_order_line( IC, op_code, convertDtoB(1), convertDtoB(1), &orders_table);
                    IC = create_unknown_line(IC, &orders_table, dest_op, &label_apear_tail);
                    IC = create_unknown_line(IC, &orders_table, dest_op, &label_apear_tail);
                }
    }
        
    else if(source_op[0] == '#'){
        if(dest = is_register(dest_op) != -1){/*Value and register*/
            IC = create_order_line( IC, op_code, convertDtoB(0), convertDtoB(3), &orders_table);
            IC = create_value_line(source_op, IC, &orders_table);
            IC = create_registers_line(0, dest, IC, &orders_table);
        }
        else if(label_exists(dest_op, &head_label)){/*Value and label*/
                IC = create_order_line( IC, op_code, convertDtoB(0), convertDtoB(1), &orders_table);
                IC = create_value_line(source_op, IC, &orders_table);
                IC = create_unknown_line(IC, &orders_table, dest_op, &label_apear_tail);
            }
            else if(first_struct_access = is_struct(dest_op)){/*Value and struct*/
                    IC = create_order_line( IC, op_code, convertDtoB(0), convertDtoB(2), &orders_table);
                    IC = create_value_line(source_op, IC, &orders_table);
                    IC = create_unknown_line(IC, &orders_table, dest_op, &label_apear_tail);
                    IC = create_index_line(first_struct_access[1], IC, &orders_table);
                }
    }
        
    
    else if(first_struct_access = is_struct(source_op)){
        if(dest = is_register(dest_op) != -1){/*Struct and register*/
            IC = create_order_line( IC, op_code, convertDtoB(2), convertDtoB(3), &orders_table);
            IC = create_unknown_line(IC, &orders_table, dest_op, &label_apear_tail);
            IC = create_index_line(first_struct_access[1], IC, &orders_table);
            IC = create_registers_line(0, dest, IC, &orders_table);
        }
        else if(label_exists(dest_op, &head_label)){/*Struct and label*/
                IC = create_order_line( IC, op_code, convertDtoB(2), convertDtoB(1), &orders_table);
                IC = create_unknown_line(IC, &orders_table, dest_op, &label_apear_tail);
                IC = create_index_line(first_struct_access[1], IC, &orders_table);
                IC = create_unknown_line(IC, &orders_table, dest_op, &label_apear_tail);
            }
            else if(second_struct_access = is_struct(dest_op)){/*Struct and struct*/
                    IC = create_order_line( IC, op_code, convertDtoB(2), convertDtoB(2), &orders_table);
                    IC = create_unknown_line(IC, &orders_table, dest_op, &label_apear_tail);
                    IC = create_index_line(first_struct_access[1], IC, &orders_table);
                    IC = create_unknown_line(IC, &orders_table, dest_op, &label_apear_tail);
                    IC = create_value_line(second_struct_access[1], IC, &orders_table);
                }
    }
    return IC;
}


/*Creates new machine code line (binary) in orderd_table*/
int create_order_line(int IC, unsigned long op_code, long source_op_addressing, long dest_op_addressing, 
unsigned int *orders_table){
    realloc_check(IC++, orders_table);

    *(orders_table + IC) = ~0<<2; /*Two zeros in the right*/
    *(orders_table + IC) = *(orders_table + IC)&(dest_op_addressing<<2);
    *(orders_table + IC) = *(orders_table + IC)&(source_op_addressing<<4);
    *(orders_table + IC) = *(orders_table + IC)&(op_code<<6);
    
    return IC++;
}


/*Creates new machine code line (binary) for registers*/
int create_registers_line(int source, int dest, int IC, unsigned int *orders_table){
    realloc_check(IC++, orders_table);

    *(orders_table + IC) = *(orders_table + IC)&(convertDtoB(source)<<6);
    *(orders_table + IC) = *(orders_table + IC)&(convertDtoB(dest)<<2);
    
    return IC++;
}


/*
Gets numeric value as string
And puts it's value as binary in new line
*/
int create_value_line(char *value, int IC, unsigned int *orders_table){
    value[0] = '\0'; /*Removes the charactar # */
    
    realloc_check(IC++, orders_table);

    *(orders_table + IC) = convertDtoB(atoi(value));
    return IC++;
}

/*Puts the wanted index of struct in new line (as binary) in case of access to struct*/
int create_index_line(int number, int IC, unsigned int *orders_table){
    realloc_check(IC++, orders_table);

    *(orders_table + IC) = convertDtoB(number);
    return IC++;
}


/*At this point, the address of the label (data type) is unknown*/
int create_unknown_line(int IC, unsigned int *orders_table, char *label, 
ptr_label_apearence label_apear_tail){
    ptr_label_apearence temp_node;

    realloc_check(IC++, orders_table);

    /*Saves the location of the label/struct apearence*/
    strcpy(temp_node->name, label);
    temp_node-> index_in_orders_table = IC; 
    temp_node->next = NULL;
    label_apear_tail->next = temp_node;
    label_apear_tail = temp_node;

    *(orders_table + IC) = '?'; /*Fills the unknown line with the char '?' for now*/
    
    return IC++;
}

/*Creates new machine (binary) code line in data_table*/
int create_data_line(int DC, char *row_content, unsigned int *data_table, char *type){
    char *token, *string_part;
    int number;

    realloc_check(DC++, data_table);
    token = strtok(row_content, " ,\t\r");

    if(!strcmp(type, ".data")){
        while (token){
            number = atoi(token);
            *(data_table + DC) = convertDtoB(number);
            DC++;
        }
    }

    if(!strcmp(type, ".string")){
        int i;

        for(i = 1; i < sizeof(token)-1; i++){/*Reads between the ""*/
            *(data_table + DC) = convertDtoB(token[i]);/*Converts the ASCII code of the letter to binary*/
            DC++;
        }

        create_zero_line(&data_table, DC);
        DC++;
    }

    if(!strcmp(type, ".struct")){
        int i;

        number = atoi(token);
        token = strtok(NULL, " ,\t\r");

        *(data_table + DC) = convertDtoB(number);
        DC++;

        for(i = 1; i < sizeof(token)-1; i++){/*Reads between the ""*/
            *(data_table + DC) = convertDtoB(token[i]);/*Converts the ASCII code of the letter to binary*/
            DC++;
        }

        create_zero_line(&data_table, DC);
        DC++;
    }

    return DC;
}


/*Create zero line for '\0' at the end of string*/
void create_zero_line(unsigned int *data_table, int DC){
    realloc_check(DC++, data_table);

    *(data_table + DC) = convertDtoB(0);
}


