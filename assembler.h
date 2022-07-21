#include <stdio.h>
#include <string.h>
#include <stdlib.h>
 
#define BASE_LENGTH 32
#define OPCODE_LENGTH 16
#define ROW_LENGTH 81
#define NUM_OF_REGISTERS 8
#define NUM_OF_GUIDANCE_NAME 5
#define MAX_LABEL_LENGTH 30
#define BIN_MACHINE_CODE_LENGTH 10

  


const char* registers[NUM_OF_REGISTERS] = {"r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7"};
const char* opcode[OPCODE_LENGTH] = {"mov", "cmp", "add", "sub", "not", "clr", "lea", "inc", "dec", "jmp", "bne", "get", "prn", "jsr", "rts", "hlt"}; 
const char base32[BASE_LENGTH] = {'!', '@', '#', '$', '%', '^', '&', '*', '<', '>', 'a', 'b', 'c', 'd', 'e', 'f', 'g',' h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v'};
const char* guidance[NUM_OF_GUIDANCE_NAME] = {"data", "string", "struct", "entry", "extern"};

enum {ENTRY, EXTERNAL, CODE, DATA};


typedef struct label *ptr_label;
typedef struct label{
    
    char name[MAX_LABEL_LENGTH];
    int type; /*Options: 0 == ENTRY, 1 == EXTERNAL, 2 == CODE, 3 == DATA*/
    int dec_address;

    ptr_label next;

}label;


typedef struct labelApearance *ptr_label_apearence;
typedef struct labelApearance{
    
    char name[MAX_LABEL_LENGTH];
    int index_in_order_table;

    ptr_label_apearence next;

}labelApearance;

/*
typedef struct OrdersBinaryCode *ptr_order_bin;
typedef struct OrdersBinaryCode
{
    unsigned int ARE : 2;
    unsigned int destination : 2;
    unsigned int source : 2;
    unsigned int opcode : 4;

    ptr_order_bin next;

}OrdersBinaryCode;
*/

typedef struct BinaryCode *ptr_bin;
typedef struct BinaryCode{
    unsigned int code : 10;
    ptr_bin next;
    
}BinaryCode;





FILE * first_copy_file(FILE *);
long int find_word(char *, FILE *);

int find_opcode(char *);
void find_group(int , char *, int );
int first_translation(FILE *);

int second_translation(FILE *);

int insert_new_label(char *, int, int );
int label_exists(char *);
int saved_words(char *);
void fill_values(FILE *, long int , int *);

void insert_new_order(char * ,int , unsigned long , char *, char *);
void create_new_line(char *, int , unsigned long , long , long );
void create_line_for_registers(int , int, int);
void create_line_for_value(char *, int);
void create_unknown_line(int);
int is_register(char *);
char** is_struct(char *);

void write_files(char *, ptr_label);
void write_ob_file(char *);
void write_ext_ent_file(char *, ptr_label);

unsigned long convertDtoB(int);
int convertBtoD(unsigned long);
char* reverstr(char *, int);
char* convertDtoB32(int);


