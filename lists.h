#ifndef LISTS_H
#define LISTS_H

#include <ctype.h>

#include "constants.h"
#include "conversionUtils.h"
#include "utils.h"

/*Functions of file 'label.c'*/
responseType create_label_node(char *, labelType, multiVars *);
responseType create_extern_label_node(char *, multiVars *);
responseType create_commands_node(int, multiVars *);
responseType create_data_node(int, multiVars *);
ptrlabel get_label_by_name(char *, ptrlabel);

#endif
