#include "assembler.h"
#include "label.c"


ptr_bin *binar_lines;
char **label_apearances;


void insert_new_order(char * label, int line, unsigned long op_code, char *source_op, char *dest_op){
    int source, dest;
    source = 0;
    dest = 0;
    char **struct_access1, **struct_access2;


    /*find the addressing type - שיטות מיעון*/
    if(source = is_register(source_op) != -1){
        if(dest = is_register(dest_op) != -1){/*Two registers*/
            create_new_line(label, line, op_code, convertDtoB(3), convertDtoB(3));
            create_line_for_registers(source, dest, line++);
        }
        else if(label_exists(dest_op)){/*Register and label*/
                create_new_line(label, line, op_code, convertDtoB(3), convertDtoB(1));
                create_line_for_registers(source, 0, line++);
                create_unknown_line(line++);
            }
            else if(struct_access1 = is_struct(dest_op)){/*Register and struct*/
                    create_new_line(label, line, op_code, convertDtoB(3), convertDtoB(2));
                    create_line_for_registers(source, 0, line++);
                    create_unknown_line(line++);
                    create_line_for_value(struct_access1[1], line++);
                }
    }
        
    else if(label_exists(source_op)){
        if(dest = is_register(dest_op) != -1){/*Label and register*/
            create_new_line(label, line, op_code, convertDtoB(1), convertDtoB(3));
            create_unknown_line(line++);
            create_line_for_registers(0, dest, line++);
        }
        else if(struct_access1 = is_struct(dest_op)){/*Label and struct*/
                create_new_line(label, line, op_code, convertDtoB(1), convertDtoB(2));
                create_unknown_line(line++);
                create_unknown_line(line++);
                create_line_for_value(struct_access1[1], line++);
            }
            else if(label_exists(dest_op)){/*Label and label*/
                    create_new_line(label, line, op_code, convertDtoB(1), convertDtoB(1));
                    create_unknown_line(line++);
                    create_unknown_line(line++);
                }
    }
        
    else if(source_op[0] == '#'){
        if(dest = is_register(dest_op) != -1){/*Value and register*/
            create_new_line(label, line, op_code, convertDtoB(0), convertDtoB(3));
            create_line_for_value(source_op, line++);
            create_line_for_registers(0, dest, line++);
        }
        else if(label_exists(dest_op)){/*Value and label*/
                create_new_line(label, line, op_code, convertDtoB(0), convertDtoB(1));
                create_line_for_value(source_op, line++);
                create_unknown_line(line++);
            }
            else if(struct_access1 = is_struct(dest_op)){/*Value and struct*/
                    create_new_line(label, line, op_code, convertDtoB(0), convertDtoB(2));
                    create_line_for_value(source_op, line++);
                    create_unknown_line(line++);
                    create_line_for_value(struct_access1[1], line++);
                }
    }
        
    
    else if(struct_access1 = is_struct(source_op)){
        if(dest = is_register(dest_op) != -1){/*Struct and register*/
            create_new_line(label, line, op_code, convertDtoB(2), convertDtoB(3));
            create_unknown_line(line++);
            create_line_for_value(struct_access1[1], line++);
            create_line_for_registers(0, dest, line++);
        }
        else if(label_exists(dest_op)){/*Struct and label*/
                create_new_line(label, line, op_code, convertDtoB(2), convertDtoB(1));
                create_unknown_line(line++);
                create_line_for_value(struct_access1[1], line++);
                create_unknown_line(line++);
            }
            else if(struct_access2 = is_struct(dest_op)){/*Struct and struct*/
                    create_new_line(label, line, op_code, convertDtoB(2), convertDtoB(2));
                    create_unknown_line(line++);
                    create_line_for_value(struct_access1[1], line++);
                    create_unknown_line(line++);
                    create_line_for_value(struct_access2[1], line++);
                }
    }

}


/*Creates new machine code line (binary)*/
void create_new_line(char *label_name, int line, unsigned long op_code, long source_op_addressing, long dest_op_addressing){
    
    ptr_bin bin;

    bin = (ptr_bin) malloc(sizeof(binaryMachineCode));
    if(!bin){
        printf("Memory allocation failed\n");
        exit(0);
    }
    
    bin->ARE = 0;
    bin->destination = dest_op_addressing;
    bin->source = source_op_addressing;
    bin->opcode = op_code;

    binar_lines[line] = &bin;

    strcpy(label_apearances[line], label_name);

    /*
    binar_lines[line] = ~0<<2; 
    binar_lines[line] = binar_lines[line]&(dest_op_addressing<<2);
    binar_lines[line] = binar_lines[line]&(source_op_addressing<<4);
    binar_lines[line] = binar_lines[line]&(op_code<<6);
    */
}


/*Creates new machine code line (binary) for registers*/
void create_line_for_registers(int source, int dest, int line){
    
    binar_lines[line] = convertDtoB(source);//לבדוק שיש 4 ביטים
    binar_lines[line] = convertDtoB(dest);//לבדוק שיש 4 ביטים
}


/*Gets numeric value as string*/
void create_line_for_value(char *val, int line){
    
    binar_lines[line] = convertDtoB(atoi(val));//לבדוק שיש 10 ביטים
}


/*At this point, the address is unknown*/
void create_unknown_line(int line){
    
    binar_lines[line] = '?';
}


create_zero_line(int line){
    ptr_bin bin;

    bin = (ptr_bin) malloc(sizeof(binaryMachineCode));
    if(!bin){
        printf("Memory allocation failed\n");
        exit(0);
    }
    
    bin->ARE = 0;
    bin->destination = 0;
    bin->source = 0;
    bin->opcode = 0;

    binar_lines[line] = &bin; 
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