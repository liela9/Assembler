#include "assembler.h"
#include "label.c"



int insert_order(char *label, int IC, unsigned long op_code, char *source_op, char *dest_op){
    int source, dest;
    char **struct_access1, **struct_access2;
    unsigned int *orders_table;
    
    orders_table = (unsigned int*)malloc(sizeof(unsigned int));

    source = 0;
    dest = 0;


    /*find the addressing type - שיטות מיעון*/
    /*
        Examples:

        Label: X, STR
        Struct: S.1
        register: r1, r2
        Value: #-5, #2
    */
    if(source = is_register(source_op) != -1){
        if(dest = is_register(dest_op) != -1){/*Two registers*/
            IC = create_order_line(label, IC, op_code, convertDtoB(3), convertDtoB(3), &orders_table);
            IC = create_registers_line(source, dest, IC, &orders_table);
        }
        else if(label_exists(dest_op)){/*Register and label*/
                IC = create_order_line(label, IC, op_code, convertDtoB(3), convertDtoB(1), &orders_table);
                IC = create_registers_line(source, 0, IC, &orders_table);
                IC = create_unknown_line(IC, &orders_table);
            }
            else if(struct_access1 = is_struct(dest_op)){/*Register and struct*/
                    IC = create_order_line(label, IC, op_code, convertDtoB(3), convertDtoB(2), &orders_table);
                    IC = create_registers_line(source, 0, IC, &orders_table);
                    IC = create_unknown_line(IC, &orders_table);
                    IC = create_index_line(struct_access1[1], IC, &orders_table);
                }
    }
        
    else if(label_exists(source_op)){
        if(dest = is_register(dest_op) != -1){/*Label and register*/
            IC = create_order_line(label, IC, op_code, convertDtoB(1), convertDtoB(3), &orders_table);
            IC = create_unknown_line(IC, &orders_table);
            IC = create_registers_line(0, dest, IC, &orders_table);
        }
        else if(struct_access1 = is_struct(dest_op)){/*Label and struct*/
                IC = create_order_line(label, IC, op_code, convertDtoB(1), convertDtoB(2), &orders_table);
                IC = create_unknown_line(IC, &orders_table);
                IC = create_unknown_line(IC, &orders_table);
                IC = create_index_line(struct_access1[1], IC, &orders_table);
            }
            else if(label_exists(dest_op)){/*Label and label*/
                    IC = create_order_line(label, IC, op_code, convertDtoB(1), convertDtoB(1), &orders_table);
                    IC = create_unknown_line(IC, &orders_table);
                    IC = create_unknown_line(IC, &orders_table);
                }
    }
        
    else if(source_op[0] == '#'){
        if(dest = is_register(dest_op) != -1){/*Value and register*/
            IC = create_order_line(label, IC, op_code, convertDtoB(0), convertDtoB(3), &orders_table);
            IC = create_value_line(source_op, IC, &orders_table);
            IC = create_registers_line(0, dest, IC, &orders_table);
        }
        else if(label_exists(dest_op)){/*Value and label*/
                IC = create_order_line(label, IC, op_code, convertDtoB(0), convertDtoB(1), &orders_table);
                IC = create_value_line(source_op, IC, &orders_table);
                IC = create_unknown_line(IC, &orders_table);
            }
            else if(struct_access1 = is_struct(dest_op)){/*Value and struct*/
                    IC = create_order_line(label, IC, op_code, convertDtoB(0), convertDtoB(2), &orders_table);
                    IC = create_value_line(source_op, IC, &orders_table);
                    IC = create_unknown_line(IC, &orders_table);
                    IC = create_index_line(struct_access1[1], IC, &orders_table);
                }
    }
        
    
    else if(struct_access1 = is_struct(source_op)){
        if(dest = is_register(dest_op) != -1){/*Struct and register*/
            IC = create_order_line(label, IC, op_code, convertDtoB(2), convertDtoB(3), &orders_table);
            IC = create_unknown_line(IC, &orders_table);
            IC = create_index_line(struct_access1[1], IC, &orders_table);
            IC = create_registers_line(0, dest, IC, &orders_table);
        }
        else if(label_exists(dest_op)){/*Struct and label*/
                IC = create_order_line(label, IC, op_code, convertDtoB(2), convertDtoB(1), &orders_table);
                IC = create_unknown_line(IC, &orders_table);
                IC = create_index_line(struct_access1[1], IC, &orders_table);
                IC = create_unknown_line(IC, &orders_table);
            }
            else if(struct_access2 = is_struct(dest_op)){/*Struct and struct*/
                    IC = create_order_line(label, IC, op_code, convertDtoB(2), convertDtoB(2), &orders_table);
                    IC = create_unknown_line(IC, &orders_table);
                    IC = create_index_line(struct_access1[1], IC, &orders_table);
                    IC = create_unknown_line(IC, &orders_table);
                    IC = create_value_line(struct_access2[1], IC, &orders_table);
                }
    }
    return IC;
}


/*Creates new machine code line in orderd_table*/
int create_order_line(char *label_name, int IC, unsigned long op_code, long source_op_addressing, long dest_op_addressing, unsigned int *orders_table){
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


/*Gets numeric value as string*/
int create_value_line(char *value, int IC, unsigned int *orders_table){
    value[0] = '\0'; /*Removes the charactar # */
    
    realloc_check(IC++, orders_table);

    *(orders_table + IC) = convertDtoB(atoi(value));
    return IC++;
}


int create_index_line(int number, int IC, unsigned int *orders_table){
    realloc_check(IC++, orders_table);

    *(orders_table + IC) = convertDtoB(number);
    return IC++;
}


/*At this point, the address of the label(data) is unknown*/
int create_unknown_line(int IC, unsigned int *orders_table){
    realloc_check(IC++, orders_table);

    *(orders_table + IC) = '?';
    
    return IC++;
}

/*Creates new machine code line in data_table*/
int create_data_line(int DC, char *row_content, unsigned int *data_table, char *type){
    char *token, *string_part;
    int number;

    realloc_check(DC++, data_table);

    token = strtok(row_content, ' ,\t\r');

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
        token = strtok(NULL, ' ,\t\r');

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


/*Checks if the operand is register*/
int is_register(char *op){
    
    int i;
    for(i = 0; i < NUM_OF_REGISTERS; i++){
        if(strcmp(op, *registers[i]))
            return i;
    }
    return -1;
}


/*Splits the name of struct and the index after the point*/
char** is_struct(char *op){
    
    char *struct_val[2];
    struct_val[0] = NULL;
    struct_val[1] = NULL;

    while (op)
    {
        if(*op == '.'){
            struct_val[0] = strtok(op, ".");
            struct_val[1] = strtok(NULL, ".");
        }
    }
    return struct_val;
}

void realloc_check(int index, unsigned int *table){
    unsigned int *ptr;
    
    ptr = (unsigned int*)realloc(table, index + sizeof(unsigned int));
    if(!ptr){
        printf("Memory allocation faild!");
        exit(0);
    }
    table = ptr;
}
    