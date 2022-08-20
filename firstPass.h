#ifndef FIRST_PASS_H
#define FIRST_PASS_H

#include "constants.h"
#include "conversionUtils.h"
#include "lines.h"
#include "lists.h"
#include "utils.h"

#define CHECK_DATA_ARGUMENT                               \
    if (!rest_line) {                                     \
        print_user_error(vars, "missing data arguments"); \
        return USER_ERROR;                                \
    }

#define CHECK_OPERAND_ARGUMENT(operand)                             \
    if (operand) {                                                  \
        operand = strtok(operand, " \t\r\n");                       \
        if (strtok(NULL, " \t\r\n")) {                              \
            print_user_error(vars, "extra character near operand"); \
            return USER_ERROR;                                      \
        }                                                           \
    }

responseType first_pass(multiVars *);
responseType handle_line(char *, char *, multiVars *);
responseType extern_entry_validate(labelType, multiVars *, char *);
responseType insert_data_label(char *, int, labelType, multiVars *);
responseType check_and_insert_data_item(char *, multiVars *);
responseType insert_string_line(char *, char *, multiVars *);
responseType insert_struct_line(char *, char *, multiVars *);
responseType insert_opcode_line(char *, char *, multiVars *);
responseType insert_data_line(char *, char *, multiVars *);

#endif /* FIRST_PASS_H */
