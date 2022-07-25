#include <stdio.h>
#include <string.h>
#include <stdlib.h>
 
#define MACRO_MAX_LINE_NUMBER 10
#define BASE_LENGTH 32
#define OPCODE_LENGTH 16
#define MAX_LINE_LENGTH 81
#define NUM_OF_REGISTERS 8
#define NUM_OF_GUIDANCE_NAME 5
#define MAX_LABEL_LENGTH 30
#define BIN_MACHINE_CODE_LENGTH 10
#define AM_FILE ".am"
#define ENT_FILE ".ent"
#define EXT_FILE ".ext"
#define OB_FILE ".ob"


enum {ENTRY, EXTERNAL, CODE, DATA};
typedef enum {false, true} bool;


typedef struct macro *ptr_macro;
typedef struct macro {
    char *macro_id; 
    char *macro_content; 

    ptr_macro next;
} macro;


typedef struct label *ptr_label;
typedef struct label{
    
    char name[MAX_LABEL_LENGTH];
    int type; /*Options: 0 == ENTRY, 1 == EXTERNAL, 2 == CODE, 3 == DATA*/
    int dec_address; /*Decimal address*/

    ptr_label next;

}label;


typedef struct labelApearance *ptr_label_apearence;
typedef struct labelApearance{
    
    char name[MAX_LABEL_LENGTH];
    int index_in_orders_table;

    ptr_label_apearence next;

}labelApearance;


/*Functions of file 'preAssembler'*/
void pre_assembler(FILE *, char *);
long int find_word(char *word, FILE *);


/*Functions of file 'macro'*/
ptr_macro add_macro(char *);
ptr_macro get_macro_by_id(char *);
void print_macro_list();
void free_macro_list();


/*Functions of file 'firsStep'*/
bool first_translation();
int find_opcode(char *);
int find_group(int IC, int , ptr_label);
void free_label_list();
void free_data_table();


/*Functions of file 'lines'*/
int insert_order(int , unsigned long , char *, char *, ptr_label);
int create_order_line(int , unsigned long , long , long , unsigned int *);
int create_registers_line(int , int , int , unsigned int *);
int create_value_line(char *, int , unsigned int *);
int create_index_line(int , int , unsigned int *);
int create_unknown_line(int , unsigned int *, char *, ptr_label_apearence );
int create_data_line(int , char *, unsigned int *, char *);
void create_zero_line(unsigned int *, int DC);
void free_orders_table();


/*Functions of file 'utils'*/
int is_register(char *);
char** is_struct(char *);
void realloc_check(int , unsigned int *);
bool saved_words(char *);
bool alphanumeric_str(char *);


/*Functions of file 'label'*/
int insert_new_label(char *, int , int , ptr_label , ptr_label );
bool label_exists(char *, ptr_label );
bool valid_label_name(char *);


/*Functions of file 'writeFiles'*/
void write_files(char *, ptr_label );
void write_ob_file(char *);
void write_ext_ent_files(char *, ptr_label );






