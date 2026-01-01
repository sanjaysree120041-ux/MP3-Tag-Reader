#ifndef VIEW_H
#define VIEW_H

#define RESET   "\033[0m"
#define RED     "\033[0;31m"
#define GREEN   "\033[0;32m"
#define BLUE    "\033[0;34m"
#define MAGENTA "\033[0;35m"
#define CYAN    "\033[0;36m"


#include "type.h"

OperationType check_operation_type(char *argv[]);

Status read_and_validate_view_args(char *argv[]);

Status open_files(char *filename);

Status do_view_operation(char *argv[]);

int endiness_convert(int size);

Status read_and_print_data(FILE *fp);

#endif